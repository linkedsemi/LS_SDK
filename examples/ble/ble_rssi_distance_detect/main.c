#define LOG_TAG "MAIN"
#include "ls_ble.h"
#include "platform.h"
#include "prf_hid.h"
#include "prf_bass.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include "lsuart.h"
#include "builtin_timer.h"
#include <string.h>
#include "co_math.h"
#include "io_config.h"
#include "prf_diss.h"
#include "SEGGER_RTT.h"
#include "tinyfs.h"
#include "rssi_smoothing_algo.h"
#include "rssi_distance_detect.h"

#define APP_DIS_DEV_NAME                ("LS_elec_vehicle")
#define APP_DIS_DEV_NAME_LEN            (sizeof(APP_DIS_DEV_NAME))

/// Manufacturer Name Value
#define APP_DIS_MANUFACTURER_NAME       ("LinkedSemi")
#define APP_DIS_MANUFACTURER_NAME_LEN   (sizeof(APP_DIS_MANUFACTURER_NAME))

/// ADV Data
#define APP_DIS_ADV_DATA                ("LS Dis Server")

/// Model Number String Value
#define APP_DIS_MODEL_NB_STR            ("LS-BLE-1.0")
#define APP_DIS_MODEL_NB_STR_LEN        (10)

/// Serial Number
#define APP_DIS_SERIAL_NB_STR           ("1.0.0.0-LE")
#define APP_DIS_SERIAL_NB_STR_LEN       (10)

/// Firmware Revision
#define APP_DIS_FIRM_REV_STR            ("1.0.0")
#define APP_DIS_FIRM_REV_STR_LEN        (5)

/// System ID Value - LSB -> MSB
#define APP_DIS_SYSTEM_ID               ("\x12\x34\x56\xFF\xFE\x9A\xBC\xDE")
#define APP_DIS_SYSTEM_ID_LEN           (8)

/// Hardware Revision String
#define APP_DIS_HARD_REV_STR           ("1.0.0")
#define APP_DIS_HARD_REV_STR_LEN       (5)

/// Software Revision String
#define APP_DIS_SW_REV_STR              ("1.0.0")
#define APP_DIS_SW_REV_STR_LEN          (5)

/// IEEE
#define APP_DIS_IEEE                    ("\xFF\xEE\xDD\xCC\xBB\xAA")
#define APP_DIS_IEEE_LEN                (6)

/// PNP ID Value
#define APP_DIS_PNP_ID                  ("\x02\x5E\x04\x40\x00\x00\x03")
#define APP_DIS_PNP_ID_LEN              (7)

#define SEC_MODE2_LEVEL2  0x05 

#define OOB_DATA_FLAG                     0x0                               /**< Indicate whether OOB is supported. */
#define AUTHREQ                           (AUTH_MITM | AUTH_BOND)           /**< Set the auth. */
#define KEY_SIZE                          0x10                              /**< Indicate the supported maximum LTK size (range: 7-16). */
#define INIT_KEY_DIST                     (KDIST_ENCKEY | KDIST_IDKEY)      /**< Set the initial key distribution. */
#define RESP_KEY_DIST                     (KDIST_ENCKEY | KDIST_IDKEY)      /**< Set the response key distribution. */

/// PNP ID Value
#define APP_DIS_PNP_ID                  ("\x02\x5E\x04\x40\x00\x00\x03")
#define APP_DIS_PNP_ID_LEN              (7)

#define DIR_NAME    7
#define RECORD_KEY1 1
#define DEV_NAME_MAX_LEN 0x20

static const uint8_t ble_device_name[DEV_NAME_MAX_LEN] = "LS_elec_vehicle";

static uint8_t con_idx_array[SDK_MAX_CONN_NUM];
static uint8_t connected_num;
static uint8_t adv_obj_hdl;
static uint8_t advertising_data[28];
static uint8_t scan_response_data[31];
static uint16_t dis_server_start_handle;
// static struct builtin_timer *update_batt_timer_inst = NULL;

struct pair_feature feat_param =
{
    .iocap = BLE_GAP_IO_CAPS_NONE,
    .oob = OOB_DATA_FLAG,
    .auth = AUTHREQ,
    .key_size = KEY_SIZE,
    .ikey_dist = INIT_KEY_DIST,
    .rkey_dist = RESP_KEY_DIST
};

