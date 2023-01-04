#ifndef REG_ADCV2_TYPE_H_
#define REG_ADCV2_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t ADCH; //0x0
    volatile uint32_t ADR; //0x4
    volatile uint32_t AMIC_CTRL; //0x8
    volatile uint32_t MISC; //0xc
    volatile uint32_t TSMP; //0x10
    volatile uint32_t AWD; //0x14
    volatile uint32_t AWD_H; //0x18
    volatile uint32_t AWD_L; //0x1c
    volatile uint32_t INJ_OFF00; //0x20
    volatile uint32_t INJ_OFF01; //0x24
    volatile uint32_t INJ_OFF02; //0x28
    volatile uint32_t INJ_OFF03; //0x2c
    volatile uint32_t FIF_CTRL0; //0x30
    volatile uint32_t REG_CTRL0; //0x34
    volatile uint32_t REG_CTRL1; //0x38
    volatile uint32_t INJ_CTRL; //0x3c
    volatile uint32_t RSI_CTRL; //0x40
    volatile uint32_t FIF_CTRL1; //0x44
    volatile uint32_t DISC_CTRL; //0x48
    volatile uint32_t MISC_CTRL; //0x4c
    volatile uint32_t TRIG; //0x50
    volatile uint32_t CLK_CFG; //0x54
    volatile uint32_t BYP_CFG; //0x58
    volatile uint32_t CH_CFG; //0x5c
    volatile uint32_t INTR_M; //0x60
    volatile uint32_t INTR_C; //0x64
    volatile uint32_t INTR_S; //0x68
    volatile uint32_t INTR_R; //0x6c
    volatile uint32_t REG_DAT00; //0x70
    volatile uint32_t REG_DAT01; //0x74
    volatile uint32_t REG_DAT02; //0x78
    volatile uint32_t REG_DAT03; //0x7c
    volatile uint32_t REG_DAT04; //0x80
    volatile uint32_t REG_DAT05; //0x84
    volatile uint32_t REG_DAT06; //0x88
    volatile uint32_t REG_DAT07; //0x8c
    volatile uint32_t REG_DAT08; //0x90
    volatile uint32_t REG_DAT09; //0x94
    volatile uint32_t REG_DAT10; //0x98
    volatile uint32_t REG_DAT11; //0x9c
    volatile uint32_t REG_DAT12; //0xa0
    volatile uint32_t RESERVED0[3];
    volatile uint32_t INJ_DAT00; //0xb0
    volatile uint32_t INJ_DAT01; //0xb4
    volatile uint32_t INJ_DAT02; //0xb8
    volatile uint32_t INJ_DAT03; //0xbc
    volatile uint32_t FIF_DAT; //0xc0
    volatile uint32_t FIFO_FLVL; //0xc4
    volatile uint32_t STAT; //0xc8
}reg_adc_t;

enum ADC_REG_ADCH_FIELD
{
    ADC_ADCH_OS_CALV_MASK = (int)0xff000000,
    ADC_ADCH_OS_CALV_POS = 24,
    ADC_ADCH_GE_CALV_MASK = (int)0xff0000,
    ADC_ADCH_GE_CALV_POS = 16,
    ADC_ADCH_TRIM_EN_MASK = (int)0x100,
    ADC_ADCH_TRIM_EN_POS = 8,
};

