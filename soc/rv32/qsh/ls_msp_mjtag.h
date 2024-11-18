#ifndef LS_MSP_MJTAG_H_
#define LS_MSP_MJTAG_H_
#include "reg_base_addr.h"
#include "reg_mjtag_type.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef QSH_APB_MJTAG1_ADDR
#define MJTAG1 ((reg_mjtag_t *)QSH_APB_MJTAG1_ADDR)
#endif
#ifdef QSH_APB_MJTAG2_ADDR
#define MJTAG2 ((reg_mjtag_t *)QSH_APB_MJTAG2_ADDR)
#endif
#ifdef QSH_APB_MJTAG3_ADDR
#define MJTAG3 ((reg_mjtag_t *)QSH_APB_MJTAG3_ADDR)
#endif

struct __MJTAG_HandleTypeDef;
void HAL_MJTAG_MSP_Init(struct __MJTAG_HandleTypeDef *inst);

void HAL_MJTAG_MSP_DeInit(struct __MJTAG_HandleTypeDef *inst);

#ifdef __cplusplus
}
#endif
#endif