static void start_adv(void);
#if 0
const uint8_t hid_report_map[] =
{
    0x05, 0x01,       // Usage Page (Generic Desktop)
    0x09, 0x06,       // Usage (Keyboard)
    0xA1, 0x01,       // Collection (Application)
    0x05, 0x07,       // Usage Page (Key Codes)
    0x19, 0xe0,       // Usage Minimum (224)
    0x29, 0xe7,       // Usage Maximum (231)
    0x15, 0x00,       // Logical Minimum (0)
    0x25, 0x01,       // Logical Maximum (1)
    0x75, 0x01,       // Report Size (1)
    0x95, 0x08,       // Report Count (8)
    0x81, 0x02,       // Input (Data, Variable, Absolute)

    0x95, 0x01,       // Report Count (1)
    0x75, 0x08,       // Report Size (8)
    0x81, 0x01,       // Input (Constant) reserved byte(1)

    0x95, 0x05,       // Report Count (5)
    0x75, 0x01,       // Report Size (1)
    0x05, 0x08,       // Usage Page (Page# for LEDs)
    0x19, 0x01,       // Usage Minimum (1)
    0x29, 0x05,       // Usage Maximum (5)
    0x91, 0x02,       // Output (Data, Variable, Absolute), Led report
    0x95, 0x01,       // Report Count (1)
    0x75, 0x03,       // Report Size (3)
    0x91, 0x01,       // Output (Data, Variable, Absolute), Led report padding

    0x95, 0x06,       // Report Count (6)
    0x75, 0x08,       // Report Size (8)
    0x15, 0x00,       // Logical Minimum (0)
    0x25, 0x65,       // Logical Maximum (101)
    0x05, 0x07,       // Usage Page (Key codes)
    0x19, 0x00,       // Usage Minimum (0)
    0x29, 0x65,       // Usage Maximum (101)
    0x81, 0x00,       // Input (Data, Array) Key array(6 bytes)

    0x09, 0x05,       // Usage (Vendor Defined)
    0x15, 0x00,       // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08,       // Report Size (8 bit)
    0x95, 0x02,       // Report Count (2)
    0xB1, 0x02,       // Feature (Data, Variable, Absolute)

    0xC0              // End Collection (Application)
};
#else
const uint8_t hid_report_map[] =
{
    0x05, 0x01,        // Usage Page(Generic Desktop)
    0x09, 0x02,        // Usage (Mouse)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x01,        // Report Id (1)
    0x09, 0x01,        // Usage (pointer)
    0xA1, 0x00,        // Collection (Physical)
    0x95, 0x05,        // Report Count (5)
    0x75, 0x01,        // Report Size (1)
    0x05, 0x09,        // Usage Page (Button)
    0x19, 0x01,        // Usage Minimum (Button 1)
    0x29, 0x05,        // Usage Maximum (Button 5)
    0x15, 0x00,        // Logical minimum (0)
    0x25, 0x01,        // Logical maximum (1)
    0x81, 0x02,        // Input (Data, Value, Absolute, Bit Field)
    0x95, 0x01,        // Report Count (1)
    0x75, 0x03,        // Report Size (3)
    0x81, 0x01,        // Input (Constant, Array, Absolute, Bit Field)
    0x75, 0x08,        // Report Size (8)
    0x95, 0x01,        // Report Count (1)
    0x05, 0x01,        // Usage Page (Generic Desktop)
    0x09, 0x38,        // Usage (Wheel)
    0x15, 0x81,        // Logical minimum (-127)
    0x25, 0x7F,        // Logical maximum (-127)
    0x81, 0x06,        // Input (Data, Value, Relative, Bit Field)
    0x05, 0x0C,        // Usage Page (Consumer)
    0x0A, 0x38, 0x02,  // Usage (AC Pan)
    0x95, 0x01,        // Report Count (1)
    0x81, 0x06,        // Input (Data, Value, Relative, Bit Field)
    0xC0,              // End Collection
    0xC0,              // End Collection
};
#endif
#define HID_REPORT_MAP_LEN (sizeof(hid_report_map))

static uint8_t search_conidx(uint8_t con_idx)
{
    uint8_t index = 0xff;
    for(uint8_t i = 0; i < SDK_MAX_CONN_NUM; i++)
    {
        if(con_idx_array[i] == con_idx)
        {
            index = i;
            break;
        }
    }
    return index;
}

bool ble_connected(uint8_t id)
{
    return con_idx_array[id] != 0xff;
}

