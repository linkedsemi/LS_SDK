#ifndef LS_MSP_SPIS_H_
#define LS_MSP_SPIS_H_

#include "reg_base_addr.h"
#include "reg_spis_type.h"

#ifdef __cplusplus
extern "C" {
#endif

// LSSPIS Macro for Register Access
#ifdef LSSPIS_BASE_ADDR
#define LSSPIS ((reg_spis_t *) LSSPIS_BASE_ADDR)
#endif

struct __SPIS_HandleTypeDef;
void HAL_LSSPIS_MSP_Init(struct  __SPIS_HandleTypeDef* inst);
void HAL_LSSPIS_MSP_DeInit(struct  __SPIS_HandleTypeDef* inst);
uint8_t HAL_SPIS_TX_DMA_Handshake_Get(struct __SPIS_HandleTypeDef *spis);
uint8_t HAL_SPIS_RX_DMA_Handshake_Get(struct __SPIS_HandleTypeDef *spis);

#ifdef __cplusplus
}
#endif

#endif