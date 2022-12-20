#ifndef _LS_SIG_MESH_H_
#define _LS_SIG_MESH_H_
#include <stdint.h>
#include "ls_ble.h"

/** \addtogroup LSSIG_MESH_PROVEE
 *  @{
 */

#define __LSSIGMESH_EMPTY     /*!< Flexible array length*/

typedef uint8_t SIGMESH_ModelHandle_TypeDef;
typedef uint8_t SIGMESH_NodeInfo_TypeDef;

#define STATUS_SIGMESH_NO_ERROR     (0x0000)    /*!<SIG mesh No Error*/

#define UUID_MESH_DEV_LEN (16)     /*!<Device UUID length*/
#define MESH_AUTH_DATA_LEN (16)    /*!<Authentication data length*/
#define MAX_MESH_MODEL_NB (20)     /*!< Max number of model in a node*/
#define MAX_MESH_MODEL_MSG_BUFFER  (380)  /*!< The buffer of model message*/

#define UPADTE_GLP_STOP_TYPE 0xfe    /*!< To be updated the status of stop type by tmall genie GLP function to application*/
#define UPADTE_GLP_STOP_TIMEOUT_TYPE 0xfd   /*!< To be updated the status of timeout type by tmall genie GLP function to application*/

//mesh server model index
#define GENERIC_ONOFF_SERVER             (0x1000)  /*!< SIG Model Index of generic onoff server 0x1000*/
#define GENERIC_ONOFF_CLIENT             (0x1001)  /*!< SIG Model Index of generic onoff client 0x1001*/
#define GENERIC_LVL_SERVER               (0x1002)  /*!< SIG Model Index of generic level server 0x1002*/
#define GENERIC_LVL_CLIENT               (0x1003)  /*!< SIG Model Index of generic level client 0x1003*/
#define SCENE_SERVER                     (0x1203)  /*!< SIG Model Index of Scene server 0x1203*/
#define LIGHTNESS_SERVER                 (0x1300)  /*!< SIG Model Index of light lightness server 0x1300*/
#define LIGHTS_CTL_SERVER                (0x1303)  /*!< SIG Model Index of light control server 0x1303*/
#define LIGHTS_CTLT_SERVER               (0x1306)  /*!< SIG Model Index of light CTL temperature server 0x1306*/
#define LIGHTS_HSL_SERVER                (0x1307)  /*!< SIG Model Index of light HSL server 0x1307*/
#define LIGHTS_HSLH_SERVER               (0x130A)  /*!< SIG Model Index of light HSL hue server 0x130A*/
#define LIGHTS_HSLSAT_SERVER             (0x130B)  /*!< SIG Model Index of light HSL saturation server 0x130B*/
#define LIGHTS_XYL_CLIENT                (0x130E)  /*!< SIG Model Index of light XYL server 0x130C*/
#define VENDOR_TMALL_SERVER              (0x01A80000) /*!< Vendor Model Index of tmall genie server 0x01A80000*/
#define VENDOR_USER_SERVER               (0x093A0001) /*!< Vendor Model Index of linkedsemi server 0x093A0001*/
#define VENDOR_USER_CLIENT               (0x093A0002)  /*!< Vendor Model Index of linkedsemi client 0x093A0002*/
        
 //foundation model status opcode
#define FOUNDATION_MDL_CONFG_APPKEY_STATUS                     (0x0380)  /*!< Application key status*/
#define FOUNDATION_MDL_CONFG_FRIEND_STATUS                     (0x1180)  /*!< Friend status*/
#define FOUNDATION_MDL_CONFG_GATT_PROXY_STATUS                 (0x1480)  /*!< GATT proxy status*/
#define FOUNDATION_MDL_CONFG_KEY_REFRESH_PHASE_STATUS          (0x1780)  /*!< Key refresh phase status*/
#define FOUNDATION_MDL_CONFG_MODEL_PUB_STATUS                  (0x1980)  /*!< Model publication status*/
#define FOUNDATION_MDL_CONFG_MODEL_SUBS_STATUS                 (0x1F80)  /*!< Model subscription status*/
#define FOUNDATION_MDL_CONFG_RELAY_STATUS                      (0x2880)  /*!< Relay status*/
#define FOUNDATION_MDL_CONFG_LPN_POLLTIMEOUT_STATUS            (0x2E80)  /*!< Low power node PollTimeout status*/
#define FOUNDATION_MDL_CONFG_HBEAT_SUBS_STATUS                 (0x3C80)  /*!< Heartbeat subscription status*/
#define FOUNDATION_MDL_CONFG_MODEL_APP_STATUS                  (0x3E80)  /*!< Model application status*/
#define FOUNDATION_MDL_CONFG_NETKEY_STATUS                     (0x4480)  /*!< Network key status*/

//Generic OnOff        
#define GENERIC_ONOFF_GET                (0x0182) /*!< Opcdoe of generic onoff get 0x0182*/
#define GENERIC_ONOFF_SET                (0x0282) /*!< Opcdoe of generic onoff set 0x0282*/
#define GENERIC_ONOFF_SET_UNAK           (0x0382) /*!< Opcdoe of generic onoff set unacknowleged 0x0382*/
#define GENERIC_ONOFF_STATUS             (0x0482) /*!< Opcdoe of generic onoff status 0x0482*/

