#ifndef LS_MSP_IWDG_H_
#define LS_MSP_IWDG_H_
#include "reg_iwdg_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LSIWDG_BASE_ADDR
#define LSIWDG ((reg_iwdg_t *)LSIWDG_BASE_ADDR) /*!< LSIWDG Macro for Register Access*/
#endif

void HAL_IWDG_MSP_Init(void);

void HAL_IWDG_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif
