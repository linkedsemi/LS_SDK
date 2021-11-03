#ifndef I2C_MSP_H_
#define I2C_MSP_H_
#include "lsi2c.h"

void HAL_I2C_MSP_Init(I2C_HandleTypeDef *inst);
void HAL_I2C_MSP_DeInit(I2C_HandleTypeDef *inst);
void HAL_I2C_MSP_Busy_Set(I2C_HandleTypeDef *inst);
void HAL_I2C_MSP_Idle_Set(I2C_HandleTypeDef *inst);
uint8_t HAL_I2C_TX_DMA_Handshake_Get(I2C_HandleTypeDef *inst);
uint8_t HAL_I2C_RX_DMA_Handshake_Get(I2C_HandleTypeDef *inst);

#endif
