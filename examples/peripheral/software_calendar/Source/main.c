#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "sleep.h"
#include "calendar.h"
struct sw_calendar_alarm alarm;

void sw_calendar_alarm_callback(struct sw_calendar_alarm *param)
{
    if(&alarm == param)
    {
        static struct tm now;        
        sw_calendar_get_time(&now);
        io_toggle_pin(PA00);
        while(1);
    }
}

int main()
{
    sys_init_none();
    io_cfg_output(PA00);
    io_cfg_output(PA01);
    sw_calendar_init();
    struct tm calendar_time;
    calendar_time.tm_year = 2021-1900;
    calendar_time.tm_mon = 8-1;
    calendar_time.tm_mday = 21;
    calendar_time.tm_hour = 10;
    calendar_time.tm_min = 0;
    calendar_time.tm_sec = 0;
    sw_calendar_set_time(&calendar_time);
    calendar_time.tm_hour = 12;
    sw_calendar_set_alarm(&alarm,&calendar_time);
    while(1)
    {
        low_power_mode_sched();
    }
}
