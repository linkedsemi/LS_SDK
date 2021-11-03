#ifndef LSPDM_MSP_H_
#define LSPDM_MSP_H_
#include "lspdm.h"

void HAL_PDM_MSP_Init(PDM_HandleTypeDef *hpdm);
void HAL_PDM_MSP_Busy_Set(PDM_HandleTypeDef *hpdm);
void HAL_PDM_MSP_Idle_Set(PDM_HandleTypeDef *hpdm);
void HAL_PDM_MSP_DeInit(PDM_HandleTypeDef *hpdm);
uint8_t HAL_PDM_CH0_Handshake_Get(PDM_HandleTypeDef *hpdm);
uint8_t HAL_PDM_CH1_Handshake_Get(PDM_HandleTypeDef *hpdm);

#endif
