#include "reg_sysc_ble.h"
#include "evt_ctrl.h"
#include "field_manipulate.h"
#include "reg_mdm2_type.h"
#include "reg_rf_type.h"

///PLL修改2402频点测试 0x200000  0x1F3333 0x1E6666 0x1CCCCC 0x20CCCC 0x219999 0x226666 0x233333
uint32_t tx_freq[40][2] ={{0x15,  0x200000},{0x15,  0x400000},{0x15,  0x600000},{0x15,  0x800000},{0x15,  0xA00000},{0x15,  0xC00000},{0x15,  0xE00000},{0x16,0x0},
{0x16,  0x200000},{0x16,  0x400000},{0x16,  0x600000},{0x16,  0x800000},{0x16,  0xA00000},{0x16,  0xC00000},{0x16,  0xE00000},{0x17,  0x0},
{0x17,  0x200000},{0x17,  0x400000},{0x17,  0x600000},{0x17,  0x800000},{0x17,  0xA00000},{0x17,  0xC00000},{0x17,  0xE00000},{0x18,  0x0},
{0x18,  0x200000},{0x18,  0x400000},{0x18,  0x600000},{0x18,  0x800000},{0x18,  0xA00000},{0x18,  0xC00000},{0x18,  0xE00000},{0x19,  0x0},
{0x19,  0x200000},{0x19,  0x400000},{0x19,  0x600000},{0x19,  0x800000},{0x19,  0xA00000},{0x19,  0xC00000},{0x19,  0xE00000},{0x1A,  0x0}};

uint32_t rx_freq[40][2] = {{4, 0x555555},{4, 0x71C71C},{4,  0x8E38E3},{4,  0xAAAAAA},{4,  0xC71C71},{4,  0xE38E38},{5,  0x0},{5,  0x1C71C7},
{5,  0x38E38E},{5,  0x555555},{5,  0x71C71C},{5,  0x8E38E3},{5,  0xAAAAAA},{5,  0xC71C71},{5,  0xE38E38},{6,  0x0},
{6,  0x1C71C7},{6,  0x38E38E},{6,  0x555555},{6,  0x71C71C},{6,  0x8E38E3},{6,  0xAAAAAA},{6,  0xC71C71},{6,  0xE38E38},
{7,  0x0},{7,  0x1C71C7},{7,  0x38E38E},{7,  0x555555},{7,  0x71C71C},{7,  0x8E38E3},{7,  0xAAAAAA},{7,  0xC71C71},
{7,  0xE38E38},{8,  0x0},{8,  0x1C71C7},{8,  0x38E38E},{8,  0x555555},{8,  0x71C71C},{8,  0x8E38E3},{8,  0xAAAAAA}};

///21
// uint8_t tx_pll_freq_adj_ext[40] = {17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15,15,14,14,14};

// uint8_t tx_pll_freq_adj_ext[40] = {18,18,18,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,15};

// uint8_t rx_pll_freq_adj_ext[40] = {29,29,29,29,29,28,28,28,28,28,28,28,28,28,28,28,27,27,27,27,27,27,27,27,27,27,27,27,26,26,26,26,26,26,26,26,26,26,26,26};

///18
uint8_t tx_pll_freq_adj_ext[40] = {18,18,18,18,18,18,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15};

uint8_t rx_pll_freq_adj_ext[40] = {30,30,30,30,30,29,29,29,29,29,29,29,29,29,29,28,28,28,28,28,28,28,28,28,28,28,28,27,27,27,27,27,27,27,27,27,26,26,26,26};


XIP_BANNED static uint8_t ch_idx_to_phy_ch(uint8_t ch_idx)
{
    uint8_t phy_ch;
    switch(ch_idx)
    {
    case 37:
        phy_ch = 0;
    break;
    case 38:
        phy_ch = 12;
    break;
    case 39:
        phy_ch = 39;
    break;
    default:
        if(ch_idx>10)
        {
            phy_ch = ch_idx +2;
        }else
        {
            phy_ch = ch_idx +1; 
        }
    break;
    }
    return phy_ch;
}

