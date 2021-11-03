#ifndef LL_CONN_H_
#define LL_CONN_H_
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "ll_evt.h"
#include "co_list.h"
#include "linked_async_framework.h"
#include "hci_format.h"
#include "timer_wrapper.h"
#include "co_error.h"
#include "ll_hci.h"
#include "evt_ctrl.h"
#include "ll_env.h"
#define LLCP_PDU_CTRDATA_MAX_LENGTH 24
#define CCM_PACKET_COUNTER_SIZE 5
#define SESS_KEY_DIV_LEN    0x08
#define INIT_VECT_LEN       0x04

/// HCI 7.8.33 LE Set Data Length Command
/// Preferred minimum number of payload octets
#define LE_MIN_OCTETS       (27)
/// Preferred minimum number of microseconds
#define LE_MIN_TIME         (328)
/// Preferred minimum number of microseconds LL:4.5.10
#define LE_MIN_TIME_CODED   (2704)
/// Preferred maximum number of payload octets
#define LE_MAX_OCTETS       (251)
/// Preferred maximum number of microseconds
#define LE_MAX_TIME         (2120)
/// Preferred maximum number of microseconds LL:4.5.10
#define LE_MAX_TIME_CODED   (17040)


enum llcp_opcode
{
    /// Connection update request
    LL_CONNECTION_UPDATE_IND_OPCODE,
    /// Channel map request
    LL_CHANNEL_MAP_IND_OPCODE,
    /// Termination indication
    LL_TERMINATE_IND_OPCODE,
    /// Encryption request
    LL_ENC_REQ_OPCODE,
    /// Encryption response
    LL_ENC_RSP_OPCODE,
    /// Start encryption request
    LL_START_ENC_REQ_OPCODE,
    /// Start encryption response
    LL_START_ENC_RSP_OPCODE,
    /// Unknown response
    LL_UNKNOWN_RSP_OPCODE,
    /// Feature request
    LL_FEATURE_REQ_OPCODE,
    /// Feature response
    LL_FEATURE_RSP_OPCODE,
    /// Pause encryption request
    LL_PAUSE_ENC_REQ_OPCODE,
    /// Pause encryption response
    LL_PAUSE_ENC_RSP_OPCODE,
    /// Version indication
    LL_VERSION_IND_OPCODE,
    /// Reject indication
    LL_REJECT_IND_OPCODE,
    /// Slave feature request
    LL_SLAVE_FEATURE_REQ_OPCODE,
    /// Connection parameters request
    LL_CONNECTION_PARAM_REQ_OPCODE,
    /// Connection parameters response
    LL_CONNECTION_PARAM_RSP_OPCODE,
    /// Reject indication extended
    LL_REJECT_EXT_IND_OPCODE,
    /// Ping request
    LL_PING_REQ_OPCODE,
    /// Ping response
    LL_PING_RSP_OPCODE,
    /// Ping request
    LL_LENGTH_REQ_OPCODE,
    /// Ping response
    LL_LENGTH_RSP_OPCODE,
    /// Phy request
    LL_PHY_REQ_OPCODE,
    /// Phy response
    LL_PHY_RSP_OPCODE,
    /// Phy update indication
    LL_PHY_UPDATE_IND_OPCODE,
    /// Min used channels indication
    LL_MIN_USED_CHANNELS_IND_OPCODE,
    /// Opcode length
    LL_OPCODE_MAX_OPCODE,
};

enum llcp_len
{
    LL_CONNECTION_UPDATE_IND_LEN     = 12,
    LL_CHANNEL_MAP_IND_LEN           = 8,
    LL_TERMINATE_IND_LEN             = 2,
    LL_ENC_REQ_LEN                   = 23,
    LL_ENC_RSP_LEN                   = 13,
    LL_START_ENC_REQ_LEN             = 1,
    LL_START_ENC_RSP_LEN             = 1,
    LL_UNKNOWN_RSP_LEN               = 2,
    LL_FEATURE_REQ_LEN               = 9,
    LL_FEATURE_RSP_LEN               = 9,
    LL_PAUSE_ENC_REQ_LEN             = 1,
    LL_PAUSE_ENC_RSP_LEN             = 1,
    LL_VERSION_IND_LEN               = 6,
    LL_REJECT_IND_LEN                = 2,
    LL_SLAVE_FEATURE_REQ_LEN         = 9,
    LL_REJECT_EXT_IND_LEN            = 3,
    LL_CONNECTION_PARAM_REQ_LEN      = 24,
    LL_CONNECTION_PARAM_RSP_LEN      = 24,
    LL_PING_REQ_LEN                  = 1,
    LL_PING_RSP_LEN                  = 1,
    LL_LENGTH_REQ_LEN                = 9,
    LL_LENGTH_RSP_LEN                = 9,
    LL_PHY_REQ_LEN                   = 3,
    LL_PHY_RSP_LEN                   = 3,
    LL_PHY_UPDATE_IND_LEN            = 5,
    LL_MIN_USED_CHANNELS_IND_LEN     = 3,
};

