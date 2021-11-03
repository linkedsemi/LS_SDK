#ifndef LL_EVT_H_
#define LL_EVT_H_
#include <stdint.h>
#include <stdbool.h>
#include "co_list.h"
#include "hci_format.h"
#include "circular_doubly_linked_list.h"
#define BLE_SLOT_TIME (625) //us
#define ADV_CHANNEL_CRC_INIT (0x555555)
#define ADV_ACCESS_ADDRESS (0x8e89bed6)
#define CONNECT_REQ_PAYLOAD_LENGTH (sizeof(struct connect_req_pdu))
#define ADV_EVT_RX_PAYLOAD_MAX (CONNECT_REQ_PAYLOAD_LENGTH)
#define SCAN_EVT_RX_PAYLOAD_MAX (37)
#define AUX_ADV_RX_PAYLOAD_MAX (255)
#define AUX_CONNECT_RSP_PAYLOAD_LENGTH (14)
#define SCAN_REQ_PAYLOAD_LENGTH (12)
#define PKT_HEADER_LENGTH (2)

///BD address type
enum
{
    ///Public BD address
    ADDR_PUBLIC                   = 0x00,
    ///Random BD Address
    ADDR_RAND,
    /// Controller generates Resolvable Private Address based on the
    /// local IRK from resolving list. If resolving list contains no matching
    /// entry, use public address.
    ADDR_RPA_OR_PUBLIC,
    /// Controller generates Resolvable Private Address based on the
    /// local IRK from resolving list. If resolving list contains no matching
    /// entry, use random address.
    ADDR_RPA_OR_RAND,
    /// mask used to determine Address type in the air
    ADDR_MASK                     = 0x01,
    /// mask used to determine if an address is an RPA
    ADDR_RPA_MASK                 = 0x02,
    /// Random device address (controller unable to resolve)
    ADDR_RAND_UNRESOLVED          = 0xFE,
    /// No address provided (anonymous advertisement)
    ADDR_NONE                     = 0xFF,
};


///Advertising event properties values for legacy PDUs
enum
{
    ///Connectable and scannable undirected
    LEGACY_ADV_IND                   = 0x13,
    ///Connectable directed (low duty cycle)
    LEGACY_ADV_DIRECT_LO_IND         = 0x15,
    ///Connectable directed (high duty cycle)
    LEGACY_ADV_DIRECT_HI_IND         = 0x1D,
    ///Connectable directed (received)
    LEGACY_ADV_DIRECT_IND            = 0x15,
    ///Scannable undirected
    LEGACY_ADV_SCAN_IND              = 0x12,
    ///Non-connectable and non-scannable undirected
    LEGACY_ADV_NONCONN_IND           = 0x10,
    ///Scan response to an ADV_IND
    LEGACY_SCAN_RSP_TO_ADV_IND       = 0x1B,
    ///Scan response to an ADV_SCAN_IND
    LEGACY_SCAN_RSP_TO_ADV_SCAN_IND  = 0x1A,
};

///Advertising event properties masks
enum
{
    ///Connectable advertising
    ADV_CON                = 0x01,
    ///Scannable advertising
    ADV_SCAN               = 0x02,
    ///Directed advertising
    ADV_DIRECT             = 0x04,
    ADV_SCAN_RSP           = 0x08,
    ///High duty cycle directed connectable advertising
    ADV_DIRECT_HI          = 0x08,
    ///Use legacy advertising PDUs
    ADV_LEGACY             = 0x10,
    ///Omit advertiser's address from all PDUs ("anonymous advertising")
    ADV_ANONYMOUS          = 0x20,
    ///Include TxPower in the extended header of the advertising PDU
    ADV_TX_PWR             = 0x40,
};

///Advertising pdu Type
enum
{
    /// Undirected advertising
    LL_ADV_CONN_UNDIR                = 0x00,
    /// Directed advertising
    LL_ADV_CONN_DIR,
    /// Non Connectable advertising
    LL_ADV_NONCONN_UNDIR,
    /// Scan Request
    LL_SCAN_REQ,
    /// Scan Response
    LL_SCAN_RSP,
    /// Connect Request
    LL_CONNECT_REQ,
    /// Discoverable advertising
    LL_ADV_DISC_UNDIR,

    LL_ADV_EXT,

    LL_CONNECT_RSP,
    LL_ADV_END
};

enum
{
    ///Clock accuracy at 500PPM
    SCA_500PPM,
    ///Clock accuracy at 250PPM
    SCA_250PPM,
    ///Clock accuracy at 150PPM
    SCA_150PPM,
    ///Clock accuracy at 100PPM
    SCA_100PPM,
    ///Clock accuracy at 75PPM
    SCA_75PPM,
    ///Clock accuracy at 50PPM
    SCA_50PPM,
    ///Clock accuracy at 30PPM
    SCA_30PPM,
    ///Clock accuracy at 20PPM
    SCA_20PPM
};

/// LLID packet
enum
{
    /// Reserved for future use
    LLID_RFU,
    /// Continue
    LLID_CONTINUE,
    /// Start
    LLID_START,
    /// Control
    LLID_CNTL,
    /// End
    LLID_END,
};

enum ble_phy
{
    BLE_1M = 1,
    BLE_2M = 2,
    BLE_CODED = 3,
};

enum ll_evt_mode
{
//    BLE_EVT_ADV_MODE             = 0,
//    BLE_EVT_SCAN_MODE,
    BLE_EVT_TEST_MODE,
    BLE_EVT_CONN_MODE,
    BLE_EVT_EXT_PRIM_ADV_MODE,
    BLE_EVT_EXT_SECOND_ADV_MODE,
    BLE_EVT_EXT_PRIM_SCAN_MODE,
    BLE_EVT_EXT_SECOND_SCAN_MODE,
    BLE_EVT_SYNC_MODE,
    BLE_EVT_MODE_MAX
};

