#include <stdio.h>
#include "ls_hal_adcv2.h"
#include "ls_msp_adc.h" 
#include "field_manipulate.h"
#include "systick.h"
#include "ls_dbg.h"
#include "log.h"

#define ADC_DISABLE_TIMEOUT     2
                        
static bool adc_isenable_poll(va_list va)
{
    ADC_HandleTypeDef *hadc = va_arg(va,ADC_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
    if (ADC_IS_ENABLE(hadc) == flag)
    {
    return true;
    }
    else
    {
    return false;
    }
}

static bool adc_flag_poll(va_list va)
{
    ADC_HandleTypeDef *hadc = va_arg(va,ADC_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
      if (hadc->Instance->INTR_R & flag)
      {
        return true;
      }
      else
      {
        return false;
      }
}

HAL_StatusTypeDef HAL_ADC_VrefType_SetConfig(ADC_HandleTypeDef *hadc,  enum ADC_Vref_TypeDef Vtype)
{
    uint32_t tmp_adr = 0;

    switch (Vtype)
    {
    case ADC_VREF_VCC:
    tmp_adr = FIELD_BUILD(ADC_ADR_BP,1)|FIELD_BUILD(ADC_ADR_VREFBUF_EN,0)|
            FIELD_BUILD(ADC_ADR_VCM_EN,1)|FIELD_BUILD(ADC_ADR_VREF_EN,0)|
            FIELD_BUILD(ADC_ADR_VRSEL,1);
    break;
    case ADC_VREF_EXPOWER:
    tmp_adr = FIELD_BUILD(ADC_ADR_BP,0)|FIELD_BUILD(ADC_ADR_VREFBUF_EN,0)|
            FIELD_BUILD(ADC_ADR_VCM_EN,1)|FIELD_BUILD(ADC_ADR_VREF_EN,1)|
            FIELD_BUILD(ADC_ADR_VRSEL,2);
    break;
    case ADC_VREF_INSIDE:
    default:
    tmp_adr = FIELD_BUILD(ADC_ADR_BP,1)|FIELD_BUILD(ADC_ADR_VREFBUF_EN,1)| 
            FIELD_BUILD(ADC_ADR_VCM_EN,1)|FIELD_BUILD(ADC_ADR_VREF_EN,1)|
            FIELD_BUILD(ADC_ADR_VRSEL,4);
    break;
    }

    if(hadc->Init.AdcDriveType == BINBUF_DIRECT_DRIVE_ADC)
    {
        tmp_adr |= FIELD_BUILD(ADC_ADR_EN_INBUF_A,0)|FIELD_BUILD(ADC_ADR_EN_INBUF_B,0);
    }else{
        tmp_adr |= FIELD_BUILD(ADC_ADR_EN_INBUF_A,1)|FIELD_BUILD(ADC_ADR_EN_INBUF_B,1);
    }

    MODIFY_REG(hadc->Instance->ADR, 
               ADC_ADC_MSB_CAL_MASK|ADC_ADR_LP_CTL_MASK|ADC_ADR_G_CAL_MASK|ADC_ADR_OS_CAL_MASK,
               tmp_adr);

    return HAL_OK;
}

static void HAL_ADC_Capture_Sequence_Set(reg_adc_t *ADCx,ADC_InitTypeDef *Structure)
{
    uint32_t disc_num = 0;
    uint32_t disc_en = 0;
    REG_FIELD_WR(ADCx->REG_CTRL1,ADC_REG_SEQLEN,Structure->NbrOfConversion - 1);
    if(Structure->DiscontinuousConvMode == ENABLE)
    {
        disc_num = Structure->NbrOfDiscConversion - 1;
        disc_en = 1;
    }
    if(Structure->ContinuousConvMode == ENABLE)
    {
        disc_num = Structure->NbrOfConversion - 1;
        disc_en = 0;
    }

    REG_FIELD_WR(ADCx->DISC_CTRL,ADC_DISC_NUM,disc_num);
    REG_FIELD_WR(ADCx->DISC_CTRL,ADC_REG_DISCEN,disc_en);
}

HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef status = HAL_OK;   
    uint32_t tmp_misc_ctrl = 0;

    /* Check the parameters */
    LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
    LS_ASSERT(IS_ADC_DATA_ALIGN(hadc->Init.DataAlign));
    LS_ASSERT(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
    LS_ASSERT(IS_VREF_SWITCH(hadc->Init.Vref));

    HAL_ADC_MSP_Init(hadc);
    HAL_ADC_MSP_Busy_Set(hadc); 

    hadc->Instance->ADCH = FIELD_BUILD(ADC_ADCH_GE_CALV,1)|
                           FIELD_BUILD(ADC_ADCH_OS_CALV,0xA0)|
                           FIELD_BUILD(ADC_ADCH_TRIM_EN,0);

    tmp_misc_ctrl |= hadc->Init.DataAlign;
    tmp_misc_ctrl |= hadc->Init.AdcCkDiv << ADC_ADC_DIV_POS;
    tmp_misc_ctrl |= ADC_ADC_RES_MASK; 

    MODIFY_REG(hadc->Instance->MISC_CTRL,
               ADC_ADC_DIV_MASK|ADC_ADC_EN_MASK|ADC_DATA_ALIGN_MASK|ADC_DMA_EN_MASK,
               tmp_misc_ctrl);

    HAL_ADC_VrefType_SetConfig(hadc,hadc->Init.Vref);

    HAL_ADC_Capture_Sequence_Set(hadc->Instance,&hadc->Init);

    return status;
}

HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;
    LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
    HAL_ADC_MSP_DeInit(hadc);
    HAL_ADC_MSP_Idle_Set(hadc);
    adc_channel_vbat_disable();
    return status;
}

HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;
    SET_BIT(hadc->Instance->MISC_CTRL,ADC_ADC_EN_MASK);
    return status;
}