//Generic OnOff        
#define GENERIC_LVL_GET                  (0x0582) /*!< Opcdoe of generic level get 0x0582*/
#define GENERIC_LVL_SET                  (0x0682) /*!< Opcdoe of generic level set 0x0682*/
#define GENERIC_LVL_SET_UNAK             (0x0782) /*!< Opcdoe of generic level set unacknowleged 0x0782*/
#define GENERIC_LVL_STATUS               (0x0882) /*!< Opcdoe of generic level status 0x0882*/
// SCENE SERVER
#define SCENE_GET                        (0x4182)  /*!< Opcdoe of scene get 0x4182*/
#define SCENE_RECALL                     (0x4282)  /*!< Opcdoe of scene recall 0x4282*/
#define SCENE_RECALL_UNAK                (0x4382)  /*!< Opcdoe of scene recall unacknowleged 0x4382*/
#define SCENE_STATUS                     (0x5E)    /*!< Opcdoe of scene status 0x5e*/
#define SCENE_REGISTER_GET               (0x4482)  /*!< Opcdoe of scene register get 0x4482*/
#define SCENE_REGISTER_STATUS            (0x4582)  /*!< Opcdoe of scene register status 0x4582*/

// SCENE SETUP SERVER
#define SCENE_STORE                      (0x4682)  /*!< Opcdoe of scene store 0x4682*/
#define SCENE_STORE_UNAK                 (0x4782)  /*!< Opcdoe of scene store 0x4782*/
#define SCENE_DELETE                     (0x9E82)  /*!< Opcdoe of scene delete 0x9e82*/
#define SCENE_DELETE_UNAK                (0x9F82)  /*!< Opcdoe of scene delete unacknowleged 0x9f82*/

//Light Lightness        
#define LIGHT_LIGHTNESS_SET              (0x4c82) /*!< Opcdoe of light lightness set 0x4c82*/
#define LIGHT_LIGHTNESS_SET_UNAK         (0x4d82) /*!< Opcdoe of light lightness set unacknowleged 0x4d82*/
#define LIGHT_LIGHTNESS_STATUS           (0x4e82) /*!< Opcdoe of light lightness status 0x4e82*/
#define LIGHT_LIGHTNESS_RANGE_STATUS     (0x5882) /*!< Opcdoe of light lightness range status 0x5882*/

//Light HSL
#define LIGHT_HSL_HUE_STATUS             (0x7182)  /*!< Opcdoe of light hsl hue 0x7182*/
#define LIGHT_HSL_SAT_STATUS             (0x7582)  /*!< Opcdoe of light hsl sat 0x7582*/
#define LIGHT_HSL_SET                    (0x7682) /*!< Opcdoe of light hsl set 0x7682*/
#define LIGHT_HSL_SET_UNACK              (0x7782) /*!< Opcdoe of light hsl set unacknowleged 0x7782*/
#define LIGHT_HSL_STATUS                 (0x7882) /*!< Opcdoe of light hsl status 0x7882*/
#define LIGHT_HSL_RANGE_STATUS           (0x7E82) /*!< Opcdoe of light hsl range status 0x7E82*/

//Light CTL
#define LIGHT_CTL_SET                    (0x5E82) /*!< Opcdoe of light ctl set 0x5E82*/
#define LIGHT_CTL_SET_UNACK              (0x5F82) /*!< Opcdoe of light ctl set unacknowleged 0x5F82*/
#define LIGHT_CTL_STATUS                 (0x6082) /*!< Opcdoe of light ctl status 0x6082*/
#define LIGHT_CTL_TEMP_RANGE_STATUS      (0x6382)  /*!< Opcdoe of light ctl temperature range status 0x6382*/
#define LIGHT_CTL_TEMP_STATUS            (0x6682) /*!< Opcdoe of light ctl temperature status 0x6682*/

// tmall Vendor        
#define APP_MESH_VENDOR_SET              (0x0001A8d1)  /*!< Vendor opcdoe of tmall genie set 0x0001A8d1*/
#define APP_MESH_VENDOR_SET_UNAK         (0x0001A8d2)  /*!< Vendor opcdoe of tmall genie set unacknowleged 0x0001A8d2*/
#define APP_MESH_VENDOR_STATUES          (0x0001A8d3)  /*!< Vendor opcdoe of tmall genie status 0x0001A8d3*/
#define APP_MESH_VENDOR_INDICATION       (0x0001A8d4)  /*!< Vendor opcdoe of tmall genie indication 0x0001A8d4*/
#define APP_MESH_VENDOR_CONFIRMATION     (0x0001A8d5)  /*!< Vendor opcdoe of tmall genie confirmation 0x0001A8d5*/
#define APP_MESH_VENDOR_TRANSPARENT_MSG  (0x0001A8cf)  /*!< Vendor opcdoe of tmall genie transparent message 0x0001A8cf*/

// linkedsemi Vendor
#define APP_LS_SIG_MESH_VENDOR_GET          (0x00093AD0)  /*!< Vendor opcdoe of linkedsemi set 0x00093AD0*/        
#define APP_LS_SIG_MESH_VENDOR_SET          (0x00093AD1)  /*!< Vendor opcdoe of linkedsemi set 0x00093AD1*/
#define APP_LS_SIG_MESH_VENDOR_SET_UNAK     (0x00093AD2)  /*!< Vendor opcdoe of linkedsemi set unacknowleged 0x00093AD2*/
#define APP_LS_SIG_MESH_VENDOR_STATUS       (0x00093AD3)  /*!< Vendor opcdoe of linkedsemi status 0x00093AD3*/
#define APP_LS_SIG_MESH_VENDOR_INDICATION   (0x00093AD4)  /*!< Vendor opcdoe of linkedsemi indication 0x00093AD4*/
#define APP_LS_SIG_MESH_VENDOR_CONFIRMATION (0x00093AD5)  /*!< Vendor opcdoe of linkedsemi confirmation 0x00093AD5*/
#define APP_LS_SIG_MESH_VENDOR_HEARTBEAT    (0x00093AD6)  /*!< Vendor opcdoe of linkedsemi heartbeat 0x00093AD6*/
#define APP_LS_SIG_MESH_VENDOR_SCENE_SET    (0x00093AD7)  /*!< Vendor opcdoe of linkedsemi scene setting 0x00093AD7*/
#define APP_LS_SIG_MESH_VENDOR_SCENE_ACK    (0x00093AD8)  /*!< Vendor opcdoe of linkedsemi scene setting ack 0x00093AD8*/

