#include "ls_hal_ecc.h"
#include "ls_msp_ecc.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_sysc_cpu.h"
#include "sys_stat.h"
#include "platform.h"
#include "qsh.h"

void HAL_LSECC_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_ECC_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_CLR_ECC_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_SET_ECC_MASK;
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_SET_ECC_MASK;
    rv_set_int_isr(QSH_ECC_IRQn, LSECC_IRQHandler);
}

void HAL_LSECC_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_ECC_MASK;
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
    csi_vic_enable_irq(QSH_ECC_IRQn);
}

void HAL_LSECC_MSP_INT_DISABLE(void)
{
    csi_vic_disable_irq(QSH_ECC_IRQn);
}

void HAL_LSECC_MSP_INT_CLRPENDING(void)
{
    csi_vic_clear_pending_irq(QSH_ECC_IRQn);
}
