#ifndef LS_BLE_H_
#define LS_BLE_H_
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/** \addtogroup BLE
 *  @{
 */

#define INVALID_CON_IDX (0xff)          /*!< Invalid connection index*/
#define INVALID_PEER_ID (0xff)          /*!< Invalid Peer ID*/

#define BLE_ADDR_LEN 6                  /*!< BLE mac address length*/
#define BLE_KEY_LEN 16                  /*!< The length of the paired temporary key*/

/**
  * @brief Own address type
  */
enum gap_own_addr_type
{
    PUBLIC_OR_RANDOM_STATIC_ADDR,       /*!< Public or random static address*/
    RESOLVABLE_PRIVATE_ADDR,            /*!< Resolvable private address*/
    NON_RESOLVABLE_PRIVATE_ADDR,        /*!< Non-resolvable private address*/
};
/**
  * @brief Peer address type
  */
enum gap_peer_addr_type
{
    PUBLIC_ADDR,                        /*!< Public address*/
    RANDOM_ADDR,                        /*!< Random address*/
};
/**
  * @brief Adv type definition
  */
enum gap_adv_type
{
    GAP_ADV_TYPE_FLAGS                      = 0x01,        /*!< Flag*/
    GAP_ADV_TYPE_MORE_16_BIT_UUID           = 0x02,        /*!< Use of more than 16 bits UUID*/
    GAP_ADV_TYPE_COMPLETE_LIST_16_BIT_UUID  = 0x03,        /*!< Complete list of 16 bit UUID*/
    GAP_ADV_TYPE_MORE_32_BIT_UUID           = 0x04,        /*!< Use of more than 32 bit UUD*/
    GAP_ADV_TYPE_COMPLETE_LIST_32_BIT_UUID  = 0x05,        /*!< Complete list of 32 bit UUID*/
    GAP_ADV_TYPE_MORE_128_BIT_UUID          = 0x06,        /*!< Use of more than 128 bit UUID*/
    GAP_ADV_TYPE_COMPLETE_LIST_128_BIT_UUID = 0x07,        /*!< Complete list of 128 bit UUID*/
    GAP_ADV_TYPE_SHORTENED_NAME             = 0x08,        /*!< Shortened device name*/
    GAP_ADV_TYPE_COMPLETE_NAME              = 0x09,        /*!< Complete device name*/
    GAP_ADV_TYPE_TRANSMIT_POWER             = 0x0A,        /*!< Transmit power*/
    GAP_ADV_TYPE_CLASS_OF_DEVICE            = 0x0D,        /*!< Class of device*/
    GAP_ADV_TYPE_SP_HASH_C                  = 0x0E,        /*!< Simple Pairing Hash C*/
    GAP_ADV_TYPE_SP_RANDOMIZER_R            = 0x0F,        /*!< Simple Pairing Randomizer*/
    GAP_ADV_TYPE_TK_VALUE                   = 0x10,        /*!< Temporary key value*/
    GAP_ADV_TYPE_OOB_FLAGS                  = 0x11,        /*!< Out of Band Flag*/
    GAP_ADV_TYPE_SLAVE_CONN_INT_RANGE       = 0x12,        /*!< Slave connection interval range*/
    GAP_ADV_TYPE_RQRD_16_BIT_SVC_UUID       = 0x14,        /*!< Require 16 bit service UUID*/
    GAP_ADV_TYPE_RQRD_32_BIT_SVC_UUID       = 0x1F,        /*!< Require 32 bit service UUID*/
    GAP_ADV_TYPE_RQRD_128_BIT_SVC_UUID      = 0x15,        /*!< Require 128 bit service UUID*/
    GAP_ADV_TYPE_SERVICE_16_BIT_DATA        = 0x16,        /*!< Service data 16-bit UUID*/
    GAP_ADV_TYPE_SERVICE_32_BIT_DATA        = 0x20,        /*!< Service data 32-bit UUID*/
    GAP_ADV_TYPE_SERVICE_128_BIT_DATA       = 0x21,        /*!< Service data 128-bit UUID*/
    GAP_ADV_TYPE_PUB_TGT_ADDR               = 0x17,        /*!< Public Target Address*/
    GAP_ADV_TYPE_RAND_TGT_ADDR              = 0x18,        /*!< Random Target Address*/
    GAP_ADV_TYPE_APPEARANCE                 = 0x19,        /*!< Appearance*/
    GAP_ADV_TYPE_ADV_INTV                   = 0x1A,        /*!< Advertising Interval*/
    GAP_ADV_TYPE_LE_BT_ADDR                 = 0x1B,        /*!< LE Bluetooth Device Address*/
    GAP_ADV_TYPE_LE_ROLE                    = 0x1C,        /*!< LE Role*/ 
    GAP_ADV_TYPE_SPAIR_HASH                 = 0x1D,        /*!< Simple Pairing Hash C-256*/
    GAP_ADV_TYPE_SPAIR_RAND                 = 0x1E,        /*!< Simple Pairing Randomizer R-256*/
    GAP_ADV_TYPE_3D_INFO                    = 0x3D,        /*!< 3D Information Data*/
        
    GAP_ADV_TYPE_MANU_SPECIFIC_DATA         = 0xFF,        /*!< Manufacturer specific data*/
};
/**
  * @brief Device address
  */
struct dev_addr
{
    uint8_t addr[BLE_ADDR_LEN];                    /*!< Address array*/
};
/**
  * @brief BLE address structure
  */
struct ble_addr
{
    struct dev_addr addr;                          /*!< Address value in form of ::dev_addr*/ 
    uint8_t type;                                  /*!< Address type*/ 
};
/**
  * @brief Type of security level.
  */
enum sec_lvl_type
{
    NO_SEC,                                        /*!< No security*/ 
    UNAUTH_SEC,                                    /*!< Unauthenticated security*/ 
    AUTH_SEC,                                      /*!< Authenticated security*/ 
    SEC_CON_SEC,                                   /*!< Security connection*/ 
};
/**
  * @brief Legacy adv properities.
  */
struct adv_prop
{
    uint16_t connectable:1,                        /*!< Connectable property*/ 
            scannable:1,                           /*!< Scannable property*/ 
            directed:1,                            /*!< Directed property*/ 
            high_duty_cycle:1,                     /*!< High duty cycle property*/ 
            reserved:1,                            /*!< Reserved*/
            anonymous:1,                           /*!< Anonymous property*/
            tx_power:1,                            /*!< TX power property*/
            periodic_tx_power:1,                   /*!< Periodic TX power property*/
            scan_req_ntf:1;                        /*!< Scan request indicate property*/
};
/**
  * @brief ADV discovery mode.
  */
enum adv_disc_mode
{
    ADV_MODE_NON_DISC = 0,                         /*!< Mode in non-discoverable*/ 
    ADV_MODE_GEN_DISC,                             /*!< Mode in general discoverable*/ 
    ADV_MODE_LIM_DISC,                             /*!< Mode in limited discoverable*/ 
    ADV_MODE_BEACON,                               /*!< Broadcast mode without presence of AD_TYPE_FLAG in advertising data*/ 
    ADV_MODE_MAX,
};
/**
  * @brief Legacy adv object parameters structure.
  */
struct legacy_adv_obj_param                        
{
    struct dev_addr *peer_addr;                    /*!< Peer address. Only valid for directed adv*/ 
    struct adv_prop prop;                          /*!< adv properities*/
    uint16_t adv_intv_min;                         /*!< Minimum adv interval, in units of 625us*/ 
    uint16_t adv_intv_max;                         /*!< Maximum adv interval, in units of 625us*/ 
    enum gap_own_addr_type own_addr_type;          /*!< Own address type*/ 
    enum gap_peer_addr_type peer_addr_type;        /*!< Peer address type*/ 
    uint8_t filter_policy;                         /*!< Adv filter policy*/ 
    uint8_t ch_map;                                /*!< Adv channel map. bit0: channel 37 enabled. bit1: channel 38 enabled. bit2: channel 39 enabled. */ 
    enum adv_disc_mode disc_mode;                  /*!< Adv discovery mode*/
};
/**
  * @brief PHY type.
  */
