#ifndef SW_TIMER_INT_H_
#define SW_TIMER_INT_H_
#include <stdint.h>
#include <stdbool.h>
#include "sw_timer.h"

sw_timer_time_t timer_time_add(sw_timer_time_t a,sw_timer_time_t b);

int timer_time_compare(sw_timer_time_t a,sw_timer_time_t b);

sw_timer_time_t timer_time_get(void);

void timer_match_set(sw_timer_time_t match);

void timer_irq_unmask(void);

void timer_irq_mask(void);

void timer_irq_clr(void);

void timer_setup(void (*isr)());


#endif