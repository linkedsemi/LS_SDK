
#include "tmall_genie_ais.h"
#include "log.h"
#include "genie_crypto.h"
#include "tmall_genie_ota.h"
#include "log.h"
#include "ls_ble.h"
#include "tmall_ais_main.h"
#include "ali_dfu_port.h"

extern genie_ota_ctx_t genie_ota_ctx;
static genie_ais_ctx_t genie_ais_ctx;

static void _ais_decrypt(uint8_t *payload, uint8_t len)
{
    uint8_t dec[16];

    genie_crypto_decrypt(payload, dec);
    memcpy(payload, dec, 16);
}


#define AIS_BUF_SIZE 68	 

static void _ais_server_indicate(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len)
{
    ais_pdu_t msg;

    memset(&msg, 0, sizeof(msg));
    if (genie_ais_ctx.state == AIS_STATE_IDLE)
    {
        msg.header.enc = 1;
    }
    else
    {
        msg.header.enc = 0;
    }
    msg.header.msg_id = msg_id;
    msg.header.cmd = cmd;
    msg.header.payload_len = len;

    if (p_msg)
    {
        memcpy(msg.payload, p_msg, len);
    }

	genie_ais_gatt_indicate((uint8_t *)&msg, len+4);
}


void genie_ais_notify(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len)
{
    ais_pdu_t msg;

    memset(&msg, 0, sizeof(msg));
    if (genie_ais_ctx.state >= AIS_STATE_IDLE && genie_ais_ctx.state <= AIS_STATE_REBOOT)
    {
        msg.header.enc = 1;
    }
    else
    {
        msg.header.enc = 0;
    }

    msg.header.cmd = cmd;
    msg.header.msg_id = msg_id;
    msg.header.payload_len = len;
    if (p_msg)
    {
        memcpy(msg.payload, p_msg, len);
    }

    genie_ais_gatt_notify_message((uint8_t *)&msg, len + 4);

}

static bool _ais_msg_check_header(ais_header_t *p_msg_header)
{
    //check seq & total, in ota case, the seq & total must be 0
    if (p_msg_header->total_frame != 0 || p_msg_header->seq != 0 || p_msg_header->ver != 0 || p_msg_header->seq > p_msg_header->total_frame)
    {
        return false;
    }
    return true;
}

static bool _ais_scrt_random(uint8_t msg_id, ais_scrt_random_t *p_scrt_random)
{
    uint8_t cipher[16];

    genie_ais_ctx.state = AIS_STATE_AUTH;
    genie_ais_get_cipher(p_scrt_random->random, cipher);
    _ais_server_indicate(msg_id, AIS_SCRT_CIPHER, cipher, 16);

    return true;
}

static bool _ais_scrt_result(uint8_t msg_id, ais_scrt_result_t *p_scrt_result)
{
    uint8_t ack = 0;

    if (p_scrt_result->result == 1)
    {
        genie_ais_reset();
        genie_ais_ctx.state = AIS_STATE_CONNECT;
    }
    else
    {
        genie_ais_ctx.state = AIS_STATE_IDLE;
    }

    _ais_server_indicate(msg_id, AIS_SCRT_ACK, &ack, 1);

    return true;
}


void ais_server_write_req_handle(ais_pdu_t *p_msg, uint16_t len)
{

	if (p_msg->header.cmd != AIS_OTA_DATA && !_ais_msg_check_header((ais_header_t *)p_msg))
	{
		//LOG_I("invalid msg, ignore");
	}

	if (p_msg->header.cmd != AIS_OTA_DATA)
	{
		//LOG_I("AIS Cmd:0x%02x", p_msg->header.cmd);
	}
	switch (p_msg->header.cmd)
	{
		case AIS_SCRT_RANDOM:
		//len = 4+16
		if (len == 20 && (genie_ais_ctx.state == AIS_STATE_CONNECT || genie_ais_ctx.state == AIS_STATE_IDLE))
		{
			 _ais_scrt_random(p_msg->header.msg_id,
			                             (ais_scrt_random_t *)p_msg->payload);
		}
		break;
		case AIS_SCRT_RESULT:
		//len = 4+1
		if (len == 5 && genie_ais_ctx.state == AIS_STATE_AUTH)
		{
			 _ais_scrt_result(p_msg->header.msg_id,
			                             (ais_scrt_result_t *)p_msg->payload);
		}
		break;
		case AIS_OTA_VER_REQ:
		if ((len == 20 && genie_ais_ctx.state == AIS_STATE_IDLE) || (len == 5 && genie_ais_ctx.state == AIS_STATE_CONNECT))
		{
			if (genie_ais_ctx.state == AIS_STATE_IDLE)
			{
				_ais_decrypt(p_msg->payload, 16);
			}
			 genie_ota_handle_version_request(p_msg->header.msg_id,
			                                         (ais_ota_ver_req_t *)p_msg->payload);
		}
		break;
		case AIS_OTA_FIRMWARE_REQ:
		//len = 4+16
		if (len == 20 && genie_ais_ctx.state == AIS_STATE_IDLE)
		{
			_ais_decrypt(p_msg->payload, 16);
			 genie_ota_handle_update_request(p_msg->header.msg_id,
			                                                (ais_ota_upd_req_t *)p_msg->payload);
            erase_dfu_flash();                                                
		}
		break;

		case AIS_OTA_DATA:
		if (len == sizeof(ais_header_t) + p_msg->header.payload_len && p_msg->header.ver == 0 && genie_ais_ctx.state == AIS_STATE_OTA)
		{
			genie_ota_parse_pdu(p_msg);
		}
		break;
		
		case AIS_OTA_CHECK_REQ:
		if (len == 20 && genie_ais_ctx.state == AIS_STATE_OTA)
		{
			_ais_decrypt(p_msg->payload, 16);
			genie_ota_check_firmware(p_msg->header.msg_id, (ais_ota_check_req_t *)p_msg->payload);
		}
		break;

	}

}

static void genie_ais_state_update(void)
{

    switch (genie_ais_ctx.state)
    {
    case AIS_STATE_DISCON:
        break;
    case AIS_STATE_CONNECT:
    case AIS_STATE_IDLE:
        break;
    case AIS_STATE_AUTH:
        break;
    case AIS_STATE_OTA:
        break;
    case AIS_STATE_REBOOT:
        break;
    default:
        break;
    }
}


void genie_ais_connect(void)
{
	if (genie_ais_ctx.state != AIS_STATE_REBOOT)
	{
		genie_ais_ctx.state = AIS_STATE_CONNECT;
		genie_ais_state_update();
	}
}

void genie_ais_disconnect(uint8_t reason)
{
    if (genie_ais_ctx.state != AIS_STATE_REBOOT)
    {

        genie_ais_ctx.state = AIS_STATE_DISCON;
        /* Flash is dirty, need erase */
        if (genie_ota_ctx.flash_clean == 1 &&
            genie_ota_ctx.ota_ready == 0)
        {
            erase_dfu_flash();
            genie_ota_ctx.flash_clean = 0;
        }
    }
    else
    {
        if (genie_ota_ctx.ota_flag != OTA_FLAG_SILENT)
        {
            //clear image change
            LOG_I("OTA Reboot!");
        }
    }
}

int genie_ais_state_set(uint8_t state)
{
    genie_ais_ctx.state = state;

    return 0;
}

uint8_t genie_ais_state_get(void)
{
    return genie_ais_ctx.state;
}