enum ADC_REG_ADR_FIELD
{
    ADC_ADR_HS_MASK = (int)0x800000,
    ADC_ADR_HS_POS = 23,
    ADC_ADR_EN_INBUF_A_MASK = (int)0x400000,
    ADC_ADR_EN_INBUF_A_POS = 22,
    ADC_ADR_EN_INBUF_B_MASK = (int)0x200000,
    ADC_ADR_EN_INBUF_B_POS = 21,
    ADC_ADR_VREF_TRIM_MASK = (int)0x1f0000,
    ADC_ADR_VREF_TRIM_POS = 16,
    ADC_ADR_VREFBUF_EN_MASK = (int)0x8000,
    ADC_ADR_VREFBUF_EN_POS = 15,
    ADC_ADR_BP_MASK = (int)0x4000,
    ADC_ADR_BP_POS = 14,
    ADC_ADC_MSB_CAL_MASK = (int)0x3000,
    ADC_ADC_MSB_CAL_POS = 12,
    ADC_ADR_G_CAL_MASK = (int)0x800,
    ADC_ADR_G_CAL_POS = 11,
    ADC_ADR_LP_CTL_MASK = (int)0x400,
    ADC_ADR_LP_CTL_POS = 10,
    ADC_ADR_OS_CAL_MASK = (int)0x200,
    ADC_ADR_OS_CAL_POS = 9,
    ADC_ADR_VCM_EN_MASK = (int)0x100,
    ADC_ADR_VCM_EN_POS = 8,
    ADC_ADR_VREF_EN_MASK = (int)0x80,
    ADC_ADR_VREF_EN_POS = 7,
    ADC_ADR_VRSEL_MASK = (int)0x70,
    ADC_ADR_VRSEL_POS = 4,
    ADC_ADC_TEST_MASK = (int)0x8,
    ADC_ADC_TEST_POS = 3,
};

enum ADC_REG_AMIC_CTRL_FIELD
{
    ADC_AMIC_EN_MASK = (int)0x4000,
    ADC_AMIC_EN_POS = 14,
    ADC_AMIC_MUTE_INPGA_MASK = (int)0x2000,
    ADC_AMIC_MUTE_INPGA_POS = 13,
    ADC_AMIC_MBVSEL_MASK = (int)0x1000,
    ADC_AMIC_MBVSEL_POS = 12,
    ADC_AMIC_LV_EN_MASK = (int)0x800,
    ADC_AMIC_LV_EN_POS = 11,
    ADC_AMIC_INMUTE_MASK = (int)0x400,
    ADC_AMIC_INMUTE_POS = 10,
    ADC_AMIC_PGA_VOL_MASK = (int)0x3f0,
    ADC_AMIC_PGA_VOL_POS = 4,
    ADC_AMIC_VMIDSEL_MASK = (int)0xc,
    ADC_AMIC_VMIDSEL_POS = 2,
    ADC_AMIC_IBSEL_MASK = (int)0x3,
    ADC_AMIC_IBSEL_POS = 0,
};

enum ADC_REG_MISC_FIELD
{
    ADC_SMPL_DLY_MASK = (int)0xfff0000,
    ADC_SMPL_DLY_POS = 16,
    ADC_TRIG_DLY_MASK = (int)0x3000,
    ADC_TRIG_DLY_POS = 12,
    ADC_ADC_CONV_OFF_MASK = (int)0x100,
    ADC_ADC_CONV_OFF_POS = 8,
    ADC_FIF_SMPHLD_MASK = (int)0x4,
    ADC_FIF_SMPHLD_POS = 2,
    ADC_INJ_SMPHLD_MASK = (int)0x2,
    ADC_INJ_SMPHLD_POS = 1,
    ADC_REG_SMPHLD_MASK = (int)0x1,
    ADC_REG_SMPHLD_POS = 0,
};

enum ADC_REG_TSMP_FIELD
{
    ADC_TSMP_CTRL_CH11_MASK = (int)0xc00000,
    ADC_TSMP_CTRL_CH11_POS = 22,
    ADC_TSMP_CTRL_CH10_MASK = (int)0x300000,
    ADC_TSMP_CTRL_CH10_POS = 20,
    ADC_TSMP_CTRL_CH9_MASK = (int)0xc0000,
    ADC_TSMP_CTRL_CH9_POS = 18,
    ADC_TSMP_CTRL_CH8_MASK = (int)0x30000,
    ADC_TSMP_CTRL_CH8_POS = 16,
    ADC_TSMP_CTRL_CH7_MASK = (int)0xc000,
    ADC_TSMP_CTRL_CH7_POS = 14,
    ADC_TSMP_CTRL_CH6_MASK = (int)0x3000,
    ADC_TSMP_CTRL_CH6_POS = 12,
    ADC_TSMP_CTRL_CH5_MASK = (int)0xc00,
    ADC_TSMP_CTRL_CH5_POS = 10,
    ADC_TSMP_CTRL_CH4_MASK = (int)0x300,
    ADC_TSMP_CTRL_CH4_POS = 8,
    ADC_TSMP_CTRL_CH3_MASK = (int)0xc0,
    ADC_TSMP_CTRL_CH3_POS = 6,
    ADC_TSMP_CTRL_CH2_MASK = (int)0x30,
    ADC_TSMP_CTRL_CH2_POS = 4,
    ADC_TSMP_CTRL_CH1_MASK = (int)0xc,
    ADC_TSMP_CTRL_CH1_POS = 2,
    ADC_TSMP_CTRL_CH0_MASK = (int)0x3,
    ADC_TSMP_CTRL_CH0_POS = 0,
};

