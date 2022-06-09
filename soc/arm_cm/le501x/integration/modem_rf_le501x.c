#include "modem_rf_le501x.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "reg_rf.h"
#include "reg_mdm2.h"
#include "reg_syscfg.h"
#include "spi_flash.h"
#include "ls_dbg.h"
#define RF_PWR_TBL_SIZE            (8)

#define FLASH_SECURITY_AREA_INDEX_1 1
#define SECURITY_AREA_PACKAGEID_OFFSET 0x24

#define LDO_START_STAGE_ANCHOR (3)
#define AFC_CAL_STAGE_ANCHOR (29)
#define GAIN_CAL_STAGE_ANCHOR (84)
#define PLL_LOCK_STAGE_ANCHOR (9)
#define PA_EN_ANCHOR (PLL_LOCK_STAGE_ANCHOR - 9)

static uint16_t package_id;
static enum rf_tx_pwr user_rf_power;
static uint8_t gain_threshold[2];
struct {
    uint8_t ldo_tx_trim:3,
            ldo_rx_trim:3;
    uint8_t bpf_code:6;
}rf_ret;

// Power table
static const int8_t RF_TX_PW_CONV_TBL[RF_PWR_TBL_SIZE] =
{
    [0] = -23,
    [1] = -20,
    [2] = -17,
    [3] = -14,
    [4] = -11,
    [5] = -8,
    [6] = -5,
    [7] = -2
};

// TX max powerf
#define RF_POWER_MAX                0x4
#define RF_POWER_MIN                0


uint8_t rf_txpwr_dbm_get(uint8_t txpwr_idx, uint8_t modulation)
{
    // power table is the same for BR and EDR
    return (RF_TX_PW_CONV_TBL[txpwr_idx]);
}


void rf_reset(void)
{
    return;
}

void rf_force_agc_enable(bool en)
{
    return;
}

int8_t rf_rssi_convert(uint8_t rssi_reg)
{
    int8_t rssi_dbm;
    uint8_t agc_state;
    agc_state = REG_FIELD_RD(RF->REG6C,RF_AGC_STATE);
    if(agc_state ==2 ){
        rssi_dbm = rssi_reg-255 + agc_state*17 ;
    }
    else if(agc_state == 1){
        rssi_dbm = rssi_reg-255 + agc_state*6 ;
    }
    else{
        rssi_dbm = rssi_reg-255-20;
    }
    return (rssi_dbm);
}

uint8_t rf_txpwr_cs_get(int8_t txpwr_dbm, bool high)
{
    return RF_POWER_MAX;
}

uint8_t rx_txpwr_max_get()
{
    return RF_POWER_MAX;
}

