#ifndef LS_MSP_DMAC_H_
#define LS_MSP_DMAC_H_
#include "reg_dmac_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DMAC1_BASE_ADDR
#define DMAC1 (reg_dmac_t *)DMAC1_BASE_ADDR
#endif

struct __DMA_Controller_HandleTypeDef;
void HAL_DMA_Controller_MSP_Init(struct __DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_DeInit(struct __DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_Busy_Set(struct __DMA_Controller_HandleTypeDef *hdma);
void HAL_DMA_Controller_MSP_Idle_Set(struct __DMA_Controller_HandleTypeDef *hdma);

#ifdef __cplusplus
}
#endif

#endif
