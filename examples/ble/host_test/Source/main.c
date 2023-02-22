#include "ls_ble.h"
#include "platform.h"
#include "ls_hal_uart.h"
#include "ls_soc_gpio.h"
UART_HandleTypeDef UART_Config; 
static void (*eif_read_callback)(void *,uint8_t);
static void (*eif_write_callback)(void *,uint8_t);
static void *tx_arg;
static void *rx_arg;
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &UART_Config)
    {
        eif_write_callback(tx_arg,0);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == &UART_Config)
    {
        eif_read_callback(rx_arg,0);
    }
}

void uart_eif_read(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy)
{
    eif_read_callback = callback;
    rx_arg = dummy;
    HAL_UART_Receive_IT(&UART_Config,bufptr,size);
}

void uart_eif_write(uint8_t *bufptr, uint32_t size, void (*callback)(void *,uint8_t), void* dummy)
{
    eif_write_callback = callback;
    tx_arg = dummy;
    HAL_UART_Transmit_IT(&UART_Config,bufptr,size);
}

void uart_eif_flow_on(void)
{

}

bool uart_eif_flow_off(void)
{
    return true;
}

static void uart_test_init(void)
{
    pinmux_uart1_init(PB00,PB01);
    io_pull_write(PB01, IO_PULL_UP);
    UART_Config.UARTX = UART1;
    UART_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Config.Init.MSBEN = 0;
    UART_Config.Init.Parity = UART_NOPARITY;
    UART_Config.Init.StopBits = UART_STOPBITS1;
    UART_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config);
}

int main()
{
    sys_init_itf();
    uart_test_init();
    ble_init();
    ble_loop();
    return 0;
}

