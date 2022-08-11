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
#include "sys_stat.h"
#include "tmall_mesh_ctl.h"
#include "tmall_light_cfg.h"
#include "tmall_ais_cfg.h"
#include "builtin_timer.h"
#include "ota_settings.h"


#define TMALL_GATT_TIMEOUT 5000
#define ALI_COMPANY_ID 0x01a8
#define COMPA_DATA_PAGES 1
#define TRIPLE_PID_LEN 4
#define MAX_NB_ADDR_REPLAY 20
#define TRIPLE_MAC_LEN 6
#define TRIPLE_SECRET_LEN 16
#define ALI_AUTH_VALUE_LEN 16
#define ALI_TRIPLE_SUM_LEN (TRIPLE_PID_LEN + TRIPLE_MAC_LEN + TRIPLE_SECRET_LEN)
#define PROV_AUTH_ACCEPT 1
#define PROV_AUTH_NOACCEPT 0
#define TMALL_TRITUPLE_FLASH_OFFSET (0x0200)
#define TMALL_GATT_SRC_ADDR_INVALID (0xffff)
#define UPADTE_TMALL_GATT_SRC_ADDR_TYPE  (0xff)
#define TMALL_GATT_MESH_MODEL_INDEX_INVALID  (0xff)
#define PROXY_CON_INTERVAL_MS 1000  //100ms
#define GATT_CON_INTERVAL_SLOT  160 //160*625us=100ms


bool sent_adv_ready=true;

uint8_t vendor_tid = 0;
#define RECORD_KEY1 1
#define RECORD_KEY2 2

#define SIG_MESH_WITH_OTA 		1

tinyfs_dir_t mesh_dir;
struct mesh_model_info model_env;
static uint8_t gatt_mesh_model_indx=TMALL_GATT_MESH_MODEL_INDEX_INVALID;
static uint16_t gatt_mesh_src_addr = TMALL_GATT_SRC_ADDR_INVALID;

SIGMESH_NodeInfo_TypeDef Node_Get_Proved_State = 0;
SIGMESH_NodeInfo_TypeDef Node_Proved_State = 0;
SIGMESH_NodeInfo_TypeDef Node_Beacon_State = 0;

static uint8_t ali_pid[TRIPLE_PID_LEN] = {0};
uint32_t ali_pid_u32 = 9416171;//8493052;
uint8_t ali_mac[TRIPLE_MAC_LEN] = {0x50,0x3d,0xeb,0x2f,0xcc,0xe3};//{0xfc,0x42,0x65,0xef,0x96,0x71};
uint8_t ali_secret[TRIPLE_SECRET_LEN] = {0xd7,0x59,0x10,0xa9,0xe4,0x38,0x26,0x87,0x1f,0xa8,0xc4,0x0c,0x08,0xa7,0xdf,0xd6};//{0x27,0x4a,0x2a,0x37,0x3e,0x0d,0xc5,0x23,0xb2,0x01,0x10,0x28,0x12,0xb3,0x08,0x7c};

static uint8_t ali_authvalue[ALI_AUTH_VALUE_LEN] = {0};

uint8_t rsp_data_info[40] = {0};
uint8_t tmall_ModelHandle = 0;

static struct builtin_timer *tmall_gatt_timer_inst = NULL;
static void ls_tmall_gatt_timer_cb(void *param);

static uint16_t provisioner_unicast_addr;
void create_adv_obj(void);

static struct gatt_svc_env tmall_aiots_svc_env;
static uint8_t connect_id = 0xff; 

uint8_t adv_obj_hdl;
uint8_t advertising_data[28];
static uint8_t scan_response_data[31];


#define TMALL_AIOTS_PID_SIZE          4
#define TMALL_AIOTS_MAC_SIZE          6
#define TMALL_AIOTS_SECRET_SIZE       16
#define TMALL_AIOTS_STR_RANDOM_SIZE   16
#define TMALL_AIOTS_BLE_KEY_SIZE      16

