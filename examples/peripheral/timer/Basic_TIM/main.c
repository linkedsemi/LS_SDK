#include "ls_hal_timer.h"
#include <string.h>
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define TIM_PRESCALER     (SDK_HCLK_MHZ-1)
#define TIM_PERIOD        (250 - 1) /* Period Value  */

TIM_HandleTypeDef TimHandle;

void Basic_Timer_Cfg(void)
{ 
    io_cfg_output(PA00);
    io_write_pin(PA00,0);

    TimHandle.Instance           = LSGPTIMA;
    TimHandle.Init.Prescaler     = TIM_PRESCALER;
    TimHandle.Init.Period        = TIM_PERIOD;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    HAL_TIM_Init(&TimHandle);
    HAL_TIM_Base_Start_IT(&TimHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == LSGPTIMA)
    {
        io_toggle_pin(PA00);
    }
}

int main(void)
{
    sys_init_none();
    Basic_Timer_Cfg();
    while (1);
}

