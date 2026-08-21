#include <string.h>
#include <stdint.h>
#include "platform.h"
#include "ls_hal_otbn_ecc.h"
#include "log.h"

/* ECDSA P-256 test vector (r/s/pubkey as u32 words, least-significant
 * word first -- the SDK verify parameter format) */
static uint32_t msg[8] = {
    0x4456fd21, 0x400bdd7d, 0xb54d7452, 0x17d015f1,
    0x90d4d90b, 0xb028ad8a, 0x6ce90fef, 0x06d71207};
static uint32_t sign_r[8] = {
    0x80a9674a, 0x1147ea56, 0x0c7d87dd, 0x99504edd,
    0xbe064de2, 0x6b35843c, 0x7dd27f33, 0x815215ad};
static uint32_t sign_s[8] = {
    0xc93fd605, 0xd0b1051e, 0xe90a6d17, 0x4dad9404,
    0x99e589ad, 0x86e30cd9, 0xc4440420, 0xa3991e01};
static uint32_t pubkey_x[8] = {
    0xbfa8c334, 0x9773b7b3, 0xf36b0689, 0x6ec0c0b2,
    0xdb6c8bf3, 0x1628ce58, 0xfacdc546, 0xb5511a6a};
static uint32_t pubkey_y[8] = {
    0x9e008c2e, 0xa8707058, 0xab9c6924, 0x7f7a11d0,
    0xb53a17fa, 0x43dd09ea, 0x1f31c143, 0x42a1c697};

static struct HAL_OTBN_ECC256_Verify_Param p256_param = {
    .msg = msg,
    .r = sign_r,
    .s = sign_s,
    .x = pubkey_x,
    .y = pubkey_y,
};

/* [0]=Polling result, [1]=IT callback result (GDB-readable) */
volatile uint32_t g_result[2] = {0, 0};

int main(void)
{
    sys_init_none();
    LOG_I(" OTBN P256_ECDSA_Verify_Test Start...");
    HAL_OTBN_Init();

    g_result[0] = HAL_OTBN_ECC256_ECDSA_Verify_Polling(&p256_param);
    if (g_result[0])
        LOG_I("HAL_OTBN_P256_Verify pass!");
    else
        LOG_I("HAL_OTBN_P256_Verify fail!");

    HAL_OTBN_ECC256_ECDSA_Verify_IT(&p256_param);

    while (1) ;
}

void HAL_OTBN_ECC256_ECDSA_Verify_CallBack(bool result)
{
    g_result[1] = result;
    LOG_I("ecdsa Verify IT: %s", result ? "PASS" : "FAIL");
}
