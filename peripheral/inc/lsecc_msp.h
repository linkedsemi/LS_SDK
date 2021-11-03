#ifndef LSECC_MSP_H_
#define LSECC_MSP_H_

void HAL_LSECC_MSP_Init(void);

void HAL_LSECC_MSP_DeInit(void);

void HAL_LSECC_Busy_Set(void);

void HAL_LSECC_Idle_Set(void);

void HAL_LSECC_MSP_INT_ENABLE(void);

void HAL_LSECC_MSP_INT_DISABLE(void);

void HAL_LSECC_MSP_INT_CLRPENDING(void);

#endif
