#ifndef LS_MSP_WWDG_H_
#define LS_MSP_WWDG_H_
#include "reg_wwdg_type.h"
#include "reg_base_addr.h"

#ifdef LSWWDT_BASE_ADDR
#define LSWWDG ((reg_wwdg_t *)LSWWDT_BASE_ADDR) /*!< LSWWDG Macro for Register Access*/
#endif


void HAL_WWDG_MSP_Init(void);

void HAL_WWDG_MSP_DeInit(void);

#endif
