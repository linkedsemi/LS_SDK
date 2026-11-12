#include <stdint.h>
#include "reg_sec_pmu_rg.h"
#include "exception_isr.h"
#include "boot_port.h"
#include "csi_core.h"
#include "common.h"

#define STACK_SIZE (8 * 1024)

__attribute__ ((noreturn)) void main(void);

extern uint32_t exception_entry;
extern uint32_t __boot_ram_data_lma__;
extern uint32_t __boot_ram_data_start__;
extern uint32_t __boot_ram_data_end__;
extern uint32_t __boot_ram_bss_start__;
extern uint32_t __boot_ram_bss_end__;
__aligned(32) static uint8_t __stack[STACK_SIZE];
__attribute__ ((naked)) void Reset_Handler()
{
    __asm ( ".option push\n"
            ".option norelax\n"
            "la gp, __global_pointer$\n"
            ".option pop": : );
            
    uint32_t addr = SEC_PMU->SFT_CTRL[SFT_CTRL_REG_NUM_WAKEUP_ADDR];
    if(addr)
    {
        void (*func)(void) = (void *)addr;
        func();
    }else
    {
        __set_MTVEC((uint32_t)&exception_entry);
        __set_MTVT((uint32_t)interrupt_vector);
        __set_SP((uint32_t)__stack + STACK_SIZE);
        uint32_t *src = &__boot_ram_data_lma__;
        uint32_t *start = &__boot_ram_data_start__;
        uint32_t *end = &__boot_ram_data_end__;
        memcpy32(start,src,end-start);
        start = &__boot_ram_bss_start__;
        end = &__boot_ram_bss_end__;
        memset32(start,0,end-start);
        main();
    }
}