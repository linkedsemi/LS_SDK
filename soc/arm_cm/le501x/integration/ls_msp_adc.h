#ifndef LS_MSP_ADC_H_
#define LS_MSP_ADC_H_
#include "reg_base_addr.h"
#include "reg_adc_type.h" 

/// LSADC Macro for Register Access
#ifdef LSADC_BASE_ADDR
#define LSADC ((reg_adc_t *)LSADC_BASE_ADDR)
#endif
#ifdef LSADC2_BASE_ADDR
#define LSADC2 ((reg_adc_t *)LSADC2_BASE_ADDR)
#endif

struct __ADC_HandleTypeDef;
void HAL_ADC_MSP_Init(struct __ADC_HandleTypeDef *inst);
void HAL_ADC_MSP_DeInit(struct __ADC_HandleTypeDef *inst);
void HAL_ADC_MSP_Busy_Set(struct __ADC_HandleTypeDef *inst);
void HAL_ADC_MSP_Idle_Set(struct __ADC_HandleTypeDef *inst);

void adc_channel_vbat_enable(void);
void adc_channel_vbat_disable(void);

void adc_channel_tempsensor_enable(void);
void adc_channel_tempsensor_disable(void);

#endif
