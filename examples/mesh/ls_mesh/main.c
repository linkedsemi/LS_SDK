#define LOG_TAG "MAIN"
#include "ls_ble.h"
#include "platform.h"
#include "prf_diss.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include "spi_flash.h"
#include "tinyfs.h"
#include "builtin_timer.h"
#include "lsuart.h"
#include "io_config.h"
#include <string.h>
#include "co_math.h"
#include "ls_mesh.h"
#include "ls_mesh_light_cfg.h"

static void ls_mesh_light_handler(uint8_t const *value, uint8_t const len);

#define SPE_SERVER_MAX_MTU  247
#define SPE_SERVER_MTU_DFT  23
#define SPE_SERVER_MAX_DATA_LEN (spe_server_mtu - 3)
#define SPE_SVC_RX_MAX_LEN (SPE_SERVER_MAX_MTU - 3)
#define SPE_SVC_TX_MAX_LEN (SPE_SERVER_MAX_MTU - 3)
#define SPE_SVC_BUFFER_SIZE (1024)

#define SPE_SERVER_TIMEOUT 50 // timer units: ms
static const uint8_t spe_svc_uuid_128[] ={0x01, 0x00, 0x68, 0xe4, 0x25, 0xf9, 0xf4, 0x1c, 0x78, 0xfd, 0x7b, 0xf6, 0xde, 0xec, 0x28, 0x53};;
static const uint8_t spe_rx_char_uuid_128[] = {0x03, 0x00, 0x68, 0xe4, 0x25, 0xf9, 0xf4, 0x1c, 0x78, 0xfd, 0x7b, 0xf6, 0xde, 0xec, 0x28, 0x53};
static const uint8_t spe_tx_char_uuid_128[] ={0x02, 0x00, 0x68, 0xe4, 0x25, 0xf9, 0xf4, 0x1c, 0x78, 0xfd, 0x7b, 0xf6, 0xde, 0xec, 0x28, 0x53};
static const uint8_t att_decl_char_array[] = {0x03,0x28};
static const uint8_t att_desc_client_char_cfg_array[] = {0x02,0x29};
enum spe_svc_att_db_handles
{
    SPE_SVC_IDX_RX_CHAR,
    SPE_SVC_IDX_RX_VAL,
    SPE_SVC_IDX_TX_CHAR,
    SPE_SVC_IDX_TX_VAL,
    SPE_SVC_IDX_TX_NTF_CFG,
    SPE_SVC_ATT_NUM
};

static struct att_decl spe_server_att_decl[SPE_SVC_ATT_NUM] =
{
    [SPE_SVC_IDX_RX_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0, 
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,

    },
    [SPE_SVC_IDX_RX_VAL] = {
        .uuid = spe_rx_char_uuid_128,
        .s.max_len = SPE_SVC_RX_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.wr_cmd = 1,
        .char_prop.wr_req = 1,
    },
    [SPE_SVC_IDX_TX_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
    [SPE_SVC_IDX_TX_VAL] = {
        .uuid = spe_tx_char_uuid_128,
        .s.max_len = SPE_SVC_TX_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.ntf_en = 1,
    },
    [SPE_SVC_IDX_TX_NTF_CFG] = {
        .uuid = att_desc_client_char_cfg_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,

    },
};
static struct svc_decl spe_server_svc =
{
    .uuid = spe_svc_uuid_128,
    .att = (struct att_decl*)spe_server_att_decl,
    .nb_att = SPE_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_128BIT,
};
static struct gatt_svc_env spe_server_svc_env;
static uint8_t connect_id = 0xff; 
static uint8_t spe_server_rx_byte;
static uint8_t spe_server_buf[SPE_SVC_BUFFER_SIZE];
static uint8_t spe_server_tx_buf[SPE_SVC_BUFFER_SIZE];
static uint16_t spe_server_rx_index = 0;
static bool spe_server_ntf_done = true;
static bool ls_mesh_ready=false;
static uint16_t spe_server_mtu = SPE_SERVER_MAX_MTU;
static struct builtin_timer *spe_server_timer_inst = NULL;
static uint16_t cccd_config = 0;

static uint8_t adv_obj_hdl;
#define LS_MESH_CON_ADV_NAME "PMESH_T9"
static uint8_t advertising_data[28] ={0x9,0x9,'P','M','E','S','H','_','T','9'};  //PMESH_T
uint8_t mac_address[6] = {0x34,0x2d,0x6b,0x63,0xa7,0xf9};
static uint8_t scan_response_data[31];
static void start_adv(void);

#if 1 
static uint8_t test_data[60]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
                              0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19, 
                              0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29, 
                              0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39, 
                              0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49, 
                              0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59
};
#if TEST_MODE
static uint8_t return_test_data[76]={0x00,0x01,0x02,0x03,0x04,0x05,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,
                                     0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,
                                     0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79, 
                                     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89, 
                                     0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99, 
                                     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9, 
                                     0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9

};
#endif //TEST_MODE
uint8_t send_data[80]={0};
#endif //TEST_MODEMODE 
static void spe_server_timer_init(void);
static void spe_server_timer_cb(void *param);
static void spe_server_read_req_ind(uint8_t att_idx, uint8_t con_idx);
static void spe_server_write_req_ind(uint8_t att_idx, uint8_t con_idx, uint16_t length, uint8_t const *value);
static void spe_server_send_notification(void);
static void spe_server_data_length_update(uint8_t con_idx);


