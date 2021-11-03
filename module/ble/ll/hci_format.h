#ifndef HCI_FORMAT_H_
#define HCI_FORMAT_H_
#include <stdint.h>
#define EVT_MASK_LEN 8
#define BLE_ADDR_LEN 6
#define LE_CHNL_MAP_LEN 5
#define BLE_KEY_LEN 16
#define RAND_NB_LEN 8
#define LE_FEATS_LEN 8
#define LMP_FEATS_LEN 8
#define LE_STATES_LEN 8
#define PRIV_KEY_256_LEN    32
#define PUB_KEY_256_LEN     64
#define EXT_ADV_DATA_MAX_LEN    229 // HCI:7.7.65.13

#define ADV_DATA_LEN_MAX 31
#define MANUFACTURER_NAME 0x093A

#define BLE_VERSION_40 6
#define BLE_VERSION_41 7
#define BLE_VERSION_42 8
#define BLE_VERSION_50 9
#define BLE_VERSION_51 10
#define BLE_VERSION_52 11

#define CURRENT_BLE_VERSION BLE_VERSION_42

/// Feature mask definition LMP:3.3
#define B0_3_SLOT_POS               0
#define B0_3_SLOT_MSK               0x01
#define B0_5_SLOT_POS               1
#define B0_5_SLOT_MSK               0x02
#define B0_ENC_POS                  2
#define B0_ENC_MSK                  0x04
#define B0_SLOT_OFF_POS             3
#define B0_SLOT_OFF_MSK             0x08
#define B0_TIMING_ACCU_POS          4
#define B0_TIMING_ACCU_MSK          0x10
#define B0_ROLE_SWITCH_POS          5
#define B0_ROLE_SWITCH_MSK          0x20
#define B0_HOLD_MODE_POS            6
#define B0_HOLD_MODE_MSK            0x40
#define B0_SNIFF_MODE_POS           7
#define B0_SNIFF_MODE_MSK           0x80

#define B1_PARK_POS                 0
#define B1_PARK_MSK                 0x01
#define B1_RSSI_POS                 1
#define B1_RSSI_MSK                 0x02
#define B1_CQDDR_POS                2
#define B1_CQDDR_MSK                0x04
#define B1_SCO_POS                  3
#define B1_SCO_MSK                  0x08
#define B1_HV2_POS                  4
#define B1_HV2_MSK                  0x10
#define B1_HV3_POS                  5
#define B1_HV3_MSK                  0x20
#define B1_MULAW_POS                6
#define B1_MULAW_MSK                0x40
#define B1_ALAW_POS                 7
#define B1_ALAW_MSK                 0x80

#define B2_CVSD_POS                 0
#define B2_CVSD_MSK                 0x01
#define B2_PAGING_PAR_NEGO_POS      1
#define B2_PAGING_PAR_NEGO_MSK      0x02
#define B2_PWR_CTRL_POS             2
#define B2_PWR_CTRL_MSK             0x04
#define B2_TRANSPARENT_SCO_POS      3
#define B2_TRANSPARENT_SCO_MSK      0x08
#define B2_FLOW_CTRL_LAG_POS        4
#define B2_FLOW_CTRL_LAG_MSK        0x70
#define B2_BCAST_ENC_POS            7
#define B2_BCAST_ENC_MSK            0x80

#define B3_EDR_2MBPS_ACL_POS        1
#define B3_EDR_2MBPS_ACL_MSK        0x02
#define B3_EDR_3MBPS_ACL_POS        2
#define B3_EDR_3MBPS_ACL_MSK        0x04
#define B3_ENH_INQSCAN_POS          3
#define B3_ENH_INQSCAN_MSK          0x08
#define B3_INT_INQSCAN_POS          4
#define B3_INT_INQSCAN_MSK          0x10
#define B3_INT_PAGESCAN_POS         5
#define B3_INT_PAGESCAN_MSK         0x20
#define B3_RSSI_INQ_RES_POS         6
#define B3_RSSI_INQ_RES_MSK         0x40
#define B3_ESCO_EV3_POS             7
#define B3_ESCO_EV3_MSK             0x80

#define B4_EV4_PKT_POS              0
#define B4_EV4_PKT_MSK              0x01
#define B4_EV5_PKT_POS              1
#define B4_EV5_PKT_MSK              0x02
#define B4_AFH_CAP_SLV_POS          3
#define B4_AFH_CAP_SLV_MSK          0x08
#define B4_AFH_CLASS_SLV_POS        4
#define B4_AFH_CLASS_SLV_MSK        0x10
#define B4_BR_EDR_NOT_SUPP_POS      5
#define B4_BR_EDR_NOT_SUPP_MSK      0x20
#define B4_LE_SUPP_POS              6
#define B4_LE_SUPP_MSK              0x40
#define B4_3_SLOT_EDR_ACL_POS       7
#define B4_3_SLOT_EDR_ACL_MSK       0x80

#define B5_5_SLOT_EDR_ACL_POS       0
#define B5_5_SLOT_EDR_ACL_MSK       0x01
#define B5_SSR_POS                  1
#define B5_SSR_MSK                  0x02
#define B5_PAUSE_ENC_POS            2
#define B5_PAUSE_ENC_MSK            0x04
#define B5_AFH_CAP_MST_POS          3
#define B5_AFH_CAP_MST_MSK          0x08
#define B5_AFH_CLASS_MST_POS        4
#define B5_AFH_CLASS_MST_MSK        0x10
#define B5_EDR_ESCO_2MBPS_POS       5
#define B5_EDR_ESCO_2MBPS_MSK       0x20
#define B5_EDR_ESCO_3MBPS_POS       6
#define B5_EDR_ESCO_3MBPS_MSK       0x40
#define B5_3_SLOT_EDR_ESCO_POS      7
#define B5_3_SLOT_EDR_ESCO_MSK      0x80

#define B6_EIR_POS                  0
#define B6_EIR_MSK                  0x01
#define B6_SIM_LE_BREDR_DEV_CAP_POS 1
#define B6_SIM_LE_BREDR_DEV_CAP_MSK 0x02
#define B6_SSP_POS                  3
#define B6_SSP_MSK                  0x08
#define B6_ENCAPS_PDU_POS           4
#define B6_ENCAPS_PDU_MSK           0x10
#define B6_ERR_DATA_REP_POS         5
#define B6_ERR_DATA_REP_MSK         0x20
#define B6_NONFLUSH_PBF_POS         6
#define B6_NONFLUSH_PBF_MSK         0x40

#define B7_LST_CHANGE_EVT_POS       0
#define B7_LST_CHANGE_EVT_MSK       0x01
#define B7_INQRES_TXPOW_POS         1
#define B7_INQRES_TXPOW_MSK         0x02
#define B7_ENH_PWR_CTRL_POS         2
#define B7_ENH_PWR_CTRL_MSK         0x04
#define B7_EXT_FEATS_POS            7
#define B7_EXT_FEATS_MSK            0x80

enum hci_packet_indicator
{
    HCI_CMD_PKT = 0x1,
    HCI_ACL_DATA_PKT,
    HCI_SYNC_DATA_PKT,
    HCI_EVT_PKT,
    HCI_ISO_DATA_PKT,
};

enum hci_opcode_group_field
{
    LINK_CONTROL = 0x1,
    LINK_POLICY ,
    CTRL_BASEBAND ,
    INFO_PARAM,
    STATUS_PARAM,
    TESTING,
    LE_CTRL = 0x8,
};

