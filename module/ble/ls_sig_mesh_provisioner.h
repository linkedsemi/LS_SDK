#ifndef _LS_SIG_MESH_PROVISIONER_H_
#define _LS_SIG_MESH_PROVISIONER_H_
#include <stdint.h>
#include "ls_ble.h"
#include "ls_sig_mesh.h"

/** \addtogroup SIG_MESH_PROVISIONER
 *  @{
 */

#define CONNECT_IDX_INVALID 0xff
/*provisioner infomation*/
#define MESH_KEY_LENGTH (16)

enum config_client_get_type
{
    CONFIG_CLIENT_GET_TYPE_BEACON = 0,
    CONFIG_CLIENT_GET_TYPE_DFLT_TTL,
    CONFIG_CLIENT_GET_TYPE_GATT_PROXY,
    CONFIG_CLIENT_GET_TYPE_RELAY,
    CONFIG_CLIENT_GET_TYPE_FRIEND,
    CONFIG_CLIENT_GET_TYPE_HB_PUBLI,
    CONFIG_CLIENT_GET_TYPE_HB_SUBS,
    CONFIG_CLIENT_GET_TYPE_NET_TRANSMIT,
    CONFIG_CLIENT_GET_TYPE_NET_KEYS,
    CONFIG_CLIENT_GET_TYPE_COMPO_DATA,
    CONFIG_CLIENT_GET_TYPE_LPN_POLLTIEOUT,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    CONFIG_CLIENT_GET_TYPE_MAX,
};

enum config_client_set_type
{

    CONFIG_CLIENT_SET_TYPE_BEACON = 0,

    CONFIG_CLIENT_SET_TYPE_DFLT_TTL,
    CONFIG_CLIENT_SET_TYPE_GATT_PROXY,
    CONFIG_CLIENT_SET_TYPE_FRIEND,
    CONFIG_CLIENT_SET_TYPE_RESET,
    CONFIG_CLIENT_SET_TYPE_NET_TX,
    CONFIG_CLIENT_SET_TYPE_RELAY,
    CONFIG_CLIENT_SET_TYPE_MAX,
};

enum config_client_value_type
{
   CONFIG_CLIENT_GET_VAL_TYPE_BEACON = 0,
   CONFIG_CLIENT_GET_VAL_TYPE_COMPO_DATA,
   CONFIG_CLIENT_GET_VAL_TYPE_DFLT_TTL,
   CONFIG_CLIENT_GET_VAL_TYPE_GATT_PROXY,
   CONFIG_CLIENT_GET_VAL_TYPE_RELAY,
   CONFIG_CLIENT_GET_VAL_TYPE_MDL_PUBLI,
   CONFIG_CLIENT_GET_VAL_TYPE_MDL_SUBS,
   CONFIG_CLIENT_GET_VAL_TYPE_MDL_SUBS_LIST,
   CONFIG_CLIENT_GET_VAL_TYPE_NETKEY,
   CONFIG_CLIENT_GET_VAL_TYPE_NETKEY_LIST,
   CONFIG_CLIENT_GET_VAL_TYPE_APPKEY,
   CONFIG_CLIENT_GET_VAL_TYPE_APPKEY_LIST,
   CONFIG_CLIENT_GET_VAL_TYPE_NODE_IDENTITY,
   CONFIG_CLIENT_GET_VAL_TYPE_MDL_APP,
   CONFIG_CLIENT_GET_VAL_TYPE_MDL_APP_LIST,
   CONFIG_CLIENT_GET_VAL_TYPE_NODE_RESET,
   CONFIG_CLIENT_GET_VAL_TYPE_FRIEND,
   CONFIG_CLIENT_GET_VAL_TYPE_PHASE,
   CONFIG_CLIENT_GET_VAL_TYPE_HB_PUBLI,
   CONFIG_CLIENT_GET_VAL_TYPE_HB_SUBS,
   CONFIG_CLIENT_GET_VAL_TYPE_LPN_POLLTIMEOUT,
   CONFIG_CLIENT_GET_VAL_TYPE_NET_TX,
};

enum config_client_net_action_type
{
    CONFIG_CLIEN_ADD_NET_KEY_TYPE = 0,
    CONFIG_CLIEN_UPDATE_NET_KEY_TYPE,
    CONFIG_CLIEN_DELETE_NET_TYPE,
    CONFIG_CLIEN_GET_NET_KEY_BOUND_APP_KEY,
    CONFIG_CLIEN_GET_NET_KEY_TYPE_NODE_ID,
    CONFIG_CLIEN_GET_NET_KEY_TYPE_PHASE,
    CONFIG_CLIEN_SET_NET_KEY_TYPE_PHASE,
    CONFIG_CLIEN_SET_NET_KEY_TYPE_NODE_ID,
    CONFIG_CLIEN_NET_KEY_TYPE_MAX,
};

