#ifndef REG_RF_TYPE_H_
#define REG_RF_TYPE_H_
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
    volatile uint32_t REG24; //0x24
    volatile uint32_t REG28; //0x28
    volatile uint32_t REG2C; //0x2c
    volatile uint32_t REG30; //0x30
    volatile uint32_t REG34; //0x34
    volatile uint32_t REG38; //0x38
    volatile uint32_t RESERVED0[5];
    volatile uint32_t REG50; //0x50
    volatile uint32_t REG54; //0x54
    volatile uint32_t REG58; //0x58
    volatile uint32_t REG5C; //0x5c
    volatile uint32_t REG60; //0x60
    volatile uint32_t REG64; //0x64
    volatile uint32_t REG68; //0x68
    volatile uint32_t REG6C; //0x6c
    volatile uint32_t REG70; //0x70
}reg_rf_t;

enum RF_REG_REG00_FIELD
{
    RF_EN_LNA_MASK = (int)0x1,
    RF_EN_LNA_POS = 0,
    RF_EN_MIXH_MASK = (int)0x2,
    RF_EN_MIXH_POS = 1,
    RF_EN_MIXL_MASK = (int)0x4,
    RF_EN_MIXL_POS = 2,
    RF_EN_BPF_MASK = (int)0x8,
    RF_EN_BPF_POS = 3,
    RF_EN_LMT_RSSI_MASK = (int)0x10,
    RF_EN_LMT_RSSI_POS = 4,
    RF_EN_ADC_MASK = (int)0x20,
    RF_EN_ADC_POS = 5,
    RF_EN_AGC_MASK = (int)0x40,
    RF_EN_AGC_POS = 6,
    RF_EN_PLL_MASK = (int)0x100,
    RF_EN_PLL_POS = 8,
    RF_EN_PA_MASK = (int)0x200,
    RF_EN_PA_POS = 9,
    RF_EN_PA_STG1_MASK = (int)0x400,
    RF_EN_PA_STG1_POS = 10,
    RF_EN_PA_STG2_MASK = (int)0x800,
    RF_EN_PA_STG2_POS = 11,
    RF_EN_DAC_BLE_MASK = (int)0x1000,
    RF_EN_DAC_BLE_POS = 12,
    RF_EN_DAC_ZB_MASK = (int)0x2000,
    RF_EN_DAC_ZB_POS = 13,
    RF_EN_PAHP_MASK = (int)0x4000,
    RF_EN_PAHP_POS = 14,
    RF_EN_LDO_PAHP_BYPS_MASK = (int)0x8000,
    RF_EN_LDO_PAHP_BYPS_POS = 15,
    RF_EN_LDO_RX_MASK = (int)0x20000,
    RF_EN_LDO_RX_POS = 17,
    RF_EN_LDO_TX_MASK = (int)0x40000,
    RF_EN_LDO_TX_POS = 18,
    RF_EN_LDO_IF_MASK = (int)0x80000,
    RF_EN_LDO_IF_POS = 19,
    RF_EN_LDO_PA_MASK = (int)0x100000,
    RF_EN_LDO_PA_POS = 20,
    RF_EN_LDO_VCO_MASK = (int)0x200000,
    RF_EN_LDO_VCO_POS = 21,
    RF_EN_LDO_PLL_MASK = (int)0x400000,
    RF_EN_LDO_PLL_POS = 22,
    RF_EN_LDO_PAHP_MASK = (int)0x800000,
    RF_EN_LDO_PAHP_POS = 23,
    RF_EN_ADC_DIG_MASK = (int)0x1000000,
    RF_EN_ADC_DIG_POS = 24,
    RF_EN_PLL_SDM_MASK = (int)0x2000000,
    RF_EN_PLL_SDM_POS = 25,
    RF_EN_AGC_PWR_MASK = (int)0x40000000,
    RF_EN_AGC_PWR_POS = 30,
    RF_EN_DAC_DIG_PWR_MASK = (int)0x80000000,
    RF_EN_DAC_DIG_PWR_POS = 31,
};