enum hci_link_ctrl_cmd_opcode_cmd_field
{
    HCI_INQ_CMD_OPCODE                        = 0x01,
    HCI_INQ_CANCEL_CMD_OPCODE                 = 0x02,
    HCI_PER_INQ_MODE_CMD_OPCODE               = 0x03,
    HCI_EXIT_PER_INQ_MODE_CMD_OPCODE          = 0x04,
    HCI_CREATE_CON_CMD_OPCODE                 = 0x05,
    HCI_DISCONNECT_CMD_OPCODE                 = 0x06,
    HCI_CREATE_CON_CANCEL_CMD_OPCODE          = 0x08,
    HCI_ACCEPT_CON_REQ_CMD_OPCODE             = 0x09,
    HCI_REJECT_CON_REQ_CMD_OPCODE             = 0x0A,
    HCI_LK_REQ_REPLY_CMD_OPCODE               = 0x0B,
    HCI_LK_REQ_NEG_REPLY_CMD_OPCODE           = 0x0C,
    HCI_PIN_CODE_REQ_REPLY_CMD_OPCODE         = 0x0D,
    HCI_PIN_CODE_REQ_NEG_REPLY_CMD_OPCODE     = 0x0E,
    HCI_CHG_CON_PKT_TYPE_CMD_OPCODE           = 0x0F,
    HCI_AUTH_REQ_CMD_OPCODE                   = 0x11,
    HCI_SET_CON_ENC_CMD_OPCODE                = 0x13,
    HCI_CHG_CON_LK_CMD_OPCODE                 = 0x15,
    HCI_MASTER_LK_CMD_OPCODE                  = 0x17,
    HCI_REM_NAME_REQ_CMD_OPCODE               = 0x19,
    HCI_REM_NAME_REQ_CANCEL_CMD_OPCODE        = 0x1A,
    HCI_RD_REM_SUPP_FEATS_CMD_OPCODE          = 0x1B,
    HCI_RD_REM_EXT_FEATS_CMD_OPCODE           = 0x1C,
    HCI_RD_REM_VER_INFO_CMD_OPCODE            = 0x1D,
    HCI_RD_CLK_OFF_CMD_OPCODE                 = 0x1F,
    HCI_RD_LMP_HDL_CMD_OPCODE                 = 0x20,
    HCI_SETUP_SYNC_CON_CMD_OPCODE             = 0x28,
    HCI_ACCEPT_SYNC_CON_REQ_CMD_OPCODE        = 0x29,
    HCI_REJECT_SYNC_CON_REQ_CMD_OPCODE        = 0x2A,
    HCI_IO_CAP_REQ_REPLY_CMD_OPCODE           = 0x2B,
    HCI_USER_CFM_REQ_REPLY_CMD_OPCODE         = 0x2C,
    HCI_USER_CFM_REQ_NEG_REPLY_CMD_OPCODE     = 0x2D,
    HCI_USER_PASSKEY_REQ_REPLY_CMD_OPCODE     = 0x2E,
    HCI_USER_PASSKEY_REQ_NEG_REPLY_CMD_OPCODE = 0x2F,
    HCI_REM_OOB_DATA_REQ_REPLY_CMD_OPCODE     = 0x30,
    HCI_REM_OOB_DATA_REQ_NEG_REPLY_CMD_OPCODE = 0x33,
    HCI_IO_CAP_REQ_NEG_REPLY_CMD_OPCODE       = 0x34,
    HCI_ENH_SETUP_SYNC_CON_CMD_OPCODE         = 0x3D,
    HCI_ENH_ACCEPT_SYNC_CON_CMD_OPCODE        = 0x3E,
    HCI_TRUNC_PAGE_CMD_OPCODE                 = 0x3F,
    HCI_TRUNC_PAGE_CAN_CMD_OPCODE             = 0x40,
    HCI_SET_CON_SLV_BCST_CMD_OPCODE           = 0x41,
    HCI_SET_CON_SLV_BCST_REC_CMD_OPCODE       = 0x42,
    HCI_START_SYNC_TRAIN_CMD_OPCODE           = 0x43,
    HCI_REC_SYNC_TRAIN_CMD_OPCODE             = 0x44,
    HCI_REM_OOB_EXT_DATA_REQ_REPLY_CMD_OPCODE = 0x45,
};

enum hci_ctrl_baseband_cmd_opcode_cmd_field
{
    HCI_SET_EVT_MASK_CMD_OPCODE               = 0x01,
    HCI_RESET_CMD_OPCODE                      = 0x03,
    HCI_SET_EVT_FILTER_CMD_OPCODE             = 0x05,
    HCI_FLUSH_CMD_OPCODE                      = 0x08,
    HCI_RD_PIN_TYPE_CMD_OPCODE                = 0x09,
    HCI_WR_PIN_TYPE_CMD_OPCODE                = 0x0A,
    HCI_CREATE_NEW_UNIT_KEY_CMD_OPCODE        = 0x0B,
    HCI_RD_STORED_LK_CMD_OPCODE               = 0x0D,
    HCI_WR_STORED_LK_CMD_OPCODE               = 0x11,
    HCI_DEL_STORED_LK_CMD_OPCODE              = 0x12,
    HCI_WR_LOCAL_NAME_CMD_OPCODE              = 0x13,
    HCI_RD_LOCAL_NAME_CMD_OPCODE              = 0x14,
    HCI_RD_CON_ACCEPT_TO_CMD_OPCODE           = 0x15,
    HCI_WR_CON_ACCEPT_TO_CMD_OPCODE           = 0x16,
    HCI_RD_PAGE_TO_CMD_OPCODE                 = 0x17,
    HCI_WR_PAGE_TO_CMD_OPCODE                 = 0x18,
    HCI_RD_SCAN_EN_CMD_OPCODE                 = 0x19,
    HCI_WR_SCAN_EN_CMD_OPCODE                 = 0x1A,
    HCI_RD_PAGE_SCAN_ACT_CMD_OPCODE           = 0x1B,
    HCI_WR_PAGE_SCAN_ACT_CMD_OPCODE           = 0x1C,
    HCI_RD_INQ_SCAN_ACT_CMD_OPCODE            = 0x1D,
    HCI_WR_INQ_SCAN_ACT_CMD_OPCODE            = 0x1E,
    HCI_RD_AUTH_EN_CMD_OPCODE                 = 0x1F,
    HCI_WR_AUTH_EN_CMD_OPCODE                 = 0x20,
    HCI_RD_CLASS_OF_DEV_CMD_OPCODE            = 0x23,
    HCI_WR_CLASS_OF_DEV_CMD_OPCODE            = 0x24,
    HCI_RD_VOICE_STG_CMD_OPCODE               = 0x25,
    HCI_WR_VOICE_STG_CMD_OPCODE               = 0x26,
    HCI_RD_AUTO_FLUSH_TO_CMD_OPCODE           = 0x27,
    HCI_WR_AUTO_FLUSH_TO_CMD_OPCODE           = 0x28,
    HCI_RD_NB_BDCST_RETX_CMD_OPCODE           = 0x29,
    HCI_WR_NB_BDCST_RETX_CMD_OPCODE           = 0x2A,
    HCI_RD_HOLD_MODE_ACTIVITY_CMD_OPCODE      = 0x2B,
    HCI_WR_HOLD_MODE_ACTIVITY_CMD_OPCODE      = 0x2C,
    HCI_RD_TX_PWR_LVL_CMD_OPCODE              = 0x2D,
    HCI_RD_SYNC_FLOW_CTRL_EN_CMD_OPCODE       = 0x2E,
    HCI_WR_SYNC_FLOW_CTRL_EN_CMD_OPCODE       = 0x2F,
    HCI_SET_CTRL_TO_HOST_FLOW_CTRL_CMD_OPCODE = 0x31,
    HCI_HOST_BUF_SIZE_CMD_OPCODE              = 0x33,
    HCI_HOST_NB_CMP_PKTS_CMD_OPCODE           = 0x35,
    HCI_RD_LINK_SUPV_TO_CMD_OPCODE            = 0x36,
    HCI_WR_LINK_SUPV_TO_CMD_OPCODE            = 0x37,
    HCI_RD_NB_SUPP_IAC_CMD_OPCODE             = 0x38,
    HCI_RD_CURR_IAC_LAP_CMD_OPCODE            = 0x39,
    HCI_WR_CURR_IAC_LAP_CMD_OPCODE            = 0x3A,
    HCI_SET_AFH_HOST_CH_CLASS_CMD_OPCODE      = 0x3F,
    HCI_RD_INQ_SCAN_TYPE_CMD_OPCODE           = 0x42,
    HCI_WR_INQ_SCAN_TYPE_CMD_OPCODE           = 0x43,
    HCI_RD_INQ_MODE_CMD_OPCODE                = 0x44,
    HCI_WR_INQ_MODE_CMD_OPCODE                = 0x45,
    HCI_RD_PAGE_SCAN_TYPE_CMD_OPCODE          = 0x46,
    HCI_WR_PAGE_SCAN_TYPE_CMD_OPCODE          = 0x47,
    HCI_RD_AFH_CH_ASSESS_MODE_CMD_OPCODE      = 0x48,
    HCI_WR_AFH_CH_ASSESS_MODE_CMD_OPCODE      = 0x49,
    HCI_RD_EXT_INQ_RSP_CMD_OPCODE             = 0x51,
    HCI_WR_EXT_INQ_RSP_CMD_OPCODE             = 0x52,
    HCI_REFRESH_ENC_KEY_CMD_OPCODE            = 0x53,
    HCI_RD_SP_MODE_CMD_OPCODE                 = 0x55,
    HCI_WR_SP_MODE_CMD_OPCODE                 = 0x56,
    HCI_RD_LOC_OOB_DATA_CMD_OPCODE            = 0x57,
    HCI_RD_INQ_RSP_TX_PWR_LVL_CMD_OPCODE      = 0x58,
    HCI_WR_INQ_TX_PWR_LVL_CMD_OPCODE          = 0x59,
    HCI_RD_DFT_ERR_DATA_REP_CMD_OPCODE        = 0x5A,
    HCI_WR_DFT_ERR_DATA_REP_CMD_OPCODE        = 0x5B,
    HCI_ENH_FLUSH_CMD_OPCODE                  = 0x5F,
    HCI_SEND_KEYPRESS_NOTIF_CMD_OPCODE        = 0x60,
    HCI_SET_EVT_MASK_PAGE_2_CMD_OPCODE        = 0x63,
    HCI_RD_FLOW_CNTL_MODE_CMD_OPCODE          = 0x66,
    HCI_WR_FLOW_CNTL_MODE_CMD_OPCODE          = 0x67,
    HCI_RD_ENH_TX_PWR_LVL_CMD_OPCODE          = 0x68,
    HCI_RD_LE_HOST_SUPP_CMD_OPCODE            = 0x6C,
    HCI_WR_LE_HOST_SUPP_CMD_OPCODE            = 0x6D,
    HCI_SET_MWS_CHANNEL_PARAMS_CMD_OPCODE     = 0x6E,
    HCI_SET_EXTERNAL_FRAME_CONFIG_CMD_OPCODE  = 0x6F,
    HCI_SET_MWS_SIGNALING_CMD_OPCODE          = 0x70,
    HCI_SET_MWS_TRANSPORT_LAYER_CMD_OPCODE    = 0x71,
    HCI_SET_MWS_SCAN_FREQ_TABLE_CMD_OPCODE    = 0x72,
    HCI_SET_MWS_PATTERN_CONFIG_CMD_OPCODE     = 0x73,
    HCI_SET_RES_LT_ADDR_CMD_OPCODE            = 0x74,
    HCI_DEL_RES_LT_ADDR_CMD_OPCODE            = 0x75,
    HCI_SET_CON_SLV_BCST_DATA_CMD_OPCODE      = 0x76,
    HCI_RD_SYNC_TRAIN_PARAM_CMD_OPCODE        = 0x77,
    HCI_WR_SYNC_TRAIN_PARAM_CMD_OPCODE        = 0x78,
    HCI_RD_SEC_CON_HOST_SUPP_CMD_OPCODE       = 0x79,
    HCI_WR_SEC_CON_HOST_SUPP_CMD_OPCODE       = 0x7A,
    HCI_RD_AUTH_PAYL_TO_CMD_OPCODE            = 0x7B,
    HCI_WR_AUTH_PAYL_TO_CMD_OPCODE            = 0x7C,
    HCI_RD_LOC_OOB_EXT_DATA_CMD_OPCODE        = 0x7D,
    HCI_RD_EXT_PAGE_TO_CMD_OPCODE             = 0x7E,
    HCI_WR_EXT_PAGE_TO_CMD_OPCODE             = 0x7F,
    HCI_RD_EXT_INQ_LEN_CMD_OPCODE             = 0x80,
    HCI_WR_EXT_INQ_LEN_CMD_OPCODE             = 0x81,
};

