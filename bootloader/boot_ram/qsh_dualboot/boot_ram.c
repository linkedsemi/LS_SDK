#include "platform.h"
#include "otp_config.h"
#include "boot_port.h"
#include "boot.h"
#include "log.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "reg_sysc_sec_cpu.h"
#include "reg_sysc_sec_awo.h"
#include "reg_sec_pmu_rg.h"
#include "ls_hal_otp_ctrl.h"
#include "ls_hal_flash.h"
#include "ls_hal_crc.h"
#include "ls_hal_qspiv2.h"
#include "ls_hal_cache.h"
#include "cpu.h"
#include "ls_dbg.h"
#include "hal_flash_int.h"
#include "field_manipulate.h"
// #include "ls_msp_qspiv2.h"
extern uint32_t __next_ram_size;
struct boot_otp otp_cfg;

#define FLASH_BASE_ADDRESS 0x8000000
#define IMAGE_OFFSET       0x10000 //IMAGE_OFFSET = CONFIG_FLASH_BASE_ADDRESS - FLASH_BASE_ADDRESS - 0x100

/* ---- Minimal SBL flash environment support (dual-slot boot) ----
 * The sbl_env partition (plain text key=value, written by code-mgt
 * fwsetenv / activation) selects which A/B app slot to boot. Format
 * mirrors openbmc/secureboot-rom boot.c parse_config; only the keys
 * needed for booting are parsed here (crypto/secure-boot paths of
 * secureboot-rom are intentionally not ported). */
struct boot_env
{
    char dual_app_active_image;
    uint32_t app_a_partition_offset;
    uint32_t app_b_partition_offset;
    /* Boot-attempt bookkeeping, mirroring openbmc/phosphor-bmc-code-mgt/zephyr/
     * fw_env.h. Both are optional: an environment written before this feature
     * simply has neither key, and the defaults below keep the pre-existing
     * behaviour (boot the selected slot, no counting) until the running image
     * confirms itself for the first time. */
    char dual_app_confirmed;   /* 0 when absent */
    uint32_t dual_app_try_count;
};

/* Consecutive boots of the active slot that did not confirm before the SBL
 * gives up on it and switches to the other one. The application resets the
 * counter the moment it reaches its confirm point, so a healthy image always
 * restarts from 0 and is never switched away; only an image that dies before
 * that point accumulates, which is exactly the failure mode this guards. */
#define BOOT_MAX_SLOT_TRIES 3

/* Defaults mirror the production A/B layout: app A at 0x10000 (also the
 * legacy fixed offset) and app B at 0x1110000. The two slot regions are
 * 0x1100000 apart, each holding app at +0x10000 and rofs at +0xD00000.
 * Keep in sync with openbmc/phosphor-bmc-code-mgt/zephyr/fw_env.h; with an
 * erased environment these defaults must still boot slot A directly instead
 * of failing over to the legacy offset every time. */
#define DEFAULT_APP_A_OFFSET 0x00010000
#define DEFAULT_APP_B_OFFSET 0x01110000

static char sbl_env_buf[BOOT_FLASH_SBL_ENV_SIZE];

/* Text length held in sbl_env_buf (excluding the terminating NUL) and whether
 * the partition actually looks like a key=value environment. Both are captured
 * by load_boot_env() BEFORE anything is parsed, because the writer below has to
 * see the partition exactly as code-mgt left it: the patcher looks for "\n"
 * terminators and the writer programs "sbl_env_len + 1" bytes. Deriving either
 * one after parsing is not safe -- see parse_boot_env(). */
static size_t sbl_env_len;
static bool sbl_env_ready;
static bool sbl_env_dirty;   /* a key was staged and not yet programmed */

static char *env_trim(char *s)
{
    char *end;
    while (*s == ' ' || *s == '\t') s++;
    if (*s == '\0') return s;
    end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t')) end--;
    end[1] = '\0';
    return s;
}

static uint32_t env_hex(const char *s)
{
    uint32_t v = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) s += 2;
    while (*s) {
        char c = *s++;
        int d;
        if (c >= '0' && c <= '9') d = c - '0';
        else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
        else break;
        v = v * 16 + d;
    }
    return v;
}

