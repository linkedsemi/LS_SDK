#ifndef SW_TIMER_H_
#define SW_TIMER_H_
#include <stdint.h>
#include <stdbool.h>
#include "circular_doubly_linked_list.h"
#include "sw_timer_port.h"

struct sw_timer_env
{
	struct cdll_hdr hdr;
	bool (*callback)(void *);
	void *cb_param;
	sw_timer_time_t period;
	sw_timer_time_t target;
};

void sw_timer_module_init(void);

void sw_timer_module_reset(void);

void sw_timer_callback_set(struct sw_timer_env *timer,bool (*func)(void *),void *param);

void sw_timer_period_set(struct sw_timer_env *timer,sw_timer_time_t period);

sw_timer_time_t sw_timer_period_get(struct sw_timer_env *timer);

void sw_timer_target_set(struct sw_timer_env *timer,sw_timer_time_t target);

sw_timer_time_t sw_timer_target_get(struct sw_timer_env *timer);

void sw_timer_insert(struct sw_timer_env *timer);

sw_timer_time_t sw_timer_start(struct sw_timer_env *timer);

void sw_timer_stop(struct sw_timer_env *timer);

bool sw_timer_active(struct sw_timer_env *timer);

struct sw_timer_env *sw_timer_list_pick(void);

void sw_timer_update(void);

#endif
