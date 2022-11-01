#include <string.h>
#include <stdlib.h>
#include "ls_hal_touchkey.h"
#include "platform.h"
#include "co_math.h"
#include "ls_soc_gpio.h"
#include "log.h"

static uint32_t chn_avg[16];
static TOUCHKEY_PARAM tkParam;
static volatile bool flag;

static void tk_init(void)
{
    HAL_TOUCHKEY_Init();
    pinmux_touchkey_cmod_init();
    /*-----------CH4,CH5,CH6,CH7--------*/
    pinmux_touchkey_ch4_init();
    pinmux_touchkey_ch5_init();
    pinmux_touchkey_ch6_init();
    pinmux_touchkey_ch7_init();
    /*-------touchKey config params---------*/
    tkParam.clk_hprd = 0xf;
    tkParam.clk_lprd = 0xf;
    tkParam.scam_disch_prd = 0x7;
    tkParam.scan_channel_en = 0xf0;
    tkParam.scan_flt_prd = 0x3;
    tkParam.scan_iter = 0xf;
    tkParam.scan_mtim = 0xfff;
    tkParam.touchkey_cp_vctl = TOUCHKEY_VCTRL_1800mV;
    HAL_TOUCHKEY_SetParam(&tkParam);
}

static void SelfCalibration(uint8_t count, uint32_t sum[16])
{
    uint8_t index = count;
    do
    {
        uint32_t result[16];
        HAL_TOUCHKEY_StartScan(result);
        for (uint8_t i = 0; i < 16; i++)
        {
            if (tkParam.scan_channel_en & CO_BIT(i))
            {
                sum[i] += result[i];
            }
        }
    } while (index--);
    for (uint8_t i = 0; i < 16; i++)
    {
        sum[i] = sum[i] / count;
    }
}

int main()
{
    sys_init_none();
    tk_init();
    SelfCalibration(50, chn_avg);
    while (1)
    {
        flag = true;
        HAL_TOUCHKEY_StartScan_IT();
        while (flag)
            ;
        // DELAY_US(500*1000);
    }
}

void HAL_TOUCHKEY_END_Callback(uint32_t *data)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        if ((tkParam.scan_channel_en & CO_BIT(i) && data[i] < chn_avg[i] * 0.6 && data[i] > chn_avg[i] * 0.1))
        {
            LOG_I("trigger CHANNEL:---%d---%d", i, data[i]);
        }
    }
    flag = false;
}
