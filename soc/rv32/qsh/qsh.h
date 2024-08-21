#ifndef BMC_H_
#define BMC_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum IRQn
{
  RV_SOFT_IRQn              = 3,
  RV_TIME_IRQn              = 7,
  RV_EXT_IRQn               = 11,
  
  BMC_PMU_0_IRQn            = 16,
  BMC_PMU_1_IRQn            = 17,
  BMC_PMU_2_IRQn            = 18,
  BMC_PMU_3_IRQn            = 19,
  BMC_PMU_4_IRQn            = 20,
  BMC_PMU_5_IRQn            = 21,
  BMC_SEC_CPU_IRQn          = 26,
  BMC_APP_CPU_IRQn          = 27,
  BMC_USB1_IRQn             = 28,
  BMC_USB2_IRQn             = 29,
  BMC_QSPI1_IRQn            = 30,
  BMC_CACHE1_IRQn           = 31,
  BMC_QSPI2_IRQn            = 32,
  BMC_CACHE2_IRQn           = 33,
  BMC_DMAC1_IRQn            = 34,
  BMC_DMAC2_IRQn            = 35,
  BMC_ESPI1_IRQn            = 36,
  BMC_ESPI2_IRQn            = 37,
  BMC_LPC_IRQn              = 38,
  
  BMC_CRYPT_IRQn            = 44,
  BMC_ECC_IRQn              = 45,
  BMC_SHA_IRQn              = 46,
  BMC_SM4_IRQn              = 47,
  BMC_OTBN_IRQn             = 48,
  
  BMC_UART1_IRQn            = 94,
  BMC_UART2_IRQn            = 95,
  BMC_DWUART1_IRQn          = 96,
  BMC_DWUART2_IRQn          = 97,
  BMC_DWUART3_IRQn          = 98,
  BMC_DWUART4_IRQn          = 99,

  IRQn_MAX,
} IRQn_Type;

#ifdef __cplusplus
}
#endif



#endif
