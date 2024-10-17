#include <string.h>
#include <stdlib.h>
#include "ls_hal_sha.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "log.h"

static const uint8_t plaintext[32] = {
    0xA7, 0xFC, 0xFC, 0x6B, 0x52, 0x69, 0xBD, 0xCC, 0xE5, 0x71, 0x79, 0x8D, 0x61, 0x8E, 0xA2, 0x19,
    0xA6, 0x8B, 0x96, 0xCB, 0x87, 0xA0, 0xE2, 0x10, 0x80, 0xC2, 0xE7, 0x58, 0xD2, 0x3E, 0x4C, 0xE9};

static const uint32_t ciphertext_sha256[8] = {
    0x96ada97d, 0x8abbef25, 0xc7703811, 0x7a52a8e4, 0x6a05e8f1, 0xfa553d87, 0x787e05a3, 0x5adccf5b};    

static const uint32_t ciphertext_sha224[7] = {
    0xc3d1a3c4, 0xb7942f35, 0xf2d61b8d, 0x5bbfcad8, 0x65e8269c, 0xbbdc1514, 0x9afec5b};

static const uint32_t ciphertext_sm3[8] = {
    0xd5339620, 0x1e34260d, 0xaa20ce75, 0x4897615c, 0x51ad9f0c, 0xedcf9ea9, 0x63008679, 0x3d914c08};

uint8_t plainbuffer[64];
uint8_t cipherbuffer_sha256[0x20];
uint8_t cipherbuffer_sha224[0x1C];
uint8_t cipherbuffer_sm3[0x20];

static void sha_init(void)
{
    HAL_LSSHA_Init();
}

static void sha_crypt_test(void)
{
    HAL_LSSHA_SHA256_Init();
    HAL_LSSHA_Update(plaintext, sizeof(plaintext));
    HAL_LSSHA_Final(cipherbuffer_sha256);
    if(!memcmp(cipherbuffer_sha256, ciphertext_sha256, sizeof(cipherbuffer_sha256)))
    {
        LOG_I("SHA256_ENCRYPT_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("SHA256_ENCRYPT_TEST_FAIL!");
    }

    HAL_LSSHA_SHA224_Init();
    HAL_LSSHA_Update(plaintext,sizeof(plaintext));
    HAL_LSSHA_Final(cipherbuffer_sha224);
    if(!memcmp(cipherbuffer_sha224, ciphertext_sha224, sizeof(cipherbuffer_sha224)))
    {
        LOG_I("SHA224_ENCRYPT_TEST_SUCCESS!");
    }
     else
    {
        LOG_I("SHA224_ENCRYPT_TEST_FAIL!");
    }

    HAL_LSSHA_SM3_Init();
    HAL_LSSHA_Update(plaintext, sizeof(plaintext));
    HAL_LSSHA_Final(cipherbuffer_sm3);
    if (!memcmp(cipherbuffer_sm3, ciphertext_sm3, sizeof(cipherbuffer_sm3)))
    {
        LOG_I("SM3_ENCRYPT_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("SM3_ENCRYPT_TEST_FAIL!");
    }
}

int main()
{
    sys_init_none();
    sha_init();
    sha_crypt_test();
    while (1)
    {
        
    }
}
