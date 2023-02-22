#define LOG_TAG "MAIN"
#include <stdio.h>
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
#include "ble_common_api.h"

#define PAIR_ENCRYPT_ENABLE  1
#define SC_OOB_ENABLE (0 & PAIR_ENCRYPT_ENABLE)
#define LEGACY_OOB_ENABLE (0 & PAIR_ENCRYPT_ENABLE)
#define LEGACY_PASSKEY_ENTRY_ENABLE (0 & PAIR_ENCRYPT_ENABLE)
#define LEGACY_JUST_WORKS_ENABLE (1 & PAIR_ENCRYPT_ENABLE)
#define NUMERIC_COMPARISON_ENABLE (0 & PAIR_ENCRYPT_ENABLE)
#define LEGACY_PAIRING_ENABLE (LEGACY_OOB_ENABLE || LEGACY_PASSKEY_ENTRY_ENABLE || LEGACY_JUST_WORKS_ENABLE || NUMERIC_COMPARISON_ENABLE)

#define UART_SVC_ADV_NAME "LS Pairing Single Role"
#define UART_SERVER_MAX_MTU  517
#define UART_SERVER_MTU_DFT  23
#define UART_SVC_RX_MAX_LEN (UART_SERVER_MAX_MTU - 3)
#define UART_SVC_TX_MAX_LEN (UART_SERVER_MAX_MTU - 3)
#define UART_SERVER_MAX_DATA_LEN (uart_server_mtu - 3)
#define UART_CLIENT_MAX_DATA_LEN (uart_client_mtu - 3)

#define UART_SERVER_MASTER_NUM 1
#define UART_CLIENT_NUM (SDK_MAX_CONN_NUM - UART_SERVER_MASTER_NUM)
#define UART_SERVER_TIMEOUT 50 // timer units: ms

#define CON_IDX_INVALID_VAL 0xff
#define CONNECTION_IS_SERVER(idx) ((idx) != CON_IDX_INVALID_VAL && (idx) == con_idx_server)

#define UART_SYNC_BYTE  0xA5
#define UART_SYNC_BYTE_LEN 1
#define UART_LEN_LEN  2
#define UART_LINK_ID_LEN 1
#if (PAIR_ENCRYPT_ENABLE == 1)
#define UART_PAIRING_SYNC_BYTE  0xB6
#if (SC_OOB_ENABLE == 1)
#define UART_SC_OOB_COMFIRM_LEN 16
#define UART_SC_OOB_RAND_LEN 16
#define UART_SC_OOB_LEN  (UART_LINK_ID_LEN+UART_SC_OOB_COMFIRM_LEN+UART_SC_OOB_RAND_LEN)
#endif //SC_OOB_ENABLE
#endif //PAIR_ENCRYPT_ENABLE
#define UART_HEADER_LEN (UART_SYNC_BYTE_LEN + UART_LEN_LEN + UART_LINK_ID_LEN)
#define UART_SVC_BUFFER_SIZE (UART_SERVER_MAX_MTU + UART_HEADER_LEN)
#define UART_RX_PAYLOAD_LEN_MAX (UART_SVC_BUFFER_SIZE - UART_HEADER_LEN)
#define UART_TX_PAYLOAD_LEN_MAX (UART_SVC_BUFFER_SIZE - UART_HEADER_LEN)

#define CONNECTED_MSG_PATTERN 0x5ce5
#define CONNECTED_MSG_PATTERN_LEN 2
#define DISCONNECTED_MSG_PATTERN 0xdead
#define DISCONNECTED_MSG_PATTERN_LEN 2

#if (LEGACY_PAIRING_ENABLE == 1)
#define LEGACY_PAIRING_PATTERN_LEN 2
#define LEGACY_PAIRING_PATTERN_LEN_LEN 2
#define UART_LEGACY_PAIRING_REQ_LEN  (UART_LINK_ID_LEN+LEGACY_PAIRING_PATTERN_LEN+LEGACY_PAIRING_PATTERN_LEN_LEN)
#if (LEGACY_OOB_ENABLE == 1)
#define LEGACY_OOB_PATTERN 0x7979
#define UART_LEGACY_OOB_RSP_LEN  (UART_LINK_ID_LEN + BLE_KEY_LEN)
#endif //LEGACY_OOB_ENABLE
#if (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
#define LEGACY_PASSKEY_ENTRY_PATTERN 0x8a8a
#define LEGACY_PAIRING_PASSKEY_LEN 6
#endif //LEGACY_PARING_ENABLE

#if (NUMERIC_COMPARISON_ENABLE == 1)
#define NUMERIC_COMPARISON_LEN 6
#define NUMERIC_COMPARISON_COMFIRMS_LEN 2
#endif //NUMERIC_COMPARISON_ENABLE
#endif //LEGACY_PAIRING_ENABLE

