#include "ls_hal_dac.h"
#include "ls_msp_dac.h"
#include "field_manipulate.h"
#include "sdk_config.h"

#if DMACV2
#include "ls_hal_dmacv2.h"
struct DMA_Channel_Config cfg;

void DAC1_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    DAC_HandleTypeDef *hdac = (DAC_HandleTypeDef *)param;
    CLEAR_BIT(hdac->Instance->DAC_CR,DAC_DMA2N1_MASK);
    hdac->Env.DMA.Callback(hdac);
}

void DAC2_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    DAC_HandleTypeDef *hdac = (DAC_HandleTypeDef *)param;
    CLEAR_BIT(hdac->Instance->DAC_CR,DAC_DMAEN2_MASK);
    hdac->Env.DMA.Callback(hdac);
}

void dac_dma_cfg(DAC_HandleTypeDef *hdac, const uint32_t *pData, uint32_t Byte_Count, void (*Callback)(DAC_HandleTypeDef *hdac))
{
    hdac->Env.DMA.Callback = Callback;
    cfg.ctrl.channel_en = 1;
    cfg.ctrl.circular_mode_en = 0;
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
    cfg.byte_count = Byte_Count;
    cfg.dummy = 0;
}

HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef* hdac, uint32_t Alignment, const uint32_t* pData, uint32_t Byte_Count,void (*Callback)(DAC_HandleTypeDef* hdac))
{
    HAL_StatusTypeDef status = HAL_OK;
    dac_dma_cfg(hdac,pData,Byte_Count,Callback);
    if(READ_BIT(hdac->Instance->DAC_ANA,DAC_EN_DAC1_MASK))
    {
        cfg.ctrl.peripheral_handshake = HAL_DAC_DMA_Handshake_Get(DAC1);
        SET_BIT(hdac->Instance->DAC_CR,DAC_DMA2N1_MASK);
        if (hdac->DACx == DAC1AndDAC2)
        {
            cfg.dst_addr += DAC_DHR12RD_ALIGNMENT(Alignment);
        }else{
            cfg.dst_addr += DAC_DHR12R1_ALIGNMENT(Alignment);
        }
        HAL_DMA_Channel_Start_IT(hdac->DMAC_Instance, hdac->Env.DMA.DMA_Channel, &cfg, DAC1_DMA_Callback, (uint32_t)hdac);  
    }

    else if(READ_BIT(hdac->Instance->DAC_ANA,DAC_EN_DAC2_MASK))
    {
        cfg.ctrl.peripheral_handshake = HAL_DAC_DMA_Handshake_Get(DAC2);
        SET_BIT(hdac->Instance->DAC_CR,DAC_DMAEN2_MASK);
        cfg.dst_addr += DAC_DHR12R2_ALIGNMENT(Alignment);
        HAL_DMA_Channel_Start_IT(hdac->DMAC_Instance, hdac->Env.DMA.DMA_Channel, &cfg, DAC2_DMA_Callback, (uint32_t)hdac);
    }
    return status;
}

#elif DMACV3
#include "ls_hal_dmacv3.h"

void DAC1_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t ch_idx,uint32_t *lli,uint32_t status_int)
{
    if(!(status_int & DMAC_TFR_MASK))
    {
        DAC_HandleTypeDef *hdac = (DAC_HandleTypeDef *)param;
        CLEAR_BIT(hdac->Instance->DAC_CR,DAC_DMA2N1_MASK);
        hdac->Env.DMA.Callback(hdac);
    }
}

void DAC2_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t ch_idx,uint32_t *lli,uint32_t status_int)
{
    if(!(status_int & DMAC_TFR_MASK))
    {
        DAC_HandleTypeDef *hdac = (DAC_HandleTypeDef *)param;
        CLEAR_BIT(hdac->Instance->DAC_CR,DAC_DMAEN2_MASK);
        hdac->Env.DMA.Callback(hdac);
    }
}

HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef* hdac, uint32_t Alignment, const uint32_t* pData, uint32_t Byte_Count,void (*Callback)(DAC_HandleTypeDef* hdac))
{
    struct ch_reg cfg;
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t dst_addr = (uint32_t)hdac->Instance;
    hdac->Env.DMA.Callback = Callback;

    if(READ_BIT(hdac->Instance->DAC_ANA,DAC_EN_DAC1_MASK))
    {
        SET_BIT(hdac->Instance->DAC_CR, DAC_DMA2N1_MASK);
        if ((hdac->DACx == DAC1AndDAC2))
        {
            dst_addr += DAC_DHR12RD_ALIGNMENT(Alignment);
        }
        else
        {
            dst_addr += DAC_DHR12R1_ALIGNMENT(Alignment);
        }
        DMA_CHANNEL_CFG(cfg,
            hdac->Env.DMA.DMA_Channel,
            (uint32_t)pData,
            dst_addr,
            TRANSFER_WIDTH_32BITS,
            Byte_Count/4,
            M2P,
            0,
            HAL_DAC_DMA_Handshake_Get(DAC1),
            0,0,0,0);
        HAL_DMA_Channel_Start_IT(hdac->DMAC_Instance, &cfg, DAC1_DMA_Callback, (uint32_t)hdac);  
    }

    else if(READ_BIT(hdac->Instance->DAC_ANA,DAC_EN_DAC2_MASK))
    {
        SET_BIT(hdac->Instance->DAC_CR,DAC_DMAEN2_MASK);
        dst_addr += DAC_DHR12R2_ALIGNMENT(Alignment);
        DMA_CHANNEL_CFG(cfg,
            hdac->Env.DMA.DMA_Channel,
            (uint32_t)pData,
            dst_addr,
            TRANSFER_WIDTH_32BITS,
            Byte_Count/4,
            M2P,
            0,
            HAL_DAC_DMA_Handshake_Get(DAC2),
            0,0,0,0);
        HAL_DMA_Channel_Start_IT(hdac->DMAC_Instance, &cfg, DAC2_DMA_Callback, (uint32_t)hdac);
    }
    return status;
}
#endif

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