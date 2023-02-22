#ifndef LS_MSP_SPI_H_
#define LS_MSP_SPI_H_
#include "reg_base_addr.h"
#include "reg_spi_type.h"

/// LSSPI Macro for Register Access
#define SPI2 ((reg_spi_t *)SPI2_BASE_ADDR)

struct __SPI_HandleTypeDef;
void HAL_SPI_MSP_Init(struct __SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_DeInit(struct __SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_Busy_Set(struct __SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_Idle_Set(struct __SPI_HandleTypeDef *inst);

struct __I2S_HandleTypeDef;
void HAL_I2S_MSP_Init(struct __I2S_HandleTypeDef *inst);
void HAL_I2S_MSP_DeInit(struct __I2S_HandleTypeDef *inst);
void HAL_I2S_MSP_Busy_Set(struct __I2S_HandleTypeDef *inst);
void HAL_I2S_MSP_Idle_Set(struct __I2S_HandleTypeDef *inst);

void LL_SPI2_MSP_Init(void);
void LL_SPI2_MSP_DeInit(void);
#endif
