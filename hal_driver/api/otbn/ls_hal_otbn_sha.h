#ifndef LS_HAL_OTBN_SHA256_H_
#define LS_HAL_OTBN_SHA256_H_
#include "ls_hal_otbn.h"
#ifdef __cplusplus
extern "C" {
#endif


void HAL_OTBN_SHA256_Init();
void HAL_OTBN_SHA256_Update(uint8_t *msg, uint32_t length);
void HAL_OTBN_SHA256_Final(uint8_t result[0x20]);



#ifdef __cplusplus
}
#endif
#endif