#define LOG_TAG "MAIN"
#include "ls_ble.h"
#include "platform.h"
#include "prf_hid.h"
#include "prf_bass.h"
#include "ls_dbg.h"
#include "cpu.h"
#include "ls_hal_uart.h"
#include "builtin_timer.h"
#include "log.h"
#include <string.h>
#include "co_math.h"
#include "ls_soc_gpio.h"
#include "SEGGER_RTT.h"   
#include "tinyfs.h"
#include "ls_hal_timer.h"
#include "co_list.h"
#include "adpcm.h"
#include "ls_hal_dmac.h"
#include "ls_hal_pdm.h"
#include "main.h"

#define APP_HID_DEV_NAME ("BLE_HID_DIC_DEMO")
#define APP_HID_DEV_NAME_LEN (sizeof(APP_HID_DEV_NAME) - 1)

/// APP_DIS_MANUFACTURER_NAME
#define APP_DIS_MANUFACTURER_NAME       ("LS_BLE")
#define APP_DIS_MANUFACTURER_NAME_LEN   (sizeof(APP_DIS_MANUFACTURER_NAME) -1)

/// System ID Value - LSB -> MSB
#define APP_DIS_SYSTEM_ID               ("\x00\x01\x02\x00\x00\x03\x04\x05")
#define APP_DIS_SYSTEM_ID_LEN           (8)

/// Model Number String Value
#define APP_DIS_MODEL_NB_STR            ("ModelNbr 0.9")
#define APP_DIS_MODEL_NB_STR_LEN        (sizeof(APP_DIS_MODEL_NB_STR) -1)

/// Serial Number
#define APP_DIS_SERIAL_NB_STR           ("LSSerialNum")
#define APP_DIS_SERIAL_NB_STR_LEN       (sizeof(APP_DIS_SERIAL_NB_STR) -1) 

/// FIRM_REV
#define APP_DIS_FIRM_REV_STR            ("LSFirmwareRev")
#define APP_DIS_FIRM_REV_STR_LEN        (sizeof(APP_DIS_FIRM_REV_STR) -1)

/// Hardware Revision String
#define APP_DIS_HARD_REV_STR           ("LSHardwareRev")
#define APP_DIS_HARD_REV_STR_LEN       (sizeof(APP_DIS_HARD_REV_STR) -1)

/// Software Revision String
#define APP_DIS_SW_REV_STR              ("LSSoftwareRev")
#define APP_DIS_SW_REV_STR_LEN          (sizeof(APP_DIS_SW_REV_STR) -1)

/// IEEE
#define APP_DIS_IEEE                    ("LSIEEEDatalist")
#define APP_DIS_IEEE_LEN                (sizeof(APP_DIS_IEEE) -1)

/// PNP ID Value
#define APP_DIS_PNP_ID                  ("\x01\x7A\x05\x62\x00\x0A\x00")
#define APP_DIS_PNP_ID_LEN              (7)

#define DIR_NAME    7
#define RECORD_KEY1 1
#define RECORD_KEY2 2
#define FIRST_TIMER_TIMEOUT 1000 // timer units: ms
#define SECOND_TIMER_TIMEOUT 7000 // timer units: ms
#define KEYSCAN_TIMER_TIMEOUT (400) // timer units: ms
#define NTF_TIMEOUT 50 // timer units: ms
#define DMIC_CLK_IO (PB10)
#define DMIC_DATA_IO (PB09)
#define DMIC_VDD_IO (PB04)
#define KEY_REPORT_IDX (0)
#define KEY_VOICE_REPORT_IDX (1)
#define DATASIZE_GENERATE_EACH_TIME 134
#define DATA_BUFFER_SIZE 7370
#define DATA_ELEMENT_SIZE 20
#define DATA_PACKET_COUNT_GENERATE_EACH_TIME   7 
#define DATA_ARRAY_NUM ((DATA_BUFFER_SIZE/DATASIZE_GENERATE_EACH_TIME)*DATA_PACKET_COUNT_GENERATE_EACH_TIME)
#define PDM_CLK_KHZ 1024
#define PDM_SAMPLE_RATE_HZ 16000
#define FRAME_BUF_SIZE 256
/**defgroup BLE_GAP_IO_CAPS GAP IO Capabilities**/
#define BLE_GAP_IO_CAPS_DISPLAY_ONLY 0x0     /**< Display Only. */
#define BLE_GAP_IO_CAPS_DISPLAY_YESNO 0x1    /**< Display and Yes/No entry. */
#define BLE_GAP_IO_CAPS_KEYBOARD_ONLY 0x2    /**< Keyboard Only. */
#define BLE_GAP_IO_CAPS_NONE 0x3             /**< No I/O capabilities. */
#define BLE_GAP_IO_CAPS_KEYBOARD_DISPLAY 0x4 /**< Keyboard and Display. */

struct gap_slave_security_req test_auth;
struct pair_feature test_feat = {BLE_GAP_IO_CAPS_NONE,
                                 OOB_DATA_FLAG,
                                 AUTHREQ,
                                 KEY_SIZE,
                                 INIT_KEY_DIST,
                                 RESP_KEY_DIST};

struct gap_pin_str test_passkey = {passkey_number, 0};

DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);
struct data_element
{
    co_list_hdr_t list_header;
    uint8_t buf[DATA_ELEMENT_SIZE];
    uint8_t length;
};
struct data_element data_element_array[DATA_ARRAY_NUM];
static co_list_t tx_unused_list;
static co_list_t tx_used_list;
PDM_HandleTypeDef hdmic;
tinyfs_dir_t hid_dir;
static struct PDM_PingPong_Bufptr pdm_data_receive;
DMA_RAM_ATTR int16_t Buf0[FRAME_BUF_SIZE];
DMA_RAM_ATTR int16_t Buf1[FRAME_BUF_SIZE];
DMA_RAM_ATTR google_tv_audio_header audioHeader;
DMA_RAM_ATTR uint8_t EncodeBuffer[FRAME_BUF_SIZE * 2 / 4];
static uint16_t send_voice_data_handle;
static struct gatt_svc_env dis_server_svc_env;
static struct gatt_svc_env dis_server_svc_first_env;
static struct gatt_svc_env dis_server_svc_second_env;
static struct gatt_svc_env dis_server_svc_third_env;
static struct gatt_svc_env dis_server_svc_user_fourth_svc_env;
static struct gatt_svc_env dis_server_svc_atv_voice_env;

static bool atv_voice_ntf_done = false;
static bool get_caps = false;
bool search_key_pressed = false; 
static bool search = false;
static bool mic_open = false;
static bool mic_close = false;
static bool sync_atv_voice = false;
static bool mic_open_ntf_flag = false;


static struct builtin_timer *first_timer_inst = NULL;
static struct builtin_timer *second_timer_inst = NULL;
static struct builtin_timer *ntf_timer_inst = NULL;
static struct builtin_timer *keyscan_timer_inst = NULL;
static uint8_t adv_obj_hdl;

static uint8_t hid_connect_id = 0xff; 
static uint32_t sync_atv_voice_count = 0;
static uint8_t service_flag = 0;
static uint8_t profile_flag = 0;
static uint16_t atv_first_cccd_config = 0;
static uint16_t atv_second_cccd_config = 0;
static uint16_t first_svc_first_cccd_config = 0;
static uint16_t fourth_svc_first_cccd_config = 0;
static uint16_t fourth_svc_second_cccd_config = 0;
static uint16_t third_svc_first_cccd_config = 0;

static uint8_t advertising_data[28];
static uint8_t scan_response_data[31];
uint8_t adpcm_ntf_buf[134] = {0};
static uint8_t GET_CAPS[1] = {0x0A};
static uint8_t MIC_OPEN[1] = {0x0C};
static uint8_t MIC_CLOSE[1] = {0x0D};
static uint8_t sync_atv_voice_buf[3] = {0x0A};
static  uint8_t mic_open_buf[3] = {0};
static uint8_t search_buf[1]={0x08};
static uint8_t audio_start[1]={0x04};
static uint8_t audio_end[1]={0x00};
static uint8_t mic_open_error[]={0x0C,0x01,0x0F};
static  uint8_t get_caps_respone_buf[] = {0x0B,0x00,0x04,0x00,0x03,0x00,0x86,0x00,0x14};


