#ifndef QSH_H_
#define QSH_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RV_SOFT_IRQN          3
#define RV_TIME_IRQN          7
#define RV_EXT_IRQN          11
#define PMU_RTC_IRQN         16
#define PMU_WDT_IRQN         17
#define PMU_TIM_IRQN         18
#define PMU_EXT_IRQN         19
#define PMU_LVD_IRQN         20
#define PMU_CASEOPEN_IRQN    21
#define PMU_PASSTHROUGH_IRQN 22

#define SYSC_SEC_CPU_IRQN    26
#define SYSC_APP_CPU_IRQN    27
#define USB1_IRQN            28
#define USB2_IRQN            29
#define QSPI1_IRQN           30
#define QSPI1_CCH_IRQN       31
#define QSPI2_IRQN           32
#define QSPI2_CCH_IRQN       33
#define DMAC1_IRQN           34
#define DMAC2_IRQN           35
#define ESPI1_IRQN           36
#define ESPI2_IRQN           37
#define LPC1_IRQN            38
#define LPC2_IRQN            39
#define ETH1_IRQN            40
#define ETH1_TX_IRQN         41
#define ETH1_RX_IRQN         42
#define ETH2_IRQN            43
#define ETH2_TX_IRQN         44
#define ETH2_RX_IRQN         45
#define EMMC1_IRQN           46
#define EMMC1_WAKEUP_IRQN    47
#define EMMC2_IRQN           48
#define EMMC2_WAKEUP_IRQN    49
#define CALC_CRYPT_IRQN      50
#define CALC_SHA_IRQN        51
#define CALC_SM4_IRQN        52
#define NIST_TRNG_IRQN       53
#define OBTN_IRQN            54
#define OTBN_SYSC_IRQN       55
#define HSE_IRQN             60
#define FDCAN_IRQN           61
#define LTPI_IRQN            62
#define OTP_CTRL_IRQN        63
#define PSRAM_IRQN           64
#define PSRAM_SEC_IRQN       65
#define PSRAM_NSEC_IRQN      66
#define SPI3_IRQN            67
#define SPI4_IRQN            68
#define SPIS1_IRQN           69
#define SPIS2_IRQN           70

#define ADTIM1_IRQN          86
#define ADTIM2_IRQN          87
#define GPTIMA1_IRQN         88
#define GPTIMA2_IRQN         89
#define GPTIMB1_IRQN         90
#define GPTIMC1_IRQN         91
#define BSTIM1_IRQN          92
#define BSTIM2_IRQN          93
#define PWM_IRQN             94
#define CAP_IRQN             95
#define I2C1_IRQN            96
#define I2C2_IRQN            97
#define I2C3_IRQN            98
#define I2C4_IRQN            99
#define I2C5_IRQN            100
#define I2C6_IRQN            101
#define I2C7_IRQN            102
#define I2C8_IRQN            103
#define I2C9_IRQN            104
#define I2C10_IRQN           105
#define I2C11_IRQN           106
#define I2C12_IRQN           107
#define I2C13_IRQN           108
#define I2C14_IRQN           109
#define I2C15_IRQN           110
#define I2C16_IRQN           111
#define I3C1_IRQN            112
#define I3C2_IRQN            113
#define I3C3_IRQN            114
#define I3C4_IRQN            115
#define I3C5_IRQN            116
#define I3C6_IRQN            117
#define I3C7_IRQN            118
#define I3C8_IRQN            119
#define I3C9_IRQN            120
#define I3C10_IRQN           121
#define I3C11_IRQN           122
#define I3C12_IRQN           123
#define I3C13_IRQN           124
#define I3C14_IRQN           125
#define UART1_IRQN           126
#define UART2_IRQN           127
#define UART3_IRQN           128
#define UART4_IRQN           129
#define UART5_IRQN           130
#define UART6_IRQN           131
#define UART7_IRQN           132
#define UART8_IRQN           133
#define UART9_IRQN           134
#define UART10_IRQN          135
#define UART11_IRQN          136
#define UART12_IRQN          137
#define SPI1_IRQN            138
#define SPI2_IRQN            139
#define ADC1_IRQN            140
#define ADC2_IRQN            141
#define PARAL_IRQN           142
#define EXTI1_IRQN           143
#define EXTI2_IRQN           144
#define EXTI3_IRQN           145
#define EXTI4_IRQN           146
#define IWDT1_IRQN           147
#define IWDT2_IRQN           148
#define WWDT1_IRQN           149
#define WWDT2_IRQN           150
#define SGPIO1_MST_IRQN      151
#define SGPIO2_MST_IRQN      152
#define SGPIO1_MON_IRQN      153
#define SGPIO2_MON_IRQN      154
#define MJTAG1_IRQN          159
#define MJTAG2_IRQN          160
#define MJTAG3_IRQN          161
#define PS2IF1_IRQN          163
#define PS2IF2_IRQN          164
#define OWM_IRQN             165
#define CEC_IRQN             166
#define KSCAN_IRQN           167
#define PECI1_IRQN           168
#define PECI2_IRQN           169
#define TRNG_IRQN            170
#define PDM_IRQN             171
#define IRQN_MAX             176

#ifdef __cplusplus
}
#endif

#endif
