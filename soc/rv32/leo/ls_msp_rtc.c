#include "leo.h"
#include "core_rv32.h"
#include "field_manipulate.h"
#include "ls_hal_rtcv2.h"
#include "ls_msp_rtc.h"
#include "exception_isr.h"
#include "reg_v33_rg.h"

static void RTC_handler(void)
{
    HAL_RTC_IRQHandler();
}

void HAL_MSP_RTC_Init(void)
{
    V33_RG->CLKG_SRST = V33_RG_CLKG_CLR_RTC_MASK;
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_RTC_MASK;
    rv_set_int_isr(RTC_IRQn, RTC_handler);
    csi_vic_clear_pending_irq(RTC_IRQn);
    csi_vic_enable_irq(RTC_IRQn);
}

void HAL_MSP_RTC_DeInit(void)
{
    V33_RG->CLKG_SRST = V33_RG_CLKG_CLR_RTC_MASK;
    csi_vic_disable_irq(RTC_IRQn);
}