enum uart_rx_status
{
    UART_IDLE,
    UART_SYNC,
    UART_LEN_REV,
    UART_LINK_ID,
    UART_OOB,
    UART_PASSKEY,
    UART_NUMERIC_COMPARISON,
    UART_RECEIVING,
};
static uint8_t uart_state = UART_IDLE;
static bool uart_tx_busy;
static uint8_t uart_rx_buf[UART_SVC_BUFFER_SIZE];
static UART_HandleTypeDef UART_Config; 
static uint8_t current_uart_tx_idx; // bit7 = 1 : client, bit7 = 0 : server
#if (PAIR_ENCRYPT_ENABLE == 1)
#if ((LEGACY_PASSKEY_ENTRY_ENABLE == 1) || (NUMERIC_COMPARISON_ENABLE == 1))
static uint8_t pk_nc_recv_state=0;
static uint8_t pk_nc_recv_index=0;
#endif//LEGACY_PASSKEY_ENTRY_ENABLE || NUMERIC_COMPARISON_ENABLE
#if (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
static bool uart_rx_pass_key_flg=false;
#endif//LEGACY_PASSKEY_ENTRY_ENABLE

#if (NUMERIC_COMPARISON_ENABLE == 1)
static bool uart_rx_numeric_comparison_flg=false;
#endif//NUMERIC_COMPARISON_ENABLE

#if ((SC_OOB_ENABLE == 1) || (LEGACY_OOB_ENABLE == 1))
static bool uart_rx_oob_flg=false;
#endif//SC_OOB_ENABLE || LEGACY_OOB_ENABLE

#endif

static const uint8_t ls_uart_svc_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x01,0x00,0x40,0x6e};
static const uint8_t ls_uart_rx_char_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x02,0x00,0x40,0x6e};
static const uint8_t ls_uart_tx_char_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x03,0x00,0x40,0x6e};
static const uint8_t att_desc_client_char_cfg_array[] = {0x02,0x29};

/************************************************data for Server*****************************************************/
static const uint8_t att_decl_char_array[] = {0x03,0x28};
enum uart_svc_att_db_handles
{
    UART_SVC_IDX_RX_CHAR,
    UART_SVC_IDX_RX_VAL,
    UART_SVC_IDX_TX_CHAR,
    UART_SVC_IDX_TX_VAL,
    UART_SVC_IDX_TX_NTF_CFG,
    UART_SVC_ATT_NUM
};
static const struct att_decl ls_uart_server_att_decl[UART_SVC_ATT_NUM] =
{
    [UART_SVC_IDX_RX_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [UART_SVC_IDX_RX_VAL] = {
        .uuid = ls_uart_rx_char_uuid_128,
        .s.max_len = UART_SVC_RX_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.wr_cmd = 1,
        .char_prop.wr_req = 1,
    },
    [UART_SVC_IDX_TX_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1, 
    },
    [UART_SVC_IDX_TX_VAL] = {
        .uuid = ls_uart_tx_char_uuid_128,
        .s.max_len = UART_SVC_TX_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.ntf_en = 1,
    },
    [UART_SVC_IDX_TX_NTF_CFG] = {
        .uuid = att_desc_client_char_cfg_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
    },
};

static const struct svc_decl ls_uart_server_svc =
{
    .uuid = ls_uart_svc_uuid_128,
    .att = (struct att_decl*)ls_uart_server_att_decl,
    .nb_att = UART_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_128BIT,
};

static struct gatt_svc_env ls_uart_server_svc_env;
static uint8_t uart_server_tx_buf[UART_SVC_BUFFER_SIZE];
static uint8_t uart_server_ble_buf[UART_SVC_BUFFER_SIZE];
static uint16_t uart_server_recv_data_length;
static bool uart_server_ntf_done;
static uint16_t uart_server_mtu;
static uint8_t con_idx_server;
static uint16_t cccd_config;

static uint8_t adv_obj_hdl;
static uint8_t advertising_data[28];
static uint8_t scan_response_data[31];

static void ls_uart_server_init(void);
static void ls_uart_init(void);
static void ls_uart_server_client_uart_tx(void);
static void ls_uart_server_read_req_ind(uint8_t att_idx, uint8_t con_idx);
static void ls_uart_server_write_req_ind(uint8_t att_idx, uint8_t con_idx, uint16_t length, uint8_t const *value);
static void ls_uart_server_send_notification(void);
static void start_adv(void);
/************************************************data for client*****************************************************/
static void ls_uart_server_client_uart_tx(void);
static void ls_single_role_timer_cb(void *param);
#if (PAIR_ENCRYPT_ENABLE == 1)

#if ((NUMERIC_COMPARISON_ENABLE == 1) || (LEGACY_PASSKEY_ENTRY_ENABLE == 1) || (LEGACY_OOB_ENABLE == 1) || (SC_OOB_ENABLE == 1))
static uint8_t uart_pairing_ble_buf[UART_SVC_BUFFER_SIZE];
#endif

#if (SC_OOB_ENABLE  == 1)
static void ls_uart_sc_oob_set(void);
#endif //SC_OOB_ENABLE
#if (LEGACY_OOB_ENABLE  == 1)
static void ls_uart_legacy_oob_set(void);
#endif //LEGACY_OOB_ENABLE
#if (LEGACY_PASSKEY_ENTRY_ENABLE  == 1)
static void ls_uart_legacy_passkey_entry_set(void);
#endif //LEGACY_PASSKEY_ENTRY_ENABLE
#if (NUMERIC_COMPARISON_ENABLE  == 1)
static void ls_uart_numeric_comparison_set(void);
#endif //NUMERIC_COMPARISON_ENABLE
#endif
static struct builtin_timer *ble_app_timer_inst = NULL;
static void ls_app_timer_init(void)
{
    ble_app_timer_inst = builtin_timer_create(ls_single_role_timer_cb);
    builtin_timer_start(ble_app_timer_inst, UART_SERVER_TIMEOUT, NULL);
}
static void ls_single_role_timer_cb(void *param)
{
    ls_uart_server_send_notification();
    ls_uart_server_client_uart_tx();

#if (PAIR_ENCRYPT_ENABLE == 1)
#if (SC_OOB_ENABLE == 1)
   ls_uart_sc_oob_set();
#endif //SC_OOB_ENABLE  

#if (LEGACY_OOB_ENABLE == 1)
   ls_uart_legacy_oob_set();
#endif // LEGACY_OOB_ENABLE  

#if (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
    ls_uart_legacy_passkey_entry_set();
#endif // LEGACY_PASSKEY_ENTRY_ENABLE  

#if (NUMERIC_COMPARISON_ENABLE == 1)
    ls_uart_numeric_comparison_set();
#endif // NUMERIC_COMPARISON_ENABLE  

#endif//PAIR_ENCRYPT_ENABLE
    if(ble_app_timer_inst)
    {
        builtin_timer_start(ble_app_timer_inst, UART_SERVER_TIMEOUT, NULL); 
    }
}
static void ls_uart_init(void)
{
    pinmux_uart1_init(PB00, PB01);
    io_pull_write(PB01, IO_PULL_UP);
    UART_Config.UARTX = UART1;
    UART_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Config.Init.MSBEN = 0;
    UART_Config.Init.Parity = UART_NOPARITY;
    UART_Config.Init.StopBits = UART_STOPBITS1;
    UART_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config);
}

