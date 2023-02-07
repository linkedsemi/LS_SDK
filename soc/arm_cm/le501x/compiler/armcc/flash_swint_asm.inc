#define SWINT_CONCAT(x,y) x##y
#define SWINT_TYPE(func) SWINT_CONCAT(func,_swint)
#define SWINT_FUNC SWINT_TYPE(FLASH_SWINT_FUNC)
#define SWINT_LOOP_LABEL(func) SWINT_CONCAT(loop_label,func)
    AREA    |.text.SWINT_FUNC|,CODE,READONLY
SWINT_FUNC PROC
    EXPORT SWINT_FUNC
    IMPORT FLASH_SWINT_FUNC
    push	{r4, r5, r6, lr}
    ldr r3, = FLASH_SWINT_FUNC
    movs r5, #0x40
    ldr r6, = 0xe000e200
    str r5, [r6,#0]
SWINT_LOOP_LABEL(FLASH_SWINT_FUNC)
    ldr r4, [r6,#0]
    tst r5,r4
    bne SWINT_LOOP_LABEL(FLASH_SWINT_FUNC)
    pop	{r4, r5, r6, pc}
    ALIGN
    ENDP
#undef SWINT_CONCAT
#undef SWINT_TYPE
#undef SWINT_FUNC
#undef SWINT_LOOP_LABEL
#undef FLASH_SWINT_FUNC