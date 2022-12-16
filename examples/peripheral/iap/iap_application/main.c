#include "ls_hal_uart.h"
#include "ls_hal_flash.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "app_config.h"

// LM30XX , link_script_app.txt
// 
//  FLASH (rx) : ORIGIN = 0x805000, LENGTH = 0x7D000
//
// LE501X , link_script_app.txt
// 
//  FLASH (rx) : ORIGIN = 0x18009000
//

UART_HandleTypeDef UART_Config;

#define LED_IO PB05

void LED_init(void)
{
    io_cfg_output(LED_IO);
    io_write_pin(LED_IO, 1);
}
void LED_flicker(uint32_t flicker)
{
    io_toggle_pin(LED_IO);
    DELAY_US(flicker);
}
void uart_init(uint8_t txd, uint8_t rxd)
{
    // pinmux_uart1_init(PA09,PA10);
    // io_pull_write(PA10, IO_PULL_UP);

    pinmux_uart1_init(txd, rxd);
    io_pull_write(rxd, IO_PULL_UP);

    UART_Config.UARTX = UART1;
    UART_Config.Init.BaudRate = UART_BAUDRATE_115200;
    UART_Config.Init.MSBEN = 0;
    UART_Config.Init.Parity = UART_NOPARITY;
    UART_Config.Init.StopBits = UART_STOPBITS1;
    UART_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config);
}

uint8_t CalcChecksum(const uint8_t *p_data, uint32_t data_size)
{
    uint32_t sum = 0;
    const uint8_t *p_data_end = p_data + data_size;

    while (p_data < p_data_end)
    {
        sum += *p_data++;
    }

    return (sum & 0xffu);
}

void earse_app_sign_data(uint8_t *len_buffer)
{
    hal_flash_sector_erase(APP_CONFIG_ADDR_BASE);
}

int main()
{
    uint8_t data_buffer[8];
    uint32_t app_load = 1;
    uint32_t flicker = 500000;

    sys_init_none();
    LED_init();
    uart_init(PB00, PB01);

    HAL_UART_Transmit(&UART_Config, (uint8_t *)"Enter the IAP application.\r\n", 28, 1000);

    while (1)
    {
        if (app_load)
        {
            if (HAL_OK == HAL_UART_Receive(&UART_Config, data_buffer, 7, 1000))
            {
                /* /----------------- IAP Command -------------------------------------------------\
                * |     0    |     1       |  2    -   3   |     4    | ... |   n+4   |    n+5    |
                * |-------------------------------------------------------------------------------|
                * |   START  |   COMMAND   |    LENGTH     |  DATA[0] | ... | DATA[n] | CHECK_SUM |
                * |-------------------------------------------------------------------------------|
                * | SOD(3Ch) | 50h/80h/90h |       x       |  data[0] | ... | data[n] |      x    |
                * \-------------------------------------------------------------------------------/
                *
                * SOD = 0x3C       (start of data)
                * ACK = 0x3E       (acknowledgement character)
                *
                * CHECK_SUM  =   Checksum(DATA)
                * COMMAND : ERASE(50h) / DOWNLOAD(80h) / SIGN(90h)
                *
                * 每次命令发送，最大200ms超时时间等待ACK。
                *
                * SEND     : IAP Command (SOD + COMMAND + LENGTH + DATA + CHECK_SUM
                * RESPONSE : CHECK_SUM  + ACK
                *                                                                               */
                if ((0x3C == data_buffer[0]) && (0x50 == data_buffer[1]))
                {
                    if (CalcChecksum(data_buffer+4,2) == data_buffer[6])
                    {                        
                        data_buffer[0] = data_buffer[6];
                        data_buffer[1] = 0x3E;
                        HAL_UART_Transmit(&UART_Config, data_buffer, 2, 1000);

                        earse_app_sign_data(data_buffer + 4);
                        app_load = 0;
                        flicker = 100000;
                    }
                }
            }            
        }
        LED_flicker(flicker);
    }
}
