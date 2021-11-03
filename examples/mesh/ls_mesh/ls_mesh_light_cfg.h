#ifndef _LS_MESH_LIGHT_CFG_H_
#define _LS_MESH_LIGHT_CFG_H_

#include "lstimer.h"
#include "le501x.h"
#include "platform.h"
#include "reg_rcc.h"
#include "io_config.h"
#include "field_manipulate.h"

#include <string.h>

#define TIMx   LSGPTIMB

#define LED_PIN_0 PB08
#define LED_PIN_1 PB09

struct light_state
{
	  uint16_t led_idx;
    uint8_t onoff_state;
    uint16_t level;
};

void ls_mesh_light_init(void);
void ls_mesh_light_set_lightness(uint16_t level, uint16_t const led_id);
void ls_mesh_light_set_onoff(uint8_t on_off, uint16_t const led_id);
uint16_t ls_mesh_light_get_lightness(uint16_t const led_id);
uint8_t ls_mesh_light_get_onoff(uint16_t const led_id);

#endif//_LS_MESH_LIGHT_CFG_H_
