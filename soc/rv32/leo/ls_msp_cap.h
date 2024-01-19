#ifndef LS_MSP_CAP_H_
#define LS_MSP_CAP_H_
#include "reg_base_addr.h"
#include "reg_cap_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CAP_BASE_ADDR
#define CAP ((reg_cap_t *) CAP_BASE_ADDR)
#endif

void HAL_LSCAP_MSP_Init(void);
void HAL_LSCAP_MSP_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif

