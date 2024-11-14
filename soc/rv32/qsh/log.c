#include <stdio.h>
#include "log.h"
#include "SEGGER_RTT.h"
#include "ls_hal_uart.h"
#include "ls_soc_gpio.h"
#include "sdk_config.h"
#include "cpu.h"
#include "semihosting.h"

#define JLINK_RTT 1
#define UART_LOG 2
#define RAM_LOG 4
#define SEMIHOSTING 8

#ifndef LOG_BACKEND
#define LOG_BACKEND (SEMIHOSTING)
#endif

#define RAM_LOG_BUF_SIZE 10000
const uint8_t hex_num_tab[] = "0123456789ABCDEF";
char ram_array[RAM_LOG_BUF_SIZE];
int count = 0;
__attribute((weak)) void (*log_output_fn)(bool linefeed, const char *format, ...);
__attribute((weak)) void (*log_hex_output_fn)(const void *data_pointer, uint16_t data_length);
void ram_log_print(char *ptr, int len);

#if (LOG_BACKEND&UART_LOG)

static void log_uart_tx(char *ptr,int len)
{
    while (len)
    {
        if (REG_FIELD_RD(UART2->SR, UART_SR_TFNF))
        {
            len--;
            UART2->TBR = (*ptr++ & (uint8_t)0xFF);
        }
    }
}

static void log_uart_init()
{
    pinmux_uart2_init(LOG_UART_TXD, LOG_UART_RXD);
    io_pull_write(LOG_UART_RXD, IO_PULL_UP);
    LL_UART2_MSP_Init();
    REG_FIELD_WR(UART2->LCR, UART_LCR_BRWEN, 1);
    UART2->BRR = LOG_UART_BAUDRATE;
    REG_FIELD_WR(UART2->LCR, UART_LCR_BRWEN, 0);
    UART2->FCR = UART_FCR_TFRST_MASK | UART_FCR_RFRST_MASK | UART_FCR_FIFOEN_MASK;
    UART2->LCR = FIELD_BUILD(UART_LCR_DLS, LOG_UART_WORDLENGTH) |
                 FIELD_BUILD(UART_LCR_STOP, LOG_UART_STOPBITS) |
                 FIELD_BUILD(UART_LCR_PARITY, LOG_UART_PARITY) |
                 FIELD_BUILD(UART_LCR_MSB, LOG_UART_MSBEN);
}

static void log_uart_deinit()
{
    LL_UART2_MSP_DeInit();
    pinmux_uart2_deinit();
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

#if defined(__CC_ARM) || defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)
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
        ram_log_print(ptr,len);
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
        ram_log_print(ptr,len);
    }
    #endif
    #if(LOG_BACKEND&SEMIHOSTING)
    {
        if (get_semihosting_state()){
            semihosting_puts(ptr, len);
        }
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
        ram_log_print(ptr,len);
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
        log_uart_init();
    }
    #endif
    #if(LOG_BACKEND&SEMIHOSTING)
    {
        if (semihosting_enabled()){
		    semihosting_init();
        }
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

void ram_log_print(char *ptr, int len)
{
    for (int j = 0; j < len; j++)
    {
        ram_array[count] = *ptr;
        count++;
        if (count >= RAM_LOG_BUF_SIZE)
        {
            count = 0;
        }
        ptr++;
    }
}