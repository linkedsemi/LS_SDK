#ifndef LS_MSP_CAN_H_
#define LS_MSP_CAN_H_
#include "reg_fdcan_type.h"
#include "reg_sysc_awo.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef BXCAN_BASE_ADDR
#define FDCAN ((reg_fdcan_t *)BXCAN_BASE_ADDR)
// #define SYSC_AWO ((reg_awo_t *)0x4000A228)
#endif

struct __FDCAN_HandleTypeDef;

void HAL_FDCAN_MSP_Init(struct __FDCAN_HandleTypeDef* inst);
void HAL_FDCAN_MSP_DeInit(struct __FDCAN_HandleTypeDef* inst);
void HAL_FDCAN_MSP_Busy_Set(void);
void HAL_FDCAN_MSP_Idle_Set(void);

#ifdef __cplusplus
}
#endif

#endif
