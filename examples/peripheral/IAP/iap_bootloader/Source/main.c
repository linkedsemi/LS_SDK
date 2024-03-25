#include "ls_hal_uart.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "uart_process.h"
#include "upgrade_process.h"
#include "log.h"
#include <stdio.h>

#if defined(LE501X)
#define LED_IO PA11
#define UART_TX_IO PB00
#define UART_RX_IO PB01
#else
#define LED_IO PB05
#define UART_TX_IO PA09
#define UART_RX_IO PA10
#endif

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
void System_Reset(void)
{
    // __set_FAULTMASK(1);
    __NVIC_SystemReset();
}
uint8_t calc_checksum(const uint8_t *p_data, uint32_t data_size)
{
    uint32_t sum = 0;
    const uint8_t *p_data_end = p_data + data_size;

    while (p_data < p_data_end)
    {
        sum += *p_data++;
    }

    return (sum & 0xffu);
}

bool check_uart_rx()
{
    /* /----------------- IAP Command ------------------------------------------------------------\
     * |     0    |     1       |  2    -   3   |     4    | ... |   n+4   |    n+5    |    n+6   |
     * |------------------------------------------------------------------------------------------|
     * |   START  |   COMMAND   |    LENGTH     |  DATA[0] | ... | DATA[n] | CHECK_SUM |    END   |
     * |------------------------------------------------------------------------------------------|
     * | SOD(3Ch) | 50h/80h/90h |       x       |  data[0] | ... | data[n] |      x    | EOD(3Fh) |
     * \------------------------------------------------------------------------------------------/
     *
     * SOD = 0x3C       (start of data)
     * EOD = 0x3F       (end of data)
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

    if (uart_cmd.uRxFlag != RX_FLAG_COMPLETION)
    {

        return false;
    }

    uart_cmd.uRxFlag = RX_FLAG_PROCESSING;
    uart_cmd.uCmd = uart_cmd.aRxBuff[1];
    uart_cmd.uCmdChecksum = uart_cmd.aRxBuff[uart_cmd.uRxSize - 2];

    switch (uart_cmd.uCmd)
    {
    case ERASE_CMD:
        break;
    case DOWNLOAD_CMD:
        break;
    case SIGNATURE_CMD:
        break;
    default:
        return false;
    }

    if (uart_cmd.uCmdChecksum != calc_checksum(uart_cmd.aRxBuff + 4, uart_cmd.uDataLen))
    {
        return false;
    }

    return true;
}

void processCmd()
{
    uint32_t temp_len;
    uint8_t response[2];
    uint8_t ack = ACK_ERR;

    LOG_HEX(uart_cmd.aRxBuff,uart_cmd.uRxSize);

    //LOG_I(\n");
    //LOG_I(AA");
    //LOG_I(\n");

    if (uart_cmd.uCmd == ERASE_CMD)
    {
        //LOG_I(erase");
        if (earse_app_code())
        {
            ack = ACK_OK;
        }
    }
    else if (uart_cmd.uCmd == DOWNLOAD_CMD)
    {
        temp_len = (((uint32_t)uart_cmd.aRxBuff[4]) << 24) | (((uint32_t)uart_cmd.aRxBuff[5]) << 16) | (((uint32_t)uart_cmd.aRxBuff[6]) << 8) | ((uint32_t)uart_cmd.aRxBuff[7]);
        // //LOG_I(down len:%d", temp_len);
        //LOG_I(111");
        if (write_app_code(uart_cmd.aRxBuff + 8, temp_len))
        {
            ack = ACK_OK;
        }
    }
    else if (uart_cmd.uCmd == SIGNATURE_CMD)
    {
        temp_len = (((uint32_t)uart_cmd.aRxBuff[36]) << 24) | (((uint32_t)uart_cmd.aRxBuff[37]) << 16) | (((uint32_t)uart_cmd.aRxBuff[38]) << 8) | ((uint32_t)uart_cmd.aRxBuff[39]);
        //LOG_I(sign len:%d", temp_len);
        if (sign_app_code(uart_cmd.aRxBuff + 4, temp_len))
        {
            response[0] = uart_cmd.uCmdChecksum;
            response[1] = ACK_OK;
            uart_send(response, 2);
            DELAY_US(500000);
            System_Reset();
        }
    }
    else
    {
        //LOG_I(err cmd");
        //无效指令
    }

    response[0] = uart_cmd.uCmdChecksum;
    response[1] = ack;
    uart_send(response, 2);
    // LOG_HEX(response, 2);
}
void show_memu(void)
{
    uart_send_string((uint8_t *)"\r\n***************************************************************");
    uart_send_string((uint8_t *)"\r\n*             In-Application Programming Application          *");
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
    sys_init_none();
    // LED_init();

    LOG_I("IAP Bootloader start.");
    if (check_application())
    {
        jump_to_app();

        // while (1) ;
    }

    uart_init(UART_TX_IO, UART_RX_IO);

    show_memu();

    uart_receive_init();
    // ticker_out(&uart_recv_ticker, 0);
    while (1)
    {
        // 30ms
        // if (ticker_out(&uart_recv_ticker, 30))
        // {
        //     uart_rx_flag_step = RX_FLAG_HEAD;
        // }
        if (check_uart_rx())
        {
            processCmd();
        }

        // LED_flicker();
    }
}
