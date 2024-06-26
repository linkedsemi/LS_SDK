#include "platform.h"
#include "ls_hal_flash.h"
#include "download.h"
#include <string.h>
#include "systick.h"
// #include "log.h"

bool g_bin_filename_exist = false;
download_info_data_t g_download_info;

const char g_bin_filename[] = "0:cdc_msc_fatfs_application.bin";

void download_info_init(void)
{
    g_download_info.bin_download_step = DOWNLOAD_STEP_READY;
    g_download_info.bin_write_offset = 0;
    g_download_info.bin_file_size = 0;
    g_download_info.bin_read_offset = 0;
    g_download_info.bin_file_isopen = false;
}
void download_check_bin_file(void)
{
    g_bin_filename_exist=false;

    FRESULT fr = f_open(&g_download_info.bin_file, g_bin_filename, FA_READ);
    if (fr == FR_OK)
    {
        f_close(&g_download_info.bin_file);
        g_bin_filename_exist = true;
    }   

    // LOG_I("bin file exits:%d",g_bin_filename_exist);
}

uint32_t download_get_file_data(uint8_t *data_buf)
{
    FRESULT fr;
    uint32_t read_length;
    uint32_t read_number;

    if (!g_download_info.bin_file_isopen)
    {
        g_download_info.bin_read_offset = 0;
        fr = f_open(&g_download_info.bin_file, g_bin_filename, FA_READ);
        if (fr == FR_OK)
        {
            g_download_info.bin_file_size = f_size(&g_download_info.bin_file);
            g_download_info.bin_file_isopen = true;
            // LOG_I("fsize:%d", g_download_info.bin_file_size);
        }
        else
        {
            // LOG_I("open error:%d", fr);
            return 0;
        }
    }

    read_length = READ_MAX_BLOCK_SIZE;
    if (g_download_info.bin_file_size < READ_MAX_BLOCK_SIZE)
    {
        read_length = g_download_info.bin_file_size;
    }
    else
    {
        if ((g_download_info.bin_file_size - g_download_info.bin_read_offset) < READ_MAX_BLOCK_SIZE)
        {
            read_length = g_download_info.bin_file_size - g_download_info.bin_read_offset;
        }
    }
    if (read_length <= 0)
    {
        // LOG_I("1 file_size:%d,read_offset:%d", g_download_info.bin_file_size, g_download_info.bin_read_offset);

        return 0;
    }

    f_read(&g_download_info.bin_file, data_buf, read_length, (UINT *)&read_number);

    if (read_number == 0)
    {
        // error
        // LOG_I("2 file_size:%d,read_offset:%d,read:%d", g_download_info.bin_file_size, g_download_info.bin_read_offset, read_length);
        return 0;
    }

    g_download_info.bin_read_offset += read_length;

    return read_length;
}

void earse_app_code(bool first)
{
#if 0    
    uint32_t offset;
    bool state = true;
    
    for (;;)
    {
        if (offset >= USER_FLASH_END_ADDRESS)
        {
            state = false;
            break;
        }
        hal_flash_sector_erase(offset);

        LOG_I("erase offset:0x%04x", offset);
        offset += 4096;
    }
    return state;
#endif
    uint32_t count = 2;

    if (first)
    {
        g_download_info.bin_write_offset = USER_FLASH_OFFSET_ADDRESS;

        if (g_download_info.bin_write_offset >= USER_FLASH_END_ADDRESS)
        {
            g_download_info.bin_download_step = DOWNLOAD_STEP_ERROR;

            if (g_download_info.bin_file_isopen)
            {
                f_close(&g_download_info.bin_file);
            }
            download_info_init();
            return;
        }
    }
    // while (count != 0)
    {
        hal_flash_sector_erase(g_download_info.bin_write_offset);

        // LOG_I("erase offset:0x%04x", g_download_info.bin_write_offset);
        g_download_info.bin_write_offset += 4096;

        if (g_download_info.bin_write_offset >= USER_FLASH_END_ADDRESS)
        {
            // LOG_I("erase complete.\r\n download begin.");
            g_download_info.bin_write_offset = USER_FLASH_OFFSET_ADDRESS;
            g_download_info.bin_download_step = DOWNLOAD_STEP_FLASH_PROGRAM;

            // break;
        }

        count--;
    }
}

