#ifndef LS_HAL_SHA_H_
#define LS_HAL_SHA_H_
#include "ls_msp_sha.h"
#include <stdbool.h>
#include "HAL_def.h"

#define SHA256_WORDS_NUM 8
#define SHA224_WORDS_NUM 7
#define SM3_WORDS_NUM 8
#define SHA256_BYTES_NUM 0x20
#define SHA224_BYTES_NUM 0x1C
#define SM3_BYTES_NUM 0x20


HAL_StatusTypeDef HAL_LSSHA_Init(void);

HAL_StatusTypeDef HAL_LSSHA_DeInit(void);

HAL_StatusTypeDef HAL_LSSHA_SHA256_Init();

HAL_StatusTypeDef HAL_LSSHA_SHA224_Init();

HAL_StatusTypeDef HAL_LSSHA_SM3_Init();

HAL_StatusTypeDef HAL_LSSHA_Update(const uint8_t *data,uint32_t length);

HAL_StatusTypeDef HAL_LSSHA_Final(uint8_t *digest);

HAL_StatusTypeDef HAL_LSSHA_SHA256(const uint8_t *data, uint32_t length, uint8_t hash_val[SHA256_BYTES_NUM]);

HAL_StatusTypeDef HAL_LSSHA_SHA256_HMAC(uint8_t out[SHA256_BYTES_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);

HAL_StatusTypeDef HAL_LSSHA_SHA224_HMAC(uint8_t out[SHA224_BYTES_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);

HAL_StatusTypeDef HAL_LSSHA_SM3_HMAC(uint8_t out[SM3_BYTES_NUM], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);

bool HAL_LSSHA_SM3_KDF(uint8_t *Z, uint32_t Zlen, uint8_t *out, uint32_t out_len);

void LSSHA_IRQHandler(void);
#endif