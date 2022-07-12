#ifndef OTA_SETTINGS_H_
#define OTA_SETTINGS_H_
#include <stdint.h>
#include <stdbool.h>
#include "prf_fotas.h"

void ota_settings_erase(void);

bool ota_settings_erase_req_get(void);

void ota_settings_erase_req_set(void);

bool ota_boot_addr_get(uint32_t *addr);

void ota_boot_addr_set(uint32_t addr);

bool ota_copy_info_get(struct fota_copy_info *ptr);

void ota_copy_info_set(struct fota_copy_info *ptr);

void ota_copy_done_set(void);

#endif