///BLE SERVICES
static const uint8_t dis_svc_uuid[] ={0x0A,0x18};//device information
static const uint8_t dis_char_pnpid_uuid[] ={0x50,0x2A};//pnp id
static const uint8_t dis_char_manufacturer_name_uuid[] ={0x29,0x2A};// manu_name id
static const uint8_t dis_char_system_id_uuid[] ={0x23,0x2A};//system_id
static const uint8_t dis_char_model_number_string_uuid[] ={0x24,0x2A};// model_number_string id
static const uint8_t dis_char_serial_number_string_uuid[] ={0x25,0x2A};//serial_number_string id
static const uint8_t dis_char_firmware_revision_uuid[] ={0x26,0x2A};// firware_revision id
static const uint8_t dis_char_hardware_revision_uuid[] ={0x27,0x2A};// hardware_revision id
static const uint8_t dis_char_software_revision_uuid[] ={0x28,0x2A};// software_revision id
static const uint8_t dis_char_IEEE_uuid[] ={0x2A,0x2A};// IEEE id
static const uint8_t att_decl_char_array[] = {0x03,0x28};//Characteristic

static const uint8_t first_svc_uuid[] = {0x71,0x01,0x11,0x79,0x9e,0xcd,0x72,0x8e,0x08,0x47,0xda,0xef,0xcb,0x51,0x8d,0xc8};
static const uint8_t first_charc_uuid[] = {0x2a,0x09,0x4d,0xa9,0xe1,0x83,0xcf,0xbe,0xda,0x4a,0xe7,0xce,0xca,0xdd,0x3d,0xea};
static const uint8_t first_desc_client_char_cfg_array[] = {0x02,0x29};

static const uint8_t second_svc_uuid[] = {0x12,0xa2,0x4d,0x2e,0xfe,0x14,0x48,0x8e,0x93,0xd2,0x17,0x3c,0xff,0xd0,0x00,0x00};
static const uint8_t second_svc_first_charc_uuid[] = {0xD1,0xFF};
static const uint8_t second_svc_second_charc_uuid[] = {0xD2,0xFF};
static const uint8_t second_svc_third_charc_uuid[] = {0xD3,0xFF};
static const uint8_t second_svc_fourth_charc_uuid[] = {0xD4,0xFF};
static const uint8_t second_svc_fifth_charc_uuid[] = {0xD5,0xFF};
static const uint8_t second_svc_sixth_charc_uuid[] = {0xD8,0xFF};
static const uint8_t second_svc_seventh_charc_uuid[] = {0xF1,0xFF};
static const uint8_t second_svc_eighth_charc_uuid[] = {0xF2,0xFF};
static const uint8_t second_svc_ninth_charc_uuid[] = {0xE0,0xFF};

static const uint8_t third_svc_uuid_128[] = {0x12,0xa2,0x4d,0x2e,0xfe,0x14,0x48,0x8e,0x93,0xd2,0x17,0x3c,0x87,0x62,0x00,0x00};
static const uint8_t third_svc_first_charc_uuid_128[] = {0x12,0xa2,0x4d,0x2e,0xfe,0x14,0x48,0x8e,0x93,0xd2,0x17,0x3c,0x87,0x63,0x00,0x00};
static const uint8_t third_svc_second_charc_uuid_128[] = {0x12,0xa2,0x4d,0x2e,0xfe,0x14,0x48,0x8e,0x93,0xd2,0x17,0x3c,0x87,0x64,0x00,0x00};
static const uint8_t third_svc_client_char_cfg_array[] = {0x02,0x29};


static const uint8_t fourth_svc_uuid_128[] = {0x64,0xb6,0x17,0xf7,0x01,0xaf,0x7d,0xbc,0x05,0x4f,0x21,0x5a,0x01,0x00,0x5e,0xad};
static const uint8_t fourth_svc_first_charc_uuid[] = {0x64,0xb6,0x17,0xf7,0x01,0xaf,0x7d,0xbc,0x05,0x4f,0x21,0x5a,0x02,0x00,0x5e,0xad};
static const uint8_t fourth_svc_second_charc_uuid[] = {0x64,0xb6,0x17,0xf7,0x01,0xaf,0x7d,0xbc,0x05,0x4f,0x21,0x5a,0x03,0x00,0x5e,0xad};
static const uint8_t fourth_svc_first_desc_client_char_cfg_array[] = {0x02,0x29};
static const uint8_t fourth_svc_third_charc_uuid[] = {0x64,0xb6,0x17,0xf7,0x01,0xaf,0x7d,0xbc,0x05,0x4f,0x21,0x5a,0x04,0x00,0x5e,0xad};
static const uint8_t fourth_svc_second_desc_client_char_cfg_array[] = {0x02,0x29};


static const uint8_t ATV_Voice_Service_uuid_128[] = {0x64,0xB6,0x17,0xF6,0x01,0xAF,0x7D,0xBC,0x05,0x4F,0x21,0x5A,0x01,0x00,0x5E,0xAB};
static const uint8_t Write_uuid_128[] = {0x64,0xB6,0x17,0xF6,0x01,0xAF,0x7D,0xBC,0x05,0x4F,0x21,0x5A,0x02,0x00,0x5E,0xAB};
static const uint8_t Read_uuid_128[] = {0x64,0xB6,0x17,0xF6,0x01,0xAF,0x7D,0xBC,0x05,0x4F,0x21,0x5A,0x03,0x00,0x5E,0xAB};
static const uint8_t Control_uuid_128[] = {0x64,0xB6,0x17,0xF6,0x01,0xAF,0x7D,0xBC,0x05,0x4F,0x21,0x5A,0x04,0x00,0x5E,0xAB};


static void first_timer_cb(void *param);
static void second_timer_cb(void *param);
static void ntf_timer_cb(void *param);
static void keyscan_timer_cb(void *param);
static void ls_timer_init(void);
static void ls_voice_send_notification(void);
static void atv_pdm_on(void);
static void atv_pdm_off(void);
void data_generator(uint8_t *buff, uint8_t length);
static void send_ntf_once(void);
static void data_tx_buf_init(void);
static void data_sender(void);
static void init_two_lists(void);
void dmic_pdm_dma_init(void);
void dmic_pdm_init(void);
void gpio_exit_init(void);
static void start_adv(void);
static void hid_server_get_dev_name(struct gap_dev_info_dev_name *dev_name_ptr, uint8_t con_idx);


static void ls_timer_init(void)
{
    first_timer_inst = builtin_timer_create(first_timer_cb);
    second_timer_inst = builtin_timer_create(second_timer_cb);
    ntf_timer_inst = builtin_timer_create(ntf_timer_cb);
    builtin_timer_start(ntf_timer_inst, NTF_TIMEOUT, NULL); 
}


static void ntf_timer_cb(void *param)
{
    if(hid_connect_id != 0xff)
    {
        if(sync_atv_voice)
        {
            sync_atv_voice_count++;
        }
        ls_voice_send_notification();
        if(mic_open_ntf_flag)
        {
            data_sender();
        }
        if(search_key_pressed)
        {
            search_key_pressed = false;
            search = true;
        }
    }

    if(ntf_timer_inst)
    {
        builtin_timer_start(ntf_timer_inst, NTF_TIMEOUT, NULL); 
    }
}

