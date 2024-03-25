    MODULE swint_asm
    PUBLIC SWINT_Handler_ASM
    EXTERN SWINT_Handler_C
    SECTION `.text.SWINT_Handler_ASM`:CODE
    THUMB
SWINT_Handler_ASM
    MOVS R0,#4
    MOV R1,LR
    TST R0,R1
    BEQ stacking_used_MSP
    mrs r0,psp
    b SWINT_C_Routine
stacking_used_MSP
    mrs r0,msp
SWINT_C_Routine
    mov r1,r4
	ldr r2,=SWINT_Handler_C
	bx r2

    END