/*
*********************************************************************************************************
*
*	模块名称 : 主程序模块
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 多服务多Profile情况下的连接通信；
*              例程目的：
*                1. 演示如何构造广播和扫描回应数据。
*                2. 演示如何添加多个Service和Profile。
*                3. 演示如何区分通信的数据是来自哪个服务的那个特征值。
*              例程内容：
*                1.多服务和多Profile的添加: 两个服务分别是 uart service 和一个私有服务 private service; 两个Profile分别是 fota pforile 和电池电量 BASS Profile。
*                2.
*              测试步骤：
*                1. app 连接广播名称是“LS Mult Services”的设备
*                2. 通过APP进行数据的上下行测试
*                   2.1. 支持Write属性的特征值，app下发数据后会以十六进制打印出来；
*                   2.2. Private Service支持Notify的特征值使能 CCCD 后会上报默认数据；
*                   2.3. 支持READ属性的属性值，读CCCD就返回当前CCCD的状态，Private Service特征值就返回程序中的默认值；
*              注意事项：
*                1.Service和Profile要一个一个添加，在SERVICE_ADDED或者PROFILE_ADDED事件中添加下一个Service或者Profile。
*                2.Profile的数量要在 app_config.h 中配置 SDK_MAX_PROFILE_NUM，例程是添加了2个Profile,故这个宏配置为2。
*
*	修改记录 :
*		版本号   日期         作者            说明
*		V1.0    2023-01-04    bcl        1. 基本功能实现
*               2023-01-05    jxia       1. 修复部分问题，添加注释
*
*	Copyright (C), 2020-2030, LinkedSemi https://www.linkedsemi.com/
*
*********************************************************************************************************
*/	

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

#define UART_SVC_ADV_NAME "LS Mult Services"        // 广播名称

#define UART_SERVER_MAX_MTU  247
#define UART_SERVER_MTU_DFT  23
#define UART_SERVER_MAX_DATA_LEN (uart_server_mtu - 3)
#define UART_SVC_RX_MAX_LEN (UART_SERVER_MAX_MTU - 3)
#define UART_SVC_TX_MAX_LEN (UART_SERVER_MAX_MTU - 3)
#define UART_SVC_BUFFER_SIZE (1024)
#define MULTI_SERVER_TIMEOUT 300   // timer units: ms

static const uint8_t ls_uart_svc_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x01,0x00,0x40,0x6e};        // 服务 128-bit uuid
static const uint8_t ls_uart_rx_char_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x02,0x00,0x40,0x6e};    // rx 特征值 128-bit uuid
static const uint8_t ls_uart_tx_char_uuid_128[] = {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x03,0x00,0x40,0x6e};    // tx 特征值 128-bit uuid
static const uint8_t att_decl_char_array[] = {0x03,0x28};                                                                               // 固定 16-bit uuid，代表特征值申明
static const uint8_t att_desc_client_char_cfg_array[] = {0x02,0x29};                                                                    // 固定 16-bit uuid, 代表特殊的描述符 CCCD(Client Characteristic Configuration Descriptor)

/*
Service

    Attribute Table
        Service Declaration
            Characteristic Declaration      // 特征值申明
            Characteristic Value            // 特征值 1
            Characteristic Declaration      // 特征值申明
            Characteristic Value            // 特征值 2
            Characteristic Descriptor       // 特征值描述符
            ...
*/
enum uart_svc_att_db_handles
{
    UART_SVC_IDX_RX_CHAR,               // 特征值申明
    UART_SVC_IDX_RX_VAL,                // RX 特征值
    UART_SVC_IDX_TX_CHAR,               // 特征值申明
    UART_SVC_IDX_TX_VAL,                // TX 特征值
    UART_SVC_IDX_TX_NTF_CFG,            // 特征值描述符
    UART_SVC_ATT_NUM                    // 当前服务一共有 UART_SVC_ATT_NUM 个属性值
};