enum dis_svc_att_db_hdl
{
    APP_DIS_MANUFACTURER_NAME_CHAR,
    APP_DIS_MANUFACTURER_NAME_VAL,
    APP_DIS_SYSTEM_ID_CHAR,
    APP_DIS_SYSTEM_ID_VAL,
    APP_DIS_MODEL_NB_STR_CHAR,
    APP_DIS_MODEL_NB_STR_VAL,
    APP_DIS_SERIAL_NB_STR_CHAR,
    APP_DIS_SERIAL_NB_STR_VAL,
    APP_DIS_FIRM_REV_STR_CHAR,
    APP_DIS_FIRM_REV_STR_VAL,
    APP_DIS_HARD_REV_STR_CHAR,
    APP_DIS_HARD_REV_STR_VAL,
    APP_DIS_SW_REV_STR_CHAR,
    APP_DIS_SW_REV_STR_VAL,
    APP_DIS_IEEE_CHAR,
    APP_DIS_IEEE_VAL,
    APP_DIS_PNP_ID_CHAR,    
    APP_DIS_PNP_ID_VAL,
    DIS_SVC_ATT_NUM,
};
enum dis_svc_att_db_hdl_user_first_v
{
    FIRST_SVC_FIRST_CHAR_V,
    FIRST_SVC_FIRST_CHARC_VAL_V,
    FIRST_SVC_FIRST_NTF_CFG_V,
    FIRST_SVC_ATT_NUM_V,
};

enum dis_svc_att_db_hdl_user_second
{
    SECOND_SVC_FIRST_CHARC_CHAR,
    SECOND_SVC_FIRST_CHARC_VAL,
    SECOND_SVC_SECOND_CHARC_CHAR,
    SECOND_SVC_SECOND_CHARC_VAL,
    SECOND_SVC_THIRD_CHARC_CHAR,
    SECOND_SVC_THIRD_CHARC_VAL,
    SECOND_SVC_FOURTH_CHARC_CHAR,
    SECOND_SVC_FOURTH_CHARC_VAL,
    SECOND_SVC_FIFTH_CHARC_CHAR,
    SECOND_SVC_FIFTH_CHARC_VAL,
    SECOND_SVC_SIXTH_CHARC_CHAR,
    SECOND_SVC_SIXTH_CHARC_VAL,
    SECOND_SVC_SEVENTH_CHARC_CHAR,
    SECOND_SVC_SEVENTH_CHARC_VAL,
    SECOND_SVC_EIGHTH_CHARC_CHAR,
    SECOND_SVC_EIGHTH_CHARC_VAL,
    SECOND_SVC_NINTH_CHARC_CHAR,
    SECOND_SVC_NINTH_CHARC_VAL,
    SECOND_SVC_ATT_NUM,
};
enum dis_svc_att_db_hdl_user_third
{
    THIRD_SVC_FIRST_CHARC_CHAR,
    THIRD_SVC_FIRST_CHARC_VAL,
    THIRD_SVC_SECOND_CHARC_CHAR,
    THIRD_SVC_SECOND_CHARC_VAL,
    THIRD_SVC_FIRST_NTF_CFG,
    THIRD_SVC_ATT_NUM,
};

enum dis_svc_att_db_hdl_user_fouth
{
    FOUTH_SVC_FIRST_CHAR,
    FOUTH_SVC_FIRST_VAL,
    FOUTH_SVC_SECOND_CHAR, 
    FOUTH_SVC_SECOND_VAL,
    FOUTH_SVC_FIRST_NTF_CFG,
    FOUTH_SVC_THIRD_CHAR, 
    FOUTH_SVC_THIRD_VAL,
    FOUTH_SVC_SECOND_NTF_CFG,
    FOUTH_SVC_ATT_NUM,
};

