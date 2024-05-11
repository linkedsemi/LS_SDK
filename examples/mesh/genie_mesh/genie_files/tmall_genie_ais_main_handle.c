#include <string.h>
#include <stdio.h>
#include "ls_ble.h"
#include "cpu.h"
#include "builtin_timer.h"
#include "co_math.h"
#include "log.h"
#include "platform.h"
#include "ls_sig_mesh.h"
#include "tinyfs.h"
#include "tmall_genie_ais.h"
#include "genie_triple.h"
#include "tmall_genie_ais_main_handle.h"
#include "tmall_mesh_ctl.h"

#define AIS_REBOOT_FLG 0xB8A9CADB
#define INVAILD_FW_VERSION 0xFFFFFFFF
#define DEFAULT_FW_VERSION 0x00010004
#define RECORD_PRJ_FW_VERSION 3
#define GENIE_PBADV_TIMEOUT_10MIN             (600 * 20) 
#define AIS_SVC_BUFFER_SIZE (1024)
#define AIS_SERVER_TIMEOUT 50

extern tinyfs_dir_t mesh_dir;
extern uint8_t connect_id;
extern uint16_t provisioner_unicast_addr;
extern uint16_t gatt_mesh_src_addr;
extern SIGMESH_NodeInfo_TypeDef Node_Get_Proved_State;
extern SIGMESH_NodeInfo_TypeDef Node_Proved_State;
extern struct mesh_model_info model_env;

uint32_t ais_prj_fw_verion=INVAILD_FW_VERSION;
uint32_t ais_reboot_req_flag= 0;
uint8_t reboot_3s_dly=0;
uint16_t silent_10min_dly=0;
bool ais_server_ntf_done = false;

static struct builtin_timer *ls_genie_ais_timer_inst = NULL;
static uint8_t ais_server_buf[AIS_SVC_BUFFER_SIZE];
static uint16_t ais_server_rx_index = 0;
static uint16_t transaction_id = 0;

const uint8_t tmall_aiots_primary_service_uuid[2] ={0xB3,0xFE};
const uint8_t tmall_aiots_read_char_uuid[2]       ={0xD4,0xFE};
const uint8_t tmall_aiots_write_req_char_uuid[2]  ={0xD5,0xFE};
const uint8_t tmall_aiots_indic_char_uuid[2]      ={0xD6,0xFE};
const uint8_t tmall_aiots_write_cmd_char_uuid[2]  ={0xD7,0xFE};
const uint8_t tmall_aiots_notify_char_uuid[2]     ={0xD8,0xFE};
const uint8_t att_decl_char_array_uuid[2]         ={0x03,0x28};
const uint8_t att_client_char_cfg_uuid[2]         ={0x02,0x29};

struct gatt_svc_env tmall_aiots_svc_env;
static void ls_genie_ais_timer_cb(void *param);

void ls_genie_ais_fw_version_init(void)
{
    uint16_t length=4;
    tinyfs_read(mesh_dir, RECORD_PRJ_FW_VERSION, (uint8_t *)&ais_prj_fw_verion, &length);
    if (ais_prj_fw_verion !=DEFAULT_FW_VERSION)
    {
        ais_prj_fw_verion = DEFAULT_FW_VERSION;
        tinyfs_write(mesh_dir, RECORD_PRJ_FW_VERSION, (uint8_t *)&ais_prj_fw_verion, sizeof(ais_prj_fw_verion));
        tinyfs_write_through();
    }
}

uint32_t ls_genie_ais_fw_version_get(void)
{
    uint16_t length=4;
    tinyfs_read(mesh_dir, RECORD_PRJ_FW_VERSION, (uint8_t *)&ais_prj_fw_verion, &length);
    return ais_prj_fw_verion;
}

void genie_pbadv_start_silent_adv(void)
{
     stop_tx_unprov_beacon();
     stop_ls_sig_mesh_gatt();
}

