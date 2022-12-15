#include <stddef.h>
#include "ls_hal_adcv2.h"
#include "ls_hal_dmacv2.h"
#include "ls_msp_adc.h"
#include "field_manipulate.h"
#include "log.h"

/**
  * @brief  DMA transfer complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
void ADC_DMA_Callback(DMA_Controller_HandleTypeDef *hdma,uint32_t param,uint8_t DMA_channel)
{
    ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)param;
    CLEAR_BIT(hadc->Instance->MISC_CTRL,ADC_DMA_EN_MASK);
    if(__HAL_ADC_GET_FLAG(hadc,ADC_INTR_FIF_OVR_MASK))
    {
        LOG_I("FIF Overrun %d",hadc->Instance->FIFO_FLVL);
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_FIF_OVR_MASK);
        REG_FIELD_WR(hadc->Instance->FIF_CTRL0,ADC_FIFO_CLR,1);
    }
    __HAL_ADC_DISABLE(hadc);
    hadc->Env.DMA.Callback(hadc);
}

HAL_StatusTypeDef HAL_ADC_LoopChannel_Start_DMA(ADC_HandleTypeDef* hadc, uint16_t* pData, uint32_t Length,void (*Callback)(ADC_HandleTypeDef* hadc))
{
    HAL_StatusTypeDef status = HAL_OK;
    struct DMA_Channel_Config cfg;

    status = ADC_Enable(hadc);
    hadc->Env.DMA.Callback = Callback;
    SET_BIT(hadc->Instance->MISC_CTRL,ADC_DMA_EN_MASK);

    cfg.ctrl.channel_en = 1;
    cfg.ctrl.circular_mode_en = 0;
    cfg.ctrl.peripheral_flow_ctrl = 0;
    cfg.ctrl.direct_mode_en = 0;
    cfg.ctrl.dma_mode_sel = Peri2Mem;
    cfg.ctrl.channel_priority = 0;
    cfg.ctrl.peripheral_handshake = HAL_ADC_DMA_Handshake_Get(hadc);
    cfg.ctrl.src_inc = 0;
    cfg.ctrl.src_width = DMA_SIZE_HALFWORD;
    cfg.ctrl.src_burst = 0;
    cfg.ctrl.src_inc_offset = 0;
    cfg.ctrl.rsvd0 = 0;
    cfg.ctrl.dst_inc = 1;
    cfg.ctrl.dst_witdh = DMA_SIZE_HALFWORD;
    cfg.ctrl.dst_burst = 0;
    cfg.ctrl.dst_inc_offset = 0;
    cfg.ctrl.rsvd1 = 0;

    cfg.src_addr = (uint32_t)&hadc->Instance->FIF_DAT;
    cfg.dst_addr = (uint32_t)pData;
    cfg.byte_count = Length;
    cfg.dummy = 0;

    HAL_DMA_Channel_Start_IT((DMA_Controller_HandleTypeDef *)hadc->DMAC_Instance,hadc->Env.DMA.DMA_Channel,&cfg,ADC_DMA_Callback,(uint32_t)hadc);

    if(hadc->Init.TrigType == ADC_SOFTWARE_TRIGT)
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_FIF_TRIG,1);
    }

    return status;
}

HAL_StatusTypeDef HAL_AD_LoopChannelC_Stop_DMA(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;

    CLEAR_BIT(hadc->Instance->MISC_CTRL,ADC_DMA_EN_MASK);
    __HAL_ADC_DISABLE(hadc);

    return status;
}

