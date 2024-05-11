#ifndef LS_MSP_TRNGV2_H_
#define LS_MSP_TRNGV2_H_
#include "reg_base_addr.h"
#include "reg_trngv2_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef TRNG_BASE_ADDR
#define LSTRNG ((reg_trng_t *)TRNG_BASE_ADDR) /*!< LSTRNG Macro for Register Access*/
#endif

#define RNGV2_DLY_SEL_VAL (0x1000)

void HAL_TRNG_MSP_Init(void);

void HAL_TRNG_MSP_DeInit(void);

void HAL_TRNG_MSP_Busy_Set(void);

void HAL_TRNG_MSP_Idle_Set(void);

#ifdef __cplusplus
}
#endif

#endif
