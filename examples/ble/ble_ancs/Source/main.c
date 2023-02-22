#define LOG_TAG "MAIN"
#include "ls_ble.h"
#include "prf_ancs.h"
#include "tinyfs.h"
#include "log.h"
#include "platform.h"
#include "ls_dbg.h"
#define ANCS_DB_RECORD_NAME 1
#define APP_ANCS_DEV_NAME                ("LS ANCS Demo")

static uint8_t adv_obj_hdl;
static uint8_t advertising_data[28];
static uint8_t scan_response_data[31];

static void get_dev_name(struct gap_dev_info_dev_name *dev_name_ptr, uint8_t con_idx)
{
    LS_ASSERT(dev_name_ptr);
    dev_name_ptr->value = (uint8_t*)APP_ANCS_DEV_NAME;
    dev_name_ptr->length = sizeof(APP_ANCS_DEV_NAME);
}
static void get_appearance(struct gap_dev_info_appearance *dev_appearance_ptr, uint8_t con_idx)
{
    LS_ASSERT(dev_appearance_ptr);
    dev_appearance_ptr->appearance = 0;
}
static void get_slv_pref_param(struct gap_dev_info_slave_pref_param *dev_slv_pref_param_ptr, uint8_t con_idx)
{
    LS_ASSERT(dev_slv_pref_param_ptr);
    dev_slv_pref_param_ptr->con_intv_min  = 8;
    dev_slv_pref_param_ptr->con_intv_max  = 20;
    dev_slv_pref_param_ptr->slave_latency =  0;
    dev_slv_pref_param_ptr->conn_timeout  = 200;
}

static void gap_manager_callback(enum gap_evt_type type,union gap_evt_u *evt,uint8_t con_idx)
{
    switch(type)
    {
    case CONNECTED:
    {
        uint8_t peer_id_cont = gap_manager_get_bonding_peer_id(con_idx);
        LOG_I("CONNECT Peer_id = %d", peer_id_cont);
        if(peer_id_cont==0xff)
        {
            gap_manager_slave_security_req(con_idx, 0x04);
        }
    }
    break;
    case DISCONNECTED:
        LOG_I("DISCONNECTED! Reason:0x%x", evt->disconnected.reason);
        dev_manager_start_adv(adv_obj_hdl,advertising_data,sizeof(advertising_data),scan_response_data,sizeof(scan_response_data));
    break;
    case CONN_PARAM_REQ:
        //LOG_I
    break;
    case CONN_PARAM_UPDATED:

    break;
    case MASTER_PAIR_REQ:
    {
        struct pair_feature feat_param={
            .iocap = BLE_GAP_IO_CAPS_NONE,
            .oob = BLE_GAP_OOB_DISABLE,
            .auth = AUTH_BOND,
            .key_size = 16,
            .ikey_dist = KDIST_ENCKEY|KDIST_IDKEY,
            .rkey_dist = KDIST_ENCKEY|KDIST_IDKEY,
        };
        gap_manager_slave_pair_response_send(con_idx, true, &feat_param);
    }break;
    case PAIR_DONE:
        if(evt->pair_done.succeed)
        {
            prf_ancs_enable_req(con_idx,NULL);
        }
    break;
    case ENCRYPT_FAIL:
        LOG_I("ENCRYPT_FAIL");
    break;
    case ENCRYPT_DONE:
    {
        uint8_t ancs_db[ANCS_DB_SIZE];
        uint16_t db_size = ANCS_DB_SIZE;
        uint8_t rslt = tinyfs_read(ROOT_DIR,ANCS_DB_RECORD_NAME,ancs_db,&db_size);
        LS_ASSERT(rslt == TINYFS_NO_ERROR);
        prf_ancs_enable_req(con_idx,ancs_db);
    }break;
    case DISPLAY_PASSKEY:
        LOG_I("DISPLAY_PASSKEY");
    break;
    case REQUEST_PASSKEY:
        LOG_I("REQUEST_PASSKEY");
    break;
    case NUMERIC_COMPARE:
        LOG_I("NUMERIC_COMPARE");
    break;
    case GET_DEV_INFO_DEV_NAME:
        get_dev_name((struct gap_dev_info_dev_name*)evt, con_idx);
    break;
    case GET_DEV_INFO_APPEARANCE:
        get_appearance((struct gap_dev_info_appearance*)evt, con_idx);
    break;
    case GET_DEV_INFO_SLV_PRE_PARAM:
        get_slv_pref_param((struct gap_dev_info_slave_pref_param*)evt, con_idx);
    break;
    default:

    break;
    }
}


