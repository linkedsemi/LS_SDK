#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "ls_hal_adcv2.h"
#include "log.h"

static ADC_HandleTypeDef ADCx_Hdl;

static void pinmux_adc_init(void)
{
    pinmux_adc1_in5_init();// PA01
    pinmux_adc1_in6_init();// PA02
    pinmux_adc1_in7_init();// PA03
}

void Error_Handler(void)
{
    while(1);
}

void ADC_Init_Func(void)
{
    ADCx_Hdl.Instance                   = LSADC1;
    ADCx_Hdl.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    ADCx_Hdl.Init.ContinuousConvMode    = ENABLE;
    ADCx_Hdl.Init.NbrOfConversion       = 3;
    ADCx_Hdl.Init.DiscontinuousConvMode = DISABLE;
    ADCx_Hdl.Init.NbrOfDiscConversion   = 0; 
    ADCx_Hdl.Init.TrigType              = ADC_SOFTWARE_TRIGT;
    ADCx_Hdl.Init.Vref                  = ADC_VREF_INSIDE;
    ADCx_Hdl.Init.AdcDriveType          = BINBUF_DIRECT_DRIVE_ADC;
    ADCx_Hdl.Init.AdcCkDiv              = 256;
    if (HAL_ADC_Init(&ADCx_Hdl) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_RegMode_Channel_setCfg(void)
{
    ADC_ChannelConfTypeDef sConfig  = {0};
    sConfig.Channel         = ADC_CHANNEL_5;
    sConfig.Rank            = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.clk_cfg         = ADC_CH_CLOCK_DIV8;
    if (HAL_ADC_ConfigChannel(&ADCx_Hdl, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfig.Channel         = ADC_CHANNEL_6;
    sConfig.Rank            = ADC_REGULAR_RANK_2;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.clk_cfg         = ADC_CH_CLOCK_DIV8;
    if (HAL_ADC_ConfigChannel(&ADCx_Hdl, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfig.Channel         = ADC_CHANNEL_7;
    sConfig.Rank            = ADC_REGULAR_RANK_3;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.clk_cfg         = ADC_CH_CLOCK_DIV8;
    if (HAL_ADC_ConfigChannel(&ADCx_Hdl, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADCx_Hdl.Instance)
    {
        LOG_I("RegMode:%d,%d,%d", HAL_ADC_GetValue(&ADCx_Hdl, ADC_REGULAR_RANK_1),
                          HAL_ADC_GetValue(&ADCx_Hdl, ADC_REGULAR_RANK_2),
                          HAL_ADC_GetValue(&ADCx_Hdl, ADC_REGULAR_RANK_3));
    }
}

void HAL_ADC_Analog_Wdg_config(void)
{
    ADC_AnalogWDGConfTypeDef AnalogWDGConfig = {0};
    AnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_ALL_REG;
    AnalogWDGConfig.Channel = ADC_CHANNEL_0;
    AnalogWDGConfig.ITMode = ENABLE;
    AnalogWDGConfig.HighThreshold = 2400;
    AnalogWDGConfig.LowThreshold = 10;
    HAL_ADC_AnalogWDGConfig(&ADCx_Hdl, &AnalogWDGConfig);
}

void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
    LOG_I("AWD CB");
    io_toggle_pin(PA00);
}

int main(void)
{
    sys_init_none();
    LOG_I("ADC AWD Start...");
    pinmux_adc_init();
    ADC_Init_Func();
    ADC_RegMode_Channel_setCfg();
    HAL_ADC_Analog_Wdg_config();
    
    io_clr_pin(PA00);
    io_cfg_output(PA00);
	while(1)
	{
        HAL_ADC_Start_IT(&ADCx_Hdl);
        DELAY_US(500000);
	};
}

