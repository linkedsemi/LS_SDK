#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#ifdef LM3050
#define SDK_HCLK_MHZ (128)
#define SDK_HSE_USED 1
#elif defined LEO
#define SDK_HCLK_MHZ (144)
#define SDK_HSE_USED 1
#endif

#endif