#include "log.h"
#include "platform.h"
#include "ls_hal_dac.h"
#include "ls_hal_comp.h"
#include "ls_soc_gpio.h"
#include "ls_soc_pinmux.h"

#define DAC1_VOL 1.0
#define DAC1_CODE DAC1_VOL*4095/1.8

static COMP_HandleTypeDef COMP_Config;
static DAC_HandleTypeDef DACx_Hdl;

static void comp_init()
{
    pinmux_comp1_init(PA00);
    COMP_Config.COMP = LSCOMP1;
    HAL_COMP_Init(&COMP_Config);
}

static void dac_init(void)
{
    DACx_Hdl.Instance           = LSDAC12;
    DACx_Hdl.DACx               = DAC2;
    DACx_Hdl.DAC2_Trigger       = SOFTWARE_TRIG;
    if (HAL_DAC_Init(&DACx_Hdl) != HAL_OK)
    {
        while (1);
    }
    HAL_DAC_SetValue(&DACx_Hdl,DAC2_ALIGN_12B_R,DAC1_CODE);
}

static void test_comp1_dac()
{
    COMP_Param param;
    param.risingintr_en         = ENABLE;
    param.fallingintr_en        = ENABLE;
    param.flt_byp               = COMP_FLT_ENABLE;
    param.flt_prd               = ENABLE;
    param.input                 = INPUT_COMP1_PC00;
    param.vrefsel               = VREFSEL_DAC2;
    param.vrefctl               = DISABLE;
    param.hysteresis            = HYS_MS_5P4MV;
    param.clk_mode              = MediumSpeed;
    HAL_COMP_Config(&COMP_Config, &param);
    HAL_COMP_Start(&COMP_Config);
}

int main(void)
{
    sys_init_none();
    comp_init();
    test_comp1_dac();
    dac_init();
    while (1)
    {
    }
}

void HAL_COMP_Callback(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge, bool output)
{
    uint8_t comp = 1;
    switch ((uint32_t)hcomp->COMP)
    {
    case (uint32_t)LSCOMP1:
        break;
    case (uint32_t)LSCOMP2:
        comp = 2;
        break;
    case (uint32_t)LSCOMP3:
        comp = 3;
        break;
    }
    switch (edge)
    {
    case COMP_EDGE_RISING:
        LOG_I("trigger : COMP%d--Rising   edge--Current level: %d", comp, output);
        break;
    case COMP_EDGE_FALLING:
        LOG_I("trigger : COMP%d--Falling  edge--Current level: %d", comp, output);
        break;
    case COMP_EDGE_BOTH:
        LOG_I("trigger : COMP%d--Both     edge--Current level: %d", comp, output);
        break;
    }
}