#define LOG_TAG "MAIN"
#include <string.h>
#include <stdio.h>
#include "cpu.h"
#include "co_math.h"
#include "ls_ble.h"
#include "platform.h"
#include "ls_sig_mesh.h"
#include "log.h"
#include "ls_dbg.h"
#include "ls_hal_flash.h"
#include "tinyfs.h"
#include "sha256.h"
#include "constants.h"
#include "field_manipulate.h"
#include "le501x.h"
#include "sys_stat.h"
#include "tmall_mesh_ctl.h"
#include "tmall_ais_cfg.h"
#include "builtin_timer.h"
#include "reg_syscfg.h"
#include "ls_soc_gpio.h"
#include "genie_time_v2.h"
#include "tmall_genie_ais.h"
#include "genie_triple.h"
#include "tmall_genie_triple_handle.h"
#include "tmall_genie_ais_main_handle.h"
#if (UART_TEST)
#include "tmall_genie_log.h"
#endif

#define TMALL_GLP_ENABLE 1

#define TMALL_NEW_FEATURE_FLAG (1<<2)
#define TMALL_NEW_FEATURE_FLAG2 ((1<<1) | (1<<5))  //Overwrite and TIMER_V2_FLAG

#define TMALL_GATT_TIMEOUT 5000
#define ALI_COMPANY_ID 0x01a8
#define COMPA_DATA_PAGES 1
#define MAX_NB_ADDR_REPLAY 20
#define PROV_AUTH_ACCEPT 1
#define PROV_AUTH_NOACCEPT 0
#define TMALL_GATT_SRC_ADDR_INVALID (0xffff)
#define UPADTE_TMALL_GATT_SRC_ADDR_TYPE  (0xff)
#define TMALL_GATT_MESH_MODEL_INDEX_INVALID  (0xff)


bool sent_adv_ready=true;

uint8_t vendor_tid = 0;
#define RECORD_KEY1 1
#define RECORD_KEY2 2
#define RECORD_KEY3 3
#define RECORD_ST_GLP_NODE 3
#define CON_IDX_INVALID_VAL 0xff

tinyfs_dir_t mesh_dir;
struct mesh_model_info model_env;
static uint8_t gatt_mesh_model_indx=TMALL_GATT_MESH_MODEL_INDEX_INVALID;
uint16_t gatt_mesh_src_addr = TMALL_GATT_SRC_ADDR_INVALID;

SIGMESH_NodeInfo_TypeDef Node_Get_Proved_State = UNPROVISIONED_KO;
SIGMESH_NodeInfo_TypeDef Node_Proved_State = MESH_PROV_STARTED;
SIGMESH_NodeInfo_TypeDef Node_Beacon_State = 0;
static bool mesh_node_prov_state = false;
#if (TMALL_GLP_ENABLE)
#define TMALL_GLP_RST_FLAG 0x96966969
#define TMALL_GLP_SLEEP_MS  1200
#define TMALL_GLP_SCAN_MS   60
#define PROXY_CON_INTERVAL_MS 1000  //100ms
#define GATT_CON_INTERVAL_SLOT  1600 //160*625us=100ms
#define TMALL_GLP_DELY_TIMEOUT 100   //100ms
#define TMALL_GLP_PROVISIONING_TIMEOUT 45000   //15s
enum delay_status
{
  GLP_IDLE,  
  GLP_DELAY_NODE_DELETE_START,
  GLP_WAIT_START_PROVISIONING
};


enum st_tmall_glp
{
    ST_GLP_EN_TMALL_MESH = 0x0000, 
    ST_GLP_DIS_TMALL_MESH,
    ST_GLP_TMALL_MESH_PROVISIONED        
};

static enum delay_status glp_dely_status = GLP_IDLE;
static struct builtin_timer *tmall_glp_dly_timer_inst = NULL;
uint16_t st_glp_node =ST_GLP_DIS_TMALL_MESH; 
uint16_t len_st_glp_node=2; 
static bool start_provisioning= false;
static void ls_tmall_glp_dly_timer_cb(void *param);
#endif

