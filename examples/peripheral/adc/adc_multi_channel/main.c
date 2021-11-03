#include "lsadc.h"
#include "platform.h"
#include "io_config.h"
#include <string.h>
#include <stdlib.h>
#include "lsdmac.h"



static void Error_Handler(void);

/* Buffer used for reception */

uint16_t aRxBuffer[16];


ADC_HandleTypeDef hadc;


volatile uint8_t recv_flag = 0;

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

void lsadc_init(void)
{


    /** Common config  */
    hadc.Instance = LSADC;
    hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode          = ADC_SCAN_DISABLE;              /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    hadc.Init.NbrOfConversion       = 9;                            /* Parameter discarded because sequencer is disabled */
    hadc.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    hadc.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */

    hadc.Init.ContinuousConvMode    = ENABLE;                        /* Continuous mode to have maximum conversion speed (no delay between conversions) */
    hadc.Init.TrigType      = ADC_REGULAR_SOFTWARE_TRIGT;            /* Trig of conversion start done by which event */
    hadc.Init.Vref          = ADC_VREF_INSIDE; 

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
}

int main(void)
{
    sys_init_none();
	adc_io_init();
	lsadc_init();

  /* Start ADC conversion on regular group with transfer by IT */
	HAL_ADC_Start_IT(&hadc);


    recv_flag = 0;
	while(1)
	{
		if(recv_flag >= 9) 
		{
            DELAY_US(1000);
            recv_flag = 0;
			HAL_ADC_Start_IT(&hadc);
		}	
	};
	
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

   if(recv_flag<9)
   {
       aRxBuffer[recv_flag++] = HAL_ADC_GetValue(hadc);
   }
   // HAL_ADC_Stop_IT(hadc);   //close adc per
}