static void ls_uart_server_init(void)
{
    con_idx_server = CON_IDX_INVALID_VAL;
    uart_server_ntf_done = true;
    uart_server_mtu = UART_SERVER_MTU_DFT;
    uart_server_recv_data_length = 0;   
}
static void ls_uart_server_read_req_ind(uint8_t att_idx, uint8_t con_idx)
{
    uint16_t handle = 0;
    if(att_idx == UART_SVC_IDX_TX_NTF_CFG)
    {
        handle = gatt_manager_get_svc_att_handle(&ls_uart_server_svc_env, att_idx);
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void*)&cccd_config, 2);
    }
}
static void ls_uart_server_write_req_ind(uint8_t att_idx, uint8_t con_idx, uint16_t length, uint8_t const *value)
{
    if(att_idx == UART_SVC_IDX_RX_VAL && uart_server_tx_buf[0] != UART_SYNC_BYTE)
    { 
        LS_ASSERT(length <= UART_TX_PAYLOAD_LEN_MAX);
        uart_server_tx_buf[0] = UART_SYNC_BYTE;
        uart_server_tx_buf[1] = length & 0xff;
        uart_server_tx_buf[2] = (length >> 8) & 0xff;
        uart_server_tx_buf[3] = con_idx; // what uart will receive should be the real connection index. array_idx is internal.
        memcpy((void*)&uart_server_tx_buf[UART_HEADER_LEN], value, length);
        uint32_t cpu_stat = enter_critical();
        if(!uart_tx_busy)
        {
            uart_tx_busy = true;
            current_uart_tx_idx = (0 << 7);
            HAL_UART_Transmit_IT(&UART_Config, &uart_server_tx_buf[0], length + UART_HEADER_LEN);
        } 
        exit_critical(cpu_stat);
    }
    else if (att_idx == UART_SVC_IDX_TX_NTF_CFG)
    {
        LS_ASSERT(length == 2);
        memcpy(&cccd_config, value, length);
    }
}
static void ls_uart_server_send_notification(void)
{
    uint32_t cpu_stat = enter_critical();
    if(con_idx_server != CON_IDX_INVALID_VAL && uart_server_recv_data_length != 0 && uart_server_ntf_done)
    {
        uart_server_ntf_done = false;
        uint16_t handle = gatt_manager_get_svc_att_handle(&ls_uart_server_svc_env, UART_SVC_IDX_TX_VAL);
        uint16_t tx_len = uart_server_recv_data_length > co_min(UART_SERVER_MAX_DATA_LEN, UART_SVC_TX_MAX_LEN) ? 
                        co_min(UART_SERVER_MAX_DATA_LEN, UART_SVC_TX_MAX_LEN) : uart_server_recv_data_length;
        uart_server_recv_data_length -= tx_len;
        gatt_manager_server_send_notification(con_idx_server, handle, &uart_server_ble_buf[0], tx_len, NULL);         
        memcpy((void*)&uart_server_ble_buf[0], (void*)&uart_server_ble_buf[tx_len], uart_server_recv_data_length);
    }
    exit_critical(cpu_stat);
}
static void create_adv_obj()
{
    struct legacy_adv_obj_param adv_param = {
        .adv_intv_min = 0x80,
        .adv_intv_max = 0x80,
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
static void start_adv(void)
{
    LS_ASSERT(adv_obj_hdl != 0xff);
    uint8_t adv_data_length = ADV_DATA_PACK(advertising_data, 1, GAP_ADV_TYPE_SHORTENED_NAME, UART_SVC_ADV_NAME, sizeof(UART_SVC_ADV_NAME));
    dev_manager_start_adv(adv_obj_hdl, advertising_data, adv_data_length, scan_response_data, 0);
}

#if (SC_OOB_ENABLE == 1)
void ls_uart_sc_oob_set(void)
{
   if (uart_rx_oob_flg ==true)
   {
       uart_rx_oob_flg = false;
       struct gap_sc_oob sc_oob_param;
       memcpy(&sc_oob_param.conf[0],&uart_pairing_ble_buf[0],BLE_KEY_LEN);
       memcpy(&sc_oob_param.rand[0],&uart_pairing_ble_buf[BLE_KEY_LEN],BLE_KEY_LEN);
       LOG_I("Uart_oob_comfirm");
       LOG_HEX(&uart_pairing_ble_buf[0],BLE_KEY_LEN);
       LOG_I("Uart_oob_rand");
       LOG_HEX(&uart_pairing_ble_buf[BLE_KEY_LEN],BLE_KEY_LEN);
       gap_manager_sc_oob_set(con_idx_server,&sc_oob_param);
   }
}
#endif //SC_OOB_ENABLE

#if (LEGACY_OOB_ENABLE == 1)
void ls_uart_legacy_oob_set(void)
{
   if (uart_rx_oob_flg ==true)
   {
       uart_rx_oob_flg = false;
       uint8_t legacy_oob_tk[BLE_KEY_LEN];
       memcpy(&legacy_oob_tk[0],&uart_pairing_ble_buf[0],BLE_KEY_LEN);
       LOG_I("Uart_legacy_oob");
       LOG_HEX(&legacy_oob_tk[0],BLE_KEY_LEN);
       gap_manager_tk_set(con_idx_server,&legacy_oob_tk[0]);
   }
}
#endif //LEGACY_OOB_ENABLE

#if (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
static void ls_uart_legacy_passkey_entry_set(void)
{
   if (uart_rx_pass_key_flg ==true)
   {
       uart_rx_pass_key_flg = false;
       uint8_t legacy_passkey_entry[LEGACY_PAIRING_PASSKEY_LEN+1];
       memcpy(&legacy_passkey_entry[0],&uart_pairing_ble_buf[0],LEGACY_PAIRING_PASSKEY_LEN+1);
       LOG_I("Uart_legacy_passkey_entry");
       gap_manager_passkey_input(con_idx_server,(struct gap_pin_str *)&legacy_passkey_entry[0]);
   }
}
#endif //LEGACY_PASSKEY_ENTRY_ENABLE

#if (NUMERIC_COMPARISON_ENABLE == 1)
static void ls_uart_numeric_comparison_set(void)
{
   if (uart_rx_numeric_comparison_flg ==true)
   {
       uart_rx_numeric_comparison_flg = false;
       bool numeric_comparison_confirm=false;
       if ((uart_pairing_ble_buf[0] == 'O') && (uart_pairing_ble_buf[1] == 'K'))
       {
           numeric_comparison_confirm =true;
       }
       LOG_I("Uart_numeric_comparison");
       gap_manager_numeric_compare_set(con_idx_server,numeric_comparison_confirm);
   }
}
#endif //NUMERIC_COMPARISON_ENABLE

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    LOG_I("tx cplt, current_uart_tx_idx = %d", current_uart_tx_idx);
    uart_tx_busy = false;
#if (PAIR_ENCRYPT_ENABLE == 1)
    #if ((NUMERIC_COMPARISON_ENABLE == 1) || (LEGACY_PASSKEY_ENTRY_ENABLE == 1) || (LEGACY_OOB_ENABLE == 1) || (LEGACY_OOB_ENABLE == 1))
    uart_pairing_ble_buf[0] = 0; // clear oob buffer sync byte
    #endif
#endif 
 
    if ((current_uart_tx_idx & (1 << 7)) == 0)
    {
        uart_server_tx_buf[0] = 0; // clear server buffer sync byte
    }   
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint16_t len;
    uint8_t con_idx;
    bool restart = true;
    switch (uart_state)
    {
    case UART_IDLE:
        if(uart_rx_buf[0] == UART_SYNC_BYTE)
        {
            uart_state = UART_SYNC;
            HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[UART_SYNC_BYTE_LEN], UART_LEN_LEN + UART_LINK_ID_LEN);
            restart = false;
        }
 #if (PAIR_ENCRYPT_ENABLE == 1)        
        else if (uart_rx_buf[0] == UART_PAIRING_SYNC_BYTE)
        {
           uart_state = UART_OOB;
           #if (SC_OOB_ENABLE ==1)
            HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[UART_SYNC_BYTE_LEN], UART_SC_OOB_LEN);
           #endif //SC_OOB_ENABLE 

           #if (LEGACY_OOB_ENABLE ==1)
            HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[UART_SYNC_BYTE_LEN], UART_LEGACY_OOB_RSP_LEN);
           #endif //SC_OOB_ENABLE 

            restart = false;
        }
