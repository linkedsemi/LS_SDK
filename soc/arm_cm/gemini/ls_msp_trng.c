#include "ls_msp_trng.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "platform.h"
#include "gemini.h"
#include "sys_stat.h"
#include "reg_sysc_per_type.h"
#include "ls_hal_trng.h"

void HAL_TRNG_MSP_Init(void)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG3, SYSC_PER_CLKG_SET_TRNG, 1);
    arm_cm_set_int_isr(TRNG_IRQn, HAL_TRNG_IRQHandler);
    __NVIC_ClearPendingIRQ(TRNG_IRQn);
    __NVIC_EnableIRQ(TRNG_IRQn);
}

void HAL_TRNG_MSP_DeInit(void)
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG3, SYSC_PER_CLKG_CLR_TRNG, 1);
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