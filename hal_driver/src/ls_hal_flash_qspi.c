#include "hal_flash_int.h"
#include "ls_hal_qspi.h"
#ifdef HAL_FLASH_C_MERGED
#define HAL_FLASH_C_DESTINATION
#include "ls_hal_flash.c"
#endif

void XIP_BANNED_FUNC(hal_flash_init,)
{
    lsqspi_init();
}

static void XIP_BANNED_FUNC(quad_io_read_dummy,uint8_t opcode_en,uint8_t mode_bits)
{
    uint8_t dummy;
    struct lsqspi_stig_rd_wr_param param;
    param.start.data = &dummy;
    param.start.opcode = QUAD_IO_READ_OPCODE;
    param.start.addr = 0;
    param.start.dummy_bytes = 1;
    param.start.dummy_bytes_en = 1;
    param.start.addr_en = 1;
    param.start.quad_addr = 1;
    param.start.mode_bits_en = 1;
    param.start.opcode_en = opcode_en;
    param.size = sizeof(dummy);
    param.mode_bits = mode_bits;
    param.quad_data = true;
    lsqspi_stig_read_data(&param);
    #ifndef FLASH_PROG_ALGO
    LS_RAM_ASSERT(dummy == DUMMY_BYTE_VAL);
    #endif
}

void XIP_BANNED_FUNC(hal_flash_xip_start,)
{
    if(hal_flash_xip_status_get())
    {
        return;
    }
    uint32_t cpu_stat = enter_critical();
    quad_io_read_dummy(1,XIP_MODE_BITS);
    struct lsqspi_direct_read_config_param direct_read_param; //do not initialize this variable with a const struct
    direct_read_param.opcode = QUAD_IO_READ_OPCODE;
    direct_read_param.dummy_bytes = 2;
    direct_read_param.quad_addr = 1;
    direct_read_param.quad_data = 1;
    direct_read_param.mode_bits_en = 1;
    direct_read_param.mode_bits = XIP_MODE_BITS;
    lsqspi_direct_read_config(&direct_read_param);
    hal_flash_xip_status_set(true);
    exit_critical(cpu_stat);
}


void XIP_BANNED_FUNC(hal_flash_xip_stop,)
{
    if(hal_flash_xip_status_get() == false)
    {
        return;
    }
    uint32_t cpu_stat = enter_critical();
    quad_io_read_dummy(0,0);
    hal_flash_xip_status_set(false);
    exit_critical(cpu_stat);
}

void XIP_BANNED_FUNC(hal_flash_write_enable,)
{
    lsqspi_stig_send_command(WRITE_ENABLE_OPCODE);
}

void XIP_BANNED_FUNC(hal_flash_read_status_register_0,uint8_t *status_reg_0)
{
    lsqspi_stig_read_register(READ_STATUS_REGISTER_0_OPCODE,status_reg_0,sizeof(uint8_t));
}

void XIP_BANNED_FUNC(hal_flash_read_status_register_1,uint8_t *status_reg_1)
{
    lsqspi_stig_read_register(READ_STATUS_REGISTER_1_OPCODE,status_reg_1,sizeof(uint8_t));
}

void XIP_BANNED_FUNC(do_hal_flash_write_status_reg_func,void * param)
{
    lsqspi_stig_write_register(WRITE_STATUS_REGISTER_OPCODE,param, sizeof(uint16_t));
}

void XIP_BANNED_FUNC(do_hal_flash_prog_func,void *param)
{
    lsqspi_stig_write_data( param);
}

void do_hal_flash_program(uint32_t offset,uint8_t *data,uint16_t length,uint8_t multi_type)
{
    struct lsqspi_stig_rd_wr_param param;
    param.start.data = data;
    param.start.opcode = multi_type == QUAD_WIRE ? QUAD_PAGE_PROGRAM_OPCODE : PAGE_PROGRAM_OPCODE;
    param.start.addr = offset;
    param.start.dummy_bytes_en = 0;
    param.start.addr_en = 1;
    param.start.quad_addr = 0;
    param.start.mode_bits_en = 0;
    param.start.opcode_en = 1;
    param.size = length;
    param.quad_data = multi_type == QUAD_WIRE;
    flash_writing_critical(do_hal_flash_prog_func,&param);
}

void XIP_BANNED_FUNC(do_hal_flash_erase_func,void *param)
{
    struct flash_erase_param *erase_param = param;
    lsqspi_stig_write_register(erase_param->opcode, erase_param->addr, 3);
}

void XIP_BANNED_FUNC(do_hal_flash_chip_erase_func,void *param)
{
    lsqspi_stig_send_command(CHIP_ERASE_OPCODE);
}

void XIP_BANNED_FUNC(do_hal_flash_read_func,void *param)
{
    lsqspi_stig_read_data(param);
}

