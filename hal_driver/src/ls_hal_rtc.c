#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "platform.h"
#include "ls_hal_rtc.h"
#include "ls_msp_rtc.h" 
#include "HAL_def.h"
#include "field_manipulate.h"
#include "cpu.h"
#include "ls_dbg.h"
#include "common.h"
#include "log.h"

#define H_2_S_YEAR(y) (y + 2000 - 1900)
#define S_2_H_YEAR(y) (y + 1900 - 2000)

enum
{
    WKSEL_CLOSE = 0,      // close RTC wakeup function
    WKSEL_START_NORMAL,   // set RTC wakeup function as normal timer
    WKSEL_START_WAKEUP,   // start RTC wakeup function when enter sleep
};

enum
{
    WKSCAL_divided_1 = 0,   // wakeup counter increases every 1 second
    WKSCAL_divided_2 = 1,   // wakeup counter increases every 1/2 second
    WKSCAL_divided_4 = 2,   // wakeup counter increases every 1/4 second
    WKSCAL_divided_8 = 4,   // wakeup counter increases every 1/8 second
    WKSCAL_divided_16 = 8,  // wakeup counter increases every 1/16 second
};

void HAL_RTC_IRQHandler(void)
{
    if (REG_FIELD_RD(RTC->IFM, RTC_IFM_WKTM) != 0)
    {
        REG_FIELD_WR(RTC->ICR, RTC_ICR_WKTM, 1);
        rtc_wkup_callback();
    }
}

void HAL_RTC_Init(uint8_t cksel)
{
    LS_ASSERT(cksel == RTC_CKSEL_LSE || cksel == RTC_CKSEL_LSI);
    HAL_MSP_RTC_Init();
    REG_FIELD_WR(RTC->CTRL,RTC_CTRL_CKSEL,cksel);
    REG_FIELD_WR(RTC->CTRL,RTC_CTRL_RTCEN,1);
}

void HAL_RTC_DeInit(void)
{
    HAL_MSP_RTC_DeInit();
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_RTCEN, 0);
}

void RTC_CalendarSet(calendar_cal_t *calendar_cal,calendar_time_t *calendar_time)
{
    uint32_t cpu_stat = enter_critical();
    #if SDK_LSI_USED
    save_calendar_init_val(*(uint32_t*)calendar_cal, *(uint32_t*)calendar_time);
    struct tm cur_tm;
    memset(&cur_tm, 0, sizeof(cur_tm));
    cur_tm.tm_year = H_2_S_YEAR(calendar_cal->year);
    cur_tm.tm_mon = calendar_cal->mon - 1;
    cur_tm.tm_mday = calendar_cal->date;
    cur_tm.tm_hour = calendar_time->hour;
    cur_tm.tm_min = calendar_time->min;
    cur_tm.tm_sec = calendar_time->sec;
    time_t cur_time_t = mktime(&cur_tm);
    save_calendar_raw_val((uint32_t)cur_time_t);
    save_seconds_remainder(0);
    #endif
    REG_FIELD_WR(RTC->CTRL,RTC_CTRL_RTCEN,0);

    DELAY_US(50);
    
    REG_FIELD_WR(RTC->CAL,RTC_CAL_YEAR_T,(calendar_cal->year/10)%100);
    REG_FIELD_WR(RTC->CAL,RTC_CAL_YEAR_U,(calendar_cal->year%100)%10);
    REG_FIELD_WR(RTC->CAL,RTC_CAL_MON_T,calendar_cal->mon/10);
    REG_FIELD_WR(RTC->CAL,RTC_CAL_MON_U,calendar_cal->mon%10);
    REG_FIELD_WR(RTC->CAL,RTC_CAL_DATE_T,calendar_cal->date/10);
    REG_FIELD_WR(RTC->CAL,RTC_CAL_DATE_U,calendar_cal->date%10);
    REG_FIELD_WR(RTC->TIME,RTC_TIME_WEEK,calendar_time->week);
    REG_FIELD_WR(RTC->TIME,RTC_TIME_HOUR_T,calendar_time->hour/10);
    REG_FIELD_WR(RTC->TIME,RTC_TIME_HOUR_U,calendar_time->hour%10);
    REG_FIELD_WR(RTC->TIME,RTC_TIME_MIN_T,calendar_time->min/10);
    REG_FIELD_WR(RTC->TIME,RTC_TIME_MIN_U,calendar_time->min%10);
    REG_FIELD_WR(RTC->TIME,RTC_TIME_SEC_T,calendar_time->sec/10);
    REG_FIELD_WR(RTC->TIME,RTC_TIME_SEC_U,calendar_time->sec%10);

    REG_FIELD_WR(RTC->CTRL,RTC_CTRL_RTCEN,1);
    exit_critical(cpu_stat);
}