HAL_StatusTypeDef ADC_ConversionStop_Disable(ADC_HandleTypeDef* hadc)
{
    uint32_t tickstart = 0U;
    uint32_t timeout = SYSTICK_MS2TICKS(ADC_DISABLE_TIMEOUT);
    /* Verification if ADC is not already disabled */
    if(ADC_IS_ENABLE(hadc) != RESET)
    {
        /* Disable the ADC peripheral */
        __HAL_ADC_DISABLE(hadc);

        /* Get tick count */
        tickstart = systick_get_value();

        /* Wait for ADC effectively disabled */
        if(systick_poll_timeout(tickstart,timeout,adc_isenable_poll,hadc,RESET))
        {
            return HAL_ERROR;
        }
    }
    return HAL_OK;
}

static void HAL_ADC_Sample_Data_Path_set(ADC_HandleTypeDef *hadc, uint32_t Channel)
{
    uint32_t byp_cfg_tmp = 0;

    byp_cfg_tmp = hadc->Instance->BYP_CFG;
    if(hadc->Init.AdcDriveType == EINBUF_DRIVE_ADC)
    {
        byp_cfg_tmp &= ~(1 << Channel);
        byp_cfg_tmp |= 1<<16<< Channel;
        
    }
    else if(hadc->Init.AdcDriveType == INRES_ONETHIRD_EINBUF_DRIVE_ADC)
    {
        byp_cfg_tmp &= ~(1 << Channel);
        byp_cfg_tmp &= ~(1<<16 <<Channel);
    }
    else
    {
        byp_cfg_tmp |= 1 << Channel;
        byp_cfg_tmp |= 1<<16<< Channel;
    }

    hadc->Instance->BYP_CFG |= byp_cfg_tmp;
}

static void HAL_ADC_Ch_cfg_Reg_SetConfig(reg_adc_t *ADCx, uint32_t Channel)
{
    // ADC Channel Enable
    ADCx->CH_CFG |= 1<<Channel;
    if(Channel > ADC_CHANNEL_3 && Channel <= ADC_CHANNEL_7)
    {
        ADCx->CH_CFG |= 1<<16<<Channel;
    }
    else
    {
        ADCx->CH_CFG &=~(1<<16<<Channel);
    }  
}

HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Check the parameters */
    LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
    LS_ASSERT(IS_ADC_CHANNEL(sConfig->Channel));
    LS_ASSERT(IS_ADC_REGULAR_RANK(sConfig->Rank));
    LS_ASSERT(IS_ADC_SAMPLE_TIME(sConfig->SamplingTime));
    
    HAL_ADC_Sample_Data_Path_set(hadc,sConfig->Channel);
    /* Regular sequence configuration */
    /* For Rank 1 to 8 */
    if (sConfig->Rank <= ADC_REGULAR_RANK_8)
    {
        hadc->Instance->REG_CTRL0 |= ADC_REG_SEQ0_RK(sConfig->Channel, sConfig->Rank);
    }
    /* For Rank 9 to 12 */
    else 
    {
        hadc->Instance->REG_CTRL1 |= ADC_REG_SEQ1_RK(sConfig->Channel, sConfig->Rank);
    }

    hadc->Instance->CLK_CFG |= ADC_CH_CLK_CFG(sConfig->clk_cfg,sConfig->Channel);

    /* Channel sampling time configuration */
    /* For channels 0 to 11 */
    hadc->Instance->TSMP |= ADC_TSMP(sConfig->SamplingTime, sConfig->Channel);

    if(sConfig->Channel == ADC1_CHANNEL_VBAT)
    {
        adc_channel_vbat_enable();
    }
    else if(sConfig->Channel == ADC1_CHANNEL_TEMPSENSOR)
    {

    }

    HAL_ADC_Ch_cfg_Reg_SetConfig(hadc->Instance,sConfig->Channel);
    
    return status;
}

