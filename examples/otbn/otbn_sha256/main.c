#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "platform.h"
#include "log.h"

static uint8_t string[] = "abc";
static uint8_t result[32];
// 0xBA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD
int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();

    HAL_OTBN_SHA256_Init();
    HAL_OTBN_SHA256_Update((uint8_t *)string, 3);
    HAL_OTBN_SHA256_Final(result);
    LOG_HEX((uint8_t *)result, 0x20);

    while (1) ;
}