/* Parse the environment text WITHOUT modifying it.
 *
 * This must stay read-only on `buf`: the whole writer below (env_patch_key(),
 * env_append_key(), boot_env_store()) operates on the raw partition text in
 * place. An earlier version split lines destructively -- *nl = '\0' on every
 * '\n' -- which left sbl_env_buf holding just the first line plus a NUL. The
 * consequences were silent and severe:
 *   - env_patch_key() walked a buffer with no line terminators left, so every
 *     key looked absent and every write silently degraded to append;
 *   - boot_env_store() measured the length with strlen(), so it programmed
 *     "dual_sec_active_image" + the appended key only (53 bytes observed) over
 *     the top of the partition, erasing the other ~605 bytes of the table.
 * code-mgt then found an unparsable environment and reset it to defaults,
 * taking dual_app_active_image back to 'a' while the board was running slot B.
 *
 * So: copy one line at a time into a small scratch buffer, as code-mgt's
 * fw_env_load() does, and leave the partition text alone.
 *
 * Accepts both selector spellings: code-mgt writes the app_* family and the
 * production secureboot-rom the sec_* family, with identical values, so either
 * may be read. */
static void parse_boot_env(const char *buf, size_t len, struct boot_env *env)
{
    char line[64];

    env->dual_app_active_image = 'a';
    env->app_a_partition_offset = DEFAULT_APP_A_OFFSET;
    env->app_b_partition_offset = DEFAULT_APP_B_OFFSET;
    env->dual_app_confirmed = 0;      /* absent -> main() treats it as "assume the target" */
    env->dual_app_try_count = 0;

    size_t i = 0;
    while (i < len) {
        size_t eol = i;
        size_t n;

        while (eol < len && buf[eol] != '\n') {
            eol++;
        }
        n = eol - i;
        if (n >= sizeof(line)) {
            n = sizeof(line) - 1;
        }
        memcpy(line, buf + i, n);
        line[n] = '\0';

        char *eq = strchr(line, '=');
        if (eq) {
            *eq = '\0';
            char *key = env_trim(line);
            char *val = env_trim(eq + 1);   /* also drops the trailing CR */
            if ((0 == strcmp(key, "dual_app_active_image") ||
                 0 == strcmp(key, "dual_sec_active_image")) && val[0]) {
                env->dual_app_active_image = val[0];
            } else if (0 == strcmp(key, "app_a_partition_offset") ||
                       0 == strcmp(key, "sec_a_partition_offset")) {
                env->app_a_partition_offset = env_hex(val);
            } else if (0 == strcmp(key, "app_b_partition_offset") ||
                       0 == strcmp(key, "sec_b_partition_offset")) {
                env->app_b_partition_offset = env_hex(val);
            } else if (0 == strcmp(key, "dual_app_confirmed")) {
                env->dual_app_confirmed = val[0];
            } else if (0 == strcmp(key, "dual_app_try_count")) {
                env->dual_app_try_count = env_hex(val);
            }
        }

        i = (eol < len) ? eol + 1 : len;
    }
}

static struct boot_env g_boot_env; /* last parsed sbl_env, see boot_xip_rebase() */

/* Redirect the QSPI direct-read (XIP) window onto the copy of the app stored at
 * `slot_offset`.
 *
 * The app image is XIP-linked to run at FLASH_BASE_ADDRESS + IMAGE_OFFSET, and
 * that link address is what the CPU must branch to whichever slot is active.
 * A slot whose copy lives in the flash's second 16MB bank (slot B at 0x1110000)
 * is unreachable by plain addressing, so the window is moved instead: EAR
 * selects the 16MB bank and BACKUP_OFFSET the 16KB-granular delta inside it.
 * Mirrors secureboot-rom rv32/qsh/bsp.c boot_flash_start_xip().
 * Returns false when the offsets are not usable (caller falls back). */
