#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#if defined(LM3050)
#define SDK_HCLK_MHZ (128)
#define SDK_HSE_USED (1)
#elif defined(LEO)
#define SDK_HCLK_MHZ (16)
#define SDK_HSE_USED (1)
#endif

#define APP_FLASH_ADDR_BASE     0x8000     // 0x00800000 + 0x5000
#define APP_CONFIG_ADDR_BASE    0x8000    // 0x00800000 + 0x5000
#define APP_DATA_ADDR_BASE      0x8100      // 0x00800000 + 0x5100
#define APP_DATA_ADDR_BASE_END  0x80000 // 0x00800000 + 0x80000


#endif
