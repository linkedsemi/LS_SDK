#ifndef TRNG_MSP_H_
#define TRNG_MSP_H_
#include "lstrng.h"

void HAL_TRNG_MSP_Init(void);
void HAL_TRNG_MSP_DeInit(void);
void HAL_TRNG_MSP_Busy_Set(void);
void HAL_TRNG_MSP_Idle_Set(void);


#endif