enum dis_svc_att_db_hdl_atv_voice
{
    WRITE_CHAR,
    WRITE_VAL,
    READ_CHAR,
    READ_VAL,
    ATV_VOICE_SVC_FIRST_NTF_CFG,
    CONTROL_CHAR,
    CONTROL_VAL,
    ATV_VOICE_SVC_SECOND_NTF_CFG,
    ATV_VOICE_SVC_ATT_NUM,
};
static const struct att_decl dis_server_att_decl[DIS_SVC_ATT_NUM] =
{
    [APP_DIS_PNP_ID_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_PNP_ID_VAL] = {
        .uuid = dis_char_pnpid_uuid,
        .s.max_len = APP_DIS_PNP_ID_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
   [APP_DIS_MANUFACTURER_NAME_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_MANUFACTURER_NAME_VAL] = {
        .uuid = dis_char_manufacturer_name_uuid,
        .s.max_len = APP_DIS_MANUFACTURER_NAME_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
    [APP_DIS_SYSTEM_ID_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_SYSTEM_ID_VAL] = {
        .uuid = dis_char_system_id_uuid,
        .s.max_len = APP_DIS_SYSTEM_ID_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
    [APP_DIS_MODEL_NB_STR_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_MODEL_NB_STR_VAL] = {
        .uuid = dis_char_model_number_string_uuid,
        .s.max_len = APP_DIS_MODEL_NB_STR_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
    [APP_DIS_SERIAL_NB_STR_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_SERIAL_NB_STR_VAL] = {
        .uuid = dis_char_serial_number_string_uuid,
        .s.max_len = APP_DIS_SERIAL_NB_STR_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
    [APP_DIS_FIRM_REV_STR_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_FIRM_REV_STR_VAL] = {
        .uuid = dis_char_firmware_revision_uuid,
        .s.max_len = APP_DIS_FIRM_REV_STR_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
    [APP_DIS_HARD_REV_STR_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_HARD_REV_STR_VAL] = {
        .uuid = dis_char_hardware_revision_uuid,
        .s.max_len = APP_DIS_HARD_REV_STR_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
    [APP_DIS_SW_REV_STR_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_SW_REV_STR_VAL] = {
        .uuid = dis_char_software_revision_uuid,
        .s.max_len = APP_DIS_SW_REV_STR_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
    [APP_DIS_IEEE_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [APP_DIS_IEEE_VAL] = {
        .uuid = dis_char_IEEE_uuid,
        .s.max_len = APP_DIS_IEEE_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
    },
};
static const struct att_decl dis_server_att_decl_first_svc[FIRST_SVC_ATT_NUM_V] =
{
    [FIRST_SVC_FIRST_CHAR_V] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,   
        .char_prop.wr_cmd = 1,
        .char_prop.ntf_en = 1,
    },
    [FIRST_SVC_FIRST_CHARC_VAL_V] = {
        .uuid = first_charc_uuid,
        .s.max_len = 256,
        .s.uuid_len = UUID_LEN_128BIT,
        .char_prop.wr_cmd = 1,
        .char_prop.ntf_en = 1,
    },
    [FIRST_SVC_FIRST_NTF_CFG_V] = {
            .uuid = first_desc_client_char_cfg_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
            .char_prop.wr_req = 1,
        },
};
static const struct att_decl dis_server_att_decl_second_svc[SECOND_SVC_ATT_NUM] =
    {
        [SECOND_SVC_FIRST_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_cmd = 1,
        },
        [SECOND_SVC_FIRST_CHARC_VAL] = {
            .uuid = second_svc_first_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_cmd = 1,
        },
        [SECOND_SVC_SECOND_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_SECOND_CHARC_VAL] = {
            .uuid = second_svc_second_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_THIRD_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_THIRD_CHARC_VAL] = {
            .uuid = second_svc_third_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_FOURTH_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_FOURTH_CHARC_VAL] = {
            .uuid = second_svc_fourth_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_FIFTH_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_FIFTH_CHARC_VAL] = {
            .uuid = second_svc_fifth_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_SIXTH_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_cmd = 1,
        },
        [SECOND_SVC_SIXTH_CHARC_VAL] = {
            .uuid = second_svc_sixth_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_cmd = 1,
        },
        [SECOND_SVC_SEVENTH_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_SEVENTH_CHARC_VAL] = {
            .uuid = second_svc_seventh_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_EIGHTH_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_req = 1,
        },
        [SECOND_SVC_EIGHTH_CHARC_VAL] = {
            .uuid = second_svc_eighth_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_req = 1,
        },
        [SECOND_SVC_NINTH_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
        [SECOND_SVC_NINTH_CHARC_VAL] = {
            .uuid = second_svc_ninth_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
        },
};
static const struct att_decl dis_server_att_decl_third_svc[THIRD_SVC_ATT_NUM] =
    {
        [THIRD_SVC_FIRST_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_cmd = 1,
        },
        [THIRD_SVC_FIRST_CHARC_VAL] = {
            .uuid = third_svc_first_charc_uuid_128,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_128BIT,
            .char_prop.wr_cmd = 1,
        },
        [THIRD_SVC_SECOND_CHARC_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_req = 1,
            .char_prop.ntf_en = 1,
        },
        [THIRD_SVC_SECOND_CHARC_VAL] = {
            .uuid = third_svc_second_charc_uuid_128,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_128BIT,
            .char_prop.wr_req = 1,
            .char_prop.ntf_en = 1,
        },
        [THIRD_SVC_FIRST_NTF_CFG] = {
            .uuid = third_svc_client_char_cfg_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
            .char_prop.wr_req = 1,
        },
};

static const struct att_decl dis_server_att_decl_fourth_svc[FOUTH_SVC_ATT_NUM] =
    {
        [FOUTH_SVC_FIRST_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .char_prop.wr_req = 1,
        },
        [FOUTH_SVC_FIRST_VAL] = {
            .uuid = fourth_svc_first_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_128BIT,
            .char_prop.wr_req = 1,
        },
        [FOUTH_SVC_SECOND_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
            .char_prop.ntf_en = 1,
        },
        [FOUTH_SVC_SECOND_VAL] = {
            .uuid = fourth_svc_second_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_128BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
            .char_prop.ntf_en = 1,
        },
        [FOUTH_SVC_FIRST_NTF_CFG] = {
            .uuid = fourth_svc_first_desc_client_char_cfg_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
            .char_prop.wr_req = 1,
        },
        [FOUTH_SVC_THIRD_CHAR] = {
            .uuid = att_decl_char_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
            .char_prop.ntf_en = 1,
        },
        [FOUTH_SVC_THIRD_VAL] = {
            .uuid = fourth_svc_third_charc_uuid,
            .s.max_len = 256,
            .s.uuid_len = UUID_LEN_128BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
            .char_prop.ntf_en = 1,
        },
        [FOUTH_SVC_SECOND_NTF_CFG] = {
            .uuid = fourth_svc_second_desc_client_char_cfg_array,
            .s.max_len = 0,
            .s.uuid_len = UUID_LEN_16BIT,
            .s.read_indication = 1,
            .char_prop.rd_en = 1,
            .char_prop.wr_req = 1,
        },
};

static const struct att_decl dis_server_att_decl_atv_voice[ATV_VOICE_SVC_ATT_NUM] =
{
    [WRITE_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        // .s.read_indication = 1,
        // .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
        .char_prop.wr_cmd = 1,
    },
    [WRITE_VAL] = {
        .uuid = Write_uuid_128,
        .s.max_len = 256,
        .s.uuid_len = UUID_LEN_128BIT,
        // .s.read_indication = 1,
        // .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
        .char_prop.wr_cmd = 1,
    },
    [READ_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        // .s.read_indication = 1,   
        // .char_prop.rd_en = 1,
        .char_prop.ntf_en = 1,
    },
    [READ_VAL] = {
        .uuid = Read_uuid_128,
        .s.max_len = 256,
        .s.uuid_len = UUID_LEN_128BIT,
        // .s.read_indication = 1,  
        // .char_prop.rd_en = 1, 
        .char_prop.ntf_en = 1,
    },
    [ATV_VOICE_SVC_FIRST_NTF_CFG] = {
        .uuid = fourth_svc_first_desc_client_char_cfg_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
    },
    [CONTROL_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        // .s.read_indication = 1,   
        // .char_prop.rd_en = 1,
        .char_prop.ntf_en = 1,
    },
    [CONTROL_VAL] = {
        .uuid = Control_uuid_128,
        .s.max_len = 256,
        .s.uuid_len = UUID_LEN_128BIT,
        // .s.read_indication = 1, 
        // .char_prop.rd_en = 1,  
        .char_prop.ntf_en = 1,
    },
    [ATV_VOICE_SVC_SECOND_NTF_CFG] = {
        .uuid = fourth_svc_first_desc_client_char_cfg_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
    },
};


static const struct svc_decl dis_server_svc =
{
    .uuid = dis_svc_uuid,
    .att = (struct att_decl*)dis_server_att_decl,
    .nb_att = DIS_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_16BIT,
    .sec_lvl = 1,
};
static const struct svc_decl dis_server_svc_first =
{
    .uuid = first_svc_uuid,
    .att = (struct att_decl*)dis_server_att_decl_first_svc,
    .nb_att = FIRST_SVC_ATT_NUM_V,
    .uuid_len = UUID_LEN_128BIT,
    .sec_lvl = 1,
};
static const struct svc_decl dis_server_svc_second =
{
    .uuid = second_svc_uuid,
    .att = (struct att_decl*)dis_server_att_decl_second_svc,
    .nb_att = SECOND_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_128BIT,
    .sec_lvl = 1,
};
static const struct svc_decl dis_server_svc_third =
{
    .uuid = third_svc_uuid_128,
    .att = (struct att_decl*)dis_server_att_decl_third_svc,
    .nb_att = THIRD_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_128BIT,
    .sec_lvl = 1,
};
static const struct svc_decl dis_server_svc_decl_fourth_svc =
{
    .uuid = fourth_svc_uuid_128,
    .att = (struct att_decl*)dis_server_att_decl_fourth_svc,
    .nb_att = FOUTH_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_128BIT,
    .sec_lvl = 1,
};
static const struct svc_decl atv_voice_svc_user =
{
    .uuid = ATV_Voice_Service_uuid_128,
    .att = (struct att_decl*)dis_server_att_decl_atv_voice,
    .nb_att = ATV_VOICE_SVC_ATT_NUM,
    .uuid_len = UUID_LEN_128BIT,
    .sec_lvl = 1,
};


const uint8_t hid_report_map[] =
    {
        0x05, 0x01, //Usage Page(Generic Desktop)
        0x09, 0x06, //Usage(Keyboard)
        0xA1, 0x01, //Collection(Application)
        0x05, 0x07, //Usage Page(Keyboard)
        0x09, 0x06, //Usage(Keyboard c and C)
        0xA1, 0x01, //Collection(Application)
        0x85, 0x01, //Report Id(1)
        0x95, 0x08, //Report Count(8)
        0x75, 0x08, //Report Size(8)
        0x15, 0x00, //Logical minimum(0)
        0x25, 0xFF, //Logical maximum(255)
        0x19, 0x00, //Usage Minimum(No event indicated)
        0x29, 0xFF, //Usage Maximum(Reserved (0x00FF))
        0x81, 0x00, //Iuput(Data,Array,Absolute,Bit Field)
        0xC0,       //End Collection

        0x05, 0x0C,       //Usage Page(Consumer)
        0x09, 0x01,       //Usage(Consumer Control)
        0xA1, 0x01,       //Collection(Application)
        0x85, 0x03,       //Report Id(3)
        0x19, 0x00,       //Usage Minimum(No event indicated)
        0x2A, 0x9D, 0x02, //Usage Maximum(Reserved (0x029D))
        0x15, 0x00,       //Logical minimum(0)
        0x26, 0x9D, 0x02, // Logical maximum(669)
        0x75, 0x10,       //Report Size(16)
        0x95, 0x02,       //Report Count(2)
        0x81, 0x00,       //Iuput(Data,Value,Absolute,Bit Field)
        0xC0,             //End Collection

        0x06, 0x00, 0xFF, //Usage Page(Vendor-defined 0xFF00)
        0x09, 0x00, //Usage(Vendor-defined 0x0000)
        0xA1, 0x01,       //Collection(Application)
        0x85, 0x5A,       //Report Id(90)
        0x95, 0xFF, //Report Count(255)
        0x75, 0x08, //Report Size(8)
        0x15, 0x00, //Logical minimum(0)
        0x25, 0xFF, //Logical maximum(255)
        0x19, 0x00, //Usage Minimum(No event indicated)
        0x29, 0xFF, //Usage Maximum(Reserved (0x00FF))
        0x81, 0x00,       //Iuput(Data,Value,Absolute,Bit Field)
        0xC0,             //End Collection
        0xC0,             //End Collection
};

#define HID_REPORT_MAP_LEN (sizeof(hid_report_map))

static void dis_server_read_req_ind(union gatt_evt_u *evt, uint8_t att_idx, uint8_t con_idx)
{
    LOG_I("---------READ-----------");
    uint16_t handle = 0;
    if (evt->server_read_req.svc == &dis_server_svc_env)
    {
        switch (att_idx)
        {
        case APP_DIS_PNP_ID_VAL:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_PNP_ID, APP_DIS_PNP_ID_LEN);
        }
        break;
        case APP_DIS_MANUFACTURER_NAME_VAL:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_MANUFACTURER_NAME, APP_DIS_MANUFACTURER_NAME_LEN);
        }
        break;
        case APP_DIS_SYSTEM_ID_VAL:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_SYSTEM_ID, APP_DIS_SYSTEM_ID_LEN);
        }
        break;
        case APP_DIS_MODEL_NB_STR_VAL:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_MODEL_NB_STR, APP_DIS_MODEL_NB_STR_LEN);
        }
        break;
        case APP_DIS_SERIAL_NB_STR_VAL:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_SERIAL_NB_STR, APP_DIS_SERIAL_NB_STR_LEN);
        }
        break;
        case APP_DIS_FIRM_REV_STR_VAL:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_FIRM_REV_STR, APP_DIS_FIRM_REV_STR_LEN);
        }
        break;
        case APP_DIS_HARD_REV_STR_VAL:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_HARD_REV_STR, APP_DIS_HARD_REV_STR_LEN);
        }
        break;
        case APP_DIS_SW_REV_STR_VAL:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_SW_REV_STR, APP_DIS_SW_REV_STR_LEN);
        }
        break;
            case APP_DIS_IEEE_VAL:
            {
                handle = gatt_manager_get_svc_att_handle(&dis_server_svc_env, att_idx);
                gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)APP_DIS_IEEE, APP_DIS_IEEE_LEN);
            }
            break;
            default:
                break;
            }
    }
    if (evt->server_read_req.svc == &dis_server_svc_first_env)
    {
        if (att_idx == FIRST_SVC_FIRST_NTF_CFG_V)
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_first_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&first_svc_first_cccd_config, 2);
        }
    }
     if (evt->server_read_req.svc == &dis_server_svc_second_env)
    {
        switch (att_idx)
        {
        case SECOND_SVC_SECOND_CHARC_VAL:
        {
            uint8_t read_second_svc_second_charc[] = {0x18, 0x46, 0x44, 0x70, 0x23, 0x5F};
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_second_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&read_second_svc_second_charc, sizeof(read_second_svc_second_charc));
        }
        break;
        case SECOND_SVC_THIRD_CHARC_VAL:
        {
            uint8_t read_second_svc_third_charc[] = {0x01, 0x90, 0x10, 0x88};
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_second_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&read_second_svc_third_charc, sizeof(read_second_svc_third_charc));
        }
        break;
        case SECOND_SVC_FOURTH_CHARC_VAL:
        {
            uint8_t read_second_svc_fourth_charc[] = {0x11, 0x00, 0x00, 0x50};
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_second_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&read_second_svc_fourth_charc, sizeof(read_second_svc_fourth_charc));
        }
        break;
        case SECOND_SVC_FIFTH_CHARC_VAL:
        {
            uint8_t read_second_svc_fifth_charc[] = {0};
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_second_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&read_second_svc_fifth_charc, sizeof(read_second_svc_fifth_charc));
        }
        break;
        case SECOND_SVC_SEVENTH_CHARC_VAL:
        {
            uint8_t read_second_svc_seventh_charc[] = {0x05, 0x01, 0x00, 0x07, 0x00, 0x08, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00};
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_second_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&read_second_svc_seventh_charc, sizeof(read_second_svc_seventh_charc));
        }
        break;
        case SECOND_SVC_NINTH_CHARC_VAL:
        {
            uint8_t read_second_svc_ninth_charc[] = {0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x90, 0x10, 0x88, 0x11, 0x00, 0x00, 0x50};
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_second_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&read_second_svc_ninth_charc, sizeof(read_second_svc_ninth_charc));
        }
        break;
        default:
            break;
        }
    }
    if (evt->server_read_req.svc == &dis_server_svc_third_env)
    {
        if (att_idx == THIRD_SVC_FIRST_NTF_CFG)
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_third_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&third_svc_first_cccd_config, 2);
        }
    }
    if (evt->server_read_req.svc == &dis_server_svc_user_fourth_svc_env)
    {
        switch (att_idx)
        {
        case FOUTH_SVC_SECOND_VAL:
        {
            uint8_t fouth_svc_second_buf[20] = {0};
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_user_fourth_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&fouth_svc_second_buf, sizeof(fouth_svc_second_buf));
        }
        break;
        case FOUTH_SVC_THIRD_VAL:
        {
            uint8_t fouth_svc_third_buf[20] = {0};
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_user_fourth_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&fouth_svc_third_buf, sizeof(fouth_svc_third_buf));
        }
        break;
        case FOUTH_SVC_FIRST_NTF_CFG:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_user_fourth_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&fourth_svc_first_cccd_config, 2);
        }
        break;
        case FOUTH_SVC_SECOND_NTF_CFG:
        {
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_user_fourth_svc_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&fourth_svc_second_cccd_config, 2);
        }
        break;
        default:
            break;
        }
    }
    if (evt->server_read_req.svc == &dis_server_svc_atv_voice_env)
    {
        switch (att_idx)
        {
        case ATV_VOICE_SVC_FIRST_NTF_CFG:
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&atv_first_cccd_config, 2);
            break;
        case ATV_VOICE_SVC_SECOND_NTF_CFG:
            handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, att_idx);
            gatt_manager_server_read_req_reply(con_idx, handle, 0, (void *)&atv_second_cccd_config, 2);
            break;
        default:
            break;
        }
    }
}
static void ls_server_write_req_ind(union gatt_evt_u *evt, uint8_t att_idx, uint8_t con_idx, uint16_t length, uint8_t const *value)
{
    LOG_I("---------WRITE-----------");
    if (evt->server_read_req.svc == &dis_server_svc_first_env)
    {
        if (att_idx == FIRST_SVC_FIRST_NTF_CFG_V)
        {
            LS_ASSERT(length == 2);
            memcpy(&first_svc_first_cccd_config, value, length);
        }
    }
    if (evt->server_read_req.svc == &dis_server_svc_third_env)
    {
        if (att_idx == THIRD_SVC_FIRST_NTF_CFG)
        {
            LS_ASSERT(length == 2);
            memcpy(&third_svc_first_cccd_config, value, length);
        }
    }

    if (evt->server_read_req.svc == &dis_server_svc_atv_voice_env)
    {
        switch (att_idx)
        {
        case ATV_VOICE_SVC_FIRST_NTF_CFG:
            LS_ASSERT(length == 2);
            memcpy(&atv_first_cccd_config, value, length);
            break;
        case ATV_VOICE_SVC_SECOND_NTF_CFG:
            LS_ASSERT(length == 2);
            memcpy(&atv_second_cccd_config, value, length);
            break;
        default:
            break;
        }
    }
    if (evt->server_read_req.svc == &dis_server_svc_user_fourth_svc_env)
    {
        switch (att_idx)
        {
        case FOUTH_SVC_FIRST_NTF_CFG:
            LS_ASSERT(length == 2);
            memcpy(&fourth_svc_first_cccd_config, value, length);
            break;
        case FOUTH_SVC_SECOND_NTF_CFG:
            LS_ASSERT(length == 2);
            memcpy(&fourth_svc_second_cccd_config, value, length);
        default:
            break;
        }
    }
}

