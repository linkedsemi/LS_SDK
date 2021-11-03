#ifndef DMAC_MSP_H_
#define DMAC_MSP_H_
#include "lsdmac.h"


void HAL_DMA_Controller_MSP_Init(DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_DeInit(DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_Busy_Set(DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_Idle_Set(DMA_Controller_HandleTypeDef *hdma);

#endif
