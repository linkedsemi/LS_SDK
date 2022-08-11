#include "cpu.h"
#include "ls_hal_flash.h"
#include "gemini.h"
#include "ls_hal_cache.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "common.h"
#define APP_ADDR 0x800200

__NO_RETURN static void boot_app(uint32_t base)
{
    uint32_t *msp = (void *)base;
    void (**reset_handler)(void) = (void *)(base + 4);
    __set_MSP(*msp);
    __enable_irq();
    (*reset_handler)();
}

__NO_RETURN void boot_ram_start()
{
    __disable_irq();
    hal_flash_dual_mode_set(true);
    hal_flash_xip_start();
    lscache_cache_enable(1);
    boot_app(APP_ADDR);
}