uint8_t rx_txpwr_min_get()
{
    return RF_POWER_MIN;
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
               | FIELD_BUILD(RF_BPF_CAL_CODE_EXT,rf_ret.bpf_code) // 1a  -1d
               | FIELD_BUILD(RF_BPF_CAL_CODE_EXT_EN,1)
               | FIELD_BUILD(RF_BPF_CAL_EN,0)
               | FIELD_BUILD(RF_EN_LNA_BYPS,0)
               | FIELD_BUILD(RF_LNA_GAIN,0)
               | FIELD_BUILD(RF_MIXL_GAIN_CTL,0)
               | FIELD_BUILD(RF_MIXH_GAIN_CTL,0)
               | FIELD_BUILD(RF_BPF_GAIN_ADJ,3)
               | FIELD_BUILD(RF_MIX_ENB_CAP,0);
    RF->REG08 = FIELD_BUILD(RF_LDO_RX_TRIM,rf_ret.ldo_rx_trim)
               | FIELD_BUILD(RF_LDO_TX_TRIM,rf_ret.ldo_tx_trim)
               | FIELD_BUILD(RF_CF_BW12M_ADJ,0)
               | FIELD_BUILD(RF_TX_RATE,0)
               | FIELD_BUILD(RF_CF_BW08M_ADJ,0)
               | FIELD_BUILD(RF_TX_DATA_TST_EN,0)
               | FIELD_BUILD(RF_PA_VCAS_RES_ADJ,0)
               | FIELD_BUILD(RF_PA_GAIN,0xf)
               | FIELD_BUILD(RF_PA_TANK_Q_ADJ,0)
               | FIELD_BUILD(RF_EN_PA_IBX2,1);
    RF->REG0C = FIELD_BUILD(RF_PA_TANK_TUNE,1)
               | FIELD_BUILD(RF_EN_RSSI_Q,1)
               | FIELD_BUILD(RF_EN_RSSI_I,1)
               | FIELD_BUILD(RF_PA_VB1_ADJ,0xf)
               | FIELD_BUILD(RF_PA_VB2_ADJ,0xf)
               | FIELD_BUILD(RF_PA_PTAT_ADJ,0)
               | FIELD_BUILD(RF_EN_PA_IPTAT,1)
               | FIELD_BUILD(RF_PA_BG_ADJ,4)
               | FIELD_BUILD(RF_EN_PA_IBG,1)
               | FIELD_BUILD(RF_PLL_BAND_CAL_SEL,0)
               | FIELD_BUILD(RF_PLL_AFC_FRAC_EN,1)
               | FIELD_BUILD(RF_PLL_AFC_DC_EN,1)
               | FIELD_BUILD(RF_PLL_VCTRL_EXT_EN,0)
               | FIELD_BUILD(RF_PLL_DIV_ADJ,2)
               | FIELD_BUILD(RF_PLL_SEL_RTX_BW,1);
    RF->REG10 = FIELD_BUILD(RF_PLL_DI_S,5)
               | FIELD_BUILD(RF_PLL_RTX_SEL,0)
               | FIELD_BUILD(RF_PLL_OPEN_EN,0)
               | FIELD_BUILD(RF_PLL_CAL_EN,0)
               | FIELD_BUILD(RF_PLL_FREQ_ADJ_EXT,0)
               | FIELD_BUILD(RF_PLL_FREQ_EXT_EN,0)
               | FIELD_BUILD(RF_PLL_FAST_LOCK_EN,0)
               | FIELD_BUILD(RF_PLL_REF_SEL,0)
               | FIELD_BUILD(RF_PLL_VREF_ADJ,0)
               | FIELD_BUILD(RF_PLL_FBDIV_PD_BYPS,0)
               | FIELD_BUILD(RF_PLL_BW_ADJ,2)
               | FIELD_BUILD(RF_PLL_LOCK_BYPS,0)
               | FIELD_BUILD(RF_PLL_CP_OS_ADJ,0)
               | FIELD_BUILD(RF_PLL_CP_OS_EN,0)
               | FIELD_BUILD(RF_PLL_VCO_ADJ,2);//2020 5.22CAI 2-6
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
               | FIELD_BUILD(RF_AGC_S11_LNA_BYPS_ADJ,1)
               | FIELD_BUILD(RF_AGC_S10_LNA_BYPS_ADJ,1)
               | FIELD_BUILD(RF_AGC_S00H,0x2a)
               | FIELD_BUILD(RF_AGC_S01_MIX_ADJ,0)
               | FIELD_BUILD(RF_AGC_S01H,0x30)
               | FIELD_BUILD(RF_AGC_S10_MIX_ADJ,0x1) 
               | FIELD_BUILD(RF_AGC_S01L,0x1a)
               | FIELD_BUILD(RF_AGC_POWER_DET_EN,1)
               | FIELD_BUILD(RF_AGC_TEST_EN,0);
    RF->REG28 = FIELD_BUILD(RF_AGC_S10L,0x1d)
               | FIELD_BUILD(RF_AGC_S11_LNA_EN_ADJ,0)
               | FIELD_BUILD(RF_AGC_S10_LNA_EN_ADJ,0)
               | FIELD_BUILD(RF_AGC_S10_BPF_ADJ,1)
               | FIELD_BUILD(RF_AGC_T_ADJ,0)
               | FIELD_BUILD(RF_AGC_VH_ADD_ADJ,0)
               | FIELD_BUILD(RF_AGC_S01_BPF_ADJ,0)
               | FIELD_BUILD(RF_AGC_S11_BPF_ADJ,1)
               | FIELD_BUILD(RF_AGC_S00_BPF_ADJ,1)
               | FIELD_BUILD(RF_AGC_S11_MIX_ADJ,1)
               | FIELD_BUILD(RF_AGC_S00_MIX_ADJ,0)
               | FIELD_BUILD(RF_AGC_S11_LNA_ADJ,3)
               | FIELD_BUILD(RF_AGC_S10_LNA_ADJ,3)
               | FIELD_BUILD(RF_AGC_S01_LNA_ADJ,3)
               | FIELD_BUILD(RF_AGC_S00_LNA_ADJ,0);
    RF->REG2C = FIELD_BUILD(RF_PLL_GAIN_CAL_SEL,5)
               | FIELD_BUILD(RF_PLL_FBDIV_RST_SEL,0)
               | FIELD_BUILD(RF_PLL_FBDIV_RST_EXT,0)
               | FIELD_BUILD(RF_PLL_PS_CNT_RST_SEL,0)
               | FIELD_BUILD(RF_AGC_TEST_S,0)
               | FIELD_BUILD(RF_PA_MN_TUNE,0)
               | FIELD_BUILD(RF_PLL_GAIN_CAL_TH,0x20)
               | FIELD_BUILD(RF_PLL_VTXD_EXT,0)
               | FIELD_BUILD(RF_PLL_VTXD_EXT_EN,0)
               | FIELD_BUILD(RF_PLL_GAIN_CAL_EN,0)
               | FIELD_BUILD(RF_PLL_GAIN_CAL_DC,1);
    RF->REG30 = FIELD_BUILD(RF_RSV,0x44)
               | FIELD_BUILD(RF_LDO_PA_TRIM,1)
               | FIELD_BUILD(RF_EN_LMT_OUTI_EXT,1)
               | FIELD_BUILD(RF_EN_LMT_OUTQ_EXT,1)
               | FIELD_BUILD(RF_PAHP_SEL,0)
               | FIELD_BUILD(RF_LDO_PAHP_TRIM,0xf)
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
               | FIELD_BUILD(RF_LDO_START_CNT,LDO_START_STAGE_ANCHOR)
               | FIELD_BUILD(RF_PA_STEP_SET,11);
    RF->REG54 = FIELD_BUILD(RF_AFC_MIN_CNT,AFC_CAL_STAGE_ANCHOR)
                | FIELD_BUILD(RF_AFC_MAX_CNT,AFC_CAL_STAGE_ANCHOR+1)
                | FIELD_BUILD(RF_GAIN_MAX_CNT,GAIN_CAL_STAGE_ANCHOR)
                | FIELD_BUILD(RF_EN_PLL_CNT,0);
    RF->REG58 = FIELD_BUILD(RF_EN_DAC_CNT,AFC_CAL_STAGE_ANCHOR-1) 
               | FIELD_BUILD(RF_PLL_CAL_EN_CNT,5)  
               | FIELD_BUILD(RF_PLL_GAIN_CAL_EN_CNT,0)
               | FIELD_BUILD(RF_EN_PA_CNT,PA_EN_ANCHOR);  
    RF->REG5C = FIELD_BUILD(RF_EN_PA_STG1_CNT,PA_EN_ANCHOR) 
               | FIELD_BUILD(RF_EN_PA_STG2_CNT,PA_EN_ANCHOR)
               | FIELD_BUILD(RF_PLL_LOCK_CNT,PLL_LOCK_STAGE_ANCHOR)
               | FIELD_BUILD(RF_EN_RX_CNT,0);
    RF->REG60 = FIELD_BUILD(RF_EN_AGC_CNT,0)|
                FIELD_BUILD(RF_TX_START_CNT,0)|
                FIELD_BUILD(RF_TX_WAIT_CNT,0)|
                FIELD_BUILD(RF_RX_START_CNT,0);
    RF->REG64 = FIELD_BUILD(RF_RSSI_OFFSET, 0X80)
               |FIELD_BUILD(RF_ADC_MDM_EN, 1);      
    RF->REG70 = FIELD_BUILD(RF_RX2MBW_FORCE_EN,0)
               | FIELD_BUILD(RF_INT_VTXD_CHN_THR1,0x19)
               | FIELD_BUILD(RF_INT_VTXD_CHN_THR0,0xc)
               | FIELD_BUILD(RF_INT_VTXD_EXT2,0)
               | FIELD_BUILD(RF_INT_VTXD_EXT1,0);


    switch (package_id)
    {
    case 0x1603:
        REG_FIELD_WR(SYSCFG->ANACFG1, SYSCFG_XO16M_CAP_TRIM, 18);
		gain_threshold[0] = 0x22;
		gain_threshold[1] = 0x1e;
    break;
    case 0x3202:
        REG_FIELD_WR(SYSCFG->ANACFG1, SYSCFG_XO16M_CAP_TRIM, 11);//LP 16  HP 9
		gain_threshold[0] = 0x20;
		gain_threshold[1] = 0x1e;
    break;
    case 0x4803:
        REG_FIELD_WR(SYSCFG->ANACFG1, SYSCFG_XO16M_CAP_TRIM, 12);
		gain_threshold[0] = 0x20;
		gain_threshold[1] = 0x1e;
    break;
    default:
    break;
    }
}

