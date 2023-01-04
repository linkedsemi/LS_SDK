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



/******************************************************************************************/
/* -----------------------   SUPPORTED HCI COMMANDS       --------------------------------*/
/******************************************************************************************/
/// BLE supported commands
//byte0
#define BLE_DISC_CMD                0x20
//byte2
#define BLE_RD_REM_VERS_CMD         0x80
//byte5
#define BLE_SET_EVT_MSK_CMD         0x40
#define BLE_RESET_CMD               0x80
//byte10
#define BLE_RD_TX_PWR_CMD            0x04
#define BLE_SET_CTRL_TO_HL_FCTRL_CMD 0x20
#define BLE_HL_BUF_SIZE_CMD          0x40
#define BLE_HL_NB_CMP_PKT_CMD        0x80
//byte14
#define BLE_RD_LOC_VERS_CMD         0x08
#define BLE_RD_LOC_SUP_FEAT_CMD     0x20
//byte15
#define BLE_RD_BD_ADDR_CMD          0x02
#define BLE_RD_RSSI_CMD             0x20
//byte22
#define BLE_SET_EVT_MSK_PG2_CMD     0x04
//byte25
#define BLE_LE_SET_EVT_MSK_CMD      0x01
#define BLE_LE_RD_BUF_SIZE_CMD      0x02
#define BLE_LE_RD_LOC_SUP_FEAT_CMD  0x04
#define BLE_LE_SET_RAND_ADDR_CMD    0x10
#define BLE_LE_SET_ADV_PARAM_CMD    0x20
#define BLE_LE_RD_ADV_TX_PWR_CMD    0x40
#define BLE_LE_SET_ADV_DATA_CMD     0x80
//byte26
#define BLE_LE_SET_SC_RSP_DATA_CMD  0x01
#define BLE_LE_SET_ADV_EN_CMD       0x02
#define BLE_LE_SET_SC_PARAM_CMD     0x04
#define BLE_LE_SET_SC_EN_CMD        0x08
#define BLE_LE_CREAT_CNX_CMD        0x10
#define BLE_LE_CREAT_CNX_CNL_CMD    0x20
#define BLE_LE_RD_WL_SIZE_CMD       0x40
#define BLE_LE_CLEAR_WL_CMD         0x80
//byte27
#define BLE_LE_ADD_DEV_WL_CMD       0x01
#define BLE_LE_REM_DEV_WL_CMD       0x02
#define BLE_LE_CNX_UPDATE_CMD       0x04
#define BLE_LE_SET_HL_CH_CLASS_CMD  0x08
#define BLE_LE_RD_CH_MAP_CMD        0x10
#define BLE_LE_RD_REM_FEAT_CMD      0x20
#define BLE_LE_ENCRYPT_CMD          0x40
#define BLE_LE_RAND_CMD             0x80
//byte28
#define BLE_LE_START_ENC_CMD        0x01
#define BLE_LE_LTK_REQ_RPLY_CMD     0x02
#define BLE_LE_LTK_REQ_NEG_RPLY_CMD 0x04
#define BLE_LE_RD_SUPP_STATES_CMD   0x08
#define BLE_LE_RX_TEST_V1_CMD       0x10
#define BLE_LE_TX_TEST_V1_CMD       0x20
#define BLE_LE_STOP_TEST_CMD        0x40

//byte32
#define BLE_RD_AUTH_PAYL_TO_CMD     0x10
#define BLE_WR_AUTH_PAYL_TO_CMD     0x20


//byte33
#define BLE_LE_REM_CON_PARA_REQ_RPLY_CMD        0x10
#define BLE_LE_REM_CON_PARA_REQ_NEG_RPLY_CMD    0x20
#define BLE_LE_SET_DATA_LEN_CMD                 0x40
#define BLE_LE_RD_SUGGTED_DFT_DATA_LEN_CMD      0x80

//byte34
#define BLE_LE_WR_SUGGTED_DFT_DATA_LEN_CMD      0x01
#define BLE_LE_RD_LOC_P256_PUB_KEY_CMD          0x02
#define BLE_LE_GEN_DHKEY_V1_CMD                 0x04
#define BLE_LE_ADD_DEV_TO_RESOLV_LIST_CMD       0x08
#define BLE_LE_REM_DEV_FROM_RESOLV_LIST_CMD     0x10
#define BLE_LE_CLEAR_RESOLV_LIST_CMD            0x20
#define BLE_LE_RD_RESOLV_LIST_SIZE_CMD          0x40
#define BLE_LE_RD_PEER_RESOLV_ADDR_CMD          0x80

