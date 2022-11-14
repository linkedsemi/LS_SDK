#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "ls_hal_adcv2.h"
#include "log.h"

uint32_t adc_test_num = 0;
uint8_t loop_mode_num = 0;
static ADC_HandleTypeDef ADCx_Hdl;

static void pinmux_adc_init(void)
{
    pinmux_adc1_in5_init();// PA01
}

void Error_Handler(void)
{
    while(1);
}

void ADC_Init_Func(void)
{
    ADCx_Hdl.Instance                   = LSADC1;
    ADCx_Hdl.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    ADCx_Hdl.Init.ContinuousConvMode    = DISABLE;
    ADCx_Hdl.Init.NbrOfConversion       = 1;
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
    sConfig.Channel                 = ADC_CHANNEL_5;
    sConfig.Rank                    = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime            = ADC_SAMPLETIME_15CYCLES;
    sConfig.clk_cfg                 = ADC_CH_CLOCK_DIV8;
    if (HAL_ADC_ConfigChannel(&ADCx_Hdl, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_InjMode_Channel_setCfg(void)
{
    ADC_InjectionConfTypeDef sConfigInjected = {0};
    sConfigInjected.InjectedChannel = ADC_CHANNEL_5;
    sConfigInjected.InjectedRank = ADC_INJECTED_RANK_1;
    sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_15CYCLES;
    sConfigInjected.InjectedOffset = 0;
    sConfigInjected.InjectedClk = ADC_CH_CLOCK_DIV8;
    sConfigInjected.InjectedNbrOfConversion = 1;
    sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
    if (HAL_ADCEx_InjectedConfigChannel(&ADCx_Hdl, &sConfigInjected) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_LoopMode_Channel_setcfg(void)
{
    ADC_LoopConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_5;
    sConfig.Rank    = ADC_LOOP_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk      = ADC_CH_CLOCK_DIV8;
    sConfig.NbrOfConversion = 1;
    sConfig.CapIntv = 0xFFFF;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADCx_Hdl.Instance)
    {
        LOG_I("Regular CH5 AD:%d",HAL_ADC_GetValue(&ADCx_Hdl,ADC_REGULAR_RANK_1));
    }
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADCx_Hdl.Instance)
    {
        LOG_I("Injected CH5 AD:%d",HAL_ADCEx_InjectedGetValue(&ADCx_Hdl,ADC_INJECTED_RANK_1));
    }
}

void HAL_ADCx_LoopConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    uint8_t fif_lvl_num = LOOP_MDOE_FIFO_LVL_NUM_GET(&ADCx_Hdl);
    if(hadc->Instance == ADCx_Hdl.Instance)
    {
        for(uint8_t i=0;i<fif_lvl_num;i++){
            LOG_I("LOOP CH5 AD:%d",HAL_ADCx_LoopGetValue(&ADCx_Hdl));
        }
        loop_mode_num++;
    }
}

int main(void)
{
    uint8_t inj_ch_cfg_flag = 0;
    uint8_t loop_ch_cfg_flag = 0;
    sys_init_none();
    LOG_I("ADC Single Channel Test Start...");
    pinmux_adc_init();
    ADC_Init_Func();
    ADC_RegMode_Channel_setCfg();
	while(1)
	{
        if (adc_test_num < 20)
        {
            HAL_ADC_Start_IT(&ADCx_Hdl);
        }
        else if (adc_test_num < 40)
        {
            if (!inj_ch_cfg_flag)
            {
                inj_ch_cfg_flag = 1;
                HAL_ADC_Stop_IT(&ADCx_Hdl);
                ADC_InjMode_Channel_setCfg();
            }
            HAL_ADCEx_InjectedStart_IT(&ADCx_Hdl);
        }
        else
        {
            if (!loop_ch_cfg_flag)
            {
                loop_ch_cfg_flag = 1;
                HAL_ADCEx_InjectedStop_IT(&ADCx_Hdl);
                ADC_LoopMode_Channel_setcfg();
                HAL_ADCx_LoopStart_IT(&ADCx_Hdl);
            }
        }

        if (!loop_ch_cfg_flag)
        {
            adc_test_num++;
        }
        else
        {
            if (loop_mode_num > 20)
            {
                loop_mode_num = 0;
                HAL_ADCx_LoopStop_IT(&ADCx_Hdl);
                LOG_I("ADC Single Channel Test End!!!");
            }
        }
        DELAY_US(500000);
	};
}

