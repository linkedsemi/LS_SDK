#include "ls_msp_pwm.h"
#include "ls_hal_pwm.h"
#include "leo.h"
#include "core_rv32.h"
#include "dmac_config.h"
#include "reg_sysc_per.h"
#include "exception_isr.h"
#include "field_manipulate.h"

void HAL_PWM_MSP_Init(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_PWM_MASK;
    SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_CLR_PWM_N_MASK;
    SYSC_PER->PD_PER_SRST0 = SYSC_PER_SRST_SET_PWM_N_MASK;
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_SET_PWM_MASK;
    rv_set_int_isr(PWM_IRQn, HAL_PWM_IRQHandler);
    csi_vic_clear_pending_irq(PWM_IRQn);
    csi_vic_enable_irq(PWM_IRQn);                         
}

void HAL_PWM_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG0 = SYSC_PER_CLKG_CLR_PWM_MASK;
    csi_vic_disable_irq(PWM_IRQn);
}

uint8_t HAL_PWM_CHANNELX_DMA_Handshake_Get(pwm_channel_t channel)
{
    return PWM_1 + channel;
}