static void ls_voice_send_notification(void)
{ 
    if(sync_atv_voice && (sync_atv_voice_count % 10 == 0))
    {
        uint16_t handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, CONTROL_VAL);
        sync_atv_voice_buf[1] = ((audioHeader.frame_number & 0xff00) >> 8);
        sync_atv_voice_buf[2] = ((audioHeader.frame_number & 0xff)-1);
        gatt_manager_server_send_notification(hid_connect_id, handle, sync_atv_voice_buf, sizeof(sync_atv_voice_buf), NULL);
        LOG_HEX(sync_atv_voice_buf,3);
        LOG_I("sync_atv_voice ntf done");
    }
    if(search)
    {
        search = false;
        uint16_t handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, CONTROL_VAL);
        gatt_manager_server_send_notification(hid_connect_id, handle, search_buf, sizeof(search_buf), NULL);
        LOG_I("search ntf done");
    }
    else if(get_caps)
    {
        get_caps = false;
        uint16_t handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, CONTROL_VAL);
        gatt_manager_server_send_notification(hid_connect_id, handle, get_caps_respone_buf, sizeof(get_caps_respone_buf), NULL);
        LOG_I("get caps ntf done");
    }
    else if(mic_open)
    {
        mic_open = false;  
        uint16_t handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, CONTROL_VAL);
        gatt_manager_server_send_notification(hid_connect_id, handle, audio_start, 1, NULL);
        builtin_timer_stop(first_timer_inst);
        mic_open_ntf_flag = true;
        atv_voice_ntf_done = true;
        dmic_pdm_dma_init();
        atv_pdm_on();
        builtin_timer_stop(second_timer_inst);
        builtin_timer_start(second_timer_inst, SECOND_TIMER_TIMEOUT, NULL); 
    }
    else if(mic_close)
    {
        uint16_t handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, CONTROL_VAL);
        mic_close = false;
        gatt_manager_server_send_notification(hid_connect_id, handle, audio_end, sizeof(audio_end), NULL);
        atv_pdm_off();
        mic_open_ntf_flag = false;
        LOG_I("close_mic");
    }   
}

