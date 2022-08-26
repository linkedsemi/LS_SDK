#include <stdio.h>
#include <string.h>
#include "at_recv_cmd.h"
#include "at_cmd_parse.h"
#include "builtin_timer.h"
#include "ls_sys.h"
#include "cpu.h"
#include "ls_soc_gpio.h"
#include "tinyfs.h"

#define RECORD_BLEAT 1
#define RECORD_BLENAME 2
#define AT_RECV_MAX_LEN 251
#define AT_TRANSPARENT_DOWN_LEVEL (AT_RECV_MAX_LEN - 40)

tinyfs_dir_t ble_at_dir;
UART_HandleTypeDef UART_Server_Config;
static struct builtin_timer *uart_server_timer_inst = NULL;
static struct builtin_timer *exit_trans_mode_timer = NULL;

uint8_t at_recv_char;
static bool uart_tx_busy = false;
struct at_buff_env ls_at_buff_env = {0};
struct at_ctrl ls_at_ctl_env = {0};
at_recv_cmd_t recv_cmd;
at_recv_t at_cmd_event;

struct at_env
{
    uint8_t at_recv_buffer[AT_RECV_MAX_LEN];
    uint8_t at_recv_index;
    uint8_t at_recv_state;
    uint8_t data_sending;
} ls_at_env = {0};

void at_clr_uart_buff(void)
{
    ls_at_env.at_recv_index = 0;
}

void at_cmd_recv_cb(void *arg)
{
    at_recv_t *msg = (at_recv_t *)arg;
    switch (msg->evt_id)
    {
    case AT_RECV_CMD:
        at_recv_cmd_handler((at_recv_cmd_t *)msg->param);
        break;
    case AT_RECV_TRANSPARENT_DATA:
    {
        builtin_timer_stop(uart_server_timer_inst);
        uint32_t cpu_stat = enter_critical();
        if (get_con_status(ls_at_ctl_env.transparent_conidx))
        {
            if (gap_manager_get_role(ls_at_ctl_env.transparent_conidx) == LS_BLE_ROLE_SLAVE) //slave send
            {
                ble_slave_send_data(ls_at_ctl_env.transparent_conidx, ls_at_env.at_recv_buffer, ls_at_env.at_recv_index);
            }
            else //master send
            {
                ble_master_send_data(ls_at_ctl_env.transparent_conidx, ls_at_env.at_recv_buffer, ls_at_env.at_recv_index);
            }
        }
        ls_at_env.at_recv_index = 0;
        ls_at_env.data_sending = 0;
        exit_critical(cpu_stat);
        if (ls_at_ctl_env.one_slot_send_start && ls_at_ctl_env.one_slot_send_len == 0)
        {
            ls_at_ctl_env.one_slot_send_start = false;
            ls_at_ctl_env.one_slot_send_len = 0;
            uint8_t at_rsp[] = "\r\nSEND OK\r\n";
            uart_write(at_rsp,sizeof(at_rsp));
        }
    }break;
    case AT_TRANSPARENT_START_TIMER:
        builtin_timer_start(uart_server_timer_inst, 50, NULL);
        break;
    default:
        break;
    }
}

void transparent_timer_handler(void *param)
{
    if (ls_at_env.data_sending == 0)
    {
        ls_at_env.data_sending = 1;
        at_cmd_event.evt_id = AT_RECV_TRANSPARENT_DATA;
        at_cmd_event.param = NULL;
        at_cmd_event.param_len = 0;
        func_post(at_cmd_recv_cb, (void *)&at_cmd_event);
    }
}

void exit_trans_mode_timer_handler(void *arg)
{
    builtin_timer_stop(exit_trans_mode_timer);
    ls_at_ctl_env.transparent_start = 0;
    ls_at_env.at_recv_index = 0;

    uint8_t at_rsp[] = "\r\nExit OK\r\n";
    uart_write(at_rsp, sizeof(at_rsp));
}