#if (LEGACY_PASSKEY_ENTRY_ENABLE ==1)        
        else
        {
             switch (pk_nc_recv_state)
             {
                case 0:
                if (uart_rx_buf[pk_nc_recv_index] == 'P')
                {
                   pk_nc_recv_state++;
                   pk_nc_recv_index++;
                   HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[pk_nc_recv_index], 1);
                }
                break;
                case 1:
                 if (uart_rx_buf[pk_nc_recv_index] == 'K')
                 {
                    pk_nc_recv_state++;
                    pk_nc_recv_index++;
                    HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[pk_nc_recv_index], 1);
                 }
                 else
                 {
                    pk_nc_recv_state = 0;
                    pk_nc_recv_index=0;
                 }  
                break;
                case 2:
                   if (uart_rx_buf[pk_nc_recv_index] == '=')
                   {
                     uart_state = UART_PASSKEY;
                     pk_nc_recv_index++;
                     HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[pk_nc_recv_index], (LEGACY_PAIRING_PASSKEY_LEN+1));
                     restart = false;
                   }   
                    pk_nc_recv_state = 0; 
                break;
                default:
                break;
              } 
        }
#endif//LEGACY_PASSKEY_ENTRY_ENABLE
#if (NUMERIC_COMPARISON_ENABLE ==1)      
         else
        {
             switch (pk_nc_recv_state)
             {
                case 0:
                if (uart_rx_buf[pk_nc_recv_index] == 'N')
                {
                   pk_nc_recv_state++;
                   pk_nc_recv_index++;
                   HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[pk_nc_recv_index], 1);
                }
                break;
                case 1:
                 if (uart_rx_buf[pk_nc_recv_index] == 'C')
                 {
                    pk_nc_recv_state++;
                    pk_nc_recv_index++;
                    HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[pk_nc_recv_index], 1);
                 }
                 else
                 {
                    pk_nc_recv_state = 0;
                    pk_nc_recv_index=0;
                 }  
                break;
                case 2:
                   if (uart_rx_buf[pk_nc_recv_index] == '=')
                   {
                     uart_state = UART_NUMERIC_COMPARISON;
                     pk_nc_recv_index++;
                     HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[pk_nc_recv_index], (NUMERIC_COMPARISON_COMFIRMS_LEN+1));
                     restart = false;
                   }   
                    pk_nc_recv_state = 0; 
                break;
                default:
                break;
              } 
        }