static bool boot_xip_rebase(uint32_t slot_offset)
{
    uint32_t ref = g_boot_env.app_a_partition_offset; /* link base offset */
    uint32_t in_bank = slot_offset % (16 * 1024 * 1024);

    if (in_bank > ref) {
        uint32_t delta = in_bank - ref;
        if (0 != (delta % (16 * 1024))) {
            LOG_E("xip rebase: slot 0x%x delta 0x%x not 16K aligned",
                  slot_offset, delta);
            return false;
        }
        hal_flashx_write_ear(&flash1, 1);
        LSQSPIV2->BACKUP_OFFSET = delta >> 14;
        LOG_I("xip rebase: ear=1 backup_offset=0x%x (slot 0x%x)",
              LSQSPIV2->BACKUP_OFFSET << 14, slot_offset);
    } else {
        hal_flashx_write_ear(&flash1, 0);
        LSQSPIV2->BACKUP_OFFSET = 0;
        LOG_I("xip rebase: ear=0 backup_offset=0 (slot 0x%x)", slot_offset);
    }
    /* Enable the cache only now, with the window already pointed at this
     * slot's copy (mirrors secureboot-rom bsp.c). */
    lscache_cache_enable(1);
    return true;
}

/* True when the partition holds something env-shaped. A freshly erased NOR
 * sector reads back as all 0xFF, which contains no '=' at all; writing boot
 * bookkeeping into that would leave code-mgt with a two-key environment it
 * cannot use (every other field would read back as 0). */
static bool env_has_keys(const char *buf, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        if (buf[i] == '=') {
            return true;
        }
    }
    return false;
}

static void load_boot_env(struct boot_env *env)
{
    const char *nul;

    boot_flash_read(BOOT_FLASH_SBL_ENV_ADDR, (uint8_t *)sbl_env_buf,
                    sizeof(sbl_env_buf));
    sbl_env_buf[sizeof(sbl_env_buf) - 1] = '\0';

    /* Capture the text length BEFORE parsing -- parse_boot_env() deliberately
     * leaves the text alone, and the writer below needs the real extent (not a
     * strlen(), which an all-0xFF partition would report as ~8KB of garbage). */
    nul = memchr(sbl_env_buf, '\0', sizeof(sbl_env_buf));
    sbl_env_len = (nul != NULL) ? (size_t)(nul - sbl_env_buf)
                                : sizeof(sbl_env_buf) - 1;
    sbl_env_ready = env_has_keys(sbl_env_buf, sbl_env_len);
    sbl_env_dirty = false;
    if (!sbl_env_ready) {
        sbl_env_len = 0;
        sbl_env_buf[0] = '\0';
    }

    parse_boot_env(sbl_env_buf, sbl_env_len, env);
    LOG_I("sbl_env: %u bytes, dual_app=%c app_a=0x%x app_b=0x%x confirmed=%c tries=%u",
          (unsigned)sbl_env_len, env->dual_app_active_image,
          env->app_a_partition_offset, env->app_b_partition_offset,
          env->dual_app_confirmed ? env->dual_app_confirmed : '-',
          env->dual_app_try_count);
}

/* ------------------------------------------------------------------
 * Minimal sbl_env writer: patch one key in place.
 *
 * The SBL deliberately does NOT re-serialize the whole table. code-mgt owns
 * that format (openbmc/phosphor-bmc-code-mgt/zephyr/fw_env.c serializes 22
 * keys, most of which this SBL does not even model), and a second full writer
 * here would drift from it the moment a key is added. Patching the two keys
 * the boot logic owns keeps every other byte exactly as code-mgt wrote it.
 *
 * A replacement value must therefore have the same width as the one it
 * replaces -- 1 char for a slot key, "0x%08x" for a hex key, both fixed by
 * fw_env_store() -- so the text never grows and the rest of the partition is
 * untouched. Returns false when the key is absent (the caller appends it).
 * ------------------------------------------------------------------ */
static bool env_patch_key(const char *key, const char *val)
{
    size_t keylen = strlen(key);
    char *p = sbl_env_buf;

    while (*p) {
        char *nl = strchr(p, '\n');
        char *line = p;

        if (nl) {
            *nl = '\0';
        }

        if (!strncmp(line, key, keylen) && line[keylen] == '=') {
            char *oldval = line + keylen + 1;
            /* Measure up to the line terminator only. sbl_env_buf keeps its
             * "\r\n" endings (that is the whole point of parsing it
             * non-destructively), so a plain strlen() would count the CR and
             * report every value one byte wider than its replacement. */
            size_t oldlen = strcspn(oldval, "\r\n");

            if (oldlen == strlen(val)) {
                memcpy(oldval, val, oldlen);
            } else {
                LOG_E("env: %s value width %u != %u, not patching", key,
                      (unsigned)strlen(val), (unsigned)oldlen);
            }
            if (nl) {
                *nl = '\n';
            }
            return true;
        }

        if (!nl) {
            break;
        }
        *nl = '\n';
        p = nl + 1;
    }
    return false;
}

