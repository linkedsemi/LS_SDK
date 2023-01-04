#include "at_recv_cmd.h"
#include "at_cmd_parse.h"
#include "ls_hal_rtc.h"
#include "sleep.h"
#include "ls_soc_gpio.h"

#define WAKEUP_MS 5000

static void at_gap_name_handler(uint8_t *p_cmd_parse);
static void at_bd_addr_handler(uint8_t *p_cmd_parse);
static void at_adv_param_set_handler(uint8_t *p_cmd_parse);
static void at_adv_handler(uint8_t *p_cmd_parse);
static void at_scan_handler(uint8_t *p_cmd_parse);
static void at_app_reset_handler(uint8_t *p_cmd_parse);
static void at_connect_handler(uint8_t *p_cmd_parse);
static void at_link_get_handler(uint8_t *p_cmd_parse);
static void at_sleep_handler(uint8_t *p_cmd_parse);
static void at_disconnect_handler(uint8_t *p_cmd_parse);
static void at_flash_save_handler(uint8_t *p_cmd_parse);
static void at_multi_connect_trans_handler(uint8_t *p_cmd_parse);
static void at_sigle_connect_trans_handler(uint8_t *p_cmd_parse);
static void at_auto_trans_auto_handler(uint8_t *p_cmd_parse);
static void at_tx_power_handler(uint8_t *p_cmd_parse);

typedef void (*at_cmd_handler_t)(uint8_t *p_cmd_parse);
typedef struct
{
    char              *cmd_tag_str; 
    uint8_t            cmd_tag_length;
    at_cmd_handler_t   cmd_handler;
} at_cmd_attr_t;

static const at_cmd_attr_t at_cmd_attr_table[] =
{
    {"NAME",     4, at_gap_name_handler},
    {"MAC",      3, at_bd_addr_handler},
    {"ADVINT",   6, at_adv_param_set_handler},
    {"ADV",      3, at_adv_handler},
    {"SCAN",     4, at_scan_handler},
    {"RESET",    5, at_app_reset_handler},
    {"CONN",     4, at_connect_handler},
    {"LINK",     4, at_link_get_handler},
    {"SLEEP",    5, at_sleep_handler},
    {"DISCONN",  7, at_disconnect_handler},
    {"FLASH",    5, at_flash_save_handler},
    {"SEND",     4, at_multi_connect_trans_handler},
    {"+++",      3, at_sigle_connect_trans_handler},
    {"AUTO+++",  7, at_auto_trans_auto_handler},
    {"POWER",    5, at_tx_power_handler},
};

const uint16_t adv_int_arr[6] = {80, 160, 320, 800, 1600, 3200};

uint8_t *find_int_from_str(uint8_t *buff)
{
    uint8_t *pos = buff;
    while (1)
    {
        if (*pos == ',' || *pos == '\r'){
            *pos = 0;
            break;
        }
        pos++;
    }
    return pos;
}

void str_to_hex_arr(uint8_t* hex_arr, uint8_t *str, uint8_t arr_len)
{
    for (uint8_t i = 0; i < arr_len; i++)
    {
        if ((str[i * 2] <= '9') && (str[i * 2] >= '0'))
            hex_arr[i] = (str[i * 2] - '0') * 16;
        else if ((str[i * 2] <= 'f') && (str[i * 2] >= 'a'))
            hex_arr[i] = (str[i * 2] - 'a' + 10) * 16;
        else if ((str[i * 2] <= 'F') && (str[i * 2] >= 'A'))
            hex_arr[i] = (str[i * 2] - 'A' + 10) * 16;

        if ((str[i * 2 + 1] <= '9') && (str[i * 2 + 1] >= '0'))
            hex_arr[i] += (str[i * 2 + 1] - '0');
        else if ((str[i * 2 + 1] <= 'f') && (str[i * 2 + 1] >= 'a'))
            hex_arr[i] += (str[i * 2 + 1] - 'a' + 10);
        else if ((str[i * 2 + 1] <= 'F') && (str[i * 2 + 1] >= 'A'))
            hex_arr[i] += (str[i * 2 + 1] - 'A' + 10);
    }
}

void hex_arr_to_str(uint8_t *str, const uint8_t hex_arr[], uint8_t arr_len)
{
    for (uint8_t i = 0; i < arr_len; i++)
    {
        sprintf((char *)(str + i * 2), "%02X", hex_arr[i]);
    }
}

