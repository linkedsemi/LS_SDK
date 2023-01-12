#include <string.h>
#include <stdlib.h>
#include "ls_hal_trng.h"
#include "platform.h"
#include "log.h"

volatile bool completeflag;

int main()
{
    sys_init_none();
    HAL_TRNG_Init();
    while (1)
    {
        completeflag = true;
        HAL_TRNG_GenerateRandomNumber_IT();
        while (completeflag);
        DELAY_US(1000 * 300);
    }
}

void HAL_TRNG_ReadyDataCallback(uint32_t random32bit)
{
    LOG_I("RandomNumber: %x", random32bit);
    completeflag = false;
}