bool program_app_code(void)
{
    uint32_t app_offset;
    uint32_t read_number;
    uint8_t read_buffer[READ_MAX_BLOCK_SIZE];
    uint8_t data_buffer[READ_MAX_BLOCK_SIZE];

    // Max. 256 bytes
    read_number = download_get_file_data(read_buffer);

    if (0 == read_number)
    {
        // LOG_I("read err");
        return false;
    }

    app_offset = g_download_info.bin_write_offset;
    // LOG_I("write offset:0x%04x", app_offset);
    if ((app_offset + read_number) >= USER_FLASH_END_ADDRESS)
    {
        // LOG_I("write err,offset:0x%04x", app_offset + read_number);
        return false;
    }

    hal_flash_page_program(app_offset, read_buffer, read_number);
    hal_flash_fast_read(app_offset, data_buffer, read_number);
    if (memcmp(data_buffer, read_buffer, read_number))
    {
        // LOG_I("memcmp err,offset:0x%04x", app_offset);
        return false;
    }

    g_download_info.bin_write_offset += read_number;
    // LOG_I("bin_write_offset,%d", g_download_info.bin_write_offset - USER_FLASH_OFFSET_ADDRESS);

    return true;
}

void write_app_code(void)
{
    uint32_t count = 4;
    uint32_t write_size;
    
    while (count != 0)
    {
        if (program_app_code())
        {
            write_size = g_download_info.bin_write_offset - USER_FLASH_OFFSET_ADDRESS;

            // LOG_I("write_size:%d,file_size:%d", write_size,g_download_info.bin_file_size);
            if (write_size == g_download_info.bin_file_size)
            {
                // LOG_I("DOWNLOAD_STEP_COMPLETE");

                f_close(&g_download_info.bin_file);
                download_info_init();
                g_download_info.bin_download_step = DOWNLOAD_STEP_COMPLETE;
                break;
            }
        }
        else
        {
            // write_size = g_download_info.bin_write_offset - USER_FLASH_OFFSET_ADDRESS;
            // LOG_I("DOWNLOAD_STEP_ERROR,%d", write_size);
            if (g_download_info.bin_file_isopen)
            {
                f_close(&g_download_info.bin_file);
            }
            download_info_init();
            g_download_info.bin_download_step = DOWNLOAD_STEP_ERROR;
            break;
        }
        count--;
    }
}

bool check_application(void)
{
    app_config_t app_config;

    hal_flash_fast_read(USER_FLASH_OFFSET_ADDRESS, (uint8_t *)&app_config, 8);

    if ((app_config.code_sign_1 == APP_CONFIG_CODE_SIGN_1) && (app_config.code_sign_2 == APP_CONFIG_CODE_SIGN_2))
    {
        // LOG_I("check_application success.");
        return true;
    }

    return false;
}

void jump_to_app(void)
{
    typedef void (*APP_FUNC)();
    uint32_t app_addr;
    APP_FUNC jump2app;


    __disable_irq();
    systick_stop();

    // skip user_info_config, 0x100
    // skip  Info Page , 0x200
#if defined(LM3050)
    uint32_t i;
    app_addr = (0x00800000 + USER_FLASH_OFFSET_ADDRESS + 256 + 512);

    for (i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ICPR[i] = 0xFFFFFFFF;
    }
#endif
    __enable_irq();
#if defined(LM3050)
    __set_PSP(*(uint32_t *)(app_addr));
    __set_MSP(*(uint32_t *)app_addr);
    SCB->VTOR = *(__IO uint32_t *)app_addr;
    app_addr = *(__IO uint32_t *)(app_addr + 4);
#elif defined(LEO)
    app_addr = *(__IO uint32_t *)(0x08000000 + USER_FLASH_OFFSET_ADDRESS);
#endif
    
    jump2app = (APP_FUNC)app_addr;
    jump2app();
}