enum ll_evt_transition_type
{
	EVT_TX_RX_TRANSITION,
	EVT_DIR_NO_TRANSITION,
	EVT_END,
};

enum ll_evt_start_type
{
    EVT_START_TX,
    EVT_START_RX,
};

enum ext_evt_data_status
{
    STATUS_COMPLETE = 0,
    STATUS_INCOMPLETE = 1,
    STATUS_TRUNCATED = 2,
    STATUS_MASK = 0x60,
    STATUS_POS = 5,
};

struct pkt_info
{
    uint16_t pdu_length;
    uint8_t cte_time;
};

struct ll_evt
{
    struct cdll_hdr hdr;
    struct cdll resched;
    struct pkt_info (*tx_data_cfg)(struct ll_evt *);
    void (*crypto_cfg)(struct ll_evt *);
    uint32_t access_address;
    uint32_t timestamp;
    uint32_t anchor;
    uint32_t rx_win_size;
    uint32_t min_duration;
    struct pkt_info pkt;
    enum ll_evt_mode mode;
    enum ble_phy tx_phy;
    bool tx_coded_125k;
    enum ble_phy rx_phy;
    bool rx_coded_125k;
    uint8_t ch;
    uint8_t tx_pwr;
    uint8_t rx_rssi;
    bool rx_crc_valid;
    bool rx_mic_error;
    bool anchor_valid;
};


struct cte_info
{
	uint8_t time:5,
		RFU:1,
		type:2;
}__attribute__((packed));

struct conn_req_lldata
{
    uint32_t AA;
    uint32_t CRCInit:24;
    uint8_t WinSize;
    uint16_t WinOffset;
    uint16_t Interval;
    uint16_t Latency;
    uint16_t Timeout;
    struct le_chnl_map ChM;
    uint8_t Hop:5,
            SCA:3;	
}__attribute__((packed));

struct connect_req_pdu
{
    struct bd_addr InitA;
    struct bd_addr AdvA;
	struct conn_req_lldata LLData;
}__attribute__((packed));

struct adv_scan_header_lsb
{
    uint8_t pdu_type:4,
            rfu:1,
            chsel:1,
            txadd:1,
            rxadd:1;
}__attribute__((packed));

struct adv_evt_rx_data
{
    struct adv_scan_header_lsb header_lsb;
    uint8_t length;
    uint8_t payload[ADV_EVT_RX_PAYLOAD_MAX];
}__attribute__((packed));

struct scan_evt_rx_data
{
    struct adv_scan_header_lsb header_lsb;
    uint8_t length;
    uint8_t payload[SCAN_EVT_RX_PAYLOAD_MAX];
}__attribute__((packed));

struct scan_aux_evt_rx_env
{
    struct adv_scan_header_lsb header_lsb;
    uint8_t length;
    uint8_t data[AUX_ADV_RX_PAYLOAD_MAX];
}__attribute__((packed));

struct extended_header
{
    uint8_t ext_header_length:6,
            adv_mode:2;
};

struct extended_header_flag
{
    uint8_t AdvA:1,
            TargetA:1,
            CTEInfo:1,
            ADI:1,
            AuxPtr:1,
            SyncInfo:1,
            TxPower:1,
            rfu1:1;
};

struct ADI_field
{
    uint16_t DID:12,
             SID:4;
}__attribute__((packed));

struct AuxPtr_field
{
    uint32_t ch_idx:6,
             ca:1,
             offset_units:1,
             aux_offset:13,
             aux_phy:3;
}__attribute__((packed));

struct SyncInfo_field
{
    uint16_t sync_pkt_offset:13,
             offset_units:1,
             rfu:2;
    uint16_t interval;
    struct le_chnl_map ch_map;
    uint32_t access_addr;
    uint32_t crc_init:24;
    uint16_t evt_counter;
}__attribute__((packed));

struct ext_header_field_param
{
    struct extended_header *ext_header;
    struct extended_header_flag *flag;
    struct bd_addr *AdvA;
    struct bd_addr *TargetA;
    struct cte_info *CTEInfo;
    struct ADI_field *ADI;
    struct AuxPtr_field *AuxPtr;
    struct SyncInfo_field *SyncInfo;
    int8_t *TxPower;
    uint8_t *ACAD;
    uint8_t ACAD_Length;
};

struct adv_data_list
{
    struct co_list_hdr hdr;
    uint8_t length;
    uint8_t data[];
};

struct adv_current_tx_env
{
    struct adv_data_list *data;
    uint8_t offset;
    uint8_t remain_length;
};

struct test_header_lsb
{
    uint8_t type : 4,
            rfu0 : 1,
            cp : 1,
            rfu1 : 2;
};

struct test_evt_rx_header
{
    struct test_header_lsb header_lsb;
    uint8_t length;
    struct cte_info cte;
}__attribute__((packed));

#define T_IFS (150)
#define CONN_DATA_MAX_LEN 251
#define CONN_CTR_DATA_MAX_LEN 26
#define BLE_AIR_PKT_CRC_LENGTH 3


uint32_t ll_get_window_widening(uint8_t sca,uint32_t time_since_last_anchor);

void ll_winsize_winoffset_generate(uint16_t intv,uint8_t *winsize,uint16_t *winoffset);

uint8_t ll_get_whiten_init_val(uint8_t ch);

void ll_whiten_init_table_init(void);

#endif
