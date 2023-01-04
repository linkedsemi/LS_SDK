#include "ls_msp_adc.h"
#include "field_manipulate.h"
#include "lm3050.h"
#include "HAL_def.h"
#include "platform.h"
#include "dmac_config.h"
#include "ls_msp_dmacv2.h"
#include <stddef.h>
#include "sys_stat.h"
#include "reg_sysc_per_type.h"
#include "reg_v33_rg_type.h"

static ADC_HandleTypeDef *adc_inst_env[2];

void ADC1_Handler(void)
{
    HAL_ADC_IRQHandler(adc_inst_env[0]);
}
void ADC2_Handler(void)
{
    HAL_ADC_IRQHandler(adc_inst_env[1]);
}

void HAL_ADC_MSP_Init(ADC_HandleTypeDef *inst)
{
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_ADC12_MASK, 0 << V33_RG_PD_ADC12_POS);
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSADC1:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_ADC1_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_CLR_ADC1_N_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_SET_ADC1_N_MASK;
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_ADC1_MASK;
        arm_cm_set_int_isr(ADC1_IRQn, ADC1_Handler);
        adc_inst_env[0] = inst;
        __NVIC_ClearPendingIRQ(ADC1_IRQn);
        __NVIC_EnableIRQ(ADC1_IRQn);
        break;
    case (uint32_t)LSADC2:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_ADC2_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_CLR_ADC2_N_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_SET_ADC2_N_MASK;
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_ADC2_MASK;
        arm_cm_set_int_isr(ADC2_IRQn, ADC2_Handler);
        adc_inst_env[1] = inst;
        __NVIC_ClearPendingIRQ(ADC2_IRQn);
        __NVIC_EnableIRQ(ADC2_IRQn);
        break;
    default:
        LS_ASSERT(0);
        break;
    }
}

void HAL_ADC_MSP_DeInit(ADC_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSADC1:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_ADC1_MASK;
        NVIC_DisableIRQ(ADC1_IRQn);
        break;
    case (uint32_t)LSADC2:
        HAL_AMIC_MSP_DeInit();
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_ADC2_MASK;
        NVIC_DisableIRQ(ADC2_IRQn);
        break;
    default:
        LS_ASSERT(0);
        break;
    }
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_ADC12_MASK, 1 << V33_RG_PD_ADC12_POS);
}

void HAL_AMIC_MSP_Init()
{
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_AMIC_MASK, 0 << V33_RG_PD_AMIC_POS);
    SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_ADC1_MASK;
	MODIFY_REG(LSADC1->AMIC_CTRL, ADC_AMIC_EN_MASK|ADC_AMIC_PGA_VOL_MASK|ADC_AMIC_IBSEL_MASK,1<<ADC_AMIC_EN_POS | 0<<ADC_AMIC_PGA_VOL_POS | 1<<ADC_AMIC_IBSEL_POS);
}

void HAL_AMIC_MSP_DeInit()
{
    CLEAR_REG(LSADC1->AMIC_CTRL);
    SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_ADC1_MASK;
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_AMIC_MASK, 1 << V33_RG_PD_AMIC_POS);
}

static void adc_status_set(ADC_HandleTypeDef *inst, bool status)
{
    switch ((uint32_t)inst->Instance)
    {
    case (uint32_t)LSADC1:
        adc1_status_set(true);
        break;
    case (uint32_t)LSADC2:
        adc2_status_set(false);
        break;
    default:
        LS_ASSERT(0);
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

void adc_channel_vbat_enable(void)
{
    MODIFY_REG(V33_RG->ANA_PMU_CTRL,
                V33_RG_BAT_DET_ADJ_MASK|V33_RG_BAT_DET_EN_MASK,
                V33_RG_BAT_DET_EN_MASK|(2<<V33_RG_BAT_DET_ADJ_POS));
}

void adc_channel_vbat_disable(void)
{
    REG_FIELD_WR(V33_RG->ANA_PMU_CTRL, V33_RG_BAT_DET_EN, 0);
}

uint8_t HAL_ADC_DMA_Handshake_Get(ADC_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)LSADC1:
        handshake = CH_ADC1;
        break;
    case (uint32_t)LSADC2:
        handshake = CH_ADC2;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
    return handshake;
}
