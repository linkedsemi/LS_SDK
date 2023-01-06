#include <string.h>
#include <stdlib.h>
#include "ls_hal_trng.h"
#include "platform.h"
#include "log.h"

static uint32_t random32bit;

int main()
{
    sys_init_none();
    HAL_TRNG_Init();
    while (1)
    {
        HAL_TRNG_GenerateRandomNumber(&random32bit);
        LOG_I("RandomNumber: %x", random32bit);
        DELAY_US(1000 * 1000);
    }
}