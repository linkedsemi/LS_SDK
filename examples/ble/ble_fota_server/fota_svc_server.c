#define LOG_TAG "OTA_SERVER"
#include <string.h>
#include "common.h"
#include "platform.h"
#include "builtin_timer.h"
#include "ls_dbg.h"
#include "ls_ble.h"
#include "reg_base_addr.h"
#include "tinycrypt/sha256.h"
#include "spi_flash.h"
#include "fota_svc_server.h"
#include "log.h"

#define FOTA_RESET_TIMEOUT 1000 // 1 second
#define FOTA_SVC_DATA_MAX_LEN (USER_MAX_MTU - 3)
enum fotas_stat
{
    FOTAS_IDLE,
    FOTAS_BUSY,
    FOTAS_STATE_MAX,
};

enum fotas_ctrl_type
{
    FOTAS_SIGNATURE_CMD,
    FOTAS_DIGEST_CMD,
    FOTAS_START_REQ,
    FOTAS_START_RSP,
    FOTAS_NEW_SECTOR_CMD,
    FOTAS_INTEGRITY_CHECK_REQ,
    FOTAS_INTEGRITY_CHECK_RSP,
};

enum fotas_cfm_status
{
    FOTAS_CFM_STATUS_NO_ERROR,
    FOTAS_CFM_STATUS_BUSY,
};

enum fota_svc_att_db_handles
{
    FOTAS_IDX_CTRL_CHAR,
    FOTAS_IDX_CTRL_VAL,
    FOTAS_IDX_CTRL_CL_CFG,
    FOTAS_IDX_DATA_CHAR,
    FOTAS_IDX_DATA_VAL,
    FOTAS_IDX_NB,
};

struct fotas_finish_ind
{
    struct fota_image_info *new_image;
    bool integrity_checking_result;
};

struct fotas_env_tag
{
    uint8_t state;
    struct fota_signature signature;
    struct fw_digest digest;
    struct fota_image_info new_image;
    struct fotas_finish_ind *finish_ind;
    uint16_t segment_data_max_length;
    uint16_t start_hdl;
    uint16_t current_sector;
    uint16_t cccd_config;
    uint8_t sector_buf[FOTAS_SECTOR_SIZE/FOTAS_PAGE_SIZE][FOTAS_PAGE_SIZE];
    uint8_t ack[FOTAS_ACK_BUF_LENGTH_MAX];
    uint8_t conidx;
};

struct fota_signature_cmd
{
    uint8_t idx;
    uint8_t data[FOTAS_SIGNATURE_CMD_DATA_LENGTH];
}__attribute__((packed));

struct fota_digest_cmd
{
    uint8_t idx;
    uint8_t data[FOTAS_DIGEST_CMD_DATA_LENGTH];
}__attribute__((packed));

struct fota_start_req
{
    uint32_t new_image_base;
    uint32_t new_image_size;
    uint16_t segment_data_max_length;
}__attribute__((packed));

struct fota_start_rsp
{
    uint8_t status;
}__attribute__((packed));

struct fota_new_sector_cmd
{
    uint16_t sector_idx;
}__attribute__((packed));

struct fota_integrity_check_req
{
    uint8_t dummy;
}__attribute__((packed));

struct fota_integrity_check_rsp
{
    uint8_t status;
}__attribute__((packed));

struct fota_ctrl
{
    enum fotas_ctrl_type type;
    union {
        struct fota_signature_cmd signature;
        struct fota_digest_cmd digest;
        struct fota_start_req start_req;
        struct fota_start_rsp start_rsp;
        struct fota_new_sector_cmd new_sector;
        struct fota_integrity_check_req integrity_check_req;
        struct fota_integrity_check_rsp integrity_check_rsp;
    }__attribute__((packed)) u;
}__attribute__((packed));

struct fota_data_att
{
    uint8_t segment_id;
    uint8_t data[];
}__attribute__((packed));

static const uint8_t att_decl_char_array[] = {0x03,0x28};
static const uint8_t att_desc_client_char_cfg_array[] = {0x02,0x29};
static const uint8_t ls_fota_svc_uuid_16[] = {0x00, 0x26};
static const uint8_t ls_fota_ctrl_char_uuid_16[] = {0x00, 0x70};
static const uint8_t ls_fota_data_char_uuid_16[] = {0x01, 0x70};

