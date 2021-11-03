#ifndef LL_EXT_ADV_H_
#define LL_EXT_ADV_H_
#include <stdint.h>
#include <stdbool.h>
#include "hci_format.h"
#include "co_list.h"
#include "co_error.h"
#include "ll_evt.h"
#include "ll_sync.h"
#include "timer_wrapper.h"

enum secondary_adv_evt_status
{
    SECONDARY_ADV_EVT_ONGOING = 0x1,
    SECONDARY_ADV_EVT_ANCHOR_UPDATED = 0x2,
};

enum conn_req_status
{
    NO_CONN_REQ,
    CONN_REQ_FROM_PRIM_EVT,
    CONN_REQ_FROM_SECOND_EVT,
};

struct adv_data_scan_rsp_data
{
    struct co_list adv_list;
    struct co_list scan_rsp_list;
    uint16_t DID:12;
};

struct adv_set_env
{
    struct ll_evt evt;
    struct ll_evt second_evt;
    struct adv_current_tx_env current_tx;
    struct sync_env *periodic;
    timer_t duration_timer;
    uint32_t secondary_series_start;
    uint32_t next_secondary_anchor;
    uint32_t conn_req_end_time;
    struct adv_data_scan_rsp_data data_list[2];
    struct le_ext_adv_param ext_param;
    struct bd_addr rand_addr;
    struct adv_evt_rx_data rx;
    enum conn_req_status connection_requesting;
    uint8_t next_second_ch;
    uint8_t max_evt;
    uint8_t completed_evts;
    uint8_t secondary_status;
    bool adv_timeout;
    bool scan_requested;
    uint8_t current_adv;
    uint8_t adv_update;
    uint8_t current_scan_rsp;
    uint8_t scan_rsp_update;
    uint8_t enabled;
};

extern uint8_t adv_sets_num;

void ll_ext_adv_env_reset(void);

enum co_error ll_ext_adv_remove_adv_set(uint8_t handle);

enum co_error ll_ext_adv_clr_adv_sets(void);

enum co_error ll_ext_adv_set_rand_addr(uint8_t handle,struct bd_addr *addr);

enum co_error ll_ext_adv_set_param_legacy_cmd(struct le_adv_param *param);

enum co_error ll_ext_adv_set_data_legacy_cmd(struct adv_data *adv);

enum co_error ll_ext_adv_set_scan_rsp_data_legacy_cmd(struct adv_data *scan_rsp);

bool ll_ext_adv_enable_adv_legacy_cmd(struct hci_le_set_adv_en_cmd *cmd,enum co_error *err);

enum co_error ll_ext_adv_set_param(uint8_t handle,struct le_ext_adv_param *param,int8_t *selected_tx_power);

enum co_error ll_ext_adv_set_periodic_param(uint8_t handle,struct le_periodic_adv_param *param);

enum co_error ll_ext_adv_set_data(struct hci_le_set_ext_adv_data_cmd *cmd);

enum co_error ll_ext_adv_set_scan_rsp_data(struct hci_le_set_ext_scan_rsp_data_cmd *cmd);

enum co_error ll_ext_adv_set_per_adv_data(struct hci_le_set_per_adv_data_cmd *cmd);

bool ll_ext_adv_enable_adv(struct hci_le_set_ext_adv_en_cmd *cmd,enum co_error *err);

bool ll_ext_adv_enable_per_adv(uint8_t adv_hdl,uint8_t enable,enum co_error *err);

uint16_t ll_ext_adv_get_max_adv_data_len(void);

uint16_t ext_adv_data_remain_length(struct adv_current_tx_env *env);

struct pkt_info sync_adv_tx_prepare(struct ll_evt *evt);

struct pkt_info sync_chain_tx_prepare(struct ll_evt *evt);

void ext_prim_adv_evt_end_handler(struct ll_evt *evt);

void ext_second_adv_evt_end_handler(struct ll_evt *evt);

void ext_prim_adv_evt_terminate_handler(struct ll_evt * evt);

void ext_second_adv_evt_terminate_handler(struct ll_evt * evt);

enum ll_evt_start_type htimer_ext_prim_adv_evt_start(struct ll_evt *evt);

enum ll_evt_start_type htimer_ext_second_adv_evt_start(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_prim_adv_tx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_second_adv_tx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_prim_adv_evt_rx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_second_adv_evt_rx_end(struct ll_evt *evt);

bool htimer_ext_prim_adv_evt_header_rx(struct ll_evt *evt,bool third_byte,uint8_t *remain_length);

bool htimer_ext_second_adv_evt_header_rx(struct ll_evt *evt,bool third_byte,uint8_t *remain_length);

enum ll_evt_transition_type htimer_ext_prim_adv_evt_sync_timeout(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_second_adv_evt_sync_timeout(struct ll_evt *evt);

#endif

