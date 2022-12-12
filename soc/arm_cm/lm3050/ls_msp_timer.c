#include "ls_msp_timer.h"
#include "ls_hal_timer.h"
#include "field_manipulate.h"
#include "lm3050.h"
#include "HAL_def.h"
#include "platform.h"
#include "sys_stat.h"
#include "reg_sysc_per_type.h"

static TIM_HandleTypeDef *inst_env[6];

void BSTIM1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[0]);
}

void GPTIMA1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[1]);
}

void GPTIMB1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[2]);
}

void GPTIMC1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[3]);
}

void ADTIM1_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[4]);
}

void ADTIM2_Handler(void)
{
    HAL_TIM_IRQHandler(inst_env[5]);
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
        arm_cm_set_int_isr(BSTIM_IRQn, BSTIM1_Handler);
        inst_env[0] = inst;
        __NVIC_ClearPendingIRQ(BSTIM_IRQn);
        __NVIC_EnableIRQ(BSTIM_IRQn);
        break;
    case (uint32_t)LSGPTIMA:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMA1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_GPTIMA1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_GPTIMA1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_GPTIMA1_MASK;
        arm_cm_set_int_isr(GPTIMA1_IRQn, GPTIMA1_Handler);
        inst_env[1] = inst;
        __NVIC_ClearPendingIRQ(GPTIMA1_IRQn);
        __NVIC_EnableIRQ(GPTIMA1_IRQn);
        break;
    case (uint32_t)LSGPTIMB:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMB1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_GPTIMB1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_GPTIMB1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_GPTIMB1_MASK;
        arm_cm_set_int_isr(GPTIMB1_IRQn, GPTIMB1_Handler);
        inst_env[2] = inst;
        __NVIC_ClearPendingIRQ(GPTIMB1_IRQn);
        __NVIC_EnableIRQ(GPTIMB1_IRQn);
        break;
    case (uint32_t)LSGPTIMC:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMC1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_GPTIMC1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_GPTIMC1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_GPTIMC1_MASK;
        arm_cm_set_int_isr(GPTIMC1_IRQn, GPTIMC1_Handler);
        inst_env[3] = inst;
        __NVIC_ClearPendingIRQ(GPTIMC1_IRQn);
        __NVIC_EnableIRQ(GPTIMC1_IRQn);
        break;
    case (uint32_t)LSADTIM1:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM1_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_ADTIM1_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_ADTIM1_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_ADTIM1_MASK;
        arm_cm_set_int_isr(ADTIM1_IRQn, ADTIM1_Handler);
        inst_env[4] = inst;
        __NVIC_ClearPendingIRQ(ADTIM1_IRQn);
        __NVIC_EnableIRQ(ADTIM1_IRQn);
        break;
    case (uint32_t)LSADTIM2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM2_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_ADTIM2_N_MASK;
        SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_ADTIM2_N_MASK;
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_ADTIM2_MASK;
        arm_cm_set_int_isr(ADTIM2_IRQn, ADTIM2_Handler);
        inst_env[5] = inst;
        __NVIC_ClearPendingIRQ(ADTIM2_IRQn);
        __NVIC_EnableIRQ(ADTIM2_IRQn);
        break;
    }
}

void HAL_TIM_MSP_DeInit(TIM_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSBSTIM:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_BSTIM1_MASK;
        __NVIC_DisableIRQ(BSTIM_IRQn);
        break;
    case (uint32_t)LSGPTIMA:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMA1_MASK;
        __NVIC_DisableIRQ(GPTIMA1_IRQn);
        break;
    case (uint32_t)LSGPTIMB:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMB1_MASK;
        __NVIC_DisableIRQ(GPTIMB1_IRQn);
        break;
    case (uint32_t)LSGPTIMC:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_GPTIMC1_MASK;
        __NVIC_DisableIRQ(GPTIMC1_IRQn);
        break;
    case (uint32_t)LSADTIM1:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM1_MASK;
        __NVIC_DisableIRQ(ADTIM1_IRQn);
        break;
    case (uint32_t)LSADTIM2:
        SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_ADTIM2_MASK;
        __NVIC_DisableIRQ(ADTIM2_IRQn);
        break;
    }
}

static void timer_status_set(TIM_HandleTypeDef *inst, uint8_t status)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSBSTIM:
        bstimer1_status_set(status);
        break;
    case (uint32_t)LSGPTIMA:
        gptimera1_status_set(status);
        break;
    case (uint32_t)LSGPTIMB:
        gptimerb1_status_set(status);
        break;
    case (uint32_t)LSGPTIMC:
        gptimerc1_status_set(status);
        break;
    case (uint32_t)LSADTIM1:
        adtimer1_status_set(status);
        break;
    case (uint32_t)LSADTIM2:
        adtimer2_status_set(status);
        break;
    }
}

void HAL_TIM_MSP_Busy_Set(TIM_HandleTypeDef *inst)
{
    timer_status_set(inst, 1);
}

void HAL_TIM_MSP_Idle_Set(TIM_HandleTypeDef *inst)
{
    timer_status_set(inst, 0);
}
