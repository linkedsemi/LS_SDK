#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include <stdbool.h>
#include "sdk_config.h"
#include "lm3050.h"
#include "ls_dbg.h"
#include "reg_sysc_awo_type.h"
#include "field_manipulate.h"
#include "common.h"
#include "systick.h"

#ifdef __cplusplus
extern "C" {
#endif
#define ISR_VECTOR_ADDR ((uint32_t *)(0x20000000))

__attribute__((always_inline)) static inline void arm_cm_set_int_isr(int8_t type,void (*isr)())
{
    ISR_VECTOR_ADDR[type + 16] = (uint32_t)isr;
}

__attribute__((always_inline)) static inline void hclk_set(uint32_t mhz)
{
    switch(mhz)
    {
    case 128:
        MODIFY_REG(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS_MASK, 8<<SYSC_AWO_CLK_SEL_HBUS_POS);
    break;
    case 64:
        SYSC_AWO->PD_AWO_CLKG_SRST = SYSC_AWO_CLKG_SET_DIV_HBUS_MASK;
        MODIFY_REG(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS_MASK|SYSC_AWO_CLK_DIV_PARA_HBUS_M1_MASK, 4<<SYSC_AWO_CLK_SEL_HBUS_POS|1<<SYSC_AWO_CLK_DIV_PARA_HBUS_M1_POS);
    break;
    case 32:
        SYSC_AWO->PD_AWO_CLKG_SRST = SYSC_AWO_CLKG_SET_DIV_HBUS_MASK;
        MODIFY_REG(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS_MASK|SYSC_AWO_CLK_DIV_PARA_HBUS_M1_MASK, 4<<SYSC_AWO_CLK_SEL_HBUS_POS|3<<SYSC_AWO_CLK_DIV_PARA_HBUS_M1_POS);
    break;
    case 24:
        LS_ASSERT(SDK_HSE_USED==0);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 1);
    break;
    case 16:
        LS_ASSERT(SDK_HSE_USED==1);
        SYSC_AWO->PD_AWO_CLKG_SRST = SYSC_AWO_CLKG_SET_DIV_HBUS_MASK;
        MODIFY_REG(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS_MASK|SYSC_AWO_CLK_DIV_PARA_HBUS_M1_MASK, 4<<SYSC_AWO_CLK_SEL_HBUS_POS|7<<SYSC_AWO_CLK_DIV_PARA_HBUS_M1_POS);
    break;
    default:
        LS_ASSERT(0);
    break;
    }
}

void clk_flash_init(void);

void platform_reset(uint32_t error);

void arm_cm_set_int_isr(int8_t type,void (*isr)());

void arm_cm_delay_asm(uint32_t);

void sys_init_none();

#define DELAY_US(a) arm_cm_delay_asm((a)*SDK_HCLK_MHZ/4)
#define DELAY_MS(a) DELAY_US((a)*1000)

#define FLASH_SWINT_NUM QSPI_IRQn

#define GLOBAL_INT_MASK_STATUS() __get_PRIMASK()

#define SRAM_BIT_BAND_ADDR(addr,bit) (uint32_t *)(((uint32_t)(addr)-0x20000000)*32+4*(bit)+0x22000000)

#define PERI_BIT_BAND_ADDR(addr,bit) (uint32_t *)(((uint32_t)(addr)-0x40000000)*32+4*(bit)+0x42000000)

static inline uint32_t flash_get_current_time(void)
{
    uint32_t t1, t2, val;
    do {
        t1  = systick_get_value();
        val = SysTick->VAL;
        t2  = systick_get_value();
    } while (t1 != t2);
    return t1 * (SysTick->LOAD + 1) + (SysTick->LOAD - val);
}
static inline uint32_t flash_time_us2ticks(uint32_t us) { return us * SDK_HCLK_MHZ; }

#if defined(__ZEPHYR__)
#include <zephyr/sys/atomic.h>
#else
static inline bool atomic_cas_ram(long *ptr, long oldval, long newval)
{
    if(*ptr == oldval) {
        *ptr = newval;
        return true;
    } else {
        return false;
    }
}

static inline long atomic_inc(long *ptr)
{
    return ++(*ptr);
}

static inline long atomic_dec(long *ptr)
{
    return --(*ptr);
}
#endif

#if defined(LM3050) && defined(FLASH_PROG_ALGO)
__attribute__((long_call)) void arm_cm_delay_asm(uint32_t);
#endif

#ifdef __cplusplus
}
#endif

#endif
