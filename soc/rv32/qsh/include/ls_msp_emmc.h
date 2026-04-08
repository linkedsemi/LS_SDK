#ifndef LS_MSP_EMMC_H_
#define LS_MSP_EMMC_H_
#include "reg_base_addr.h"
#include "reg_emmc_type.h"
#include "ls_hal_emmc.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef APP_EMMC1_CFG_ADDR
#define LSEMMC1 APP_EMMC1_CFG_ADDR
#endif

#ifdef APP_EMMC2_CFG_ADDR
#define LSEMMC2 APP_EMMC2_CFG_ADDR
#endif

void HAL_LSEMMC_MSP_Init(sdhci_host *host);
void HAL_LSEMMC_MSP_DeInit(sdhci_host *host);

#ifdef __cplusplus
}
#endif

#endif
