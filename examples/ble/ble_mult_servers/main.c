#define LOG_TAG "MAIN"
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
#include "prf_fotas.h"
#include "ota_settings.h"
#include "SEGGER_RTT.h"
#include "prf_bass.h"

#define UART_SVC_ADV_NAME "LS Mult Servers"

#define UART_SERVER_MAX_MTU  247
#define UART_SERVER_MTU_DFT  23
#define UART_SERVER_MAX_DATA_LEN (uart_server_mtu - 3)
#define UART_SVC_RX_MAX_LEN (UART_SERVER_MAX_MTU - 3)
#define UART_SVC_TX_MAX_LEN (UART_SERVER_MAX_MTU - 3)
#define UART_SVC_BUFFER_SIZE (1024)

#define UART_SERVER_TIMEOUT 50 // timer units: ms
static const uint8_t ls_uart_svc_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x01,0x00,0x40,0x6e};
static const uint8_t ls_uart_rx_char_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x02,0x00,0x40,0x6e};
static const uint8_t ls_uart_tx_char_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x03,0x00,0x40,0x6e};
static const uint8_t att_decl_char_array[] = {0x03,0x28};
static const uint8_t att_desc_client_char_cfg_array[] = {0x02,0x29};
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
    [UART_SVC_IDX_RX_CHAR] = {						//写特征值
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [UART_SVC_IDX_RX_VAL] = {
        .uuid = ls_uart_rx_char_uuid_128,			//写特征值uuid
        .s.max_len = UART_SVC_RX_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.wr_cmd = 1,
        .char_prop.wr_req = 1,
    },
    [UART_SVC_IDX_TX_CHAR] = {						//通知特征值
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1, 
    },
    [UART_SVC_IDX_TX_VAL] = {
        .uuid = ls_uart_tx_char_uuid_128,			//通知特征值uuid
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
    .uuid = ls_uart_svc_uuid_128,					//主服务uuid
    .att = (struct att_decl*)ls_uart_server_att_decl,
    .nb_att = UART_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_128BIT,
};
static struct gatt_svc_env ls_uart_server_svc_env;


#define PRIVATE_SERVER_MAX_MTU  247
#define PRIVATE_SVC_MAX_LEN (PRIVATE_SERVER_MAX_MTU - 3)

static const uint8_t ls_private_svc_uuid_128[] = 			{0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x01,0x00,0x34,0xa0};
static const uint8_t ls_private_read_char_uuid_128[] = 		{0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x02,0x00,0x34,0xa0};
static const uint8_t ls_private_write_char_uuid_128[] = 	{0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x03,0x00,0x34,0xa0};
static const uint8_t ls_private_notify_char_uuid_128[] = 	{0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x04,0x00,0x34,0xa0};
static const uint8_t ls_private_indicate_char_uuid_128[] = 	{0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x05,0x00,0x34,0xa0};

enum private_svc_att_db_handles
{
    PROVATE_SVC_IDX_READ_CHAR,
    PROVATE_SVC_IDX_READ_VAL,
    PROVATE_SVC_IDX_WRITE_CHAR,
    PROVATE_SVC_IDX_WRITE_VAL,
    PROVATE_SVC_IDX_NOTITY_CHAR,
    PROVATE_SVC_IDX_NOTITY_VAL,
    PROVATE_SVC_IDX_NOTITY_NTF_CFG,
    PROVATE_SVC_IDX_INDICATE_CHAR,
    PROVATE_SVC_IDX_INDICATEVAL,
    PROVATE_SVC_IDX_INDICATE_NTF_CFG,
    PROVATE_SVC_ATT_NUM
};

static const struct att_decl ls_private_server_att_decl[PROVATE_SVC_ATT_NUM] =
{
    [PROVATE_SVC_IDX_READ_CHAR] = {						//读特征值
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [PROVATE_SVC_IDX_READ_VAL] = {
        .uuid = ls_private_read_char_uuid_128,			//读特征值uuid
        .s.max_len = PRIVATE_SVC_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },    
	[PROVATE_SVC_IDX_WRITE_CHAR] = {					//写特征值
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [PROVATE_SVC_IDX_WRITE_VAL] = {
        .uuid = ls_private_write_char_uuid_128,			//写特征值uuid
        .s.max_len = PRIVATE_SVC_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.wr_cmd = 1,
        .char_prop.wr_req = 1,
    },
    [PROVATE_SVC_IDX_NOTITY_CHAR] = {					//通知特征值
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1, 
    },
    [PROVATE_SVC_IDX_NOTITY_VAL] = {
        .uuid = ls_private_notify_char_uuid_128,		//通知特征值uuid
        .s.max_len = PRIVATE_SVC_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.ntf_en = 1,
    },
    [PROVATE_SVC_IDX_NOTITY_NTF_CFG] = {
        .uuid = att_desc_client_char_cfg_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
    },
    [PROVATE_SVC_IDX_INDICATE_CHAR] = {					//指示特征值
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1, 
    },
    [PROVATE_SVC_IDX_INDICATEVAL] = {
        .uuid = ls_private_indicate_char_uuid_128,		//指示特征值uuid
        .s.max_len = PRIVATE_SVC_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.ind_en = 1,
    },
    [PROVATE_SVC_IDX_INDICATE_NTF_CFG] = {
        .uuid = att_desc_client_char_cfg_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
    },
};
static const struct svc_decl ls_private_server_svc =
{
    .uuid = ls_private_svc_uuid_128,
    .att = (struct att_decl*)ls_private_server_att_decl,
    .nb_att = PROVATE_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_128BIT,
};
static struct gatt_svc_env ls_private_server_svc_env;

static uint8_t connect_id = 0xff; 
static uint16_t uart_cccd_config = 0;
static uint16_t pri_not_cccd_config = 0;
static uint16_t pri_ind_cccd_config = 0;

static uint8_t adv_obj_hdl;
static uint8_t advertising_data[28] = {0x05, 0x09, 'u', 'a', 'r', 't'};
static uint8_t scan_response_data[31];

static void ls_uart_server_read_req_ind(uint8_t att_idx, uint8_t con_idx);
static void start_adv(void);
static void ls_uart_server_data_length_update(uint8_t con_idx);


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
    static uint32_t new_image_size_bytes = 0;
    static uint16_t segment_data_max_length = 0;
    switch(type)
    {
    case FOTAS_START_REQ_EVT:
    {
        enum fota_start_cfm_status status;
        if(fw_signature_check(evt->fotas_start_req.digest, evt->fotas_start_req.signature))
        {
            status = FOTA_REQ_ACCEPTED;
            new_image_size_bytes = evt->fotas_start_req.new_image->size;
            segment_data_max_length = evt->fotas_start_req.segment_data_max_length;
        }else
        {
            status = FOTA_REQ_REJECTED;
        }
        prf_fotas_start_confirm(status);
    }break;
    case FOTAS_PROGRESS_EVT:
    {
        uint32_t bytes_transfered = evt->fotas_progress.current_sector * 4096 + evt->fotas_progress.current_segment * segment_data_max_length;
        uint8_t percentage =  bytes_transfered*100/new_image_size_bytes >= 100 ? 100 : bytes_transfered*100/new_image_size_bytes;
        LOG_I("ota progress ---------> %d%%", percentage);
    }
    break;
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
    default:
        LS_ASSERT(0);
    break;
    }
}


static void ls_uart_server_read_req_ind(uint8_t att_idx, uint8_t con_idx)
{
    uint16_t handle = 0;
    if(att_idx == UART_SVC_IDX_TX_NTF_CFG)					//通知的cccd状态
    {
        handle = gatt_manager_get_svc_att_handle(&ls_uart_server_svc_env, att_idx);
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void*)&uart_cccd_config, 2);
    }
}


