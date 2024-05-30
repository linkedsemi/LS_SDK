#include "tmall_light_cfg.h"
#include "ls_soc_gpio.h"

TIM_HandleTypeDef light_tim_hdl;
TIM_OC_InitTypeDef light_tim_cfg;
static struct light_state tmall_light_state;

static void light_control(bool lightness_flag)
{
    if((!lightness_flag) && (tmall_light_state.onoff_state == 0))
    {
        light_tim_cfg.Pulse = 0;

        HAL_TIM_PWM_ConfigChannel(&light_tim_hdl, &light_tim_cfg, TIM_CHANNEL_1); 
        HAL_TIM_PWM_Start(&light_tim_hdl, TIM_CHANNEL_1);

        HAL_TIM_PWM_ConfigChannel(&light_tim_hdl, &light_tim_cfg, TIM_CHANNEL_2); 
        HAL_TIM_PWM_Start(&light_tim_hdl, TIM_CHANNEL_2);
    }
    else
    {
        light_tim_cfg.Pulse = tmall_light_state.level >> 8;
        
        HAL_TIM_PWM_ConfigChannel(&light_tim_hdl, &light_tim_cfg, TIM_CHANNEL_1); 
        HAL_TIM_PWM_Start(&light_tim_hdl, TIM_CHANNEL_1);
        
        HAL_TIM_PWM_ConfigChannel(&light_tim_hdl, &light_tim_cfg, TIM_CHANNEL_2); 
        HAL_TIM_PWM_Start(&light_tim_hdl, TIM_CHANNEL_2);
    }
}

void tmall_light_set_lightness(uint16_t level)
{
    if(tmall_light_state.level != level)
    {
        tmall_light_state.onoff_state = 1;
        tmall_light_state.level = level;
        light_control(true);
    }
}

void tmall_light_set_onoff(uint8_t on_off)
{
    if(tmall_light_state.onoff_state != on_off)
    {
        tmall_light_state.onoff_state = on_off;
        light_control(false);
    }
}

uint8_t tmall_light_get_onoff(void)
{
    return tmall_light_state.onoff_state;
}

uint16_t tmall_light_get_lightness(void)
{
    return tmall_light_state.level;
}

void tmall_light_init(void)
{
    uint16_t level_t = 0x55FF;
    light_tim_hdl.Instance = TIMx;

    pinmux_gptimb1_ch1_init(PA00,true,0);
	pinmux_gptimb1_ch2_init(PA01,true,0);
  
    light_tim_hdl.Init.Prescaler = SDK_HCLK_MHZ-1;
    light_tim_hdl.Init.Period = 249;
    light_tim_hdl.Init.ClockDivision = 0;
    light_tim_hdl.Init.CounterMode = TIM_COUNTERMODE_UP;
    light_tim_hdl.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Init(&light_tim_hdl);

    light_tim_cfg.OCMode = TIM_OCMODE_PWM1;
    light_tim_cfg.OCPolarity = TIM_OCPOLARITY_HIGH;
    light_tim_cfg.OCFastMode = TIM_OCFAST_DISABLE;

    tmall_light_set_lightness(level_t);
}

