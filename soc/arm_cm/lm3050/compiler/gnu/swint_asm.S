    .syntax unified
    .arch armv6-m

    .section .text.SWINT_Handler_ASM
    .align 1
	.globl SWINT_Handler_ASM
	.type SWINT_Handler_ASM,%function
SWINT_Handler_ASM:
    mov r0,sp
    mov r1,r4
	ldr r2,=SWINT_Handler_C
	bx r2

    .size	SWINT_Handler_ASM, . - SWINT_Handler_ASM
