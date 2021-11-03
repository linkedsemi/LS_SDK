#ifndef LL_ENV_H_
#define LL_ENV_H_
#include <stdbool.h>
#include "hci_format.h"
#include "co_list.h"

/// Specify if Host has no preference into all_phys parameter HCI:7.8.48 / HCI:7.8.49
enum le_phys_preference
{
    /// The Host has no preference among the transmitter PHYs supported by the Controller
    ALL_PHYS_TX_NO_PREF = (1 << 0),
    /// The Host has no preference among the receiver PHYs supported by the Controller
    ALL_PHYS_RX_NO_PREF = (1 << 1),
};

/// Specify what rate Host prefers to use in transmission on coded PHY. HCI:7.8.49
enum le_phy_opt
{
    /// The Host has no preferred coding when transmitting on the LE Coded PHY
    PHY_OPT_NO_LE_CODED_TX_PREF,
    /// The Host prefers that S=2 coding be used when transmitting on the LE Coded PHY
    PHY_OPT_S2_LE_CODED_TX_PREF,
    /// The Host prefers that S=8 coding be used when transmitting on the LE Coded PHY
    PHY_OPT_S8_LE_CODED_TX_PREF,
};

/// Specify what PHY Host prefers to use for RX or TX HCI:7.8.48 / HCI:7.8.49
enum le_phy_mask
{
    /// The Host prefers to use the LE 1M transmitter/receiver PHY (possibly among others)
    PHY_1MBPS_BIT      = (1<<0),
    PHY_1MBPS_POS      = (0),
    /// The Host prefers to use the LE 2M transmitter/receiver PHY (possibly among others)
    PHY_2MBPS_BIT      = (1<<1),
    PHY_2MBPS_POS      = (1),
    /// The Host prefers to use the LE Coded transmitter/receiver PHY (possibly among others)
    PHY_CODED_BIT      = (1<<2),
    PHY_CODED_POS      = (2),
    /// The Host prefers to use the LE Coded transmitter/receiver PHY (possibly among others)
    PHY_ALL        = (PHY_1MBPS_BIT | PHY_2MBPS_BIT | PHY_CODED_BIT),
};

enum ble_feature
{
    //byte 0
    BLE_FEAT_ENC                       = (0),
    BLE_FEAT_CON_PARAM_REQ_PROC        = (1),
    BLE_FEAT_EXT_REJ_IND               = (2),
    BLE_FEAT_SLAVE_INIT_FEAT_EXCHG     = (3),
    BLE_FEAT_PING                      = (4),
    BLE_FEAT_DATA_PKT_LEN_EXT          = (5),
    BLE_FEAT_LL_PRIVACY                = (6),
    BLE_FEAT_EXT_SCAN_FILT_POLICY      = (7),
    //byte 1
    BLE_FEAT_2M_PHY                    = (8),
    BLE_FEAT_STABLE_MOD_IDX_TX         = (9),
    BLE_FEAT_STABLE_MOD_IDX_RX         = (10),
    BLE_FEAT_CODED_PHY                 = (11),
    BLE_FEAT_EXT_ADV                   = (12),
    BLE_FEAT_PER_ADV                   = (13),
    BLE_CHAN_SEL_ALGO_2                = (14),
    BLE_PWR_CLASS_1                    = (15),
    //byte 2
    MIN_NUM_USED_CHAN_PROC             = (16),
    BLE_FEAT_CON_CTE_REQ               = (17),
    BLE_FEAT_CON_CTE_RSP               = (18),
    BLE_FEAT_CONLESS_CTE_TX            = (19),
    BLE_FEAT_CONLESS_CTE_RX            = (20),
    BLE_FEAT_AOD                       = (21),
    BLE_FEAT_AOA                       = (22),
    BLE_FEAT_CTE_RX                    = (23),
    //byte 3
    BLE_FEAT_PER_ADV_SYNC_TRANSF_TX    = (24),
    BLE_FEAT_PER_ADV_SYNC_TRANSF_RX    = (25),
    BLE_FEAT_SLEEP_CLK_ACC_UPD         = (26),
    BLE_FEAT_PUB_KEY_VALID             = (27),
};
	
