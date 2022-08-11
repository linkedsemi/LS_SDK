#include <string.h>
#include <stdint.h>
#include "platform.h"
#include "gemini.h"
#include "field_manipulate.h"
#include "ls_soc_gpio.h"
#include "ls_hal_flash.h"
#include "compile_flag.h"
#include "reg_sysc_awo_type.h"
#include "reg_v33_rg_type.h"
#include "sleep.h"
#include "systick.h"
#include "ls_dbg.h"
#define ISR_VECTOR_ADDR ((uint32_t *)(0x20000000))

__attribute__((weak)) void SystemInit(){
    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
    SCB->VTOR = (uint32_t)ISR_VECTOR_ADDR;
}

void clk_switch()
{
    hclk_set(SDK_HCLK_MHZ);
}

static void dpll_clk_config(enum dpll_clk clk)
{
    // if(clk==DPLL_136M)
    // {
    //     LS_ASSERT(SDK_HSE_USED == 1 || SDK_HSE_MHZ >= 16);
    //     // TODO
    //     REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_SEL_REF_24M, 2);//配置pdll的时钟源位HSE
    //     REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_NDIV, 16);//配置倍频参数
    //     REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_SEL_144M, 0);//配置时钟分频 0：1/3  1：1/2
    //     /*使能PDLL*/
    //     REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_EN_128M, 1);
    //     REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_LOCK_BYPS, 1);
    //     REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_EN, 1);
    // }
    // else
    // {
        // TODO
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_SEL_REF_24M, 0);//配置pdll的时钟源位HSE
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_NDIV, (uint8_t)(SDK_HCLK_MHZ/10)-1);//配置倍频参数
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_SEL_144M, 0);//配置时钟分频 0：1/3  1：1/2
        /*使能PDLL*/
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_EN_128M, 1);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_LOCK_BYPS, 1);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_ANA0, SYSC_AWO_AWO_DPLL_EN, 1);
    // }
}

static void hclk_switch_to_hse()
{
    /*HSE起振*/
    REG_FIELD_WR(V33_RG->PMU_SET_VAL, V33_RG_CLK_SET_HSE, 1);
    REG_FIELD_WR(V33_RG->PMU_SET_VAL, V33_RG_PMU_SET_TGGL, 1);
    REG_FIELD_WR(V33_RG->PMU_SET_VAL, V33_RG_PMU_SET_TGGL, 0);
    
}

static void hclk_switch_to_hsi()
{
    /*HSI起振*/
    REG_FIELD_WR(V33_RG->PMU_SET_VAL, V33_RG_CLK_SET_HSI, 1);
    REG_FIELD_WR(V33_RG->PMU_SET_VAL, V33_RG_PMU_SET_TGGL, 1);
    REG_FIELD_WR(V33_RG->PMU_SET_VAL, V33_RG_PMU_SET_TGGL, 0);
    
}


void hclk_set(uint32_t mhz)
{
    if(SDK_HSE_USED)
    {
        hclk_switch_to_hse();
    }else
    {
        hclk_switch_to_hsi();
    }
    switch(mhz)
    {
    // case 136:
    //     dpll_clk_config(DPLL_136M);
    //     REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 8);
    //     break;
    case 128:
        dpll_clk_config(DPLL_128M);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 8);
    break;
    // case 68:
    //     dpll_clk_config(DPLL_136M);
    //     REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 4);
    // break;
    case 64:
        dpll_clk_config(DPLL_128M);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 8);
    case 32:
        dpll_clk_config(DPLL_128M);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 8);
    break;
    case 24:
        LS_ASSERT(SDK_HSE_USED==0);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 1);
    break;
    case 16:
        LS_ASSERT(SDK_HSE_USED==1);
        REG_FIELD_WR(SYSC_AWO->PD_AWO_CLK_CTRL, SYSC_AWO_CLK_SEL_HBUS, 2);
    break;
    default:
        LS_ASSERT(0);
    break;
    }
}

void arm_cm_set_int_isr(uint8_t type,void (*isr)())
{
    ISR_VECTOR_ADDR[type + 16] = (uint32_t)isr;
}

void sys_init_none()
{
    clk_switch();
    io_init();
    low_power_init();
    systick_start();
}

void platform_reset(uint32_t error)
{

}
