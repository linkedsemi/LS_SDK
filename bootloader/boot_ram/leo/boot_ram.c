#include "cpu.h"
#include "ls_hal_flash.h"
#include "leo.h"
#include "ls_hal_cache.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "common.h"
#include "reg_sysc_awo.h"
#include "core_rv32.h"
#include "reg_v33_rg.h"
#include "field_manipulate.h"
#include "ls_hal_sha.h"
#include "../../module/micro-ecc/uECC.h"

#define APP_ADDR 0x8000800
#define APP_OFFSET 0x800
#define APP_SIGN_OFFSET APP_OFFSET - 0x40
#define APP_SIZE_INFO APP_OFFSET - 0x44

#define EC_MODE_PIN PB06
#define I2C0_SCL_PIN PA11
#define I2C1_SCL_PIN PC02
#define I2C2_SCL_PIN PC04
#define I2C2_SCL_ALT_PIN PE00
#define I2C3_SCL_PIN PB00
#define I2C4_SCL_PIN PE05
#define I2C5_SCL_PIN PE13
#define I2C6_SCL_PIN PB14
#define I2C7_SCL_PIN PH07

const uint8_t i2c_scl_list[] = {
    I2C0_SCL_PIN,
    I2C1_SCL_PIN,
    I2C2_SCL_PIN,
    I2C2_SCL_ALT_PIN,
    I2C3_SCL_PIN,
    I2C4_SCL_PIN,
    I2C5_SCL_PIN,
    I2C6_SCL_PIN,
    I2C7_SCL_PIN,
};

void boot_app(uint32_t base)
{
    void (*reset_handler)(void) = (void *)(base);
    reset_handler();
    while(1);
}

static void trim_val_load()
{
    uint32_t trim_value[12] = {0};

    hal_flash_read_security_area(1,0,(uint8_t *)trim_value,sizeof(trim_value));
    if(trim_value[0] == ~trim_value[1])
    {
        V33_RG->SRAM_LOCK = trim_value[0];
    }
    if(trim_value[2] == ~trim_value[3])
    {
        V33_RG->ANA_PMU_CTRL = trim_value[2];
    }
    if(trim_value[4] == ~trim_value[5])
    {
        V33_RG->TRIM0 = trim_value[4];
    }
    if(trim_value[6] == ~trim_value[7])
    {
        MODIFY_REG(V33_RG->SFT_CTRL01,0x70000000,trim_value[6]);
    }
    if(trim_value[8] == ~trim_value[9])
    {
        SYSC_AWO->PD_AWO_ANA1 = trim_value[8];
    }
    if(trim_value[10] == ~trim_value[11])
    {
        V33_RG->OP_CTRL = trim_value[10];
    }
}

void io_vcore_exti_config(uint8_t pin,exti_edge_t edge);
static void i2c_dbg_detect_int_disable()
{
    uint8_t i;
    for(i=0;i<ARRAY_LEN(i2c_scl_list);++i)
    {
        io_vcore_exti_config(i2c_scl_list[i],INT_EDGE_NONE);

    }
    csi_vic_disable_irq(EXTI_ASYNC_IRQn);
}

static void ext_flash_io_deinit()
{
    //cs
    uint8_t pin = PB07;
	set_gpio_mode((gpio_port_pin_t *)&pin);
    io_cfg_disable(pin);
    //clk
    pin = PB10;
	set_gpio_mode((gpio_port_pin_t *)&pin);
    io_cfg_disable(pin);
    //mosi
    pin = PB08;
	set_gpio_mode((gpio_port_pin_t *)&pin);
    io_cfg_disable(pin);
    //miso
    pin = PB09;
	set_gpio_mode((gpio_port_pin_t *)&pin);
    io_cfg_disable(pin);
}

extern bool sec_boot;
extern bool secp256k1;
extern uint8_t pub_key[64];
bool sign_verification(uint8_t *signature)
{
    uint32_t app_len;
    uint32_t digest[SHA256_WORDS_NUM];
    hal_flash_quad_io_read(APP_SIZE_INFO, (uint8_t *)&app_len,sizeof(app_len));
    HAL_LSSHA_Init();
    HAL_LSSHA_SHA256((void *)APP_ADDR,app_len,digest);
    HAL_LSSHA_DeInit();
    uECC_Curve curve = secp256k1 ? uECC_secp256k1() : uECC_secp256r1();
    uint8_t result =  uECC_verify(pub_key,(uint8_t *)digest,32,signature,curve);
    return result;
}

void ecc_verify(void)
{
    bool passed = false;
    uint8_t signature[64];
    if(sec_boot)
    {
        hal_flash_quad_io_read(APP_SIGN_OFFSET,signature,sizeof(signature));
        passed = sign_verification(signature);
        while(passed == false);
    }
}

void boot_ram_start()
{
    if(io_read_pin(EC_MODE_PIN))
    {
        ext_flash_io_deinit();
        DELAY_US(1100);
        i2c_dbg_detect_int_disable();
    }else
    {   //pull up ph02 ph03
        MODIFY_REG(SYSC_AWO->IO[7].PUPD,3<<16<<2,3<<2);
    }
    __disable_irq();
    hal_flash_drv_var_init(false,false);
    hal_flash_init();
    hal_flash_dual_mode_set(false);
    pinmux_hal_flash_quad_init();
    trim_val_load();
    hal_flash_xip_start();
    lscache_cache_enable(1);
    hal_flash_xip_func_ptr_init();
    ecc_verify();
    boot_app(APP_ADDR);
}