static UART_HandleTypeDef UART_Server_Config; 
static bool uart_server_tx_busy;
static void ls_uart_init(void);

static void spe_server_timer_init(void)
{
    spe_server_timer_inst = builtin_timer_create(spe_server_timer_cb);
    builtin_timer_start(spe_server_timer_inst, SPE_SERVER_TIMEOUT, NULL);
}
static void spe_server_timer_cb(void *param)
{
    if(connect_id != 0xff)
    {
         uint32_t cpu_stat = enter_critical();
        // LOG_I("uart timer out, length=%d", uart_server_rx_index);
        spe_server_send_notification();
        exit_critical(cpu_stat);
    }
    if(spe_server_timer_inst)
    {
        builtin_timer_start(spe_server_timer_inst, SPE_SERVER_TIMEOUT, NULL); 
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_server_tx_busy = false;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(spe_server_rx_index < SPE_SVC_BUFFER_SIZE)
    {
        spe_server_buf[spe_server_rx_index++] = spe_server_rx_byte;

        if (ls_mesh_ready==false)
        {
           spe_server_rx_index = 0;  
        }
        else
        {
           if (spe_server_rx_index >= spe_server_buf[0]) //define  uart_server_buf[0] == data_len
           {
               spe_server_rx_index = 0;
               LOG_I("ls_mesh_beacon");
               LOG_HEX(&spe_server_buf[1],(spe_server_buf[0]-1));
               ls_mesh_set_beacon_value_ind(&spe_server_buf[1],(spe_server_buf[0]-1));
           }
        }
    }
    else
    {   
        LOG_I("uart server rx buffer overflow!");
    }
    HAL_UART_Receive_IT(&UART_Server_Config, &spe_server_rx_byte, 1);
}

static void ls_uart_init(void)
{
    uart1_io_init(PB00, PB01);
    UART_Server_Config.UARTX = UART1;
    UART_Server_Config.Init.BaudRate = UART_BAUDRATE_9600;
    UART_Server_Config.Init.MSBEN = 0;
    UART_Server_Config.Init.Parity = UART_NOPARITY;
    UART_Server_Config.Init.StopBits = UART_STOPBITS1;
    UART_Server_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Server_Config);
}

