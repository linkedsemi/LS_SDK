#include <string.h>
#include "platform.h"
#include "ls_hal_flash.h"
#include "upgrade_process.h"
#include "common.h"
#include "app_config.h"
#include "systick.h"
#include "uart_process.h"
#if defined(LE501X)
#include "iap_sha256.h"
#else
#include "ls_hal_sha.h"
#endif
#include "log.h"

void get_app_config(uint8_t *buffer)
{
    LOG_I("APP_CONFIG_ADDR_BASE:%d",APP_CONFIG_ADDR_BASE);
    hal_flash_fast_read(APP_CONFIG_ADDR_BASE, buffer, 8);
}

bool sign_app_code(uint8_t *p_data, uint32_t sign_code_len)
{
    uint8_t buf[256];
    app_config_t *p_app_config;
    uint8_t sha256_code[32];
    uint8_t i;

#if defined(LE501X)
    sha256_get((uint8_t *)APP_FLASH_ADDR_BASE, sign_code_len, sha256_code);
#else
    uint32_t sha256_buffer[8];
    uint8_t j;
    HAL_LSSHA_Init();
    HAL_LSSHA_SHA256((const uint8_t *)(0x800000 + APP_FLASH_ADDR_BASE), sign_code_len, sha256_buffer);
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
        // //LOG_I(sign err");
        return false;
    }

    memset(buf, 0, sizeof(buf));
    p_app_config = (app_config_t *)buf;
    p_app_config->code_sign = APP_CONFIG_CODE_SIGN;
    p_app_config->code_len = sign_code_len;

    hal_flash_page_erase(APP_CONFIG_ADDR_BASE);
    hal_flash_page_program(APP_CONFIG_ADDR_BASE, buf, 256);

    return true;
}

bool earse_app_code(void)
{
    uint32_t offset;
    bool state = true;

    offset = APP_FLASH_ADDR_BASE;
    for (;;)
    {
        if (offset >= APP_DATA_ADDR_BASE_END)
        {
            break;
        }
        LOG_I("offset:%x", offset);
        hal_flash_sector_erase(offset);
        offset += 4096;
    }
    return state;
}

bool write_app_code(uint8_t *p_data, uint32_t code_offset)
{
    uint32_t app_offset;
    uint8_t buf[256];

    app_offset = APP_FLASH_ADDR_BASE + code_offset;
    // LOG_I("write offset:0x%04x", app_offset);
    if ((app_offset + 256) > APP_DATA_ADDR_BASE_END)
    {
        //LOG_I(write err,offset:0x%04x", app_offset + 256);
        return false;
    }

    hal_flash_page_program(app_offset, p_data, 256);
    hal_flash_fast_read(app_offset, buf, 256);
    if (memcmp(p_data, buf, 256))
    {
        //LOG_I(memcmp err,offset:0x%04x", app_offset);
        return false;
    }

    return true;
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
    app_addr = (APP_DATA_ADDR_BASE);
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICPR[0] = 0xFFFFFFFF;
#else
    app_addr = (0x00800000 + APP_DATA_ADDR_BASE); // skip Info Page , 0x200
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
    memcpy((void *)0x20000000, (void *)app_addr, 188);
#else
    SCB->VTOR = *(__IO uint32_t *)app_addr;
#endif

    app_addr = *(__IO uint32_t *)(app_addr + 4);
    // jump2app = (APP_FUNC)app_addr;
    #if defined(LE501X)
    jump2app = (APP_FUNC)*(uint32_t *)( APP_DATA_ADDR_BASE + 4);
    #else
    jump2app = (APP_FUNC)*(uint32_t *)(0x00800000 + APP_DATA_ADDR_BASE + 4);
    #endif
    
    jump2app();
}