HAL_StatusTypeDef RTC_CalendarGet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time)
{
    HAL_StatusTypeDef result = HAL_OK;
    REG_FIELD_WR(RTC->BKEN, RTC_BKEN_BKEN, 1); // set bken to update data immediately
    DELAY_US(1);
    #if SDK_LSI_USED
    calendar_cal_t prev_cal;
    calendar_time_t prev_time;
    uint32_t prev_raw_val;
    load_calendar_init_val((uint32_t*)&prev_cal, (uint32_t*)&prev_time);
    load_calendar_raw_val(&prev_raw_val);
    #endif

    calendar_cal->year  = REG_FIELD_RD(RTC->CAL,RTC_CAL_YEAR_T)*10 + REG_FIELD_RD(RTC->CAL,RTC_CAL_YEAR_U);
    calendar_cal->mon   = REG_FIELD_RD(RTC->CAL,RTC_CAL_MON_T)*10 + REG_FIELD_RD(RTC->CAL,RTC_CAL_MON_U); 
    calendar_cal->date  = REG_FIELD_RD(RTC->CAL,RTC_CAL_DATE_T)*10 + REG_FIELD_RD(RTC->CAL,RTC_CAL_DATE_U);     
    calendar_time->week = REG_FIELD_RD(RTC->TIME,RTC_TIME_WEEK);
    calendar_time->hour = REG_FIELD_RD(RTC->TIME,RTC_TIME_HOUR_T)*10 + REG_FIELD_RD(RTC->TIME,RTC_TIME_HOUR_U); 
    calendar_time->min  = REG_FIELD_RD(RTC->TIME,RTC_TIME_MIN_T)*10 + REG_FIELD_RD(RTC->TIME,RTC_TIME_MIN_U);     
    calendar_time->sec  = REG_FIELD_RD(RTC->TIME,RTC_TIME_SEC_T)*10 + REG_FIELD_RD(RTC->TIME,RTC_TIME_SEC_U);
    #if SDK_LSI_USED
    struct tm prev_tm;
    memset(&prev_tm, 0, sizeof(prev_tm));
    prev_tm.tm_year = H_2_S_YEAR(prev_cal.year);
    prev_tm.tm_mon = prev_cal.mon - 1;
    prev_tm.tm_mday = prev_cal.date;
    prev_tm.tm_hour = prev_time.hour;
    prev_tm.tm_min = prev_time.min;
    prev_tm.tm_sec = prev_time.sec;
    time_t prev_time_t = mktime(&prev_tm);

    struct tm cur_tm;
    memset(&cur_tm, 0, sizeof(cur_tm));
    cur_tm.tm_year = H_2_S_YEAR(calendar_cal->year);
    cur_tm.tm_mon = calendar_cal->mon - 1;
    cur_tm.tm_mday = calendar_cal->date;
    cur_tm.tm_hour = calendar_time->hour;
    cur_tm.tm_min = calendar_time->min;
    cur_tm.tm_sec = calendar_time->sec;
    time_t cur_time_t = mktime(&cur_tm);
    save_calendar_raw_val((uint32_t)cur_time_t);

    uint32_t delta_seconds_counting = (uint32_t)(cur_time_t - prev_raw_val);
    uint64_t delta_seconds_numerator = (uint64_t)delta_seconds_counting * 32768 * get_lsi_cnt_val();
    uint32_t delta_seconds_remainder = __div64_32(&delta_seconds_numerator, LSI_CNT_CYCLES * 1000000);
    delta_seconds_counting = (uint32_t)delta_seconds_numerator;
    uint32_t prev_remainder;
    load_seconds_remainder(&prev_remainder);
    prev_remainder += delta_seconds_remainder;
    if (prev_remainder >= LSI_CNT_CYCLES * 1000000)
    {
        prev_remainder -= LSI_CNT_CYCLES * 1000000;
        delta_seconds_counting++;
    }
    save_seconds_remainder(prev_remainder);
    cur_time_t = prev_time_t + delta_seconds_counting;
    struct tm* tm_ptr = localtime(&cur_time_t);
    calendar_cal->year = S_2_H_YEAR(tm_ptr->tm_year);
    calendar_cal->mon = tm_ptr->tm_mon + 1;
    calendar_cal->date = tm_ptr->tm_mday;
    calendar_time->hour = tm_ptr->tm_hour;
    calendar_time->min = tm_ptr->tm_min;
    calendar_time->sec = tm_ptr->tm_sec;
    calendar_time->week = tm_ptr->tm_wday == 0 ? 7 : tm_ptr->tm_wday; // convert Sunday from 0 to 7
    save_calendar_init_val(*(uint32_t*)calendar_cal, *(uint32_t*)calendar_time);
    #endif
    return result;
}

void RTC_wkuptime_set(uint32_t t_ms)
{
    LS_ASSERT(t_ms > 0);
    RTC_wkuptime_clr();
    DELAY_US(50);
    REG_FIELD_WR(RTC->WKUP, RTC_WKUP_WKSCAL, WKSCAL_divided_16);
    #if SDK_LSI_USED
    uint64_t numerator = (uint64_t)t_ms * 16 * 1000 * LSI_CNT_CYCLES;
    uint32_t denominator = 32768 * get_lsi_cnt_val();
    uint32_t remainder = __div64_32(&numerator, denominator);
    uint32_t quotient = (uint32_t)numerator;
    if (remainder >= denominator / 2)
    {
        quotient++;
    }
//    LOG_I("t_ms: %d, quotient: %d, remainder: %d, lsi_cnt_val %d", t_ms, quotient, remainder, get_lsi_cnt_val());
    REG_FIELD_WR(RTC->WKUP, RTC_WKUP_WKCAL, quotient);
    #else
    REG_FIELD_WR(RTC->WKUP, RTC_WKUP_WKCAL, (t_ms * 16)/1000);
    #endif
    REG_FIELD_WR(RTC->WKUP, RTC_WKUP_WKSEL, WKSEL_START_NORMAL);
    REG_FIELD_WR(RTC->IER, RTC_IER_WKTM, 1);
    // REG_FIELD_WR(RTC->CTRL, RTC_CTRL_RTCEN, 1);
}

void RTC_wkuptime_clr(void)
{
    REG_FIELD_WR(RTC->IDR, RTC_IER_WKTM, 1);
    REG_FIELD_WR(RTC->WKUP, RTC_WKUP_WKSCAL, 0);
    REG_FIELD_WR(RTC->WKUP, RTC_WKUP_WKCAL, 0);
    REG_FIELD_WR(RTC->WKUP, RTC_WKUP_WKSEL, 0);
}
__attribute__((weak)) void rtc_wkup_callback(void){}
