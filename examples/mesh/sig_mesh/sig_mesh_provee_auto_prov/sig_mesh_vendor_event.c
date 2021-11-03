#include <string.h>
#include "builtin_timer.h"
#include "log.h"
#include "ls_dbg.h"
#include "le501x.h"
#include "sig_mesh_ctl.h"
#include "sig_mesh_vendor_event.h"
#include "lsuart.h"
#include "io_config.h"

#define UART_BUFFER_SIZE (1024)
#define VENDOT_EVENT_TIMER_TIMEOUT 50
#define VENDOT_EVENT_DATA_LEN      UART_BUFFER_SIZE
#define DATA_LEN_LEN               4

uint8_t vendor_event_data[DATA_LEN_LEN+VENDOT_EVENT_DATA_LEN];

struct builtin_timer *vendor_event_timer = NULL;
static uint8_t uart_rx_byte;
static uint16_t uart_rx_index = 0;
static bool uart_tx_busy;
static uint8_t uart_buf[UART_BUFFER_SIZE];
static uint8_t uart_tx_buf[UART_BUFFER_SIZE];
static UART_HandleTypeDef UART_Server_Config; 
static uint32_t cnt_vendor_event_info=0;

static void ls_uart_init(void)
{
    uart1_io_init(PB00, PB01);
    UART_Server_Config.UARTX = UART1;
    UART_Server_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Server_Config.Init.MSBEN = 0;
    UART_Server_Config.Init.Parity = UART_NOPARITY;
    UART_Server_Config.Init.StopBits = UART_STOPBITS1;
    UART_Server_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Server_Config);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_tx_busy = false;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(uart_rx_index < UART_BUFFER_SIZE)
    {
        uart_buf[uart_rx_index++] = uart_rx_byte;
    }
    else
    {   
        LOG_I("uart rx buffer overflow!");
    }

    HAL_UART_Receive_IT(&UART_Server_Config, &uart_rx_byte, 1);
}

void vendor_event_accept_info(uint8_t const *info, uint32_t info_len)
{
    if(uart_tx_busy)
    {
        LOG_I("Uart tx busy, data discard!");
    }
    else
    {
      uart_tx_busy = true;
      LS_ASSERT(info_len <= UART_BUFFER_SIZE);
      memcpy(uart_tx_buf, info, info_len);
      HAL_UART_Transmit_IT(&UART_Server_Config, uart_tx_buf, info_len);
    }
}

void vendor_event_timer_cb(void *param)
{
    if (uart_rx_index >0)
    {
      cnt_vendor_event_info++;
      memcpy(&vendor_event_data[0],(uint8_t *)&cnt_vendor_event_info, DATA_LEN_LEN);
      memcpy(&vendor_event_data[DATA_LEN_LEN],&uart_buf[0], uart_rx_index);
      app_vendor_model_tx_message_handler(&vendor_event_data[0], DATA_LEN_LEN+uart_rx_index);
      uart_rx_index = 0;
    }
    builtin_timer_start(vendor_event_timer, VENDOT_EVENT_TIMER_TIMEOUT, NULL);
}

void vendor_event_init(void)
{
    ls_uart_init();
    HAL_UART_Receive_IT(&UART_Server_Config, &uart_rx_byte, 1);
    vendor_event_timer = builtin_timer_create(vendor_event_timer_cb);
    builtin_timer_start(vendor_event_timer, VENDOT_EVENT_TIMER_TIMEOUT, NULL);
}
