#include "platform.h"
#include "ls_soc_gpio.h"
#include "ls_hal_dac.h"
#include "ls_hal_dmacv2.h"
#include "ls_hal_timer.h"
#include "sine_wave.h"
#include "log.h"

DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);
static DAC_HandleTypeDef DACx_Hdl;

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
    pinmux_dac2_init();         // PC04
}

void Error_Handler(void)
{
    while(1);
}

void DAC_Init_Func(void)
{
    DMA_CONTROLLER_INIT(dmac1_inst);
    DACx_Hdl.Env.DMA.DMA_Channel = 1;
    DACx_Hdl.DMAC_Instance = &dmac1_inst;

    DACx_Hdl.Instance           = LSDAC12;
    DACx_Hdl.DACx               = DAC2;
    DACx_Hdl.DAC2_Trigger       = GENERAL_TimerA_TRGO;
    DACx_Hdl.DAC2_wave          = No_Wave;
    DACx_Hdl.DAC2_Mamp          = triangle_amplitude_4095;
    if (HAL_DAC_Init(&DACx_Hdl) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_DAC_ConvCpltCallback(DAC_HandleTypeDef *hdac) 
{
    HAL_DAC_Start_DMA(&DACx_Hdl,DAC2_ALIGN_12B_R,sin_wave,sizeof(sin_wave),HAL_DAC_ConvCpltCallback);
}

int main(void)
{
    sys_init_none();
    pinmux_dac_init();
    Basic_Timer_Cfg();
    DAC_Init_Func();
    HAL_DAC_Start_DMA(&DACx_Hdl,DAC2_ALIGN_12B_R,sin_wave,sizeof(sin_wave),HAL_DAC_ConvCpltCallback);
    while (1)
    {
    }
}