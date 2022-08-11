#include "ls_msp_crypt.h"
#include "field_manipulate.h"
#include "platform.h"
#include "gemini.h"
#include "reg_sysc_cpu_type.h"
#include "ls_hal_crypt.h"
#include "sys_stat.h"
void HAL_LSCRYPT_MSP_Init(void)
{
    REG_FIELD_WR(SYSC_CPU->PD_CPU_CLKG, SYSC_CPU_CLKG_SET_CRYPT, 1);
    arm_cm_set_int_isr(CRYPT_IRQn, HAL_LSCRYPT_IRQHandler);
    __NVIC_ClearPendingIRQ(CRYPT_IRQn);
    __NVIC_EnableIRQ(CRYPT_IRQn);
}

void HAL_LSCRYPT_MSP_DeInit(void)
{
    __NVIC_DisableIRQ(CRYPT_IRQn);
    REG_FIELD_WR(SYSC_CPU->PD_CPU_CLKG, SYSC_CPU_CLKG_CLR_CRYPT, 1);
}

void HAL_LSCRYPT_MSP_Busy_Set(void)
{
    crypt_status_set(true);
}

void HAL_LSCRYPT_MSP_Idle_Set(void)
{
    crypt_status_set(false);
}


