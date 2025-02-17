#include <stdio.h>
#include "log.h"
#include "mini-printf.h"
#include "SEGGER_RTT.h"
#include "ls_hal_uart.h"
#include "ls_soc_gpio.h"
#include "sdk_config.h"
#include "cpu.h"
#if __riscv
#include "semihosting.h"
#endif

#define JLINK_RTT 1
#define UART_LOG 2
#define RAM_LOG 4
#define SEMIHOSTING 8

#ifndef LOG_BACKEND
#if __arm__ || __ICCARM__
#define LOG_BACKEND (JLINK_RTT)
#elif __riscv
// #define LOG_BACKEND (UART_LOG|RAM_LOG)
// #define LOG_BACKEND (RAM_LOG)
#define LOG_BACKEND (SEMIHOSTING)
#else
#error arch not supported
#endif
#endif
#define RAM_LOG_BUF_SIZE 10000
const uint8_t hex_num_tab[] = "0123456789ABCDEF";
char ram_array[RAM_LOG_BUF_SIZE];
bool log_en;
int count = 0;
__attribute((weak)) void (*log_output_fn)(bool linefeed, const char *format, ...);
__attribute((weak)) void (*log_hex_output_fn)(const void *data_pointer, uint16_t data_length);
void ram_log_print(char *ptr, int len);

#if (LOG_BACKEND&UART_LOG)

#if (LOG_UART_INST == LOG_UART1)
#define LOG_UART  UART1
#define LOG_PINMUX_INIT_FUNC pinmux_uart1_init
#define LOG_PINMUX_DEINIT_FUNC pinmux_uart1_deinit
#define LOG_LL_MSP_INIT_FUNC LL_UART1_MSP_Init
#define LOG_LL_MSP_DEINIT_FUNC LL_UART1_MSP_DeInit

#elif  (LOG_UART_INST == LOG_UART2)
#define LOG_UART  UART2
#define LOG_PINMUX_INIT_FUNC pinmux_uart2_init
#define LOG_PINMUX_DEINIT_FUNC pinmux_uart2_deinit
#define LOG_LL_MSP_INIT_FUNC LL_UART2_MSP_Init
#define LOG_LL_MSP_DEINIT_FUNC LL_UART2_MSP_DeInit

#elif  (LOG_UART_INST == LOG_UART3)
#define LOG_UART  UART3
#define LOG_PINMUX_INIT_FUNC pinmux_uart3_init
#define LOG_PINMUX_DEINIT_FUNC pinmux_uart3_deinit
#define LOG_LL_MSP_INIT_FUNC LL_UART3_MSP_Init
#define LOG_LL_MSP_DEINIT_FUNC LL_UART3_MSP_DeInit
#else
#error "No This Uart Instance..."
#endif

static void uart_log_tx(char *ptr,int len)
{
    while (len)
    {
        if (REG_FIELD_RD(LOG_UART->SR, UART_SR_TFNF))
        {
            len--;
            LOG_UART->TBR = (*ptr++ & (uint8_t)0xFF);
        }
    }
}

static void uart_log_init()
{
    LOG_LL_MSP_INIT_FUNC();
    LOG_PINMUX_INIT_FUNC(LOG_UART_TXD, LOG_UART_RXD);
    
    REG_FIELD_WR(LOG_UART->LCR, UART_LCR_BRWEN, 1);
    LOG_UART->BRR = LOG_UART_BAUDRATE;
    REG_FIELD_WR(LOG_UART->LCR, UART_LCR_BRWEN, 0);
    LOG_UART->FCR = UART_FCR_TFRST_MASK | UART_FCR_RFRST_MASK | UART_FCR_FIFOEN_MASK;
    LOG_UART->LCR = FIELD_BUILD(UART_LCR_DLS, LOG_UART_WORDLENGTH) |
                 FIELD_BUILD(UART_LCR_STOP, LOG_UART_STOPBITS) |
                 FIELD_BUILD(UART_LCR_PARITY, LOG_UART_PARITY) |
                 FIELD_BUILD(UART_LCR_MSB, LOG_UART_MSBEN);
}

void uart_log_pause()
{
    LOG_LL_MSP_DEINIT_FUNC();
    LOG_PINMUX_DEINIT_FUNC();
}

void uart_log_resume()
{
    uart_log_init();
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
        uart_log_tx((char *)&ch,1);
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
        uart_log_tx(ptr,len);
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
        uart_log_tx(ptr,len);
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
        uart_log_init();
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
