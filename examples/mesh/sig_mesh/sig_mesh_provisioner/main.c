#define LOG_TAG "MAIN"
#include <string.h>
#include <stdio.h>
#include "ls_ble.h"
#include "platform.h"
#include "ls_sig_mesh.h"
#include "ls_sig_mesh_provisioner.h"
#include "ls_sig_mesh.h"
#include "sig_mesh_prover_ctl.h"
#include "log.h"
#include "ls_dbg.h"
#include "ls_hal_flash.h"
#include "tinyfs.h"
#include "field_manipulate.h"
#include "le501x.h"
#include "at_sig_mesh_prover_recv_cmd.h"
#include "at_sig_mesh_prover_cmd_ind.h"

#define COMPANY_ID 0x093A
#define COMPA_DATA_PAGES 1
#define MAX_NB_ADDR_REPLAY 20
#define CNT_NETWORK_TRANS  5
#define INTERVAL_NETWORK_TRANS 2
#define PROV_AUTH_ACCEPT   1
#define PROV_AUTH_NOACCEPT 0
#define RECORD_PROVER_KEY1 1
#define RECORD_PROVER_NETKEY_LID 2
#define RECORD_PROVER_APPKEY_LID 3
#define DEV_NAME_MAX_LEN 0x20
#define INVALID_MODEL_LID 0xff
#define INVALID_KEY_LID 0xff

#define PROVER_UNICAST_ADDR 0x0001
#define NODE_BASE_UNICAST_ADDR  0x0002

uint16_t lid_length = 1;
extern uint16_t node_unicast_address;
tinyfs_dir_t ls_sigmesh_provision_dir;
struct mesh_model_info model_env;
struct mesh_publish_info_ind mesh_publish_env[MAX_MESH_MODEL_NB];
static uint8_t model_tid = 0;
uint8_t usr_mac_addr[6]= {12,12,13,14,15,16}; //5#
char ble_device_name[DEV_NAME_MAX_LEN] = "ls_sig_mesh_provisioner";
/*
auth data
*/
static uint8_t prover_auth_data[16] = {0xF4,0xC7,0x0B,0xE8,0x10,0xE1,0x3A,0xAE,0xF8,0x3B,0x05,0xD4,0xA1,0xDA,0x8C,0xF3};

/*
 Network Keys
*/
#define COMPO_DATA_PAGE0 0
#define NETKEY_ID0 2
#define APPKEY_ID0 0

uint8_t netkey[NETKEY_ID0+1][MESH_KEY_LENGTH]={{0x00,0x2b,0x1e,0xdc,0x3d,0x17,0x4f,0x06,0x29,0x80,0x8a,0x8e,0x4f,0xa4,0xa2,0xf7}}; //0xf7a2a44f8e8a8029064f173ddc1e2b00
#define APPKEY_ID0 0
uint8_t appkey[APPKEY_ID0+1][MESH_KEY_LENGTH]={{0x98,0x7f,0x87,0x2b,0x79,0x41,0x85,0x24,0x33,0xb5,0x84,0x98,0x50,0xd1,0x16,0x32}};  //0x3216d1509884b533248541792b877f98


uint8_t devkey[MESH_KEY_LENGTH]={0};
uint8_t devkey_lid=0;
uint8_t netkey_lid=INVALID_KEY_LID;
uint8_t appkey_lid=INVALID_KEY_LID;
uint16_t recode_key_length=1;
uint8_t health_client_model_lid=0;

struct node_element_id_info
{
   uint8_t max_num_elements;
   uint8_t elements_id;
};

struct node_element_id_info node_elt;

static void gatt_manager_callback(enum gatt_evt_type type, union gatt_evt_u *evt, uint8_t con_idx){}
static void gap_manager_callback(enum gap_evt_type type, union gap_evt_u *evt, uint8_t con_idx){}

