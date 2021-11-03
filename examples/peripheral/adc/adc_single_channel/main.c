#include "lsadc.h"
#include "platform.h"
#include "io_config.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "lsdmac.h"
#include "reg_syscfg.h"
static void Error_Handler(void);

static uint16_t adc_value;

static ADC_HandleTypeDef hadc;

static volatile uint8_t recv_flag = 0;

static void lsadc_init(void)
{
    io_clr_pin(PA00);
    io_cfg_output(PA00);
    hadc.Instance = LSADC;
    hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode          = ADC_SCAN_DISABLE;              /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    hadc.Init.NbrOfConversion       = 1;                            /* Parameter discarded because sequencer is disabled */
    hadc.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    hadc.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */
    hadc.Init.ContinuousConvMode    = DISABLE;                        /* Continuous mode to have maximum conversion speed (no delay between conversions) */
    hadc.Init.TrigType      = ADC_INJECTED_SOFTWARE_TRIGT;            /* The reference voltage uses an internal reference */
    hadc.Init.Vref          = ADC_VREF_INSIDE;
    hadc.Init.AdcCkDiv = ADC_CLOCK_DIV2;

    if (HAL_ADC_Init(&hadc) != HAL_OK)
    {
        Error_Handler();
    }
    ADC_InjectionConfTypeDef sConfigInjected = {0};
    sConfigInjected.InjectedChannel = ADC_CHANNEL_VBAT;
    sConfigInjected.InjectedRank = ADC_INJECTED_RANK_1;
    sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_15CYCLES;
    sConfigInjected.InjectedOffset = 0;
    sConfigInjected.InjectedNbrOfConversion = 1;
    sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
    sConfigInjected.AutoInjectedConv = DISABLE;

  if (HAL_ADCEx_InjectedConfigChannel(&hadc, &sConfigInjected) != HAL_OK)
  {
    /* Channel Configuration Error */
    Error_Handler();
  }
}

int main(void)
{
    sys_init_none();
	lsadc_init();
    HAL_ADCEx_InjectedStart_IT(&hadc);
    recv_flag = 0;
	while(1)
	{
		if(recv_flag == 1) 
		{
            DELAY_US(200*1000); //delay 200ms
            recv_flag = 0;
            LOG_I("Vbat_vol: %d mv",(8*1400*adc_value/4095));  //By default, 1/8 of the power supply is used to collect
			HAL_ADCEx_InjectedStart_IT(&hadc);
		}
	};
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
static void Error_Handler(void)
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

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    recv_flag = 1;
    adc_value = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
}

