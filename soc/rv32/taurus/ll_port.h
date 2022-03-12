#ifndef LL_PORT_H_
#define LL_PORT_H_
#include "reg_mac_type.h"
#include "reg_base_addr.h"
#define MAC ((reg_mac_t *)MAC_BASE_ADDR)
#define MAC_CLK_MHZ (16)
#define BLE_EVT_INT_NUM 9
#define MAC_FIFO_DEPTH 64

void ble_pkt_irq_mask(void);

void ble_pkt_irq_unmask(void);

void ble_pkt_irq_clr(void);

void ble_util_irq_clr(void);

void sleep_expected_time_set(uint32_t time);

uint32_t sleep_duration_get();

void mac_reg_sync(void);

#endif