#define VENDOR_OPCODE_LEN (3)               /*!< Vendor opcdoe length*/
#define VENDOR_OPCODE_MASK (0x0000C0)       /*!< Vendor opcdoe MASK*/
#define VENDOR_OPCODE_TYPE (0xC0)       /*!< Vendor opcdoe type*/
/**s
  * @brief SIG mesh event type
  */
enum mesh_evt_type
{
    MESH_ACTIVE_ENABLE = 0,          /*!< To be reported this event type after SIG mesh was initialized and activated*/
    MESH_ACTIVE_DISABLE,             /*!< To be reported this event type after SIG mesh was stopped*/
    MESH_ACTIVE_REGISTER_MODEL,      /*!< To be reported this event type after all requested models were registered, you need to save the returned local index*/
    MESH_ACTIVE_MODEL_PUBLISH,       /*!< To be reported this event type after client model was enable publish function by provisioner, you need to save the returned information of publish*/
    MESH_ACTIVE_MODEL_GROUP_MEMBERS, /*!< To be reported this event type after all requested models were automatically bound AppKey, only for genie mesh*/
    MESH_ACTIVE_MODEL_PUBLISHED,    /*!< To be reported this event type after the protocol stack confirms that the message was successfully Published*/
    MESH_ACTIVE_MODEL_RSP_SENT,      /*!< To be reported this event type after the protocol stack confirms that the message was successfully sent*/
    MESH_ACTIVE_LPN_START,           /*!< To be reported that this event type requests low power properties (such as timeout, interval, previous_address, RX window factor) after the low-power feature node was registered*/
    MESH_ACTIVE_LPN_OFFER,           /*!< When the low-power node establishes a friendly relationship, all nearby friend-supporting attributes are reported to the application layer and this event type is activated*/
    MESH_ACTIVE_LPN_STATUS,          /*!< To be reported that this event type requests to send a status message of LPN, such as Friendship status/address of friend node*/
    MESH_ACTIVE_STORAGE_LOAD,        /*!< To be reported this event type when each time the device was restarted and reported whether the device was a node */
    MESH_GET_PROV_INFO,              /*!<To be reported this event type requesting device properties (such as uuid, urihash, oob) during provisioning*/
    MESH_GET_PROV_AUTH_INFO,         /*!<To be reported that this event type requests device authentication values during configuration*/
    MESH_REPORT_ATTENTION_STATE,     /*!< To be reported this event type after the attention state had been updated*/
    MESH_REPOPT_PROV_RESULT,         /*!<To be reported this event type whether the device would successfully become a node after it was provisioned*/
    MESH_ACCEPT_MODEL_INFO,          /*!<To be reported this event type when vendor model recevied messages*/
    MESH_REPORT_TIMER_STATE,         /*!<To be reported this event type when the power-on timer timed out to perform power-on count clearing*/
    MESH_GENIE_PROV_COMP,            /*!<To be reported this event type after all requested models were automatically bound AppKey, only for genie lower power*/
    MESH_ADV_REPORT,                 /*!<To be reported this event type when the device scaned an adv message*/
    MESH_STATE_UPD_IND,              /*!<To be reported this event type when sig model recevied messages*/
    MESH_ACTIVE_GLP_START,           /*!<To be reported this event type when each time the node was restarted and enabled genie lower power*/
    MESH_ACTIVE_GLP_STOP,            /*!<To be reported this event type when the node was stopped genie lower power*/
    MESH_ACTIVE_AUTO_PROV,           /*!<To be reported this event type when automatic provisioning was enabled on the device*/
    MESH_EVT_TYPE_MAX,
};
/**
  * @brief sig mesh feature type definition
  */
enum mesh_feature
{
    EN_RELAY_NODE = 0x00000001,      /*!< Relay feature*/
    EN_PROXY_NODE = 0x00000002,      /*!< Both the Gatt feature and proxy feature are enabled*/
    EN_FRIEND_NODE = 0x00000004,     /*!< Friend feature*/
    EN_LOW_POWER_NODE = 0x00000008,  /*!< Lower power feature*/
    EN_MSG_API = 0x00010000,         /*!< The Message's API feature must be enabled*/
    EN_PB_GATT = 0x00020000,         /*!< Both the Gatt feature and proxy feature are enabled*/
    EN_DYN_BCN_INTV = 0x00040000,    /*!< Dynamic beacon interval feature*/
    EN_PROVER = 0x00080000,          /*!< Provisioner feature*/
};

/**
  * @brief Device state definition
  */
enum mesh_provisioned_state
{
    UNPROVISIONED_KO = 0x00,     /*!< The device was not a node*/
    PROVISIONING,
    PROVISIONED_OK,               /*!< The device was a node*/
};

/**
  * @brief provisioning state of the device definition
  */
enum mesh_provisioning_result
{
    MESH_PROV_STARTED = 0x0, /*!< The device was provisioning*/
    MESH_PROV_SUCCEED,       /*!< The device provisioned and successly to be a node*/
    MESH_PROV_FAILED,        /*!< The device provisioned but fail to be a node*/
};

/**
  * @brief mesh timer sate of user definition
  */
enum mesh_timer_state
{
    MESH_TIMER_DOING = 0x00,  /*!< The timer was working*/
    MESH_TIMER_DONE = 0x01,   /*!< The timer timed out*/
};

