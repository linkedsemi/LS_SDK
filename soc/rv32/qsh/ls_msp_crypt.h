#ifndef LS_MSP_CRYPT_H_
#define LS_MSP_CRYPT_H_
#include "reg_base_addr.h"
#include "reg_crypt_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SEC_CALC_AES_ADDR
#define LSCRYPT ((reg_crypt_t *)SEC_CALC_AES_ADDR)
#endif

void HAL_LSCRYPT_MSP_Init(void);
void HAL_LSCRYPT_MSP_Busy_Set(void);
void HAL_LSCRYPT_MSP_Idle_Set(void);
void HAL_LSCRYPT_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
