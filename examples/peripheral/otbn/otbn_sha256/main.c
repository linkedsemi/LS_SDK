#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "log.h"

extern const char sha256_text[540];

static uint8_t result[32];  //0x81c03b03b75b7779ed13fb36038795a81a1f7f642f5c4a1fc8e391e1930bfd08
int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    
    HAL_OTBN_SHA256_Init();
    HAL_OTBN_SHA256_Update((uint8_t *)sha256_text, 540);
    HAL_OTBN_SHA256_Final(result);
    LOG_HEX((uint8_t *)result, 0x20);

    while (1) ;
}