#define TMALL_AIOTS_STR_BLE_KEY_INPUT_LENGTH (((TMALL_AIOTS_SECRET_SIZE<<1)+1)+((TMALL_AIOTS_PID_SIZE<<1)+1)+((TMALL_AIOTS_MAC_SIZE<<1)+1)+(TMALL_AIOTS_STR_RANDOM_SIZE+1))  //4=3(",")+1("\0")

#define TMALL_AIOTS_SVC_MAX_MTU  247
#define TMALL_AIOTS_SVC_MTU_DFT  23
#define TMALL_AIOTS_SVC_MAX_DATA_LEN (TMALL_AIOTS_SVC_MAX_MTU - 3)
#define TMALL_AIOTS_SVC_RX_MAX_LEN (TMALL_AIOTS_SVC_MAX_MTU - 3)
#define TMALL_AIOTS_TX_MAX_LEN (TMALL_AIOTS_SVC_MAX_MTU - 3)

/*
*   Primary Service
*/
static const uint8_t tmall_aiots_primary_service_uuid[2] ={0xB3,0xFE};
static const uint8_t tmall_aiots_read_char_uuid[2]       ={0xD4,0xFE};
static const uint8_t tmall_aiots_write_req_char_uuid[2]  ={0xD5,0xFE};
static const uint8_t tmall_aiots_indic_char_uuid[2]      ={0xD6,0xFE};
static const uint8_t tmall_aiots_write_cmd_char_uuid[2]  ={0xD7,0xFE};
static const uint8_t tmall_aiots_notify_char_uuid[2]     ={0xD8,0xFE};
static const uint8_t att_decl_char_array_uuid[2]         ={0x03,0x28};
static const uint8_t att_client_char_cfg_uuid[2]         ={0x02,0x29};


enum aiots_svc_att_db_handles
{
    TMALL_AIOTS_READ_CHAR,
    TMALL_AIOTS_READ_VAL,
    TMALL_AIOTS_WRITE_CHAR,
    TMALL_AIOTS_WRITE_VAL,
    TMALL_AIOTS_IND_CHAR,
    TMALL_AIOTS_IND_VAL,
    TMALL_AIOTS_IND_CCC,
    TMALL_AIOTS_WRITE_CMD_CHAR,
    TMALL_AIOTS_WRITE_CMD_VAL,
    TMALL_AIOTS_NTF_CHAR,
    TMALL_AIOTS_NTF_VAL,
    TMALL_AIOTS_NTF_CCC,
    TMALL_AIOTS_ATT_NUM
};

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

static uint8_t sha256_handler(const char *input_str, uint8_t *chiper)
{
    uint8_t ret = TC_CRYPTO_FAIL;
    uint8_t g_auth[32];
    struct tc_sha256_state_struct sha256_ctx;

    ret = tc_sha256_init(&sha256_ctx);
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    ret = tc_sha256_update(&sha256_ctx, (const uint8_t *)input_str, strlen(input_str));
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    ret = tc_sha256_final(&g_auth[0], &sha256_ctx);
    if (ret == TC_CRYPTO_FAIL)
    {
        return ret;
    }

    memcpy(chiper, &g_auth[0], 16);
    return ret;
}

void hextostring(const uint8_t *source, char *dest, int len)
{
    int i;
    char tmp[3];

    for (i = 0; i < len; i++)
    {
        sprintf(tmp, "%02x", (unsigned char)source[i]);
        memcpy(&dest[i * 2], tmp, 2);
    }
}

