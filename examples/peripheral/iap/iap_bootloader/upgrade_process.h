#ifndef _UPGRADE_PROCESS_H
#define _UPGRADE_PROCESS_H

#include "platform.h"

typedef void (*APP_FUNC)();

typedef struct
{
#define APP_CONFIG_CODE_SIGN 0X11223344

    uint32_t code_sign;
    uint32_t code_len;

} app_config_t;

void get_app_config(uint8_t *buffer);
bool earse_app_code(void);
bool sign_app_code(uint8_t *p_data, uint32_t sign_code_len);
bool write_app_code(uint8_t *p_data, uint32_t code_offset);
void jump_to_app(void);
bool check_application(void);

#endif