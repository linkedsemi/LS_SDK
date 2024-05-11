#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#define SDK_HSE_USED (1)
#define SDK_LSI_USED (1)

#ifdef LM3050
#define SDK_HCLK_MHZ   (128)
#define LOG_UART_TXD PB00
#elif defined(LEO)
#define SDK_HCLK_MHZ   (144)
#define LOG_UART_TXD PB00
#endif

#define TICK_SOURCE_SYSTICK 0
#define TICK_SOURCE_LSTIMER 1
#define LITEOS_TICK_SOURE TICK_SOURCE_LSTIMER

#endif
