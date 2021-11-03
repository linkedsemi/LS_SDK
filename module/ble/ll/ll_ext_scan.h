#ifndef LL_EXT_SCAN_H_
#define LL_EXT_SCAN_H_
#include <stdbool.h>
#include "hci_format.h"
#include "co_error.h"
#include "ll_evt.h"
#include "timer_wrapper.h"

struct prim_scan_rx_env
{
    struct co_list_hdr hdr;
    uint32_t timestamp;
    struct scan_evt_rx_data data;
    uint8_t rx_rssi;
    enum ble_phy phy;
};

struct second_scan_buf_env
{
    struct co_list_hdr hdr;
    uint32_t timestamp;
    uint32_t rx_win_size;
    struct bd_addr AdvA;
    struct bd_addr TargetA;
    struct ADI_field ADI;
    uint8_t evt_type;
    uint8_t AdvA_Type;
    uint8_t TargetA_Type;
    int8_t TxPower;
    union{
        uint8_t ch;
        uint8_t adv_data_length;
    }u;
    enum ble_phy phy;
    enum ble_phy phy2;
    uint8_t rssi;
    struct scan_aux_evt_rx_env data;
};

struct conn_req_data_env
{
    uint32_t AA;
    uint32_t CRCInit:24,
            Hop:5;
    uint16_t WinOffset;
    uint8_t WinSize;
};

enum scan_rsp_status
{
    SCAN_RSP_REQUESTING,
    SCAN_RSP_RECEIVING,
    SCAN_RSP_CHAIN_RECEIVING,
};

struct ll_ext_scan_env
{
    struct ll_evt prim_evt;
    struct ll_evt second_evt;
    struct prim_scan_rx_env *prim_rx;
    struct co_list second_scan;
    uint32_t prim_scan_start_instant;
    union{
        struct {
            timer_t duration;
            timer_t period;
            struct ext_scan_param param;
            bool duration_timeout;
            enum scan_rsp_status scan_rsp_stat;
            uint8_t filter_dup;
        }scan;
        struct {
            uint32_t conn_req_end_time;
            struct conn_req_data_env conn_req_data;
            struct ext_create_con_param param;
            uint8_t conn_req_sent;
        }init;
    }u;
    struct adv_scan_header_lsb prim_adv_header_lsb;
    uint8_t current_phy_idx;
    uint8_t scanning;
    uint8_t initiating;
};

void ll_ext_scan_env_reset(void);

enum co_error ll_ext_scan_set_param_legacy_cmd(struct le_scan_param *param);

bool ll_ext_scan_enable_scan_legacy_cmd(struct hci_le_set_scan_en_cmd *cmd,enum co_error *err);

enum co_error ll_ext_scan_initiating_start_legacy_cmd(struct le_create_con_param *param);

enum co_error ll_ext_scan_set_param(struct ext_scan_param *param);

bool ll_ext_scan_enable_scan(struct hci_le_set_ext_scan_en_cmd *cmd,enum co_error *err);

enum co_error ll_ext_scan_initiating_start(struct ext_create_con_param *param);

bool ll_ext_scan_initiating_cancel(enum co_error *err);

void ext_prim_scan_evt_end_handler(struct ll_evt *evt);

void ext_second_scan_evt_end_handler(struct ll_evt *evt);

void ext_prim_scan_evt_terminate_handler(struct ll_evt * evt);

void ext_second_scan_evt_terminate_handler(struct ll_evt * evt);

enum ll_evt_start_type htimer_ext_prim_scan_evt_start(struct ll_evt *evt);

enum ll_evt_start_type htimer_ext_second_scan_evt_start(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_prim_scan_tx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_second_scan_tx_end(struct ll_evt *evt);

bool htimer_ext_prim_scan_evt_header_rx(struct ll_evt *evt,bool third_byte,uint8_t *remain_length);

bool htimer_ext_second_scan_evt_header_rx(struct ll_evt *evt,bool third_byte,uint8_t *remain_length);

enum ll_evt_transition_type htimer_ext_prim_scan_evt_rx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_second_scan_evt_rx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_prim_scan_evt_sync_timeout(struct ll_evt *evt);

enum ll_evt_transition_type htimer_ext_second_scan_evt_sync_timeout(struct ll_evt *evt);

uint8_t *ext_header_extract(uint8_t *payload,struct ext_header_field_param *param);

#endif

