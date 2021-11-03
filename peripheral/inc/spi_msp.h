#ifndef SPI_MSP_H_
#define SPI_MSP_H_

#include "lsspi.h"


void HAL_SPI_MSP_Init(SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_DeInit(SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_Busy_Set(SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_Idle_Set(SPI_HandleTypeDef *inst);



#endif