static void ls_private_server_read_req_ind(uint8_t att_idx, uint8_t con_idx)
{
    uint16_t handle = 0;
    if(att_idx == PROVATE_SVC_IDX_READ_VAL)					//读特征值返回数据
    {
		uint8_t data[10] = {0,1,2,3,4,5,6,7,8,9};
        handle = gatt_manager_get_svc_att_handle(&ls_private_server_svc_env, att_idx);
        gatt_manager_server_read_req_reply(con_idx, handle, 0, data, sizeof(data));
    }
    else if(att_idx == PROVATE_SVC_IDX_NOTITY_NTF_CFG)		//通知的cccd状态
    {
        handle = gatt_manager_get_svc_att_handle(&ls_private_server_svc_env, att_idx);
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void*)&pri_not_cccd_config, 2);
    }
    else if(att_idx == PROVATE_SVC_IDX_INDICATE_NTF_CFG)	//指示的cccd状态
    {
        handle = gatt_manager_get_svc_att_handle(&ls_private_server_svc_env, att_idx);
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void*)&pri_ind_cccd_config, 2);
    }
}


static void ls_uart_server_data_length_update(uint8_t con_idx)
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
        LOG_I("disconnected! reason = %x ",evt->disconnected.reason);   								//断连原因
        start_adv();
    break;
    case CONN_PARAM_REQ:
        //LOG_I
    break;
    case CONN_PARAM_UPDATED:
		LOG_I("conn param updata  interval = %d  latency = %d  sup_to = %d",evt->conn_param_updated.con_interval,evt->conn_param_updated.con_latency,evt->conn_param_updated.sup_to);
    break;
    default:

    break;
    }
}

