#ifndef PRF_ANCS_H_
#define PRF_ANCS_H_
#include <stdint.h>

#define ANC_APP_ID_MAX_LENGTH 32

#define ANCS_DB_SIZE 26

/// Category ID Values
enum
{
    /// Other
    CAT_ID_OTHER             = 0,
    /// Incoming Call
    CAT_ID_CALL              = 1,
    /// Missed Call
    CAT_ID_MISSED_CALL       = 2,
    /// Voice Mail
    CAT_ID_VOICE_MAIL        = 3,
    /// Social network
    CAT_ID_SOCIAL            = 4,
    /// Schedule
    CAT_ID_SCHEDULE          = 5,
    /// Email
    CAT_ID_EMAIL             = 6,
    /// News Feed
    CAT_ID_NEWS              = 7,
    /// Health and Fitness
    CAT_ID_HEALTH_FITNESS    = 8,
    /// Business and Finance
    CAT_ID_BUSINESS_FINANCE  = 9,
    /// Location
    CAT_ID_LOCATION          = 10,
    /// Entertainment
    CAT_ID_ENTERTAINMENT     = 11,

    CAT_ID_NB,

    /// All supported categories
    CAT_ID_ALL_SUPPORTED_CAT = 255,
};

/// Event ID Values
enum
{
    /// Notification Added
    EVT_ID_NTF_ADDED        = 0,
    /// Notification Modified
    EVT_ID_NTF_MODIFIED     = 1,
    /// Notification Removed
    EVT_ID_NTF_REMOVED      = 2,

    EVT_ID_NB,

    EVT_ID_ALL_SUPPORTED_EVT = 255,
};

/// Event Flags
enum
{
    /// Silent
    EVT_FLAG_SILENT                 = (1 << 0),
    /// Important
    EVT_FLAG_IMPORTANT              = (1 << 1),

    //pre existing
	EVT_FLAG_PRE_EXISTING           = (1 << 2),

	//position action
	EVT_FLAG_POSITIVE_ACTION        = (1 << 3),

	//Negative action
	EVT_FLAG_NEGATIVE_ACTION        = (1 << 4),

    EVT_FLAG_NB,

    EVT_FLAG_ALL_SUPPORTED_EVT_FLAG = (1 << 7),
};

/// Command ID Values
enum
{
    /// Get Notification Attributes
    CMD_ID_GET_NTF_ATTS      = 0,
    /// Get App Attributes
    CMD_ID_GET_APP_ATTS      = 1,

    CMD_ID_PERFORM_NTF_ACTION = 2,
    
    CMD_ID_NB,

    /// All supported commands
    CMD_ID_ALL_SUPPORTED_CMD = 255,
};

/// Notification Attribute ID Values
enum
{
    /// App Identifier
    NTF_ATT_ID_APP_ID        = 0,
    /// Title (Needs to be followed by a 2-bytes max length parameter)
    NTF_ATT_ID_TITLE         = 1,
    /// Subtitle (Needs to be followed by a 2-bytes max length parameter)
    NTF_ATT_ID_SUBTITLE      = 2,
    /// Message (Needs to be followed by a 2-bytes max length parameter)
    NTF_ATT_ID_MSG           = 3,
    /// Message Size
    NTF_ATT_ID_MSG_SIZE      = 4,
    /// Date
    NTF_ATT_ID_DATE          = 5,

    NTF_ATT_ID_POS_ACTION_LABEL = 6,
    
    NTF_ATT_ID_NEG_ACTION_LABEL = 7,
    
    NTF_ATT_ID_NB,

    /// All supported Notification Attributes
    NTF_ATT_ID_ALL_SUPPORTED_NTF_ATT = 255,
};


/// App Attribute ID Values
enum
{
    /// Display Name present
    APP_ATT_ID_DISPLAY_NAME  = 0,
    
    APP_ATT_ID_NB,

    /// All supported App Attributes
    APP_ATT_ID_ALL_SUPPORTED_APP_ATT = 255,
};

// App Attribute Bit Mask Flags
enum
{
    /// App Identifier
    APP_ATT_ID_DISPLAY_NAME_PRESENT  = 0x01,
    
};

// ActionID Values
enum
{
    ACT_ID_POSITIVE = 0,
    ACT_ID_NEGATIVE
};

/// Notification Source Characteristic Value Structure
struct ancs_ntf_src
{
    /// Event ID
    uint8_t event_id;

    /// Event Flags
    uint8_t event_flags;

    /// Category ID
    uint8_t cat_id;

    /// Category Count: Number of active notifications in the given category
    uint8_t cat_cnt;

    /// Notification UID
    uint32_t ntf_uid;
};

typedef struct
{
    uint8_t str[ANC_APP_ID_MAX_LENGTH];
}ancs_app_id_t;

typedef union
{
    ancs_app_id_t app_id;
    uint32_t ntf_uid;
}ancs_id_u;

struct ancs_att_ind
{
    ancs_id_u id;
    uint16_t length;
    uint8_t att_id;
    uint8_t val[];
};

enum ancs_evt_type
{
    ANCS_ENABLE_RSP,
    ANCS_CLIENT_CONFIGURATION_ENABLED,
    ANCS_CLIENT_CONFIGURATION_DISABLED,
    ANCS_NOTIFICATION_SOURCE,
    ANCS_NOTIFICATION_ATTRIBUTES_REPORT,
    ANCS_NOTIFICATION_ATTRIBUTES_COMPLETE,
    ANCS_APP_ATTRIBUTES_REPORT,
    ANCS_APP_ATTRIBUTES_COMPLETE,
    ANCS_PERFORM_NOTIFICATION_ACTION_COMPLETE,
};

struct ancs_enable_rsp_evt
{
    void *ancs_db;
    uint8_t status;
};

union ancs_evt_u
{
    struct ancs_enable_rsp_evt enable_rsp;
    struct ancs_ntf_src *ntf_src;
    struct ancs_att_ind *ntf_atts_report;
    struct ancs_att_ind *app_atts_report;
};

void dev_manager_prf_ancs_add(uint8_t sec_lvl);

void prf_ancs_callback_init(void (*cb)(enum ancs_evt_type,union ancs_evt_u *,uint8_t));

void prf_ancs_enable_req(uint8_t con_idx,void *ancs_db);

void prf_ancs_get_notification_attributes(uint8_t con_idx,uint32_t ntf_uid,uint16_t att_mask,uint16_t title_length,uint16_t subtitle_length,uint16_t message_length);

void prf_ancs_get_app_attributes(uint8_t con_idx,uint8_t *app_id,uint8_t att_mask);

void prf_ancs_perform_notfication_action(uint8_t con_idx,uint32_t ntf_uid,uint8_t action_id);

void prf_ancs_client_configuration_enable(uint8_t con_idx);

void prf_ancs_client_configuration_disable(uint8_t con_idx);

#endif
