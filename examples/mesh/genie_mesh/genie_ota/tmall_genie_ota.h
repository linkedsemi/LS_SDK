#ifndef __GENIE_OTA_H__
#define __GENIE_OTA_H__

#include <string.h>
#include <stdbool.h>
#include "tmall_genie_ais.h"

#define CONFIG_AIS_TOTAL_FRAME 16

#define OTA_RECV_BUF_SIZE (CONFIG_AIS_TOTAL_FRAME * 256)

enum
{
    OTA_FLAG_SILENT = 0x02,
    AIS_OTA_VER_REQ = 0x20,      //APP request get version info
    AIS_OTA_VER_RESP = 0x21,     //Response the version info request
    AIS_OTA_FIRMWARE_REQ = 0x22, //APP push firmware info
    AIS_OTA_UPD_RESP = 0x23,     //Response to APP which can update or not and have received firmware size
    AIS_OTA_STATUS = 0x24,       //Response to APP that last frame number and have received firmware size
    AIS_OTA_CHECK_REQ = 0x25,    //APP download finish,then device check firmware
    AIS_OTA_CHECK_RESP = 0x26,   //Response to APP the result of firmeware check
    AIS_OTA_DATA = 0x2f          //This is ota firmware data
};


//For pingpong OTA
enum
{
    DFU_IMAGE_A = 0,
    DFU_IMAGE_B,
    DFU_IMAGE_TOTAL = DFU_IMAGE_B,
    DFU_IMAGE_INVALID_ID,
};

typedef struct genie_ota_ctx_s
{
    uint8_t err_count;

    uint8_t last_seq;
    uint8_t total_frame;
    uint8_t except_seq;
    uint32_t rx_size;
    uint8_t len_4B;
    uint8_t data_4B[4];

    uint8_t image_type;
    uint32_t image_ver;
    uint32_t image_size;
    uint16_t image_crc16;
    uint8_t ota_flag;

    uint8_t flash_clean : 1;
    uint8_t ota_ready : 1;
    uint16_t rx_len;
    uint8_t recv_buf[OTA_RECV_BUF_SIZE];
} genie_ota_ctx_t;

typedef struct
{
    uint8_t image_type;
} __attribute__((packed)) ais_ota_ver_req_t;

typedef struct
{
    uint8_t image_type;
    uint32_t ver;
} __attribute__((packed)) ais_ota_ver_resp_t;

typedef struct
{
    uint8_t image_type;
    uint32_t ver;
    uint32_t fw_size;
    uint16_t crc16;
    uint8_t ota_flag;
} __attribute__((packed)) ais_ota_upd_req_t;

typedef struct
{
    uint8_t state;
    uint32_t rx_size;
    uint8_t total_frame;
} __attribute__((packed)) ais_ota_upd_resp_t;

typedef struct
{
    uint8_t last_seq : 4;
    uint8_t total_frame : 4;
    uint32_t rx_size;
} __attribute__((packed)) ais_ota_status_report_t;

typedef struct
{
    uint8_t state;
} __attribute__((packed)) ais_ota_check_req_t;

typedef struct
{
    uint8_t state;
} __attribute__((packed)) ais_ota_check_resp_t;



bool genie_ota_handle_update_request(uint8_t msg_id, ais_ota_upd_req_t *p_ota_req);

bool genie_ota_handle_version_request(uint8_t msg_id, ais_ota_ver_req_t *p_ver_req);

bool genie_ota_parse_pdu(ais_pdu_t *p_msg);

bool genie_ota_check_firmware(uint8_t msg_id, ais_ota_check_req_t *p_check_req);

bool genie_ota_is_ready(void);


#endif