enum ADC_REG_AWD_FIELD
{
    ADC_REG_AWDEN_MASK = (int)0x1000,
    ADC_REG_AWDEN_POS = 12,
    ADC_INJ_AWDEN_MASK = (int)0x100,
    ADC_INJ_AWDEN_POS = 8,
    ADC_AWD_SINGLE_MASK = (int)0x10,
    ADC_AWD_SINGLE_POS = 4,
    ADC_AWD_CHANNEL_MASK = (int)0xf,
    ADC_AWD_CHANNEL_POS = 0,
};

enum ADC_REG_AWD_H_FIELD
{
    ADC_AWD_HVL_MASK = (int)0xfff,
    ADC_AWD_HVL_POS = 0,
};

enum ADC_REG_AWD_L_FIELD
{
    ADC_AWD_LVL_MASK = (int)0xfff,
    ADC_AWD_LVL_POS = 0,
};

enum ADC_REG_INJ_OFF00_FIELD
{
    ADC_INJ_OFFSET0_MASK = (int)0xfff,
    ADC_INJ_OFFSET0_POS = 0,
};

enum ADC_REG_INJ_OFF01_FIELD
{
    ADC_INJ_OFFSET1_MASK = (int)0xfff,
    ADC_INJ_OFFSET1_POS = 0,
};

enum ADC_REG_INJ_OFF02_FIELD
{
    ADC_INJ_OFFSET2_MASK = (int)0xfff,
    ADC_INJ_OFFSET2_POS = 0,
};

enum ADC_REG_INJ_OFF03_FIELD
{
    ADC_INJ_OFFSET3_MASK = (int)0xfff,
    ADC_INJ_OFFSET3_POS = 0,
};

enum ADC_REG_FIF_CTRL0_FIELD
{
    ADC_FIFO_CLR_MASK = (int)0x100000,
    ADC_FIFO_CLR_POS = 20,
    ADC_FIF_SEQLEN_MASK = (int)0x30000,
    ADC_FIF_SEQLEN_POS = 16,
    ADC_FIF_SEQ03_MASK = (int)0xf000,
    ADC_FIF_SEQ03_POS = 12,
    ADC_FIF_SEQ02_MASK = (int)0xf00,
    ADC_FIF_SEQ02_POS = 8,
    ADC_FIF_SEQ01_MASK = (int)0xf0,
    ADC_FIF_SEQ01_POS = 4,
    ADC_FIF_SEQ00_MASK = (int)0xf,
    ADC_FIF_SEQ00_POS = 0,
};

enum ADC_REG_REG_CTRL0_FIELD
{
    ADC_REG_SEQ07_MASK = (int)0xf0000000,
    ADC_REG_SEQ07_POS = 28,
    ADC_REG_SEQ06_MASK = (int)0xf000000,
    ADC_REG_SEQ06_POS = 24,
    ADC_REG_SEQ05_MASK = (int)0xf00000,
    ADC_REG_SEQ05_POS = 20,
    ADC_REG_SEQ04_MASK = (int)0xf0000,
    ADC_REG_SEQ04_POS = 16,
    ADC_REG_SEQ03_MASK = (int)0xf000,
    ADC_REG_SEQ03_POS = 12,
    ADC_REG_SEQ02_MASK = (int)0xf00,
    ADC_REG_SEQ02_POS = 8,
    ADC_REG_SEQ01_MASK = (int)0xf0,
    ADC_REG_SEQ01_POS = 4,
    ADC_REG_SEQ00_MASK = (int)0xf,
    ADC_REG_SEQ00_POS = 0,
};