void trans_mode_enter(void)
{
    if(ls_at_buff_env.default_info.auto_trans == true)
    {
        at_clr_uart_buff();
        ls_at_ctl_env.transparent_start = 1;
    }
}

void gap_adv_report_ind(struct adv_report_evt *param)
{
    uint8_t free_rpt_idx = 0xff;
    for(uint8_t idx = 0; idx<ADV_REPORT_NUM; idx++)
    {
        if(ls_at_buff_env.adv_rpt[idx].adv_addr_type==0xFF && free_rpt_idx == 0xff)
            free_rpt_idx = idx;
        if(memcmp(ls_at_buff_env.adv_rpt[idx].adv_addr.addr,param->adv_addr->addr,BLE_ADDR_LEN) == 0 )
            return;
    }
    if(param->info.connectable){
        ls_at_buff_env.adv_rpt[free_rpt_idx].evt_type = param->info;
        ls_at_buff_env.adv_rpt[free_rpt_idx].adv_addr_type = param->adv_addr_type;
        memcpy(ls_at_buff_env.adv_rpt[free_rpt_idx].adv_addr.addr,param->adv_addr->addr,BLE_ADDR_LEN);
        ls_at_buff_env.adv_rpt[free_rpt_idx].rssi = param->rssi;
        ls_at_buff_env.adv_rpt[free_rpt_idx].data_len = param->length;
        memcpy(ls_at_buff_env.adv_rpt[free_rpt_idx].data,param->data,param->length);
        LOG_HEX(ls_at_buff_env.adv_rpt[free_rpt_idx].data,param->length);
    }
}

void gap_scaning_cmp_ind(void)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    uint8_t addr_str[BLE_ADDR_LEN*2+1];
    msg_len = sprintf((char *)msg_rsp,"\r\n+SCAN:ON\r\nOK\r\n");
    uart_write(msg_rsp,msg_len);

    for(uint8_t idx = 0; idx<ADV_REPORT_NUM; idx++)
    {
        if(ls_at_buff_env.adv_rpt[idx].evt_type.connectable)
        {
            hex_arr_to_str(addr_str,ls_at_buff_env.adv_rpt[idx].adv_addr.addr,BLE_ADDR_LEN);
            addr_str[BLE_ADDR_LEN * 2] = 0;

            msg_len = sprintf((char *)msg_rsp,"\r\nNo: %d Addr:%s Rssi:%ddBm\r\n",idx,addr_str,(signed char)ls_at_buff_env.adv_rpt[idx].rssi);
            uart_write(msg_rsp,msg_len);
        }
    }
}

void trans_mode_exit(void)
{
    if(ls_at_ctl_env.transparent_start)
    {
        ls_at_ctl_env.transparent_start = 0;
        at_clr_uart_buff();
    }
}

static void at_gap_name_handler(uint8_t *p_cmd_parse)
{
    uint8_t idx = 0;
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    switch (*p_cmd_parse++)
    {
    case '?':
        msg_len = sprintf((char*)msg_rsp, "\r\n+NAME:%s\r\nOK\r\n", ble_device_name);
        uart_write(msg_rsp,msg_len);
        break;
    case '=':
        for (idx = 0; idx < DEV_NAME_MAX_LEN; idx++)
        {
            if (*(p_cmd_parse + idx) == '\r')
                break;
        }
        if (idx >= DEV_NAME_MAX_LEN)
        {
            *(p_cmd_parse + idx) = 0x0;
            msg_len = sprintf((char*)msg_rsp, "\r\n+NAME:%s\r\nERR\r\n", p_cmd_parse);
            uart_write(msg_rsp,msg_len);
            break;
        }
        memset(ble_device_name, 0x0, DEV_NAME_MAX_LEN);
        memcpy(ble_device_name, p_cmd_parse, idx);
        at_start_adv();

        msg_len = sprintf((char*)msg_rsp, "\r\n+NAME:%s\r\nOK\r\n", ble_device_name);
        uart_write(msg_rsp,msg_len);
        break;
    default:
        break;
    }
}

