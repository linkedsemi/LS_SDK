#ifndef EVT_CTRL_H_
#define EVT_CTRL_H_
#include "ll_evt.h"
#include "ll_config.h"
#include "hci_format.h"
#include "ll_port.h"
#include "field_manipulate.h"

#define CCM_IV_SIZE 8
#define AS_SOON_AS_POSSIBLE_DELAY US2HCLK(250)
#define EVT_START_IN_ADVANCE US2HCLK(200)

struct ll_crypto_env
{
	uint32_t key[BLE_KEY_LEN/sizeof(uint32_t)];
	uint32_t iv[CCM_IV_SIZE/sizeof(uint32_t)];
	uint32_t local_cnt_lsb;
	uint32_t peer_cnt_lsb;
	uint8_t local_cnt_msb;
	uint8_t peer_cnt_msb;
};

extern uint8_t ll_default_tx_pwr;
extern uint8_t tx_rampup_time;
extern uint8_t tx_rampdown_time_minus_1;
extern uint8_t rx_rampup_time;
extern uint8_t rx_path_delay_1m_phy;
extern uint8_t rx_path_delay_2m_phy;
extern uint8_t tx_path_delay_1m_phy;
extern uint8_t tx_path_delay_2m_phy;
extern void (*rf_tx_cfg_fn)(enum ble_phy phy,uint8_t ch,uint8_t tx_pwr);
extern void (*rf_rx_cfg_fn)(enum ble_phy phy,uint8_t ch);
#ifdef LE501X
struct tx_desc{
    uint16_t nextptr:14,
                reserved0:1,
                txdone:1;
    union{
        uint16_t txllid:2,
                txnesn:1,
                txsn:1,
                txmd:1,
                txcp:1,
                txaclrfu:2,
                txlen:8;
        uint16_t txtype0:4,
                txadvrfu:1,
                txchsel:1,
                txtxadd:1,
                txrxadd:1,
                txadvlen:8;
    }u1;
    uint16_t txdataptr;
    uint16_t txaelength:6,
            txaemode:2,
            txadva:1,
            txtgta:1,
            txcte:1,
            txadi:1,
            txauxptr:1,
            txsync:1,
            txpow:1,
            txrsvd:1;
    uint16_t tx_ll_ch:6,
            txaux_ca:1,
            txauxoffset_unit:1,
            txauxoffset_l:8;
    uint16_t txauxoffset_m:5,
            txaux_phy:3;
    uint16_t txaeheader_dataptr;
    uint16_t txctetime:5,
            txcterfu:1,
            txctetype:2;
}__attribute__((aligned(4)));

struct rx_desc{
    uint16_t nextptr:14,
            reserved0:1,
            rxdone:1;
    union{
        uint16_t conn_syncerr:1,
                conn_rxtimeerr:1,
                conn_lenerr:1,
                conn_crcerr:1,
                conn_micerr:1,
                conn_lliderr:1,
                conn_snerr:1,
                conn_nesnerr:1,
                reserved1:7,
                conn_rxcteerr:1;
        uint16_t adv_syncerr:1,
                adv_rxtimeerr:1,
                adv_lenerr:1,
                adv_crcerr:1,
                adv_priverr:1,
                adv_typeerr:1,
                bdaddr_match:1,
                peer_add_match:1,
                in_peradvl:1,
                in_whl:1,
                dev_filtering_ok:1,
                advmodeerr:1,
                followauxptr:1,
                reserved2:2,
                adv_rxcteerr:1;
        uint16_t rxstatisom0;
    }u1;
    union{
        uint16_t rxllid:2,
                rxnesn:1,
                rxsn:1,
                rxmd:1,
                rxcp:1,
                rxaclrfu:2,
                rxlen:8;
        uint16_t rxtype:4,
                rxadvrfu:1,
                rxchsel:1,
                rxtxadd:1,
                rxrxadd:1,
                rxadvlen:8;
        uint16_t rxphisom0;
    }u2;
    uint16_t rxrssi:8,
            used_chd_idx:6,
            rate:2;
    uint16_t rxclknsync0;
    uint16_t rxclknsync1:12;
    uint16_t rxfcntsync:10,
            reserved3:1,
            rxlinklbl:5;
    uint16_t rxwpalptr;
    uint16_t rxralptr;
    uint16_t rxaelength:6,
            rxaemode:2,
            rxadva:1,
            rxtgta:1,
            rxcte:1,
            rxadi:1,
            rxauxptr:1,
            rxsync:1,
            rxpow:1,
            rxrsvd:1;
    uint16_t rxctetime:5,
            rxcterfu:1,
            rxctetype:2,
            nbrxiqsamp:8;
    uint16_t rxcteptr;
}__attribute__((aligned(4)));