static void gap_manager_callback(enum gap_evt_type type, union gap_evt_u *evt, uint8_t con_idx)
{
    uint16_t ntf_cfg;
    uint16_t len = sizeof(ntf_cfg);
    struct ble_addr direct_master_addr;
    switch (type)
    {
    case CONNECTED:
    {
        hid_connect_id = con_idx;
        service_flag = 0;
        test_auth.auth = 0x5;
        mic_open_ntf_flag = false;
        gap_manager_get_peer_addr(hid_connect_id, &direct_master_addr);
        LOG_HEX(direct_master_addr.addr.addr, sizeof(direct_master_addr.addr.addr));
        LOG_I("connected! direct_master_addr.type : %d", direct_master_addr.type);
        uint8_t record_key2_write_flag = tinyfs_write(hid_dir, RECORD_KEY2, (uint8_t *)&direct_master_addr.addr.addr, sizeof(direct_master_addr.addr.addr));
        if (record_key2_write_flag == TINYFS_NO_ERROR)
        {
            tinyfs_write_through();
            LOG_I("record_key2_write_peer_addr1_success :%d", record_key2_write_flag);
        }
        else
        {
            LOG_I("record_key2_write_peer_addr1_fail :%d", record_key2_write_flag);
        }
        uint8_t record_key1_read_flag = tinyfs_read(hid_dir, RECORD_KEY1, (uint8_t *)&ntf_cfg, &len);
        if (record_key1_read_flag == TINYFS_NO_ERROR)
        {
            hid_ntf_cfg_init(ntf_cfg, con_idx, evt->connected.peer_id);
            LOG_I("record_key1_read_ntf_cfg_success :%d", record_key1_read_flag);
        }
        else
        {
            LOG_I("record_key1_read_ntf_cfg_fail :%d", record_key1_read_flag);
        }

        bas_batt_lvl_update(0, 0x62);
        struct gap_update_conn_param con_param = {
            .intv_min = 0x0B,
            .intv_max = 0x0B,
            .latency = 0,
            .sup_timeout = 400,
        };
        gap_manager_update_conn_param(con_idx, &con_param);
    }
    break;
    case DISCONNECTED:
        LOG_I("disconnected! reson : %x", evt->disconnected.reason);
        hid_connect_id = 0xff;
        atv_pdm_off();
        mic_open_ntf_flag = false;
        start_adv();
        break;
    case CONN_PARAM_REQ:

        break;
    case CONN_PARAM_UPDATED:
        LOG_I("conn_param_updated,intv:%d latency:%d sup_to:%d", evt->conn_param_updated.con_interval,
              evt->conn_param_updated.con_latency,
              evt->conn_param_updated.sup_to);
        break;
    case MASTER_PAIR_REQ: //4
        gap_manager_slave_pair_response_send(hid_connect_id, true, &test_feat);
        //gap_manager_passkey_input(hid_connect_id,&test_passkey);
        break;

    case SLAVE_SECURITY_REQ: //5
        LOG_I("SLAVE_SECURITY_REQ");

        break;

    case PAIR_DONE: //6
        LOG_I("PAIR_DONE reason :%d , success :%d", evt->pair_done.u.fail_reason, evt->pair_done.succeed);
        break;

    case ENCRYPT_DONE: //7
        LOG_I("disconnected! reson : %x", evt->disconnected.reason);
        break;

    case DISPLAY_PASSKEY: //8
        LOG_I("DISPLAY_PASSKEY");
        // LOG_I("passkey=%d",evt->display_passkey.passkey.pin);
        // LOG_I("DISPLAY_PASSKEY");
        //gap_manager_passkey_input(hid_connect_id,&test_passkey);
        break;

    case REQUEST_PASSKEY: //9
        LOG_I("REQUEST_PASSKEY");
        //gap_manager_passkey_input(hid_connect_id,&test_passkey);
        break;

    case NUMERIC_COMPARE: //10
        LOG_I("NUMERIC_COMPARE");
        //gap_manager_numeric_compare_set(hid_connect_id,true);
        break;
    case GET_DEV_INFO_DEV_NAME:
        hid_server_get_dev_name((struct gap_dev_info_dev_name *)evt, con_idx);
        break;
    default:

        break;
    }
}

static void gatt_manager_callback(enum gatt_evt_type type, union gatt_evt_u *evt, uint8_t con_idx)
{
    // LOG_I("gatt evt:%d",type);
    switch (type)
    {
    case SERVER_READ_REQ:
        LOG_I("read req");
        dis_server_read_req_ind(evt,evt->server_read_req.att_idx, con_idx);
        break;
    case SERVER_WRITE_REQ:
        LOG_I("write req");
         if(!memcmp(GET_CAPS,evt->server_write_req.value,1))
        {
            get_caps = true;
            LOG_HEX(evt->server_write_req.value,evt->server_write_req.length);
            LOG_I("get caps");
        }
        else if(!memcmp(MIC_OPEN,evt->server_write_req.value,1))
        {
            init_two_lists();
            memcpy(mic_open_buf,evt->server_write_req.value,sizeof(mic_open_buf));
            LOG_HEX(mic_open_buf,3);
            builtin_timer_stop(first_timer_inst);
            builtin_timer_start(first_timer_inst, FIRST_TIMER_TIMEOUT, NULL);
            mic_open = true;
        }
        else if(!memcmp(MIC_CLOSE,evt->server_write_req.value,1))
        {
            builtin_timer_stop(second_timer_inst);
            mic_close = true;
        }
        ls_server_write_req_ind(evt,evt->server_write_req.att_idx, con_idx, evt->server_write_req.length, evt->server_write_req.value);
        break;
    case SERVER_NOTIFICATION_DONE:
        if (mic_open_ntf_flag)
        {
            if (hid_connect_id != 0xff)
            {
                atv_voice_ntf_done = true;
                send_ntf_once();
                // LOG_I("NTF DONE!");
            }
        }
        break;
    case MTU_CHANGED_INDICATION:
        LOG_I("MTU:%d",evt->mtu_changed_ind.mtu);
        break;
    case CLIENT_RECV_INDICATION:
        LOG_I("clinent recv ind,hdl:%d",evt->client_recv_notify_indicate.handle);
        //LOG_I(evt->client_recv_notify_indicate.value, evt->client_recv_notify_indicate.length);
        break;
    default:
        LOG_I("Event not handled!");
        break;
    }
}

static void hid_server_get_dev_name(struct gap_dev_info_dev_name *dev_name_ptr, uint8_t con_idx)
{
    LS_ASSERT(dev_name_ptr);
    dev_name_ptr->value = (uint8_t *)APP_HID_DEV_NAME;
    dev_name_ptr->length = APP_HID_DEV_NAME_LEN;
}