XIP_BANNED static void rf_tx_cfg(enum ble_phy phy,uint8_t ch,uint8_t tx_pwr)
{
    ch = ch_idx_to_phy_ch(ch);
    if(phy == BLE_1M)
    {
        MODIFY_REG(RF->REG10,RF_PLL_FREQ_ADJ_EXT_MASK|RF_PLL_DI_S_MASK,tx_pll_freq_adj_ext[ch]<<RF_PLL_FREQ_ADJ_EXT_POS|tx_freq[ch][0]<<RF_PLL_DI_S_POS);
        REG_FIELD_WR(RF->REG14, RF_PLL_FRAC,tx_freq[ch][1]);
    }
}

XIP_BANNED static void rf_rx_cfg(enum ble_phy phy,uint8_t ch)
{
    ch = ch_idx_to_phy_ch(ch);
    if(phy == BLE_1M)
    {
        MODIFY_REG(RF->REG10,RF_PLL_FREQ_ADJ_EXT_MASK|RF_PLL_DI_S_MASK,rx_pll_freq_adj_ext[ch]<<RF_PLL_FREQ_ADJ_EXT_POS|rx_freq[ch][0]<<RF_PLL_DI_S_POS);
        REG_FIELD_WR(RF->REG14, RF_PLL_FRAC,rx_freq[ch][1]);
    }
}

static void modem_reg_init()
{
    MDM2->REG08 = FIELD_BUILD(MDM2_MIN_MAG_CONF,0x474)
               | FIELD_BUILD(MDM2_DRIFT_COR_SET,1)
               | FIELD_BUILD(MDM2_IF_SHIFT,0x400);
    MDM2->REG20 = FIELD_BUILD(MDM2_LR_IF_SHIFT,0x400)
               | FIELD_BUILD(MDM2_LR_RX_INVERT,1)
               | FIELD_BUILD(MDM2_LR_IQ_INVERT,0)
               | FIELD_BUILD(MDM2_LR_ACC_INVERT,0);
}