static void at_bd_addr_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    uint8_t dev_addr_str[2 * BLE_ADDR_LEN + 1];
    uint8_t dev_addr[BLE_ADDR_LEN];
    bool type;
    memset(msg_rsp, 0, sizeof(msg_rsp));

    switch (*p_cmd_parse++)
    {
    case '=':
        str_to_hex_arr(dev_addr, p_cmd_parse, BLE_ADDR_LEN);
        dev_manager_set_mac_addr(dev_addr);
        hex_arr_to_str(dev_addr_str, dev_addr, BLE_ADDR_LEN);
        dev_addr_str[BLE_ADDR_LEN * 2] = 0;

        msg_len = sprintf((char *)msg_rsp, "\r\n+MAC:%s\r\nOK\r\n", dev_addr_str);
        uart_write(msg_rsp,msg_len);
        break;
    case '?':
        dev_manager_get_identity_bdaddr(dev_addr, &type);
        hex_arr_to_str(dev_addr_str, dev_addr, BLE_ADDR_LEN);
        dev_addr_str[BLE_ADDR_LEN * 2] = 0;

        msg_len = sprintf((char *)msg_rsp, "\r\n+MAC:%s\r\nOK\r\n", dev_addr_str);
        uart_write(msg_rsp,msg_len);
        break;
    default:
        break;
    }
}

static void at_adv_param_set_handler(uint8_t *p_cmd_parse)
{
    uint8_t temp;
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    switch (*p_cmd_parse++)
    {
    case '?':
        msg_len = sprintf((char *)msg_rsp,"\r\n+ADVINT:%d\r\nOK\r\n",ls_at_buff_env.default_info.advint);
        uart_write(msg_rsp,msg_len);
        break;
    case '=':
        temp = ls_at_buff_env.default_info.advint;
        update_adv_intv(adv_int_arr[atoi((const char *)p_cmd_parse)]);
        ls_at_buff_env.default_info.advint = atoi((const char *)p_cmd_parse);
        if(ls_at_buff_env.default_info.advint>5)
        {
            msg_len = sprintf((char *)msg_rsp,"\r\n+ADVINT:%d\r\nERR\r\n",ls_at_buff_env.default_info.advint);
            ls_at_buff_env.default_info.advint = temp;
        }
        else{
            msg_len = sprintf((char *)msg_rsp,"\r\n+ADVINT:%d\r\nOK\r\n",ls_at_buff_env.default_info.advint);
        }
        uart_write(msg_rsp,msg_len);
        break;
    default:
        break;
    }
}

static void at_adv_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    switch (*p_cmd_parse++)
    {
    case '?':
        if(get_adv_status())
        {
            msg_len = sprintf((char *)msg_rsp, "\r\n+ADV:B\r\nOK\r\n");
            uart_write(msg_rsp,msg_len);
        }
        else
        {
            msg_len = sprintf((char *)msg_rsp, "\r\n+ADV:I\r\nOK\r\n");
            uart_write(msg_rsp,msg_len);
        }
        break;
    case '=':
        if(*p_cmd_parse == 'B')
        {
            at_start_adv();
            msg_len = sprintf((char *)msg_rsp, "\r\n+ADV:B\r\nOK\r\n");
            uart_write(msg_rsp,msg_len);
        }
        else if(*p_cmd_parse == 'I')
        {
            at_stop_adv();
            msg_len = sprintf((char *)msg_rsp, "\r\n+ADV:I\r\nOK\r\n");
            uart_write(msg_rsp,msg_len);
        }
        break;
    default:
        break;
    }
}

static void at_scan_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    msg_len = sprintf((char *)msg_rsp,"\r\nScan start...\r\n");
    uart_write(msg_rsp,msg_len);

    switch(*p_cmd_parse++)
    {
        case '=':
        {
            uint8_t scan_time = atoi((const char *)p_cmd_parse);
            if(scan_time > 0 && scan_time < 100)
                ls_at_ctl_env.scan_duration = scan_time*100;
        }
        break;
    }
    memset(&(ls_at_buff_env.adv_rpt[0]),0xff,sizeof(struct at_adv_report)*ADV_REPORT_NUM);
    if(ls_at_ctl_env.scan_duration == 0)
        start_scan(500);
    else
        start_scan(ls_at_ctl_env.scan_duration);
}

static void at_app_reset_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    msg_len = sprintf((char *)msg_rsp,"\r\n+RESET\r\nOK\r\n");
    uart_write(msg_rsp,msg_len);
    platform_reset(0);
}

