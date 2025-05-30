#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdint.h>
#include "field_manipulate.h"
#include "sdk_config.h"
#include "core_rv32.h"
#include "qsh.h"
#include "reg_sysc_sec_cpu.h"
#include "reg_sysc_app_cpu.h"

#ifndef __ASM
#define __ASM                   __asm     /*!< asm keyword for GNU Compiler */
#endif

#ifndef __INLINE
#define __INLINE                inline    /*!< inline keyword for GNU Compiler */
#endif

#ifndef __ALWAYS_STATIC_INLINE
#define __ALWAYS_STATIC_INLINE  __attribute__((always_inline)) static inline
#endif

#ifndef __STATIC_INLINE
#define __STATIC_INLINE         static inline
#endif

__ALWAYS_STATIC_INLINE void e906_init()
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

#ifdef BOOT_ROM
void rom_delay(uint32_t us);
#define DELAY_US(a) rom_delay(a)
#else
#define DELAY_US(a) rv32_delay_asm((a)*SDK_HCLK_MHZ/5,1)
#endif
#define DELAY_MS(a) DELAY_US((a)*1000)

#define FLASH_SWINT_NUM QSPI1_IRQN
#define GLOBAL_INT_MASK_STATUS() (!(__get_MSTATUS()&0x8))

__ALWAYS_STATIC_INLINE void cpu_intr_sec_unmask(void)
{
    SYSC_SEC_CPU->SEC_CPU_IMSK = 1;
}

__ALWAYS_STATIC_INLINE void cpu_intr_sec_mask(void)
{
    SYSC_SEC_CPU->SEC_CPU_IMSK = 0;
}

__ALWAYS_STATIC_INLINE void cpu_intr_sec_activate(void)
{
    SYSC_SEC_CPU->SEC_CPU_INTR = 1;
}

__ALWAYS_STATIC_INLINE void cpu_intr_sec_clr(void)
{
    SYSC_SEC_CPU->SEC_CPU_INTR = 0;
}

__ALWAYS_STATIC_INLINE void app_cpu_reset(void)
{
    SYSC_SEC_CPU->APP_CPU_SRST = 0x2; /* reset */
}

__ALWAYS_STATIC_INLINE void cpu_intr_app_unmask(void)
{
    SYSC_APP_CPU->APP_CPU_IMSK = 1;
}

__ALWAYS_STATIC_INLINE void cpu_intr_app_mask(void)
{
    SYSC_APP_CPU->APP_CPU_IMSK = 0;
}

__ALWAYS_STATIC_INLINE void cpu_intr_app_activate(void)
{
    SYSC_APP_CPU->APP_CPU_INTR = 1;
}

__ALWAYS_STATIC_INLINE void cpu_intr_app_clr(void)
{
    SYSC_APP_CPU->APP_CPU_INTR = 0;
}

#if defined(CONFIG_CPU2_BOOT_ADDR)
__ALWAYS_STATIC_INLINE void app_cpu_dereset(void)
{
    SYSC_SEC_CPU->APP_CPU_ADDR_CFG = CONFIG_CPU2_BOOT_ADDR; /* set cpu1 pc addr */
    SYSC_SEC_CPU->APP_CPU_SRST = 0x1; /* release reset */
}
#endif

__ALWAYS_STATIC_INLINE void app_cpu_dereset_by_addr(uint32_t pc_addr)
{
    SYSC_SEC_CPU->APP_CPU_ADDR_CFG = pc_addr; /* set cpu1 pc addr */
    SYSC_SEC_CPU->APP_CPU_SRST = 0x1; /* release reset */
}

__ALWAYS_STATIC_INLINE void app_cpu_reset_pc(uint32_t addr)
{
    SYSC_SEC_CPU->APP_CPU_ADDR_CFG = addr;
}

#endif