enum config_client_app_action_type
{
    CONFIG_CLIENT_ADD_APP_KEY_TYPE= 0,
    CONFIG_CLIENT_UPDATE_APP_KEY_TYPE,
    CONFIG_CLIENT_DELETE_APP_KEY_TYPE,
    CONFIG_CLIENT_ACTIVE_APP_TYPE_MAX,
};

enum config_client_mdl_get_type
{
    CONFIG_CLIENT_MDL_GET_TYPE_PUBLI = 0,
    CONFIG_CLIENT_MDL_GET_TYPE_SUBS,
    CONFIG_CLIENT_MDL_GET_TYPE_APP,
    CONFIG_CLIENT_MDL_GET_TYPE_MAX,
};

enum config_client_mdl_subs_action_type
{
    CONFIG_CLIENT_MDL_SUBS_ACTION_TYPE_ADD = 0,
    CONFIG_CLIENT_MDL_SUBS_ACTION_TYPE_DELETE,
    CONFIG_CLIENT_MDL_SUBS_ACTION_TYPE_OVERWRITE,
    CONFIG_CLIENT_MDL_SUBS_ACTION_TYPE_DELETE_ALL,
    CONFIG_CLIENT_MDL_SUBS_ACTION_TYPE_MAX,
};


enum config_client_mdl_app_action_type
{
    CONFIG_CLIENT_MDL_APP_ACTION_TYPE_BIND,
    CONFIG_CLIENT_MDL_APP_ACTION_TYPE_UNBIND,
    CONFIG_CLIENT_MDL_APP_ACTION_TYPE_MAX,
};

enum config_client_mdl_publi_set_type
{
    CONFIG_CLIENT_MDL_PUBLI_SET_TYPE_ADDR,
    CONFIG_CLIENT_MDL_PUBLI_SET_TYPE_VADDR,
    CONFIG_CLIENT_MDL_PUBLI_SET_TYPE_MAX,
};

enum mesh_provisioner_evt_type
{
    MESH_PROVER_GET_PROV_AUTH_INFO = MESH_EVT_TYPE_MAX,
    MESH_PROVER_KEY_DEV_ADD_RSP_INFO,
    MESH_PROVER_KEY_NET_ADD_IND,
    MESH_PROVER_KEY_APP_ADD_IND,
    MESH_PROVER_HEALTH_MODEL_RSP_INFO,
    MESH_PROVER_SET_DEV_RSP_INFO,
    MESH_PROVER_IDENTIFY_REQ_IND_INFO,
    MESH_PROVER_REPORT_IV_SEQ_INFO,
    MESH_PROVER_EVT_MAX,
};

enum mesh_provisioner_rx_ind_type
{
    MESH_PROVER_ACTIVE_NODE_FOUND=0,
    MESH_PROVER_ACTIVE_NODE_GATT,
    MESH_PROVER_ACTIVE_NODE_STOPPED,
    MESH_PROVER_ACTIVE_PROXY_SVC,
    MESH_PROVER_ACTIVE_STATE,
    MESH_PROVER_CONFC_GET_BEACON_STATUS,
    MESH_PROVER_CONFC_GET_DEFAULT_TTL_STATUS,
    MESH_PROVER_CONFC_GET_GATT_PROXY_STATUS,
    MESH_PROVER_CONFC_GET_FRIEND_STATUS,
    MESH_PROVER_CONFC_MODEL_PUB_STATUS,
    MESH_PROVER_CONFC_MODEL_SUBS_STATUS,
    MESH_PROVER_CONFC_MODEL_APP_STATUS,
    MESH_PROVER_CONFC_COMP_DATA_PAGE0,
    MESH_PROVER_CONFC_COMP_DATA_PAGE0_ELEMENT,
    MESH_PROVER_CONFC_APP_KEY_STATUS,
    MESH_PROVER_CONFC_NET_TX_STATUS,
    MESH_PROVER_RX_IND_MAX,
};

enum prover_provisioning_state
{
    PROVISIONING_STARTED,
    PROVISIONING_SUCCEED,
    PROVISIONING_FAILED,
};

