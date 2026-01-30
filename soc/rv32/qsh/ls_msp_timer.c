#include "ls_msp_timer.h"
#include "ls_hal_timer.h"
#include "reg_sysc_app_per.h"
#include "field_manipulate.h"
#include "qsh.h"
#include "HAL_def.h"
#include <stdbool.h>
#include "platform.h"
#include "core_rv32.h"
#include "exception_isr.h"
#include "sys_stat.h"
#include "ls_dbg.h"
static TIM_HandleTypeDef *inst_env[9];

void BSTIM1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[0]);
}

void GPTIMA1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[1]);
}

void GPTIMA2_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[2]);
}

void GPTIMB1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[3]);
}

void GPTIMC1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[4]);
}

void ADTIM1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[5]);
}

void ADTIM2_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[6]);
}

void ADTIM3_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[7]);
}

void ADTIM4_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[8]);
}

void HAL_TIM_MSP_Init(TIM_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSBSTIM:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_BSTIM1_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_SET_BSTIM1_N_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_SET_BSTIM1_N_MASK;
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_SET_BSTIM1_MASK;
        inst_env[0] = inst;
        rv_set_int_isr(BSTIM1_IRQN, BSTIM1_Handler);
        csi_vic_clear_pending_irq(BSTIM1_IRQN);
        csi_vic_enable_irq(BSTIM1_IRQN);
        break;
    case (uint32_t)LSGPTIMA:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_GPTIMA1_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_CLR_GPTIMA1_N_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_SET_GPTIMA1_N_MASK;
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_SET_GPTIMA1_MASK;
        inst_env[1] = inst;
        rv_set_int_isr(GPTIMA1_IRQN, GPTIMA1_Handler);
        csi_vic_clear_pending_irq(GPTIMA1_IRQN);
        csi_vic_enable_irq(GPTIMA1_IRQN);
        break;
    case (uint32_t)LSGPTIMA2:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_GPTIMA2_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_CLR_GPTIMA2_N_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_SET_GPTIMA2_N_MASK;
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_SET_GPTIMA2_MASK;
        inst_env[2] = inst;
        rv_set_int_isr(GPTIMA2_IRQN, GPTIMA2_Handler);
        csi_vic_clear_pending_irq(GPTIMA2_IRQN);
        csi_vic_enable_irq(GPTIMA2_IRQN);
        break;
    case (uint32_t)LSGPTIMB:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_GPTIMB1_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_CLR_GPTIMB1_N_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_SET_GPTIMB1_N_MASK;
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_SET_GPTIMB1_MASK;
        inst_env[3] = inst;
        rv_set_int_isr(GPTIMB1_IRQN, GPTIMB1_Handler);
        csi_vic_clear_pending_irq(GPTIMB1_IRQN);
        csi_vic_enable_irq(GPTIMB1_IRQN);
        break;
    case (uint32_t)LSGPTIMC:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_GPTIMC1_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_CLR_GPTIMC1_N_MASK;
        SYSC_APP_PER->PD_PER_SRST0 = SYSC_APP_PER_SRST_SET_GPTIMC1_N_MASK;
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_SET_GPTIMC1_MASK;
        inst_env[4] = inst;
        rv_set_int_isr(GPTIMC1_IRQN, GPTIMC1_Handler);
        csi_vic_clear_pending_irq(GPTIMC1_IRQN);
        csi_vic_enable_irq(GPTIMC1_IRQN);
        break;
    default:
        LS_ASSERT(1);
        break;
    }
}

void HAL_TIM_MSP_DeInit(TIM_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSBSTIM:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_BSTIM1_MASK;
        csi_vic_disable_irq(BSTIM1_IRQN);
        break;
    case (uint32_t)LSGPTIMA:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_GPTIMA1_MASK;
        csi_vic_disable_irq(GPTIMA1_IRQN);
        break;
    case (uint32_t)LSGPTIMA2:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_GPTIMA2_MASK;
        csi_vic_disable_irq(GPTIMA2_IRQN);
        break;
    case (uint32_t)LSGPTIMB:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_GPTIMB1_MASK;
        csi_vic_disable_irq(GPTIMB1_IRQN);
        break;
    case (uint32_t)LSGPTIMC:
        SYSC_APP_PER->PD_PER_CLKG0 = SYSC_APP_PER_CLKG_CLR_GPTIMC1_MASK;
        csi_vic_disable_irq(GPTIMC1_IRQN);
        break;
    default:
        LS_ASSERT(1);
        break;
    }
}

static void timer_status_set(TIM_HandleTypeDef *inst,uint8_t status)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSBSTIM:
        bstimer1_status_set(status);
        break;
    case (uint32_t)LSGPTIMA:
        gptimera1_status_set(status);
        break;
    case (uint32_t)LSGPTIMA2:
        gptimera2_status_set(status);
        break;
    case (uint32_t)LSGPTIMB:
        gptimerb1_status_set(status);
        break;
    case (uint32_t)LSGPTIMC:
        gptimerc1_status_set(status);
        break;
    default:
        LS_ASSERT(1);
        break;
    }
}

void HAL_TIM_MSP_Busy_Set(TIM_HandleTypeDef *inst)
{
    timer_status_set(inst,1);
}

void HAL_TIM_MSP_Idle_Set(TIM_HandleTypeDef *inst)
{
    timer_status_set(inst,0);
}