static void prover_mesh_manager_rx_ind_callback(enum mesh_provisioner_rx_ind_type type, union ls_sig_mesh_provisioner_rx_info_u *evt)
{
   switch (type)
    {
    case MESH_PROVER_ACTIVE_NODE_FOUND:
    { 
            uint8_t dev_uuid[16]={0};
            int8_t rssi;
            memcpy(&dev_uuid[0],&(evt->prover_node_scan_info.dev_uuid[0]),UUID_MESH_DEV_LEN);
            rssi = evt->prover_node_scan_info.rssi;
            at_prover_report_dev_uuid(&dev_uuid[0],rssi);
    }
    break;
    case MESH_PROVER_ACTIVE_NODE_GATT:
    break;
    case MESH_PROVER_ACTIVE_NODE_STOPPED:
    break;
    case MESH_PROVER_ACTIVE_PROXY_SVC:
    break;
    case MESH_PROVER_ACTIVE_STATE:
    {
         at_prover_report_provisiong_status(evt->prover_node_state_info.state,evt->prover_node_state_info.status,evt->prover_node_state_info.unicast_addr);
        if (evt->prover_node_state_info.state == PROVISIONING_SUCCEED)
        {
            ls_sig_mesh_prover_config_client_get(CONFIG_CLIENT_GET_TYPE_DFLT_TTL,0); 
        }
    }
    break;
    
    case MESH_PROVER_CONFC_COMP_DATA_PAGE0:
    {
        node_elt.max_num_elements = evt->confc_get_compo_data_info.dev_nb_elements;
        node_elt.elements_id = 0;
        at_prover_report_dev_composition_data0(evt->confc_get_compo_data_info.unicast_addr, evt->confc_get_compo_data_info.company_id, evt->confc_get_compo_data_info.product_id, evt->confc_get_compo_data_info.version_id, evt->confc_get_compo_data_info.support_features,evt->confc_get_compo_data_info.dev_nb_elements);
    }
    break;
    case MESH_PROVER_CONFC_COMP_DATA_PAGE0_ELEMENT:
    {
        at_prover_report_dev_composition_data0_element(evt->confc_get_compo_data_element_info.unicast_addr+node_elt.elements_id, evt->confc_get_compo_data_element_info.number_sig_models, evt->confc_get_compo_data_element_info.number_vendor_models, (uint8_t *)&(evt->confc_get_compo_data_element_info.model_info[0]));
        if (node_elt.elements_id !=(node_elt.max_num_elements-1))
        {
            node_elt.elements_id++;
        }
        else
        {
          ls_sig_mesh_prover_config_client_set(CONFIG_CLIENT_SET_TYPE_NET_TX,0/*no_use*/,CNT_NETWORK_TRANS,INTERVAL_NETWORK_TRANS);
        }
    }
    break;
    case MESH_PROVER_CONFC_GET_DEFAULT_TTL_STATUS:
        at_prover_report_dev_default_ttl(evt->confc_get_default_ttl_info.unicast_addr,evt->confc_get_default_ttl_info.default_ttl);
    break;
    case MESH_PROVER_CONFC_APP_KEY_STATUS:
        at_prover_report_node_app_key_status(evt->confc_get_app_key_status_info.unicast_addr,evt->confc_get_app_key_status_info.active_status,evt->confc_get_app_key_status_info.net_key_id,evt->confc_get_app_key_status_info.app_key_id);
        at_prover_report_dev_key(evt->confc_get_app_key_status_info.unicast_addr,&devkey[0]);
    break;
    case MESH_PROVER_CONFC_MODEL_SUBS_STATUS:
        at_prover_report_model_subs_status(evt->confc_model_subs_app_status_info.unicast_addr,evt->confc_model_subs_app_status_info.status,evt->confc_model_subs_app_status_info.element_addr,evt->confc_model_subs_app_status_info.model_id,evt->confc_model_subs_app_status_info.value);
    break;
    case MESH_PROVER_CONFC_MODEL_PUB_STATUS:
        at_prover_report_model_pub_status(evt->confc_model_pubs_status_info.unicast_addr,evt->confc_model_pubs_status_info.status,evt->confc_model_pubs_status_info.element_addr,evt->confc_model_pubs_status_info.publish_addr,evt->confc_model_pubs_status_info.app_key_id,evt->confc_model_pubs_status_info.cred_flag,evt->confc_model_pubs_status_info.publish_ttl,evt->confc_model_pubs_status_info.publish_period_ms,evt->confc_model_pubs_status_info.publish_retx_cont,evt->confc_model_pubs_status_info.publish_retx_intv_step_solution,evt->confc_model_pubs_status_info.model_id);
    break;
    case MESH_PROVER_CONFC_MODEL_APP_STATUS:
        at_prover_report_model_app_status(evt->confc_model_subs_app_status_info.unicast_addr,evt->confc_model_subs_app_status_info.status,evt->confc_model_subs_app_status_info.element_addr,evt->confc_model_subs_app_status_info.model_id,evt->confc_model_subs_app_status_info.value);
    break;
    case MESH_PROVER_CONFC_NET_TX_STATUS:
        ls_sig_mesh_prover_config_client_active_appkey(CONFIG_CLIENT_ADD_APP_KEY_TYPE,NETKEY_ID0,APPKEY_ID0,&appkey[0][0]);
      break;    
      default:
        break;
    }    
}

