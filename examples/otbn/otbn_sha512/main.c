#include <string.h>
#include <stdint.h>
#include "ls_hal_otbn_sha.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"
#include "tinycrypt/sha256.h"
#include "ls_hal_sha.h"

static uint8_t string[] = "abc";
static uint8_t result[SHA512_RESULT_SIZE]; 
// 0xDDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F
int main(void)
{
    sys_init_none();
    HAL_OTBN_Init();
    
    HAL_OTBN_SHA512_Init();
    io_cfg_output(PA11);
    io_set_pin(PA11);

    // HAL_LSSHA_SHA256_Init();//457ms
    // io_clr_pin(PA11);
    // HAL_LSSHA_Update((uint8_t *)0x10000000, 0x80000);
    // HAL_LSSHA_Final(result);
    // io_set_pin(PA11);
    
    // struct tc_sha256_state_struct hash;
    // tc_sha256_init(&hash);
    // io_clr_pin(PA11);//900ms+
    // tc_sha256_update(&hash, (uint8_t *)0x10000000, 0x10000);
    // tc_sha256_update(&hash, (uint8_t *)0x10010000, 0x10000);
    // tc_sha256_update(&hash, (uint8_t *)0x10020000, 0x10000);
    // tc_sha256_update(&hash, (uint8_t *)0x10030000, 0x10000);
    // tc_sha256_update(&hash, (uint8_t *)0x10040000, 0x10000);
    // tc_sha256_update(&hash, (uint8_t *)0x10050000, 0x10000);
    // tc_sha256_update(&hash, (uint8_t *)0x10060000, 0x10000);
    // tc_sha256_update(&hash, (uint8_t *)0x10070000, 0x10000);
    // tc_sha256_final(result, &hash);
    // io_set_pin(PA11);
    // LOG_HEX((uint8_t *)result, SHA512_RESULT_SIZE);

    HAL_OTBN_SHA256_Init();
    io_clr_pin(PA11);
    HAL_OTBN_SHA256_Update((uint8_t *)0x10000000, 0x80000);
    io_set_pin(PA11);
    HAL_OTBN_SHA256_Final(result);
    LOG_HEX((uint8_t *)result, SHA512_RESULT_SIZE);

    while (1) ;
}
