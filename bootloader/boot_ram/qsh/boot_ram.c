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

struct boot_otp otp_cfg;

/*
name     address   size
bootram  0x8000000 64(kB)
image    0x8010000
*/
#define IMAGE_OFFSET       0x10000

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

void boot_flash_start_xip(uint32_t offset)
{
    flash1.continuous_mode_enable = true;
    flash1.continuous_mode_on = false;
    hal_flashx_init(&flash1);
    hal_flashx_continuous_mode_start(&flash1);
    lsqspiv2_direct_quad_read_config(LSQSPIV2, true);

    REG_FIELD_WR(LSQSPIV2->QSPI_CTRL1, LSQSPIV2_MODE_DAC, 1);
    MODIFY_REG(LSQSPIV2->QSPI_CTRL1, LSQSPIV2_CAP_DLY_MASK, 0 << LSQSPIV2_CAP_DLY_POS);

    pinmux_hal_flash_quad_init();
    lscache_cache_enable(1);
}

static bool boot_nonsecure(uint32_t *exe_addr, uint32_t offset)
{
    imageHeader_t header;
    boot_flash_read(offset, (uint8_t *)&header, sizeof(imageHeader_t));

    uint32_t crc = boot_crc32((uint8_t *)&header, sizeof(imageHeader_t) - sizeof(uint32_t));
    if (crc != header.header_crc)
        return false;

    if (header.exe_addr == 0x0) {
        *exe_addr = FLASH_CACHE_ADDR + IMAGE_OFFSET + header.offset;
        boot_flash_start_xip(offset);
    } else {
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

    flash1.reg = (void *)LSQSPIV2;
    flash1.dual_mode_only = false;
    flash1.continuous_mode_enable = false;
    flash1.writing = false;
    flash1.suspend_count = 0;
    flash1.continuous_mode_on = false;
    flash1.addr4b = false;

   // pinmux_hal_flash_quad_init();
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

    boot_flash_swint_init();
    uint8_t jedec_id[3] = {};
    hal_flashx_read_id(&flash1, jedec_id);
    if ((jedec_id[0] != 0) && (jedec_id[1] != 0) && (jedec_id[2] != 0)) {
        if ((2 << (jedec_id[2] - 1)) > (16 << 20)) {
            flash1.addr4b = true;
        }
    } else {
        while(1);
    }
    hal_flash_qe_status_read_and_set();
    HAL_LSCRC_Init();
}

int main()
{
    platform_init();

    LOG_I("Flash Boot...");

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