/// Features byte 0
#define BLE_FEATURES_BYTE0  (  (1 << BLE_FEAT_ENC                   ) \
                             /*| (1 << BLE_FEAT_CON_PARAM_REQ_PROC    )*/ \
                             | (1 << BLE_FEAT_EXT_REJ_IND           ) \
                             | (1 << BLE_FEAT_SLAVE_INIT_FEAT_EXCHG ) \
                             /*| (1 << BLE_FEAT_PING                  )*/ \
                             | (1 << BLE_FEAT_DATA_PKT_LEN_EXT      ) \
                             /*| (1 << BLE_FEAT_LL_PRIVACY            )*/ \
                             /*| (1 << BLE_FEAT_EXT_SCAN_FILT_POLICY  )*/ \
                             )

/// Features byte 1
#define BLE_FEATURES_BYTE1  (  (1                             << (BLE_FEAT_2M_PHY            - 8) ) \
                             /*| (1                             << (BLE_FEAT_STABLE_MOD_IDX_TX - 8) ) */\
                             /*| (1                             << (BLE_FEAT_STABLE_MOD_IDX_RX - 8) ) */\
                             /*| (1                             << (BLE_FEAT_CODED_PHY         - 8) ) */\
                             /*| (1                             << (BLE_FEAT_EXT_ADV           - 8) ) */\
                             /*| (1                             << (BLE_FEAT_PER_ADV           - 8) ) */\
                             | (1                             << (BLE_CHAN_SEL_ALGO_2        - 8) ) \
                             | (1                             << (BLE_PWR_CLASS_1            - 8) ) \
                             )

/// Features byte 2
#define BLE_FEATURES_BYTE2  (0)//( (1 << (MIN_NUM_USED_CHAN_PROC - 16) ) )

/// Features byte 3
#define BLE_FEATURES_BYTE3  (0)

/// Features byte 4
#define BLE_FEATURES_BYTE4  (0)

/// Features byte 5
#define BLE_FEATURES_BYTE5  (0)

/// Features byte 6
#define BLE_FEATURES_BYTE6  (0)

/// Features byte 7
#define BLE_FEATURES_BYTE7  (0)

/// BLE supported states
//byte 0
#define BLE_NON_CON_ADV_STATE                       0x01
#define BLE_DISC_ADV_STATE                          0x02
#define BLE_CON_ADV_STATE                           0x04
#define BLE_HDC_DIRECT_ADV_STATE                    0x08
#define BLE_PASS_SCAN_STATE                         0x10
#define BLE_ACTIV_SCAN_STATE                        0x20
#define BLE_INIT_MASTER_STATE                       0x40
#define BLE_CON_SLAVE_STATE                         0x80

//byte 1
#define BLE_NON_CON_ADV_PASS_SCAN_STATE             0x01
#define BLE_DISC_ADV_PASS_SCAN_STATE                0x02
#define BLE_CON_ADV_PASS_SCAN_STATE                 0x04
#define BLE_HDC_DIRECT_ADV_PASS_SCAN_STATE          0x08
#define BLE_NON_CON_ADV_ACTIV_SCAN_STATE            0x10
#define BLE_DISC_ADV_ACTIV_SCAN_STATE               0x20
#define BLE_CON_ADV_ACTIV_SCAN_STATE                0x40
#define BLE_HDC_DIRECT_ADV_ACTIV_SCAN_STATE         0x80

//byte 2
#define BLE_NON_CON_ADV_INIT_STATE                  0x01
#define BLE_DISC_ADV_INIT_STATE                     0x02
#define BLE_NON_CON_ADV_MASTER_STATE                0x04
#define BLE_DISC_ADV_MASTER_STATE                   0x08
#define BLE_NON_CON_ADV_SLAVE_STATE                 0x10
#define BLE_DISC_ADV_SLAVE_STATE                    0x20
#define BLE_PASS_SCAN_INIT_STATE                    0x40
#define BLE_ACTIV_SCAN_INIT_STATE                   0x80

