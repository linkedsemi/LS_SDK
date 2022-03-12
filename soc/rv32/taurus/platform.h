#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include "sdk_config.h"

void stack_assert_asm(uint32_t,uint32_t,uint32_t);

void platform_reset(uint32_t);

void clk_switch(void);

void irq_priority(void);

void sys_init_none(void);

void sys_init_itf(void);

void sys_init_app(void);

void rv32_delay_asm(uint32_t,uint32_t);

#define DELAY_US(a) rv32_delay_asm((a)*SDK_HCLK_MHZ/3,1)



#endif
