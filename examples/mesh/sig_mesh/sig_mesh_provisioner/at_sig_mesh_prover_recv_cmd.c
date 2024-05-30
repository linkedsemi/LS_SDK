#include <stdio.h>
#include <string.h>
#include "at_sig_mesh_prover_recv_cmd.h"
#include "at_sig_mesh_prover_cmd_parse.h"
#include "builtin_timer.h"
#include "ls_sys.h"
#include "cpu.h"
#include "ls_soc_gpio.h"
#include "tinyfs.h"
#include "log.h"

#define AT_RECV_MAX_LEN 251

tinyfs_dir_t ble_at_dir;
UART_HandleTypeDef UART_Server_Config;
static struct builtin_timer *exit_trans_mode_timer = NULL;

uint8_t at_recv_char;
static bool uart_tx_busy = false;
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
    ls_at_env.at_recv_index = 0;

    uint8_t at_rsp[] = "\r\nExit OK\r\n";
    uart_write(at_rsp, sizeof(at_rsp));
}

void at_recv(uint8_t c)
{
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
    UART_Server_Config.Init.BaudRate = UART_BAUDRATE_921600;
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
    
}

void at_store_info_to_flash(void)
{
   
}

void at_init(void)
{
    tinyfs_mkdir(&ble_at_dir, ROOT_DIR, 5);
    at_load_info_from_flash();
    ls_uart_init();

    exit_trans_mode_timer = builtin_timer_create(exit_trans_mode_timer_handler);
}
