#include <string.h>
#include "platform.h"
#include "ls_hal_flash.h"
#include "upgrade_process.h"
#include "common.h"
#include "app_config.h"
#include "systick.h"

#if defined(LE501X)
#include "iap_sha256.h"
#else
#include "ls_hal_sha.h"
#endif

static uint32_t g_wirte_app_code_offset = 0;

void get_app_config(uint8_t *buffer)
{
    hal_flash_fast_read(APP_CONFIG_ADDR_BASE, buffer, 8);
}

bool sign_app_code(uint8_t *p_data,uint16_t data_len)
{
    app_config_t app_config;
    uint8_t sha256_code[32];
    uint8_t i;

    hal_flash_fast_read(APP_CONFIG_ADDR_BASE, (uint8_t *)&app_config, 8);

    if ((app_config.code_len == 0x00) || (app_config.code_len == 0xFFFF) || (data_len !=32) )
    {
        return false;
    }
#if defined(LE501X)
    sha256_get((uint8_t *)APP_DATA_ADDR_BASE, app_config.code_len, sha256_code);
#else
    uint32_t sha256_buffer[8];
    uint8_t j;
    HAL_LSSHA_Init();
    HAL_LSSHA_SHA256((const uint8_t *)(0x800000 + APP_DATA_ADDR_BASE), app_config.code_len, sha256_buffer);
    HAL_LSSHA_DeInit();

    for (i = 0, j = 0; i < 8; i++)
    {
        sha256_code[j++] = sha256_buffer[i];
        sha256_code[j++] = sha256_buffer[i] >> 8;
        sha256_code[j++] = sha256_buffer[i] >> 16;
        sha256_code[j++] = sha256_buffer[i] >> 24;
    }
#endif
    
    for (i = 0; i < 32; i++)
    {
        if (sha256_code[i] != p_data[i])
        {
            break;
        }
    }

    if (i != 32)
    {
        return false;
    }

    app_config.code_sign = APP_CONFIG_CODE_SIGN;

    hal_flash_sector_erase(APP_CONFIG_ADDR_BASE);
    hal_flash_page_program(APP_CONFIG_ADDR_BASE, (uint8_t *)&app_config, 8);

    return true;
}

void earse_app_code(uint8_t *p_data,uint16_t data_len)
{
    uint32_t i, block, offset;
    app_config_t app_config;

    app_config.code_len = data_len;

    block = app_config.code_len / 4096;
    if (app_config.code_len % 4096)
    {
        block++;
    }

    offset = 0;
    for (i = 0; i < block; i++)
    {
        hal_flash_sector_erase(APP_DATA_ADDR_BASE + offset);
        offset += 4096;
    }

    g_wirte_app_code_offset = 0;

    // 更新代码数据长度
    hal_flash_sector_erase(APP_CONFIG_ADDR_BASE);

    app_config.code_sign = 0xFFFFFFFF;

    hal_flash_page_program(APP_CONFIG_ADDR_BASE, (uint8_t *)&app_config, 8);
}

uint32_t write_app_code(uint8_t *p_data,uint16_t data_len)
{
    uint32_t app_offset;

    app_offset = APP_DATA_ADDR_BASE + g_wirte_app_code_offset;

    hal_flash_page_program(app_offset, p_data, data_len);

    g_wirte_app_code_offset += data_len;

    return 1;
}

bool check_application(void)
{
    app_config_t app_config;
    app_config.code_sign = 0;

    get_app_config((uint8_t *)&app_config);

    if (app_config.code_sign == APP_CONFIG_CODE_SIGN)
    {
        return true;
    }

    return false;
}

void jump_to_app(void)
{
    APP_FUNC jump2app;
    uint32_t app_addr;



    __disable_irq();
    systick_stop();
#if defined(LE501X)
    // app_addr = (APP_DATA_ADDR_BASE + 0x2000);           //skip Info Page & Second Bootloader , 0x2000
    app_addr = (APP_DATA_ADDR_BASE); // skip Info Page & Second Bootloader , 0x2000
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICPR[0] = 0xFFFFFFFF;
#else
    app_addr = (0x00800000 + APP_DATA_ADDR_BASE + 512); // skip Info Page , 0x200
    uint32_t i;
    for (i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ICPR[i] = 0xFFFFFFFF;
    }
#endif

    __enable_irq();

    // DELAY_US(500000);

    __set_PSP(*(uint32_t *)(app_addr));
    __set_MSP(*(uint32_t *)app_addr);

    #if defined(LE501X)
    memcpy((void*)0x20000000, (void*)app_addr, 188);       
    #else
    SCB->VTOR = *(__IO uint32_t *)app_addr;
    #endif

    app_addr = *(__IO uint32_t *)(app_addr + 4);
    jump2app = (APP_FUNC)app_addr;
    jump2app();
}
