#include "cpu.h"
#include "ls_hal_flash.h"
#include "lm3050.h"
#include "ls_hal_cache.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "common.h"
#include "reg_sysc_awo_type.h"
#include "reg_v33_rg_type.h"
#define APP_ADDR 0x800300

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
__NO_RETURN void boot_ram_start()
{
    __disable_irq();
    SYSC_AWO->IO[3].PUPD = 0xf000;
    hal_flash_dual_mode_set(true);
    pinmux_hal_flash_quad_init();
    hal_flash_xip_start();
    lscache_cache_enable(1);
    trim_val_load();
    boot_app(APP_ADDR);
}