static uint8_t gen_ali_authValue(void)
{
    uint8_t status = TC_CRYPTO_FAIL;
    char cal_ble_key_input[55] = ""; // pid + ',' + mac + ',' + secret = 8+1+12+1+32+'\0'
    char mac_str[(TRIPLE_MAC_LEN << 1) + 1] = "";
    char secret_str[(TRIPLE_SECRET_LEN << 1) + 1] = "";
    uint8_t tmp_arry[ALI_AUTH_VALUE_LEN] = {0};

    uint8_t ali_trituple[ALI_TRIPLE_SUM_LEN] = {0};
    hal_flash_fast_read(TMALL_TRITUPLE_FLASH_OFFSET, &ali_trituple[0], ALI_TRIPLE_SUM_LEN);
    if ((ali_trituple[0] != 0xff) && (ali_trituple[1] != 0xff) && (ali_trituple[2] != 0xff))
    {
        ali_pid_u32 = (((uint32_t)ali_trituple[0]) << 24) | (((uint32_t)ali_trituple[1]) << 16) | (((uint32_t)ali_trituple[2]) << 8) | (((uint32_t)ali_trituple[3]));
        memcpy(&ali_mac[0], &ali_trituple[TRIPLE_PID_LEN], TRIPLE_MAC_LEN);
        memcpy(&ali_secret[0], &ali_trituple[TRIPLE_PID_LEN + TRIPLE_MAC_LEN], TRIPLE_SECRET_LEN);
    }

    hextostring(ali_mac, mac_str, TRIPLE_MAC_LEN);
    hextostring(ali_secret, secret_str, TRIPLE_SECRET_LEN);

    sprintf(&cal_ble_key_input[0], "%08lx,%s,%s", ali_pid_u32, mac_str, secret_str);

    status = sha256_handler(&cal_ble_key_input[0], &ali_authvalue[0]);

    memcpy(&ali_pid[0], ((uint8_t *)&ali_pid_u32), TRIPLE_PID_LEN);

    memcpy(tmp_arry, ali_mac, TRIPLE_MAC_LEN);
    for (uint8_t j = 0; j < TRIPLE_MAC_LEN; j++)
    {
        ali_mac[j] = tmp_arry[TRIPLE_MAC_LEN - 1 - j];
    }

    memcpy(tmp_arry, ali_authvalue, ALI_AUTH_VALUE_LEN);
    for (uint8_t j = 0; j < ALI_AUTH_VALUE_LEN; j++)
    {
        ali_authvalue[j] = tmp_arry[ALI_AUTH_VALUE_LEN - 1 - j];
    }

    if (status == TC_CRYPTO_FAIL)
    {
        memset(&ali_authvalue[0], 0, ALI_AUTH_VALUE_LEN);
        return (0);
    }

    return (1);
}

void ls_sig_mesh_set_proxy_con_interval(uint16_t *interval_ms)
{
    *interval_ms = PROXY_CON_INTERVAL_MS;
}

 void ls_sig_mesh_set_pb_gatt_con_interval(uint16_t *interval_slot)  /**< 1slot=625us */
 {
    *interval_slot = GATT_CON_INTERVAL_SLOT;
 }
