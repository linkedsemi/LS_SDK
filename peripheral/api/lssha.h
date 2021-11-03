#ifndef LSSHA_H_
#define LSSHA_H_
#include "reg_sha_type.h"
#include "reg_base_addr.h"
#include "HAL_def.h"
#ifdef LSSHA_BASE_ADDR
#define LSSHA ((reg_sha_t *)LSSHA_BASE_ADDR)
#endif
#define SHA256_WORDS_NUM 8

HAL_StatusTypeDef HAL_LSSHA_Init(void);

HAL_StatusTypeDef HAL_LSSHA_DeInit(void);

HAL_StatusTypeDef HAL_LSSHA_SHA256(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM]);

HAL_StatusTypeDef HAL_LSSHA_SHA256_IT(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM]);

void HAL_LSSHA_SHA256_Complete_Callback(void);

void LSSHA_IRQHandler(void);
#endif