//byte35
#define BLE_LE_RD_LOCAL_RESOLV_ADDR_CMD         0x01
#define BLE_LE_SET_ADDR_RESOL_CMD               0x02
#define BLE_LE_SET_RESOLV_PRIV_ADDR_TO_CMD      0x04
#define BLE_LE_RD_MAX_DATA_LEN_CMD              0x08
#define BLE_LE_RD_PHY_CMD                       0x10
#define BLE_LE_SET_DFT_PHY_CMD                  0x20
#define BLE_LE_SET_PHY_CMD                      0x40
#define BLE_LE_RX_TEST_V2_CMD                   0x80
//byte36
#define BLE_LE_TX_TEST_V2_CMD                   0x01
#define BLE_LE_SET_ADV_SET_RAND_ADDR_CMD        0x02
#define BLE_LE_SET_EXT_ADV_PARAM_CMD            0x04
#define BLE_LE_SET_EXT_ADV_DATA_CMD             0x08
#define BLE_LE_SET_EXT_SCAN_RSP_DATA_CMD        0x10
#define BLE_LE_SET_EXT_ADV_EN_CMD               0x20
#define BLE_LE_RD_MAX_ADV_DATA_LEN_CMD          0x40
#define BLE_LE_RD_NB_SUPP_ADV_SETS_CMD          0x80
//byte37
#define BLE_LE_RMV_ADV_SET_CMD                  0x01
#define BLE_LE_CLEAR_ADV_SETS_CMD               0x02
#define BLE_LE_SET_PER_ADV_PARAM_CMD            0x04
#define BLE_LE_SET_PER_ADV_DATA_CMD             0x08
#define BLE_LE_SET_PER_ADV_EN_CMD               0x10
#define BLE_LE_SET_EXT_SCAN_PARAM_CMD           0x20
#define BLE_LE_SET_EXT_SCAN_EN_CMD              0x40
#define BLE_LE_EXT_CREATE_CON_CMD               0x80
//byte38
#define BLE_LE_PER_ADV_CREATE_SYNC_CMD          0x01
#define BLE_LE_PER_ADV_CREATE_SYNC_CANCEL_CMD   0x02
#define BLE_LE_PER_ADV_TERM_SYNC_CMD            0x04
#define BLE_LE_ADD_DEV_TO_PER_ADV_LIST_CMD      0x08
#define BLE_LE_RMV_DEV_FROM_PER_ADV_LIST_CMD    0x10
#define BLE_LE_CLEAR_PER_ADV_LIST_CMD           0x20
#define BLE_LE_RD_PER_ADV_LIST_SIZE_CMD         0x40
#define BLE_LE_RD_TX_PWR_CMD                    0x80
//byte39
#define BLE_LE_RD_RF_PATH_COMP_CMD              0x01
#define BLE_LE_WR_RF_PATH_COMP_CMD              0x02
#define BLE_LE_SET_PRIV_MODE_CMD                0x04
#define BLE_LE_RX_TEST_V3_CMD                   0x08
#define BLE_LE_TX_TEST_V3_CMD                   0x10
#define BLE_LE_SET_CONLESS_CTE_TX_PARAM_CMD     0x20
#define BLE_LE_SET_CONLESS_CTE_TX_EN_CMD        0x40
#define BLE_LE_SET_CONLESS_IQ_SAMPL_EN_CMD      0x80
//byte40
#define BLE_LE_SET_CON_CTE_RX_PARAM_CMD         0x01
#define BLE_LE_SET_CON_CTE_TX_PARAM_CMD         0x02
#define BLE_LE_CON_CTE_REQ_EN_CMD               0x04
#define BLE_LE_CON_CTE_RSP_EN_CMD               0x08
#define BLE_LE_RD_ANTENNA_INF_CMD               0x10
#define BLE_LE_SET_PER_ADV_RX_EN_CMD            0x20
#define BLE_LE_PER_ADV_SYNC_TRANSF_CMD          0x40
#define BLE_LE_PER_ADV_SET_INFO_TRANSF_CMD      0x80
//byte41
#define BLE_LE_SET_PER_ADV_SYNC_TRANSF_PARAM_CMD        0x01
#define BLE_LE_SET_DFT_PER_ADV_SYNC_TRANSF_PARAM_CMD    0x02
#define BLE_LE_GEN_DHKEY_V2_CMD                         0x04
#define BLE_LE_MOD_SLP_CLK_ACC_CMD                      0x10

//byte0
#define BLE_CMDS_BYTE0      BLE_DISC_CMD
//byte2
#define BLE_CMDS_BYTE2      BLE_RD_REM_VERS_CMD
//byte5
#define BLE_CMDS_BYTE5      (BLE_SET_EVT_MSK_CMD | BLE_RESET_CMD)
//byte10
#define BLE_CMDS_BYTE10     0/*(BLE_HL_NB_CMP_PKT_CMD | BLE_RD_TX_PWR_CMD\
                            |BLE_HL_BUF_SIZE_CMD | BLE_SET_CTRL_TO_HL_FCTRL_CMD)*/
