#ifndef SWINT_CALL_ASM_H_
#define SWINT_CALL_ASM_H_
#if defined(__GNUC__)
#define SWINT_FUNC_CALL_INLINE_ASM(func,swint_set)\
        __asm__ volatile ("push {lr}\n"\
                "ldr r3,="#func"\n"\
               "bl "#swint_set"\n"\
               "pop {pc}" : : : )

#define SWINT_SET_INLINE_ASM(irq_num) \
        uint32_t mask = 1<<((irq_num)&0x1f);\
        uint32_t pending_addr = 0xe000e200 + ((irq_num)>>5)*4;\
        uint32_t pending_stat = 0;\
        __asm__ volatile ("str %[aMask],[%[aAddr],#0]\n"\
                "cmp:\n"\
                "ldr %[aStat],[%[aAddr],#0]\n"\
                "tst %[aMask],%[aStat]\n"\
                "bne cmp": [aStat] "+r" (pending_stat) : \
            [aMask] "r" (mask),[aAddr] "r" (pending_addr)\
            : "r0", "r1", "r2", "r3")

#elif defined(__ICCARM__)

#elif defined(__CC_ARM)
#define SWINT_FUNC_CALL_INLINE_ASM(func,swint_set)\
        push {lr}\n\
        ldr r3,="#func"\n\
        bl "#swint_set"\n\
        pop {pc}
 
#define SWINT_SET_INLINE_ASM(irq_num) \
        uint32_t mask = 1<<((irq_num)&0x1f);\
        uint32_t pending_addr = 0xe000e200 + ((irq_num)>>5)*4;\
        __asm (\
                ldr r5, =mask\n\
                ldr r6, =pending_addr\n\
                str r5,{r6}\n\
            cmp:\n\
                ldr r4,{r6}\n\
                tst r5,r4\n\
                bne cmp\
        )
#endif
#endif