void user_distance_detect_handle(bool detected)
{
    io_cfg_output(PA01);
    LOG_I("user_distance_detect_handle: %d", detected);
    if (detected)
    {
        io_set_pin(PA01);
    }
    else
    {
        io_clr_pin(PA01);
    }
}
// static void update_batt_timer_cb(void* arg)
// {
//     bas_batt_lvl_update(0,100);
//     builtin_timer_start(update_batt_timer_inst, 1000, NULL);
// }

// static void update_batt_timer_init(void)
// {
//     if (NULL == update_batt_timer_inst)
//     {
//         update_batt_timer_inst = builtin_timer_create(update_batt_timer_cb);
//     }
// }

static void dis_server_get_dev_name(struct gap_dev_info_dev_name *dev_name_ptr, uint8_t con_idx)
{
    LS_ASSERT(dev_name_ptr);
    dev_name_ptr->value = (uint8_t*)APP_DIS_DEV_NAME;
    dev_name_ptr->length = APP_DIS_DEV_NAME_LEN;
}
static void dis_server_get_appearance(struct gap_dev_info_appearance *dev_appearance_ptr, uint8_t con_idx)
{
    LS_ASSERT(dev_appearance_ptr);
    dev_appearance_ptr->appearance = 0;
}
static void dis_server_get_slv_pref_param(struct gap_dev_info_slave_pref_param *dev_slv_pref_param_ptr, uint8_t con_idx)
{
    LS_ASSERT(dev_slv_pref_param_ptr);
    dev_slv_pref_param_ptr->con_intv_min  = 8;
    dev_slv_pref_param_ptr->con_intv_max  = 20;
    dev_slv_pref_param_ptr->slave_latency =  0;
    dev_slv_pref_param_ptr->conn_timeout  = 200;
}

static void dis_server_get_value(uint8_t value, uint8_t con_idx)
{
    uint8_t len = 0;
    uint8_t *data = NULL;
    switch (value)
    {
    case DIS_SERVER_MANUFACTURER_NAME_CHAR:
        len = APP_DIS_MANUFACTURER_NAME_LEN;
        data = (uint8_t *)APP_DIS_MANUFACTURER_NAME;
        break;
    case DIS_SERVER_MODEL_NB_STR_CHAR:
        len = APP_DIS_MODEL_NB_STR_LEN;
        data = (uint8_t *)APP_DIS_MODEL_NB_STR;
        break;
    case DIS_SERVER_SERIAL_NB_STR_CHAR:
        len = APP_DIS_SERIAL_NB_STR_LEN;
        data = (uint8_t *)APP_DIS_SERIAL_NB_STR;
        break;
    case DIS_SERVER_HARD_REV_STR_CHAR:
        len = APP_DIS_HARD_REV_STR_LEN;
        data = (uint8_t *)APP_DIS_HARD_REV_STR;
        break;
    case DIS_SERVER_FIRM_REV_STR_CHAR:
        len = APP_DIS_FIRM_REV_STR_LEN;
        data = (uint8_t *)APP_DIS_FIRM_REV_STR;
        break;
    case DIS_SERVER_SW_REV_STR_CHAR:
        len = APP_DIS_SW_REV_STR_LEN;
        data = (uint8_t *)APP_DIS_SW_REV_STR;
        break;
    case DIS_SERVER_SYSTEM_ID_CHAR:
        len = APP_DIS_SYSTEM_ID_LEN;
        data = (uint8_t *)APP_DIS_SYSTEM_ID;
        break;
    case DIS_SERVER_IEEE_CHAR:
        len = APP_DIS_IEEE_LEN;
        data = (uint8_t *)APP_DIS_IEEE;
        break;
    case DIS_SERVER_PNP_ID_CHAR:
        len = APP_DIS_PNP_ID_LEN;
        data = (uint8_t *)APP_DIS_PNP_ID;
        break;
    default:
        LOG_I("Unsupported dis value!");
        break;
    }
    if(data)
    {
        prf_diss_value_confirm(con_idx, value, len, data);
    }   
}

static void prf_dis_server_callback(enum diss_evt_type type,union diss_evt_u *evt,uint8_t con_idx)
{
    switch(type)
    {
    case DIS_SERVER_SET_VALUE_RSP:

    break;
    case DIS_SERVER_GET_VALUE_IND:
        dis_server_get_value(evt->get_value_ind.value, con_idx);
    break;
    default:
        LS_ASSERT(0);
    break;
    }
}

