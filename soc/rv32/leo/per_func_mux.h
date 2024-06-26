#ifndef PER_FUNC_MUX_H_
#define PER_FUNC_MUX_H_

#ifdef __cplusplus
extern "C" {
#endif

#define FIO_GPTIMA1_CH1     1
#define FIO_GPTIMA1_CH2     2
#define FIO_GPTIMA1_CH3     3
#define FIO_GPTIMA1_CH4     4
#define FIO_GPTIMA1_ETR     5
#define FIO_GPTIMA2_CH1     6
#define FIO_GPTIMA2_CH2     7
#define FIO_GPTIMA2_CH3     8
#define FIO_GPTIMA2_CH4     9
#define FIO_GPTIMA2_ETR     10
#define FIO_GPTIMB1_CH1     11
#define FIO_GPTIMB1_CH2     12
#define FIO_GPTIMB1_CH3     13
#define FIO_GPTIMB1_CH4     14
#define FIO_GPTIMB1_ETR     15
#define FIO_GPTIMC1_CH1     16
#define FIO_GPTIMC1_CH1N    17
#define FIO_GPTIMC1_CH2     18
#define FIO_GPTIMC1_BK      19
#define FIO_ADTIM1_CH1      20
#define FIO_ADTIM1_CH1N     21
#define FIO_ADTIM1_CH2      22
#define FIO_ADTIM1_CH2N     23
#define FIO_ADTIM1_CH3      24
#define FIO_ADTIM1_CH3N     25
#define FIO_ADTIM1_CH4      26
#define FIO_ADTIM1_ETR      27
#define FIO_ADTIM1_BK       28
#define FIO_ADTIM2_CH1      29
#define FIO_ADTIM2_CH1N     30
#define FIO_ADTIM2_CH2      31
#define FIO_ADTIM2_CH2N     32
#define FIO_ADTIM2_CH3      33
#define FIO_ADTIM2_CH3N     34
#define FIO_ADTIM2_CH4      35
#define FIO_ADTIM2_ETR      36
#define FIO_ADTIM2_BK       37
#define FIO_ADTIM3_CH1      38
#define FIO_ADTIM3_CH1N     39
#define FIO_ADTIM3_CH2      40
#define FIO_ADTIM3_CH2N     41
#define FIO_ADTIM3_CH3      42
#define FIO_ADTIM3_CH3N     43
#define FIO_ADTIM3_CH4      44
#define FIO_ADTIM3_ETR      45
#define FIO_ADTIM3_BK       46
#define FIO_ADTIM4_CH1      47
#define FIO_ADTIM4_CH1N     48
#define FIO_ADTIM4_CH2      49
#define FIO_ADTIM4_CH2N     50
#define FIO_ADTIM4_CH3      51
#define FIO_ADTIM4_CH3N     52
#define FIO_ADTIM4_CH4      53
#define FIO_ADTIM4_ETR      54
#define FIO_ADTIM4_BK       55
#define FIO_I2C1_SCL        56
#define FIO_I2C1_SDA        57
#define FIO_I2C1_SMBA       58
#define FIO_I2C2_SCL        59
#define FIO_I2C2_SDA        60
#define FIO_I2C2_SMBA       61
#define FIO_I2C3_SDA        62
#define FIO_I2C3_SCL        63
#define FIO_I2C3_SMBA       64
#define FIO_I2C4_SCL        65
#define FIO_I2C4_SDA        66
#define FIO_I2C4_SMBA       67
#define FIO_I2C5_SCL        68
#define FIO_I2C5_SDA        69
#define FIO_I2C5_SMBA       70
#define FIO_I2C6_SDA        71
#define FIO_I2C6_SCL        72
#define FIO_I2C6_SMBA       73
#define FIO_UART1_TXD       74
#define FIO_UART1_RXD       75
#define FIO_UART1_CTSN      76
#define FIO_UART1_RTSN      77
#define FIO_UART1_CK        78
#define FIO_UART2_TXD       79
#define FIO_UART2_RXD       80
#define FIO_UART2_CTSN      81
#define FIO_UART2_RTSN      82
#define FIO_UART3_TXD       83
#define FIO_UART3_RXD       84
#define FIO_UART3_CTSN      85
#define FIO_UART3_RTSN      86
#define FIO_DWUART1_TXD       87
#define FIO_DWUART1_RXD       88
#define FIO_DWUART1_CTSN      89
#define FIO_DWUART1_RTSN      90
#define FIO_DWUART1_DE        91
#define FIO_DWUART1_RE        92
#define FIO_DWUART2_TXD       93
#define FIO_DWUART2_RXD       94
#define FIO_DWUART2_CTSN      95
#define FIO_DWUART2_RTSN      96
#define FIO_DWUART2_DE        97
#define FIO_DWUART2_RE        98
#define FIO_SPI1_NSS0       99
#define FIO_SPI1_NSS1       100
#define FIO_SPI1_SCK        101
#define FIO_SPI1_DQ0        102
#define FIO_SPI1_DQ1        103
#define FIO_SPI1_DQ2        104
#define FIO_SPI1_DQ3        105
#define FIO_SPI2_SCK        106
#define FIO_SPI2_NSS        107
#define FIO_SPI2_MOSI       108
#define FIO_SPI2_MISO       109
#define FIO_SPI2_I2S        110
#define FIO_SPI3_SCK        111
#define FIO_SPI3_NSS        112
#define FIO_SPI3_MOSI       113
#define FIO_SPI3_MISO       114
#define FIO_SPI3_I2S        115
#define FIO_PDM_CLK         116
#define FIO_PDM_DATA0       117
#define FIO_PDM_DATA1       118
#define FIO_PIS_CH0         119
#define FIO_PIS_CH1         120
#define FIO_FDCAN_TXD       121
#define FIO_FDCAN_RXD       122
#define FIO_USB_DP          123
#define FIO_USB_DM          124
#define FIO_COMP1           125
#define FIO_COMP2           126
#define FIO_COMP3           127
#define FIO_PWM1            128
#define FIO_PWM2            129
#define FIO_PWM3            130
#define FIO_PWM4            131
#define FIO_PWM5            132
#define FIO_PWM6            133
#define FIO_PWM7            134
#define FIO_PWM8            135
#define FIO_CAP1            136
#define FIO_CAP2            137
#define FIO_CAP3            138
#define FIO_CAP4            139
#define FIO_CAP5            140
#define FIO_CAP6            141
#define FIO_CAP7            142
#define FIO_CAP8            143
#define FIO_OWM             144
#define FIO_PS2H1_CLK      145
#define FIO_PS2H1_DAT      146
#define FIO_PS2H2_CLK      147
#define FIO_PS2H2_DAT      148
#define FIO_PS2H3_CLK      149
#define FIO_PS2H3_DAT      150
#define FIO_PS2H4_CLK      151
#define FIO_PS2H4_DAT      152
#define FIO_CEC             153
#define FIO_PECI            154
#define FIO_I2C_DBG_SCL     155
#define FIO_I2C_DBG_SDA     156
#define FIO_USB_CID         163

enum per_func
{
    /* GP TIM A */
    GPTIMA1_CH1 = FIO_GPTIMA1_CH1,
    GPTIMA1_CH2 = FIO_GPTIMA1_CH2,
    GPTIMA1_CH3 = FIO_GPTIMA1_CH3,
    GPTIMA1_CH4 = FIO_GPTIMA1_CH4,
    GPTIMA1_ETR = FIO_GPTIMA1_ETR,
    /* GP TIM B */
    GPTIMB1_CH1 = FIO_GPTIMB1_CH1,
    GPTIMB1_CH2 = FIO_GPTIMB1_CH2,
    GPTIMB1_CH3 = FIO_GPTIMB1_CH3,
    GPTIMB1_CH4 = FIO_GPTIMB1_CH4,
    GPTIMB1_ETR = FIO_GPTIMB1_ETR,
    /* GP TIM C */
    GPTIMC1_CH1 = FIO_GPTIMC1_CH1,
    GPTIMC1_CH1N = FIO_GPTIMC1_CH1N,
    GPTIMC1_CH2 = FIO_GPTIMC1_CH2,
    GPTIMC1_BK  = FIO_GPTIMC1_BK,
    /* AD TIM 1 */
    ADTIM1_CH1  = FIO_ADTIM1_CH1,
    ADTIM1_CH1N = FIO_ADTIM1_CH1N,
    ADTIM1_CH2  = FIO_ADTIM1_CH2,
    ADTIM1_CH2N = FIO_ADTIM1_CH2N,
    ADTIM1_CH3  = FIO_ADTIM1_CH3,
    ADTIM1_CH3N = FIO_ADTIM1_CH3N,
    ADTIM1_CH4  = FIO_ADTIM1_CH4,
    ADTIM1_ETR  = FIO_ADTIM1_ETR,
    ADTIM1_BK   = FIO_ADTIM1_BK,
    /* AD TIM 2 */
    ADTIM2_CH1  = FIO_ADTIM2_CH1,
    ADTIM2_CH1N = FIO_ADTIM2_CH1N,
    ADTIM2_CH2  = FIO_ADTIM2_CH2,
    ADTIM2_CH2N = FIO_ADTIM2_CH2N,
    ADTIM2_CH3  = FIO_ADTIM2_CH3,
    ADTIM2_CH3N = FIO_ADTIM2_CH3N,
    ADTIM2_CH4  = FIO_ADTIM2_CH4,
    ADTIM2_ETR  = FIO_ADTIM2_ETR,
    ADTIM2_BK   = FIO_ADTIM2_BK,
    /* I2C 1 */
    IIC1_SCL    = FIO_I2C1_SCL,
    IIC1_SDA    = FIO_I2C1_SDA,
    IIC1_SMBA   = FIO_I2C1_SMBA,
    /* I2C 2 */
    IIC2_SCL    = FIO_I2C2_SCL,
    IIC2_SDA    = FIO_I2C2_SDA,
    IIC2_SMBA   = FIO_I2C2_SMBA,
    /* I2C 3 */
    IIC3_SDA    = FIO_I2C3_SDA,
    IIC3_SCL    = FIO_I2C3_SCL,
    IIC3_SMBA   = FIO_I2C3_SMBA,
    /* I2C 4 */
    IIC4_SCL    = FIO_I2C4_SCL,
    IIC4_SDA    = FIO_I2C4_SDA,
    IIC4_SMBA   = FIO_I2C4_SMBA,
    /* I2C 5 */
    IIC5_SCL    = FIO_I2C5_SCL,
    IIC5_SDA    = FIO_I2C5_SDA,
    IIC5_SMBA   = FIO_I2C5_SMBA,
    /* I2C 6 */
    IIC6_SDA    = FIO_I2C6_SDA,
    IIC6_SCL    = FIO_I2C6_SCL,
    IIC6_SMBA   = FIO_I2C6_SMBA,
    /* UART 1 */
    UART1_TXD   = FIO_UART1_TXD,
    UART1_RXD   = FIO_UART1_RXD,
    UART1_CTSN  = FIO_UART1_CTSN,
    UART1_RTSN  = FIO_UART1_RTSN,
    UART1_CK    = FIO_UART1_CK,
    /* UART 2 */
    UART2_TXD   = FIO_UART2_TXD,
    UART2_RXD   = FIO_UART2_RXD,
    /* UART 3 */
    UART3_TXD   = FIO_UART3_TXD,
    UART3_RXD   = FIO_UART3_RXD,
    /* UART 4 */
    DWUART1_TXD   = FIO_DWUART1_TXD,
    DWUART1_RXD   = FIO_DWUART1_RXD,
    /* UART 5 */
    DWUART2_TXD   = FIO_DWUART2_TXD,
    DWUART2_RXD   = FIO_DWUART2_RXD,
    /* SPI 1 */
    SPI1_NSS0   = FIO_SPI1_NSS0,
    SPI1_NSS1   = FIO_SPI1_NSS1,
    SPI1_SCK    = FIO_SPI1_SCK,
    SPI1_DQ0    = FIO_SPI1_DQ0,
    SPI1_DQ1    = FIO_SPI1_DQ1,
    SPI1_DQ2    = FIO_SPI1_DQ2,
    SPI1_DQ3    = FIO_SPI1_DQ3,
    /* SPI 2 */
    SPI2_SCK    = FIO_SPI2_SCK,
    SPI2_NSS    = FIO_SPI2_NSS,
    SPI2_MOSI   = FIO_SPI2_MOSI,
    SPI2_MISO   = FIO_SPI2_MISO,
    SPI2_IIS    = FIO_SPI2_I2S,
    /* SPI 3 */
    SPI3_SCK    = FIO_SPI3_SCK,
    SPI3_NSS    = FIO_SPI3_NSS,
    SPI3_MOSI   = FIO_SPI3_MOSI,
    SPI3_MISO   = FIO_SPI3_MISO,
    SPI3_IIS    = FIO_SPI3_I2S,
    /* PDM */
    PDM_CLK     = FIO_PDM_CLK,
    PDM_DATA0   = FIO_PDM_DATA0,
    PDM_DATA1   = FIO_PDM_DATA1,
    /* PIS */
    PIS_CH0     = FIO_PIS_CH0,
    PIS_CH1     = FIO_PIS_CH1,
    /* FDCAN */
    FDCAN_TXD   = FIO_FDCAN_TXD,
    FDCAN_RXD   = FIO_FDCAN_RXD,
    /* USB */
    USB_DP      = FIO_USB_DP,
    USB_DM      = FIO_USB_DM,
    USB_CID      = FIO_USB_CID,
    /* COMPx */
    COMP1       = FIO_COMP1,
    COMP2       = FIO_COMP2,
    COMP3       = FIO_COMP3,

    /* I2C_DBG */
    I2C_DBG_CLK = FIO_I2C_DBG_SCL,
    I2C_DBG_DAT = FIO_I2C_DBG_SDA,

    /* CEC */
    CEC_CH      = FIO_CEC,

    /* PS2 */
    PS2H1_CLK   = FIO_PS2H1_CLK,
    PS2H1_DAT   = FIO_PS2H1_DAT,
    PS2H2_CLK   = FIO_PS2H2_CLK,
    PS2H2_DAT   = FIO_PS2H2_DAT,
    PS2H3_CLK   = FIO_PS2H3_CLK,
    PS2H3_DAT   = FIO_PS2H3_DAT,
    PS2H4_CLK   = FIO_PS2H4_CLK,
    PS2H4_DAT   = FIO_PS2H4_DAT,
    
    /* OWM */
    OWM_CH      = FIO_OWM,

    /* PWM */
    PWM_CH1     = FIO_PWM1,
    PWM_CH2     = FIO_PWM2,
    PWM_CH3     = FIO_PWM3,
    PWM_CH4     = FIO_PWM4,
    PWM_CH5     = FIO_PWM5,
    PWM_CH6     = FIO_PWM6,
    PWM_CH7     = FIO_PWM7,
    PWM_CH8     = FIO_PWM8,

    /* PECI */
    PECI_DAT    = FIO_PECI,

    // RSV07,
    // ANT0,
    // ANT1,
    // ANT2,
    // ANT3,
    // ANT4,
    // ANT5,
    // ANT6,
    // ANT7,
};



#ifdef __cplusplus
}
#endif




#endif