static void HAL_ADC_Inj_Offset_Config(reg_adc_t* ADCx,uint32_t InjRank,uint32_t OffsetVal)
{
    /* Configure the offset: offset enable/disable, InjectedChannel, offset value */
    switch(InjRank)
    {
    case ADC_INJECTED_RANK_1:
    /* Set injected channel 1 offset */
    MODIFY_REG(ADCx->INJ_OFF00,
                ADC_INJ_OFFSET0_MASK,
                OffsetVal);
    break;
    case ADC_INJECTED_RANK_2:
    /* Set injected channel 2 offset */
    MODIFY_REG(ADCx->INJ_OFF01,
                ADC_INJ_OFFSET1_MASK,
                OffsetVal);
    break;
    case ADC_INJECTED_RANK_3:
    /* Set injected channel 3 offset */
    MODIFY_REG(ADCx->INJ_OFF02,
                ADC_INJ_OFFSET2_MASK,
                OffsetVal);
    break;
    case ADC_INJECTED_RANK_4:
    MODIFY_REG(ADCx->INJ_OFF03,
                ADC_INJ_OFFSET3_MASK,
                OffsetVal);
    break;
    default:
    break;
    }
}

HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc, ADC_InjectionConfTypeDef* sConfigInjected)
{
    HAL_StatusTypeDef status = HAL_OK;

    hadc->Instance->CLK_CFG |= ADC_CH_CLK_CFG(sConfigInjected->InjectedClk,sConfigInjected->InjectedChannel);

    /* Channel sampling time configuration */
    hadc->Instance->TSMP |= ADC_TSMP(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel);

    if(sConfigInjected->InjectedRank <= sConfigInjected->InjectedNbrOfConversion)
    {
        if(REG_FIELD_RD(hadc->Instance->INJ_CTRL,ADC_INJ_SEQLEN) != sConfigInjected->InjectedNbrOfConversion)
        {
            REG_FIELD_WR(hadc->Instance->INJ_CTRL,ADC_INJ_SEQLEN,sConfigInjected->InjectedNbrOfConversion - 1);
        }

        hadc->Instance->INJ_CTRL |= ADC_INJ_SEQ_RK(sConfigInjected->InjectedChannel,sConfigInjected->InjectedRank);

        HAL_ADC_Sample_Data_Path_set(hadc,sConfigInjected->InjectedChannel);

        HAL_ADC_Inj_Offset_Config(hadc->Instance,sConfigInjected->InjectedRank,sConfigInjected->InjectedOffset);

        if(sConfigInjected->InjectedChannel == ADC1_CHANNEL_VBAT)
        {
            adc_channel_vbat_enable();
        }
        else if(sConfigInjected->InjectedChannel == ADC1_CHANNEL_TEMPSENSOR)
        {

        }

        HAL_ADC_Ch_cfg_Reg_SetConfig(hadc->Instance,sConfigInjected->InjectedChannel);
    }
    else
    {
        status = HAL_INVALIAD_PARAM;
    }

    if(status == HAL_OK)
    {
        if(sConfigInjected->InjectedDiscontinuousConvMode == ENABLE)
        {
            REG_FIELD_WR(hadc->Instance->DISC_CTRL,ADC_INJ_DISCEN,1);
        }
        else
        {
            REG_FIELD_WR(hadc->Instance->DISC_CTRL,ADC_INJ_DISCEN,0);
        }
    }
    
    return status;
}

