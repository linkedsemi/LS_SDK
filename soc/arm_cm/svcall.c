#include "hal_flash_int.h"
#include "flash_svcall_int.h"
#include "hal_flash_svcall.h"
#include "compile_flag.h"
typedef uint32_t (*svcall_fn_t)(uint32_t,uint32_t,uint32_t,uint32_t);

ROM_SYMBOL const svcall_fn_t svcall_table[SVCALL_NUM_MAX] = {
    [SVCALL_FLASH_PROGRAM] = (svcall_fn_t)do_hal_flash_program,
    [SVCALL_FLASH_ERASE] = (svcall_fn_t)do_hal_flash_erase,
    [SVCALL_FLASH_READ] = (svcall_fn_t)do_hal_flash_read,
    [SVCALL_FLASH_CHIP_ERASE] = (svcall_fn_t)do_hal_flash_chip_erase,
    [SVCALL_FLASH_ERASE_SECURITY] = (svcall_fn_t)do_hal_flash_erase_security_area,
    [SVCALL_FLASH_PROGRAM_SECURITY] = (svcall_fn_t)do_hal_flash_program_security_area,
    [SVCALL_FLASH_READ_SECURITY] = (svcall_fn_t)do_hal_flash_read_security_area,
    [SVCALL_FLASH_READ_REG] = (svcall_fn_t)do_hal_flash_read_reg,
};

ROM_SYMBOL void SVC_Handler_C(uint32_t *svc_args)
{
    uint8_t svc_num = ((uint8_t *)svc_args[6])[-2];
    if(svc_num<SVCALL_NUM_MAX)
    {
        svc_args[0] = svcall_table[svc_num](svc_args[0],svc_args[1],svc_args[2],svc_args[3]);
    }
}

