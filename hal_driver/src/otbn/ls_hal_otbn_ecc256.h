#ifndef ECC_256_H_
#define ECC_256_H_
#include "ls_hal_otbn.h"
#ifdef __cplusplus
extern "C" {
#endif

struct HAL_OTBN_P256_Verify_Param
{
    uint32_t msg[8];
    uint32_t r[8];  /* signature R */
    uint32_t s[8];  /* signature S */
    uint32_t x[8];  /* public key x-coordinate */
    uint32_t y[8];  /* public key y-coordinate */
    uint32_t x_r[8];/* signature verification result x_r */
};

bool HAL_OTBN_P256_Verify_Polling(struct HAL_OTBN_P256_Verify_Param *verify_param);
void HAL_OTBN_ECC256_ECDSA_Verify_IT(struct HAL_OTBN_P256_Verify_Param *verify_param);
void HAL_OTBN_ECC256_ECDSA_Verify_CallBack(bool result);


#ifdef __cplusplus
}
#endif
#endif