/* Append "key=value\r\n" to the env text, keeping the trailing NUL. */
static bool env_append_key(const char *key, const char *val)
{
    int n;

    if (!sbl_env_ready || sbl_env_len + 1 >= sizeof(sbl_env_buf)) {
        return false;
    }
    n = snprintf(sbl_env_buf + sbl_env_len, sizeof(sbl_env_buf) - sbl_env_len,
                 "%s=%s\r\n", key, val);
    if (n <= 0 || (size_t)n >= sizeof(sbl_env_buf) - sbl_env_len) {
        return false;
    }
    sbl_env_len += (size_t)n;
    return true;
}

/* Program the patched env text back, then read it back and compare. A failure
 * is NOT fatal to the boot: the caller boots the slot it already picked, we
 * only lose the fallback across the next reset. */
static bool boot_env_store(void)
{
    uint32_t len = (uint32_t)sbl_env_len + 1; /* include the NUL */
    uint32_t off = 0;
    static uint8_t verify[BOOT_FLASH_SBL_ENV_SIZE];

    hal_flash_sector_erase(BOOT_FLASH_SBL_ENV_ADDR);
    hal_flash_sector_erase(BOOT_FLASH_SBL_ENV_ADDR + 4096);

    /* One page program per 256-byte page. hal_flash_multi_io_page_program()
     * issues exactly one program command (hal_flashx_quad_page_program() in
     * ls_hal_flash_qspiv2.c does a single hal_flashx_program_operation()), and a
     * page program that crosses a page boundary wraps inside the page instead
     * of continuing -- the reference flashProgram() in
     * examples/utility/flash_prog splits the same way. The env text is ~660
     * bytes, so this is 3 pages, not one. */
    while (off < len) {
        uint32_t page = BOOT_FLASH_SBL_ENV_ADDR + off;
        uint32_t chunk = 256u - (page & 0xffu);

        if (chunk > len - off) {
            chunk = len - off;
        }
        hal_flash_multi_io_page_program(page, (uint8_t *)sbl_env_buf + off,
                                        (uint16_t)chunk);
        off += chunk;
    }

    boot_flash_read(BOOT_FLASH_SBL_ENV_ADDR, verify, len);
    if (0 != memcmp(verify, sbl_env_buf, len)) {
        LOG_E("env: read-back mismatch, not trusted");
        return false;
    }
    LOG_I("env: stored %u bytes", len);
    return true;
}

/* Stage one key into the in-memory environment text: patched in place when the
 * key already exists, appended otherwise. Nothing is programmed yet -- call
 * boot_env_flush() after staging a group of related keys, so the group costs
 * one erase + one program instead of one of each per key. */
static bool boot_env_stage(const char *key, const char *val)
{
    if (!sbl_env_ready) {
        /* Never build a partial environment on top of an erased/foreign
         * partition: code-mgmt would read the keys it recognises and leave
         * every other field at zero. Booting is unaffected -- the defaults
         * parsed out of the empty buffer already describe slot A with the right
         * offsets. */
        LOG_E("env: %s not staged, sbl_env holds no environment yet", key);
        return false;
    }
    if (!env_patch_key(key, val) && !env_append_key(key, val)) {
        LOG_E("env: cannot set %s (no room)", key);
        return false;
    }
    sbl_env_dirty = true;
    return true;
}

/* Program the staged text back. Does nothing when no key was staged, which is
 * the steady state (a confirmed image on the slot it already confirmed). A
 * failure is not fatal: the caller boots the slot it already picked and we only
 * lose the fallback across the next reset. */
static void boot_env_flush(void)
{
    if (sbl_env_dirty) {
        (void)boot_env_store();
    }
}

