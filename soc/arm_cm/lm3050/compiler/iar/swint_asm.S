    MODULE swint_asm
    PUBLIC SWINT_Handler_ASM
    EXTERN SWINT_Handler_C
    SECTION `.text.SWINT_Handler_ASM`:CODE
    THUMB
SWINT_Handler_ASM
    mov r0,sp
	ldr r1,=SWINT_Handler_C
	bx r1

    END