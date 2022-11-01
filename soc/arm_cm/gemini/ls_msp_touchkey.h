#ifndef LS_MSP_TOUCHKEY_H_
#define LS_MSP_TOUCHKEY_H_
#include "reg_base_addr.h"
#include "reg_touchkey_type.h"

#ifdef LSTOUCHKEY_BASE_ADDR
/// LSTOUCHKEY Macro for Register Access
#define LSTOUCHKEY ((reg_touchkey_t *)LSTOUCHKEY_BASE_ADDR)
#endif

void HAL_LSTOUCHKEY_MSP_Init(void);
void HAL_LSTOUCHKEY_MSP_DeInit(void);

#endif