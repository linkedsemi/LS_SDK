#include "platform.h"
#include "boot_port.h"
#include "boot.h"
#include "log.h"
#include <ctype.h>
#include "reg_sysc_sec_cpu.h"
#include "reg_sysc_sec_awo.h"
#include "reg_sec_pmu_rg.h"
#include "ls_hal_flash.h"
#include "ls_hal_crc.h"
#include "ls_hal_qspiv2.h"
#include "ls_hal_cache.h"
#include "ls_dbg.h"

extern uint32_t __next_ram_size;

__attribute__((aligned(4))) uint8_t temp_buf[TEMP_BUF_SIZE];

void boot_flash_read(uint32_t offset, uint8_t *data, uint32_t length)
{
    hal_flash_fast_read(offset, data, length);
}

uint32_t boot_crc32(uint8_t *data, uint32_t length)
{
    return HAL_LSCRC_CRC_CALC(&CRC32_PARAM, data, length);
}

void boot_flash_start_xip(uint32_t offset)
{
    lsqspiv2_direct_quad_read_config(LSQSPIV2, false);
#if 0
    LSQSPIV2->BACKUP_OFFSET = offset >> 14;
#endif
    lscache_cache_enable(1);
}

static bool boot_nonsecure(uint32_t *exe_addr, uint32_t offset)
{
    imageHeader_t header;
    boot_flash_read(offset, (uint8_t *)&header, sizeof(imageHeader_t));

    uint32_t crc = boot_crc32((uint8_t *)&header, sizeof(imageHeader_t) - sizeof(uint32_t));
    if (crc != header.header_crc)
        return false;

    LOG_I("flash_image --exe_addr:0x%x", header.exe_addr);
    if (SRAM1_ADDR > header.exe_addr) {
        *exe_addr = header.exe_addr;
        boot_flash_start_xip(offset);
    } else {
        if ((uint32_t)&__next_ram_size < header.length) {
            LOG_I("__next_ram_size: 0x%x < image size: 0x%x", (uint32_t)&__next_ram_size, header.length);
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

void rom_delay(uint32_t us)
{
    uint32_t CLK_MHZ = 0;
    switch (REG_FIELD_RD(SYSC_SEC_AWO->PD_AWO_CLK_CTRL0, SYSC_SEC_AWO_CLK_SEL_HBUS))
    {
    case SEC_AWO_REG_CLK_SEL_HSI:
    case SEC_AWO_REG_CLK_SEL_HSE:
    case SEC_AWO_REG_CLK_SEL_CLIKIN:
        CLK_MHZ = 25;
        break;
    case SEC_AWO_REG_CLK_SEL_DPLL_DIV:
        CLK_MHZ = 600 / (REG_FIELD_RD(SYSC_SEC_AWO->PD_AWO_CLK_CTRL0, SYSC_SEC_AWO_CLK_DIV_PARA_HBUS_M1) + 1);
        break;
    case SEC_AWO_REG_CLK_SEL_DPLL_600M:
        CLK_MHZ = 600;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
#ifdef FPGA_TEST
    CLK_MHZ = SDK_HCLK_MHZ;
#endif
    rv32_delay_asm((us) * (CLK_MHZ) / 8, 1);
}

static void set_runtime_cfg()
{
    if ((0 == READ_BIT(SYSC_SEC_AWO->DPLL_LOCK, SYSC_SEC_AWO_DPLL1_LOCK_MASK))
        && (0 == READ_BIT(SYSC_SEC_AWO->DPLL_LOCK, SYSC_SEC_AWO_DPLL2_LOCK_MASK))) {
    } else {
        app_cpu_reset();
    }

    pinmux_hal_flash_quad_init();
    flash1.reg = (void *)LSQSPIV2;
    flash1.dual_mode_only = false;
    flash1.continuous_mode_enable = false;
    flash1.writing = false;
    flash1.suspend_count = 0;
    flash1.continuous_mode_on = false;
    flash1.addr4b = false;
    hal_flash_init();
    clk_flash_init();

    LOG_I("flash reset...");
    hal_flash_release_from_deep_power_down();
    rom_delay(20);
    hal_flash_software_reset();
    rom_delay(200);

    hal_flash_qe_status_read_and_set();
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

    set_runtime_cfg();
    LOG_I("OTP CFG_DATA:");
    for (uint32_t i = 0; i < OTP_LOG_WORD_LENGTH; i += 4)
        LOG_I("0x%02x:\t0x%08x\t0x%08x\t0x%08x\t0x%08x", i * 4, ptr[i], ptr[i + 1], ptr[i + 2], ptr[i + 3]);

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

    HAL_LSCRC_Init();
}

int main()
{
    platform_init();

    LOG_I("Flash Boot...");

    while (1) {
        uint32_t offset = 64 * 1024;
        uint32_t exe_addr;
        if (!boot_nonsecure(&exe_addr, offset)) {
            continue;
        }
        goto_next((void *)exe_addr);
    }
    return 0;
}
