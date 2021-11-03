#include "trng_msp.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "sys_stat.h"
#include "platform.h"
#include "le501x.h"

void HAL_TRNG_MSP_Init(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_TRNG,1);
    arm_cm_set_int_isr(TRNG_IRQn,HAL_TRNG_IRQHandler);
    __NVIC_ClearPendingIRQ(TRNG_IRQn);
    __NVIC_EnableIRQ(TRNG_IRQn);
}

void HAL_TRNG_MSP_DeInit(void)
{
    __NVIC_DisableIRQ(TRNG_IRQn);
    REG_FIELD_WR(RCC->APB1EN, RCC_TRNG,0);
}

void HAL_TRNG_MSP_Busy_Set(void)
{
    trng_status_set(true);
}

void HAL_TRNG_MSP_Idle_Set(void)
{
    trng_status_set(false);
}
