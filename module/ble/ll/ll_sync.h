#ifndef LL_SYNC_H_
#define LL_SYNC_H_
#include "ll_evt.h"
#include "hci_format.h"
#include "per_adv_list.h"
#include "timer_wrapper.h"

enum per_sync_opt
{
    /**
     * Use the Periodic Advertiser List to determine which advertiser to listen to, otherwise use the Advertising SID,
     * Advertising Address Type and Advertising Address parameters
     */
    PER_SYNC_FILT_USE_PAL_POS        = 0,
    PER_SYNC_FILT_USE_PAL_BIT        = 0x01,
    /// Periodic advertising reports initially enabled or disabled (default enabled)
    PER_SYNC_REP_INIT_DIS_POS        = 1,
    PER_SYNC_REP_INIT_DIS_BIT        = 0x02,
};

struct sync_adv_env
{
    struct adv_current_tx_env current_tx;
    struct co_list data[2];
    uint32_t next_timestamp;
    struct le_periodic_adv_param param;
    uint8_t current;
    uint8_t update;
    bool started;
    uint8_t handle;
};

struct sync_evt_rx_env
{
    struct co_list_hdr hdr;
    struct scan_aux_evt_rx_env data;
    int8_t tx_power;
    int8_t rssi;
    uint8_t cte_type;
    uint8_t data_status;
    uint8_t adv_data_length;
    uint8_t sync_hdl;
};

struct sync_scan_env
{
    struct sync_evt_rx_env *rx;
    struct per_adv_list_env *adv_info;
    timer_t sync_timeout_timer;
    struct per_adv_create_sync_param param;
    bool chain_header;
    bool synced;
    bool timeout;
};

struct sync_env
{
    struct co_list_hdr hdr;
    struct ll_evt evt;
    union
    {
        struct sync_adv_env adv;
        struct sync_scan_env scan;
    }u;
    uint32_t sync_anchor;
    uint16_t interval;
    uint16_t evt_counter;
    uint32_t crc_init:24;
    struct le_chnl_map channel_map;
    bool enabled;
    bool adv;
};

void ll_sync_env_reset(void);

struct sync_env *ll_sync_env_alloc(void);

void ll_sync_env_release(struct sync_env *ptr);

void ll_sync_per_adv_env_init(struct sync_env *env,uint8_t handle);

void ll_sync_per_adv_start(struct sync_env *env,enum ble_phy phy,bool tx_coded_125k);

void ll_sync_scan_sync_start(struct sync_env *env,struct ll_evt *aux_evt,struct SyncInfo_field *SyncInfo);

void sync_evt_end_handler(struct ll_evt *evt);

void sync_evt_terminate_handler(struct ll_evt * evt);

enum ll_evt_start_type htimer_sync_evt_start(struct ll_evt *evt);

enum ll_evt_transition_type htimer_sync_evt_tx_end(struct ll_evt *evt);

enum ll_evt_transition_type htimer_sync_evt_rx_end(struct ll_evt *evt);

bool htimer_sync_evt_header_rx(struct ll_evt *evt,bool third_byte,uint8_t *remain_length);

enum ll_evt_transition_type htimer_sync_evt_sync_timeout(struct ll_evt *evt);

enum co_error ll_sync_create(struct per_adv_create_sync_param *param);

enum co_error ll_sync_cancel(void);

bool ll_sync_terminate(uint8_t sync_hdl,enum co_error *err);

struct sync_env *ll_sync_get_pending_env(void);
#endif

