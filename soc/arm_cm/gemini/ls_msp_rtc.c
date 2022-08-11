#include "ls_msp_rtc.h"
#include "reg_base_addr.h"
#include "reg_syscfg.h"
#include "platform.h"
#include "field_manipulate.h"
#include "gemini.h"
#include "reg_rcc.h"
#include "reg_v33_rg_type.h"

void RTC_handler(void)
{
    HAL_RTC_IRQHandler();
}

void HAL_MSP_RTC_Init(void)
{
    REG_FIELD_WR(V33_RG->CLKG_SRST, V33_RG_CLKG_SET_RTC, 1);
    arm_cm_set_int_isr(RTC_IRQn, RTC_handler);
    __NVIC_ClearPendingIRQ(RTC_IRQn);
    __NVIC_EnableIRQ(RTC_IRQn);
}

void HAL_MSP_RTC_DeInit(void)
{
    REG_FIELD_WR(V33_RG->CLKG_SRST, V33_RG_CLKG_CLR_RTC, 1);
}

