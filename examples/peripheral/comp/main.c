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
    param.risingintr_en = 1;    // interrupt enable for the rising edge interrupt
    param.fallingintr_en = 1;   // interrupt enable for the falling edge interrupt
    param.flt_byp = 0;          // filter bypass
    param.flt_prd = 1;          // the filter period in MSI clock
    param.input = 0;            // input :IOVIP[0]
    param.vrefsel = 4;          // reference source select: internal reference defined by VREFCTL
    param.vrefctl = 2;          // internal reference voltage select: 0.6V
    param.hysteresis = 3;       // hysteresis select: HS:15.6mV
    param.clk_mode = HighSpeed; // speed mode select ( LS/MS/HS )
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

void HAL_COMP_Callback(COMP_HandleTypeDef *hcomp, enum comp_intr_edge edge, bool status)
{
    uint8_t comp = 0;
    switch ((uint32_t)hcomp->COMP)
    {
    case (uint32_t)LSCOMP1:
        comp = 1;
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
        LOG_I("trigger : COMP%d--Rising   edge--%d", comp, status);
        break;
    case COMP_EDGE_FALLING:
        LOG_I("trigger : COMP%d--Falling  edge--%d", comp, status);
        break;
    case COMP_EDGE_BOTH:
        LOG_I("trigger : COMP%d--Both     edge--%d", comp, status);
        break;
    }
}