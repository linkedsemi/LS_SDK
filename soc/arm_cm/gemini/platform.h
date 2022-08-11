#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"
#include "gemini.h"

enum dpll_clk
{
    DPLL_128M,
    DPLL_136M,
};

void hclk_set(uint32_t mhz);

void clk_switch(void);

void stack_assert_asm(uint32_t,uint32_t,uint32_t);

void platform_reset(uint32_t error);

void arm_cm_set_int_isr(uint8_t type,void (*isr)());

void arm_cm_delay_asm(uint32_t);

void sys_init_none();

void pll_enable();

void irq_priority(void);

#define DELAY_US(a) arm_cm_delay_asm((a)*SDK_HCLK_MHZ/5)

#define SRAM_BIT_BAND_ADDR(addr,bit) (uint32_t *)(((uint32_t)(addr)-0x20000000)*32+4*(bit)+0x22000000)

#define PERI_BIT_BAND_ADDR(addr,bit) (uint32_t *)(((uint32_t)(addr)-0x40000000)*32+4*(bit)+0x42000000)

#if defined(GEMINI) && defined(FLASH_PROG_ALGO)
__attribute__((long_call)) void arm_cm_delay_asm(uint32_t);
#endif

#endif
