    .syntax unified
    .arch armv6-m

    .section .text.SWINT_Handler_ASM
    .align 1
	.globl SWINT_Handler_ASM
	.type SWINT_Handler_ASM,%function
SWINT_Handler_ASM:
    mov r0,sp
	ldr r1,=SWINT_Handler_C
	bx r1

    .size	SWINT_Handler_ASM, . - SWINT_Handler_ASM
