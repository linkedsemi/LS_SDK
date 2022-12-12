#include "ls_msp_sm4.h"
#include "field_manipulate.h"
#include "platform.h"
#include "lm3050.h"
#include "reg_sysc_cpu_type.h"
#include "ls_hal_sm4.h"
#include "sys_stat.h"
void HAL_LSSM4_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_CALC_SM4_MASK;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_CALC_SM4_MASK;
    arm_cm_set_int_isr(SM4_IRQn, HAL_SM4_IRQHandler);
    __NVIC_ClearPendingIRQ(SM4_IRQn);
    __NVIC_EnableIRQ(SM4_IRQn);
}
void HAL_LSSM4_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CALC_SM4_MASK;
    __NVIC_DisableIRQ(SM4_IRQn);
}