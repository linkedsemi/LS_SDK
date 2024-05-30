#ifndef _SIG_MESH_CTL_H_
#define _SIG_MESH_CTL_H_
#include "ls_ble.h"
#include "ls_sig_mesh.h"
#include "tinyfs.h"

extern uint16_t mesh_key_lid;

/// Client Model Index
enum MESH_MDL_CLI_CFG
{
    /// ************ Generic ************
    MESH_CMDL_CFG_IDX_GENC_MIN                 = 0x100,
    /// Generic OnOff Client
    MESH_CMDL_CFG_IDX_GENC_ONOFF               = MESH_CMDL_CFG_IDX_GENC_MIN,
    /// Generic Level Client
    MESH_CMDL_CFG_IDX_GENC_LEVEL,
    /// Generic Default Transition Time Client
    MESH_CMDL_CFG_IDX_GENC_DFT_TRANS_TIME,
    /// Generic Power OnOff Client
    MESH_CMDL_CFG_IDX_GENC_POWER_ONOFF,
    /// Generic Power Level Client
    MESH_CMDL_CFG_IDX_GENC_POWER_LEVEL,
    /// Generic Battery Client
    MESH_CMDL_CFG_IDX_GENC_BATTERY,
    /// Generic Location Client
    MESH_CMDL_CFG_IDX_GENC_LOCATION,
    /// Generic Property Client
    MESH_CMDL_CFG_IDX_GENC_PROPERTY,

    /// ************ Lighting ***********

    /// Light Lightness Client
    MESH_CMDL_CFG_IDX_LIGHTC_LN                = MESH_CMDL_CFG_IDX_GENC_MIN+50,
    /// Light CTL Client
    MESH_CMDL_CFG_IDX_LIGHTC_CTL,
    /// Light HSL Client
    MESH_CMDL_CFG_IDX_LIGHTC_HSL,
    /// Light xyL Client
    MESH_CMDL_CFG_IDX_LIGHTC_XYL,
};

enum MESH_VENDORS_MDL_CFG
{
    /// ************ Vendor Server ************
    MESH_MDL_CFG_VENDORS_MIN = 0x1100,
    /// Vendor Server
    MESH_MDL_CFG_VENDORS_INFO = MESH_MDL_CFG_VENDORS_MIN,
};

enum MESH_VENDORC_MDL_CFG
{
    /// ************ Vendor Client ************
    MESH_MDL_CFG_VENDORC_MIN = 0x1200,
    /// Vendor Client
    MESH_MDL_CFG_VENDORC_INFO = MESH_MDL_CFG_VENDORC_MIN,
};


// Generic OnOff Set
struct mesh_generic_onoff_set
{
    uint8_t onoff;
    uint8_t tid;
    uint8_t ttl;
    uint8_t delay;
};

// Generic OnOff Status
struct mesh_generic_onoff_status
{
    uint8_t present_onoff;
    uint8_t target_onoff;
    uint8_t remain;
}__attribute__((packed));

// General Level Status
struct mesh_generic_level_set
{
    uint16_t level;
    uint8_t tid;
    uint8_t ttl;
    uint8_t delay;
};

// General Level Status
struct mesh_generic_level_status
{
    uint16_t current_level;
    uint16_t target_level;
    uint8_t remain;
}__attribute__((packed));

// Light HSL Set
struct mesh_hsl_model_set
{
    uint16_t lightness;
    uint16_t hue;
    uint16_t hsl_saturation;
    uint8_t tid;
    uint8_t transition_time;
    uint8_t delay;
}__attribute__((packed));

// Light HSL Status
struct mesh_hsl_model_status
{
    uint16_t hsl_lightness;
    uint16_t hsl_hue;
    uint16_t hsl_saturation;
    uint8_t remain;
} __attribute__((packed));

struct mesh_ctl_model_set
{
    uint16_t lightness;
    uint16_t temperature;
    uint16_t delta_UV;
    uint8_t tid;
    uint8_t trans_time;
    uint8_t delay;
}__attribute__((packed));

// Light CTL Status
struct mesh_ctl_model_status
{
    uint16_t current_lightness;
    uint16_t current_temperature;
    uint16_t target_lightness;
    uint16_t target_temperature;
    uint8_t remain;
} __attribute__((packed)) ;

// Vendor Model Set new
struct mesh_vendor_model_set
{
    uint8_t tid;
    uint16_t attr_type;
    uint8_t *attr_parameter;
}__attribute__((packed));

// Vendor Model Indication
struct mesh_vendor_model_indication
{
    uint8_t tid;
    uint16_t attr_type;
    uint8_t *attr_parameter;
}__attribute__((packed));

enum SIGMESH_PROVER_MODEL_DEF
{
    PROVER_MODEL0_GENERIC_ONOFF_CLI,
    PROVER_MODEL0_VENDOR_CLI,
    PROVER_MODEL0_VENDOR_SVR,
    PROVER_MODEL_MAX_NUM
};

extern struct mesh_model_info model_env;
void sig_mesh_mdl_state_upd_hdl(struct model_state_upd* msg);

/**
 * @brief 
 * 
 * @param tx_msg
 * @param dest_addr
 * @param model_id
 */
void prover_client_model_tx_message_handler(uint32_t tx_msg, uint16_t dest_addr, uint32_t model_id);
/**
 * @brief 
 * 
 * @param vendor_opcode 
 * @param model_id 
 * @param data 
 * @param data_len 
 * @param dest_address 
 */
void prover_send_message_vendor_model(uint32_t vendor_opcode, uint32_t model_id, uint8_t *data, uint8_t data_len, uint16_t dest_address);
#endif // _SIG_MESH_CTL_H_
