#include <string.h>
#include <stdlib.h>
#include "ls_hal_sha512.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"


static uint8_t sha512_digest[0x80];

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
    HAL_SHA512_SHA512_Update((uint32_t *)0x10000000, 0x1000);
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