static const struct att_decl ls_ota_att_decl[FOTAS_IDX_NB] =
{
    [FOTAS_IDX_CTRL_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,   
        .char_prop.rd_en = 1,
    },
    [FOTAS_IDX_CTRL_VAL] = {
        .uuid = ls_fota_ctrl_char_uuid_16,
        .s.max_len = sizeof(struct fota_ctrl),
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.ind_en = 1,
        .char_prop.wr_req = 1,
    },
    [FOTAS_IDX_CTRL_CL_CFG] = {
        .uuid = att_desc_client_char_cfg_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1,
        .char_prop.wr_req = 1,
    },
    [FOTAS_IDX_DATA_CHAR] = {
        .uuid = att_decl_char_array,
        .s.max_len = 0,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.rd_en = 1, 
    },
    [FOTAS_IDX_DATA_VAL] = {
        .uuid = ls_fota_data_char_uuid_16,
        .s.max_len = FOTA_SVC_DATA_MAX_LEN,
        .s.uuid_len = UUID_LEN_16BIT,
        .s.read_indication = 1,
        .char_prop.wr_cmd = 1,
        .char_prop.rd_en = 1,
    },
};
static const struct svc_decl ls_ota_server_svc =
{
    .uuid = ls_fota_svc_uuid_16,
    .att = (struct att_decl*)ls_ota_att_decl,
    .nb_att = FOTAS_IDX_NB,
    .uuid_len = UUID_LEN_16BIT,
};
static struct gatt_svc_env ls_ota_svc_env;

static struct fotas_env_tag fotas_env;
static struct builtin_timer *fotas_rsp_timer = NULL;
/**************************************************************************************************************************/
#if FW_ECC_VERIFY
const uint8_t fotas_pub_key[64];
bool fw_signature_check(struct fw_digest *digest,struct fota_signature *signature)
{
    return uECC_verify(fotas_pub_key, digest->data, sizeof(digest->data), signature->data, uECC_secp256r1());
}
#else
bool fw_signature_check(struct fw_digest *digest,struct fota_signature *signature)
{
    return true;
}
#endif

