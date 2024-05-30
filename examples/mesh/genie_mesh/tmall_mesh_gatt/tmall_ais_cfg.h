#ifndef __TMALL_AIOTS_CFG__
#define __TMALL_AIOTS_CFG__
#include <stdint.h>

#define ALI_CID_LENGTH   2
#define ALI_PID_LENGTH   4
#define ALI_MAC_LENGTH   6
#define ALI_KEY_LENGTH   16
#define ALI_STR_PID_LENGTH   8
#define ALI_STR_MAC_LENGTH   12
#define ALI_STR_KEY_LENGTH   32

#define PRODUCT_ID_LENGTH   4
#define DEVICE_MAC_LENGTH   6

#define AD_TYPE_UUID16                 0x02
#define AD_STRUCT_UU16_DATA_LEN        0x02
#define AD_TYPE_MANU_SPEC_DATA         0xFF
#define ALI_COMPANY_ID_LSB             0xa8
#define ALI_COMPANY_ID_MSB             0x01
#define MANU_SPEC_DATA_LEN             0x0f

enum SUBTYPE
{
    SUBTY_BLE_GATT_MESH =0x8,
    SUBTYPE_BLE_BEACON = 0x9,
    SUBTYPE_BLE_AUDIO  = 0xa,
    SUBTYPE_BLE_GATT   = 0xb,
};

struct tmall_aiot_adv_data
{
    uint8_t length;
    uint8_t type;
    uint8_t cid[ALI_CID_LENGTH];
    union 
    {
        struct
        {
            uint8_t vid    :4;
            uint8_t subtype:4;   //enum SUBTYPE
        }b;
        uint8_t ubyte;
    }aiot_info;

    union 
    {
        struct 
        {
            uint8_t   ble_version     :2;
            uint8_t   ota_option      :1;
            uint8_t   security_option :1;
            uint8_t   security_mode   :1;
            uint8_t   adv_mode        :1;
            uint8_t   reserved        :2;
        }b;
        uint8_t ubyte;
    }fmsk;
    
    uint8_t pid[PRODUCT_ID_LENGTH];
    uint8_t mac[DEVICE_MAC_LENGTH];
};
#endif //__TMALL_AIOTS_CFG__
