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
    
#define FLASH_SWINT_FUNC do_hal_flash_program
#include "flash_swint_asm.inc"
	
#define FLASH_SWINT_FUNC do_hal_flash_erase
#include "flash_swint_asm.inc"

#define FLASH_SWINT_FUNC do_hal_flash_read
#include "flash_swint_asm.inc"

#define FLASH_SWINT_FUNC do_hal_flash_read_reg
#include "flash_swint_asm.inc"

#define FLASH_SWINT_FUNC do_hal_flash_chip_erase
#include "flash_swint_asm.inc"

#define FLASH_SWINT_FUNC do_hal_flash_erase_security_area
#include "flash_swint_asm.inc"
	
#define FLASH_SWINT_FUNC do_hal_flash_program_security_area
#include "flash_swint_asm.inc"

#define FLASH_SWINT_FUNC do_hal_flash_read_security_area
#include "flash_swint_asm.inc"
	END
