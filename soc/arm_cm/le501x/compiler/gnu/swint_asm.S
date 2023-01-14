    .section .text.SWINT_Handler_ASM
    .align 1
	.globl SWINT_Handler_ASM
	.type SWINT_Handler_ASM,%function
SWINT_Handler_ASM:
    mov r0,sp
	b SWINT_Handler_C

    .size	SWINT_Handler_ASM, . - SWINT_Handler_ASM
