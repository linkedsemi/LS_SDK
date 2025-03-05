#ifndef LS_MSP_LTPI_H_
#define LS_MSP_LTPI_H_
#include "reg_ltpi_phy_type.h"
#include "reg_base_addr.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef APP_LTPI_HPM_CFG_ADDR
#define LTPI_HPM ((reg_ltpi_phy_t *)APP_LTPI_HPM_CFG_ADDR)
#endif
#ifdef APP_LTPI_PHY_CTL_ADDR
#define LTPI_PHY ((reg_ltpi_phy_t *)APP_LTPI_PHY_CTL_ADDR)
#endif

void HAL_MSP_LTPI_PHY_Init();

void HAL_MSP_LTPI_PHY_DeInit();

#ifdef __cplusplus
}
#endif
#endif