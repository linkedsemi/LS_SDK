#ifndef LS_MSP_RTC_H_
#define LS_MSP_RTC_H_
#include "reg_rtcv2_type.h"
#include "reg_base_addr.h"

#ifdef LSRTC_BASE_ADDR
#define RTC ((reg_rtc_t *)LSRTC_BASE_ADDR)
#endif

void HAL_MSP_RTC_Init(void);
void HAL_MSP_RTC_DeInit(void);
#if SDK_LSI_USED
void save_calendar_init_val(uint32_t cal, uint32_t time);
void save_calendar_raw_val(uint32_t raw_val);
void save_seconds_remainder(uint32_t remainder);
void load_calendar_init_val(uint32_t *cal, uint32_t *time);
void load_calendar_raw_val(uint32_t *raw_val);
void load_seconds_remainder(uint32_t *remainder);
#endif
#endif