struct prover_node_scan_info
{
   uint32_t uri_hash;
   uint16_t oob_info;
   int8_t rssi;
   uint8_t dev_uuid[UUID_MESH_DEV_LEN];  
};

struct prover_active_state_info
{
   uint8_t state;
   uint16_t status;
   uint16_t unicast_addr;
};

struct prover_add_dev_key_rsp_info
{
    uint8_t  dev_key_lid;
    uint16_t unicast_addr;
    uint8_t  dev_key[BLE_KEY_LEN];  
};

struct prover_add_net_key_ind_info
{
    uint8_t  net_key_lid;
};

struct prover_add_app_key_ind_info
{
    uint8_t  app_key_lid;
};


struct prover_health_client_model_rsp_info
{
    uint8_t  mdl_lid;
};

struct prover_identify_req_ind_info
{
    uint8_t  dev_nb_elt;
    uint16_t dev_algorithms;
    uint8_t  dev_pub_key_type;
    uint8_t  dev_static_oob_type;
    uint8_t  dev_out_oob_size;
    uint16_t dev_out_oob_action;
    uint8_t  dev_in_oob_size;
    uint16_t dev_in_oob_action;
}__attribute__((packed));

struct prover_confc_get_compo_data_ind_info
{
    uint16_t unicast_addr;
    uint16_t company_id;
    uint16_t product_id;
    uint16_t version_id;
    uint16_t min_num_replay;
    uint16_t support_features;
    uint8_t  dev_nb_elements;
};

struct prover_confc_get_compo_data_element_ind_info
{
    uint16_t unicast_addr;
    uint16_t loc_desc;
    uint8_t  number_sig_models;
    uint8_t  number_vendor_models;
    uint32_t model_info[__LSSIGMESH_EMPTY];
}__attribute__((packed));

struct prover_confc_get_default_ttl_ind_info
{
    uint16_t unicast_addr;
    uint8_t  default_ttl;
};

struct prover_confc_get_app_key_status_ind_info
{
    uint16_t unicast_addr;
    uint8_t  active_status;
    uint16_t net_key_id;
    uint16_t app_key_id;
}__attribute__((packed));

struct prover_confc_model_subs_app_status_ind_info
{
    uint16_t unicast_addr;
    uint8_t  status;
    uint16_t element_addr;
    uint32_t model_id;
    uint16_t value; //group_addr/appkey_id

};

struct prover_confc_model_pubs_status_ind_info
{
   uint16_t unicast_addr;
   uint8_t status;
   uint16_t element_addr;
   uint16_t publish_addr;
   uint16_t app_key_id;
   bool cred_flag;
   uint8_t publish_ttl;
   uint32_t publish_period_ms;
   uint8_t publish_retx_cont;
   uint8_t publish_retx_intv_step_solution;
   uint32_t model_id;
};

struct prover_report_iv_seq_info
{
    uint32_t iv;
    uint32_t seq;
};

union ls_sig_mesh_provisioner_evt_u 
{
  struct prover_add_dev_key_rsp_info  prover_node_add_dev_key_rsp_info;
  struct prover_health_client_model_rsp_info prover_node_health_model_rsp_info;
  struct prover_add_net_key_ind_info prover_node_add_net_key_ind_info;
  struct prover_add_app_key_ind_info prover_node_add_app_key_ind_info;
  struct prover_identify_req_ind_info prover_identify_req_ind_info;
  struct prover_report_iv_seq_info prover_seq_iv_info;
};

union ls_sig_mesh_provisioner_rx_info_u 
{
  struct prover_active_state_info  prover_node_state_info;
  struct prover_node_scan_info prover_node_scan_info;
  struct prover_confc_get_compo_data_ind_info confc_get_compo_data_info;
  struct prover_confc_get_compo_data_element_ind_info confc_get_compo_data_element_info;
  struct prover_confc_get_default_ttl_ind_info confc_get_default_ttl_info;
  struct prover_confc_get_app_key_status_ind_info confc_get_app_key_status_info;
  struct prover_confc_model_subs_app_status_ind_info confc_model_subs_app_status_info;
  struct prover_confc_model_pubs_status_ind_info confc_model_pubs_status_info;
};

/**
 * @brief 
 * 
 * @param evt_cb
 * @param rx_ind_handle
 */