enum RF_REG_REG04_FIELD
{
    RF_LNA_VB_ADJ_MASK = (int)0x7,
    RF_LNA_VB_ADJ_POS = 0,
    RF_LNA_TANK_TUNE_MASK = (int)0x38,
    RF_LNA_TANK_TUNE_POS = 3,
    RF_LNA_R_ADJ_MASK = (int)0xc0,
    RF_LNA_R_ADJ_POS = 6,
    RF_MIXL_BIAS_CTL_MASK = (int)0x700,
    RF_MIXL_BIAS_CTL_POS = 8,
    RF_MIXL_BIAS_SEL_MASK = (int)0x800,
    RF_MIXL_BIAS_SEL_POS = 11,
    RF_MIXH_BIAS_CTL_MASK = (int)0x7000,
    RF_MIXH_BIAS_CTL_POS = 12,
    RF_MIXH_BIAS_SEL_MASK = (int)0x8000,
    RF_MIXH_BIAS_SEL_POS = 15,
    RF_BPF_CAL_CODE_EXT_MASK = (int)0x3f0000,
    RF_BPF_CAL_CODE_EXT_POS = 16,
    RF_BPF_CAL_CODE_EXT_EN_MASK = (int)0x400000,
    RF_BPF_CAL_CODE_EXT_EN_POS = 22,
    RF_BPF_CAL_EN_MASK = (int)0x800000,
    RF_BPF_CAL_EN_POS = 23,
    RF_EN_LNA_BYPS_MASK = (int)0x1000000,
    RF_EN_LNA_BYPS_POS = 24,
    RF_LNA_GAIN_MASK = (int)0x6000000,
    RF_LNA_GAIN_POS = 25,
    RF_MIXL_GAIN_CTL_MASK = (int)0x8000000,
    RF_MIXL_GAIN_CTL_POS = 27,
    RF_MIXH_GAIN_CTL_MASK = (int)0x10000000,
    RF_MIXH_GAIN_CTL_POS = 28,
    RF_BPF_GAIN_ADJ_MASK = (int)0x60000000,
    RF_BPF_GAIN_ADJ_POS = 29,
    RF_MIX_ENB_CAP_MASK = (int)0x80000000,
    RF_MIX_ENB_CAP_POS = 31,
};

enum RF_REG_REG08_FIELD
{
    RF_LDO_RX_TRIM_MASK = (int)0x700,
    RF_LDO_RX_TRIM_POS = 8,
    RF_LDO_TX_TRIM_MASK = (int)0x3800,
    RF_LDO_TX_TRIM_POS = 11,
    RF_CF_BW12M_ADJ_MASK = (int)0x10000,
    RF_CF_BW12M_ADJ_POS = 16,
    RF_TX_RATE_MASK = (int)0x20000,
    RF_TX_RATE_POS = 17,
    RF_CF_BW08M_ADJ_MASK = (int)0x40000,
    RF_CF_BW08M_ADJ_POS = 18,
    RF_TX_DATA_TST_EN_MASK = (int)0x80000,
    RF_TX_DATA_TST_EN_POS = 19,
    RF_PA_VCAS_RES_ADJ_MASK = (int)0x800000,
    RF_PA_VCAS_RES_ADJ_POS = 23,
    RF_PA_GAIN_MASK = (int)0xf000000,
    RF_PA_GAIN_POS = 24,
    RF_PA_TANK_Q_ADJ_MASK = (int)0x70000000,
    RF_PA_TANK_Q_ADJ_POS = 28,
    RF_EN_PA_IBX2_MASK = (int)0x80000000,
    RF_EN_PA_IBX2_POS = 31,
};

enum RF_REG_REG0C_FIELD
{
    RF_PA_TANK_TUNE_MASK = (int)0x7,
    RF_PA_TANK_TUNE_POS = 0,
    RF_EN_RSSI_Q_MASK = (int)0x40,
    RF_EN_RSSI_Q_POS = 6,
    RF_EN_RSSI_I_MASK = (int)0x80,
    RF_EN_RSSI_I_POS = 7,
    RF_PA_VB1_ADJ_MASK = (int)0xf00,
    RF_PA_VB1_ADJ_POS = 8,
    RF_PA_VB2_ADJ_MASK = (int)0xf000,
    RF_PA_VB2_ADJ_POS = 12,
    RF_PA_PTAT_ADJ_MASK = (int)0x70000,
    RF_PA_PTAT_ADJ_POS = 16,
    RF_EN_PA_IPTAT_MASK = (int)0x80000,
    RF_EN_PA_IPTAT_POS = 19,
    RF_PA_BG_ADJ_MASK = (int)0x700000,
    RF_PA_BG_ADJ_POS = 20,
    RF_EN_PA_IBG_MASK = (int)0x800000,
    RF_EN_PA_IBG_POS = 23,
    RF_PLL_BAND_CAL_SEL_MASK = (int)0x1000000,
    RF_PLL_BAND_CAL_SEL_POS = 24,
    RF_PLL_AFC_FRAC_EN_MASK = (int)0x2000000,
    RF_PLL_AFC_FRAC_EN_POS = 25,
    RF_PLL_AFC_DC_EN_MASK = (int)0x4000000,
    RF_PLL_AFC_DC_EN_POS = 26,
    RF_PLL_VCTRL_EXT_EN_MASK = (int)0x8000000,
    RF_PLL_VCTRL_EXT_EN_POS = 27,
    RF_PLL_DIV_ADJ_MASK = (int)0x30000000,
    RF_PLL_DIV_ADJ_POS = 28,
    RF_PLL_SEL_RTX_BW_MASK = (int)0x40000000,
    RF_PLL_SEL_RTX_BW_POS = 30,
};

