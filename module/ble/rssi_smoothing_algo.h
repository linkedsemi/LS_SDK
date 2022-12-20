#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _RSSI_SMOOTHING_ALGO_H_
#define _RSSI_SMOOTHING_ALGO_H_
#define CON_FOR_RSSI_SMTH_ALGO_NUM 4

#define NEW_RSSI_DERIVATION 5 // new rssi value derivation

int8_t get_cur_rssi(uint8_t con_id);
void rssi_smoothing_algo_init(uint8_t con_id, bool enable);
// the parameters of handler are rssi(int8_t), init_addr(const uint8_t*) and init_addr_type(uint8_t)
// the handler will be executed in interrupt
void con_rssi_thld_init(bool (*handler)(int8_t, const uint8_t*, uint8_t));
#endif
