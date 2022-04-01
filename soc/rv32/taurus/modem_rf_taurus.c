#include "reg_sysc_ble.h"
#include "evt_ctrl.h"

static uint8_t ch_idx_to_phy_ch(uint8_t ch_idx)
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

void rf_tx_cfg(enum ble_phy phy,uint8_t ch,uint8_t tx_pwr)
{
    ch = ch_idx_to_phy_ch(ch);
    
}

void rf_rx_cfg(enum ble_phy phy,uint8_t ch)
{
    ch = ch_idx_to_phy_ch(ch);

}

void modem_rf_init()
{
    rf_tx_cfg_fn = rf_tx_cfg;
    rf_rx_cfg_fn = rf_rx_cfg;
    SYSC_BLE->PD_BLE_CLKG = SYSC_BLE_CLKG_SET_MDM_MASK | SYSC_BLE_CLKG_SET_RF_MASK;

}