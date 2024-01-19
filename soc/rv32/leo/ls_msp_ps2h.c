#include "ls_msp_ps2h.h"
#include "ls_hal_ps2h.h"
#include "exception_isr.h"
#include "reg_sysc_per.h"
#include "core_rv32.h"
#include "leo.h"

static PS2H_HandleTypeDef *PS2H_inst_env[4];

static void PS2H1_IRQHandler()
{
    HAL_PS2H_IRQHandler(PS2H_inst_env[0]);
}

static void PS2H2_IRQHandler()
{
    HAL_PS2H_IRQHandler(PS2H_inst_env[1]);
}

static void PS2H3_IRQHandler()
{
    HAL_PS2H_IRQHandler(PS2H_inst_env[2]);
}

static void PS2H4_IRQHandler()
{
    HAL_PS2H_IRQHandler(PS2H_inst_env[3]);
}

void HAL_PS2H_MSP_Init(PS2H_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->PS2HX)
    {
    case (uint32_t)PS2H1:
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PS2H1_MASK;
        SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_PS2H1_MASK;
        SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_PS2H1_MASK;
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_PS2H1_MASK;
        rv_set_int_isr(PS2H1_IRQn,PS2H1_IRQHandler);
        PS2H_inst_env[0] = inst;
        csi_vic_clear_pending_irq(PS2H1_IRQn);
        csi_vic_enable_irq(PS2H1_IRQn);
        break;
    case (uint32_t)PS2H2:
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PS2H2_MASK;
        SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_PS2H2_MASK;
        SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_PS2H2_MASK;
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_PS2H2_MASK;
        rv_set_int_isr(PS2H2_IRQn,PS2H2_IRQHandler);
        PS2H_inst_env[0] = inst;
        csi_vic_clear_pending_irq(PS2H2_IRQn);
        csi_vic_enable_irq(PS2H2_IRQn);
        break;
    case (uint32_t)PS2H3:
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PS2H3_MASK;
        SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_PS2H3_MASK;
        SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_PS2H3_MASK;
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_PS2H3_MASK;
        rv_set_int_isr(PS2H3_IRQn,PS2H3_IRQHandler);
        PS2H_inst_env[0] = inst;
        csi_vic_clear_pending_irq(PS2H3_IRQn);
        csi_vic_enable_irq(PS2H3_IRQn);
        break;
    case (uint32_t)PS2H4:
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PS2H4_MASK;
        SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_PS2H4_MASK;
        SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_PS2H4_MASK;
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_PS2H4_MASK;
        rv_set_int_isr(PS2H4_IRQn,PS2H4_IRQHandler);
        PS2H_inst_env[0] = inst;
        csi_vic_clear_pending_irq(PS2H4_IRQn);
        csi_vic_enable_irq(PS2H4_IRQn);
        break;
    }
}
void HAL_PS2H_MSP_DeInit(PS2H_HandleTypeDef *inst)
{
    switch((uint32_t)inst->PS2HX)
    {
    case (uint32_t)PS2H1:
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PS2H1_MASK;
        csi_vic_disable_irq(PS2H1_IRQn);
    break;
    case (uint32_t)PS2H2:
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PS2H2_MASK;
        csi_vic_disable_irq(PS2H2_IRQn);
    break;
    case (uint32_t)PS2H3:
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PS2H3_MASK;
        csi_vic_disable_irq(PS2H3_IRQn);
    break;
    case (uint32_t)PS2H4:
        SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_PS2H4_MASK;
        csi_vic_disable_irq(PS2H4_IRQn);
    break;
    }
}