static const struct att_decl ls_uart_server_att_decl[UART_SVC_ATT_NUM] =
{
    [UART_SVC_IDX_RX_CHAR] = {                      // 特征值申明
        .uuid = att_decl_char_array,                // attribute uuid，特征值申明是固定的16-bit uuid
        .s.max_len = 0,                             // 当前属性值支持的通信的最大的字节数
        .s.uuid_len = UUID_LEN_16BIT,               // UUID 的长度,常用的 16-BIT 和 128-BIT
        .s.read_indication = 1,                     // 默认为 1
        .char_prop.rd_en = 1,                       // 支持读属性
    },
    [UART_SVC_IDX_RX_VAL] = {                       // RX 特征值，128-bit uuid, (characteristic support write req/cmd properties)
        .uuid = ls_uart_rx_char_uuid_128,
        .s.max_len = UART_SVC_RX_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.wr_cmd = 1,                      // 支持Write-no-response属性
        .char_prop.wr_req = 1,                      // 支持Write-with-response属性
    },
    [UART_SVC_IDX_TX_CHAR] = {                      // 特征值申明
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1, 
    },
    [UART_SVC_IDX_TX_VAL] = {
        .uuid = ls_uart_tx_char_uuid_128,           // TX 特征值，128-bit uuid, (characteristic support notify properties)
        .s.max_len = UART_SVC_TX_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.ntf_en = 1,                      //支持 Notification 属性
    },
    [UART_SVC_IDX_TX_NTF_CFG] = {                   // TX 特征值描述符 CCCD, 当 Characteristic 具有Notify或者Indicate操作属性时，都要为其添加 CCCD attribute
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
    .uuid = ls_uart_svc_uuid_128,                       // 服务 128-bit uuid
    .att = (struct att_decl*)ls_uart_server_att_decl,   // Service Attribute Table
    .nb_att = UART_SVC_ATT_NUM,                         // Attribute NUmber
    .uuid_len = UUID_LEN_128BIT,                        // 128-bit uuid
};
static struct gatt_svc_env ls_uart_server_svc_env;


#define PRIVATE_SERVER_MAX_MTU  247
#define PRIVATE_SVC_MAX_LEN (PRIVATE_SERVER_MAX_MTU - 3)

static const uint8_t ls_private_svc_uuid_128[] =            {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x01,0x00,0x34,0xa0};      // Service 服务128-bit uuid
static const uint8_t ls_private_read_char_uuid_128[] =      {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x02,0x00,0x34,0xa0};      // 支持读属性的特征值 uuid
static const uint8_t ls_private_write_char_uuid_128[] =     {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x03,0x00,0x34,0xa0};      // 支持写属性的特征值 uuid
static const uint8_t ls_private_notify_char_uuid_128[] =    {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x04,0x00,0x34,0xa0};      // 支持 Notify 属性特征值 uuid
static const uint8_t ls_private_indicate_char_uuid_128[] =  {0x9e,0xca,0xdc,0x24,0x0e,0xe5,0xa9,0xe0,0x93,0xf3,0xa3,0xb5,0x05,0x00,0x34,0xa0};      // 支持 Indication 属性特征值 uuid

enum private_svc_att_db_handles
{
    PRIVATE_SVC_IDX_READ_CHAR,              // 特征值申明
    PRIVATE_SVC_IDX_READ_VAL,               // Read 属性特征值
    PRIVATE_SVC_IDX_WRITE_CHAR,             // 特征值申明
    PRIVATE_SVC_IDX_WRITE_VAL,              // Write 属性特征值
    PRIVATE_SVC_IDX_NOTITY_CHAR,            // 特征值申明
    PRIVATE_SVC_IDX_NOTITY_VAL,             // Notify 属性特征值
    PRIVATE_SVC_IDX_NOTITY_NTF_CFG,         // 特征值描述符
    PRIVATE_SVC_IDX_INDICATE_CHAR,          // 特征值申明
    PRIVATE_SVC_IDX_INDICATEVAL,            // Indication 属性特征值
    PRIVATE_SVC_IDX_INDICATE_NTF_CFG,       // 特征值描述符
    PRIVATE_SVC_ATT_NUM                     // 服务属性数量
};

static const struct att_decl ls_private_server_att_decl[PRIVATE_SVC_ATT_NUM] =
{
    [PRIVATE_SVC_IDX_READ_CHAR] = {                     // Characteristic Declaration 
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [PRIVATE_SVC_IDX_READ_VAL] = {                      // Characteristic Value (characteristic support read properties)
        .uuid = ls_private_read_char_uuid_128,          // 128-bit Characteristic UUID
        .s.max_len = PRIVATE_SVC_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,                           // Read enable
    },    
	[PRIVATE_SVC_IDX_WRITE_CHAR] = {                    // Characteristic Declaration 
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [PRIVATE_SVC_IDX_WRITE_VAL] = {                     // Characteristic Value (characteristic support write req/cmd properties)
        .uuid = ls_private_write_char_uuid_128,         // 128-bit Characteristic UUID
        .s.max_len = PRIVATE_SVC_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.wr_cmd = 1,                          // write req&cmd enable
        .char_prop.wr_req = 1,
    },
    [PRIVATE_SVC_IDX_NOTITY_CHAR] = {                   // Characteristic Declaration 
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1, 
    },
    [PRIVATE_SVC_IDX_NOTITY_VAL] = {                    // Characteristic Value (characteristic support Notify properties)
        .uuid = ls_private_notify_char_uuid_128,		
        .s.max_len = PRIVATE_SVC_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.ntf_en = 1,                          // Notify Enable
    },
    [PRIVATE_SVC_IDX_NOTITY_NTF_CFG] = {                // Characteristic Descriptor
        .uuid = att_desc_client_char_cfg_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
    },
    [PRIVATE_SVC_IDX_INDICATE_CHAR] = {                 // Characteristic Declaration
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1, 
    },
    [PRIVATE_SVC_IDX_INDICATEVAL] = {                   // Characteristic Value (characteristic support Notify properties)
        .uuid = ls_private_indicate_char_uuid_128,		
        .s.max_len = PRIVATE_SVC_MAX_LEN,
        .s.uuid_len = UUID_LEN_128BIT,
        .s.read_indication = 1,
        .char_prop.ind_en = 1,                          // Indication Enable
    },
    [PRIVATE_SVC_IDX_INDICATE_NTF_CFG] = {              // Characteristic Descriptor
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
    .uuid = ls_private_svc_uuid_128,                            // Service 服务 uuid
    .att = (struct att_decl*)ls_private_server_att_decl,        // 属性表
    .nb_att = PRIVATE_SVC_ATT_NUM,                              // 属性数量
    .uuid_len = UUID_LEN_128BIT,                                // 服务 uuid 是 128-bit
};
static struct gatt_svc_env ls_private_server_svc_env;

static uint8_t connect_id = 0xff; 
static uint16_t uart_cccd_config = 0;
static uint16_t pri_nft_cccd_config = 0;
static uint16_t pri_ind_cccd_config = 0;

static uint8_t adv_obj_hdl;
static uint8_t advertising_data[28] = {0};
static uint8_t scan_response_data[31];

static struct builtin_timer * ls_multi_server_timer_inst = NULL;
static void ls_multi_server_timer_cb(void *param);
static void ls_multi_server_send_notification(void);
static bool multi_server_ntf_done = true;

static void ls_uart_server_read_req_ind(uint8_t att_idx, uint8_t con_idx);
static void start_adv(void);
static void ls_uart_server_data_length_update(uint8_t con_idx);

static void ls_multi_server_init(void)
{
    ls_multi_server_timer_inst = builtin_timer_create(ls_multi_server_timer_cb);        // 创建 builtin timer，并注册回调处理函数
    builtin_timer_start(ls_multi_server_timer_inst, MULTI_SERVER_TIMEOUT, NULL);        // 开启软件定时器，定时周期为 MULTI_SERVER_TIMEOUT 300ms
}

static void ls_multi_server_timer_cb(void *param)       // builtin timer 定时回调处理函数
{
    if(connect_id != 0xff)      // 判断当前是连接状态
    {
        bas_batt_lvl_update(0,100);     // 上报当前电池电量状态，默认100%电池电量。
        uint32_t cpu_stat = enter_critical();
        ls_multi_server_send_notification();        // Notify 上报数据
        exit_critical(cpu_stat);
    }

    if(ls_multi_server_timer_inst)
    {
        builtin_timer_start(ls_multi_server_timer_inst, MULTI_SERVER_TIMEOUT, NULL);        // 重新开启定时器
    }
}

static void ls_multi_server_send_notification(void)
{
    uint8_t ntf_test_data[2] = {0xa5, 0x5a};        // 默认测试上报数据

    if(pri_nft_cccd_config > 0 && multi_server_ntf_done)     // 使能了 CCCD 并且前一个Nofiticate数据包已经交给协议栈处理
    {
        multi_server_ntf_done = false;
        uint16_t handle = gatt_manager_get_svc_att_handle(&ls_private_server_svc_env, PRIVATE_SVC_IDX_NOTITY_VAL);      // 通过private server服务支持Notify的特征值 PRIVATE_SVC_IDX_NOTITY_VAL 上报测试数据
        gatt_manager_server_send_notification(connect_id, handle, ntf_test_data, sizeof(ntf_test_data), NULL);
    }    
}

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


/*
    OTA Profile 回调函数，处理OTA 的开始、结束和进行中的事件
*/
static void prf_fota_server_callback(enum fotas_evt_type type,union fotas_evt_u *evt)
{
    static uint32_t new_image_size_bytes = 0;
    static uint16_t segment_data_max_length = 0;
    switch(type)
    {
    case FOTAS_START_REQ_EVT:                           // OTA 升级开始
    {
        enum fota_start_cfm_status status;
        if(fw_signature_check(evt->fotas_start_req.digest, evt->fotas_start_req.signature))     // 固件签名检查，如果没有使能固件签名，会继续走后面的升级流程
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
    case FOTAS_PROGRESS_EVT:                           // OTA 升级进行中，打印当前的升级进度
    {
        uint32_t bytes_transfered = evt->fotas_progress.current_sector * 4096 + evt->fotas_progress.current_segment * segment_data_max_length;
        uint8_t percentage =  bytes_transfered*100/new_image_size_bytes >= 100 ? 100 : bytes_transfered*100/new_image_size_bytes;
        LOG_I("ota progress ---------> %d%%", percentage);
    }
    break;
    case FOTAS_FINISH_EVT:                             // OTA 升级结束
        if(evt->fotas_finish.status & FOTA_STATUS_MASK && evt->fotas_finish.status & FOTA_REBOOT_MASK)
        {
            if(evt->fotas_finish.boot_addr)
            {
                ota_boot_addr_set(evt->fotas_finish.boot_addr);             // 将APP传下来的boot addr记录到Flash OTA Setting 特定区域 
            }
            if(evt->fotas_finish.status & FOTA_SETTINGS_ERASE_MASK)
            {
                ota_settings_erase_req_set();                              // OTA APP有配置Erase,配置相关关键字
            }
            if(evt->fotas_finish.copy.fw_copy_size)
            {
                ota_copy_info_set(&evt->fotas_finish.copy);                 // 配置搬移固件的起始地址、目的地址和固件大小
            }
            platform_reset(RESET_OTA_SUCCEED);                              // 软件复位
        }
    break;
    default:
        LS_ASSERT(0);
    break;
    }
}

/*
*   uart server服务的GATT Read事件处理函数
*/
static void ls_uart_server_read_req_ind(uint8_t att_idx, uint8_t con_idx)
{
    uint16_t handle = 0;
    if(att_idx == UART_SVC_IDX_TX_NTF_CFG)                 // APP 读取uart server服务的CCCD 状态
    {
        handle = gatt_manager_get_svc_att_handle(&ls_uart_server_svc_env, att_idx);
        // 返回当前cccd的状态。参数：connect_id , CCCD attribute 对应的handle值, 默认的status 0, cccd 的状态值，cccd 状态值的数据长度。
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void*)&uart_cccd_config, 2);
    }
}

/*
*   private server服务的GATT Read事件处理函数
*/
static void ls_private_server_read_req_ind(uint8_t att_idx, uint8_t con_idx)
{
    uint16_t handle = 0;
    if(att_idx == PRIVATE_SVC_IDX_READ_VAL)					                                        // 读取具有读属性的特征值
    {
		uint8_t data[10] = {0,1,2,3,4,5,6,7,8,9};                                                   // 返回默认值
        handle = gatt_manager_get_svc_att_handle(&ls_private_server_svc_env, att_idx);              // 获取该特征值对应的 handle 值
        gatt_manager_server_read_req_reply(con_idx, handle, 0, data, sizeof(data));                 // 返回测试数据
    }
    else if(att_idx == PRIVATE_SVC_IDX_NOTITY_NTF_CFG)                                              // 读取其中一个Notify属性特征值 CCCD 的状态
    {
        handle = gatt_manager_get_svc_att_handle(&ls_private_server_svc_env, att_idx);              // 获取该 CCCD 的handle
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void*)&pri_nft_cccd_config, 2);     // 返回该 CCCD 的状态值
    }
    else if(att_idx == PRIVATE_SVC_IDX_INDICATE_NTF_CFG)                                            // 读取其中一个Indicate属性特征值 CCCD 的状态
    {
        handle = gatt_manager_get_svc_att_handle(&ls_private_server_svc_env, att_idx);              // 获取该 CCCD 的handle
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void*)&pri_ind_cccd_config, 2);     // 返回该 CCCD 的状态值
    }
}

