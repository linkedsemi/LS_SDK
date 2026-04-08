#ifndef LS_MSP_OTPV2_H_
#define LS_MSP_OTPV2_H_
#include "reg_base_addr.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef REG_OTP_BASE
#define OTP2 ((reg_axi_otp_t *)(REG_OTP_BASE + 0x1100))
#endif

#ifdef REG_OTP_CYP_BASE
#define OTP3 ((reg_axi_otp_t *)(REG_OTP_CYP_BASE + 0x1100))
#endif

void HAL_LSOTPV2_MSP_Init();

void HAL_LSOTPV2_MSP_DeInit();

#ifdef __cplusplus
}
#endif

#endif /* LS_MSP_OTPV2_H_ */