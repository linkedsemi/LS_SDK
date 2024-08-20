#include "ls_msp_sm4.h"
#include "ls_hal_sm4.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_sysc_cpu.h"
#include "core_rv32.h"
#include "platform.h"
#include "qsh.h"

void HAL_LSSM4_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_CLR_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_SET_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_SET_CALC_SM4_MASK;
    rv_set_int_isr(BMC_SM4_IRQn, HAL_SM4_IRQHandler);
    csi_vic_clear_pending_irq(BMC_SM4_IRQn);
    csi_vic_enable_irq(BMC_SM4_IRQn);
}

void HAL_LSSM4_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_CALC_SM4_MASK;
    csi_vic_disable_irq(BMC_SM4_IRQn);
}