#ifndef LS_HAL_SHA_H_
#define LS_HAL_SHA_H_
#include "ls_msp_sha.h"
#include <stdbool.h>
#include "HAL_def.h"

#define SHA256_WORDS_NUM 8
#define SHA224_WORDS_NUM 7
#define SM3_WORDS_NUM 8


HAL_StatusTypeDef HAL_LSSHA_Init(void);

HAL_StatusTypeDef HAL_LSSHA_DeInit(void);

HAL_StatusTypeDef HAL_LSSHA_SHA256_Init();

HAL_StatusTypeDef HAL_LSSHA_SHA224_Init();

HAL_StatusTypeDef HAL_LSSHA_SM3_Init();

HAL_StatusTypeDef HAL_LSSHA_Update(const uint8_t *data,uint32_t length);

HAL_StatusTypeDef HAL_LSSHA_Final(uint8_t *digest);

HAL_StatusTypeDef HAL_LSSHA_SHA256(const uint8_t *data, uint32_t length, uint32_t hash_val[SHA256_WORDS_NUM]);

HAL_StatusTypeDef HAL_HMAC_SHA256(uint32_t out[SHA256_WORDS_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);

HAL_StatusTypeDef HAL_HMAC_SHA224(uint32_t out[SHA224_WORDS_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);

bool HAL_KDF_SM3(uint8_t *Z, uint32_t Zlen, uint8_t *out, uint32_t out_len);

void LSSHA_IRQHandler(void);
#endif