void hal_flash_quad_io_read(uint32_t offset, uint8_t * data, uint16_t length)
{
    struct lsqspi_stig_rd_wr_param param;
    param.start.data = data;
    param.start.opcode = QUAD_IO_READ_OPCODE;
    param.start.addr = offset;
    param.start.dummy_bytes = 1;
    param.start.dummy_bytes_en = 1;
    param.start.addr_en = 1;
    param.start.quad_addr = 1;
    param.start.mode_bits_en = 1;
    param.start.opcode_en = 1;
    param.size = length;
    param.mode_bits = 0;
    param.quad_data = 1;
    hal_flash_read_operation(&param);
}

void hal_flash_read_24bit_addr_8bit_dummy(uint32_t offset, uint8_t * data, uint16_t length,uint8_t opcode)
{
    struct lsqspi_stig_rd_wr_param param;
    param.start.data = data;
    param.start.opcode = opcode;
    param.start.addr = offset;
    param.start.dummy_bytes = 0;
    param.start.dummy_bytes_en = 1;
    param.start.addr_en = 1;
    param.start.quad_addr = 0;
    param.start.mode_bits_en = 0;
    param.start.opcode_en = 1;
    param.size = length;
    param.quad_data = 0;
    hal_flash_read_operation(&param);
}


void XIP_BANNED_FUNC(hal_flash_deep_power_down,)
{
    lsqspi_stig_send_command( DEEP_POWER_DOWN_OPCODE);
}

void XIP_BANNED_FUNC(hal_flash_release_from_deep_power_down,)
{
    lsqspi_stig_send_command(RELEASE_FROM_DEEP_POWER_DOWN_OPCODE);
}

void XIP_BANNED_FUNC(do_hal_flash_read_reg_func,void *param)
{
    struct flash_read_reg_param *ptr = param;
    lsqspi_stig_read_register(ptr->opcode,ptr->buf,ptr->length);
}

void hal_flash_read_unique_id(uint8_t unique_serial_id[16])
{
    struct lsqspi_stig_rd_wr_param param;
    param.start.data = unique_serial_id;
    param.start.opcode = READ_UNIQUE_ID_OPCODE;
    param.start.addr = 0;
    param.start.dummy_bytes = 0;
    param.start.dummy_bytes_en = 1;
    param.start.addr_en = 1;
    param.start.quad_addr = 0;
    param.start.mode_bits_en = 0;
    param.start.opcode_en = 1;
    param.size = 16;
    param.quad_data = false;
    hal_flash_read_operation(&param);
}


void XIP_BANNED_FUNC(do_hal_flash_erase_security_area_func,void *param)
{
    lsqspi_stig_write_register(ERASE_SECURITY_AREA_OPCODE,param,3);
}

void XIP_BANNED_FUNC(do_hal_flash_program_security_area_func,void *param)
{
    lsqspi_stig_write_data( param);
}

void do_hal_flash_program_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
{
    struct lsqspi_stig_rd_wr_param param;
    param.start.data = data;
    param.start.opcode = PROGRAM_SECURITY_AREA_OPCODE;
    param.start.addr = idx<<12 | (addr&0x1ff);
    param.start.dummy_bytes_en = 0;
    param.start.addr_en = 1;
    param.start.quad_addr = 0;
    param.start.mode_bits_en = 0;
    param.start.opcode_en = 1;
    param.size = length;
    param.quad_data = false;
    flash_writing_critical(do_hal_flash_program_security_area_func, &param);
}


void XIP_BANNED_FUNC(do_hal_flash_read_security_area_func,void *param)
{
    lsqspi_stig_read_data( param);
}

void do_hal_flash_read_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
{
    struct lsqspi_stig_rd_wr_param param;
    param.start.data = data;
    param.start.opcode = READ_SECURITY_AREA_OPCODE;
    param.start.addr = idx<<12 | (addr&0x1ff);
    param.start.dummy_bytes = 0;
    param.start.dummy_bytes_en = 1;
    param.start.addr_en = 1;
    param.start.quad_addr = 0;
    param.start.mode_bits_en = 0;
    param.start.opcode_en = 1;
    param.size = length;
    param.quad_data = false;
    flash_reading_critical(do_hal_flash_read_security_area_func,&param);
}


void XIP_BANNED_FUNC(hal_flash_software_reset,)
{
    lsqspi_stig_send_command(RESET_EN_OPCODE);
    lsqspi_stig_send_command(RESET_OPCODE);
}

void XIP_BANNED_FUNC(hal_flash_prog_erase_suspend,)
{
    lsqspi_stig_send_command(PROG_ERASE_SUSPEND);
}


void XIP_BANNED_FUNC(hal_flash_prog_erase_resume,)
{
    lsqspi_stig_send_command(PROG_ERASE_RESUME);
}

__attribute__((weak)) void hal_flash_dual_io_read(uint32_t offset,uint8_t *data,uint16_t length){}

void XIP_BANNED_FUNC(hal_flash_xip_mode_reset,)
{
    uint8_t data = CONTINUOUS_READ_MODE_RESET;
    lsqspi_stig_write_register(CONTINUOUS_READ_MODE_RESET,&data,sizeof(data));
}
