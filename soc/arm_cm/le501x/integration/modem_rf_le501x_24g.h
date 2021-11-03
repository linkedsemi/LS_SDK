#ifndef MODEM_RF_LE501X_24G_H_
#define MODEM_RF_LE501X_24G_H_
#include <stdint.h>
#include <stdbool.h>
void modem_rf_init_24g(void);
void modem_rf_set_rx_phy(uint8_t phy);
int8_t rf_rssi_convert_24g(uint8_t rssi_reg);
#endif

