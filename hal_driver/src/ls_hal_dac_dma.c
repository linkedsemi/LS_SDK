#include "ls_hal_dac.h"
#include "ls_hal_dmacv2.h"
#include "ls_msp_dac.h"
#include "field_manipulate.h"

struct DMA_Channel_Config cfg;

void DAC1_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    DAC_HandleTypeDef *hdac = (DAC_HandleTypeDef *)param;
    CLEAR_BIT(hdac->Instance->DAC_CR,DAC_DMAEN2_MASK);
    CLEAR_BIT(hdac->Instance->DAC_CR,DAC_DMA2N1_MASK);
    hdac->Env.DMA.Callback(hdac);
}

void DAC2_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    DAC_HandleTypeDef *hdac = (DAC_HandleTypeDef *)param;
    CLEAR_BIT(hdac->Instance->DAC_CR,DAC_DMAEN2_MASK);
    CLEAR_BIT(hdac->Instance->DAC_CR,DAC_DMA2N1_MASK);
    hdac->Env.DMA.Callback(hdac);
}

void dac_dma_cfg(DAC_HandleTypeDef *hdac, const uint32_t *pData, uint32_t Length, void (*Callback)(DAC_HandleTypeDef *hdac))
{
    hdac->Env.DMA.Callback = Callback;
    cfg.ctrl.channel_en = 1;
    cfg.ctrl.circular_mode_en = 1;
    cfg.ctrl.peripheral_flow_ctrl = 0;
    cfg.ctrl.direct_mode_en = 0;
    cfg.ctrl.dma_mode_sel = Mem2Peri;
    cfg.ctrl.channel_priority = 0;
    cfg.ctrl.src_inc = 1;
    cfg.ctrl.src_width = DMA_SIZE_WORD;
    cfg.ctrl.src_burst = 0;
    cfg.ctrl.src_inc_offset = 0;
    cfg.ctrl.rsvd0 = 0;
    cfg.ctrl.dst_inc = 0;
    cfg.ctrl.dst_witdh = DMA_SIZE_WORD;
    cfg.ctrl.dst_burst = 0;
    cfg.ctrl.dst_inc_offset = 0;
     cfg.ctrl.rsvd1 = 0;
    cfg.src_addr = (uint32_t)pData;
    cfg.dst_addr = (uint32_t)hdac->Instance;
    cfg.byte_count = Length;
    cfg.dummy = 0;
}

HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef* hdac, uint32_t Alignment, const uint32_t* pData, uint32_t Length,void (*Callback)(DAC_HandleTypeDef* hdac))
{
    HAL_StatusTypeDef status = HAL_OK;
    dac_dma_cfg(hdac,pData,Length,Callback);
    if(READ_BIT(hdac->Instance->DAC_ANA,DAC_EN_DAC1_MASK))
    {
        cfg.ctrl.peripheral_handshake = HAL_DAC_DMA_Handshake_Get(DAC1);
        SET_BIT(hdac->Instance->DAC_CR,DAC_DMA2N1_MASK);
        if ((hdac->DACx == DAC1AndDAC2))
        {
            cfg.dst_addr += DAC_DHR12RD_ALIGNMENT(Alignment);
        }else{
            cfg.dst_addr += DAC_DHR12R1_ALIGNMENT(Alignment);
        }
        WRITE_REG(hdac->Instance->DAC_SWTRIGR,DAC_SWTRIG1_MASK);
        HAL_DMA_Channel_Start_IT(hdac->DMAC_Instance, hdac->Env.DMA.DMA_Channel, &cfg, DAC1_DMA_Callback, (uint32_t)hdac);  
    }

    if(READ_BIT(hdac->Instance->DAC_ANA,DAC_EN_DAC2_MASK))
    {
        cfg.ctrl.peripheral_handshake = HAL_DAC_DMA_Handshake_Get(DAC2);
        SET_BIT(hdac->Instance->DAC_CR,DAC_DMAEN2_MASK);
        if ((hdac->DACx == DAC1AndDAC2))
        {
            cfg.dst_addr += DAC_DHR12RD_ALIGNMENT(Alignment);
        }else
        {
            cfg.dst_addr += DAC_DHR12R2_ALIGNMENT(Alignment);
        }
        
        WRITE_REG(hdac->Instance->DAC_SWTRIGR,DAC_SWTRIG2_MASK);
        HAL_DMA_Channel_Start_IT(hdac->DMAC_Instance, hdac->Env.DMA.DMA_Channel, &cfg, DAC2_DMA_Callback, (uint32_t)hdac);
    }
    return status;
}

HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
    HAL_StatusTypeDef status = HAL_OK;
    switch (Channel)
    {
    case DAC_CHANNEL_1:
        CLEAR_BIT(hdac->Instance->DAC_CR, DAC_DMA2N1_MASK);
        __HAL_DAC1_DISABLE(hdac);
        break;
    case DAC_CHANNEL_2:
        CLEAR_BIT(hdac->Instance->DAC_CR, DAC_DMAEN2_MASK);
        __HAL_DAC2_DISABLE(hdac);
        break;
    default:
        CLEAR_BIT(hdac->Instance->DAC_CR, DAC_DMA2N1_MASK | DAC_DMAEN2_MASK);
        __HAL_DAC1_DISABLE(hdac);
        __HAL_DAC2_DISABLE(hdac);
        break;
    }
    return status;
}