#include "ls_hal_adc.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "ls_hal_dmac.h"
#include "ls_hal_timer.h"
#include "pis_config.h"
#include "ls_hal_pis.h"
#include "reg_syscfg.h"

#define LED_IO PA01

static void Error_Handler(void);

static ADC_HandleTypeDef hadc;

static TIM_HandleTypeDef TimHandle;

static void timer_1ms_cfg(void)
{ 
    TimHandle.Instance           = LSGPTIMC;
    TimHandle.Init.Prescaler     = SDK_HCLK_MHZ - 1; // 1MHz freq
    TimHandle.Init.Period        = 999; // 1ms
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    TimHandle.Init.TrgoSource = TIM_TRGO_UPDATE;
    HAL_TIM_Init(&TimHandle);
    HAL_TIM_Base_Start(&TimHandle);
}
static void pis_cfg(void)
{
    HAL_PIS_Config(6,GPTIMC1_TRGO,ADC_INJ_TRIG,PIS_SYNC_DIRECT,PIS_BOTH_EDGES);
}

static void adc_analog_wdg_test_init(void)
{
    pinmux_adc12b_in0_init(); 

    hadc.Instance = LSADC;
    hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode          = ADC_SCAN_ENABLE;
    hadc.Init.NbrOfConversion       = 1;
    hadc.Init.DiscontinuousConvMode = DISABLE;
    hadc.Init.NbrOfDiscConversion   = 1;
    hadc.Init.ContinuousConvMode    = DISABLE;
    hadc.Init.TrigType      = ADC_PIS_TRIG;
    hadc.Init.Vref          = ADC_VREF_INSIDE;
    hadc.Init.AdcCkDiv = ADC_CLOCK_DIV32;
    if (HAL_ADC_Init(&hadc) != HAL_OK)
    {
        Error_Handler();
    }

    ADC_InjectionConfTypeDef sConfigInjected = {0};
    sConfigInjected.InjectedChannel = ADC_CHANNEL_0; // PB12
    sConfigInjected.InjectedRank = ADC_INJECTED_RANK_1;
    sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_15CYCLES;
    sConfigInjected.InjectedOffset = 0;
    sConfigInjected.InjectedNbrOfConversion = 2;
    sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
    sConfigInjected.AutoInjectedConv = DISABLE;

    if (HAL_ADCEx_InjectedConfigChannel(&hadc, &sConfigInjected) != HAL_OK)
    {
        /* Channel Configuration Error */
        Error_Handler();
    }

    sConfigInjected.InjectedChannel = ADC_CHANNEL_VBAT;
    sConfigInjected.InjectedRank = ADC_INJECTED_RANK_2;
    sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_15CYCLES;
    sConfigInjected.InjectedOffset = 0;
    sConfigInjected.InjectedNbrOfConversion = 2;
    sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
    sConfigInjected.AutoInjectedConv = DISABLE;

    if (HAL_ADCEx_InjectedConfigChannel(&hadc, &sConfigInjected) != HAL_OK)
    {
        /* Channel Configuration Error */
        Error_Handler();
    }

    ADC_AnalogWDGConfTypeDef AnalogWDGConfig;
    AnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_SINGLE_INJEC;
    AnalogWDGConfig.Channel = ADC_CHANNEL_0;
    AnalogWDGConfig.ITMode = ENABLE;
    AnalogWDGConfig.HighThreshold = 0xfff/2; // half of the highest voltage
    AnalogWDGConfig.LowThreshold = 0xfff/8; 
    extern HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);
    HAL_ADC_AnalogWDGConfig(&hadc, &AnalogWDGConfig);
    HAL_ADCEx_InjectedStart(&hadc);
    pis_cfg();
    timer_1ms_cfg();
    LOG_I("adc_analog_wdg_test_init");
}

void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
    io_toggle_pin(PA01);
}

int main(void)
{
    sys_init_none();
    adc_analog_wdg_test_init();
    io_clr_pin(PA01);
    io_cfg_output(PA01);
    while(1)
    {
        DELAY_US(1000*1000); // delay for 1s
        LOG_I("adc value %d", HAL_ADCEx_InjectedGetValue(&hadc, ADC_INJECTED_RANK_1));
        LOG_I("bat value %d", HAL_ADCEx_InjectedGetValue(&hadc, ADC_INJECTED_RANK_2));
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
