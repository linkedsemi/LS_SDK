#ifndef TIMER_WRAPPER_H_
#define TIMER_WRAPPER_H_
#include "sw_timer.h"
#include "ll_config.h"
typedef struct sw_timer_env timer_env_t;
typedef struct sw_timer_env *timer_t;

timer_t timer_create(bool (*callback)(void *),void *param,uint32_t period);

void timer_delete(timer_t timer);

uint32_t timer_period_get(timer_t timer);

void timer_period_set(timer_t timer,uint32_t period);

void timer_start(timer_t timer);

bool timer_stop(timer_t timer);

void timer_wrapper_init_sw_timer(void);

extern timer_t (*timer_create_fn)(bool (*callback)(void *),void *param,uint32_t period);
extern void (*timer_delete_fn)(timer_t timer);
extern uint32_t (*timer_period_get_fn)(timer_t timer);
extern void (*timer_period_set_fn)(timer_t timer,uint32_t period);
extern void (*timer_start_fn)(timer_t timer);
extern bool (*timer_stop_fn)(timer_t timer);
#endif