static void prf_hid_server_callback(enum hid_evt_type type, union hid_evt_u *evt)
{
    uint16_t ntf_cfg;
    switch (type)
    {
    case HID_REPORT_READ:
        evt->read_report_req.length = 0;  
        if(evt->read_report_req.type == APP_HOGPD_REPORT_MAP)
        {
            evt->read_report_req.value = (uint8_t *)hid_report_map;
            evt->read_report_req.length = HID_REPORT_MAP_LEN;
        }
        break;
    case HID_NTF_CFG:
        LOG_I("hid_ntf_cfg save flash record_key1 : %x",evt->ntf_cfg.value);
        ntf_cfg = evt->ntf_cfg.value; 
        tinyfs_write(hid_dir, RECORD_KEY1, (uint8_t*)&ntf_cfg, sizeof(ntf_cfg));
        tinyfs_write_through();
        break;
    case HID_NTF_DONE:
        LOG_I("HID NTF DONE");
        break;
    case HID_REPORT_WRITE:
        LOG_I("HID REPORT WRITE");
        break;   
    default:
        break;
    }
}

static void prf_batt_server_callback(enum bass_evt_type type, union bass_evt_u *evt)
{

}

static uint8_t adv_data_buf[] = {0x03,0x03,0x12,0x18,0x03,0x19,0x80,0x01};
static uint8_t scan_rsp_data_buf[] = {0x0F,0x09,0x4A,0x49,0x4F,0x20,0x42,0x4C,0x45,0x20,0x52,0x65,0x6D,0x6F,0x74,0x65,0x03,0x19,0x80,0x01};

static void start_adv(void)
{
    memcpy(advertising_data,adv_data_buf,sizeof(adv_data_buf));
    memcpy(scan_response_data,scan_rsp_data_buf,sizeof(scan_rsp_data_buf));
    LOG_I("start adv");
    dev_manager_start_adv(adv_obj_hdl, advertising_data, sizeof(adv_data_buf), scan_response_data,sizeof(scan_rsp_data_buf));
}
static void create_adv_obj()
{
    struct legacy_adv_obj_param adv_param = {
        .adv_intv_min = 0x20,
        .adv_intv_max = 0x20,
        .own_addr_type = PUBLIC_OR_RANDOM_STATIC_ADDR,
        .filter_policy = 0,
        .ch_map = 0x7,
        .disc_mode = ADV_MODE_GEN_DISC,
        .prop = {
            .connectable = 1,
            .scannable = 1,
            .directed = 0,
            .high_duty_cycle = 0,
        },
    };
    dev_manager_create_legacy_adv_object(&adv_param);
    LOG_I("ADV_OBJ");
}

static void prf_added_handler(struct profile_added_evt *evt)
{
		LOG_I("added profile idx:%d, start handle:0x%x\n", evt->id, evt->start_hdl);
		uint16_t error_mkdir = 0;
		switch (evt->id)
		{
		case PRF_HID:
				error_mkdir = tinyfs_mkdir(&hid_dir, ROOT_DIR, DIR_NAME);
				LOG_I("error_mkdir = %d", error_mkdir);
				prf_hid_server_callback_init(prf_hid_server_callback);
				create_adv_obj();
				break;
		case PRF_BASS:
		{
				struct hid_db_cfg db_cfg = {0};
				db_cfg.hids_nb = 1;
				db_cfg.cfg[0].svc_features = HID_PROTO_MODE;
				db_cfg.cfg[0].report_nb = 3;
				db_cfg.cfg[0].report_id[0] = 1;
				db_cfg.cfg[0].report_id[1] = 3;
				db_cfg.cfg[0].report_id[2] = 90;

				db_cfg.cfg[0].report_cfg[0] = HID_REPORT_IN;
				db_cfg.cfg[0].report_cfg[1] = HID_REPORT_IN;
				db_cfg.cfg[0].report_cfg[2] = HID_REPORT_FEAT;

				db_cfg.cfg[0].info.bcdHID = 0;
				db_cfg.cfg[0].info.bCountryCode = 0;
				db_cfg.cfg[0].info.flags = HID_WKUP_FOR_REMOTE;
				prf_bass_server_callback_init(prf_batt_server_callback);
				dev_manager_prf_hid_server_add(NO_SEC, &db_cfg, sizeof(db_cfg));
				LOG_I("--------------------------");
		}
		break;

		default:
				break;
		}
}

static void dev_manager_callback(enum dev_evt_type type, union dev_evt_u *evt)
{

    switch (type)
    {
    case STACK_INIT:
    {
        struct ble_stack_cfg cfg = {
            .private_addr = false,
            .controller_privacy = false,
        };
        dev_manager_stack_init(&cfg);
    }
    break;
    case STACK_READY:
    {
        uint8_t addr[6];
        bool type;
        dev_manager_get_identity_bdaddr(addr, &type);
        LOG_I("type:%d,addr:", type);
        LOG_HEX(addr, sizeof(addr));
        DMA_CONTROLLER_INIT(dmac1_inst);
        dev_manager_add_service((struct svc_decl *)&dis_server_svc);
        ls_timer_init();
        dmic_pdm_init();
        data_tx_buf_init();
        gpio_exit_init();
    }
    break;
    case SERVICE_ADDED:
    {
        service_flag++;
        switch (service_flag)
        {
        case 1:
            gatt_manager_svc_register(evt->service_added.start_hdl, DIS_SVC_ATT_NUM, &dis_server_svc_env);
            dev_manager_add_service((struct svc_decl *)&dis_server_svc_decl_fourth_svc);
            break;
        case 2:
            gatt_manager_svc_register(evt->service_added.start_hdl, FIRST_SVC_ATT_NUM_V, &dis_server_svc_user_fourth_svc_env);
            dev_manager_add_service((struct svc_decl *)&dis_server_svc_first);
            break;
        case 3:
            gatt_manager_svc_register(evt->service_added.start_hdl, FOUTH_SVC_ATT_NUM, &dis_server_svc_first_env);
            dev_manager_add_service((struct svc_decl *)&dis_server_svc_second);
            break;
        case 4:
            gatt_manager_svc_register(evt->service_added.start_hdl, SECOND_SVC_ATT_NUM, &dis_server_svc_second_env);
            dev_manager_add_service((struct svc_decl *)&dis_server_svc_third);
            break;
        case 5:
            gatt_manager_svc_register(evt->service_added.start_hdl, THIRD_SVC_ATT_NUM, &dis_server_svc_third_env);
            dev_manager_add_service((struct svc_decl *)&atv_voice_svc_user);
            break;
        case 6:
        {
            gatt_manager_svc_register(evt->service_added.start_hdl, ATV_VOICE_SVC_ATT_NUM, &dis_server_svc_atv_voice_env);
            struct bas_db_cfg db_cfg = {
                .ins_num = 1,
                .ntf_enable[0] = 1,
            };
            dev_manager_prf_bass_server_add(NO_SEC, &db_cfg, sizeof(db_cfg));
        }
        break;
        default:
            break;
        }
    }
    break;
    case PROFILE_ADDED:
        profile_flag++;
        prf_added_handler(&evt->profile_added);
        LOG_I("PROFILE_FLAG = %d", profile_flag);
        break;
    case ADV_OBJ_CREATED:
        LS_ASSERT(evt->obj_created.status == 0);
        adv_obj_hdl = evt->obj_created.handle;
        start_adv();
        break;
    case ADV_STOPPED:
        break;
    case SCAN_STOPPED:

        break;
    default:

        break;
    }
}

static void first_timer_cb(void *param)
{
    if(hid_connect_id != 0xff)
    {
        builtin_timer_stop(first_timer_inst);
        uint16_t handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, CONTROL_VAL);
        gatt_manager_server_send_notification(hid_connect_id, handle, mic_open_error, sizeof(mic_open_error), NULL);
        LOG_I("TIMEOUT 1");
    }
}

