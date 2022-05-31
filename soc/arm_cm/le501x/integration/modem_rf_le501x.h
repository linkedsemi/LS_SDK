#ifndef MODEM_RF_LE501X_H_
#define MODEM_RF_LE501X_H_
#include <stdint.h>
#include <stdbool.h>

enum rf_tx_pwr
{
    TX_N8DBM = -2,
    TX_N4DBM = -1,
    TX_0DBM = 0,
    TX_3DBM,
    TX_5DBM,
    TX_7DBM,
    TX_12DBM_PAHP,
};

uint8_t rf_txpwr_dbm_get(uint8_t txpwr_idx, uint8_t modulation);

void rf_reset(void);

void rf_force_agc_enable(bool en);

int8_t rf_rssi_convert(uint8_t rssi_reg);

uint8_t rf_txpwr_cs_get(int8_t txpwr_dbm, bool high);

uint8_t rx_txpwr_max_get(void);

uint8_t rx_txpwr_min_get(void);

void modem_rf_reinit(void);

void modem_rf_init(void);

void rf_set_power(enum rf_tx_pwr tx_power);

void tempsensor_ldo_init(void);

void tempsensor_ldo_deinit(void);

void rf_reg_config(uint8_t,uint8_t,uint16_t);
#endif