#endif //NUMERIC_COMPARISON_ENABLE
#endif//PAIR_ENCRYPT_ENABLE    
        break;
    case UART_SYNC:
        memcpy((void*)&len, (void*)&uart_rx_buf[UART_SYNC_BYTE_LEN], UART_LEN_LEN);
        con_idx = uart_rx_buf[UART_SYNC_BYTE_LEN + UART_LEN_LEN];
       
        if (CONNECTION_IS_SERVER(con_idx))
        {
            if(len > 0 && len <= UART_RX_PAYLOAD_LEN_MAX)
            {
                uart_state = UART_RECEIVING;
                HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[UART_HEADER_LEN], len);
                restart = false;
            }
        }
        else      
        {
            LOG_I("Uart recv invalid con idx = %d!!!", con_idx);
            // restart = true; 
        }
        break;
#if (PAIR_ENCRYPT_ENABLE == 1)
    case UART_OOB:
         con_idx = uart_rx_buf[UART_SYNC_BYTE_LEN]; 
          if (CONNECTION_IS_SERVER(con_idx))
          {
               #if (SC_OOB_ENABLE ==1)
              memcpy((void*)&uart_pairing_ble_buf[0], (void*)&uart_rx_buf[UART_SYNC_BYTE_LEN+UART_LINK_ID_LEN], UART_SC_OOB_COMFIRM_LEN+UART_SC_OOB_RAND_LEN);
              #endif //SC_OOB_ENABLE

              #if (LEGACY_OOB_ENABLE ==1)
              memcpy((void*)&uart_pairing_ble_buf[0], (void*)&uart_rx_buf[UART_SYNC_BYTE_LEN+UART_LINK_ID_LEN], BLE_KEY_LEN);
              #endif //LEGACY_OOB_ENABLE

              #if ((SC_OOB_ENABLE == 1) || (LEGACY_OOB_ENABLE == 1))
              uart_rx_oob_flg =true;
              #endif//SC_OOB_ENABLE || LEGACY_OOB_ENABLE
          }
    break;
#if (LEGACY_PASSKEY_ENTRY_ENABLE ==1)      
    case UART_PASSKEY:
            memset(&uart_pairing_ble_buf[0],0,(LEGACY_PAIRING_PASSKEY_LEN+1));

            memcpy(&uart_pairing_ble_buf[0], &uart_rx_buf[pk_nc_recv_index], (LEGACY_PAIRING_PASSKEY_LEN+1));
            pk_nc_recv_index = 0;
            uart_rx_pass_key_flg= true;
    break;
#endif // LEGACY_PASSKEY_ENTRY_ENABLE

#if (NUMERIC_COMPARISON_ENABLE ==1)      
    case UART_NUMERIC_COMPARISON:
            memset(&uart_pairing_ble_buf[0],0,(NUMERIC_COMPARISON_COMFIRMS_LEN+1));

            memcpy(&uart_pairing_ble_buf[0], &uart_rx_buf[pk_nc_recv_index], (NUMERIC_COMPARISON_COMFIRMS_LEN+1));
            pk_nc_recv_index = 0;
            uart_rx_numeric_comparison_flg= true;
    break;
