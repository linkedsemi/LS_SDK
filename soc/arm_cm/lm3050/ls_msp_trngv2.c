#include "ls_msp_trngv2.h"
#include "field_manipulate.h"
#include "platform.h"
#include "lm3050.h"
#include "sys_stat.h"
#include "reg_sysc_cpu_type.h"
#include "reg_sysc_per_type.h"
#include "ls_hal_trng.h"

void HAL_TRNG_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_TRNG_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_PER_SRST_CLR_TRNG_N_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_PER_SRST_SET_TRNG_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_TRNG_MASK;
    arm_cm_set_int_isr(TRNG_IRQn, HAL_TRNG_IRQHandler);
    __NVIC_ClearPendingIRQ(TRNG_IRQn);
    __NVIC_EnableIRQ(TRNG_IRQn);
}

void HAL_TRNG_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_TRNG_MASK;
    __NVIC_DisableIRQ(TRNG_IRQn);
}

void HAL_TRNG_MSP_Busy_Set(void)
{
    trng_status_set(true);
}

void HAL_TRNG_MSP_Idle_Set(void)
{
    trng_status_set(false);
}
