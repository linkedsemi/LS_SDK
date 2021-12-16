#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _RSSI_SMOOTHING_ALGO_H_
#define _RSSI_SMOOTHING_ALGO_H_
#define CON_FOR_RSSI_SMTH_ALGO_NUM 4

#define NEW_RSSI_DERIVATION 5 // new rssi value derivation

int8_t get_cur_rssi(uint8_t con_id);
void rssi_smoothing_algo_init(uint8_t con_id, bool enable);
#endif
