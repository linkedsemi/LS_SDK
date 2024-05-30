#ifndef SWINT_CALL_ASM_H_
#define SWINT_CALL_ASM_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __CC_ARM

#define SWINT_STRINGIFY(x) #x
#define SWINT_TO_STR(line_num) SWINT_STRINGIFY(line_num)
#define SWINT_LOOP_LABEL "label_line"SWINT_TO_STR(__LINE__)

#define SWINT_FUNC_CALL_INLINE_ASM(func,irq_num)\
        do{\
            __asm volatile ("ldr r4,="#func"\n": : : );\
            uint32_t mask = 1<<((irq_num)&0x1f);\
            uint32_t pending_addr = 0xe000e200 + ((irq_num)>>5)*4;\
            uint32_t pending_stat = 0;\
            __asm volatile ("str %[aMask],[%[aAddr],#0]\n"\
                    SWINT_LOOP_LABEL":\n"\
                    "ldr %[aStat],[%[aAddr],#0]\n"\
                    "tst %[aMask],%[aStat]\n"\
                    "bne "SWINT_LOOP_LABEL : [aStat] "+r" (pending_stat) : \
                [aMask] "r" (mask),[aAddr] "r" (pending_addr)\
                : "r0", "r1", "r2", "r3","r4");\
        }while(0)
#endif

#ifdef __cplusplus
}
#endif

#endif