//byte 3
#define BLE_PASS_SCAN_MASTER_STATE                  0x01
#define BLE_ACTIV_SCAN_MASTER_STATE                 0x02
#define BLE_PASS_SCAN_SLAVE_STATE                   0x04
#define BLE_ACTIV_SCAN_SLAVE_STATE                  0x08
#define BLE_INIT_MASTER_MASTER_STATE                0x10
#define BLE_LDC_DIRECT_ADV_STATE                    0x20
#define BLE_LDC_DIRECT_ADV_PASS_SCAN_STATE          0x40
#define BLE_LDC_DIRECT_ADV_ACTIV_SCAN_STATE         0x80

//byte 4
#define BLE_CON_ADV_INIT_MASTER_SLAVE_STATE         0x01
#define BLE_HDC_DIRECT_ADV_INIT_MASTER_SLAVE_STATE  0x02
#define BLE_LDC_DIRECT_ADV_INIT_MASTER_SLAVE_STATE  0x04
#define BLE_CON_ADV_MASTER_SLAVE_STATE              0x08
#define BLE_HDC_DIRECT_ADV_MASTER_SLAVE_STATE       0x10
#define BLE_LDC_DIRECT_ADV_MASTER_SLAVE_STATE       0x20
#define BLE_CON_ADV_SLAVE_SLAVE_STATE               0x40
#define BLE_HDC_DIRECT_ADV_SLAVE_SLAVE_STATE        0x80

//byte 5
#define BLE_LDC_DIRECT_ADV_SLAVE_SLAVE_STATE        0x01
#define BLE_INIT_MASTER_SLAVE_STATE                 0x02

/// States byte 0
#define BLE_STATES_BYTE0    ( BLE_NON_CON_ADV_STATE | BLE_DISC_ADV_STATE\
                            | BLE_CON_ADV_STATE | BLE_HDC_DIRECT_ADV_STATE\
                            | BLE_PASS_SCAN_STATE | BLE_ACTIV_SCAN_STATE\
                            | BLE_INIT_MASTER_STATE | BLE_CON_SLAVE_STATE)

/// States byte 1
#define BLE_STATES_BYTE1    ( BLE_NON_CON_ADV_PASS_SCAN_STATE | BLE_DISC_ADV_PASS_SCAN_STATE\
                            | BLE_CON_ADV_PASS_SCAN_STATE | BLE_HDC_DIRECT_ADV_PASS_SCAN_STATE\
                            | BLE_NON_CON_ADV_ACTIV_SCAN_STATE | BLE_DISC_ADV_ACTIV_SCAN_STATE\
                            | BLE_CON_ADV_ACTIV_SCAN_STATE | BLE_HDC_DIRECT_ADV_ACTIV_SCAN_STATE)

/// States byte 2
#define BLE_STATES_BYTE2    ( BLE_NON_CON_ADV_INIT_STATE | BLE_DISC_ADV_INIT_STATE\
                            | BLE_NON_CON_ADV_MASTER_STATE | BLE_DISC_ADV_MASTER_STATE\
                            | BLE_NON_CON_ADV_SLAVE_STATE | BLE_DISC_ADV_SLAVE_STATE\
                            | BLE_PASS_SCAN_INIT_STATE | BLE_ACTIV_SCAN_INIT_STATE)

/// States byte 3
#define BLE_STATES_BYTE3    ( BLE_PASS_SCAN_MASTER_STATE | BLE_ACTIV_SCAN_MASTER_STATE\
                            | BLE_PASS_SCAN_SLAVE_STATE | BLE_ACTIV_SCAN_SLAVE_STATE\
                            | BLE_INIT_MASTER_MASTER_STATE | BLE_LDC_DIRECT_ADV_STATE\
                            | BLE_LDC_DIRECT_ADV_PASS_SCAN_STATE | BLE_LDC_DIRECT_ADV_ACTIV_SCAN_STATE)