void prf_ls_sig_mesh_provisioner_callback_init(void (*evt_cb)(enum mesh_provisioner_evt_type, union ls_sig_mesh_provisioner_evt_u *),void (*rx_ind_handle)(enum mesh_provisioner_rx_ind_type, union ls_sig_mesh_provisioner_rx_info_u *));
/**
 * @brief 
 * 
 * @param unicast_addr
 * @param dev_uuid
 */
void ls_sig_mesh_add_uuid_unicast_addr(const uint16_t unicast_addr, const uint8_t* dev_uuid);
/**
 * @brief 
 * 
 * @param unicast_addr provisioner unicast address
 */
void ls_sig_mesh_provisioner_init(const uint16_t unicast_addr);
/**
 * @brief 
 * 
 * @param unicast_addr 
 * @param dev_key 
 */
void ls_sig_mesh_provisioner_add_dev_key(const uint16_t unicast_addr, const uint8_t* dev_key);
/**
 * @brief 
 * 
 * @param netkey_id 
 * @param net_key 
 */
void ls_sig_mesh_provisioner_add_net_key(const uint16_t netkey_id, const uint8_t* net_key);
/**
 * @brief 
 * 
 * @param netkey_id 
 */
void ls_sig_mesh_provisioner_use_new_net_key(const uint16_t netkey_id);
/**
 * @brief 
 * 
 * @param netkey_id 
 * @param net_key 
 */
void ls_sig_mesh_provisioner_update_net_key(const uint16_t netkey_id, const uint8_t* net_key);
/**
 * @brief 
 * 
 * @param netkey_id 
 */
void ls_sig_mesh_provisioner_revoke_old_net_key(const uint16_t netkey_id);
/**
 * @brief 
 * 
 * @param netkey_id 
 */
void ls_sig_mesh_provisioner_delete_net_key(const uint16_t netkey_id);
/**
 * @brief 
 * 
 * @param netkey_id 
 * @param appkey_id 
 * @param app_key 
 */
void ls_sig_mesh_provisioner_add_app_key(const uint16_t netkey_id, const uint16_t appkey_id, const uint8_t* app_key);
/**
 * @brief 
 * 
 * @param netkey_id 
 * @param appkey_id 
 * @param app_key 
 */
void ls_sig_mesh_provisioner_update_app_key(const uint16_t netkey_id, const uint16_t appkey_id, const uint8_t* app_key);
/**
 * @brief 
 * 
 * @param netkey_id 
 * @param appkey_id 
 */
void ls_sig_mesh_provisioner_delete_app_key(const uint16_t netkey_id, const uint16_t appkey_id);
/**
 * @brief 
 * 
 * @param timeout 
 */
void ls_sig_mesh_provisioner_scan(uint16_t timeout);
/**
 * @brief 
 * 
 * @param conidx 
 * @param dev_uuid
 * @param unicast_addr 
 * @param attention_dur_s 
 */
void ls_sig_mesh_provisioner_invite(const uint8_t conidx, const uint8_t *dev_uuid, const uint16_t unicast_addr, const uint8_t attention_dur_s);
/**
 * @brief 
 * 
 */
void ls_sig_mesh_provisioner_stop(void);
/**
 * @brief 
 * 
 * @param param 
 */
void app_mesh_prover_set_prov_auth_info(struct mesh_prov_auth_info *param);
/**
 * @brief 
 * 
 * @param accept 
 * @param netkey_lid 
 * @param algo 
 * @param pub_key 
 * @param auth_method 
 * @param auth_action 
 * @param auth_size 
 */
void ls_sig_mesh_identify_cfm(bool accept, uint8_t netkey_lid, uint8_t algo, uint8_t pub_key, uint8_t auth_method, uint8_t auth_action, uint8_t auth_size);
/**
 * @brief 
 * 
 * @param primary_addr
 */
void ls_sig_mesh_prover_config_reg_model(uint16_t primary_addr);
/**
 * @brief 
 * 
 * @param dev_key_lid 
 * @param net_key_lid 
 * @param primary_addr 
 */
void ls_sig_mesh_prover_config_set_dev(uint8_t dev_key_lid, uint8_t net_key_lid, uint16_t primary_addr);
/**
 * @brief 
 * 
 * @param act_netkey_type 
 * @param net_key_id 
 * @param data 
 * @param data_len 
 */
void ls_sig_mesh_prover_config_client_active_netkey(uint8_t act_netkey_type, uint16_t net_key_id, const uint8_t *data ,uint8_t data_len);
/**
 * @brief 
 * 
 * @param act_appkey_type 
 * @param net_key_id 
 * @param app_key_id 
 * @param appkey 
 */
