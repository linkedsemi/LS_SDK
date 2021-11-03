#ifndef EVT_CTRL_H_
#define EVT_CTRL_H_
#include "ll_evt.h"
#include "ll_config.h"
#include "hci_format.h"
#include "ll_port.h"

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

void mac_hw_init(void);

void ll_evt_init(struct ll_evt *evt,enum ll_evt_mode mode);

void adv_scan_evt_init(struct ll_evt *evt,enum ll_evt_mode mode);

void evt_ctrl_reset(void);

uint32_t htimer_current_get(void);

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

void pkt_transmit(uint8_t header_lsb,uint8_t payload_total_length,uint8_t *cte_info,void (*data_fill_func)(void *),void *param,uint8_t *remaining,uint8_t remaining_length);

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

void whiten_disable(void);

void whiten_enable(void);

void crc_init_config(uint32_t crc_init);

void whiten_init_config(uint8_t whiten_init);

void mac_sleep_status_sync(void);

uint32_t mac_sleep(void);

void mac_wakeup_req(void);

void ble_timer2_irq_clr(void);

void ble_timer2_irq2_unmask(void);

void ble_timer2_irq2_mask(void);

void aes_128_req(uint8_t *data,uint8_t *key);
#endif