enum phy_type
{
    PHY_TYPE_1M = 1,                               /*!< LE 1Mbps phy*/ 
    PHY_TYPE_2M,                                   /*!< LE 2Mbps phy*/ 
    PHY_TYPE_CODED,                                /*!< LE Coded phy*/ 
};
/**
  * @brief PHY option.
  */
enum phy_option
{
    PHY_OPT_LE_CODED_ALL_RATES     = (1 << 0),   	/*!< No preference for rate used when transmitting on the LE Coded PHY*/
    PHY_OPT_LE_CODED_500K_RATE     = (1 << 1),    	/*!< 500kbps rate preferred when transmitting on the LE Coded PHY*/
    PHY_OPT_LE_CODED_125K_RATE     = (1 << 2),		/*!< 125kbps  when transmitting on the LE Coded PHY*/
};  
/**
  * @brief Extended adv object parameters structure.
  */
struct ext_adv_obj_param
{
    struct legacy_adv_obj_param legacy_adv_obj;    /*!< Shared legacy adv parameters*/ 
    uint8_t max_skip;                              /*!< Maximum number of advertising events the controller can skip before sending the
                                                        AUX_ADV_IND packets. 0 means that AUX_ADV_IND PDUs shall be sent prior each
                                                        advertising events*/
    uint8_t phy;                                   /*!< Indicate on which PHY secondary advertising has to be performed. Refer to ::phy_type*/ 
    uint8_t adv_sid;                               /*!< Adv set ID*/ 
};
/**
  * @brief Scanning type.
  */
enum scan_type
{
    GENERAL_DISCOVERABLE,                          /*!< General discovery*/ 
    LIMITED_DISCOVERABLE,                          /*!< Limited discovery*/               
    OBSERVER,                                      /*!< Observer*/ 
    OBSERVER_WHITELIST,                            /*!< Selective observer*/ 
    CONNECTABLE,                                   /*!< Connectable discovery*/ 
    CONNECTABLE_WHITELIST,                         /*!< Selective connectable discovery*/ 
};
/**
  * @brief Scan filter duplicates policy.
  */
enum filter_dup_policy
{
    DUP_FILT_DIS = 0,                              /*!< Disable filtering of duplicated packets*/ 
    DUP_FILT_EN,                                   /*!< Enable filtering of duplicated packets*/ 
    DUP_FILT_EN_PERIOD,                            /*!< Enable filtering of duplicated packets, reset for each scan period*/ 
};
/**
  * @brief Scanning parameters.
  */
struct start_scan_param
{
    uint16_t scan_intv;                            /*!< Scan intervals in units of 625us*/ 
    uint16_t scan_window;                          /*!< Scan window in units of 625us*/ 
    uint16_t duration;                             /*!< Scan duration in units of 10ms. 0 means the scan action will run continuously until app stop it*/ 
    uint16_t period;                               /*!< Scan window in units of 625us*/ 
    enum scan_type type;                           /*!< Scan type*/ 
    uint8_t active:1,                              /*!< Active scan*/ 
            filter_duplicates:2;                   /*!< Duplicate packet filtering policy. Refer to ::filter_dup_policy*/ 
};
/**
  * @brief Initiating type.
  */
enum init_type
{
    DIRECT_CONNECTION,                              /*!< Direct connection establishment, establish a connection with an indicated device*/ 
    AUTO_CONNECTION_WHITELIST,                      /*!< Automatic connection establishment, establish a connection with all devices whose address is present in the white list*/ 
};
/**
  * @brief Start initiating parameters.
  */
struct start_init_param
{
    struct dev_addr *peer_addr;                     /*!< Peer device address*/ 
    uint16_t scan_intv;                             /*!< Scan intervals in units of 625us*/ 
    uint16_t scan_window;                           /*!< Scan window in units of 625us*/ 
    uint16_t conn_to;                               /*!< Timeout for automatic connection establishment (in unit of 10ms). Cancel the procedure if not all indicated devices have been connected when the timeout occurs. 0 means there is no timeout*/ 
    uint16_t conn_intv_min;                         /*!< Minimum value for the connection interval (in unit of 1.25ms). Shall be less than or equal to conn_intv_max value. Allowed range is 7.5ms to 4s*/ 
    uint16_t conn_intv_max;                         /*!< Maximum value for the connection interval (in unit of 1.25ms). Shall be greater than or equal to conn_intv_min value. Allowed range is 7.5ms to 4s*/ 
    uint16_t conn_latency;                          /*!< Slave latency. Number of events that can be missed by a connected slave device*/ 
    uint16_t supervision_to;                        /*!< Link supervision timeout (in unit of 10ms). Allowed range is 100ms to 32s*/ 
    uint8_t peer_addr_type;                         /*!< Address type for peer device. 0=public/1=private random*/
    enum init_type type;                            /*!< Initiating type*/ 
};

/**
  * @brief Type of events in device manager.
  */
enum dev_evt_type
{
    STACK_INIT,                                     /*!< Stack initialized event*/ 
    STACK_READY,                                    /*!< Stack ready event*/ 
    PROFILE_ADDED,                                  /*!< Profile added event*/ 
    SERVICE_ADDED,                                  /*!< Service added event*/ 
    ADV_OBJ_CREATED,                                /*!< Adv object created event*/ 
    SCAN_OBJ_CREATED,                               /*!< Scan object created event*/ 
    INIT_OBJ_CREATED,                               /*!< Initiate object created event*/ 
    ADV_STARTED,                                    /*!< Adv started event*/ 
    ADV_STOPPED,                                    /*!< Adv stopped event*/
    ADV_UPDATED,                                    /*!< Adv data updated event*/
    SCAN_STARTED,                                   /*!< Scan started event*/ 
    SCAN_STOPPED,                                   /*!< Scan stopped event*/ 
    INIT_STARTED,                                   /*!< Initiate started event*/ 
    INIT_STOPPED,                                   /*!< Initiate stopped event*/ 
    OBJ_DELETED,                                    /*!< Object deleted event*/ 
    ADV_REPORT,                                     /*!< Receive adv report event*/ 
    SCAN_REQ_IND,                                   /*!< Indicate reception of scan request event*/ 
};
/**
  * @brief Profile IDs.
  */
enum prf_id
{
    PRF_DIS_SERVER,                                 /*!< Device information service profile*/ 
    PRF_MESH,                                       /*!< */ 
    PRF_LS_MESH,                                    /*!< */ 
    PRF_FOTA_SERVER,                                /*!< FOTA server service*/ 
    PRF_HID,                                        /*!< HID profile*/ 
    PRF_BASS,                                       /*!< Battery service profile*/ 
    PRF_ANCS,                                       /*!< Apple Notification Center Service*/
};
/**
  * @brief Profile added event.
  */
struct profile_added_evt
{
    uint16_t start_hdl;                             /*!< Start handle of the profile*/ 
    enum prf_id id;                                 /*!< Profile ID*/ 
};
/**
  * @brief Service added event.
  */
struct service_added_evt
{
    uint16_t start_hdl;                             /*!< Start handle of the Service*/ 
    uint8_t status;                                 /*!< Status of the service add action*/ 
};
/**
  * @brief Object created event.
  */
struct obj_created_evt
{
    uint8_t handle;                                 /*!< Handle of the created object*/ 
    uint8_t status;                                 /*!< Status of object create action*/ 
};
/**
  * @brief Object started event.
  */
struct started_evt
{
    uint8_t handle;                                 /*!< Handle of the started event*/ 
};
/**
  * @brief ADV updated event.
  */
struct adv_updated_evt
{
    uint8_t handle;                                 /*!< Handle of the updated adv event*/ 
};
/**
  * @brief Object stopped event.
  */
struct stopped_evt
{
    uint8_t handle;                                 /*!< Handle of the stopped event*/ 
    uint8_t reason;                                 /*!< Reason for stopped event*/ 
};
/**
  * @brief Object deleted event.
  */
struct obj_deleted_evt
{
    uint8_t handle;                                 /*!< Handle of the deleted object*/ 
    uint8_t status;                                 /*!< Status of object delete action*/
};
/**
  * @brief Advertising report type.
  */
