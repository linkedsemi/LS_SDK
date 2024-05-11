#include "ls_hal_dmacv3.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_cpu.h"
#include "field_manipulate.h"
#include "leo.h"
#include "core_rv32.h"
#include "exception_isr.h"

struct __DMA_Controller_HandleTypeDef *dma_inst[2];

void DMAC1_Handler()
{
    HAL_DMA_Controller_IRQHandler(dma_inst[0]);
}

void DMAC2_Handler()
{
    HAL_DMA_Controller_IRQHandler(dma_inst[1]);
}

void HAL_DMA_Controller_MSP_Init(struct __DMA_Controller_HandleTypeDef *hdma)
{
    switch((uint32_t)hdma->Instance)
    {
    case (uint32_t)DMAC1:
        SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_DMAC1_MASK;
        SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_DMAC1_MASK;
        SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_DMAC1_MASK;
        SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_DMAC1_MASK;
        rv_set_int_isr(DMAC1_IRQn, DMAC1_Handler);
        dma_inst[0] = hdma;
        csi_vic_clear_pending_irq(DMAC1_IRQn);
        csi_vic_enable_irq(DMAC1_IRQn);
        break;
    case (uint32_t)DMAC2:
        SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_DMAC2_MASK;
        SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_DMAC2_MASK;
        SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_DMAC2_MASK;
        SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_DMAC2_MASK;
        rv_set_int_isr(DMAC2_IRQn, DMAC2_Handler);
        dma_inst[1] = hdma;
        csi_vic_clear_pending_irq(DMAC2_IRQn);
        csi_vic_enable_irq(DMAC2_IRQn);
        break;
    }
}

void HAL_DMA_Controller_MSP_DeInit(struct __DMA_Controller_HandleTypeDef *hdma)
{
    switch((uint32_t)hdma->Instance)
    {
    case (uint32_t)DMAC1:
        csi_vic_disable_irq(DMAC1_IRQn);
        SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_DMAC1_MASK;
        break;
    case (uint32_t)DMAC2:
        csi_vic_disable_irq(DMAC2_IRQn);
        SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_DMAC2_MASK;
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
        MODIFY_REG(SYSC_AWO->DMAC1_CH_SEL[ch_idx / 4], 0xff << (ch_idx % 4) * 8, (0x80 | handshake) << (ch_idx % 4) * 8);
        break;
    case (uint32_t)DMAC2:
        MODIFY_REG(SYSC_AWO->DMAC2_CH_SEL[ch_idx / 4], 0xff << (ch_idx % 4) * 8, (0x80 | handshake) << (ch_idx % 4) * 8);
        break;
    default:
        break;
    }
}