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
#include "SEGGER_RTT.h"
#include "ls_sys.h"
#include "lstk.h"
#define UART_SERVER_WITH_OTA 0

#if UART_SERVER_WITH_OTA == 1
#define UART_SVC_ADV_NAME "LS Uart Server ota prf"
#else
#define UART_SVC_ADV_NAME "LS Uart Server"
#endif
#define UART_SERVER_MAX_MTU 247
#define UART_SERVER_MTU_DFT 23
#define UART_SERVER_MAX_DATA_LEN (uart_server_mtu - 3)
#define UART_SVC_RX_MAX_LEN (UART_SERVER_MAX_MTU - 3)
#define UART_SVC_TX_MAX_LEN (UART_SERVER_MAX_MTU - 3)
#define UART_SVC_BUFFER_SIZE (1024)

#define UART_SERVER_TIMEOUT 50 // timer units: ms
static const uint8_t ls_uart_svc_uuid_128[] = {0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x01, 0x00, 0x40, 0x6e};
static const uint8_t ls_uart_rx_char_uuid_128[] = {0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x02, 0x00, 0x40, 0x6e};
static const uint8_t ls_uart_tx_char_uuid_128[] = {0x9e, 0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x03, 0x00, 0x40, 0x6e};
static const uint8_t att_decl_char_array[] = {0x03, 0x28};
static const uint8_t att_desc_client_char_cfg_array[] = {0x02, 0x29};
static uint8_t BUf0_ctl_io[] = {PB12, PC01, PC00, PA06, PA07, PA09, PA08, PA15};
static uint8_t BUf1_ctl_io[] = {PB02, PB04, PB10, PB11, PB13, PA04};
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
        .att = (struct att_decl *)ls_uart_server_att_decl,
        .nb_att = UART_SVC_ATT_NUM,
        .uuid_len = UUID_LEN_128BIT,
};
static struct gatt_svc_env ls_uart_server_svc_env;
static uint8_t connect_id = 0xff;
static uint8_t uart_server_rx_byte;
static uint8_t uart_server_buf[UART_SVC_BUFFER_SIZE];
static uint8_t uart_server_tx_buf[UART_SVC_BUFFER_SIZE];
static uint16_t uart_server_rx_index = 0;
static UART_HandleTypeDef UART_Server_Config;
static bool uart_server_tx_busy;
static bool uart_server_ntf_done = true;
static uint16_t uart_server_mtu = UART_SERVER_MTU_DFT;
static struct builtin_timer *uart_server_timer_inst = NULL;
static bool update_adv_intv_flag = false;
static uint16_t cccd_config = 0;

static uint8_t adv_obj_hdl;
static uint8_t advertising_data[28] = {0x05, 0x09, 'u', 'a', 'r', 't'};
static uint8_t scan_response_data[31];

static TK_HandleTypeDef tkHandle;
static volatile uint8_t RxBUFF[3] = {0};
static volatile uint8_t IRQ = 0;

static void ls_uart_server_init(void);
static void ls_uart_server_timer_cb(void *param);
static void ls_uart_init(void);
static void ls_uart_server_read_req_ind(uint8_t att_idx, uint8_t con_idx);
static void ls_uart_server_write_req_ind(uint8_t att_idx, uint8_t con_idx, uint16_t length, uint8_t const *value);
static void ls_uart_server_send_notification(void);
static void start_adv(void);
static void ls_uart_server_data_length_update(uint8_t con_idx);

static bool lsTK_Init(void);
static void Error_TKHandle(void);
static void Touch_LED(void);
static void Init_GPIO(void);

#if UART_SERVER_WITH_OTA == 1
#if FW_ECC_VERIFY
extern const uint8_t fotas_pub_key[64];
bool fw_signature_check(struct fw_digest *digest, struct fota_signature *signature)
{
    return uECC_verify(fotas_pub_key, digest->data, sizeof(digest->data), signature->data, uECC_secp256r1());
}
#else
bool fw_signature_check(struct fw_digest *digest, struct fota_signature *signature)
{
    return true;
}
#endif

