#include <string.h>
#include "cpu.h"
#include "platform.h"
#include "io_config.h"
#include "ls_dbg.h"
#include "lsuart.h"
#include "ls_24g.h"
#include "app_user_24g.h"
#include "log.h"

#define _ISR // The macro means the function will be called in interrupt.

#define RF_CHANNEL_DEFAULT 2380
#define RF_PHY_DEFAULT PROP_24G_PHY_1MBPS

#define UART_SYNC_BYTE  0xA5
#define UART_SYNC_BYTE_LEN 1
#define UART_LEN_LEN 1
#define UART_24G_BUF_SIZE (UART_SYNC_BYTE_LEN + UART_LEN_LEN + VALID_TX_LEN_MAX)

enum uart_rx_status
{
    UART_IDLE,
    UART_SYNC,
    UART_LEN_REV,
    UART_LINK_ID,
    UART_RECEIVING,
};
static uint8_t uart_state = UART_IDLE;
static bool uart_tx_busy = false;
static uint8_t uart_rx_buf[UART_24G_BUF_SIZE];
static uint8_t uart_tx_buf[UART_24G_BUF_SIZE];
static uint8_t rf_rx_length;
static UART_HandleTypeDef UART_Config; 

static void app_user_24g_rx(void);
static void ls_uart_recv_restart(void);

_ISR static void app_user_24g_tx_cb(void *param)
{
    // LOG_I("24g tx completed");
    ls_uart_recv_restart();
    app_user_24g_rx();
}
_ISR static void app_user_24g_rx_cb(void *param)
{
    // LOG_I("24g rx completed, length=%d", rf_rx_length);
    if (!uart_tx_busy && rf_rx_length > 0)
    {
        uart_tx_busy = true;
        HAL_UART_Transmit_IT(&UART_Config, &uart_tx_buf[0], rf_rx_length);
        rf_rx_length = 0;
        // LOG_I("rssi: %d", RF_24g_GetRssi());
    }
}

static void ls_uart_init(void)
{
    uart1_io_init(PB00, PB01);
    io_pull_write(PB01, IO_PULL_UP);
    UART_Config.UARTX = UART1;
    UART_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Config.Init.MSBEN = 0;
    UART_Config.Init.Parity = UART_NOPARITY;
    UART_Config.Init.StopBits = UART_STOPBITS1;
    UART_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config);
}
static void ls_uart_recv_restart(void)
{
    uart_state = UART_IDLE;
    HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[0], UART_SYNC_BYTE_LEN);
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    LOG_I("uart tx cplt");
    uart_tx_busy = false; 
    app_user_24g_rx();
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t len;
    bool restart = true;
    switch (uart_state)
    {
    case UART_IDLE:
        if(uart_rx_buf[0] == UART_SYNC_BYTE)
        {
            uart_state = UART_SYNC;
            HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[UART_SYNC_BYTE_LEN], UART_LEN_LEN);
            restart = false;
        }
        break;
    case UART_SYNC:
        len = uart_rx_buf[UART_SYNC_BYTE_LEN];
        if (len > VALID_TX_LEN_MAX)
        {
            LOG_I("Invalid length!");
            uart_state = UART_IDLE;
        }
        else
        {
            uart_state = UART_RECEIVING;
            HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[UART_SYNC_BYTE_LEN + UART_LEN_LEN], len);
            restart = false;
        }
        break;
    case UART_RECEIVING:
        len = uart_rx_buf[UART_SYNC_BYTE_LEN];
        RF_24g_Tx(&uart_rx_buf[UART_SYNC_BYTE_LEN + UART_LEN_LEN], len, app_user_24g_tx_cb, NULL); 
        restart = false;
        break;
    default:
        break;
    }
    if(restart)
    {
        ls_uart_recv_restart();
    }
}

static void app_user_24g_rx(void)
{
    RF_24g_Rx(uart_tx_buf, &rf_rx_length, app_user_24g_rx_cb, NULL);
}

void app_user_24g_init(void)
{
    ls_uart_init();
    ls_uart_recv_restart();
    RF_24g_SetChannel(RF_CHANNEL_DEFAULT);
    RF_24g_SetPhy(RF_PHY_DEFAULT);
    app_user_24g_rx();
}

int main()
{
    sys_init_24g();
    RF_24g_Init();
    app_user_24g_init();
    while (1)
    {
        
    }
}
