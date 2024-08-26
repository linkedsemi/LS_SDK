#include "ls_msp_sha.h"
#include "reg_sysc_cpu.h"
#include "qsh.h"
#include "platform.h"
#include "ls_hal_sha.h"
#include "exception_isr.h"
#include "core_rv32.h"
#include "sys_stat.h"

void HAL_LSSHA_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_CALC_SHA_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_CLR_CALC_SHA_MASK;
    SYSC_CPU->PD_CPU_SRST[1] = SYSC_CPU_SRST_SET_CALC_SHA_MASK;
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_SET_CRYPT_MASK;
    rv_set_int_isr(QSH_SHA_IRQn,LSSHA_IRQHandler);
    csi_vic_clear_pending_irq(QSH_SHA_IRQn);
    csi_vic_enable_irq(QSH_SHA_IRQn);
}

void HAL_LSSHA_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG[1] = SYSC_CPU_CLKG_CLR_CALC_SHA_MASK;
    csi_vic_disable_irq(QSH_SHA_IRQn);
}

void HAL_LSSHA_MSP_Busy_Set(void)
{
    sha_status_set(true);
}

void HAL_LSSHA_MSP_Idle_Set(void)
{
    sha_status_set(false);
}