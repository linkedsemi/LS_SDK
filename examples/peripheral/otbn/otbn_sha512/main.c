#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "log.h"

static uint8_t string[] = "abc";
static uint8_t result[SHA512_RESULT_SIZE]; 
// 0xDDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F
int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    
    HAL_OTBN_SHA512_Init();
    HAL_OTBN_SHA512_Update((uint8_t *)string, 3);
    HAL_OTBN_SHA512_Final(result);
    LOG_HEX((uint8_t *)result, SHA512_RESULT_SIZE);

    while (1) ;
}
