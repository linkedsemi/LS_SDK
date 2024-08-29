#ifndef EVT_CTRL_H_
#define EVT_CTRL_H_
#include "ll_evt.h"
#include "ll_config.h"
#include "hci_format.h"
#include "ll_port.h"
#include "field_manipulate.h"

#define CCM_IV_SIZE 8
#ifdef LE501X
#define AS_SOON_AS_POSSIBLE_DELAY US2HCLK(1000)
#define EVT_START_IN_ADVANCE US2HCLK(600)
#else
#define AS_SOON_AS_POSSIBLE_DELAY US2HCLK(250)
#define EVT_START_IN_ADVANCE US2HCLK(200)
#endif

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
        struct{
            uint16_t txllid:2,
                    txnesn:1,
                    txsn:1,
                    txmd:1,
                    txcp:1,
                    txaclrfu:2,
                    txlen:8;
        }txphce;
        struct{
            uint16_t txtype0:4,
                    txadvrfu:1,
                    txchsel:1,
                    txtxadd:1,
                    txrxadd:1,
                    txadvlen:8;
        }txphadv;
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
            txaux_phy:3,
            reserved1:8;
    uint16_t txaeheader_dataptr;
    uint16_t txctetime:5,
            txcterfu:1,
            txctetype:2,
            reserved2:8;
}__attribute__((aligned(4)));

struct rx_desc{
    uint16_t nextptr:14,
            reserved0:1,
            rxdone:1;
    union{
        struct{
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
        }rxstatce;
        struct {
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
        }rxstatadv;
        uint16_t rxstatisom0;
    }u1;
    union{
        struct{
            uint16_t rxllid:2,
                    rxnesn:1,
                    rxsn:1,
                    rxmd:1,
                    rxcp:1,
                    rxaclrfu:2,
                    rxlen:8;
        }rxphce;
        struct{
            uint16_t rxtype:4,
                    rxadvrfu:1,
                    rxchsel:1,
                    rxtxadd:1,
                    rxrxadd:1,
                    rxadvlen:8;
        }rxphadv;
        uint16_t rxphisom0;
    }u2;
    uint16_t rxrssi:8,
            used_chd_idx:6,
            rate:2;
    uint16_t rxclknsync0;
    uint16_t rxclknsync1;
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
    uint16_t rxdataptr;
    uint16_t rxctetime:5,
            rxcterfu:1,
            rxctetype:2,
            nbrxiqsamp:8;
    uint16_t rxcteptr;
}__attribute__((aligned(4)));

struct ex_table{
    uint16_t mode:3,
            status:3,
            iso:1,
            rsvd:1,
            ae_nps:1,
            reserved0:1,
            spa:1,
            sch_prio1:5;
    uint16_t rawstp_lsb;
    uint16_t rawstp_msb;
    uint16_t finestp;
    uint16_t csptr;
    uint16_t prio1d:15,
            prio1d_unit:1;
    uint16_t sch_prio2:5,
            reserved1:3,
            sch_prio3:5,
            reserved2:3;
    uint16_t reserved3:8,
            pti_prio:5,
            reserved4:3;
}__attribute__((aligned(4)));