enum hci_info_param_cmd_opcode_cmd_field
{
    HCI_RD_LOCAL_VER_INFO_CMD_OPCODE          = 0x1,
    HCI_RD_LOCAL_SUPP_CMDS_CMD_OPCODE         = 0x2,
    HCI_RD_LOCAL_SUPP_FEATS_CMD_OPCODE        = 0x3,
    HCI_RD_LOCAL_EXT_FEATS_CMD_OPCODE         = 0x4,
    HCI_RD_BUFF_SIZE_CMD_OPCODE               = 0x5,
    HCI_RD_BD_ADDR_CMD_OPCODE                 = 0x9,
    HCI_RD_LOCAL_SUPP_CODECS_CMD_OPCODE       = 0xB,
};

enum hci_status_param_cmd_opcode_cmd_field
{
    HCI_RD_FAIL_CONTACT_CNT_CMD_OPCODE             = 0x01,
    HCI_RST_FAIL_CONTACT_CNT_CMD_OPCODE            = 0x02,
    HCI_RD_LINK_QUAL_CMD_OPCODE                    = 0x03,
    HCI_RD_RSSI_CMD_OPCODE                         = 0x05,
    HCI_RD_AFH_CH_MAP_CMD_OPCODE                   = 0x06,
    HCI_RD_CLK_CMD_OPCODE                          = 0x07,
    HCI_RD_ENC_KEY_SIZE_CMD_OPCODE                 = 0x08,
    HCI_GET_MWS_TRANSPORT_LAYER_CONFIG_CMD_OPCODE  = 0x0C,
};

enum hci_le_ctrl_cmd_opcode_cmd_field
{
    HCI_LE_SET_EVT_MASK_CMD_OPCODE                 = 0x01,
    HCI_LE_RD_BUFF_SIZE_CMD_OPCODE                 = 0x02,
    HCI_LE_RD_LOCAL_SUPP_FEATS_CMD_OPCODE          = 0x03,
    HCI_LE_SET_RAND_ADDR_CMD_OPCODE                = 0x05,
    HCI_LE_SET_ADV_PARAM_CMD_OPCODE                = 0x06,
    HCI_LE_RD_ADV_CHNL_TX_PW_CMD_OPCODE            = 0x07,
    HCI_LE_SET_ADV_DATA_CMD_OPCODE                 = 0x08,
    HCI_LE_SET_SCAN_RSP_DATA_CMD_OPCODE            = 0x09,
    HCI_LE_SET_ADV_EN_CMD_OPCODE                   = 0x0A,
    HCI_LE_SET_SCAN_PARAM_CMD_OPCODE               = 0x0B,
    HCI_LE_SET_SCAN_EN_CMD_OPCODE                  = 0x0C,
    HCI_LE_CREATE_CON_CMD_OPCODE                   = 0x0D,
    HCI_LE_CREATE_CON_CANCEL_CMD_OPCODE            = 0x0E,
    HCI_LE_RD_WLST_SIZE_CMD_OPCODE                 = 0x0F,
    HCI_LE_CLEAR_WLST_CMD_OPCODE                   = 0x10,
    HCI_LE_ADD_DEV_TO_WLST_CMD_OPCODE              = 0x11,
    HCI_LE_RMV_DEV_FROM_WLST_CMD_OPCODE            = 0x12,
    HCI_LE_CON_UPDATE_CMD_OPCODE                   = 0x13,
    HCI_LE_SET_HOST_CH_CLASS_CMD_OPCODE            = 0x14,
    HCI_LE_RD_CHNL_MAP_CMD_OPCODE                  = 0x15,
    HCI_LE_RD_REM_FEATS_CMD_OPCODE                 = 0x16,
    HCI_LE_ENC_CMD_OPCODE                          = 0x17,
    HCI_LE_RAND_CMD_OPCODE                         = 0x18,
    HCI_LE_START_ENC_CMD_OPCODE                    = 0x19,
    HCI_LE_LTK_REQ_REPLY_CMD_OPCODE                = 0x1A,
    HCI_LE_LTK_REQ_NEG_REPLY_CMD_OPCODE            = 0x1B,
    HCI_LE_RD_SUPP_STATES_CMD_OPCODE               = 0x1C,
    HCI_LE_RX_TEST_CMD_OPCODE                      = 0x1D,
    HCI_LE_TX_TEST_CMD_OPCODE                      = 0x1E,
    HCI_LE_TEST_END_CMD_OPCODE                     = 0x1F,
    HCI_LE_REM_CON_PARAM_REQ_REPLY_CMD_OPCODE      = 0x20,
    HCI_LE_REM_CON_PARAM_REQ_NEG_REPLY_CMD_OPCODE  = 0x21,
    HCI_LE_SET_DATA_LEN_CMD_OPCODE                 = 0x22,
    HCI_LE_RD_SUGGTED_DFT_DATA_LEN_CMD_OPCODE      = 0x23,
    HCI_LE_WR_SUGGTED_DFT_DATA_LEN_CMD_OPCODE      = 0x24,
    HCI_LE_RD_LOC_P256_PUB_KEY_CMD_OPCODE          = 0x25,
    HCI_LE_GEN_DHKEY_CMD_OPCODE                    = 0x26,
    HCI_LE_ADD_DEV_TO_RSLV_LIST_CMD_OPCODE         = 0x27,
    HCI_LE_RMV_DEV_FROM_RSLV_LIST_CMD_OPCODE       = 0x28,
    HCI_LE_CLEAR_RSLV_LIST_CMD_OPCODE              = 0x29,
    HCI_LE_RD_RSLV_LIST_SIZE_CMD_OPCODE            = 0x2A,
    HCI_LE_RD_PEER_RSLV_ADDR_CMD_OPCODE            = 0x2B,
    HCI_LE_RD_LOC_RSLV_ADDR_CMD_OPCODE             = 0x2C,
    HCI_LE_SET_ADDR_RESOL_EN_CMD_OPCODE            = 0x2D,
    HCI_LE_SET_RSLV_PRIV_ADDR_TO_CMD_OPCODE        = 0x2E,
    HCI_LE_RD_MAX_DATA_LEN_CMD_OPCODE              = 0x2F,
    HCI_LE_RD_PHY_CMD_OPCODE                       = 0x30,
    HCI_LE_SET_DFT_PHY_CMD_OPCODE                  = 0x31,
    HCI_LE_SET_PHY_CMD_OPCODE                      = 0x32,
    HCI_LE_ENH_RX_TEST_CMD_OPCODE                  = 0x33,
    HCI_LE_ENH_TX_TEST_CMD_OPCODE                  = 0x34,
    HCI_LE_SET_ADV_SET_RAND_ADDR_CMD_OPCODE        = 0x35,
    HCI_LE_SET_EXT_ADV_PARAM_CMD_OPCODE            = 0x36,
    HCI_LE_SET_EXT_ADV_DATA_CMD_OPCODE             = 0x37,
    HCI_LE_SET_EXT_SCAN_RSP_DATA_CMD_OPCODE        = 0x38,
    HCI_LE_SET_EXT_ADV_EN_CMD_OPCODE               = 0x39,
    HCI_LE_RD_MAX_ADV_DATA_LEN_CMD_OPCODE          = 0x3A,
    HCI_LE_RD_NB_SUPP_ADV_SETS_CMD_OPCODE          = 0x3B,
    HCI_LE_RMV_ADV_SET_CMD_OPCODE                  = 0x3C,
    HCI_LE_CLEAR_ADV_SETS_CMD_OPCODE               = 0x3D,
    HCI_LE_SET_PER_ADV_PARAM_CMD_OPCODE            = 0x3E,
    HCI_LE_SET_PER_ADV_DATA_CMD_OPCODE             = 0x3F,
    HCI_LE_SET_PER_ADV_EN_CMD_OPCODE               = 0x40,
    HCI_LE_SET_EXT_SCAN_PARAM_CMD_OPCODE           = 0x41,
    HCI_LE_SET_EXT_SCAN_EN_CMD_OPCODE              = 0x42,
    HCI_LE_EXT_CREATE_CON_CMD_OPCODE               = 0x43,
    HCI_LE_PER_ADV_CREATE_SYNC_CMD_OPCODE          = 0x44,
    HCI_LE_PER_ADV_CREATE_SYNC_CANCEL_CMD_OPCODE   = 0x45,
    HCI_LE_PER_ADV_TERM_SYNC_CMD_OPCODE            = 0x46,
    HCI_LE_ADD_DEV_TO_PER_ADV_LIST_CMD_OPCODE      = 0x47,
    HCI_LE_RMV_DEV_FROM_PER_ADV_LIST_CMD_OPCODE    = 0x48,
    HCI_LE_CLEAR_PER_ADV_LIST_CMD_OPCODE           = 0x49,
    HCI_LE_RD_PER_ADV_LIST_SIZE_CMD_OPCODE         = 0x4A,
    HCI_LE_RD_TX_PWR_CMD_OPCODE                    = 0x4B,
    HCI_LE_RD_RF_PATH_COMP_CMD_OPCODE              = 0x4C,
    HCI_LE_WR_RF_PATH_COMP_CMD_OPCODE              = 0x4D,
    HCI_LE_SET_PRIV_MODE_CMD_OPCODE                = 0x4E,
/*
    HCI_LE_RX_TEST_V3_CMD_OPCODE                   = 0x4F,
    HCI_LE_TX_TEST_V3_CMD_OPCODE                   = 0x50,
    HCI_LE_SET_CONLESS_CTE_TX_PARAM_CMD_OPCODE          = 0x51,
    HCI_LE_SET_CONLESS_CTE_TX_EN_CMD_OPCODE             = 0x52,
    HCI_LE_SET_CONLESS_IQ_SAMPL_EN_CMD_OPCODE           = 0x53,
    HCI_LE_SET_CON_CTE_RX_PARAM_CMD_OPCODE              = 0x54,
    HCI_LE_SET_CON_CTE_TX_PARAM_CMD_OPCODE              = 0x55,
    HCI_LE_CON_CTE_REQ_EN_CMD_OPCODE                    = 0x56,
    HCI_LE_CON_CTE_RSP_EN_CMD_OPCODE                    = 0x57,
    HCI_LE_RD_ANTENNA_INF_CMD_OPCODE                    = 0x58,
    HCI_LE_SET_PER_ADV_REC_EN_CMD_OPCODE                = 0x59,
    HCI_LE_PER_ADV_SYNC_TRANSF_CMD_OPCODE               = 0x5A,
    HCI_LE_PER_ADV_SET_INFO_TRANSF_CMD_OPCODE           = 0x5B,
    HCI_LE_SET_PER_ADV_SYNC_TRANSF_PARAM_CMD_OPCODE     = 0x5C,
    HCI_LE_SET_DFT_PER_ADV_SYNC_TRANSF_PARAM_CMD_OPCODE = 0x5D,
    HCI_LE_GEN_DHKEY_V2_CMD_OPCODE                      = 0x5E,
    HCI_LE_MOD_SLEEP_CLK_ACC_CMD_OPCODE                 = 0x5F,
*/
    LE_CTRL_CMD_OPCODE_MAX,
};