uint32_t htimer_current_get();
__attribute__((always_inline)) static inline uint8_t htimer_irq1_mask_status_get()
{
    return REG_FIELD_RD(MAC->INTCNTL1,RWMAC_TIMESTAMPTGT1INTMSK);
}
__attribute__((always_inline)) static inline bool mac_fifo_empty()
{
    return true;
}
#else
__attribute__((always_inline)) static inline void tx_underrun_irq1_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK1,MAC_TX_UNDERRUN_INT,1);
}

__attribute__((always_inline)) static inline void rx_overrun_irq1_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK1,MAC_RX_OVERRUN_INT,1);
}

__attribute__((always_inline)) static inline void aes_done_irq2_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK2,MAC_AES_DONE_INT,1);
}

__attribute__((always_inline)) static inline void wakeup_irq2_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK2,MAC_WAKEUP_INT,1);
}

__attribute__((always_inline)) static inline uint32_t htimer_current_get()
{
    return MAC->CURRENT_TIME;
}

__attribute__((always_inline)) static inline void htimer_match_set(uint32_t count)
{
    MAC->TARGET_TIME1 = count;
}

__attribute__((always_inline)) static inline uint32_t htimer_match_get()
{
    return MAC->TARGET_TIME1;
}

__attribute__((always_inline)) static inline void htimer_irq1_mask()
{
    REG_FIELD_WR(MAC->INT_MASK1,MAC_TIMER1_INT,0);
}

__attribute__((always_inline)) static inline void htimer_irq1_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK1, MAC_TIMER1_INT, 1);
}

__attribute__((always_inline)) static inline uint8_t htimer_irq1_mask_status_get()
{
    return REG_FIELD_RD(MAC->INT_MASK1,MAC_TIMER1_INT);
}

__attribute__((always_inline)) static inline void htimer_irq_clr()
{
    MAC->INT_CLR = FIELD_BUILD(MAC_TIMER1_INT,1);
}

__attribute__((always_inline)) static inline void sync_found_irq1_mask()
{
    REG_FIELD_WR(MAC->INT_MASK1,MAC_RX_SYNC_FOUND_INT,0);
}

__attribute__((always_inline)) static inline void sync_found_irq_clr()
{
    MAC->INT_CLR = FIELD_BUILD(MAC_RX_SYNC_FOUND_INT,1);
}

__attribute__((always_inline)) static inline void sync_found_irq1_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK1,MAC_RX_SYNC_FOUND_INT,1);
}

__attribute__((always_inline)) static inline void ble_tx_fifo_int_clr()
{
    MAC->INT_CLR = FIELD_BUILD(MAC_TX_FIFO_INT,1);
}

__attribute__((always_inline)) static inline void ble_rx_fifo_int_clr()
{
    MAC->INT_CLR = FIELD_BUILD(MAC_RX_FIFO_INT,1);
}

__attribute__((always_inline)) static inline bool mac_fifo_empty()
{
    return REG_FIELD_RD(MAC->FSM_STAT, MAC_FIFO_LEVEL) == 0;
}

__attribute__((always_inline)) static inline void ble_rx_fifo_int1_mask()
{
    REG_FIELD_WR(MAC->INT_MASK1, MAC_RX_FIFO_INT, 0);
}

__attribute__((always_inline)) static inline void ble_tx_fifo_int1_mask()
{
    REG_FIELD_WR(MAC->INT_MASK1, MAC_TX_FIFO_INT, 0);
}


__attribute__((always_inline)) static inline uint32_t ble_irq_stat1_get()
{
    return MAC->INT_STAT1;
}

__attribute__((always_inline)) static inline uint32_t ble_irq_stat2_get()
{
    return MAC->INT_STAT2;
}

__attribute__((always_inline)) static inline void fifo_tx_dir_set()
{
    MAC->FIFO_CFG = FIELD_BUILD(MAC_FIFO_DIR, 0) | FIELD_BUILD(MAC_FIFO_CLR, 0);
}

__attribute__((always_inline)) static inline void fifo_rx_dir_set()
{
    MAC->FIFO_CFG = FIELD_BUILD(MAC_FIFO_DIR, 1) | FIELD_BUILD(MAC_FIFO_CLR, 0);
}

