#ifndef LS_MSP_KSCAN_H_
#define LS_MSP_KSCAN_H_

#include "reg_base_addr.h"
#include "reg_kscan_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KSCAN_BASE_ADDR
/// LSKSCAN Macro for Register Access
#define KSCAN ((reg_kscan_t *) KSCAN_BASE_ADDR)
#endif

void HAL_KSCAN_MSP_Init(void);

void HAL_KSCAN_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
