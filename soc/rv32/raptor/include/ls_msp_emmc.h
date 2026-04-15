#ifndef LS_MSP_EMMC_H_
#define LS_MSP_EMMC_H_
#include "reg_base_addr.h"
#include "reg_emmc_type.h"
#include "ls_hal_emmc.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef REG_EMMC0_BASE
#define LSEMMC REG_EMMC0_BASE
#endif


void HAL_LSEMMC_MSP_Init(sdhci_host *host);
void HAL_LSEMMC_MSP_DeInit(sdhci_host *host);

#ifdef __cplusplus
}
#endif

#endif