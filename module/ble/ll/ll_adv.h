#ifndef LL_ADV_H_
#define LL_ADV_H_
#include "ll_evt.h"
#include "co_error.h"

void ll_adv_env_init(void);

enum ll_evt_start_type htimer_adv_evt_start(struct ll_evt *evt);

enum ll_evt_transition_type htimer_adv_tx_end(struct ll_evt *evt);

struct pkt_info htimer_adv_evt_header_rx(struct ll_evt *evt);

enum ll_evt_transition_type htimer_adv_evt_rx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_adv_evt_sync_timeout(struct ll_evt *evt);

void adv_evt_terminate_handler(struct ll_evt *evt);

void adv_evt_end_handler(struct ll_evt *evt);

enum co_error adv_param_set(struct hci_le_set_adv_param_cmd *cmd);

enum co_error adv_data_set(struct adv_data *data);

enum co_error scan_rsp_data_set(struct adv_data *data);

bool adv_enable(enum co_error *err);

bool adv_disable(enum co_error *err);

#endif
