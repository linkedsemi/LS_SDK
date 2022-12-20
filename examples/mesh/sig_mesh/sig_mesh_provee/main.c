#define LOG_TAG "MAIN"
#include <string.h>
#include <stdio.h>
#include "ls_ble.h"
#include "platform.h"
#include "ls_sig_mesh.h"
#include "log.h"
#include "ls_dbg.h"
#include "ls_hal_flash.h"
#include "tinyfs.h"
#include "tinycrypt/sha256.h"
#include "tinycrypt/constants.h"
#include "field_manipulate.h"
#include "le501x.h"
#include "sig_mesh_ctl.h"
#include "sig_light_cfg.h"
#include "sig_mesh_vendor_event.h"

#define COMPANY_ID 0x093A
#define COMPA_DATA_PAGES 1
#define MAX_NB_ADDR_REPLAY 20
#define PROV_AUTH_ACCEPT 1
#define PROV_AUTH_NOACCEPT 0
#define DEV_NAME_MAX_LEN 0x20

uint8_t vendor_tid = 0;
#define RECORD_KEY1 1
#define RECORD_KEY2 2

tinyfs_dir_t ls_sigmesh_dir;
struct mesh_model_info model_env;
struct lpn_offer_info friendship_env;
struct lpn_status_info local_lpn_env;
SIGMESH_NodeInfo_TypeDef Node_Get_Proved_State = 0;

static uint8_t dev_uuid[16] = {0x92,0x88,0x8A,0xFB,0xF0,0xCA,0x8F,0x45,0xB2,0xDF,0x93,0xEE,0x71,0x12,0x7C,0x68};
static uint8_t auth_data[16] = {0xF4,0xC7,0x0B,0xE8,0x10,0xE1,0x3A,0xAE,0xF8,0x3B,0x05,0xD4,0xA1,0xDA,0x8C,0xF3};

char ble_device_name[DEV_NAME_MAX_LEN] = "ls_sig_mesh_provee";
uint8_t rsp_data_info[40] = {0};
struct mesh_publish_info_ind mesh_publish_env[MAX_MESH_MODEL_NB];
static uint8_t model_tid = 0;
static uint8_t vendor_model_tid = 0;

static uint16_t provisioner_unicast_addr;
static uint8_t adv_obj_hdl;
static bool mesh_node_prov_state = false;
void app_client_model_tx_message_handler(uint32_t tx_msg, uint8_t model_indx);
void app_generic_onoff_status_report(uint8_t onoff);

