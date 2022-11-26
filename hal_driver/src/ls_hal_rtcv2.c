#include "ls_hal_rtcv2.h"
#include "platform.h"
#include "sdk_default_config.h"
#include <stdint.h>

HAL_StatusTypeDef HAL_RTC_Cycle_Set(uint32_t cyc_1hz, uint32_t calib_cyc, bool calib_en)
{
    RTC->CALIB = FIELD_BUILD(RTC_CALIB_CYC1HZ, cyc_1hz - 1) | FIELD_BUILD(RTC_CALIB_CYC, calib_cyc);
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_CALIB, calib_en);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RTC_Init(void)
{
    HAL_MSP_RTC_Init();
    HAL_RTC_Cycle_Set(SDK_LCLK_HZ, 0, false);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RTC_DeInit(void)
{
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_RTCEN, 0);
    HAL_MSP_RTC_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RTC_CalendarSet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time)
{
    MODIFY_REG(RTC->CTRL, RTC_CTRL_RTCEN_MASK | RTC_CTRL_TGGL_MASK, 0);
    RTC->CAL = FIELD_BUILD(RTC_CAL_YEAR, calendar_cal->year) |
               FIELD_BUILD(RTC_CAL_MON, calendar_cal->mon) |
               FIELD_BUILD(RTC_CAL_WEEK, calendar_cal->week);
    RTC->TIME = FIELD_BUILD(RTC_TIME_DATE, calendar_time->date) |
                FIELD_BUILD(RTC_TIME_HOUR, calendar_time->hour + 1) |
                FIELD_BUILD(RTC_TIME_MIN, calendar_time->min + 1) |
                FIELD_BUILD(RTC_TIME_SEC, calendar_time->sec + 1);
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_TGGL, 1);
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_RTCEN, 1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RTC_CalendarGet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time)
{
    calendar_cal->year = REG_FIELD_RD(RTC->CURCAL, RTC_CAL_YEAR);
    calendar_cal->mon = REG_FIELD_RD(RTC->CURCAL, RTC_CAL_MON);
    calendar_cal->week = REG_FIELD_RD(RTC->CURCAL, RTC_CAL_WEEK);
    calendar_time->date = REG_FIELD_RD(RTC->CURTIME, RTC_TIME_DATE);
    calendar_time->hour = REG_FIELD_RD(RTC->CURTIME, RTC_TIME_HOUR) - 1;
    calendar_time->min = REG_FIELD_RD(RTC->CURTIME, RTC_TIME_MIN) - 1;
    calendar_time->sec = REG_FIELD_RD(RTC->CURTIME, RTC_TIME_SEC) - 1;
    return HAL_OK;
}

static void clear_intr()
{
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_INTRCLR, 1);
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_INTRCLR, 0);
}

HAL_StatusTypeDef HAL_RTC_AlarmSet(calendar_cal_t *calendar_cal, calendar_time_t *calendar_time)
{
    RTC->CAL = FIELD_BUILD(RTC_CAL_YEAR, calendar_cal->year) |
               FIELD_BUILD(RTC_CAL_MON, calendar_cal->mon) |
               FIELD_BUILD(RTC_CAL_WEEK, calendar_cal->week);
    RTC->TIME = FIELD_BUILD(RTC_TIME_DATE, calendar_time->date) |
                FIELD_BUILD(RTC_TIME_HOUR, calendar_time->hour + 1) |
                FIELD_BUILD(RTC_TIME_MIN, calendar_time->min + 1) |
                FIELD_BUILD(RTC_TIME_SEC, calendar_time->sec + 1);
    clear_intr();
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_ALARMEN, 1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RTC_AlarmClear(void)
{
    REG_FIELD_WR(RTC->CTRL, RTC_CTRL_ALARMEN, 0);
    clear_intr();
    return HAL_OK;
}

__attribute__((weak)) void HAL_RTC_alarm_callback(void) {}

void HAL_RTC_IRQHandler(void)
{
    clear_intr();
    HAL_RTC_alarm_callback();
}