static void gatt_manager_callback(enum gatt_evt_type type,union gatt_evt_u *evt,uint8_t con_idx)
{
    
}

static void create_adv_obj()
{
    struct legacy_adv_obj_param adv_param = {
        .adv_intv_min = 0x20,
        .adv_intv_max = 0x20,
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

static void ancs_app_att_report(uint8_t con_idx,struct ancs_att_ind *param)
{
    uint8_t i;
    LOG_I("app att val:");
    for(i = 0; i < param->length; i++)
    {
        LOG_RAW("0x%02x ", param->val[i]);
    }
    LOG_RAW("\r\n");
}

static void ancs_ntf_att_report(uint8_t con_idx,struct ancs_att_ind *param)
{
    uint8_t i = 0;
    switch(param->att_id)
    {
        case NTF_ATT_ID_APP_ID:
            LOG_I("appid = %s", param->val);
            prf_ancs_get_app_attributes(con_idx,param->val,1<<APP_ATT_ID_DISPLAY_NAME);
            break;
        case NTF_ATT_ID_TITLE:
            LOG_I("att id tile:");
            for(i = 0; i < param->length; i++)
            {
                LOG_RAW("0x%02x ", param->val[i]);
            }
            LOG_RAW("\r\n");
            break;
        case NTF_ATT_ID_SUBTITLE:
            LOG_I("att id subtitle:");
            for(i = 0; i < param->length; i++)
            {
                LOG_RAW("0x%02x ", param->val[i]);
            }
            LOG_RAW("\r\n");
            break;		
        case NTF_ATT_ID_MSG:
            LOG_I("att id msg:");
            for(i = 0; i < param->length; i++)
            {
                LOG_RAW("0x%02x ", param->val[i]);
            }
            LOG_RAW("\r\n");
            break;
        case NTF_ATT_ID_POS_ACTION_LABEL:
            if(param->length > 0)
            {
                LOG_I("positive action label:");
                for(i = 0; i < param->length; i++)
                {
                    LOG_RAW("0x%02x ", param->val[i]);
                }
                LOG_RAW("\r\n");
            }
            break;
        case NTF_ATT_ID_NEG_ACTION_LABEL:
            if(param->length > 0)
            {
                LOG_I("negative action label:");
                for(i = 0; i < param->length; i++)
                {
                    LOG_RAW("0x%02x ", param->val[i]);
                }
                LOG_RAW("\r\n");
            }
            break;
        default:
            LOG_I("ntf_att_ind_handler defalut: 0x%x", param->att_id);
            break;
    }
}

static void call_handler(uint8_t con_idx,struct ancs_ntf_src *ntf_src)
{
    switch(ntf_src->event_id)
    {
    case EVT_ID_NTF_ADDED:
        prf_ancs_get_notification_attributes(con_idx,ntf_src->ntf_uid,
            1 << NTF_ATT_ID_APP_ID| 1 << NTF_ATT_ID_TITLE | 1 << NTF_ATT_ID_MSG | 1 << NTF_ATT_ID_POS_ACTION_LABEL | 1 << NTF_ATT_ID_NEG_ACTION_LABEL,
            20,20,20);
    break;
    case EVT_ID_NTF_MODIFIED:

    break;
    case EVT_ID_NTF_REMOVED:

    break;
    }
}

static void ntf_src_handler(uint8_t con_idx,struct ancs_ntf_src *ntf_src)
{
    switch(ntf_src->cat_id)
    {
    case CAT_ID_OTHER:

    break;
    case CAT_ID_CALL:
        call_handler(con_idx,ntf_src);
    break;
    case CAT_ID_MISSED_CALL:

    break;
    case CAT_ID_VOICE_MAIL:

    break;
    case CAT_ID_SOCIAL:

    break;
    case CAT_ID_SCHEDULE:

    break;
    case CAT_ID_EMAIL:

    break;
    case CAT_ID_NEWS:

    break;
    case CAT_ID_HEALTH_FITNESS:

    break;
    case CAT_ID_BUSINESS_FINANCE:

    break;
    case CAT_ID_LOCATION:

    break;
    case CAT_ID_ENTERTAINMENT:

    break;
    }
}

static void prf_ancs_callback(enum ancs_evt_type type,union ancs_evt_u *evt,uint8_t con_idx)
{
    switch(type)
    {
    case ANCS_ENABLE_RSP:
        if(evt->enable_rsp.status==0&&evt->enable_rsp.ancs_db)
        {
            tinyfs_write(ROOT_DIR,ANCS_DB_RECORD_NAME,evt->enable_rsp.ancs_db,ANCS_DB_SIZE);
            tinyfs_write_through();
        }
        prf_ancs_client_configuration_enable(con_idx);
    break;
    case ANCS_CLIENT_CONFIGURATION_ENABLED:
        LOG_I("ancs cl cfg enabled");
    break;
    case ANCS_CLIENT_CONFIGURATION_DISABLED:

    break;
    case ANCS_NOTIFICATION_SOURCE:
        LOG_I("evt_id=0x%x, evt_flg=0x%x, cat_id=0x%x, cat_cnt=0x%x, ntf_uid=0x%x", 
            evt->ntf_src->event_id, evt->ntf_src->event_flags, evt->ntf_src->cat_id, evt->ntf_src->cat_cnt, evt->ntf_src->ntf_uid);
        ntf_src_handler(con_idx,evt->ntf_src);
    break;
    case ANCS_NOTIFICATION_ATTRIBUTES_REPORT:
        ancs_ntf_att_report(con_idx,evt->ntf_atts_report);
    break;
    case ANCS_NOTIFICATION_ATTRIBUTES_COMPLETE:
        LOG_I("GET NTF ATTS CMP");
    break;
    case ANCS_APP_ATTRIBUTES_REPORT:
        ancs_app_att_report(con_idx,evt->app_atts_report);
    break;
    case ANCS_APP_ATTRIBUTES_COMPLETE:
        LOG_I("GET APP ATTS CMP");
    break;
    case ANCS_PERFORM_NOTIFICATION_ACTION_COMPLETE:
        LOG_I("PERFORM NTF ACTION CMP");
    break;
    }
}

static void prf_added_handler(struct profile_added_evt *evt)
{
    LOG_I("profile:%d, start handle:0x%x\n",evt->id,evt->start_hdl);
    switch(evt->id)
    {
    case PRF_ANCS:
        prf_ancs_callback_init(prf_ancs_callback);
        create_adv_obj();
    break;
    default:

    break;
    }
}

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
    }break;
    case STACK_READY:
    {
        uint8_t addr[6];
        bool type;
        dev_manager_get_identity_bdaddr(addr,&type);
        LOG_I("type:%d,addr:",type);
        LOG_HEX(addr,sizeof(addr));
        dev_manager_prf_ancs_add(NO_SEC);
    }break;
    case SERVICE_ADDED:

    break;
    case PROFILE_ADDED:
        prf_added_handler(&evt->profile_added);
    break;
    case ADV_OBJ_CREATED:
		{
        LS_ASSERT(evt->obj_created.status == 0);
        adv_obj_hdl = evt->obj_created.handle;
        uint16_t hid_uuid_value = 0x1812;
        uint8_t adv_data_length = ADV_DATA_PACK(advertising_data, 2, GAP_ADV_TYPE_SHORTENED_NAME, APP_ANCS_DEV_NAME, sizeof(APP_ANCS_DEV_NAME)-1 ,
                                                                     GAP_ADV_TYPE_COMPLETE_LIST_16_BIT_UUID, &hid_uuid_value, 2);
        (void)adv_data_length;
        dev_manager_start_adv(adv_obj_hdl,advertising_data,sizeof(advertising_data),scan_response_data,sizeof(scan_response_data));
		}break;
    case ADV_STOPPED:
    
    break;
    case SCAN_STOPPED:
    
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
