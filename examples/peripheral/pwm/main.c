#include "ls_msp_pwm.h"
#include "ls_hal_pwm.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define PWM_CHANNEL PWM_Channel8

static void pwm_init()
{
    LOG_I("pwm_polling init start!");
    pinmux_pwm_ch8_init(PH00);
    HAL_PWM_Init(PWM_CLK_PRE_DIV_128);

    PWM_Param param;
    param.pwm_cyc = 1000;
    param.pwm_high = 250;
    param.pwm_num = 1;
    param.pol = PWM_POLARITY_NOINVERTED;
    param.cmp = PWM_CMP_OUTVALUE_HIGH;
    param.mode = PWM_MODE_ONLY_COUNTSUP;
    param.dma_en = false;
    HAL_PWM_SetConfig(PWM_CHANNEL, &param);
}
int main(void)
{
    sys_init_none();
    pwm_init();
    HAL_PWM_Start(PWM_CHANNEL);
    while (1)
    {
    }
}

void HAL_PWM_START_Callback(pwm_channel_t channel)
{
    LOG_I("CHANNEL %d : start!", channel + 1);
    DELAY_MS(1000);
    HAL_PWM_Stop(channel);
}

void HAL_PWM_STOP_Callback(pwm_channel_t channel)
{
    LOG_I("CHANNEL %d : stop!", channel + 1);
    DELAY_MS(1000);
    HAL_PWM_Start(channel);
}
