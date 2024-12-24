#ifndef LS_MSP_QSPIV2_H_
#define LS_MSP_QSPIV2_H_
#include "qspiv2_config.h"
#include "reg_qspiv2_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SEC_QSPI1_ADDR
#define LSQSPIV2 ((reg_lsqspiv2_t *) SEC_QSPI1_ADDR)
#endif
#ifdef APP_QSPI2_ADDR
#define LSQSPIV2_2 ((reg_lsqspiv2_t *) APP_QSPI2_ADDR)
#endif

extern uint32_t (*qspiv2_global_int_disable_fn)();
extern void (*qspiv2_global_int_restore_fn)(uint32_t);

void lsqspiv2_msp_init(void);

#ifdef __cplusplus
}
#endif

#endif

