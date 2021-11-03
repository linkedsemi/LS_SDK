#ifndef SWINT_CALL_H_
#define SWINT_CALL_H_
#include <stdint.h>
#include "compile_flag.h"
#include "swint_call_asm.h"

void ll_swint_set(void);

#define LL_SWINT_FUNC_CALL_INLINE_ASM(func) SWINT_FUNC_CALL_INLINE_ASM(func,ll_swint_set)

#define LL_SWINT_CALL_3_ARGV(swint_call_name,return_type,func_name,param0_type,param1_type,param2_type)\
    __attribute__((naked)) NOINLINE return_type swint_call_name(param0_type p0,param1_type p1,param2_type p2) \
    {\
        LL_SWINT_FUNC_CALL_INLINE_ASM(func_name); \
    }


#define LL_SWINT_CALL_2_ARGV(swint_call_name,return_type,func_name,param0_type,param1_type)\
    __attribute__((naked)) NOINLINE return_type swint_call_name(param0_type p0,param1_type p1) \
    {\
        LL_SWINT_FUNC_CALL_INLINE_ASM(func_name); \
    }


#define LL_SWINT_CALL_1_ARGV(swint_call_name,return_type,func_name,param0_type)\
    __attribute__((naked)) NOINLINE return_type swint_call_name(param0_type p0) \
    {\
        LL_SWINT_FUNC_CALL_INLINE_ASM(func_name); \
    }


#define LL_SWINT_CALL_NO_ARGV(swint_call_name,return_type,func_name)\
    __attribute__((naked)) NOINLINE return_type swint_call_name() \
    {\
        LL_SWINT_FUNC_CALL_INLINE_ASM(func_name); \
    }

#endif
