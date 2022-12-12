#ifndef LS_MSP_CAN_H_
#define LS_MSP_CAN_H_
#include "reg_can_type.h"
#include "reg_base_addr.h"

#define BXCAN ((reg_bxcan_t *)BXCAN_BASE_ADDR)

struct __CAN_HandleTypeDef;
void HAL_BXCAN_MSP_Init(struct __CAN_HandleTypeDef* inst);
void HAL_BXCAN_MSP_DeInit(struct __CAN_HandleTypeDef* inst);

void HAL_BXCAN_MSP_Busy_Set(void);
void HAL_BXCAN_MSP_Idle_Set(void);

#endif