enum adv_report_type
{
    REPORT_TYPE_ADV_EXT = 0,                        /*!< Extended advertising report*/ 
    REPORT_TYPE_ADV_LEG,                            /*!< Legacy advertising report*/ 
    REPORT_TYPE_SCAN_RSP_EXT,                       /*!< Extended scan response report*/ 
    REPORT_TYPE_SCAN_RSP_LEG,                       /*!< Legacy scan response report*/ 
    REPORT_TYPE_PER_ADV,                            /*!< Periodic advertising report*/ 
};
/**
  * @brief Adv report information.
  */
struct adv_report_info
{
    uint8_t evt_type:3,                             /*!< Adv report type. Refer to ::adv_report_type*/ 
            complete:1,                             /*!< Report is complete*/ 
            connectable:1,                          /*!< Connectable advertising*/ 
            scannable:1,                            /*!< Scannable advertising*/ 
            directed:1;                             /*!< Directed advertising*/ 
};
/**
  * @brief Adv report event.
  */
struct adv_report_evt
{
    uint8_t *data;                                  /*!< Adv data*/ 
    struct dev_addr *adv_addr;                      /*!< Address of the device send the adv*/ 
    uint16_t length;                                /*!< Adv report length*/ 
    uint8_t adv_addr_type;                          /*!< Adv address type*/ 
    int8_t rssi;                                    /*!< RSSI*/ 
    struct adv_report_info info;                    /*!< Adv report information*/ 
};
/**
  * @brief Scan request indicate event.
  */
struct scan_req_ind_evt
{
    uint8_t obj_hdl;                                /*!<Handle of the adv activity*/
    uint8_t adv_addr_type;                          /*!< Transmitter device address type*/ 
    struct dev_addr *adv_addr;                      /*!<Transmitter device address*/
};
/**
  * @brief Device event union.
  */
union dev_evt_u
{
    struct profile_added_evt profile_added;         /*!< Profile added event*/ 
    struct service_added_evt service_added;         /*!< Service added event*/ 
    struct obj_created_evt obj_created;             /*!< Object created event*/ 
    struct started_evt started;                     /*!< Started event*/ 
    struct adv_updated_evt adv_updated;             /*!< Adv updated event*/ 
    struct stopped_evt stopped;                     /*!< Stopped event*/ 
    struct obj_deleted_evt deleted;                 /*!< Object deleted event*/ 
    struct adv_report_evt adv_report;               /*!< Adv report event*/ 
    struct scan_req_ind_evt scan_req_ind;           /*!< Scan request indicate event*/ 
};
/**
  * @brief BLE Stack configuration.
  */
struct ble_stack_cfg
{
    bool private_addr;                              /*!< Identity address type. 0: Public 1: Random*/ 
    bool controller_privacy;                        /*!< Indicate if controller privacy is enabled*/ 
};
/**
  * @brief Length of UUID
  */
enum uuid_length
{
    UUID_LEN_16BIT = 0,                             /*!< 16bits UUID*/
    UUID_LEN_32BIT,                                 /*!< 32bits UUID*/
    UUID_LEN_128BIT,                                /*!< 128bits UUID*/
};
/**
  * @brief Characteristics properities.
  */
struct char_properties
{
    uint8_t broadcast:1,                            /*!< Broadcast of characteristic value in Server Characteristic Configuration Descriptor enable*/
            rd_en:1,                                /*!< Read request enable*/
            wr_cmd:1,                               /*!< Write command enable*/
            wr_req:1,                               /*!< Write request enable*/
            ntf_en:1,                               /*!< Notification enable*/
            ind_en:1,                               /*!< Indication enable*/
            wr_signed:1,                            /*!< Write signed enable*/
            ext_prop:1;                             /*!< Extended properities enable*/
};
/**
  * @brief Service and attribute permissions definition.
  */
enum svc_att_perm
{
    PERM_NO_AUTH = 0,                           /*!< NON Authenticated*/
    PERM_UNAUTH,                                /*!< Unauthenticated*/
    PERM_AUTH,                                  /*!< Authenticated*/
    PERM_SEC_CON,                               /*!< Security connection*/
};
/**
  * @brief Characteristics permissions
  */
struct char_permissions
{
    uint8_t rd_perm:2,                              /*!< Read permission. Refer to ::svc_att_perm*/
            wr_perm:2,                              /*!< Write permission. Refer to ::svc_att_perm*/
            ind_perm:2,                             /*!< Indication permission. Refer to ::svc_att_perm*/
            ntf_perm:2;                             /*!< Notification permission. Refer to ::svc_att_perm*/
};
/**
  * @brief Attribute declaration.
  */
struct att_decl
{
    const uint8_t *uuid;                            /*!< UUID of the attribute*/
    struct{
        uint16_t max_len:12,                        /*!< Maximum length supported by the attribute in units of byte*/
                eks:1,                              /*!< 1 means Encryption key Size must be 16 bytes*/
                uuid_len:2,                         /*!< Length of UUID. Refer to ::uuid_length*/
                read_indication:1;                  /*!< Trigger Read Indication. 0 means data in database, 1 means read request will be forwarded to application*/
    }s;
    struct char_permissions char_perm;              /*!< Characteristic permission*/
    struct char_properties char_prop;               /*!< Characteristic properties*/
};
/**
  * @brief Service declaration.
  */
struct svc_decl
{
    const uint8_t *uuid;                            /*!< UUID of the service*/
    struct att_decl *att;                           /*!< Attributes contained in the services*/
    uint8_t nb_att;                                 /*!< Number of attributes contained in the services*/
    uint8_t    sec_lvl:2,                           /*!< Security level. Refer to ::svc_att_perm*/
            uuid_len:2,                             /*!< Length of UUID. Refer to ::uuid_length*/
            secondary:1;                            /*!< 0 = Primary Service, 1 = Secondary Service*/
};
/**
  * @brief GAP event types enumeration.
  */
enum gap_evt_type
{
    CONNECTED,                                      /*!< Connected event*/
    DISCONNECTED,                                   /*!< Disconnected event*/
    CONN_PARAM_REQ,                                 /*!< Connection parameter request event*/
    CONN_PARAM_UPDATED,                             /*!< Connection parameter updated event*/
    MASTER_PAIR_REQ,                                /*!< Master pair request event*/
    SLAVE_SECURITY_REQ,                             /*!< Slave security request event*/
    PAIR_DONE,                                      /*!< Pair done event*/
    ENCRYPT_FAIL,                                   /*!< Encryption fail event*/
    ENCRYPT_DONE,                                   /*!< Encryption done event*/
    DISPLAY_PASSKEY,                                /*!< Display passkey event*/
    REQUEST_PASSKEY,                                /*!< Request passkey event*/
    NUMERIC_COMPARE,                                /*!< Numeric compare event*/
    REQUEST_LEGACY_OOB,                             /*!< Request legacy OOB event*/
    REQUEST_SC_OOB,                                 /*!< Request security connection OOB event*/
    GET_DEV_INFO_DEV_NAME,                          /*!< Get device name of device information*/
    GET_DEV_INFO_APPEARANCE,                        /*!< Get appearance Icon of device information*/
    GET_DEV_INFO_SLV_PRE_PARAM,                     /*!< Get slave preferred parameters of device information*/
    GET_DEV_INFO_PEER_RSSI,                         /*!< Get connection RSSI indication*/
    PHY_UPDATED,										                /*!< PHY updated event*/
};
/**
  * @brief BLE roles enumeration.
  */
enum LS_BLE_ROLE
{
    LS_BLE_ROLE_MASTER,                             /*!< Role of master*/
    LS_BLE_ROLE_SLAVE,                              /*!< Role of slave*/
};
/**
  * @brief Connection parameters structure.
  */
struct gap_conn_param
{
    uint16_t intv_min;                              /*!< Connection interval minimum*/
    uint16_t intv_max;                              /*!< Connection interval maximum*/
    uint16_t latency;                               /*!< Latency*/
    uint16_t time_out;                              /*!< Supervision timeout*/
};
/**
  * @brief Connection parameters request.
  */
struct gap_conn_param_req
{
    struct gap_conn_param const *conn_param;        /*!< Connection parameters received*/
    bool *accept;                                   /*!< True = accept, False = reject*/
};
/**
  * @brief Connection parameters updated indication.
  */
struct gap_conn_param_updated
{
    uint16_t            con_interval;               /*!< Connection interval value*/
    uint16_t            con_latency;                /*!< Connection latency value*/
    uint16_t            sup_to;                     /*!< Supervision timeout*/
};
/**
  * @brief SEC OOB value.
  */
struct gap_sc_oob
{
    uint8_t conf[BLE_KEY_LEN];              /*!< Confirm Value*/
    uint8_t rand[BLE_KEY_LEN];              /*!< Random Number*/
};

/**
  * @brief Defgroup BLE_GAP_IO_CAPS GAP IO Capabilities.
  */
enum gap_io_caps
{
    BLE_GAP_IO_CAPS_DISPLAY_ONLY,           /*!< Display Only*/
    BLE_GAP_IO_CAPS_DISPLAY_YESNO,          /*!< Display and Yes/No entry*/
    BLE_GAP_IO_CAPS_KEYBOARD_ONLY,          /*!< Keyboard Only*/
    BLE_GAP_IO_CAPS_NONE,                   /*!< No I/O capabilities*/
    BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY,       /*!< Keyboard and Display*/
};
/**
  * @brief Defgroup SEC_OOB_FLAG  OOB Data Flag.
  */
enum gap_pair_oob
{
    BLE_GAP_OOB_DISABLE,                    /*!< OOB Authentication data not present*/
    BLE_GAP_OOB_ENABLE,                     /*!< OOB Authentication data from remote device present*/
};
/**
  * @brief Defgroup SEC_AUTH_FLAG  SEC Auth Flag.
  */
enum gap_pair_auth
{
    AUTH_NONE              =  0,           /*!< No auth requirement*/
    AUTH_BOND              = (1 << 0),     /*!< Bond flag*/
    AUTH_MITM              = (1 << 2),     /*!< MITM flag*/
    AUTH_SEC_CON           = (1 << 3),     /*!< Security connection flag*/
    AUTH_KEY_PRESS_NOTIFY  = (1 << 4),     /*!< Key press notify flag*/
};
/**
  * @brief Defgroup SEC_KEY_DIST_FLAG  SEC Key Distribution Flag.
  */
enum gap_key_dist
{
    KDIST_NONE             =  0,           /*!< No key needs to be distributed*/
    KDIST_ENCKEY           = (1 << 0),     /*!< Distribute encryption and master identification info*/
    KDIST_IDKEY            = (1 << 1),     /*!< Distribute identity and address info*/
    KDIST_SIGNKEY          = (1 << 2),     /*!< Distribute signing info*/
};
/**
  * @brief Set security parameter.
  */
struct pair_feature
{
    uint8_t iocap;                          /*!< Set the IO capability, This parameter can be a value of @ref gap_io_caps*/
    uint8_t oob;                            /*!< Indicate whether OOB is supported, This parameter can be a value of @ref gap_pair_oob*/
    uint8_t auth;                           /*!< Set the auth, This parameter can be a value of @ref gap_pair_auth*/
    uint8_t key_size;                       /*!< Indicate the supported maximum LTK size (range: 7-16), This parameter can be a value of @ref gap_io_caps*/
    uint8_t ikey_dist;                      /*!< Set the initial key distribution, This parameter can be a value of @ref gap_key_dist*/
    uint8_t rkey_dist;                      /*!< Set the response key distribution, This parameter can be a value of @ref gap_key_dist*/
};
/**
  * @brief Connected indication event structure.
  */
struct gap_connected
{
    uint16_t con_interval;                  /*!< Connection interval*/
    uint16_t con_latency;                   /*!< Latency*/
    uint16_t sup_to;                        /*!< Supervision timeout*/
    uint8_t peer_id;                        /*!< Peer ID*/
};
/**
  * @brief Disconnected indication event structure.
  */
struct gap_disconnected
{
    uint8_t reason;                         /*!< Reason for disconnection*/
};

/**
  * @brief Disconnected indication event structure.
  */
struct gap_phy_updated
{
    uint8_t tx_phy;                         /// LE PHY for data transmission (@see enum phy_type)
    uint8_t rx_phy;                         /// LE PHY for data reception (@see enum phy_type)
};

/**
  * @brief Set master security parameter.
  */
struct gap_master_pair_req
{
    uint8_t auth;                           /*!< Set the auth, This parameter can be a value of @ref gap_pair_auth*/
};
/**
  * @brief Set slave security parameter.
  */
struct gap_slave_security_req
{
    uint8_t auth;                           /*!< Set the auth, This parameter can be a value of @ref gap_pair_auth*/
};
/**
  * @brief Parameter of pairing completion.
  */
struct gap_pair_done
{
    bool succeed;                          /*!< The value indicates a successful pairing,Successful pairing is "true" and unsuccessful pairing is "false"*/
    union{
        uint8_t auth;                      /*!< Pairing level achieved, This parameter can be a value of @ref gap_pair_auth*/
        uint8_t fail_reason;               /*!< The reasons for the failure of the pairing*/
    }u;
};
/**
  * @brief Failed to encrypt the parameter.
  */
struct gap_encrypt_fail
{
    uint8_t reason;                        /*!< The reason for encryption failure*/
};
/**
  * @brief Encryption completed security parameters.
  */
struct gap_encrypt_done
{
    uint8_t auth;                          /*!< Pairing level achieved, This parameter can be a value of @ref gap_pair_auth*/
};
/**
  * @brief Passkey structure.
  */
struct gap_pin_str
{
    char pin[6];                           /*!< 6 decimal numbers as passkey*/
    char str_pad;                          /*!< The byte behind pin used to store '\0'*/
};
/**
  * @brief SEC passkey entry value.
  */
struct gap_display_passkey
{
    struct gap_pin_str passkey;              /**< Passkey entry value (000000~999999),This parameter can be a value of @ref gap_pin_str */
};
/**
  * @brief SEC number comparison value.
  */
struct gap_numeric_compare
{
    struct gap_pin_str number;              /**< Number comparison value (000000~999999),This parameter can be a value of @ref gap_pin_str */
};

/**
  * @brief Secure Connection OOB Exchange Event structure
  */
struct gap_sc_oob_exchange
{
    struct gap_sc_oob *sc_oob;             /**< Pointer to SC OOB value @ref gap_sc_oob */
};

/**
  * @brief Get device name.
  */
struct gap_dev_info_dev_name
{
    uint16_t length;                                /*!< Length of device name*/
    uint8_t* value;                                 /*!< Pointer to device name*/
};
/**
  * @brief Get appearance.
  */
struct gap_dev_info_appearance
{
    uint16_t appearance;                            /*!< Device appearance icon*/
};
/**
  * @brief Get slave preferred parameters.
  */
struct gap_dev_info_slave_pref_param
{
    uint16_t con_intv_min;                          /*!< Minimum connection interval*/
    uint16_t con_intv_max;                          /*!< Maximum connection interval*/
    uint16_t slave_latency;                         /*!< Slave latency*/
    uint16_t conn_timeout;                          /*!< Supervision timeout*/
};
/**
  * @brief The RSSI value of the current connection.
  */
struct gap_dev_info_peer_rssi
{
    int8_t rssi;                            /**< The RSSI value of the current connection(master or slave) */
};
/**
  * @brief GAP event union definition.
  */
union gap_evt_u
{
    struct gap_connected connected;                            /*!< Connected event*/
    struct gap_disconnected disconnected;                      /*!< Disconnected event*/
    struct gap_conn_param_req conn_param_req;                  /*!< Connection parameter request event*/
    struct gap_conn_param_updated conn_param_updated;          /*!< Connection parameter updated event*/
    struct gap_master_pair_req master_pair_req;                /*!< Master pair request event*/
    struct gap_slave_security_req slave_security_req;          /*!< Slave security request event*/
    struct gap_pair_done pair_done;                            /*!< Pair done event*/
    struct gap_encrypt_fail encrypt_fail;                      /*!< Encryption fail event*/
    struct gap_encrypt_done encrypt_done;                      /*!< Encryption done event*/
    struct gap_display_passkey display_passkey;                /*!< Display passkey event*/
    struct gap_numeric_compare numeric_compare;                /*!< Numeric comparison event*/
    struct gap_sc_oob_exchange sc_oob_exchange;                /*!< Secure Connection OOB Exchange event*/
    struct gap_dev_info_dev_name get_dev_name;                 /*!< Get device name*/
    struct gap_dev_info_appearance get_appearance;             /*!< Get Get appearance*/
    struct gap_dev_info_slave_pref_param slv_pref_param;       /*!< Get slave preferred parameters*/
    struct gap_dev_info_peer_rssi peer_rssi;                   /*!< Get RSSI value of the current connection*/
    struct gap_phy_updated phy_updated;                        /*!< PHY updated event*/
};
/**
  * @brief Connection parameter update.
  */
struct gap_update_conn_param
{
    uint16_t intv_min;                                         /*!< Mininum connection interval*/
    uint16_t intv_max;                                         /*!< Maximum connection interval*/
    uint16_t latency;                                          /*!< Latency*/
    uint16_t sup_timeout;                                      /*!< Supervision timeout*/
    uint16_t ce_len_min;                                       /*!< Mininum connection event length*/
    uint16_t ce_len_max;                                       /*!< Maximum connection event length*/
};
/**
  * @brief Set packet size in air.
  */
struct gap_set_pkt_size
{
    uint16_t pkt_size;                                         /*!< Packet size in bytes*/
};

/**
  * @brief GATT event types.
  * @note  Event types include request/done/indication or other messages sent to applications 
  * by stack.
  */
enum gatt_evt_type
{
    SERVER_READ_REQ = 0,               /*!< Read request for server*/
    SERVER_WRITE_REQ,                  /*!< write request for server*/
    SERVER_NOTIFICATION_DONE,          /*!< Send notification done for server*/
    SERVER_INDICATION_DONE,            /*!< Send indication done for server*/

    CLIENT_RECV_NOTIFICATION,          /*!< Receive notification for client*/
    CLIENT_RECV_INDICATION,            /*!< Receive indication for client*/
    CLIENT_PRIMARY_SVC_DIS_IND,        /*!< Primary service discovery indication for client*/
    CLIENT_INCL_SVC_DIS_IND,           /*!< Included service discovery indication for client*/
    CLIENT_CHAR_DIS_BY_UUID_IND,       /*!< Characteristic discovery by UUID indication for client*/ 
    CLIENT_CHAR_DESC_DIS_BY_UUID_IND,  /*!< Characteristic descriptor discovery by UUID indication for client*/
    CLIENT_RD_CHAR_VAL_BY_UUID_IND,    /*!< Read characteristic value by UUID indication for client*/
    CLIENT_WRITE_WITH_RSP_DONE,        /*!<  Write response indication for client*/
    CLIENT_WRITE_NO_RSP_DONE,          /*!<  Write with no response indication for client*/
    CLIENT_DISC_OP_DONE,               /*!<  discovery operation done for client*/

    MTU_CHANGED_INDICATION,            /*!<  MTU exchange indication for client & server*/
    GATT_EVT_MAX
};
/**
  * @brief Service set values status.
  */
enum svc_set_value_status
{
    SVC_SET_VAL_NO_ERROR,              /*!< No error*/
    SVC_SET_VAL_NOT_SUPPORTED,         /*!< Action not supported*/
    SVC_SET_VAL_INVALID_HANDLE,        /*!< Invalid handle*/
    SVC_SET_VAL_INVALID_OFFSET,        /*!< Invalid offset*/
    SVC_SET_VAL_INVALID_LENGTH,        /*!< Invalid length*/
};
/**
  * @brief Service get values status.
  */
enum svc_get_value_status   
{
    SVC_GET_VAL_NO_ERROR,              /*!< No error*/
    SVC_GET_VAL_NOT_SUPPORTED,         /*!< Action not supported*/
    SVC_GET_VAL_INVALID_HANDLE,        /*!< Invalid handle*/
    SVC_GET_VAL_APP_ERROR,             /*!< Application or profile error*/
};
/**
  * @brief GATT service environment.
  */
struct gatt_svc_env
{
    void *hdr;                         /*!< Pointer to next gatt_svc_env*/
    uint16_t start_hdl;                /*!< Start handle of the service*/
    uint8_t att_num;                   /*!< Attributes number in the service*/
};
/**
  * @brief GATT read request.
  */
struct gatt_server_read_req
{
    struct gatt_svc_env const *svc;    /*!< Pointer to serice containing the attribute to read*/
    uint8_t att_idx;                   /*!< Attribute index*/
};

/**
  * @brief GATT write request.
  */
struct gatt_server_write_req
{
    struct gatt_svc_env const *svc;    /*!< Pointer to serice containing the attribute to read*/
    uint8_t const *value;              /*!< Pointer to value to write*/
    uint8_t *return_status;            /*!< Return status*/
    uint16_t offset;                   /*!< Offset at which the data has to be written*/
    uint16_t length;                   /*!< Length of data to write*/
    uint8_t att_idx;                   /*!< Attribute index*/
};
/**
  * @brief Send notify/indicate done on GATT server.
  */
struct gatt_server_notify_indicate_done
{
    uint16_t transaction_id;           /*!< Index of transaction*/
    uint8_t status;                    /*!< Status of notifiy/indicate done*/
};
/**
  * @brief Received notify/indicate on GATT client.
  */
struct gatt_client_recv_notify_indicate
{
    uint16_t handle;                   /*!< Handle of notification/indication*/
    uint16_t length;                   /*!< Length of notification/indication*/
    uint8_t const *value;              /*!< Pointer to value in notification/indication*/
};
/**
  * @brief MTU exchange indicate.
  */
struct gatt_mtu_changed_indicate
{
    uint16_t mtu;                      /*!< MTU received*/
};
/**
  * @brief Range of GATT handles.
  */
struct gatt_handle_range
{
    uint16_t begin_handle;             /*!< Start handle*/
    uint16_t end_handle;               /*!< End handle*/
};
/**
  * @brief Service discovery indicate for GATT client.
  */
struct gatt_client_svc_disc_indicate
{
    const uint8_t *uuid;                         /*!< UUID of the service*/
    struct gatt_handle_range handle_range;       /*!< Handle range of the service*/
    enum uuid_length uuid_len;                   /*!< Length of the service UUID*/
};
/**
  * @brief Included service discovery indicate for GATT client.
  */
struct gatt_client_svc_disc_include_indicate
{
    const uint8_t *uuid;                          /*!< UUID of the service*/
    struct gatt_handle_range handle_range;        /*!< Handle range of the service*/
    uint16_t attr_handle;                         /*!< Attribute handle of included service*/
    enum uuid_length uuid_len;                    /*!< Length of the service UUID*/
};
/**
  * @brief Characteristic discovery indicate for GATT client.
  */
struct gatt_client_disc_char_indicate
{
    const uint8_t *uuid;                          /*!< UUID of the characteristic*/
    uint16_t attr_handle;                         /*!< Attribute handle of characteristic*/
    uint16_t pointer_handle;                      /*!< Pointer attribute handle to UUID*/
    uint8_t properties;                           /*!< Properities of the characteristic*/
    enum uuid_length uuid_len;                    /*!< Length of the service UUID*/
};
/**
  * @brief Characteristic descriptro discovery indicate for GATT client.
  */
struct gatt_client_disc_char_desc_indicate
{
    const uint8_t *uuid;                          /*!< UUID of the descriptor*/
    uint16_t attr_handle;                         /*!< Attribute handle of descriptor*/
    enum uuid_length uuid_len;                    /*!< Length of the service UUID*/
};
/**
  * @brief Read indication.
  */
struct gatt_read_indicate
{
    uint8_t const *value;                         /*!< Pointer to the value read*/
    uint16_t handle;                              /*!< Attribute handle*/
    uint16_t offset;                              /*!< Offset at which the data has to be written*/
    uint16_t length;                              /*!< Length of value*/
};
/**
  * @brief Response for write request.
  */
struct gatt_write_rsp
{
    uint16_t transaction_id;                      /*!< Index of transaction*/
    uint8_t status;                               /*!< Status of write*/
};
/**
  * @brief Response for write command.
  */
struct gatt_write_no_rsp
{
    uint16_t transaction_id;                      /*!< Index of transaction*/
    uint8_t status;                               /*!< Status of write*/
};
/**
  * @brief Send discovery operation done on GATT server.
  */
struct gatt_client_discovery_operation_done
{
    uint16_t transaction_id;                      /*!< Index of transaction*/
    uint8_t status;                               /*!< Status of write*/
};

/**
  * @brief Union definition for GATT events.
  */
union gatt_evt_u
{
    struct gatt_server_read_req server_read_req;                                         /*!< GATT server read request.*/
    struct gatt_server_write_req server_write_req;                                       /*!< GATT server write request.*/
    struct gatt_server_notify_indicate_done server_notify_indicate_done;                 /*!< GATT server send notify/indicate done.*/           
    struct gatt_client_recv_notify_indicate client_recv_notify_indicate;                 /*!< GATT client receive notify/indicate.*/
    struct gatt_mtu_changed_indicate mtu_changed_ind;                                    /*!< MTU exchange indication.*/
    struct gatt_client_svc_disc_indicate client_svc_disc_indicate;                       /*!< GATT client service discovery indicate.*/
    struct gatt_client_svc_disc_include_indicate client_svc_disc_include_indicate;       /*!< GATT client included service discovery indicate.*/
    struct gatt_client_disc_char_indicate client_disc_char_indicate;                     /*!< GATT client characteristic discovery indicate.*/
    struct gatt_client_disc_char_desc_indicate client_disc_char_desc_indicate;           /*!< GATT client characteristic descriptor discovery indicate.*/
    struct gatt_read_indicate client_read_indicate;                                      /*!< GATT client read indicate.*/
    struct gatt_write_rsp client_write_rsp;                                              /*!< GATT client write request response.*/
    struct gatt_write_no_rsp client_write_no_rsp;                                        /*!< GATT client write command response.*/
    struct gatt_client_discovery_operation_done  client_discovery_operation_done;        /*!< GATT client discovery operation done.*/
};

/**
 ****************************************************************************************
 * \brief Packing function for advertising data and scan response.
 * Arguments passed to the function must follow the sequence of adv_type/data_buf/length.
 * \param[in]  buf                Buffer contains packed data.
 * \param[in]  field_nums         Number of adv data or scan response types.
 * \return                        Packed data length in bytes.
 ****************************************************************************************
 */
uint8_t *adv_data_pack(uint8_t *buf,uint8_t field_nums,...);
#define ADV_DATA_PACK(buf,field_nums,...) (adv_data_pack((buf),(field_nums),__VA_ARGS__) - (buf))

/**
 ****************************************************************************************
 * \brief Function for BLE initialization.
 * 
 ****************************************************************************************
 */
void ble_init(void);
/**
 ****************************************************************************************
 * \brief Function for BLE event handling with an internal infinite loop.
 * Any function behind ble_loop will never be executed.
 * 
 ****************************************************************************************
 */
void ble_loop(void);
/**
 ****************************************************************************************
 * \brief Initialization of dev_manager.
 * 
 * \param[in]  cb                Callback function to handle all the dev_manager messages.
 ****************************************************************************************
 */
void dev_manager_init(void (*cb)(enum dev_evt_type,union dev_evt_u *));
/**
 ****************************************************************************************
 * \brief Re-register callback of dev_manager.
 * 
 * \param[in]  cb                Callback function to handle all the dev_manager messages.
 ****************************************************************************************
 */
void dev_manager_register_callback(void (*cb)(enum dev_evt_type,union dev_evt_u *));
/**
 ****************************************************************************************
 * \brief Initialization of dev_manager stack.
 * 
 * \param[in]  cfg               BLE stack configuration.
 ****************************************************************************************
 */
void dev_manager_stack_init(struct ble_stack_cfg *cfg);
/**
 ****************************************************************************************
 * \brief Initialization of dev_manager stack.
 * 
 * \param[out]  addr                 Pointer to identity address.
 * \param[out]  random               Indicate if identity address is a public (False) or 
 *                                   static private random (True) address.
 ****************************************************************************************
 */
void dev_manager_get_identity_bdaddr(uint8_t *addr,bool *random);
/**
 ****************************************************************************************
 * \brief Add service with specified start handle.
 * 
 * \param[in]   svc                 Pointer to service to added.
   \param[in]   start_handle        Start handle of the service to add.
 *
 ****************************************************************************************
 */
void dev_manager_add_service_with_start_handle(struct svc_decl *svc, uint16_t start_handle);
/**
 ****************************************************************************************
 * \brief Add service.
 * 
 * \param[in]   svc                 Pointer to service to added.
 *
 ****************************************************************************************
 */
void dev_manager_add_service(struct svc_decl *svc);
/**
 ****************************************************************************************
 * \brief Set value for specified attribute.
 * 
 * \param[in]   handle              Attribute handle.
 * \param[in]   length              Length of the value.
 * \param[in]   value               Pointer to value to set.
 * 
 ****************************************************************************************
 */
uint8_t dev_manager_svc_set_value(uint16_t handle, uint16_t length, uint8_t *value);
/**
 ****************************************************************************************
 * \brief Get value for specified attribute.
 * 
 * \param[in]   handle              Attribute handle.
 * \param[out]  length              Length of the value.
 * \param[out]  value               Pointer to value to get.
 * 
 ****************************************************************************************
 */
uint8_t dev_manager_svc_get_value(uint16_t handle, uint8_t *value, uint16_t *length);
/**
 ****************************************************************************************
 * \brief Create legacy adv object.
 * 
 * \param[in]   p_param             Parameter for legacy adv object.
 *
 ****************************************************************************************
 */
void dev_manager_create_legacy_adv_object(struct legacy_adv_obj_param *p_param);
/**
 ****************************************************************************************
 * \brief Create extended adv object.
 * 
 * \param[in]   p_param             Parameter for extended adv object.
 *
 ****************************************************************************************
 */
void dev_manager_create_ext_adv_object(struct ext_adv_obj_param *p_param);
/**
 ****************************************************************************************
 * \brief Create scan object.
 * 
 * \param[in]   own_addr_type       Parameter for scan object.
 *
 ****************************************************************************************
 */
void dev_manager_create_scan_object(enum gap_own_addr_type own_addr_type);
/**
 ****************************************************************************************
 * \brief Create initiate object.
 * 
 * \param[in]   own_addr_type       Own address type.
 *
 ****************************************************************************************
 */
void dev_manager_create_init_object(enum gap_own_addr_type own_addr_type);
/**
 ****************************************************************************************
 * \brief Start advertising.
 * 
 * \param[in]   adv_handle                 Handle of adv object.
 * \param[in]   adv_data                   Adv data.
 * \param[in]   adv_data_length            Length of adv data.
 * \param[in]   scan_rsp_data              Scan response data.
 * \param[in]   scan_rsp_data_length       Length of Scan response data.
 *
 ****************************************************************************************
 */
void dev_manager_start_adv(uint8_t adv_handle,uint8_t *adv_data,uint8_t adv_data_length,uint8_t *scan_rsp_data,uint8_t scan_rsp_data_length);
/**
 ****************************************************************************************
 * \brief Set duration of adv.
 * 
 * \param[in]   duration       Duration of adv activity(in unit of 10ms). 0 means that 
 *                             advertising continues until the application disable it.
 *
 ****************************************************************************************
 */
void dev_manager_set_adv_duration(uint16_t duration);
/**
 ****************************************************************************************
 * \brief Update advertising data or scan response data.
 * 
 * \param[in]   adv_handle                 Handle of adv object.
 * \param[in]   adv_data                   Adv data.
 * \param[in]   adv_data_length            Length of adv data.
 * \param[in]   scan_rsp_data              Scan response data.
 * \param[in]   scan_rsp_data_length       Length of Scan response data.
 *
 ****************************************************************************************
 */
void dev_manager_update_adv_data(uint8_t adv_handle,uint8_t *adv_data,uint8_t adv_data_length,uint8_t *scan_rsp_data,uint8_t scan_rsp_data_length);
/**
 ****************************************************************************************
 * \brief Stop advertising.
 * 
 * \param[in]   adv_handle                 Handle of adv object.
 *
 ****************************************************************************************
 */
