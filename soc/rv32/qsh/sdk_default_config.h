#ifndef SDK_DEFAULT_CONFIG_H_
#define SDK_DEFAULT_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SDK_HSE_USED
#define SDK_HSE_USED (0)
#endif

#ifndef SDK_HSE_MHZ
#define SDK_HSE_MHZ (16)
#endif

#if SDK_HSE_MHZ>24
#error "The Supported HSE Max Freq is 24MHz"
#endif

#ifndef SDK_LSI_USED
#define SDK_LSI_USED (1)
#endif

#ifndef SDK_HCLK_MHZ
#define SDK_HCLK_MHZ (50)
#endif

#ifndef SDK_PCLK_DIV
#define SDK_PCLK_DIV (1)
#endif

#ifndef SDK_LCLK_HZ
#define SDK_LCLK_HZ (32768)
#endif

#ifndef LOG_UART_TXD
#define LOG_UART_TXD (PA11)
#endif
#ifndef LOG_UART_RXD
#define LOG_UART_RXD (PA12)
#endif
#ifndef LOG_UART_BAUDRATE
#define LOG_UART_BAUDRATE UART_BAUDRATE_115200
#endif
#ifndef LOG_UART_WORDLENGTH
#define LOG_UART_WORDLENGTH UART_BYTESIZE8
#endif
#ifndef LOG_UART_STOPBITS
#define LOG_UART_STOPBITS UART_STOPBITS1
#endif
#ifndef LOG_UART_PARITY
#define LOG_UART_PARITY UART_NOPARITY
#endif
#ifndef LOG_UART_MSBEN
#define LOG_UART_MSBEN 0
#endif


#define SDK_PCLK_MHZ (SDK_HCLK_MHZ/SDK_PCLK_DIV)


#define DMACV3 1

#ifdef __cplusplus
}
#endif

#endif

