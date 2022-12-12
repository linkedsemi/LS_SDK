#include "ls_msp_crypt.h"
#include "field_manipulate.h"
#include "platform.h"
#include "lm3050.h"
#include "reg_sysc_cpu_type.h"
#include "ls_hal_crypt.h"
#include "sys_stat.h"
void HAL_LSCRYPT_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CRYPT_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_CRYPT_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_CRYPT_MASK;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_CRYPT_MASK;
    arm_cm_set_int_isr(CRYPT_IRQn, HAL_LSCRYPT_IRQHandler);
    __NVIC_ClearPendingIRQ(CRYPT_IRQn);
    __NVIC_EnableIRQ(CRYPT_IRQn);
}

void HAL_LSCRYPT_MSP_DeInit(void)
{
    __NVIC_DisableIRQ(CRYPT_IRQn);
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CRYPT_MASK;
}

void HAL_LSCRYPT_MSP_Busy_Set(void)
{
    crypt_status_set(true);
}

void HAL_LSCRYPT_MSP_Idle_Set(void)
{
    crypt_status_set(false);
}


