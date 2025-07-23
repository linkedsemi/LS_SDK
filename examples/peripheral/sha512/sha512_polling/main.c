#include <string.h>
#include <stdlib.h>
#include "ls_hal_sha512.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"


static uint8_t sha512_digest[0x80];
__attribute__((aligned(4))) uint8_t aaaa[] = "8FC344A1B37DDB5BE214D27040B80C10B9880878E5A14B442A07401EC7F833EB7966C37AB01E0E933049A656F32BC7ABDFC77A7AB326BB06E8073BB2784F6BA60";

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