static void at_connect_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    uint8_t peer_dev_addr_str[BLE_ADDR_LEN*2+1];

    memset(msg_rsp, 0, sizeof(msg_rsp));

    switch (*p_cmd_parse++)
    {
    case '=':
    {
        uint8_t idx = atoi((const char *)p_cmd_parse);
        start_init(ls_at_buff_env.adv_rpt[idx].adv_addr.addr,ls_at_buff_env.adv_rpt[idx].adv_addr_type);
        hex_arr_to_str(peer_dev_addr_str,ls_at_buff_env.adv_rpt[idx].adv_addr.addr,BLE_ADDR_LEN);
    }
    break;
    }
    msg_len = sprintf((char *)msg_rsp,"\r\n+CONN:%s\r\nOK\r\n",peer_dev_addr_str);
    uart_write(msg_rsp,msg_len);
}

static void at_link_get_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    struct ble_addr tmp_addr;
    uint8_t mac_str[BLE_ADDR_LEN*2+1];
    uint8_t link_mode;
    msg_len = sprintf((char *)msg_rsp,"\r\n+LINK\r\nOK\r\n");
    uart_write(msg_rsp,msg_len);
    if ( *p_cmd_parse == '?')
    {
        for (uint8_t i=0; i < SDK_MAX_CONN_NUM; i++)
        {
            if (get_con_status(i)==false)
            {
                continue;
            }
            if (gap_manager_get_role(i) == LS_BLE_ROLE_SLAVE)
            {
                gap_manager_get_peer_addr(i, &tmp_addr);
                link_mode = 'S';
            }
            else
            {
                gap_manager_get_peer_addr(i, &tmp_addr);
                link_mode = 'M';
            }
            
            hex_arr_to_str(mac_str,(const uint8_t*)&tmp_addr.addr.addr,BLE_ADDR_LEN);
            mac_str[BLE_ADDR_LEN*2] = 0;
            msg_len = sprintf((char *)msg_rsp,"Link_ID: %d LinkMode:%c PeerAddr:%s\r\n",i,link_mode,mac_str);
            uart_write(msg_rsp,msg_len);
        }
    }
}

static void at_sleep_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    uint8_t sleep_mode_set;
    struct deep_sleep_wakeup wkup;
    switch(*p_cmd_parse++)
    {
        case '=':
        sleep_mode_set = atoi((const char *)p_cmd_parse);
        if(sleep_mode_set>2){
            msg_len = sprintf((char *)msg_rsp,"\r\n+SLEEP:\r\nERR\r\n");
            uart_write(msg_rsp,msg_len);
        }
        else
        {
            msg_len = sprintf((char *)msg_rsp,"\r\n+SLEEP:\r\nOK\r\n");
            uart_write(msg_rsp,msg_len);
            HAL_UART_DeInit(&UART_Server_Config);
            pinmux_uart1_deinit();
            io_pull_write(PB01,IO_PULL_DISABLE);
            if(sleep_mode_set==0){
                wkup_io_setup();
            }
            else if(sleep_mode_set==1){
                HAL_RTC_Init(RTC_CKSEL_LSI);
                RTC_wkuptime_set(WAKEUP_MS);
                memset(&wkup,0,sizeof(wkup));

                wkup.rtc = 1;
                enter_deep_sleep_mode_lvl2_lvl3(&wkup);
            }
            else if(sleep_mode_set==2){
                memset(&wkup,0,sizeof(wkup));
                wkup.pb15 = 1;
                wkup.pb15_rising_edge = 1;
                enter_deep_sleep_mode_lvl2_lvl3(&wkup);
            }
        }
        break;
    }
}

static void at_disconnect_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    switch(*p_cmd_parse++)
    {
        case '=':
            if(*p_cmd_parse == 'A')
            {
                for(uint8_t i=0; i < get_ble_con_num(); i++)
                {
                    if (get_con_status(i)==false)
                    {
                        continue;
                    }
                    gap_manager_disconnect(i, 0x13);           
                }
            }
            else
            {
                uint8_t con_idx = atoi((const char *)p_cmd_parse);
                if(get_con_status(con_idx))
                {
                    gap_manager_disconnect(con_idx, 0x13);
                }
                else
                {
                    msg_len = sprintf((char *)msg_rsp,"\r\n+DISCONN:%d\r\nERR\r\n",con_idx);
                    uart_write(msg_rsp,msg_len);
                }
            }
        break;
        default:break;
    }
}

static void at_flash_save_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    at_store_info_to_flash();
    msg_len = sprintf((char *)msg_rsp,"\r\n+FLASH\r\nOK\r\n");
    uart_write(msg_rsp,msg_len);
}

