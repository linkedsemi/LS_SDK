#include "ls_msp_sm4.h"
#include "ls_hal_sm4.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_sysc_sec_cpu.h"
#include "core_rv32.h"
#include "platform.h"
#include "qsh.h"

void HAL_LSSM4_MSP_Init(void)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_CLR_CALC_SM4_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[1] = SYSC_SEC_CPU_SRST_CLR_CALC_SM4_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[1] = SYSC_SEC_CPU_SRST_SET_CALC_SM4_MASK;
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_SET_CALC_SM4_MASK;
    rv_set_int_isr(CALC_SM4_IRQN, HAL_SM4_IRQHandler);
    csi_vic_clear_pending_irq(CALC_SM4_IRQN);
    csi_vic_enable_irq(CALC_SM4_IRQN);
}

void HAL_LSSM4_MSP_DeInit(void)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_CLR_CALC_SM4_MASK;
    csi_vic_disable_irq(CALC_SM4_IRQN);
}