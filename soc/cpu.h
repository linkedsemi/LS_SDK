#ifndef CPU_H_
#define CPU_H_
#include <stdbool.h>
#include <stdint.h>

uint32_t enter_critical(void);

void exit_critical(uint32_t);

bool in_interrupt(void);

void disable_global_irq(void);

void enable_global_irq(void);

#if ROM_CODE == 1 && !defined(BOOT_ROM)
extern uint32_t (*enter_critical_fn)(void);
extern void (*exit_critical_fn)(uint32_t);
#define ENTER_CRITICAL enter_critical_fn
#define EXIT_CRITICAL exit_critical_fn
#else
#define ENTER_CRITICAL enter_critical
#define EXIT_CRITICAL exit_critical
#endif

#endif

