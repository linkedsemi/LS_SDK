#include "ls_msp_adc.h"
#include "field_manipulate.h"
#include "leo.h"
#include "HAL_def.h"
#include "platform.h"
#include "dmac_config.h"
#include <stddef.h>
#include "exception_isr.h"
#include "sys_stat.h"
#include "reg_sysc_per.h"
#include "reg_v33_rg.h"
#include "ls_dbg.h"
#include "core_rv32.h"
#include "ls_hal_flash.h"

static ADC_HandleTypeDef *adc_inst_env[2];

void ADC1_Handler(void)
{
    HAL_ADC_IRQHandler(adc_inst_env[0]);
}
void ADC2_Handler(void)
{
    HAL_ADC_IRQHandler(adc_inst_env[1]);
}

static void load_trim_value(reg_adc_t* adc,uint16_t addr)
{
    uint32_t adc_trim_value[6] = {0};
    hal_flash_read_security_area(1,addr,(uint8_t *)adc_trim_value,sizeof(adc_trim_value));
    if(adc_trim_value[0]==~adc_trim_value[1])
    {
        adc->ADR = adc_trim_value[0];
    }
    if(adc_trim_value[4]==~adc_trim_value[5])
    {
        MODIFY_REG(adc->ADCH,ADC_ADCH_OS_CALV_MASK,(adc_trim_value[2]>>16)<<ADC_ADCH_OS_CALV_POS);
    }
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
        rv_set_int_isr(ADC1_IRQn, ADC1_Handler);
        adc_inst_env[0] = inst;
        csi_vic_clear_pending_irq(ADC1_IRQn);
        csi_vic_enable_irq(ADC1_IRQn);
        load_trim_value(LSADC1,0x30);
        break;
    case (uint32_t)LSADC2:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_ADC2_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_CLR_ADC2_N_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_SET_ADC2_N_MASK;
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_ADC2_MASK;
        rv_set_int_isr(ADC2_IRQn, ADC2_Handler);
        adc_inst_env[1] = inst;
        csi_vic_clear_pending_irq(ADC2_IRQn);
        csi_vic_enable_irq(ADC2_IRQn);
        load_trim_value(LSADC2,0x38);
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
        csi_vic_disable_irq(ADC1_IRQn);
        break;
    case (uint32_t)LSADC2:
        HAL_AMIC_MSP_DeInit();
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_ADC2_MASK;
        csi_vic_disable_irq(ADC2_IRQn);
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
    SET_BIT(V33_RG->ANA_PMU_CTRL, V33_RG_BAT_DET_CTRL_MASK);
}

void adc_channel_vbat_disable(void)
{
    CLEAR_BIT(V33_RG->ANA_PMU_CTRL, V33_RG_BAT_DET_CTRL_MASK);
}

uint8_t HAL_ADC_DMA_Handshake_Get(ADC_HandleTypeDef *inst)
{
    uint8_t handshake = 0;
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)LSADC1:
        handshake = ADC1;
        break;
    case (uint32_t)LSADC2:
        handshake = ADC2;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
    return handshake;
}
