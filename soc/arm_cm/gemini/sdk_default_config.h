#ifndef SDK_DEFAULT_CONFIG_H_
#define SDK_DEFAULT_CONFIG_H_

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
#define SDK_HCLK_MHZ (24)
#endif

#ifndef SDK_PCLK_DIV
#define SDK_PCLK_DIV (1)
#endif

#ifndef SDK_LCLK_HZ
#define SDK_LCLK_HZ (32768)
#endif

#define SDK_PCLK_MHZ (SDK_HCLK_MHZ/SDK_PCLK_DIV)

#ifndef SDK_SRAM1_PWR_DOWN
#define SDK_SRAM1_PWR_DOWN 0
#endif

#ifndef SDK_SRAM2_PWR_DOWN
#define SDK_SRAM2_PWR_DOWN 0
#endif

#ifndef SDK_SRAM3_PWR_DOWN
#define SDK_SRAM3_PWR_DOWN 0
#endif

#ifndef SDK_SRAM4_PWR_DOWN
#define SDK_SRAM4_PWR_DOWN 0
#endif

#define DMACV2 1

#endif

