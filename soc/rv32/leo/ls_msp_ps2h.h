#ifndef LS_MSP_PS2H_H_
#define LS_MSP_PS2H_H_
#include "reg_base_addr.h"
#include "reg_ps2h_type.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef PS2H1_BASE_ADDR
#define PS2H1 ((reg_ps2h_t *) PS2H1_BASE_ADDR)
#endif
#ifdef PS2H2_BASE_ADDR
#define PS2H2 ((reg_ps2h_t *) PS2H2_BASE_ADDR)
#endif
#ifdef PS2H3_BASE_ADDR
#define PS2H3 ((reg_ps2h_t *) PS2H3_BASE_ADDR)
#endif
#ifdef PS2H4_BASE_ADDR
#define PS2H4 ((reg_ps2h_t *) PS2H4_BASE_ADDR)
#endif

struct __PS2H_HandleTypeDef;
void HAL_PS2H_MSP_Init(struct __PS2H_HandleTypeDef *inst);
void HAL_PS2H_MSP_DeInit();

#ifdef __cplusplus
}
#endif

#endif