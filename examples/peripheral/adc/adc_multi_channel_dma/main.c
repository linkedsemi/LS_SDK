#include "lsadc.h"
#include "platform.h"
#include "io_config.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "lsdmac.h"
#include "log.h"

#define CONVER_COMPLETED 1
#define START_CONVER 0
DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);


static void Error_Handler(void);

ADC_HandleTypeDef hadc;



/*Mutli Channel Mode*/

#define CT_MUTLI_CHANNEL_SINGLE_SAMPLING 11
DMA_RAM_ATTR uint16_t result_mutil_channel_single_sampling[CT_MUTLI_CHANNEL_SINGLE_SAMPLING];



volatile uint8_t conver_flag = 0;

/* Private functions ---------------------------------------------------------*/  
static void adc_io_init(void)
{
		 adc12b_in0_io_init(); 
		 adc12b_in1_io_init();
		 adc12b_in2_io_init();
		 adc12b_in3_io_init();
		 adc12b_in4_io_init();
		 adc12b_in5_io_init();
		 adc12b_in6_io_init();
		 adc12b_in7_io_init();
		 adc12b_in8_io_init();
}

static void lsadc_multi_channel_single_sampling_init(void)
{
    DMA_CONTROLLER_INIT(dmac1_inst);
    hadc.Env.DMA.DMA_Channel        = 0;
    hadc.DMAC_Instance              = &dmac1_inst;
     /** Common config  */
    hadc.Instance = LSADC;
    hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode          = ADC_SCAN_ENABLE;              /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    hadc.Init.NbrOfConversion       = 11;                            /* Parameter discarded because sequencer is disabled */
    hadc.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    hadc.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */
    hadc.Init.ContinuousConvMode    = DISABLE;                        /* Continuous mode to have maximum conversion speed (no delay between conversions) */
    hadc.Init.TrigType              = ADC_REGULAR_SOFTWARE_TRIGT;            /* Trig of conversion start done by which event */
    hadc.Init.Vref                  = ADC_VREF_INSIDE;                        /* default mode*/
    hadc.Init.AdcDriveType          = EINBUF_DRIVE_ADC;               /* default mode*/
    hadc.Init.AdcCkDiv              = ADC_CLOCK_DIV32;                       /* default mode*/

    if (HAL_ADC_Init(&hadc) != HAL_OK)
    {
        Error_Handler();
    }
		
    ADC_ChannelConfTypeDef sConfig = {0};
    /** 
     * Configure Regular Channel 
    */
    sConfig.Channel      = ADC_CHANNEL_0;
    sConfig.Rank         = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    
	sConfig.Channel  = ADC_CHANNEL_1;
    sConfig.Rank         = ADC_REGULAR_RANK_2;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
		
	sConfig.Channel  = ADC_CHANNEL_2;
    sConfig.Rank         = ADC_REGULAR_RANK_3;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }	
	sConfig.Channel  = ADC_CHANNEL_3;
    sConfig.Rank         = ADC_REGULAR_RANK_4;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }	
	sConfig.Channel  = ADC_CHANNEL_4;
    sConfig.Rank         = ADC_REGULAR_RANK_5;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }	
	sConfig.Channel  = ADC_CHANNEL_5;
    sConfig.Rank         = ADC_REGULAR_RANK_6;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }			
	  sConfig.Channel  = ADC_CHANNEL_6;
    sConfig.Rank         = ADC_REGULAR_RANK_7;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }		
	sConfig.Channel  = ADC_CHANNEL_7;
    sConfig.Rank         = ADC_REGULAR_RANK_8;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }	
    sConfig.Channel  = ADC_CHANNEL_8;
    sConfig.Rank         = ADC_REGULAR_RANK_9;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }	
    sConfig.Channel  = ADC_CHANNEL_TEMPSENSOR;
    sConfig.Rank         = ADC_REGULAR_RANK_10;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }
    sConfig.Channel  = ADC_CHANNEL_VBAT;
    sConfig.Rank         = ADC_REGULAR_RANK_11;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;//ADC_SAMPLETIME_15CYCLES;
    
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
       Error_Handler();
    }

}


int main(void)
{
    sys_init_none();
    adc_io_init();
	memset(&result_mutil_channel_single_sampling[0],0,sizeof(result_mutil_channel_single_sampling));
	lsadc_multi_channel_single_sampling_init();

    conver_flag = CONVER_COMPLETED;	
 
	while(1)
	{
		if(conver_flag == CONVER_COMPLETED) 
		{
            LOG_I("%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d", result_mutil_channel_single_sampling[0], 
                                                                 result_mutil_channel_single_sampling[1], 
                                                                 result_mutil_channel_single_sampling[2], 
                                                                 result_mutil_channel_single_sampling[3], 
                                                                 result_mutil_channel_single_sampling[4], 
                                                                 result_mutil_channel_single_sampling[5], 
                                                                 result_mutil_channel_single_sampling[6], 
                                                                 result_mutil_channel_single_sampling[7], 
                                                                 result_mutil_channel_single_sampling[8], 
                                                                 result_mutil_channel_single_sampling[9], 
                                                                 result_mutil_channel_single_sampling[10]);
            conver_flag = START_CONVER;
		  	 /* Start ADC conversion on regular group with transfer by DMA */
            if (HAL_ADC_Start_DMA(&hadc, (uint16_t *)(&result_mutil_channel_single_sampling[0]), CT_MUTLI_CHANNEL_SINGLE_SAMPLING, HAL_ADC_ConvCpltCallback) != HAL_OK)
            {
            /* Start Error */
                Error_Handler();
            }					

		}		
	};
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  conver_flag = CONVER_COMPLETED;
}


