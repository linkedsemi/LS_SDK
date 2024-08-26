#ifndef QSH_H_
#define QSH_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum IRQn
{
  RV_SOFT_IRQn              = 3,
  RV_TIME_IRQn              = 7,
  RV_EXT_IRQn               = 11,
  
  QSH_PMU_0_IRQn            = 16,
  QSH_PMU_1_IRQn            = 17,
  QSH_PMU_2_IRQn            = 18,
  QSH_PMU_3_IRQn            = 19,
  QSH_PMU_4_IRQn            = 20,
  QSH_PMU_5_IRQn            = 21,
  QSH_SEC_CPU_IRQn          = 26,
  QSH_APP_CPU_IRQn          = 27,
  QSH_USB1_IRQn             = 28,
  QSH_USB2_IRQn             = 29,
  QSH_QSPI1_IRQn            = 30,
  QSH_CACHE1_IRQn           = 31,
  QSH_QSPI2_IRQn            = 32,
  QSH_CACHE2_IRQn           = 33,
  QSH_DMAC1_IRQn            = 34,
  QSH_DMAC2_IRQn            = 35,
  QSH_ESPI1_IRQn            = 36,
  QSH_ESPI2_IRQn            = 37,
  QSH_LPC_IRQn              = 38,
  
  QSH_CRYPT_IRQn            = 44,
  QSH_ECC_IRQn              = 45,
  QSH_SHA_IRQn              = 46,
  QSH_SM4_IRQn              = 47,
  QSH_OTBN_IRQn             = 48,
  
  QSH_UART1_IRQn            = 94,
  QSH_UART2_IRQn            = 95,
  QSH_DWUART1_IRQn          = 96,
  QSH_DWUART2_IRQn          = 97,
  QSH_DWUART3_IRQn          = 98,
  QSH_DWUART4_IRQn          = 99,

  IRQn_MAX,
} IRQn_Type;

#ifdef __cplusplus
}
#endif



#endif
