#include "platform.h"
#include "ls_soc_gpio.h"
#include "ls_hal_dac.h"
#include "log.h"

static DAC_HandleTypeDef DACx_Hdl;

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
    DACx_Hdl.Instance           = LSDAC12;
    DACx_Hdl.DACx               = DAC2;
    DACx_Hdl.DAC2_Trigger       = SOFTWARE_TRIG;
    DACx_Hdl.DAC2_wave          = No_Wave;
    DACx_Hdl.DAC2_Mamp          = triangle_amplitude_1;
    if (HAL_DAC_Init(&DACx_Hdl) != HAL_OK)
    {
        Error_Handler();
    }
}

int main(void)
{
    sys_init_none();
    pinmux_dac_init();
    DAC_Init_Func();
    HAL_DAC_SetValue(&DACx_Hdl, DAC2_ALIGN_12B_R, 4095);
    LOG_I("%d",HAL_DAC_GetValue(&DACx_Hdl));
    while ((1))
    {
   
    }
}