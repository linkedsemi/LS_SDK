#ifndef CALC_DIV_H_
#define CALC_DIV_H_
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t calc_div(uint32_t dividend,uint32_t divisor,bool signed_div);

#ifdef __cplusplus
}
#endif

#endif

