#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "log.h"

static uint8_t string[] = "abc";
static uint8_t result[SHA384_RESULT_SIZE]; 
// 0xCB00753F45A35E8BB5A03D699AC65007272C32AB0EDED1631A8B605A43FF5BED8086072BA1E7CC2358BAECA134C825A7

static uint32_t hkdf_salt = 0x44332211;
static uint32_t hkdf_ikm[] = {
    0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
    0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
static uint32_t hkdf_result[] = {
    0x4328d2a2, 0x4bce12d3, 0xb5604d8, 0xdc6dd86e,
    0xa6c48ee9, 0x52186373, 0xab2e2240, 0x13daac4f};

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    
    HAL_OTBN_SHA384_Init();
    HAL_OTBN_SHA384_Update((uint8_t *)string, 3);
    HAL_OTBN_SHA384_Final(result);
    LOG_HEX(result, SHA384_RESULT_SIZE);

    HAL_OTBN_SHA384_HKDF((uint8_t *)&hkdf_salt,sizeof(hkdf_salt),(uint8_t *)hkdf_ikm,sizeof(hkdf_ikm),NULL,0,result,0x20);
    if (!memcmp((uint8_t *)hkdf_result, result, 0x20))
    {
        LOG_I("SHA384_HKDF Encrypt Test Pass....");
    }
    else
    {
        LOG_I("SHA384_HKDF Encrypt Test Fail....");
    }

    while (1) ;
}
