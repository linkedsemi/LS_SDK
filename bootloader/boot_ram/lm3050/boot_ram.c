#include "cpu.h"
#include "ls_hal_flash.h"
#include "lm3050.h"
#include "ls_hal_cache.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "common.h"
#include "reg_sysc_awo_type.h"
#include "reg_v33_rg_type.h"
#include "ls_hal_sha.h"
#include "../../module/micro-ecc/uECC.h"
#include "ls_msp_qspiv2.h"
#define APP_ADDR 0x800500
#define APP_OFFSET 0x500
#define APP_SIGN_OFFSET APP_OFFSET - 0x40
#define APP_SIZE_INFO APP_OFFSET - 0x44


__NO_RETURN static void boot_app(uint32_t base)
{
    uint32_t *msp = (void *)base;
    void (**reset_handler)(void) = (void *)(base + 4);
    __set_MSP(*msp);
    __enable_irq();
    (*reset_handler)();
    while(1);
}
static void trim_val_load()
{
    uint32_t trim_value[8] = {0};

    hal_flash_read_security_area(1,0x10,(uint8_t *)trim_value,sizeof(trim_value));
    if(trim_value[0] == ~trim_value[1])
    {
        SYSC_AWO->PD_AWO_ANA1 = trim_value[0];
    }

    if(trim_value[2] == ~trim_value[3])
    {
        V33_RG->OP_CTRL = trim_value[2];
    }

    if(trim_value[6] == ~trim_value[7])
    {
        V33_RG->TRIM0 = trim_value[6];
    }
}

extern bool sec_boot;
extern bool secp256k1;
extern uint8_t pub_key[64];
bool signature_verification(uint8_t *signature)
{
    uint32_t app_len;
    uint32_t digest[SHA256_WORDS_NUM];
    hal_flash_dual_io_read(APP_SIZE_INFO, (uint8_t *)&app_len,sizeof(app_len));
    HAL_LSSHA_Init();
    HAL_LSSHA_SHA256((void *)APP_ADDR,app_len,digest);
    HAL_LSSHA_DeInit();
    uECC_Curve curve = secp256k1 ? uECC_secp256k1() : uECC_secp256r1();
    uint8_t result =  uECC_verify(pub_key,(uint8_t *)digest,32,signature,curve);
    return result;
}

static void ecc_verify(void)
{
    bool passed = false;
    uint8_t signature[64];
    if(sec_boot)
    {
        hal_flash_dual_io_read(APP_SIGN_OFFSET,signature,sizeof(signature));
        passed = signature_verification(signature);
        while(passed == false);
    }
}

__NO_RETURN void boot_ram_start()
{
    __disable_irq();
    SYSC_AWO->IO[3].PUPD = 0xf000;
    flash1.reg = LSQSPIV2;
    flash1.dual_mode_only = true;
    flash1.writing = false;
    flash1.continuous_mode_enable = false;
    flash1.continuous_mode_on = false;
    flash1.suspend_count = 0;
    flash1.addr4b = false;
    hal_flash_init();
    pinmux_hal_flash_quad_init();
    lscache_cache_enable(1);
    trim_val_load();
    ecc_verify();
    boot_app(APP_ADDR);
}