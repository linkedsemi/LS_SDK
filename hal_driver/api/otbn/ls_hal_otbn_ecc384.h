#ifndef LS_HAL_OTBN_ECC384_H_
#define LS_HAL_OTBN_ECC384_H_
#include "ls_hal_otbn.h"
#ifdef __cplusplus
extern "C" {
#endif

enum HAL_OTBN_ECC384_CURVES
{
    HAL_OTBN_ECC384_CURVE_P384 = 0,
};

struct HAL_OTBN_ECC384_Verify_Param
{
    uint32_t *message;
    uint32_t *sign_r;
    uint32_t *sign_s;
    uint32_t *pubkey_x;
    uint32_t *pubkey_y;
};

void HAL_OTBN_ECC384_ECDSA_Verify_CallBack(bool result);
bool HAL_OTBN_ECC384_ECDSA_Verify_Polling(enum HAL_OTBN_ECC384_CURVES curve, struct HAL_OTBN_ECC384_Verify_Param *verify_param);
void HAL_OTBN_ECC384_ECDSA_Verify_IT(enum HAL_OTBN_ECC384_CURVES curve, struct HAL_OTBN_ECC384_Verify_Param *verify_param);

#ifdef __cplusplus
}
#endif
#endif