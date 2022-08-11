#ifndef LS_MSP_SPI_H_
#define LS_MSP_SPI_H_
#include "reg_base_addr.h"
#include "reg_spi_type.h"

/// LSSPI Macro for Register Access
#ifdef SPI2_BASE_ADDR
#define SPI2 ((reg_spi_t *)SPI2_BASE_ADDR) 
#endif
#ifdef SPI3_BASE_ADDR
#define SPI3 ((reg_spi_t *)SPI3_BASE_ADDR)
#endif

struct __SPI_HandleTypeDef;
void HAL_SPI_MSP_Init(struct __SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_DeInit(struct __SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_Busy_Set(struct __SPI_HandleTypeDef *inst);
void HAL_SPI_MSP_Idle_Set(struct __SPI_HandleTypeDef *inst);

void LL_SPI2_MSP_Init(void);
void LL_SPI2_MSP_DeInit(void);
void LL_SPI3_MSP_Init(void);
void LL_SPI3_MSP_DeInit(void);
#endif
