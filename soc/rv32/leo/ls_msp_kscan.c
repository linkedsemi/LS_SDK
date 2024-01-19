#include "ls_msp_kscan.h"
#include "ls_hal_kscan.h"
#include "leo.h"
#include "core_rv32.h"
#include "reg_sysc_per.h"
#include "exception_isr.h"

void HAL_KSCAN_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_KSCAN_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_KSCAN_N_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_KSCAN_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_KSCAN_MASK;
    rv_set_int_isr(KSCAN_IRQn, HAL_KSCAN_IRQHandler);
    csi_vic_clear_pending_irq(KSCAN_IRQn);
    csi_vic_enable_irq(KSCAN_IRQn);
}

void HAL_KSCAN_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_KSCAN_MASK;
    csi_vic_disable_irq(KSCAN_IRQn);
}
