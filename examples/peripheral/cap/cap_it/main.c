#include "app_config.h"
#include "ls_msp_cap.h"
#include "ls_hal_cap.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define         _CAP_CHANNEL5         CAP_Channel5
#define         _CAP_CHANNEL7        CAP_Channel7
CAP_Param cap_param;
static void ls_cap_init(void)
{
    cap_param.cap_pre_div = 7;
    HAL_CAP_Init(&cap_param);
}

void ioinit()
{
    io_cfg_output(PA01);
    io_clr_pin(PA01);
}

int main(void)
{
    sys_init_none();
    pinmux_cap_ch5_init(PH06);
    pinmux_cap_ch7_init(PH07);
    ls_cap_init();
    ioinit();
    LOG_I("cap_init\n ");
    if (HAL_CAP_Start(_CAP_CHANNEL5, LOW_HIGH, true) == HAL_ERROR)
    {
        LOG_I("init_error");
        while (1);
    }
    if (HAL_CAP_Start(_CAP_CHANNEL7, LOW_HIGH, true) == HAL_ERROR)
    {
        LOG_I("init_error");
        while (1);
    }
    // HAL_CAP_Stop(_CAP_CHANNEL5);
    while(1)
    {
        io_toggle_pin(PA01);
        DELAY_US(5000);
    }
}

void HAL_CAP_ERR_HIGH_Callback(uint8_t channel)
{
    LOG_I("Channel %d capture high pulse error interrupt",channel + 1);
    // while (1);
}

void HAL_CAP_ERR_LOW_Callback(uint8_t channel)
{
    LOG_I("Channel %d capture low pulse error interrupt", channel + 1);
    // while (1);
}

void HAL_CAP_END_Callback(uint8_t channel, cap_count_t cap_count)
{
    LOG_I("Channel %d capture end interrupt", channel + 1);
    LOG_I("GetCount = %x\n ", cap_count);
    uint32_t gerfreq =  CAP_GET_FREQ(cap_param.cap_pre_div, cap_count.cap_low, cap_count.cap_high);
    LOG_I("gerfreq = %x\n" ,gerfreq);
}