enum ADC_REG_REG_CTRL1_FIELD
{
    ADC_REG_SEQLEN_MASK = (int)0xf00000,
    ADC_REG_SEQLEN_POS = 20,
    ADC_REG_SEQ11_MASK = (int)0xf000,
    ADC_REG_SEQ11_POS = 12,
    ADC_REG_SEQ10_MASK = (int)0xf00,
    ADC_REG_SEQ10_POS = 8,
    ADC_REG_SEQ09_MASK = (int)0xf0,
    ADC_REG_SEQ09_POS = 4,
    ADC_REG_SEQ08_MASK = (int)0xf,
    ADC_REG_SEQ08_POS = 0,
};

enum ADC_REG_INJ_CTRL_FIELD
{
    ADC_INJ_SEQLEN_MASK = (int)0x30000,
    ADC_INJ_SEQLEN_POS = 16,
    ADC_INJ_SEQ03_MASK = (int)0xf000,
    ADC_INJ_SEQ03_POS = 12,
    ADC_INJ_SEQ02_MASK = (int)0xf00,
    ADC_INJ_SEQ02_POS = 8,
    ADC_INJ_SEQ01_MASK = (int)0xf0,
    ADC_INJ_SEQ01_POS = 4,
    ADC_INJ_SEQ00_MASK = (int)0xf,
    ADC_INJ_SEQ00_POS = 0,
};

enum ADC_REG_RSI_CTRL_FIELD
{
    ADC_RSI_EN_MASK = (int)0x1,
    ADC_RSI_EN_POS = 0,
    ADC_RSI_CH_MASK = (int)0xf0,
    ADC_RSI_CH_POS = 4,
};

enum ADC_REG_FIF_CTRL1_FIELD
{
    ADC_FIF_INTV_MASK = (int)0xffff,
    ADC_FIF_INTV_POS = 0,
};

enum ADC_REG_DISC_CTRL_FIELD
{
    ADC_DISC_NUM_MASK = (int)0xf00,
    ADC_DISC_NUM_POS = 8,
    ADC_INJ_DISCEN_MASK = (int)0x10,
    ADC_INJ_DISCEN_POS = 4,
    ADC_REG_DISCEN_MASK = (int)0x1,
    ADC_REG_DISCEN_POS = 0,
};

enum ADC_REG_MISC_CTRL_FIELD
{
    ADC_ADC_DIV_MASK = (int)0x1ff0000,
    ADC_ADC_DIV_POS = 16,
    ADC_DMA_EN_MASK = (int)0x1000,
    ADC_DMA_EN_POS = 12,
    ADC_DATA_ALIGN_MASK = (int)0x100,
    ADC_DATA_ALIGN_POS = 8,
    ADC_ADC_RES_MASK = (int)0x30,
    ADC_ADC_RES_POS = 4,
    ADC_ADC_EN_MASK = (int)0x1,
    ADC_ADC_EN_POS = 0,
};

enum ADC_REG_TRIG_FIELD
{
    ADC_FIF_TRIG_MASK = (int)0x100,
    ADC_FIF_TRIG_POS = 8,
    ADC_INJ_TRIG_MASK = (int)0x10,
    ADC_INJ_TRIG_POS = 4,
    ADC_REG_TRIG_MASK = (int)0x1,
    ADC_REG_TRIG_POS = 0,
};

