/*
 * Copyright (C) 2018-2020 Alibaba Group Holding Limited
 */
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "cpu.h"
#include "ls_sys.h"
#include "platform.h"
#include "tmall_mesh_ctl.h"
#include "tmall_curtain_cfg.h"
#include "ls_sig_mesh.h"
#include "slist.h"
#include "builtin_timer.h"
#include "genie_time_v2.h"
#include "systick.h"
#include "ls_hal_flash.h"
#include "crc16.h"

#define u16_t uint16_t
#define GFI_MESH_VND_TIMER 4
#define BT_MESH_ADDR_TMALL_GENIE 0xf000
#define APP_MESH_VENDOR_MARK 0x000000ff
#define GENIE_TIME_STORE_OFFSET 0x7B000
#define GENIE_TIMER_BUFFER_LENGHT 1024
#define TIMER_V2_CRC_INIT_VAL (0x5555)
#define TIMER_V2_CRC_LENGTH 2

#define timer_v2_crc16calc (crc16ccitt)
static inline uint8_t is_leap_year(uint16_t year);
static genie_time_data_t genie_time_data;
static genie_time_ctx_t genie_time_ctx;
static utc_time_t local_time = {0};
static struct builtin_timer *sw_timer_sec = NULL;
static uint8_t timeout_report_status_tid =0x80;
extern struct mesh_model_info model_env;
extern uint16_t provisioner_unicast_addr;
extern uint16_t gatt_mesh_src_addr;

typedef int (*transport_result_cb)(void *p_params);
typedef struct _genie_transport_payload_s
{
    uint8_t element_id;
    uint8_t opid;
    uint8_t tid;
    uint8_t retry_cnt;
    uint16_t dst_addr;
    uint8_t *p_payload;
    uint16_t payload_len;
    transport_result_cb result_cb;
} genie_transport_payload_param_t;

typedef struct _genie_transport_model_param_s
{
    void *p_elem;
    void *p_model; //It is current model
    transport_result_cb result_cb;
    uint8_t retry;
    uint8_t opid;
    uint8_t tid;
    uint8_t ttl;
    uint8_t xmit;
    uint16_t app_idx;
    uint16_t src_addr;
    uint16_t dst_addr;
    uint16_t retry_period;
    uint16_t len;
    uint8_t *data;
} genie_transport_model_param_t;

typedef struct _genie_time_event_s
{
    uint8_t element_id;
    uint8_t count;
    genie_time_attr_item_t items[GT_TIMER_ATTR_OP_MAX];
} genie_time_event_t;

