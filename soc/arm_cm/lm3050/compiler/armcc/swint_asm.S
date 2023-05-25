    PRESERVE8
    THUMB
    AREA    |.text.SWINT_Handler_ASM|, CODE, READONLY
    FRAME UNWIND ON
SWINT_Handler_ASM PROC
    EXPORT SWINT_Handler_ASM
    IMPORT SWINT_Handler_C
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
    ALIGN
    ENDP
    
#define FLASH_SWINT_FUNC do_hal_flash_program
#include "flash_swint_asm.inc"
	
#define FLASH_SWINT_FUNC do_hal_flash_write_reg
#include "flash_swint_asm.inc"

#define FLASH_SWINT_FUNC do_hal_flash_read
#include "flash_swint_asm.inc"

#define FLASH_SWINT_FUNC do_hal_flash_read_reg
#include "flash_swint_asm.inc"

#define FLASH_SWINT_FUNC do_hal_flash_chip_erase
#include "flash_swint_asm.inc"
	END
