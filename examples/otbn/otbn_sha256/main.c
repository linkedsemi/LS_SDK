#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "log.h"

static uint8_t string[] = "abc";
static uint8_t result[32];
// 0xBA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD

/* HKDF test vector: salt = 0x44332211 (LE bytes 11 22 33 44), ikm = 32
 * bytes 0x00..0x1f, info = NULL; 32-byte OKM reference computed with
 * Python hashlib/hmac (RFC 5869). */
static uint32_t hkdf_salt = 0x44332211;
static uint32_t hkdf_ikm[] = {
    0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
    0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
static uint32_t hkdf_result[] = {
    0x72f8bc40, 0x60a9ce7c, 0xfca6b08e, 0xd0f643d2,
    0xe02b6334, 0x89229067, 0x9cf569d3, 0x51808f0a};
static uint8_t hkdf_out[32];

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();

    if (HAL_OTBN_SHA256_Init() != HAL_OK ||
        HAL_OTBN_SHA256_Update((uint8_t *)string, 3) != HAL_OK ||
        HAL_OTBN_SHA256_Final(result) != HAL_OK) {
        LOG_I("SHA256 fail!");
        while (1) ;
    }
    LOG_HEX((uint8_t *)result, 0x20);

    if (HAL_OTBN_SHA256_HKDF((uint8_t *)&hkdf_salt, sizeof(hkdf_salt),
                             (uint8_t *)hkdf_ikm, sizeof(hkdf_ikm),
                             NULL, 0, hkdf_out, 0x20) != HAL_OK)
    {
        LOG_I("SHA256_HKDF Encrypt Test Fail....");
    }
    else if (!memcmp((uint8_t *)hkdf_result, hkdf_out, 0x20))
    {
        LOG_I("SHA256_HKDF Encrypt Test Pass....");
    }
    else
    {
        LOG_I("SHA256_HKDF Encrypt Test Fail....");
    }

    while (1) ;
}
