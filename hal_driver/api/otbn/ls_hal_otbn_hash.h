#ifndef LS_HAL_OTBN_HASH_H_
#define LS_HAL_OTBN_HASH_H_
#include "ls_hal_otbn.h"
#ifdef __cplusplus
extern "C" {
#endif

#define HMAC_I_PAD 0x36
#define HMAC_O_PAD 0x5C

#define OTBN_HASH_BLOCK_SIZE_SHA256 (0x40)
#define OTBN_HASH_BLOCK_SIZE_SHA384 (0x80)
#define OTBN_HASH_BLOCK_SIZE_SHA512 (0x80)
#define OTBN_HASH_BLOCK_MAXSIZE     (0x80)

#define OTBN_HASH_RESULT_SIZE_SHA256 (0x20)
#define OTBN_HASH_RESULT_SIZE_SHA384 (0x30)
#define OTBN_HASH_RESULT_SIZE_SHA512 (0x40)
#define OTBN_HASH_RESULT_MAXSIZE     (0x40)

typedef enum 
{
    OTBN_HASH_ALGO_SHA256 = 0x1,
    OTBN_HASH_ALGO_SHA384 = 0x2,
    OTBN_HASH_ALGO_SHA512 = 0x4,
} otbn_hash_algo;

typedef struct 
{
    uint8_t kx[OTBN_HASH_BLOCK_MAXSIZE];
    uint8_t kh[OTBN_HASH_RESULT_MAXSIZE];
    uint8_t *key;
    uint32_t key_size;
    uint32_t block_size;
    otbn_hash_algo hash_algo;
} otbn_hash_hamc_env;


bool HAL_OTBN_HASH_Init(otbn_hash_algo algo);

bool HAL_OTBN_HASH_Update(otbn_hash_algo algo, uint8_t *msg, uint32_t msg_size);

bool HAL_OTBN_HASH_Final(otbn_hash_algo algo, uint8_t *out);

void HAL_OTBN_HASH(otbn_hash_algo algo, uint8_t *msg, uint32_t msg_size, uint8_t *out);





void HAL_OTBN_HASH_HMAC_SetKey(otbn_hash_hamc_env *hmac, uint8_t *key, uint32_t key_size);

void HAL_OTBN_HASH_HMAC_Update(otbn_hash_hamc_env *hmac, uint8_t *msg, uint32_t msg_size);

void HAL_OTBN_HASH_HMAC_Final(otbn_hash_hamc_env *hmac, uint8_t *out);

void HAL_OTBN_HASH_HMAC(otbn_hash_algo algo, uint8_t *out,
                        uint8_t *key, uint32_t key_size,
                        uint8_t *msg, uint32_t msg_size);




void HAL_OTBN_HASH_HKDF_Extract(otbn_hash_algo algo,
                                uint8_t *salt, uint32_t salt_len,
                                uint8_t *ikm, uint32_t ikm_len,
                                uint8_t *prk, uint32_t *prk_length);

bool HAL_OTBN_HASH_HKDF_Expand(otbn_hash_algo algo,
                               uint8_t *prk, uint32_t prk_len,
                               uint8_t *info, uint32_t info_len,
                               uint8_t *okm, uint32_t okm_len);

bool HAL_OTBN_HASH_HKDF(otbn_hash_algo algo,
                        uint8_t *salt, uint32_t salt_len,
                        uint8_t *ikm, uint32_t ikm_len,
                        uint8_t *info, uint32_t info_len,
                        uint8_t *okm, uint32_t okm_len);



#ifdef __cplusplus
}
#endif
#endif