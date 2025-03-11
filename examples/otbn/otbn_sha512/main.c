#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "ls_hal_otbn_hash.h"
#include "platform.h"
#include "log.h"

static uint8_t result[SHA512_RESULT_SIZE]; 
static uint8_t buffer[0x180];

int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    memset(buffer, 0x61, 0x180);
    
    HAL_OTBN_SHA512_Init();
    HAL_OTBN_SHA512_Update((uint8_t *)buffer, 0x180);
    HAL_OTBN_SHA512_Final(result);
    LOG_HEX((uint8_t *)result, SHA512_RESULT_SIZE);

    __BKPT();
    while (1) ;
}