__attribute__((always_inline)) static inline void tx_fifo_set(uint8_t data)
{
    MAC->FIFO_TX = data;
}

__attribute__((always_inline)) static inline void tx_header_payload_length_config(uint8_t payload_length,uint8_t cte_info_en)
{
    MAC->TX_LEN = FIELD_BUILD(MAC_TX_PAYLOAD_LEN, payload_length) | FIELD_BUILD(MAC_TX_CTE_INFO_EN, cte_info_en);
}

__attribute__((always_inline)) static inline void ble_tx_fifo_int1_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK1, MAC_TX_FIFO_INT, 1);
}

__attribute__((always_inline)) static inline void aes_enable()
{
    MAC->CRYPTO_CTRL = FIELD_BUILD(MAC_AES_HEAD_MASK, 0xe3) | FIELD_BUILD(MAC_AES_EN, 1);
}

__attribute__((always_inline)) static inline void aes_disable()
{
    MAC->CRYPTO_CTRL = FIELD_BUILD(MAC_AES_EN, 0);
}

__attribute__((always_inline)) static inline void ble_tx_fsm_trigger_disable()
{
    MAC->TX_CTRL = FIELD_BUILD(MAC_TX_FSM_EN,0);
}

__attribute__((always_inline)) static inline void ble_rx_fsm_trigger_disable()
{
    MAC->RX_CTRL = FIELD_BUILD(MAC_RX_FSM_EN,0);
}

__attribute__((always_inline)) static inline void ble_rx_fsm_reset()
{
    MAC->RX_CTRL = FIELD_BUILD(MAC_RX_FSM_STOP,1)|FIELD_BUILD(MAC_RX_FSM_EN,0);
}

__attribute__((always_inline)) static inline void ble_tx_fsm_reset()
{
    MAC->TX_CTRL = FIELD_BUILD(MAC_TX_FSM_STOP,1)|FIELD_BUILD(MAC_TX_FSM_EN,0);
}

__attribute__((always_inline)) static inline uint8_t rx_fifo_get()
{
    return MAC->FIFO_RX;
}

__attribute__((always_inline)) static inline void ble_rx_fifo_int1_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK1, MAC_RX_FIFO_INT, 1);
}

__attribute__((always_inline)) static inline bool get_crc_valid()
{
    return REG_FIELD_RD(MAC->RX_STATUS,MAC_RX_CRC_SHIFT) == 0;
}

__attribute__((always_inline)) static inline bool get_mic_error()
{
    return REG_FIELD_RD(MAC->RX_STATUS,MAC_RX_MIC_ERROR);
}

__attribute__((always_inline)) static inline uint32_t get_rx_time()
{
    return MAC->RX_TIME;
}

__attribute__((always_inline)) static inline void sleep_req_clr()
{
    REG_FIELD_WR(MAC->SLEEP_CTRL,MAC_SLEEP_REQ,0);
}

__attribute__((always_inline)) static inline uint32_t sleep_anchor_get()
{
    return MAC->SLEEP_ANCHOR;
}

__attribute__((always_inline)) static inline void sleep_irq_clr()
{
    MAC->INT_CLR = FIELD_BUILD(MAC_SLEEP_INT,1);
}

__attribute__((always_inline)) static inline void mac_wakeup_req()
{
    REG_FIELD_WR(MAC->SLEEP_CTRL,MAC_WAKEUP_REQ,1);
}

__attribute__((always_inline)) static inline void time_adjust_set(uint32_t val)
{
    MAC->TIME_ADJUST = val;
}

__attribute__((always_inline)) static inline void wakeup_int_clr()
{
    MAC->INT_CLR = FIELD_BUILD(MAC_WAKEUP_INT,1);
}

__attribute__((always_inline)) static inline void wakeup_req_clr()
{
    REG_FIELD_WR(MAC->SLEEP_CTRL,MAC_WAKEUP_REQ,0);
}

__attribute__((always_inline)) static inline void ble_timer2_irq2_unmask()
{
    REG_FIELD_WR(MAC->INT_MASK2,MAC_TIMER2_INT,1);
}

__attribute__((always_inline)) static inline void ble_timer2_irq2_mask()
{
    REG_FIELD_WR(MAC->INT_MASK2,MAC_TIMER2_INT,0);
}

__attribute__((always_inline)) static inline void ble_timer2_irq_clr()
{
    MAC->INT_CLR = FIELD_BUILD(MAC_TIMER2_INT,1);
}