static void BPF_CAL()
{
    MODIFY_REG(RF->REG00,RF_EN_AGC_MASK,RF_EN_BPF_MASK);
    MODIFY_REG(RF->REG04,RF_BPF_CAL_EN_MASK|RF_BPF_CAL_CODE_EXT_EN_MASK,0);
    // BPF CAL start
    REG_FIELD_WR(RF->REG04,RF_BPF_CAL_EN,1); // 0->1
    while((!(REG_FIELD_RD(RF->REG34,RF_BPF_CAL_DONE))));
    rf_ret.bpf_code = REG_FIELD_RD(RF->REG38,RF_BPF_CAL_CODE);
    REG_FIELD_WR(RF->REG04,RF_BPF_CAL_EN,0); 
    //bpf end
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
static void pll_cal_testreg_init()
{
        // AFE TEST mode enable
    REG_FIELD_WR(RF->REG50,RF_ANA_TEST_EN,1);
    REG_FIELD_WR(RF->REG50,RF_LDO_TEST_EN,1);
    REG_FIELD_WR(RF->REG10,RF_PLL_RTX_SEL,1);
    REG_FIELD_WR(RF->REG50,RF_PLL_TEST_EN,1);
}
static void pll_cal_testreg_deinit()
{
        // AFE TEST mode disenable
    REG_FIELD_WR(RF->REG50,RF_ANA_TEST_EN,0);
    REG_FIELD_WR(RF->REG50,RF_LDO_TEST_EN,0);
    REG_FIELD_WR(RF->REG10,RF_PLL_RTX_SEL,0);
    REG_FIELD_WR(RF->REG50,RF_PLL_TEST_EN,0);
}

void tempsensor_ldo_init(void)
{
    // AFE TEST mode enable
    REG_FIELD_WR(RF->REG00,RF_EN_LDO_IF,1);
    REG_FIELD_WR(RF->REG50,RF_LDO_TEST_EN,1); 
}

void tempsensor_ldo_deinit(void)
{
        // AFE TEST mode disenable
    REG_FIELD_WR(RF->REG50,RF_LDO_TEST_EN,0);
}

static void rf_reg_retention()
{
    uint32_t rf_reg08 = RF->REG08;
    rf_ret.ldo_tx_trim = REG_FIELD_RD(rf_reg08,RF_LDO_TX_TRIM);//9.14
    rf_ret.ldo_rx_trim = REG_FIELD_RD(rf_reg08,RF_LDO_RX_TRIM);
}

static void tx_pwr_config()
{
    if(user_rf_power == TX_12DBM_PAHP)
    {
        REG_FIELD_WR(RF->REG00,RF_EN_PAHP,1);
        REG_FIELD_WR(RF->REG30,RF_PAHP_SEL,1);
    }else
    {
        REG_FIELD_WR(RF->REG00,RF_EN_PAHP,0);
        REG_FIELD_WR(RF->REG30,RF_PAHP_SEL,0);
        switch(user_rf_power)
        {
        case TX_N8DBM:
            REG_FIELD_WR(RF->REG08,RF_PA_TANK_Q_ADJ,7);
        break;
        case TX_N4DBM:
            REG_FIELD_WR(RF->REG08,RF_PA_TANK_Q_ADJ,3);
        break;
        case TX_0DBM:
            REG_FIELD_WR(RF->REG30,RF_LDO_PA_TRIM,1);
        break;
        case TX_3DBM:
            REG_FIELD_WR(RF->REG30,RF_LDO_PA_TRIM,2);
        break;
        case TX_5DBM:
            REG_FIELD_WR(RF->REG30,RF_LDO_PA_TRIM,4);
        break;
        case TX_7DBM:
            REG_FIELD_WR(RF->REG30,RF_LDO_PA_TRIM,7);
        break;
        default:
            LS_ASSERT(0);
        break;
        }
    }
}

void rf_set_power(enum rf_tx_pwr tx_power)
{
    user_rf_power = tx_power;
    tx_pwr_config();
}

void modem_rf_reinit()
{
    rf_reg_init();
    modem_reg_init();
    tx_pwr_config();
}

void modem_rf_init()
{
    RCC->APB1EN |= 1<<RCC_RF_POS | 1<<RCC_MDM2_POS;
    spi_flash_read_security_area(FLASH_SECURITY_AREA_INDEX_1, SECURITY_AREA_PACKAGEID_OFFSET,(void *)&package_id, sizeof(uint16_t));
    rf_reg_retention();
    pll_cal_testreg_init();
    BPF_CAL();
    pll_cal_testreg_deinit();
    modem_rf_reinit();
}

void rf_reg_config(uint8_t idx,uint8_t format,uint16_t rate)
{
    switch(format)
    {
    case 2:case 4:case 5:case 6:case 28:case 30:
        rate = rate & 3;
    break;
    case 3:case 8:case 9:case 10:case 11:case 14:case 15:case 29:
        rate = rate>>2 & 3;
    break;
    default:
        
    break;
    }
    switch(rate)
    {
    case 0:
        REG_FIELD_WR(RF->REG2C,RF_PLL_GAIN_CAL_TH,gain_threshold[0]);
    break;
    case 1:
        REG_FIELD_WR(RF->REG2C,RF_PLL_GAIN_CAL_TH,gain_threshold[1]);
    break;
    default:

    break;
    }
}