/**
  * @brief  The reason definition why genie lower power was stoped   
  */
enum tmall_glp_stop_reason
{
    NO_STOPPING_GLP_REQ = 0x00,         /*!< Normal state for glp*/
    APPLICATION_USER_STOPPING_GLP_REQ,  /*!< User requests to turn off GLP*/
    PROVISIONING_INVITE_SWITCH_GLP_REQ, /*!< During provisioning requests to turn off GLP*/
    PROVISIONING_COMP_SWITCH_GLP_REQ,   /*!< After provisioning requests to turn on GLP*/
};

/**
  * @brief  state definition of genie lower power   
  */
enum tmall_glp_state
{
    TMALL_GLP_STATE_IDLE =0x00,   /*!< Idle state for glp*/
    TMALL_GLP_STATE_ACTIVE,       /*!< Active state for glp*/
};

/**
  * @brief  State identifier values of sig model  
  */
enum mesh_state_idx
{
    MESH_STATE_GEN_ONOFF = 0,               /*!< Generic OnOff state*/
    MESH_STATE_GEN_LVL,                     /*!< Generic Level state*/
    MESH_STATE_GEN_DTT,                     /*!< Generic Default Transition Time state*/
    MESH_STATE_GEN_POWER_ACTUAL,            /*!< Generic Power Actual state*/
    MESH_STATE_GEN_POWER_LAST,              /*!< Generic Power Last state*/
    MESH_STATE_GEN_POWER_DFLT,              /*!< Generic Power Default state*/
    MESH_STATE_GEN_POWER_RANGE,             /*!< Generic Power Range state*/
    MESH_STATE_GEN_ONPOWERUP,               /*!< Generic OnPowerUp state*/

    MESH_STATE_LIGHT_LN = 50,               /*!< Light Lightness*/
    MESH_STATE_LIGHT_LN_LIN,                /*!< Light Lightness Linear*/
    MESH_STATE_LIGHT_LN_LAST,               /*!< Light Lightness Last*/
    MESH_STATE_LIGHT_LN_DFLT,               /*!< Light Lightness Default*/
    MESH_STATE_LIGHT_LN_RANGE,              /*!< Light Lightness Range*/
    MESH_STATE_LIGHT_LN_RANGE_MIN,          /*!< Light Lightness Range Min*/
    MESH_STATE_LIGHT_LN_RANGE_MAX,          /*!< Light Lightness Range Max*/

    MESH_STATE_LIGHT_CTL_LN = 100,          /*!<  Light CTL Lightness*/
    MESH_STATE_LIGHT_CTL_TEMP,              /*!< Light CTL Temperature*/
    MESH_STATE_LIGHT_CTL_DELTA_UV,          /*!< Light CTL Delta UV*/
    MESH_STATE_LIGHT_CTL_TEMP_DFLT,         /*!< Light CTL Temperature Default*/
    MESH_STATE_LIGHT_CTL_TEMP_RANGE,        /*!< Light CTL Temperature Range*/
    MESH_STATE_LIGHT_CTL_DELTA_UV_DFLT,     /*!< Light CTL Delta UV Default*/

    MESH_STATE_LIGHT_HSL_LN = 150,          /*!< Light HSL Lightness*/
    MESH_STATE_LIGHT_HSL_HUE,               /*!< Light HSL Hue*/
    MESH_STATE_LIGHT_HSL_SAT,               /*!< Light HSL Saturation*/
    MESH_STATE_LIGHT_HSL_TGT,               /*!< Light HSL Target*/
    MESH_STATE_LIGHT_HSL_DFLT,              /*!< Light HSL Default (Lightness + Hue + Saturation)*/
    MESH_STATE_LIGHT_HSL_DFLT_LN,           /*!<  Light HSL Lightness Default*/
    MESH_STATE_LIGHT_HSL_DFLT_HUE,          /*!< Light HSL Hue Default*/
    MESH_STATE_LIGHT_HSL_DFLT_SAT,          /*!< Light HSL Saturation Default*/
    MESH_STATE_LIGHT_HSL_RANGE_HUE,         /*!< Light HSL Hue Range*/
    MESH_STATE_LIGHT_HSL_RANGE_SAT,         /*!< Light HSL Saturation Range*/

    MESH_STATE_LIGHT_XYL_LN = 200,          /*!< Light xyL Lightness*/
    MESH_STATE_LIGHT_XYL_XY,                /*!< Light xyL x and y*/
    MESH_STATE_LIGHT_XYL_LN_TGT,            /*!< Light xyL Lightness Target*/
    MESH_STATE_LIGHT_XYL_XY_TGT,            /*!< Light xyL x and y Target*/
    MESH_STATE_LIGHT_XYL_LN_DFLT,           /*!< Light xyL Lightness Default*/ 
    MESH_STATE_LIGHT_XYL_XY_DFLT,           /*!< Light xyL x and y Default*/ 
    MESH_STATE_LIGHT_XYL_XY_RANGE,           /*!< Light xyL x and y Range*/ 

    MESH_STATE_SCENE_RECALL_SCENE_NUM =250,  /*!< Recall Scene num*/
    MESH_STATE_SCENE_STORE_SCENE_NUM,        /*!< Store Scene num*/
    MESH_STATE_SCENE_DELETE_SCENE_NUM,       /*!< Delete Scene num*/
    MESH_STATE_SCENE_GET_STATUS,             /*!< Get Scene status*/
    MESH_STATE_SCENE_REGISTER_GET_STATUS,    /*!< Get Register Scene status*/
};

/**
  * @brief  The Receive window factor values are used in the friend offer delay calculation 
  */
