#include "log.h"
#include "platform.h"
#include "ls_hal_comp.h"
#include "ls_soc_gpio.h"
#include "ls_soc_pinmux.h"

static COMP_HandleTypeDef COMP_Config;

static void comp_init()
{
    pinmux_comp1_init(PA00);
    COMP_Config.COMP = LSCOMP1;
    HAL_COMP_Init(&COMP_Config);
}

static void test_comp1()
{
    COMP_Param param;
    param.risingintr_en         = ENABLE;
    param.fallingintr_en        = ENABLE;
    param.flt_byp               = COMP_FLT_ENABLE;
    param.flt_prd               = ENABLE;
    param.input                 = INPUT_COMP1_PC00;
    param.vrefsel               = VREFSEL_INTERNAL_REFERENCE_VOLTAGE;
    param.vrefctl               = VREFCTL_900MV;
    param.hysteresis            = HYS_HS_21P9MV;
    param.clk_mode              = HighSpeed;
    HAL_COMP_Config(&COMP_Config, &param);
    HAL_COMP_Start(&COMP_Config);
}

int main(void)
{
    sys_init_none();
    comp_init();
    test_comp1();
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