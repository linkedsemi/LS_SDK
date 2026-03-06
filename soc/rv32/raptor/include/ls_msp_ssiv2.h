#ifndef LS_MSP_SSIV2_H_
#define LS_MSP_SSIV2_H_
#include "reg_ssiv2_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef REG_FWSPI_BASE
#define LSSSIV2 ((reg_axi_ssi_t *)REG_FWSPI_BASE)
#endif

void HAL_LSSSIV2_MSP_Init();
void HAL_LSSSIV2_MSP_DeInit();

#ifdef __cplusplus
}
#endif

#endif