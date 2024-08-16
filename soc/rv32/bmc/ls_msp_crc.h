#ifndef LS_MSP_CRC_H_
#define LS_MSP_CRC_H_
#include "reg_calc_crc_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BMC_PER_CRC_ADDR
#define LSCRC ((reg_calc_crc_t *)BMC_PER_CRC_ADDR)
#endif

void HAL_LSCRC_MSP_Init(void);

void HAL_LSCRC_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
