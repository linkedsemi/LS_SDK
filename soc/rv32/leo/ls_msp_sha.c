#include "ls_msp_sha.h"
#include "reg_sysc_cpu.h"
#include "leo.h"
#include "platform.h"
#include "ls_hal_sha.h"
#include "exception_isr.h"
#include "core_rv32.h"
#include "sys_stat.h"

#if defined(BOOT_ROM)
void HAL_LSSHA_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_CALC_SHA_MASK;
}

void HAL_LSSHA_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CALC_SHA_MASK;
}
#else
void HAL_LSSHA_MSP_Init(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_CALC_SHA_MASK;
    rv_set_int_isr(CALC_SHA_IRQn,LSSHA_IRQHandler);
    csi_vic_clear_pending_irq(CALC_SHA_IRQn);
    csi_vic_enable_irq(CALC_SHA_IRQn);
}

void HAL_LSSHA_MSP_DeInit(void)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_CALC_SHA_MASK;
    csi_vic_disable_irq(CALC_SHA_IRQn);
}
#endif

void HAL_LSSHA_MSP_Busy_Set(void)
{
    sha_status_set(true);
}

void HAL_LSSHA_MSP_Idle_Set(void)
{
    sha_status_set(false);
}