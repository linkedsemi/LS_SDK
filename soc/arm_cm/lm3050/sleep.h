#ifndef SLEEP_H_
#define SLEEP_H_
#include "compile_flag.h"


void low_power_init(void);

void deep_sleep(void);

void low_power_mode_sched(void);

void enter_deep_sleep_mode_lvl2_lvl3(bool lp2_mode);
#endif