enum lpn_rx_window_factor
{
    LPN_RX_WINDOW_FACTOR_1   = 0,          /*!< ReceiveWindowFactor 1*/ 
    LPN_RX_WINDOW_FACTOR_1_5,              /*!< ReceiveWindowFactor 1.5*/ 
    LPN_RX_WINDOW_FACTOR_2,                /*!< ReceiveWindowFactor 2*/ 
    LPN_RX_WINDOW_FACTOR_2_5,              /*!< ReceiveWindowFactor 2.5*/ 
};


/**
  * @brief  The contribution of the RSSI measured by the Friend node used in Friend Offer Delay calculations 
  */
enum lpn_rssi_factor
{
    LPN_RSSI_FACTOR_1   = 0,              /*!< RSSIFactor 1*/ 
    LPN_RSSI_FACTOR_1_5,                  /*!< RSSIFactor 1.5*/ 
    LPN_RSSI_FACTOR_2,                    /*!< RSSIFactor 2*/ 
    LPN_RSSI_FACTOR_2_5,                  /*!< RSSIFactor 2.5*/ 
};

/**
  * @brief  The minimum number of messages that the Friend node can store in its Friend Queue, the min queue size log field is defiendd as log2(Nx). 
  */
enum friend_node_min_queue_size_log
{
    FRIEND_NODE_MIN_QUEUE_SIZE_LOG_PROHIB = 0,   /*!< Prohibited*/
    FRIEND_NODE_MIN_QUEUE_SIZE_LOG_N2,           /*!< At least 1 message is stored in the friend queue*/
    FRIEND_NODE_MIN_QUEUE_SIZE_LOG_N4,           /*!< At least 2 messages are stored in the friend queue*/
    FRIEND_NODE_MIN_QUEUE_SIZE_LOG_N8,           /*!< At least 3 messages are stored in the friend queue*/
    FRIEND_NODE_MIN_QUEUE_SIZE_LOG_N16,          /*!< At least 4 messages are stored in the friend queue*/
    FRIEND_NODE_MIN_QUEUE_SIZE_LOG_N32,          /*!< At least 5 messages are stored in the friend queue*/
    FRIEND_NODE_MIN_QUEUE_SIZE_LOG_N64,          /*!< At least 6 messages are stored in the friend queue*/
    FRIEND_NODE_MIN_QUEUE_SIZE_LOG_N128,         /*!< At least 7 messages are stored in the friend queue*/
};

enum scene_status_code_
{
    SCENE_STATUS_CODE_SUCCESS    =0x00,
    SCENE_STATUS_CODE_REG_FULL   =0x01,
    SCENE_STATUS_CODE_NOT_FOUND  =0x02,
    SCENE_STATUS_CODE_RESERVED   =0x03
}; 

/**
  * @brief Device state information struct
  */
struct report_dev_provisioned_state_info
{
    uint8_t proved_state;                     /*!<  enum mesh_provisioned_state*/  
    uint8_t proving_success_state;            /*!<  enum mesh_provisioning_result */
};

/**
  * @brief Authentication values struct
  */
struct mesh_prov_info
{
    uint8_t DevUuid[UUID_MESH_DEV_LEN];     /*!< device uuid*/ 
    uint32_t UriHash;                       /*!< Supported URI-Hash types*/ 
    uint16_t OobInfo;                       /*!< OOB information*/
    uint8_t PubKeyOob;                      /*!< Supported public key types*/ 
    uint8_t StaticOob;                      /*!< Supported Static OOB types*/
    uint8_t OutOobSize;                     /*!< Maximum size in octets of Output OOB supported*/
    uint8_t InOobSize;                      /*!< Maximum size in octets of Input OOB supported*/
    uint16_t OutOobAction;                  /*!< Supported Output OOB Actions*/
    uint16_t InOobAction;                   /*!< Supported Input OOB Actions*/
    uint8_t Info;                           /*!< Bit field providing additional information*/
}__attribute__((packed));

/**
  * @brief Authentication information struct
  */
struct mesh_prov_auth_info
{
    uint8_t Adopt;                           /*!< Accept pairing request, 0 reject*/
    uint8_t AuthSize;                        /*!< authentication size*/
    uint8_t AuthBuffer[MESH_AUTH_DATA_LEN];  /*!< authentication value*/
};
/**
  * @brief Attention state
  */
struct report_mesh_attention_info
{
    uint8_t state;
};

/**
  * @brief Report updated state struct
  */
struct update_state_info
{
    uint8_t upd_type;                  /*!< The state type of the update*/
    uint8_t len;                       /*!< data lenght*/
    uint8_t data[__LSSIGMESH_EMPTY];   /*!< data*/
};

/**
  * @brief Send messages struct
  */
struct model_send_info
{
    uint8_t ModelHandle;                /*!< Client Model local index*/
    uint8_t app_key_lid;                /*!< App key local index*/
    uint16_t dest_addr;                 /*!< Destination address*/
    uint32_t opcode;                    /*!< Message opcode*/
    uint16_t len;                       /*!< Message length*/
    uint8_t info[MAX_MESH_MODEL_MSG_BUFFER]; /*!< Message */
};
/**
  * @brief Publish message struct -for Client Vendor model
  */
struct vendor_model_publish_message
{
    uint8_t ModelHandle;                 /*!< Client Model local index*/
    uint8_t TxHandle;                    /*!< Message transmiter number*/
    uint32_t MsgOpcode;                  /*!< Message opcode*/
    uint16_t MsgLength;                  /*!< Message length*/
    uint8_t msg[MAX_MESH_MODEL_MSG_BUFFER];  /*!< Message */
}__attribute__((packed));
/**
  * @brief Set state message structure - for Client SIG model
  */
