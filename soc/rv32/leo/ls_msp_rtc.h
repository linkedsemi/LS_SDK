#ifndef LS_MSP_RTC_H_
#define LS_MSP_RTC_H_
#include "reg_rtcv2_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LSRTC_BASE_ADDR
#define RTC ((reg_rtc_t *)LSRTC_BASE_ADDR)
#endif

void HAL_MSP_RTC_Init(void);
void HAL_MSP_RTC_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
