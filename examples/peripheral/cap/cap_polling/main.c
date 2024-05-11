#include "app_config.h"
#include "ls_msp_cap.h"
#include "ls_hal_cap.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define         _CAP_CHANNEL         CAP_Channel8

static cap_count_t capcount;
static CAP_Param cap_param;
static void ls_cap_init(void)
{
    cap_param.cap_pre_div = 7;
    HAL_CAP_Init(&cap_param);
}

int main(void)
{
    sys_init_none();
    io_cfg_output(PH07);
    pinmux_cap_ch8_init(PH06);    // 所选pinmux函数必须和_CAP_CHANNEL匹配
    ls_cap_init();
    LOG_I("cap_init\n ");
    if(HAL_CAP_Start(_CAP_CHANNEL, LOW_HIGH, false) == HAL_OK)
    {
        for (uint32_t i = 0; i < 1000; i++)
        {
            if (HAL_CAP_GetCount(_CAP_CHANNEL, &capcount) != HAL_ERROR)
            {
                LOG_I("GetCount = %x\n ", capcount);
                uint32_t gerfreq =  CAP_GET_FREQ(cap_param.cap_pre_div, capcount.cap_low, capcount.cap_high);
                LOG_I("gerfreq = %x\n", gerfreq);
            }
            else
            {
                LOG_I("error");
                while (1);
            }
        }
    }
    HAL_CAP_Stop(_CAP_CHANNEL);
    while(1)
    {

    }
}