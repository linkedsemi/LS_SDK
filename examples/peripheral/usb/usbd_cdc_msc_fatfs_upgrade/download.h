#ifndef _DOWNLOAD_H
#define _DOWNLOAD_H

#include <stdint.h>
#include <stdbool.h>
#include "ff.h"

#define USER_FLASH_OFFSET_ADDRESS 0x41000 // 0x00800000 + 0x41000  = 260KB
#define USER_FLASH_END_ADDRESS 0x00080000     // 0x00841000 -  0x00880000 = 252KB (0x3F000)
#define USER_FLASH_CODE_SIZE 0x3F000     // 0x00841000 -  0x00880000 = 252KB (0x3F000)

#define DOWNLOAD_STEP_READY 0
#define DOWNLOAD_STEP_CHIP_ERASE 1
#define DOWNLOAD_STEP_FLASH_PROGRAM 2
#define DOWNLOAD_STEP_COMPLETE 3
#define DOWNLOAD_STEP_ERROR 4
#define DOWNLOAD_STEP_TIMEOUT 5

#define READ_MAX_BLOCK_SIZE 256

typedef struct
{
#define APP_CONFIG_CODE_SIGN_1 0x11223344
#define APP_CONFIG_CODE_SIGN_2 0xAABBCCDD

    uint32_t code_sign_1;
    uint32_t code_sign_2;

} app_config_t;

typedef struct
{
    FIL bin_file;

    uint8_t r1;
    uint8_t r2;
    uint8_t bin_file_isopen;
    uint8_t bin_download_step;

    uint32_t bin_write_offset;

    uint32_t bin_file_size;
    uint32_t bin_read_offset;
    
} download_info_data_t;

extern bool g_bin_filename_exist;
extern download_info_data_t g_download_info;

void download_info_init(void);
void download_check_bin_file(void);
void earse_app_code(bool first);
void write_app_code(void);
bool check_application(void);
void jump_to_app(void);

#endif
