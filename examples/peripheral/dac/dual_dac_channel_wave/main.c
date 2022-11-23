#include "ls_hal_timer.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "ls_hal_dac.h"

#define TIM_PRESCALER     (8-1)
#define TIM_PERIOD        (4) /* Period Value  */

static DAC_HandleTypeDef DACx_Hdl;

TIM_HandleTypeDef TimHandle;

void Basic_Timer_Cfg(void)
{ 
    TimHandle.Instance           = LSGPTIMA;
    TimHandle.Init.Prescaler     = TIM_PRESCALER;   // 8 frequency division
    TimHandle.Init.Period        = TIM_PERIOD;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode   = TIM_COUNTERMODE_DOWN;
    TimHandle.Init.TrgoSource = TIM_TRGO_UPDATE;
    HAL_TIM_Init(&TimHandle);
    HAL_TIM_Base_Start(&TimHandle);
}

static void pinmux_dac_init(void)
{
    pinmux_dac1_init();         // PA07
    pinmux_dac2_init();         // PC04
}

void Error_Handler(void)
{
    while(1);
}

void DAC_Init_Func(void)
{
    DACx_Hdl.Instance           = LSDAC12;
    DACx_Hdl.DACx               = DAC1AndDAC2;
    DACx_Hdl.DAC1_Trigger       = GENERAL_TimerA_TRGO;
    DACx_Hdl.DAC1_wave          = Noise_Wave;
    DACx_Hdl.DAC1_Mamp          = triangle_amplitude_4095;
    DACx_Hdl.DAC2_Trigger       = GENERAL_TimerA_TRGO;
    DACx_Hdl.DAC2_wave          = Triangle_Wave;
    DACx_Hdl.DAC2_Mamp          = triangle_amplitude_4095;
    if (HAL_DAC_Init(&DACx_Hdl) != HAL_OK)
    {
        Error_Handler();
    }
}

int main(void)
{
    sys_init_none();
    pinmux_dac_init();
    Basic_Timer_Cfg();
    DAC_Init_Func();
    while ((1))
    {
   
    }
}