#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "tinycrypt/sha256.h"
#include "log.h"

extern const char sha256_text[540];

static uint8_t result[32];  //38D18DA8209A9EA9AB6B811AAF6967688CE28995C2B666F39CE68E704AC27B90
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
