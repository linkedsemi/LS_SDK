#ifndef LS_MSP_PIS_H_
#define LS_MSP_PIS_H_
#include "reg_pis_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

/// LSPIS Macro for Register Access
#define LSPIS ((reg_pis_t *)LSPIS_BASE_ADDR)

void HAL_PIS_MSP_Init(void);

void HAL_PIS_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
