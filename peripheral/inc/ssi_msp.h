#ifndef SSI_MSP_H_
#define SSI_MSP_H_
#include "lsssi.h"

void HAL_SSI_MSP_Init(SSI_HandleTypeDef *hssi);
void HAL_SSI_MSP_DeInit(SSI_HandleTypeDef *hssi);
void HAL_SSI_MSP_Busy_Set(SSI_HandleTypeDef *hssi);
void HAL_SSI_MSP_Idle_Set(SSI_HandleTypeDef *hssi);
uint8_t HAL_SSI_TX_DMA_Handshake_Get(SSI_HandleTypeDef *hssi);
uint8_t HAL_SSI_RX_DMA_Handshake_Get(SSI_HandleTypeDef *hssi);
#endif
