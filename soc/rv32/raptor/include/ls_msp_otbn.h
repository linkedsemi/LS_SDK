#ifndef LS_MSP_OTBN_H_
#define LS_MSP_OTBN_H_
#include "reg_otbn_type.h"
#include "reg_base_addr.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef REG_OTBN_BASE
#define LSOTBN ((reg_otbn_t *)REG_OTBN_BASE)
#define OTBN_IMEM_ADDR (REG_OTBN_BASE + 0x4000)
#define OTBN_DMEM_ADDR (REG_OTBN_BASE + 0x8000)
#endif

void HAL_LSOTBN_MSP_Init(void);

void HAL_LSOTBN_MSP_DeInit(void);

void HAL_OTBN_SYSC_IRQHandler();

#ifdef __cplusplus
}
#endif
#endif