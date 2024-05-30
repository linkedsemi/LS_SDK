#ifndef TMALL_LIGHT_CFG_H_
#define TMALL_LIGHT_CFG_H_

#include "ls_hal_timer.h"
#include "le501x.h"
#include "platform.h"
#include "reg_rcc.h"
#include "ls_hal_uart.h"
#include "field_manipulate.h"
#include "ls_soc_gpio.h"

#include <string.h>

#define TIMx   LSGPTIMB
#define LIGHT_LED_1                  (PB08)
#define LIGHT_LED_2                  (PA01)
#define LIGHT_LED_3                  (PB09)
#define LIGHT_BUTTON_1               (PA07)
#define LIGHT_BUTTON_2               (PB15)
#define LIGHT_BUTTON_3               (PA08)

#define GENERIC_LEVEL_MIN (-32767-1)

struct light_state
{
    uint16_t led_idx;
    uint8_t onoff_state;
    uint16_t level;
};

void ls_mesh_pwm_init(void);
void ls_mesh_light_set_lightness(uint16_t level, uint16_t const led_id);
void ls_mesh_light_set_onoff(uint8_t on_off, uint16_t const led_id);
uint16_t ls_mesh_light_get_lightness(uint16_t const led_id);
uint8_t ls_mesh_light_get_onoff(uint16_t const led_id);
void light_button_init(void);
void ls_button_timer_init(void);

#endif
