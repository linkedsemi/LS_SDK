#define LOG_TAG "MAIN"
#include "ls_ble.h"
#include "platform.h"
#include "prf_diss.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include "ls_hal_uart.h"
#include "builtin_timer.h"
#include <string.h>
#include "co_math.h"
#include "ls_soc_gpio.h"
#include "prf_fotas.h"
#include "SEGGER_RTT.h"


#define LS_ADVERTISER_NAME "LS Advertiser_0"

#define LS_ADVERTISER_TIMEOUT 50 // timer units: ms

static struct builtin_timer *ls_advertiser_timer_inst = NULL;
static bool update_adv_intv_flag = false;
static bool update_adv_data_flag = false;

static uint8_t adv_obj_hdl;
static uint8_t advertising_data[28];
static uint8_t scan_response_data[31];

static void ls_advertiser_init(void);
static void ls_advertiser_timer_cb(void *param);
static void start_adv(void);
static void ls_advertiser_update_adv_data(void);

static void ls_advertiser_init(void)
{
    ls_advertiser_timer_inst = builtin_timer_create(ls_advertiser_timer_cb);
    builtin_timer_start(ls_advertiser_timer_inst, LS_ADVERTISER_TIMEOUT, NULL);
}

static void ls_advertiser_update_adv_interval(uint8_t input_intv)
{
    LOG_I("input_char: %d",input_intv);
    uint32_t new_intv = (input_intv - '0')*160;
    dev_manager_update_adv_interval(adv_obj_hdl, new_intv, new_intv);
    dev_manager_stop_adv(adv_obj_hdl);
    update_adv_intv_flag = true;
}

static void ls_advertiser_timer_cb(void *param)
{
    uint8_t input_char = (uint8_t)SEGGER_RTT_GetKey();
    if(input_char != 0xff)
    {
        switch (input_char)
        {
        case '0':
            ls_advertiser_update_adv_data();
        break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ls_advertiser_update_adv_interval(input_char);
        break;
        default:
            break;
        }
    }
    if(ls_advertiser_timer_inst)
    {
        builtin_timer_start(ls_advertiser_timer_inst, LS_ADVERTISER_TIMEOUT, NULL); 
    }
}

static void create_adv_obj()
{
    struct legacy_adv_obj_param adv_param = {
        .adv_intv_min = 160,
        .adv_intv_max = 160,
        .own_addr_type = PUBLIC_OR_RANDOM_STATIC_ADDR,
        .filter_policy = 0,
        .ch_map = 0x7,
        .disc_mode = ADV_MODE_GEN_DISC,
        .prop = {
            .connectable = 0,
            .scannable = 1,
            .directed = 0,
            .high_duty_cycle = 0,
        },
    };
    dev_manager_create_legacy_adv_object(&adv_param);
}
static void start_adv(void)
{
    LS_ASSERT(adv_obj_hdl != 0xff);
    uint8_t adv_data_length = ADV_DATA_PACK(advertising_data, 1, GAP_ADV_TYPE_SHORTENED_NAME, LS_ADVERTISER_NAME, sizeof(LS_ADVERTISER_NAME));
    dev_manager_start_adv(adv_obj_hdl, advertising_data, adv_data_length, scan_response_data, 0);
    LOG_I("adv start");
}
static void ls_advertiser_update_adv_data(void)
{
    LS_ASSERT(adv_obj_hdl != 0xff);
    if (!update_adv_data_flag)
    {
        static uint8_t adv_data_update_counter = 1;
        uint8_t adv_data_array[28];
        memcpy((void*)&adv_data_array[0], LS_ADVERTISER_NAME, sizeof(LS_ADVERTISER_NAME));
        adv_data_array[sizeof(LS_ADVERTISER_NAME)-2] = adv_data_update_counter++ + '0';
        uint8_t adv_data_length = ADV_DATA_PACK(advertising_data, 1, GAP_ADV_TYPE_SHORTENED_NAME, adv_data_array, sizeof(LS_ADVERTISER_NAME));
        dev_manager_update_adv_data(adv_obj_hdl, advertising_data, adv_data_length, scan_response_data, 0);
        update_adv_data_flag = true;
        if (10 == adv_data_update_counter)
        {
            adv_data_update_counter = 0;
        }
        LOG_I("adv data update");
    }
    else
    {
        LOG_I("previous adv data updating is unfinished!");
    }
    
}
/*
static void create_highduty_adv_obj(void)
{
    struct legacy_adv_obj_param adv_param = {
        .peer_addr = (struct dev_addr*)peer_addr_1,
        .peer_addr_type = RANDOM_ADDR,
        .adv_intv_min = 0x20,
        .adv_intv_max = 0x20,
        .own_addr_type = PUBLIC_OR_RANDOM_STATIC_ADDR,
        .filter_policy = 0,
        .ch_map = 0x7,
        .disc_mode = ADV_MODE_NON_DISC,
        .prop = {
            .connectable = 1,
            .scannable = 0,
            .directed = 1,
            .high_duty_cycle = 1,
        },
    };
    dev_manager_create_legacy_adv_object(&adv_param);
}*/

static void dev_manager_callback(enum dev_evt_type type,union dev_evt_u *evt)
{
    switch(type)
    {
    case STACK_INIT:
    {
        struct ble_stack_cfg cfg = {
            .private_addr = false,
            .controller_privacy = false,
        };
        dev_manager_stack_init(&cfg);
    }
    break;
    case STACK_READY:
    {
        uint8_t addr[6];
        bool type;
        dev_manager_get_identity_bdaddr(addr,&type);
        LOG_I("type:%d,addr:",type);
        LOG_HEX(addr,sizeof(addr));
        ls_advertiser_init();  
        create_adv_obj();    
    }
    break;
    case ADV_OBJ_CREATED:
        LS_ASSERT(evt->obj_created.status == 0);
        adv_obj_hdl = evt->obj_created.handle;
        start_adv();
    break;
    case ADV_STARTED:
        LOG_I("adv started");
    break;
    case ADV_UPDATED:
        update_adv_data_flag = false;
        LOG_I("adv updated");
    break;
    case ADV_STOPPED:
        if (update_adv_intv_flag)
        {
            update_adv_intv_flag = false;
            start_adv();
        }    
    break;
    default:

    break;
    }
}


int main()
{
    sys_init_app();
    ble_init();
    dev_manager_init(dev_manager_callback);
    // gap_manager_init(gap_manager_callback);
    // gatt_manager_init(gatt_manager_callback);
    ble_loop();
}