enum llcp_type
{
    LL_NO_CTRL_PROCEDURE,
    LL_CONN_UPD_PROCEDURE,
    LL_CHNL_MAP_PROCEDURE,
    LL_ENCRYPT_START_PROCEDURE,
    LL_ENCRYPT_PAUSE_PROCEDURE,
    LL_FEAT_EXCH_PROCEDURE,
    LL_VER_EXCH_PROCEDURE,
    LL_CONN_PARAM_REQ_PROCEDURE,
    LL_PING_PROCEDURE,
    LL_DATA_LEN_UPD_PROCEDURE,
    LL_PHY_UPD_PROCEDURE,
};

enum conn_encryption_status
{
    CONN_TX_ENCRYPTED_MASK = 0x1,
    CONN_RX_ENCRYPTED_MASK = 0x2,
};

struct ll_terminate_ind_ctrdata
{
    uint8_t error_code;
}__attribute__((packed));

struct ll_conn_upd_req_ctrdata
{
    uint8_t WinSize;
    uint16_t WinOffset;
    uint16_t Interval;
    uint16_t Latency;
    uint16_t Timeout;
    uint16_t Instant;
}__attribute__((packed));

struct ll_ver_ind_ctrdata
{
    struct version_ind ver;
}__attribute__((packed));

struct ll_feat_ctrdata
{
    struct le_features feat_set;
}__attribute__((packed));

struct ll_enc_req_ctrdata
{
    struct rand_nb rand;
    uint16_t ediv;
    uint8_t skdm[SESS_KEY_DIV_LEN];
    uint8_t ivm[INIT_VECT_LEN];
}__attribute__((packed));

struct ll_enc_rsp_ctrdata
{
    uint8_t skds[SESS_KEY_DIV_LEN];
    uint8_t ivs[INIT_VECT_LEN];
}__attribute__((packed));

struct ll_length_ctrdata
{
    uint16_t max_rx_octets;
    uint16_t max_rx_time;
    uint16_t max_tx_octets;
    uint16_t max_tx_time;
}__attribute__((packed));

struct ll_reject_ind_ctrdata
{
    uint8_t error_code;
}__attribute__((packed));

struct ll_reject_ext_ind_ctrdata
{
    uint8_t reject_opcode;
    uint8_t error_code;
}__attribute__((packed));

struct ll_unknown_rsp_ctrdata
{
    uint8_t unknown_type;
}__attribute__((packed));

struct ll_phy_req_rsp_ctrdata
{
    uint8_t tx_phys;
    uint8_t rx_phys;
}__attribute__((packed));

struct ll_phy_upd_ctrdata
{
    uint8_t m2s_phy;
    uint8_t s2m_phy;
    uint16_t instant;
}__attribute__((packed));

struct conn_upd_proc_env
{
    struct ll_conn_upd_req_ctrdata param;
};

struct ll_chnl_map_req_ctrdata
{
    struct le_chnl_map ChM;
    uint16_t Instant;
}__attribute__((packed));

struct chnl_map_proc_env
{
    struct ll_chnl_map_req_ctrdata param;
};

struct encrypt_proc_env
{
    struct ltk ltk;
    struct rand_nb rand;
    uint16_t ediv;
    uint8_t skd[2*SESS_KEY_DIV_LEN];
    bool refresh;
};

struct feat_exch_proc_env
{

};

struct conn_param_req_proc_env
{

};

struct ping_proc_env
{

};

struct data_len_upd_env
{
    struct ll_length_ctrdata data;
};

struct phy_upd_env
{
    struct ll_phy_upd_ctrdata data;
    enum le_phy_opt phy_opt;
    bool instant_waiting;
};

union llcp_env
{
    struct conn_upd_proc_env conn_upd;
    struct chnl_map_proc_env chnl_map;
    struct encrypt_proc_env encrypt;
    struct data_len_upd_env data_len_upd;
    struct phy_upd_env phy_upd;
};

struct conn_header_lsb
{
    uint8_t llid:2,
            nesn:1,
            sn:1,
            md:1,
            cp:1,
            rfu:2;
};

struct conn_data_header
{
    struct conn_header_lsb header_lsb;
    uint8_t length;
    struct cte_info cte;
}__attribute__((packed));

struct conn_data
{
    struct conn_header_lsb header_lsb;
    uint8_t length;
    uint8_t buf_idx;
    uint8_t offset;
};

struct conn_txrx_data
{
    struct co_list_hdr hdr;
    struct conn_data buf;
};

struct conn_rx_ctrl_pdu
{
    enum llcp_opcode opcode;
    uint8_t ctr_data[CONN_CTR_DATA_MAX_LEN];
}__attribute__((packed));

struct conn_rx_ctrl_env
{
    uint8_t length;
    struct conn_rx_ctrl_pdu payload;
};

struct data_length_env
{
    uint16_t connEffectiveMaxTxOctets;
    uint16_t connEffectiveMaxTxTime;
    uint16_t connEffectiveMaxRxOctets;
    uint16_t connEffectiveMaxRxTime;
};

