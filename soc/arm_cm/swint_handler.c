#include <stdint.h>
#include "hal_flash_int.h"
#include "swint_call_asm.h"
#include "platform.h"

void SWINT_Handler_C(uint32_t *args)
{
    uint32_t (*func)(uint32_t,uint32_t,uint32_t) = (uint32_t (*)(uint32_t,uint32_t,uint32_t))args[3];
    args[0] = func(args[0],args[1],args[2]);
}


__attribute__((naked)) void do_hal_flash_program_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_program,flash_swint_set);
}

__attribute__((naked)) void do_hal_flash_erase_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_erase,flash_swint_set);
}

__attribute__((naked)) void do_hal_flash_read_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read,flash_swint_set);
}

__attribute__((naked)) void do_hal_flash_read_reg_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read_reg,flash_swint_set);
}

__attribute__((naked)) void do_hal_flash_chip_eras_swint(void)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_chip_erase,flash_swint_set);

}

__attribute__((naked)) void do_hal_flash_erase_security_are_swint(uint8_t idx)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_erase_security_area,flash_swint_set);

}

__attribute__((naked)) void do_hal_flash_program_security_are_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_program_security_area,flash_swint_set);

}

__attribute__((naked)) void do_hal_flash_read_security_area_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read_security_area,flash_swint_set);
}
