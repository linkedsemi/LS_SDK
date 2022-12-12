#include "ls_msp_rtc.h"
#include "reg_base_addr.h"
#include "platform.h"
#include "field_manipulate.h"
#include "lm3050.h"
#include "ls_hal_rtcv2.h"
#include "reg_v33_rg_type.h"

void RTC_handler(void)
{
    HAL_RTC_IRQHandler();
}

void HAL_MSP_RTC_Init(void)
{
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_RTC_MASK;
    arm_cm_set_int_isr(RTC_IRQn, HAL_RTC_IRQHandler);
    __NVIC_ClearPendingIRQ(RTC_IRQn);
    __NVIC_EnableIRQ(RTC_IRQn);
}

void HAL_MSP_RTC_DeInit(void)
{
    V33_RG->CLKG_SRST = V33_RG_CLKG_CLR_RTC_MASK;
     __NVIC_DisableIRQ(RTC_IRQn);
}

