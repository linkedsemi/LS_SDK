#include "ota_settings.h"
#include "inflash_settings.h"
#include "ls_hal_flash.h"
#include "prf_fotas.h"
#define OTA_COPY_INFO_OFFSET 128
#define OTA_COPY_INFO_RANGE 128
#define OTA_BOOT_ADDR_OFFSET 64
#define OTA_BOOT_ADDR_RANGE 64
#define OTA_SETTINGS_ERASE_REQ_OFFSET 0
#define OTA_SETTINGS_ERASE_REQ_RANGE 16
extern uint32_t get_ota_settings_offset(void);

static inline struct setting_info get_ota_copy_info()
{
    struct setting_info info = {
        .start = get_ota_settings_offset() + OTA_COPY_INFO_OFFSET,
        .range = OTA_COPY_INFO_RANGE,
        .size_by_word = sizeof(struct fota_copy_info)/sizeof(uint32_t),
    };
    return info;
}

static inline struct setting_info get_ota_boot_addr_info()
{
    struct setting_info info = {
        .start = get_ota_settings_offset() + OTA_BOOT_ADDR_OFFSET,
        .range = OTA_BOOT_ADDR_RANGE,
        .size_by_word = sizeof(uint32_t)/sizeof(uint32_t),
    };
    return info;
}

static inline struct setting_info get_ota_settings_erase_req_info()
{
    struct setting_info info = {
        .start = get_ota_settings_offset() + OTA_SETTINGS_ERASE_REQ_OFFSET,
        .range = OTA_SETTINGS_ERASE_REQ_RANGE,
        .size_by_word = sizeof(uint32_t)/sizeof(uint32_t),
    };
    return info;
}

void ota_settings_erase(void)
{
    hal_flash_sector_erase(get_ota_settings_offset());
}


bool ota_settings_erase_req_get(void)
{
    struct setting_info info = get_ota_settings_erase_req_info();
    uint32_t req_flag;
    uint32_t offset;
    return settings_get(&info,&req_flag,&offset);
}

void ota_settings_erase_req_set(void)
{
    struct setting_info info = get_ota_settings_erase_req_info();
    __attribute__((aligned(4))) uint8_t req_flag[4] = {'E','R','A','S'};
    settings_set(&info,(uint32_t *)req_flag);
}

bool ota_boot_addr_get(uint32_t *addr)
{
    struct setting_info info = get_ota_boot_addr_info();
    uint32_t offset;
    return settings_get(&info,addr,&offset);
}

void ota_boot_addr_set(uint32_t addr)
{
    struct setting_info info = get_ota_boot_addr_info();
    settings_set(&info,&addr);
}

bool ota_copy_info_get(struct fota_copy_info *ptr)
{
    struct setting_info info = get_ota_copy_info();
    uint32_t offset;
    return settings_get(&info,(void *)ptr,&offset);
}

void ota_copy_info_set(struct fota_copy_info *ptr)
{
    struct setting_info info = get_ota_copy_info();
    settings_set(&info,(void *)ptr);
}

void ota_copy_done_set(void)
{
    struct setting_info info = get_ota_copy_info();
    settings_make_invalid(&info);
}
