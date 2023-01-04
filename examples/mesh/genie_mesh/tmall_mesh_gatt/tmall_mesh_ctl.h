#ifndef TMALL_MESH_CTL_H_
#define TMALL_MESH_CTL_H_
#include "ls_ble.h"
#include "ls_sig_mesh.h"
#include "tinyfs.h"

#define MESH_VENDOR_ASKING_ATTR             0x0001A8de
#define MESH_VENDOR_ASKING_ATTR_RET         0x0001A8df

#define VENDOR_ATTR_TYPE_LEVEL              0x010A
#define VENDOR_ATTR_TYPE_EVENT              0xF009
#define VENDOR_ATTR_TYPE_SET_STEP           0xF00B
#define VENDOR_ATTR_TYPE_TIME_ON_SET        0xF010
#define VENDOR_ATTR_TYPE_TIME_ON_REPORT     0xF011
#define VENDOR_ATTR_TYPE_TIME_OFF           0xF012
#define VENDOR_ATTR_TYPE_DIRECTION          0x0521
#define VENDOR_ATTR_TYPE_ONOFF              0x0100
#define VENDOR_ATTR_TYPE_SECONDARY_ONOFF    0x0124
#define VENDOR_ATTR_TYPE_THIRD_ONOFF        0x0125

#define VENDOR_ATTR_TYPE_WORK_STATUS        0xF001
#define VENDOR_ATTR_SCENE_MODEL			    0xF004

#define VENDOR_ATTR_TYPE_SET_UNIX           0xF01F
#define VENDOR_ATTR_TYPE_SET_TIMEZONE       0xF01E
#define VENDOR_ATTR_TYPE_DEL_TIMER          0xF012
#define VENDOR_ATTR_TYPE_SET_TIMER          0xF010
#define VENDOR_ATTR_TYPE_SET_PERIOD_TIMER   0xF011

#define VENDOR_ATTR_TYPE_workSwitch			0x0135
#define VENDOR_ATTR_TYPE_lefttime	        0x012f
#define VENDOR_ATTR_TYPE_localRecipe	    0x0571
#define VENDOR_ATTR_TYPE_workstatus			0xf001
#define VENDOR_ATTR_TYPE_runTime			0x012d
#define VENDOR_ATTR_TYPE_ReserveLeftTime	0x0550
#define VENDOR_ATTR_TYPE_stirringSpeed		0x015a
#define VENDOR_ATTR_TYPE_holdingTemp		0x015b
#define VENDOR_ATTR_TYPE_errorCode			0x0000

#define RECORD_PRESET_SCENCE_BASE			0X2710		//10000
#define RECORD_PRESET_SCENCE_NUM			9
#define RECORD_CONFIG_SCENCE_BASE			0X2774		//10100
#define RECORD_CONFIG_SCENCE_NUM			24
extern uint16_t mesh_key_lid;

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

struct scene_recall_messge
{
   uint16_t scene_number;
   uint8_t tid;
   uint8_t trans_time;
   uint8_t delay;
}__attribute__((packed));

//Scene status message
struct scene_staus_message
{
    uint8_t status_code;
    uint16_t current_scene;
    uint16_t target_scene;
    uint8_t remaining_time;  
}__attribute__((packed));;

//Scene register status message
struct scene_register_staus_message
{
    uint8_t status_code;
    uint16_t current_scene;
    uint8_t scenes[10];
}__attribute__((packed));


//Scene register status message
struct scene_store_message
{
    uint16_t scene_number;
    uint8_t vendor_model;
	uint16_t type_curtainctrl;
	uint8_t parameter_curtainctrl[6];
}__attribute__((packed));

//Scene register status message
struct scene_delete_message
{
    uint16_t scene_number;
};
void mesh_send_custom_adv(uint16_t duration,uint8_t *adv_data,uint8_t adv_data_length);
void tmall_mesh_recv_onoff_msg(struct model_rx_info *info);
void tmall_mesh_recv_vendor_msg(struct model_rx_info *info);
void tmall_mesh_recv_lightness_msg(struct model_rx_info *info);
void tmall_mesh_recv_light_ctl_msg(struct model_rx_info *msg);
void tmall_mesh_recv_light_hsl_msg(struct model_rx_info *msg);
void exti_gpio_init(void);
void tmall_mesh_recv_scene_msg(struct model_rx_info *info);
#endif
