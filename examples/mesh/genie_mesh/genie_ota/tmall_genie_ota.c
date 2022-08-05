
#include "tmall_genie_ota.h"
#include "tmall_genie_ais.h"
#include "genie_crypto.h"
#include "log.h"
#include "ali_dfu_port.h"
#include "platform.h"
#include "tmall_ais_main.h"
#include "ota_settings.h"

genie_ota_ctx_t genie_ota_ctx;
#define  AIS_OTA_FLASH_BASE_ADDRESS   0x18064000
#define  AIS_APP_FLASH_BASE_ADDRESS   0x18056000


extern uint32_t ais_reboot_req_flag; 
struct fota_copy_info ais_ota_ptr;

uint32_t genie_version_appver_get(void)
{
    return ls_genie_ais_fw_version_get();
}

static void _ais_set_ota_change(void)
{
    genie_ota_ctx.ota_ready = 1;
    ais_reboot_req_flag = 0xB8A9CADB;
}


bool genie_ota_handle_version_request(uint8_t msg_id, ais_ota_ver_req_t *p_ver_req)
{
    uint8_t plaine_data[GENIE_CRYPTO_UNIT_SIZE];
    uint8_t encrypt_data[GENIE_CRYPTO_UNIT_SIZE];

    ais_ota_ver_resp_t *p_ver_resp = (ais_ota_ver_resp_t *)plaine_data;

    if (p_ver_req->image_type == 0)
    {
        memset(plaine_data, 11, sizeof(plaine_data));
        p_ver_resp->image_type = 0;
        p_ver_resp->ver = genie_version_appver_get();

        if (genie_ais_state_get() == AIS_STATE_IDLE)
        {
            genie_crypto_encrypt(plaine_data, encrypt_data);
            genie_ais_notify(msg_id, AIS_OTA_VER_RESP, encrypt_data, GENIE_CRYPTO_UNIT_SIZE);
        }
        else
        {
            genie_ais_notify(msg_id, AIS_OTA_VER_RESP, plaine_data, 5); //5=sizeof(ais_ota_ver_resp_t)
        }

        return true;
    }

    return false;
}


bool genie_ota_handle_update_request(uint8_t msg_id, ais_ota_upd_req_t *p_ota_req)
{
    uint8_t plaine_data[GENIE_CRYPTO_UNIT_SIZE];
    uint8_t encrypt_data[GENIE_CRYPTO_UNIT_SIZE];

    ais_ota_upd_resp_t *p_upd_resp = (ais_ota_upd_resp_t *)plaine_data;

    memset(plaine_data, 10, sizeof(plaine_data));
    if (p_ota_req->image_type != 0 || p_ota_req->ver <= genie_version_appver_get() ||
        ali_dfu_get_ota_partition_max_size() < p_ota_req->fw_size || 0 == p_ota_req->fw_size) //Is illeagal
    {
        p_upd_resp->state = 0;
        p_upd_resp->rx_size = 0;
    }
    else
    {
        genie_ais_state_set(AIS_STATE_OTA);
        memset(&genie_ota_ctx, 0, sizeof(genie_ota_ctx));
        genie_ota_ctx.image_type = p_ota_req->image_type;
        genie_ota_ctx.image_ver = p_ota_req->ver;
        genie_ota_ctx.image_size = p_ota_req->fw_size;
        genie_ota_ctx.image_crc16 = p_ota_req->crc16;
        genie_ota_ctx.ota_flag = p_ota_req->ota_flag;
        p_upd_resp->state = 1;

        /*If support breakpoint continue,you should set rx_size*/
        p_upd_resp->rx_size = 0;
    }

    p_upd_resp->total_frame = CONFIG_AIS_TOTAL_FRAME - 1;
    genie_crypto_encrypt(plaine_data, encrypt_data);

    genie_ais_notify(msg_id, AIS_OTA_UPD_RESP, encrypt_data, GENIE_CRYPTO_UNIT_SIZE);
    
    ais_ota_ptr.fw_copy_size = genie_ota_ctx.image_size;
    ais_ota_ptr.fw_copy_src_addr = AIS_OTA_FLASH_BASE_ADDRESS;
    ais_ota_ptr.fw_copy_dst_addr = AIS_APP_FLASH_BASE_ADDRESS;

    return true;
}

void genie_ota_status_report(void)
{
    uint8_t plaine_data[GENIE_CRYPTO_UNIT_SIZE];
    uint8_t encrypt_data[GENIE_CRYPTO_UNIT_SIZE];

    ais_ota_status_report_t *p_status_report = (ais_ota_status_report_t *)plaine_data;

    memset(plaine_data, 11, sizeof(plaine_data));
    p_status_report->last_seq = genie_ota_ctx.last_seq;
    p_status_report->total_frame = genie_ota_ctx.total_frame;
    p_status_report->rx_size = genie_ota_ctx.rx_size;


    genie_crypto_encrypt(plaine_data, encrypt_data);
    genie_ais_notify(0, AIS_OTA_STATUS, encrypt_data, GENIE_CRYPTO_UNIT_SIZE);
}


