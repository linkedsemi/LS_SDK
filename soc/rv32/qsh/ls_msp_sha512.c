#include "ls_msp_sha512.h"
#include "ls_hal_sha512.h"
#include "reg_sysc_sec_cpu.h"
#include "exception_isr.h"
#include "dmac_config.h"
#include "core_rv32.h"
#include "qsh.h"

void HAL_SHA512_MSP_Init(void)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_CLR_SHA512_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[0] = SYSC_SEC_CPU_SRST_CLR_SHA512_MASK;
    SYSC_SEC_CPU->PD_CPU_SRST[0] = SYSC_SEC_CPU_SRST_SET_SHA512_MASK;
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_SET_SHA512_MASK;
    rv_set_int_isr(SHA512_IRQN, SHA512_IRQHandler);
    csi_vic_clear_pending_irq(SHA512_IRQN);
    csi_vic_enable_irq(SHA512_IRQN);
}

void HAL_SHA512_MSP_DeInit(void)
{
    SYSC_SEC_CPU->PD_CPU_CLKG[0] = SYSC_SEC_CPU_CLKG_CLR_SHA512_MASK;
    csi_vic_disable_irq(SHA512_IRQN);

}

uint8_t HAL_SHA512_DMA_Handshake_Get(void)
{
    return CH_SHA512;
}