struct llcp_termination_pdu
{
    uint8_t opcode;
    uint8_t err_code;
}__attribute__((packed));

struct llcp_normal_pdu
{
    uint8_t opcode;
    uint8_t ctr_data[LLCP_PDU_CTRDATA_MAX_LENGTH];
}__attribute__((packed));

enum tx_ctrl_buf_idx
{
    LLCP_TX_BUF_TERMINATE_IND,
    LLCP_TX_BUF_LOCAL_PROCEDURE,
    LLCP_TX_BUF_PEER_PROCEDURE,
};

struct llcp_tx_pdu_env
{
    struct llcp_termination_pdu terminate;
    struct llcp_normal_pdu local_proc;
    struct llcp_normal_pdu peer_proc;
};

struct ll_ctrl_procedure
{
    timer_t rsp_timeout_timer;
    union llcp_env env;
    enum llcp_type ctrl_type;
};

struct ll_conn_env{
    struct co_list_hdr hdr;
    struct ll_evt evt;
    struct co_list pending_tx;
    struct co_list received;
    struct co_list sent;
    struct co_list tx_release;
    struct co_list rx_acl_data;
    struct conn_txrx_data *tx;
    struct hci_acl_air_rx_data *rx;
    timer_t supv_to_timer;
    struct ll_ctrl_procedure local;
    struct ll_ctrl_procedure peer;
    struct ll_crypto_env crypto;
    struct data_length_env data_len_ext;    
    struct llcp_tx_pdu_env tx_ctrl;
    struct conn_rx_ctrl_env rx_ctrl;
    uint32_t crc_init:24;
    uint8_t hop:5,
            sca:3;
    uint16_t interval;
    uint16_t slv_latency;
    uint16_t supervision_timeout;
    uint16_t counter;
    struct le_features peer_features;
    struct version_ind peer_ver;
    struct le_chnl_map channel_map;
    struct conn_data_header rx_header;
    struct conn_header_lsb prev_rx_header;
    uint8_t unmapped_channel;
    uint8_t disconnect_reason;
    uint8_t force_disconnect;
    uint8_t csa2;
    uint8_t established;
    uint8_t prev_rx_crc_valid;
    uint8_t nesn;
    uint8_t sn;
    enum conn_encryption_status encrypted;
    uint8_t master;
    uint8_t peer_version_valid;
    uint8_t peer_features_valid;
};

extern uint16_t conn_data_max_len;
extern uint8_t tx_data_buf_num;

enum co_error ll_conn_rd_rem_ver_info(uint16_t conhdl);

void ll_conn_channel_map_update_all(void);

enum co_error get_ll_conn_rssi(uint16_t idx,uint8_t *rssi);

enum co_error ll_conn_disconnect(uint16_t idx,uint8_t reason);

enum co_error ll_conn_update(struct hci_le_con_update_cmd *cmd);

enum co_error ll_conn_start_encryption(struct hci_le_start_enc_cmd *cmd);

enum co_error ll_conn_ltk_reply(uint16_t idx,struct ltk *ltk);

enum co_error ll_conn_set_data_length(uint16_t idx,uint16_t tx_octets,uint16_t tx_time);

enum co_error get_ll_conn_channel_map(uint16_t idx,struct le_chnl_map *buf);

enum co_error ll_conn_get_remote_features(uint16_t idx);

enum co_error ll_conn_rd_phy(uint16_t idx,uint8_t *tx_phy,uint8_t *rx_phy);

enum co_error ll_conn_set_phy(struct hci_le_set_phy_cmd *cmd);

struct ll_conn_env *ll_conn_env_alloc(void);

uint16_t get_ll_conn_env_idx(struct ll_conn_env *env);

struct ll_conn_env *get_ll_conn_env_by_idx(uint16_t idx);

void ll_hci_rx_air_tx_start(struct ll_conn_env *env,struct hci_acl_air_tx_data *buf);

void ll_conn_env_init(struct ll_conn_env *env,bool master,struct conn_req_lldata *lldata,uint32_t conn_req_end_time,bool csa2,enum ble_phy phy);

void conn_evt_end_handler(struct ll_evt *evt);

void conn_evt_terminate_handler(struct ll_evt *evt);

enum ll_evt_start_type htimer_conn_evt_start(struct ll_evt *evt);

enum ll_evt_transition_type htimer_conn_evt_rx_end(struct ll_evt *evt);

bool htimer_conn_evt_header_rx(struct ll_evt *evt,bool third_byte,uint8_t *remain_length);

enum ll_evt_transition_type htimer_conn_tx_end(struct ll_evt *evt);

void rx_buf_release_protected_swint(struct hci_acl_air_rx_data *ptr);

uint8_t hci_acl_data_rx_buf_release(struct hci_acl_air_tx_data *ptr);

struct hci_acl_air_tx_data *hci_acl_data_rx_buf_alloc(void);

enum ll_evt_transition_type htimer_conn_evt_sync_timeout(struct ll_evt *evt);

#endif

