#ifndef _UART_PROCESS_H
#define _UART_PROCESS_H

#include "platform.h"

#define BUF_SIZE 320

extern uint8_t uart_buffer[BUF_SIZE];
extern uint16_t uart_buffer_len;

void uart_init(uint8_t txd, uint8_t rxd);
void uart_receive(void);
void uart_send_receive_data(void);
void uart_send(uint8_t *data,uint16_t data_len);
int32_t ticker_out(uint32_t *ticker, uint32_t compare_value);
void uart_receive_init(void);
void uart_send_string(uint8_t *str);
#endif