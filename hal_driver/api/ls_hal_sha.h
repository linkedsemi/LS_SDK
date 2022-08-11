#ifndef LS_HAL_SHA_H_
#define LS_HAL_SHA_H_
#include "ls_msp_sha.h"
#include "HAL_def.h"

#define SHA256_WORDS_NUM 8

HAL_StatusTypeDef HAL_LSSHA_Init(void);

HAL_StatusTypeDef HAL_LSSHA_DeInit(void);

HAL_StatusTypeDef HAL_LSSHA_SHA256(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM]);

HAL_StatusTypeDef HAL_LSSHA_SHA256_IT(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM]);

void HAL_LSSHA_SHA256_Complete_Callback(void);

void LSSHA_IRQHandler(void);
#endif
