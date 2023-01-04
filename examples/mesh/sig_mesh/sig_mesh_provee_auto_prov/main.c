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
#include "sig_mesh_vendor_event.h"
#include "ls_soc_gpio.h"
#include "builtin_timer.h"

#define COMPANY_ID 0x093A
#define COMPA_DATA_PAGES 1
#define MAX_NB_ADDR_REPLAY 20
#define PROV_AUTH_ACCEPT 1
#define PROV_AUTH_NOACCEPT 0
#define DEV_NAME_MAX_LEN 0x20
#define RECORD_KEY1 1
#define RECORD_KEY2 2
#define NODE_UNICAST_ADDR 0x03  /*!< unicast_address >= 0x0002*/
#define GROUP_ADDR 0xC000  /*!< group_address >= 0xC000*/
#define PUBLISH_TTL 11  
#define PROV_SUCCESS_LED  PA01 
#define LED_ON  1
#define LED_OFF 0
#define AUTO_SIG_MESH_LP_MODE 0

tinyfs_dir_t ls_sigmesh_dir;
struct mesh_model_info model_env;
struct lpn_offer_info friendship_env;
struct lpn_status_info local_lpn_env;
SIGMESH_NodeInfo_TypeDef Node_Get_Proved_State = 0;
SIGMESH_NodeInfo_TypeDef Node_Proved_State = 0;

static uint8_t dev_uuid[16] = {0x92,0x88,0x8A,0xFB,0xF0,0xCA,0x8F,0x45,0xB2,0xDF,0x93,0xEE,0x71,0x12,0x7C,0x68};
static uint8_t auth_data[16] = {0xF4,0xC7,0x0B,0xE8,0x10,0xE1,0x3A,0xAE,0xF8,0x3B,0x05,0xD4,0xA1,0xDA,0x8C,0xF3};

//just for auto prov mode
uint8_t net_key[16] = {0x4D,0xC8,0x86,0xC8,0x0A,0x53,0xEF,0x80,0x5B,0x5C,0x30,0x59,0xF6,0xE3,0xA7,0xAD};
uint8_t app_key[16] = {0x8E,0x40,0x71,0xA5,0x3F,0x7A,0xEA,0xF0,0x81,0xB9,0xCF,0x8B,0x83,0x05,0x12,0x52};

char ble_device_name[DEV_NAME_MAX_LEN] = "ls_sig_mesh_provee";
uint8_t rsp_data_info[40] = {0};
struct mesh_publish_info_ind mesh_publish_env[MAX_MESH_MODEL_NB];
static uint8_t model_tid = 0;
static uint8_t vendor_model_tid = 0;
static uint8_t seqnum_offset=0;

static uint16_t mesh_src_addr;
static uint8_t adv_obj_hdl;
struct vendor_model_publish_message tx_msg_info;
void app_client_model_tx_message_handler(uint32_t tx_msg, uint8_t model_indx);
#if (AUTO_SIG_MESH_LP_MODE == 1)
#define TIMER_100ms	  100
static bool glp_tx_enable=false;
struct builtin_timer *user_timer_delay_rsp = NULL;
void timer_delay_rsp_callback(void *param);
void timer_delay_rsp_callback(void *param)
{
    if(glp_tx_enable==true)
    {
        mesh_vendor_model_publish_message_handler(&tx_msg_info);
        builtin_timer_start(user_timer_delay_rsp, TIMER_100ms, NULL);
        glp_tx_enable = false;
    }
    else
    {
       app_status_set(false);
    }
}
void builtin_timer_delay_rsp_Init(void)
{
	user_timer_delay_rsp = builtin_timer_create(timer_delay_rsp_callback);
}
#endif

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
        break;
    case CONN_PARAM_REQ:

        break;
    case CONN_PARAM_UPDATED:

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
    vendor_model_tid++;
    tx_msg_info.ModelHandle = model_env.info[MODEL2_VENDOR_MODEL_CLI].model_lid;
    tx_msg_info.TxHandle = vendor_model_tid;
    tx_msg_info.MsgOpcode = APP_LS_SIG_MESH_VENDOR_SET;
    tx_msg_info.MsgLength = len;
    seqnum_offset = (len>>3) + (((len%8)>0)?1:0);
    memcpy(&tx_msg_info.msg[0], data, tx_msg_info.MsgLength);
    #if (AUTO_SIG_MESH_LP_MODE == 1) 
     app_status_set(true);
     glp_tx_enable=true;
     builtin_timer_start(user_timer_delay_rsp, TIMER_100ms, NULL);
    #else
    mesh_vendor_model_publish_message_handler(&tx_msg_info);
    #endif 
}