void auto_check_unbind(void)
{
    uint16_t length = 1;
    uint8_t coutinu_power_up_num = 0;
    tinyfs_mkdir(&mesh_dir, ROOT_DIR, 5);
    tinyfs_read(mesh_dir, RECORD_KEY1, &coutinu_power_up_num, &length);
    LOG_I("coutinu_power_up_num:%d", coutinu_power_up_num);

    if (coutinu_power_up_num > 4)
    {
        coutinu_power_up_num = 0;
        tinyfs_write(mesh_dir, RECORD_KEY1, &coutinu_power_up_num, sizeof(coutinu_power_up_num));
        SIGMESH_UnbindAll();
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
    info.DevUuid[13] = 0x02;
    info.DevUuid[14] = 0x00;
    info.DevUuid[15] = 0x00;
    info.UriHash = 0xd97478b3;
    info.OobInfo = 0x0000;
    info.UriHash_Present = false;
    start_tx_unprov_beacon(&info);
}

void disable_tx_unprov_beacon(void)
{
    stop_tx_unprov_beacon();
}

void report_provisioner_unicast_address_ind(uint16_t unicast_address)
{
    provisioner_unicast_addr = unicast_address;
    tinyfs_write(mesh_dir, RECORD_KEY2, (uint8_t *)&unicast_address, sizeof(unicast_address));
    tinyfs_write_through();
}


void ls_tmall_gatt_timer_init(void)
{
    tmall_gatt_timer_inst = builtin_timer_create(ls_tmall_gatt_timer_cb);
}

uint8_t state_unprov_beacn=0;
static void ls_tmall_gatt_timer_cb(void *param)
{
    if(Node_Get_Proved_State == UNPROVISIONED_KO)
    {
     if (state_unprov_beacn == 1)
    {
        state_unprov_beacn=2;
        enable_tx_unprov_beacon();
        start_ls_sig_mesh_gatt(); 
        LOG_I("start_unprov");
    }
    
    if(state_unprov_beacn==0) 
    {
        state_unprov_beacn =1;
         disable_tx_unprov_beacon();
         stop_ls_sig_mesh_gatt();
         builtin_timer_start(tmall_gatt_timer_inst, TMALL_GATT_TIMEOUT, NULL);
         LOG_I("stop_unprov");
    }
    }
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


static void gap_manager_callback(enum gap_evt_type type, union gap_evt_u *evt, uint8_t con_idx)
{
    switch (type)
    {
    case CONNECTED:
         connect_id = con_idx;
        LOG_I("connected!");
        break;
    case DISCONNECTED:
         LOG_I("DISCONNECTED!");
         LOG_I("disconnect_reason=%x",evt->disconnected.reason);
          gatt_mesh_src_addr = TMALL_GATT_SRC_ADDR_INVALID;
        break;
    case CONN_PARAM_REQ:
         LOG_I("PARAM_REQ!");
        break;
    case CONN_PARAM_UPDATED:
       LOG_I("PARAM_UPDATED!");
       gatt_manager_client_mtu_exch_send(connect_id);
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
    break;
    case SERVER_NOTIFICATION_DONE:
        LOG_I("SERVER_NOTIFICATION_DONE!");
    break;
    case MTU_CHANGED_INDICATION:
        LOG_I("MTU_CHANGED_INDICATION!");
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
    onoff_rsp.info[0] = tmall_light_get_onoff();
    model_send_info_handler(&onoff_rsp);
}

static void mesh_manager_callback(enum mesh_evt_type type, union ls_sig_mesh_evt_u *evt)
{
    switch (type)
    {
    case MESH_ACTIVE_ENABLE:
    {       
        gatt_mesh_src_addr = TMALL_GATT_SRC_ADDR_INVALID;
        TIMER_Set(2, 3000); //clear power up num
    }
    break;
    case MESH_ACTIVE_DISABLE:
    {
        gatt_mesh_src_addr = TMALL_GATT_SRC_ADDR_INVALID;
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
        tmall_light_set_lightness(0xFFFF);
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
        Node_Get_Proved_State = evt->st_proved.proved_state;
        if (Node_Get_Proved_State == PROVISIONED_OK)
        {
            uint16_t length = sizeof(provisioner_unicast_addr);
            LOG_I("src_addr=%x",provisioner_unicast_addr);
            LOG_I("The node is provisioned");
            tmall_light_set_lightness(0xffff);
            tinyfs_read(mesh_dir, RECORD_KEY2, (uint8_t*)&provisioner_unicast_addr, &length);
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
        param.DevUuid[0] = 0xA8;
        param.DevUuid[1] = 0x01;
        param.DevUuid[2] = 0x71;
        memcpy(&param.DevUuid[3], &ali_pid[0], TRIPLE_PID_LEN);
        memcpy(&param.DevUuid[3 + TRIPLE_PID_LEN], &ali_mac[0], TRIPLE_MAC_LEN);
        param.DevUuid[13] = 0x02;
        param.DevUuid[14] = 0x00;
        param.DevUuid[15] = 0x00;
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
        if ((Node_Get_Proved_State == PROVISIONED_OK) || (Node_Proved_State == MESH_PROV_SUCCEED))
        {
            if((evt->update_state_param.upd_type == UPADTE_TMALL_GATT_SRC_ADDR_TYPE) && (gatt_mesh_src_addr==TMALL_GATT_SRC_ADDR_INVALID))
            {
                 memcpy((uint8_t *)&gatt_mesh_src_addr, &(evt->update_state_param.data[0]), 2);
                 LOG_I("MESH_STATE_UPD_IND=%4x", gatt_mesh_src_addr);
                 gatt_mesh_model_indx=0;
                 generic_onoff_status_report(gatt_mesh_model_indx,GENERIC_ONOFF_STATUS);
            }
        }      
    }
    break;
    case MESH_REPOPT_PROV_RESULT:
    {
      	Node_Proved_State = evt->prov_rslt_sate.state;  
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

#if(SIG_MESH_WITH_OTA==1)
#if FW_ECC_VERIFY
extern const uint8_t fotas_pub_key[64];
bool fw_signature_check(struct fw_digest *digest,struct fota_signature *signature)
{
    return uECC_verify(fotas_pub_key, digest->data, sizeof(digest->data), signature->data, uECC_secp256r1());
}
#else
bool fw_signature_check(struct fw_digest *digest,struct fota_signature *signature)
{
    return true;
}
#endif

static void prf_fota_server_callback(enum fotas_evt_type type,union fotas_evt_u *evt)
{
    switch(type)
    {
    case FOTAS_START_REQ_EVT:
    {
        enum fota_start_cfm_status status;
        if(fw_signature_check(evt->fotas_start_req.digest, evt->fotas_start_req.signature))
        {
            status = FOTA_REQ_ACCEPTED;
        }else
        {
            status = FOTA_REQ_REJECTED;
        }

         LOG_I("type=0x%x,status=0x%x",type,status);
        prf_fotas_start_confirm(status);
    }break;
    case FOTAS_FINISH_EVT:
        if(evt->fotas_finish.status & FOTA_STATUS_MASK && evt->fotas_finish.status & FOTA_REBOOT_MASK)
        {
            if(evt->fotas_finish.boot_addr)
            {
                ota_boot_addr_set(evt->fotas_finish.boot_addr);
            }
            if(evt->fotas_finish.status & FOTA_SETTINGS_ERASE_MASK)
            {
                ota_settings_erase_req_set();
            }
            if(evt->fotas_finish.copy.fw_copy_size)
            {
                ota_copy_info_set(&evt->fotas_finish.copy);
            }
            platform_reset(RESET_OTA_SUCCEED);
        }
    break;
    case FOTAS_PROGRESS_EVT:
    break;
    default:
        LS_ASSERT(0);
    break;
    }
}
#endif


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
#if (SIG_MESH_WITH_OTA == 1)         
        dev_manager_prf_fota_server_add(NO_SEC);
#else
        dev_manager_add_service((struct svc_decl *)&tmall_aiots_server_svc);  
#endif            
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
#if (SIG_MESH_WITH_OTA == 1)         
         if (evt->profile_added.id == PRF_FOTA_SERVER)
         {
            prf_fota_server_callback_init(prf_fota_server_callback);
            dev_manager_add_service((struct svc_decl *)&tmall_aiots_server_svc);
            break;  
         }
#endif         
         if (evt->profile_added.id == PRF_MESH)
         {
             prf_ls_sig_mesh_callback_init(mesh_manager_callback);
             model_env.nb_model = 2;
             model_env.info[0].model_id = GENERIC_ONOFF_SERVER;
             model_env.info[0].element_id = 0;
             model_env.info[1].model_id = VENDOR_TMALL_SERVER;
             model_env.info[1].element_id = 0;
             ls_sig_mesh_init(&model_env);
             break;
         }
     }
    default:
        break;
    }
}

int main()
{
    sys_init_app();
    mesh_stack_data_bss_init();
    tmall_light_init();
    //exti_gpio_init();
    gen_ali_authValue();
    ble_init();
    auto_check_unbind();
    dev_manager_init(dev_manager_callback);
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
}
