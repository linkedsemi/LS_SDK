#include "ls_hal_uart.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "uart_process.h"
#include "upgrade_process.h"

uint32_t uart_recv_ticker;
uint8_t last_checksum;

#define SOD 0x3C /*start of data */
#define ERASE_CMD 0x50
#define DOWNLOAD_CMD 0x80
#define SIGNATURE_CMD 0x90
#define ACK 0x3E /* ACK*/

#define LED_IO PB04

void LED_init(void)
{
    io_cfg_output(LED_IO);
    io_write_pin(LED_IO, 1);
}
void LED_flicker(void)
{
    io_toggle_pin(LED_IO);
    DELAY_US(500000);
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

uint32_t check_uart_rx()
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
    
    uint16_t len;

    if (uart_buffer[0] != SOD)
        return 0;

    len = uart_buffer[2] * 256 + uart_buffer[3];

    last_checksum = CalcChecksum(uart_buffer + 4, len);

    if (uart_buffer[len + 4] != last_checksum)
        return 0;

    return 1;
}
void System_Reset(void)
{
    // __set_FAULTMASK(1);
    __NVIC_SystemReset();
}
void processCmd()
{
    uint8_t response[2];
    uint8_t cmd;
    uint16_t len;

    cmd = uart_buffer[1];

    if (cmd == ERASE_CMD)
    {
        len = uart_buffer[4] * 256 + uart_buffer[5];
        earse_app_code(uart_buffer + 4, len);
    }
    else if (cmd == DOWNLOAD_CMD)
    {
        len = uart_buffer[2] * 256 + uart_buffer[3];
        write_app_code(uart_buffer + 4, len);
    }
    else if (cmd == SIGNATURE_CMD)
    {
        len = uart_buffer[2] * 256 + uart_buffer[3];
        
        if( sign_app_code(uart_buffer + 4, len))
        {
            response[0] = last_checksum;
            response[1] = ACK;
            uart_send(response, 2);
            DELAY_US(500000);
            System_Reset();
        }
    }
    else
    {
        //无效指令
        return;
    }

    response[0] = last_checksum;
    response[1] = ACK;
    uart_send(response, 2);

}
void show_memu(void)
{
    uart_send_string((uint8_t *)"\r\n***************************************************************");
    uart_send_string((uint8_t *)"\r\n*    LE501X/LM30XX In-Application Programming Application     *");
    uart_send_string((uint8_t *)"\r\n*                                                             *");
    uart_send_string((uint8_t *)"\r\n*                                              (Version 1.0.0)*");
    uart_send_string((uint8_t *)"\r\n***************************************************************");
    uart_send_string((uint8_t *)"\r\n");
    uart_send_string((uint8_t *)"\r\n********************** IAP  functions *************************");
    uart_send_string((uint8_t *)"\r\n*  1.Erase Flash application      -----------------------> 1  *");
    uart_send_string((uint8_t *)"\r\n*  2.Download Flash application   -----------------------> 2  *");
    uart_send_string((uint8_t *)"\r\n*  3.Signature user application   -----------------------> 3  *");
    uart_send_string((uint8_t *)"\r\n***************************************************************");
    uart_send_string((uint8_t *)"\r\n");
}
int main()
{
    uint32_t into_receive_count;

    sys_init_none();

    if (check_application())
    {
        jump_to_app();

        // while (1) ;
    }

    uart_init(PB00, PB01);
    show_memu();

    uart_receive_init();
    ticker_out(&uart_recv_ticker, 0);
    into_receive_count = 0;

    while (1)
    {
        // 100ms
        if (ticker_out(&uart_recv_ticker, 100))
        {
            into_receive_count++;
            ticker_out(&uart_recv_ticker, 0);
            if (check_uart_rx())
            {
                into_receive_count = 5;
                processCmd();
            }
            // 300ms 接收到杂乱数据，清除接收数据
            if (into_receive_count >= 5)
            {
                into_receive_count = 0;
                uart_receive_init();
            }
        }

        // LED_flicker();
    }
}