static void mesh_manager_callback(enum mesh_evt_type type, union ls_sig_mesh_evt_u *evt)
{
    switch (type)
    {
    case MESH_ACTIVE_ENABLE:
    {
#if (AUTO_SIG_MESH_LP_MODE == 1)        
        struct start_glp_info param;
        param.RxDelyMs = 60;//60ms
        param.SleepIntvlMs = 86400;//1200ms
        start_glp_handler(&param);
        builtin_timer_delay_rsp_Init();
#endif 
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
            uint16_t length = sizeof(mesh_src_addr);
            LOG_I("The node is provisioned");
            tinyfs_read(ls_sigmesh_dir, RECORD_KEY2, (uint8_t *)&mesh_src_addr, &length);
            #if (AUTO_SIG_MESH_LP_MODE ==0)  
            io_write_pin(PROV_SUCCESS_LED,LED_ON);
            #endif  
        }
        else
        {
            LOG_I("The node is not provisioned");
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
        param.StaticOob = 0x01;
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
           #if (AUTO_SIG_MESH_LP_MODE == 1)
            app_status_set(false);
           #else
            io_write_pin(PROV_SUCCESS_LED,LED_ON);
           #endif 
        }
       else if(evt->prov_rslt_sate.state == MESH_PROV_FAILED)
        {
            LOG_I("prov failled:%d",evt->prov_rslt_sate.status);
        }
    }
    break;
    case MESH_ACCEPT_MODEL_INFO:
    {
        if (evt->rx_msg.opcode == APP_LS_SIG_MESH_VENDOR_SET)
         {
            if (model_env.info[MODEL2_VENDOR_MODEL_SVC].model_lid == evt->rx_msg.ModelHandle)
            {
                uint32_t cnt_message_tx= evt->rx_msg.info[0];
                cnt_message_tx |= (uint32_t)(evt->rx_msg.info[1]<<8);
                cnt_message_tx |= (uint32_t)(evt->rx_msg.info[2]<<16);
                cnt_message_tx |= (uint32_t)(evt->rx_msg.info[3]<<24);
                vendor_event_accept_info(&evt->rx_msg.info[0],evt->rx_msg.rx_info_len);
            }
         } 
    }
    break;
    case MESH_ACTIVE_MODEL_PUBLISHED:
    {
         ls_sig_mesh_auto_prov_update_ivseq_handler(seqnum_offset);
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
    case MESH_ACTIVE_AUTO_PROV:
    {
            struct mesh_auto_prov_info init_param;
            init_param.model_nb = model_env.nb_model;
			memcpy((uint8_t *)&init_param.unicast_addr,&dev_uuid[0],2); 
            init_param.unicast_addr = NODE_UNICAST_ADDR; //Recommendation unicast_addr >= 0x0002
            init_param.group_addr = GROUP_ADDR;//+group_para_handle();   //Recommendation group_addr >= 0xC000LOG_I()
            init_param.ttl = PUBLISH_TTL;
            init_param.model_info[MODEL0_GENERIC_ONOFF_SVC].model_id = model_env.info[MODEL0_GENERIC_ONOFF_SVC].model_id;
            init_param.model_info[MODEL0_GENERIC_ONOFF_SVC].publish_flag = false;
            init_param.model_info[MODEL0_GENERIC_ONOFF_SVC].subs_flag = true;

            init_param.model_info[MODEL1_GENERIC_LEVEL_SVC].model_id = model_env.info[MODEL1_GENERIC_LEVEL_SVC].model_id;
            init_param.model_info[MODEL1_GENERIC_LEVEL_SVC].publish_flag = false;
            init_param.model_info[MODEL1_GENERIC_LEVEL_SVC].subs_flag = true;

            init_param.model_info[MODEL2_VENDOR_MODEL_SVC].model_id = model_env.info[MODEL2_VENDOR_MODEL_SVC].model_id;
            init_param.model_info[MODEL2_VENDOR_MODEL_SVC].publish_flag = false;
            init_param.model_info[MODEL2_VENDOR_MODEL_SVC].subs_flag = true;

            init_param.model_info[MODEL0_GENERIC_ONOFF_CLI].model_id = model_env.info[MODEL0_GENERIC_ONOFF_CLI].model_id;
            init_param.model_info[MODEL0_GENERIC_ONOFF_CLI].publish_flag = true;
            init_param.model_info[MODEL0_GENERIC_ONOFF_CLI].subs_flag = true;

            init_param.model_info[MODEL1_GENERIC_LEVEL_CLI].model_id = model_env.info[MODEL1_GENERIC_LEVEL_CLI].model_id;
            init_param.model_info[MODEL1_GENERIC_LEVEL_CLI].publish_flag = true;
            init_param.model_info[MODEL1_GENERIC_LEVEL_CLI].subs_flag = true;

            init_param.model_info[MODEL2_VENDOR_MODEL_CLI].model_id = model_env.info[MODEL2_VENDOR_MODEL_CLI].model_id;
            init_param.model_info[MODEL2_VENDOR_MODEL_CLI].publish_flag = true;
            init_param.model_info[MODEL2_VENDOR_MODEL_CLI].subs_flag = true;
            memcpy(&init_param.app_key[0], &app_key[0], 16);
            memcpy(&init_param.net_key[0], &net_key[0], 16);

            ls_sig_mesh_auto_prov_handler(&init_param, true);
    }
    break;
    default:
    {
    }
    break;
    }
}

uint8_t usr_mac_addr[6]={NODE_UNICAST_ADDR,2,3,4,5,0xC6};
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
        dev_manager_set_mac_addr(&usr_mac_addr[0]);
    }
    break;

    case STACK_READY:
    {
        uint8_t addr[6];
        struct ls_sig_mesh_cfg feature = {
            .MeshFeatures = EN_RELAY_NODE | EN_MSG_API,
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
        vendor_event_init(); 
        dev_manager_prf_ls_sig_mesh_add(NO_SEC, &feature);
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
        model_env.info[MODEL2_VENDOR_MODEL_SVC].element_id = 0;
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
        model_env.info[MODEL2_VENDOR_MODEL_CLI].element_id = 0;
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
    case ADV_STOPPED:
    {
    }
    break;
    case SCAN_STOPPED:
    {
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
    #if (AUTO_SIG_MESH_LP_MODE == 0)
    io_cfg_output(PROV_SUCCESS_LED);
    io_write_pin(PROV_SUCCESS_LED,LED_OFF);
    #endif
    ble_init();
    auto_check_unbind();
    dev_manager_init(dev_manager_callback);
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
    return 0;
}
