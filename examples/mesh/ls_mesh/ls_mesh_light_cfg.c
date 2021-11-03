#include "ls_mesh_light_cfg.h"

TIM_HandleTypeDef light_tim_hdl;
TIM_OC_InitTypeDef light_tim_cfg;
static struct light_state ls_mesh_light_state[2];

static void light_control(bool lightness_flag, uint16_t const led_id)
{
	uint32_t channel_id = (led_id == LED_PIN_0)? TIM_CHANNEL_1:TIM_CHANNEL_2;
	uint8_t *onoff_state = (led_id == ls_mesh_light_state[0].led_idx)? &(ls_mesh_light_state[0].onoff_state):&(ls_mesh_light_state[1].onoff_state);
	uint16_t *led_level = (led_id == ls_mesh_light_state[0].led_idx)? &(ls_mesh_light_state[0].level):&(ls_mesh_light_state[1].level);
    if((!lightness_flag) && (*onoff_state == 0))
    {
        light_tim_cfg.Pulse = 0;

        HAL_TIM_PWM_ConfigChannel(&light_tim_hdl, &light_tim_cfg, channel_id); 
        HAL_TIM_PWM_Start(&light_tim_hdl, channel_id);
    }
    else
    {
        light_tim_cfg.Pulse = (*led_level) >> 8;
        
        HAL_TIM_PWM_ConfigChannel(&light_tim_hdl, &light_tim_cfg, channel_id); 
        HAL_TIM_PWM_Start(&light_tim_hdl, channel_id);
       
    }
}

void ls_mesh_light_set_lightness(uint16_t level, uint16_t const led_id)
{
	  uint8_t *onoff_state = (led_id == ls_mesh_light_state[0].led_idx)? &(ls_mesh_light_state[0].onoff_state):&(ls_mesh_light_state[1].onoff_state);
	  uint16_t *led_level = (led_id == ls_mesh_light_state[0].led_idx)? &(ls_mesh_light_state[0].level):&(ls_mesh_light_state[1].level);
    if(*led_level != level)
    {
        *onoff_state = 1;
        *led_level = level;
        light_control(true,led_id);
    }
}

void ls_mesh_light_set_onoff(uint8_t on_off, uint16_t const led_id)
{
	  uint8_t *onoff_state = (led_id == ls_mesh_light_state[0].led_idx)? &(ls_mesh_light_state[0].onoff_state):&(ls_mesh_light_state[1].onoff_state);
    if(*onoff_state != on_off)
    {
        *onoff_state = on_off;
        light_control(false,led_id);
    }
}

uint8_t ls_mesh_light_get_onoff(uint16_t const led_id)
{
    return (led_id == ls_mesh_light_state[0].led_idx)?(ls_mesh_light_state[0].onoff_state):(ls_mesh_light_state[1].onoff_state);
}

uint16_t ls_mesh_light_get_lightness(uint16_t const led_id)
{
	return (led_id == ls_mesh_light_state[0].led_idx)?(ls_mesh_light_state[0].level):(ls_mesh_light_state[1].level);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* TIMx Peripheral clock enable */
    REG_FIELD_WR(RCC->APB1EN, RCC_GPTIMB1, 1);
    gptimb1_ch1_io_init(LED_PIN_0,true,0);
    gptimb1_ch1_io_init(LED_PIN_1,true,0);
}

void ls_mesh_light_init(void)
{
    uint16_t level_t = 0x55FF;
    light_tim_hdl.Instance = TIMx;

    gptimb1_ch1_io_init(LED_PIN_0, true, 0);
    gptimb1_ch1_io_init(LED_PIN_1, true, 0);

    light_tim_hdl.Init.Prescaler = 63;
    light_tim_hdl.Init.Period = 249;
    light_tim_hdl.Init.ClockDivision = 0;
    light_tim_hdl.Init.CounterMode = TIM_COUNTERMODE_UP;
    light_tim_hdl.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Init(&light_tim_hdl);

    light_tim_cfg.OCMode = TIM_OCMODE_PWM1;
    light_tim_cfg.OCPolarity = TIM_OCPOLARITY_HIGH;
    light_tim_cfg.OCFastMode = TIM_OCFAST_DISABLE;

	ls_mesh_light_state[0].led_idx = LED_PIN_0;
	ls_mesh_light_state[1].led_idx = LED_PIN_1;
    ls_mesh_light_set_lightness(level_t,ls_mesh_light_state[0].led_idx);
	ls_mesh_light_set_lightness(level_t,ls_mesh_light_state[1].led_idx);
}

