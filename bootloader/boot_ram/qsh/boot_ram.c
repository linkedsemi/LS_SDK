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

    // qspiv2_global_int_disable_fn = enter_critical;
    // qspiv2_global_int_restore_fn = exit_critical;

    flash1.reg = (void *)LSQSPIV2;
    flash1.dual_mode_only = false;
    flash1.continuous_mode_enable = false;
    flash1.writing = false;
    flash1.suspend_count = 0;
    flash1.continuous_mode_on = false;
    flash1.addr4b = false;

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

static void cpu_600M_ahb_300M_qspi_200M_init()
{
    SYSC_SEC_AWO->PD_AWO_CLK_CTRL1 = FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_PBUS0, 0x0)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_PBUS1, 0x0)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_PBUS2, 0x0)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_PBUS3, 0x0)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_PBUS4, 0x3)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_DIV_HBUS, 0x1)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_OTP, 0x1);
    SYSC_SEC_AWO->CLKG_DIV_DPLL = SYSC_SEC_AWO_CLKG_DIV_DPLL_CLR_MASK;
    SYSC_SEC_AWO->PD_AWO_CLK_CTRL0 = 
                                  // FIELD_BUILD(SYSC_SEC_AWO_CLK_DIV_PARA_HBUS_M1, 0x1)
                                     FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_HBUS, 0x1)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_HBUS_M1, 0x1) /* set ahb_clk = 1/2 * cpu_clk */
                                 //| FIELD_BUILD(SYSC_SEC_AWO_HSE_DCT_EN, 0)
                                   | FIELD_BUILD(SYSC_SEC_AWO_HBUS_FLT_CTRL, 0x9)
                                   | FIELD_BUILD(SYSC_SEC_AWO_QSPI_FLT_CTRL, 0x9)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_QSPI, 0x1)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_HBUS_FLT, 0x2)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_QSPI_FLT, 0x2);
    SYSC_SEC_AWO->CLKG_DIV_DPLL = SYSC_SEC_AWO_CLKG_DIV_DPLL_SET_MASK;
    SYSC_SEC_AWO->PD_AWO_CLK_CTRL0 =
                                  // FIELD_BUILD(SYSC_SEC_AWO_CLK_DIV_PARA_HBUS_M1, 0x1)
                                     FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_HBUS, 0x10)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_HBUS_M1, 0x1)
                                 //| FIELD_BUILD(SYSC_SEC_AWO_HSE_DCT_EN, 0)
                                   | FIELD_BUILD(SYSC_SEC_AWO_HBUS_FLT_CTRL, 0x9)
                                   | FIELD_BUILD(SYSC_SEC_AWO_QSPI_FLT_CTRL, 0x9)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_QSPI, 0x10)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_HBUS_FLT, 0x2)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_QSPI_FLT, 0x2);
}

static void enable_dpll()
{
    CLEAR_BIT(SYSC_SEC_AWO->DPLL1_CTRL1, SYSC_SEC_AWO_DPLL1_CTRL1_PLL1_CLKREF_SEL_MASK); /* clkin */
    SET_BIT(SYSC_SEC_AWO->DPLL1_CTRL1, SYSC_SEC_AWO_DPLL1_CTRL1_PLL1_EN_MASK); /* clr reset */
    SET_BIT(SYSC_SEC_AWO->DPLL1_CTRL1, SYSC_SEC_AWO_DPLL1_CTRL1_PLL1_RSTN_MASK); /* enable pll1 */
    while(0 == READ_BIT(SYSC_SEC_AWO->DPLL_LOCK, SYSC_SEC_AWO_DPLL1_LOCK_MASK));

    CLEAR_BIT(SYSC_SEC_AWO->DPLL2_CTRL1, SYSC_SEC_AWO_DPLL2_CTRL1_PLL2_CLKREF_SEL_MASK); /* clkin */
    SET_BIT(SYSC_SEC_AWO->DPLL2_CTRL1, SYSC_SEC_AWO_DPLL2_CTRL1_PLL2_EN_MASK); /* clr reset */
    SET_BIT(SYSC_SEC_AWO->DPLL2_CTRL1, SYSC_SEC_AWO_DPLL2_CTRL1_PLL2_RSTN_MASK); /* enable pll2 */
    while(0 == READ_BIT(SYSC_SEC_AWO->DPLL_LOCK, SYSC_SEC_AWO_DPLL2_LOCK_MASK));
}


void platform_init()
{
    __enable_irq();

    boot_otp_read(0x0, (uint8_t *)&otp_cfg, sizeof(otp_cfg));
    set_runtime_cfg();

    LSCACHE->CCR = FIELD_BUILD(LSCACHE_EN, 0);
    if ((0 == READ_BIT(SYSC_SEC_AWO->DPLL_LOCK, SYSC_SEC_AWO_DPLL1_LOCK_MASK))
        && (0 == READ_BIT(SYSC_SEC_AWO->DPLL_LOCK, SYSC_SEC_AWO_DPLL2_LOCK_MASK))) {
        enable_dpll();
        cpu_600M_ahb_300M_qspi_200M_init();
    }

    LOG_INIT();

    hal_flashx_init(&flash1);

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
