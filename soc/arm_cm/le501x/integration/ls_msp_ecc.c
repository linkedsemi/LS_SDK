#include "reg_rcc.h"
#include "sys_stat.h"
#include "field_manipulate.h"
#include "le501x.h"
#include "platform.h"
#include "ls_hal_ecc.h"
#include "ls_msp_ecc.h"

void HAL_LSECC_MSP_Init(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_ECC,1);
    arm_cm_set_int_isr(ECC_IRQn,LSECC_IRQHandler);
}

void HAL_LSECC_MSP_DeInit(void)
{
    REG_FIELD_WR(RCC->APB1EN, RCC_ECC,0);
}

void HAL_LSECC_Busy_Set(void)
{
    ecc_status_set(true);
}

void HAL_LSECC_Idle_Set(void)
{
    ecc_status_set(false);
}

void HAL_LSECC_MSP_INT_ENABLE(void)
{
    __NVIC_EnableIRQ(ECC_IRQn);
}

void HAL_LSECC_MSP_INT_DISABLE(void)
{
    __NVIC_DisableIRQ(ECC_IRQn);
}

void HAL_LSECC_MSP_INT_CLRPENDING(void)
{
    __NVIC_ClearPendingIRQ(ECC_IRQn);
}
