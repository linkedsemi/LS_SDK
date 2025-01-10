#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "ls_hal_adcv2.h"
#include "ls_hal_pis.h"
#include "ls_hal_uart.h"
#include "ls_hal_timer.h"
#include "log.h"

static ADC_HandleTypeDef ADCx_Hdl;
static TIM_HandleTypeDef timHandle;

static void pinmux_adc_init(void)
{
    pinmux_adc1_in5_init(); // PA14
}

void Error_Handler(void)
{
    while (1)
        ;
}

void ADC_Init_Func(void)
{
    ADCx_Hdl.Instance = LSADC1;
    ADCx_Hdl.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    ADCx_Hdl.Init.ContinuousConvMode = DISABLE;
    ADCx_Hdl.Init.NbrOfConversion = 1;
    ADCx_Hdl.Init.DiscontinuousConvMode = DISABLE;
    ADCx_Hdl.Init.NbrOfDiscConversion = 0;
    ADCx_Hdl.Init.TrigType = ADC_SOFTWARE_TRIGT;
    ADCx_Hdl.Init.Vref = ADC_VREF_INSIDE;
    ADCx_Hdl.Init.AdcDriveType = BINBUF_DIRECT_DRIVE_ADC;
    ADCx_Hdl.Init.AdcCkDiv = 256;
    if (HAL_ADC_Init(&ADCx_Hdl) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_RegMode_Channel_setCfg(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_5;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    sConfig.clk_cfg = ADC_CH_CLOCK_DIV8;
    if (HAL_ADC_ConfigChannel(&ADCx_Hdl, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_trigger_Init(void)
{
    timHandle.Instance = LSGPTIMA;
    timHandle.Init.Prescaler = SDK_HCLK_MHZ - 1;
    timHandle.Init.Period = 200000; // 200000us = 200ms;
    timHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    timHandle.Init.TrgoSource = TIM_TRGO_UPDATE;

    /* PIS */
    HAL_PIS_Config(1, GPTIMA1_ADCTRIG, ADC0_REG_TRIG, PIS_SYNC_DIRECT, PIS_EDGE_NONE);

    HAL_TIM_Init(&timHandle);
    HAL_TIM_Base_Start(&timHandle);
}

int main(void)
{
    uint32_t value = 0;
    uint32_t value_temp = 0;

    sys_init_none();
    LOG_I("ADC Timer trigger Test Start...");
    pinmux_adc_init();
    ADC_Init_Func();
    ADC_RegMode_Channel_setCfg();
    ADC_trigger_Init();

    HAL_ADC_Start(&ADCx_Hdl);

    while (1)
    {
        value_temp = HAL_ADC_GetValue(&ADCx_Hdl, ADC_REGULAR_RANK_1);
        if (value != value_temp)
        {
            value = value_temp;
            LOG_I("Regular CH5 AD:%d", value);
        }
    }
}