void auto_check_unbind(void)
{
    uint16_t length = 1;
    uint8_t coutinu_power_up_num = 0;
    tinyfs_read(ls_sigmesh_dir, RECORD_KEY1, &coutinu_power_up_num, &length);
    LOG_I("coutinu_power_up_num:%d", coutinu_power_up_num);

    if (coutinu_power_up_num > 4)
    {
        coutinu_power_up_num = 0;
        tinyfs_write(ls_sigmesh_dir, RECORD_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        tinyfs_write_through();
        SIGMESH_UnbindAll();
    }
    else
    {
        coutinu_power_up_num++;
        tinyfs_write(ls_sigmesh_dir, RECORD_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        tinyfs_write_through();
    }
}


static void gap_manager_callback(enum gap_evt_type type, union gap_evt_u *evt, uint8_t con_idx)
{
    switch (type)
    {
    case CONNECTED:
        LOG_I("connected");
        break;
    case DISCONNECTED:
        LOG_I("disconnected");
        if(mesh_node_prov_state == true)
        {
            ls_sig_mesh_proxy_adv_ctl(true);
        }
        break;
    default:

        break;
    }
}

static void gatt_manager_callback(enum gatt_evt_type type, union gatt_evt_u *evt, uint8_t con_idx)
{
    
}

void app_client_model_tx_message_handler(uint32_t tx_msg, uint8_t model_idx)
{
    struct model_cli_trans_info param;
    model_tid++;
    param.mdl_lid = mesh_publish_env[model_idx].model_lid;
    param.app_key_lid = model_env.app_key_lid;
    param.dest_addr = mesh_publish_env[model_idx].addr;
    LOG_I("mdl_lid=%x,dest_addr=%x,tx_msg=%x,model_tid=%x",param.mdl_lid,param.dest_addr,tx_msg,model_tid);
    param.state_1 = tx_msg;
    param.state_2 = 0x00;
    param.delay_ms = 50;
    param.trans_info = (uint16_t)(model_tid << 8);
    param.trans_time_ms = 100;
    mesh_standard_model_publish_message_handler(&param);
}

void app_vendor_model_tx_message_handler(uint8_t *data, uint8_t len)
{
    struct vendor_model_publish_message tx_msg_info;
    vendor_model_tid++;
    tx_msg_info.ModelHandle = model_env.info[MODEL2_VENDOR_MODEL_CLI].model_lid;
    tx_msg_info.TxHandle = vendor_model_tid;
    tx_msg_info.MsgOpcode = APP_LS_SIG_MESH_VENDOR_SET;
    tx_msg_info.MsgLength = len;
    memcpy(&tx_msg_info.msg[0], data, tx_msg_info.MsgLength);
    LOG_I("vendor_model");
    LOG_HEX(&tx_msg_info.msg[0],tx_msg_info.MsgLength);
    mesh_vendor_model_publish_message_handler(&tx_msg_info);
}

void app_generic_onoff_status_report(uint8_t onoff)
{
    struct model_send_info onoff_rsp;
    onoff_rsp.ModelHandle = model_env.info[MODEL0_GENERIC_ONOFF_SVC].model_lid; 
    onoff_rsp.app_key_lid = model_env.app_key_lid; 
    onoff_rsp.opcode = GENERIC_ONOFF_STATUS;  
    onoff_rsp.dest_addr = provisioner_unicast_addr;
    onoff_rsp.len = 1; 
    onoff_rsp.info[0] = onoff;
    model_send_info_handler(&onoff_rsp);
}

void app_generic_vendor_report(uint16_t dest_addr)
{
    struct model_send_info onoff_rsp;
    onoff_rsp.ModelHandle = model_env.info[MODEL2_VENDOR_MODEL_SVC].model_lid; 
    onoff_rsp.app_key_lid = model_env.app_key_lid; 
    onoff_rsp.opcode = APP_LS_SIG_MESH_VENDOR_STATUS;  
    onoff_rsp.dest_addr = dest_addr;
    onoff_rsp.len = 3; 
    onoff_rsp.info[0] = 0x11;
    onoff_rsp.info[1] = 0x22;
    onoff_rsp.info[2] = 0x33;
    model_send_info_handler(&onoff_rsp);
}

void report_provisioner_unicast_address_ind(uint16_t unicast_address)
{
    provisioner_unicast_addr = unicast_address;
    tinyfs_write(ls_sigmesh_dir, RECORD_KEY2, (uint8_t *)&unicast_address, sizeof(unicast_address));
    tinyfs_write_through();
}

static void mesh_manager_callback(enum mesh_evt_type type, union ls_sig_mesh_evt_u *evt)
{
    switch (type)
    {
    case MESH_ACTIVE_ENABLE:
    {
        TIMER_Set(2, 3000); //clear power up num
    }
    break;
    case MESH_ACTIVE_DISABLE:
    {
        SIGMESH_UnbindAll();
        platform_reset(0);
    }
    break;
    case MESH_ACTIVE_REGISTER_MODEL:
    {
        for (uint8_t i = 0; i < model_env.nb_model; i++)
        {
            model_env.info[i].model_lid = evt->sig_mdl_info.info[i].model_lid;
        }
        model_env.app_key_lid = evt->sig_mdl_info.app_key_lid;
    }
    break;
    case MESH_ACTIVE_MODEL_PUBLISH:
    {
        for (uint8_t i = 0; i < model_env.nb_model; i++)
        {
            if (evt->mesh_publish_info.model_lid == model_env.info[i].model_lid)
            {
                 mesh_publish_env[i].model_lid = evt->mesh_publish_info.model_lid;
                 mesh_publish_env[i].period_ms = evt->mesh_publish_info.period_ms;
                 mesh_publish_env[i].addr =  evt->mesh_publish_info.addr;
            }
        }
       
    }
    break;
    case MESH_ACTIVE_LPN_START:
    {
        struct start_lpn_info param;
        param.poll_timeout_100ms = 20; //timeout min 1s
        param.poll_intv_ms = 1000;
        param.previous_addr = 0x2013;
        param.rx_delay_ms = 10; //rx delay min 10ms
        param.rx_window_factor = LPN_RX_WINDOW_FACTOR_2_5;
        param.min_queue_size_log = FRIEND_NODE_MIN_QUEUE_SIZE_LOG_N16;
        start_lpn_handler(&param);
    }
    break;
    case MESH_ACTIVE_LPN_OFFER:
    {
        friendship_env.friend_addr = evt->lpn_offer_info.friend_addr;
        friendship_env.friend_rx_window = evt->lpn_offer_info.friend_rx_window;
        friendship_env.friend_queue_size = evt->lpn_offer_info.friend_queue_size;
        friendship_env.friend_subs_list_size = evt->lpn_offer_info.friend_subs_list_size;
        friendship_env.friend_rssi = evt->lpn_offer_info.friend_rssi;
        lnp_select_friend_handler(friendship_env.friend_addr);
    }
    break;
    case MESH_ACTIVE_LPN_STATUS:
    {
        local_lpn_env.lpn_status = evt->lpn_status_info.lpn_status;
        local_lpn_env.friend_addr = evt->lpn_status_info.friend_addr;
    }
    break;
    case MESH_ACTIVE_STORAGE_LOAD:
    {
        Node_Get_Proved_State = evt->st_proved.proved_state;
        if (Node_Get_Proved_State == PROVISIONED_OK)
        {
            uint16_t length = sizeof(provisioner_unicast_addr);
            LOG_I("The node is provisioned");
            ls_mesh_light_set_lightness(0xffff, LIGHT_LED_2);
            ls_mesh_light_set_lightness(0xffff, LIGHT_LED_3);
            tinyfs_read(ls_sigmesh_dir, RECORD_KEY2, (uint8_t *)&provisioner_unicast_addr, &length);
            mesh_node_prov_state = true;
        }
        else
        {
            LOG_I("The node is not provisioned");
            mesh_node_prov_state = false;
        }
        
    }
    break;
    case MESH_GET_PROV_INFO:
    {
        struct mesh_prov_info param;
        memcpy(&param.DevUuid[0],&dev_uuid[0],16);
        param.UriHash = 0x00000000;
        param.OobInfo = 0x0000;
        param.PubKeyOob = 0x00;
        param.StaticOob = 0x00;
        param.OutOobSize = 0x00;
        param.InOobSize = 0x00;
        param.OutOobAction = 0x0000;
        param.InOobAction = 0x0000;
        param.Info = 0x00;
        set_prov_param(&param);
    }
    break;
    case MESH_GET_PROV_AUTH_INFO:
    {
        struct mesh_prov_auth_info param;
        param.Adopt = PROV_AUTH_ACCEPT;
        memcpy(&param.AuthBuffer[0], &auth_data[0], 16);
        param.AuthSize = 16;
        set_prov_auth_info(&param);
    }
    break;
    case MESH_REPOPT_PROV_RESULT:
    {
        if(evt->prov_rslt_sate.state == MESH_PROV_STARTED)
        {
            LOG_I("prov started");
        }
        else if(evt->prov_rslt_sate.state == MESH_PROV_SUCCEED)
        {
            LOG_I("prov succeed");
            mesh_node_prov_state = true;
            ls_mesh_light_set_lightness(0xffff,LIGHT_LED_2);
            ls_mesh_light_set_lightness(0xffff,LIGHT_LED_3);
        }
       else if(evt->prov_rslt_sate.state == MESH_PROV_FAILED)
        {
            LOG_I("prov failled:%d",evt->prov_rslt_sate.status);
        }
    }
    break;
    case MESH_ACCEPT_MODEL_INFO:
    {
         LOG_I("vendor info");
         LOG_I("model_lid=%x,opcode=%x",evt->rx_msg.ModelHandle,evt->rx_msg.opcode);
         LOG_HEX(&evt->rx_msg.info[0],evt->rx_msg.rx_info_len);
        if (evt->rx_msg.opcode == APP_LS_SIG_MESH_VENDOR_SET)
         {

            ls_mesh_light_set_onoff(evt->rx_msg.info[0], LIGHT_LED_1); 

            app_generic_vendor_report(evt->rx_msg.source_addr);
         } 
    }
    break;
    case MESH_STATE_UPD_IND:
    {
        sig_mesh_mdl_state_upd_hdl(&evt->mdl_state_upd_ind);
    }
    break;
    case MESH_REPORT_TIMER_STATE:
    {
        if (2 == evt->mesh_timer_state.timer_id)
        {
            uint8_t clear_power_on_num = 0;
            TIMER_Cancel(2);
            tinyfs_write(ls_sigmesh_dir, RECORD_KEY1, &clear_power_on_num, sizeof(clear_power_on_num));
            tinyfs_write_through();
        }
    }
    break;
    case MESH_ADV_REPORT:
    {
        // if(evt->adv_report.adv_addr->addr[5] == 0x20 && evt->adv_report.adv_addr->addr[4] == 0x17)
        // {
        //     LOG_I("dev addr: %02x:%02x:%02x:%02x:%02x:%02x",evt->adv_report.adv_addr->addr[5],
        //                                                     evt->adv_report.adv_addr->addr[4],
        //                                                     evt->adv_report.adv_addr->addr[3],
        //                                                     evt->adv_report.adv_addr->addr[2],
        //                                                     evt->adv_report.adv_addr->addr[1],
        //                                                     evt->adv_report.adv_addr->addr[0]);
        //     //LOG_HEX(evt->adv_report.adv_addr.addr,6);
        //     LOG_HEX(evt->adv_report.data,evt->adv_report.length);
        // }
        
    }
    break;
    default:
     break;
    }
}

void ls_sig_mesh_con_set_scan_rsp_data(uint8_t *scan_rsp_data, uint8_t *scan_rsp_data_len)
{
    uint8_t *pos;
    pos = scan_rsp_data;
    *pos++ = strlen(ble_device_name)+1;
    *pos++ = '\x08';
    memcpy(pos, ble_device_name, strlen((const char *)ble_device_name));
    pos += strlen((const char *)ble_device_name);

    *scan_rsp_data_len = ((uint32_t)pos - (uint32_t)(&scan_rsp_data[0]));
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
        struct ls_sig_mesh_cfg feature = {
            .MeshFeatures = EN_RELAY_NODE | EN_MSG_API | EN_PB_GATT | EN_PROXY_NODE,
            .MeshCompanyID = COMPANY_ID,
            .MeshProID = 0x001A,
            .MeshProVerID = 0x0001,
            .MeshLocDesc = 0x0100,
            .NbAddrReplay  = MAX_NB_ADDR_REPLAY,
            .NbCompDataPage = COMPA_DATA_PAGES,
            .FrdRxWindowMS = 90,
            .FrdQueueSize = 16,
            .FrdSubsListSize = 10,
        };
        bool type;
        dev_manager_get_identity_bdaddr(addr, &type);
        memcpy(&dev_uuid[0],addr,6);
        LOG_I("stack ready:");
        LOG_HEX(addr,6);
        dev_manager_prf_ls_sig_mesh_add(NO_SEC, &feature);
        ls_button_timer_init();
        vendor_event_init();
    }
    break;
    case PROFILE_ADDED:
    {
        prf_ls_sig_mesh_callback_init(mesh_manager_callback);

        model_env.nb_model = USR_MODEL_MAX_NUM;
        model_env.app_key_lid = 0;
        //server
        model_env.info[MODEL0_GENERIC_ONOFF_SVC].sig_model_cfg_idx = MESH_MDL_CFG_ONOFF;
        model_env.info[MODEL0_GENERIC_ONOFF_SVC].element_id = 0;
        model_env.info[MODEL0_GENERIC_ONOFF_SVC].model_lid = 0;
        model_env.info[MODEL0_GENERIC_ONOFF_SVC].model_id = GENERIC_ONOFF_SERVER;

        model_env.info[MODEL1_GENERIC_LEVEL_SVC].sig_model_cfg_idx = MESH_MDL_CFG_LEVEL;
        model_env.info[MODEL1_GENERIC_LEVEL_SVC].element_id = 0;
        model_env.info[MODEL1_GENERIC_LEVEL_SVC].model_lid = 0;
        model_env.info[MODEL1_GENERIC_LEVEL_SVC].model_id = GENERIC_LVL_SERVER;

        model_env.info[MODEL2_VENDOR_MODEL_SVC].vendor_model_cfg_idx = MESH_MDL_CFG_VENDORS_INFO;
        model_env.info[MODEL2_VENDOR_MODEL_SVC].element_id = 1;
        model_env.info[MODEL2_VENDOR_MODEL_SVC].model_lid = 0;
        model_env.info[MODEL2_VENDOR_MODEL_SVC].vendor_model_role = 0; //sever model
        model_env.info[MODEL2_VENDOR_MODEL_SVC].model_id = VENDOR_USER_SERVER;

        //client
        model_env.info[MODEL0_GENERIC_ONOFF_CLI].sig_model_cfg_idx = MESH_CMDL_CFG_IDX_GENC_ONOFF;
        model_env.info[MODEL0_GENERIC_ONOFF_CLI].element_id = 0;
        model_env.info[MODEL0_GENERIC_ONOFF_CLI].model_lid = 0;
        model_env.info[MODEL0_GENERIC_ONOFF_CLI].model_id = GENERIC_ONOFF_CLIENT;

        model_env.info[MODEL1_GENERIC_LEVEL_CLI].sig_model_cfg_idx = MESH_CMDL_CFG_IDX_GENC_LEVEL;
        model_env.info[MODEL1_GENERIC_LEVEL_CLI].element_id = 0;
        model_env.info[MODEL1_GENERIC_LEVEL_CLI].model_lid = 0;
        model_env.info[MODEL1_GENERIC_LEVEL_CLI].model_id = GENERIC_LVL_CLIENT;

        model_env.info[MODEL2_VENDOR_MODEL_CLI].vendor_model_cfg_idx = MESH_MDL_CFG_VENDORC_INFO;
        model_env.info[MODEL2_VENDOR_MODEL_CLI].element_id = 1;
        model_env.info[MODEL2_VENDOR_MODEL_CLI].model_lid = 0;
        model_env.info[MODEL2_VENDOR_MODEL_CLI].vendor_model_role = 1; //client model
        model_env.info[MODEL2_VENDOR_MODEL_CLI].model_id = VENDOR_USER_CLIENT;
        
        ls_sig_mesh_init(&model_env);
    }
    break;
    case ADV_OBJ_CREATED:
    {
        adv_obj_hdl = evt->obj_created.handle;
        LOG_I("adv obj hdl:%d",adv_obj_hdl);
    }
    break;
    default:
       break;
    }   
}

int main()
{
    sys_init_app();
    mesh_stack_data_bss_init();
    tinyfs_mkdir(&ls_sigmesh_dir, ROOT_DIR, 5);
    ls_mesh_pwm_init();
    light_button_init();
    ble_init();
    auto_check_unbind();
    dev_manager_init(dev_manager_callback);
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
    return 0;
}
