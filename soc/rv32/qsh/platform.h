#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include "sdk_config.h"
#include "core_rv32.h"
#include "qsh.h"



void rv32_delay_asm(uint32_t,uint32_t);

#define DELAY_US(a) rv32_delay_asm((a)*SDK_HCLK_MHZ/5,1)
#define DELAY_MS(a) DELAY_US((a)*1000)


#define FLASH_SWINT_NUM RV_SOFT_IRQn
#define GLOBAL_INT_MASK_STATUS() (!(__get_MSTATUS()&0x8))

#endif