static void prf_fota_server_callback(enum fotas_evt_type type, union fotas_evt_u *evt, uint8_t con_idx)
{
    switch (type)
    {
    case FOTAS_START_REQ_EVT:
    {
        // ota_settings_write(SINGLE_FOREGROUND);
        ota_settings_write(DOUBLE_FOREGROUND);
        enum fota_start_cfm_status status;
        if (fw_signature_check(evt->fotas_start_req.digest, evt->fotas_start_req.signature))
        {
            status = FOTA_REQ_ACCEPTED;
        }
        else
        {
            status = FOTA_REQ_REJECTED;
        }
        prf_fotas_start_confirm(status);
    }
    break;
    case FOTAS_FINISH_EVT:
        if (evt->fotas_finish.integrity_checking_result)
        {
            if (evt->fotas_finish.new_image->base != get_app_image_base())
            {
                ota_copy_info_set(evt->fotas_finish.new_image);
            }
            else
            {
                ota_settings_erase();
            }
            platform_reset(RESET_OTA_SUCCEED);
        }
        else
        {
            platform_reset(RESET_OTA_FAILED);
        }
        break;
    default:
        LS_ASSERT(0);
        break;
    }
}
#endif
static void ls_uart_server_init(void)
{
    uart_server_timer_inst = builtin_timer_create(ls_uart_server_timer_cb);
    builtin_timer_start(uart_server_timer_inst, UART_SERVER_TIMEOUT, NULL);
}

static void ls_uart_server_update_adv_interval(uint8_t input_intv)
{
    LOG_I("input_char: %d", input_intv);
    uint32_t new_intv = (input_intv - '0') * 160;
    dev_manager_update_adv_interval(adv_obj_hdl, new_intv, new_intv);
    dev_manager_stop_adv(adv_obj_hdl);
    update_adv_intv_flag = true;
}

