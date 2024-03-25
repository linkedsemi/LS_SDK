#ifndef REG_MDM2_TYPE_H_
#define REG_MDM2_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t REG00; //0x0
    volatile uint32_t REG04; //0x4
    volatile uint32_t REG08; //0x8
    volatile uint32_t REG0C; //0xc
    volatile uint32_t REG10; //0x10
    volatile uint32_t REG14; //0x14
    volatile uint32_t REG18; //0x18
    volatile uint32_t REG1C; //0x1c
    volatile uint32_t REG20; //0x20
}reg_mdm2_t;

enum MDM2_REG_REG00_FIELD
{
    MDM2_RF_CH_NO_MASK = (int)0x3f,
    MDM2_RF_CH_NO_POS = 0,
    MDM2_WHITENING_MASK = (int)0x100,
    MDM2_WHITENING_POS = 8,
    MDM2_CD2_EN_MASK = (int)0x200,
    MDM2_CD2_EN_POS = 9,
    MDM2_CD1_EN_MASK = (int)0x400,
    MDM2_CD1_EN_POS = 10,
    MDM2_SAMPLE_EN_MASK = (int)0x800,
    MDM2_SAMPLE_EN_POS = 11,
    MDM2_CORR_REG_EN_MASK = (int)0x1000,
    MDM2_CORR_REG_EN_POS = 12,
    MDM2_ACC_REG_EN_MASK = (int)0x2000,
    MDM2_ACC_REG_EN_POS = 13,
    MDM2_TX_SEL_MASK = (int)0x10000,
    MDM2_TX_SEL_POS = 16,
    MDM2_RX_SEL_MASK = (int)0x20000,
    MDM2_RX_SEL_POS = 17,
    MDM2_TX_INVERT_MASK = (int)0x40000,
    MDM2_TX_INVERT_POS = 18,
    MDM2_RX_INVERT_MASK = (int)0x80000,
    MDM2_RX_INVERT_POS = 19,
    MDM2_IQ_INVERT_MASK = (int)0x100000,
    MDM2_IQ_INVERT_POS = 20,
    MDM2_ACC_INVERT_MASK = (int)0x200000,
    MDM2_ACC_INVERT_POS = 21,
    MDM2_FILT2_CLK_PH_MASK = (int)0x400000,
    MDM2_FILT2_CLK_PH_POS = 22,
    MDM2_LI_INVERT_MASK = (int)0x800000,
    MDM2_LI_INVERT_POS = 23,
    MDM2_LQ_INVERT_MASK = (int)0x1000000,
    MDM2_LQ_INVERT_POS = 24,
    MDM2_TXCLK_PH_MASK = (int)0x2000000,
    MDM2_TXCLK_PH_POS = 25,
    MDM2_DEBUG_SEL_MASK = (int)0x4000000,
    MDM2_DEBUG_SEL_POS = 26,
    MDM2_DEBUG_MODE_MASK = (int)0x78000000,
    MDM2_DEBUG_MODE_POS = 27,
};

enum MDM2_REG_REG04_FIELD
{
    MDM2_CRC_PRESET_MASK = (int)0xffffff,
    MDM2_CRC_PRESET_POS = 0,
};

enum MDM2_REG_REG08_FIELD
{
    MDM2_MIN_MAG_CONF_MASK = (int)0x7ff,
    MDM2_MIN_MAG_CONF_POS = 0,
    MDM2_DRIFT_COR_SET_MASK = (int)0x3000,
    MDM2_DRIFT_COR_SET_POS = 12,
    MDM2_IF_SHIFT_MASK = (int)0x1fff0000,
    MDM2_IF_SHIFT_POS = 16,
};

enum MDM2_REG_REG0C_FIELD
{
    MDM2_PTH1_MASK = (int)0xff,
    MDM2_PTH1_POS = 0,
    MDM2_PTH2_MASK = (int)0xff00,
    MDM2_PTH2_POS = 8,
    MDM2_PTH3_MASK = (int)0xff0000,
    MDM2_PTH3_POS = 16,
    MDM2_CORR_GAIN_MASK = (int)0xff000000,
    MDM2_CORR_GAIN_POS = 24,
};

enum MDM2_REG_REG10_FIELD
{
    MDM2_CORR_V1_MASK = (int)0xff,
    MDM2_CORR_V1_POS = 0,
    MDM2_CORR_V2_MASK = (int)0xff00,
    MDM2_CORR_V2_POS = 8,
    MDM2_CORR_V3_MASK = (int)0xff0000,
    MDM2_CORR_V3_POS = 16,
    MDM2_CTH_TH_REG_MASK = (int)0xff000000,
    MDM2_CTH_TH_REG_POS = 24,
};

enum MDM2_REG_REG14_FIELD
{
    MDM2_CTH_TH21_MASK = (int)0x3ff,
    MDM2_CTH_TH21_POS = 0,
    MDM2_CTH_TH22_MASK = (int)0xffc00,
    MDM2_CTH_TH22_POS = 10,
    MDM2_CTH_NUM_CFG_MASK = (int)0x300000,
    MDM2_CTH_NUM_CFG_POS = 20,
    MDM2_CTH_TH1_MASK = (int)0xff000000,
    MDM2_CTH_TH1_POS = 24,
};

enum MDM2_REG_REG18_FIELD
{
    MDM2_SAMPLE_TH_MASK = (int)0xff,
    MDM2_SAMPLE_TH_POS = 0,
    MDM2_SAMPLE_NUM_CFG_MASK = (int)0x300,
    MDM2_SAMPLE_NUM_CFG_POS = 8,
    MDM2_CD2_NUM_CFG_MASK = (int)0xc00,
    MDM2_CD2_NUM_CFG_POS = 10,
    MDM2_FDATA_CNT_V_MASK = (int)0xf0000,
    MDM2_FDATA_CNT_V_POS = 16,
    MDM2_RATE_CNT_V_MASK = (int)0xf00000,
    MDM2_RATE_CNT_V_POS = 20,
    MDM2_ACC_TH_MASK = (int)0x7000000,
    MDM2_ACC_TH_POS = 24,
};

enum MDM2_REG_REG1C_FIELD
{
    MDM2_ACCESS_MASK = (int)0xffffffff,
    MDM2_ACCESS_POS = 0,
};

enum MDM2_REG_REG20_FIELD
{
    MDM2_LR_IF_SHIFT_MASK = (int)0x1fff,
    MDM2_LR_IF_SHIFT_POS = 0,
    MDM2_LR_RX_INVERT_MASK = (int)0x2000,
    MDM2_LR_RX_INVERT_POS = 13,
    MDM2_LR_IQ_INVERT_MASK = (int)0x4000,
    MDM2_LR_IQ_INVERT_POS = 14,
    MDM2_LR_ACC_INVERT_MASK = (int)0x8000,
    MDM2_LR_ACC_INVERT_POS = 15,
};
#ifdef __cplusplus
}
#endif

#endif
