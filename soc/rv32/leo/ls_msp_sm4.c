#include "ls_msp_sm4.h"
#include "ls_hal_sm4.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_sysc_cpu.h"
#include "core_rv32.h"
#include "platform.h"
#include "leo.h"

void HAL_LSSM4_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_SRST_SET_CALC_SM4_MASK;
    rv_set_int_isr(CALC_SM4_IRQn, HAL_SM4_IRQHandler);
    csi_vic_clear_pending_irq(CALC_SM4_IRQn);
    csi_vic_enable_irq(CALC_SM4_IRQn);
}

void HAL_LSSM4_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CALC_SM4_MASK;
    csi_vic_disable_irq(CALC_SM4_IRQn);
}