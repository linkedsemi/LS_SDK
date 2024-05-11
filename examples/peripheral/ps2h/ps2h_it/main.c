#include "ls_hal_ps2h.h"
#include "ls_msp_ps2h.h"
#include "ls_hal_uart.h"
#include "ls_soc_gpio.h"
#include "ls_soc_pinmux.h"
#include "platform.h"
#include "log.h"

static PS2H_HandleTypeDef PS2H_Config;
static UART_HandleTypeDef UART_Config;
static uint8_t uart_rxdata; 

static void ps2h_init(void)
{
    LOG_I("demo ps2h_it start!");
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

int main()
{
    sys_init_none();
    ps2h_init();
    HAL_PS2H_Receive_IT_Start(&PS2H_Config);
    while (1)
    {
        HAL_UART_Receive(&UART_Config, &uart_rxdata, 1, HAL_MAX_DELAY);
        HAL_StatusTypeDef rs = HAL_PS2H_Transmit(&PS2H_Config, uart_rxdata);
        if (rs != HAL_OK)
        LOG_I("tx error code: 0x%x", rs);
        else
        LOG_I("tx successful");
    }
}

void HAL_PS2H_RxCpltCallback(PS2H_HandleTypeDef *hps2h, uint8_t data)
{
    LOG_I("receive data:  0x%x", data);
}

void HAL_PS2H_TxCpltCallback(PS2H_HandleTypeDef *hps2h)
{
    LOG_I("tx successful!");
}

void HAL_PS2H_TxErrorCallBack(PS2H_HandleTypeDef *hps2h)
{
    LOG_I("tx error!");
}

void HAL_PS2H_RxErrorCallBack(PS2H_HandleTypeDef *hps2h, RxErrorMode errmode)
{
    if (errmode & PS2_ERROR_START_BIT)
        LOG_I("rx error: START_BIT!");
    if (errmode & PS2_ERROR_STOP_BIT)
        LOG_I("rx error: STOP_BIT!");
    if (errmode & PS2_ERROR_PARITY_BIT)
        LOG_I("rx error: PARITY_BIT!");
    if (errmode & PS2_ERROR_RXFIFO_OVERRUN)
        LOG_I("rx error: RXFIFO_OVERRUN!");
}