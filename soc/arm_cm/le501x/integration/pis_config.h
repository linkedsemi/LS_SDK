#ifndef PIS_CONFIG_H_
#define PIS_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/// PIS Source
enum pis_src
{
    ADC_AWD_UP = 0x4,
    ADC_AWD_DN = 0x5,
    ADC_READY = 0x6,
    UART1_RXD = 0x8,
    UART2_RXD = 0x9,
    UART3_RXD = 0xa,
    ADTIM1_TRGO = 0xc,
    ADTIM1_ADCTRIG = 0xd,
    GPTIMA1_TRGO = 0x10,
    GPTIMA1_ADCTRIG = 0x11,
    GPTIMB1_TRGO = 0x14,
    GPTIMB1_ADCTRIG = 0x15,
    GPTIMC1_TRGO = 0x18,
    GPTIMC1_ADCTRIG = 0x19,
    BSTIM1_TRGO = 0x1c,
    BSTIM1_ADCTRIG = 0x1d,
    LPTIM_TRGO = 0x20,
    EXTI_DBC_CMP0 = 0x24,
    EXTI_DBC_CMP1 = 0x25,
    EXTI_DBC_CMP2 = 0x26,
    EXTI_DBC_CMP3 = 0x27,
    EXTI_CMP_ADCTRIG0 = 0x28,
    EXTI_CMP_ADCTRIG1 = 0x29,
    EXTI_CMP_ADCTRIG2 = 0x2a,
    EXTI_CMP_ADCTRIG3 = 0x2b,
    EXTI_GPIO_ADCTRIG = 0x2c,
    LVD_CMP = 0x30,
    RTC_TRIG = 0x34,
};

/// PIS Destination
enum pis_dst
{
    ADC_REG_TRIG = 0x1,
    ADC_INJ_TRIG = 0x2,
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
    LPTIM1_ITR0 = 0x1c,
    LPTIM1_ITR1 = 0x1d,
    LPTIM1_ITR2 = 0x1e,
    LPTIM1_ITR3 = 0x1f,    
    LPTIM1_ITR4 = 0x20,
    LPTIM1_ITR5 = 0x21,
    LPTIM1_ITR6 = 0x22,
    LPTIM1_ITR7 = 0x23,   
    EXTI_CMP0 = 0x24,
    EXTI_CMP1 = 0x25,
    EXTI_CMP2 = 0x26,
    EXTI_CMP3 = 0x27,
};

#define PIC_CHANNEL_NUM 8

#ifdef __cplusplus
}
#endif

#endif
