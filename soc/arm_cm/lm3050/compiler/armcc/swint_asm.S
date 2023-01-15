    PRESERVE8
    THUMB
    AREA    |.text.SWINT_Handler_ASM|, CODE, READONLY
    FRAME UNWIND ON
SWINT_Handler_ASM PROC
    EXPORT SWINT_Handler_ASM
    IMPORT SWINT_Handler_C
    mov r0,sp
	ldr r1,=SWINT_Handler_C
	bx r1
    ALIGN
    ENDP
    
    END