static void fota_state_set(uint8_t state)
{
    LS_ASSERT(state < FOTAS_STATE_MAX);
    fotas_env.state = state;
}
static uint8_t fota_state_get(void)
{
    return fotas_env.state;
}
static void fotas_flash_cleanup(void)
{
    uint32_t size = fotas_env.new_image.size;
    uint32_t offset = fotas_env.new_image.base - FLASH_BASE_ADDR;
    while(size)
    {
        spi_flash_sector_erase(offset);
        if(size > FLASH_SECTOR_SIZE)
        {
            size -= FLASH_SECTOR_SIZE;
            offset += FLASH_SECTOR_SIZE;
        }else
        {
            break;
        }
    }
}
static void fotas_timer_cb(void *param)
{
    if(fotas_env.finish_ind->integrity_checking_result)
    {
        if(fotas_env.new_image.base != get_app_image_base())
        {
            ota_copy_info_set(&fotas_env.new_image);
        }
        else
        {
            ota_settings_erase();
        }
        platform_reset(RESET_OTA_SUCCEED);
    }else
    {
        platform_reset(RESET_OTA_FAILED);
    }
}
static bool fw_digest_check(void)
{
    struct tc_sha256_state_struct sha256;
    uint8_t buf[TC_SHA256_BLOCK_SIZE];
    uint8_t digest[TC_SHA256_DIGEST_SIZE];
    tc_sha256_init(&sha256);
    uint32_t size = fotas_env.new_image.size;
    uint32_t offset = fotas_env.new_image.base - FLASH_BASE_ADDR;
    while(size)
    {
        uint16_t length;
        if(size > sizeof(buf))
        {
            size -= sizeof(buf);
            length = sizeof(buf);
        }else
        {
            length = size;
            size = 0;
        }
        spi_flash_quad_io_read(offset,buf, length);
        tc_sha256_update(&sha256,buf, length);
        offset += length;
    }
    tc_sha256_final(digest, &sha256);
    LOG_HEX(digest,TC_SHA256_DIGEST_SIZE);
    LOG_HEX(fotas_env.digest.data,TC_SHA256_DIGEST_SIZE);
    return memcmp(digest,fotas_env.digest.data,TC_SHA256_DIGEST_SIZE) ? false : true;
}
static void program_last_sector_to_flash(void)
{
    uint8_t i;
    for(i = 0; i< FOTAS_SECTOR_SIZE/FOTAS_PAGE_SIZE ; ++i)
    {
        spi_flash_quad_page_program(fotas_env.new_image.base - FLASH_BASE_ADDR + fotas_env.current_sector * FOTAS_SECTOR_SIZE +
            i*FOTAS_PAGE_SIZE, fotas_env.sector_buf[i], FOTAS_PAGE_SIZE);
    }
}
static void foats_read_cfm_send(uint8_t con_idx, uint16_t handle, uint8_t status, uint8_t *data, uint16_t length)
{
    gatt_manager_server_read_req_reply(con_idx, handle, status, data, length);
}
void ls_ota_server_read_req_ind(uint8_t att_idx, uint8_t con_idx)
{
    switch (att_idx)
    {
    case FOTAS_IDX_DATA_VAL:
    {
        LOG_I("rd data ack");
        uint16_t handle = gatt_manager_get_svc_att_handle(&ls_ota_svc_env, FOTAS_IDX_DATA_VAL);
        foats_read_cfm_send(con_idx, handle, FOTAS_CFM_STATUS_NO_ERROR, fotas_env.ack, FOTAS_ACK_BUF_LENGTH_MAX);
    }
    break;
    case FOTAS_IDX_CTRL_CL_CFG:
    {
        uint16_t handle = gatt_manager_get_svc_att_handle(&ls_ota_svc_env, FOTAS_IDX_CTRL_CL_CFG);
        foats_read_cfm_send(con_idx, handle, FOTAS_CFM_STATUS_NO_ERROR, (uint8_t*)&fotas_env.cccd_config, sizeof(uint16_t));
    }
    break;
    case FOTAS_IDX_CTRL_VAL:
    default:
        LOG_W("rd char:%d",att_idx);
    break;
    }
}
static void fotas_send_indication(uint8_t conidx, uint8_t *data, uint16_t length)
{
    static uint16_t transaction_id = 0;
    uint16_t handle = gatt_manager_get_svc_att_handle(&ls_ota_svc_env, FOTAS_IDX_CTRL_VAL);
    gatt_manager_server_send_indication(conidx, handle, (void *)data, length, &transaction_id);
    transaction_id++;
}
static void fotas_send_start_rsp(uint8_t conidx, uint8_t status)
{
    struct fota_ctrl start_rsp;
    start_rsp.type = FOTAS_START_RSP;
    start_rsp.u.start_rsp.status = status;
    fotas_send_indication(conidx, (void *)&start_rsp, sizeof(start_rsp));
}
static void fotas_integrity_check_rsp_ind_send(uint8_t conidx,uint8_t status)
{
    struct fota_ctrl integrity_check_rsp;
    integrity_check_rsp.type = FOTAS_INTEGRITY_CHECK_RSP;
    integrity_check_rsp.u.integrity_check_rsp.status = status;
    fotas_send_indication(conidx, (void *)&integrity_check_rsp, sizeof(integrity_check_rsp));
}
static uint8_t ctrl_pkt_dispatch(const uint8_t *data,uint16_t length,uint8_t conidx)
{
    struct fota_ctrl *ctrl = (struct fota_ctrl *)data;
    LOG_I("ctrl type:%d",ctrl->type);
    uint8_t cfm_status = FOTAS_CFM_STATUS_NO_ERROR;
    switch(ctrl->type)
    {
    case FOTAS_SIGNATURE_CMD:
        memcpy(&fotas_env.signature.data[ctrl->u.signature.idx*FOTAS_SIGNATURE_CMD_DATA_LENGTH],ctrl->u.signature.data,FOTAS_SIGNATURE_CMD_DATA_LENGTH);
    break;
    case FOTAS_DIGEST_CMD:
        memcpy(&fotas_env.digest.data[ctrl->u.digest.idx*FOTAS_DIGEST_CMD_DATA_LENGTH],ctrl->u.digest.data,FOTAS_DIGEST_CMD_DATA_LENGTH);
    break;
    case FOTAS_START_REQ:
        if(fota_state_get()==FOTAS_IDLE)
        {
            fota_state_set(FOTAS_BUSY);
            ota_settings_write(DOUBLE_BACKGROUND); 
            fotas_env.conidx = conidx;
            fotas_env.new_image.base = ctrl->u.start_req.new_image_base;
            fotas_env.new_image.size = ctrl->u.start_req.new_image_size;
            fotas_env.segment_data_max_length = ctrl->u.start_req.segment_data_max_length;
            enum fota_start_cfm_status status;
            if(fw_signature_check(&fotas_env.digest, &fotas_env.signature))
            {
                status = FOTA_REQ_ACCEPTED;
                fotas_flash_cleanup();
            }else
            {
                status = FOTA_REQ_REJECTED;
            }
            fotas_send_start_rsp(conidx, status);
            if (fotas_rsp_timer == NULL)
            {
                fotas_rsp_timer = builtin_timer_create(fotas_timer_cb);
            }
        }
        else
        {
            cfm_status = FOTAS_CFM_STATUS_BUSY;
        }
    break;
    case FOTAS_NEW_SECTOR_CMD:
    {
        if(ctrl->u.new_sector.sector_idx)
        {
            program_last_sector_to_flash();
        }
        fotas_env.current_sector = ctrl->u.new_sector.sector_idx;
        memset(fotas_env.ack,0,FOTAS_ACK_BUF_LENGTH_MAX);
        //LOG_I("new sector,%d,%d",fotas_env.current_sector,fotas_env.start_hdl);
    }
    break;
    case FOTAS_INTEGRITY_CHECK_REQ:
    {
        uint16_t last_sector_size = fotas_env.new_image.size % FOTAS_SECTOR_SIZE;
        if(last_sector_size)
        {
            memset((uint8_t *)fotas_env.sector_buf + last_sector_size, 0xff, FOTAS_SECTOR_SIZE - last_sector_size);
        }
        program_last_sector_to_flash();
        fotas_env.finish_ind->integrity_checking_result = fw_digest_check();
        uint8_t digest_check_status = fotas_env.finish_ind->integrity_checking_result ? 0 : 0x80;
        fotas_integrity_check_rsp_ind_send(conidx, digest_check_status);
        if (fotas_rsp_timer != NULL)
        {
            builtin_timer_start(fotas_rsp_timer, FOTA_RESET_TIMEOUT, NULL);
        }
        fota_state_set(FOTAS_IDLE);
    }
    break;
    default:
        LS_ASSERT(0);
    break;
    }
    return cfm_status;
}
void ls_ota_server_write_req_ind(struct gatt_server_write_req *wr_req, uint8_t con_idx)
{
    uint8_t att_idx = wr_req->att_idx;
    uint16_t length = wr_req->length;
    uint8_t const *value = wr_req->value;
    LOG_I("write req,start_hdl:%d,att_db_idx:%d", fotas_env.start_hdl, att_idx);
    uint8_t cfm_status = FOTAS_CFM_STATUS_NO_ERROR;
    switch (att_idx)
    {
    case FOTAS_IDX_CTRL_VAL:
        cfm_status = ctrl_pkt_dispatch(value, length, con_idx);
    break;
    case FOTAS_IDX_CTRL_CL_CFG:
        LS_ASSERT(length == 2);
        LOG_I("desc_cfg:%d,%d,%d", att_idx, length,*value);
        memcpy(&fotas_env.cccd_config, value, length);
    break;
    case FOTAS_IDX_DATA_VAL:
    {
        struct fota_data_att *ptr = (struct fota_data_att *)value;
        uint16_t len;
        if(ptr->segment_id == CEILING(FOTAS_SECTOR_SIZE, fotas_env.segment_data_max_length) - 1)
        {
            len = FOTAS_SECTOR_SIZE % fotas_env.segment_data_max_length ? FOTAS_SECTOR_SIZE % fotas_env.segment_data_max_length : fotas_env.segment_data_max_length;
        }else
        {
            len = fotas_env.segment_data_max_length;
        }
        LOG_I("segment:%d,dst %x,%d",ptr->segment_id,(uint8_t *)fotas_env.sector_buf + ptr->segment_id*fotas_env.segment_data_max_length,length);
        memcpy((uint8_t *)fotas_env.sector_buf + ptr->segment_id*fotas_env.segment_data_max_length, ptr->data, len);
        fotas_env.ack[ptr->segment_id/8] |= 1<< ptr->segment_id % 8;
        LOG_I("ack[%d] = 0x%x",ptr->segment_id/8,fotas_env.ack[ptr->segment_id/8]);
    }
    break;
    default:
        LOG_W("invalid, %d, %d", fotas_env.start_hdl, att_idx);
    break;
    }
    *wr_req->return_status = cfm_status;
}
void fotas_add_service(void)
{
    dev_manager_add_service((struct svc_decl *)&ls_ota_server_svc);
}
void fotas_register_svc(uint16_t start_hdl)
{
    gatt_manager_svc_register(start_hdl, FOTAS_IDX_NB, &ls_ota_svc_env);
}
