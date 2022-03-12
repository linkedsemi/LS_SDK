#include "lstimer_msp.h"
#include "lstimer.h"
#include "field_manipulate.h"
#include "taurus.h"
#include "HAL_def.h"
#include "sys_stat.h"
#include "platform.h"
#include "reg_sysc_per.h"
#include "core_rv32.h"
#include "exception_isr.h"
static TIM_HandleTypeDef *inst_env[5];

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

__attribute__((weak)) void csi_timer_isr(void *inst){}


void CSI_GPTIMA_Handler()
{
    csi_timer_isr(inst_env[1]);
}

void CSI_ADTIM_Handler()
{
    csi_timer_isr(inst_env[4]);
}

void CSI_GPTIMC_Handler()
{
    csi_timer_isr(inst_env[3]);
}

static void gptima_msp_init(void *inst,void (*handler)())
{
    REG_FIELD_WR(SYSC_PER->PD_PER_SRST0, SYSC_PER_SRST_SET_GPTIMA1_N, 1);
    REG_FIELD_WR(SYSC_PER->PD_PER_SRST0, SYSC_PER_SRST_CLR_GPTIMA1_N, 1);
    inst_env[1] = inst;
    rv_set_int_isr(GPTIMA1_IRQn,handler);
    csi_vic_clear_pending_irq(GPTIMA1_IRQn);
    csi_vic_enable_irq(GPTIMA1_IRQn);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_SET_GPTIMA1, 1);
}

static void gptimb_msp_init(void *inst,void (*handler)())
{
    REG_FIELD_WR(SYSC_PER->PD_PER_SRST0, SYSC_PER_SRST_SET_GPTIMB1_N, 1);
    REG_FIELD_WR(SYSC_PER->PD_PER_SRST0, SYSC_PER_SRST_CLR_GPTIMB1_N, 1);
    inst_env[2] = inst;
    rv_set_int_isr(GPTIMB1_IRQn,handler);
    csi_vic_clear_pending_irq(GPTIMB1_IRQn);
    csi_vic_enable_irq(GPTIMB1_IRQn);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_SET_GPTIMB1, 1);
}

static void gptimc_msp_init(void *inst,void (*handler)())
{
    REG_FIELD_WR(SYSC_PER->PD_PER_SRST0, SYSC_PER_SRST_SET_GPTIMC1_N, 1);
    REG_FIELD_WR(SYSC_PER->PD_PER_SRST0, SYSC_PER_SRST_CLR_GPTIMC1_N, 1);
    inst_env[3] = inst;
    rv_set_int_isr(GPTIMC1_IRQn,handler);
    csi_vic_clear_pending_irq(GPTIMC1_IRQn);
    csi_vic_enable_irq(GPTIMC1_IRQn);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_SET_GPTIMC1, 1);
}

static void adtim_msp_init(void *inst,void (*handler)())
{
    REG_FIELD_WR(SYSC_PER->PD_PER_SRST0, SYSC_PER_SRST_SET_ADTIM1_N, 1);
    REG_FIELD_WR(SYSC_PER->PD_PER_SRST0, SYSC_PER_SRST_CLR_ADTIM1_N, 1);
    inst_env[4] = inst;
    rv_set_int_isr(ADTIM1_IRQn,handler);
    csi_vic_clear_pending_irq(ADTIM1_IRQn);
    csi_vic_enable_irq(ADTIM1_IRQn);
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_SET_ADTIM1, 1);
}

uint32_t CSI_TIM_MSP_Init(void *inst,uint32_t idx,bool pwm_mode)
{
    uint32_t reg_base = 0;
    if(pwm_mode == true)
    {
        idx += 1;
    }
    switch(idx)
    {
    case 1:
        gptima_msp_init(inst,CSI_GPTIMA_Handler);
        reg_base = LSGPTIMA_BASE_ADDR;
    break;
    case 2:
        adtim_msp_init(inst,CSI_ADTIM_Handler);
        reg_base = LSADTIM_BASE_ADDR;
    break;
    case 3:
        gptimc_msp_init(inst,CSI_GPTIMC_Handler);
        reg_base = LSGPTIMC_BASE_ADDR;
    break;
    default:
    break;
    }
    return reg_base;
}

void HAL_TIM_MSP_Init(TIM_HandleTypeDef *inst)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)LSGPTIMA:
        gptima_msp_init(inst,GPTIMA1_Handler);
    break;
    case (uint32_t)LSGPTIMB:
        gptimb_msp_init(inst,GPTIMB1_Handler);
    break;
    case (uint32_t)LSGPTIMC:
        gptimc_msp_init(inst,GPTIMC1_Handler);
    break;
    case (uint32_t)LSADTIM:
        adtim_msp_init(inst,ADTIM1_Handler);
    break;
    }
}

static void gptima_msp_deinit()
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_CLR_GPTIMA1, 1);
    csi_vic_disable_irq(GPTIMA1_IRQn);
}

static void gptimb_msp_deinit()
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_CLR_GPTIMB1, 1);
    csi_vic_disable_irq(GPTIMB1_IRQn);
}

static void gptimc_msp_deinit()
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_CLR_GPTIMC1, 1);
    csi_vic_disable_irq(GPTIMC1_IRQn);
}

static void adtim_msp_deinit()
{
    REG_FIELD_WR(SYSC_PER->PD_PER_CLKG0, SYSC_PER_CLKG_SET_ADTIM1, 1);
    csi_vic_disable_irq(ADTIM1_IRQn);
}

void CSI_TIM_MSP_DeInit(uint32_t idx,bool pwm_mode)
{
    if(pwm_mode == true)
    {
        idx += 1;
    }
    switch(idx)
    {
    case 0:
        //bstim_msp_deinit();
    break;
    case 1:
        gptima_msp_deinit();
    break;
    case 2:
        adtim_msp_deinit();
    break;
    case 3:
        gptimc_msp_deinit();
    break;
    default:
    break;
    }
}

void HAL_TIM_MSP_DeInit(TIM_HandleTypeDef *inst)
{
    switch((uint32_t)inst->Instance)
    {
    break;
    case (uint32_t)LSGPTIMA:
        gptima_msp_deinit();
    break;
    case (uint32_t)LSGPTIMB:
        gptimb_msp_deinit();
    break;
    case (uint32_t)LSGPTIMC:
        gptimc_msp_deinit();
    break;
    case (uint32_t)LSADTIM:
        adtim_msp_deinit();
    break;
    }
}

static void timer_status_set(TIM_HandleTypeDef *inst,uint8_t status)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)LSGPTIMA:
    gptimera1_status_set(status);
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


