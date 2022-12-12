#ifndef LS_MSP_CRC_H_
#define LS_MSP_CRC_H_
#include "reg_calc_crc_type.h"
#include "reg_base_addr.h"

#define LSCRC ((reg_calc_crc_t *)LSCRC_BASE_ADDR)

void HAL_LSCRC_MSP_Init(void);

void HAL_LSCRC_MSP_DeInit(void);

#endif