HAL_StatusTypeDef HAL_ADC_LoopConfigChannel(ADC_HandleTypeDef* hadc,ADC_LoopConfTypeDef* sConfig)
{
    HAL_StatusTypeDef status = HAL_OK;

    if(sConfig->Rank <= sConfig->NbrOfConversion)
    {
        hadc->Instance->CLK_CFG |= ADC_CH_CLK_CFG(sConfig->LoopClk,sConfig->Channel);

        /* Channel sampling time configuration */
        hadc->Instance->TSMP |= ADC_TSMP(sConfig->SamplingTime, sConfig->Channel);

        hadc->Instance->FIF_CTRL1 = sConfig->CapIntv;

        if(REG_FIELD_RD(hadc->Instance->FIF_CTRL0,ADC_FIF_SEQLEN) != sConfig->NbrOfConversion)
        {
            REG_FIELD_WR(hadc->Instance->FIF_CTRL0,ADC_FIF_SEQLEN,sConfig->NbrOfConversion - 1);
        }

        hadc->Instance->FIF_CTRL0 |= ADC_FIF_SEQ_RK(sConfig->Channel,sConfig->Rank);

        HAL_ADC_Sample_Data_Path_set(hadc,sConfig->Channel);

        if(sConfig->Channel == ADC1_CHANNEL_VBAT)
        {
            adc_channel_vbat_enable();
        }
        else if(sConfig->Channel == ADC1_CHANNEL_TEMPSENSOR)
        {

        }
        else if(sConfig->Channel == ADC2_CHANNEL_AMIC)
        {
            HAL_AMIC_MSP_Init();
        }

        HAL_ADC_Ch_cfg_Reg_SetConfig(hadc->Instance,sConfig->Channel);
    }
    else
    {
        status = HAL_INVALIAD_PARAM;
    }
    return status;
}

HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{
    HAL_StatusTypeDef status = HAL_OK;

    if (AnalogWDGConfig->ITMode == ENABLE)
    {
        /* Enable the ADC Analog watchdog interrupt */
        __HAL_ADC_ENABLE_IT(hadc, ADC_INTR_AWDH_MASK);
        __HAL_ADC_ENABLE_IT(hadc, ADC_INTR_AWDL_MASK);
    }
    else
    {
        /* Disable the ADC Analog watchdog interrupt */
        __HAL_ADC_DISABLE_IT(hadc, ADC_INTR_AWDH_MASK);
        __HAL_ADC_DISABLE_IT(hadc, ADC_INTR_AWDL_MASK);
    }

    MODIFY_REG(hadc->Instance->AWD,
                ADC_REG_AWDEN_MASK|ADC_INJ_AWDEN_MASK|ADC_AWD_SINGLE_MASK|ADC_AWD_CHANNEL_MASK,
                AnalogWDGConfig->WatchdogMode|AnalogWDGConfig->Channel);

    /* Set the high threshold */
    WRITE_REG(hadc->Instance->AWD_H, AnalogWDGConfig->HighThreshold);

    /* Set the low threshold */
    WRITE_REG(hadc->Instance->AWD_L, AnalogWDGConfig->LowThreshold);
    return status;
}

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = ADC_Enable(hadc);
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_REG_TRIG,1);
    }
    
    return status;
}

HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef status = HAL_OK;

    /* Disable ADC peripheral */
    status = ADC_ConversionStop_Disable(hadc);
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_REG_TRIG,0);
    }
    
    return status;
}

HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
    uint32_t tickstart = 0U;
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

    /* Get tick count */
    tickstart = systick_get_value();

    /* Wait until End of Conversion flag is raised */
    if(systick_poll_timeout(tickstart,timeout,adc_flag_poll,hadc,ADC_INTR_REG_END_MASK))
    {
        return HAL_TIMEOUT;
    }

    REG_FIELD_WR(hadc->Instance->INTR_C,ADC_INTR_REG_END,1);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;
    ADC_Enable(hadc);
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_INJ_TRIG,1);
    }
    
    return status;
}

HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;
    /* Disable ADC peripheral */
    status = ADC_ConversionStop_Disable(hadc);
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_INJ_TRIG,0);
    }
    
    return status;
}

HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
    uint32_t tickstart;
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

    /* Get timeout */
    tickstart = systick_get_value();

    /* Wait until End of Conversion flag is raised */
    if(systick_poll_timeout(tickstart,timeout,adc_flag_poll,hadc,ADC_INTR_INJ_END_MASK))
    {
        return HAL_TIMEOUT;
    }

    REG_FIELD_WR(hadc->Instance->INTR_C,ADC_INTR_INJ_END,1);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADCx_LoopStart(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;
    ADC_Enable(hadc);

    // FIFO Clear Enable
    while(REG_FIELD_RD(hadc->Instance->FIFO_FLVL,ADC_FIFO_FLVL)!=0){
        REG_FIELD_WR(hadc->Instance->FIF_CTRL0,ADC_FIFO_CLR,1);
    }
    
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_FIF_TRIG,1);
    }
    
    return status;
}

