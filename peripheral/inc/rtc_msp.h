#ifndef RTC_MSP_H_
#define RTC_MSP_H_

#include "lsrtc.h"

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
