#include <stdio.h>
#include "log.h"
#include "SEGGER_RTT.h"
#include "ls_hal_uart.h"
#include "ls_soc_gpio.h"

#define JLINK_RTT           1
#define UART_LOG           2
#define RAM_LOG             4
#ifndef LOG_BACKEND
#if __arm__ || __ICCARM__
#define LOG_BACKEND (JLINK_RTT)
#elif __riscv
#define LOG_BACKEND (0)
#else
#error arch not supported
#endif
#endif

#define LOG_UART_TXD (PB00)
#define LOG_UART_RXD (PB01)

const uint8_t hex_num_tab[] = "0123456789ABCDEF";
__attribute((weak)) void (*log_output_fn)(bool linefeed,const char *format,...);
__attribute((weak)) void (*log_hex_output_fn)(const void * data_pointer , uint16_t data_length);

#if (LOG_BACKEND&UART_LOG)
static UART_HandleTypeDef log_uart;

static void log_uart_tx(char *ptr,int len)
{
    HAL_UART_Transmit(&log_uart,(void *)ptr,(uint16_t)len,1000);
}

static void log_uart_init()
{
    pinmux_uart3_init(LOG_UART_TXD, LOG_UART_RXD);
    HAL_UART_Init(&log_uart);
}

static void log_uart_deinit()
{
    HAL_UART_DeInit(&log_uart);
    pinmux_uart3_deinit();
}

void uart_log_pause()
{
    log_uart_deinit();
}

void uart_log_resume()
{
    log_uart_init();
}
#else
void uart_log_pause(){}
void uart_log_resume(){}
#endif

#if defined(__CC_ARM)
int fputc(int ch, FILE *f)
{
    #if(LOG_BACKEND&JLINK_RTT)
    {
        SEGGER_RTT_PutCharSkip(0, ch);
    }
    #endif
    #if(LOG_BACKEND&UART_LOG)
    {
        log_uart_tx((char *)&ch,1);
    }
    #endif
    #if(LOG_BACKEND&RAM_LOG)
    {
//        ram_log_print(linefeed,format,&args);
    }
    #endif
    return ch;
}

#elif defined(__GNUC__)
#ifndef CONFIG_AOS
int _write (int fd, char *ptr, int len)
{
    #if(LOG_BACKEND&JLINK_RTT)
    {
        SEGGER_RTT_Write(0, ptr, len);
    }
    #endif
    #if(LOG_BACKEND&UART_LOG)
    {
        log_uart_tx(ptr,len);
    }
    #endif
    #if(LOG_BACKEND&RAM_LOG)
    {
//        ram_log_print(linefeed,format,&args);
    }
    #endif
    return len;
}
#endif
#elif defined(__ICCARM__)
int __write (int fd, char *ptr, int len)
{
    #if(LOG_BACKEND&JLINK_RTT)
    {
        SEGGER_RTT_Write(0, ptr, len);
    }
    #endif
    #if(LOG_BACKEND&UART_LOG)
    {
        log_uart_tx(ptr,len);
    }
    #endif
    #if(LOG_BACKEND&RAM_LOG)
    {
//        ram_log_print(linefeed,format,&args);
    }
    #endif
    return len;
}
#endif

void log_output(bool linefeed,const char *format,...)
{
    va_list args;
    va_start(args,format);
    vprintf(format,args);
    va_end(args);
    if(linefeed)
    {
        putchar('\n');
    }
}

void ls_log_init()
{
    log_output_fn = log_output;
    log_hex_output_fn = log_hex_output;
    #if(LOG_BACKEND&JLINK_RTT)
    {
        SEGGER_RTT_Init();
    }
    #endif
    #if(LOG_BACKEND&UART_LOG)
    {
        log_uart.UARTX = UART3;
        log_uart.Init.BaudRate = UART_BAUDRATE_921600;
        log_uart.Init.WordLength = UART_BYTESIZE8;
        log_uart.Init.StopBits = UART_STOPBITS1;
        log_uart.Init.Parity = UART_NOPARITY;
        log_uart.Init.MSBEN = 0;
        log_uart.Init.HwFlowCtl = 0;
        log_uart_init();
    }
    #endif
    #if(LOG_BACKEND&RAM_LOG)
    {

    }
    #endif
}

/**
 ****************************************************************************************
 * @brief  tools for printf to  log data.
 *
 * @param[in]  data_pointer      Pointer to the data to be printf.
 * @param[in]  data_length    The length of data to be printf.
 *
 ****************************************************************************************
 */
void log_hex_output(const void * data_pointer , uint16_t data_length)
{
    
    uint8_t *data = (uint8_t*)data_pointer;
    uint8_t  tmp_h,tmp_l;
    uint32_t total_length = data_length * 2 + 2;
    char  log_format_buff[total_length];
    char *bufptr=log_format_buff;
    //content
    for(uint16_t i=0;i<data_length;i++)
    {
        tmp_h = data[i] >> 4;
        tmp_l = data[i] & 0x0F;
        *bufptr = hex_num_tab[tmp_h];  bufptr++;
        *bufptr = hex_num_tab[tmp_l];  bufptr++;
    }
    *bufptr = '\n'; bufptr ++;
    *bufptr = '\0';
    printf("%s",log_format_buff);
}




