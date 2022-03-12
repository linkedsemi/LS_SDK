#include "common.h"
#include "csi_core.h"
#include "exception_isr.h"
void SystemInit(void);
void main(void) __attribute__ ((noreturn));
extern uint32_t __data_lma__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __StackTop;
extern uint32_t exception_entry;

__attribute__ ((naked)) void Reset_Handler()
{
    __asm ( ".option push\n"
            ".option norelax\n"
            "la gp, __global_pointer$\n"
            ".option pop": : );
    __set_MTVEC((uint32_t)&exception_entry);
    __set_MTVT((uint32_t)interrupt_vector);
    __set_SP((uint32_t)&__StackTop);
    SystemInit();
    extern uint32_t __bss_start__;
    extern uint32_t __bss_end__;
    uint32_t *start = &__bss_start__;
    uint32_t *end = &__bss_end__;
    memset32(start,0,end-start);
    main();
}