struct control_struct
{
    uint16_t format:5,
            reserved0:3,
            dnabort:1,
            rxbsy_en:1,
            txbsy_en:1,
            reserved01:5;
    uint16_t priv_npub:1,
            rxcrypt_en:1,
            txcrypt_en:1,
            crypt_mode:1,
            mic_mode:1,
            nullrxllidflt:1,
            sas:1,
            reserved1:1,
            linklbl:5,
            reserved11:3;
    uint16_t isolinkcntl;
    uint16_t txrate:2,
            rxrate:2,
            auxrate:2,
            reserved2:2,
            txthr:4,
            rxthr:4;
    uint16_t bdaddr_0;
    uint16_t bdaddr_1;
    uint16_t bdaddr_2;
    uint16_t syncword_l;
    uint16_t syncword_m;
    uint16_t crcinit_l;
    uint16_t crcinit_m:8,
            rxmaxctebuf:8;
    uint16_t ral_en:1,
            ral_mode:1,
            local_rpa_sel:1,
            peradv_filt_en:1,
            ral_resol_en:1,
            reserved3:3,
            filter_policy:8;
    uint16_t ch_idx:6,
            reservedd4:2,
            hopint:5,
            hop_mode:2,
            fh_en:1;
    uint16_t txpwr:8,
            ext_pa_en:1,
            ends_on_sac:1,
            rxmafserr:1,
            rxbfmicerr:1,
            nesn:1,
            sn:1,
            lastempty:1,
            rxbuff_full:1;
    uint16_t dfen:1,
            dffilteren:1,
            dftype:2,
            dfsampcntl:2,
            dfswcntl:2,
            dfrspen:1,
            reserved8:7;
    uint16_t rxwinsz:15,
            rxwide:1;
    uint16_t isotxdescptr;
    uint16_t isorxdescptr;
    uint16_t acltxdescptr;
    uint16_t rx_ant_patt_length:7,
            reserved5:1,
            max_samp_cte:5,
            reserved6:2,
            dfrsp:1;
    uint16_t rx_antenna_id_ptr;
    uint16_t tx_ant_patt_length;
    uint16_t tx_antenna_id_ptr;
    union{
        uint16_t winoffset;
        uint16_t minevtime;
    }u0;
    uint16_t maxevtime;
    union{
        uint16_t conninterval;
        uint16_t chmap0;
    }u1;
    uint16_t chmap1;
    uint16_t chmap2:5,
            advchmap:3,
            reserved7:2,
            ch_aux:6;
    uint16_t aclrxmaxbuff:8,
            isorxmaxbuf:8;
    uint16_t rxmaxtime;
    union{
        uint16_t sk0;
        uint16_t adv_bd_addr0;
        uint16_t peer_ralptr;
    }u2;
    union{
        uint16_t sk1;
        uint16_t adv_bd_addr1;
    }u3;
    union{
        uint16_t sk2;
        uint16_t adv_bd_addr2;
    }u4;
    union{
        uint16_t sk3;
        uint16_t adv_bd_addr3;
    }u5;
    union{
        uint16_t sk4;
        uint16_t auxtxdescptr;
    }u6;
    union{
        uint16_t sk5;
        uint16_t winoffset_2m;
    }u7;
    union{
        uint16_t sk6;
        uint16_t conninterval_2m;
    }u8;
    union{
        uint16_t sk7;
        uint16_t winoffset_lr;
    }u9;
    union{
        uint16_t iv0;
        uint16_t conninterval_lr;
    }u10;
    uint16_t iv1;
    uint16_t iv2;
    uint16_t iv3;
    union{
        uint16_t txwinoffset;
        uint16_t txccmpktcnt0;
    }u11;
    union{
        struct{
            uint16_t prev_adv_pkt_type:3,
                    prev_adv_mode:2,
                    prev_lam:1,
                    prev_pam:1,
                    prev_cte:1;
        }extadvstat;
        uint16_t txccmpktcnt1;
    }u12;
    uint16_t txccmpktcnt2;
    uint16_t rxccmpktcnt0;
    uint16_t rxccmpktcnt1;
    uint16_t rxccmpktcnt2;
    uint16_t evtcnt;
    uint16_t evtcnt_offset0;
    uint16_t evtcnt_offset1;
    uint16_t evtcnt_offset2;
    uint16_t isoevtcntl;
    uint16_t isotxrxcntl;
    uint16_t acltxdesccnt:8,
             aclrxdesccnt:8;
    uint16_t isotxrxpktcnt;
}__attribute__((aligned(4)));

extern struct ex_table em_et;
extern struct control_struct em_cs;
extern struct tx_desc adv_scan_tx_desc[];
extern struct rx_desc adv_scan_rx_desc[];
extern struct rx_desc *rx_desc_buf_ptr;
extern struct tx_desc **tx_desc_buf_ptr;
extern uint8_t tx_desc_buf_num;
extern uint8_t rx_desc_buf_num;
extern uint8_t em_adv_rx_buf[];
uint32_t htimer_current_get();
__attribute__((always_inline)) static inline uint8_t htimer_irq1_mask_status_get()
{
    return REG_FIELD_RD(MAC->INTCNTL1,RWMAC_TIMESTAMPTGT1INTMSK);
}

__attribute__((always_inline)) static inline bool mac_fifo_empty()
{
    return true;
}

uint32_t get_pkt_start_time(struct rx_desc *rx,enum ble_phy phy);

uint64_t time_mac2stamp(uint32_t clkn,uint16_t finecnt);

void set_em_et_rawstp_finestp(uint32_t timestamp);

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