static void prover_mesh_manager_callback(enum mesh_provisioner_evt_type type, union ls_sig_mesh_provisioner_evt_u *evt)
{
    switch (type)
    {
    case MESH_PROVER_GET_PROV_AUTH_INFO:
     {
        struct mesh_prov_auth_info param;
        param.Adopt = PROV_AUTH_ACCEPT;
        memcpy(&param.AuthBuffer[0], &prover_auth_data[0], 16);
        param.AuthSize = 16;
        app_mesh_prover_set_prov_auth_info(&param);
     }
    break;       
    case MESH_PROVER_KEY_DEV_ADD_RSP_INFO:
    { 
       devkey_lid =  evt->prover_node_add_dev_key_rsp_info.dev_key_lid;
       memcpy(&devkey[0],&evt->prover_node_add_dev_key_rsp_info.dev_key[0],BLE_KEY_LEN);
       ls_sig_mesh_prover_config_set_dev(devkey_lid,netkey_lid,(node_unicast_address)/*dev primary unicast address*/);
    }
    break;
    case MESH_PROVER_HEALTH_MODEL_RSP_INFO:
    {
       health_client_model_lid =  evt->prover_node_health_model_rsp_info.mdl_lid;
        at_prover_ready_ind();

        tinyfs_read(ls_sigmesh_provision_dir, RECORD_PROVER_NETKEY_LID, &netkey_lid, &recode_key_length);
        tinyfs_read(ls_sigmesh_provision_dir, RECORD_PROVER_APPKEY_LID, &appkey_lid, &recode_key_length);
        LOG_I("netkey_lid=%d",netkey_lid);
        LOG_I("appkey_lid=%d",appkey_lid);
        if (netkey_lid == INVALID_KEY_LID)
        {
          ls_sig_mesh_provisioner_add_net_key(NETKEY_ID0,&netkey[0][0]);  
        }
    }
    break;
    case MESH_PROVER_KEY_NET_ADD_IND:
    {
        netkey_lid = evt->prover_node_add_net_key_ind_info.net_key_lid;
        LOG_I("creat_netkey_lid=%d",netkey_lid);
        tinyfs_write(ls_sigmesh_provision_dir, RECORD_PROVER_NETKEY_LID, &netkey_lid, sizeof(netkey_lid));
        tinyfs_write_through();

        if (appkey_lid == INVALID_KEY_LID)
        {
          ls_sig_mesh_provisioner_add_app_key(NETKEY_ID0,APPKEY_ID0,&appkey[0][0]);
        }
    }
    break;
     case MESH_PROVER_KEY_APP_ADD_IND:
    {
        appkey_lid = evt->prover_node_add_app_key_ind_info.app_key_lid;
         LOG_I("creat_appkey_lid=%d",appkey_lid);
        tinyfs_write(ls_sigmesh_provision_dir, RECORD_PROVER_APPKEY_LID, &appkey_lid, sizeof(appkey_lid));
        tinyfs_write_through();
    }
    break;
    case MESH_PROVER_SET_DEV_RSP_INFO:
    {
       at_prover_report_node_info(node_unicast_address,netkey_lid,devkey_lid);
    }
    break;
    case MESH_PROVER_IDENTIFY_REQ_IND_INFO:
    {
        ls_sig_mesh_identify_cfm(true /*accept*/,netkey_lid/*netkey_lid*/,0x00/*FIPS P-256 ECC*/,0x00/*No OOB Public key uesed*/,0x00/*auth_method*/,0x00/*auth_action*/,0x00/*auth_size*/);
    }
    break;
    case MESH_PROVER_REPORT_IV_SEQ_INFO:
    {
        at_prover_report_iv_seq_info(evt->prover_seq_iv_info.iv,evt->prover_seq_iv_info.seq);
    }
    break; 
    default:
       break;
    }
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
    break;
    case MESH_ACTIVE_STORAGE_LOAD:
    break;
    case MESH_GET_PROV_INFO:
    break;
    case MESH_GET_PROV_AUTH_INFO:
    {
        struct mesh_prov_auth_info param;
        param.Adopt = PROV_AUTH_ACCEPT;
        memcpy(&param.AuthBuffer[0], &prover_auth_data[0], 16);
        param.AuthSize = 16;
        set_prov_auth_info(&param);
    }
    break;
    case MESH_REPOPT_PROV_RESULT:
    break;
    case MESH_ACCEPT_MODEL_INFO:
    break;
    case MESH_STATE_UPD_IND:
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
        dev_manager_stack_init(&cfg);
        dev_manager_set_mac_addr(&usr_mac_addr[0]);
    }
    break;
    case STACK_READY:
    {
        uint8_t addr[6];
        struct ls_sig_mesh_cfg feature = {
            .MeshFeatures = EN_PROVER | EN_MSG_API /*| EN_PB_GATT*/,
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
        dev_manager_prf_ls_sig_mesh_add(NO_SEC, &feature);
    }
    break;
    case SERVICE_ADDED:
    break;
    case PROFILE_ADDED:
    {
        memset(&node_elt,0,sizeof(struct node_element_id_info));
        prf_ls_sig_mesh_provisioner_callback_init(prover_mesh_manager_callback,prover_mesh_manager_rx_ind_callback);
        prf_ls_sig_mesh_callback_init(mesh_manager_callback);
        model_env.nb_model = PROVER_MODEL_MAX_NUM;
        model_env.app_key_lid = 0;
         //client
        model_env.info[PROVER_MODEL0_GENERIC_ONOFF_CLI].sig_model_cfg_idx = MESH_CMDL_CFG_IDX_GENC_ONOFF;
        model_env.info[PROVER_MODEL0_GENERIC_ONOFF_CLI].element_id = 0;
        model_env.info[PROVER_MODEL0_GENERIC_ONOFF_CLI].model_lid = 0;
        model_env.info[PROVER_MODEL0_GENERIC_ONOFF_CLI].model_id = GENERIC_ONOFF_CLIENT;

        model_env.info[PROVER_MODEL0_VENDOR_CLI].sig_model_cfg_idx = MESH_MDL_CFG_VENDORC_INFO;
        model_env.info[PROVER_MODEL0_VENDOR_CLI].element_id = 0;
        model_env.info[PROVER_MODEL0_VENDOR_CLI].model_lid = 0;
        model_env.info[PROVER_MODEL0_VENDOR_CLI].vendor_model_role = 1;
        model_env.info[PROVER_MODEL0_VENDOR_CLI].model_id = VENDOR_USER_CLIENT;

        model_env.info[PROVER_MODEL0_VENDOR_SVR].vendor_model_cfg_idx = MESH_MDL_CFG_VENDORS_INFO;
        model_env.info[PROVER_MODEL0_VENDOR_SVR].element_id = 0;
        model_env.info[PROVER_MODEL0_VENDOR_SVR].model_lid = 0;
        model_env.info[PROVER_MODEL0_VENDOR_SVR].vendor_model_role = 0; //sever model
        model_env.info[PROVER_MODEL0_VENDOR_SVR].model_id = VENDOR_USER_SERVER;

        ls_sig_mesh_provisioner_init(PROVER_UNICAST_ADDR);
//        ls_sig_mesh_init(&model_env);
        ls_sig_mesh_prover_config_reg_model(PROVER_UNICAST_ADDR/*dev primary unicast address*/); 
         ls_sig_mesh_init(&model_env);
    }
    break;
    case ADV_OBJ_CREATED:
    break;
    case ADV_STOPPED:
    break;
    case SCAN_STOPPED:
    break;
    default:
        break;
    }
}

