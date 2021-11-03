#include "lsadc.h"
#include "ls_ble.h"
#include "cpu.h"
#include "platform.h"
#include "io_config.h"
#include <string.h>
#include <stdlib.h>
#include "lsdmac.h"
#include "log.h"
#include "field_manipulate.h"

static ADC_HandleTypeDef hadc;
uint32_t adc_value = 0;
int16_t tempsensor = 0;

void adc_init(void)
{
	hadc.Instance = LSADC;
    hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode          = ADC_SCAN_DISABLE;
    hadc.Init.NbrOfConversion       = 1;
    hadc.Init.DiscontinuousConvMode = DISABLE;
    hadc.Init.NbrOfDiscConversion   = 1;
    hadc.Init.ContinuousConvMode    = DISABLE; 
    hadc.Init.TrigType              = ADC_REGULAR_SOFTWARE_TRIGT;            /* !<Trig of conversion start done by which event */
	hadc.Init.Vref          		= ADC_VREF_INSIDE;			            /*!< Vref 3 types : ADC_VREF_VCC/ADC_VREF_EXPOWER/ADC_VREF_INSIDE*/
    hadc.Init.AdcDriveType          = BINBUF_DIRECT_DRIVE_ADC;	    /*!< AdcDriveTyp, please refer to the type @ref enum ADC_Drv_TypeDef*/
	hadc.Init.AdcCkDiv              = ADC_CLOCK_DIV32;      

	if (HAL_ADC_Init(&hadc) != HAL_OK)
	{
	}

    ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel 	 = ADC_CHANNEL_TEMPSENSOR;//ADC_CHANNEL_4;
	sConfig.Rank         = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
	}
}

uint32_t Get_ADC_Value()
{	
    if (HAL_ADC_Start(&hadc) != HAL_OK)
    {
    }
	
    HAL_ADC_PollForConversion(&hadc,5000);  /*!< timeout 5s*/

	return HAL_ADC_GetValue(&hadc);  // Return adc value
}

int main(void)
{
   sys_init_none();
   adc_init();
	
	while(1)
	{
        adc_value = (hadc.Init.AdcDriveType == INRES_ONETHIRD_EINBUF_DRIVE_ADC)?(Get_ADC_Value()*3):Get_ADC_Value();
        tempsensor = GET_ADC_TEMPSENSOR_VREF_INSIDE(adc_value);
        LOG_I("adc val:%d", adc_value);
        LOG_I("tempsensor val:%d", tempsensor);
	};  
}
