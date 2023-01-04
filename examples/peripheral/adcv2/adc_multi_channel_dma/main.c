#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "ls_hal_adcv2.h"
#include "ls_hal_dmacv2.h"
#include "log.h"

DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);
static ADC_HandleTypeDef ADCx_Hdl;

#define ADC_CHANNLE_NUM (4)
DMA_RAM_ATTR uint16_t Loop_adc_value[ADC_CHANNLE_NUM];

static void pinmux_adc_init(void)
{
    pinmux_adc1_in4_init();// PA00
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
    DMA_CONTROLLER_INIT(dmac1_inst);
    ADCx_Hdl.Env.DMA.DMA_Channel        = 0;
    ADCx_Hdl.DMAC_Instance              = &dmac1_inst;

    ADCx_Hdl.Instance                   = LSADC1;
    ADCx_Hdl.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    ADCx_Hdl.Init.ContinuousConvMode    = DISABLE;
    ADCx_Hdl.Init.NbrOfConversion       = 0;
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

void ADC_LoopMode_Channel_setcfg(void)
{
    ADC_LoopConfTypeDef sConfig = {0};
    sConfig.Channel         = ADC_CHANNEL_4;
    sConfig.Rank            = ADC_LOOP_RANK_1;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk         = ADC_CH_CLOCK_DIV8;
    sConfig.NbrOfConversion = 4;
    sConfig.CapIntv = 0xFFFF;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }

    sConfig.Channel         = ADC_CHANNEL_5;
    sConfig.Rank            = ADC_LOOP_RANK_2;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk         = ADC_CH_CLOCK_DIV8;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }

    sConfig.Channel         = ADC_CHANNEL_6;
    sConfig.Rank            = ADC_LOOP_RANK_3;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk         = ADC_CH_CLOCK_DIV8;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }

    sConfig.Channel         = ADC_CHANNEL_7;
    sConfig.Rank            = ADC_LOOP_RANK_4;
    sConfig.SamplingTime    = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk         = ADC_CH_CLOCK_DIV8;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if(hadc->Instance == ADCx_Hdl.Instance)
    {
        for(uint8_t i=0;i<ADC_CHANNLE_NUM;i++){
            LOG_I("LOOPMode RANK%d:%d",i%ADC_CHANNLE_NUM,Loop_adc_value[i]);
        }
    }
}

int main(void)
{
    sys_init_none();
    LOG_I("ADC Test Start...");
    pinmux_adc_init();
    ADC_Init_Func();
    ADC_LoopMode_Channel_setcfg();
    
    while (1)
    {
        HAL_ADC_LoopChannel_Start_DMA(&ADCx_Hdl, Loop_adc_value, sizeof(Loop_adc_value), HAL_ADC_ConvCpltCallback);
        DELAY_US(500000);
    };
}

