#include "hal_flash_int.h"
#include "compile_flag.h"

void _hal_flash_program_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length);
void XIP_BANNED_FUNC(hal_flash_program_security_area,uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
{
    hal_flash_xip_stop();
    _hal_flash_program_security_area(idx,addr,data,length);
    hal_flash_xip_start();
}

void _hal_flash_quad_page_program(uint32_t offset,uint8_t *data,uint16_t length);
void XIP_BANNED_FUNC(hal_flash_quad_page_program,uint32_t offset,uint8_t *data,uint16_t length)
{
    hal_flash_xip_stop();
    _hal_flash_quad_page_program(offset,data,length);
    hal_flash_xip_start();
}

void _hal_flash_dual_io_read(uint32_t offset,uint8_t *data,uint16_t length);
void XIP_BANNED_FUNC(hal_flash_dual_io_read,uint32_t offset,uint8_t *data,uint16_t length)
{
    hal_flash_xip_stop();
    _hal_flash_dual_io_read(offset,data,length);
    hal_flash_xip_start();
}

void _hal_flash_quad_io_read(uint32_t offset, uint8_t * data, uint16_t length);
void XIP_BANNED_FUNC(hal_flash_quad_io_read,uint32_t offset, uint8_t * data, uint16_t length)
{
    hal_flash_xip_stop();
    _hal_flash_quad_io_read(offset,data,length);
    hal_flash_xip_start();
}

void _hal_flash_read_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length);
void XIP_BANNED_FUNC(hal_flash_read_security_area,uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
{
    hal_flash_xip_stop();
    _hal_flash_read_security_area(idx,addr,data,length);
    hal_flash_xip_start();
}

void _hal_flash_chip_erase();
void XIP_BANNED_FUNC(hal_flash_chip_erase)
{
    hal_flash_xip_stop();
    _hal_flash_chip_erase();
    hal_flash_xip_start();
}

void _hal_flash_erase_security_area(uint8_t idx);
void XIP_BANNED_FUNC(hal_flash_erase_security_area,uint8_t idx)
{
    hal_flash_xip_stop();
    _hal_flash_erase_security_area(idx);
    hal_flash_xip_start();
}

void _hal_flash_fast_read(uint32_t offset, uint8_t * data, uint16_t length);
void XIP_BANNED_FUNC(hal_flash_fast_read,uint32_t offset, uint8_t * data, uint16_t length)
{
    hal_flash_xip_stop();
    _hal_flash_fast_read(offset,data,length);
    hal_flash_xip_start();
}

void _hal_flash_read_id(uint8_t jedec_id[3]);
void XIP_BANNED_FUNC(hal_flash_read_id,uint8_t jedec_id[3])
{
    hal_flash_xip_stop();
    _hal_flash_read_id(jedec_id);
    hal_flash_xip_start();
}

void _hal_flash_sector_erase(uint32_t offset);
void XIP_BANNED_FUNC(hal_flash_sector_erase,uint32_t offset)
{
    hal_flash_xip_stop();
    _hal_flash_sector_erase(offset);
    hal_flash_xip_start();
}

void _hal_flash_dual_page_program(uint32_t offset,uint8_t *data,uint16_t length);
void XIP_BANNED_FUNC(hal_flash_dual_page_program,uint32_t offset,uint8_t *data,uint16_t length)
{
    hal_flash_xip_stop();
    _hal_flash_dual_page_program(offset,data,length);
    hal_flash_xip_start();
}

void _hal_flash_read_unique_id(uint8_t unique_serial_id[16]);
void XIP_BANNED_FUNC(hal_flash_read_unique_id,uint8_t unique_serial_id[16])
{
    hal_flash_xip_stop();
    _hal_flash_read_unique_id(unique_serial_id);
    hal_flash_xip_start();
}

void _hal_flash_page_program(uint32_t offset,uint8_t *data,uint16_t length);
void XIP_BANNED_FUNC(hal_flash_page_program,uint32_t offset,uint8_t *data,uint16_t length)
{
    hal_flash_xip_stop();
    _hal_flash_page_program(offset,data,length);
    hal_flash_xip_start();
}

void _hal_flash_erase_operation(uint32_t offset,uint8_t opcode);
void XIP_BANNED_FUNC(hal_flash_page_erase,uint32_t offset)
{
    hal_flash_xip_stop();
    _hal_flash_erase_operation(offset,PAGE_ERASE_OPCODE);
    hal_flash_xip_start();
}
