#include "ls_msp_adc.h"
#include "field_manipulate.h"
#include "ls_hal_adc.h"
#include "gemini.h"
#include "HAL_def.h"
#include "platform.h"
#include "dmac_config.h"
#include "ls_msp_dmac.h"
#include <stddef.h>
#include "sys_stat.h"

static ADC_HandleTypeDef *adc_inst_env[2];

void ADC1_Handler(void)
{
    HAL_ADC_IRQHandler(adc_inst_env);
}
void ADC2_Handler(void)
{
    HAL_ADC_IRQHandler(adc_inst_env);
}

void HAL_ADC_MSP_Init(ADC_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSADC:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG2, SYSC_PER_CLKG_SET_ADC0, 1);
        arm_cm_set_int_isr(ADC0_IRQn, ADC1_Handler);
        adc_inst_env[0] = inst;
        __NVIC_ClearPendingIRQ(ADC0_IRQn);
        __NVIC_EnableIRQ(ADC0_IRQn);
        break;
    case (uint32_t)LSADC2:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG2, SYSC_PER_CLKG_SET_ADC1, 1);
        arm_cm_set_int_isr(ADC1_IRQn, ADC2_Handler);
        adc_inst_env[1] = inst;
        __NVIC_ClearPendingIRQ(ADC1_IRQn);
        __NVIC_EnableIRQ(ADC1_IRQn);
        break;
    }
}

void HAL_ADC_MSP_DeInit(ADC_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSADC:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG2, SYSC_PER_CLKG_CLR_ADC0, 1);
        NVIC_DisableIRQ(ADC0_IRQn);
        break;
    case (uint32_t)LSADC2:
        REG_FIELD_WR(SYSC_PER->PD_PER_CLKG2, SYSC_PER_CLKG_CLR_ADC1, 1);
        NVIC_DisableIRQ(ADC1_IRQn);
        break;
    }
}

static void adc_status_set(ADC_HandleTypeDef *inst, bool status)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSADC:
        adc1_status_set(true);
        break;
    case (uint32_t)LSADC2:
        adc2_status_set(false);
        break;
    }
}

void HAL_ADC_MSP_Busy_Set(ADC_HandleTypeDef *inst)
{
    adc_status_set(inst, true);
}

void HAL_ADC_MSP_Idle_Set(ADC_HandleTypeDef *inst)
{
    adc_status_set(inst, false);
}
