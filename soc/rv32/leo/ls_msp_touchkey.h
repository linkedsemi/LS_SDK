#ifndef LS_MSP_TOUCHKEY_H_
#define LS_MSP_TOUCHKEY_H_
#include "reg_base_addr.h"
#include "reg_touchkey_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef TOUCHKEY_BASE_ADDR
/// LSTOUCHKEY Macro for Register Access
#define LSTOUCHKEY ((reg_touchkey_t *)TOUCHKEY_BASE_ADDR)
#endif

void HAL_LSTOUCHKEY_MSP_Init(void);

void HAL_LSTOUCHKEY_MSP_DeInit(void);

void HAL_LSTOUCHKEY_MSP_Busy_Set(void);

void HAL_LSTOUCHKEY_MSP_Idle_Set(void);

#ifdef __cplusplus
}
#endif

#endif