#endif // NUMERIC_COMPARISON_ENABLE          
#endif // PAIR_ENCRYPT_ENABLE  
    case UART_RECEIVING:
        memcpy((void*)&len, (void*)&uart_rx_buf[UART_SYNC_BYTE_LEN], UART_LEN_LEN);
        con_idx = uart_rx_buf[UART_SYNC_BYTE_LEN + UART_LEN_LEN];     
        if (CONNECTION_IS_SERVER(con_idx))
        {              
            if(uart_server_recv_data_length == 0)
            {
                memcpy((void*)&uart_server_ble_buf[0], (void*)&uart_rx_buf[UART_HEADER_LEN], len);
                uart_server_recv_data_length = len;
            }            
        }        
        // restart = false;
        break;
    default:
        break;
    }
    if(restart)
    {
        uart_state = UART_IDLE;
        HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[0], UART_SYNC_BYTE_LEN);
    }
}
static void ls_uart_server_client_uart_tx(void)
{  
    if (uart_server_tx_buf[0] == UART_SYNC_BYTE)
    {
        uint32_t cpu_stat = enter_critical();
        if (!uart_tx_busy)
        {
            uint16_t length = (uart_server_tx_buf[2] << 8) | uart_server_tx_buf[1];
            uart_tx_busy = true;
            current_uart_tx_idx = (0 << 7);
            HAL_UART_Transmit_IT(&UART_Config, &uart_server_tx_buf[0], length + UART_HEADER_LEN);
        }
        exit_critical(cpu_stat);
    }
}

static void connect_pattern_send_prepare(uint8_t con_idx)
{   
    if (CONNECTION_IS_SERVER(con_idx))
    {         
        uart_server_tx_buf[0] = UART_SYNC_BYTE;
        uart_server_tx_buf[1] = CONNECTED_MSG_PATTERN_LEN & 0xff;
        uart_server_tx_buf[2] = (CONNECTED_MSG_PATTERN_LEN >> 8) & 0xff;
        uart_server_tx_buf[3] = con_idx;
        uart_server_tx_buf[4] = CONNECTED_MSG_PATTERN & 0xff;
        uart_server_tx_buf[5] = (CONNECTED_MSG_PATTERN >> 8) & 0xff;         
    }  
}

static void disconnect_pattern_send_prepare(uint8_t con_idx, uint8_t role)
{   
    if (role == LS_BLE_ROLE_SLAVE)
    {
         
        uart_server_tx_buf[0] = UART_SYNC_BYTE;
        uart_server_tx_buf[1] = DISCONNECTED_MSG_PATTERN_LEN & 0xff;
        uart_server_tx_buf[2] = (DISCONNECTED_MSG_PATTERN_LEN >> 8) & 0xff;
        uart_server_tx_buf[3] = con_idx;
        uart_server_tx_buf[4] = DISCONNECTED_MSG_PATTERN & 0xff;
        uart_server_tx_buf[5] = (DISCONNECTED_MSG_PATTERN >> 8) & 0xff;        
    } 
}

#if (LEGACY_OOB_ENABLE == 1) ||  (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
static void legacy_paring_pattern_send_prepare(uint8_t con_idx, enum gap_evt_type type)
{   
    uart_pairing_ble_buf[0] = UART_PAIRING_SYNC_BYTE;
    uart_pairing_ble_buf[1] = LEGACY_PAIRING_PATTERN_LEN & 0xff;
    uart_pairing_ble_buf[2] = (LEGACY_PAIRING_PATTERN_LEN >> 8) & 0xff;
    uart_pairing_ble_buf[3] = con_idx;
    switch (type)
    {
       case REQUEST_LEGACY_OOB:
         #if (LEGACY_OOB_ENABLE == 1)
         uart_pairing_ble_buf[4] = LEGACY_OOB_PATTERN & 0xff;
         uart_pairing_ble_buf[5] = (LEGACY_OOB_PATTERN >> 8) & 0xff; 
         #endif //LEGACY_OOB_ENABLE
       break;
       case REQUEST_PASSKEY:
        #if (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
         uart_pairing_ble_buf[4] = LEGACY_PASSKEY_ENTRY_PATTERN & 0xff;
         uart_pairing_ble_buf[5] = (LEGACY_PASSKEY_ENTRY_PATTERN >> 8) & 0xff; 
        #endif //LEGACY_PASSKEY_ENTRY_ENABLE
        break;
       default:
       break;
    }   
}
#endif //LEGACY_OOB_ENABLE