/// States byte 4
#define BLE_STATES_BYTE4    ( BLE_CON_ADV_INIT_MASTER_SLAVE_STATE | BLE_HDC_DIRECT_ADV_INIT_MASTER_SLAVE_STATE\
                            | BLE_LDC_DIRECT_ADV_INIT_MASTER_SLAVE_STATE | BLE_CON_ADV_MASTER_SLAVE_STATE\
                            | BLE_HDC_DIRECT_ADV_MASTER_SLAVE_STATE | BLE_LDC_DIRECT_ADV_MASTER_SLAVE_STATE\
                            | BLE_CON_ADV_SLAVE_SLAVE_STATE | BLE_HDC_DIRECT_ADV_SLAVE_SLAVE_STATE)

/// States byte 5
#define BLE_STATES_BYTE5    ( BLE_LDC_DIRECT_ADV_SLAVE_SLAVE_STATE |  BLE_INIT_MASTER_SLAVE_STATE)

/// States byte 6
#define BLE_STATES_BYTE6    0x0
/// States byte 7
#define BLE_STATES_BYTE7    0x0

struct aes_128_calc_env
{
    struct co_list_hdr hdr;
    uint8_t *key;
    uint8_t *data;
    uint8_t *rslt;
    void (*callback)(void *);
    void *param;
};

uint8_t get_adv_ch_tx_power(void);

void le_set_host_channel_classification(struct le_chnl_map *map);

void get_le_supported_states(struct le_states *buf);

void bt_set_evt_mask(const struct evt_mask *mask);

void le_set_rand_addr(struct bd_addr *addr);

void le_set_public_addr(const uint8_t *addr);

void get_local_le_supported_features(struct le_features *features);

void le_set_evt_mask(const struct evt_mask *mask);

bool bt_evt_mask_check(enum hci_evt_code evt_code);

bool le_evt_mask_check(enum hci_le_mega_evt_subcode le_evt_subcode);

uint8_t get_local_sca(void);

struct bd_addr * get_le_rand_addr(void);

struct bd_addr * get_le_public_addr(void);

uint16_t sca_to_ppm(uint8_t sca);

void get_channel_classification(struct le_chnl_map *map);

struct le_chnl_map *get_channel_classification_ptr(void);

void generate_new_ecc_priv_key(void);

void generate_new_ecc_pub_key(void (*cb)(void *));

void generate_dhkey(uint8_t *pub_key_x,uint8_t *pub_key_y,void (*cb)(void *));

uint8_t *get_ecc_result_buf(void);

void set_suggested_default_data_length(uint16_t max_tx_octets,uint16_t max_tx_time);

void get_suggested_default_data_length(uint16_t *max_tx_octets,uint16_t *max_tx_time);

void set_rf_path_compensation(int16_t tx_path_compensation,int16_t rx_path_compensation);

void get_rf_path_compensation(int16_t *tx_path_compensation,int16_t *rx_path_compensation);

void set_preferred_rx_phys(enum le_phy_mask phy);

enum le_phy_mask get_preferred_rx_phys(void);

void set_preferred_tx_phys(enum le_phy_mask phy);

enum le_phy_mask get_preferred_tx_phys(void);

uint32_t access_address_generate(void);

void ll_reset(void);

void ll_init(void);

bool addr_match(struct bd_addr *addr0,struct bd_addr *addr1);

bool valid_in_channel_map(struct le_chnl_map *ch_map,uint8_t idx);

uint8_t channel_select_algorithm_1(struct le_chnl_map *ch_map,uint8_t *unmapped_channel,uint8_t hop);

uint8_t channel_select_algorithm_2(struct le_chnl_map *ch_map,uint32_t access_code,uint16_t counter);

void ll_aes_128_done(void *rslt);

/* key: lsb, plaintext: lsb, ciphertext: msb */
void ll_aes_128(uint8_t *key,uint8_t *plaintext,uint8_t *ciphertext,void (*callback)(void *),void *param);

struct aes_128_calc_env *aes_128_calc_current_pick();

#endif