//byte14
#define BLE_CMDS_BYTE14     (BLE_RD_LOC_VERS_CMD | BLE_RD_LOC_SUP_FEAT_CMD)
//byte15
#define BLE_CMDS_BYTE15     (BLE_RD_BD_ADDR_CMD | BLE_RD_RSSI_CMD)
//byte22
#define BLE_CMDS_BYTE22     0//(BLE_SET_EVT_MSK_PG2_CMD)
//byte25
#define BLE_CMDS_BYTE25     (BLE_LE_SET_EVT_MSK_CMD | BLE_LE_RD_BUF_SIZE_CMD\
                            |BLE_LE_RD_LOC_SUP_FEAT_CMD | BLE_LE_SET_RAND_ADDR_CMD\
                            |BLE_LE_SET_ADV_PARAM_CMD | BLE_LE_RD_ADV_TX_PWR_CMD\
                            |BLE_LE_SET_ADV_DATA_CMD)
//byte26
#define BLE_CMDS_BYTE26     (BLE_LE_SET_SC_RSP_DATA_CMD | BLE_LE_SET_ADV_EN_CMD\
                            |BLE_LE_SET_SC_PARAM_CMD | BLE_LE_SET_SC_EN_CMD\
                            |BLE_LE_CREAT_CNX_CMD | BLE_LE_CREAT_CNX_CNL_CMD\
                            |BLE_LE_RD_WL_SIZE_CMD | BLE_LE_CLEAR_WL_CMD)
//byte27
#define BLE_CMDS_BYTE27     (BLE_LE_ADD_DEV_WL_CMD | BLE_LE_REM_DEV_WL_CMD\
                            |BLE_LE_CNX_UPDATE_CMD | BLE_LE_SET_HL_CH_CLASS_CMD\
                            |BLE_LE_RD_CH_MAP_CMD | BLE_LE_RD_REM_FEAT_CMD\
                            |BLE_LE_ENCRYPT_CMD | BLE_LE_RAND_CMD)
//byte28
#define BLE_CMDS_BYTE28     (BLE_LE_START_ENC_CMD | BLE_LE_LTK_REQ_RPLY_CMD\
                            |BLE_LE_LTK_REQ_NEG_RPLY_CMD | BLE_LE_RD_SUPP_STATES_CMD\
                            |BLE_LE_RX_TEST_V1_CMD | BLE_LE_TX_TEST_V1_CMD\
                            |BLE_LE_STOP_TEST_CMD)
//byte32
#define BLE_CMDS_BYTE32     0//(BLE_RD_AUTH_PAYL_TO_CMD | BLE_WR_AUTH_PAYL_TO_CMD)

//byte33
#define BLE_CMDS_BYTE33     (BLE_LE_SET_DATA_LEN_CMD | BLE_LE_RD_SUGGTED_DFT_DATA_LEN_CMD) 
                            /*(BLE_LE_REM_CON_PARA_REQ_RPLY_CMD | BLE_LE_REM_CON_PARA_REQ_NEG_RPLY_CMD\
                            | BLE_LE_SET_DATA_LEN_CMD | BLE_LE_RD_SUGGTED_DFT_DATA_LEN_CMD)*/
//byte34
#define BLE_CMDS_BYTE34     (  BLE_LE_WR_SUGGTED_DFT_DATA_LEN_CMD   \
                             | BLE_LE_RD_LOC_P256_PUB_KEY_CMD       \
                             | BLE_LE_GEN_DHKEY_V1_CMD              )
                            /*(  BLE_LE_WR_SUGGTED_DFT_DATA_LEN_CMD   \
                             | BLE_LE_RD_LOC_P256_PUB_KEY_CMD       \
                             | BLE_LE_GEN_DHKEY_V1_CMD              \
                             | BLE_LE_ADD_DEV_TO_RESOLV_LIST_CMD    \
                             | BLE_LE_REM_DEV_FROM_RESOLV_LIST_CMD  \
                             | BLE_LE_CLEAR_RESOLV_LIST_CMD         \
                             | BLE_LE_RD_RESOLV_LIST_SIZE_CMD       \
                             | BLE_LE_RD_PEER_RESOLV_ADDR_CMD        )*/
//byte35
#define BLE_CMDS_BYTE35     (  BLE_LE_RD_MAX_DATA_LEN_CMD           \
                             | BLE_LE_RD_PHY_CMD                    \
                             | BLE_LE_SET_DFT_PHY_CMD               \
                             | BLE_LE_SET_PHY_CMD                   \
                             | BLE_LE_RX_TEST_V2_CMD                 )
                            /*(  BLE_LE_RD_LOCAL_RESOLV_ADDR_CMD      \
                             | BLE_LE_SET_ADDR_RESOL_CMD            \
                             | BLE_LE_SET_RESOLV_PRIV_ADDR_TO_CMD   \
                             | BLE_LE_RD_MAX_DATA_LEN_CMD           \
                             | BLE_LE_RD_PHY_CMD                    \
                             | BLE_LE_SET_DFT_PHY_CMD               \
                             | BLE_LE_SET_PHY_CMD                   \
                             | BLE_LE_RX_TEST_V2_CMD                 )*/