static void gap_manager_callback(enum gap_evt_type type, union gap_evt_u *evt, uint8_t con_idx)
{
    uint8_t search_idx = 0xff;
    switch (type)
    {
    case CONNECTED:
        {
            connected_num++;
            search_idx = search_conidx(con_idx);
            LS_ASSERT(search_idx == 0xff);
            search_idx = search_conidx(0xff); // search the first idle idx
            LS_ASSERT(search_idx != 0xff);
            con_idx_array[search_idx] = con_idx; 
            LOG_I("connected!");
            // builtin_timer_start(update_batt_timer_inst, 1000, NULL);

            distance_detect_reset(con_idx);
            rssi_smoothing_algo_init(con_idx, true);
            distance_detect_timer_start();

            // static bool sec_lvl_flag = false;
            // sec_lvl_flag = !sec_lvl_flag;
            // if (sec_lvl_flag)
            // {
            //     gatt_manager_server_set_svc_permission(con_idx, dis_server_start_handle, UNAUTH_SEC);
            //     LOG_I("raise sec lvl!");
            // }
            // else
            // {
            //     gatt_manager_server_set_svc_permission(con_idx, dis_server_start_handle, NO_SEC);
            //     LOG_I("lower sec lvl!");
            // }
        }
        break;
    case DISCONNECTED:
        {
            LOG_I("disconnected!");
            search_idx = search_conidx(con_idx);
            LS_ASSERT(search_idx != 0xff);
            con_idx_array[search_idx] = 0xff;
            connected_num--;
            if (connected_num == SDK_MAX_CONN_NUM - 1)
            {
                start_adv();
            }
            // builtin_timer_stop(update_batt_timer_inst);
        }
        break;
    case CONN_PARAM_REQ:

        break;
    case CONN_PARAM_UPDATED:

        break;
    case MASTER_PAIR_REQ: //4
        gap_manager_slave_pair_response_send(con_idx, true, &feat_param);
        break;

    case SLAVE_SECURITY_REQ: //5
        LOG_I("SLAVE_SECURITY_REQ");
        break;

    case PAIR_DONE: //6
        LOG_I("PAIR_DONE");
        break;

    case ENCRYPT_DONE: //7
        break;

    case DISPLAY_PASSKEY: //8
        LOG_I("DISPLAY_PASSKEY");
        break;

    case REQUEST_PASSKEY: //9
        LOG_I("REQUEST_PASSKEY");
        break;

    case NUMERIC_COMPARE: //10
        LOG_I("NUMERIC_COMPARE");
        break;
    case GET_DEV_INFO_DEV_NAME:
        dis_server_get_dev_name((struct gap_dev_info_dev_name*)evt, con_idx);
    break;
    case GET_DEV_INFO_APPEARANCE:
        dis_server_get_appearance((struct gap_dev_info_appearance*)evt, con_idx);
    break;
    case GET_DEV_INFO_SLV_PRE_PARAM:
        dis_server_get_slv_pref_param((struct gap_dev_info_slave_pref_param*)evt, con_idx);
    break;
    default:

        break;
    }
}

static void prf_hid_server_callback(enum hid_evt_type type, union hid_evt_u *evt, uint8_t con_idx)
{
    switch (type)
    {
    case HID_REPORT_READ:
        evt->read_report_req.length = 0;  
        if(evt->read_report_req.type == APP_HOGPD_REPORT_MAP)
        {
            evt->read_report_req.value = (uint8_t *)hid_report_map;
            evt->read_report_req.length = HID_REPORT_MAP_LEN;
        }
        break;
    case HID_NTF_CFG:
        LOG_I("ntf_cfg save 2:%08x",evt->ntf_cfg.value);
        break;
    case HID_NTF_DONE:
        LOG_I("HID NTF DONE");
        break;
    case HID_REPORT_WRITE:
        LOG_I("HID REPORT WRITE");
        break;
    default:
        break;
    }
}

static void prf_batt_server_callback(enum bass_evt_type type, union bass_evt_u *evt, uint8_t con_idx)
{

}