void boot_flash_read(uint32_t offset, uint8_t *data, uint32_t length)
{
    hal_flash_multi_io_read(offset, data, length);
}

void boot_otp_read(uint32_t offset, uint8_t *data, uint32_t length)
{
    HAL_OTP_Read(offset, data, length);
}

uint32_t boot_crc32(uint8_t *data, uint32_t length)
{
    return HAL_LSCRC_CRC_CALC(&CRC32_PARAM, data, length);
}

/* Prepare the QSPI direct-read (XIP) path. The cache is deliberately NOT
 * enabled here: boot_xip_rebase() turns it on after the window has been
 * pointed at the slot being booted, so no line can be cached from the wrong
 * offset (secureboot-rom orders it the same way). */
void boot_flash_start_xip(void)
{
    pinmux_hal_flash_quad_init();
    hal_flashx_continuous_mode_start(&flash1);
    lsqspiv2_direct_quad_read_config(LSQSPIV2, false);
}

static bool boot_nonsecure(uint32_t *exe_addr, uint32_t offset)
{
    imageHeader_t header;
    boot_flash_read(offset, (uint8_t *)&header, sizeof(imageHeader_t));

    uint32_t crc = boot_crc32((uint8_t *)&header, sizeof(imageHeader_t) - sizeof(uint32_t));
    if (crc != header.header_crc)
        return false;

    if (header.exe_addr == 0x0) {
        /* XIP image: it is linked to run at FLASH_BASE_ADDRESS + IMAGE_OFFSET,
         * so the same binary can serve both slots only if the QSPI direct-read
         * window is moved onto this slot's copy first. */
        if (!boot_xip_rebase(offset)) {
            return false;
        }
        *exe_addr = FLASH_BASE_ADDRESS + offset + header.offset; //0x100 : header size
        /* Normalise back to the link address: for slot B the formula above
         * yields a second-16MB-bank address, which the rebased window maps
         * back down. Mirrors secureboot-rom boot.c goto_next(). */
        if ((*exe_addr - FLASH_BASE_ADDRESS) > (16 * 1024 * 1024)) {
            *exe_addr -= (16 * 1024 * 1024) + (LSQSPIV2->BACKUP_OFFSET << 14);
        }
    } else {
        if ((uint32_t)&__next_ram_size < header.length) {
            return false;
        }
        *exe_addr = header.exe_addr;
        boot_flash_read(offset + header.offset, (uint8_t *)header.exe_addr, header.length);
    }
    return true;
}

void goto_next(void *exe_addr)
{
    LOG_I("GoTo Next Addr : 0x%x", exe_addr);
    DELAY_US(1000);
    void (*goto_sbl)();
    goto_sbl = (void *)exe_addr;
    __set_MTVT((uint32_t)0);
    goto_sbl();
}

static void set_runtime_cfg()
{
    log_en = otp_cfg.startup_param.log_uart_en;
    if (log_en) {
        log_output_fn = log_output;
        log_hex_output_fn = log_hex_output;
    }

//    pinmux_hal_flash_quad_init();
}

static void boot_flash_swint_init()
{
    MODIFY_REG(CLIC->CLICCFG,CLIC_CLICCFG_NLBIT_Msk,0xf<<CLIC_CLICCFG_NLBIT_Pos);
    rv_set_int_isr(FLASH_SWINT_NUM,FLASH_SWINT_HANDLER);
    CLIC->CLICINT[FLASH_SWINT_NUM].ATTR = 1 << CLIC_INTATTR_TRIG_Pos;
    csi_vic_set_prio(FLASH_SWINT_NUM,0xf);
    csi_vic_clear_pending_irq(FLASH_SWINT_NUM);
    csi_vic_enable_irq(FLASH_SWINT_NUM);
}

