#include "hal_flash_int.h"
#include "swint_call_asm.h"

#define FLASH_EXECUTE_WITH_RETVAL(return_val,op,...) \
    do{\
        if(GLOBAL_INT_MASK_STATUS())\
        {\
            return_val = op(__VA_ARGS__);\
        }else\
        {\
            return_val = op##_swint(__VA_ARGS__);\
        }\
    }while(0)

#define FLASH_EXECUTE_NO_RETVAL(op,...) \
    do{\
        if(GLOBAL_INT_MASK_STATUS())\
        {\
            op(__VA_ARGS__);\
        }else\
        {\
            op##_swint(__VA_ARGS__);\
        }\
    }while(0)

void hal_flash_program_operation(void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_program,param);
}

void hal_flash_erase_operation(void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_erase,param);
}

void hal_flash_read_operation(void*param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_read, param);
}

void hal_flash_read_reg_operation(void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_read_reg,param);
}

void hal_flash_chip_erase_operation()
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_chip_erase);
}

void hal_flash_erase_security_area_operation(uint8_t idx)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_erase_security_area,idx);
}

void hal_flash_program_security_area_operation(void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_program_security_area, param);
}

void hal_flash_read_security_area_operation(void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_read_security_area, param);
}

#ifndef __CC_ARM
__attribute__((naked)) void do_hal_flash_program_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_program,FLASH_SWINT_NUM);
}

__attribute__((naked)) void do_hal_flash_erase_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_erase,FLASH_SWINT_NUM);
}

__attribute__((naked)) void do_hal_flash_read_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read,FLASH_SWINT_NUM);
}

__attribute__((naked)) void do_hal_flash_read_reg_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read_reg,FLASH_SWINT_NUM);
}

__attribute__((naked)) void do_hal_flash_chip_erase_swint(void)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_chip_erase,FLASH_SWINT_NUM);
}

__attribute__((naked)) void do_hal_flash_erase_security_area_swint(uint8_t idx)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_erase_security_area,FLASH_SWINT_NUM);
}

__attribute__((naked)) void do_hal_flash_program_security_area_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_program_security_area,FLASH_SWINT_NUM);
}

__attribute__((naked)) void do_hal_flash_read_security_area_swint(void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flash_read_security_area,FLASH_SWINT_NUM);
}

#endif