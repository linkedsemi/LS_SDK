#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include "field_manipulate.h"
#include "sdk_config.h"
#include "core_rv32.h"
#include "qsh.h"
#include "reg_sysc_sec_cpu.h"
#include "reg_sysc_app_cpu.h"

__attribute__((always_inline)) static inline void e906_init()
{
    uint32_t value = __get_MSTATUS();
    MODIFY_REG(value,0x6000,0x2000); 
    __set_MSTATUS(value);//enable fpu
    value = __get_MHCR();
    value |= (CACHE_MHCR_RS_Msk | CACHE_MHCR_BPE_Msk | CACHE_MHCR_L0BTB_Msk);
    __set_MHCR(value);
}

void sys_init_none(void);

void rv_set_int_isr(uint8_t type,void (*isr)());

void rv32_delay_asm(uint32_t,uint32_t);

void SWINT_Handler_ASM();

void flash_swint_init();

#ifdef FREERTOS
#define FLASH_SWINT_HANDLER OS_SWINT_Handler
#else
#define FLASH_SWINT_HANDLER SWINT_Handler_ASM
#endif

#define DELAY_US(a) rv32_delay_asm((a)*SDK_HCLK_MHZ/5,1)
#define DELAY_MS(a) DELAY_US((a)*1000)

#define FLASH_SWINT_NUM RV_SOFT_IRQN
#define GLOBAL_INT_MASK_STATUS() (!(__get_MSTATUS()&0x8))

static inline void cpu_intr0_unmask(void)
{
    SYSC_APP_CPU->APP_CPU_IMSK = 1;
}

static inline void cpu_intr0_mask(void)
{
    SYSC_APP_CPU->APP_CPU_IMSK = 0;
}

static inline void cpu_intr0_activate(void)
{
    SYSC_APP_CPU->APP_CPU_INTR = 1;
}

static inline void cpu_intr0_clr(void)
{
    SYSC_APP_CPU->APP_CPU_INTR = 0;
}

static inline void cpu_intr1_unmask(void)
{
    SYSC_SEC_CPU->SEC_CPU_IMSK = 1;
}

static inline void cpu_intr1_mask(void)
{
    SYSC_SEC_CPU->SEC_CPU_IMSK = 0;
}

static inline void cpu_intr1_activate(void)
{
    SYSC_SEC_CPU->SEC_CPU_INTR = 1;
}

static inline void cpu_intr1_clr(void)
{
    SYSC_SEC_CPU->SEC_CPU_INTR = 0;
}

static inline void app_cpu_reset(void)
{
    SYSC_SEC_CPU->APP_CPU_SRST = 0;
}

static inline void app_cpu_dereset(void)
{
    SYSC_SEC_CPU->APP_CPU_SRST = 1;
}

static inline void app_cpu_reset_pc(uint32_t addr)
{
    SYSC_SEC_CPU->APP_CPU_ADDR_CFG = addr;
}

#endif
