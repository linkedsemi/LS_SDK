#ifndef SWINT_CALL_ASM_H_
#define SWINT_CALL_ASM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SWINT_STRINGIFY(x) #x
#define SWINT_TO_STR(line_num) SWINT_STRINGIFY(line_num)
#define SWINT_LOOP_LABEL "label_line"SWINT_TO_STR(__LINE__)

#define SWINT_FUNC_CALL_INLINE_ASM(func,irq_num)\
        do{\
            __asm ("la a4,"#func"\n" : : : );\
            uint32_t mask = 1;\
            uint32_t pending_addr = 0xe0801000 + (irq_num)*4;\
            __asm ("sb %0,0(%1)\n"\
                    SWINT_LOOP_LABEL":\n"\
                    "lb %0,0(%1)\n"\
                    "bnez %0,"SWINT_LOOP_LABEL"\n"\
                    : : "r"(mask),"r"(pending_addr) \
                : "a0", "a1", "a2", "a3","a4");\
        }while(0)

#ifdef __cplusplus
}
#endif

#endif