int genie_ais_gatt_indicate( void *data, uint16_t len)
{
     uint16_t handle = gatt_manager_get_svc_att_handle(&tmall_aiots_svc_env, TMALL_AIOTS_IND_VAL);
    gatt_manager_server_send_indication(connect_id,handle,data,len,&transaction_id);
    transaction_id++;
	return 0;
}

int genie_ais_gatt_notify_message(void *data, uint16_t len)
{
    if(ais_server_rx_index < AIS_SVC_BUFFER_SIZE)
    {
        memcpy(&ais_server_buf[ais_server_rx_index],(uint8_t *)data,len);
        ais_server_rx_index += len;
    }
    else
    {   
        LOG_I("ais server rx buffer overflow!");
    }
    return 0;
}

void genie_ais_server_send_notification(void)
{
    if(ais_server_rx_index > 0 && ais_server_ntf_done)
    {
       ais_server_ntf_done =false;
       uint16_t handle = gatt_manager_get_svc_att_handle(&tmall_aiots_svc_env, TMALL_AIOTS_NTF_VAL);
       uint16_t tx_len = ais_server_rx_index > co_min(TMALL_AIOTS_SVC_MAX_DATA_LEN, TMALL_AIOTS_TX_MAX_LEN) ? co_min(TMALL_AIOTS_SVC_MAX_DATA_LEN, TMALL_AIOTS_TX_MAX_LEN) : ais_server_rx_index;
       ais_server_rx_index -= tx_len;
       gatt_manager_server_send_notification(connect_id, handle, ais_server_buf, tx_len, NULL);
       memcpy((void*)&ais_server_buf[0], (void*)&ais_server_buf[tx_len], ais_server_rx_index);
    }    
}

void genie_ais_gap_disconnect(uint8_t reason)
{
    gap_manager_disconnect(connect_id,0x13);
}

void ls_genie_ais_timer_init(void)
{
    ls_genie_ais_timer_inst = builtin_timer_create(ls_genie_ais_timer_cb);
    builtin_timer_start(ls_genie_ais_timer_inst, AIS_SERVER_TIMEOUT, NULL); 
}


static void ls_genie_ais_timer_cb(void *param)
{
     if(connect_id != 0xff)
     {
        uint32_t cpu_stat = enter_critical();
        genie_ais_server_send_notification();
        exit_critical(cpu_stat);
    }

    if (ais_reboot_req_flag ==AIS_REBOOT_FLG)
    {
        reboot_3s_dly++;
        if (reboot_3s_dly >60) //50*60=3000ms
        {
            platform_reset(RESET_OTA_SUCCEED);
        }
    }

    //do tmall hardware node reset event
     if (Node_Get_Proved_State == UNPROVISIONING)
     {
         uint16_t dst_addr=0;
         if (gatt_mesh_src_addr !=0xffff) //TMALL_GATT_SRC_ADDR_VALID
         {
            dst_addr = gatt_mesh_src_addr;
         }
         else
         {
            dst_addr = provisioner_unicast_addr;
         }
         
         if (0 == tmall_mesh_hardware_node_reset_ind(model_env.info[1].model_lid, model_env.app_key_lid, dst_addr))
         {
             Node_Get_Proved_State = UNPROVISIONED_KO;
         }
      }

    if((Node_Get_Proved_State == UNPROVISIONED_KO) && (Node_Proved_State == MESH_PROV_STARTED))
    {
       silent_10min_dly++;
       if(silent_10min_dly >GENIE_PBADV_TIMEOUT_10MIN)
       {
           silent_10min_dly =0;
           genie_pbadv_start_silent_adv();
       }
    }
    else
    {
        silent_10min_dly =0;
    }

    if(ls_genie_ais_timer_inst)
    {
      builtin_timer_start(ls_genie_ais_timer_inst, AIS_SERVER_TIMEOUT, NULL); 
    }
}
