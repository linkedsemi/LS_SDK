#ifndef LL_HCI_H_
#define LL_HCI_H_
#include <stdint.h>
#include <stdarg.h>
#include "co_list.h"
#include "hci_format.h"
#include "ll_evt.h"
#define OPCODE_BUILD(ogf,ocf) ((ogf)<<10|(ocf))

struct hci_evt_header
{
	uint8_t evt_code;
	uint8_t length;
}__attribute__((packed));

struct hci_evt_buf
{
	struct hci_evt_header header;
	uint8_t param[];
}__attribute__((packed));

struct hci_le_meta_evt_buf
{
	struct hci_evt_header header;
	uint8_t subevent_code;
	uint8_t param[];
}__attribute__((packed));

struct hci_acl_data_header
{
    uint16_t handle:12,
            pb_flag:2,
            bc_flag:2;
    uint16_t length;
}__attribute__((packed));

struct hci_acl_data_upstream_buf
{
	struct hci_acl_data_header header;
	uint8_t data[];
}__attribute__((packed));

struct hci_tx_element
{
	struct co_list_hdr hdr;
	union{
		struct hci_acl_data_upstream_buf *acl_data;
		struct hci_evt_buf *evt;
	}u;
	uint8_t type; //enum hci_packet_indicator
};

struct hci_acl_air_rx_data_buf
{
	struct hci_acl_data_header header;
	uint8_t data[CONN_DATA_MAX_LEN];
}__attribute__((packed));

struct hci_acl_air_rx_data
{
	struct co_list_hdr hdr;
	struct hci_acl_air_rx_data_buf buf;
};

struct hci_acl_air_tx_data_buf
{
	struct hci_acl_data_header header;
	uint8_t data[CONN_DATA_MAX_LEN];
}__attribute__((packed));

struct hci_acl_air_tx_data
{
	struct co_list_hdr hdr;
	struct hci_acl_air_tx_data_buf buf;
};

void ll_hci_init(void);

void hci_packet_indicator_read(void);

bool hci_get_cmd_mode_legacy(void);

bool hci_cmd_status_evt_write(uint8_t status,uint16_t cmd_opcode);

bool hci_enc_change_evt_write(uint8_t status,uint16_t conhdl,uint8_t enc_stat);

bool hci_enc_key_ref_cmp_evt_write(uint8_t status,uint16_t conhdl);

bool hci_disc_cmp_evt_write(uint8_t status,uint16_t conhdl,uint8_t reason);

bool hci_cmd_cmp_evt_write(uint16_t cmd_opcode,uint8_t *return_params,uint8_t return_length);

bool hci_le_enh_con_cmp_evt_write(void (*evt_param_fill)(struct hci_le_enh_con_cmp_evt *,va_list),void *conn,void *adv_or_scan);

bool hci_le_con_cmp_evt_write(void (*evt_param_fill)(struct hci_le_con_cmp_evt *,va_list),void *conn,void *adv_or_scan);

bool hci_nb_cmp_pkts_evt_write(uint16_t conhdl,uint16_t nb_cmp_pkts);

bool hci_rd_rem_ver_info_cmp_evt_write(uint8_t status,uint16_t conhdl,struct version_ind *ver);

bool hci_le_con_update_cmp_evt_write(void (*evt_param_fill)(struct hci_le_con_update_cmp_evt *,va_list),void *conn);

bool hci_le_rd_rem_feats_cmd_cmp_evt_write(uint8_t status,uint16_t conhdl,struct le_features *le_feats);

bool hci_le_ltk_request_evt_write(uint16_t conhdl,struct rand_nb *rand,uint16_t ediv);

bool hci_le_data_len_chg_evt_write(uint16_t conhdl,void *data_length_env);

bool hci_le_adv_report_evt_write(uint8_t data_length,void(* evt_param_fill)(struct hci_le_adv_report_evt *, va_list),void *rx);

bool hci_le_phy_upd_cmp_evt_write(void (*evt_param_fill)(struct hci_le_phy_upd_cmp_evt *,va_list),void *conn);

bool hci_le_ext_adv_report_evt_write(uint8_t data_length,void(* evt_param_fill)(struct hci_le_ext_adv_report_evt *, va_list),void *rx);

bool hci_le_per_adv_sync_est_evt_write(void (*evt_param_fill)(struct hci_le_per_adv_sync_est_evt *,va_list),void *sync);

bool hci_le_per_adv_report_evt_write(uint8_t data_length,void (*evt_param_fill)(struct hci_le_per_adv_report_evt *,va_list),void *rx);

bool hci_le_per_adv_sync_lost_evt_write(uint8_t sync_handle);

bool hci_le_scan_timeout_evt_write(void);

bool hci_le_adv_set_term_evt_write(uint8_t status,uint8_t adv_hdl,uint16_t conhdl,uint8_t completed_adv_evt_cnts);

bool hci_le_scan_req_rcvd_evt_write(uint8_t adv_hdl,uint8_t scanner_addr_type,struct bd_addr *scanner_addr);

bool hci_le_ch_sel_algo_evt_write(uint16_t conhdl,uint8_t csa);

void hci_tx_start(void *data,enum hci_packet_indicator type);

#endif

