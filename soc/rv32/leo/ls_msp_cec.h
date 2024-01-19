#ifndef LS_MSP_CEC_H_
#define LS_MSP_CEC_H_

#include "reg_base_addr.h"
#include "reg_cec_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CEC_BASE_ADDR
#define CEC ((reg_cec_t *) CEC_BASE_ADDR)
#endif

struct __CEC_HandleTypeDef;
void HAL_CEC_MSP_Init(struct __CEC_HandleTypeDef *inst);

void HAL_CEC_MSP_DeInit(struct __CEC_HandleTypeDef *inst);

#ifdef __cplusplus
}
#endif

#endif

