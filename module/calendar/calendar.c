#include <stdlib.h>
#include "calendar.h"
#include "sw_timer_port.h"
#include "sw_timer_int.h"
#include "common.h"
#include "cpu.h"
#define SW_CALENDAR_BASE_TIMER_PERIOD_MS ((uint64_t)11*3600*1000)

static struct sw_timer_env calendar_base_timer;
static struct sw_timer_env recent_alarm_timer;
static struct cdll alarm_list;
static time_t time_base;
static sw_timer_time_t timer_count;

__attribute__((weak)) void sw_calendar_alarm_callback(struct sw_calendar_alarm *alarm){}

static void get_current_internal_time(sw_timer_time_t *sw_timer_time,time_t *abs_time)
{
    sw_timer_time_t current = timer_time_get();
    int diff = timer_time_compare(current,timer_count);
    time_t now = PERIOD_2_MS(diff)/1000 + time_base;
    if(sw_timer_time)
    {
        *sw_timer_time = current;
    }
    if(abs_time)
    {
        *abs_time = now;
    }
}

static void recent_alarm_timer_stop()
{
    uint32_t cpu_stat = ENTER_CRITICAL();
    if(sw_timer_active(&recent_alarm_timer))
    {
        sw_timer_stop(&recent_alarm_timer);
    }
    EXIT_CRITICAL(cpu_stat);
}


static void alarm_update()
{
    struct cdll_hdr *hdr = cdll_first(&alarm_list);
    if(hdr)
    {
        struct sw_calendar_alarm *first = CONTAINER_OF(hdr,struct sw_calendar_alarm,hdr);
        sw_timer_time_t sw_timer_time;
        time_t abs_time;
        get_current_internal_time(&sw_timer_time,&abs_time);
        if(first->target - abs_time < SW_CALENDAR_BASE_TIMER_PERIOD_MS/1000 )
        {
            recent_alarm_timer_stop();
            sw_timer_time_t timer_target = timer_time_add(MS_2_PERIOD(1000*(first->target - abs_time)),sw_timer_time);
            sw_timer_target_set(&recent_alarm_timer,timer_target);
            sw_timer_insert(&recent_alarm_timer);
        }
    }else
    {
        recent_alarm_timer_stop();
    }
}

static void alarm_resched(bool callback)
{
    while(1)
    {
        struct cdll_hdr *hdr = cdll_first(&alarm_list);
        if(hdr == NULL)
        {
            break;
        }
        struct sw_calendar_alarm *alarm = CONTAINER_OF(hdr,struct sw_calendar_alarm,hdr);
        time_t abs_time;
        get_current_internal_time(NULL,&abs_time);
        if(abs_time >= alarm->target)
        {
            cdll_pop_front(&alarm_list);
            if(callback) sw_calendar_alarm_callback(alarm);
        }else
        {
            break;
        }
    }
    alarm_update();
}

static bool alarm_callback(void *param)
{
    alarm_resched(true);
    return false;
}

static bool calendar_base_timer_callback(void *param)
{
    time_base += SW_CALENDAR_BASE_TIMER_PERIOD_MS/1000;
    timer_count = sw_timer_target_get(&calendar_base_timer);
    alarm_resched(true);
    return true;
}

void sw_calendar_init()
{
    sw_timer_callback_set(&calendar_base_timer, calendar_base_timer_callback, NULL);
    sw_timer_period_set(&calendar_base_timer,MS_2_PERIOD(SW_CALENDAR_BASE_TIMER_PERIOD_MS));
    cdll_init(&alarm_list);
    sw_timer_callback_set(&recent_alarm_timer,alarm_callback,NULL);
}

static void calendar_base_timer_stop()
{
    uint32_t cpu_stat = ENTER_CRITICAL();
    if(sw_timer_active(&calendar_base_timer))
    {
        sw_timer_stop(&calendar_base_timer);
    }
    EXIT_CRITICAL(cpu_stat);
}

void sw_calendar_set_time(struct tm *timeptr)
{
    calendar_base_timer_stop();
    recent_alarm_timer_stop();
    time_base = mktime(timeptr);
    timer_count = sw_timer_start(&calendar_base_timer);

    alarm_resched(false);
}

void sw_calendar_get_time(struct tm *timeptr)
{
    time_t now;
    get_current_internal_time(NULL, &now);
    struct tm *ptr = localtime(&now);
    *timeptr = *ptr;
}

static bool alarm_compare(struct cdll_hdr *ptr,struct cdll_hdr *ref_hdr)
{
    struct sw_calendar_alarm *insert = CONTAINER_OF(ptr,struct sw_calendar_alarm, hdr);
    struct sw_calendar_alarm *ref = CONTAINER_OF(ref_hdr,struct sw_calendar_alarm, hdr);
    return insert->target>ref->target;
}

bool sw_calendar_set_alarm(struct sw_calendar_alarm *alarm,struct tm *timeptr)
{
    alarm->target = mktime(timeptr);
    time_t abs_time;
    get_current_internal_time(NULL,&abs_time);
    if(alarm->target<=abs_time)
    {
        return false;
    }
    uint32_t cpu_stat = ENTER_CRITICAL();
    cdll_insert(&alarm_list,&alarm->hdr,alarm_compare);
    alarm_update();
    EXIT_CRITICAL(cpu_stat);
    return true;
}

bool sw_calendar_remove_alarm(struct sw_calendar_alarm *alarm)
{
    if(sw_calendar_alarm_active(alarm))
    {
        uint32_t cpu_stat = ENTER_CRITICAL();
        cdll_extract(&alarm_list,&alarm->hdr);
        alarm_update();
        EXIT_CRITICAL(cpu_stat);
        return true;
    }else
    {
        return false;
    }
}

bool sw_calendar_alarm_active(struct sw_calendar_alarm *alarm)
{
    return cdll_is_elem_linked(&alarm->hdr);
}

