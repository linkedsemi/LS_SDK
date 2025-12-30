#ifndef LS_MSP_IWDG_H_
#define LS_MSP_IWDG_H_
#include "reg_iwdgv2_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SEC_PMU_IWDT1_ADDR
#define SEC_PMU_IWDG ((reg_iwdg_t *)SEC_PMU_IWDT1_ADDR) /*!< LSIWDG Macro for Register Access*/
#endif
#ifdef SEC_IWDT1_ADDR
#define SEC_IWDG ((reg_iwdg_t *)SEC_IWDT1_ADDR) /*!< LSIWDG Macro for Register Access*/
#endif
#ifdef APP_IWDT2_ADDR
#define APP_IWDG ((reg_iwdg_t *)APP_IWDT2_ADDR) /*!< LSIWDG Macro for Register Access*/
#endif

#define WDT_FLAG_RESET_SHIFT		(0)

#define WDT_FLAG_RESET_CPU_CORE		(1 << WDT_FLAG_RESET_SHIFT)

#define WDT_FLAG_RESET_SOC		(2 << WDT_FLAG_RESET_SHIFT)




void HAL_IWDG_MSP_Init(reg_iwdg_t *iwdg);

void HAL_IWDG_MSP_DeInit(reg_iwdg_t *iwdg);

void HAL_IWDG_MSP_DEBUG(reg_iwdg_t *iwdg, uint8_t debug_en);

int HAL_IWDG_IS_MATCH(reg_iwdg_t *iwdg,uint8_t flags);
#ifdef __cplusplus
}
#endif

#endif
