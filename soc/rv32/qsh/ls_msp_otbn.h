#ifndef LS_MSP_OTBN_H_
#define LS_MSP_OTBN_H_
#include "reg_otbn_type.h"
#include "reg_base_addr.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef QSH_PER_OTBN_ADDR
#define LSOTBN ((reg_otbn_t *)QSH_PER_OTBN_ADDR)
#endif

void HAL_LSOTBN_MSP_Init(void);

void HAL_LSOTBN_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif
#endif