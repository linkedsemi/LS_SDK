#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include "core_rv32.h"
#include "sdk_config.h"



void rv32_delay_asm(uint32_t,uint32_t);

#define DELAY_US(a) rv32_delay_asm((a)*SDK_HCLK_MHZ/5,1)
#define DELAY_MS(a) DELAY_US((a)*1000)

#endif