enum ADC_REG_CLK_CFG_FIELD
{
    ADC_CLOCK_CFG_CH11_MASK = (int)0xc00000,
    ADC_CLOCK_CFG_CH11_POS = 22,
    ADC_CLOCK_CFG_CH10_MASK = (int)0x300000,
    ADC_CLOCK_CFG_CH10_POS = 20,
    ADC_CLOCK_CFG_CH9_MASK = (int)0xc0000,
    ADC_CLOCK_CFG_CH9_POS = 18,
    ADC_CLOCK_CFG_CH8_MASK = (int)0x30000,
    ADC_CLOCK_CFG_CH8_POS = 16,
    ADC_CLOCK_CFG_CH7_MASK = (int)0xc000,
    ADC_CLOCK_CFG_CH7_POS = 14,
    ADC_CLOCK_CFG_CH6_MASK = (int)0x3000,
    ADC_CLOCK_CFG_CH6_POS = 12,
    ADC_CLOCK_CFG_CH5_MASK = (int)0xc00,
    ADC_CLOCK_CFG_CH5_POS = 10,
    ADC_CLOCK_CFG_CH4_MASK = (int)0x300,
    ADC_CLOCK_CFG_CH4_POS = 8,
    ADC_CLOCK_CFG_CH3_MASK = (int)0xc0,
    ADC_CLOCK_CFG_CH3_POS = 6,
    ADC_CLOCK_CFG_CH2_MASK = (int)0x30,
    ADC_CLOCK_CFG_CH2_POS = 4,
    ADC_CLOCK_CFG_CH1_MASK = (int)0xc,
    ADC_CLOCK_CFG_CH1_POS = 2,
    ADC_CLOCK_CFG_CH0_MASK = (int)0x3,
    ADC_CLOCK_CFG_CH0_POS = 0,

};

enum ADC_REG_BYP_CFG_FIELD
{
    ADC_RES_BYP_CH11_MASK = (int)0x8000000,
    ADC_RES_BYP_CH11_POS = 27,
    ADC_RES_BYP_CH10_MASK = (int)0x4000000,
    ADC_RES_BYP_CH10_POS = 26,
    ADC_RES_BYP_CH9_MASK = (int)0x2000000,
    ADC_RES_BYP_CH9_POS = 25,
    ADC_RES_BYP_CH8_MASK = (int)0x1000000,
    ADC_RES_BYP_CH8_POS = 24,
    ADC_RES_BYP_CH7_MASK = (int)0x800000,
    ADC_RES_BYP_CH7_POS = 23,
    ADC_RES_BYP_CH6_MASK = (int)0x400000,
    ADC_RES_BYP_CH6_POS = 22,
    ADC_RES_BYP_CH5_MASK = (int)0x200000,
    ADC_RES_BYP_CH5_POS = 21,
    ADC_RES_BYP_CH4_MASK = (int)0x100000,
    ADC_RES_BYP_CH4_POS = 20,
    ADC_RES_BYP_CH3_MASK = (int)0x80000,
    ADC_RES_BYP_CH3_POS = 19,
    ADC_RES_BYP_CH2_MASK = (int)0x40000,
    ADC_RES_BYP_CH2_POS = 18,
    ADC_RES_BYP_CH1_MASK = (int)0x20000,
    ADC_RES_BYP_CH1_POS = 17,
    ADC_RES_BYP_CH0_MASK = (int)0x10000,
    ADC_RES_BYP_CH0_POS = 16,
    ADC_BUF_BYP_CH11_MASK = (int)0x800,
    ADC_BUF_BYP_CH11_POS = 11,
    ADC_BUF_BYP_CH10_MASK = (int)0x400,
    ADC_BUF_BYP_CH10_POS = 10,
    ADC_BUF_BYP_CH9_MASK = (int)0x200,
    ADC_BUF_BYP_CH9_POS = 9,
    ADC_BUF_BYP_CH8_MASK = (int)0x100,
    ADC_BUF_BYP_CH8_POS = 8,
    ADC_BUF_BYP_CH7_MASK = (int)0x80,
    ADC_BUF_BYP_CH7_POS = 7,
    ADC_BUF_BYP_CH6_MASK = (int)0x40,
    ADC_BUF_BYP_CH6_POS = 6,
    ADC_BUF_BYP_CH5_MASK = (int)0x20,
    ADC_BUF_BYP_CH5_POS = 5,
    ADC_BUF_BYP_CH4_MASK = (int)0x10,
    ADC_BUF_BYP_CH4_POS = 4,
    ADC_BUF_BYP_CH3_MASK = (int)0x8,
    ADC_BUF_BYP_CH3_POS = 3,
    ADC_BUF_BYP_CH2_MASK = (int)0x4,
    ADC_BUF_BYP_CH2_POS = 2,
    ADC_BUF_BYP_CH1_MASK = (int)0x2,
    ADC_BUF_BYP_CH1_POS = 1,
    ADC_BUF_BYP_CH0_MASK = (int)0x1,
    ADC_BUF_BYP_CH0_POS = 0,

};