enum RF_REG_REG10_FIELD
{
    RF_PLL_DI_S_MASK = (int)0x1f,
    RF_PLL_DI_S_POS = 0,
    RF_PLL_RTX_SEL_MASK = (int)0x20,
    RF_PLL_RTX_SEL_POS = 5,
    RF_PLL_OPEN_EN_MASK = (int)0x40,
    RF_PLL_OPEN_EN_POS = 6,
    RF_PLL_CAL_EN_MASK = (int)0x80,
    RF_PLL_CAL_EN_POS = 7,
    RF_PLL_FREQ_ADJ_EXT_MASK = (int)0x1f00,
    RF_PLL_FREQ_ADJ_EXT_POS = 8,
    RF_PLL_FREQ_EXT_EN_MASK = (int)0x2000,
    RF_PLL_FREQ_EXT_EN_POS = 13,
    RF_PLL_FAST_LOCK_EN_MASK = (int)0x4000,
    RF_PLL_FAST_LOCK_EN_POS = 14,
    RF_PLL_REF_SEL_MASK = (int)0x8000,
    RF_PLL_REF_SEL_POS = 15,
    RF_PLL_VREF_ADJ_MASK = (int)0x70000,
    RF_PLL_VREF_ADJ_POS = 16,
    RF_PLL_FBDIV_PD_BYPS_MASK = (int)0x80000,
    RF_PLL_FBDIV_PD_BYPS_POS = 19,
    RF_PLL_BW_ADJ_MASK = (int)0x700000,
    RF_PLL_BW_ADJ_POS = 20,
    RF_PLL_LOCK_BYPS_MASK = (int)0x800000,
    RF_PLL_LOCK_BYPS_POS = 23,
    RF_PLL_CP_OS_ADJ_MASK = (int)0xf000000,
    RF_PLL_CP_OS_ADJ_POS = 24,
    RF_PLL_CP_OS_EN_MASK = (int)0x10000000,
    RF_PLL_CP_OS_EN_POS = 28,
    RF_PLL_VCO_ADJ_MASK = (int)0xe0000000,
    RF_PLL_VCO_ADJ_POS = 29,
};

enum RF_REG_REG14_FIELD
{
    RF_PLL_FRAC_MASK = (int)0xffffff,
    RF_PLL_FRAC_POS = 0,
    RF_DAC_CAL_DATA_EXT_MASK = (int)0x1000000,
    RF_DAC_CAL_DATA_EXT_POS = 24,
    RF_DAC_CAL_EN_EXT_MASK = (int)0x2000000,
    RF_DAC_CAL_EN_EXT_POS = 25,
    RF_DAC_EXT_EN_MASK = (int)0x4000000,
    RF_DAC_EXT_EN_POS = 26,
    RF_DAC_BLE_DELAY_ADJ_MASK = (int)0xf8000000,
    RF_DAC_BLE_DELAY_ADJ_POS = 27,
};

enum RF_REG_REG18_FIELD
{
    RF_DAC_REFL_ADJ_MASK = (int)0xe0,
    RF_DAC_REFL_ADJ_POS = 5,
    RF_ADC_MUX_SEL_MASK = (int)0x700,
    RF_ADC_MUX_SEL_POS = 8,
    RF_ADC_VREF_ADJ_MASK = (int)0x800,
    RF_ADC_VREF_ADJ_POS = 11,
    RF_ADC_TEST_SEL_MASK = (int)0x3000,
    RF_ADC_TEST_SEL_POS = 12,
    RF_EN_ADC_CNT_MODE_MASK = (int)0x4000,
    RF_EN_ADC_CNT_MODE_POS = 14,
    RF_ADC_START_MASK = (int)0x8000,
    RF_ADC_START_POS = 15,
};

