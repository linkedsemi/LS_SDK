#ifndef __TMALL_GENIE_AIS_MAIN_HANDLE_H__
#define __TMALL_GENIE_AIS_MAIN_HANDLE_H__
#include "ls_ble.h"

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

extern const uint8_t tmall_aiots_primary_service_uuid[2];
extern const uint8_t tmall_aiots_read_char_uuid[2];
extern const uint8_t tmall_aiots_write_req_char_uuid[2];
extern const uint8_t tmall_aiots_indic_char_uuid[2];
extern const uint8_t tmall_aiots_write_cmd_char_uuid[2];
extern const uint8_t tmall_aiots_notify_char_uuid[2];
extern const uint8_t att_decl_char_array_uuid[2];
extern const uint8_t att_client_char_cfg_uuid[2];

#define TMALL_AIOTS_PID_SIZE          4
#define TMALL_AIOTS_MAC_SIZE          6
#define TMALL_AIOTS_SECRET_SIZE       16
#define TMALL_AIOTS_STR_RANDOM_SIZE   16
#define TMALL_AIOTS_BLE_KEY_SIZE      16

#define TMALL_AIOTS_STR_BLE_KEY_INPUT_LENGTH (((TMALL_AIOTS_SECRET_SIZE<<1)+1)+((TMALL_AIOTS_PID_SIZE<<1)+1)+((TMALL_AIOTS_MAC_SIZE<<1)+1)+(TMALL_AIOTS_STR_RANDOM_SIZE+1))  //4=3(",")+1("\0")

#define TMALL_AIOTS_SVC_MAX_MTU  300
#define TMALL_AIOTS_SVC_MTU_DFT  23
#define TMALL_AIOTS_SVC_MAX_DATA_LEN (TMALL_AIOTS_SVC_MAX_MTU - 3)
#define TMALL_AIOTS_SVC_RX_MAX_LEN (TMALL_AIOTS_SVC_MAX_MTU - 3)
#define TMALL_AIOTS_TX_MAX_LEN (TMALL_AIOTS_SVC_MAX_MTU - 3)

extern struct gatt_svc_env tmall_aiots_svc_env;
extern bool ais_server_ntf_done;
void ls_genie_ais_timer_init(void);
void genie_ais_server_send_notification(void);
void ls_genie_ais_fw_version_init(void);
int genie_ais_gatt_notify_message(void *data, uint16_t len);
int genie_ais_gatt_indicate(void *data, uint16_t len);
void genie_ais_gap_disconnect(uint8_t reason);
uint32_t ls_genie_ais_fw_version_get(void);

#endif //__TMALL_GENIE_AIS_MAIN_HANDLE_H__
