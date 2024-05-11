/*
 * Copyright (C) 2018-2020 Alibaba Group Holding Limited
 */

#ifndef __GENIE_TIME_V2_H__
#define __GENIE_TIME_V2_H__

#include "slist.h"
#include "ls_sig_mesh.h"

#if defined(__CC_ARM)
#pragma anon_unions
#endif

#define __packed __attribute__((__packed__))
/* timer store in device flash */
#define GT_TIMER_STORE
#define GT_TIMER_RECORD

#define GT_SYNC_TIME_MIN (5)      // Unit:s
#define GT_SYNC_TIME_SCOPE (60)   // Unit:s
#define GT_BOOT_REPORT_MIN (1)    // Unit:s
#define GT_BOOT_REPORT_SCOPE (10) // Unit:s

/* time sync request when device bootup */
#define GT_SYNC_TIME_BOOTUP (1)

#define GT_TIMER_MAX (13)
#define GT_TIMER_ATTR_OP_MAX (4)
#define GT_TIMER_CYCLE_ATTR_OP_MAX (2)
#define GT_TIMER_RECORD_MAX (4)
#define GT_TIMER_PARAM_LEN_MAX (8)
#define GT_TIMER_SCHEDULE_MAX (0x7F)
#define GT_TIMER_OP_ALL_INDEX (0xFF)

/* timer ali attr type */
#define GT_TIMER_LOCAL_SETTING_T 0xF013
#define GT_TIMER_PERIODIC_SETTING_T 0xF014
#define GT_TIMER_CYCLE_SETTING_T 0xF015
#define GT_TIMER_ENABLE_T 0xF016
#define GT_TIMER_DELETE_T 0xF017
#define GT_TIMER_QUERY_T 0xF018
#define GT_TIMER_RECORD_T 0xF019
#define GT_TIMER_INDEX_REPORT_T 0xF020

#define GT_TIME_SYNC_T 0xF01D
#define GT_UNIX_TIME_SETTING_T 0xF01F
#define GT_TIMEZONE_SETTING_T 0xF01E

/* event up attr type */
#define GT_EVENT_UP_T 0xF009
/* timer timeout event ID */
#define GT_TIMER_TIMEOUT_EVT_ID 0x11

#define GT_SW_TIMER_ID (0)
#define GT_SW_TIMER_PERIOD (1000)

#define GT_TIME_SYNC_PERIOD_DEF 180
#define GT_TIME_SYNC_RETRY_DELAY_DEF 5
#define GT_TIME_SYNC_RETRY_TIMES_DEF 3

#define MINU 60
#define HOUR (60 * MINU)
#define DAY (24 * HOUR)			

/* timer status code */
typedef enum
{
    GT_CODE_SUCCESS = 0x00,
    GT_CODE_SUCCESS_YAW = 0x01,
    GT_CODE_NOT_UNIX_TIME = 0x80,
    GT_CODE_NOT_UNIX_TIME_ABN = 0x81,
    GT_CODE_NOT_SUP_ATTR_OP = 0x82,
    GT_CODE_NOT_SUP_ATTR_PARAM = 0x83,
    GT_CODE_TIMER_TIME_INVALID = 0x84,
    GT_CODE_TIMER_INDEX_INVALID = 0x85,
    GT_CODE_TIMER_FULL = 0x86,
    GT_CODE_TIMER_PARAM_INVALID = 0x87,
} genie_time_status_code_e;

/* timer run state */
typedef enum
{
    GT_TIMER_DISABLE = 0,
    GT_TIMER_ENABLE = 1,
    GT_TIMER_STAT_INVALID = 0xf,
} genie_time_state_e;

/* timer type */
typedef enum
{
    GT_TIMER_LOCAL = 1,
    GT_TIMER_PERIODIC = 2,
    GT_TIMER_CYCLE = 3,
    GT_TIMER_TYPE_INVALID = 0xf,
} genie_time_type_e;

/* cycle timer stat */
typedef enum
{
    GT_CYCLE_STAT_RUN = 0,
    GT_CYCLE_STAT_SLEEP = 1,
} genie_time_cycle_stat_e;

typedef enum
{
    GT_OK = 0,
    GT_E_NOT_INIT,
    GT_E_UNIX_TIME_NOT_SET,
    GT_E_ATTR_PARAM,
    GT_E_UNIX_TIME,
    GT_E_INDEX,
    GT_E_PARAM,
    GT_E_NORESOURCE,
} genie_time_errno_e;

