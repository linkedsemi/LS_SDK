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

void boot_flash_start_xip(void)
{
    pinmux_hal_flash_quad_init();
    hal_flashx_continuous_mode_start(&flash1);
    lsqspiv2_direct_quad_read_config(LSQSPIV2, false);
    
    lscache_cache_enable(1);
}

static bool boot_nonsecure(uint32_t *exe_addr, uint32_t offset)
{
    imageHeader_t header;
    boot_flash_read(offset, (uint8_t *)&header, sizeof(imageHeader_t));

    uint32_t crc = boot_crc32((uint8_t *)&header, sizeof(imageHeader_t) - sizeof(uint32_t));
    if (crc != header.header_crc)
        return false;

    if (SRAM1_ADDR > header.exe_addr) {
        // *exe_addr = header.exe_addr;
        *exe_addr = FLASH_BASE_ADDRESS + offset + sizeof(imageHeader_t); //0x100 : header size
        // boot_flash_start_xip(offset);
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

    boot_flash_start_xip();
    LOG_I("Xip started...");

    while (1) {
        uint32_t offset = IMAGE_OFFSET;
        uint32_t exe_addr;
        if (!boot_nonsecure(&exe_addr, offset)) {
            continue;
        }
        goto_next((void *)exe_addr);
    }
    return 0;
}
