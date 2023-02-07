    MODULE swint_asm
    PUBLIC SWINT_Handler_ASM
    EXTERN SWINT_Handler_C
    SECTION `.text.SWINT_Handler_ASM`:CODE
    THUMB
SWINT_Handler_ASM
    mov r0,sp
    mov r1,r4
	ldr r2,=SWINT_Handler_C
	bx r2

    END