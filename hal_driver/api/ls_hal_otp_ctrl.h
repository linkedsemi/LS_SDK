#ifndef LS_HAL_OTP_CTRL_H_
#define LS_HAL_OTP_CTRL_H_
#include "HAL_def.h"
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif


void HAL_OTP_CTRL_Init();

void HAL_OTP_SET_WR_Addr(uint32_t addr[0x4]);

void HAL_OTP_SET_RD_Addr(uint32_t addr[0x4]);

HAL_StatusTypeDef HAL_OTP_Read(uint32_t offset, uint8_t *data, uint32_t length);

HAL_StatusTypeDef HAL_OTP_Write(uint32_t offset, uint8_t *data, uint32_t length);


#ifdef __cplusplus
}
#endif
#endif