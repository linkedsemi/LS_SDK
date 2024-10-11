#ifndef LS_MSP_CRYPT_H_
#define LS_MSP_CRYPT_H_
#include "reg_base_addr.h"
#include "reg_crypt_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef QSH_PER_CRYPT_ADDR
/// LSCRYPT Macro for Register Access
#define LSCRYPT ((reg_crypt_t *)QSH_PER_CRYPT_ADDR)
#endif

void HAL_LSCRYPT_MSP_Init(void);
void HAL_LSCRYPT_MSP_Busy_Set(void);
void HAL_LSCRYPT_MSP_Idle_Set(void);
void HAL_LSCRYPT_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif