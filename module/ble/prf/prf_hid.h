#ifndef PRF_HID_H_
#define PRF_HID_H_
#include <stdint.h>

/** \addtogroup BLE
 *  @{
 */

/** \addtogroup PRF_HID
 *  @{
 */

///This macro definition indicates that the maximum number of HID service instances is 2
#define HID_NB_ADD_MAX    (2)
///This macro definition indicates that the maximal number of Report Characteristics that can be present in a HID Service is 5
#define HID_NB_REPORT_MAX (5)

///HID device service features
enum hid_svc_feature
{
    HID_KEYBOARD        = 0X01,/**< The HID device is operating as a keyboard */
    HID_MOUSE           = 0X02,/**< The HID device is operating as a mouse */
    HID_PROTO_MODE      = 0X04,/**< The HID Device supports the Boot Protocol Mode */
    HID_EXT_REF         = 0X08,/**< The Report Map Characteristic value maps information to an external service characteristic */
    HID_BOOT_KB_WR      = 0X10,/**< The Boot Keyboard Input Report Characteristic value is writable */
    HID_BOOT_MOUSE_WR   = 0X20,/**< The Boot Mouse Input Report Characteristic value is writable */
    HID_MASK            = 0X3F,
    HID_REPORT_NTF_EN   = 0X40,/**< Report Notification Enabled */
};
///Report characteristic parameter configuration
enum hid_report_cfg
{
    HID_REPORT_IN   = 0X01,/**< The Report is an Input Report */
    HID_REPORT_OUT  = 0X02,/**< The Report is an Output Report */
    HID_REPORT_FEAT = 0X03,/**< The Report is a Feature Report */
    HID_REPORT_WR   = 0X10,/**< The Report Characteristic value is writable. Taken in account only if the Report is an Input Report */
};
///Representation of the flags parameter in the HID information
enum hid_info_flag
{
    HID_WKUP_FOR_REMOTE = 0X01,/**< Inform if the HID Device is capable of providing wake-up signal to a HID host */
    HID_NORM_CONN,/**< Inform if the HID Device is normally connectable */
};
///HID Information structure
struct hid_info
{
    uint16_t bcdHID;/**< HID Class Specification release number in binarycoded decimal (for example, 1.50 is 0x150) */
    uint8_t bCountryCode;/**< Hardware target country */
    uint8_t flags;/**< Flags ::hid_info_flag */
};

/// External Report Reference
struct hid_ext_ref
{
    uint16_t inc_svc_hdl;/**<External Report Reference - Included Service*/
    uint16_t rep_ref_uuid;/**<External Report Reference - Characteristic UUID*/
};

///HID configuration structure
struct hids_cfg
{
    uint8_t svc_features;/**< Features supported in the HID Service ::hid_svc_feature */
    uint8_t report_nb;/**< Value of the HID Information Characteristic */
    uint8_t report_cfg[HID_NB_REPORT_MAX];/**< Features supported by each of the Report Characteristics in the HID Service ::hid_report_cfg */
    uint8_t report_id[HID_NB_REPORT_MAX];/**< Report id number for a given report type, The Report ID is defined in the Report Map */
    struct hid_info info; /**< Value of the HID Information Characteristic ::hid_info */
    struct hid_ext_ref ext_ref; /**< Value of the External Report Reference ::hid_ext_ref */
};
///HID database configuration structure
struct hid_db_cfg
{
    uint8_t hids_nb;/**< Number of HID service */
    struct hids_cfg cfg[HID_NB_ADD_MAX];/**< HID configuration items ::hids_cfg */
};
///Type of operation HID events
enum hid_evt_type
{
    HID_REPORT_READ,/**< Read report value configuration */
    HID_NTF_CFG,/**< The report notifies configuration values */
    HID_NTF_DONE,/**< Report Notification done */
    HID_REPORT_WRITE,/**< Modify/Set report value */
};
/// Type of reports enumeration
enum app_hogpd_report_type
{
    APP_HOGPD_REPORT,/**< The Report characteristic is used to exchange data between a HID Device and a HID Host */
    APP_HOGPD_REPORT_MAP,/**< The Report Map characteristic */
    APP_HOGPD_BOOT_KEYBOARD_INPUT_REPORT,/**< Boot Keyboard Input Report */
    APP_HOGPD_BOOT_KEYBOARD_OUTPUT_REPORT,/**< Boot Keyboard Output Report */
    APP_HOGPD_BOOT_MOUSE_INPUT_REPORT,/**< Boot Mouse Input Report */
};
///A structure for reporting information about read events
struct hid_read_report_req_evt
{
    uint16_t length;/**< The length of the data to be sent */
    uint8_t* value;/**< Point to the data address to send */
    uint8_t  hid_idx;/**< HIDS Instance */
    uint8_t  type;/**< type of report ::app_hogpd_report_type */
    uint8_t  idx;/**< Report Instance - 0 for boot reports and report map */
    uint8_t con_idx;/**< Connect id */
};
///A structure for reporting information about write events
struct hid_write_report_req_evt
{
    uint16_t length;/**< The length of the data to be sent */
    uint8_t* value;/**< Point to the data address to send */
    uint8_t  hid_idx;/**< HIDS Instance */
    uint8_t  type;/**< type of report ::app_hogpd_report_type */
    uint8_t  idx;/**< Report Instance - 0 for boot reports and report map */
    uint8_t con_idx;/**< Connect id */
};
///Structure for the Report configuration events
struct hid_ntf_cfg_evt
{
    uint16_t value;/**< Notification Configuration Value */
    uint8_t con_idx;/**< Connect id */
};

struct hid_ntf_done_evt
{
    uint8_t con_idx;/**< Connect id */
};

///Information data Union used to read or write information events
union hid_evt_u
{
    struct hid_read_report_req_evt read_report_req;/**< ::hid_read_report_req_evt */
    struct hid_ntf_cfg_evt ntf_cfg;/**< ::hid_ntf_cfg_evt */
    struct hid_write_report_req_evt write_report_req;/**< ::hid_write_report_req_evt */
    struct hid_ntf_done_evt ntf_done;/**< ::hid_ntf_done_evt */
};

/**  \brief Initializes the HID events that reports a request to the counterpart device
 *   \param[in] evt_cb  Callback function for HID events
 */
void prf_hid_server_callback_init(void (*evt_cb)(enum hid_evt_type, union hid_evt_u *));

/**  \brief Add the HID service to the database of the local device
 *   \param[in] sec_lvl Security level eg:default NO_SEC
 *   \param[in] cfg Configure structure variables for HID service information ::hid_db_cfg
 *   \param[in] len Length of hid_db_cfg
 */
void dev_manager_prf_hid_server_add(uint8_t sec_lvl, struct hid_db_cfg* cfg,uint16_t len);

/**  \brief A function interface for the HID device to send data
 *   \param[in] report_idx HID report instance
 *   \param[in] report_data Point to the data address to send
 *   \param[in] len The length of the data to be sent
 *   \param[in] conidx Connect instance
 */
void app_hid_send_keyboard_report(uint8_t report_idx, uint8_t *report_data,uint8_t len,uint8_t conidx);

/**  \brief Report notification configuration
 *   \param[in] ntf_cfg The report notifies configuration values
 *   \param[in] con_idx Connect instance
 *   \param[in] peer_id Peer device instance
 */
void hid_ntf_cfg_init(uint16_t ntf_cfg,uint8_t con_idx,uint8_t peer_id);

/** @}*/


/** @}*/

#endif
