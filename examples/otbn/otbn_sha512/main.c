#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "log.h"

static uint8_t result[SHA512_RESULT_SIZE];
static uint8_t buffer[0x180];

/* HKDF test vector: salt = 0x44332211 (LE bytes 11 22 33 44), ikm = 32
 * bytes 0x00..0x1f, info = NULL; 32-byte OKM reference computed with
 * Python hashlib/hmac (RFC 5869). */
static uint32_t hkdf_salt = 0x44332211;
static uint32_t hkdf_ikm[] = {
    0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
    0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
static uint32_t hkdf_result[] = {
    0x01e4a014, 0x3cd902f1, 0xa8a10364, 0x181f227e,
    0x746d02c9, 0x10cb28d8, 0x6bcdcaf4, 0xfe2a86e9};
static uint8_t hkdf_out[32];

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    memset(buffer, 0x61, 0x180);

    if (HAL_OTBN_SHA512_Init() != HAL_OK ||
        HAL_OTBN_SHA512_Update((uint8_t *)buffer, 0x180) != HAL_OK ||
        HAL_OTBN_SHA512_Final(result) != HAL_OK) {
        LOG_I("SHA512 fail!");
        while (1) ;
    }
    LOG_HEX((uint8_t *)result, SHA512_RESULT_SIZE);

    if (HAL_OTBN_SHA512_HKDF((uint8_t *)&hkdf_salt, sizeof(hkdf_salt),
                             (uint8_t *)hkdf_ikm, sizeof(hkdf_ikm),
                             NULL, 0, hkdf_out, 0x20) != HAL_OK)
    {
        LOG_I("SHA512_HKDF Encrypt Test Fail....");
    }
    else if (!memcmp((uint8_t *)hkdf_result, hkdf_out, 0x20))
    {
        LOG_I("SHA512_HKDF Encrypt Test Pass....");
    }
    else
    {
        LOG_I("SHA512_HKDF Encrypt Test Fail....");
    }

    __BKPT();
    while (1) ;
}