void at_recv(uint8_t c)
{
    if (ls_at_ctl_env.transparent_start)
    {
        if (ls_at_env.at_recv_index == 0)
        {
            at_cmd_event.evt_id = AT_TRANSPARENT_START_TIMER;
            at_cmd_event.param = NULL;
            at_cmd_event.param_len = 0;
            func_post(at_cmd_recv_cb, (void *)&at_cmd_event);
        }
        if (ls_at_env.at_recv_index < (AT_RECV_MAX_LEN - 2))
        {
            ls_at_env.at_recv_buffer[ls_at_env.at_recv_index++] = c;
        }

        builtin_timer_stop(exit_trans_mode_timer);
        if(ls_at_env.at_recv_index == 3)
        {
            if( ls_at_env.at_recv_buffer[ls_at_env.at_recv_index-1] == '+'
                && ls_at_env.at_recv_buffer[ls_at_env.at_recv_index-2] == '+'
                && ls_at_env.at_recv_buffer[ls_at_env.at_recv_index-3] == '+')
                builtin_timer_start(exit_trans_mode_timer,500,NULL);
        }

        if ((ls_at_env.at_recv_index > AT_TRANSPARENT_DOWN_LEVEL) && (ls_at_env.data_sending == 0))
        {
            ls_at_env.data_sending = 1;
            at_cmd_event.evt_id = AT_RECV_TRANSPARENT_DATA;
            at_cmd_event.param = NULL;
            at_cmd_event.param_len = 0;
            func_post(at_cmd_recv_cb, (void *)&at_cmd_event);
        }
        goto _end;
    }
    if (ls_at_ctl_env.one_slot_send_start)
    {
        if (ls_at_ctl_env.one_slot_send_len > 0)
        {
            if (ls_at_env.at_recv_index == 0)
            {
                at_cmd_event.evt_id = AT_TRANSPARENT_START_TIMER;
                at_cmd_event.param = NULL;
                at_cmd_event.param_len = 0;
                func_post(at_cmd_recv_cb, (void *)&at_cmd_event);
            }
            if (ls_at_env.at_recv_index < (AT_RECV_MAX_LEN - 2))
            {
                ls_at_env.at_recv_buffer[ls_at_env.at_recv_index++] = c;
            }

            ls_at_ctl_env.one_slot_send_len--;

            if (((ls_at_env.at_recv_index > AT_TRANSPARENT_DOWN_LEVEL) && (ls_at_env.data_sending == 0)) || (ls_at_ctl_env.one_slot_send_len == 0))
            {
                ls_at_env.data_sending = 1;
                at_cmd_event.evt_id = AT_RECV_TRANSPARENT_DATA;
                at_cmd_event.param = NULL;
                at_cmd_event.param_len = 0;
                func_post(at_cmd_recv_cb, (void *)&at_cmd_event);
            }
        }
        goto _end;
    }

    switch (ls_at_env.at_recv_state)
    {
    case 0:
        if (c == 'A')
        {
            ls_at_env.at_recv_state++;
        }
        break;
    case 1:
        if (c == 'T')
            ls_at_env.at_recv_state++;
        else
            ls_at_env.at_recv_state = 0;
        break;
    case 2:
        if (c == '+')
            ls_at_env.at_recv_state++;
        else
            ls_at_env.at_recv_state = 0;
        break;
    case 3:
        ls_at_env.at_recv_buffer[ls_at_env.at_recv_index] = c;
        if ((c == '\n') && (ls_at_env.at_recv_buffer[ls_at_env.at_recv_index - 1] == '\r'))
        {
            memset(&recv_cmd,0,sizeof(recv_cmd));
            recv_cmd.recv_len = ls_at_env.at_recv_index + 1;
            memcpy(recv_cmd.recv_data, ls_at_env.at_recv_buffer, recv_cmd.recv_len);
            at_cmd_event.evt_id = AT_RECV_CMD;
            at_cmd_event.param = (uint8_t*)&recv_cmd;
            at_cmd_event.param_len = sizeof(at_recv_cmd_t);
            func_post(at_cmd_recv_cb, (void *)&at_cmd_event);

            ls_at_env.at_recv_state = 0;
            ls_at_env.at_recv_index = 0;
        }
        else
        {
            ls_at_env.at_recv_index++;
            if (ls_at_env.at_recv_index >= AT_RECV_MAX_LEN)
            {
                ls_at_env.at_recv_state = 0;
                ls_at_env.at_recv_index = 0;
            }
        }
        break;
    default:
        break;
    }

_end:;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_tx_busy = false;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    at_recv(at_recv_char);
    HAL_UART_Receive_IT(&UART_Server_Config, &at_recv_char, 1);
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
    HAL_UART_Receive_IT(&UART_Server_Config, &at_recv_char, 1);  
}