enum hci_evt_code
{
    HCI_INQ_CMP_EVT_CODE                       = 0x01,
    HCI_INQ_RES_EVT_CODE                       = 0x02,
    HCI_CON_CMP_EVT_CODE                       = 0x03,
    HCI_CON_REQ_EVT_CODE                       = 0x04,
    HCI_DISC_CMP_EVT_CODE                      = 0x05,
    HCI_AUTH_CMP_EVT_CODE                      = 0x06,
    HCI_REM_NAME_REQ_CMP_EVT_CODE              = 0x07,
    HCI_ENC_CHG_EVT_CODE                       = 0x08,
    HCI_CHG_CON_LK_CMP_EVT_CODE                = 0x09,
    HCI_MASTER_LK_CMP_EVT_CODE                 = 0x0A,
    HCI_RD_REM_SUPP_FEATS_CMP_EVT_CODE         = 0x0B,
    HCI_RD_REM_VER_INFO_CMP_EVT_CODE           = 0x0C,
    HCI_QOS_SETUP_CMP_EVT_CODE                 = 0x0D,
    HCI_CMD_CMP_EVT_CODE                       = 0x0E,
    HCI_CMD_STATUS_EVT_CODE                    = 0x0F,
    HCI_HW_ERR_EVT_CODE                        = 0x10,
    HCI_FLUSH_OCCURRED_EVT_CODE                = 0x11,
    HCI_ROLE_CHG_EVT_CODE                      = 0x12,
    HCI_NB_CMP_PKTS_EVT_CODE                   = 0x13,
    HCI_MODE_CHG_EVT_CODE                      = 0x14,
    HCI_RETURN_LINK_KEYS_EVT_CODE              = 0x15,
    HCI_PIN_CODE_REQ_EVT_CODE                  = 0x16,
    HCI_LK_REQ_EVT_CODE                        = 0x17,
    HCI_LK_NOTIF_EVT_CODE                      = 0x18,
    HCI_DATA_BUF_OVFLW_EVT_CODE                = 0x1A,
    HCI_MAX_SLOT_CHG_EVT_CODE                  = 0x1B,
    HCI_RD_CLK_OFF_CMP_EVT_CODE                = 0x1C,
    HCI_CON_PKT_TYPE_CHG_EVT_CODE              = 0x1D,
    HCI_QOS_VIOL_EVT_CODE                      = 0x1E,
    HCI_PAGE_SCAN_REPET_MODE_CHG_EVT_CODE      = 0x20,
    HCI_FLOW_SPEC_CMP_EVT_CODE                 = 0x21,
    HCI_INQ_RES_WITH_RSSI_EVT_CODE             = 0x22,
    HCI_RD_REM_EXT_FEATS_CMP_EVT_CODE          = 0x23,
    HCI_SYNC_CON_CMP_EVT_CODE                  = 0x2C,
    HCI_SYNC_CON_CHG_EVT_CODE                  = 0x2D,
    HCI_SNIFF_SUB_EVT_CODE                     = 0x2E,
    HCI_EXT_INQ_RES_EVT_CODE                   = 0x2F,
    HCI_ENC_KEY_REFRESH_CMP_EVT_CODE           = 0x30,
    HCI_IO_CAP_REQ_EVT_CODE                    = 0x31,
    HCI_IO_CAP_RSP_EVT_CODE                    = 0x32,
    HCI_USER_CFM_REQ_EVT_CODE                  = 0x33,
    HCI_USER_PASSKEY_REQ_EVT_CODE              = 0x34,
    HCI_REM_OOB_DATA_REQ_EVT_CODE              = 0x35,
    HCI_SP_CMP_EVT_CODE                        = 0x36,
    HCI_LINK_SUPV_TO_CHG_EVT_CODE              = 0x38,
    HCI_ENH_FLUSH_CMP_EVT_CODE                 = 0x39,
    HCI_USER_PASSKEY_NOTIF_EVT_CODE            = 0x3B,
    HCI_KEYPRESS_NOTIF_EVT_CODE                = 0x3C,
    HCI_REM_HOST_SUPP_FEATS_NOTIF_EVT_CODE     = 0x3D,
    HCI_LE_META_EVT_CODE                       = 0x3E,
    HCI_MAX_EVT_MSK_PAGE_1_CODE                = 0x40,
    HCI_SYNC_TRAIN_CMP_EVT_CODE                = 0x4F,
    HCI_SYNC_TRAIN_REC_EVT_CODE                = 0x50,
    HCI_CON_SLV_BCST_REC_EVT_CODE              = 0x51,
    HCI_CON_SLV_BCST_TO_EVT_CODE               = 0x52,
    HCI_TRUNC_PAGE_CMP_EVT_CODE                = 0x53,
    HCI_SLV_PAGE_RSP_TO_EVT_CODE               = 0x54,
    HCI_CON_SLV_BCST_CH_MAP_CHG_EVT_CODE       = 0x55,
    HCI_AUTH_PAYL_TO_EXP_EVT_CODE              = 0x57,
    HCI_MAX_EVT_MSK_PAGE_2_CODE                = 0x58,
    HCI_DBG_META_EVT_CODE                      = 0xFF,

};

