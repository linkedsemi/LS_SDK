#ifndef LS_HAL_OTBN_SHA_H_
#define LS_HAL_OTBN_SHA_H_
#include "reg_otbn_type.h"
#include "ls_hal_otbn.h"
#ifdef __cplusplus
extern "C" {
#endif

#define HMAC_I_PAD 0x36
#define HMAC_O_PAD 0x5C

#define SHA256_RESULT_SIZE          (0x20)
#define SHA384_RESULT_SIZE          (0x30)
#define SHA512_RESULT_SIZE          (0x40)

void HAL_OTBN_SHA256_Init();
void HAL_OTBN_SHA256_Update(uint8_t *msg, uint32_t length);
void HAL_OTBN_SHA256_Final(uint8_t result[SHA256_RESULT_SIZE]);
void HAL_OTBN_SHA256_HMAC(uint8_t out[SHA256_RESULT_SIZE], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);
bool HAL_OTBN_SHA256_HKDF(uint8_t *salt, uint32_t salt_len,
                          uint8_t *ikm, uint32_t ikm_len,
                          uint8_t *info, uint32_t info_len,
                          uint8_t *okm, uint32_t okm_len);

void HAL_OTBN_SHA384_Init();
void HAL_OTBN_SHA384_Update(uint8_t *msg, uint32_t length);
void HAL_OTBN_SHA384_Final(uint8_t result[SHA384_RESULT_SIZE]);
void HAL_OTBN_SHA384_HMAC(uint8_t out[SHA384_RESULT_SIZE], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);
bool HAL_OTBN_SHA384_HKDF(uint8_t *salt, uint32_t salt_len,
                          uint8_t *ikm, uint32_t ikm_len,
                          uint8_t *info, uint32_t info_len,
                          uint8_t *okm, uint32_t okm_len);

void HAL_OTBN_SHA512_Init();
void HAL_OTBN_SHA512_Update(uint8_t *msg, uint32_t length);
void HAL_OTBN_SHA512_Final(uint8_t result[SHA512_RESULT_SIZE]);
void HAL_OTBN_SHA512_HMAC(uint8_t out[SHA512_RESULT_SIZE], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);
bool HAL_OTBN_SHA512_HKDF(uint8_t *salt, uint32_t salt_len,
                          uint8_t *ikm, uint32_t ikm_len,
                          uint8_t *info, uint32_t info_len,
                          uint8_t *okm, uint32_t okm_len);


#ifdef __cplusplus
}
#endif
#endif