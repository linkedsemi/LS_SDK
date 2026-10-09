#include "platform.h"
#include "otp_config.h"
#include "boot_port.h"
#include "boot.h"
#include "log.h"
#include <ctype.h>
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
};

/* Defaults mirror the production A/B layout: app A at 0x10000 (also the
 * legacy fixed offset) and app B at 0x1110000. The two slot regions are
 * 0x1100000 apart, each holding app at +0x10000 and rofs at +0xD00000.
 * Keep in sync with openbmc/phosphor-bmc-code-mgt/zephyr/fw_env.h; with an
 * erased environment these defaults must still boot slot A directly instead
 * of failing over to the legacy offset every time. */
#define DEFAULT_APP_A_OFFSET 0x00010000
#define DEFAULT_APP_B_OFFSET 0x01110000

static char sbl_env_buf[BOOT_FLASH_SBL_ENV_SIZE];

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

static void parse_boot_env(char *buf, struct boot_env *env)
{
    env->dual_app_active_image = 'a';
    env->app_a_partition_offset = DEFAULT_APP_A_OFFSET;
    env->app_b_partition_offset = DEFAULT_APP_B_OFFSET;

    char *p = buf;
    while (*p) {
        char *nl = strchr(p, '\n');
        if (nl) *nl = '\0';
        char *eq = strchr(p, '=');
        if (eq) {
            *eq = '\0';
            char *key = env_trim(p);
            char *val = env_trim(eq + 1);
            /* Accept both spellings: code-mgt writes the app_* family and the
             * production secureboot-rom the sec_* family, with identical
             * values, so either may be read. */
            if ((0 == strcmp(key, "dual_app_active_image") ||
                 0 == strcmp(key, "dual_sec_active_image")) && val[0]) {
                env->dual_app_active_image = val[0];
            } else if (0 == strcmp(key, "app_a_partition_offset") ||
                       0 == strcmp(key, "sec_a_partition_offset")) {
                env->app_a_partition_offset = env_hex(val);
            } else if (0 == strcmp(key, "app_b_partition_offset") ||
                       0 == strcmp(key, "sec_b_partition_offset")) {
                env->app_b_partition_offset = env_hex(val);
            }
        }
        if (!nl) break;
        p = nl + 1;
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

static void load_boot_env(struct boot_env *env)
{
    boot_flash_read(BOOT_FLASH_SBL_ENV_ADDR, (uint8_t *)sbl_env_buf,
                    sizeof(sbl_env_buf));
    sbl_env_buf[sizeof(sbl_env_buf) - 1] = '\0';
    parse_boot_env(sbl_env_buf, env);
    LOG_I("sbl_env: dual_app=%c app_a=0x%x app_b=0x%x",
          env->dual_app_active_image, env->app_a_partition_offset,
          env->app_b_partition_offset);
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
    int first = (env.dual_app_active_image == 'b') ? 1 : 0;

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
