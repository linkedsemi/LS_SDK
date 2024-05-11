#ifndef LEO_H_
#define LEO_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum IRQn
{
  RV_SOFT_IRQn     = 3,
  RV_TIME_IRQn     = 7,
  RV_EXT_IRQn      = 11,
  RTC_IRQn         = 16,
  WDT_IRQn         = 17,
  TIM_IRQn         = 18,
  V33_EXT_IRQn     = 19,
  LVD33_IRQn       = 20,
  COMP_IRQn        = 21,
  USB_IRQn         = 22,
  QSPI_IRQn        = 23,
  CACHE_IRQn       = 24,
  DMAC1_IRQn       = 25,
  DMAC2_IRQn       = 26,
  ESPI_IRQn        = 27,
  LPC_IRQn         = 28,
  BXCAN_IRQn       = 29,
  ECC_IRQn         = 30,
  CALC_SHA_IRQn    = 31,
  CALC_SM4_IRQn    = 32,
  CRYPT_IRQn       = 33,
  BSTIM1_IRQn      = 34,
  GPTIMA1_IRQn     = 35,
  GPTIMA2_IRQn     = 36,
  GPTIMB1_IRQn     = 37,
  GPTIMC1_IRQn     = 38,
  ADTIM1_IRQn      = 39,
  ADTIM2_IRQn      = 40,
  ADTIM3_IRQn      = 41,
  ADTIM4_IRQn      = 42,
  PWM_IRQn         = 43,
  CAP_IRQn         = 44,
  I2C1_IRQn        = 45,
  I2C2_IRQn        = 46,
  I2C3_IRQn        = 47,
  I2C4_IRQn        = 48,
  I2C5_IRQn        = 49,
  I2C6_IRQn        = 50,
  UART1_IRQn       = 51,
  UART2_IRQn       = 52,
  UART3_IRQn       = 53,
  DWUART1_IRQn     = 54,
  DWUART2_IRQn     = 55,
  SPI1_IRQn        = 56,
  SPI2_IRQn        = 57,
  SPI3_IRQn        = 58,
  SPIS_IRQn        = 59,
  ADC1_IRQn        = 60,
  ADC2_IRQn        = 61,
  PDM_IRQn         = 62,
  EXTI0_IRQn       = 63,
  EXTI1_IRQn       = 64,
  WWDT_IRQn        = 65,
  TK_IRQn          = 66,
  TRNG_IRQn        = 67,
  KSCAN_IRQn       = 68,
  OWM_IRQn         = 69,
  PS2H1_IRQn      = 70,
  PS2H2_IRQn      = 71,
  PS2H3_IRQn      = 72,
  PS2H4_IRQn      = 73,
  CEC_IRQn         = 74,
  PECI_IRQn        = 75,
  FILTER_IRQn      = 76,
  HSE_IRQn         = 77,
  EXTI_ASYNC_IRQn  = 78,
  SFT_IRQn         = 79,
  IRQn_MAX,
}IRQn_Type;

#ifdef __cplusplus
}
#endif



#endif