bool genie_ota_parse_pdu(ais_pdu_t *p_msg)
{
    uint8_t offset = 0;
    uint8_t *p_payload = p_msg->payload;
    uint16_t payload_len = p_msg->header.payload_len;

    if (p_msg->header.seq > p_msg->header.total_frame)
    {
        return false;
    }
   
    if (p_msg->header.seq != genie_ota_ctx.except_seq)
    {
        if (genie_ota_ctx.err_count++ == 0)
        {
            /* send fail */
            genie_ota_status_report();
            /* refresh timer */
            return true;
        }
        return false;
    }

    if (genie_ota_ctx.rx_size + p_msg->header.payload_len > genie_ota_ctx.image_size)
    {
        return false;
    }

    genie_ota_ctx.err_count = 0;
    if (p_msg->header.seq == 0)
    {
        genie_ota_ctx.rx_len = 0;
        memset(genie_ota_ctx.recv_buf, 0, sizeof(genie_ota_ctx.recv_buf));
    }

    if (genie_ota_ctx.len_4B)
    {
        memcpy(genie_ota_ctx.data_4B + genie_ota_ctx.len_4B,
               p_msg->payload, 4 - genie_ota_ctx.len_4B);

        genie_ota_ctx.flash_clean = 1;
        memcpy(genie_ota_ctx.recv_buf + genie_ota_ctx.rx_len,
               genie_ota_ctx.data_4B, 4);
        genie_ota_ctx.rx_len += 4;

        offset = 4 - genie_ota_ctx.len_4B;
        p_payload += offset;
        payload_len -= (payload_len < offset) ? payload_len : offset;
    }

    genie_ota_ctx.len_4B = payload_len & 0x0003;
    payload_len = payload_len & 0xfffc;

    if (payload_len)
    {
        genie_ota_ctx.flash_clean = 1;
        memcpy(genie_ota_ctx.recv_buf + genie_ota_ctx.rx_len, p_payload, payload_len);
        genie_ota_ctx.rx_len += payload_len;
    }

    if (genie_ota_ctx.len_4B)
    {
        memcpy(genie_ota_ctx.data_4B, p_payload + payload_len, genie_ota_ctx.len_4B);
    }

    genie_ota_ctx.last_seq = p_msg->header.seq;
    genie_ota_ctx.total_frame = p_msg->header.total_frame;
    genie_ota_ctx.rx_size += p_msg->header.payload_len;

    if (p_msg->header.seq == p_msg->header.total_frame)
    {
        ali_dfu_image_update(genie_ota_ctx.image_type,
                             genie_ota_ctx.rx_size - genie_ota_ctx.rx_len, genie_ota_ctx.rx_len,
                             (int *)genie_ota_ctx.recv_buf);
         genie_ota_ctx.rx_len = 0;
        genie_ota_ctx.except_seq = 0;
    }
    else
    {
        genie_ota_ctx.except_seq = p_msg->header.seq + 1;
    }

    if (genie_ota_ctx.rx_size == genie_ota_ctx.image_size || p_msg->header.seq == p_msg->header.total_frame)
    {
        genie_ota_status_report();
    }

    return true;
}

bool genie_ota_check_firmware(uint8_t msg_id, ais_ota_check_req_t *p_check_req)
{
    uint16_t crc16 = 0;
    uint8_t plaine_data[GENIE_CRYPTO_UNIT_SIZE];
    uint8_t encrypt_data[GENIE_CRYPTO_UNIT_SIZE];
    ais_ota_check_resp_t *p_check_resp = (ais_ota_check_resp_t *)plaine_data;

    genie_ais_state_set(AIS_STATE_IDLE);

    if (p_check_req->state == 1)
    {
        memset(plaine_data, 15, sizeof(plaine_data));

        p_check_resp->state = dfu_check_checksum(genie_ota_ctx.image_type, &crc16);

        if (p_check_resp->state && crc16 != genie_ota_ctx.image_crc16)
        {
            p_check_resp->state = 0;
        }

        if (p_check_resp->state)
        {
            ota_settings_erase_req_set();
            ota_copy_info_set(&ais_ota_ptr);
            genie_ais_state_set(AIS_STATE_REBOOT);
            _ais_set_ota_change();
            LOG_I("ota success, reboot in 3s!");
        }
        else
        {
            LOG_I("ota failed");
        }

        genie_crypto_encrypt(plaine_data, encrypt_data);
        genie_ais_notify(msg_id, AIS_OTA_CHECK_RESP, encrypt_data, GENIE_CRYPTO_UNIT_SIZE);

        return true;
    }
    else
    {
        return false;
    }
}



