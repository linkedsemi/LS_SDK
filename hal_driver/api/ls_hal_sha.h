#ifndef LS_HAL_SHA_H_
#define LS_HAL_SHA_H_
#include "ls_msp_sha.h"
#include "HAL_def.h"

#define SHA256_WORDS_NUM 8
#define SHA224_WORDS_NUM 7
#define SM3_WORDS_NUM 8


HAL_StatusTypeDef HAL_LSSHA_Init(void);

HAL_StatusTypeDef HAL_LSSHA_DeInit(void);

HAL_StatusTypeDef HAL_LSSHA_SHA256(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM]);

HAL_StatusTypeDef HAL_LSSHA_SHA224(const uint8_t *data,uint32_t length,uint32_t sha224[SHA224_WORDS_NUM]);

HAL_StatusTypeDef HAL_LSSHA_SM3(const uint8_t *data,uint32_t length,uint32_t sm3[SM3_WORDS_NUM]);

HAL_StatusTypeDef HAL_LSSHA_SHA256_IT(const uint8_t *data,uint32_t length,uint32_t sha256[SHA256_WORDS_NUM]);

HAL_StatusTypeDef HAL_LSSHA_SHA224_IT(const uint8_t *data,uint32_t length,uint32_t sha224[SHA224_WORDS_NUM]);

HAL_StatusTypeDef HAL_LSSHA_SM3_IT(const uint8_t *data,uint32_t length,uint32_t sm3[SM3_WORDS_NUM]);

void HAL_LSSHA_SHA256_Complete_Callback(void);

void HAL_LSSHA_SHA224_Complete_Callback(void);

void HAL_LSSHA_SM3_Complete_Callback(void);

void LSSHA_IRQHandler(void);
#endif