void auto_check_unbind(void)
{
    uint16_t length = 1;
    uint8_t coutinu_power_up_num = 0;
    tinyfs_read(ls_sigmesh_provision_dir, RECORD_PROVER_KEY1, &coutinu_power_up_num, &length);

    if (coutinu_power_up_num > 4)
    {
        coutinu_power_up_num = 0;
        tinyfs_write(ls_sigmesh_provision_dir, RECORD_PROVER_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        tinyfs_write_through();
        tinyfs_del_record(ls_sigmesh_provision_dir, RECORD_PROVER_NETKEY_LID);
        tinyfs_write_through();
        tinyfs_del_record(ls_sigmesh_provision_dir, RECORD_PROVER_APPKEY_LID);
        tinyfs_write_through();
        SIGMESH_UnbindAll();
    }
    else
    {
        coutinu_power_up_num++;
        tinyfs_write(ls_sigmesh_provision_dir, RECORD_PROVER_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        tinyfs_write_through();
    }
}

void prover_client_model_tx_message_handler(uint32_t tx_msg, uint16_t dest_addr, uint32_t model_id)
{
     struct model_cli_trans_info param;
     uint8_t publish_model_lid = INVALID_MODEL_LID;
    for (uint8_t i = 0; i < model_env.nb_model; i++)
    {
       if (model_env.info[i].model_id == model_id)
       {
          publish_model_lid = model_env.info[i].model_lid;
          break;
       }
    }

    if (publish_model_lid == INVALID_MODEL_LID) 
    {
        return;
    }  
     model_tid++;
     param.mdl_lid = publish_model_lid;
     param.app_key_lid = model_env.app_key_lid;
     param.dest_addr = dest_addr;
     param.state_1 = tx_msg;
     param.state_2 = 0x00;
     param.delay_ms = 50;
     param.trans_info = (uint16_t)(model_tid << 8);
     param.trans_time_ms = 100;
     mesh_standard_model_publish_message_handler(&param);
}

void prover_send_message_vendor_model(uint32_t vendor_opcode, uint32_t model_id, uint8_t *data, uint8_t data_len, uint16_t dest_address)
{
    struct model_send_info tx_msg_info;
    uint8_t publish_model_lid = INVALID_MODEL_LID;
    for (uint8_t i = 0; i < model_env.nb_model; i++)
    {
       if (model_env.info[i].model_id == model_id)
       {
          publish_model_lid = model_env.info[i].model_lid;
          break;
       }
    }

    if (publish_model_lid == INVALID_MODEL_LID) 
    {
        return;
    }  

    tx_msg_info.ModelHandle = publish_model_lid; 
    tx_msg_info.app_key_lid = model_env.app_key_lid; 
    tx_msg_info.dest_addr = dest_address;
    tx_msg_info.opcode = vendor_opcode; 
    tx_msg_info.len = data_len; 
    memcpy(&(tx_msg_info.info[0]),data,data_len);
    model_send_info_handler(&tx_msg_info);
}

int main()
{
    sys_init_app();
    mesh_stack_data_bss_init();
    tinyfs_mkdir(&ls_sigmesh_provision_dir, ROOT_DIR, 5);   
    ble_init();
    auto_check_unbind();
    at_init();
    dev_manager_init(dev_manager_callback);
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
    return 0;
}
