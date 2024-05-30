#include <string.h>
#include "cpu.h"
#include "platform.h"
#include "le501x.h"
#include "sleep.h"
#include "sys_stat.h"
#include "ls_soc_gpio.h"
#include "ls_dbg.h"
#include "ls_hal_uart.h"
#include "ls_24g_common_freertos.h"
#include "ls_24g.h"
#include "app_user_24g.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "log.h"

#define RX_TIMER_INTERVAL_MS 10
#define RX_DURATION_MS 6

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
static volatile bool uart_tx_busy = false;
static uint8_t uart_rx_buf[UART_24G_BUF_SIZE];
static uint8_t uart_tx_buf[UART_24G_BUF_SIZE];
static uint8_t rf_rx_buf[UART_24G_BUF_SIZE];
static uint8_t rf_rx_length;
static volatile bool rf_tx_cplt_flag = true;
static UART_HandleTypeDef UART_Config; 

extern void io_toggle_log(uint8_t pin, uint16_t count);

static void app_user_24g_rx(void);
static void ls_uart_recv_restart(void);

_ISR static void app_user_24g_tx_cb(void *param)
{
    // LOG_I("24g tx completed");
    ls_uart_recv_restart();
    app_user_24g_rx();
    rf_tx_cplt_flag = true;
}
_ISR static void app_user_24g_rx_cb(void *param)
{
    // LOG_I("24g rx completed, length=%d", rf_rx_length);
    if (!uart_tx_busy && rf_rx_length > 0)
    {
        uart_tx_busy = true;
        memcpy_ram((void*)&uart_tx_buf[0], (void*)&rf_rx_buf[0], rf_rx_length);
        HAL_UART_Transmit_IT(&UART_Config, &uart_tx_buf[0], rf_rx_length);
        rf_rx_length = 0;
        // LOG_I("rssi: %d", RF_24g_GetRssi());
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
static void ls_uart_deinit(void)
{
    pinmux_uart1_deinit();
    HAL_UART_DeInit(&UART_Config);
}
static void ls_uart_recv_restart(void)
{
    // return ;
    uart_state = UART_IDLE;
    HAL_UART_Receive_IT(&UART_Config, &uart_rx_buf[0], UART_SYNC_BYTE_LEN);
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    // LOG_I("uart tx cplt");
    uart_tx_busy = false; 
    // app_user_24g_rx();
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
        rf_tx_cplt_flag = false;
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
    RF_24g_Rx(rf_rx_buf, &rf_rx_length, app_user_24g_rx_cb, NULL);
}
static void app_user_24g_peri_init(void)
{
    ls_uart_init();
    ls_uart_recv_restart();
}

static void app_user_24g_rf_init(void)
{
    RF_24g_SetChannel(RF_CHANNEL_DEFAULT);
    RF_24g_SetPhy(RF_PHY_DEFAULT);
    app_user_24g_rx();
}

static void app_user_24g_peri_deinit(void)
{
    ls_uart_deinit();
}

static void *user_rx_timer_hdl;
static void user_rx_timer_cb(TimerHandle_t xTimer)
{
    static bool sleep_flag = true;
    if (sleep_flag)
    {
        xTimerChangePeriod(user_rx_timer_hdl, pdMS_TO_TICKS(RX_TIMER_INTERVAL_MS), portMAX_DELAY);
        app_status_set(false); // app allow sleep entrance
        while(uart_tx_busy);
        app_user_24g_peri_deinit();
        RF_24g_Stop();
    }
    else
    {
        xTimerChangePeriod(user_rx_timer_hdl, pdMS_TO_TICKS(RX_DURATION_MS), portMAX_DELAY);
        uart_tx_busy = false;
        app_status_set(true); // app prevent sleep entrance
        app_user_24g_peri_init();
        app_user_24g_rf_init();
    }
    sleep_flag = !sleep_flag;
}

static void user_rx_init(void)
{
    app_status_set(true);
    app_user_24g_peri_init();
    app_user_24g_rf_init();

    user_rx_timer_hdl = xTimerCreate("user_rx", pdMS_TO_TICKS(RX_DURATION_MS), pdTRUE, &user_rx_timer_hdl, user_rx_timer_cb);
    xTimerStart(user_rx_timer_hdl,portMAX_DELAY);
}

extern void rtos_init(void);
int main(void)
{
    sys_init_24g();
    rtos_init();
    RF_24g_Init();
    user_rx_init();
    vTaskStartScheduler();
}
