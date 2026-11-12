#include <string.h>
#include <stdlib.h>
#include "ls_hal_sha512.h"
#include "ls_hal_dmacv3.h"
#include "platform.h"
#include "log.h"

static uint8_t buffer[0x40];

DEF_DMA_CONTROLLER(dmac1_sha_inst,DMAC1);


static void sha_init(void)
{
    LOG_I("Sha512 DMA Test Start...");
}

static void sha_test(void)
{
}

int main()
{
    sys_init_none();
    sha_init();
    sha_test();
    while (1)
    {
        
    }
}
