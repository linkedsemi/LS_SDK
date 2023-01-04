#ifndef TMALL_LIGHT_CFG_H_
#define TMALL_LIGHT_CFG_H_

#include "ls_hal_timer.h"
#include "le501x.h"
#include "platform.h"
#include "reg_rcc.h"
#include "field_manipulate.h"

#include <string.h>

#define TIMx   LSGPTIMB

#define LED_PORT_0 LSGPIOA
#define LED_PORT_1 LSGPIOA
#define LED_PIN_0 GPIO_PIN_0
#define LED_PIN_1 GPIO_PIN_1

struct light_state
{
    uint8_t onoff_state;
    uint16_t level;
};

void tmall_light_init(void);
void tmall_light_set_lightness(uint16_t level);
void tmall_light_set_onoff(uint8_t on_off);
uint16_t tmall_light_get_lightness(void);
uint8_t tmall_light_get_onoff(void);

#endif
