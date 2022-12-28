#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "ls_hal_adcv2.h"
#include "log.h"

static ADC_HandleTypeDef ADCx_Hdl;
uint32_t adc_test_num = 0;

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

void ADC_InjMode_Channel_setCfg(void)
{
    ADC_InjectionConfTypeDef sConfigInjected = {0};
    sConfigInjected.InjectedChannel         = ADC_CHANNEL_5;
    sConfigInjected.InjectedRank            = ADC_INJECTED_RANK_1;
    sConfigInjected.InjectedSamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfigInjected.InjectedOffset          = 0;
    sConfigInjected.InjectedClk             = ADC_CH_CLOCK_DIV8;
    sConfigInjected.InjectedNbrOfConversion = 3;
    sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
    if (HAL_ADCEx_InjectedConfigChannel(&ADCx_Hdl, &sConfigInjected) != HAL_OK)
    {
        Error_Handler();
    }

    sConfigInjected.InjectedChannel         = ADC_CHANNEL_6;
    sConfigInjected.InjectedRank            = ADC_INJECTED_RANK_2;
    sConfigInjected.InjectedSamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfigInjected.InjectedOffset          = 0;
    sConfigInjected.InjectedClk             = ADC_CH_CLOCK_DIV8;
    if (HAL_ADCEx_InjectedConfigChannel(&ADCx_Hdl, &sConfigInjected) != HAL_OK)
    {
        Error_Handler();
    }

    sConfigInjected.InjectedChannel         = ADC_CHANNEL_7;
    sConfigInjected.InjectedRank            = ADC_INJECTED_RANK_3;
    sConfigInjected.InjectedSamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfigInjected.InjectedOffset          = 0;
    sConfigInjected.InjectedClk             = ADC_CH_CLOCK_DIV8;
    if (HAL_ADCEx_InjectedConfigChannel(&ADCx_Hdl, &sConfigInjected) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_LoopMode_Channel_setcfg(void)
{
    ADC_LoopConfTypeDef sConfig = {0};
    sConfig.Channel         = ADC_CHANNEL_5;
    sConfig.Rank            = ADC_LOOP_RANK_1;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk         = ADC_CH_CLOCK_DIV8;
    sConfig.NbrOfConversion = 3;
    sConfig.CapIntv = 0xFFFF;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }

    sConfig.Channel         = ADC_CHANNEL_6;
    sConfig.Rank            = ADC_LOOP_RANK_2;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk         = ADC_CH_CLOCK_DIV8;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }

    sConfig.Channel         = ADC_CHANNEL_7;
    sConfig.Rank            = ADC_LOOP_RANK_3;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk         = ADC_CH_CLOCK_DIV8;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_RegMode_Poll_GetValue(void)
{
    HAL_ADC_Start(&ADCx_Hdl);
    if (HAL_ADC_PollForConversion(&ADCx_Hdl, 1000) == HAL_OK)
    {
        LOG_I("RegMode:%d,%d,%d", HAL_ADC_GetValue(&ADCx_Hdl, ADC_REGULAR_RANK_1),
                          HAL_ADC_GetValue(&ADCx_Hdl, ADC_REGULAR_RANK_2),
                          HAL_ADC_GetValue(&ADCx_Hdl, ADC_REGULAR_RANK_3));
    }
    else
    {
        LOG_I("TIMEOUT");
    }
}

void ADC_InjMode_Poll_GetValue(void)
{
    HAL_ADCEx_InjectedStart(&ADCx_Hdl);
    if (HAL_ADCEx_InjectedPollForConversion(&ADCx_Hdl, 1000) == HAL_OK)
    {
        LOG_I("InjMode:%d,%d,%d", HAL_ADCEx_InjectedGetValue(&ADCx_Hdl, ADC_REGULAR_RANK_1),
                          HAL_ADCEx_InjectedGetValue(&ADCx_Hdl, ADC_REGULAR_RANK_2),
                          HAL_ADCEx_InjectedGetValue(&ADCx_Hdl, ADC_REGULAR_RANK_3));
    }
    else
    {
        LOG_I("TIMEOUT");
    }
}

void ADC_LoopMode_Poll_GetValue(void)
{
    HAL_ADCx_LoopStart(&ADCx_Hdl);
    if (HAL_ADCx_LoopPollForConversion(&ADCx_Hdl, 1000) == HAL_OK)
    {
        uint8_t fif_lvl_num = LOOP_MDOE_FIFO_LVL_NUM_GET(&ADCx_Hdl);
        for(uint8_t i=0;i<fif_lvl_num;i++)
        {
            LOG_I("LOOPMode RANK%d:%d",i%3,HAL_ADCx_LoopGetValue(&ADCx_Hdl));
        }
    }
    else
    {
        LOG_I("TIMEOUT");
    }
}

int main(void)
{
    uint8_t inj_ch_cfg_flag = 0;
    uint8_t loop_ch_cfg_flag = 0;
    sys_init_none();
    LOG_I("ADC Blocking Sample Test Start...");
    pinmux_adc_init();
    ADC_Init_Func();
    ADC_RegMode_Channel_setCfg();
	while(1)
	{
        if (adc_test_num < 20)
        {
            ADC_RegMode_Poll_GetValue();
        }
        else if (adc_test_num < 40)
        {
            if (!inj_ch_cfg_flag)
            {
                inj_ch_cfg_flag = 1;
                ADC_InjMode_Channel_setCfg();
            }
            ADC_InjMode_Poll_GetValue();
        }
        else if(adc_test_num < 60)
        {
            if (!loop_ch_cfg_flag)
            {
                loop_ch_cfg_flag = 1;
                ADC_LoopMode_Channel_setcfg();
            }
            ADC_LoopMode_Poll_GetValue();
        }
        else
        {
            if (loop_ch_cfg_flag)
            {
                loop_ch_cfg_flag = 0;
                HAL_ADCx_LoopStop(&ADCx_Hdl);
                LOG_I("ADC Blocking Sample Test End!!!");
            }
        }
        adc_test_num++;
        DELAY_US(500000);
	};
}

