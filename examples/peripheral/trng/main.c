#include <string.h>
#include <stdlib.h>
#include "ls_hal_trng.h"
#include "platform.h"
#include "log.h"

int main()
{
    sys_init_none();
    uint32_t random32bit;
#ifdef LEO
    rng_init();
#endif
    while (1)
    {
        random32bit = GenerateRandom32Bit();
        LOG_I("Random32bit: 0x%x", random32bit);
        DELAY_US(1000 * 1000);
    }
}