enum hci_le_mega_evt_subcode
{
    HCI_LE_CON_CMP_EVT_SUBCODE                 = 0x01,
    HCI_LE_ADV_REPORT_EVT_SUBCODE              = 0x02,
    HCI_LE_CON_UPDATE_CMP_EVT_SUBCODE          = 0x03,
    HCI_LE_RD_REM_USED_FEATS_CMP_EVT_SUBCODE   = 0x04,
    HCI_LE_LTK_REQUEST_EVT_SUBCODE             = 0x05,
    HCI_LE_REM_CON_PARAM_REQ_EVT_SUBCODE       = 0x06,
    HCI_LE_DATA_LEN_CHG_EVT_SUBCODE            = 0x07,
    HCI_LE_RD_LOC_P256_PUB_KEY_CMP_EVT_SUBCODE = 0x08,
    HCI_LE_GEN_DHKEY_CMP_EVT_SUBCODE           = 0x09,
    HCI_LE_ENH_CON_CMP_EVT_SUBCODE             = 0x0A,
    HCI_LE_DIR_ADV_REP_EVT_SUBCODE             = 0x0B,
    HCI_LE_PHY_UPD_CMP_EVT_SUBCODE             = 0x0C,
    HCI_LE_EXT_ADV_REPORT_EVT_SUBCODE          = 0x0D,
    HCI_LE_PER_ADV_SYNC_EST_EVT_SUBCODE        = 0x0E,
    HCI_LE_PER_ADV_REPORT_EVT_SUBCODE          = 0x0F,
    HCI_LE_PER_ADV_SYNC_LOST_EVT_SUBCODE       = 0x10,
    HCI_LE_SCAN_TIMEOUT_EVT_SUBCODE            = 0x11,
    HCI_LE_ADV_SET_TERMINATED_EVT_SUBCODE      = 0x12,
    HCI_LE_SCAN_REQ_RCVD_EVT_SUBCODE           = 0x13,
    HCI_LE_CH_SEL_ALGO_EVT_SUBCODE             = 0x14,
    HCI_LE_META_EVT_SUBCODE_MAX,
};

struct evt_mask
{
    ///8-byte array for mask value
    uint8_t mask[EVT_MASK_LEN];
}__attribute__((packed));

struct hci_set_evt_mask_cmd
{
    ///Event Mask
    struct evt_mask    event_mask;
}__attribute__((packed));

struct hci_le_set_evt_mask_cmd 
{
    ///LE Event Mask
    struct evt_mask le_mask;
}__attribute__((packed));

struct hci_rd_rem_ver_info_cmd 
{
    uint16_t conhdl;
}__attribute__((packed));

struct hci_disconnect_cmd
{
    /// connection handle
    uint16_t    conhdl;
    /// reason
    uint8_t     reason;
}__attribute__((packed));

struct hci_rd_rssi_cmd
{
    uint16_t conhdl;
}__attribute__((packed));

struct bd_addr
{
    ///6-byte array address value
    uint8_t  addr[BLE_ADDR_LEN];
}__attribute__((packed));

struct hci_le_set_rand_addr_cmd
{
    struct bd_addr rand_addr;
}__attribute__((packed));

struct le_adv_param
{
    ///Minimum interval for advertising
    uint16_t       adv_intv_min;
    ///Maximum interval for advertising
    uint16_t       adv_intv_max;
    ///Advertising type
    uint8_t        adv_type;
    ///Own address type:  public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t        own_addr_type;
    ///Peer address type: public=0 / random=1
    uint8_t        peer_addr_type;
    ///Peer Bluetooth device address
    struct bd_addr peer_addr;
    ///Advertising channel map
    uint8_t        adv_chnl_map;
    ///Advertising filter policy
    uint8_t        adv_filt_policy;

}__attribute__((packed));

struct hci_le_set_adv_param_cmd
{
    struct le_adv_param param;
}__attribute__((packed));

enum advertising_type
{
    ADV_IND,
    ADV_DIRECT_IND_HIGH_DUTY,
    ADV_SCAN_IND,
    ADV_NONCONN_IND,
    ADV_DIRECT_IND_LOW_DUTY,
}__attribute__((packed));

struct adv_data
{
    uint8_t length;
    uint8_t data[ADV_DATA_LEN_MAX];
}__attribute__((packed));

struct hci_le_set_adv_data_cmd
{
    struct adv_data adv;
}__attribute__((packed));

struct hci_le_set_scan_rsp_data_cmd
{
    struct adv_data scan_rsp;
}__attribute__((packed)); 

struct hci_le_set_adv_en_cmd
{
    uint8_t enable;
}__attribute__((packed));

struct le_scan_param
{
    ///Scan type - 0=passive / 1=active
    uint8_t        scan_type;
    ///Scan interval
    uint16_t       scan_intv;
    ///Scan window size
    uint16_t       scan_window;
    ///Own address type - public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t        own_addr_type;
    ///Scan filter policy
    uint8_t        scan_filt_policy;
}__attribute__((packed));

struct hci_le_set_scan_param_cmd
{
    struct le_scan_param param;
}__attribute__((packed));

struct hci_le_set_scan_en_cmd
{
    ///Scan enable - 0=disabled, 1=enabled
    uint8_t        scan_en;
    ///Enable for duplicates filtering - 0 =disabled/ 1=enabled
    uint8_t        filter_duplic_en;
}__attribute__((packed));

struct le_create_con_param
{
    ///Scan interval (N * 0.625 ms)
    uint16_t       scan_intv;
    ///Scan window size (N * 0.625 ms)
    uint16_t       scan_window;
    ///Initiator filter policy
    uint8_t        init_filt_policy;
    ///Peer address type - public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t        peer_addr_type;
    ///Peer BD address
    struct bd_addr peer_addr;
    ///Own address type - public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t        own_addr_type;
    ///Minimum of connection interval (N * 1.25 ms)
    uint16_t       con_intv_min;
    ///Maximum of connection interval (N * 1.25 ms)
    uint16_t       con_intv_max;
    ///Connection latency
    uint16_t       con_latency;
    ///Link supervision timeout
    uint16_t       superv_to;
    ///Minimum CE length (N * 0.625 ms)
    uint16_t       ce_len_min;
    ///Maximum CE length (N * 0.625 ms)
    uint16_t       ce_len_max;
}__attribute__((packed));

struct hci_le_create_con_cmd
{
    struct le_create_con_param param;
}__attribute__((packed));

struct ble_dev_addr
{
    ///Type of address of the device to be added to the White List - 0=public/1=random
    uint8_t        addr_type;
    ///Address of device to be added to White List
    struct bd_addr addr;
}__attribute__((packed));

struct hci_le_add_dev_to_wlst_cmd
{
    struct ble_dev_addr dev;
}__attribute__((packed));

struct hci_le_rmv_dev_from_wlst_cmd
{
    struct ble_dev_addr dev;
}__attribute__((packed));

struct hci_le_con_update_cmd
{
    ///Connection Handle
    uint16_t       conhdl;
    ///Minimum of connection interval (units of 1.25 ms)
    uint16_t       con_intv_min;
    ///Maximum of connection interval (units of 1.25 ms)
    uint16_t       con_intv_max;
    ///Connection latency (units of connection event)
    uint16_t       con_latency;
    ///Link supervision timeout (units of 10 ms)
    uint16_t       superv_to;
    ///Minimum of CE length (units of 0.625 ms)
    uint16_t       ce_len_min;
    ///Maximum of CE length (units of 0.625 ms)
    uint16_t       ce_len_max;
}__attribute__((packed));

struct le_chnl_map
{
    ///5-byte channel map array
    uint8_t map[LE_CHNL_MAP_LEN];
}__attribute__((packed));

struct hci_le_set_host_ch_class_cmd
{
    ///Channel map
    struct le_chnl_map chmap;
}__attribute__((packed));

struct hci_le_rd_chnl_map_cmd
{
    uint16_t    conhdl;
}__attribute__((packed));

struct le_states
{
    ///8-byte array for LE states
    uint8_t  supp_states[LE_STATES_LEN];
}__attribute__((packed));

struct hci_le_rd_rem_feats_cmd
{
    ///Connection handle
    uint16_t            conhdl;
}__attribute__((packed));

struct ltk
{
    ///16-byte array for LTK value
    uint8_t ltk[BLE_KEY_LEN];
}__attribute__((packed));

struct hci_le_enc_cmd
{
    ///Long term key structure
    struct ltk     key;
    ///Pointer to buffer with plain data to encrypt - 16 bytes
    uint8_t        plain_data[16];
}__attribute__((packed));

struct rand_nb
{
    ///8-byte array for random number
    uint8_t     nb[RAND_NB_LEN];
}__attribute__((packed));

struct hci_le_start_enc_cmd
{
    ///Connection handle
    uint16_t        conhdl;
    ///Random number - 8B
    struct rand_nb  nb;
    ///Encryption Diversifier
    uint16_t       enc_div;
    ///Long term key
    struct ltk     ltk;
}__attribute__((packed));

struct hci_le_ltk_req_reply_cmd
{
    ///Connection handle
    uint16_t        conhdl;
    ///Long term key
    struct ltk      ltk;
}__attribute__((packed));

struct hci_le_ltk_req_neg_reply_cmd
{
    ///Connection handle
    uint16_t        conhdl;
}__attribute__((packed));