static void spe_server_read_req_ind(uint8_t att_idx, uint8_t con_idx)
{
    uint16_t handle = 0;
    if(att_idx == SPE_SVC_IDX_TX_NTF_CFG)
    {
        handle = gatt_manager_get_svc_att_handle(&spe_server_svc_env, att_idx);
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void*)&cccd_config, 2);
    }
}
static void spe_server_write_req_ind(uint8_t att_idx, uint8_t con_idx, uint16_t length, uint8_t const *value)
{
    if(att_idx == SPE_SVC_IDX_RX_VAL)
    { 
#if 1    
        memcpy(&send_data[0],value,length);
        memcpy(&send_data[length],&advertising_data[2],8);
        memcpy(&send_data[length+8],test_data,60);
        ls_mesh_set_beacon_value_ind(&send_data[0],length+68);
#else        

     ls_mesh_set_beacon_value_ind(value,length);
#endif //TEST_MODEMODE     
        ls_mesh_light_handler(value,length);    //test code
    }
    else if (att_idx == SPE_SVC_IDX_TX_NTF_CFG)
    {
        LS_ASSERT(length == 2);
        memcpy(&cccd_config, value, length);
    }   
}

static void spe_server_send_notification(void)
{
    if(spe_server_rx_index > 0 && spe_server_ntf_done)
    {
        spe_server_ntf_done = false;
        uint16_t handle = gatt_manager_get_svc_att_handle(&spe_server_svc_env, SPE_SVC_IDX_TX_VAL);
        uint16_t tx_len = spe_server_rx_index > co_min(SPE_SERVER_MAX_DATA_LEN, SPE_SVC_TX_MAX_LEN) ? co_min(SPE_SERVER_MAX_DATA_LEN, SPE_SVC_TX_MAX_LEN) : spe_server_rx_index;
        spe_server_rx_index -= tx_len;
        gatt_manager_server_send_notification(connect_id, handle, spe_server_buf, tx_len, NULL);
        memcpy((void*)&spe_server_buf[0], (void*)&spe_server_buf[tx_len], spe_server_rx_index);
    }    
}

static void spe_server_data_length_update(uint8_t con_idx)
{
    struct gap_set_pkt_size dlu_param = 
    {
        .pkt_size = 251,
    };
    gap_manager_set_pkt_size(con_idx, &dlu_param);
}

static void gap_manager_callback(enum gap_evt_type type,union gap_evt_u *evt,uint8_t con_idx)
{
    switch(type)
    {
    case CONNECTED:
        connect_id = con_idx;
        LOG_I("connected!");
    break;
    case DISCONNECTED:
        connect_id = 0xff;
        spe_server_mtu = SPE_SERVER_MTU_DFT;
        start_adv();
        LOG_I("disconnected!");
    break;
    case CONN_PARAM_REQ:
        //LOG_I
    break;
    case CONN_PARAM_UPDATED:

    break;
    default:

    break;
    }
}

static void gatt_manager_callback(enum gatt_evt_type type,union gatt_evt_u *evt,uint8_t con_idx)
{
    switch (type)
    {
    case SERVER_READ_REQ:
        LOG_I("read req");
        spe_server_read_req_ind(evt->server_read_req.att_idx, con_idx);
    break;
    case SERVER_WRITE_REQ:
        LOG_I("write req");
        spe_server_write_req_ind(evt->server_write_req.att_idx, con_idx, evt->server_write_req.length, evt->server_write_req.value);
    break;
    case SERVER_NOTIFICATION_DONE:
        spe_server_ntf_done = true;
        LOG_I("ntf done");
    break;
    case MTU_CHANGED_INDICATION:
        spe_server_mtu = evt->mtu_changed_ind.mtu;
        LOG_I("mtu: %d", spe_server_mtu);
        spe_server_data_length_update(con_idx);
    break;
    default:
        LOG_I("Event not handled!");
        break;
    }
}


static void ls_mesh_manager_callback(enum ls_mesh_evt_type type, union ls_mesh_evt_u *evt)
{
    uint16_t len_value=0;
      switch (type)
      {
          case LS_MESH_RX_MSG_EVT:
          {
               len_value = (evt->ls_mesh_send_msg.msg_len+1)-16;
              if(uart_server_tx_busy)
              {
                LOG_I("Uart tx busy, data discard!");
              }
              else
              {
                 uart_server_tx_busy = true;
                 LS_ASSERT(len_value <= SPE_SVC_BUFFER_SIZE);
                 memcpy(&spe_server_tx_buf[0], (uint8_t*)&(evt->ls_mesh_send_msg.value[0]), len_value);
                 HAL_UART_Transmit_IT(&UART_Server_Config, &spe_server_tx_buf[0], len_value);
              }

             ls_mesh_light_handler(&(evt->ls_mesh_send_msg.value[0]), len_value);
             LOG_I("pmesh_rx_data");
             LOG_HEX(&(evt->ls_mesh_send_msg.value[0]),len_value);
          }
          break;
          default:
             break;
      }
}