enum RF_REG_REG1C_FIELD
{
    RF_EN_LDO_PLL_BYPS_MASK = (int)0x1,
    RF_EN_LDO_PLL_BYPS_POS = 0,
    RF_EN_LDO_RX_BYPS_MASK = (int)0x2,
    RF_EN_LDO_RX_BYPS_POS = 1,
    RF_EN_LDO_TX_BYPS_MASK = (int)0x4,
    RF_EN_LDO_TX_BYPS_POS = 2,
    RF_EN_LDO_IF_BYPS_MASK = (int)0x8,
    RF_EN_LDO_IF_BYPS_POS = 3,
    RF_EN_LDO_PA_BYPS_MASK = (int)0x10,
    RF_EN_LDO_PA_BYPS_POS = 4,
    RF_EN_LDO_VCO_BYPS_MASK = (int)0x20,
    RF_EN_LDO_VCO_BYPS_POS = 5,
    RF_ADC_REFBUF_LP_MASK = (int)0x40,
    RF_ADC_REFBUF_LP_POS = 6,
    RF_DAC_REFH_ADJ_MASK = (int)0x80,
    RF_DAC_REFH_ADJ_POS = 7,
    RF_PLL_DI_P_MASK = (int)0x1f000000,
    RF_PLL_DI_P_POS = 24,
    RF_PLL_FBDIV_PD_MASK = (int)0x20000000,
    RF_PLL_FBDIV_PD_POS = 29,
    RF_PLL_SDM_TEST_EN_MASK = (int)0x40000000,
    RF_PLL_SDM_TEST_EN_POS = 30,
    RF_PLL_FRAC_INT_MODE_MASK = (int)0x80000000,
    RF_PLL_FRAC_INT_MODE_POS = 31,
};

enum RF_REG_REG20_FIELD
{
    RF_BPF_IADJ_MASK = (int)0x7,
    RF_BPF_IADJ_POS = 0,
    RF_BPF_BW_ADJ_MASK = (int)0x18,
    RF_BPF_BW_ADJ_POS = 3,
    RF_BPF_MODE_SEL_MASK = (int)0x20,
    RF_BPF_MODE_SEL_POS = 5,
    RF_BPF_CENT_ADJ_MASK = (int)0xc0,
    RF_BPF_CENT_ADJ_POS = 6,
    RF_AT0_SEL_MASK = (int)0xf0000,
    RF_AT0_SEL_POS = 16,
    RF_AT1_SEL_MASK = (int)0xf00000,
    RF_AT1_SEL_POS = 20,
};

enum RF_REG_REG24_FIELD
{
    RF_AGC_S00L_MASK = (int)0x3f,
    RF_AGC_S00L_POS = 0,
    RF_AGC_S11_LNA_BYPS_ADJ_MASK = (int)0x40,
    RF_AGC_S11_LNA_BYPS_ADJ_POS = 6,
    RF_AGC_S10_LNA_BYPS_ADJ_MASK = (int)0x80,
    RF_AGC_S10_LNA_BYPS_ADJ_POS = 7,
    RF_AGC_S00H_MASK = (int)0x3f00,
    RF_AGC_S00H_POS = 8,
    RF_AGC_S01_MIX_ADJ_MASK = (int)0xc000,
    RF_AGC_S01_MIX_ADJ_POS = 14,
    RF_AGC_S01H_MASK = (int)0x3f0000,
    RF_AGC_S01H_POS = 16,
    RF_AGC_S10_MIX_ADJ_MASK = (int)0xc00000,
    RF_AGC_S10_MIX_ADJ_POS = 22,
    RF_AGC_S01L_MASK = (int)0x3f000000,
    RF_AGC_S01L_POS = 24,
    RF_AGC_POWER_DET_EN_MASK = (int)0x40000000,
    RF_AGC_POWER_DET_EN_POS = 30,
    RF_AGC_TEST_EN_MASK = (int)0x80000000,
    RF_AGC_TEST_EN_POS = 31,
};

