#ifndef LS_MSP_QSPIV2_H_
#define LS_MSP_QSPIV2_H_
#include "qspiv2_config.h"
#include "reg_qspiv2_type.h"
#include "reg_base_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LSQSPIV2 ((reg_lsqspiv2_t *)LSQSPIV2_BASE_ADDR)

void lsqspiv2_msp_init(void);


#ifdef __cplusplus
}
#endif

#endif

