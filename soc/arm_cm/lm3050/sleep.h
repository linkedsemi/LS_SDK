#ifndef SLEEP_H_
#define SLEEP_H_
#include "compile_flag.h"

#ifdef __cplusplus
extern "C" {
#endif

void low_power_init(void);

void deep_sleep(void);

void low_power_mode_sched(void);

void enter_deep_sleep_mode_lvl2_lvl3(bool lp2_mode);

#ifdef __cplusplus
}
#endif

#endif

