#ifndef LS_LL_OPAMP_H_
#define LS_LL_OPAMP_H_
#include <stdbool.h>
#ifdef LM3050
#include "reg_v33_rg_type.h"
#include "field_manipulate.h"

static inline void LL_OPAMP_Set(bool op1en, bool op2en, bool op3en)
{
    MODIFY_REG(V33_RG->OP_CTRL, V33_RG_OP1_EN_MASK | V33_RG_OP2_EN_MASK | V33_RG_OP3_EN_MASK, op1en << V33_RG_OP1_EN_POS | op2en << V33_RG_OP2_EN_POS | op3en << V33_RG_OP3_EN_POS);
}
#endif

#endif