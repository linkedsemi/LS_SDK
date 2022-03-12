#include "reg_sysc_ble.h"

void modem_rf_init()
{
    SYSC_BLE->PD_BLE_CLKG = SYSC_BLE_CLKG_SET_MDM_MASK | SYSC_BLE_CLKG_SET_RF_MASK;

}