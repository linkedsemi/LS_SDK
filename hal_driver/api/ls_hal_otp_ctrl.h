#ifndef LS_HAL_OTP_CTRL_H_
#define LS_HAL_OTP_CTRL_H_
#include "HAL_def.h"
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif


void HAL_OTP_CTRL_Init();

void HAL_OTP_CTRL_SET_WR_Addr(uint32_t addr[0x4]);

void HAL_OTP_CTRL_SET_RD_Addr(uint32_t addr[0x4]);

HAL_StatusTypeDef HAL_OTP_CTRL_Read(uint32_t offset, uint8_t *data, uint32_t size);

HAL_StatusTypeDef HAL_OTP_CTRL_Write_bit(uint32_t offset, uint8_t bit_field);

HAL_StatusTypeDef HAL_OTP_CTRL_Write_256bit(uint32_t offset, uint8_t *data, uint32_t size);


#ifdef __cplusplus
}
#endif
#endif