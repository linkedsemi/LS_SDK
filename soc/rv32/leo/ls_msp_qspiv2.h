#ifndef LS_MSP_QSPIV2_H_
#define LS_MSP_QSPIV2_H_
#include "qspiv2_config.h"
#include "reg_qspiv2_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LSQSPIV2 ((reg_lsqspiv2_t *)LSQSPIV2_BASE_ADDR)

extern uint32_t (*qspiv2_global_int_disable_fn)();
extern void (*qspiv2_global_int_restore_fn)(uint32_t);

void lsqspiv2_msp_init(reg_lsqspiv2_t *reg);

#ifdef __cplusplus
}
#endif

#endif

