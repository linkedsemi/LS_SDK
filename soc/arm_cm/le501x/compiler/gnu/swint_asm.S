    .syntax unified
    .arch armv6-m

    .section .text.SWINT_Handler_ASM
    .align 1
	.globl SWINT_Handler_ASM
	.type SWINT_Handler_ASM,%function
SWINT_Handler_ASM:
    MOVS R0,#4
    MOV R1,LR
    TST R0,R1
    BEQ stacking_used_MSP
    mrs r0,psp
    b SWINT_C_Routine
stacking_used_MSP:
    mrs r0,msp
SWINT_C_Routine:
    mov r1,r4
	ldr r2,=SWINT_Handler_C
	bx r2

    .size	SWINT_Handler_ASM, . - SWINT_Handler_ASM
