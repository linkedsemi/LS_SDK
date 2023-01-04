#include "calc_div.h"
#include "field_manipulate.h"
#include "reg_calc_type.h"
#include "reg_base_addr.h"

#define CALC ((reg_calc_t *)CALC_BASE_ADDR)

uint64_t calc_div(uint32_t dividend,uint32_t divisor,bool signed_div)
{
    CALC->DIVCSR = FIELD_BUILD(CALC_DIV_SIGN,signed_div?1:0) | FIELD_BUILD(CALC_DIV_TRM,0);
    CALC->DIVS = divisor;
    CALC->DIVD = dividend;
    while(REG_FIELD_RD(CALC->DIVCSR,CALC_DIV_BUSY));
    return (uint64_t)CALC->DIVR<<32 | CALC->DIVQ;
}

