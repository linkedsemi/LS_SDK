#ifndef LS_MSP_ECC_H_
#define LS_MSP_ECC_H_
#include "reg_base_addr.h"
#include "reg_ecc_type.h"

#define LSECC ((reg_ecc_t *)LSECC_BASE_ADDR)

void HAL_LSECC_MSP_Init(void);

void HAL_LSECC_MSP_DeInit(void);

void HAL_LSECC_Busy_Set(void);

void HAL_LSECC_Idle_Set(void);

void HAL_LSECC_MSP_INT_ENABLE(void);

void HAL_LSECC_MSP_INT_DISABLE(void);

void HAL_LSECC_MSP_INT_CLRPENDING(void);

#endif