enum ADC_REG_CH_CFG_FIELD
{
    ADC_CFG_CH11_MASK = (int)0x8000000,
    ADC_CFG_CH11_POS = 27,
    ADC_CFG_CH10_MASK = (int)0x4000000,
    ADC_CFG_CH10_POS = 26,
    ADC_CFG_CH9_MASK = (int)0x2000000,
    ADC_CFG_CH9_POS = 25,
    ADC_CFG_CH8_MASK = (int)0x1000000,
    ADC_CFG_CH8_POS = 24,
    ADC_CFG_CH7_MASK = (int)0x800000,
    ADC_CFG_CH7_POS = 23,
    ADC_CFG_CH6_MASK = (int)0x400000,
    ADC_CFG_CH6_POS = 22,
    ADC_CFG_CH5_MASK = (int)0x200000,
    ADC_CFG_CH5_POS = 21,
    ADC_CFG_CH4_MASK = (int)0x100000,
    ADC_CFG_CH4_POS = 20,
    ADC_CFG_CH3_MASK = (int)0x80000,
    ADC_CFG_CH3_POS = 19,
    ADC_CFG_CH2_MASK = (int)0x40000,
    ADC_CFG_CH2_POS = 18,
    ADC_CFG_CH1_MASK = (int)0x20000,
    ADC_CFG_CH1_POS = 17,
    ADC_CFG_CH0_MASK = (int)0x10000,
    ADC_CFG_CH0_POS = 16,
    ADC_EN_CH11_MASK = (int)0x800,
    ADC_EN_CH11_POS = 11,
    ADC_EN_CH10_MASK = (int)0x400,
    ADC_EN_CH10_POS = 10,
    ADC_EN_CH9_MASK = (int)0x200,
    ADC_EN_CH9_POS = 9,
    ADC_EN_CH8_MASK = (int)0x100,
    ADC_EN_CH8_POS = 8,
    ADC_EN_CH7_MASK = (int)0x80,
    ADC_EN_CH7_POS = 7,
    ADC_EN_CH6_MASK = (int)0x40,
    ADC_EN_CH6_POS = 6,
    ADC_EN_CH5_MASK = (int)0x20,
    ADC_EN_CH5_POS = 5,
    ADC_EN_CH4_MASK = (int)0x10,
    ADC_EN_CH4_POS = 4,
    ADC_EN_CH3_MASK = (int)0x8,
    ADC_EN_CH3_POS = 3,
    ADC_EN_CH2_MASK = (int)0x4,
    ADC_EN_CH2_POS = 2,
    ADC_EN_CH1_MASK = (int)0x2,
    ADC_EN_CH1_POS = 1,
    ADC_EN_CH0_MASK = (int)0x1,
    ADC_EN_CH0_POS = 0,
};

enum ADC_REG_INTR_FIELD
{
    ADC_INTR_FIF_ERR_MASK = (int)0x100,
    ADC_INTR_FIF_ERR_POS = 8,
    ADC_INTR_INJ_ERR_MASK = (int)0x80,
    ADC_INTR_INJ_ERR_POS = 7,
    ADC_INTR_REG_ERR_MASK = (int)0x40,
    ADC_INTR_REG_ERR_POS = 6,
    ADC_INTR_FIF_OVR_MASK = (int)0x20,
    ADC_INTR_FIF_OVR_POS = 5,
    ADC_INTR_FIF_END_MASK = (int)0x10,
    ADC_INTR_FIF_END_POS = 4,
    ADC_INTR_INJ_END_MASK = (int)0x8,
    ADC_INTR_INJ_END_POS = 3,
    ADC_INTR_REG_END_MASK = (int)0x4,
    ADC_INTR_REG_END_POS = 2,
    ADC_INTR_AWDH_MASK = (int)0x2,
    ADC_INTR_AWDH_POS = 1,
    ADC_INTR_AWDL_MASK = (int)0x1,
    ADC_INTR_AWDL_POS = 0,
};

