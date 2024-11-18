#ifndef LS_MSP_SHA_H_
#define LS_MSP_SHA_H_
#include "reg_sha_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef QSH_APB_SHA_ADDR
#define LSSHA ((reg_sha_t *)QSH_APB_SHA_ADDR)
#endif


void HAL_LSSHA_MSP_Init(void);

void HAL_LSSHA_MSP_DeInit(void);

void HAL_LSSHA_MSP_Busy_Set(void);

void HAL_LSSHA_MSP_Idle_Set(void);

#ifdef __cplusplus
}
#endif

#endif