uint8_t ali_pid[TRIPLE_PID_LEN] = {0};
uint32_t ali_pid_u32 = 6668605;
uint8_t ali_mac[TRIPLE_MAC_LEN] = {0x18,0x14,0x6c,0x7e,0x23,0x1e};
uint8_t ali_secret[TRIPLE_SECRET_LEN] = {0x7d,0x23,0xf0,0x5c,0xb0,0xa1,0x41,0xe9,0xe6,0x86,0xbf,0x1b,0x17,0x17,0x18,0x96};

uint8_t ali_authvalue[ALI_AUTH_VALUE_LEN] = {0};

uint8_t rsp_data_info[40] = {0};
uint8_t tmall_ModelHandle = 0;

static uint8_t mesh_node_appkey_bind_state = 0;
uint16_t provisioner_unicast_addr;
void create_adv_obj(void);
uint8_t connect_id = CON_IDX_INVALID_VAL; 

uint8_t adv_obj_hdl;
uint8_t advertising_data[28];
static uint8_t scan_response_data[31];

struct builtin_timer *tmall_gatt_timer_inst = NULL;
void ls_tmall_gatt_timer_cb(void *param);
/*
*   Primary Service
*/



static const struct att_decl tmall_aiots_att_decl[TMALL_AIOTS_ATT_NUM] =
{
    [TMALL_AIOTS_READ_CHAR] = {
        .uuid = att_decl_char_array_uuid,
        .s.max_len = 0, 
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_READ_VAL] = {
        .uuid = tmall_aiots_read_char_uuid,
        .s.max_len = 0,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_WRITE_CHAR] = {
        .uuid = att_decl_char_array_uuid,
        .s.max_len = 0,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_WRITE_VAL] = {
        .uuid = tmall_aiots_write_req_char_uuid,
        .s.max_len = TMALL_AIOTS_SVC_MAX_DATA_LEN,
        .char_prop.wr_req = 1,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_IND_CHAR] = {
        .uuid = att_decl_char_array_uuid,
        .s.max_len = 0,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_IND_VAL] = {
        .uuid = tmall_aiots_indic_char_uuid,
        .s.max_len = TMALL_AIOTS_SVC_MAX_DATA_LEN,
        .char_prop.ind_en = 1,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_IND_CCC] = {
        .uuid = att_client_char_cfg_uuid,
        .s.max_len = 0,
        .char_prop.ind_en =1,
        .char_prop.wr_req = 1,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_WRITE_CMD_CHAR] = {
        .uuid = att_decl_char_array_uuid,
        .s.max_len = 0,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_WRITE_CMD_VAL] = {
        .uuid = tmall_aiots_write_cmd_char_uuid,
        .s.max_len = TMALL_AIOTS_SVC_MAX_DATA_LEN,
        .char_prop.wr_cmd = 1,
        .char_prop.rd_en  = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_NTF_CHAR] = {
        .uuid = att_decl_char_array_uuid,
        .s.max_len = 0,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_NTF_VAL] = {
        .uuid = tmall_aiots_notify_char_uuid,
        .s.max_len = TMALL_AIOTS_SVC_MAX_DATA_LEN,
        .char_prop.ntf_en = 1,
        .char_prop.rd_en  = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
    [TMALL_AIOTS_NTF_CCC] = {
        .uuid = att_client_char_cfg_uuid,
        .s.max_len = 0,
        .char_prop.wr_req = 1,
        .char_prop.ntf_en = 1,
        .char_prop.rd_en = 1,
        .s.read_indication = 1,
        .s.uuid_len = UUID_LEN_16BIT,
    },
};

static const struct svc_decl tmall_aiots_server_svc =
{
    .uuid = tmall_aiots_primary_service_uuid,
    .att = (struct att_decl*)tmall_aiots_att_decl,
    .nb_att = TMALL_AIOTS_ATT_NUM,
    .uuid_len = UUID_LEN_16BIT,
};



void auto_check_unbind(void)
{
    uint16_t length = 1;
    uint8_t coutinu_power_up_num = 0;
    tinyfs_read(mesh_dir, RECORD_KEY1, &coutinu_power_up_num, &length);
    LOG_I("coutinu_power_up_num:%d", coutinu_power_up_num);

    if (coutinu_power_up_num > 4)
    {
        coutinu_power_up_num = 0;
        genie_time_data_erase();
        tinyfs_write(mesh_dir, RECORD_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        if ((Node_Get_Proved_State == PROVISIONED_OK) || (Node_Proved_State == MESH_PROV_SUCCEED))
        {
            Node_Get_Proved_State = UNPROVISIONING;
            Node_Proved_State = MESH_PROV_STARTED;
        }
    }
    else
    {
        coutinu_power_up_num++;
        tinyfs_write(mesh_dir, RECORD_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        tinyfs_write_through();
    }
}

void enable_tx_unprov_beacon(void)
{
    struct bcn_start_unprov_param info;
    info.DevUuid[0] = 0xA8;
    info.DevUuid[1] = 0x01;
    info.DevUuid[2] = 0x71;
    memcpy(&info.DevUuid[3], &ali_pid[0], TRIPLE_PID_LEN);
    memcpy(&info.DevUuid[3 + TRIPLE_PID_LEN], &ali_mac[0], TRIPLE_MAC_LEN);
    info.DevUuid[13] = TMALL_NEW_FEATURE_FLAG;
    info.DevUuid[14] = 0x00;
    info.DevUuid[15] = TMALL_NEW_FEATURE_FLAG2;  //TIMER_V2_FLAG
    info.UriHash = 0xd97478b3;
    info.OobInfo = 0x0000;
    info.UriHash_Present = false;
    start_tx_unprov_beacon(&info);
}

void disable_tx_unprov_beacon(void)
{
    stop_tx_unprov_beacon();
}

#if (TMALL_GLP_ENABLE)
static void ls_tmall_glp_dly_timer_cb(void *param)
{
    switch(glp_dely_status)
    {
        case GLP_DELAY_NODE_DELETE_START:
        {
           gatt_mesh_src_addr = TMALL_GATT_SRC_ADDR_INVALID;
           tinyfs_del_record(mesh_dir, RECORD_ST_GLP_NODE);
           SIGMESH_UnbindAll();
           platform_reset(0);
        }
        break;
        case GLP_WAIT_START_PROVISIONING:
        {
            if (start_provisioning == false)
            {
               platform_reset(0);
            }
        }
        default:
          break;   
    }  
}

static void ls_tmall_glp_dly_timer_init(void)
{
    tmall_glp_dly_timer_inst = builtin_timer_create(ls_tmall_glp_dly_timer_cb);
}

static void tmall_glp_enable_handler(void)
{
      struct start_glp_info param;
         param.RxDelyMs = TMALL_GLP_SCAN_MS;
         param.SleepIntvlMs = TMALL_GLP_SLEEP_MS;
         start_glp_handler(&param);
         app_status_set(false);
}

void ls_sig_mesh_set_proxy_con_interval(uint16_t *interval_ms)
{
    *interval_ms = PROXY_CON_INTERVAL_MS;
}

 void ls_sig_mesh_set_pb_gatt_con_interval(uint16_t *interval_slot)  /**< 1slot=625us */
 {
    *interval_slot = GATT_CON_INTERVAL_SLOT;
 }
 
void prov_foundation_mdl_cfg_svr_rsp(uint32_t opcode,uint16_t status)
{
    if ((opcode == FOUNDATION_MDL_CONFG_APPKEY_STATUS) && (status == STATUS_SIGMESH_NO_ERROR) && (mesh_node_prov_state == true))
    {
        st_glp_node = ST_GLP_TMALL_MESH_PROVISIONED;
        tinyfs_write(mesh_dir, RECORD_ST_GLP_NODE, (uint8_t *)&st_glp_node, sizeof(len_st_glp_node));
        tinyfs_write_through();
        tmall_glp_enable_handler();
    }
}
#endif

void report_provisioner_unicast_address_ind(uint16_t unicast_address)
{
    provisioner_unicast_addr = unicast_address;
    tinyfs_write(mesh_dir, RECORD_KEY2, (uint8_t *)&unicast_address, sizeof(unicast_address));
    tinyfs_write_through();
}

void ls_sig_mesh_con_set_scan_rsp_data(uint8_t *scan_rsp_data, uint8_t *scan_rsp_data_len)
{
       uint8_t tmp_scnrsp_data_len=0;

       //AD struct2  //UUID16_SOME
        scan_response_data[tmp_scnrsp_data_len] = AD_STRUCT_UU16_DATA_LEN + 1; //+1 adv type
        scan_response_data[tmp_scnrsp_data_len+1] = AD_TYPE_UUID16;
        memcpy(&scan_response_data[tmp_scnrsp_data_len+2],tmall_aiots_primary_service_uuid, AD_STRUCT_UU16_DATA_LEN);
       tmp_scnrsp_data_len = AD_STRUCT_UU16_DATA_LEN+2;
       //rsp Manufacturer Specific Data
       struct tmall_aiot_adv_data *tmall_aiot_set_data = (struct tmall_aiot_adv_data *)(&scan_response_data[tmp_scnrsp_data_len]); 
        tmall_aiot_set_data->length = MANU_SPEC_DATA_LEN;
        tmall_aiot_set_data->type = AD_TYPE_MANU_SPEC_DATA;
        tmall_aiot_set_data->cid[0] = ALI_COMPANY_ID_LSB;          //ali company identifiers low byte
        tmall_aiot_set_data->cid[1] = ALI_COMPANY_ID_MSB;          //ali company identifiers high byte
        tmall_aiot_set_data->aiot_info.b.vid = 0x05;                 //ali ble version 5
        tmall_aiot_set_data->aiot_info.b.subtype = SUBTY_BLE_GATT_MESH; //ali gatt mesh type
        tmall_aiot_set_data->fmsk.b.ble_version = 0x01;              //ble5.0
        tmall_aiot_set_data->fmsk.b.ota_option = true;
        tmall_aiot_set_data->fmsk.b.security_option = true;
        tmall_aiot_set_data->fmsk.b.security_mode = 1;               //0: Mode a secret 1: device a secret
        tmall_aiot_set_data->fmsk.b.adv_mode = 1;
        memcpy( &tmall_aiot_set_data->pid[0],(uint8_t *)(&ali_pid_u32), ALI_PID_LENGTH);
        memcpy( &tmall_aiot_set_data->mac[0],&ali_mac[0], ALI_MAC_LENGTH);
        tmp_scnrsp_data_len += sizeof(struct tmall_aiot_adv_data)/sizeof(uint8_t);
        memcpy(scan_rsp_data,scan_response_data,tmp_scnrsp_data_len);
        *scan_rsp_data_len = tmp_scnrsp_data_len;
}  

void tmall_mesh_add_subscription(uint16_t element, uint8_t model_lid, uint16_t group_address)
{
    uint8_t element_offset = element - ls_sig_mesh_get_primary_address();

    for(uint8_t i=0;i<model_env.nb_model;i++)
    {
     //do tmall hardware node reset event
         
      if ((model_env.info[i].element_id == element_offset) && (model_env.info[i].model_lid != model_lid))
         {
           model_subscribe(model_env.info[i].model_lid, group_address); 
      }
    }
}


void tmall_mesh_delete_subscription(uint16_t element, uint8_t model_lid, uint16_t group_address)
{
    uint8_t element_offset = element - ls_sig_mesh_get_primary_address();
    for(uint8_t i=0;i<model_env.nb_model;i++)
    {   
      if ((model_env.info[i].element_id == element_offset) && (model_env.info[i].model_lid != model_lid))
      {
           model_unsubscribe(model_env.info[i].model_lid, group_address); 
      }    
    }
}

static void gap_manager_callback(enum gap_evt_type type, union gap_evt_u *evt, uint8_t con_idx)
{
    switch (type)
    {
    case CONNECTED:
    {
        connect_id = con_idx;
       if (mesh_node_prov_state == false) 
       {
          start_provisioning = true;
          builtin_timer_stop(tmall_glp_dly_timer_inst);
       }
       else
       {
         genie_ais_connect();
         ais_server_ntf_done =true;
       }
        LOG_I("connected!");
    }
        break;
    case DISCONNECTED:
         connect_id = CON_IDX_INVALID_VAL;
         LOG_I("DISCONNECTED!");
         LOG_I("disconnect_reason=%x",evt->disconnected.reason);
          gatt_mesh_src_addr = TMALL_GATT_SRC_ADDR_INVALID;
         if (mesh_node_prov_state == false)
         {
           glp_dely_status = GLP_WAIT_START_PROVISIONING;
           builtin_timer_start(tmall_glp_dly_timer_inst, TMALL_GLP_PROVISIONING_TIMEOUT, NULL);  
         }
         else
         {
            ais_server_ntf_done = false;
            genie_ais_disconnect(evt->disconnected.reason);
         } 
        break;
    case CONN_PARAM_REQ:
         LOG_I("PARAM_REQ!");
        break;
    case CONN_PARAM_UPDATED:
        LOG_I("PARAM_UPDATED!");
        break;
    default:

        break;
    }
}

static void gatt_manager_callback(enum gatt_evt_type type, union gatt_evt_u *evt, uint8_t con_idx)
{
     switch (type)
    {
    case SERVER_READ_REQ:
        LOG_I("SERVER_READ_REQ!");
    break;
    case SERVER_WRITE_REQ:
        LOG_I("SERVER_WRITE_REQ!");  
        ais_server_write_req_handle((void *)evt->server_write_req.value, evt->server_write_req.length);    
    break;
    case SERVER_NOTIFICATION_DONE:
        ais_server_ntf_done =true;
        LOG_I("SERVER_NOTIFICATION_DONE!");
    break;
    case MTU_CHANGED_INDICATION:
        LOG_I("MTU_CHANGED_INDICATION!");
    break;
     case SERVER_INDICATION_DONE:
      LOG_I("SERVER_INDICATION_DONE!");
    break;
    default:
        LOG_I("Event not handled!");
        break;
    }
}

static void generic_onoff_status_report(uint8_t model_index, uint32_t opcode)
{
    struct model_send_info onoff_rsp;
    onoff_rsp.ModelHandle = model_env.info[model_index].model_lid; 
    onoff_rsp.app_key_lid = mesh_key_lid; 
    onoff_rsp.opcode = opcode;  
    onoff_rsp.dest_addr = gatt_mesh_src_addr;
    onoff_rsp.len = 1; 
    onoff_rsp.info[0] = 0xff;
    model_send_info_handler(&onoff_rsp);
}

static void mesh_manager_callback(enum mesh_evt_type type, union ls_sig_mesh_evt_u *evt)
{
    switch (type)
    {
    case MESH_ACTIVE_ENABLE:
    {   
#if (TMALL_GLP_ENABLE)        
       if (mesh_node_prov_state == true)
        {
           tmall_glp_enable_handler();
        }

        if (st_glp_node == ST_GLP_EN_TMALL_MESH) 
       {
           glp_dely_status = GLP_WAIT_START_PROVISIONING;
           builtin_timer_start(tmall_glp_dly_timer_inst, TMALL_GLP_PROVISIONING_TIMEOUT, NULL);  
       }
#endif            
        gatt_mesh_src_addr = TMALL_GATT_SRC_ADDR_INVALID;
        TIMER_Set(2, 3000); //clear power up num
    }
    break;
    case MESH_ACTIVE_DISABLE:
    {
	  genie_time_finalize();
#if (TMALL_GLP_ENABLE)         
        if (mesh_node_prov_state == true)
#endif        
        {
          glp_dely_status = GLP_DELAY_NODE_DELETE_START;
          builtin_timer_start(tmall_glp_dly_timer_inst, TMALL_GLP_DELY_TIMEOUT, NULL);  
        }     
    }
    break;
    case MESH_ACTIVE_REGISTER_MODEL:
    {
        for (uint8_t i = 0; i < model_env.nb_model; i++)
        {
            model_env.info[i].model_lid = evt->sig_mdl_info.info[i].model_lid;
        }
        model_env.app_key_lid = evt->sig_mdl_info.app_key_lid;
        mesh_node_appkey_bind_state = 1;
        tinyfs_write(mesh_dir, RECORD_KEY3, &mesh_node_appkey_bind_state, sizeof(mesh_node_appkey_bind_state));
        tinyfs_write_through();

        model_subscribe(model_env.info[0].model_lid, 0xC000); //group address 0xc000
        model_subscribe(model_env.info[1].model_lid, 0xC000); //group address 0xc000
        model_subscribe(model_env.info[2].model_lid, 0xC000); //group address 0xc000
        model_subscribe(model_env.info[3].model_lid, 0xC000); //group address 0xc000
        model_subscribe(model_env.info[4].model_lid, 0xC000); //group address 0xc000
    }
    break;
    case MESH_ACTIVE_MODEL_GROUP_MEMBERS:
    {
        LOG_I("Prov Succeed");
        // tmall_light_set_lightness(0xFFFF);
    }
    break;
    case MESH_ACTIVE_MODEL_RSP_SENT:
    {
        
        if (gatt_mesh_model_indx !=TMALL_GATT_MESH_MODEL_INDEX_INVALID)
        {
           if((gatt_mesh_model_indx++)<=model_env.nb_model)
           {
              generic_onoff_status_report(gatt_mesh_model_indx, GENERIC_ONOFF_STATUS);
           }
           else
           {
              gatt_mesh_model_indx=TMALL_GATT_MESH_MODEL_INDEX_INVALID;
           }
        } 
    }
    break;
    case MESH_ACTIVE_STORAGE_LOAD:
    {
         uint16_t length = sizeof(mesh_node_appkey_bind_state);
        Node_Get_Proved_State = evt->st_proved.proved_state;
        tinyfs_read(mesh_dir, RECORD_KEY3, &mesh_node_appkey_bind_state, &length);
        if ((Node_Get_Proved_State == PROVISIONED_OK) && (mesh_node_appkey_bind_state == 1))
        {
            uint16_t length = sizeof(provisioner_unicast_addr);
            LOG_I("src_addr=%x",provisioner_unicast_addr);
            LOG_I("The node is provisioned");
            // tmall_light_set_lightness(0xffff);
            tinyfs_read(mesh_dir, RECORD_KEY2, (uint8_t*)&provisioner_unicast_addr, &length);    
            mesh_node_prov_state = true;       
        }
		else if (Node_Get_Proved_State == PROVISIONED_OK) 
        {
            LOG_I("provising failed!");
            mesh_node_appkey_bind_state = 0;
            tinyfs_write(mesh_dir, RECORD_KEY3, &mesh_node_appkey_bind_state, sizeof(mesh_node_appkey_bind_state));
            genie_time_data_erase();
			mesh_node_prov_state = false;
            SIGMESH_UnbindAll();
            platform_reset(0);
        }
        else
        {
            mesh_node_prov_state = false;
            LOG_I("The node is not provisioned");
        }
        
    }
    break;
    case MESH_GET_PROV_INFO:
    {
        struct mesh_prov_info param;
        param.DevUuid[0] = 0xA8;
        param.DevUuid[1] = 0x01;
        param.DevUuid[2] = 0x71;
        memcpy(&param.DevUuid[3], &ali_pid[0], TRIPLE_PID_LEN);
        memcpy(&param.DevUuid[3 + TRIPLE_PID_LEN], &ali_mac[0], TRIPLE_MAC_LEN);
        param.DevUuid[13] = TMALL_NEW_FEATURE_FLAG;
        param.DevUuid[14] = 0x00;
        param.DevUuid[15] = TMALL_NEW_FEATURE_FLAG2;  
        param.UriHash = 0xd97478b3;
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
        memcpy(&param.AuthBuffer[0], &ali_authvalue[0], ALI_AUTH_VALUE_LEN);
        param.AuthSize = ALI_AUTH_VALUE_LEN;
        set_prov_auth_info(&param);
    }
    break;
    case MESH_STATE_UPD_IND:
    {
        if (mesh_node_prov_state == true)
        {
            if((evt->update_state_param.upd_type == UPADTE_TMALL_GATT_SRC_ADDR_TYPE) && (gatt_mesh_src_addr==TMALL_GATT_SRC_ADDR_INVALID))
            {
                 memcpy((uint8_t *)&gatt_mesh_src_addr, &(evt->update_state_param.data[0]), 2);
                 LOG_I("MESH_STATE_UPD_IND=%4x", gatt_mesh_src_addr);
                 gatt_mesh_model_indx=0;
                 generic_onoff_status_report(gatt_mesh_model_indx,GENERIC_ONOFF_STATUS);
            }
        }

#if (TMALL_GLP_ENABLE)    
        if(evt->update_state_param.upd_type == UPADTE_GLP_STOP_TYPE)
        {  
           start_provisioning = true;
           builtin_timer_stop(tmall_glp_dly_timer_inst);
        }

        if (Node_Proved_State == MESH_PROV_FAILED)
        {
           glp_dely_status = GLP_WAIT_START_PROVISIONING;
           builtin_timer_start(tmall_glp_dly_timer_inst, TMALL_GLP_PROVISIONING_TIMEOUT, NULL);  
        }

       if (evt->update_state_param.upd_type == UPADTE_GLP_STOP_TIMEOUT_TYPE)
       {
          app_status_set(false);		//false lowpower
       } 
#endif      
    }
    break; 
    case MESH_GENIE_PROV_COMP:
    {
#if (TMALL_GLP_ENABLE)        
        if (connect_id != INVALID_CON_IDX)
        {
           tmall_glp_enable_handler();
        }
 #endif       
    }
    break;    
    case MESH_REPOPT_PROV_RESULT:
    {
      	Node_Proved_State = evt->prov_rslt_sate.state;  
        if (Node_Proved_State == MESH_PROV_SUCCEED)
        {
             mesh_node_prov_state = true;  
        }
       
    }
    break;
    case MESH_ACCEPT_MODEL_INFO:
    {
        if(evt->rx_msg.ModelHandle == model_env.info[0].model_lid)
        {
            tmall_mesh_recv_onoff_msg(&evt->rx_msg);
        }
        else if(evt->rx_msg.ModelHandle == model_env.info[1].model_lid)
        {
            tmall_mesh_recv_vendor_msg(&evt->rx_msg);
        }
        else if(evt->rx_msg.ModelHandle == model_env.info[2].model_lid)
        {
            tmall_mesh_recv_lightness_msg(&evt->rx_msg);
        }
        else if(evt->rx_msg.ModelHandle == model_env.info[3].model_lid)
        {
            tmall_mesh_recv_light_ctl_msg(&evt->rx_msg);
        }
        else if(evt->rx_msg.ModelHandle == model_env.info[4].model_lid)
        {
            tmall_mesh_recv_light_hsl_msg(&evt->rx_msg);
        }    
    }
    break;
    case MESH_REPORT_TIMER_STATE:
    {
        if (2 == evt->mesh_timer_state.timer_id)
        {
            uint8_t clear_power_on_num = 0;
            TIMER_Cancel(2);
            tinyfs_write(mesh_dir, RECORD_KEY1, &clear_power_on_num, sizeof(clear_power_on_num));
            tinyfs_write_through();
        }
    }
    break;
    case MESH_ADV_REPORT:
    {
        if(evt->adv_report.adv_addr->addr[5] == 0x20 && evt->adv_report.adv_addr->addr[4] == 0x17)
        {
            LOG_I("dev addr: %02x:%02x:%02x:%02x:%02x:%02x",evt->adv_report.adv_addr->addr[5],
                                                            evt->adv_report.adv_addr->addr[4],
                                                            evt->adv_report.adv_addr->addr[3],
                                                            evt->adv_report.adv_addr->addr[2],
                                                            evt->adv_report.adv_addr->addr[1],
                                                            evt->adv_report.adv_addr->addr[0]);
            //LOG_HEX(evt->adv_report.adv_addr.addr,6);
            LOG_HEX(evt->adv_report.data,evt->adv_report.length);
        }
        
    }
    break;
    default:
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
            .private_addr = true,
            .controller_privacy = false,
        };
        dev_manager_set_mac_addr(&ali_mac[0]);
        dev_manager_stack_init(&cfg);
    }
    break;

    case STACK_READY:
    {
        uint8_t addr[6];
        bool type;
        dev_manager_get_identity_bdaddr(addr, &type);
        dev_manager_add_service((struct svc_decl *)&tmall_aiots_server_svc); 
    }
    break;

    case SERVICE_ADDED:
    {
        gatt_manager_svc_register(evt->service_added.start_hdl, TMALL_AIOTS_ATT_NUM, &tmall_aiots_svc_env);
        
        struct ls_sig_mesh_cfg feature = {
            .MeshFeatures = EN_RELAY_NODE | EN_MSG_API | EN_PB_GATT | EN_PROXY_NODE,
            .MeshCompanyID = ALI_COMPANY_ID,
            .MeshProID = 0,
            .MeshProVerID = 0,
            .MeshLocDesc = 0,
            .NbAddrReplay  = MAX_NB_ADDR_REPLAY,
            .NbCompDataPage = COMPA_DATA_PAGES,
        };

        dev_manager_prf_ls_sig_mesh_add(NO_SEC, &feature);
    }
    break;
    case PROFILE_ADDED:
    {
        prf_ls_sig_mesh_callback_init(mesh_manager_callback);
        model_env.nb_model = 2;
        model_env.info[0].model_id = GENERIC_ONOFF_SERVER;
        model_env.info[0].element_id = 0;
        model_env.info[1].model_id = VENDOR_TMALL_SERVER;
        model_env.info[1].element_id = 0;  
         
#if (TMALL_GLP_ENABLE) 
        ls_tmall_glp_dly_timer_init();
		ls_genie_ais_timer_init();            
       if ((tinyfs_read(mesh_dir, RECORD_ST_GLP_NODE, (uint8_t*)&st_glp_node, &len_st_glp_node)) !=TINYFS_NO_ERROR)
       {
          st_glp_node = ST_GLP_DIS_TMALL_MESH;
          tinyfs_write(mesh_dir, RECORD_ST_GLP_NODE, (uint8_t *)&st_glp_node, sizeof(len_st_glp_node));
          tinyfs_write_through();
       }

        if (SYSCFG->BKD[0] == TMALL_GLP_RST_FLAG)
        {
          SYSCFG->BKD[0] = 0;  
          st_glp_node = ST_GLP_EN_TMALL_MESH; 
        }

        if ((st_glp_node == ST_GLP_TMALL_MESH_PROVISIONED) || (st_glp_node == ST_GLP_EN_TMALL_MESH))
        {    
            app_status_set(true);     
            ls_sig_mesh_init(&model_env);
            auto_check_unbind();
        }
        else
        {
           st_glp_node = ST_GLP_DIS_TMALL_MESH;
           app_status_set(false);
        }
#else
        app_status_set(true);
        ls_tmall_glp_dly_timer_init();
        ls_sig_mesh_init(&model_env);
        auto_check_unbind();
#endif        
    }
    break;
    default:
        break;
    }
}

void exti_io_enable(void)
{
    io_cfg_input(PA07);    //PA00 config input
    io_pull_write(PA07, IO_PULL_UP);    //PA00 config pullup
    io_exti_config(PA07,INT_EDGE_FALLING);    //PA00 interrupt falling edge
}

int main()
{
    sys_init_app();
    mesh_stack_data_bss_init();
	ble_init();
    exti_io_enable();
    #if (UART_TEST)
    ls_uart_init();
    #endif // (UART_TEST)
    gen_ali_authValue();
    genie_triple_init();
    tinyfs_mkdir(&mesh_dir, ROOT_DIR, 10);
    ls_genie_ais_fw_version_init();
    dev_manager_init(dev_manager_callback);
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
}

void io_exti_callback(uint8_t pin,exti_edge_t edge)
{
    if (pin == PA07)
    {
        if(st_glp_node == ST_GLP_DIS_TMALL_MESH)
        {
           disable_global_irq(); 
           SYSCFG->BKD[0] = TMALL_GLP_RST_FLAG;
          platform_reset(0);
        } 
    }
}
