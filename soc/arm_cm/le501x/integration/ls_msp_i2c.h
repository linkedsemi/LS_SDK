#ifndef LS_MSP_I2C_H_
#define LS_MSP_I2C_H_
#include "reg_base_addr.h"
#include "reg_i2c_type.h"


/// LSI2C Macro for Register Access
#ifdef I2C1_BASE_ADDR
#define I2C1 ((reg_i2c_t *)I2C1_BASE_ADDR)
#endif
#ifdef I2C2_BASE_ADDR
#define I2C2 ((reg_i2c_t *)I2C2_BASE_ADDR)
#endif
#ifdef I2C3_BASE_ADDR
#define I2C3 ((reg_i2c_t *)I2C3_BASE_ADDR)
#endif
struct __I2C_HandleTypeDef;
void HAL_I2C_MSP_Init(struct __I2C_HandleTypeDef *inst);
void HAL_I2C_MSP_DeInit(struct __I2C_HandleTypeDef *inst);
void HAL_I2C_MSP_Busy_Set(struct __I2C_HandleTypeDef *inst);
void HAL_I2C_MSP_Idle_Set(struct __I2C_HandleTypeDef *inst);
uint8_t HAL_I2C_TX_DMA_Handshake_Get(struct __I2C_HandleTypeDef *inst);
uint8_t HAL_I2C_RX_DMA_Handshake_Get(struct __I2C_HandleTypeDef *inst);

void LL_I2C1_MSP_Init(void);
void LL_I2C1_MSP_DeInit(void);
void LL_I2C2_MSP_Init(void);
void LL_I2C2_MSP_DeInit(void);

#endif
