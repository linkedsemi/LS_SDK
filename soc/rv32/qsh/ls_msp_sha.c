#include "ls_msp_sha.h"
#include "ls_hal_sha.h"
#include "reg_sysc_sec_cpu.h"
#include "exception_isr.h"
#include "dmac_config.h"
#include "core_rv32.h"
#include "qsh.h"

void HAL_LSSHA_MSP_Init(void)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_CLR_CALC_SHA_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[1] = SYSC_SEC_CPU_SRST_CLR_CALC_SHA_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[1] = SYSC_SEC_CPU_SRST_SET_CALC_SHA_MASK;
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_SET_CALC_SHA_MASK;
    rv_set_int_isr(CALC_SHA_IRQN,LSSHA_IRQHandler);
    csi_vic_clear_pending_irq(CALC_SHA_IRQN);
    csi_vic_enable_irq(CALC_SHA_IRQN);
}

void HAL_LSSHA_MSP_DeInit(void)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[1] = SYSC_SEC_CPU_CLKG_CLR_CALC_SHA_MASK;
    csi_vic_disable_irq(CALC_SHA_IRQN);
}

uint8_t HAL_SHA_DMA_Handshake_Get(void)
{
    return DMA_SHA256;
}

void HAL_LSSHA_MSP_Busy_Set(void)
{
}

void HAL_LSSHA_MSP_Idle_Set(void)
{
}