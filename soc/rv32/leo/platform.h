#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include "leo.h"
#include "ls_dbg.h"
#include "core_rv32.h"
#include "sdk_config.h"
#include "reg_sysc_awo.h"
#include "field_manipulate.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void (*interrupt_vector[])();

__attribute__((always_inline)) static inline void hclk_set(uint32_t mhz)
{
    switch(mhz)
    {
    case 144:
        MODIFY_REG(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS_MASK, 8<<SYSC_AWO_CLK_SEL_HBUS_POS);
    break;
    case 72:
        SYSC_AWO->PD_AWO_CLKG_SRST = SYSC_AWO_CLKG_SET_DIV_HBUS_MASK;
        MODIFY_REG(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS_MASK|SYSC_AWO_CLK_DIV_PARA_HBUS_M1_MASK, 4<<SYSC_AWO_CLK_SEL_HBUS_POS|1<<SYSC_AWO_CLK_DIV_PARA_HBUS_M1_POS);
    break;
    case 36:
        SYSC_AWO->PD_AWO_CLKG_SRST = SYSC_AWO_CLKG_SET_DIV_HBUS_MASK;
        MODIFY_REG(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS_MASK|SYSC_AWO_CLK_DIV_PARA_HBUS_M1_MASK, 4<<SYSC_AWO_CLK_SEL_HBUS_POS|3<<SYSC_AWO_CLK_DIV_PARA_HBUS_M1_POS);
    break;
    case 24:
        LS_ASSERT(SDK_HSE_USED==0);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 1);
    break;
    case 16:
        LS_ASSERT(SDK_HSE_USED==1);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 2);
    break;
    default:
        LS_ASSERT(0);
    break;
    }
}

void rv_set_int_isr(uint8_t type,void (*isr)());

void platform_reset(uint32_t);

void key_reset(uint32_t seconds, uint8_t pin, bool voltage_level);

void sys_init_none(void);

void rv32_delay_asm(uint32_t,uint32_t);

void SWINT_Handler_ASM();

void OS_SWINT_Handler();

void clk_flash_init();

uint32_t get_hclk_mhz();

void rng_init();

#ifndef RNG_32K_NUMBER
#define RNG_32K_NUMBER (20)
#endif
uint32_t GenerateRandom32Bit();

#define DELAY_US(a) rv32_delay_asm((a)*SDK_HCLK_MHZ/5,1)
#define DELAY_MS(a) DELAY_US((a)*1000)

#define ROM_FLASH_API
#ifdef ROM_FLASH_API
#define FLASH_SWINT_NUM RV_SOFT_IRQn
#else
#define FLASH_SWINT_NUM QSPI_IRQn
#endif

#ifdef FREERTOS
#define FLASH_SWINT_HANDLER OS_SWINT_Handler
#else
#define FLASH_SWINT_HANDLER SWINT_Handler_ASM
#endif

#define GLOBAL_INT_MASK_STATUS() (!(__get_MSTATUS()&0x8))

#ifdef __cplusplus
}
#endif

#endif