static void gap_manager_callback(enum gap_evt_type type,union gap_evt_u *evt,uint8_t con_idx)
{
    switch(type)
    {
        case CONNECTED:
            if (gap_manager_get_role(con_idx) == LS_BLE_ROLE_SLAVE)
            {
                LS_ASSERT(con_idx_server == 0xff);
                con_idx_server = con_idx;   
                connect_pattern_send_prepare(con_idx); 

    #if (PAIR_ENCRYPT_ENABLE == 1)
            gap_manager_slave_security_req(con_idx, AUTH_SEC_CON);
    #endif //PAIR_ENCRYPT_ENABLE

            }
            LOG_I("connected! new con_idx = %d", con_idx);
        break;
        case DISCONNECTED:
            LOG_I("disconnected! delete con_idx = %d", con_idx);       
            if (CONNECTION_IS_SERVER(con_idx))
            {
                ls_uart_server_init();
                disconnect_pattern_send_prepare(con_idx, LS_BLE_ROLE_SLAVE);
                con_idx_server = CON_IDX_INVALID_VAL;        
                uart_server_mtu = UART_SERVER_MTU_DFT;
                start_adv();
            }      
        break;
        case CONN_PARAM_REQ:

        break;
        case CONN_PARAM_UPDATED:
        break;
    #if (PAIR_ENCRYPT_ENABLE == 1)   
    case MASTER_PAIR_REQ:
        {	
        #if (LEGACY_JUST_WORKS_ENABLE == 1)
            struct pair_feature feat_param={
                .iocap = BLE_GAP_IO_CAPS_NONE,
                .oob = BLE_GAP_OOB_DISABLE,
                .auth = AUTH_MITM | AUTH_BOND,
                .key_size = 16,
                .ikey_dist = KDIST_ENCKEY|KDIST_IDKEY,
                .rkey_dist = KDIST_ENCKEY|KDIST_IDKEY,
            };
            gap_manager_slave_pair_response_send(con_idx, true, &feat_param);
            LOG_I("JUST_WORKS  ");
        
        #elif (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
            struct pair_feature feat_param={
                .iocap = BLE_GAP_IO_CAPS_DISPLAY_ONLY,
                .oob = BLE_GAP_OOB_DISABLE,
                .auth = AUTH_MITM | AUTH_BOND,
                .key_size = 16,
                .ikey_dist = KDIST_ENCKEY|KDIST_IDKEY,
                .rkey_dist = KDIST_ENCKEY|KDIST_IDKEY,
            };
            gap_manager_slave_pair_response_send(con_idx, true, &feat_param);
            LOG_I("PASSKEY  ");
            
        #elif (NUMERIC_COMPARISON_ENABLE == 1)
            struct pair_feature feat_param={
                .iocap = BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY,
                .oob = BLE_GAP_OOB_DISABLE,
                .auth = AUTH_SEC_CON | AUTH_MITM,
                .key_size = 16,
                .ikey_dist = KDIST_ENCKEY|KDIST_IDKEY,
                .rkey_dist = KDIST_ENCKEY|KDIST_IDKEY,
            };
            gap_manager_slave_pair_response_send(con_idx, true, &feat_param);
            LOG_I("NUMERIC_COMPARISON  ");		
            
        #elif (LEGACY_OOB_ENABLE == 1)
            struct pair_feature feat_param={
                .iocap = BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY,
                .oob = BLE_GAP_OOB_ENABLE,
                .auth = AUTH_MITM ,
                .key_size = 16,
                .ikey_dist = KDIST_ENCKEY|KDIST_IDKEY,
                .rkey_dist = KDIST_ENCKEY|KDIST_IDKEY,
            };
            gap_manager_slave_pair_response_send(con_idx, true, &feat_param);
            LOG_I("LEGACY_OOB  ");		
                 
        #elif (SC_OOB_ENABLE == 1)
            struct pair_feature feat_param={
                .iocap = BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY,
                .oob = BLE_GAP_OOB_ENABLE,
                .auth = AUTH_SEC_CON | AUTH_BOND,
                .key_size = 16,
                .ikey_dist = KDIST_ENCKEY|KDIST_IDKEY,
                .rkey_dist = KDIST_ENCKEY|KDIST_IDKEY,
            };
            gap_manager_slave_pair_response_send(con_idx, true, &feat_param);
        #endif
        }break;
        case PAIR_DONE:
        {
            if(evt->pair_done.succeed)
            {
                LOG_I("PAIR_DONE");
            }
        }
        break;
        case ENCRYPT_FAIL:
            LOG_I("ENCRYPT_FAIL");
        break;
        case ENCRYPT_DONE:
        {
        }break;  
        case NUMERIC_COMPARE:
        {
            #if (NUMERIC_COMPARISON_ENABLE == 1)
            LOG_I("NUMERIC_COMPARE");
            uint8_t str_numeric_comparison[NUMERIC_COMPARISON_LEN *2 +1]={0};
            uint8_t str_numeric_comparison_len=0;
            memcpy(str_numeric_comparison,(uint8_t *)&(evt->numeric_compare.number),NUMERIC_COMPARISON_LEN);
            str_numeric_comparison_len = sprintf((char*)&uart_pairing_ble_buf[0],"\r\nNC=%s\r\n",str_numeric_comparison);
            uint32_t cpu_stat = enter_critical();
            if(!uart_tx_busy)
            {
                uart_tx_busy = true;
                HAL_UART_Transmit_IT(&UART_Config, &uart_pairing_ble_buf[0], str_numeric_comparison_len);
            } 
            exit_critical(cpu_stat);
            
            #endif //NUMERIC_COMPARISON_ENABLE
        }
        break;
        case REQUEST_PASSKEY:
        {
            #if (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
            LOG_I("REQUEST_PASSKEY");
            legacy_paring_pattern_send_prepare(con_idx,REQUEST_PASSKEY);
            uint32_t cpu_stat = enter_critical();
            if(!uart_tx_busy)
            {
                uart_tx_busy = true;
                HAL_UART_Transmit_IT(&UART_Config, &uart_pairing_ble_buf[0], UART_SYNC_BYTE_LEN+UART_LEGACY_PAIRING_REQ_LEN);
            } 
            exit_critical(cpu_stat);
            #endif //LEGACY_PASSKEY_ENTRY_ENABLE
        }
        break;
        case DISPLAY_PASSKEY:
        {
            #if (LEGACY_PASSKEY_ENTRY_ENABLE == 1)
            LOG_I("DISPLAY_PASSKEY");
            uint8_t str_pass_key_entry[LEGACY_PAIRING_PASSKEY_LEN *2 +1]={0};
            uint8_t str_pass_key_entry_len=0;
            memcpy(str_pass_key_entry,(uint8_t *)&(evt->display_passkey.passkey),LEGACY_PAIRING_PASSKEY_LEN);
            str_pass_key_entry_len = sprintf((char*)&uart_pairing_ble_buf[0],"\r\nPK=%s\r\n",str_pass_key_entry);
            uint32_t cpu_stat = enter_critical();
            if(!uart_tx_busy)
            {
                uart_tx_busy = true;
                HAL_UART_Transmit_IT(&UART_Config, &uart_pairing_ble_buf[0], str_pass_key_entry_len);
            } 
            exit_critical(cpu_stat);
            #endif //LEGACY_PASSKEY_ENTRY_ENABLE
        }
        break;
        case REQUEST_LEGACY_OOB:
        {
        #if (LEGACY_OOB_ENABLE == 1)
            LOG_I("REQUEST_LEGACY_OOB");
            legacy_paring_pattern_send_prepare(con_idx,REQUEST_LEGACY_OOB);
            uint32_t cpu_stat = enter_critical();
            if(!uart_tx_busy)
            {
                uart_tx_busy = true;
                HAL_UART_Transmit_IT(&UART_Config, &uart_pairing_ble_buf[0], UART_SYNC_BYTE_LEN+UART_LEGACY_PAIRING_REQ_LEN);
            } 
            exit_critical(cpu_stat);
            #endif //LEGACY_OOB_ENABLE
        }
        break;
        case REQUEST_SC_OOB:
        {
            #if (SC_OOB_ENABLE == 1)
            LOG_I("REQUEST_SC_OOB");
            uart_pairing_ble_buf[0] = UART_PAIRING_SYNC_BYTE;
            uart_pairing_ble_buf[1] = con_idx;
            memcpy((void*)&uart_pairing_ble_buf[UART_SYNC_BYTE_LEN+UART_LINK_ID_LEN], &(evt->sc_oob_exchange.sc_oob->conf[0]),BLE_KEY_LEN);
            memcpy((void*)&uart_pairing_ble_buf[UART_SYNC_BYTE_LEN+UART_LINK_ID_LEN+BLE_KEY_LEN], &(evt->sc_oob_exchange.sc_oob->rand[0]),BLE_KEY_LEN);
            uint32_t cpu_stat = enter_critical();
            if(!uart_tx_busy)
            {
                uart_tx_busy = true;
                HAL_UART_Transmit_IT(&UART_Config, &uart_pairing_ble_buf[0], UART_SYNC_BYTE_LEN+UART_SC_OOB_LEN);
            } 
            exit_critical(cpu_stat);
        #endif //SC_OOB_ENABLE
        }
        break;
    #endif  // PAIR_ENCRYPT_ENABLE
        default:

        break;
    }
}