void platform_init()
{
    __enable_irq();

    boot_otp_read(0x0, (uint8_t *)&otp_cfg, sizeof(otp_cfg));
    set_runtime_cfg();

    LSCACHE->CCR = FIELD_BUILD(LSCACHE_EN, 0);
    dpll_qspi_clk_config_and_clk_switch();

    LOG_INIT();

    struct hal_flash_env *flash[] = {
        &flash1,
#if defined(LSQSPIV2_2_ENABLED)
        &flash2,
#endif
    };

    flash1.reg = (void *)LSQSPIV2;
#if defined(LSQSPIV2_2_ENABLED)
    flash2.reg = (void *)LSQSPIV2_2;
#endif

    for (int i = 0; i < sizeof(flash) / sizeof(flash[0]); i++) {
        flash[i]->dual_mode_only = false;
        flash[i]->continuous_mode_enable = false;
        flash[i]->writing = false;
        flash[i]->suspend_count = 0;
        flash[i]->continuous_mode_on = false;
        flash[i]->addr4b = false;

        pinmux_hal_flashx_quad_init(flash[i]->reg);

        hal_flashx_init(flash[i]);
        clk_flashx_init(flash[i]->reg);

        hal_flashx_software_reset(flash[i]);
        DELAY_US(500);
        hal_flashx_release_from_deep_power_down(flash[i]);
        DELAY_US(100);

        boot_flash_swint_init();
        uint8_t jedec_id[3] = {};
        uint32_t size;
        hal_flashx_read_id(&flash1, jedec_id);
        if ((jedec_id[0] != 0) && (jedec_id[1] != 0) && (jedec_id[2] != 0)) {
            size = (2 << (jedec_id[2] - 1));
            if (size > (16 << 20)) {
                flash1.addr4b = true;
            }
        } else {
            while(1);
        }
    }
    // hal_flash_qe_status_read_and_set();
    HAL_LSCRC_Init();
}

