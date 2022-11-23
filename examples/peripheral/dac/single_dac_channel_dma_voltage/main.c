#include "platform.h"
#include "ls_soc_gpio.h"
#include "ls_hal_dac.h"
#include "ls_hal_dmacv2.h"
#include "log.h"

DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);
static DAC_HandleTypeDef DACx_Hdl;

#define DAC_CHANNLE_NUM (3)

DMA_RAM_ATTR uint32_t single_dac_channel_value[DAC_CHANNLE_NUM]={0xfff,0x800,0x400};

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
    DACx_Hdl.DAC2_Trigger       = SOFTWARE_TRIG;
    DACx_Hdl.DAC2_wave          = No_Wave;
    DACx_Hdl.DAC2_Mamp          = triangle_amplitude_4095;
    if (HAL_DAC_Init(&DACx_Hdl) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_DAC_ConvCpltCallback(DAC_HandleTypeDef *hdac) 
{

}

int main(void)
{
    sys_init_none();
    pinmux_dac_init();
    DAC_Init_Func();
    while (1)
    {
        HAL_DAC_Start_DMA(&DACx_Hdl,DAC2_ALIGN_12B_R,single_dac_channel_value,sizeof(single_dac_channel_value),HAL_DAC_ConvCpltCallback);
        LOG_I("%d",HAL_DAC_GetValue(&DACx_Hdl));
        DELAY_US(500000);
    }
}