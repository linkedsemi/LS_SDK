#include "ls_msp_rtc.h"
#include "reg_base_addr.h"
#include "reg_syscfg.h"
#include "platform.h"
#include "field_manipulate.h"
#include "le501x.h"
#include "reg_rcc.h"
#include "ls_hal_rtc.h"

void RTC_handler(void)
{
    HAL_RTC_IRQHandler();
}
void HAL_MSP_RTC_Init(void)
{
    REG_FIELD_WR(RCC->AHBRST, RCC_RTC, 1);
    REG_FIELD_WR(RCC->AHBRST, RCC_RTC, 0);
    arm_cm_set_int_isr(RTC_IRQn, RTC_handler);
    __NVIC_ClearPendingIRQ(RTC_IRQn);
    __NVIC_EnableIRQ(RTC_IRQn);
    REG_FIELD_WR(RCC->AHBEN, RCC_RTC, 1);
}

void HAL_MSP_RTC_DeInit(void)
{
    REG_FIELD_WR(RCC->AHBEN, RCC_RTC, 0);
}
#if SDK_LSI_USED
void save_calendar_init_val(uint32_t cal, uint32_t time)
{
    SYSCFG->BKD[4] = cal;
    SYSCFG->BKD[5] = time;
}

void save_calendar_raw_val(uint32_t raw_val)
{
    SYSCFG->BKD[3] = raw_val;
}

void save_seconds_remainder(uint32_t remainder)
{
    SYSCFG->BKD[2] = remainder;
}

void load_calendar_raw_val(uint32_t *raw_val)
{
    *raw_val = SYSCFG->BKD[3];
}

void load_calendar_init_val(uint32_t *cal, uint32_t *time)
{
    *cal = SYSCFG->BKD[4];
    *time = SYSCFG->BKD[5];
}

void load_seconds_remainder(uint32_t *remainder)
{
    *remainder = SYSCFG->BKD[2];
}
#endif

