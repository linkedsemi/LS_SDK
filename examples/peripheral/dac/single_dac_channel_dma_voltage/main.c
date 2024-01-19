#include "platform.h"
#include "ls_soc_gpio.h"
#include "ls_hal_dac.h"
#include "ls_hal_timer.h"
#include "log.h"
#if DMACV2
#include "ls_hal_dmacv2.h"
#elif DMACV3
#include "ls_hal_dmacv3.h"
#else
#include "ls_hal_dmac.h"
#endif

#define TIM_PRESCALER     (8-1)
#define TIM_PERIOD        (4) /* Period Value  */
#define numeric_quantities_count (3)

DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);
static DAC_HandleTypeDef DACx_Hdl;

TIM_HandleTypeDef TimHandle;
DMA_RAM_ATTR uint32_t single_dac_channel_value[numeric_quantities_count]={0xfff,0x800,0x400};

static void pinmux_dac_init(void)
{
    #ifdef LM3050
    pinmux_dac2_init();         // PC04
    #elif defined LEO
    pinmux_dac2_out1_init();    // PA03
    #endif
}

void Error_Handler(void)
{
    while(1);
}

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
    HAL_DAC_Start_DMA(&DACx_Hdl,DAC2_ALIGN_12B_R,single_dac_channel_value,sizeof(single_dac_channel_value),HAL_DAC_ConvCpltCallback);
}

int main(void)
{
    sys_init_none();
    pinmux_dac_init();
    DAC_Init_Func();
    Basic_Timer_Cfg();
    HAL_DAC_Start_DMA(&DACx_Hdl,DAC2_ALIGN_12B_R,single_dac_channel_value,sizeof(single_dac_channel_value),HAL_DAC_ConvCpltCallback);
    while (1)
    {

    }
}