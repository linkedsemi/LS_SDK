#include "field_manipulate.h"
#include "lm3050.h"
#include "platform.h"
#include "ls_hal_ecc.h"
#include "reg_sysc_cpu_type.h"
#include "sys_stat.h"
#include "ls_msp_ecc.h"

void HAL_LSECC_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_ECC_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_ECC_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_ECC_MASK;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_ECC_MASK;
    arm_cm_set_int_isr(ECC_IRQn, LSECC_IRQHandler);
}

void HAL_LSECC_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_ECC_MASK;
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
