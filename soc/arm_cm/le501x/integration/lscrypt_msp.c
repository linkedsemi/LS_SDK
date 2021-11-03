#include "lscrypt_msp.h"
#include "sys_stat.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "platform.h"
#include "le501x.h"

void HAL_LSCRYPT_MSP_Init(void)
{
    REG_FIELD_WR(RCC->APB1EN,  RCC_CRYPT, 1);
    arm_cm_set_int_isr(CRYPT_IRQn,HAL_LSCRYPT_IRQHandler);
    __NVIC_ClearPendingIRQ(CRYPT_IRQn);
    __NVIC_EnableIRQ(CRYPT_IRQn);
}

void HAL_LSCRYPT_MSP_Busy_Set(void)
{
    crypt_status_set(true);
}

void HAL_LSCRYPT_MSP_Idle_Set(void)
{
    crypt_status_set(false);
}

void HAL_LSCRYPT_MSP_DeInit(void)
{
    __NVIC_DisableIRQ(CRYPT_IRQn);
    REG_FIELD_WR(RCC->APB1EN,  RCC_CRYPT, 0);
}

