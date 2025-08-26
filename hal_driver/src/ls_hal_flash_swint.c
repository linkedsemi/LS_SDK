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

void FLASH_API_SECTION(hal_flashx_program_operation,struct hal_flash_env *env,void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flashx_program,env,param);
}

void FLASH_API_SECTION(hal_flashx_write_reg_operation,struct hal_flash_env *env,void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flashx_write_reg,env,param);
}

void FLASH_API_SECTION(hal_flashx_read_operation,struct hal_flash_env *env,void*param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flashx_read,env,param);
}

void FLASH_API_SECTION(hal_flashx_read_reg_operation,struct hal_flash_env *env,void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flashx_read_reg,env,param);
}

void FLASH_API_SECTION(hal_flashx_chip_erase_operation,struct hal_flash_env *env,void *param)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flashx_chip_erase,env,param);
}

#ifndef __CC_ARM
NOINLINE void FLASH_API_SECTION(do_hal_flashx_program_swint,struct hal_flash_env *env,void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flashx_program,FLASH_SWINT_NUM);
}

NOINLINE void FLASH_API_SECTION(do_hal_flashx_write_reg_swint,struct hal_flash_env *env,void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flashx_write_reg,FLASH_SWINT_NUM);
}

NOINLINE void FLASH_API_SECTION(do_hal_flashx_read_swint,struct hal_flash_env *env,void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flashx_read,FLASH_SWINT_NUM);
}

NOINLINE void FLASH_API_SECTION(do_hal_flashx_read_reg_swint,struct hal_flash_env *env,void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flashx_read_reg,FLASH_SWINT_NUM);
}

NOINLINE void FLASH_API_SECTION(do_hal_flashx_chip_erase_swint,struct hal_flash_env *env,void *param)
{
    SWINT_FUNC_CALL_INLINE_ASM(do_hal_flashx_chip_erase,FLASH_SWINT_NUM);
}

#endif