static void gatt_manager_callback(enum gatt_evt_type type,union gatt_evt_u *evt,uint8_t con_idx)
{
    if (connect_id != 0xff)
    {
        switch (type)
        {
        case SERVER_READ_REQ:
            LOG_I("read req");
			if(ls_uart_server_svc_env.start_hdl == evt->server_read_req.svc->start_hdl)      			//串口服务读请求数据
			{
				ls_uart_server_read_req_ind(evt->server_read_req.att_idx, con_idx);
			}
			else if(ls_private_server_svc_env.start_hdl == evt->server_read_req.svc->start_hdl)			//私有服务读请求数据
			{
				ls_private_server_read_req_ind(evt->server_read_req.att_idx, con_idx);
			}
        break;
        case SERVER_WRITE_REQ:
		{
            LOG_I("write req");
			if(ls_uart_server_svc_env.start_hdl == evt->server_write_req.svc->start_hdl)				//串口服务写请求数据
			{
				LOG_I("uart server write data = ");
				LOG_HEX(evt->server_write_req.value,evt->server_write_req.length);
			}
			else if(ls_private_server_svc_env.start_hdl == evt->server_write_req.svc->start_hdl)		//私有服务写请求数据
			{
				LOG_I("private server write data = ");
				LOG_HEX(evt->server_write_req.value,evt->server_write_req.length);
			}
		}
		
        break;
        case SERVER_NOTIFICATION_DONE:
            LOG_I("ntf done");
        break;
        case MTU_CHANGED_INDICATION:
            LOG_I("mtu: %d", evt->mtu_changed_ind.mtu);
            ls_uart_server_data_length_update(con_idx);
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

static void start_adv(void)
{
    LS_ASSERT(adv_obj_hdl != 0xff);
	uint8_t user_data[10] = {1,2,3,4,5,6,7,8,9,0};
	uint8_t app_data[2] = {0xc2,0x03};
	
    uint8_t adv_data_length = ADV_DATA_PACK(advertising_data, 2, GAP_ADV_TYPE_SHORTENED_NAME, UART_SVC_ADV_NAME, strlen(UART_SVC_ADV_NAME),			//广播名称数据
																GAP_ADV_TYPE_APPEARANCE, app_data, sizeof(app_data));								//设备外观数据
	
    uint8_t scan_data_length = ADV_DATA_PACK(scan_response_data, 1, GAP_ADV_TYPE_MANU_SPECIFIC_DATA, user_data, sizeof(user_data));					//厂商数据
		
    dev_manager_start_adv(adv_obj_hdl, advertising_data, adv_data_length, scan_response_data, scan_data_length);
    LOG_I("adv start");
}

static void prf_batt_server_callback(enum bass_evt_type type, union bass_evt_u *evt)
{

}

static void prf_added_handler(struct profile_added_evt *evt)
{
    LOG_I("profile:%d, start handle:0x%x\n",evt->id,evt->start_hdl);
    switch(evt->id)
    {
		case PRF_FOTA_SERVER:
		{
			prf_fota_server_callback_init(prf_fota_server_callback);			//fota注册回调函数
			
			struct bas_db_cfg db_cfg = {
				.ins_num = 1,
				.ntf_enable[0] = 1,
			};
			dev_manager_prf_bass_server_add(NO_SEC,&db_cfg,sizeof(db_cfg));		//添加电池电量profile服务
		}
		break;
			
		case PRF_BASS:
			prf_bass_server_callback_init(prf_batt_server_callback); 			//电池电量注册回调函数
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
    }
    break;
    case STACK_READY:
    {
        uint8_t addr[6];
        bool type;
        dev_manager_get_identity_bdaddr(addr,&type);
        LOG_I("type:%d,addr:",type);
        LOG_HEX(addr,sizeof(addr));
		
        dev_manager_add_service((struct svc_decl *)&ls_uart_server_svc);		//添加串口服务
    }
    break;
    case SERVICE_ADDED:
	{
		static uint8_t server_num = 0;
		if(server_num == 0)
		{
			server_num = 1;
			gatt_manager_svc_register(evt->service_added.start_hdl, UART_SVC_ATT_NUM, &ls_uart_server_svc_env);		//注册串口服务
			dev_manager_add_service((struct svc_decl *)&ls_private_server_svc);										//添加私有服务
		}
		else if(server_num == 1)
		{
			server_num = 2;
			gatt_manager_svc_register(evt->service_added.start_hdl, PROVATE_SVC_ATT_NUM, &ls_private_server_svc_env);//注册私有服务
			dev_manager_prf_fota_server_add(NO_SEC);																 //添加fota升级profile服务
		}
	}
    break;
    case PROFILE_ADDED:
        prf_added_handler(&evt->profile_added);						     		//处理profile服务注册回调函数
    break;
    case ADV_OBJ_CREATED:
        LS_ASSERT(evt->obj_created.status == 0);
        adv_obj_hdl = evt->obj_created.handle;
        start_adv();
    break;
    case ADV_STARTED:
        LOG_I("adv started");
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
