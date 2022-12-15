#include "ls_hal_dmacv2.h"
#include "ls_dbg.h"

void HAL_DMA_Controller_Init(DMA_Controller_HandleTypeDef *hdma)
{
    HAL_DMA_Controller_MSP_Init(hdma);
    HAL_DMA_Controller_MSP_Busy_Set(hdma);
}

void HAL_DMA_Controller_DeInit(DMA_Controller_HandleTypeDef *hdma)
{
    HAL_DMA_Controller_MSP_Idle_Set(hdma);
    HAL_DMA_Controller_MSP_DeInit(hdma);
}

void HAL_DMA_Channel_Start_IT(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,struct DMA_Channel_Config *cfg,void (*callback)(DMA_Controller_HandleTypeDef *,uint32_t,uint8_t),uint32_t param)
{
    hdma->channel_callback[ch_idx] = callback;
    hdma->param[ch_idx] = param;
    hdma->Instance->ICR = 3<<(ch_idx*2);
    hdma->Instance->IER = 3<<(ch_idx*2);
    hdma->Instance->CH[ch_idx].SAR = cfg->src_addr;
    hdma->Instance->CH[ch_idx].DAR = cfg->dst_addr;
    hdma->Instance->CH[ch_idx].BCR = cfg->byte_count;
    uint32_t *csr = (uint32_t *)&cfg->ctrl;
    hdma->Instance->CH[ch_idx].CSR = *csr;
}

void HAL_DMA_Controller_IRQHandler(DMA_Controller_HandleTypeDef *hdma)
{
    uint32_t irq = hdma->Instance->IFM;
    uint8_t i;
    LS_ASSERT((irq&0xaaaaaaaa)==0);
    for(i=0;i<DMAC_CHANNEL_NUM;++i)
    {
        if(irq&1<<(i*2))
        {
            hdma->Instance->ICR = 1<<(i*2);
            hdma->channel_callback[i](hdma,hdma->param[i],i);
        }
    }
}