__attribute__((always_inline)) static inline bool ble_timer2_irq2_mask_status_get()
{
    return REG_FIELD_RD(MAC->INT_MASK2,MAC_TIMER2_INT);
}

__attribute__((always_inline)) static inline void ble_timer2_match_set(uint32_t count)
{
    MAC->TARGET_TIME2 = count;
}

__attribute__((always_inline)) static inline uint32_t ble_timer2_match_get()
{
    return MAC->TARGET_TIME2;
}

__attribute__((always_inline)) static inline void aes_done_int_clr()
{
    MAC->INT_CLR = FIELD_BUILD(MAC_AES_DONE_INT,1);
}

__attribute__((always_inline)) static inline void crc_whiten_init_val_config(uint32_t crc_init,uint8_t whiten_init,bool whiten_disabled)
{
    MAC->CRC_WHITEN = FIELD_BUILD(MAC_CRC_INIT, crc_init)
                        | FIELD_BUILD(MAC_WHITEN_INIT, whiten_init)
                        | FIELD_BUILD(MAC_WHITEN_BYPASS, whiten_disabled);
}

__attribute__((always_inline)) static inline void whiten_disable()
{
    REG_FIELD_WR(MAC->CRC_WHITEN,MAC_WHITEN_BYPASS,1);
}

__attribute__((always_inline)) static inline void whiten_enable()
{
    REG_FIELD_WR(MAC->CRC_WHITEN,MAC_WHITEN_BYPASS,0);
}

__attribute__((always_inline)) static inline void crc_init_config(uint32_t crc_init)
{
    REG_FIELD_WR(MAC->CRC_WHITEN,MAC_CRC_INIT,crc_init);
}

__attribute__((always_inline)) static inline void whiten_init_config(uint8_t whiten_init)
{
    REG_FIELD_WR(MAC->CRC_WHITEN,MAC_WHITEN_INIT,whiten_init);
}

__attribute__((always_inline)) static inline void sleep_req_set()
{
    REG_FIELD_WR(MAC->SLEEP_CTRL,MAC_SLEEP_REQ,1);
}

#endif

void mac_hw_init(void);

void ll_evt_init(struct ll_evt *evt,enum ll_evt_mode mode);

void adv_scan_evt_init(struct ll_evt *evt,enum ll_evt_mode mode);

void evt_ctrl_reset(void);

bool evt_cancel(bool ongoing,struct ll_evt *evt);

bool evt_remove_no_evt_end(struct ll_evt *evt);

bool evt_remove(struct ll_evt *evt);

bool evt_remove_swint(struct ll_evt *evt);

bool evt_insert_update_timestamp(struct ll_evt *evt);

bool evt_insert(struct ll_evt *evt);

bool evt_insert_swint(struct ll_evt *evt);

bool evt_insert_no_timestamp(struct ll_evt *evt,bool anchor_valid);

bool evt_insert_no_timestamp_swint(struct ll_evt *evt,bool anchor_valid);

uint32_t evt_available_time_slice_get(uint32_t start,uint32_t duration);

bool evt_continue(enum ble_phy phy,uint16_t pdu_length,uint8_t cte_time,bool coded_125k);

bool event_limit_get(uint32_t *limit);

void tx_fifo_fill_bd_addr(struct bd_addr *addr);

void tx_fifo_set(uint8_t data);

void pkt_transmit_specific(uint8_t header_lsb,uint8_t payload_total_length,uint8_t *cte_info,void (*data_fill_func)(void *),void *param,uint8_t (*specific_tx_data_set)(uint8_t,void *),void *tx_data_set_param);

void ble_tx_phy_ch_set(enum ble_phy phy,uint8_t ch,uint8_t tx_pwr,bool tx_coded_125k);

void ll_set_rx_ptr(uint8_t *ptr);

void conn_crypto_enable(struct ll_crypto_env *crypto,bool master,bool tx);

uint32_t get_pkt_duration_us(enum ble_phy phy,uint16_t pdu_length,uint8_t cte_time,bool coded_125k);

void ble_pkt_isr(void);

void ble_util_isr(void);

void ble_timer2_match_set(uint32_t count);

void timer2_isr_func_set(void (*isr)());

void crc_whiten_init_val_config(uint32_t crc_init,uint8_t whiten_init,bool whiten_disabled);

void mac_sleep_status_sync(void);

uint32_t mac_sleep(void);

void aes_128_req(uint8_t *data,uint8_t *key);

void ifs_transition_set(bool);

#endif

