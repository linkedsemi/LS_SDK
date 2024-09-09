#include <string.h>
#include <stdint.h>
#include "platform.h"
#include "ls_hal_otbn_ecc256.h"
#include "log.h"

static struct HAL_OTBN_P256_Verify_Param p256_param =
{
    .msg = {0x4456fd21 ,0x400bdd7d ,0xb54d7452 ,0x17d015f1 ,0x90d4d90b ,0xb028ad8a ,0x6ce90fef ,0x06d71207},
    .r = {0x80a9674a ,0x1147ea56 ,0x0c7d87dd ,0x99504edd ,0xbe064de2 ,0x6b35843c ,0x7dd27f33 ,0x815215ad},
    .s = {0xc93fd605 ,0xd0b1051e ,0xe90a6d17 ,0x4dad9404 ,0x99e589ad ,0x86e30cd9 ,0xc4440420 ,0xa3991e01},
    .x = {0xbfa8c334 ,0x9773b7b3 ,0xf36b0689 ,0x6ec0c0b2 ,0xdb6c8bf3 ,0x1628ce58 ,0xfacdc546 ,0xb5511a6a},
    .y = {0x9e008c2e ,0xa8707058 ,0xab9c6924 ,0x7f7a11d0 ,0xb53a17fa ,0x43dd09ea ,0x1f31c143 ,0x42a1c697},
    .x_r = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
};

int main(void)
{
    sys_init_none();
    LOG_I(" OTBN P256_ECDSA_Verify_Test Start...");
    HAL_OTBN_Init();

    if (HAL_OTBN_P256_Verify_Polling(&p256_param))
        LOG_I("HAL_OTBN_P256_Verify pass!");
    else
        LOG_I("HAL_OTBN_P256_Verify fail!");

    HAL_OTBN_ECC256_ECDSA_Verify_IT(&p256_param);

    while (1) ;
}

void HAL_OTBN_ECC256_ECDSA_Verify_CallBack(bool result)
{
    LOG_I("ecdsa Verify IT result : %d", result);
}

