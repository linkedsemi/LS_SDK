#include <stddef.h>
#include "lsadc.h"
#include "lsdmac.h"
#include "adc_msp.h"
#include "field_manipulate.h"

/**
  * @brief  DMA transfer complete callback. 
  * @param  hdma: pointer to DMA handle.
  * @retval None
  */
static void ADC_DMA_Callback(void *hdma,uint32_t param)
{
  /* Retrieve ADC handle corresponding to current DMA handle */
  ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)param;

  /* Update state machine on conversion status if not in error state */
  if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL | HAL_ADC_STATE_ERROR_DMA))
  {
    /* Update ADC state machine */
    SET_BIT(hadc->State, HAL_ADC_STATE_REG_EOC);
    
    /* Determine whether any further conversion upcoming on group regular     */
    /* by external trigger, continuous mode or scan sequence on going.        */
    /* Note: On STM32F1 devices, in case of sequencer enabled                 */
    /*       (several ranks selected), end of conversion flag is raised       */
    /*       at the end of the sequence.                                      */
    if(ADC_IS_SOFTWARE_START_REGULAR(hadc)        && 
       (hadc->Init.ContinuousConvMode == DISABLE)   )
    {
      /* Set ADC state */
      CLEAR_BIT(hadc->State, HAL_ADC_STATE_REG_BUSY);   
      
      if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_INJ_BUSY))
      {
        SET_BIT(hadc->State, HAL_ADC_STATE_READY);
      }
    }
    
    /* Conversion complete callback */
    hadc->Env.DMA.Callback();
  }
  else
  {
    /* Call DMA error callback */
    //hadc->DMA_Handle.XferErrorCallback(hdma);
  }
}

HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint16_t* pData, uint32_t Length,void (*Callback)())
{
    HAL_StatusTypeDef tmp_hal_status = HAL_OK;
     
    /* Check the parameters */
   // LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
    
	/* Process locked */
	__HAL_LOCK(hadc);
	
	/* Enable the ADC peripheral */
	tmp_hal_status = ADC_Enable(hadc);
	
	/* Start conversion if ADC is effectively enabled */
	if (tmp_hal_status == HAL_OK)
	{
			/* Set ADC state                                                        */
			/* - Clear state bitfield related to regular group conversion results   */
			/* - Set state bitfield related to regular operation                    */
			ADC_STATE_CLR_SET(hadc->State,
							HAL_ADC_STATE_READY | HAL_ADC_STATE_REG_EOC | HAL_ADC_STATE_REG_OVR | HAL_ADC_STATE_REG_EOSMP,
							HAL_ADC_STATE_REG_BUSY);
			

			/* If conversions on group regular are also triggering group injected,  */
			/* update ADC state.                                                    */
			if (READ_BIT(hadc->Instance->CR1, ADC_JAUTO_MASK) != RESET)
			{
				ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_INJ_EOC, HAL_ADC_STATE_INJ_BUSY);  
			}
			
			/* State machine update: Check if an injected conversion is ongoing */
			if (HAL_IS_BIT_SET(hadc->State, HAL_ADC_STATE_INJ_BUSY))
			{
				/* Reset ADC error code fields related to conversions on group regular */
				CLEAR_BIT(hadc->ErrorCode, (HAL_ADC_ERROR_OVR | HAL_ADC_ERROR_DMA));         
			}
			else
			{
				/* Reset ADC all error code fields */
				ADC_CLEAR_ERRORCODE(hadc);
			}
			
			/* Process unlocked */
			/* Unlock before starting ADC conversions: in case of potential         */
			/* interruption, to let the process to ADC IRQ Handler.                 */
			__HAL_UNLOCK(hadc);
			
			
			/* Clear regular group conversion flag and overrun flag */
			/* (To ensure of no unknown state from potential previous ADC           */
			/* operations)                                                          */
			__HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOC);
			
			/* Manage ADC and DMA start: ADC overrun interruption, DMA start, ADC   */
			/* start (in case of SW start):  
                                                   */
			/* Set the DMA transfer complete callback */					
            hadc->Env.DMA.Callback = Callback;
			/* Enable ADC DMA mode */
			SET_BIT(hadc->Instance->CR2, ADC_DMAEN_MASK);
            struct DMA_Channel_Config prim = {
                .src_data_end_ptr = (uint32_t)&hadc->Instance->RDR,
                .dst_data_end_ptr = (uint32_t)&pData[Length-1],
                .ctrl_data = {
                    .cycle_ctrl = DMA_Cycle_Basic,
                    .next_useburst = 0,
                    .n_minus_1 = Length - 1,
                    .R_power = DMA_RPOWER1,
                    .src_prot_ctrl = 0,
                    .dst_prot_ctrl = 0,
                    .src_size = DMA_SIZE_HALFWORD,
                    .src_inc = DMA_INC_NONE,
                    .dst_size = DMA_SIZE_HALFWORD,
                    .dst_inc = DMA_INC_HALFWORD,
                },
                .dummy = (uint32_t)ADC_DMA_Callback,
            };
            HAL_DMA_Channel_Config_Set(hadc->DMAC_Instance,hadc->Env.DMA.DMA_Channel,false,&prim);
            HAL_DMA_Channel_Start_IT(hadc->DMAC_Instance,hadc->Env.DMA.DMA_Channel,CH_ADC,(uint32_t)hadc);			
			
			/* Enable conversion of regular group.                                  */
			/* If software start has been selected, conversion starts immediately.  */
			/* If external trigger has been selected, conversion will start at next */
			/* trigger event.                                                       */
			if ( ADC_IS_SOFTWARE_START_REGULAR(hadc)) 
			{
					/* Start ADC conversion on regular group with SW start */
					SET_BIT(hadc->Instance->CR2, ADC_RTRIG_MASK);
			}
	}
	else
	{
		/* Process unlocked */
		__HAL_UNLOCK(hadc);
	}
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @note   For devices with several ADCs: This function is for single-ADC mode 
  *         only. For multimode, use the dedicated MultimodeStop function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
     
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC peripheral */
  tmp_hal_status = ADC_ConversionStop_Disable(hadc);
  
  /* Check if ADC is effectively disabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Disable ADC DMA mode */
    CLEAR_BIT(hadc->Instance->CR2, ADC_DMAEN_MASK);
    
    /* Disable the DMA channel (in case of DMA in circular mode or stop while */
    /* DMA transfer is on going)                                              */
		
    /* Check if DMA channel effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                        HAL_ADC_STATE_READY);
    }
    else
    {
      /* Update ADC state machine to error */
      SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_DMA);
    }
  }
    
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
    
  /* Return function status */
  return tmp_hal_status;
}