//byte36
#define BLE_CMDS_BYTE36     (  BLE_LE_TX_TEST_V2_CMD                \
                             | BLE_LE_SET_ADV_SET_RAND_ADDR_CMD     \
                             | BLE_LE_SET_EXT_ADV_PARAM_CMD         \
                             | BLE_LE_SET_EXT_ADV_DATA_CMD          \
                             | BLE_LE_SET_EXT_SCAN_RSP_DATA_CMD     \
                             | BLE_LE_SET_EXT_ADV_EN_CMD            \
                             | BLE_LE_RD_MAX_ADV_DATA_LEN_CMD       \
                             | BLE_LE_RD_NB_SUPP_ADV_SETS_CMD        )
//byte37
#define BLE_CMDS_BYTE37     (  BLE_LE_RMV_ADV_SET_CMD               \
                             | BLE_LE_CLEAR_ADV_SETS_CMD            \
                             | BLE_LE_SET_PER_ADV_PARAM_CMD         \
                             | BLE_LE_SET_PER_ADV_DATA_CMD          \
                             | BLE_LE_SET_PER_ADV_EN_CMD            \
                             | BLE_LE_SET_EXT_SCAN_PARAM_CMD        \
                             | BLE_LE_SET_EXT_SCAN_EN_CMD           \
                             | BLE_LE_EXT_CREATE_CON_CMD             )
//byte38
#define BLE_CMDS_BYTE38     (  BLE_LE_PER_ADV_CREATE_SYNC_CMD        \
                             | BLE_LE_PER_ADV_CREATE_SYNC_CANCEL_CMD \
                             | BLE_LE_PER_ADV_TERM_SYNC_CMD          \
                             | BLE_LE_ADD_DEV_TO_PER_ADV_LIST_CMD    \
                             | BLE_LE_RMV_DEV_FROM_PER_ADV_LIST_CMD  \
                             | BLE_LE_CLEAR_PER_ADV_LIST_CMD         \
                             | BLE_LE_RD_PER_ADV_LIST_SIZE_CMD       \
                             /*| BLE_LE_RD_TX_PWR_CMD*/                   )
//byte39
#define BLE_CMDS_BYTE39      (  BLE_LE_RD_RF_PATH_COMP_CMD            \
                              | BLE_LE_WR_RF_PATH_COMP_CMD            )
                            /*(  BLE_LE_RD_RF_PATH_COMP_CMD            \
                             | BLE_LE_WR_RF_PATH_COMP_CMD            \
                             | BLE_LE_SET_PRIV_MODE_CMD              \
                             | BLE_LE_RX_TEST_V3_CMD                 \
                             | BLE_LE_TX_TEST_V3_CMD                 \
                             | BLE_LE_SET_CONLESS_CTE_TX_PARAM_CMD   \
                             | BLE_LE_SET_CONLESS_CTE_TX_EN_CMD      \
                             | BLE_LE_SET_CONLESS_IQ_SAMPL_EN_CMD     )*/
//byte40
#define BLE_CMDS_BYTE40     0/*(  BLE_LE_SET_CON_CTE_RX_PARAM_CMD       \
                             | BLE_LE_SET_CON_CTE_TX_PARAM_CMD       \
                             | BLE_LE_CON_CTE_REQ_EN_CMD             \
                             | BLE_LE_CON_CTE_RSP_EN_CMD             \
                             | BLE_LE_RD_ANTENNA_INF_CMD             \
                             | BLE_LE_SET_PER_ADV_RX_EN_CMD          \
                             | BLE_LE_PER_ADV_SYNC_TRANSF_CMD        \
                             | BLE_LE_PER_ADV_SET_INFO_TRANSF_CMD     )*/
//byte41
#define BLE_CMDS_BYTE41     0/*(  BLE_LE_SET_PER_ADV_SYNC_TRANSF_PARAM_CMD        \
                             | BLE_LE_SET_DFT_PER_ADV_SYNC_TRANSF_PARAM_CMD    \
                             | BLE_LE_GEN_DHKEY_V2_CMD                         \
                             | BLE_LE_MOD_SLP_CLK_ACC_CMD                       )*/


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

void bt_set_evt_mask_page_2(const struct evt_mask *mask);

void bt_get_local_supported_cmds(struct supp_cmds *buf);

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