enum ADC_REG_REG_DAT00_FIELD
{
    ADC_REG_DAT00_MASK = (int)0xffff,
    ADC_REG_DAT00_POS = 0,
};

enum ADC_REG_REG_DAT01_FIELD
{
    ADC_REG_DAT01_MASK = (int)0xffff,
    ADC_REG_DAT01_POS = 0,
};

enum ADC_REG_REG_DAT02_FIELD
{
    ADC_REG_DAT02_MASK = (int)0xffff,
    ADC_REG_DAT02_POS = 0,
};

enum ADC_REG_REG_DAT03_FIELD
{
    ADC_REG_DAT03_MASK = (int)0xffff,
    ADC_REG_DAT03_POS = 0,
};

enum ADC_REG_REG_DAT04_FIELD
{
    ADC_REG_DAT04_MASK = (int)0xffff,
    ADC_REG_DAT04_POS = 0,
};

enum ADC_REG_REG_DAT05_FIELD
{
    ADC_REG_DAT05_MASK = (int)0xffff,
    ADC_REG_DAT05_POS = 0,
};

enum ADC_REG_REG_DAT06_FIELD
{
    ADC_REG_DAT06_MASK = (int)0xffff,
    ADC_REG_DAT06_POS = 0,
};

enum ADC_REG_REG_DAT07_FIELD
{
    ADC_REG_DAT07_MASK = (int)0xffff,
    ADC_REG_DAT07_POS = 0,
};

enum ADC_REG_REG_DAT08_FIELD
{
    ADC_REG_DAT08_MASK = (int)0xffff,
    ADC_REG_DAT08_POS = 0,
};

enum ADC_REG_REG_DAT09_FIELD
{
    ADC_REG_DAT09_MASK = (int)0xffff,
    ADC_REG_DAT09_POS = 0,
};

enum ADC_REG_REG_DAT10_FIELD
{
    ADC_REG_DAT10_MASK = (int)0xffff,
    ADC_REG_DAT10_POS = 0,
};

enum ADC_REG_REG_DAT11_FIELD
{
    ADC_REG_DAT11_MASK = (int)0xffff,
    ADC_REG_DAT11_POS = 0,
};

enum ADC_REG_REG_DAT12_FIELD
{
    ADC_REG_DAT12_MASK = (int)0xffff,
    ADC_REG_DAT12_POS = 0,
};

enum ADC_REG_INJ_DAT00_FIELD
{
    ADC_INJ_DAT00_MASK = (int)0xffff,
    ADC_INJ_DAT00_POS = 0,
};

enum ADC_REG_INJ_DAT01_FIELD
{
    ADC_INJ_DAT01_MASK = (int)0xffff,
    ADC_INJ_DAT01_POS = 0,
};

enum ADC_REG_INJ_DAT02_FIELD
{
    ADC_INJ_DAT02_MASK = (int)0xffff,
    ADC_INJ_DAT02_POS = 0,
};

enum ADC_REG_INJ_DAT03_FIELD
{
    ADC_INJ_DAT03_MASK = (int)0xffff,
    ADC_INJ_DAT03_POS = 0,
};

enum ADC_REG_FIF_DAT_FIELD
{
    ADC_FIF_DAT_MASK = (int)0xffff,
    ADC_FIF_DAT_POS = 0,
};

enum ADC_REG_FIFO_FLVL_FIELD
{
    ADC_FIFO_FLVL_MASK = (int)0xf,
    ADC_FIFO_FLVL_POS = 0,
};

enum ADC_REG_STAT_FIELD
{
    ADC_FSM_MASK = (int)0x3,
    ADC_FSM_POS = 0,
    ADC_CNVT_REQ_MASK = (int)0xf0,
    ADC_CNVT_REQ_POS = 4,
};

#endif