struct hci_le_rx_test_cmd
{
    ///RX frequency for Rx test
    uint8_t        rx_freq;
}__attribute__((packed));

struct hci_le_tx_test_cmd
{
    ///TX frequency for Tx test
    uint8_t        tx_freq;
    ///TX test data length
    uint8_t        test_data_len;
    ///TX test payload type - see enum
    uint8_t        pk_payload_type;
}__attribute__((packed));

struct hci_le_rem_con_param_req_reply_cmd
{
    ///Connection handle
    uint16_t        conhdl;
    ///Interval_Min
    uint16_t        interval_min;
    ///Interval_Max
    uint16_t        interval_max;
    ///Latency
    uint16_t        latency;
    ///Timeout
    uint16_t        timeout;
    ///Minimum_CE_Length
    uint16_t        min_ce_len;
    ///Maximum_CE_Length
    uint16_t        max_ce_len;
}__attribute__((packed));

struct hci_le_rem_con_param_req_neg_reply_cmd
{
    ///Connection handle
    uint16_t        conhdl;
    ///Reason
    uint8_t         reason;
}__attribute__((packed));

struct hci_le_set_data_len_cmd
{
    ///Connection Handle
    uint16_t       conhdl;
    ///Preferred maximum number of payload octets that the local Controller should include
    ///in a single Link Layer Data Channel PDU.
    uint16_t       tx_octets;
    ///Preferred maximum number of microseconds that the local Controller should use to transmit
    ///a single Link Layer Data Channel PDU
    uint16_t       tx_time;
}__attribute__((packed));

struct hci_le_wr_suggted_dft_data_len_cmd
{
    ///Suggested value for the Controller's maximum transmitted number of payload octets to be used
    uint16_t       suggted_max_tx_octets;
    ///Suggested value for the Controller's maximum packet transmission time to be used
    uint16_t       suggted_max_tx_time;
}__attribute__((packed));

struct hci_le_generate_dh_key_cmd
{
    uint8_t public_key[64];
}__attribute__((packed));

struct irk
{
    ///16-byte array for IRK value
    uint8_t key[BLE_KEY_LEN];
}__attribute__((packed));

struct hci_le_add_dev_to_rslv_list_cmd
{
    /// Peer Identity Address Type
    uint8_t             peer_id_addr_type;
    /// Peer Identity Address
    struct bd_addr      peer_id_addr;
    /// Peer IRK
    struct irk          peer_irk;
    /// Local IRK
    struct irk          local_irk;
}__attribute__((packed));



struct hci_le_rd_peer_rslv_addr_cmd
{
    /// Peer Identity Address Type
    uint8_t             peer_id_addr_type;
    /// Peer Identity Address
    struct bd_addr      peer_id_addr;
}__attribute__((packed));

struct hci_le_rd_loc_rslv_addr_cmd
{
    /// Peer Identity Address Type
    uint8_t             peer_id_addr_type;
    /// Peer Identity Address
    struct bd_addr      peer_id_addr;
}__attribute__((packed));

struct hci_le_rmv_dev_from_rslv_list_cmd
{
    /// Peer Identity Address Type
    uint8_t             peer_id_addr_type;
    /// Peer Identity Address
    struct bd_addr      peer_id_addr;
}__attribute__((packed));

struct hci_le_set_addr_resol_en_cmd
{
    /// Address Resolution Enable
    uint8_t             enable;
}__attribute__((packed));

struct hci_le_set_rslv_priv_addr_to_cmd
{
    /// RPA Timeout
    uint16_t            rpa_timeout;
}__attribute__((packed));

struct hci_le_rd_phy_cmd
{
    /// Connection Handle
    uint16_t            conhdl;
}__attribute__((packed));

struct hci_le_set_dft_phy_cmd
{
    /// Preferred PHYS selection
    uint8_t            all_phys;
    /// Preferred PHYS for TX
    uint8_t            tx_phys;
    /// Preferred PHYS for RX
    uint8_t            rx_phys;
}__attribute__((packed));

struct hci_le_set_phy_cmd
{
    /// Connection Handle
    uint16_t           conhdl;
    /// Preferred PHYS selection
    uint8_t            all_phys;
    /// Preferred PHYS for TX
    uint8_t            tx_phys;
    /// Preferred PHYS for RX
    uint8_t            rx_phys;
    /// PHY options
    uint16_t           phy_opt;
}__attribute__((packed));

struct hci_le_rx_test_v2_cmd
{
    /// RX channel, range: 0x00 to 0x27
    uint8_t     rx_channel;
    /// PHY (@enum le_phy_value)
    uint8_t     phy;
    /// Modulation index (0: standard | 1: stable)
    uint8_t     mod_idx;
}__attribute__((packed));


struct hci_le_tx_test_v2_cmd
{
    /// TX channel, range: 0x00 to 0x27
    uint8_t     tx_channel;
    /// Length of test data in bytes, range: 0x00 to 0xFF
    uint8_t     test_data_len;
    /**
     * Packet payload
     * 0x00 PRBS9 sequence "11111111100000111101" (in transmission order) as described in [Vol 6] Part F, Section 4.1.5
     * 0x01 Repeated "11110000" (in transmission order) sequence as described in [Vol 6] Part F, Section 4.1.5
     * 0x02 Repeated "10101010" (in transmission order) sequence as described in [Vol 6] Part F, Section 4.1.5
     * 0x03 PRBS15 sequence as described in [Vol 6] Part F, Section 4.1.5
     * 0x04 Repeated "11111111" (in transmission order) sequence
     * 0x05 Repeated "00000000" (in transmission order) sequence
     * 0x06 Repeated "00001111" (in transmission order) sequence
     * 0x07 Repeated "01010101" (in transmission order) sequence
     * 0x08-0xFF Reserved for future use
     */
    uint8_t     pkt_payl;
    /// PHY (@enum le_phy_value)
    uint8_t     phy;
}__attribute__((packed));

struct hci_le_set_adv_set_rand_addr_cmd
{
    /// Advertising handle
    uint8_t adv_hdl;
    /// Advertising random address
    struct bd_addr rand_addr;
}__attribute__((packed));

struct le_ext_adv_param
{
    /// Advertising event properties
    uint16_t adv_evt_properties;
    /// Primary advertising minimum interval
    uint8_t prim_adv_intv_min[3];
    /// Primary advertising maximum interval
    uint8_t prim_adv_intv_max[3];
    /// Primary advertising channel map
    uint8_t prim_adv_chnl_map;
    /// Own address type:  public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t own_addr_type;
    /// Peer address type: public=0 / random=1
    uint8_t peer_addr_type;
    /// Peer Bluetooth device address
    struct bd_addr peer_addr;
    /// Advertising filter policy
    uint8_t adv_filt_policy;
    /// Advertising Tx power
    int8_t adv_tx_pwr;
    /// Primary advertising PHY
    uint8_t prim_adv_phy;
    /// Secondary advertising max skip
    uint8_t sec_adv_max_skip;
    /// Secondary advertising PHY
    uint8_t sec_adv_phy;
    /// Advertising SID
    uint8_t adv_sid;
    /// Scan request notification enable
    uint8_t scan_req_notif_en;
}__attribute__((packed));

struct hci_le_set_ext_adv_param_cmd
{
    uint8_t adv_hdl;
    struct le_ext_adv_param param;
}__attribute__((packed));

struct hci_le_set_ext_adv_data_cmd
{
    /// Advertising handle
    uint8_t adv_hdl;
    /**
     *  Operation
     *  0x00 Intermediate fragment of fragmented extended advertising data
     *  0x01 First fragment of fragmented extended advertising data
     *  0x02 Last fragment of fragmented extended advertising data
     *  0x03 Complete extended advertising data
     *  0x04 [ID7300_r06] Unchanged data (just update the Advertising DID)
     *  All other values Reserved for future use
     */
    uint8_t operation;
    /**
     *  Fragment preference
     *  0x00 The Controller may fragment all Host advertising data
     *  0x01 The Controller should not fragment nor minimize fragmentation of Host advertising data
     *  All other values Reserved for future use
     */
    uint8_t frag_pref;
    /// Advertising Data Length (0-252 bytes)
    uint8_t data_len;
    /// Advertising data
    uint8_t data[];
}__attribute__((packed));

struct hci_le_set_ext_scan_rsp_data_cmd
{
    /// Advertising handle
    uint8_t adv_hdl;
    /**
     *  Operation
     *  0x00 Intermediate fragment of fragmented extended advertising data
     *  0x01 First fragment of fragmented extended advertising data
     *  0x02 Last fragment of fragmented extended advertising data
     *  0x03 Complete extended advertising data
     *  0x04 [ID7300_r06] Unchanged data (just update the Advertising DID)
     *  All other values Reserved for future use
     */
    uint8_t operation;
    /**
     *  Fragment preference
     *  0x00 The Controller may fragment all Host advertising data
     *  0x01 The Controller should not fragment nor minimize fragmentation of Host advertising data
     *  All other values Reserved for future use
     */
    uint8_t frag_pref;
    /// Scan Response Data Length (0-252 bytes)
    uint8_t data_len;
    /// Advertising data
    uint8_t data[];
}__attribute__((packed));