int main()
{
    platform_init();

    /* The SoC keeps a 4-bit "how many times have we already tried to boot"
     * counter in SEC_PMU (STARTUP_PART_FLAG + BOOTRAM_STARTUP_PART_FLAG): the
     * ROM-orchestrated boot chain sets one bit per attempt, flips
     * dual_sec_active_image for the non-zero values and, once all four bits are
     * set, refuses both slots and falls into UART boot. Nothing ever reset it
     * on a successful boot, and neither a warm reset nor the app CPU can: the
     * field survives resets and SEC_PMU is only writable from this (secure)
     * core -- the app's attempt in soc_late_init_hook() is silently dropped.
     * The board therefore stopped booting after a handful of resets and only
     * came back after removing power.
     *
     * Getting here means the boot chain did find and hand over to this stage,
     * so the attempt is over: hand the counter back to zero. That also stops
     * the chain from rewriting dual_sec_active_image behind code-mgt's back
     * (the flip only happens while the counter is non-zero), keeping the
     * sbl_env the single source of truth for the active slot. */
    CLEAR_BIT(SEC_PMU->SFT_CTRL[SFT_CTRL_REG_NUM_RESET_FLAG],
              STARTUP_PART_FLAG_MASK);
    CLEAR_BIT(SEC_PMU->SFT_CTRL[SFT_CTRL_REG_NUM_RESET_FLAG],
              BOOTRAM_STARTUP_PART_FLAG_MASK);

    boot_flash_start_xip();
    LOG_I("Xip started...");

    struct boot_env env;
    load_boot_env(&env);
    g_boot_env = env;

    /* Boot the app slot selected by dual_app_active_image (code-mgt
         * flashes the OPPOSITE slot and flips the env before rebooting).
         * On failure fall back to the other slot, then to the legacy fixed
         * offset (0x10000, the pre-dual-slot layout). */
        uint32_t slot_off[2] = {env.app_a_partition_offset,
                               env.app_b_partition_offset};

        /* ---- Confirm-and-fallback ----------------------------------------
         *
         * The header CRC below only proves the image is INTACT. A brand new image
         * can pass it and still die on its first instructions, and then nothing
         * switches slots: this stage has already jumped, and on the next reset it
         * would pick the same slot again -- a boot loop that only removing power
         * breaks, while code-mgt already reported the update as successful.
         *
         * So count attempts. Every boot of the active slot that the application
         * did not confirm (see fw_env_confirm_running_slot()) increments the
         * counter; the application resets it as soon as it reaches its confirm
         * point, so a healthy image restarts from 0 every single time and is never
         * switched away. Once the counter passes BOOT_MAX_SLOT_TRIES the image is
         * considered bad and the other slot is selected instead -- preferring the
         * one that last confirmed, if that is not the slot we are leaving.
         */
        char target = env.dual_app_active_image;
        char confirmed = env.dual_app_confirmed;
        uint32_t tries = env.dual_app_try_count;

        if (target != 'a' && target != 'b') {
            LOG_E("sbl_env: bad dual_app_active_image '%c', assuming slot a", target);
            target = 'a';
        }
        if (confirmed != 'a' && confirmed != 'b') {
            /* No confirmed key yet: this environment predates the feature, or the
             * image has never confirmed. Treat the current target as good so the
             * boot behaviour is bit-for-bit what it was before these keys existed. */
            confirmed = target;
        }

        tries++;
        if (tries > BOOT_MAX_SLOT_TRIES) {
            char other = (target == 'a') ? 'b' : 'a';
            char next = (confirmed != target) ? confirmed : other;
            char t[2];
            char c[16];

            LOG_W("slot %c did not confirm in %u attempts, switching to slot %c",
                  target, tries, next);
            target = next;
            tries = 0;
            /* t must be filled from the NEW target, after the assignment above.
             * Initializing it from target at declaration time captured the slot
             * being left, so both selector writes became no-ops (b -> b): the
             * counter moved, the rollback did not stick, and the next boot went
             * straight back into the abandoned slot. The read-back check in
             * boot_env_store() cannot catch that -- it verifies the bytes it was
             * handed, and those bytes were the wrong ones. */
            t[0] = target;
            t[1] = '\0';
            snprintf(c, sizeof(c), "0x%08x", (unsigned int)tries);

            /* Order matters. The counter is zeroed FIRST. Flipping the selector
             * while a stale count still sits at BOOT_MAX_SLOT_TRIES means that a
             * power cut between the two writes leaves the next boot tripping the
             * fallback again and flipping straight back into the slot we just
             * abandoned -- the rollback undoes itself. Zeroed first, an
             * interruption instead lands on "fresh budget, old selector": the bad
             * slot simply gets its full BOOT_MAX_SLOT_TRIES attempts before being
             * left again.
             *
             * Both selector spellings are flipped: this SBL reads app_*, the
             * production secureboot-rom reads sec_*, and fw_env_set_by_key() keeps
             * them in lockstep. */
            boot_env_stage("dual_app_try_count", c);
            boot_env_stage("dual_app_active_image", t);
            boot_env_stage("dual_sec_active_image", t);
        } else if (tries > 1 || confirmed != target) {
            /* Persist the counter even when we keep the slot: it is the only place
             * the attempt count survives the reset we are about to take. Skipped
             * entirely when it is still zero, i.e. once the image has confirmed. */
            char c[16];

            snprintf(c, sizeof(c), "0x%08x", (unsigned int)tries);
            boot_env_stage("dual_app_try_count", c);
        }
        /* One erase + one program for the whole group; a no-op in steady state. */
        boot_env_flush();

        LOG_I("boot decision: slot %c (confirmed=%c tries=%u/%u)", target, confirmed,
              tries, (unsigned)BOOT_MAX_SLOT_TRIES);

        int first = (target == 'b') ? 1 : 0;

    while (1) {
        uint32_t exe_addr;
        if (boot_nonsecure(&exe_addr, slot_off[first])) {
            LOG_I("Booting slot %c @ 0x%x", 'a' + first, slot_off[first]);
            goto_next((void *)exe_addr);
        }
        LOG_E("slot %c @ 0x%x boot failed, trying fallback",
              'a' + first, slot_off[first]);
        if (boot_nonsecure(&exe_addr, slot_off[first ^ 1])) {
            LOG_I("Booting fallback slot %c @ 0x%x", 'a' + (first ^ 1),
                  slot_off[first ^ 1]);
            goto_next((void *)exe_addr);
        }
        LOG_E("both slots failed, trying legacy offset 0x%x", IMAGE_OFFSET);
        DELAY_US(1000 * 1000);
        if (boot_nonsecure(&exe_addr, IMAGE_OFFSET)) {
            goto_next((void *)exe_addr);
        }
        DELAY_US(1000 * 1000);
    }
    return 0;
}
