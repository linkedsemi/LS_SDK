#include <string.h>
#include "app_config.h"
#include "ls_ble.h"
#include "compile_flag.h"
#include "builtin_timer.h"
#include "rssi_distance_detect.h"
#include "rssi_smoothing_algo.h"
#include "log.h"

#define CON_FOR_DISTANCE_DETECT_NUM CON_FOR_RSSI_SMTH_ALGO_NUM
_Static_assert(CON_FOR_DISTANCE_DETECT_NUM > 0 && CON_FOR_DISTANCE_DETECT_NUM <= SDK_MAX_CONN_NUM, "distance_detect_con_define");

#define PHONE_DETECT_RSSI_THRETHOLD -65 // phone detect rssi threthold in units of dbm
#define PHONE_DETECT_RSSI_TOLERANCE 5 // rssi tolerance in units of dbm
#define PHONE_DETECT_TIMER_INTERVAL 100 // phone detect timer interval in units of ms
#define PHONE_DETECT_THRETHOLD_CNT 5 // valid count threthold

static struct builtin_timer *distance_detect_inst = NULL;
static uint8_t distance_detect_valid_cnt[CON_FOR_DISTANCE_DETECT_NUM];
static uint8_t distance_detect_invalid_cnt[CON_FOR_DISTANCE_DETECT_NUM];
static uint8_t distance_detect_con_flag; // each bit for one connection, CON_FOR_DISTANCE_DETECT_NUM at most

__attribute__((weak)) bool ble_connected(uint8_t id)
{
    return false;
}
__attribute__((weak)) void user_distance_detect_handle(bool detected)
{
    // do nothing for weak function
}

static inline void set_distance_detect_valid(uint8_t id)
{
    distance_detect_con_flag |= 1 << id;
}
static inline void set_distance_detect_invalid(uint8_t id)
{
    distance_detect_con_flag &= ~(1 << id);
}
static bool distance_detected(void)
{
    return (distance_detect_con_flag & ((1 << CON_FOR_DISTANCE_DETECT_NUM) - 1)) != 0;
}
static bool get_distance_detect_status(uint8_t id)
{
    return (distance_detect_con_flag & (1 << id)) >> id;
}
static void phone_try_set_invalid(uint8_t id)
{
    if (get_distance_detect_status(id) != 0)
    {
        set_distance_detect_invalid(id);
        if (!distance_detected())
        {
            user_distance_detect_handle(false);
        }
    }
}
void distance_detect_timer_start(void)
{
    if (distance_detect_inst != NULL)
    {
        builtin_timer_start(distance_detect_inst, PHONE_DETECT_TIMER_INTERVAL, NULL);
    }
}

static void distance_detect_timer_cb(void* arg)
{
    bool no_device_connected = true;
    for (uint8_t i = 0; i < CON_FOR_DISTANCE_DETECT_NUM; i++)
    {
        if (ble_connected(i))
        {
            no_device_connected = false;
            int8_t rssi = get_cur_rssi(i);
            if (rssi >= PHONE_DETECT_RSSI_THRETHOLD)
            {
                distance_detect_valid_cnt[i]++;
            }
            else
            {
                distance_detect_valid_cnt[i] = 0;
            }
            
            if (rssi <= PHONE_DETECT_RSSI_THRETHOLD - PHONE_DETECT_RSSI_TOLERANCE)
            {
                distance_detect_invalid_cnt[i]++;
            }
            else
            {
                distance_detect_invalid_cnt[i] = 0;
            }
            
            if (distance_detect_valid_cnt[i] >= PHONE_DETECT_THRETHOLD_CNT)
            {
                if (!distance_detected())
                {
                    user_distance_detect_handle(true);
                }
                set_distance_detect_valid(i);
            }
            else if (distance_detect_invalid_cnt[i] >= PHONE_DETECT_THRETHOLD_CNT)
            {
                phone_try_set_invalid(i);
            }
        }
        else
        {
            set_distance_detect_invalid(i);
        }
        
    }
    if (no_device_connected)
    {
        user_distance_detect_handle(false);
    }
    else
    {
        distance_detect_timer_start();
    }
}
void distance_detect_reset(uint8_t id)
{
    if (NULL == distance_detect_inst)
    {
        distance_detect_inst = builtin_timer_create(distance_detect_timer_cb);
    }
    distance_detect_valid_cnt[id] = 0;
    distance_detect_invalid_cnt[id] = 0;
}