static void gatt_manager_callback(enum gatt_evt_type type,union gatt_evt_u *evt,uint8_t con_idx)
{
    bool disconnected = false; 
    if (gap_manager_get_role(con_idx) == LS_BLE_ROLE_SLAVE)
    {
        disconnected = con_idx_server == CON_IDX_INVALID_VAL;
    }
   
    if (!disconnected)
    {
        switch (type)
        {     
        case SERVER_READ_REQ:
            LOG_I("read req");
            ls_uart_server_read_req_ind(evt->server_read_req.att_idx, con_idx);
        break;
        case SERVER_WRITE_REQ:
            LOG_I("write req");
            ls_uart_server_write_req_ind(evt->server_write_req.att_idx, con_idx, evt->server_write_req.length, evt->server_write_req.value);
        break;
        case SERVER_NOTIFICATION_DONE:
            uart_server_ntf_done = true;
            LOG_I("ntf done");
        break;
        
        case MTU_CHANGED_INDICATION:
            if (CONNECTION_IS_SERVER(con_idx))
            {    
              uart_server_mtu = evt->mtu_changed_ind.mtu; 
            }
            LOG_I("mtu exch ind, mtu = %d", evt->mtu_changed_ind.mtu);
        break;
        default:
            LOG_I("Event not handled!");
            break;
        }
    }
    else
    {
        LOG_I("receive gatt msg when disconnected!");
    } 
}
static void dev_manager_callback(enum dev_evt_type type,union dev_evt_u *evt)
{
    switch(type)
    {
    case STACK_INIT:
    {
        struct ble_stack_cfg cfg = {
            .private_addr = true,
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
        dev_manager_add_service((struct svc_decl *)&ls_uart_server_svc);
        ls_uart_server_init();
        ls_uart_init(); 
        ls_app_timer_init();
        HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[0], UART_SYNC_BYTE_LEN);            
    }
    break; 
    case SERVICE_ADDED:
        gatt_manager_svc_register(evt->service_added.start_hdl, UART_SVC_ATT_NUM, &ls_uart_server_svc_env);
        create_adv_obj();
    break;
    case ADV_OBJ_CREATED:
        LS_ASSERT(evt->obj_created.status == 0);
        adv_obj_hdl = evt->obj_created.handle;
        start_adv();
        LOG_I("adv start");
    break;
    case ADV_STOPPED:
        LOG_I("adv stopped");
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
