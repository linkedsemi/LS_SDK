#ifndef LS_MSP_DWTRNG_H_
#define LS_MSP_DWTRNG_H_
#include "reg_base_addr.h"
#include "reg_dwtrng_type.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef QSH_PER_DWTRNG_ADDR
#define DWTRNG ((reg_dwtrng_t *)QSH_PER_DWTRNG_ADDR)
#endif

void HAL_DWTRNG_MSP_Init(void);

void HAL_DWTRNG_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