void ls_sig_mesh_prover_config_client_active_appkey(uint8_t act_appkey_type, uint16_t net_key_id, uint16_t app_key_id, const uint8_t *appkey);
/**
 * @brief 
 * 
 * @param get_model_type 
 * @param element_address 
 * @param model_id 
 */
void ls_sig_mesh_prover_config_client_get_model(uint8_t get_model_type, uint16_t element_address, uint32_t model_id);
/**
 * @brief 
 * 
 * @param model_subscript_act_type 
 * @param element_address 
 * @param model_id 
 * @param address_type 
 * @param length 
 * @param address_uuid 
 */
void ls_sig_mesh_prover_config_client_act_model_subscript(uint8_t model_subscript_act_type, uint16_t element_address, uint32_t model_id, bool address_type, uint16_t length, const uint8_t *address_uuid);
/**
 * @brief 
 * 
 * @param addr_type 
 * @param element_addr 
 * @param appkey_id 
 * @param cred_flag 
 * @param pub_ttl 
 * @param pub_period 
 * @param retx_cnt 
 * @param retx_intv_slots 
 * @param mdl_id 
 * @param length 
 * @param val 
 */
void ls_sig_mesh_prover_config_client_set_model_publication(uint8_t addr_type, uint16_t element_addr, uint16_t appkey_id, bool cred_flag, uint8_t pub_ttl, uint8_t pub_period, uint8_t retx_cnt, uint8_t retx_intv_slots, uint32_t mdl_id, uint16_t length, const uint8_t* val);
/**
 * @brief 
 * 
 * @param mdl_app_act_type 
 * @param element_addr 
 * @param appkey_id 
 * @param mdl_id 
 */
void ls_sig_mesh_prover_config_client_act_model_app(uint8_t mdl_app_act_type, uint16_t element_addr, uint16_t appkey_id, uint32_t mdl_id);
/**
 * @brief 
 * 
 * @param set_type 
 * @param value 
 * @param tx_cnt 
 * @param intv_slots 
 */
void ls_sig_mesh_prover_config_client_set(uint8_t set_type, uint8_t value, uint8_t tx_cnt, uint8_t intv_slots);
/**
 * @brief 
 * 
 * @param get_type 
 * @param value 
 */
void ls_sig_mesh_prover_config_client_get(uint8_t get_type, uint16_t value);
/**
 * @brief 
 * 
 * @param dst 
 * @param cnt 
 * @param period_s 
 * @param ttl 
 * @param features 
 * @param nekkey_id 
 */
void ls_sig_mesh_prover_config_client_set_heartbeat_publication(uint16_t dst, uint16_t cnt, uint16_t period_s, uint8_t ttl, uint16_t features, uint16_t nekkey_id);
/**
 * @brief 
 * 
 * @param src 
 * @param dst 
 * @param period_s 
 */
void ls_sig_mesh_prover_config_client_set_heartbeat_subscription(uint16_t src, uint16_t dst, uint16_t period_s);
/**
 * @brief 
 * 
 * @param address 
 * @param appkey_lid 
 * @param get_type 
 * @param company_id 
 */
void ls_sig_mesh_prover_health_client_get(uint16_t address, uint8_t appkey_lid, uint8_t get_type, uint16_t company_id);
/**
 * @brief 
 * 
 * @param address 
 * @param appkey_lid 
 * @param set_type 
 * @param set_cfg 
 * @param val 
 */
void ls_sig_mesh_prover_health_client_set(uint16_t address, uint8_t appkey_lid, uint8_t set_type, uint8_t set_cfg, uint8_t val);
/**
 * @brief 
 * 
 * @param address 
 * @param appkey_lid 
 * @param act_type 
 * @param act_cfg 
 * @param test_id 
 * @param company_id 
 */
void ls_sig_mesh_prover_health_client_act_fault(uint16_t address, uint8_t appkey_lid, uint8_t act_type, uint8_t act_cfg, uint8_t test_id, uint16_t company_id);
/**
 * @brief 
 * 
 */
void ls_sig_mesh_prover_health_client_reg_model(void);
/**
 * @brief 
 * 
 * @param prover_iv 
 * @param prover_seq 
 */
void ls_sig_mesh_set_prover_iv_seq(const uint32_t prover_iv, const uint32_t prover_seq);
/**
 * @brief 
 * 
 */
void ls_sig_mesh_get_prover_iv_seq(void);

/** @} */

#endif //(_LS_SIG_MESH_PROVISIONER_H_