static void second_timer_cb(void *param)
{
    if(hid_connect_id != 0xff)
    {
        builtin_timer_stop(second_timer_inst);
        atv_pdm_off();
        mic_open_ntf_flag = false;
        uint16_t handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, CONTROL_VAL);
        gatt_manager_server_send_notification(hid_connect_id, handle, audio_end, sizeof(audio_end), NULL);
        LOG_I("TIMEOUT 2");
    }
}

static void atv_pdm_on(void)
{
    Adpcm_FrameEncode_Restart(&audioHeader);
    HAL_PDM_Start(&hdmic);
    sync_atv_voice = true;
}

static void atv_pdm_off(void)
{
    sync_atv_voice = false;
    sync_atv_voice_count = 0;
    HAL_PDM_Stop(&hdmic);
}
uint8_t get_cur_connected(uint8_t *con_idx)
{
    *con_idx = hid_connect_id;
    return (hid_connect_id != 0xff);
}

uint8_t get_cur_connected_state(void)
{
    uint8_t connect_idx1 = 0;
    connect_idx1 = hid_connect_id;
    return (connect_idx1 != 0xff);
}



static void data_tx_buf_init(void)
{
    for (uint16_t i = 0; i < DATA_ARRAY_NUM - 1; i++)
    {
        data_element_array[i].list_header.next = (co_list_hdr_t *)&data_element_array[i+1];
        co_list_push_back(&tx_unused_list, &data_element_array[i].list_header);
    }
    data_element_array[DATA_ARRAY_NUM - 1].list_header.next = NULL;
    co_list_push_back(&tx_unused_list, &data_element_array[DATA_ARRAY_NUM - 1].list_header);
}

static void init_two_lists(void)
{
    uint16_t num_available_used_list = co_list_size(&tx_used_list);
    if (num_available_used_list > 0)
    {
        for (uint16_t i = 0; i < num_available_used_list; i++)
        {
            struct co_list_hdr *item_ptr = co_list_pop_front(&tx_used_list);
            co_list_push_back(&tx_unused_list, item_ptr);
        }
    }
    else
    {
        LOG_I("num_available_used_list EMPTY");
    }
    
}

void data_generator(uint8_t *buff, uint8_t length)
{
    uint16_t num_available = co_list_size(&tx_unused_list);
    if (num_available >= DATA_PACKET_COUNT_GENERATE_EACH_TIME)
    {
        uint16_t offset = 0;
        for (uint16_t i = 0; i < DATA_PACKET_COUNT_GENERATE_EACH_TIME; i++)
        {
            struct co_list_hdr *item_ptr = co_list_pop_front(&tx_unused_list);
            struct data_element *temp_element = CONTAINER_OF(item_ptr, struct data_element, list_header);
            uint8_t memcpy_length = DATA_ELEMENT_SIZE < length ? DATA_ELEMENT_SIZE : length;
            temp_element->length = memcpy_length;
            length -= memcpy_length;
            memcpy(temp_element->buf, buff + offset, temp_element->length);
            offset += temp_element->length;
            co_list_push_back(&tx_used_list, item_ptr);
        }
    }
    else
    {
       LOG_I("avail buf low %d", num_available);
    }

}
static void send_ntf_once(void)
{
    if (!co_list_is_empty(&tx_used_list))
    {
        struct co_list_hdr *item_ptr = co_list_pop_front(&tx_used_list);
        struct data_element *temp_element = CONTAINER_OF(item_ptr, struct data_element, list_header); 
        send_voice_data_handle = gatt_manager_get_svc_att_handle(&dis_server_svc_atv_voice_env, READ_VAL);
        gatt_manager_server_send_notification(hid_connect_id, send_voice_data_handle, temp_element->buf, temp_element->length, NULL);
        memset(temp_element->buf,0,temp_element->length);
        co_list_push_back(&tx_unused_list, item_ptr); 
        atv_voice_ntf_done = false;
    }
    else
    {
        // LOG_I("----co_list_is_empty----");
    }
    
}

static void data_sender(void)
{
    if (atv_voice_ntf_done)
    {
        send_ntf_once();
    }   
}

void HAL_PDM_DMA_CpltCallback(PDM_HandleTypeDef *hpdm,uint8_t ch_idx,uint8_t buf_idx)
{
    if (get_cur_connected_state())
    {
        if (buf_idx)
        {
            Adpcm_FrameEncode_Google_TV_Audio((int16_t *)pdm_data_receive.Bufptr[1], EncodeBuffer, &audioHeader, FRAME_BUF_SIZE);
        }
        else
        {
            Adpcm_FrameEncode_Google_TV_Audio((int16_t *)pdm_data_receive.Bufptr[0], EncodeBuffer, &audioHeader, FRAME_BUF_SIZE);
        }
        adpcm_ntf_buf[0] = ((audioHeader.frame_number & 0xff00) >> 8);
        adpcm_ntf_buf[1] = ((audioHeader.frame_number & 0xff) - 1);
        adpcm_ntf_buf[2] = audioHeader.remote_id;
        adpcm_ntf_buf[3] = (audioHeader.adpcmVal.previous_predict_adpcm & 0xff00) >> 8;
        adpcm_ntf_buf[4] = (audioHeader.adpcmVal.previous_predict_adpcm & 0xff);
        adpcm_ntf_buf[5] = audioHeader.adpcmVal.tableIndex;
        memcpy((uint8_t *)&adpcm_ntf_buf[6], EncodeBuffer, 128);
        data_generator(adpcm_ntf_buf, 134);
    }
}
void dmic_pdm_dma_init(void)
{
    
    hdmic.DMAC_Instance = &dmac1_inst;
    hdmic.Env.DMA.Channel[0] = 1;
    // hdmic.Env.DMA.Channel[1] = 2;
    pdm_data_receive.Bufptr[0] = (uint16_t *)Buf0;
    pdm_data_receive.Bufptr[1] = (uint16_t *)Buf1;
    HAL_PDM_PingPong_Transfer_Config_DMA(&hdmic,&pdm_data_receive,NULL,FRAME_BUF_SIZE);
    
}

void dmic_pdm_init(void)
{
    pinmux_pdm_clk_init(DMIC_CLK_IO);
    pinmux_pdm_data0_init(DMIC_DATA_IO);
    hdmic.Instance = LSPDM;
    PDM_Init_TypeDef Init = 
    {
        .fir = PDM_FIR_COEF_16KHZ,
        .cfg = {
            .clk_ratio = PDM_CLK_RATIO(PDM_CLK_KHZ),
            .sample_rate = PDM_SAMPLE_RATE(PDM_CLK_KHZ,PDM_SAMPLE_RATE_HZ),
            .cap_delay = 30,
            .data_gain = 6,
        },
        .mode = PDM_MODE_Mono,
    };
    HAL_PDM_Init(&hdmic,&Init);
}

static uint8_t open_mic_buf[4] = {0x21, 0x02, 0x00, 0x00};
static uint8_t clear_open_mic_buf[4] = {0};
static void keyscan_timer_cb(void *param)
{
    if (hid_connect_id != 0xff)
    {
        if (io_read_pin(PB15))
        {
            search_key_pressed = true;
            app_hid_send_keyboard_report(KEY_VOICE_REPORT_IDX, (uint8_t *)&open_mic_buf[0], 4, hid_connect_id);
            app_hid_send_keyboard_report(KEY_VOICE_REPORT_IDX, clear_open_mic_buf, 4, hid_connect_id);
        }
    }
}

void gpio_exit_init(void)
{
    io_cfg_input(PB15);
    io_exti_config(PB15, INT_EDGE_RISING);
}

void io_exti_callback(uint8_t pin,exti_edge_t edge)
{
    switch (pin)
    {
    case PB15:
    {
        if (keyscan_timer_inst)
        {
            builtin_timer_start(keyscan_timer_inst, KEYSCAN_TIMER_TIMEOUT, NULL);
        }
        else
        {
            keyscan_timer_inst = builtin_timer_create(keyscan_timer_cb);
        }
    }
    break;
    default:
        break;
    }
}

int main()
{
    sys_init_app();
    ble_init();
    dev_manager_init(dev_manager_callback);
    gap_manager_init(gap_manager_callback);
    gatt_manager_init(gatt_manager_callback);
    ble_loop();
}
