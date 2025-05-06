#ifndef LS_MSP_SHA512_H_
#define LS_MSP_SHA512_H_
#include "reg_sha512_type.h"
#include "reg_base_addr.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef SEC_CALC_SHA512_ADDR
#define SHA512 ((reg_sha512_t *)SEC_CALC_SHA512_ADDR)
#endif

void HAL_SHA512_MSP_Init(void);

void HAL_SHA512_MSP_DeInit(void);

uint8_t HAL_SHA512_DMA_Handshake_Get(void);

#ifdef __cplusplus
}
#endif

#endif
