#ifndef GPIO_MODE_H_
#define GPIO_MODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SET_GPIO_MODE_GPIO 0x00000000u /*!< gpio Mode    */
#define SET_GPIO_MODE_ANALOG 0x00000001u   /*!< Analog Mode  */
#define SET_GPIO_MODE_AF 0x00000002u       /*!< Alternate Function Mode  */
#define SET_GPIO_MODE_TEST 0x00000003u     /*!<  Test Mode        */

enum GPIO_AF
{
    AF_JLINK_SWD = 0x00,
    AF_JLINK_SCK,

    AF_UART1_CK,
    AF_UART1_TXD,
    AF_UART1_RXD,
    AF_UART1_CTSN,
    AF_UART1_RTSN,

    AF_ANT_SW0,

    AF_UART2_TXD,
    AF_UART2_RXD,

    AF_ANT_SW1,
    AF_ANT_SW2,

    AF_PIS_CH0_OUT,
    AF_PIS_CH1_OUT,

    AF_ANT_SW3,
    AF_ANT_SW4,

    AF_I2C1_SCL,
    AF_I2C1_SDA,
    AF_I2C1_SMBA,

    AF_I2C2_SCL,
    AF_I2C2_SDA,

    AF_SPI1_NSS0,
    AF_SPI1_SCK,
    AF_SPI1_DQ0,
    AF_SPI1_DQ1,
    AF_SPI1_DQ2,
    AF_SPI1_DQ3,

    AF_SPI2_SCK,
    AF_SPI2_NSS,
    AF_SPI2_MOSI,
    AF_SPI2_MISO,

    AF_ADTIM1_CH1,

    AF_ADTIM1_CH1N,
    AF_ADTIM1_CH2,
    AF_ADTIM1_CH2N,
    AF_ADTIM1_CH3,
    AF_ADTIM1_CH3N,
    AF_ADTIM1_CH4,
    AF_ADTIM1_ETR,
    AF_ADTIM1_BK,

    AF_GPTIMA1_CH1,
    AF_GPTIMA1_CH2,
    AF_GPTIMA1_CH3,
    AF_GPTIMA1_CH4,
    AF_GPTIMA1_ETR,

    AF_GPTIMB1_CH1,
    AF_GPTIMB1_CH2,
    AF_GPTIMB1_CH3,
    AF_GPTIMB1_CH4,
    AF_GPTIMB1_ETR,

    AF_GPTIMC1_CH1,
    AF_GPTIMC1_CH1N,
    AF_GPTIMC1_CH2,
    AF_GPTIMC1_BK,

    AF_LPTIM_OUT,

    AF_ANT_SW5,

    AF_PDM_CLK,

    AF_UART3_TXD,
    AF_UART3_RXD,

    AF_PDM_DATA0,
    AF_PDM_DATA1,

    AF_ANT_SW6,
    AF_SPI1_NSS1,
    AF_I2S_CLK
};

enum GPIO_ANA_FUNC
{
    ANA_FUNC_DIS = 0,
    ANA_FUNC1,
    ANA_FUNC2
};

#ifdef __cplusplus
}
#endif

#endif