struct hci_le_set_ext_adv_en_cmd
{
    /// Enable
    uint8_t enable;
    /// Number of sets (1 - 0x3F)
    uint8_t nb_sets;
    /// Advertising handle
    uint8_t adv_hdl[1];
    /// Duration (N * 10 ms), 0x0000 No advertising duration. Advertising to continue until the Host disables it.
    uint16_t duration[1];
    /// Maximum number of extended advertising events
    uint8_t max_ext_adv_evt[1];
}__attribute__((packed));

struct hci_le_rem_adv_set_cmd
{
    /// Advertising handle
    uint8_t adv_hdl;
}__attribute__((packed));

struct le_periodic_adv_param
{
    /// Minimum advertising interval for periodic advertising
    uint16_t adv_intv_min;
    /// Maximum advertising interval for periodic advertising
    uint16_t adv_intv_max;
    /// Advertising properties
    uint16_t adv_prop;
}__attribute__((packed));

struct hci_le_set_per_adv_param_cmd
{
    uint8_t adv_hdl;
    struct le_periodic_adv_param param;
}__attribute__((packed));

struct hci_le_set_per_adv_data_cmd
{
    /// Advertising handle
    uint8_t adv_hdl;
    /**
     *  Operation
     *  0x00 Intermediate fragment of fragmented periodic advertising data
     *  0x01 First fragment of fragmented periodic advertising data
     *  0x02 Last fragment of fragmented periodic advertising data
     *  0x03 Complete periodic advertising data
     *  All other values Reserved for future use
     */
    uint8_t operation;
    /// Advertising Data Length (0-252 bytes)
    uint8_t data_len;
    /// Advertising data
    uint8_t data[];
}__attribute__((packed));

struct hci_le_set_per_adv_en_cmd
{
    /// Enable
    uint8_t enable;
    /// Advertising handle
    uint8_t adv_hdl;
}__attribute__((packed));

#define MAX_SCAN_PHYS     2

struct ext_scan_param
{
    ///Own address type public/random/rpa
    uint8_t         own_addr_type;
    ///Scanning filter policy
    uint8_t         scan_filt_policy;
    ///Indicates the PHY(s) on which the advertising packets should be received
    uint8_t         scan_phys;
    ///Paramaters for PHY(s)
    struct scan_phy_param
    {
        ///Scaning Type: passive/active
        uint8_t         scan_type;
        ///Scan interval (slots)
        uint16_t        scan_intv;
        ///Scan window size (slots)
        uint16_t        scan_window;
    }__attribute__((packed)) phy[MAX_SCAN_PHYS];
}__attribute__((packed));

struct hci_le_set_ext_scan_param_cmd
{
    struct ext_scan_param param;
}__attribute__((packed));

struct hci_le_set_ext_scan_en_cmd
{
    ///Scan enable - 0=disabled, 1=enabled
    uint8_t             scan_en; 
    ///Filter duplicates - 0=disabled, 1=enabled, 2=enabled & reset each scan period
    uint8_t             filter_duplic;
    ///Scan duration (Time=N*10ms)  | 0x0000: Scan continuously until explicitly disable
    uint16_t            duration;
    ///Scan period (Time=N*1.28sec) | 0x0000: Periodic scanning disabled
    uint16_t            period;
}__attribute__((packed));

struct init_phy_param
{
    ///Scan interval (N * 0.625 ms)
    uint16_t        scan_interval;
    ///Scan window size (N * 0.625 ms)
    uint16_t        scan_window;
    ///Minimum of connection interval (N * 1.25 ms)
    uint16_t       con_intv_min;
    ///Maximum of connection interval (N * 1.25 ms)
    uint16_t       con_intv_max;
    ///Connection latency
    uint16_t       con_latency;
    ///Link supervision timeout
    uint16_t       superv_to;
    ///Minimum CE length (N * 0.625 ms)
    uint16_t       ce_len_min;
    ///Maximum CE length (N * 0.625 ms)
    uint16_t       ce_len_max;
}__attribute__((packed));

#define MAX_INIT_PHYS     3

struct ext_create_con_param
{
    ///Initiator filter policy
    uint8_t         init_filter_policy;
    ///Own address type public/random/rpa
    uint8_t         own_addr_type;
    ///Peer address type public/random/rpa
    uint8_t         peer_addr_type;
    ///Peer address
    struct bd_addr  peer_addr;
    ///Indicates the PHY(s) on which the advertising packets should be received
    uint8_t         init_phys;
    ///Paramaters for PHY(s)
    struct init_phy_param phy[MAX_INIT_PHYS];
}__attribute__((packed));

struct hci_le_ext_create_con_cmd
{
    struct ext_create_con_param param;
}__attribute__((packed));

struct per_adv_create_sync_param
{
    /// Options (@see enum per_sync_opt)
    uint8_t         options;
    ///Advertising SID
    uint8_t         adv_sid;
    ///Advertising address type
    uint8_t         adv_addr_type;
    ///Advertiser address
    struct bd_addr  adv_addr;
    ///max Skip after receive
    uint16_t        skip;
    ///Sync timeout (Time=N*10ms)
    uint16_t        sync_to;
    /// Sync CTE type (@see enum sync_cte_type)
    uint8_t         sync_cte_type;
}__attribute__((packed));

struct hci_le_per_adv_create_sync_cmd
{
    struct per_adv_create_sync_param param;
}__attribute__((packed));

struct hci_le_per_adv_term_sync_cmd
{
    ///Sync handle
    uint16_t        sync_handle;
}__attribute__((packed));

struct hci_le_add_dev_to_per_adv_list_cmd
{
     ///Advertiser address type
    uint8_t         adv_addr_type;
    ///Advertiser address
    struct bd_addr  adv_addr;
    ///Advertising SID
    uint8_t         adv_sid;
}__attribute__((packed));

struct hci_le_rmv_dev_from_per_adv_list_cmd
{
     ///Advertiser address type
    uint8_t         adv_addr_type;
    ///Advertiser address
    struct bd_addr  adv_addr;
    ///Advertising SID
    uint8_t         adv_sid;
}__attribute__((packed));

struct hci_le_wr_rf_path_comp_cmd
{
    /// RF TX Path Compensation
    int16_t tx_path_comp;
    /// RF RX Path Compensation
    int16_t rx_path_comp;
}__attribute__((packed));

struct hci_le_set_priv_mode_cmd
{
    ///Peer identity address type
    uint8_t         peer_addr_type;
    ///Peer identity address
    struct bd_addr  peer_addr;
    ///Privacy mode
    uint8_t         priv_mode;
}__attribute__((packed));

#define MAX_SWITCHING_PATTERN_LEN  (0x4B)

struct hci_le_rx_test_v3_cmd
{
    /// RX channel, range: 0x00 to 0x27
    uint8_t     rx_channel;
    /// PHY (@enum le_phy_value)
    uint8_t     phy;
    /// Modulation index (0: standard | 1: stable)
    uint8_t     mod_idx;
    /// Expected CTE length in 8us units, range: 0x02 to 0x14
    uint8_t     exp_cte_len;
    /// Expected CTE type (0: AOA | 1: AOD-1us | 2: AOD-2us)
    uint8_t     exp_cte_type;
    /// Slot durations (1: 1 us | 2: 2 us)
    uint8_t     slot_dur;
    /// Length of switching pattern (number of antenna IDs in the pattern), range: 0x02 to 0x4B
    uint8_t     switching_pattern_len;
    /// Antenna IDs
    uint8_t     antenna_id[MAX_SWITCHING_PATTERN_LEN];
}__attribute__((packed));

struct hci_le_tx_test_v3_cmd
{
    /// TX channel, range: 0x00 to 0x27
    uint8_t     tx_channel;
    /// Length of test data in bytes, range: 0x00 to 0xFF
    uint8_t     test_data_len;
    /**
     * Packet payload
     * 0x00 PRBS9 sequence "11111111100000111101" (in transmission order) as described in [Vol 6] Part F, Section 4.1.5
     * 0x01 Repeated "11110000" (in transmission order) sequence as described in [Vol 6] Part F, Section 4.1.5
     * 0x02 Repeated "10101010" (in transmission order) sequence as described in [Vol 6] Part F, Section 4.1.5
     * 0x03 PRBS15 sequence as described in [Vol 6] Part F, Section 4.1.5
     * 0x04 Repeated "11111111" (in transmission order) sequence
     * 0x05 Repeated "00000000" (in transmission order) sequence
     * 0x06 Repeated "00001111" (in transmission order) sequence
     * 0x07 Repeated "01010101" (in transmission order) sequence
     * 0x08-0xFF Reserved for future use
     */
    uint8_t     pkt_payl;
    /// PHY (@enum le_phy_value)
    uint8_t     phy;
    /// CTE length (in 8us unit)
    uint8_t     cte_len;
    /// CTE type (0: AOA | 1: AOD-1us | 2: AOD-2us)
    uint8_t     cte_type;
    /// Length of switching pattern (number of antenna IDs in the pattern)
    uint8_t     switching_pattern_len;
    /// Antenna IDs
    uint8_t     antenna_id[MAX_SWITCHING_PATTERN_LEN];
}__attribute__((packed));

