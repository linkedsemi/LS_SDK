#ifndef LS_MSP_IWDG_H_
#define LS_MSP_IWDG_H_
#include "reg_base_addr.h"
#include "reg_iwdgv2_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef REG_WDT0_BASE
#define IWDT0 ((reg_iwdg_t *)REG_WDT0_BASE)
#endif

#ifdef REG_WDT1_BASE
#define IWDT1 ((reg_iwdg_t *)REG_WDT1_BASE)
#endif

#ifdef REG_WDT2_BASE
#define IWDT2 ((reg_iwdg_t *)REG_WDT2_BASE)
#endif

#ifdef REG_WDT3_BASE
#define IWDT3 ((reg_iwdg_t *)REG_WDT3_BASE)
#endif

#ifdef REG_WDT4_BASE
#define IWDT4 ((reg_iwdg_t *)REG_WDT4_BASE)
#endif

#ifdef REG_WDT5_BASE
#define IWDT5 ((reg_iwdg_t *)REG_WDT5_BASE)
#endif

#ifdef REG_WDT6_BASE
#define IWDT6 ((reg_iwdg_t *)REG_WDT6_BASE)
#endif

#ifdef REG_WDT7_BASE
#define IWDT7 ((reg_iwdg_t *)REG_WDT7_BASE)
#endif

void HAL_IWDG_MSP_Init(reg_iwdg_t *iwdg);

void HAL_IWDG_MSP_DeInit(reg_iwdg_t *iwdg);

#ifdef __cplusplus
}
#endif

#endif