enum RF_REG_REG28_FIELD
{
    RF_AGC_S10L_MASK = (int)0x3f,
    RF_AGC_S10L_POS = 0,
    RF_AGC_S11_LNA_EN_ADJ_MASK = (int)0x40,
    RF_AGC_S11_LNA_EN_ADJ_POS = 6,
    RF_AGC_S10_LNA_EN_ADJ_MASK = (int)0x80,
    RF_AGC_S10_LNA_EN_ADJ_POS = 7,
    RF_AGC_S10_BPF_ADJ_MASK = (int)0x300,
    RF_AGC_S10_BPF_ADJ_POS = 8,
    RF_AGC_T_ADJ_MASK = (int)0xc00,
    RF_AGC_T_ADJ_POS = 10,
    RF_AGC_VH_ADD_ADJ_MASK = (int)0x3000,
    RF_AGC_VH_ADD_ADJ_POS = 12,
    RF_AGC_S01_BPF_ADJ_MASK = (int)0xc000,
    RF_AGC_S01_BPF_ADJ_POS = 14,
    RF_AGC_S11_BPF_ADJ_MASK = (int)0x30000,
    RF_AGC_S11_BPF_ADJ_POS = 16,
    RF_AGC_S00_BPF_ADJ_MASK = (int)0xc0000,
    RF_AGC_S00_BPF_ADJ_POS = 18,
    RF_AGC_S11_MIX_ADJ_MASK = (int)0x300000,
    RF_AGC_S11_MIX_ADJ_POS = 20,
    RF_AGC_S00_MIX_ADJ_MASK = (int)0xc00000,
    RF_AGC_S00_MIX_ADJ_POS = 22,
    RF_AGC_S11_LNA_ADJ_MASK = (int)0x3000000,
    RF_AGC_S11_LNA_ADJ_POS = 24,
    RF_AGC_S10_LNA_ADJ_MASK = (int)0xc000000,
    RF_AGC_S10_LNA_ADJ_POS = 26,
    RF_AGC_S01_LNA_ADJ_MASK = (int)0x30000000,
    RF_AGC_S01_LNA_ADJ_POS = 28,
    RF_AGC_S00_LNA_ADJ_MASK = (int)0xc0000000,
    RF_AGC_S00_LNA_ADJ_POS = 30,
};

enum RF_REG_REG2C_FIELD
{
    RF_PLL_GAIN_CAL_SEL_MASK = (int)0x7,
    RF_PLL_GAIN_CAL_SEL_POS = 0,
    RF_PLL_FBDIV_RST_SEL_MASK = (int)0x8,
    RF_PLL_FBDIV_RST_SEL_POS = 3,
    RF_PLL_FBDIV_RST_EXT_MASK = (int)0x10,
    RF_PLL_FBDIV_RST_EXT_POS = 4,
    RF_PLL_PS_CNT_RST_SEL_MASK = (int)0x20,
    RF_PLL_PS_CNT_RST_SEL_POS = 5,
    RF_AGC_TEST_S_MASK = (int)0xc0,
    RF_AGC_TEST_S_POS = 6,
    RF_PA_MN_TUNE_MASK = (int)0xe000,
    RF_PA_MN_TUNE_POS = 13,
    RF_PLL_GAIN_CAL_TH_MASK = (int)0xff0000,
    RF_PLL_GAIN_CAL_TH_POS = 16,
    RF_PLL_VTXD_EXT_MASK = (int)0x1f000000,
    RF_PLL_VTXD_EXT_POS = 24,
    RF_PLL_VTXD_EXT_EN_MASK = (int)0x20000000,
    RF_PLL_VTXD_EXT_EN_POS = 29,
    RF_PLL_GAIN_CAL_EN_MASK = (int)0x40000000,
    RF_PLL_GAIN_CAL_EN_POS = 30,
    RF_PLL_GAIN_CAL_DC_MASK = (int)0x80000000,
    RF_PLL_GAIN_CAL_DC_POS = 31,
};

