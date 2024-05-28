#ifndef LS_HAL_ECC_H_
#define LS_HAL_ECC_H_
#include <stdbool.h>
#include "ls_msp_ecc.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ecc_mont_mod
{
    const uint32_t mod[8];
    const uint32_t h[8];
    const uint32_t omega;
};

struct ecc_curve_param
{
    struct ecc_mont_mod p,n;
    const uint32_t neg_a[8];
    const uint32_t G[16];
};

extern const struct ecc_curve_param secp256r1_param;

extern const struct ecc_curve_param secp256k1_param;

extern const struct ecc_curve_param sm2_param;

extern const struct ecc_curve_param bp_p256_r1_param;

extern const struct ecc_curve_param bn_p256_param;

void HAL_LSECC_Init(void);

void HAL_LSECC_DeInit(void);

void HAL_LSECC_PointAdd(const struct ecc_curve_param *curve,const uint8_t *const point_a[2],const uint8_t *const point_b[2],uint8_t *const result[2]);

void HAL_LSECC_PointAdd_IT(const struct ecc_curve_param *curve,const uint8_t *const point_a[2],const uint8_t *const point_b[2],uint8_t *const result[2]);

void HAL_LSECC_PointAdd_Complete_Callback(void);

void HAL_LSECC_PointMult(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *const public_key[2],uint8_t *const result[2]);

void HAL_LSECC_PointMult_IT(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *const public_key[2],uint8_t *const result[2]);

void HAL_LSECC_PointMult_Complete_Callback(void);

void HAL_LSECC_Sign(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *message_hash,uint32_t hash_size,const uint8_t *k,uint8_t *signature);

void HAL_LSECC_Sign_IT(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *message_hash,uint32_t hash_size,const uint8_t *k,uint8_t *signature);

void HAL_LSECC_Sign_Complete_Callback(void);

bool HAL_LSECC_Verify(const struct ecc_curve_param *curve,const uint8_t *const public_key[2],const uint8_t *message_hash,uint32_t hash_size,const uint8_t *signature);

void HAL_LSECC_Verify_IT(const struct ecc_curve_param *curve,const uint8_t *const public_key[2],const uint8_t *message_hash,uint32_t hash_size,const uint8_t *signature);

void HAL_LSECC_Verify_Complete_Callback(bool succeed);

void LSECC_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif
