#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "log.h"

static uint8_t string[] = "abc";
static uint8_t result[SHA384_RESULT_SIZE]; 
// 0xCB00753F45A35E8BB5A03D699AC65007272C32AB0EDED1631A8B605A43FF5BED8086072BA1E7CC2358BAECA134C825A7
int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    
    HAL_OTBN_SHA384_Init();
    HAL_OTBN_SHA384_Update((uint8_t *)sha384_text, SHA384_TEXT_LENTH);
    HAL_OTBN_SHA384_Final(result);
    LOG_HEX((uint8_t *)result, SHA384_RESULT_SIZE);

    while (1) ;
}
