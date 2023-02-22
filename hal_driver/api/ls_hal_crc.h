#ifndef LS_HAL_CRC_H_
#define LS_HAL_CRC_H_
#include "HAL_def.h"
#include "ls_msp_crc.h"

void HAL_LSCRC_Init(void);

void HAL_LSCRC_DeInit(void);

uint32_t HAL_LSCRC_CRC32(uint32_t crc,const uint8_t *data,uint32_t length);

uint32_t HAL_LSCRC_32bit_Reverse(uint32_t in);
#endif
