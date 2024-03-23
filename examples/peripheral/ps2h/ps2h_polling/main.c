#include "ls_hal_ps2h.h"
#include "ls_msp_ps2h.h"
#include "ls_hal_uart.h"
#include "ls_soc_gpio.h"
#include "ls_soc_pinmux.h"
#include "platform.h"
#include "log.h"

static PS2H_HandleTypeDef PS2H_Config;
static UART_HandleTypeDef UART_Config;
static uint8_t ps2h_data; 
static uint8_t uart_data; 
static volatile bool flag;

static void ps2h_init(void)
{
    LOG_I("demo ps2h_polling start!");
    flag = false;
    pinmux_ps2h1_init(PA06, PA07);
    PS2H_Param param;
    param.err_mode             = PS2_TO_IDLE_STATE;
    param.flt_num              = PS2_FLTNUM_5CLK;
    param.tx_mode              = PS2_TXMODE_WAIT_RXEND;
    PS2H_Config.PS2HX          = PS2H1;
    HAL_PS2H_Init(&PS2H_Config, &param);
    DELAY_MS(10);
    UART_Config.UARTX = UART3;
    UART_Config.RTOValue = 5;
    UART_Config.Init.BaudRate = UART_BAUDRATE_921600;
    UART_Config.Init.MSBEN = 0;
    UART_Config.Init.Parity = UART_NOPARITY;
    UART_Config.Init.StopBits = UART_STOPBITS1;
    UART_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config);
}

static void ps2h_test()
{
    HAL_StatusTypeDef rs;
    
    LOG_I("transmit data: 0x%x", uart_data);
    rs  = HAL_PS2H_Transmit(&PS2H_Config, uart_data);
    if (rs != HAL_OK)
    {
        LOG_I("tx error code: 0x%x", rs);
        return;
    }
    LOG_I("transmit ok");

    rs = HAL_PS2H_Receive(&PS2H_Config, &ps2h_data, HAL_MAX_DELAY);
    if (rs != HAL_OK)
        LOG_I("rx error code: 0x%x", rs);
    else
        LOG_I("receive data: 0x%x", ps2h_data);
}

int main()
{
    sys_init_none();
    ps2h_init();
    HAL_UART_Receive_IT(&UART_Config, &uart_data, 1);
    while (1)
    {
        if (flag)
        {
            flag = false;
            ps2h_test();
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    HAL_UART_Receive_IT(&UART_Config, &uart_data, 1);
    flag = true;
}