#include <string.h>
#include <stdlib.h>
#include "ls_hal_sha512.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"


static uint8_t sha512_digest[0x80];
__attribute__((aligned(4))) uint8_t aaaa[] = "8FC344A1B37DDB5BE214D27040B80C10B9880878E5A14B442A07401EC7F833EB7966C37AB01E0E933049A656F32BC7ABDFC77A7AB326BB06E8073BB2784F6BA60";
static uint8_t ciphertext_sha512_digest[0x80] = {
    0x30, 0x2C, 0xA1, 0x49, 0xC7, 0x5F, 0x35, 0x12, 0x0F, 0x55, 0xBF, 0xC5, 0x49, 0x7A, 0xEA, 0x8C, 
    0xC6, 0x37, 0x5C, 0x93, 0xFF, 0xA6, 0x3E, 0xFE, 0xB7, 0x6C, 0xBA, 0x8D, 0x05, 0x25, 0x47, 0x89, 
    0x55, 0xE9, 0xBA, 0xD5, 0xD5, 0x88, 0xE5, 0x7E, 0x2D, 0x55, 0xEF, 0xBA, 0xE0, 0x67, 0x37, 0xA0, 
    0x86, 0x8F, 0xAC, 0xCD, 0xA5, 0x4E, 0x18, 0x58, 0x15, 0x47, 0x71, 0xAE, 0xD2, 0x39, 0x35, 0xC7};

static void sha_init(void)
{
    HAL_SHA512_Init();//0x40005000
    LOG_I("Sha512 Polling Test Start...");
}

static void sha_test(void)
{
    io_cfg_output(PH02);
    io_set_pin(PH02);
    
    HAL_SHA512_SHA512_Init();
    HAL_SHA512_SHA512_Update((uint32_t *)aaaa, strlen((const char*)aaaa));
    HAL_SHA512_SHA512_Final(sha512_digest);
    LOG_HEX(sha512_digest, 0x40);
    if(!memcmp(sha512_digest, ciphertext_sha512_digest, sizeof(ciphertext_sha512_digest)))
    {
        LOG_I("SHA512_ENCRYPT_TEST_SUCCESS!");
    }
    else
    {
        LOG_I("SHA512_ENCRYPT_TEST_FAIL!");
    }

    // SHA512->INTR_MSK= 0x0;
    // SHA512->ADDR = (uint32_t)a;
    // SHA512->CTRL = 0xD;
    // // SHA512->CTRL |= 1 << 16;
    // SHA512->CTRL |= 2;
}

int main()
{
    sys_init_none();
    sha_init();
    sha_test();
    

    __BKPT();
    while (1)
    {
        
    }
}
