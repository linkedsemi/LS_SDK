
#include "compile_flag.h"
#include "platform.h"
#include "cpu.h"
#include "log.h"
#include "swint_call_asm.h"
#include "systick.h"
#include "exception_isr.h"
#include "ls_soc_gpio.h"
#include "ls_hal_flash.h"
#include "ls_msp_qspiv2.h"
#include "field_manipulate.h"
#include "per_func_mux.h"
#include "reg_sec_pmu_rg.h"
#include "reg_sysc_sec_awo.h"
#include "qsh.h"

#define PMU_CLK_VAL (SDK_HSE_USED << V33_RG_CLK_SET_HSE_POS | 1 << V33_RG_CLK_SET_HSI_POS | (!SDK_LSI_USED) << V33_RG_CLK_SET_LSE_POS)

__attribute__((aligned(64))) void (*interrupt_vector[IRQN_MAX])();
struct hal_flash_env flash1;

__attribute__((weak)) void SystemInit(){
    e906_init();
    // MODIFY_REG(V33_RG->TRIM0,V33_RG_HSE_CTRL_MASK,7<<V33_RG_HSE_CTRL_POS);
    // REG_FIELD_WR(V33_RG->RST_SFT, V33_RG_CLK_SEL_LS, SDK_LSI_USED ? 1 : 2);
    // V33_RG->PMU_SET_VAL = PMU_CLK_VAL;
    // V33_RG->PMU_SET_VAL = V33_RG_PMU_SET_TGGL_MASK | PMU_CLK_VAL;
    // V33_RG->PMU_SET_VAL = PMU_CLK_VAL;
    if(SDK_HSE_USED)
    {//delay for hse stabilization
        rv32_delay_asm(14400,1);
    }
    enable_global_irq();
}

__ALWAYS_STATIC_INLINE void set_trim_params()
{
    REG_FIELD_WR(SEC_PMU->MISC_CTRL0, SEC_PMU_RG_CLK_LDO1_VSEL, 0);
    REG_FIELD_WR(SEC_PMU->MISC_CTRL0, SEC_PMU_RG_CLK_LDO2_VSEL, 0);
}

__ALWAYS_STATIC_INLINE void enable_dpll()
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

__ALWAYS_STATIC_INLINE void cpu_600M_ahb_300M_qspi_200M_init()
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
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_QSPI, 0x10) /* dpll 200M */
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_HBUS_FLT, 0x2)
                                   | FIELD_BUILD(SYSC_SEC_AWO_CLK_SEL_QSPI_FLT, 0x2);
}

void XIP_BANNED_FUNC(dpll_qspi_clk_config_and_clk_switch,)
{
    if ((0 == READ_BIT(SYSC_SEC_AWO->DPLL_LOCK, SYSC_SEC_AWO_DPLL1_LOCK_MASK))
        && (0 == READ_BIT(SYSC_SEC_AWO->DPLL_LOCK, SYSC_SEC_AWO_DPLL2_LOCK_MASK))) {
        set_trim_params();
        enable_dpll();
        cpu_600M_ahb_300M_qspi_200M_init();
    }
}

NOINLINE void XIP_BANNED_FUNC(clk_flash_init,)
{
    dpll_qspi_clk_config_and_clk_switch();
    MODIFY_REG(LSQSPIV2->QSPI_CTRL1,LSQSPIV2_MODE_DAC_MASK|LSQSPIV2_CAP_DLY_MASK|LSQSPIV2_CAP_NEG_MASK,
                1<<LSQSPIV2_MODE_DAC_POS|QSPI_CAPTURE_DELAY<<LSQSPIV2_CAP_DLY_POS|QSPI_CAPTURE_NEG<<LSQSPIV2_CAP_NEG_POS);
}

// static void set_all_irq_priority_to_lowest_level()
// {
//     uint8_t i;
//     for(i=0;i<IRQN_MAX;++i)
//     {
//         csi_vic_set_prio(i,0);
//     }
// }

void flash_swint_init()
{
    rv_set_int_isr(FLASH_SWINT_NUM,FLASH_SWINT_HANDLER);
    CLIC->CLICINT[FLASH_SWINT_NUM].ATTR = 1 << CLIC_INTATTR_TRIG_Pos;
    csi_vic_set_prio(FLASH_SWINT_NUM,0xf);
    csi_vic_clear_pending_irq(FLASH_SWINT_NUM);
    csi_vic_enable_irq(FLASH_SWINT_NUM);
}

void sys_init_none()
{
    clk_flash_init();
    // set_all_irq_priority_to_lowest_level();
    io_init();
    log_en = true;
    LOG_INIT();

    // pinmux_hal_flash_init();
    // pinmux_hal_flash_quad_init();
    // flash_swint_init();
    // hal_flash_drv_var_init(false, false);
    // hal_flash_xip_func_ptr_init();
    
    // hal_flash_init();
    // hal_flash_xip_mode_reset();
    // hal_flash_software_reset();
    // hal_flash_release_from_deep_power_down();
    // hal_flash_qe_status_read_and_set();
    // hal_flash_xip_start();

    // low_power_init();
    systick_start();
    // sw_timer_module_init();
    // HAL_PIS_Init();
}

void rv_set_int_isr(uint8_t type,void (*isr)())
{
    interrupt_vector[type] = isr;
}

void SWINT_Handler_C(uint32_t *args)
{
    uint32_t (*func)(uint32_t,uint32_t,uint32_t,uint32_t) = (void *)args[11];
    args[15] = func(args[15],args[14],args[13],args[12]);
}

__attribute__((weak)) int _close (int fildes){  return -1;}

__attribute__((weak)) int _fstat (int fildes,void *st){  return -1;}

__attribute__((weak)) int _isatty (int file){  return 0;}

__attribute__((weak)) int _read (int file,char *ptr,int len){  return -1;}

__attribute__((weak)) int _lseek (int   file,int   ptr,int   dir){  return -1;}

void XIP_BANNED_FUNC(sync_for_xip_stop,)
{
    /* wait for CS_N release */
    while ((SEC_PMU->QSPI_PAD_DIN & 0x1) == 0);
}
