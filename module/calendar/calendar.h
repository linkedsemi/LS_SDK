#ifndef CALENDAR_H_
#define CALENDAR_H_
#include <stdint.h>
#include <time.h>
#include "sw_timer.h"

struct sw_calendar_alarm
{
    struct cdll_hdr hdr;
    time_t target;
};

void sw_calendar_init(void);

void sw_calendar_set_time(struct tm *timeptr);

void sw_calendar_get_time(struct tm *timeptr);

bool sw_calendar_set_alarm(struct sw_calendar_alarm *alarm,struct tm *timeptr);

bool sw_calendar_remove_alarm(struct sw_calendar_alarm *alarm);

bool sw_calendar_alarm_active(struct sw_calendar_alarm *alarm);

void sw_calendar_alarm_callback(struct sw_calendar_alarm *alarm);
#endif