static inline uint32_t UTC2unix(utc_time_t *utc_time)
{
    uint32_t days;
    uint16_t g_noleap_daysbeforemonth[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

    days = (utc_time->year - 1970) * 365;
    days += (utc_time->year - 1969) >> 2;

    days += g_noleap_daysbeforemonth[utc_time->month];

    if (utc_time->month >= 2 && is_leap_year(utc_time->year))
    {
        days++;
    }

    days += utc_time->day - 1;

    return ((days * 24 + utc_time->hour) * 60 + utc_time->minutes) * 60 + utc_time->seconds;
}

static inline utc_time_t unix2UTC(uint32_t unix_time)
{
    utc_time_t utc;

    uint16_t g_noleap_daysbeforemonth[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    uint32_t epoch;
    uint32_t jdn;
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int sec;
    int weekday;

    epoch = unix_time;

    jdn = epoch / DAY;
    epoch -= DAY * jdn;

    weekday = (jdn + 4) % 7; // 1970/1/1 is thursday

    hour = epoch / HOUR;
    epoch -= HOUR * hour;

    minutes = epoch / MINU;
    epoch -= MINU * minutes;

    sec = epoch;

    year = jdn / (4 * 365 + 1);  /* Number of 4-years periods since the epoch */
    jdn -= year * (4 * 365 + 1); /* Remaining days */
    year <<= 2;                  /* Years since the epoch */

    /* Then we will brute force the next 0-3 years */
    bool leapyear;
    int tmp;

    for (;;)
    {
        /* Is this year a leap year (we'll need this later too) */
        leapyear = is_leap_year(year + 1970);

        /* Get the number of days in the year */
        tmp = (leapyear ? 366 : 365);

        /* Do we have that many days? */
        if (jdn >= tmp)
        {
            /* Yes.. bump up the year */
            year++;
            jdn -= tmp;
        }
        else
        {
            /* Nope... then go handle months */
            break;
        }
    }

    /* At this point, value has the year and days has number days into this year */
    year += 1970;

    /* Handle the month (zero based) */
    int min = 0;
    int max = 11;
    int value = 0;

    do
    {
        /* Get the midpoint */
        value = (min + max) >> 1;

        /* Get the number of days that occurred before the beginning of the month
         * following the midpoint.
         */
        tmp = g_noleap_daysbeforemonth[value + 1];

        if (value + 1 >= 2 && leapyear)
        {
            tmp++;
        }

        /* Does the number of days before this month that equal or exceed the
         * number of days we have remaining?
         */
        if (tmp > jdn)
        {
            /* Yes.. then the month we want is somewhere from 'min' and to the
             * midpoint, 'value'.  Could it be the midpoint?
             */
            tmp = g_noleap_daysbeforemonth[value];

            if (value >= 2 && leapyear)
            {
                tmp++;
            }

            if (tmp > jdn)
            {
                /* No... The one we want is somewhere between min and value-1 */
                max = value - 1;
            }
            else
            {
                /* Yes.. 'value' contains the month that we want */
                break;
            }
        }
        else
        {
            /* No... The one we want is somwhere between value+1 and max */
            min = value + 1;
        }

        /* If we break out of the loop because min == max, then we want value
         * to be equal to min == max.
         */
        value = min;
    } while (min < max);

    /* The selected month number is in value. Subtract the number of days in the
     * selected month
     */
    tmp = g_noleap_daysbeforemonth[value];

    if (value >= 2 && leapyear)
    {
        tmp++;
    }

    jdn -= tmp;

    /* At this point, value has the month into this year (zero based) and days has
     * number of days into this month (zero based)
     */
    month = value; // zero based
    day = jdn + 1; // one based

    utc.year = year;
    utc.month = month;
    utc.day = day;
    utc.weekday = weekday;
    utc.hour = hour;
    utc.minutes = minutes;
    utc.seconds = sec;

    return utc;
}

static inline uint8_t next_weekday_diff_get(uint8_t weekday_now, uint8_t schedule)
{
    uint16_t schedule_tmp = 0;
    uint8_t day_diff = 0;

    if (weekday_now == 0)
    {
        weekday_now = 7;
    }

    schedule_tmp = ((schedule | ((uint16_t)schedule << 7)) >> (weekday_now - 1)) & 0x7f;

    while (day_diff < 7)
    {
        if ((schedule_tmp >> day_diff) & 0x0001)
        {
            break;
        }

        day_diff++;
    }
    // //LOG_I("day_diff:%d", day_diff);
    return day_diff;
}

#if 0
static inline uint8_t next_monthday_diff_get(uint8_t monthday_now, uint32_t schedule)
{
    uint32_t schedule_tmp = 0;
    uint8_t day_diff = 0;

    //LOG_I("month_now:%d, schedule:0x%08x", monthday_now, schedule);
    if (monthday_now > 31)
    {
        monthday_now = 31;
    }

    schedule_tmp = ((schedule | (schedule << 31)) >> (monthday_now - 1)) & 0x7fffffff;
    //LOG_I("schedule_tmp:0x%08x", schedule_tmp);

    while (day_diff < 31)
    {
        if ((schedule_tmp >> day_diff) & 0x00000001)
        {
            break;
        }

        day_diff++;
    }
    //LOG_I("day_diff:%d", day_diff);
    return day_diff;
}

static inline uint8_t next_monthday(uint8_t monthday_now)
{
    uint8_t monthday_next = 0;
    uint8_t month_days_list[12] = {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31,
    };

    if (is_leap_year(local_time.year))
    {
        month_days_list[1] = 29;
    }

    monthday_next = (monthday_now + 1);
    if (monthday_next > month_days_list[local_time.month])
    {
        monthday_next = 1;
    }

    return monthday_next;
}
#endif

static inline uint8_t next_weekday(uint8_t weekday_now)
{
    return (weekday_now + 1) % 7;
}

#if 0
static inline uint8_t is_weekday_match(uint8_t weekday_now, uint8_t schedule)
{
    uint8_t weekday_mask = weekday_now ? (uint8_t)(1 << (weekday_now - 1)) : (uint8_t)(1 << 6);
    return (weekday_mask == (schedule & weekday_mask));
}
#endif
static inline uint8_t is_leap_year(uint16_t year)
{
    if (((year % 4) == 0) && ((year % 100) != 0))
    {
        return 1;
    }
    else if ((year % 400) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static inline void month_update()
{
    local_time.month++;

    if (local_time.month >= 12)
    {
        local_time.month = 0;
        local_time.year++;
    }
}

static inline void days_update()
{
    uint8_t month_days_list[12] = {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31,
    };

    local_time.day++;

    if (is_leap_year(local_time.year))
    {
        month_days_list[1] = 29;
    }

    uint8_t month_day = month_days_list[local_time.month];

    if (local_time.day > month_day)
    {
        local_time.day = 0;
        month_update();
    }

    local_time.weekday = (local_time.weekday + 1) % 7;
}

static inline void hours_update()
{
    local_time.hour++;

    if (local_time.hour == 24)
    {
        local_time.hour = 0;
        days_update();
    }
}

static inline void minutes_update()
{
    local_time.minutes++;

    if (local_time.minutes == 60)
    {
        local_time.minutes = 0;
        hours_update();
    }
}

static inline void seconds_update()
{
    local_time.seconds++;

    if (local_time.seconds == 60)
    {
        local_time.seconds = 0;
        minutes_update();
    }
}

static int genie_time_sync_conf_get(uint16_t *period_time, uint8_t *retry_delay, uint8_t *retry_times)
{
    *period_time = genie_time_data.time_sync_config.period_time;
    *retry_delay = genie_time_data.time_sync_config.retry_delay;
    *retry_times = genie_time_data.time_sync_config.retry_times;
    return 0;
}

static int genie_time_sync_conf_set(uint16_t period_time, uint8_t retry_delay, uint8_t retry_times)
{
    //LOG_I("timing sync set, period_time:%d, retry_delay:%d, retry_times:%d",
    //       period_time, retry_delay, retry_times);

    if (!period_time || !retry_delay || !retry_times)
    {
        return -GT_E_PARAM;
    }

    uint32_t cpu_stat = enter_critical();
    genie_time_data.time_sync_config.period_time = period_time;
    genie_time_data.time_sync_config.retry_delay = retry_delay;
    genie_time_data.time_sync_config.retry_times = retry_times;
    genie_time_ctx.time_sync_unix_time_match = genie_time_ctx.unix_time + period_time * MINU;
    genie_time_ctx.time_sync_retry_times = retry_times;
    exit_critical(cpu_stat);
   // //LOG_I("time_sync_unix_time_match:%u, cur_unix_time:%u, diff:%u", genie_time_ctx.time_sync_unix_time_match, genie_time_ctx.unix_time, period_time * MINU);
    return 0;
}

utc_time_t genie_time_local_time_get()
{
    return local_time;
}

void genie_time_local_time_show()
{
    LOG_I("localtime: %4d/%2d/%2d %2d:%2d:%d weekday: %2d timezone: %04d",
                  local_time.year, local_time.month + 1, local_time.day,
                  local_time.hour, local_time.minutes, local_time.seconds,
                  local_time.weekday, genie_time_data.timezone);
}

static int genie_time_local_time_update(uint32_t unix_time)
{
    static uint32_t last_time_ms = 0;
    uint32_t cur_time_ms = 0;
    uint8_t rand_1byte = 0;

    if (!genie_time_ctx.init)
    {
        return -GT_E_NOT_INIT;
    }

    genie_time_ctx.update = 1;
    genie_time_ctx.unix_time = unix_time;
    local_time = unix2UTC(unix_time);

    //LOG_I("update unix_time: %u", unix_time);
    //LOG_I("localtime: %4d/%2d/%2d %2d:%2d:%d weekday: %2d",
    //       local_time.year, local_time.month + 1, local_time.day,
    //       local_time.hour, local_time.minutes, local_time.seconds,
    //       local_time.weekday);
     //LOG_I("unix_time revert: %u", UTC2unix(&local_time));

     uint32_t cpu_stat = enter_critical();
    genie_time_ctx.time_sync_tmms = unix_time;
    genie_time_ctx.time_sync_unix_time_match = genie_time_ctx.unix_time + genie_time_data.time_sync_config.period_time * MINU;
    genie_time_ctx.time_sync_retry_times = genie_time_data.time_sync_config.retry_times;
    exit_critical(cpu_stat);
    ////LOG_I("time_sync_unix_time_match:%u, cur_unix_time:%u, diff:%u", genie_time_ctx.time_sync_unix_time_match,
    //               genie_time_ctx.unix_time, genie_time_data.time_sync_config.period_time * MINU);

    cur_time_ms = systick_get_value();
    if ((genie_time_ctx.boot_report_s == 0) && (cur_time_ms > last_time_ms) && ((cur_time_ms - last_time_ms) >= 60000))
    {
        rand_1byte = rand()%255;
        genie_time_ctx.boot_report_s = GT_BOOT_REPORT_MIN + (30 * rand_1byte / 255);
        //LOG_I("boot_report_s:%d", genie_time_ctx.boot_report_s);
    }
    last_time_ms = cur_time_ms;

    return 0;
}

uint32_t genie_time_unix_time_get()
{
    return genie_time_ctx.unix_time;
}

static int8_t genie_time_timezone_get()
{
    return genie_time_data.timezone;
}

static int genie_time_timezone_update(int8_t timezone)
{
    //LOG_I("timezone update %d", timezone);

    if (timezone < -12 || timezone > 14)
    {
        return -GT_E_PARAM;
    }

    if (!genie_time_ctx.init)
    {
        return -GT_E_NOT_INIT;
    }

    genie_time_data.timezone = timezone;
    //LOG_I("update timezone: %d", genie_time_data.timezone);
    return 0;
}

static uint8_t genie_time_succcode_get(void)
{
    uint32_t sync_period_time = genie_time_data.time_sync_config.period_time * MINU;
    uint32_t diff = 0;

    if (genie_time_ctx.unix_time >= genie_time_ctx.time_sync_tmms)
    {
        diff = genie_time_ctx.unix_time - genie_time_ctx.time_sync_tmms;
        if (diff > sync_period_time)
        {
            //LOG_I("time sync diff %u out of %u", diff, sync_period_time);
            return GT_CODE_SUCCESS_YAW;
        }
        else
        {
            return GT_CODE_SUCCESS;
        }
    }
    return GT_CODE_SUCCESS;
}

static uint8_t genie_time_errcode_convert(int err)
{
    uint8_t errcode = 0;

    if (err == -GT_E_NOT_INIT)
    {
        errcode = GT_CODE_NOT_SUP_ATTR_OP;
    }
    else if ((err == -GT_E_UNIX_TIME_NOT_SET))
    {
        if (sys_slist_is_empty(&(genie_time_ctx.timer_list_active)))
        {
            errcode = GT_CODE_NOT_UNIX_TIME;
        }
        else
        {
            errcode = GT_CODE_NOT_UNIX_TIME_ABN;
        }
    }
    else if (err == -GT_E_ATTR_PARAM)
    {
        errcode = GT_CODE_NOT_SUP_ATTR_PARAM;
    }
    else if (err == -GT_E_UNIX_TIME)
    {
        errcode = GT_CODE_TIMER_TIME_INVALID;
    }
    else if (err == -GT_E_INDEX)
    {
        errcode = GT_CODE_TIMER_INDEX_INVALID;
    }
    else if (err == -GT_E_NORESOURCE)
    {
        errcode = GT_CODE_TIMER_FULL;
    }
    else if (err == -GT_E_PARAM)
    {
        errcode = GT_CODE_TIMER_PARAM_INVALID;
    }
    else
    {
        errcode = GT_CODE_SUCCESS;
    }

    //LOG_I("err:%d, errcode:0x%02x", err, errcode);
    return errcode;
}

static int genie_time_send_payload(genie_transport_payload_param_t *payload_param, uint16_t app_idx)
{
    if (payload_param == NULL || payload_param->p_payload == NULL)
    {
        //LOG_I("invalid param");
        return -1;
    }

   struct model_send_info send_info;
    send_info.opcode = payload_param->opid | (0x000001a8<<8);
    send_info.ModelHandle = model_env.info[1].model_lid;
    send_info.app_key_lid = model_env.app_key_lid;
    send_info.dest_addr = payload_param->dst_addr;
    send_info.info[0]=payload_param->tid;
    send_info.len = payload_param->payload_len+1;
    memcpy(&send_info.info[1], payload_param->p_payload, payload_param->payload_len);
    //LOG_I("send_payload,dest_addr=0x%x,len=%d,opcode=0x%x",send_info.dest_addr,payload_param->payload_len,send_info.opcode);
    //LOG_HEX(send_info.info,send_info.len);
    model_send_info_handler(&send_info);
    return 0;
}

static int genie_time_timer_errcode_status(uint8_t elem_id, uint16_t attr_type, uint8_t err_code, uint8_t index, uint8_t tid, uint16_t app_idx)
{
    uint8_t len = 0;
    uint8_t payload[8] = {0};
    genie_transport_payload_param_t transport_payload_param;

    memset(payload, 0x0, sizeof(payload));
    payload[len++] = attr_type & 0xff;
    payload[len++] = (attr_type >> 8) & 0xff;
    payload[len++] = err_code;
    if (index > 0)
    {
        payload[len++] = index;
    }

    memset(&transport_payload_param, 0, sizeof(genie_transport_payload_param_t));
    transport_payload_param.opid = (uint8_t)(APP_MESH_VENDOR_STATUS & APP_MESH_VENDOR_MARK);
    transport_payload_param.element_id = elem_id;
    transport_payload_param.tid = tid;
    transport_payload_param.p_payload = payload;
    transport_payload_param.payload_len = len;
    transport_payload_param.retry_cnt = 1;
    transport_payload_param.dst_addr = ((gatt_mesh_src_addr==0xffff)?provisioner_unicast_addr:gatt_mesh_src_addr);

    return genie_time_send_payload(&transport_payload_param, app_idx);
}

static void genie_time_request_unix_time(void)
{
    int len = 0;
    uint8_t payload[8] = {0};
    genie_transport_payload_param_t transport_payload_param;

    memset(payload, 0x0, sizeof(payload));
    payload[len++] = GT_UNIX_TIME_SETTING_T & 0xff;
    payload[len++] = (GT_UNIX_TIME_SETTING_T >> 8) & 0xff;

    memset(&transport_payload_param, 0, sizeof(genie_transport_payload_param_t));
    transport_payload_param.opid = (APP_MESH_VENDOR_INDICATE_TG & APP_MESH_VENDOR_MARK);
    transport_payload_param.p_payload = payload;
    transport_payload_param.payload_len = len;
    transport_payload_param.retry_cnt = 1;
    transport_payload_param.dst_addr = BT_MESH_ADDR_TMALL_GENIE;

    genie_time_send_payload(&transport_payload_param, 0);
}

static int genie_time_getting_status(uint8_t elem_id, uint8_t tid, uint16_t app_idx, u16_t attr_type)
{
    u16_t len = 0;
    uint8_t payload[16] = {0};
    genie_transport_payload_param_t transport_payload_param;

    memset(payload, 0x0, sizeof(payload));
    switch (attr_type)
    {
    case GT_UNIX_TIME_SETTING_T:
    {
        uint32_t unix_time = genie_time_unix_time_get();

        payload[len++] = GT_UNIX_TIME_SETTING_T & 0xff;
        payload[len++] = (GT_UNIX_TIME_SETTING_T >> 8) & 0xff;
        payload[len++] = (uint8_t)(unix_time & 0xff);
        payload[len++] = (uint8_t)((unix_time >> 8) & 0xff);
        payload[len++] = (uint8_t)((unix_time >> 16) & 0xff);
        payload[len++] = (uint8_t)((unix_time >> 24) & 0xff);
    }
    break;
    case GT_TIMEZONE_SETTING_T:
    {
        int8_t timezone = genie_time_timezone_get();
        payload[len++] = GT_TIMEZONE_SETTING_T & 0xff;
        payload[len++] = (GT_TIMEZONE_SETTING_T >> 8) & 0xff;
        payload[len++] = timezone;
    }
    break;
    case GT_TIME_SYNC_T:
    {
        u16_t period_time = 0;
        uint8_t retry_delay = 0;
        uint8_t retry_times = 0;

        genie_time_sync_conf_get(&period_time, &retry_delay, &retry_times);
        payload[len++] = GT_TIME_SYNC_T & 0xff;
        payload[len++] = (GT_TIME_SYNC_T >> 8) & 0xff;
        payload[len++] = period_time & 0xff;
        payload[len++] = (period_time >> 8) & 0xff;
        payload[len++] = retry_delay;
        payload[len++] = retry_times;
    }
    break;

    default:
        return -1;
    }

    memset(&transport_payload_param, 0, sizeof(genie_transport_payload_param_t));
    transport_payload_param.opid = (uint8_t)(APP_MESH_VENDOR_STATUS & APP_MESH_VENDOR_MARK);
    transport_payload_param.element_id = elem_id;
    transport_payload_param.tid = tid;
    transport_payload_param.p_payload = payload;
    transport_payload_param.payload_len = len;
    transport_payload_param.retry_cnt = 1;
    transport_payload_param.dst_addr = ((gatt_mesh_src_addr==0xffff)?provisioner_unicast_addr:gatt_mesh_src_addr);

    return genie_time_send_payload(&transport_payload_param, app_idx);
}

static int genie_time_setting_event(uint8_t elem_id, genie_transport_model_param_t *p_msg)
{
    int ret = 0;
    uint8_t errcode = 0;
    uint8_t *pmsg = p_msg->data;
    uint16_t attr_type;
    uint16_t msg_len = p_msg->len;
    static uint8_t last_tid = 0;

    if ((p_msg->tid == last_tid) && (elem_id > 0))
    {
        //LOG_I("ignore repeat msg tid:%d %d elem_id:%d", p_msg->tid, last_tid, elem_id);
        return ret;
    }

    memcpy((uint8_t *)&attr_type,(pmsg+1),2);
    msg_len -= 2;
    pmsg+=3;
    last_tid = p_msg->tid;

    switch (attr_type)
    {
    case GT_UNIX_TIME_SETTING_T:
    {
        if (msg_len >= 4)
        {
            uint32_t unix_time = 0;
            int8_t timezone = 0;
            unix_time = (pmsg[0]) | (pmsg[1] << 8) | (pmsg[2] << 16) | (pmsg[3] << 24);
            pmsg += 4;
            msg_len -= 4;
            ret = genie_time_local_time_update(unix_time);
            if (msg_len >= 1)
            {
                timezone = *pmsg++;
                msg_len += 1;
                ret = genie_time_timezone_update(timezone);
            }
        }
        else
        {
            ret = -GT_E_PARAM;
        }
    }
    break;
    case GT_TIMEZONE_SETTING_T:
    {
        if (msg_len >= 1)
        {
            int8_t timezone = *pmsg++;
            msg_len += 1;
            ret = genie_time_timezone_update(timezone);
        }
        else
        {
            ret = -GT_E_PARAM;
        }
    }
    break;
    case GT_TIME_SYNC_T:
    {
        if (msg_len >= 4)
        {
            uint16_t period_time = (pmsg[0]) | (pmsg[1] << 8);
            pmsg += 2;
            msg_len += 2;
            uint8_t retry_delay = *pmsg++;
            uint8_t retry_times = *pmsg++;
            msg_len += 2;
            ret = genie_time_sync_conf_set(period_time, retry_delay, retry_times);
        }
        else
        {
            ret = -GT_E_PARAM;
        }
    }
    break;

    default:
        return -1;
    }

    if (p_msg->opid == (APP_MESH_VENDOR_SET_ACK & APP_MESH_VENDOR_MARK))
    {
        if (ret)
        {
            errcode = genie_time_errcode_convert(ret);
        }

        if (errcode != 0)
        {
            genie_time_timer_errcode_status(elem_id, attr_type, errcode, 0, p_msg->tid, p_msg->app_idx);
        }
        else
        {
            genie_time_getting_status(elem_id, p_msg->tid, p_msg->app_idx, attr_type);
        }
    }

    return ret;
}

int genie_time_data_erase()
{
#ifdef GT_TIMER_STORE

    for (uint8_t i = 0; i < 4; i++)
    {
        hal_flash_page_erase(i*FLASH_PAGE_SIZE+GENIE_TIME_STORE_OFFSET);
    }
    return 0;
#else
    return 0;
#endif
}

static void genie_time_data_flash_write(const uint32_t offset, const uint8_t* const data)
{
   static uint16_t cal_crc=0;
   static uint16_t check_crc=0;
   static uint16_t length_u16=0;
   static uint8_t tmp_data[GENIE_TIMER_BUFFER_LENGHT]={0};
   static uint32_t flash_offset=0;
    do
    {
       flash_offset = offset;
       length_u16=sizeof(genie_time_data_t);
       if (length_u16>=GENIE_TIMER_BUFFER_LENGHT)
       {
           //LOG_I("genie timer buffer overflow >1024bytes");
           return;
       }
       memcpy(tmp_data,data,length_u16);
       cal_crc = timer_v2_crc16calc(TIMER_V2_CRC_INIT_VAL,(uint8_t *)&tmp_data, length_u16);
       memcpy(&tmp_data[GENIE_TIMER_BUFFER_LENGHT-TIMER_V2_CRC_LENGTH],(uint8_t *)&cal_crc,TIMER_V2_CRC_LENGTH);
//       uint32_t cpu_stat = enter_critical();
       for (uint8_t i = 0; i < 4; i++)
       {
          hal_flash_page_erase(flash_offset);
          hal_flash_page_program(flash_offset, &tmp_data[i*FLASH_PAGE_SIZE], FLASH_PAGE_SIZE);
          flash_offset += FLASH_PAGE_SIZE;
       }
       memset(tmp_data,0,GENIE_TIMER_BUFFER_LENGHT);
       flash_offset= offset;
       hal_flash_fast_read(flash_offset, tmp_data, GENIE_TIMER_BUFFER_LENGHT);
//       exit_critical(cpu_stat);
       check_crc =  timer_v2_crc16calc(TIMER_V2_CRC_INIT_VAL,(uint8_t *)&tmp_data, length_u16);
       cal_crc=0;
       memcpy((uint8_t *)&cal_crc,&tmp_data[GENIE_TIMER_BUFFER_LENGHT-TIMER_V2_CRC_LENGTH],TIMER_V2_CRC_LENGTH);
      if (check_crc == cal_crc)
      {
         break;
      }
    }while(1);
}

static int genie_time_data_save()
{
#ifdef GT_TIMER_STORE
    genie_time_data_flash_write(GENIE_TIME_STORE_OFFSET,(uint8_t *)&genie_time_data);
    return 0;
#else
    return 0;
#endif
}

static int genie_time_data_restore()
{
   static uint8_t tmp_data[GENIE_TIMER_BUFFER_LENGHT]={0};
   static uint32_t cal_crc=0;
   static uint32_t check_crc=0;
   static uint16_t length_u16=0;
#ifdef GT_TIMER_STORE
    length_u16 = sizeof(genie_time_data_t);

    memset(&genie_time_data, 0, length_u16);
    uint32_t cpu_stat = enter_critical();
    hal_flash_fast_read(GENIE_TIME_STORE_OFFSET, (uint8_t *)&tmp_data, GENIE_TIMER_BUFFER_LENGHT);
    exit_critical(cpu_stat);
    check_crc = timer_v2_crc16calc(TIMER_V2_CRC_INIT_VAL,(uint8_t *)&tmp_data, length_u16);
    memcpy((uint8_t *)&cal_crc,&tmp_data[GENIE_TIMER_BUFFER_LENGHT-TIMER_V2_CRC_LENGTH],TIMER_V2_CRC_LENGTH);
    memcpy(&genie_time_data, (uint8_t *)&tmp_data,length_u16);
    if ((genie_time_data.magic != 0xABCD) || (check_crc !=cal_crc))
    {
        //LOG_I("timers restore failed");
        return -1;
    }

    for (uint8_t i = 0; i < GT_TIMER_MAX; i++)
    {
        if (genie_time_data.timer_data[i].state != GT_TIMER_STAT_INVALID)
        {
            sys_slist_append(&genie_time_ctx.timer_list_active, &genie_time_data.timer_data[i].next);
            //LOG_I("restore timer index:0x%02x, state:0x%02x, type:0x%02x", genie_time_data.timer_data[i].index,
            //               genie_time_data.timer_data[i].state, genie_time_data.timer_data[i].type);
        }
        else
        {
            sys_slist_append(&genie_time_ctx.timer_list_idle, &genie_time_data.timer_data[i].next);
        }
    }

    return 0;
#else
    return -1;
#endif
}

static genie_time_timer_t *genie_time_timer_find(uint8_t index)
{
    genie_time_timer_t *tmp, *node;
    sys_slist_t *list;

     uint32_t cpu_stat = enter_critical();
    list = &genie_time_ctx.timer_list_active;
    SYS_SLIST_FOR_EACH_CONTAINER_SAFE(list, genie_time_timer_t,node, tmp, next)
    {
        if ((node->index & 0x7F) == (index & 0x7F))
        {
            exit_critical(cpu_stat);
            return node;
        }
    }
    exit_critical(cpu_stat);
    return NULL;
}

static genie_time_timer_t *genie_time_timer_new()
{
    genie_time_timer_t *free_timer;
     uint32_t cpu_stat = enter_critical();
    free_timer = (genie_time_timer_t *)sys_slist_get(&genie_time_ctx.timer_list_idle);
    exit_critical(cpu_stat);
    //LOG_I("timer new %p", free_timer);
    return free_timer;
}

static int genie_time_timer_stop(uint8_t index)
{
    genie_time_timer_t *vendor_timer = genie_time_timer_find(index);
    if (vendor_timer != NULL)
    {
        //LOG_I("timer stop index:0x%02x", index);
         uint32_t cpu_stat = enter_critical();
        vendor_timer->index = 0;
        vendor_timer->state = GT_TIMER_STAT_INVALID;
        vendor_timer->type = GT_TIMER_TYPE_INVALID;
        sys_slist_find_and_remove(&genie_time_ctx.timer_list_active, &vendor_timer->next);
        sys_slist_append(&genie_time_ctx.timer_list_idle, &vendor_timer->next);
        exit_critical(cpu_stat);
    }

    return 0;
}

static int genie_time_timer_enable(uint8_t index)
{
    if (!genie_time_ctx.init)
    {
        return -GT_E_NOT_INIT;
    }

    //LOG_I("timer enable index:0x%02x", index);
    genie_time_timer_t *vendor_timer = genie_time_timer_find(index);
    if (vendor_timer == NULL)
    {
        return -GT_E_INDEX;
    }
    else
    {
         uint32_t cpu_stat = enter_critical();
        vendor_timer->index = index;
        vendor_timer->state = (index & 0x80) >> 7;
        exit_critical(cpu_stat);
        //LOG_I("timer update index:0x%02x, state:%d", vendor_timer->index, vendor_timer->state);
        return 0;
    }
}

static int genie_time_timer_remove(uint8_t index)
{
    if (!genie_time_ctx.init)
    {
        return -GT_E_NOT_INIT;
    }

    //LOG_I("timer remove index 0x%02x", index);

    /* remove alll timers */
    if (index == GT_TIMER_OP_ALL_INDEX)
    {
        genie_time_timer_t *tmp = NULL, *node = NULL;
        SYS_SLIST_FOR_EACH_CONTAINER_SAFE(&genie_time_ctx.timer_list_active, genie_time_timer_t, node, tmp, next)
        {
            genie_time_timer_stop(node->index);
        }
    }
    else
    {
        genie_time_timer_stop(index);
    }

    return 0;
}

#ifdef GT_TIMER_RECORD
static int genie_time_timer_record_set(uint8_t index, uint8_t type)
{
    int i = 0;
    uint8_t latest_pos = 0;
    uint32_t latest_unix_time = genie_time_data.time_record[latest_pos].unix_time;
    uint32_t unix_time = 0;

    for (i = 0; i < GT_TIMER_RECORD_MAX; i++)
    {
        if (genie_time_data.time_record[i].index == 0)
        {
            latest_pos = i;
            break;
        }
        else
        {
            unix_time = genie_time_data.time_record[i].unix_time;
            if (unix_time < latest_unix_time)
            {
                latest_pos = i;
                latest_unix_time = unix_time;
            }
        }
    }

    genie_time_data.time_record[latest_pos].index = index;
    genie_time_data.time_record[latest_pos].type = type;
    genie_time_data.time_record[latest_pos].unix_time = genie_time_ctx.unix_time;
    return 0;
}

static int genie_time_timer_record_status(uint8_t elem_id, uint16_t attr_type, uint8_t index, uint8_t tid, uint16_t app_idx)
{
    int i = 0;
    uint8_t len = 0, record_cnt = 0;
    uint8_t payload[32] = {0};
    uint32_t unix_time = 0;
    genie_transport_payload_param_t transport_payload_param;

    memset(payload, 0x0, sizeof(payload));
    payload[len++] = attr_type & 0xff;
    payload[len++] = (attr_type >> 8) & 0xff;
    payload[len++] = genie_time_succcode_get();
    if (index == GT_TIMER_OP_ALL_INDEX)
    {
        payload[len++] = index;
        for (i = 0; i < GT_TIMER_RECORD_MAX; i++)
        {
            if (genie_time_data.time_record[i].index != 0)
            {
                payload[len++] = genie_time_data.time_record[i].index;
            }
        }
    }
    else
    {
        for (i = 0; i < GT_TIMER_RECORD_MAX; i++)
        {
            if ((genie_time_data.time_record[i].index & 0x7F) == (index & 0x7F))
            {
                unix_time = genie_time_data.time_record[i].unix_time;
                payload[len++] = genie_time_data.time_record[i].type;
                payload[len++] = genie_time_data.time_record[i].index;
                payload[len++] = unix_time & 0xff;
                payload[len++] = (unix_time >> 8) & 0xff;
                payload[len++] = (unix_time >> 16) & 0xff;
                payload[len++] = (unix_time >> 24) & 0xff;
                record_cnt++;
            }
        }

        if (record_cnt == 0)
        {
            return -GT_E_INDEX;
        }
    }

    memset(&transport_payload_param, 0, sizeof(genie_transport_payload_param_t));
    transport_payload_param.opid = (uint8_t)(APP_MESH_VENDOR_STATUS & APP_MESH_VENDOR_MARK);
    transport_payload_param.element_id = elem_id;
    transport_payload_param.tid = tid;
    transport_payload_param.p_payload = payload;
    transport_payload_param.payload_len = len;
    transport_payload_param.retry_cnt = 1;
    transport_payload_param.dst_addr = ((gatt_mesh_src_addr==0xffff)?provisioner_unicast_addr:gatt_mesh_src_addr);
    genie_time_send_payload(&transport_payload_param, app_idx);
    return 0;
}
#endif

static int genie_time_timer_attr_data_binary(genie_time_attr_data_t *attr_data, uint8_t data[])
{
    int i = 0, j = 0;
    uint8_t attr_cnt = 0;
    uint8_t param_len = 0;

    if (attr_data == NULL)
    {
        return -1;
    }

    attr_cnt = attr_data->count;
    for (i = 0; i < attr_cnt; i++)
    {
        param_len = attr_data->items[i].param_len;
        data[j++] = attr_data->items[i].type & 0xff;
        data[j++] = (attr_data->items[i].type >> 8) & 0xff;
        data[j++] = param_len;
        memcpy(data + j, attr_data->items[i].param_data, param_len);
        j += param_len;
    }

    return j;
}

static int genie_time_timer_detail_data(uint8_t elem_id, uint16_t attr_type, uint8_t index, uint8_t tid, uint16_t app_idx)
{
    int len = 0;
    uint8_t payload[64] = {0};
    uint8_t attr_data_bin[64] = {0};
    uint8_t attr_data_len = 0;
    uint8_t tx_elem_id = elem_id;
    genie_transport_payload_param_t transport_payload_param;

    genie_time_timer_t *vendor_timer = genie_time_timer_find(index);
    if (vendor_timer == NULL)
    {
        return -GT_E_INDEX;
    }
    else
    {
        if (vendor_timer->type == GT_TIMER_TYPE_INVALID)
        {
            return -GT_E_PARAM;
        }

        memset(payload, 0x0, sizeof(payload));
        payload[len++] = attr_type & 0xff;
        payload[len++] = (attr_type >> 8) & 0xff;
        payload[len++] = genie_time_succcode_get();
        payload[len++] = vendor_timer->type;
        payload[len++] = vendor_timer->index;

        if (vendor_timer->type == GT_TIMER_LOCAL)
        {
            genie_time_attr_data_t *attr_data = &vendor_timer->local_timer.attr_data;
            uint32_t unix_time = vendor_timer->local_timer.unix_time_match + attr_data->count;
            tx_elem_id = attr_data->elem_id;
            //LOG_I("unix_time:0x%08x, attr_cnt:%d", unix_time, attr_data->count);
            payload[len++] = unix_time & 0xff;
            payload[len++] = (unix_time >> 8) & 0xff;
            payload[len++] = (unix_time >> 16) & 0xff;
            payload[len++] = (unix_time >> 24) & 0xff;

            memset(attr_data_bin, 0x00, sizeof(attr_data_bin));
            attr_data_len = genie_time_timer_attr_data_binary(attr_data, attr_data_bin);
            if (attr_data_len > 0)
            {
                memcpy(&payload[len], attr_data_bin, attr_data_len);
                len += attr_data_len;
            }
            else
            {
                return -GT_E_ATTR_PARAM;
            }
        }
        else if (vendor_timer->type == GT_TIMER_PERIODIC)
        {
            genie_time_attr_data_t *attr_data = &vendor_timer->periodic_timer.attr_data;
            int16_t timezone = vendor_timer->periodic_timer.timezone;
            uint8_t schedule = vendor_timer->periodic_timer.schedule;
            uint16_t periodic_time = vendor_timer->periodic_timer.periodic_time | (attr_data->count << 12);
            tx_elem_id = attr_data->elem_id;
             //LOG_I("periodic_time:0x%04x, attr_cnt:%d", periodic_time, attr_data->count);
            payload[len++] = periodic_time & 0xff;
            payload[len++] = (periodic_time >> 8) & 0xff;
            payload[len++] = timezone & 0xff;
            payload[len++] = (timezone >> 8) & 0xff;
            payload[len++] = schedule & 0xff;

            memset(attr_data_bin, 0x00, sizeof(attr_data_bin));
            attr_data_len = genie_time_timer_attr_data_binary(attr_data, attr_data_bin);
            if (attr_data_len > 0)
            {
                memcpy(&payload[len], attr_data_bin, attr_data_len);
                len += attr_data_len;
            }
            else
            {
                return -GT_E_ATTR_PARAM;
            }
        }
        else if (vendor_timer->type == GT_TIMER_CYCLE)
        {
            genie_time_cycle_attr_data_t *run_attr_data = &vendor_timer->cycle_timer.run_attr_data;
            genie_time_cycle_attr_data_t *sleep_attr_data = &vendor_timer->cycle_timer.sleep_attr_data;
            int16_t timezone = vendor_timer->cycle_timer.timezone;
            uint8_t schedule = vendor_timer->cycle_timer.schedule;
            uint16_t begin_time = vendor_timer->cycle_timer.begin_time;
            uint16_t end_time = vendor_timer->cycle_timer.end_time;
            uint16_t run_time = vendor_timer->cycle_timer.run_time + (run_attr_data->count << 12);
            uint16_t sleep_time = vendor_timer->cycle_timer.sleep_time + (sleep_attr_data->count << 12);
            tx_elem_id = run_attr_data->elem_id;
             //LOG_I("begin_time:0x%04x, end_time:0x%04x", begin_time, end_time);
             //LOG_I("run_time:0x%04x, attr_cnt:%d", run_time, run_attr_data->count);
             //LOG_I("sleep_time:0x%04x, attr_cnt:%d", sleep_time, sleep_attr_data->count);

            payload[len++] = begin_time & 0xff;
            payload[len++] = (begin_time >> 8) & 0xff;
            payload[len++] = end_time & 0xff;
            payload[len++] = (end_time >> 8) & 0xff;
            payload[len++] = timezone & 0xff;
            payload[len++] = (timezone >> 8) & 0xff;
            payload[len++] = schedule & 0xff;
            payload[len++] = run_time & 0xff;
            payload[len++] = (run_time >> 8) & 0xff;
            memset(attr_data_bin, 0x00, sizeof(attr_data_bin));
            attr_data_len = genie_time_timer_attr_data_binary((genie_time_attr_data_t *)run_attr_data, attr_data_bin);
            if (attr_data_len > 0)
            {
                memcpy(&payload[len], attr_data_bin, attr_data_len);
                len += attr_data_len;
            }
            else
            {
                return -GT_E_ATTR_PARAM;
            }

            payload[len++] = sleep_time & 0xff;
            payload[len++] = (sleep_time >> 8) & 0xff;
            memset(attr_data_bin, 0x00, sizeof(attr_data_bin));
            attr_data_len = genie_time_timer_attr_data_binary((genie_time_attr_data_t *)sleep_attr_data, attr_data_bin);
            if (attr_data_len > 0)
            {
                memcpy(&payload[len], attr_data_bin, attr_data_len);
                len += attr_data_len;
            }
            else
            {
                return -GT_E_ATTR_PARAM;
            }
        }

        //LOG_I("tx elem_id:%d,%d", tx_elem_id, elem_id);
        memset(&transport_payload_param, 0, sizeof(genie_transport_payload_param_t));
        transport_payload_param.opid = (uint8_t)(APP_MESH_VENDOR_STATUS & APP_MESH_VENDOR_MARK);
        transport_payload_param.element_id = tx_elem_id;
        transport_payload_param.tid = tid;
        transport_payload_param.p_payload = payload;
        transport_payload_param.payload_len = len;
        transport_payload_param.retry_cnt = 1;
        transport_payload_param.dst_addr = ((gatt_mesh_src_addr==0xffff)?provisioner_unicast_addr:gatt_mesh_src_addr);
        genie_time_send_payload(&transport_payload_param, app_idx);
        return 0;
    }
}

static uint32_t genie_time_timer_hour2unix_convert(uint16_t hour_time_24, uint16_t end_time, uint8_t schedule, int16_t timezone, uint8_t add_one_day)
{
    uint32_t unix_time_match = 0;
    uint32_t end_time_match = 0;
    int16_t minu_offset = 0;
    utc_time_t utc;

    //LOG_I("local_time:%4d/%2d/%2d %2d:%2d:%d weekday %2d",
    //       local_time.year, local_time.month + 1, local_time.day,
    //       local_time.hour, local_time.minutes, local_time.seconds,
   //        local_time.weekday);

    utc = local_time;
    utc.hour = 0;
    utc.minutes = 0;
    utc.seconds = 0;

    if (schedule > 0)
    {
        utc.day = utc.day + next_weekday_diff_get(local_time.weekday, schedule);
    }

    minu_offset = hour_time_24 - timezone;
    if (minu_offset >= 24 * MINU)
    {
        minu_offset -= 24 * MINU;
    }
    unix_time_match = UTC2unix(&utc) + minu_offset * MINU;
    if (end_time > 0)
    {
        end_time_match = unix_time_match + (end_time - hour_time_24) * MINU;
    }
    if ((unix_time_match <= genie_time_ctx.unix_time) && (end_time_match <= genie_time_ctx.unix_time))
    {
        if (schedule > 0)
        {
            unix_time_match += (1 + next_weekday_diff_get(next_weekday(local_time.weekday), schedule)) * DAY;
        }
        else
        {
            if (add_one_day)
            {
                unix_time_match += 1 * DAY;
            }
            else
            {
                //LOG_I("unix_time_match:%u less than %u", unix_time_match, genie_time_ctx.unix_time);
                return 0;
            }
        }
    }

    utc = unix2UTC(unix_time_match);
    //LOG_I("match utc:%4d/%2d/%2d %2d:%2d:%d weekday:%2d",
    //       utc.year, utc.month + 1, utc.day,
    //       utc.hour, utc.minutes, utc.seconds, utc.weekday);

    return unix_time_match;
}

static int genie_time_timer_local_start(uint8_t index, uint32_t unix_time, genie_time_attr_data_t *attr_data)
{
    genie_time_timer_t *vendor_timer;

    //LOG_I("local timer start index:0x%02x unix_time:%d", index, unix_time);

    if (!genie_time_ctx.init)
    {
        return -GT_E_NOT_INIT;
    }

    if (!genie_time_ctx.update)
    {
        return -GT_E_UNIX_TIME_NOT_SET;
    }

    if (unix_time <= genie_time_ctx.unix_time)
    {
        //LOG_I("unix_time_match:%u less than %u", unix_time, genie_time_ctx.unix_time);
        return -GT_E_UNIX_TIME;
    }

    vendor_timer = genie_time_timer_find(index);
    if (vendor_timer == NULL)
    {
        vendor_timer = genie_time_timer_new();
        if (vendor_timer == NULL)
        {
            return -GT_E_NORESOURCE;
        }
    }
    else
    {
         uint32_t cpu_stat = enter_critical();
        sys_slist_find_and_remove(&genie_time_ctx.timer_list_active, &vendor_timer->next);
        exit_critical(cpu_stat);
    }

    vendor_timer->index = index;
    vendor_timer->state = (index & 0x80) >> 7;
    vendor_timer->type = GT_TIMER_LOCAL;
    vendor_timer->local_timer.unix_time_match = unix_time;
    memcpy(&(vendor_timer->local_timer.attr_data), attr_data, sizeof(genie_time_attr_data_t));

    //LOG_I("index:0x%02x, unix_time_match:%u, cur_unix_time:%u, diff:%u", vendor_timer->index,
    //               vendor_timer->local_timer.unix_time_match, genie_time_ctx.unix_time,
    //               (vendor_timer->local_timer.unix_time_match - genie_time_ctx.unix_time));

     uint32_t cpu_stat = enter_critical();
    sys_slist_append(&genie_time_ctx.timer_list_active, &vendor_timer->next);
    exit_critical(cpu_stat);

    genie_time_data_save();

    return 0;
}

static int genie_time_timer_periodic_start(uint8_t index, uint16_t periodic_time, int16_t timezone, uint8_t schedule, genie_time_attr_data_t *attr_data)
{
    uint32_t unix_time_match = 0;
    genie_time_timer_t *vendor_timer;

    //LOG_I("periodic timer start index:0x%02x periodic_time:%d timezone:%d schedule:0x%02x", index, periodic_time, timezone, schedule);

    if (!genie_time_ctx.init)
    {
        return -GT_E_NOT_INIT;
    }

    if (!genie_time_ctx.update)
    {
        return -GT_E_UNIX_TIME_NOT_SET;
    }

    if (schedule > GT_TIMER_SCHEDULE_MAX)
    {
        return -GT_E_PARAM;
    }

    unix_time_match = genie_time_timer_hour2unix_convert(periodic_time, 0, schedule, timezone, 1);
    if (unix_time_match == 0)
    {
        return -GT_E_UNIX_TIME;
    }

    vendor_timer = genie_time_timer_find(index);
    if (vendor_timer == NULL)
    {
        vendor_timer = genie_time_timer_new();
        if (vendor_timer == NULL)
        {
            return -GT_E_NORESOURCE;
        }
    }
    else
    {
         uint32_t cpu_stat = enter_critical();
        sys_slist_find_and_remove(&genie_time_ctx.timer_list_active, &vendor_timer->next);
        exit_critical(cpu_stat);
    }

    vendor_timer->index = index;
    vendor_timer->state = (index & 0x80) >> 7;
    vendor_timer->type = GT_TIMER_PERIODIC;
    vendor_timer->periodic_timer.periodic_time = periodic_time;
    vendor_timer->periodic_timer.timezone = timezone;
    vendor_timer->periodic_timer.schedule = schedule;
    vendor_timer->periodic_timer.unix_time_match = unix_time_match;
    memcpy(&(vendor_timer->periodic_timer.attr_data), attr_data, sizeof(genie_time_attr_data_t));

    //LOG_I("index:0x%02x, unix_time_match:%u, cur_unix_time:%u, diff:%u", vendor_timer->index,
    //               vendor_timer->periodic_timer.unix_time_match, genie_time_ctx.unix_time,
    //               (vendor_timer->periodic_timer.unix_time_match - genie_time_ctx.unix_time));

     uint32_t cpu_stat = enter_critical();
    sys_slist_append(&genie_time_ctx.timer_list_active, &vendor_timer->next);
    exit_critical(cpu_stat);

    genie_time_data_save();

    return 0;
}

static int genie_time_timer_cycle_start(uint8_t index, uint16_t begin_time, uint16_t end_time, int16_t timezone, uint8_t schedule, uint16_t run_time, uint16_t sleep_time, genie_time_cycle_attr_data_t *run_attr, genie_time_cycle_attr_data_t *sleep_attr)
{
    uint32_t unix_time_match = 0;
    uint32_t end_time_match = 0;
    genie_time_timer_t *vendor_timer;

    //LOG_I("cycle timer start index:0x%02x begin_time:%d end_time:%d run_time:%d sleep_time:%d timezone:%d schedule:0x%02x", index, begin_time, end_time, run_time, sleep_time, timezone, schedule);

    if (!genie_time_ctx.init)
    {
        return -GT_E_NOT_INIT;
    }

    if (!genie_time_ctx.update)
    {
        return -GT_E_UNIX_TIME_NOT_SET;
    }

    if (schedule > GT_TIMER_SCHEDULE_MAX)
    {
        return -GT_E_PARAM;
    }

    if ((end_time == 0) || (begin_time >= end_time))
    {
        return -GT_E_PARAM;
    }

    unix_time_match = genie_time_timer_hour2unix_convert(begin_time, end_time, schedule, timezone, 1);
    end_time_match = unix_time_match + (end_time - begin_time) * MINU;
    if ((unix_time_match == 0) || (end_time_match == 0))
    {
        return -GT_E_UNIX_TIME;
    }

    vendor_timer = genie_time_timer_find(index);
    if (vendor_timer == NULL)
    {
        vendor_timer = genie_time_timer_new();
        if (vendor_timer == NULL)
        {
            return -GT_E_NORESOURCE;
        }
    }
    else
    {
         uint32_t cpu_stat = enter_critical();
        sys_slist_find_and_remove(&genie_time_ctx.timer_list_active, &vendor_timer->next);
        exit_critical(cpu_stat);
    }

    vendor_timer->index = index;
    vendor_timer->state = (index & 0x80) >> 7;
    vendor_timer->type = GT_TIMER_CYCLE;
    vendor_timer->cycle_timer.stat = GT_CYCLE_STAT_RUN;
    vendor_timer->cycle_timer.timezone = timezone;
    vendor_timer->cycle_timer.begin_time = begin_time;
    vendor_timer->cycle_timer.end_time = end_time;
    vendor_timer->cycle_timer.run_time = run_time;
    vendor_timer->cycle_timer.sleep_time = sleep_time;
    vendor_timer->cycle_timer.schedule = schedule;
    vendor_timer->cycle_timer.unix_time_match = unix_time_match;
    vendor_timer->cycle_timer.end_time_match = end_time_match;
    memcpy(&(vendor_timer->cycle_timer.run_attr_data), run_attr, sizeof(genie_time_cycle_attr_data_t));
    memcpy(&(vendor_timer->cycle_timer.sleep_attr_data), sleep_attr, sizeof(genie_time_cycle_attr_data_t));

    //LOG_I("index:0x%02x, stat:%d, unix_time_match:[%u,%u], cur_unix_time:%u, diff:%d", vendor_timer->index,
    //               vendor_timer->cycle_timer.stat, vendor_timer->cycle_timer.unix_time_match, vendor_timer->cycle_timer.end_time_match,
    //               genie_time_ctx.unix_time, (int32_t)(vendor_timer->cycle_timer.unix_time_match - genie_time_ctx.unix_time));

     uint32_t cpu_stat = enter_critical();
    sys_slist_append(&genie_time_ctx.timer_list_active, &vendor_timer->next);
    exit_critical(cpu_stat);

    genie_time_data_save();

    return 0;
}

static int genie_time_timer_all_index_status(uint8_t elem_id, uint16_t attr_type, uint8_t tid, uint16_t app_idx)
{
    uint8_t len = 0;
    uint8_t payload[32] = {0};
    genie_time_timer_t *tmp = NULL, *node = NULL;
    genie_transport_payload_param_t transport_payload_param;

    memset(payload, 0x0, sizeof(payload));
    payload[len++] = attr_type & 0xff;
    payload[len++] = (attr_type >> 8) & 0xff;
    if (attr_type != GT_TIMER_INDEX_REPORT_T)
    {
        payload[len++] = genie_time_succcode_get();
    }
    if (attr_type == GT_TIMER_QUERY_T)
    {
        payload[len++] = 0xff;
    }
    
    SYS_SLIST_FOR_EACH_CONTAINER_SAFE(&genie_time_ctx.timer_list_active, genie_time_timer_t, node, tmp, next)
    {
        if (node->state != GT_TIMER_STAT_INVALID)
        {
            payload[len++] = node->index;
        }
    }
    memset(&transport_payload_param, 0, sizeof(genie_transport_payload_param_t));
    transport_payload_param.opid = (uint8_t)(APP_MESH_VENDOR_STATUS & APP_MESH_VENDOR_MARK);
    transport_payload_param.element_id = elem_id;
    transport_payload_param.tid = tid;
    transport_payload_param.p_payload = payload;
    transport_payload_param.payload_len = len;
    transport_payload_param.retry_cnt = 1;
    transport_payload_param.dst_addr = ((gatt_mesh_src_addr==0xffff)?provisioner_unicast_addr:gatt_mesh_src_addr);

    return genie_time_send_payload(&transport_payload_param, app_idx);
}

static int genie_time_timer_attr_data_parse(uint8_t *msg, uint8_t msg_len, uint8_t attr_cnt, genie_time_attr_data_t *attr_data)
{
    uint8_t len, err = 0;
    uint8_t *pmsg = msg;
    uint8_t msg_len_pre = msg_len;

    attr_data->count = attr_cnt;
   // //LOG_I("attr_data count:%d", attr_data->count);
    for (int i = 0; i < attr_cnt; i++)
    {
        if (msg_len < 3)
        {
            err = 1;
            break;
        }
        attr_data->items[i].type = (pmsg[0]) | (pmsg[1] << 8);
        pmsg += 2;
        msg_len -= 2;

        len = *pmsg++;
        msg_len -= 1;

        if ((msg_len < len) || (len > GT_TIMER_PARAM_LEN_MAX))
        {
            //LOG_I("msg_len:%d, attr_data_len:%d invalid", msg_len, len);
            err = 1;
            break;
        }

        attr_data->items[i].param_len = len;
        memcpy(attr_data->items[i].param_data, pmsg, len);
        //LOG_I("parse attr_data[%d]: 0x%04x, %d", i, attr_data->items[i].type, len);
        //LOG_HEX(&attr_data->items[i].param_data, len);
        pmsg += len;
        msg_len -= len;
    }

    if ((err == 1) || (msg_len_pre == msg_len))
    {
        return -GT_E_ATTR_PARAM;
    }
    else
    {
        return (msg_len_pre - msg_len);
    }
}

int genie_time_timer_local_setting_event(uint8_t elem_id, genie_transport_model_param_t *p_msg)
{
    int ret = 0;
    uint8_t index, attr_data_cnt;
    uint8_t errcode = 0;
    uint8_t *pmsg = p_msg->data;
    uint16_t attr_type;
    uint16_t msg_len = p_msg->len;
    uint32_t unix_time;
    uint32_t unixtime_tmp;
    genie_time_attr_data_t attr_data;
    
    memcpy((uint8_t *)&attr_type,(pmsg+1),2);
    msg_len -= 2;
    pmsg+=3;

    //LOG_I("attr_type=0x%x,pmsg=0x%x",attr_type,*pmsg);
    //LOG_HEX(p_msg->data,msg_len); 
    if (p_msg->opid != (APP_MESH_VENDOR_SET_ACK & APP_MESH_VENDOR_MARK))
    {
        return -1;
    }

    if (msg_len >= 5)
    {
        index = *pmsg++;
        msg_len -= 1;
        unixtime_tmp = (pmsg[0]) | (pmsg[1] << 8) | (pmsg[2] << 16) | (pmsg[3] << 24);
        pmsg += 4;
        msg_len -= 4;

        unix_time = unixtime_tmp / 60 * 60;
        attr_data_cnt = unixtime_tmp % 60;
         //LOG_I("unix_time:%u, attr_data_cnt:%u", unix_time, attr_data_cnt);
        if ((attr_data_cnt > GT_TIMER_ATTR_OP_MAX) || (attr_data_cnt <= 0))
        {
            //LOG_I("attr_cnt:%d invalid", attr_data_cnt);
            ret = -GT_E_ATTR_PARAM;
        }
        else
        {
            memset(&attr_data, 0, sizeof(attr_data));
            attr_data.elem_id = elem_id;
            ret = genie_time_timer_attr_data_parse(pmsg, msg_len, attr_data_cnt, &attr_data);
            if (ret > 0)
            {
                pmsg += ret;
                msg_len -= ret;
                ret = genie_time_timer_local_start(index, unix_time, &attr_data);
            }
        }

        if (ret)
        {
            errcode = genie_time_errcode_convert(ret);
        }

        if (errcode != 0)
        {
            return genie_time_timer_errcode_status(elem_id, attr_type, errcode, index, p_msg->tid, p_msg->app_idx);
        }
    }

    return genie_time_timer_all_index_status(elem_id, attr_type, p_msg->tid, p_msg->app_idx);
}

int genie_time_timer_period_setting_event(uint8_t elem_id, genie_transport_model_param_t *p_msg)
{
    int ret = 0;
    uint8_t index, attr_data_cnt;
    uint8_t errcode = 0;
    uint8_t *pmsg = p_msg->data;
    uint16_t attr_type;
    uint16_t msg_len = p_msg->len;
    uint16_t periodic_tmp, periodic_time;
    int16_t timezone;
    uint8_t schedule;
    genie_time_attr_data_t attr_data;

    memcpy((uint8_t *)&attr_type,(pmsg+1),2);
    msg_len -= 2;
    pmsg+=3;

    if (p_msg->opid != (APP_MESH_VENDOR_SET_ACK & APP_MESH_VENDOR_MARK))
    {
        return -1;
    }

    if (msg_len >= 6)
    {
        index = *pmsg++;
        msg_len -= 1;
        periodic_tmp = (pmsg[0]) | (pmsg[1] << 8);
        pmsg += 2;
        msg_len -= 2;

        periodic_time = periodic_tmp & 0x0FFF;
        attr_data_cnt = (periodic_tmp >> 12) & 0x0F;
         //LOG_I("periodic_time:%u, attr_data_cnt:%u", periodic_time, attr_data_cnt);
        if ((attr_data_cnt > GT_TIMER_ATTR_OP_MAX) || (attr_data_cnt <= 0))
        {
            //LOG_I("attr_cnt:%d invalid", attr_data_cnt);
            ret = -GT_E_ATTR_PARAM;
        }
        else
        {
            timezone = (pmsg[0]) | (pmsg[1] << 8);
            pmsg += 2;
            msg_len -= 2;

            schedule = *pmsg++;
            msg_len -= 1;

            memset(&attr_data, 0, sizeof(attr_data));
            attr_data.elem_id = elem_id;
            ret = genie_time_timer_attr_data_parse(pmsg, msg_len, attr_data_cnt, &attr_data);
            if (ret > 0)
            {
                pmsg += ret;
                msg_len -= ret;
                ret = genie_time_timer_periodic_start(index, periodic_time, timezone, schedule, &attr_data);
            }
        }

        if (ret)
        {
            errcode = genie_time_errcode_convert(ret);
        }

        if (errcode != 0)
        {
            return genie_time_timer_errcode_status(elem_id, attr_type, errcode, index, p_msg->tid, p_msg->app_idx);
        }
    }

    return genie_time_timer_all_index_status(elem_id, attr_type, p_msg->tid, p_msg->app_idx);
}

int genie_time_timer_cycle_setting_event(uint8_t elem_id, genie_transport_model_param_t *p_msg)
{
    int ret = 0;
    uint8_t index, run_op_cnt, sleep_op_cnt;
    uint8_t errcode = 0;
    uint8_t *pmsg = p_msg->data;
    uint16_t attr_type;
    uint16_t msg_len = p_msg->len;
    uint16_t begin_time, end_time;
    uint16_t temp_time, run_time, sleep_time;
    int16_t timezone;
    uint8_t schedule;
    genie_time_cycle_attr_data_t run_attr_data, sleep_attr_data;

    memcpy((uint8_t *)&attr_type,(pmsg+1),2);
    msg_len -= 2;
    pmsg+=3;

    if (p_msg->opid != (APP_MESH_VENDOR_SET_ACK & APP_MESH_VENDOR_MARK))
    {
        return -1;
    }

    if (msg_len >= 10)
    {
        index = *pmsg++;
        msg_len -= 1;
        begin_time = (pmsg[0]) | (pmsg[1] << 8);
        pmsg += 2;
        msg_len -= 2;
        end_time = (pmsg[0]) | (pmsg[1] << 8);
        pmsg += 2;
        msg_len -= 2;

        timezone = (pmsg[0]) | (pmsg[1] << 8);
        pmsg += 2;
        msg_len -= 2;

        schedule = *pmsg++;
        msg_len -= 1;

        temp_time = (pmsg[0]) | (pmsg[1] << 8);
        pmsg += 2;
        msg_len -= 2;
        run_time = temp_time & 0x0FFF;
        run_op_cnt = (temp_time >> 12) & 0x0F;
         //LOG_I("run_time:%u, run_op_cnt:%u", run_time, run_op_cnt);
        if ((run_op_cnt > GT_TIMER_CYCLE_ATTR_OP_MAX) || (run_op_cnt <= 0))
        {
            //LOG_I("attr_cnt:%d invalid", run_op_cnt);
            ret = -GT_E_ATTR_PARAM;
        }
        else
        {
            memset(&run_attr_data, 0, sizeof(run_attr_data));
            run_attr_data.elem_id = elem_id;
            ret = genie_time_timer_attr_data_parse(pmsg, msg_len, run_op_cnt, (genie_time_attr_data_t *)&run_attr_data);
            if (ret > 0)
            {
                pmsg += ret;
                msg_len -= ret;

                if (msg_len >= 2)
                {
                    temp_time = (pmsg[0]) | (pmsg[1] << 8);
                    pmsg += 2;
                    msg_len -= 2;
                    sleep_time = temp_time & 0x0FFF;
                    sleep_op_cnt = (temp_time >> 12) & 0x0F;
                    // //LOG_I("sleep_time:%u, sleep_op_cnt:%u", sleep_time, sleep_op_cnt);
                    if ((run_op_cnt > GT_TIMER_CYCLE_ATTR_OP_MAX) || (run_op_cnt <= 0))
                    {
                        //LOG_I("attr_cnt:%d invalid", run_op_cnt);
                        ret = -GT_E_ATTR_PARAM;
                    }
                    else
                    {
                        memset(&sleep_attr_data, 0, sizeof(sleep_attr_data));
                        sleep_attr_data.elem_id = elem_id;
                        ret = genie_time_timer_attr_data_parse(pmsg, msg_len, sleep_op_cnt, (genie_time_attr_data_t *)&sleep_attr_data);
                        if (ret > 0)
                        {
                            pmsg += ret;
                            msg_len -= ret;
                            ret = genie_time_timer_cycle_start(index, begin_time, end_time, timezone, schedule, run_time, sleep_time, &run_attr_data, &sleep_attr_data);
                        }
                    }
                }
            }
        }

        if (ret)
        {
            errcode = genie_time_errcode_convert(ret);
        }

        if (errcode != 0)
        {
            return genie_time_timer_errcode_status(elem_id, attr_type, errcode, index, p_msg->tid, p_msg->app_idx);
        }
    }

    return genie_time_timer_all_index_status(elem_id, attr_type, p_msg->tid, p_msg->app_idx);
}

int genie_time_timer_enable_event(uint8_t elem_id, genie_transport_model_param_t *p_msg)
{
    int ret = 0;
    uint8_t index = 0;
    uint8_t *pmsg = p_msg->data;
    uint16_t attr_type;
    uint16_t msg_len = p_msg->len;
    uint8_t errcode = 0;

    memcpy((uint8_t *)&attr_type,(pmsg+1),2);
    msg_len -= 2;
    pmsg+=3;

    if (p_msg->opid != (APP_MESH_VENDOR_SET_ACK & APP_MESH_VENDOR_MARK))
    {
        return -1;
    }

    while (msg_len >= 1)
    {
        index = *pmsg++;
        msg_len--;

        ret = genie_time_timer_enable(index);
        if (ret != 0)
        {
            break;
        }
    }

    if (ret)
    {
        errcode = genie_time_errcode_convert(ret);
    }

    if (errcode != 0)
    {
        return genie_time_timer_errcode_status(elem_id, attr_type, errcode, index, p_msg->tid, p_msg->app_idx);
    }

    genie_time_data_save();

    return genie_time_timer_all_index_status(elem_id, attr_type, p_msg->tid, p_msg->app_idx);
}

int genie_time_timer_remove_event(uint8_t elem_id, genie_transport_model_param_t *p_msg)
{
    int ret = 0;
    uint8_t index = 0;
    uint8_t *pmsg = p_msg->data;
    uint16_t attr_type;
    uint16_t msg_len = p_msg->len;
    uint8_t errcode = 0;

    memcpy((uint8_t *)&attr_type,(pmsg+1),2);
    msg_len -= 2;
    pmsg+=3;

    if (p_msg->opid != (APP_MESH_VENDOR_SET_ACK & APP_MESH_VENDOR_MARK))
    {
        return -1;
    }

    while (msg_len >= 1)
    {
        index = *pmsg++;
        msg_len--;

        if (index == GT_TIMER_OP_ALL_INDEX)
        {
            ret = genie_time_timer_remove(index);
            break;
        }
        else
        {
            ret = genie_time_timer_remove(index);
            if (ret != 0)
            {
                break;
            }
        }
    }

    if (ret)
    {
        errcode = genie_time_errcode_convert(ret);
    }

    if (errcode != 0)
    {
        return genie_time_timer_errcode_status(elem_id, attr_type, errcode, index, p_msg->tid, p_msg->app_idx);
    }

    genie_time_data_save();

    return genie_time_timer_all_index_status(elem_id, attr_type, p_msg->tid, p_msg->app_idx);
}

int genie_time_timer_query_event(uint8_t elem_id, genie_transport_model_param_t *p_msg)
{
    int ret = 0;
    uint8_t index;
    uint8_t *pmsg = p_msg->data;
    uint16_t attr_type;
    uint16_t msg_len = p_msg->len;
    uint8_t errcode = 0;

    memcpy((uint8_t *)&attr_type,(pmsg+1),2);
    msg_len -= 2;
    pmsg+=3;

    if (msg_len > 0)
    {
        index = *pmsg++;
        msg_len--;

        //LOG_I("query index: 0x%02x", index);
        if (index == GT_TIMER_OP_ALL_INDEX)
        {
            return genie_time_timer_all_index_status(elem_id, attr_type, p_msg->tid, p_msg->app_idx);
        }
        else
        {
            ret = genie_time_timer_detail_data(elem_id, attr_type, index, p_msg->tid, p_msg->app_idx);
            if (ret)
            {
                errcode = genie_time_errcode_convert(ret);
            }

            if (errcode != 0)
            {
                return genie_time_timer_errcode_status(elem_id, attr_type, errcode, index, p_msg->tid, p_msg->app_idx);
            }
        }
    }
    return 0;
}

#ifdef GT_TIMER_RECORD
int genie_time_timer_record_event(uint8_t elem_id, genie_transport_model_param_t *p_msg)
{
    int ret = 0;
    uint8_t index;
    uint8_t *pmsg = p_msg->data;
    uint16_t attr_type;
    uint16_t msg_len = p_msg->len;
    uint8_t errcode = 0;

    memcpy((uint8_t *)&attr_type,(pmsg+1),2);
    msg_len -= 2;
    pmsg+=3;

    if (msg_len > 0)
    {
        index = *pmsg++;
        msg_len--;

        //LOG_I("record index: 0x%02x", index);
        ret = genie_time_timer_record_status(elem_id, attr_type, index, p_msg->tid, p_msg->app_idx);
        if (ret)
        {
            errcode = genie_time_errcode_convert(ret);
        }

        if (errcode != 0)
        {
            return genie_time_timer_errcode_status(elem_id, attr_type, errcode, index, p_msg->tid, p_msg->app_idx);
        }
    }
    return 0;
}
#endif

static void genie_time_timer_timeout_indicate(uint8_t idx[])
{
    int len = 0;
    uint8_t index = 0;
    uint8_t payload[32] = {0};
    genie_transport_payload_param_t transport_payload_param;

    memset(payload, 0x0, sizeof(payload));
    payload[len++] = GT_EVENT_UP_T & 0xff;
    payload[len++] = (GT_EVENT_UP_T >> 8) & 0xff;
    payload[len++] = GT_TIMER_TIMEOUT_EVT_ID;
    for (int i = 0; i < GT_TIMER_MAX; i++)
    {
        index = idx[i];
        if (index > 0)
        {
            payload[len++] = index;
        }
    }
    memset(&transport_payload_param, 0, sizeof(genie_transport_payload_param_t));
    transport_payload_param.opid = (uint8_t)(APP_MESH_VENDOR_STATUS & APP_MESH_VENDOR_MARK);
    transport_payload_param.p_payload = payload;
    transport_payload_param.payload_len = len;
    transport_payload_param.retry_cnt = 1;
    transport_payload_param.dst_addr = ((gatt_mesh_src_addr==0xffff)?provisioner_unicast_addr:gatt_mesh_src_addr);
    genie_time_send_payload(&transport_payload_param, 0xffff);
}

static uint8_t genie_time_timer_timeout_chk(genie_time_timer_t *vendor_timer)
{
    uint8_t timeout_flg = 0;
    uint32_t diff = 0;

    if (vendor_timer->state == GT_TIMER_STAT_INVALID)
    {
        return timeout_flg;
    }

    if (vendor_timer->type == GT_TIMER_LOCAL)
    {
        if (vendor_timer->local_timer.unix_time_match <= genie_time_ctx.unix_time)
        {
            diff = genie_time_ctx.unix_time - vendor_timer->local_timer.unix_time_match;
            if ((diff < GT_SYNC_TIME_SCOPE) && (vendor_timer->state == GT_TIMER_ENABLE))
            {
                timeout_flg = 1;
                genie_time_ctx.event_cb(GT_EVT_TIMEOUT, vendor_timer->index, &(vendor_timer->local_timer.attr_data));
            }
            else
            {
                timeout_flg = 2;
            }
        }
    }
    else if (vendor_timer->type == GT_TIMER_PERIODIC)
    {
        if (vendor_timer->periodic_timer.unix_time_match <= genie_time_ctx.unix_time)
        {
            diff = genie_time_ctx.unix_time - vendor_timer->periodic_timer.unix_time_match;
            if ((diff < GT_SYNC_TIME_SCOPE) && (vendor_timer->state == GT_TIMER_ENABLE))
            {
                timeout_flg = 1;
                genie_time_ctx.event_cb(GT_EVT_TIMEOUT, vendor_timer->index, &(vendor_timer->periodic_timer.attr_data));
            }
            else
            {
                timeout_flg = 2;
            }
        }
    }
    else if (vendor_timer->type == GT_TIMER_CYCLE)
    {
        if (vendor_timer->cycle_timer.unix_time_match <= genie_time_ctx.unix_time)
        {
            diff = genie_time_ctx.unix_time - vendor_timer->cycle_timer.unix_time_match;
             //LOG_I("cycle timer diff:%u", diff);
            if ((diff < 10) && (vendor_timer->state == GT_TIMER_ENABLE))
            {
                timeout_flg = 1;
                if (vendor_timer->cycle_timer.stat == GT_CYCLE_STAT_RUN)
                {
                    genie_time_ctx.event_cb(GT_EVT_TIMEOUT, vendor_timer->index, (genie_time_attr_data_t *)&(vendor_timer->cycle_timer.run_attr_data));
                }
                else
                {
                    genie_time_ctx.event_cb(GT_EVT_TIMEOUT, vendor_timer->index, (genie_time_attr_data_t *)&(vendor_timer->cycle_timer.sleep_attr_data));
                }
            }
            else
            {
                timeout_flg = 2;
            }
        }
    }

    return timeout_flg;
}

static void genie_time_work_handler(void *work)
{
    uint32_t unix_time_match = 0;
    uint32_t end_time_match = 0;
    uint32_t diff = 0;
    uint8_t timeout_cnt = 0;
    uint8_t timeout_flg = 0;
    uint8_t save_flg = 0;
    uint8_t timeout_idx[GT_TIMER_MAX] = {0};
    genie_time_timer_t *tmp = NULL, *node = NULL;

    if (genie_time_ctx.update)
    {
        memset(timeout_idx, 0x0, sizeof(timeout_idx));
        SYS_SLIST_FOR_EACH_CONTAINER_SAFE(&genie_time_ctx.timer_list_active, genie_time_timer_t, node, tmp, next)
        {
            timeout_flg = genie_time_timer_timeout_chk(node);
            if (timeout_flg > 0)
            {
                save_flg = 1;
                if (timeout_flg == 1)
                {
#ifdef GT_TIMER_RECORD
                    genie_time_timer_record_set(node->index, node->type);
#endif
                    timeout_idx[timeout_cnt++] = node->index;
                }
                if (node->type == GT_TIMER_LOCAL)
                {
                    genie_time_timer_stop(node->index);
                    genie_time_ctx.change_report = 1;
                }
                else if (node->type == GT_TIMER_PERIODIC)
                {
                    unix_time_match = genie_time_timer_hour2unix_convert(node->periodic_timer.periodic_time, 0, node->periodic_timer.schedule, node->periodic_timer.timezone, 0);
                    if (unix_time_match == 0)
                    {
                        genie_time_timer_stop(node->index);
                        genie_time_ctx.change_report = 1;
                    }
                    else
                    {
                         uint32_t cpu_stat = enter_critical();
                        node->periodic_timer.unix_time_match = unix_time_match;
                        exit_critical(cpu_stat);
                        //LOG_I("periodic index:0x%02x, unix_time_match:%u, cur_unix_time:%u, diff:%u", node->index,
                        //               node->periodic_timer.unix_time_match, genie_time_ctx.unix_time,
                        //               (node->periodic_timer.unix_time_match - genie_time_ctx.unix_time));
                    }
                }
                else if (node->type == GT_TIMER_CYCLE)
                {
                    while (node->cycle_timer.unix_time_match <= genie_time_ctx.unix_time)
                    {
                         uint32_t cpu_stat = enter_critical();
                        if (node->cycle_timer.stat == GT_CYCLE_STAT_RUN)
                        {
                            node->cycle_timer.unix_time_match = node->cycle_timer.unix_time_match + node->cycle_timer.run_time * MINU;
                            node->cycle_timer.stat = GT_CYCLE_STAT_SLEEP;
                        }
                        else
                        {
                            node->cycle_timer.unix_time_match = node->cycle_timer.unix_time_match + node->cycle_timer.sleep_time * MINU;
                            node->cycle_timer.stat = GT_CYCLE_STAT_RUN;
                        }
                        exit_critical(cpu_stat);

                        if (node->cycle_timer.unix_time_match > node->cycle_timer.end_time_match)
                        {
                            unix_time_match = genie_time_timer_hour2unix_convert(node->cycle_timer.begin_time, 0, node->cycle_timer.schedule, node->cycle_timer.timezone, 0);
                            end_time_match = unix_time_match + (node->cycle_timer.end_time - node->cycle_timer.begin_time) * MINU;
                            if ((unix_time_match == 0) || (end_time_match == 0))
                            {
                                genie_time_timer_stop(node->index);
                                genie_time_ctx.change_report = 1;
                            }
                            else
                            {
                                 uint32_t cpu_stat = enter_critical();
                                node->cycle_timer.stat = GT_CYCLE_STAT_RUN;
                                node->cycle_timer.unix_time_match = unix_time_match;
                                node->cycle_timer.end_time_match = end_time_match;
                                exit_critical(cpu_stat);
                            }
                            break;
                        }
                    }

                    if (node->cycle_timer.unix_time_match > 0)
                    {
                        //LOG_I("cycle index:0x%02x, stat:%d, unix_time_match:[%u,%u], cur_unix_time:%u, diff:%u", node->index,
                        //       node->cycle_timer.stat, node->cycle_timer.unix_time_match, node->cycle_timer.end_time_match,
                        //       genie_time_ctx.unix_time, (node->cycle_timer.unix_time_match - genie_time_ctx.unix_time));
                    }
                }
            }
        }

        if (save_flg == 1)
        {
            genie_time_data_save();
        }

        if (timeout_cnt > 0)
        {
            genie_time_timer_timeout_indicate(timeout_idx);
        }
        else if (genie_time_ctx.change_report)
        {
            genie_time_timer_all_index_status(0, GT_TIMER_INDEX_REPORT_T, 0, 0xffff);
            genie_time_ctx.change_report = 0;
            genie_time_ctx.boot_report_s = 0;
        }
        else if (genie_time_ctx.boot_report_s > 0)
        {
            uint32_t sync_period_time = genie_time_data.time_sync_config.period_time * MINU;
            diff = genie_time_ctx.unix_time + sync_period_time - genie_time_ctx.time_sync_unix_time_match;
             //LOG_I("boot report diff:%d, boot_report_s:%d", diff, genie_time_ctx.boot_report_s);
            if (diff >= genie_time_ctx.boot_report_s)
            {
                //LOG_I("device boot report all index");
                genie_time_timer_all_index_status(0, GT_TIMER_INDEX_REPORT_T, 0, 0xffff);
                genie_time_ctx.boot_report_s = 0;
            }
        }
    }

  //   //LOG_I("unix_time:%u, time_sync_unix_time_match:%u", genie_time_ctx.unix_time, genie_time_ctx.time_sync_unix_time_match);
    if (genie_time_ctx.time_sync_unix_time_match && (genie_time_ctx.time_sync_unix_time_match <= genie_time_ctx.unix_time))
    {
        genie_time_ctx.event_cb(GT_EVT_TIME_SYNC, 0, NULL);

         //LOG_I("config time_sync_retry_times:%d, time_sync_retry_times:%d", genie_time_data.time_sync_config.retry_times, genie_time_ctx.time_sync_retry_times);
         uint32_t cpu_stat = enter_critical();
        if (genie_time_ctx.time_sync_retry_times > 0)
        {
            diff = 2 * (genie_time_data.time_sync_config.retry_times - genie_time_ctx.time_sync_retry_times) + 1;
            if (diff > genie_time_data.time_sync_config.retry_delay)
            {
                diff = genie_time_data.time_sync_config.retry_delay;
            }
            genie_time_ctx.time_sync_retry_times--;
        }
        else
        {
            diff = genie_time_data.time_sync_config.period_time;
            genie_time_ctx.time_sync_retry_times = genie_time_data.time_sync_config.retry_times;
        }
        genie_time_ctx.time_sync_unix_time_match = genie_time_ctx.unix_time + diff * MINU;
        exit_critical(cpu_stat);
       // //LOG_I("time_sync_unix_time_match:%u, cur_unix_time:%u, diff:%u", genie_time_ctx.time_sync_unix_time_match, genie_time_ctx.unix_time, diff * MINU);
    }
}

#ifdef CONFIG_PM_SLEEP
static void genie_time_sw_timer_cb(void *p_timer, void *args)
{
    if (genie_time_ctx.update)
    {
        seconds_update();
    }

    genie_time_ctx.unix_time += 1;

    if (genie_time_ctx.unix_time % 60 == 0)
    {
        //LOG_I("current unix time: %d", genie_time_ctx.unix_time);
    }
}
#else
static void genie_time_sw_timer_cb(void *args)
{
    builtin_timer_start(sw_timer_sec, GT_SW_TIMER_PERIOD, NULL);
    if (genie_time_ctx.update)
    {
        seconds_update();
    }

    genie_time_ctx.unix_time += 1;

    if (genie_time_ctx.unix_time % 60 == 0)
    {
        //LOG_I("current unix time: %d", genie_time_ctx.unix_time);
    }

    genie_time_work_handler(NULL);
}
#endif

__weak void tmall_curtain_set_onoff(uint8_t on_off){}
void genie_event( genie_time_event_t *time_event)
{
    struct model_send_info msg;
    uint8_t payload[32] = {0};
    int len = 0;
    genie_time_attr_item_t *attr_item;
    //LOG_I("attr_data_cnt:%d", time_event->count);
    for (int i = 0; i < time_event->count; i++)
    {
        attr_item = &(time_event->items[i]);
        //LOG_I("element_id=%d,event attr_data[%d]: 0x%04x, %d", time_event->element_id, i,attr_item->type, attr_item->param_len);
        //LOG_HEX(attr_item->param_data, attr_item->param_len);

        payload[len++] = attr_item->type & 0xff;
        payload[len++] = (attr_item->type >> 8) & 0xff;
        memcpy(payload + len, attr_item->param_data, attr_item->param_len);
        len += attr_item->param_len;

        if ((attr_item->type == VENDOR_ATTR_TYPE_powerstate) && (attr_item->param_len ==1))
        {
            tmall_curtain_set_onoff(attr_item->param_data[0]);
        }
    }

    memset(&msg, 0, sizeof(struct model_send_info));          
    msg.ModelHandle = model_env.info[1].model_lid;
    msg.app_key_lid = model_env.app_key_lid;
    msg.opcode = APP_MESH_VENDOR_STATUS;
    msg.dest_addr = ((gatt_mesh_src_addr!=0xffff)?gatt_mesh_src_addr:provisioner_unicast_addr);
    timeout_report_status_tid++;
    if(timeout_report_status_tid >=0xbf)
    {
       timeout_report_status_tid = 0x80; 
    }
    msg.info[0] = timeout_report_status_tid;
    memcpy(&msg.info[1],payload,len);
    msg.len = (++len);
    
    model_send_info_handler(&msg);
}    

static int genie_time_event_cb(uint8_t event, uint8_t index, genie_time_attr_data_t *data)
{
    if (event == GT_EVT_TIMEOUT)
    {
        genie_time_event_t genie_time_event;

        genie_time_local_time_show();
        //LOG_I("timer index 0x%02x timeout", index);

        memset(&genie_time_event, 0, sizeof(genie_time_event));
        genie_time_event.element_id = data->elem_id;
        genie_time_event.count = data->count;
        memcpy(genie_time_event.items, data->items, sizeof(genie_time_event.items));
        genie_event(&genie_time_event);
    }
    else if (event == GT_EVT_TIME_SYNC)
    {
        genie_time_request_unix_time();
    }

    return 0;
}

int tmall_mesh_recv_vendor_timer_msg(struct model_rx_info *msg,uint8_t sn_mdl)
{
    u16_t attr_type = 0;
    uint8_t is_time_mesg = 1;
    uint8_t elem_id = 0;
    genie_transport_model_param_t p_msg;
    struct mesh_vendor_model_set *vendor_set;

    if (!msg || !msg->info || msg->rx_info_len < 2)
    {
        is_time_mesg = 0;
        return is_time_mesg;
    }
    vendor_set = (struct mesh_vendor_model_set *)msg->info;
    p_msg.tid = vendor_set->tid;
    p_msg.app_idx = msg->app_key_lid;
    p_msg.opid = (msg->opcode & APP_MESH_VENDOR_MARK);
    elem_id = model_env.info[sn_mdl].element_id;
    p_msg.len = msg->rx_info_len;
    p_msg.data = msg->info;
    p_msg.src_addr = msg->source_addr;
    switch (msg->opcode)
    {
    case APP_MESH_VENDOR_GET:
    {
        attr_type = vendor_set->attr_type;
         //LOG_I("GET attr_type:0x%04x, len:%d", attr_type, p_msg.len);
        if (attr_type == GT_UNIX_TIME_SETTING_T || attr_type == GT_TIMEZONE_SETTING_T || attr_type == GT_TIME_SYNC_T)
        {
            genie_time_getting_status(elem_id, p_msg.tid, p_msg.app_idx, attr_type);
        }
        else if (attr_type == GT_TIMER_QUERY_T)
        {
            genie_time_timer_query_event(elem_id, &p_msg);
        }
#ifdef GT_TIMER_RECORD
        else if (attr_type == GT_TIMER_RECORD_T)
        {
            genie_time_timer_record_event(elem_id, &p_msg);
        }
#endif
        else
        {
            is_time_mesg = 0;
        }
    }
    break;

    case APP_MESH_VENDOR_SET_ACK:
    case APP_MESH_VENDOR_SET_UNACK:
    {
        attr_type = vendor_set->attr_type;

         //LOG_I("SET attr_type:0x%04x, len:%d", attr_type, p_msg.len);
        if (attr_type == GT_UNIX_TIME_SETTING_T || attr_type == GT_TIMEZONE_SETTING_T || attr_type == GT_TIME_SYNC_T)
        {
            genie_time_setting_event(elem_id, &p_msg);
        }
        else if (attr_type == GT_TIMER_LOCAL_SETTING_T)
        {
            genie_time_timer_local_setting_event(elem_id, &p_msg);
        }
        else if (attr_type == GT_TIMER_PERIODIC_SETTING_T)
        {
            genie_time_timer_period_setting_event(elem_id, &p_msg);
        }
        else if (attr_type == GT_TIMER_CYCLE_SETTING_T)
        {
            genie_time_timer_cycle_setting_event(elem_id, &p_msg);
        }
        else if (attr_type == GT_TIMER_ENABLE_T)
        {
            genie_time_timer_enable_event(elem_id, &p_msg);
        }
        else if (attr_type == GT_TIMER_DELETE_T)
        {
            genie_time_timer_remove_event(elem_id, &p_msg);
        }
        else
        {
            is_time_mesg = 0;
        }
    }
    break;

    case APP_MESH_VENDOR_CONFIME_TG:
    {
         attr_type = vendor_set->attr_type;

         //LOG_I("CONFIME_TG attr_type:0x%04x, len:%d", attr_type, p_msg.len);
        if (attr_type == GT_UNIX_TIME_SETTING_T || attr_type == GT_TIMEZONE_SETTING_T || attr_type == GT_TIME_SYNC_T)
        {
            genie_time_setting_event(elem_id, &p_msg);
        }
        else
        {
            is_time_mesg = 0;
        }
    }
    break;

    default:
    {
        is_time_mesg = 0;
    }
    break;
    }

    return is_time_mesg;
}

int genie_time_init(void)
{
    int i = 0;
    uint8_t rand_1byte = 0;
    uint8_t random_time;

     //LOG_I("genie time init(%d, %d)", sizeof(genie_time_data_t), sizeof(genie_time_timer_t));

    if (genie_time_ctx.init)
    {
        return 0;
    }

    memset(&genie_time_ctx, 0, sizeof(genie_time_ctx));
    memset(&local_time, 0, sizeof(local_time));

    genie_time_ctx.event_cb = genie_time_event_cb;

    sys_slist_init(&genie_time_ctx.timer_list_active);
    sys_slist_init(&genie_time_ctx.timer_list_idle);

    sw_timer_sec = builtin_timer_create(genie_time_sw_timer_cb);
    builtin_timer_start(sw_timer_sec, GT_SW_TIMER_PERIOD, NULL);

    genie_time_ctx.init = 1;

    if (genie_time_data_restore() != 0)
    {
        //LOG_I("no have saved timer");

        memset(&genie_time_data, 0, sizeof(genie_time_data));
        genie_time_data.magic = 0xABCD;

        for (i = 0; i < GT_TIMER_MAX; i++)
        {
            genie_time_data.timer_data[i].index = 0;
            genie_time_data.timer_data[i].state = GT_TIMER_STAT_INVALID;
            genie_time_data.timer_data[i].type = GT_TIMER_TYPE_INVALID;
            sys_slist_append(&genie_time_ctx.timer_list_idle, &genie_time_data.timer_data[i].next);
        }
    }

#ifdef GT_SYNC_TIME_BOOTUP
    // sync unix time
    genie_time_data.time_sync_config.period_time = GT_TIME_SYNC_PERIOD_DEF;
    genie_time_data.time_sync_config.retry_delay = GT_TIME_SYNC_RETRY_DELAY_DEF;
    genie_time_data.time_sync_config.retry_times = GT_TIME_SYNC_RETRY_TIMES_DEF;

    rand_1byte = rand()%255;
    random_time = GT_SYNC_TIME_MIN + (GT_SYNC_TIME_SCOPE * rand_1byte / 255);
    genie_time_ctx.time_sync_unix_time_match = genie_time_ctx.unix_time + random_time;
   // //LOG_I("time_sync_unix_time_match:%u, cur_unix_time:%u, diff:%u", genie_time_ctx.time_sync_unix_time_match, genie_time_ctx.unix_time, random_time);
    genie_time_ctx.time_sync_retry_times = genie_time_data.time_sync_config.retry_times;

    genie_time_ctx.boot_report_s = GT_BOOT_REPORT_MIN + (GT_BOOT_REPORT_SCOPE * rand_1byte / 255);
    //LOG_I("boot_report_s:%d", genie_time_ctx.boot_report_s);
#endif

    return 0;
}

int genie_time_finalize(void)
{
    int ret;

    if (!genie_time_ctx.init)
    {
        return -1;
    }

    genie_time_timer_remove(GT_TIMER_OP_ALL_INDEX);

    genie_time_timer_all_index_status(0, GT_TIMER_INDEX_REPORT_T, 0, 0xffff);

    memset(&local_time, 0, sizeof(local_time));

    ret = genie_time_data_erase();
    return ret;
}
