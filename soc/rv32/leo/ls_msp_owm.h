#ifndef LS_MSP_OWM_H_
#define LS_MSP_OWM_H_

#include "reg_base_addr.h"
#include "reg_owm_type.h"

#ifdef __cplusplus
extern "C" {
#endif

// LSOWM Macro for Register Access
#ifdef LSOWM_BASE_ADDR
#define LSOWM ((reg_owm_t *) LSOWM_BASE_ADDR)
#endif

struct __OWM_HandleTypeDef;
void HAL_LSOWM_MSP_Init(struct __OWM_HandleTypeDef* inst);
void HAL_LSOWM_MSP_DeInit(struct __OWM_HandleTypeDef* inst);

#ifdef __cplusplus
}
#endif

#endif