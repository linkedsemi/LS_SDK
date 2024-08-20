#ifndef LS_MSP_SM4_H_
#define LS_MSP_SM4_H_
#include "reg_base_addr.h"
#include "reg_sm4_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BMC_PER_SM4_ADDR
#define LSSM4 ((reg_sm4_t *)BMC_PER_SM4_ADDR)
#endif

void HAL_LSSM4_MSP_Init(void);
void HAL_LSSM4_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif