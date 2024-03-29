#include "ls_hal_adc.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "ls_hal_dmac.h"
#include "reg_syscfg.h"

#define ADC_CHANNEL_0_TEST 		1				 /* channel 0 test */
#define RTC_CHANNEL_VBAT_TEST 	2				 /* channel vbat test */

#define ADC_CHANNEL_CASE ADC_CHANNEL_0_TEST

static void Error_Handler(void);

static uint16_t adc_value;

static ADC_HandleTypeDef hadc;

static volatile uint8_t recv_flag = 0;


static void lsadc_init(void)
{
#if ADC_CHANNEL_CASE == ADC_CHANNEL_0_TEST
	pinmux_adc12b_in0_init();
#endif
	
    hadc.Instance = LSADC;
    hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode          = ADC_SCAN_DISABLE;              /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    hadc.Init.NbrOfConversion       = 1;                            /* Parameter discarded because sequencer is disabled */
    hadc.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    hadc.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */
    hadc.Init.ContinuousConvMode    = DISABLE;                        /* Continuous mode to have maximum conversion speed (no delay between conversions) */
    hadc.Init.TrigType      = ADC_INJECTED_SOFTWARE_TRIGT;            /* The reference voltage uses an internal reference */
    hadc.Init.AdcCkDiv = ADC_CLOCK_DIV32;
#if ADC_CHANNEL_CASE == ADC_CHANNEL_0_TEST
    hadc.Init.Vref          = ADC_VREF_VCC;
	
#elif ADC_CHANNEL_CASE == RTC_CHANNEL_VBAT_TEST
    hadc.Init.Vref          = ADC_VREF_INSIDE;
#endif
	
    if (HAL_ADC_Init(&hadc) != HAL_OK)
    {
        Error_Handler();
    }
	
    ADC_InjectionConfTypeDef sConfigInjected = {0};
	
#if ADC_CHANNEL_CASE == ADC_CHANNEL_0_TEST
    sConfigInjected.InjectedChannel = ADC_CHANNEL_0;
	
#elif ADC_CHANNEL_CASE == RTC_CHANNEL_VBAT_TEST
    sConfigInjected.InjectedChannel = ADC_CHANNEL_VBAT;	
#endif
	
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
			
#if ADC_CHANNEL_CASE == ADC_CHANNEL_0_TEST
            LOG_I("adc_value:%d  %d mv",adc_value,(3300*adc_value/4095)); 
#elif ADC_CHANNEL_CASE == RTC_CHANNEL_VBAT_TEST
            LOG_I("Vbat_vol: %d mv",(8*1400*adc_value/4095));  //By default, 1/8 of the power supply is used to collect
#endif
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