enum RF_REG_REG30_FIELD
{
    RF_RSV_MASK = (int)0xff,
    RF_RSV_POS = 0,
    RF_LDO_PA_TRIM_MASK = (int)0x1c00,
    RF_LDO_PA_TRIM_POS = 10,
    RF_EN_LMT_OUTI_EXT_MASK = (int)0x2000,
    RF_EN_LMT_OUTI_EXT_POS = 13,
    RF_EN_LMT_OUTQ_EXT_MASK = (int)0x4000,
    RF_EN_LMT_OUTQ_EXT_POS = 14,
    RF_PAHP_SEL_MASK = (int)0x8000,
    RF_PAHP_SEL_POS = 15,
    RF_LDO_PAHP_TRIM_MASK = (int)0xf0000,
    RF_LDO_PAHP_TRIM_POS = 16,
    RF_EN_AT_MASK = (int)0x8000000,
    RF_EN_AT_POS = 27,
    RF_PAHP_ADJ_MASK = (int)0xf0000000,
    RF_PAHP_ADJ_POS = 28,
};

enum RF_REG_REG34_FIELD
{
    RF_ADC_DATA_RDY_MASK = (int)0x2000,
    RF_ADC_DATA_RDY_POS = 13,
    RF_AGC_STATE1_MASK = (int)0x4000,
    RF_AGC_STATE1_POS = 14,
    RF_AGC_STATE0_MASK = (int)0x8000,
    RF_AGC_STATE0_POS = 15,
    RF_BPF_CAL_DONE_MASK = (int)0x20000,
    RF_BPF_CAL_DONE_POS = 17,
    RF_AGC_STATE_TEST_MASK = (int)0x300000,
    RF_AGC_STATE_TEST_POS = 20,
    RF_ADC_DATA_MASK = (int)0xffc00000,
    RF_ADC_DATA_POS = 22,
};

enum RF_REG_REG38_FIELD
{
    RF_PLL_LOCK_MASK = (int)0x1,
    RF_PLL_LOCK_POS = 0,
    RF_PLL_GAIN_CAL_DONE_MASK = (int)0x2,
    RF_PLL_GAIN_CAL_DONE_POS = 1,
    RF_PLL_BAND_CAL_DONE_MASK = (int)0x4,
    RF_PLL_BAND_CAL_DONE_POS = 2,
    RF_PLL_DAC_ADJ_TEST_MASK = (int)0xf8,
    RF_PLL_DAC_ADJ_TEST_POS = 3,
    RF_PLL_FREQ_ADJ_MASK = (int)0x1f00,
    RF_PLL_FREQ_ADJ_POS = 8,
    RF_PLL_MASH_OOUT_MASK = (int)0xff0000,
    RF_PLL_MASH_OOUT_POS = 16,
    RF_BPF_CAL_CODE_MASK = (int)0x3f000000,
    RF_BPF_CAL_CODE_POS = 24,
};

enum RF_REG_REG50_FIELD
{
    RF_ANA_TEST_EN_MASK = (int)0x1,
    RF_ANA_TEST_EN_POS = 0,
    RF_PLL_AFC_BP_MASK = (int)0x2,
    RF_PLL_AFC_BP_POS = 1,
    RF_PLL_GAIN_BP_MASK = (int)0x4,
    RF_PLL_GAIN_BP_POS = 2,
    RF_PPF_RC_BP_MASK = (int)0x8,
    RF_PPF_RC_BP_POS = 3,
    RF_LDO_TEST_EN_MASK = (int)0x10,
    RF_LDO_TEST_EN_POS = 4,
    RF_RD_CLK_EN_MASK = (int)0x20,
    RF_RD_CLK_EN_POS = 5,
    RF_PLL_TEST_EN_MASK = (int)0x40,
    RF_PLL_TEST_EN_POS = 6,
    RF_CH_SEL_MASK = (int)0x80,
    RF_CH_SEL_POS = 7,
    RF_PA_VB_SEL_MASK = (int)0x100,
    RF_PA_VB_SEL_POS = 8,
    RF_PA_VB_TARGET_MASK = (int)0xf000,
    RF_PA_VB_TARGET_POS = 12,
    RF_LDO_START_CNT_MASK = (int)0xff0000,
    RF_LDO_START_CNT_POS = 16,
    RF_PA_STEP_SET_MASK = (int)0x1f000000,
    RF_PA_STEP_SET_POS = 24,
};

enum RF_REG_REG54_FIELD
{
    RF_AFC_MIN_CNT_MASK = (int)0xff,
    RF_AFC_MIN_CNT_POS = 0,
    RF_AFC_MAX_CNT_MASK = (int)0xff00,
    RF_AFC_MAX_CNT_POS = 8,
    RF_GAIN_MAX_CNT_MASK = (int)0xff0000,
    RF_GAIN_MAX_CNT_POS = 16,
    RF_EN_PLL_CNT_MASK = (int)0xff000000,
    RF_EN_PLL_CNT_POS = 24,
};

