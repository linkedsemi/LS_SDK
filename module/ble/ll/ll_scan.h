#ifndef LL_SCAN_H_
#define LL_SCAN_H_
#include "ll_evt.h"
#include "co_error.h"

void ll_scan_env_init(void);

bool initiating_cancel(enum co_error *err);

enum co_error initiating_start(struct le_create_con_param *param);

bool scan_disable(enum co_error *err);

bool scan_enable(uint8_t filter_duplicates_en,enum co_error *err);

enum co_error scan_param_set(struct hci_le_set_scan_param_cmd *cmd);

enum ll_evt_start_type htimer_scan_evt_start(struct ll_evt *evt);

enum ll_evt_transition_type htimer_scan_tx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_scan_evt_rx_end(struct ll_evt *evt);

struct pkt_info htimer_scan_evt_header_rx(struct ll_evt *evt);

void scan_evt_terminate_handler(struct ll_evt *evt);

void scan_evt_end_handler(struct ll_evt *evt);

enum ll_evt_transition_type htimer_scan_evt_sync_timeout(struct ll_evt *evt);

#endif
