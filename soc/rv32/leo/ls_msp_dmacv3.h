#ifndef LS_MSP_DMACV3_H_
#define LS_MSP_DMACV3_H_
#define DMAC_CHANNEL_NUM 6
#include "reg_dmacv3_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DMAC1_BASE_ADDR
#define DMAC1 (reg_dmac_t *)DMAC1_BASE_ADDR
#endif
#ifdef DMAC2_BASE_ADDR
#define DMAC2 (reg_dmac_t *)DMAC2_BASE_ADDR
#endif

struct __DMA_Controller_HandleTypeDef;
void HAL_DMA_Controller_MSP_Init(struct __DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_DeInit(struct __DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_Busy_Set(struct __DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_Idle_Set(struct __DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Channel_Handshake_Set(struct __DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,uint8_t handshake);

#ifdef __cplusplus
}
#endif

#endif