void dev_manager_stop_adv(uint8_t adv_handle);
/**
 ****************************************************************************************
 * \brief Start scan.
 * 
 * \param[in]   scan_handle        Handle of scan object.
 * \param[in]   param            Parameter for scan object.
 * 
 ****************************************************************************************
 */
void dev_manager_start_scan(uint8_t scan_handle, struct start_scan_param * param);
/**
 ****************************************************************************************
 * \brief Stop scan.
 * 
 * \param[in]   scan_handle        Handle of scan object.
 *
 ****************************************************************************************
 */
void dev_manager_stop_scan(uint8_t scan_handle);
/**
 ****************************************************************************************
 * \brief Start initiate.
 * 
 * \param[in]   init_handle         Handle of init object.
 * \param[in]   param             Parameter for init object.
 *
 ****************************************************************************************
 */
void dev_manager_start_init(uint8_t init_handle, struct start_init_param * param);
/**
 ****************************************************************************************
 * \brief Stop initiate.
 * 
 * \param[in]   init_handle         Handle of init object.
 *
 ****************************************************************************************
 */
void dev_manager_stop_init(uint8_t init_handle);
/**
 ****************************************************************************************
 * \brief Delete activity.
 * 
 * \param[in]   obj_hdl             Handle of object to delete.
 *
 ****************************************************************************************
 */
void dev_manager_delete_activity(uint8_t obj_hdl);
/**
 ****************************************************************************************
 * \brief Set mac address.
 * 
 * \param[in]   addr                Pointer to mac address to set.
 *
 ****************************************************************************************
 */
void dev_manager_set_mac_addr(uint8_t *addr);
/**
 ****************************************************************************************
 * \brief Update adv interval. The new intervals will not be applied until the adv activity
 *        is restarted.
 * \param[in]  adv_handle         Handle of the adv activity to be updated.
 * \param[in]  new_intv_min       Minimum new adv interval.
 * \param[in]  new_intv_max       Maxmium new adv interval.
 * \return                        Status of updating. 0 means NO_ERROR, otherwise means invalid
 *                                handle of adv.
 ****************************************************************************************
 */
uint8_t dev_manager_update_adv_interval(uint8_t adv_handle, uint32_t new_intv_min, uint32_t new_intv_max);
/**
 ****************************************************************************************
 * \brief Initialization of gap_manager.
 * 
 * \param[in]  evt_cb             Callback function to handle all the gap_manager messages.
 * 
 ****************************************************************************************
 */
void gap_manager_init(void (*evt_cb)(enum gap_evt_type,union gap_evt_u *,uint8_t));
/**
 ****************************************************************************************
 * \brief Re-register callback of gap_manager.
 * 
 * \param[in]  evt_cb             Callback function to handle all the gap_manager messages.
 * 
 ****************************************************************************************
 */
void gap_manager_register_callback(void (*evt_cb)(enum gap_evt_type,union gap_evt_u *,uint8_t));
/**
 ****************************************************************************************
 * \brief Disconnect specified connection.
 * 
 * \param[in]  con_idx            Connection ID number to disconnect.
 * \param[in]  reason             Reason to disconnect.
 * 
 ****************************************************************************************
 */
void gap_manager_disconnect(uint8_t con_idx,uint8_t reason);
/**
 ****************************************************************************************
 * \brief Set Phy for specific connection.
 * 
 * \param[in]  con_idx            Connection ID number to disconnect.
 * \param[in]  tx_phy             Supported LE PHY for data transmission (@see enum phy_type)
 * \param[in]  rx_phy             Supported LE PHY for data reception (@see enum phy_type)
 * \param[in]  phy_opt            PHY options (@see enum phy_option)
 * 
 ****************************************************************************************
 */   
void gap_manager_set_phy(uint8_t con_idx,uint8_t tx_phy,uint8_t rx_phy,uint8_t phy_opt);
/**
 ****************************************************************************************
 * \brief The master starts the bonding process
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  pair_feat         Pairing parameter setting, This parameter can be a value of @ref pair_feature.
 ****************************************************************************************
 */
void gap_manager_master_bond(uint8_t con_idx, struct pair_feature * pair_feat);
/**
 ****************************************************************************************
 * \brief The master starts the secure connection process
 * 
 * \param[in]  con_idx           Connection ID number.
 ****************************************************************************************
 */
void gap_manager_master_encrypt(uint8_t con_idx);
/**
 ****************************************************************************************
 * \brief Initiate an encryption request from the slave. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  auth              SEC Auth param, This parameter can be a value of @ref gap_pair_auth
 ****************************************************************************************
 */
void gap_manager_slave_security_req(uint8_t con_idx, uint8_t auth);
/**
 ****************************************************************************************
 * \brief The slave exchange pairs information.
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  accept            Whether to save master pairing information,value(0 or 1).
 * \param[in]  feat              Pairing parameter setting, This parameter can be a value of @ref pair_feature.
 ****************************************************************************************
 */
void gap_manager_slave_pair_response_send(uint8_t con_idx,uint8_t accept,struct pair_feature *feat);
/**
 ****************************************************************************************
 * \brief Master and slave pair key input. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  passkey           Connect the key, This parameter can be a value of @ref gap_pin_str.
 ****************************************************************************************
 */
void gap_manager_passkey_input(uint8_t con_idx,struct gap_pin_str *passkey);
/**
 ****************************************************************************************
 * \brief Verify that the key is the same in numerical comparison mode(Only for LE Secure Connections). 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  equal             Numeric comparison results.
 ****************************************************************************************
 */
void gap_manager_numeric_compare_set(uint8_t con_idx,bool equal);
/**
 ****************************************************************************************
 * \brief Set the security oob of the specified connection. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  sc_oob            SEC OOB value, This parameter can be a value of @ref gap_sc_oob.
 ****************************************************************************************
 */
void gap_manager_sc_oob_set(uint8_t con_idx,struct gap_sc_oob *sc_oob);
/**
 ****************************************************************************************
 * \brief Set the security oob of the specified connection,
 *        BLE_KEY_LEN The length of the paired temporary key. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  key               Pairing Temporary Key value.
 ****************************************************************************************
 */
void gap_manager_tk_set(uint8_t con_idx,uint8_t key[BLE_KEY_LEN]);
/**
 ****************************************************************************************
 * \brief Gets the role of the specified connection. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \return                       Role of the connection. Refer to ::LS_BLE_ROLE.
 * 
 ****************************************************************************************
 */
uint8_t gap_manager_get_role(uint8_t con_idx);
/**
 ****************************************************************************************
 * \brief Gets the security level of the specified connection. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \return The security level of the specified connection.
 ****************************************************************************************
 */
uint8_t gap_manager_get_sec_lvl(uint8_t con_idx);
/**
 ****************************************************************************************
 * \brief Gets the peer device address. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[out] addr              Pointer to address.
 * 
 ****************************************************************************************
 */
void gap_manager_get_peer_addr(uint8_t con_idx,struct ble_addr *addr);
/**
 ****************************************************************************************
 * \brief Gets peer identity device address. 
 * 
 * \param[in]  peer_id           Pairing ID number.
 * \param[out] addr              Pointer to address.
 * 
 ****************************************************************************************
 */
void gap_manager_get_identity_addr(uint8_t peer_id,struct ble_addr *addr);
/**
 ****************************************************************************************
 * \brief Update parameter for specified connection. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  p_param           Pointer to parameter to update.
 * \return Whether the connection parameter is valid
 * 
 ****************************************************************************************
 */
uint8_t gap_manager_update_conn_param(uint8_t con_idx,struct gap_update_conn_param *p_param);
/**
 ****************************************************************************************
 * \brief Update packet size in air for specified connection. 
 * 
 * \param[in]  con_idx           Connection ID number.
 * \param[in]  p_param           Pointer to packet size parameter to set.
 * 
 ****************************************************************************************
 */
void gap_manager_set_pkt_size(uint8_t con_idx, struct gap_set_pkt_size *p_param);
/**
 ****************************************************************************************
 * \brief Deletes the bound device information. 
 * 
 * \param[in]  peer_id           Pairing ID number.
 ****************************************************************************************
 */
