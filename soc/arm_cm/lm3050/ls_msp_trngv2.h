#ifndef LS_MSP_TRNGV2_H_
#define LS_MSP_TRNGV2_H_
#include "reg_base_addr.h"
#include "reg_trngv2_type.h"

#ifdef LSTRNG_BASE_ADDR
#define LSTRNG ((reg_trng_t *)LSTRNG_BASE_ADDR) /*!< LSTRNG Macro for Register Access*/
#endif

void HAL_TRNG_MSP_Init(void);
void HAL_TRNG_MSP_DeInit(void);
void HAL_TRNG_MSP_Busy_Set(void);
void HAL_TRNG_MSP_Idle_Set(void);


#endif
