#include "ls_msp_timer.h"
#include "ls_hal_timer.h"
#include "reg_sysc_per.h"
#include "field_manipulate.h"
#include "leo.h"
#include "HAL_def.h"
#include <stdbool.h>
#include "platform.h"
#include "core_rv32.h"
#include "exception_isr.h"
#include "sys_stat.h"

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
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_BSTIM1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_BSTIM1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_BSTIM1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_BSTIM1_MASK;
        inst_env[0] = inst;
        rv_set_int_isr(BSTIM1_IRQn, BSTIM1_Handler);
        csi_vic_clear_pending_irq(BSTIM1_IRQn);
        csi_vic_enable_irq(BSTIM1_IRQn);
        break;
    case (uint32_t)LSGPTIMA:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMA1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_GPTIMA1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_GPTIMA1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_GPTIMA1_MASK;
        inst_env[1] = inst;
        rv_set_int_isr(GPTIMA1_IRQn, GPTIMA1_Handler);
        csi_vic_clear_pending_irq(GPTIMA1_IRQn);
        csi_vic_enable_irq(GPTIMA1_IRQn);
        break;
    case (uint32_t)LSGPTIMA2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMA2_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_GPTIMA2_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_GPTIMA2_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_GPTIMA2_MASK;
        inst_env[2] = inst;
        rv_set_int_isr(GPTIMA2_IRQn, GPTIMA2_Handler);
        csi_vic_clear_pending_irq(GPTIMA2_IRQn);
        csi_vic_enable_irq(GPTIMA2_IRQn);
        break;
    case (uint32_t)LSGPTIMB:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMB1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_GPTIMB1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_GPTIMB1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_GPTIMB1_MASK;
        inst_env[3] = inst;
        rv_set_int_isr(GPTIMB1_IRQn, GPTIMB1_Handler);
        csi_vic_clear_pending_irq(GPTIMB1_IRQn);
        csi_vic_enable_irq(GPTIMB1_IRQn);
        break;
    case (uint32_t)LSGPTIMC:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMC1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_GPTIMC1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_GPTIMC1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_GPTIMC1_MASK;
        inst_env[4] = inst;
        rv_set_int_isr(GPTIMC1_IRQn, GPTIMC1_Handler);
        csi_vic_clear_pending_irq(GPTIMC1_IRQn);
        csi_vic_enable_irq(GPTIMC1_IRQn);
        break;
    case (uint32_t)LSADTIM:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_ADTIM1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_ADTIM1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_ADTIM1_MASK;
        inst_env[5] = inst;
        rv_set_int_isr(ADTIM1_IRQn, ADTIM1_Handler);
        csi_vic_clear_pending_irq(ADTIM1_IRQn);
        csi_vic_enable_irq(ADTIM1_IRQn);
        break;
    case (uint32_t)LSADTIM2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM2_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_ADTIM2_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_ADTIM2_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_ADTIM2_MASK;
        inst_env[6] = inst;
        rv_set_int_isr(ADTIM2_IRQn, ADTIM2_Handler);
        csi_vic_clear_pending_irq(ADTIM2_IRQn);
        csi_vic_enable_irq(ADTIM2_IRQn);
        break;
    case (uint32_t)LSADTIM3:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM3_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_ADTIM3_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_ADTIM3_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_ADTIM3_MASK;
        inst_env[7] = inst;
        rv_set_int_isr(ADTIM3_IRQn, ADTIM3_Handler);
        csi_vic_clear_pending_irq(ADTIM3_IRQn);
        csi_vic_enable_irq(ADTIM3_IRQn);
        break;
    case (uint32_t)LSADTIM4:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM4_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_ADTIM4_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_ADTIM4_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_ADTIM4_MASK;
        inst_env[8] = inst;
        rv_set_int_isr(ADTIM4_IRQn, ADTIM4_Handler);
        csi_vic_clear_pending_irq(ADTIM4_IRQn);
        csi_vic_enable_irq(ADTIM4_IRQn);
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
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_BSTIM1_MASK;
        csi_vic_disable_irq(BSTIM1_IRQn);
        break;
    case (uint32_t)LSGPTIMA:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMA1_MASK;
        csi_vic_disable_irq(GPTIMA1_IRQn);
        break;
    case (uint32_t)LSGPTIMA2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMA2_MASK;
        csi_vic_disable_irq(GPTIMA2_IRQn);
        break;
    case (uint32_t)LSGPTIMB:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMB1_MASK;
        csi_vic_disable_irq(GPTIMB1_IRQn);
        break;
    case (uint32_t)LSGPTIMC:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMC1_MASK;
        csi_vic_disable_irq(GPTIMC1_IRQn);
        break;
    case (uint32_t)LSADTIM:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM1_MASK;
        csi_vic_disable_irq(ADTIM1_IRQn);
        break;
    case (uint32_t)LSADTIM2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM2_MASK;
        csi_vic_disable_irq(ADTIM2_IRQn);
        break;
    case (uint32_t)LSADTIM3:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM3_MASK;
        csi_vic_disable_irq(ADTIM3_IRQn);
        break;
    case (uint32_t)LSADTIM4:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM4_MASK;
        csi_vic_disable_irq(ADTIM4_IRQn);
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
    case (uint32_t)LSADTIM:
        adtimer1_status_set(status);
        break;
    case (uint32_t)LSADTIM2:
        adtimer2_status_set(status);
        break;
    case (uint32_t)LSADTIM3:
        adtimer3_status_set(status);
        break;
    case (uint32_t)LSADTIM4:
        adtimer4_status_set(status);
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


