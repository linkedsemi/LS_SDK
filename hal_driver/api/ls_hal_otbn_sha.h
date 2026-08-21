#ifndef LS_HAL_OTBN_SHA_H_
#define LS_HAL_OTBN_SHA_H_
#include "reg_otbn_type.h"
#include "ls_hal_otbn.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
 * Per-algorithm SHA-256 / SHA-384 / SHA-512 / SM3 interfaces
 *
 * Return-value convention (shared with the algorithm-agnostic
 * wrapper layer below):
 *   HAL_StatusTypeDef  0 == HAL_OK on success, non-zero = execution
 *   error (HAL_ERROR / HAL_TIMEOUT).  No function here returns a
 *   boolean; results are written to the out parameter only.
 * ============================================================ */

#define HMAC_I_PAD 0x36
#define HMAC_O_PAD 0x5C

#define SHA256_RESULT_SIZE          (0x20)
#define SHA384_RESULT_SIZE          (0x30)
#define SHA512_RESULT_SIZE          (0x40)

#define SM3_BLOCK_SIZE              (0x40)
#define SHA256_BLOCK_SIZE           (0x40)
#define SHA384_BLOCK_SIZE           (0x80)
#define SHA512_BLOCK_SIZE           (0x80)

HAL_StatusTypeDef HAL_OTBN_SHA256_Init();
HAL_StatusTypeDef HAL_OTBN_SHA256_Update(uint8_t *msg, uint32_t length);
HAL_StatusTypeDef HAL_OTBN_SHA256_Final(uint8_t result[SHA256_RESULT_SIZE]);
HAL_StatusTypeDef HAL_OTBN_SHA256_HMAC_SetKey(uint8_t *key, uint32_t key_size);
HAL_StatusTypeDef HAL_OTBN_SHA256_HMAC_Update(uint8_t *msg, uint32_t msg_size);
HAL_StatusTypeDef HAL_OTBN_SHA256_HMAC_Final(uint8_t *out);
HAL_StatusTypeDef HAL_OTBN_SHA256_HMAC(uint8_t out[SHA256_RESULT_SIZE], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);
HAL_StatusTypeDef HAL_OTBN_SHA256_HKDF(uint8_t *salt, uint32_t salt_len,
                          uint8_t *ikm, uint32_t ikm_len,
                          uint8_t *info, uint32_t info_len,
                          uint8_t *okm, uint32_t okm_len);

HAL_StatusTypeDef HAL_OTBN_SHA384_Init();
HAL_StatusTypeDef HAL_OTBN_SHA384_Update(uint8_t *msg, uint32_t length);
HAL_StatusTypeDef HAL_OTBN_SHA384_Final(uint8_t result[SHA384_RESULT_SIZE]);
HAL_StatusTypeDef HAL_OTBN_SHA384_HMAC_SetKey(uint8_t *key, uint32_t key_size);
HAL_StatusTypeDef HAL_OTBN_SHA384_HMAC_Update(uint8_t *msg, uint32_t msg_size);
HAL_StatusTypeDef HAL_OTBN_SHA384_HMAC_Final(uint8_t *out);
HAL_StatusTypeDef HAL_OTBN_SHA384_HMAC(uint8_t out[SHA384_RESULT_SIZE], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);
HAL_StatusTypeDef HAL_OTBN_SHA384_HKDF(uint8_t *salt, uint32_t salt_len,
                          uint8_t *ikm, uint32_t ikm_len,
                          uint8_t *info, uint32_t info_len,
                          uint8_t *okm, uint32_t okm_len);

HAL_StatusTypeDef HAL_OTBN_SHA512_Init();
HAL_StatusTypeDef HAL_OTBN_SHA512_Update(uint8_t *msg, uint32_t length);
HAL_StatusTypeDef HAL_OTBN_SHA512_Final(uint8_t result[SHA512_RESULT_SIZE]);
HAL_StatusTypeDef HAL_OTBN_SHA512_HMAC_SetKey(uint8_t *key, uint32_t key_size);
HAL_StatusTypeDef HAL_OTBN_SHA512_HMAC_Update(uint8_t *msg, uint32_t msg_size);
HAL_StatusTypeDef HAL_OTBN_SHA512_HMAC_Final(uint8_t *out);
HAL_StatusTypeDef HAL_OTBN_SHA512_HMAC(uint8_t out[SHA512_RESULT_SIZE], uint8_t *data, uint32_t data_len, uint8_t *key, uint32_t key_len);
HAL_StatusTypeDef HAL_OTBN_SHA512_HKDF(uint8_t *salt, uint32_t salt_len,
                          uint8_t *ikm, uint32_t ikm_len,
                          uint8_t *info, uint32_t info_len,
                          uint8_t *okm, uint32_t okm_len);


HAL_StatusTypeDef HAL_OTBN_SM3_Init();
HAL_StatusTypeDef HAL_OTBN_SM3_Final(uint8_t result[0x20]);
HAL_StatusTypeDef HAL_OTBN_SM3_Update(uint8_t *msg, uint32_t length);

/* ============================================================
 * Algorithm-agnostic HASH / HMAC / HKDF wrapper
 * (dispatch to the per-algorithm interfaces above)
 * ============================================================ */

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


HAL_StatusTypeDef HAL_OTBN_HASH_Init(otbn_hash_algo algo);

HAL_StatusTypeDef HAL_OTBN_HASH_Update(otbn_hash_algo algo, uint8_t *msg, uint32_t msg_size);

HAL_StatusTypeDef HAL_OTBN_HASH_Final(otbn_hash_algo algo, uint8_t *out);

HAL_StatusTypeDef HAL_OTBN_HASH(otbn_hash_algo algo, uint8_t *msg, uint32_t msg_size, uint8_t *out);




HAL_StatusTypeDef HAL_OTBN_HASH_HMAC_SetKey(otbn_hash_hamc_env *hmac, uint8_t *key, uint32_t key_size);

HAL_StatusTypeDef HAL_OTBN_HASH_HMAC_Update(otbn_hash_hamc_env *hmac, uint8_t *msg, uint32_t msg_size);

HAL_StatusTypeDef HAL_OTBN_HASH_HMAC_Final(otbn_hash_hamc_env *hmac, uint8_t *out);

HAL_StatusTypeDef HAL_OTBN_HASH_HMAC(otbn_hash_algo algo, uint8_t *out,
                        uint8_t *key, uint32_t key_size,
                        uint8_t *msg, uint32_t msg_size);




HAL_StatusTypeDef HAL_OTBN_HASH_HKDF_Extract(otbn_hash_algo algo,
                                uint8_t *salt, uint32_t salt_len,
                                uint8_t *ikm, uint32_t ikm_len,
                                uint8_t *prk, uint32_t *prk_length);

HAL_StatusTypeDef HAL_OTBN_HASH_HKDF_Expand(otbn_hash_algo algo,
                               uint8_t *prk, uint32_t prk_len,
                               uint8_t *info, uint32_t info_len,
                               uint8_t *okm, uint32_t okm_len);

HAL_StatusTypeDef HAL_OTBN_HASH_HKDF(otbn_hash_algo algo,
                        uint8_t *salt, uint32_t salt_len,
                        uint8_t *ikm, uint32_t ikm_len,
                        uint8_t *info, uint32_t info_len,
                        uint8_t *okm, uint32_t okm_len);



#ifdef __cplusplus
}
#endif
#endif
