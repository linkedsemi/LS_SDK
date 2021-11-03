#ifndef LSTIMER_MSP_H_
#define LSTIMER_MSP_H_
#include "lstimer.h"

void HAL_TIM_MSP_Init(TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_DeInit(TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_Busy_Set(TIM_HandleTypeDef *inst);
void HAL_TIM_MSP_Idle_Set(TIM_HandleTypeDef *inst);

#endif