struct hci_nb_cmp_pkts_evt
{
    uint8_t     nb_of_hdl;
    uint16_t    conhdl[1];
    uint16_t    nb_comp_pkt[1];
}__attribute__((packed));

struct hci_disc_cmp_evt
{
    ///Status of received command
    uint8_t     status;
    ///Connection Handle
    uint16_t    conhdl;
    ///Reason for disconnection
    uint8_t     reason;
}__attribute__((packed));

struct version_ind
{
    ///LMP version
    uint8_t     vers;
    ///Manufacturer name
    uint16_t    compid;
    ///LMP subversion
    uint16_t    subvers;
}__attribute__((packed));

struct hci_rd_rem_ver_info_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    struct version_ind ver;
}__attribute__((packed));

struct hci_enc_change_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///Encryption enabled information
    uint8_t     enc_stat;
}__attribute__((packed));

struct hci_enc_key_ref_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
}__attribute__((packed));

struct hci_data_buf_ovflw_evt
{
    ///Link type
    uint8_t link_type;
}__attribute__((packed));

struct hci_hw_err_evt
{
    /// HW error code
    uint8_t hw_code;
}__attribute__((packed));

enum
{
    ///Master role
    ROLE_MASTER,
    ///Slave role
    ROLE_SLAVE,
};

struct hci_le_enh_con_cmp_evt
{
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Device role - 0=Master/ 1=Slave
    uint8_t             role;
    ///Peer address type - 0=public/1=random
    uint8_t             peer_addr_type;
    ///Peer address
    struct bd_addr      peer_addr;
    ///Local Resolvable Private Address
    struct bd_addr      loc_rslv_priv_addr;
    ///Peer Resolvable Private Address
    struct bd_addr      peer_rslv_priv_addr;
    ///Connection interval
    uint16_t            con_interval;
    ///Connection latency
    uint16_t            con_latency;
    ///Link supervision timeout
    uint16_t            sup_to;
    ///Master clock accuracy
    uint8_t             clk_accuracy;
}__attribute__((packed));

struct hci_le_con_cmp_evt
{
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Device role - 0=Master/ 1=Slave
    uint8_t             role;
    ///Peer address type - 0=public/1=random
    uint8_t             peer_addr_type;
    ///Peer address
    struct bd_addr      peer_addr;
    ///Connection interval
    uint16_t            con_interval;
    ///Connection latency
    uint16_t            con_latency;
    ///Link supervision timeout
    uint16_t            sup_to;
    ///Master clock accuracy
    uint8_t             clk_accuracy;
}__attribute__((packed));

struct hci_le_con_update_cmp_evt
{
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Connection interval value
    uint16_t            con_interval;
    ///Connection latency value
    uint16_t            con_latency;
    ///Supervision timeout
    uint16_t            sup_to;
}__attribute__((packed));

struct hci_rd_local_supp_feats_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t         status;
    ///Local  supported features
    uint8_t feats[LMP_FEATS_LEN];
}__attribute__((packed));

struct le_features
{
    ///8-byte array for LE features
    uint8_t feats[LE_FEATS_LEN];
}__attribute__((packed));

struct hci_le_rd_rem_feats_cmd_cmp_evt
{
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///Le Features
    struct le_features  le_feats;
}__attribute__((packed));

struct hci_le_ltk_request_evt
{
    ///Connection handle
    uint16_t            conhdl;
    ///Random number
    struct rand_nb      rand;
    ///Encryption diversifier
    uint16_t            ediv;
}__attribute__((packed));

struct hci_le_data_len_chg_evt
{
    ///Connection handle
    uint16_t            conhdl;
    ///The maximum number of payload octets in TX
    uint16_t            max_tx_octets;
    ///The maximum time that the local Controller will take to TX
    uint16_t            max_tx_time;
    ///The maximum number of payload octets in RX
    uint16_t            max_rx_octets;
    ///The maximum time that the local Controller will take to RX
    uint16_t            max_rx_time;
}__attribute__((packed));

struct hci_le_rd_local_p256_public_key_cmp_evt
{
    ///Status of received command
    uint8_t             status;
    /// The 32 byte Diffie Helman Key
    uint8_t             public_key[64];
}__attribute__((packed));

struct hci_le_gen_dhkey_cmp_evt
{
    uint8_t      status;
    uint8_t      dh_key[32];
}__attribute__((packed));

struct hci_rd_local_ver_info_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t     status;
    ///HCI version number
    uint8_t     hci_ver;
    ///HCI revision number
    uint16_t    hci_rev;
    ///LMP version
    uint8_t     lmp_ver;
    ///manufacturer name
    uint16_t    manuf_name;
    ///LMP Subversion
    uint16_t    lmp_subver;
}__attribute__((packed));

struct hci_rd_bd_addr_cmd_cmp_evt
{
    /// Status of the command reception
    uint8_t             status;
    ///BD address
    struct bd_addr      local_addr;
}__attribute__((packed));

struct hci_rd_rssi_cmd_cmp_evt
{
    ///Status for command reception
    uint8_t status;
    ///Connection handle
    uint16_t conhdl;
    ///RSSI value
    uint8_t rssi;
}__attribute__((packed));

struct hci_le_phy_upd_cmp_evt
{
    ///Status of received command
    uint8_t             status;
    ///Connection handle
    uint16_t            conhdl;
    ///TX phy chosen
    uint8_t             tx_phy;
    ///RX phy chosen
    uint8_t             rx_phy;
}__attribute__((packed));

struct hci_le_ext_adv_report_evt
{
    ///Number of advertising reports in this event
    uint8_t             nb_reports;
    ///Event type
    uint16_t       evt_type;
    ///Advertising address type: public/random
    uint8_t        adv_addr_type;
    ///Advertising address value
    struct bd_addr adv_addr;
    ///Primary PHY
    uint8_t        phy;
    ///Secondary PHY
    uint8_t        phy2;
    ///Advertising SID
    uint8_t        adv_sid;
    ///Tx Power
    uint8_t        tx_power;
    ///RSSI value for advertising packet (in dBm, between -127 and +20 dBm)
    int8_t         rssi;
    ///Periodic Advertising interval (Time=N*1.25ms)
    uint16_t       interval;
    ///Direct address type
    uint8_t        dir_addr_type;
    ///Direct address value
    struct bd_addr dir_addr;
    ///Data length in advertising packet
    uint8_t        data_len;
    ///Data of advertising packet
    uint8_t        data[];
}__attribute__((packed));

struct hci_le_adv_report_evt
{
    uint8_t num_reports;
    ///Event type:
    /// - ADV_CONN_UNDIR: Connectable Undirected advertising
    /// - ADV_CONN_DIR: Connectable directed advertising
    /// - ADV_DISC_UNDIR: Discoverable undirected advertising
    /// - ADV_NONCONN_UNDIR: Non-connectable undirected advertising
    uint8_t        evt_type;
    ///Advertising address type: public/random
    uint8_t        adv_addr_type;
    ///Advertising address value
    struct bd_addr adv_addr;
    ///Data length in advertising packet
    uint8_t        data_len;
    ///Data of advertising packet
    uint8_t        data_rssi[];
}__attribute__((packed));

struct hci_le_per_adv_sync_est_evt
{
    /// Status of the advertising sync
    uint8_t             status;
    /// Sync Handle to be used
    uint16_t            sync_handle;
    /// Advertising SID
    uint8_t             adv_sid;
    ///Advertising address type: public/random
    uint8_t             adv_addr_type;
    ///Advertising address value
    struct bd_addr      adv_addr;
    /// Advertiser PHY (@enum le_phy_value)
    uint8_t             phy;
    /// Advertising interval (Time=N*1.25ms)
    uint16_t            interval;
    /// Advertiser clock accuracy (@see enum SCA)
    uint8_t             adv_ca;
}__attribute__((packed));

struct hci_le_per_adv_report_evt
{
    /// Sync Handle to be used
    uint16_t            sync_handle;
    /// Tx Power
    uint8_t             tx_power;
    /// RSSI
    uint8_t             rssi;
    /// CTE type
    uint8_t             cte_type;
    /// Data Status
    uint8_t             status;
    ///Data length in advertising packet
    uint8_t             data_len;
    ///Data of advertising packet
    uint8_t             data[];
}__attribute__((packed));

struct hci_le_per_adv_sync_lost_evt
{
    /// Sync Handle to be used
    uint16_t            sync_handle;
}__attribute__((packed));

struct hci_le_adv_set_term_evt
{
    /// Status
    uint8_t  status;
    /// Advertising handle
    uint8_t  adv_hdl;
    /// Connection handle
    uint16_t conhdl;
    /// Num_Completed_Extended_Advertising_Events
    uint8_t  nb_cmp_ext_adv_evt;
}__attribute__((packed));

struct hci_le_scan_req_rcvd_evt
{
    /// Advertising handle
    uint8_t  adv_hdl;
    /// Scanner address type:  public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
    uint8_t scan_addr_type;
    /// Scanner address
    struct bd_addr scan_addr;
}__attribute__((packed));

struct hci_le_ch_sel_algo_evt
{
    /// Connection handle
    uint16_t  conhdl;
    /// Channel selection algorithm
    uint8_t ch_sel_algo;
}__attribute__((packed));

#endif
