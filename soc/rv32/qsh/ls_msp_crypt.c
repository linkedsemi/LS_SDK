#include "ls_msp_crypt.h"
#include "ls_hal_crypt.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "reg_sysc_cpu.h"
#include "core_rv32.h"
#include "sys_stat.h"
#include "qsh.h"

void HAL_LSCRYPT_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_CRYPT_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_CLR_CRYPT_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_SET_CRYPT_MASK;
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_SET_CRYPT_MASK;
    rv_set_int_isr(QSH_CRYPT_IRQn, HAL_LSCRYPT_IRQHandler);
    csi_vic_clear_pending_irq(QSH_CRYPT_IRQn);
    csi_vic_enable_irq(QSH_CRYPT_IRQn);
}

void HAL_LSCRYPT_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_CRYPT_MASK;
    csi_vic_disable_irq(QSH_CRYPT_IRQn);
}

void HAL_LSCRYPT_MSP_Busy_Set(void)
{
    crypt_status_set(true);
}

void HAL_LSCRYPT_MSP_Idle_Set(void)
{
    crypt_status_set(false);
}


