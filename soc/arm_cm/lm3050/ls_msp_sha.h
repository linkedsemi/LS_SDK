#ifndef LS_MSP_SHA_H_
#define LS_MSP_SHA_H_
#include "reg_sha_type.h"
#include "reg_base_addr.h"

#ifdef LSSHA_BASE_ADDR
#define LSSHA ((reg_sha_t *)LSSHA_BASE_ADDR)
#endif


void HAL_LSSHA_MSP_Init(void);

void HAL_LSSHA_MSP_DeInit(void);

void HAL_LSSHA_MSP_Busy_Set(void);

void HAL_LSSHA_MSP_Idle_Set(void);
#endif
