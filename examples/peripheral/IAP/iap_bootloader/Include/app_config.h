#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#define SDK_HSE_USED (1)
#define SDK_HCLK_MHZ (16)

#if defined(LE501X)
#define APP_FLASH_ADDR_BASE     0x18007000
#define APP_CONFIG_ADDR_BASE    0x18007000
#define APP_DATA_ADDR_BASE      0x18007100
#define APP_DATA_ADDR_BASE_END  0x1807F000
#elif defined(LM3050)
#define APP_FLASH_ADDR_BASE     0x5000     // 0x00800000 + 0x5000
#define APP_CONFIG_ADDR_BASE    0x5000    // 0x00800000 + 0x5000
#define APP_DATA_ADDR_BASE      0x5100      // 0x00800000 + 0x5100
#define APP_DATA_ADDR_BASE_END  0x80000 // 0x00800000 + 0x80000
#else
#error "error config for chip."
#endif

#endif
