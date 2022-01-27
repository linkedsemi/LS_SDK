#ifndef LSECC_H_
#define LSECC_H_
#include "reg_base_addr.h"
#include "reg_lsecc_type.h"

#define LSECC ((reg_ecc_t *)LSECC_BASE_ADDR)

struct ecc_curve_param
{
    const uint32_t p[8];
    const uint32_t neg_a[8];
    const uint32_t h[8];
    const uint32_t omega;
};

extern const struct ecc_curve_param secp256r1_param;

extern const struct ecc_curve_param secp256k1_param;

extern const struct ecc_curve_param sm2_param;

void HAL_LSECC_Init(void);

void HAL_LSECC_DeInit(void);

void HAL_LSECC_PointMult(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *public_key[2],uint8_t *result[2]);

void HAL_LSECC_PointMult_IT(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *public_key[2],uint8_t *result[2]);

void HAL_LSECC_PointMult_Complete_Callback(void);

void LSECC_IRQHandler(void);

#endif
