#include "hal_flash_svcall.h"
#include "flash_svcall_int.h"
#include "hal_flash_int.h"

#define FLASH_EXECUTE_WITH_RETVAL(return_val,op,...) \
    do{\
        if(GLOBAL_INT_MASK_STATUS())\
        {\
            return_val = op(__VA_ARGS__);\
        }else\
        {\
            return_val = op##_svcall(__VA_ARGS__);\
        }\
    }while(0)

#define FLASH_EXECUTE_NO_RETVAL(op,...) \
    do{\
        if(GLOBAL_INT_MASK_STATUS())\
        {\
            op(__VA_ARGS__);\
        }else\
        {\
            op##_svcall(__VA_ARGS__);\
        }\
    }while(0)

void hal_flash_program_operation(uint32_t offset,uint8_t *data,uint16_t length,uint8_t multi_type)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_program,offset,data,length,multi_type);
}

void hal_flash_erase_operation(uint32_t offset,uint8_t opcode)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_erase,offset,opcode);
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

void hal_flash_program_security_area_operation(uint8_t idx, uint16_t addr, uint8_t * data, uint16_t length)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_program_security_area, idx,addr,data,length);
}

void hal_flash_read_security_area_operation(uint8_t idx, uint16_t addr, uint8_t * data, uint16_t length)
{
    FLASH_EXECUTE_NO_RETVAL(do_hal_flash_read_security_area, idx,addr,data,length);
}