enum RF_REG_REG58_FIELD
{
    RF_EN_DAC_CNT_MASK = (int)0xff,
    RF_EN_DAC_CNT_POS = 0,
    RF_PLL_CAL_EN_CNT_MASK = (int)0xff00,
    RF_PLL_CAL_EN_CNT_POS = 8,
    RF_PLL_GAIN_CAL_EN_CNT_MASK = (int)0xff0000,
    RF_PLL_GAIN_CAL_EN_CNT_POS = 16,
    RF_EN_PA_CNT_MASK = (int)0xff000000,
    RF_EN_PA_CNT_POS = 24,
};

enum RF_REG_REG5C_FIELD
{
    RF_EN_PA_STG1_CNT_MASK = (int)0xff,
    RF_EN_PA_STG1_CNT_POS = 0,
    RF_EN_PA_STG2_CNT_MASK = (int)0xff00,
    RF_EN_PA_STG2_CNT_POS = 8,
    RF_PLL_LOCK_CNT_MASK = (int)0xff0000,
    RF_PLL_LOCK_CNT_POS = 16,
    RF_EN_RX_CNT_MASK = (int)0xff000000,
    RF_EN_RX_CNT_POS = 24,
};

enum RF_REG_REG60_FIELD
{
    RF_EN_AGC_CNT_MASK = (int)0xff,
    RF_EN_AGC_CNT_POS = 0,
    RF_TX_START_CNT_MASK = (int)0xff00,
    RF_TX_START_CNT_POS = 8,
    RF_TX_WAIT_CNT_MASK = (int)0xff0000,
    RF_TX_WAIT_CNT_POS = 16,
    RF_RX_START_CNT_MASK = (int)0xff000000,
    RF_RX_START_CNT_POS = 24,
};

enum RF_REG_REG64_FIELD
{
    RF_ADC_MDM_EN_MASK = (int)0x1,
    RF_ADC_MDM_EN_POS = 0,
    RF_LDO_PA_SEL_MASK = (int)0x2,
    RF_LDO_PA_SEL_POS = 1,
    RF_RSSI_OFFSET_MASK = (int)0xff00,
    RF_RSSI_OFFSET_POS = 8,
};

enum RF_REG_REG68_FIELD
{
    RF_AGC_GAIN0_MASK = (int)0xff,
    RF_AGC_GAIN0_POS = 0,
    RF_AGC_GAIN1_MASK = (int)0xff00,
    RF_AGC_GAIN1_POS = 8,
    RF_AGC_GAIN2_MASK = (int)0xff0000,
    RF_AGC_GAIN2_POS = 16,
    RF_AGC_GAIN3_MASK = (int)0xff000000,
    RF_AGC_GAIN3_POS = 24,
};

enum RF_REG_REG6C_FIELD
{
    RF_ADC_MDM_BUSY_MASK = (int)0x1,
    RF_ADC_MDM_BUSY_POS = 0,
    RF_AGC_STATE_MASK = (int)0x30,
    RF_AGC_STATE_POS = 4,
    RF_RSSI_VALUE_MASK = (int)0xff00,
    RF_RSSI_VALUE_POS = 8,
    RF_ADC_RSSI_MASK = (int)0x3ff0000,
    RF_ADC_RSSI_POS = 16,
};

enum RF_REG_REG70_FIELD
{
    RF_INT_VTXD_EXT1_MASK = (int)0x1F,
    RF_INT_VTXD_EXT1_POS = 0,
    RF_INT_VTXD_EXT2_MASK = (int)0x1F00,
    RF_INT_VTXD_EXT2_POS = 8,
    RF_INT_VTXD_CHN_THR0_MASK = (int)0x3F0000,
    RF_INT_VTXD_CHN_THR0_POS = 16,
    RF_INT_VTXD_CHN_THR1_MASK = (int)0x3F000000,
    RF_INT_VTXD_CHN_THR1_POS = 24,
    RF_RX2MBW_FORCE_EN_MASK = (int)0x80000000,
    RF_RX2MBW_FORCE_EN_POS = 31,
};

#ifdef __cplusplus
}
#endif

#endif

