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
  QSH_FDCAN_IRQn            = 39,
  QSH_RGMII_IRQn            = 40,
  QSH_EMMC_IRQn             = 41,
  QSH_LTPI_IRQn             = 42,
  QSH_HSE_IRQn              = 43,
  QSH_CRYPT_IRQn            = 44,
  QSH_ECC_IRQn              = 45,
  QSH_SHA_IRQn              = 46,
  QSH_SM4_IRQn              = 47,
  QSH_OTBN_IRQn             = 48,
  QSH_SYSC_OTBN_IRQn        = 49,
  QSH_SYSC_SPID1_IRQn       = 50,
  QSH_SYSC_SPID2_IRQn       = 51,
  
  QSH_SPID1_IRQn            = 54,
  QSH_SPID2_IRQn            = 55,
  QSH_ADTIM1_IRQn           = 56,
  QSH_ADTIM2_IRQn           = 57,
  QSH_GPTIMA1_IRQn          = 58,
  QSH_GPTIMA2_IRQn          = 59,
  QSH_GPTIMB1_IRQn          = 60,
  QSH_GPTIMC1_IRQn          = 61,
  QSH_BSTIM1_IRQn           = 62,
  QSH_BSTIM2_IRQn           = 63,
  QSH_PWM_IRQn              = 64,
  QSH_CAP_IRQn              = 65,
  QSH_I2C1_IRQn             = 66,
  QSH_I2C2_IRQn             = 67,
  QSH_I2C3_IRQn             = 68,
  QSH_I2C4_IRQn             = 69,
  QSH_I2C5_IRQn             = 70,
  QSH_I2C6_IRQn             = 71,
  QSH_I2C7_IRQn             = 72,
  QSH_I2C8_IRQn             = 73,
  QSH_I2C9_IRQn             = 74,
  QSH_I2C10_IRQn            = 75,
  QSH_I2C11_IRQn            = 76,
  QSH_I2C12_IRQn            = 77,
  QSH_I2C13_IRQn            = 78,
  QSH_I2C14_IRQn            = 79,
  QSH_I3C1_IRQn             = 80,
  QSH_I3C2_IRQn             = 81,
  QSH_I3C3_IRQn             = 80,
  QSH_I3C4_IRQn             = 83,
  QSH_I3C5_IRQn             = 80,
  QSH_I3C6_IRQn             = 85,
  QSH_I3C7_IRQn             = 86,
  QSH_I3C8_IRQn             = 87,
  QSH_I3C9_IRQn             = 88,
  QSH_I3C10_IRQn            = 89,
  QSH_I3C11_IRQn            = 90,
  QSH_I3C12_IRQn            = 91,
  QSH_I3C13_IRQn            = 92,
  QSH_I3C14_IRQn            = 93,
  QSH_UART1_IRQn            = 94,
  QSH_UART2_IRQn            = 95,
  QSH_DWUART1_IRQn          = 96,
  QSH_DWUART2_IRQn          = 97,
  QSH_DWUART3_IRQn          = 98,
  QSH_DWUART4_IRQn          = 99,
  QSH_SPI1_IRQn             = 100,
  QSH_SPI2_IRQn             = 101,
  QSH_SPI3_IRQn             = 102,
  QSH_SPI4_IRQn             = 103,
  QSH_SPIS1_IRQn            = 104,
  QSH_SPIS2_IRQn            = 105,
  QSH_ADC1_IRQn             = 106,
  QSH_ADC2_IRQn             = 107,
  QSH_ADC3_IRQn             = 108,
  QSH_EXTI1_IRQn            = 109,
  QSH_EXTI2_IRQn            = 110,
  QSH_EXTI3_IRQn            = 111,
  QSH_EXTI4_IRQn            = 112,
  QSH_IWDT1_IRQn            = 113,
  QSH_IWDT2_IRQn            = 114,
  QSH_WWDT1_IRQn            = 115,
  QSH_WWDT2_IRQn            = 116,
  QSH_SPIM1_IRQn            = 117,
  QSH_SPIM2_IRQn            = 118,
  QSH_SMBF1_IRQn            = 119,
  QSH_SMBF2_IRQn            = 120,
  QSH_SMBF3_IRQn            = 121,
  QSH_SMBF4_IRQn            = 122,
  QSH_MJTAG1_IRQn           = 123,
  QSH_MJTAG2_IRQn           = 124,
  QSH_MJTAG3_IRQn           = 125,
  QSH_SGPIO_MST_IRQn        = 126,
  QSH_PS2IF1_IRQn           = 127,
  QSH_PS2IF2_IRQn           = 128,
  QSH_OWM_IRQn              = 129,
  QSH_CEC_IRQn              = 130,
  QSH_KSCAN_IRQn            = 131,
  QSH_PECI_IRQn             = 132,
  QSH_TRNG_IRQn             = 133,
  QSH_PDM_IRQn              = 134,
  QSH_FILTER_IRQn           = 135,
  QSH_SCAL_IRQn             = 136,
  QSH_GPIO_MON_IRQn         = 137,

  IRQn_MAX,
} IRQn_Type;

#ifdef __cplusplus
}
#endif



#endif