static void start_adv(void)
{
    uint8_t adv_data_len;
    uint8_t scan_rsp_data_len;
    uint8_t manufacturer_value[] = {0xB8, 0x08};
    uint16_t uuid_value = 0x1812;
    adv_data_len = ADV_DATA_PACK(advertising_data, 2, GAP_ADV_TYPE_MANU_SPECIFIC_DATA, manufacturer_value, sizeof(manufacturer_value),
                                                      GAP_ADV_TYPE_COMPLETE_LIST_16_BIT_UUID, &uuid_value, sizeof(uuid_value));
    scan_rsp_data_len = ADV_DATA_PACK(scan_response_data, 1, GAP_ADV_TYPE_SHORTENED_NAME, ble_device_name, strlen((const char *)ble_device_name));

    LOG_I("start adv");
    dev_manager_start_adv(adv_obj_hdl, advertising_data, adv_data_len, scan_response_data, scan_rsp_data_len);
}
static void create_adv_obj()
{
    struct legacy_adv_obj_param adv_param = {
        .adv_intv_min = 800,
        .adv_intv_max = 800,
        .own_addr_type = PUBLIC_OR_RANDOM_STATIC_ADDR,
        .filter_policy = 0,
        .ch_map = 0x7,
        .disc_mode = ADV_MODE_GEN_DISC,
        .prop = {
            .connectable = 1,
            .scannable = 1,
            .directed = 0,
            .high_duty_cycle = 0,
        },
    };
    dev_manager_create_legacy_adv_object(&adv_param);
}

static void prf_added_handler(struct profile_added_evt *evt)
{
    LOG_I("profile:%d, start handle:0x%x\n", evt->id, evt->start_hdl);
    switch (evt->id)
    {
    case PRF_DIS_SERVER:
    {
        dis_server_start_handle = evt->start_hdl;
        prf_dis_server_callback_init(prf_dis_server_callback);
        struct bas_db_cfg db_cfg = {
            .ins_num = 1,
            .ntf_enable[0] = 1,
        };
        dev_manager_prf_bass_server_add(NO_SEC,&db_cfg,sizeof(db_cfg));
    }
    break;
    case PRF_HID:
    {
        prf_hid_server_callback_init(prf_hid_server_callback);
        create_adv_obj();
    }break;
    case PRF_BASS:
    {
        struct hid_db_cfg db_cfg;   
        db_cfg.hids_nb = 1;
        db_cfg.cfg[0].svc_features = HID_KEYBOARD;
        db_cfg.cfg[0].report_nb = 1;
        db_cfg.cfg[0].report_id[0] = 0;
        db_cfg.cfg[0].report_cfg[0] = HID_REPORT_IN;
        db_cfg.cfg[0].info.bcdHID = 0X0111;
        db_cfg.cfg[0].info.bCountryCode = 0;
        db_cfg.cfg[0].info.flags = HID_WKUP_FOR_REMOTE | HID_NORM_CONN;
        dev_manager_prf_hid_server_add(NO_SEC, &db_cfg, sizeof(db_cfg)); 
        prf_bass_server_callback_init(prf_batt_server_callback); 
    }break;
    default:
        break;
    }
}

static void gatt_manager_callback(enum gatt_evt_type type, union gatt_evt_u *evt, uint8_t con_idx)
{
    LOG_I("gatt evt:%d",type);
    switch (type)
    {
    case SERVER_READ_REQ:
        LOG_I("read req");
        break;
    case SERVER_WRITE_REQ:
        LOG_I("write req");
        break;
    case SERVER_NOTIFICATION_DONE:
        LOG_I("ntf done");
        break;
    case MTU_CHANGED_INDICATION:
        LOG_I("MTU:%d",evt->mtu_changed_ind.mtu);
        break;
    case CLIENT_RECV_INDICATION:
        LOG_I("clinent recv ind,hdl:%d",evt->client_recv_notify_indicate.handle);
        break;
    default:
        LOG_I("Event not handled!");
        break;
    }
}

static void dev_manager_callback(enum dev_evt_type type, union dev_evt_u *evt)
{
    switch (type)
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
        dev_manager_get_identity_bdaddr(addr, &type);
        LOG_I("type:%d,addr:", type);
        LOG_HEX(addr, sizeof(addr));

        dev_manager_prf_dis_server_add(NO_SEC,0xffff);
        // update_batt_timer_init();
        memset((void*)&con_idx_array[0], 0xff, sizeof(con_idx_array));
    }
    break;
    case PROFILE_ADDED:
        prf_added_handler(&evt->profile_added);
        break;
    case ADV_OBJ_CREATED:
        LS_ASSERT(evt->obj_created.status == 0);
        adv_obj_hdl = evt->obj_created.handle;
        start_adv();
        break;
    case ADV_STOPPED:
        if (connected_num < SDK_MAX_CONN_NUM)
        {
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
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
}