static void rf_reg_init()
{
     RF->REG00 = FIELD_BUILD(RF_EN_DAC_DIG_PWR, 1)
               | FIELD_BUILD(RF_EN_AGC_PWR, 1)
               | FIELD_BUILD(RF_EN_PLL_SDM, 1)
               | FIELD_BUILD(RF_EN_ADC_DIG, 1)
               | FIELD_BUILD(RF_EN_LDO_PAHP, 1)
               | FIELD_BUILD(RF_EN_LDO_PLL, 1)
               | FIELD_BUILD(RF_EN_LDO_VCO, 1)
               | FIELD_BUILD(RF_EN_LDO_PA, 1)
               | FIELD_BUILD(RF_EN_LDO_IF, 1)
               | FIELD_BUILD(RF_EN_LDO_TX, 1)
               | FIELD_BUILD(RF_EN_LDO_RX, 1)
               | FIELD_BUILD(RF_EN_LDO_PAHP_BYPS, 0)
               | FIELD_BUILD(RF_EN_PAHP, 0)
               | FIELD_BUILD(RF_EN_DAC_ZB, 0)
               | FIELD_BUILD(RF_EN_DAC_BLE, 0)
               | FIELD_BUILD(RF_EN_PA_STG2, 0)
               | FIELD_BUILD(RF_EN_PA_STG1, 0)
               | FIELD_BUILD(RF_EN_PA, 0)
               | FIELD_BUILD(RF_EN_PLL, 1)
               | FIELD_BUILD(RF_EN_AGC, 0)
               | FIELD_BUILD(RF_EN_ADC, 1)
               | FIELD_BUILD(RF_EN_LMT_RSSI, 1)
               | FIELD_BUILD(RF_EN_BPF, 1)
               | FIELD_BUILD(RF_EN_MIXL, 1)
               | FIELD_BUILD(RF_EN_MIXH, 1)
               | FIELD_BUILD(RF_EN_LNA, 1);
    RF->REG04 = FIELD_BUILD(RF_LNA_VB_ADJ,7)
               | FIELD_BUILD(RF_LNA_TANK_TUNE,1)
               | FIELD_BUILD(RF_LNA_R_ADJ,0)
               | FIELD_BUILD(RF_MIXL_BIAS_CTL,3)
               | FIELD_BUILD(RF_MIXL_BIAS_SEL,0)
               | FIELD_BUILD(RF_MIXH_BIAS_CTL,3)
               | FIELD_BUILD(RF_MIXH_BIAS_SEL,0)
               | FIELD_BUILD(RF_BPF_CAL_CODE_EXT,0x30)
               | FIELD_BUILD(RF_BPF_CAL_CODE_EXT_EN,1)
               | FIELD_BUILD(RF_BPF_CAL_EN,0)
               | FIELD_BUILD(RF_EN_LNA_BYPS,0)
               | FIELD_BUILD(RF_LNA_GAIN,0)
               | FIELD_BUILD(RF_MIXL_GAIN_CTL,0)
               | FIELD_BUILD(RF_MIXH_GAIN_CTL,0)
               | FIELD_BUILD(RF_BPF_GAIN_ADJ,3)
               | FIELD_BUILD(RF_MIX_ENB_CAP,0);
    RF->REG08 = FIELD_BUILD(RF_LDO_RX_TRIM,4)
               | FIELD_BUILD(RF_LDO_TX_TRIM,4)
               | FIELD_BUILD(RF_CF_BW12M_ADJ,0)
               | FIELD_BUILD(RF_TX_RATE,0)
               | FIELD_BUILD(RF_CF_BW08M_ADJ,0)
               | FIELD_BUILD(RF_TX_DATA_TST_EN,0)
               | FIELD_BUILD(RF_PA_VCAS_RES_ADJ,0)
               | FIELD_BUILD(RF_PA_GAIN,0xf)
               | FIELD_BUILD(RF_PA_TANK_Q_ADJ,0)
               | FIELD_BUILD(RF_EN_PA_IBX2,1);
    RF->REG0C = FIELD_BUILD(RF_PA_TANK_TUNE,0)
               | FIELD_BUILD(RF_EN_RSSI_Q,1)
               | FIELD_BUILD(RF_EN_RSSI_I,1)
               | FIELD_BUILD(RF_PA_VB1_ADJ,0xf)
               | FIELD_BUILD(RF_PA_VB2_ADJ,0xf)
               | FIELD_BUILD(RF_PA_PTAT_ADJ,2)
               | FIELD_BUILD(RF_EN_PA_IPTAT,1)
               | FIELD_BUILD(RF_PA_BG_ADJ,6)
               | FIELD_BUILD(RF_EN_PA_IBG,1)
               | FIELD_BUILD(RF_PLL_BAND_CAL_SEL,0)///自动校准AFC
               | FIELD_BUILD(RF_PLL_AFC_FRAC_EN,1)
               | FIELD_BUILD(RF_PLL_AFC_DC_EN,1)
               | FIELD_BUILD(RF_PLL_VCTRL_EXT_EN,0)
               | FIELD_BUILD(RF_PLL_DIV_ADJ,2)
               | FIELD_BUILD(RF_PLL_SEL_RTX_BW,0);
    RF->REG10 = FIELD_BUILD(RF_PLL_DI_S,5)
               | FIELD_BUILD(RF_PLL_RTX_SEL,0)
               | FIELD_BUILD(RF_PLL_OPEN_EN,0)
               | FIELD_BUILD(RF_PLL_CAL_EN,0)
               | FIELD_BUILD(RF_PLL_FREQ_ADJ_EXT,0)
               | FIELD_BUILD(RF_PLL_FREQ_EXT_EN,1)
               | FIELD_BUILD(RF_PLL_FAST_LOCK_EN,0)
               | FIELD_BUILD(RF_PLL_REF_SEL,0)
               | FIELD_BUILD(RF_PLL_VREF_ADJ,0)
               | FIELD_BUILD(RF_PLL_FBDIV_PD_BYPS,0)
               | FIELD_BUILD(RF_PLL_BW_ADJ,2)
               | FIELD_BUILD(RF_PLL_LOCK_BYPS,0)
               | FIELD_BUILD(RF_PLL_CP_OS_ADJ,0)
               | FIELD_BUILD(RF_PLL_CP_OS_EN,0)
               | FIELD_BUILD(RF_PLL_VCO_ADJ,6);
    RF->REG14 = FIELD_BUILD(RF_PLL_FRAC,0)
               | FIELD_BUILD(RF_DAC_CAL_DATA_EXT,0)
               | FIELD_BUILD(RF_DAC_CAL_EN_EXT,0)
               | FIELD_BUILD(RF_DAC_EXT_EN,0)
               | FIELD_BUILD(RF_DAC_BLE_DELAY_ADJ,0x10);
    RF->REG18 = FIELD_BUILD(RF_DAC_REFL_ADJ,0)
               | FIELD_BUILD(RF_ADC_MUX_SEL,0)
               | FIELD_BUILD(RF_ADC_VREF_ADJ,0)
               | FIELD_BUILD(RF_ADC_TEST_SEL,0)
               | FIELD_BUILD(RF_EN_ADC_CNT_MODE,0)
               | FIELD_BUILD(RF_ADC_START,0);
    RF->REG1C = FIELD_BUILD(RF_EN_LDO_PLL_BYPS,0)
               | FIELD_BUILD(RF_EN_LDO_RX_BYPS,0)
               | FIELD_BUILD(RF_EN_LDO_TX_BYPS,0)
               | FIELD_BUILD(RF_EN_LDO_IF_BYPS,0)
               | FIELD_BUILD(RF_EN_LDO_PA_BYPS,0)
               | FIELD_BUILD(RF_EN_LDO_VCO_BYPS,0)
               | FIELD_BUILD(RF_ADC_REFBUF_LP,0)
               | FIELD_BUILD(RF_DAC_REFH_ADJ,1)
               | FIELD_BUILD(RF_PLL_DI_P,0x1f)
               | FIELD_BUILD(RF_PLL_FBDIV_PD,0)
               | FIELD_BUILD(RF_PLL_SDM_TEST_EN,0)
               | FIELD_BUILD(RF_PLL_FRAC_INT_MODE,0);
    RF->REG20 = FIELD_BUILD(RF_BPF_IADJ,4)
               | FIELD_BUILD(RF_BPF_BW_ADJ,1)
               | FIELD_BUILD(RF_BPF_MODE_SEL,0)
               | FIELD_BUILD(RF_BPF_CENT_ADJ,2)
               | FIELD_BUILD(RF_AT0_SEL,0xe)
               | FIELD_BUILD(RF_AT1_SEL,0xe);
    RF->REG24 = FIELD_BUILD(RF_AGC_S00L,8)
               | FIELD_BUILD(RF_AGC_S11_LNA_BYPS_ADJ,0)
               | FIELD_BUILD(RF_AGC_S10_LNA_BYPS_ADJ,0)
               | FIELD_BUILD(RF_AGC_S00H,0x2a)
               | FIELD_BUILD(RF_AGC_S01_MIX_ADJ,2)
               | FIELD_BUILD(RF_AGC_S01H,0x30)
               | FIELD_BUILD(RF_AGC_S10_MIX_ADJ,0x2) 
               | FIELD_BUILD(RF_AGC_S01L,0x1a)
               | FIELD_BUILD(RF_AGC_POWER_DET_EN,1)
               | FIELD_BUILD(RF_AGC_TEST_EN,0);
    RF->REG28 = FIELD_BUILD(RF_AGC_S10L,0x1d)
               | FIELD_BUILD(RF_AGC_S11_LNA_EN_ADJ,1)
               | FIELD_BUILD(RF_AGC_S10_LNA_EN_ADJ,1)
               | FIELD_BUILD(RF_AGC_S10_BPF_ADJ,3)
               | FIELD_BUILD(RF_AGC_T_ADJ,0)
               | FIELD_BUILD(RF_AGC_VH_ADD_ADJ,0)
               | FIELD_BUILD(RF_AGC_S01_BPF_ADJ,3)
               | FIELD_BUILD(RF_AGC_S11_BPF_ADJ,3)
               | FIELD_BUILD(RF_AGC_S00_BPF_ADJ,3)
               | FIELD_BUILD(RF_AGC_S11_MIX_ADJ,2)
               | FIELD_BUILD(RF_AGC_S00_MIX_ADJ,2)
               | FIELD_BUILD(RF_AGC_S11_LNA_ADJ,0)
               | FIELD_BUILD(RF_AGC_S10_LNA_ADJ,0)
               | FIELD_BUILD(RF_AGC_S01_LNA_ADJ,0)
               | FIELD_BUILD(RF_AGC_S00_LNA_ADJ,0);
    RF->REG2C = FIELD_BUILD(RF_PLL_GAIN_CAL_SEL,5)
               | FIELD_BUILD(RF_PLL_FBDIV_RST_SEL,0)
               | FIELD_BUILD(RF_PLL_FBDIV_RST_EXT,0)
               | FIELD_BUILD(RF_PLL_PS_CNT_RST_SEL,0)
               | FIELD_BUILD(RF_AGC_TEST_S,0)
               | FIELD_BUILD(RF_PA_MN_TUNE,0)
               | FIELD_BUILD(RF_PLL_GAIN_CAL_TH,0x22)
               | FIELD_BUILD(RF_PLL_VTXD_EXT,0xa)
               | FIELD_BUILD(RF_PLL_VTXD_EXT_EN,0)
               | FIELD_BUILD(RF_PLL_GAIN_CAL_EN,0)
               | FIELD_BUILD(RF_PLL_GAIN_CAL_DC,1);
    RF->REG30 = FIELD_BUILD(RF_RSV,0x44)
               | FIELD_BUILD(RF_LDO_PA_TRIM,7)
               | FIELD_BUILD(RF_EN_LMT_OUTI_EXT,1)
               | FIELD_BUILD(RF_EN_LMT_OUTQ_EXT,1)
               | FIELD_BUILD(RF_PAHP_SEL,0)
               | FIELD_BUILD(RF_LDO_PAHP_TRIM,0)
               | FIELD_BUILD(RF_EN_AT,0)
               | FIELD_BUILD(RF_PAHP_ADJ,0xf);
    RF->REG50 = FIELD_BUILD(RF_ANA_TEST_EN,0)
               | FIELD_BUILD(RF_PLL_AFC_BP,0)
               | FIELD_BUILD(RF_PLL_GAIN_BP,0)
               | FIELD_BUILD(RF_PPF_RC_BP,1)
               | FIELD_BUILD(RF_LDO_TEST_EN,0)
               | FIELD_BUILD(RF_RD_CLK_EN,1)
               | FIELD_BUILD(RF_PLL_TEST_EN,0)
               | FIELD_BUILD(RF_CH_SEL,1)
               | FIELD_BUILD(RF_PA_VB_SEL,0)  //  0-rf_ctl      1-cs_ctl
               | FIELD_BUILD(RF_PA_VB_TARGET,0xf) 
               | FIELD_BUILD(RF_LDO_START_CNT,3)
               | FIELD_BUILD(RF_PA_STEP_SET,5);
    RF->REG54 = FIELD_BUILD(RF_AFC_MIN_CNT,24)
                | FIELD_BUILD(RF_AFC_MAX_CNT,0x30)
                | FIELD_BUILD(RF_GAIN_MAX_CNT,0x10)
                | FIELD_BUILD(RF_EN_PLL_CNT,0x4);
    RF->REG58 = FIELD_BUILD(RF_EN_DAC_CNT,23) 
               | FIELD_BUILD(RF_PLL_CAL_EN_CNT,5)  
               | FIELD_BUILD(RF_PLL_GAIN_CAL_EN_CNT,4)
               | FIELD_BUILD(RF_EN_PA_CNT,0x4a);  
    RF->REG5C = FIELD_BUILD(RF_EN_PA_STG1_CNT,0x4a) 
               | FIELD_BUILD(RF_EN_PA_STG2_CNT,0x4a)
               | FIELD_BUILD(RF_PLL_LOCK_CNT,0x4a)
               | FIELD_BUILD(RF_EN_RX_CNT,0x2);
    RF->REG60 = FIELD_BUILD(RF_EN_AGC_CNT,0)|
                FIELD_BUILD(RF_TX_START_CNT,0)|
                FIELD_BUILD(RF_TX_WAIT_CNT,0)|
                FIELD_BUILD(RF_RX_START_CNT,0);
    RF->REG64 = FIELD_BUILD(RF_RSSI_OFFSET, 0x80)
               |FIELD_BUILD(RF_ADC_MDM_EN, 1);
    RF->REG70 = FIELD_BUILD(RF_RX2MBW_FORCE_EN,0)
               | FIELD_BUILD(RF_INT_VTXD_CHN_THR1,0x19)
               | FIELD_BUILD(RF_INT_VTXD_CHN_THR0,0xc)
               | FIELD_BUILD(RF_INT_VTXD_EXT2,0)
               | FIELD_BUILD(RF_INT_VTXD_EXT1,0);
}

void modem_rf_init()
{
    rf_tx_cfg_fn = rf_tx_cfg;
    rf_rx_cfg_fn = rf_rx_cfg;
    SYSC_BLE->PD_BLE_CLKG = SYSC_BLE_CLKG_SET_MDM_MASK | SYSC_BLE_CLKG_SET_RF_MASK;
    modem_reg_init();
    rf_reg_init();
}