
#include "compile_flag.h"
#include "platform.h"
#include "cpu.h"
#include "log.h"
#include "swint_call_asm.h"
#include "systick.h"
#include "exception_isr.h"
#include "ls_soc_gpio.h"
#include "field_manipulate.h"
#include "per_func_mux.h"
#include "qsh.h"

#define PMU_CLK_VAL (SDK_HSE_USED << V33_RG_CLK_SET_HSE_POS | 1 << V33_RG_CLK_SET_HSI_POS | (!SDK_LSI_USED) << V33_RG_CLK_SET_LSE_POS)

__attribute__((aligned(64))) void (*interrupt_vector[IRQN_MAX])();

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

// NOINLINE void XIP_BANNED_FUNC(clk_flash_init,)
// {
//     dpll_qspi_clk_config();
//     MODIFY_REG(LSQSPIV2->QSPI_CTRL1,LSQSPIV2_MODE_DAC_MASK|LSQSPIV2_CAP_DLY_MASK|LSQSPIV2_CAP_NEG_MASK,
//                 1<<LSQSPIV2_MODE_DAC_POS|QSPI_CAPTURE_DELAY<<LSQSPIV2_CAP_DLY_POS|QSPI_CAPTURE_NEG<<LSQSPIV2_CAP_NEG_POS);
//     clk_switch();
// }

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
    // clk_flash_init();
    // set_all_irq_priority_to_lowest_level();
    // hal_flash_xip_func_ptr_init();
    io_init();
#if !defined(KERNEL)
    LOG_INIT();
#endif
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
    while (io_get_input_val(QSPI1_CSN_PIN) == 0);
}
