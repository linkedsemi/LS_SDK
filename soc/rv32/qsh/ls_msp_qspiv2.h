#ifndef LS_MSP_QSPIV2_H_
#define LS_MSP_QSPIV2_H_
#include "qspiv2_config.h"
#include "reg_qspiv2_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef QSH_APB_QSPI1_ADDR
#define LSQSPIV2 ((reg_lsqspiv2_t *) QSH_APB_QSPI1_ADDR)
#endif
#ifdef QSH_APB_QSPI2_ADDR
#define LSQSPIV2_2 ((reg_lsqspiv2_t *) QSH_APB_QSPI2_ADDR)
#endif

extern uint32_t (*qspiv2_global_int_disable_fn)();
extern void (*qspiv2_global_int_restore_fn)(uint32_t);

void lsqspiv2_msp_init(void);

#ifdef __cplusplus
}
#endif

#endif

