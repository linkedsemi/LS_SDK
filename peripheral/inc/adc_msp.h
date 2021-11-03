#ifndef ADC_MSP_H_
#define ADC_MSP_H_

#include "lsadc.h"

void HAL_ADC_MSP_Init(ADC_HandleTypeDef *inst);
void HAL_ADC_MSP_DeInit(ADC_HandleTypeDef *inst);
void HAL_ADC_MSP_Busy_Set(ADC_HandleTypeDef *inst);
void HAL_ADC_MSP_Idle_Set(ADC_HandleTypeDef *inst);

void adc_channel_vbat_enable(void);
void adc_channel_vbat_disable(void);

void adc_channel_tempsensor_enable(void);
void adc_channel_tempsensor_disable(void);

#endif
