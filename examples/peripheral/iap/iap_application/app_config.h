#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_


#define SDK_HSE_USED (1)
#define SDK_HCLK_MHZ (16)

#if defined(LE501X)
#define APP_CONFIG_ADDR_BASE     0x18008000     //0x18000000 + 0x2000 + 0x6000
#define APP_DATA_ADDR_BASE       0x18009000     //0x18000000 + 0x2000 + 0x7000
#else
#define APP_CONFIG_ADDR_BASE     0x4000         //0x00800000 + 0x4000
#define APP_DATA_ADDR_BASE       0x5000         //0x00800000 + 0x5000
#endif


#endif