static void at_multi_connect_trans_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    if ((*p_cmd_parse++) == '=')
    {
        uint8_t *pos_int_end = NULL;
        pos_int_end = find_int_from_str(p_cmd_parse);
        uint8_t con_idx = atoi((const char *)p_cmd_parse);

        p_cmd_parse = pos_int_end + 1;
        pos_int_end = find_int_from_str(p_cmd_parse);
        uint32_t len = atoi((const char *)p_cmd_parse);

        if (get_con_status(con_idx))
        {
            ls_at_ctl_env.transparent_conidx = con_idx;
            ls_at_ctl_env.one_slot_send_len = len;
            ls_at_ctl_env.one_slot_send_start = true;
            at_clr_uart_buff();
            msg_len = sprintf((char *)msg_rsp, "\r\n>\r\n");
        }
        else
        {
            msg_len = sprintf((char *)msg_rsp, "\r\n+SEND\r\nERR\r\n");
        }
        uart_write(msg_rsp,msg_len);
    }
}

static void at_sigle_connect_trans_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    if (get_ble_con_num() == 1)
    {
        uint8_t i;
        for (i = 0; i < SDK_MAX_CONN_NUM; i++)
        {
            if (get_con_status(i))
                break;
        }
        ls_at_ctl_env.transparent_start = 1;
        ls_at_ctl_env.transparent_conidx = i;
        at_clr_uart_buff();

        msg_len = sprintf((char *)msg_rsp, "\r\n+++\r\nOK\r\n");
    }
    else
    {
        msg_len = sprintf((char *)msg_rsp, "\r\n+++\r\nERR\r\n");
    }
    uart_write(msg_rsp,msg_len);
}

static void at_auto_trans_auto_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    switch (*p_cmd_parse++)
    {
    case '?':
        if(ls_at_buff_env.default_info.auto_trans == true)
            msg_len = sprintf((char *)msg_rsp,"\r\n+AUTO+++:Y\r\nOK\r\n");
        else
            msg_len = sprintf((char *)msg_rsp,"\r\n+AUTO+++:Y\r\nOK\r\n");
        uart_write(msg_rsp,msg_len);
        break;
    case '=':
        if(*p_cmd_parse == 'Y')
        {
            ls_at_buff_env.default_info.auto_trans = true;
            msg_len = sprintf((char *)msg_rsp,"\r\n+AUTO+++:Y\r\nOK\r\n");
        }
        else if(*p_cmd_parse == 'N')
        {
            ls_at_buff_env.default_info.auto_trans = false;
            msg_len = sprintf((char *)msg_rsp,"\r\n+AUTO+++:N\r\nOK\r\n");
        }
        uart_write(msg_rsp,msg_len);
        break;
    default:
        break;
    }
}

static void at_tx_power_handler(uint8_t *p_cmd_parse)
{
    uint8_t msg_len;
    uint8_t msg_rsp[100];
    memset(msg_rsp, 0, sizeof(msg_rsp));

    switch(*p_cmd_parse++)
    {
        case '?':
            msg_len = sprintf((char *)msg_rsp,"\r\n+POWER:%d\r\nOK\r\n",ls_at_buff_env.default_info.rfpower);
            uart_write(msg_rsp,msg_len);
            break;
        case '=':
            ls_at_buff_env.default_info.rfpower = atoi((const char *)p_cmd_parse);
            if(ls_at_buff_env.default_info.rfpower > TX_12DBM_PAHP)
                msg_len = sprintf((char *)msg_rsp,"\r\n+POWER:%d\r\nERR\r\n",ls_at_buff_env.default_info.rfpower);
            else
            {
                LOG_I("power:%d",ls_at_buff_env.default_info.rfpower);
                rf_set_power((enum rf_tx_pwr)ls_at_buff_env.default_info.rfpower);
                msg_len = sprintf((char *)msg_rsp,"\r\n+POWER:%d\r\nOK\r\n",ls_at_buff_env.default_info.rfpower);
            }
            uart_write(msg_rsp,msg_len);
            break;
        default:
            break;
    }
}

void at_recv_cmd_handler(at_recv_cmd_t *param)
{
    uint8_t cmd_num = sizeof(at_cmd_attr_table) / sizeof(at_cmd_attr_t);
    uint8_t *buff = param->recv_data;
    for(uint8_t i=0;i<cmd_num;i++) {
        if(memcmp(buff, at_cmd_attr_table[i].cmd_tag_str,at_cmd_attr_table[i].cmd_tag_length) == 0){
            buff += strlen(at_cmd_attr_table[i].cmd_tag_str);
            at_cmd_attr_table[i].cmd_handler(buff);
        }
    }
}
