#include "ls_msp_sha.h"
#include "reg_sysc_cpu_type.h"
#include "lm3050.h"
#include "platform.h"
#include "sys_stat.h"
#include "ls_hal_sha.h"
#include "compile_flag.h"

void HAL_LSSHA_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CALC_SHA_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_CALC_SHA_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_CALC_SHA_MASK;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_CALC_SHA_MASK;
    arm_cm_set_int_isr(SHA_IRQn,LSSHA_IRQHandler);
    __NVIC_ClearPendingIRQ(SHA_IRQn);
    __NVIC_EnableIRQ(SHA_IRQn);
}

ROM_SYMBOL void HAL_LSSHA_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CALC_SHA_MASK;
    __NVIC_DisableIRQ(SHA_IRQn);
}

void HAL_LSSHA_MSP_Busy_Set(void)
{
    sha_status_set(true);
}

void HAL_LSSHA_MSP_Idle_Set(void)
{
    sha_status_set(false);
}