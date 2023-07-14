#ifndef _UART_PROCESS_H
#define _UART_PROCESS_H

#include "platform.h"
#include "ls_hal_uart.h"

#define SOD 0x3C /*start of data */
#define ERASE_CMD 0x50
#define DOWNLOAD_CMD 0x80
#define SIGNATURE_CMD 0x90
#define ACK_OK 0x3E  /* ACK*/
#define EOD 0x3F     /* end of data */
#define ACK_ERR 0x2E /* ACK*/

#define BUF_SIZE 320

typedef struct
{
    volatile uint8_t uRxFlag;

#define RX_FLAG_HEAD 0x00       // HEAD
#define RX_FLAG_RECEIVING 0x01  // receiving
#define RX_FLAG_COMPLETION 0x02 // completion
#define RX_FLAG_PROCESSING 0x03 // processing

    uint8_t uR;
    uint8_t uCmdChecksum;
    uint8_t uCmd;

    uint16_t uDataLen;

    uint16_t uRxSize;
    uint8_t aRxBuff[BUF_SIZE];

} uart_receive_data_t;

extern uart_receive_data_t uart_cmd;

// extern uint32_t uart_recv_ticker;
// extern uint8_t uart_rx_flag_step;

void uart_init(uint8_t txd, uint8_t rxd);
void uart_receive_init(void);
void uart_send(uint8_t *data, uint16_t data_len);
void uart_send_string(uint8_t *str);

// int32_t ticker_out(uint32_t *ticker, uint32_t compare_value);

#endif