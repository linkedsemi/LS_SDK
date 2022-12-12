#include "ls_hal_timer.h"
#include <string.h>
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#if defined(LE501X)
#define DTC_PWM_TIMER LSADTIM
#elif defined(LM3050)
#define DTC_PWM_TIMER LSADTIM1
#endif

#define TIM_PRESCALER     (SDK_HCLK_MHZ-1)
#define TIM_PERIOD        (250 - 1) /* Period Value  */
#define TIM_PULSE1        125       /* Capture Compare 1 Value  */
#define TIM_PULSE2        200       /* Capture Compare 2 Value  */
#define TIM_PULSE3        100       /* Capture Compare 3 Value  */
#define TIM_PULSE4        50        /* Capture Compare 4 Value  */

TIM_HandleTypeDef TimHandle;

static void DeadTime_Complementary_PWM_Cfg(void)
{
    pinmux_adtim1_ch1_init(PA00,true,0);
    pinmux_adtim1_ch1n_init(PA01);
    TIM_BreakDeadTimeConfigTypeDef BDT_Config = {0};
    TIM_OC_InitTypeDef sConfig = {0};
    TimHandle.Instance = DTC_PWM_TIMER;
    TimHandle.Init.Prescaler = TIM_PRESCALER;
    TimHandle.Init.Period = TIM_PERIOD;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Init(&TimHandle);

    BDT_Config.OffStateRunMode = TIM_OSSR_DISABLE;
    BDT_Config.OffStateIDLEMode = TIM_OSSI_DISABLE;
    BDT_Config.LockLevel = TIM_LOCKLEVEL_OFF;
    BDT_Config.DeadTime = 0x3f;//0~0xFF
    BDT_Config.BreakState = TIM_BREAK_DISABLE;
    BDT_Config.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    BDT_Config.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&TimHandle,&BDT_Config);

    sConfig.OCMode = TIM_OCMODE_PWM1;
    sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfig.OCFastMode = TIM_OCFAST_DISABLE;
    sConfig.Pulse = TIM_PULSE3;
        
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&TimHandle, TIM_CHANNEL_1);
}


int main(void)
{
    sys_init_none();
    DeadTime_Complementary_PWM_Cfg();
    while (1);
}

