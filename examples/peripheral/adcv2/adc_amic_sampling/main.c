#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "ls_hal_adcv2.h"
#include "log.h"

static ADC_HandleTypeDef ADCx_Hdl;
void pinmux_amic_init(void);
void Error_Handler(void)
{
    while(1);
}   

void ADC_Init_Func(void)
{
	pinmux_amic_init();
    ADCx_Hdl.Instance                   = LSADC2;           //Select adc1 here
    ADCx_Hdl.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    ADCx_Hdl.Init.ContinuousConvMode    = DISABLE;
    ADCx_Hdl.Init.NbrOfConversion       = 1;
    ADCx_Hdl.Init.DiscontinuousConvMode = DISABLE;
    ADCx_Hdl.Init.NbrOfDiscConversion   = 0; 
    ADCx_Hdl.Init.TrigType              = ADC_SOFTWARE_TRIGT;
    ADCx_Hdl.Init.Vref                  = ADC_VREF_INSIDE;     //Select the internal reference voltage
    ADCx_Hdl.Init.AdcDriveType          = INRES_ONETHIRD_EINBUF_DRIVE_ADC; 
    ADCx_Hdl.Init.AdcCkDiv              = 256;         

    if (HAL_ADC_Init(&ADCx_Hdl) != HAL_OK)
    {
        Error_Handler();
    }
}

void ADC_LoopMode_Channel_setcfg(void)
{
    ADC_LoopConfTypeDef sConfig = {0};
    sConfig.Channel = ADC2_CHANNEL_AMIC;
    sConfig.Rank    = ADC_LOOP_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    sConfig.LoopClk      = ADC_CH_CLOCK_DIV1;
    sConfig.NbrOfConversion = 1;
    sConfig.CapIntv = 0xffff;
    if(HAL_ADC_LoopConfigChannel(&ADCx_Hdl,&sConfig)!= HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_ADCx_LoopConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    uint8_t fif_lvl_num = LOOP_MDOE_FIFO_LVL_NUM_GET(&ADCx_Hdl);
    if(hadc->Instance == ADCx_Hdl.Instance)
    {
        for(uint8_t i=0;i<fif_lvl_num;i++){
            LOG_I("LOOP CH9 AD:%d",HAL_ADCx_LoopGetValue(&ADCx_Hdl));
        }
    }
}

int main(void)
{
	sys_init_none();
	ADC_Init_Func();
	ADC_LoopMode_Channel_setcfg();
	HAL_ADCx_LoopStart_IT(&ADCx_Hdl);
	while(1)
	{
        
    }
}