/*
*   DLE 更新
*/
static void ls_uart_server_data_length_update(uint8_t con_idx)
{
    struct gap_set_pkt_size dlu_param = 
    {
        .pkt_size = 251,
    };
    gap_manager_set_pkt_size(con_idx, &dlu_param);
}

/*
*   GAP 事件处理函数； 处理连接、断连、配对绑定和连接参数更新等事件；
*   参数说明：
*            enum gap_evt_type type: 当前的 GAP 事件类型；包括 CONNECTED、DISCONNECTED、MATER_PAIR_REQ等。
*            union gap_evt_u *evt: 该GAP事件对应的参数。例如DISCONNECTED事件，断连事件可以通过 evt->disconnected.reason 打印出断连的原因。
*            uint8_t con_idx: GAP事件对应的 connect id。多连接情况下，可以通过这个 id 来区分现在是和哪个Client 主机通信。
*/
static void gap_manager_callback(enum gap_evt_type type,union gap_evt_u *evt,uint8_t con_idx)
{
    switch(type)
    {
        case CONNECTED:             // CONNECTED 连接建立事件
            connect_id = con_idx;   // 记录当前连接的 CONNECT_ID
            ls_multi_server_init();     // 连接建立以后创建一个 300ms 的builtin timer，上报电池电量，并且如果使能了Private server的Notify CCCD，就Notify上报测试数据
            LOG_I("connected!");
        break;
        case DISCONNECTED:
            connect_id = 0xff; 
            builtin_timer_stop(ls_multi_server_timer_inst);     // 断连停止 300ms 的builtin timer
            LOG_I("disconnected! reason = %x ",evt->disconnected.reason);       // DISCONNECT 断连事件，打印断连原因
            start_adv();
        break;
        case CONN_PARAM_REQ:

        break;
        case CONN_PARAM_UPDATED:        // 连接参数已经更新事件，打印当前的连接参数
            LOG_I("conn param updata  interval = %d  latency = %d  sup_to = %d",evt->conn_param_updated.con_interval,evt->conn_param_updated.con_latency,evt->conn_param_updated.sup_to);
        break;
        default:

        break;
    }
}