HAL_StatusTypeDef HAL_ADCx_LoopStop(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;
    /* Disable ADC peripheral */
    status = ADC_ConversionStop_Disable(hadc);
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_FIF_TRIG,0);
    }
    
    REG_FIELD_WR(hadc->Instance->FIF_CTRL0,ADC_FIFO_CLR,1);
    return status;
}

HAL_StatusTypeDef HAL_ADCx_LoopPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
    uint32_t tickstart;
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

    /* Get timeout */
    tickstart = systick_get_value();

    /* Wait until End of Conversion flag is raised */
    if(systick_poll_timeout(tickstart,timeout,adc_flag_poll,hadc,ADC_INTR_FIF_END_MASK))
    {
        return HAL_TIMEOUT;
    }

    REG_FIELD_WR(hadc->Instance->INTR_C,ADC_INTR_FIF_END,1);
    REG_FIELD_WR(hadc->Instance->TRIG,ADC_FIF_TRIG,0);

    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = ADC_Enable(hadc);

    __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_REG_END_MASK);
    
    __HAL_ADC_ENABLE_IT(hadc,ADC_INTR_REG_END_MASK);

    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_REG_TRIG,1);
    }
    

    return status;
}

HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = ADC_ConversionStop_Disable(hadc);

    __HAL_ADC_DISABLE_IT(hadc,ADC_INTR_REG_END_MASK);
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_REG_TRIG,0);
    }  

    return status;
}

HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = ADC_Enable(hadc);

    __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_INJ_END_MASK);
    
    __HAL_ADC_ENABLE_IT(hadc,ADC_INTR_INJ_END_MASK);

    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_INJ_TRIG,1);
    } 

    return status;
}

HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = ADC_ConversionStop_Disable(hadc);

    __HAL_ADC_DISABLE_IT(hadc,ADC_INTR_INJ_END_MASK);

    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_INJ_TRIG,0);
    }

    return status;
}

HAL_StatusTypeDef HAL_ADCx_LoopStart_IT(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef status = HAL_OK;
    status = ADC_Enable(hadc);
    // clear state
    __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_INJ_END_MASK);

    // FIFO Clear Enable
    while(REG_FIELD_RD(hadc->Instance->FIFO_FLVL,ADC_FIFO_FLVL)!=0){
        REG_FIELD_WR(hadc->Instance->FIF_CTRL0,ADC_FIFO_CLR,1);
    }
    
    REG_FIELD_WR(hadc->Instance->INTR_M,ADC_INTR_FIF_END,1);
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_FIF_TRIG,1);
    }

    return status;
}

HAL_StatusTypeDef HAL_ADCx_LoopStop_IT(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = ADC_ConversionStop_Disable(hadc);
    if(IS_ADC_SOFTWARE_TRIGTYPE(hadc->Init.TrigType))
    {
        REG_FIELD_WR(hadc->Instance->TRIG,ADC_FIF_TRIG,0);
    }
    __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_FIF_END_MASK);
    REG_FIELD_WR(hadc->Instance->INTR_M,ADC_INTR_FIF_END,0);
    REG_FIELD_WR(hadc->Instance->FIF_CTRL0,ADC_FIFO_CLR,1);
    __HAL_ADC_DISABLE_IT(hadc,ADC_INTR_FIF_END_MASK);

    return status;
}

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc, uint32_t RegularRank)
{
    uint32_t ad_value = 0;

    if(__HAL_ADC_GET_FLAG(hadc,ADC_INTR_REG_ERR_MASK))
    {
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_REG_ERR_MASK);
        LOG_I("REG Error!!!");
    }

    switch (RegularRank)
    {
    case ADC_REGULAR_RANK_1:
        ad_value = hadc->Instance->REG_DAT00 & 0xffff;
        break;
    case ADC_REGULAR_RANK_2:
        ad_value = hadc->Instance->REG_DAT01 & 0xffff;
        break;
    case ADC_REGULAR_RANK_3:
        ad_value = hadc->Instance->REG_DAT02 & 0xffff;
        break;
    case ADC_REGULAR_RANK_4:
        ad_value = hadc->Instance->REG_DAT03 & 0xffff;
        break;
    case ADC_REGULAR_RANK_5:
        ad_value = hadc->Instance->REG_DAT04 & 0xffff;
        break;
    case ADC_REGULAR_RANK_6:
        ad_value = hadc->Instance->REG_DAT05 & 0xffff;
        break;    
    case ADC_REGULAR_RANK_7:
        ad_value = hadc->Instance->REG_DAT06 & 0xffff;
        break;
    case ADC_REGULAR_RANK_8:
        ad_value = hadc->Instance->REG_DAT07 & 0xffff;
        break;
    case ADC_REGULAR_RANK_9:
        ad_value = hadc->Instance->REG_DAT08 & 0xffff;
        break;
    case ADC_REGULAR_RANK_10:
        ad_value = hadc->Instance->REG_DAT09 & 0xffff;
        break;
    case ADC_REGULAR_RANK_11:
        ad_value = hadc->Instance->REG_DAT10 & 0xffff;
        break;
    case ADC_REGULAR_RANK_12:
        ad_value = hadc->Instance->REG_DAT11 & 0xffff;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
    return ad_value;
}

uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank)
{
    uint32_t ad_value = 0;

    if(__HAL_ADC_GET_FLAG(hadc,ADC_INTR_INJ_ERR_MASK))
    {
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_INJ_ERR_MASK);
        LOG_I("INJ Error!!!");
    }

    /* Get ADC converted value */ 
    switch(InjectedRank)
    { 
    case ADC_INJECTED_RANK_1:
        ad_value = hadc->Instance->INJ_DAT00 & 0xffff;
        break;
    case ADC_INJECTED_RANK_2: 
        ad_value = hadc->Instance->INJ_DAT01 & 0xffff;
        break;
    case ADC_INJECTED_RANK_3: 
        ad_value = hadc->Instance->INJ_DAT02 & 0xffff;
        break;
    case ADC_INJECTED_RANK_4: 
        ad_value = hadc->Instance->INJ_DAT03 & 0xffff;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
    return ad_value;
}

uint32_t HAL_ADCx_LoopGetValue(ADC_HandleTypeDef* hadc)
{
    if(__HAL_ADC_GET_FLAG(hadc,ADC_INTR_FIF_ERR_MASK))
    {
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_FIF_ERR_MASK);
        LOG_I("FIF Error!!!");
    }
    if(__HAL_ADC_GET_FLAG(hadc,ADC_INTR_FIF_OVR_MASK))
    {
        LOG_I("FIF Overrun %d",hadc->Instance->FIFO_FLVL);
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_FIF_OVR_MASK);
        REG_FIELD_WR(hadc->Instance->FIF_CTRL0,ADC_FIFO_CLR,1);
    }
    return hadc->Instance->FIF_DAT;
}

void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc)
{
    if(__HAL_ADC_GET_IT_SOURCE(hadc,ADC_INTR_REG_END_MASK))
    {
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_REG_END_MASK);
        /* Conversion complete callback */
        HAL_ADC_ConvCpltCallback(hadc);
    }
    if(__HAL_ADC_GET_IT_SOURCE(hadc,ADC_INTR_INJ_END_MASK))
    {
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_INJ_END_MASK);
        /* Conversion complete callback */ 
        HAL_ADCEx_InjectedConvCpltCallback(hadc);
    }
    if(__HAL_ADC_GET_IT_SOURCE(hadc,ADC_INTR_FIF_END_MASK))
    {
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_FIF_END_MASK);
        HAL_ADCx_LoopConvCpltCallback(hadc);
    }

    if(__HAL_ADC_GET_IT_SOURCE(hadc,ADC_INTR_AWDH_MASK))
    {
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_AWDH_MASK);
        /* Level out of window callback */ 
        HAL_ADC_LevelOutOfWindowCallback(hadc);
    }
    if(__HAL_ADC_GET_IT_SOURCE(hadc,ADC_INTR_AWDL_MASK))
    {
        __HAL_ADC_CLEAR_IT(hadc,ADC_INTR_AWDL_MASK);
        /* Level out of window callback */ 
        HAL_ADC_LevelOutOfWindowCallback(hadc);
    }
}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief  Injected conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADCEx_InjectedConvCpltCallback could be implemented in the user file
  */
}

/**
  * @brief  Loop conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADCx_LoopConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADCEx_InjectedConvCpltCallback could be implemented in the user file
  */
}

/**
  * @brief  Analog watchdog callback in non blocking mode. 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_LevelOutOfWindowCallback must be implemented in the user file.
  */
}