static void ls_mesh_light_handler(uint8_t const *value, uint8_t const len)   //test code
{
		switch(value[2])
		{
		  case 0x00:
			{
			  ls_mesh_light_set_onoff(false,LED_PIN_0);
			  ls_mesh_light_set_onoff(false,LED_PIN_1);
              LOG_I("power_off");
			}
				break;
			case 0x01:
			{	
			  ls_mesh_light_set_onoff(true,LED_PIN_0);
			  ls_mesh_light_set_onoff(false,LED_PIN_1);
              LOG_I("channel_1");
			}	
				break;
			case 0x02:
			{
			  ls_mesh_light_set_onoff(false,LED_PIN_0);
			  ls_mesh_light_set_onoff(true,LED_PIN_1);
              LOG_I("channel_2");
			}	
				break;
			case 0x03:
			{
			  ls_mesh_light_set_onoff(true,LED_PIN_0);
			  ls_mesh_light_set_onoff(true,LED_PIN_1);
              LOG_I("power_on");
			}	
				break;
			default:
				break;
		}
#if TEST_MODE
      if (!memcmp(&advertising_data[2], &value[0],8))
      {
          LOG_I("P_MESH_T%d to P_MESH_T%d",value[15]-0x30,value[7]-0x30);
          if (!memcmp(&return_test_data[16], &value[16],60))
          {
              LOG_I("rx return Message");
          }
          else
          {
              LOG_I("tx return Message");
             memcpy(&return_test_data[0],&value[8],8);
             memcpy(&return_test_data[8],&advertising_data[2],8);
             ls_mesh_set_beacon_value_ind(&return_test_data[0],76);
          }
      }
#endif //TEST_MODEMODE        	
}


static void create_adv_obj()
{
    struct legacy_adv_obj_param adv_param = {
        .adv_intv_min = 32,  //500ms
        .adv_intv_max = 32,  //500ms
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
    uint8_t adv_data_length = ADV_DATA_PACK(advertising_data, 1, GAP_ADV_TYPE_SHORTENED_NAME, LS_MESH_CON_ADV_NAME, sizeof(LS_MESH_CON_ADV_NAME));
    dev_manager_start_adv(adv_obj_hdl,advertising_data,adv_data_length,scan_response_data,0);
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
        dev_manager_set_mac_addr(&mac_address[0]);
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
        ls_mesh_init();
        dev_manager_add_service((struct svc_decl *)&spe_server_svc);
        ls_uart_init(); 
        HAL_UART_Receive_IT(&UART_Server_Config, &spe_server_rx_byte, 1); 
        spe_server_timer_init();
    }
    break;
    case SERVICE_ADDED:
        gatt_manager_svc_register(evt->service_added.start_hdl, SPE_SVC_ATT_NUM, &spe_server_svc_env);
 //        create_adv_obj();
        dev_manager_prf_ls_mesh_add(NO_SEC, NULL/*&feature*/);
    break;
    case PROFILE_ADDED: 
        prf_ls_mesh_callback_init(ls_mesh_manager_callback);
        ls_mesh_ready =true;
        create_adv_obj();
    break;    
    case ADV_OBJ_CREATED:
        LS_ASSERT(evt->obj_created.status == 0);
        adv_obj_hdl = evt->obj_created.handle;
        start_adv();
        ls_mesh_start();
    break;
    case ADV_STOPPED:
      LOG_I("adv_stopped");
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
    ls_mesh_light_init();
    ble_init();
    dev_manager_init(dev_manager_callback);
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
}
