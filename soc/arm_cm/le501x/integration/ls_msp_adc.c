#include "ls_msp_adc.h"
#include "reg_rcc.h"
#include "field_manipulate.h"
#include "ls_hal_adc.h"
#include "le501x.h"
#include "modem_rf_le501x.h"
#include "HAL_def.h"
#include "sys_stat.h"
#include "platform.h"
#include "dmac_config.h"
#include "ls_msp_dmac.h"
#include <stddef.h>
#include "reg_syscfg.h"


static void *adc_inst_env;

void ADC_Handler(void)
{
    HAL_ADC_IRQHandler(adc_inst_env); 
}

__attribute__((weak)) void csi_adc_isr(void *inst){}
void CSI_ADC_Handler()
{
    csi_adc_isr(adc_inst_env);
}

static void adc_msp_init(void *inst,void (*handler)())
{
    REG_FIELD_WR(RCC->APB2RST, RCC_ADC, 1);
    REG_FIELD_WR(RCC->APB2RST, RCC_ADC, 0);
    arm_cm_set_int_isr(ADC_IRQn,handler);
    adc_inst_env = inst;
    NVIC_ClearPendingIRQ(ADC_IRQn);
    NVIC_EnableIRQ(ADC_IRQn);
    REG_FIELD_WR(RCC->APB2EN, RCC_ADC, 1);
}

void adc_msp_deinit(void)
{
    REG_FIELD_WR(RCC->APB2RST, RCC_ADC, 1);
    REG_FIELD_WR(RCC->APB2RST, RCC_ADC, 0);
    REG_FIELD_WR(RCC->APB2EN, RCC_ADC, 0);
    NVIC_DisableIRQ(ADC_IRQn);
}

uint32_t CSI_ADC_MSP_Init(void *inst,uint32_t idx)
{
    adc_msp_init(inst,CSI_ADC_Handler);
    return LSADC_BASE_ADDR;
}

void CSI_ADC_MSP_DeInit(uint32_t idx)
{
    adc_msp_deinit();
}

void HAL_ADC_MSP_Init(ADC_HandleTypeDef *inst)
{
    adc_msp_init(inst,ADC_Handler);
}

void HAL_ADC_MSP_DeInit(ADC_HandleTypeDef *inst)
{
    adc_msp_deinit();
}

void HAL_ADC_MSP_Busy_Set(ADC_HandleTypeDef *inst)
{
    adc12b_status_set(true);
}

void HAL_ADC_MSP_Idle_Set(ADC_HandleTypeDef *inst)
{
    adc12b_status_set(false);
}

void adc_channel_vbat_enable(void)
{
    REG_FIELD_WR(SYSCFG->PMU_TRIM, SYSCFG_EN_BAT_DET, 1);
}

void adc_channel_vbat_disable(void)
{
    REG_FIELD_WR(SYSCFG->PMU_TRIM, SYSCFG_EN_BAT_DET, 0);
}

void adc_channel_tempsensor_enable(void)
{
    tempsensor_ldo_init();
}

void adc_channel_tempsensor_disable(void)
{
    tempsensor_ldo_deinit();
}