void uart_write(uint8_t *value, uint16_t length)
{
    HAL_UART_Transmit(&UART_Server_Config, value, length, 1000);
}

void uart_tx_it(uint8_t *value, uint16_t length)
{
    if (uart_tx_busy)
    {
        LOG_I("Uart tx busy, data discard!");
    }
    else
    {
        uart_tx_busy = true;
        HAL_UART_Transmit_IT(&UART_Server_Config, value, length);
    }
}

void at_load_info_from_flash(void)
{
    uint8_t ret;
    struct at_buff_env buff;
    uint16_t len = sizeof(buff);
    uint16_t name_len = sizeof(ble_device_name);

    ret = tinyfs_read(ble_at_dir, RECORD_BLENAME, ble_device_name, &name_len);
    if(ret != TINYFS_NO_ERROR)
    {
        LOG_I("ble device name read:%d",ret);
    }
    ret = tinyfs_read(ble_at_dir, RECORD_BLEAT, (uint8_t*)&buff, &len);
    if(ret != TINYFS_NO_ERROR)
    {
        LOG_I("at read:%d",ret);
        ls_at_buff_env.default_info.rfpower = TX_0DBM;
        ls_at_buff_env.default_info.advint = 0;
    }
    else
    {
        memcpy(&ls_at_buff_env, &buff, len);
        if(ls_at_buff_env.default_info.rfpower>TX_12DBM_PAHP) {
            ls_at_buff_env.default_info.rfpower = TX_0DBM;
        }
        if(ls_at_buff_env.default_info.advint>5) {
            ls_at_buff_env.default_info.advint = 0;
        }
    }
    rf_set_power((enum rf_tx_pwr)ls_at_buff_env.default_info.rfpower);
}

void at_store_info_to_flash(void)
{
    uint8_t ret;
    ret = tinyfs_write(ble_at_dir, RECORD_BLENAME, ble_device_name, sizeof(ble_device_name));
    if(ret != TINYFS_NO_ERROR)
    {
        LOG_I("name write:%d",ret);
    }
    ret = tinyfs_write(ble_at_dir, RECORD_BLEAT, (uint8_t*)&ls_at_buff_env, sizeof(ls_at_buff_env));
    if(ret != TINYFS_NO_ERROR)
    {
        LOG_I("ble write:%d",ret);
    }
    tinyfs_write_through();
}

void wkup_io_setup(void)
{
    io_cfg_input(PB15);
    io_pull_write(PB15,IO_PULL_DOWN);
    io_exti_config(PB15,INT_EDGE_RISING); 
     
}

void io_exti_callback(uint8_t pin,exti_edge_t edge)
{
    switch(pin)
    {
    case PB15:
        ls_uart_init();
    break;
    default:
    break;    
    }
}

void at_init(void)
{
    tinyfs_mkdir(&ble_at_dir, ROOT_DIR, 5);
    at_load_info_from_flash();
    ls_uart_init();

    uart_server_timer_inst = builtin_timer_create(transparent_timer_handler);
    exit_trans_mode_timer = builtin_timer_create(exit_trans_mode_timer_handler);
}
