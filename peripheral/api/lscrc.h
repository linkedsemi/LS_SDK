#ifndef LSCRC_H_
#define LSCRC_H_
#include "HAL_def.h"
#include "reg_calc_crc_type.h"
#include "reg_base_addr.h"
#define LSCRC ((reg_calc_crc_t *)LSCRC_BASE_ADDR)

void HAL_LSCRC_Init(void);

void HAL_LSCRC_DeInit(void);

uint32_t HAL_LSCRC_CRC32(uint32_t crc,const uint8_t *data,uint32_t length);

uint32_t HAL_LSCRC_32bit_Reverse(uint32_t in);
#endif
