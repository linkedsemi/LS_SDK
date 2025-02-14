#include "ls_hal_dmacv3.h"
#include "ls_msp_dmacv3.h"
#include "reg_sysc_app_cpu.h"
#include "field_manipulate.h"
#include "exception_isr.h"
#include "core_rv32.h"
#include "qsh.h"

struct __DMA_Controller_HandleTypeDef *dma_inst[2];

void DMAC1_Handler()
{
    HAL_DMA_Controller_IRQHandler(dma_inst[0]);
}

void DMAC2_Handler()
{
    HAL_DMA_Controller_IRQHandler(dma_inst[1]);
}

#if defined(__ZEPHYR__)
#include <zephyr/kernel.h>
#endif
void HAL_DMA_Controller_MSP_Init(struct __DMA_Controller_HandleTypeDef *hdma)
{
    switch((uint32_t)hdma->Instance)
    {
    case (uint32_t)DMAC1:
        SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_CLR_DMAC1_MASK;
        SYSC_APP_CPU->PD_CPU_SRST  = SYSC_APP_CPU_SRST_CLR_DMAC1_MASK;
        SYSC_APP_CPU->PD_CPU_SRST  = SYSC_APP_CPU_SRST_SET_DMAC1_MASK;
        SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_SET_DMAC1_MASK;
        dma_inst[0] = hdma;
#if defined(__ZEPHYR__)
        IRQ_CONNECT(DMAC1_IRQN, 0, DMAC1_Handler, NULL, 0);
        irq_enable(DMAC1_IRQN);
#else
        rv_set_int_isr(DMAC1_IRQN, DMAC1_Handler);
        csi_vic_clear_pending_irq(DMAC1_IRQN);
        csi_vic_enable_irq(DMAC1_IRQN);
#endif
        break;
    case (uint32_t)DMAC2:
        SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_CLR_DMAC2_MASK;
        SYSC_APP_CPU->PD_CPU_SRST  = SYSC_APP_CPU_SRST_CLR_DMAC2_MASK;
        SYSC_APP_CPU->PD_CPU_SRST  = SYSC_APP_CPU_SRST_SET_DMAC2_MASK;
        SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_SET_DMAC2_MASK;
        dma_inst[1] = hdma;
#if defined(__ZEPHYR__)
        IRQ_CONNECT(DMAC2_IRQN, 0, DMAC2_Handler, NULL, 0);
        irq_enable(DMAC2_IRQN);
#else
        rv_set_int_isr(DMAC2_IRQN, DMAC2_Handler);
        csi_vic_clear_pending_irq(DMAC2_IRQN);
        csi_vic_enable_irq(DMAC2_IRQN);
#endif
        break;
    }
}

void HAL_DMA_Controller_MSP_DeInit(struct __DMA_Controller_HandleTypeDef *hdma)
{
    switch((uint32_t)hdma->Instance)
    {
    case (uint32_t)DMAC1:
        csi_vic_disable_irq(DMAC1_IRQN);
        SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_CLR_DMAC1_MASK;
        break;
    case (uint32_t)DMAC2:
        csi_vic_disable_irq(DMAC2_IRQN);
        SYSC_APP_CPU->PD_CPU_CLKG0 = SYSC_APP_CPU_CLKG_CLR_DMAC2_MASK;
        break;
    }
}

void HAL_DMA_Controller_MSP_Busy_Set(struct __DMA_Controller_HandleTypeDef *hdma)
{

}

void HAL_DMA_Controller_MSP_Idle_Set(struct __DMA_Controller_HandleTypeDef *hdma)
{
    
}

void HAL_DMA_Channel_Handshake_Set(struct __DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,uint8_t handshake)
{
    switch ((uint32_t)hdma->Instance)
    {
    case (uint32_t)DMAC1:
        MODIFY_REG(SYSC_APP_CPU->DMAC1_CH_SEL[ch_idx / 2], 0xff << ((ch_idx % 2) * 16), (handshake | 0x100) << ((ch_idx % 2) * 16));
        break;
    case (uint32_t)DMAC2:
        MODIFY_REG(SYSC_APP_CPU->DMAC2_CH_SEL[ch_idx / 2], 0xff << ((ch_idx % 2) * 16), (handshake | 0x100) << ((ch_idx % 2) * 16));
        break;
    default:
        break;
    }
}