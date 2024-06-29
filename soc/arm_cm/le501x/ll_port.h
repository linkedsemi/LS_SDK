#ifndef LL_PORT_H_
#define LL_PORT_H_
#include "reg_base_addr.h"
#include "reg_rwmac_type.h"
#define MAC ((reg_rwmac_t *)MAC_BASE_ADDR)
#define LL_SWINT_NUM 22
#define MAC_CLK_MHZ (16)

void ble_pkt_irq_mask(void);

void ble_pkt_irq_unmask(void);

void ble_pkt_irq_clr(void);

void ble_util_irq_clr(void);

void sleep_expected_time_set(uint32_t time);

uint32_t sleep_duration_get();

void mac_reg_sync(void);

#endif
