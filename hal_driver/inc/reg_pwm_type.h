#ifndef REG_PWM_TYPE_H_
#define REG_PWM_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(CONFIG_PWM_LS_V2)
#define CHAN_CONT 16
#define RESVERED 0
#else
#define CHAN_CONT 8
#define RESVERED 8
#endif

    typedef struct __PWM_PARAM_R
    {
        volatile uint32_t PWM_CYC;
        volatile uint32_t PWM_HIGH;
        volatile uint32_t PWM_NUM;
        volatile uint32_t PWM_Param_Reserve;
    } reg_pwm_param_t;

    typedef struct
    {
        volatile uint32_t PWM_EN;      // 0x00  PWM enable for channel X, high active
        volatile uint32_t PWM_PRE_DIV; // 0x04
        volatile uint32_t PWM_Reserve0[2];
        volatile uint32_t INTR_MSK; // 0x10  interrupt mask, each bit for one interrupt
        volatile uint32_t INTR_CLR;
        volatile uint32_t INTR_STT;
        volatile uint32_t INTR_RAW;
        volatile uint32_t PWM_CTRL[CHAN_CONT + RESVERED]; // 0x20
        volatile reg_pwm_param_t PWM_PARAM[CHAN_CONT + RESVERED]; // 0x60
    } reg_pwm_t;

    enum PWM_REG_PWM_EN_FIELD
    {
        PWM1_ENABLE_MASK = (int)0x1,
        PWM1_ENABLE_POS = 0,
        PWM2_ENABLE_MASK = (int)0x2,
        PWM2_ENABLE_POS = 1,
        PWM3_ENABLE_MASK = (int)0x4,
        PWM3_ENABLE_POS = 2,
        PWM4_ENABLE_MASK = (int)0x8,
        PWM4_ENABLE_POS = 3,
        PWM5_ENABLE_MASK = (int)0x10,
        PWM5_ENABLE_POS = 4,
        PWM6_ENABLE_MASK = (int)0x20,
        PWM6_ENABLE_POS = 5,
        PWM7_ENABLE_MASK = (int)0x40,
        PWM7_ENABLE_POS = 6,
        PWM8_ENABLE_MASK = (int)0x80,
        PWM8_ENABLE_POS = 7,
        PWM1_DISABLE_MASK = (int)0x10000,
        PWM1_DISABLE_POS = 16,
        PWM2_DISABLE_MASK = (int)0x20000,
        PWM2_DISABLE_POS = 17,
        PWM3_DISABLE_MASK = (int)0x40000,
        PWM3_DISABLE_POS = 18,
        PWM4_DISABLE_MASK = (int)0x80000,
        PWM4_DISABLE_POS = 19,
        PWM5_DISABLE_MASK = (int)0x100000,
        PWM5_DISABLE_POS = 20,
        PWM6_DISABLE_MASK = (int)0x200000,
        PWM6_DISABLE_POS = 21,
        PWM7_DISABLE_MASK = (int)0x400000,
        PWM7_DISABLE_POS = 22,
        PWM8_DISABLE_MASK = (int)0x800000,
        PWM8_DISABLE_POS = 23,
    };

    enum PWM_REG_PWM_CTRL_FIELD
    {
        PWM_DMA_EN_MASK = (int)0x1,
        PWM_DMA_EN_POS = 0,
        PWM_MODE_MASK = (int)0x2,
        PWM_MODE_POS = 1,
        PWM_CMP_MASK = (int)0x4,
        PWM_CMP_POS = 2,
        PWM_POL_MASK = (int)0x8,
        PWM_POL_POS = 3,
    };

    enum PWM_REG_INTR_MSK_FIELD
    {
        INTR_PWM1_START_MASK = (int)0x1,
        INTR_PWM1_START_POS = 0,
        INTR_PWM1_END_MASK = (int)0x2,
        INTR_PWM1_END_POS = 1,
        INTR_PWM2_START_MASK = (int)0x4,
        INTR_PWM2_START_POS = 2,
        INTR_PWM2_END_MASK = (int)0x8,
        INTR_PWM2_END_POS = 3,
        INTR_PWM3_START_MASK = (int)0x10,
        INTR_PWM3_START_POS = 4,
        INTR_PWM3_END_MASK = (int)0x20,
        INTR_PWM3_END_POS = 5,
        INTR_PWM4_START_MASK = (int)0x40,
        INTR_PWM4_START_POS = 6,
        INTR_PWM4_END_MASK = (int)0x80,
        INTR_PWM4_END_POS = 7,
        INTR_PWM5_START_MASK = (int)0x100,
        INTR_PWM5_START_POS = 8,
        INTR_PWM5_END_MASK = (int)0x200,
        INTR_PWM5_END_POS = 9,
        INTR_PWM6_START_MASK = (int)0x400,
        INTR_PWM6_START_POS = 10,
        INTR_PWM6_END_MASK = (int)0x800,
        INTR_PWM6_END_POS = 11,
        INTR_PWM7_START_MASK = (int)0x1000,
        INTR_PWM7_START_POS = 12,
        INTR_PWM7_END_MASK = (int)0x2000,
        INTR_PWM7_END_POS = 13,
        INTR_PWM8_START_MASK = (int)0x4000,
        INTR_PWM8_START_POS = 14,
        INTR_PWM8_END_MASK = (int)0x8000,
        INTR_PWM8_END_POS = 15,
    };

    enum PWM_REG_INTR_CLR_FIELD
    {
        INTR_PWM1_START_CLR_MASK = (int)0x1,
        INTR_PWM1_START_CLR_POS = 0,
        INTR_PWM1_END_CLR_MASK = (int)0x2,
        INTR_PWM1_END_CLR_POS = 1,
        INTR_PWM2_START_CLR_MASK = (int)0x4,
        INTR_PWM2_START_CLR_POS = 2,
        INTR_PWM2_END_CLR_MASK = (int)0x8,
        INTR_PWM2_END_CLR_POS = 3,
        INTR_PWM3_START_CLR_MASK = (int)0x10,
        INTR_PWM3_START_CLR_POS = 4,
        INTR_PWM3_END_CLR_MASK = (int)0x20,
        INTR_PWM3_END_CLR_POS = 5,
        INTR_PWM4_START_CLR_MASK = (int)0x40,
        INTR_PWM4_START_CLR_POS = 6,
        INTR_PWM4_END_CLR_MASK = (int)0x80,
        INTR_PWM4_END_CLR_POS = 7,
        INTR_PWM5_START_CLR_MASK = (int)0x100,
        INTR_PWM5_START_CLR_POS = 8,
        INTR_PWM5_END_CLR_MASK = (int)0x200,
        INTR_PWM5_END_CLR_POS = 9,
        INTR_PWM6_START_CLR_MASK = (int)0x400,
        INTR_PWM6_START_CLR_POS = 10,
        INTR_PWM6_END_CLR_MASK = (int)0x800,
        INTR_PWM6_END_CLR_POS = 11,
        INTR_PWM7_START_CLR_MASK = (int)0x1000,
        INTR_PWM7_START_CLR_POS = 12,
        INTR_PWM7_END_CLR_MASK = (int)0x2000,
        INTR_PWM7_END_CLR_POS = 13,
        INTR_PWM8_START_CLR_MASK = (int)0x4000,
        INTR_PWM8_START_CLR_POS = 14,
        INTR_PWM8_END_CLR_MASK = (int)0x8000,
        INTR_PWM8_END_CLR_POS = 15,
    };

    enum PWM_REG_INTR_STT_FIELD
    {
        INTR_PWM1_START_STT_MASK = (int)0x1,
        INTR_PWM1_START_STT_POS = 0,
        INTR_PWM1_END_STT_MASK = (int)0x2,
        INTR_PWM1_END_STT_POS = 1,
        INTR_PWM2_START_STT_MASK = (int)0x4,
        INTR_PWM2_START_STT_POS = 2,
        INTR_PWM2_END_STT_MASK = (int)0x8,
        INTR_PWM2_END_STT_POS = 3,
        INTR_PWM3_START_STT_MASK = (int)0x10,
        INTR_PWM3_START_STT_POS = 4,
        INTR_PWM3_END_STT_MASK = (int)0x20,
        INTR_PWM3_END_STT_POS = 5,
        INTR_PWM4_START_STT_MASK = (int)0x40,
        INTR_PWM4_START_STT_POS = 6,
        INTR_PWM4_END_STT_MASK = (int)0x80,
        INTR_PWM4_END_STT_POS = 7,
        INTR_PWM5_START_STT_MASK = (int)0x100,
        INTR_PWM5_START_STT_POS = 8,
        INTR_PWM5_END_STT_MASK = (int)0x200,
        INTR_PWM5_END_STT_POS = 9,
        INTR_PWM6_START_STT_MASK = (int)0x400,
        INTR_PWM6_START_STT_POS = 10,
        INTR_PWM6_END_STT_MASK = (int)0x800,
        INTR_PWM6_END_STT_POS = 11,
        INTR_PWM7_START_STT_MASK = (int)0x1000,
        INTR_PWM7_START_STT_POS = 12,
        INTR_PWM7_END_STT_MASK = (int)0x2000,
        INTR_PWM7_END_STT_POS = 13,
        INTR_PWM8_START_STT_MASK = (int)0x4000,
        INTR_PWM8_START_STT_POS = 14,
        INTR_PWM8_END_STT_MASK = (int)0x8000,
        INTR_PWM8_END_STT_POS = 15,
    };

#ifdef __cplusplus
}
#endif

#endif /* REG_PWM_TYPE_H_ */
