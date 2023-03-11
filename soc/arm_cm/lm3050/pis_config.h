#ifndef PIS_CONFIG_H_
#define PIS_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/// PIS Source
enum pis_src
{
    COMB_COMP = 0x0,
    COMP0_DAT = 0x1,
    COMP1_DAT = 0x2,
    COMP2_DAT = 0x3,
    ADC0_AWD_UP = 0x4,
    ADC0_AWD_DN = 0x5,
    ADC1_AWD_UP = 0x6,
    ADC1_AWD_DN = 0x7,
    UART1_RXD = 0x8,
    UART2_RXD = 0x9,
    UART3_RXD = 0xa,
    UART4_RXD = 0xb,
    ADTIM1_TRGO = 0xc,
    ADTIM1_ADCTRIG = 0xd,
    ADTIM2_TRGO = 0xe,
    ADTIM2_ADCTRIG = 0xf,
    GPTIMA1_TRGO = 0x10,
    GPTIMA1_ADCTRIG = 0x11,
    GPTIMB1_TRGO = 0x14,
    GPTIMB1_ADCTRIG = 0x15,
    GPTIMC1_TRGO = 0x18,
    GPTIMC1_ADCTRIG = 0x19,
    BSTIM1_TRGO = 0x1c,
    BSTIM1_ADCTRIG = 0x1d,
    CLK_LS = 0x20,
    CLK_HSI_DIV = 0x21,
    CLK_MSI_DIV = 0x22,
    EXTI_DBC_CMP0 = 0x24,
    EXTI_DBC_CMP1 = 0x25,
    EXTI_DBC_CMP2 = 0x26,
    EXTI_DBC_CMP3 = 0x27,
    EXTI_CMP_ADCTRIG0 = 0x28,
    EXTI_CMP_ADCTRIG1 = 0x29,
    EXTI_CMP_ADCTRIG2 = 0x2a,
    EXTI_CMP_ADCTRIG3 = 0x2b,
    EXTI_GPIO_ADCTRIG = 0x2c,
    ADC0_READY = 0x2d,
    ADC1_READY = 0x2e,
    LVD33_INTR = 0x30,
    RTC_INTR = 0x34,
    PIS_SFT0 = 0x38,
    PIS_SFT1 = 0x39,
    PIS_SFT2 = 0x3a,
    PIS_SFT3 = 0x3b,

};

/// PIS Destination
enum pis_dst
{
    ADTIM1_ITR0 = 0x4,
    ADTIM1_ITR1 = 0x5,
    ADTIM1_ITR2 = 0x6,
    ADTIM1_ITR3 = 0x7,
    ADTIM1_CMP_IN0 = 0x8,
    ADTIM1_CMP_IN1 = 0x9,
    ADTIM1_CMP_IN2 = 0xa,
    ADTIM1_CMP_IN3 = 0xb,
    GPTIMA1_ITR0 = 0xc,
    GPTIMA1_ITR1 = 0xd,
    GPTIMA1_ITR2 = 0xe,
    GPTIMA1_ITR3 = 0xf,
    GPTIMB1_ITR0 = 0x10,
    GPTIMB1_ITR1 = 0x11,
    GPTIMB1_ITR2 = 0x12,
    GPTIMB1_ITR3 = 0x13,
    GPTIMC1_ITR0 = 0x14,
    GPTIMC1_ITR1 = 0x15,
    GPTIMC1_ITR2 = 0x16,
    GPTIMC1_ITR3 = 0x17,
    GPTIMC1_CMP_IN0 = 0x18,
    GPTIMC1_CMP_IN1 = 0x19,
    GPTIMC1_CMP_IN2 = 0x1a,
    GPTIMC1_CMP_IN3 = 0x1b,
    ADTIM2_ITR0 = 0x1c,
    ADTIM2_ITR1 = 0x1d,
    ADTIM2_ITR2 = 0x1e,
    ADTIM2_ITR3 = 0x1f,
    ADTIM2_CMP_IN0 = 0x20,
    ADTIM2_CMP_IN1 = 0x21,
    ADTIM2_CMP_IN2 = 0x22,
    ADTIM2_CMP_IN3 = 0x23,
    EXTI_CMP0 = 0x24,
    EXTI_CMP1 = 0x25,
    EXTI_CMP2 = 0x26,
    EXTI_CMP3 = 0x27,
    DAC12_TRIG = 0x28,
    ADC0_REG_TRIG = 0x2c,
    ADC0_INJ_TRIG = 0x2d,
    ADC1_REG_TRIG = 0x2e,
    ADC1_INJ_TRIG = 0x2f,

};

#define PIC_CHANNEL_NUM 8

#ifdef __cplusplus
}
#endif

#endif
