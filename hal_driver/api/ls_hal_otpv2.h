#ifndef LS_HAL_OTPV2_H_
#define LS_HAL_OTPV2_H_
#include "ls_msp_otpv2.h"
#include "reg_otpv2_type.h"
#include "HAL_def.h"
#include <stdbool.h>

typedef struct __OTPV2_HandleTypeDef
{
  reg_axi_otp_t                	*Instance;

} OTPV2_HandleTypeDef;

#define OTP_MEM_TOTAL_BYTES 2048

HAL_StatusTypeDef HAL_OTPV2_Init();

HAL_StatusTypeDef HAL_OTPV2_DeInit();

HAL_StatusTypeDef HAL_OTPV2_Read_Write(bool is_system_side, bool is_read, uint32_t offset, uint32_t *data, uint32_t length);

HAL_StatusTypeDef HAL_OTPV2_Read(uint32_t offset, uint32_t *data, uint32_t length);

HAL_StatusTypeDef HAL_OTPV2_Write(uint32_t offset, uint32_t *data, uint32_t length);

#endif