typedef enum
{
    GT_EVT_TIMEOUT = 0,
    GT_EVT_TIME_SYNC = 1,
} genie_time_event_e;

typedef struct _genie_time_attr_item_s
{
    uint16_t type;
    uint8_t param_len;
    uint8_t param_data[GT_TIMER_PARAM_LEN_MAX];
} __packed genie_time_attr_item_t;

typedef struct _genie_time_attr_data_s
{
    uint8_t elem_id : 4;
    uint8_t count : 4;
    genie_time_attr_item_t items[GT_TIMER_ATTR_OP_MAX];
} __packed genie_time_attr_data_t;

typedef struct _genie_time_cycle_attr_data_s
{
    uint8_t elem_id : 4;
    uint8_t count : 4;
    genie_time_attr_item_t items[GT_TIMER_CYCLE_ATTR_OP_MAX];
} __packed genie_time_cycle_attr_data_t;

typedef struct _genie_time_timer_local_s
{
    uint32_t unix_time_match;
    genie_time_attr_data_t attr_data;
} __packed genie_time_timer_local_t;

typedef struct _genie_time_timer_periodic_s
{
    uint8_t schedule;
    int16_t timezone;
    uint16_t periodic_time;
    uint32_t unix_time_match;
    genie_time_attr_data_t attr_data;
} __packed genie_time_timer_periodic_t;

typedef struct _genie_time_timer_cycle_s
{
    uint8_t stat : 1;
    uint8_t schedule : 7;
    uint16_t begin_time;
    uint16_t end_time;
    uint16_t run_time;
    uint16_t sleep_time;
    int16_t timezone;
    uint32_t unix_time_match;
    uint32_t end_time_match;
    genie_time_cycle_attr_data_t run_attr_data;
    genie_time_cycle_attr_data_t sleep_attr_data;
} __packed genie_time_timer_cycle_t;

typedef struct _genie_time_timer_s
{
    sys_snode_t next;
    uint8_t index;
    uint8_t state : 4;
    uint8_t type : 4;
    union
    {
        genie_time_timer_local_t local_timer;
        genie_time_timer_periodic_t periodic_timer;
        genie_time_timer_cycle_t cycle_timer;
    };
} genie_time_timer_t;

typedef struct _genie_time_sync_s
{
    uint16_t period_time;
    uint8_t retry_delay;
    uint8_t retry_times;
} __packed genie_time_sync_t;

#ifdef GT_TIMER_RECORD
typedef struct _genie_time_record_s
{
    uint8_t index;
    uint8_t type;
    uint32_t unix_time;
} __packed genie_time_record_t;
#endif

typedef struct _genie_time_data_s
{
    uint16_t magic;
    int16_t timezone;
    genie_time_sync_t time_sync_config;
#ifdef GT_TIMER_RECORD
    genie_time_record_t time_record[GT_TIMER_RECORD_MAX];
#endif
    genie_time_timer_t timer_data[GT_TIMER_MAX];
} genie_time_data_t;

typedef int (*genie_time_event_func_t)(uint8_t event, uint8_t index, genie_time_attr_data_t *data);

typedef struct _genie_time_ctx_s
{
    uint8_t init : 1;
    uint8_t update : 1;
    uint8_t change_report : 1;
    uint8_t boot_report_s;
    sys_slist_t timer_list_active;
    sys_slist_t timer_list_idle;
    uint32_t unix_time;
    uint32_t time_sync_tmms;
    uint32_t time_sync_unix_time_match;
    uint8_t time_sync_retry_times;
    genie_time_event_func_t event_cb;
} genie_time_ctx_t;

typedef struct _utc_time_s
{
    uint16_t year;   // 2019+
    uint8_t month;   // 0-11
    uint8_t day;     // 1-31
    uint8_t seconds; // 0-59
    uint8_t minutes; // 0-59
    uint8_t hour;    // 0-23
    uint8_t weekday; // 0 means sunday
} utc_time_t;

int genie_time_init(void);
int genie_time_finalize(void);
//int genie_time_handle_model_mesg(genie_transport_model_param_t *p_msg);
int tmall_mesh_recv_vendor_timer_msg(struct model_rx_info *msg,uint8_t sn_mdl);
int genie_time_data_erase();
#endif
