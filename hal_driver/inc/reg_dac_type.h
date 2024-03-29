#ifndef REG_DAC_TYPE_H_
#define REG_DAC_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t DAC_CR; //0x0
    volatile uint32_t DAC_SWTRIGR; //0x4
    volatile uint32_t DAC_DHR12R1; //0x8
    volatile uint32_t DAC_DHR12L1; //0xc
    volatile uint32_t DAC_DHR8R1; //0x10
    volatile uint32_t DAC_DHR12R2; //0x14
    volatile uint32_t DAC_DHR12L2; //0x18
    volatile uint32_t DAC_DHR8R2; //0x1c
    volatile uint32_t DAC_DHR12RD; //0x20
    volatile uint32_t DAC_DHR12LD; //0x24
    volatile uint32_t DAC_DHR8RD; //0x28
    volatile uint32_t DAC_DOR1; //0x2c
    volatile uint32_t DAC_DOR2; //0x30
    volatile uint32_t RESERVED0[3];
    volatile uint32_t DAC_ANA; //0x40
}reg_dac_t;

enum DAC_REG_DAC_CR_FIELD
{
    DAC_DMAEN2_MASK = (int)0x10000000,
    DAC_DMAEN2_POS = 28,
    DAC_MAMP2_MASK = (int)0xf000000,
    DAC_MAMP2_POS = 24,
    DAC_WAVE2_MASK = (int)0xc00000,
    DAC_WAVE2_POS = 22,
    DAC_TSEL2_MASK = (int)0x380000,
    DAC_TSEL2_POS = 19,
    DAC_TEN2_MASK = (int)0x40000,
    DAC_TEN2_POS = 18,
    DAC_BOFF2_MASK = (int)0x20000,
    DAC_BOFF2_POS = 17,
    DAC_EN2_MASK = (int)0x10000,
    DAC_EN2_POS = 16,
    DAC_DMA2N1_MASK = (int)0x1000,
    DAC_DMA2N1_POS = 12,
    DAC_MAMP1_MASK = (int)0xf00,
    DAC_MAMP1_POS = 8,
    DAC_WAVE1_MASK = (int)0xc0,
    DAC_WAVE1_POS = 6,
    DAC_TSEL1_MASK = (int)0x38,
    DAC_TSEL1_POS = 3,
    DAC_TEN1_MASK = (int)0x4,
    DAC_TEN1_POS = 2,
    DAC_BOFF1_MASK = (int)0x2,
    DAC_BOFF1_POS = 1,
    DAC_EN1_MASK = (int)0x1,
    DAC_EN1_POS = 0,
};

enum DAC_REG_DAC_SWTRIGR_FIELD
{
    DAC_SWTRIG2_MASK = (int)0x2,
    DAC_SWTRIG2_POS = 1,
    DAC_SWTRIG1_MASK = (int)0x1,
    DAC_SWTRIG1_POS = 0,
};

enum DAC_REG_DAC_DHR12R1_FIELD
{
    DAC_DACC1DHR_DHR12R1_MASK = (int)0xfff,
    DAC_DACC1DHR_DHR12R1_POS = 0,
};

enum DAC_REG_DAC_DHR12L1_FIELD
{
    DAC_DACC1DHR_DHR12L1_MASK = (int)0xfff0,
    DAC_DACC1DHR_DHR12L1_POS = 4,
};

enum DAC_REG_DAC_DHR8R1_FIELD
{
    DAC_DACC1DHR_DHR8R1_MASK = (int)0xff,
    DAC_DACC1DHR_DHR8R1_POS = 0,
};

enum DAC_REG_DAC_DHR12R2_FIELD
{
    DAC_DACC2DHR_DHR12R2_MASK = (int)0xfff,
    DAC_DACC2DHR_DHR12R2_POS = 0,
};

enum DAC_REG_DAC_DHR12L2_FIELD
{
    DAC_DACC2DHR_DHR12L2_MASK = (int)0xfff0,
    DAC_DACC2DHR_DHR12L2_POS = 4,
};

enum DAC_REG_DAC_DHR8R2_FIELD
{
    DAC_DACC2DHR_DHR8R2_MASK = (int)0xff,
    DAC_DACC2DHR_DHR8R2_POS = 0,
};

enum DAC_REG_DAC_DHR12RD_FIELD
{
    DAC_DACC2DHR_DHR12RD_MASK = (int)0xfff0000,
    DAC_DACC2DHR_DHR12RD_POS = 16,
    DAC_DACC1DHR_DHR12RD_MASK = (int)0xfff,
    DAC_DACC1DHR_DHR12RD_POS = 0,
};

enum DAC_REG_DAC_DHR12LD_FIELD
{
    DAC_DACC2DHR_DHR12LD_MASK = (int)0xfff00000,
    DAC_DACC2DHR_DHR12LD_POS = 20,
    DAC_DACC1DHR_DHR12LD_MASK = (int)0xfff0,
    DAC_DACC1DHR_DHR12LD_POS = 4,
};

enum DAC_REG_DAC_DHR8RD_FIELD
{
    DAC_DACC2DHR_DHR8RD_MASK = (int)0xff00,
    DAC_DACC2DHR_DHR8RD_POS = 8,
    DAC_DACC1DHR_DHR8RD_MASK = (int)0xff,
    DAC_DACC1DHR_DHR8RD_POS = 0,
};

enum DAC_REG_DAC_DOR1_FIELD
{
    DAC_DACC1DOR_MASK = (int)0xfff,
    DAC_DACC1DOR_POS = 0,
};

enum DAC_REG_DAC_DOR2_FIELD
{
    DAC_DACC2DOR_MASK = (int)0xfff,
    DAC_DACC2DOR_POS = 0,
};

enum DAC_REG_DAC_ANA_FIELD
{
    DAC_CH2_CLK_SEL_MASK = (int)0x30000000,
    DAC_CH2_CLK_SEL_POS = 28,
    DAC_VREF_DAC2_TRIM_MASK = (int)0xf800000,
    DAC_VREF_DAC2_TRIM_POS = 23,
    DAC_VCM_DAC2_TRIM_MASK = (int)0x780000,
    DAC_VCM_DAC2_TRIM_POS = 19,
    DAC_GC_DAC2_MASK = (int)0x60000,
    DAC_GC_DAC2_POS = 17,
    DAC_EN_DAC2_MASK = (int)0x10000,
    DAC_EN_DAC2_POS = 16,
    DAC_CH1_CLK_SEL_MASK = (int)0x3000,
    DAC_CH1_CLK_SEL_POS = 12,
    DAC_VREF_DAC1_TRIM_MASK = (int)0xf80,
    DAC_VREF_DAC1_TRIM_POS = 7,
    DAC_VCM_DAC1_TRIM_MASK = (int)0x78,
    DAC_VCM_DAC1_TRIM_POS = 3,
    DAC_GC_DAC1_MASK = (int)0x6,
    DAC_GC_DAC1_POS = 1,
    DAC_EN_DAC1_MASK = (int)0x1,
    DAC_EN_DAC1_POS = 0,
};

#ifdef __cplusplus
}
#endif

#endif