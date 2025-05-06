#ifndef LS_MSP_OTP_CTRL_H_
#define LS_MSP_OTP_CTRL_H_
#include "reg_otp_ctrl_type.h"
#include "reg_base_addr.h"
#ifdef __cplusplus
extern "C" {
#endif

#define OTP_MEM_TOTAL_BYTES   (0x1000)

#define OTP_CTRL ((reg_otp_ctrl_t *)SEC_OTP_CTRL_ADDR)

void HAL_MSP_OTP_CTRL_Init();

void HAL_MSP_OTP_CTRL_DeInit();


#ifdef __cplusplus
}
#endif
#endif