struct model_cli_set_state_info
{
    uint32_t state_1;                    /*!< state1*/ 
    uint32_t state_2;                    /*!< state1*/ 
    uint16_t dest_addr;                  /*!< Destination address*/ 
    uint16_t set_info;                   /*!< Set information*/
    uint8_t mdl_lid;                     /*!< Client Model local index*/
    uint8_t app_key_lid;                 /*!< App key local index*/
};
/**
  * @brief Start transition to a new state message structure - for Client SIG model
  */
struct model_cli_trans_info
{
    uint32_t state_1;                   /*!< Model state1*/ 
    uint32_t state_2;                   /*!< Model state2*/
    uint32_t trans_time_ms;             /*!< Transition time in milliseconds*/
    uint16_t trans_info;                /*!< Transition information*/
    uint16_t dest_addr;                 /*!< Destination address*/ 
    uint16_t delay_ms;                  /*!< Delay in milliseconds*/
    uint8_t mdl_lid;                    /*!< Client Model local index*/
    uint8_t app_key_lid;                /*!< App key local index*/
};

/**
  * @brief  Request parameter structure - for genie lower power
  */
struct start_glp_info
{
    uint8_t RxDelyMs;                  /*!< rx delay at least 10ms*/
    uint16_t SleepIntvlMs;             /*!< rx delay at least 10ms*/
}__attribute__((packed));
/**
  * @brief Request parameter structure - for lower power node
  */
struct start_lpn_info
{
    uint8_t rx_window_factor;        /*!<  enum lpn_rx_window_factor*/
    uint8_t min_queue_size_log;      /*!<  enum enum friend_node_min_queue_size_log*/
    uint8_t rx_delay_ms;             /*!< rx delay at least 10ms*/
    uint16_t previous_addr;          
    uint32_t poll_timeout_100ms;     /*!< poll timeout at least 1s*/ 
    uint32_t poll_intv_ms;           /*!< poll interval*/
}__attribute__((packed));
/**
  * @brief Report friend node parameter structure - for lower power node
  */
 struct lpn_offer_info
{
    uint16_t friend_addr;             /*!< friend node unicast address*/
    uint8_t  friend_rx_window;        /*!< friend node rx window*/
    uint8_t  friend_queue_size;       /*!< friend queue size, enum friend_node_min_queue_size_log*/
    uint8_t  friend_subs_list_size;   /*!< friend subscription list size*/
    int8_t   friend_rssi;             /*!< friend node rssi*/
};
/**
  * @brief Report friendship status structure - for lower power node
  */
struct lpn_status_info
{
    uint16_t lpn_status;              /*!< Friendship status*/       
    uint16_t friend_addr;             /*!< friend node unicast_addr*/
};
/**
  * @brief Receive message structure from other nodes
  */
struct model_rx_info
{
    uint8_t ModelHandle;              /*!< Model local index*/
    uint8_t app_key_lid;              /*!< App Key local index*/
    int8_t rssi;                      /*!< rssi of message*/
    uint16_t source_addr;             /*!< source_addr of message*/
    uint8_t not_relayed;              /*!<True if message have been received by an immediate peer;False, it can have been relayed.*/       
    uint32_t opcode;                  /*!< Operation code*/
    uint16_t rx_info_len;             /*!< message length*/
    uint8_t info[__LSSIGMESH_EMPTY];  /*!< message*/
};

/**
  * @brief State update indication structure for SIG Model
  */
struct model_state_upd
{
    uint8_t elmt_idx;                /*!< Element index*/
    uint16_t state_id;               /*!< State identifier,  num mesh_state_idx*/
    uint32_t state;                  /*!<  New state value or targeted state value depending on transition time*/
    uint32_t trans_time_ms;          /*!<  Transition time in milliseconds*/
};
/**
  * @brief Report provisioning state
  */
struct report_mesh_prov_result_info
{
    uint8_t state;                   /*!< Provisioning  state , enum mesh_provisioning_result*/
    uint16_t status;                 /*!< Provisioning failed reason*/
};
/**
  * @brief Report mesh timer state
  */
struct report_mesh_timer_state_info
{
    uint8_t timer_id;               /*!< mesh timer index*/
    uint8_t status;                 /*!< mesh timer status,  enum mesh_timer_state*/
};
/**
  * @brief Registered Model inforation structure for model
  */
struct model_id_info
{
    uint8_t element_id;             /*!< Element index*/
    uint8_t model_lid;              /*!< Model local index*/
    uint8_t vendor_model_role;      /*!< Vendor Model Server or Client*/
    uint16_t sig_model_cfg_idx;     /*!< Config Index for Sig Model*/
    uint16_t vendor_model_cfg_idx;  /*!< Config Index for Vendor Model*/
    uint32_t model_id;              /*!<  Model Index*/
}__attribute__((packed));
/**
  * @brief Registered Model all informations structure for node
  */
struct mesh_model_info
{
    uint8_t nb_model;                                /*!< Total registered Model*/
    uint8_t app_key_lid;                             /*!< App key loacal index*/
    struct model_id_info info[MAX_MESH_MODEL_NB];    /*!< Maximum models in a node  struct model_id_info*/ 
};

/**
  * @brief Report new publication parameters for a model
  */
struct mesh_publish_info_ind
{
    uint8_t  model_lid;            /*!< Model local index*/
    uint32_t period_ms;            /*!< Publish period in milliseconds*/
    uint16_t addr;                 /*!< Publication address*/
};

/**
  * @brief Auto provisioning information for model
  */
struct mesh_auto_prov_model_info
{
    bool publish_flag;            /*!< Enable Publish function*/
    bool subs_flag;               /*!< Enable Subscript function*/
    uint32_t model_id;            /*!<  Model Index*/
}__attribute__((packed));
/**
  * @brief Auto provisioning information for node
  */