void gap_manager_delete_bonding(uint8_t peer_id);
/**
 ****************************************************************************************
 * \brief Gets the pairing ID of the bound device. 
 * 
 * \param[in]  link_id           Connection ID number.
 * \return The pairing ID of the bound device.
 ****************************************************************************************
 */
uint8_t gap_manager_get_bonding_peer_id(uint8_t link_id);
/**
 ****************************************************************************************
 * \brief Gets the number of bound devices. 
 * 
 * \return The number of bound devices.
 ****************************************************************************************
 */
uint8_t gap_manager_get_bonded_dev_num(void);
/**
 ****************************************************************************************
 * \brief Gets the RSSI value of the specified connected device. 
 * 
 * \param[in]  link_id           Connection ID number.
 ****************************************************************************************
 */
void gap_manager_get_peer_rssi(uint8_t link_id);
/**
 ****************************************************************************************
 * \brief Initialize GATT manager.
 *
 * \param[in]  evt_cb               Callback function for gatt service.
 *
 ****************************************************************************************
 */
void gatt_manager_init(void (*evt_cb)(enum gatt_evt_type,union gatt_evt_u *,uint8_t));
/**
 ****************************************************************************************
 * \brief Re-register callback of GATT manager.
 *
 * \param[in]  evt_cb               Callback function for gatt service.
 *
 ****************************************************************************************
 */
void gatt_manager_register_callback(void (*evt_cb)(enum gatt_evt_type,union gatt_evt_u *,uint8_t));
/**
 ****************************************************************************************
 * \brief Register service in GATT manager.
 *
 * \param[in]  start_hdl               Start handle of the service to be registered.
 * \param[in]  att_num                 Number of attributes contained in the service.
 * \param[in]  svc                     Pointer of service to be registered.
 *
 ****************************************************************************************
 */
void gatt_manager_svc_register(uint16_t start_hdl,uint8_t att_num,struct gatt_svc_env *svc);
/**
 ****************************************************************************************
 * \brief Set service/profile permission.
 *
 * \param[in]  handle                  Start handle of the service/profile.
 * \param[in]  perm                    Permission value to set. Refer to ::sec_lvl_type
 *
 ****************************************************************************************
 */
void gatt_manager_server_set_svc_permission(uint16_t handle, uint16_t perm);
/**
 ****************************************************************************************
 * \brief Send reply to read request from GATT client.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  handle                  Handle of attribute to read.
 * \param[in]  status                  Status of read command execution in application.
 * \param[in]  data                    Pointer of data reply.
 * \param[in]  length                  Length of data to send in the units of bytes.
 *
 ****************************************************************************************
 */
void gatt_manager_server_read_req_reply(uint8_t con_idx,uint16_t handle,uint8_t status,uint8_t *data,uint16_t length);
/**
 ****************************************************************************************
 * \brief Send indication to client.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  handle                  Handle of attribute to send indication.
 * \param[in]  data                    Pointer of data reply.
 * \param[in]  length                  Length of data to send in the units of bytes.
 * \param[in]  transaction_id          Id of transaction between stack with application.
 *
 ****************************************************************************************
 */
void gatt_manager_server_send_indication(uint8_t con_idx,uint16_t handle,uint8_t *data,uint16_t length,uint16_t *transaction_id);
/**
 ****************************************************************************************
 * \brief Send service changed indication.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  start_handle            Start handle of attributes changed.
 * \param[in]  end_handle              End handle of attributes changed.
 *
 ****************************************************************************************
 */
void gatt_manager_server_send_svc_changed_indication(uint8_t con_idx, uint16_t start_handle, uint16_t end_handle);
/**
 ****************************************************************************************
 * \brief Send notification to client.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  handle                  Handle of attribute to send notification.
 * \param[in]  data                    Pointer of data reply.
 * \param[in]  length                  Length of data to send in the units of bytes.
 * \param[in]  transaction_id          Id of transaction between stack with application.
 *
 ****************************************************************************************
 */
void gatt_manager_server_send_notification(uint8_t con_idx,uint16_t handle,uint8_t *data,uint16_t length,uint16_t *transaction_id);
/**
 ****************************************************************************************
 * \brief Send indication confirm to server.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  handle                  Handle of attribute to send confirm.
 *
 ****************************************************************************************
 */
void gatt_manager_client_indication_confirm(uint8_t con_idx,uint16_t handle);
/**
 ****************************************************************************************
 * \brief Get the handle of attribute in the specified service.
 *
 * \param[in]  svc                     Pointer of the service containing the attribute.
 * \param[in]  att_idx                 Attribute index.
 *
 ****************************************************************************************
 */
uint16_t gatt_manager_get_svc_att_handle(struct gatt_svc_env *svc,uint8_t att_idx);
/**
 ****************************************************************************************
 * \brief Send data to GATT server by writing command(write without response).
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  handle                  Handle of attribute to write.
 * \param[in]  data                    Pointer of data to send.
 * \param[in]  length                  Length of data to send in the units of bytes.
 *
 ****************************************************************************************
 */
void gatt_manager_client_write_no_rsp(uint8_t con_idx,uint16_t handle,uint8_t *data,uint16_t length);
/**
 ****************************************************************************************
 * \brief Send data to GATT server by writing request(write with response).
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  handle                  Handle of attribute to write.
 * \param[in]  data                    Pointer of data to send.
 * \param[in]  length                  Length of data to send in the units of bytes.
 *
 ****************************************************************************************
 */
void gatt_manager_client_write_with_rsp(uint8_t con_idx,uint16_t handle,uint8_t *data,uint16_t length);
/**
 ****************************************************************************************
 * \brief Enable cccd(client characteristic configuration descriptor) on GATT server service.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  handle                  Handle of attribute of cccd.
 * \param[in]  notification_en         1 = enable notification, 0 = disable notification.
 * \param[in]  indication_en           1 = enable indication, 0 = disable indication.
 *
 ****************************************************************************************
 */
void gatt_manager_client_cccd_enable(uint8_t con_idx,uint16_t handle,bool notification_en, bool indication_en);
/**
 ****************************************************************************************
 * \brief Discovery service by specified uuid.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  uuid                    Pointer of uuid to be discovered.
 * \param[in]  uuid_len                Length of uuid in units of ::uuid_length.
 * \param[in]  start_hdl               Start handle of the range to search.
 * \param[in]  end_hdl                 End handle of the range to search.
 *
 ****************************************************************************************
 */
void gatt_manager_client_svc_discover_by_uuid(uint8_t con_idx,uint8_t *uuid,enum uuid_length uuid_len,uint16_t start_hdl,uint16_t end_hdl);
/**
 ****************************************************************************************
 * \brief Discovery characteristic by specified uuid.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  uuid                    Pointer of uuid to be discovered.
 * \param[in]  uuid_len                Length of uuid in units of ::uuid_length.
 * \param[in]  start_hdl               Start handle of the range to search.
 * \param[in]  end_hdl                 End handle of the range to search.
 *
 ****************************************************************************************
 */
void gatt_manager_client_char_discover_by_uuid(uint8_t con_idx,uint8_t *uuid,enum uuid_length uuid_len,uint16_t start_hdl,uint16_t end_hdl);
/**
 ****************************************************************************************
 * \brief Discovery cccd.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  start_hdl               Start handle of the range to search.
 * \param[in]  end_hdl                 End handle of the range to search.
 *
 ****************************************************************************************
 */
void gatt_manager_client_desc_char_discover(uint8_t con_idx,uint16_t start_hdl,uint16_t end_hdl);
/**
 ****************************************************************************************
 * \brief Send MTU exchange to GATT server.
 *
 * \param[in]  con_idx                 Connection index.
 *
 ****************************************************************************************
 */
void gatt_manager_client_mtu_exch_send(uint8_t con_idx);
/**
 ****************************************************************************************
 * \brief Read attribute value by handle.
 *
 * \param[in]  con_idx                 Connection index.
 * \param[in]  handle                  Handle of attribute to read.
 *
 ****************************************************************************************
 */
void gatt_manager_client_read(uint8_t con_idx,uint16_t handle);

/** @}*/

#endif

