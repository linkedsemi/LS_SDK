#include <string.h>
#include "cpu.h"
#include "platform.h"
#include "le501x.h"
#include "sleep.h"
#include "sw_timer.h"
#include "sys_stat.h"
#include "ls_soc_gpio.h"
#include "ls_dbg.h"
#include "ls_hal_uart.h"
#include "ls_24g_common.h"
#include "ls_24g.h"
#include "app_user_24g.h"
#include "log.h"

#define _ISR // The macro means the function will be called in interrupt.

#define RF_CHANNEL_DEFAULT 2402
#define RF_PHY_DEFAULT PROP_24G_PHY_1MBPS

#define UART_SYNC_BYTE  0xA5
#define UART_SYNC_BYTE_LEN 1
#define UART_LEN_LEN 1
#define UART_24G_BUF_SIZE (UART_SYNC_BYTE_LEN + UART_LEN_LEN + VALID_TX_LEN_MAX)

#define USER_TIMER_PERIOD_MS 200
#define IO_FILTER_TIMER_PERIOD_MS 30
#define USER_TEST_IO PA07

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
static uint8_t uart_rx_buf[UART_24G_BUF_SIZE] = {0x02, 0x01, 0x06, 0x07, 0x08, 'L', 'S', '_', '2', '4', 'G'};
static uint8_t uart_tx_buf[UART_24G_BUF_SIZE];
static uint8_t rf_rx_length;
static volatile bool rf_tx_cplt_flag = true;
static UART_HandleTypeDef UART_Config; 
static struct sw_timer_env user_timer;
static struct sw_timer_env io_filter_timer;

static void app_user_24g_rx(void);
static void ls_uart_recv_restart(void);
static bool timer_cb(void *param);

uint8_t get_tx_format(void){return PROP_24G_LEGACY_ADV_FORMAT;}

_ISR static void app_user_24g_tx_cb(void *param)
{
    // LOG_I("24g tx completed");
    // ls_uart_recv_restart();
    // app_user_24g_rx();
    RF_24g_Tx(&uart_rx_buf[0], 11, app_user_24g_tx_cb, NULL); 
    rf_tx_cplt_flag = true;
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
    RF_24g_Rx(uart_tx_buf, &rf_rx_length, app_user_24g_rx_cb, NULL);
}
static void app_user_24g_peri_init(void)
{
    io_pull_write(USER_TEST_IO, IO_PULL_UP);
    io_cfg_input(USER_TEST_IO);
    io_exti_config(USER_TEST_IO,INT_EDGE_FALLING);
    

    io_cfg_output(PA00);
    ls_uart_init();
    ls_uart_recv_restart();
}

static void app_user_24g_rf_init(void)
{
    RF_24g_SetChannel(RF_CHANNEL_DEFAULT);
    RF_24g_SetPhy(RF_PHY_DEFAULT);
    // app_user_24g_rx();
    RF_24g_Tx(&uart_rx_buf[0], 11, app_user_24g_tx_cb, NULL); 
}

static void app_user_24g_peri_deinit(void)
{
    io_pull_write(USER_TEST_IO, IO_PULL_DOWN);
    ls_uart_deinit();
}

void io_exti_callback(uint8_t pin,exti_edge_t edge) 
{
    switch (pin)
    {
    case USER_TEST_IO:
        io_exti_config(USER_TEST_IO,INT_EDGE_DISABLE);
        NVIC_DisableIRQ(EXTI_IRQn);
        sw_timer_start(&io_filter_timer);
        break;
    default:
        break;
    }
}

static void app_user_sw_timer_init(void)
{
    sw_timer_callback_set(&user_timer,timer_cb,&user_timer);
    sw_timer_period_set(&user_timer,MS_2_PERIOD(USER_TIMER_PERIOD_MS));
    sw_timer_start(&user_timer);

    sw_timer_callback_set(&io_filter_timer,timer_cb,&io_filter_timer);
    sw_timer_period_set(&io_filter_timer,MS_2_PERIOD(IO_FILTER_TIMER_PERIOD_MS));
    // sw_timer_start(&io_filter_timer);
}
static bool timer_cb(void *param)
{
    bool timer_continue = true;
    if(param == (void *)&io_filter_timer)
    {
        static uint16_t gpio_filter_high_cnt = 0;
        static uint16_t gpio_filter_low_cnt = 0;
        if (1 == io_read_pin(USER_TEST_IO))
        {
            gpio_filter_low_cnt = 0;
            if(3 == ++gpio_filter_high_cnt)
            {
                if (rf_tx_cplt_flag && !uart_tx_busy && PROP_24G_STATE_IDLE == get_cur_prop_24g_state())
                {
                    app_status_set(true); // app prevent sleep entrance
                    app_user_24g_peri_init();
                    app_user_24g_rf_init();
                }
                // sw_timer_stop(&io_filter_timer);
                timer_continue = false;
                io_pull_write(USER_TEST_IO, IO_PULL_UP);
                io_exti_config(USER_TEST_IO,INT_EDGE_FALLING);
                
                NVIC_EnableIRQ(EXTI_IRQn);
                gpio_filter_high_cnt = 0;
            }
        }
        else
        {
            gpio_filter_high_cnt = 0;
            if (3 == ++gpio_filter_low_cnt)
            {
                // sw_timer_stop(&io_filter_timer);
                app_status_set(false); // app permit sleep entrance
                app_user_24g_peri_deinit();
                // RF_24g_Stop();
                timer_continue = false;
                io_pull_write(USER_TEST_IO, IO_PULL_DOWN);
                io_exti_config(USER_TEST_IO,INT_EDGE_RISING);
                
                NVIC_EnableIRQ(EXTI_IRQn);
                gpio_filter_low_cnt = 0;
            }
        }
    }
    else if (param == (void*)&user_timer)
    {
        io_toggle_pin(PA00);
    }
    
    return timer_continue;
}

int main()
{
    sys_init_24g();
    RF_24g_Init();

    app_user_24g_rf_init();
    // app_user_24g_peri_init();
    // app_user_sw_timer_init();
    while (1)
    {
        // ls_24g_sleep_wakeup();
    }
}
