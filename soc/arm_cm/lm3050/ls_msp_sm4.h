#ifndef LS_MSP_SM4_H_
#define LS_MSP_SM4_H_
#include "reg_base_addr.h"
#include "reg_sm4_type.h"

#ifdef LSSM4_BASE_ADDR
/// LSSM4 Macro for Register Access
#define LSSM4 ((reg_sm4_t *)LSSM4_BASE_ADDR)
#endif

void HAL_LSSM4_MSP_Init(void);
void HAL_LSSM4_MSP_DeInit(void);

#endif