#include <stdint.h>
#include "hal_flash_int.h"
#include "platform.h"

void SWINT_Handler_C(uint32_t *args)
{
    uint32_t (*func)(uint32_t,uint32_t,uint32_t) = (uint32_t (*)(uint32_t,uint32_t,uint32_t))args[3];
    args[0] = func(args[0],args[1],args[2]);
}

#ifndef __CC_ARM
__attribute__((naked)) void do_hal_flash_program_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_program,FLASH_SWINT_SET_ASM);
}

__attribute__((naked)) void do_hal_flash_erase_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_erase,FLASH_SWINT_SET_ASM);
}

__attribute__((naked)) void do_hal_flash_read_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read,FLASH_SWINT_SET_ASM);
}

__attribute__((naked)) void do_hal_flash_read_reg_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read_reg,FLASH_SWINT_SET_ASM);
}

__attribute__((naked)) void do_hal_flash_chip_erase_swint(void)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_chip_erase,FLASH_SWINT_SET_ASM);
}

__attribute__((naked)) void do_hal_flash_erase_security_area_swint(uint8_t idx)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_erase_security_area,FLASH_SWINT_SET_ASM);
}

__attribute__((naked)) void do_hal_flash_program_security_area_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_program_security_area,FLASH_SWINT_SET_ASM);
}

__attribute__((naked)) void do_hal_flash_read_security_area_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read_security_area,FLASH_SWINT_SET_ASM);
}

#endif