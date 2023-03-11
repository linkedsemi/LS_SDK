#ifndef DMAC_CONFIG_H_
#define DMAC_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DMAC1_MAX_CHANNEL_NUM 8

typedef enum
{
    CH_UART1_RX = 0,
    CH_UART1_TX = 1,
    CH_UART2_RX = 2,
    CH_UART2_TX = 3,
    CH_UART3_RX = 4,
    CH_UART3_TX = 5,
    CH_SPI1_RX = 8,
    CH_SPI1_TX = 9,
    CH_SPI2_RX = 10,
    CH_SPI2_TX = 11,
    CH_I2C1_RX = 12,
    CH_I2C1_TX = 13,
    CH_I2C2_RX = 14,
    CH_I2C2_TX = 15,
	
    CH_PDMCH0_RX = 17,
	CH_PDMCH1_RX = 18,
    CH_CRYPT_WR = 19,
    CH_CRYPT_RD = 20,
    CH_TRNG = 21,
    CH_ECC = 22,
    CH_ADC = 23,
    CH_LSADTIM1_CH1 = 24,
    CH_LSADTIM1_CH2 = 25,
    CH_LSADTIM1_CH3 = 26,
    CH_LSADTIM1_CH4 = 27,
    CH_LSADTIM1_UP = 28,
    CH_LSADTIM1_TRIG = 29,
    CH_LSADTIM1_COM = 30,
    CH_LSGPTIM2_CH1 = 32,
    CH_LSGPTIM2_CH2 = 33,
    CH_LSGPTIM2_CH3 = 34,
    CH_LSGPTIM2_CH4 = 35,
    CH_LSGPTIM2_UP = 36,
    CH_LSGPTIM2_TRIG = 37,
    CH_LSGPTIM3_CH1 = 40,
    CH_LSGPTIM3_CH2 = 41,
    CH_LSGPTIM3_CH3 = 42,
    CH_LSGPTIM3_CH4 = 43,
    CH_LSGPTIM3_UP = 44,
    CH_LSGPTIM3_TRIG = 45,
    CH_LSGPTIM1_CH1 = 48,
    CH_LSGPTIM1_CH2 = 49,
    CH_LSGPTIM1_UP = 50,
    CH_LSGPTIM1_TRIG = 51,
    CH_LSGPTIM1_COM = 52,
    CH_BSTIM1_UP = 56,
    CH_NONE = 63,
} DMA_ChnSig_TypeDef;

#ifdef __cplusplus
}
#endif

#endif