static void ls_uart_server_timer_cb(void *param)
{
    if (connect_id != 0xff)
    {
        uint32_t cpu_stat = enter_critical();
        // LOG_I("uart timer out, length=%d", uart_server_rx_index);
        ls_uart_server_send_notification();
        exit_critical(cpu_stat);
    }
    uint8_t input_char = (uint8_t)SEGGER_RTT_GetKey();
    if (connect_id == 0xff && input_char != 0xff && input_char > '0' && input_char <= '9')
    {
        ls_uart_server_update_adv_interval(input_char);
    }
    if (uart_server_timer_inst)
    {
        builtin_timer_start(uart_server_timer_inst, UART_SERVER_TIMEOUT, NULL);
    }
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_server_tx_busy = false;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (uart_server_rx_index < UART_SVC_BUFFER_SIZE)
    {
        uart_server_buf[uart_server_rx_index++] = uart_server_rx_byte;
    }
    else
    {
        LOG_I("uart server rx buffer overflow!");
    }
    HAL_UART_Receive_IT(&UART_Server_Config, &uart_server_rx_byte, 1);
}
static void ls_uart_init(void)
{
    pinmux_uart1_init(PB00, PB01);
    io_pull_write(PB01, IO_PULL_UP);
    UART_Server_Config.UARTX = UART1;
    UART_Server_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Server_Config.Init.MSBEN = 0;
    UART_Server_Config.Init.Parity = UART_NOPARITY;
    UART_Server_Config.Init.StopBits = UART_STOPBITS1;
    UART_Server_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Server_Config);
}
static void ls_uart_server_read_req_ind(uint8_t att_idx, uint8_t con_idx)
{
    uint16_t handle = 0;
    if (att_idx == UART_SVC_IDX_TX_NTF_CFG)
    {
        handle = gatt_manager_get_svc_att_handle(&ls_uart_server_svc_env, att_idx);
        gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&cccd_config, 2);
    }
}
static void ls_uart_server_write_req_ind(uint8_t att_idx, uint8_t con_idx, uint16_t length, uint8_t const *value)
{
    if (att_idx == UART_SVC_IDX_RX_VAL)
    {
        if (uart_server_tx_busy)
        {
            LOG_I("Uart tx busy, data discard!");
        }
        else
        {
            uart_server_tx_busy = true;
            LS_ASSERT(length <= UART_SVC_BUFFER_SIZE);
            memcpy(uart_server_tx_buf, (uint8_t *)value, length);
            HAL_UART_Transmit_IT(&UART_Server_Config, (uint8_t *)uart_server_tx_buf, length);
        }
    }
    else if (att_idx == UART_SVC_IDX_TX_NTF_CFG)
    {
        LS_ASSERT(length == 2);
        memcpy(&cccd_config, value, length);
    }
}
static void ls_uart_server_send_notification(void)
{
    if (uart_server_rx_index > 0 && uart_server_ntf_done)
    {
        uart_server_ntf_done = false;
        uint16_t handle = gatt_manager_get_svc_att_handle(&ls_uart_server_svc_env, UART_SVC_IDX_TX_VAL);
        uint16_t tx_len = uart_server_rx_index > co_min(UART_SERVER_MAX_DATA_LEN, UART_SVC_TX_MAX_LEN) ? co_min(UART_SERVER_MAX_DATA_LEN, UART_SVC_TX_MAX_LEN) : uart_server_rx_index;
        uart_server_rx_index -= tx_len;
        gatt_manager_server_send_notification(connect_id, handle, uart_server_buf, tx_len, NULL);
        memcpy((void *)&uart_server_buf[0], (void *)&uart_server_buf[tx_len], uart_server_rx_index);
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

static void gap_manager_callback(enum gap_evt_type type, union gap_evt_u *evt, uint8_t con_idx)
{
    switch (type)
    {
    case CONNECTED:
        connect_id = con_idx;
        LOG_I("connected!");
        break;
    case DISCONNECTED:
        connect_id = 0xff;
        uart_server_mtu = UART_SERVER_MTU_DFT;
        LOG_I("disconnected!");
        start_adv();
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

static void gatt_manager_callback(enum gatt_evt_type type, union gatt_evt_u *evt, uint8_t con_idx)
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
        uart_server_mtu = evt->mtu_changed_ind.mtu;
        LOG_I("mtu: %d", uart_server_mtu);
        ls_uart_server_data_length_update(con_idx);
        break;
    default:
        LOG_I("Event not handled!");
        break;
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
    uint8_t adv_data_length = ADV_DATA_PACK(advertising_data, 1, GAP_ADV_TYPE_SHORTENED_NAME, UART_SVC_ADV_NAME, sizeof(UART_SVC_ADV_NAME));
    dev_manager_start_adv(adv_obj_hdl, advertising_data, adv_data_length, scan_response_data, 0);
    LOG_I("adv start");
}
/*
static void create_highduty_adv_obj(void)
{
    struct legacy_adv_obj_param adv_param = {
        .peer_addr = (struct dev_addr*)peer_addr_1,
        .peer_addr_type = RANDOM_ADDR,
        .adv_intv_min = 0x20,
        .adv_intv_max = 0x20,
        .own_addr_type = PUBLIC_OR_RANDOM_STATIC_ADDR,
        .filter_policy = 0,
        .ch_map = 0x7,
        .disc_mode = ADV_MODE_NON_DISC,
        .prop = {
            .connectable = 1,
            .scannable = 0,
            .directed = 1,
            .high_duty_cycle = 1,
        },
    };
    dev_manager_create_legacy_adv_object(&adv_param);
}*/
#if UART_SERVER_WITH_OTA == 1
static void prf_added_handler(struct profile_added_evt *evt)
{
    LOG_I("profile:%d, start handle:0x%x\n", evt->id, evt->start_hdl);
    switch (evt->id)
    {
    case PRF_FOTA_SERVER:
        prf_fota_server_callback_init(prf_fota_server_callback);
        create_adv_obj();
        break;
    default:

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
        dev_manager_get_identity_bdaddr(addr, &type);
        LOG_I("type:%d,addr:", type);
        LOG_HEX(addr, sizeof(addr));
        dev_manager_add_service((struct svc_decl *)&ls_uart_server_svc);
        ls_uart_init();
        HAL_UART_Receive_IT(&UART_Server_Config, &uart_server_rx_byte, 1);
        ls_uart_server_init();
    }
    break;
    case SERVICE_ADDED:
        gatt_manager_svc_register(evt->service_added.start_hdl, UART_SVC_ATT_NUM, &ls_uart_server_svc_env);
#if UART_SERVER_WITH_OTA == 1
        dev_manager_prf_fota_server_add(NO_SEC);
#else
        create_adv_obj();
#endif
        break;
#if UART_SERVER_WITH_OTA == 1
    case PROFILE_ADDED:
        prf_added_handler(&evt->profile_added);
        break;
#endif
    case ADV_OBJ_CREATED:
        LS_ASSERT(evt->obj_created.status == 0);
        adv_obj_hdl = evt->obj_created.handle;
        start_adv();
        break;
    case ADV_STOPPED:
        if (update_adv_intv_flag)
        {
            update_adv_intv_flag = false;
            start_adv();
        }
        break;
    case SCAN_STOPPED:

        break;
    default:

        break;
    }
}
/**
 * @brief init TK
 * 
 * @return true 
 * @return false 
 */
static bool lsTK_Init(void)
{
    /* touch initialize start */
    tkHandle.Init.NPRR = 0;                         // Set the noise ratio to 4 times
    tkHandle.Init.DNPR = TK_DNPR_DISABLE;           // Disable noise protection
    tkHandle.Init.MultiOn = TK_MULTION_DISABLE;     // Disable multichannel detection
    tkHandle.Init.Debounce = 3;                     // Set the anti-jitter value to 3
    tkHandle.Init.ChannelEN = 0x3FFF;               // Open all channels
    tkHandle.Init.GbSen = 0xA0;                     // Set global sensitivity to 0xda
    tkHandle.Init.LP = TK_LP_DISABLE;               // Disable automatic low-power scan mode
    tkHandle.Init.IComGS = 0x28;                    // Set group scan compensation current to 0x28
    tkHandle.Init.CdcFswDiv = 0x07;                 // Set the CDC module scanning frequency to 0x07
    tkHandle.Init.LowPowerScanPeriod = TK_LPSP_500; // set the low-power scan period to 500ms
    tkHandle.Init.KeyDebounceCount = 1;             // Set the number of jitters to 1
    tkHandle.Init.LpDelay = 4;                      // Set the time for automatic low-power scanning to 4*1S
    tkHandle.Init.ScanPeriod = 1;                   // Set the scan period
    tkHandle.Init.GsMask = 0x0;                     // Disable low-power scanning for all channels
    tkHandle.Init.LSenseGS = 0x68;                  // Set group scan sensitivity to 0x68

    if (HAL_TK_Init(&tkHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_TKHandle();
    }
    /* ENABLE  interrupt*/

    return 0;
    /* touch initialize end */
}

/**
 * @brief init gpio
 * 
 */
static void Init_GPIO(void)
{
    /*WKUP key io initial*/
    io_cfg_input(PB15);
    io_pull_write(PB15, IO_PULL_UP);
    io_exti_config(PB15, INT_EDGE_FALLING);
    /*LED io initial*/
    for (uint8_t i = 0; i < 8; i++)
    {
        if (i < sizeof(BUf1_ctl_io))
        {
            io_set_pin(BUf1_ctl_io[i]);
            io_cfg_output(BUf1_ctl_io[i]);
        }
        io_set_pin(BUf0_ctl_io[i]);
        io_cfg_output(BUf0_ctl_io[i]);
    }
}

/**
 * @brief Read the channel state and turn on the corresponding LED light
 * 
 */
static void Touch_LED(void)
{
    HAL_TK_Get_Reg(CNTLR, (uint8_t *)RxBUFF, 2); //Reads the key channel number that is touched
    RxBUFF[1] = RxBUFF[1] & 0X3F;
    // /*Send the key channel number to the phone*/
    // uint16_t handle = gatt_manager_get_svc_att_handle(&ls_uart_server_svc_env, UART_SVC_IDX_TX_VAL);
    // gatt_manager_server_send_notification(connect_id, handle, RxBUFF, 2, NULL);
    LOG_I("TK_CNTLR:%x  TK_CNTHR:%x", RxBUFF[0], RxBUFF[1] & 0x3f); //Print channel number
    for (uint8_t i = 0; i < 8; i++)
    {
        if (i < sizeof(BUf1_ctl_io))
        {
            if ((RxBUFF[1] >> i) & 0x01)
            {
                io_clr_pin(BUf1_ctl_io[i]);
            }
            else
            {
                io_set_pin(BUf1_ctl_io[i]);
            }
        }

        if ((RxBUFF[0] >> i) & 0x01)
        {
            io_clr_pin(BUf0_ctl_io[i]);
        }
        else
        {
            io_set_pin(BUf0_ctl_io[i]);
        }
    }
}
/**
 * @brief Read the channel number and channel signal value to be touched, and light up the LED
 * 
 * @param null
 */
static void Touch_Updata(void *param)
{
    Touch_LED();
    HAL_TK_Get_Reg(SIGLR0, (uint8_t *)RxBUFF, 1);
    HAL_TK_Get_Reg((SIGLR0 + 1), (uint8_t *)(RxBUFF + 1), 1);
    LOG_I("SIGLR0:%#X  SIGHR0:%#X", RxBUFF[0], RxBUFF[1]);
    HAL_TK_ScanEnable(&tkHandle);
}
/**
 * @brief 
 * 
 * @return int 
 */
int main()
{
    sys_init_app();
    ble_init();
    Init_GPIO();
    lsTK_Init();
    HAL_TK_Enable_IT(&tkHandle);
    dev_manager_init(dev_manager_callback);
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
}
/**
 * @brief Run  error to enter this function
 */
static void Error_TKHandle(void)
{
    while (1)
    {
        ;
    }
}

/**
 * @brief  Key interrupt callback
 */
void io_exti_callback(uint8_t pin,exti_edge_t edge)
{
    switch (pin)
    {
    case PA00:
        func_post(Touch_Updata, NULL);
        break;
    default:
        break;
    }
}