/*
*   GATT 事件处理函数。
*   参数说明：
*            enum gatt_evt_type type: 当前的 GATT 事件类型；包括 GATT Read、Write、Notification done、MTU Exchange等。
*            union gatt_evt_u *evt: 该事件对应的参数。例如SERVER_WRITE_REQ事件，APP下发的数据就在 evt->server_write_req.value 中，也包括这次write事件对应的服务信息等。
*            uint8_t con_idx: GATT事件对应的 connect id。多连接情况下，可以通过这个 id 来区分现在是和哪个Client 主机通信。
*/
static void gatt_manager_callback(enum gatt_evt_type type,union gatt_evt_u *evt,uint8_t con_idx)
{
    if (connect_id != 0xff)
    {
        switch (type)
        {
            case SERVER_READ_REQ:       // Read:APP读取Server端的数据
                LOG_I("read req");
                if(ls_uart_server_svc_env.start_hdl == evt->server_read_req.svc->start_hdl)     // 根据服务的 start_handle 来区分当前读的是哪个服务。
                {
                    ls_uart_server_read_req_ind(evt->server_read_req.att_idx, con_idx);
                }
                else if(ls_private_server_svc_env.start_hdl == evt->server_read_req.svc->start_hdl)
                {
                    ls_private_server_read_req_ind(evt->server_read_req.att_idx, con_idx);
                }
            break;
            case SERVER_WRITE_REQ:      // Write:APP写数据到Server端
            {
                LOG_I("write req");
                if(ls_uart_server_svc_env.start_hdl == evt->server_write_req.svc->start_hdl)                // 根据服务的 start_handle 来区分当前写的是哪个服务。
                {
                    LOG_I("att_idx=%d,uart server write data = 0x", evt->server_write_req.att_idx);         // 根据evt->server_write_req.att_idx 判断写的是该服务下的哪个特征值。
                    LOG_HEX(evt->server_write_req.value,evt->server_write_req.length);                      // LOG 十六进制打印出写入的值。
                }
                else if(ls_private_server_svc_env.start_hdl == evt->server_write_req.svc->start_hdl)
                {
                    LOG_I("att_idx=%d,private server write data = 0x", evt->server_write_req.att_idx);      // 十六进制打印收到的数据
                    LOG_HEX(evt->server_write_req.value,evt->server_write_req.length);
                    if(evt->server_write_req.att_idx == PRIVATE_SVC_IDX_NOTITY_NTF_CFG)                     // 区分是否是使能 CCCD
                    {
                        memcpy(&pri_nft_cccd_config, evt->server_write_req.value, evt->server_write_req.length);
                    }
                    else if(evt->server_write_req.att_idx == PRIVATE_SVC_IDX_INDICATE_NTF_CFG)              // 区分是否是使能 CCCD
                    {
                        memcpy(&pri_ind_cccd_config, evt->server_write_req.value, evt->server_write_req.length);
                    }
                }
            }
            break;
            case SERVER_NOTIFICATION_DONE:      // NOTIFICATION_DONE,该事件意味当前的Notificate数据包已经交给协议栈处理，可以继续发下一包Notificate数据
                multi_server_ntf_done = true;
                LOG_I("ntf done");
            break;
            case MTU_CHANGED_INDICATION:        // MTU Exchange 已经完成指示事件
                LOG_I("mtu: %d", evt->mtu_changed_ind.mtu);     // 打印当前的 MTU
                ls_uart_server_data_length_update(con_idx);     // 发起 DLE 更新
            break;
            default:
                LOG_I("Event not handled! type = %d", type);
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
        .adv_intv_min = 0x20,                               // 广播间隔，单位是 0.625ms , 当 adv_intv_min 和 adv_intv_max 相等时，就为固定的广播间隔。 当前配置为 20ms 广播间隔。
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

    /*
     ADV_DATA_PACK 是一个变长参数的接口，负责构造广播和扫描回应数据。广播数据的结构AD_STRUCT是固定的:Length + Type + Data
       参数说明: (数据指针,AD_STRUCT的个数, Type, Data, Length,... )
       返回值: 构造完之后的广播或者扫描回应数据的总长度
	*/
    uint8_t adv_data_length = ADV_DATA_PACK(advertising_data, 2, GAP_ADV_TYPE_SHORTENED_NAME, UART_SVC_ADV_NAME, strlen(UART_SVC_ADV_NAME),     // 通过ADV_DATA_PACK构造广播数据。当前数据有2个域，包含GAP_ADV_TYPE_SHORTENED_NAME和GAP_ADV_TYPE_APPEARANCE
                                                                 GAP_ADV_TYPE_APPEARANCE, app_data, sizeof(app_data));
	
    uint8_t scan_data_length = ADV_DATA_PACK(scan_response_data, 1, GAP_ADV_TYPE_MANU_SPECIFIC_DATA, user_data, sizeof(user_data));             // 构造扫描回应数据。当前数据只有一个厂商数据域 GAP_ADV_TYPE_MANU_SPECIFIC_DATA
		
    dev_manager_start_adv(adv_obj_hdl, advertising_data, adv_data_length, scan_response_data, scan_data_length);                                // 开始广播
    LOG_I("adv start");
}

static void prf_batt_server_callback(enum bass_evt_type type, union bass_evt_u *evt)        // BASS Profile 回调函数
{

}

static void prf_added_handler(struct profile_added_evt *evt)
{
    LOG_I("profile:%d, start handle:0x%x\n",evt->id,evt->start_hdl);
    switch(evt->id)         // 根据 PROFILED_ADDED 事件传入的 id, 区分现在添加的是哪个Profile
    {
		case PRF_FOTA_SERVER:
		{
			prf_fota_server_callback_init(prf_fota_server_callback);             // 服务添加步骤6：注册fota的回调函数，fota profile 相关的事件在该回调函数中处理
			
			struct bas_db_cfg db_cfg = {
				.ins_num = 1,
				.ntf_enable[0] = 1,
			};
			dev_manager_prf_bass_server_add(NO_SEC,&db_cfg,sizeof(db_cfg));     // 服务添加步骤7：添加电池电量 BASS Profile
		}
		break;
			
		case PRF_BASS:
			prf_bass_server_callback_init(prf_batt_server_callback);            // 服务添加步骤8：注册BASS Profile 的回调函数
			create_adv_obj();                                                   // 服务添加完毕，创建广播对象。 创建完毕产生 ADV_OBJ_CREATED 事件；
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
            dev_manager_get_identity_bdaddr(addr,&type);        // 获取并打印当前设备的 MAC 地址
            LOG_I("type:%d,addr:",type);
            LOG_HEX(addr,sizeof(addr));
            
            dev_manager_add_service((struct svc_decl *)&ls_uart_server_svc);             // 服务添加步骤1：添加第一个 uart server 服务
        }
        break;
        case SERVICE_ADDED:
        {
            static uint8_t server_num = 0;
            if(0 == server_num)
            {
                server_num = 1;
                gatt_manager_svc_register(evt->service_added.start_hdl, UART_SVC_ATT_NUM, &ls_uart_server_svc_env);     // 服务添加步骤2：uart server服务信息注册，将服务的start handle 和 attribute number 存储在本地全局变量ls_uart_server_svc_env
                dev_manager_add_service((struct svc_decl *)&ls_private_server_svc);                                     // 服务添加步骤3：添加第二个服务 private server
            }
            else if(server_num == 1)
            {
                server_num = 2;
                gatt_manager_svc_register(evt->service_added.start_hdl, PRIVATE_SVC_ATT_NUM, &ls_private_server_svc_env);       // 服务添加步骤4：private server 服务信息注册
                dev_manager_prf_fota_server_add(NO_SEC);                                                                        // 服务添加步骤5：添加 fota profile
            }
        }
        break;
        case PROFILE_ADDED:
            prf_added_handler(&evt->profile_added);     // Profile Added 事件处理函数
        break;
        case ADV_OBJ_CREATED:                           // 广播对象创建完毕
            LS_ASSERT(evt->obj_created.status == 0);
            adv_obj_hdl = evt->obj_created.handle;
            start_adv();                                // 开始广播。 广播和扫描回应数据在这个接口中配置。
        break;
        case ADV_STARTED:                               // 开始广播事件
            LOG_I("adv started");
        break;
        case ADV_STOPPED:                               // 广播停止事件
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
