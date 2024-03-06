#include <string.h>
#include "platform.h"
#include "ls_hal_flash.h"
#include "upgrade_process.h"
#include "common.h"
#include "app_config.h"
#include "systick.h"
#include "log.h"

void get_app_config(uint8_t *buffer)
{
    hal_flash_fast_read(APP_CONFIG_ADDR_BASE, buffer, 8);
}

bool sign_app_code(void)
{
    uint8_t buf[256];
    app_config_t *p_app_config;
    p_app_config = (app_config_t *)buf;
    p_app_config->code_sign = APP_CONFIG_CODE_SIGN;

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
        hal_flash_sector_erase(offset);
        offset += 4096;
    }
    return state;
}



bool write_app_code(uint8_t *p_data, uint32_t code_offset)
{
    uint32_t app_offset;
    uint8_t buf[256];

    app_offset = code_offset;
    // LOG_I("write offset:0x%04x", app_offset);
    if ((app_offset + 256) > APP_DATA_ADDR_BASE_END)
    {
        LOG_I("write err,offset:0x%04x", app_offset + 256);
        return false;
    }

    hal_flash_page_program(app_offset, p_data, 256);
    hal_flash_fast_read(app_offset, buf, 256);
    if (memcmp(p_data, buf, 256))
    {
        LOG_I("memcmp err,offset:0x%04x", app_offset);
        return false;
    }

    return true;
}

bool check_application(void)
{
    app_config_t app_config;
    app_config.code_sign = 0;
    // LOG_I("check application");
    get_app_config((uint8_t *)&app_config);

    if (app_config.code_sign == APP_CONFIG_CODE_SIGN)
    {
        // LOG_I("check application success!");
        return true;
    }
    return false;
}

void jump_to_app(void)
{
    APP_FUNC jump2app;
#if defined(LE501X) || defined(LM3050)
    uint32_t app_addr;
#endif
    __disable_irq();
    systick_stop();
#if defined(LE501X)
    app_addr = (APP_DATA_ADDR_BASE);
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICPR[0] = 0xFFFFFFFF;
#elif defined(LM3050)
    app_addr = (0x00800000 + APP_DATA_ADDR_BASE); // skip Info Page , 0x200
    uint32_t i;
    for (i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ICPR[i] = 0xFFFFFFFF;
    }
#endif
    __enable_irq();
    #if defined(LEO)
    // __set_SP((uint32_t)&app_addr);
    #else
    __set_PSP(*(uint32_t *)(app_addr));
    __set_MSP(*(uint32_t *)app_addr);
    #endif

#if defined(LE501X)
    memcpy((void *)0x20000000, (void *)app_addr, 188);
#elif defined(LM3050)
    SCB->VTOR = *(__IO uint32_t *)app_addr;
#endif

#if defined(LE501X)
    jump2app = (APP_FUNC) * (uint32_t *)(APP_DATA_ADDR_BASE + 4);
#elif defined(LM3050)
    jump2app = (APP_FUNC) * (uint32_t *)(0x00800000 + APP_DATA_ADDR_BASE + 4);
#elif defined(LEO)
    jump2app = (APP_FUNC)(uint32_t *)(0x008000000 + APP_DATA_ADDR_BASE);
#endif

    jump2app();
}