struct mesh_auto_prov_info
{
    uint16_t unicast_addr;        /*!< unicast address*/
    uint8_t model_nb;             /*!< Total registered Model*/
    uint8_t ttl;                  /*!< time to live for publish*/
    uint16_t group_addr;          /*!< Group address for publish and subscription*/
    struct mesh_auto_prov_model_info model_info[MAX_MESH_MODEL_NB];  /*!< Maximum models in a node  struct mesh_auto_prov_model_info*/ 
    uint8_t app_key[16];          /*App key*/
    uint8_t net_key[16];          /*Net key*/
}__attribute__((packed));

/**
  * @brief Sig Mesh event union definition.
  */
union ls_sig_mesh_evt_u {
    struct report_dev_provisioned_state_info st_proved;            /*!< Device state information,  struct report_dev_provisioned_state_info*/
    struct report_mesh_attention_info update_attention;            /*!< Attention state, struct report_mesh_attention_info*/
    struct report_mesh_prov_result_info prov_rslt_sate;            /*!< Report provisioning state,  struct report_mesh_prov_result_info*/
    struct model_rx_info rx_msg;                                   /*!< Receive message structure from other nodes,  struct model_rx_info*/
    struct update_state_info update_state_param;                   /*!< Report updated state struct,  struct update_state_info*/
    struct report_mesh_timer_state_info mesh_timer_state;          /*!< Report mesh timer state,  struct report_mesh_timer_state_info*/
    struct adv_report_evt adv_report;                              /*!< Report adv information,  struct adv_report_evt*/
    struct model_state_upd mdl_state_upd_ind;                      /*!< State update indication structure for SIG Model,  struct model_state_upd*/
    struct mesh_model_info sig_mdl_info;                           /*!< Registered Model all informations structure for node,  struct mesh_model_info*/
    struct mesh_publish_info_ind mesh_publish_info;                /*!< Report new publication parameters for a model,  struct mesh_publish_info_ind*/
    struct mesh_auto_prov_info mesh_auto_prov_param;               /*!< Auto provisioning information for node,  struct mesh_auto_prov_info*/
    struct lpn_offer_info lpn_offer_info;                          /*!< Report friend node parameter structure - for lower power node,  struct lpn_offer_info*/
    struct lpn_status_info lpn_status_info;                        /*!< Report friendship status structure - for lower power node,  struct lpn_status_info*/
};
/**
  * @brief Sig Mesh initial parameter.
  */
struct ls_sig_mesh_cfg
{
    uint32_t MeshFeatures;            /*!< Features supported by nodes, enum mesh_feature*/
    uint16_t MeshCompanyID;           /*!< CompanyID supported by SIG */
    uint16_t MeshProID;               /*!< Production ID */
    uint16_t MeshProVerID;            /*!< Production Version ID */
    uint16_t MeshLocDesc;             /*!<user-defined */  
    uint16_t NbAddrReplay;            /*!<Number of relay node support for replay attrack*/ 
    uint8_t NbCompDataPage;           /*!< Page number of composition data*/
    uint8_t FrdRxWindowMS;            /*!< Rx Windows of friend node*/ 
    uint8_t FrdQueueSize;             /*!< QueueCache size of friend node*/
    uint8_t FrdSubsListSize;          /*!< Subscript List size of friend node*/
};
/**
  * @brief Restart beacon parameter of device.
  */
struct bcn_start_unprov_param
{
    uint8_t DevUuid[UUID_MESH_DEV_LEN];       /*!< uuid of device*/  
    uint16_t OobInfo;                         /*!< OOB information*/
    uint32_t UriHash;                         /*!< URI-Hash information*/
    bool UriHash_Present;                     /*!< Support or not*/
}__attribute__((packed));
/**
 * @brief  Initialization Event Callback of Sig mesh.
 * 
 * @param evt_cb    Callback function to handle all sig mesh messages.
 */
void prf_ls_sig_mesh_callback_init(void (*evt_cb)(enum mesh_evt_type, union ls_sig_mesh_evt_u *));
/**
 * @brief Add Sig mesh profile to dev manager 
 * 
 * @param sec_lvl  No security
 * @param cfg      Node Suported Feature, struct ls_sig_mesh_cfg
 */
void dev_manager_prf_ls_sig_mesh_add(uint8_t sec_lvl, struct ls_sig_mesh_cfg *cfg);
/**
 * @brief Initialization of Sig mesh.
 * 
 * @param param  Register Model informatin, struct mesh_model_info
 */
void ls_sig_mesh_init(struct mesh_model_info *param);
/**
 * @brief Set the prov parameter
 * 
 * @param param struct mesh_prov_info 
 */
void set_prov_param(struct mesh_prov_info *param);
/**
 * @brief Set the prov auth parameter
 * 
 * @param param struct mesh_prov_auth_info 
 */
void set_prov_auth_info(struct mesh_prov_auth_info *param);
/**
 * @brief Subscribe group address for model
 * 
 * @param ModelHandle model local id
 * @param Addr  group address
 */
void model_subscribe(uint8_t const ModelHandle, uint16_t const Addr);
/**
 * @brief unsubscribe group address for model
 * 
 * @param ModelHandle model local id
 * @param Addr  group address
 */
void model_unsubscribe(uint8_t const ModelHandle, uint16_t const Addr);
/**
 * @brief delete all information about Subscription for model
 * 
 * @param ModelHandle model local id
 */
void model_unsubscribe_all(uint8_t  ModelHandle);
/**
 * @brief publish group address and set parameters for model
 * @param ModelHandle model local id
 * @param Addr  group address
 * @param virtual_uuid Virtual address you should set NULL when group address be set 16bits
 * @param app_key_lid  app_key local index 
 * @param publish_ttl        time to live for publish message 
 * @param publish_period     period transmit for publish message
 * @param publish_retransimit     Number of transmissions of published messages
 * @param friendship_cred_flag    jush for friendship
 * 
 */
