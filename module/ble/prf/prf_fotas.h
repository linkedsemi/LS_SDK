#ifndef PRF_FOTAS_H_
#define PRF_FOTAS_H_
#include <stdint.h>
#include <stdbool.h>

enum fotas_evt_type
{
    FOTAS_START_REQ_EVT,
    FOTAS_PROGRESS_EVT,
    FOTAS_FINISH_EVT,
};

enum fota_start_cfm_status
{
    FOTA_REQ_ACCEPTED,
    FOTA_REQ_REJECTED,
};

struct fota_signature
{
    uint8_t data[64];
};

struct fw_digest
{
    uint8_t data[32];
};

struct fota_image_info
{
    uint32_t base;
    uint32_t size;
};

struct fotas_start_req_evt
{
    struct fota_signature *signature;
    struct fw_digest *digest;
    struct fota_image_info *new_image;
    uint16_t segment_data_max_length;
};

struct fotas_progress_evt
{
    uint16_t current_sector;
    uint8_t current_segment;
};

struct fota_copy_info
{
    uint32_t fw_copy_src_addr;
    uint32_t fw_copy_dst_addr;
    uint32_t fw_copy_size;
};

#define FOTA_STATUS_MASK 0x1
#define FOTA_REBOOT_MASK 0x2
#define FOTA_SETTINGS_ERASE_MASK 0x4

struct fotas_finish_evt
{
    struct fota_copy_info copy;
    uint32_t boot_addr;
    uint8_t status;
};

union fotas_evt_u
{
    struct fotas_start_req_evt fotas_start_req;
    struct fotas_finish_evt fotas_finish;
    struct fotas_progress_evt fotas_progress;
};


void prf_fota_server_callback_init(void (*evt_cb)(enum fotas_evt_type,union fotas_evt_u *));

void dev_manager_prf_fota_server_add(uint8_t sec_lvl);

void prf_fotas_start_confirm(enum fota_start_cfm_status status);

uint8_t prf_fotas_get_current_conidx(void);

#endif