void model_set_publication(uint8_t  ModelHandle, uint16_t Addr, uint8_t *virtual_uuid, uint8_t app_key_lid, uint8_t publish_ttl, uint8_t publish_period, uint8_t publish_retransimit,uint8_t friendship_cred_flag);

/**
 * @brief  Get all subscript address from subscribe_list
 * 
 * @param ModelHandle model local id
 * @param add_list    application list
 * @param uuid_flag   get uuid flag 
 */
void model_get_subscribe_list(uint8_t  ModelHandle, uint8_t *add_list, bool uuid_flag);
/**
 * @brief Get size from subscribe_list
 * 
 * @param ModelHandle model local id
 * @return uint16_t   listSize
 */
uint16_t  model_get_subscribe_listSize(uint8_t  ModelHandle);
/**
 * @brief Get primary address to Node
 * 
 * @return uint16_t 
 */
uint16_t  ls_sig_mesh_get_primary_address(void);
/**
 * @brief User send  message to other nodes by Vendor Client Model
 * 
 * @param param  struct model_send_info
 */
void model_send_info_handler(struct model_send_info *param);
/**
 * @brief Set state to other nodes by Sig Client Model
 * 
 * @param param struct model_cli_set_state_info
 */
void mesh_model_client_set_state_handler(struct model_cli_set_state_info *param);
/**
 * @brief Publish message to other nodes by by Sig Client Model
 * 
 * @param param  struct model_cli_trans_info
 */
void mesh_standard_model_publish_message_handler(struct model_cli_trans_info *param);
/**
 * @brief Publish message to other nodes by by Vendor Client Model,but Cann't set dest address
 * 
 * @param msg  struct vendor_model_publish_message
 */
void mesh_vendor_model_publish_message_handler(struct vendor_model_publish_message *msg);
/**
 * @brief Set mesh timer
 * 
 * @param TimerID 
 * @param DelayMS
 */
void TIMER_Set(uint8_t TimerID, uint32_t DelayMS);
/**
 * @brief  Delete mesh timer
 * 
 * @param TimerID
 */
void TIMER_Cancel(uint8_t TimerID);
/**
 * @brief  Clear all provisioned information, a node beacoms a device
 * 
 */
void SIGMESH_UnbindAll(void);
/**
 * @brief  Device stop unprov beacon 
 * 
 */
void stop_tx_unprov_beacon(void);
/**
 * @brief Device start unprov beacon
 * 
 * @param param struct bcn_start_unprov_param
 */
void start_tx_unprov_beacon(struct bcn_start_unprov_param *param);
/**
 * @brief Set_scan_rsp_data for genie mesh gatt
 * 
 * @param scan_rsp_data
 * @param scan_rsp_data_len
 */
void ls_sig_mesh_con_set_scan_rsp_data(uint8_t *scan_rsp_data, uint8_t *scan_rsp_data_len);
/**
 * @brief Enable Gatt mesh function and Start connectable adv
 * 
 */
void start_ls_sig_mesh_gatt(void);
/**
 * @brief Disable Gatt mesh function and Stop connectable adv
 * 
 */
void stop_ls_sig_mesh_gatt(void);
/**
 * @brief Enable/Disable Proxy adv
 * 
 * @param enable
 */
void ls_sig_mesh_proxy_adv_ctl(uint8_t enable);
/**
 * @brief Enable lower power for genie mesh
 * 
 * @param param struct start_glp_info
 */
void start_glp_handler(struct start_glp_info *param);
/**
 * @brief Disable lower power for genie mesh
 * 
 */
void stop_glp_handler(void);
/**
 * @brief Enable lower power for lpn
 * 
 * @param param
 */
void start_lpn_handler(struct start_lpn_info *param);
/**
 * @brief Disable lower power for lpn
 * 
 */
void stop_lpn_handler(void);
/**
 * @brief Disable Sig mesh function
 * 
 */
void ls_sig_mesh_disable(void);
/**
 * @brief Enable Sig mesh function
 * 
 */
void ls_sig_mesh_enable(void);
/**
 * @brief  Select friend node for LPN
 * 
 * @param friend_addr
 */
void lnp_select_friend_handler(uint16_t friend_addr);
/**
 * @brief Enable Auto Provisioning process
 * 
 * @param param struct mesh_auto_prov_info
 * @param auto_prov_mesh_flag  Enable/Disable Flag
 */
void ls_sig_mesh_auto_prov_handler(struct mesh_auto_prov_info const *param, bool const auto_prov_mesh_flag);
/**
 * @brief update iv_seq by manual for auto provisioning mode
 * 
 *  * @param seq_offset  set offset of seqence number by length of message
 */
void ls_sig_mesh_auto_prov_update_ivseq_handler(uint32_t seq_offset);
/**
 * @brief Report unicast_address of provisioner
 * 
 * @param unicast_address
 */
void report_provisioner_unicast_address_ind(uint16_t unicast_address);
/**
 * @brief Set Connectable Adv interval for proxy node
 * 
 * @param interval_ms
 */
void ls_sig_mesh_set_proxy_con_interval(uint16_t *interval_ms);
/**
 * @brief Set Connectable Adv interval for device
 * 
 * @param interval_slot
 */
void ls_sig_mesh_set_pb_gatt_con_interval(uint16_t *interval_slot);
/**
 * @brief Inform Application about send status of foundation model config server
 * 
 * @param opcode
 * @param status
 */
void prov_foundation_mdl_cfg_svr_rsp(uint32_t opcode,uint16_t status);

/** @} */

#endif //(_LS_SIG_MESH_H_
