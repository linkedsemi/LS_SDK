#include "spi_flash_int.h"
#include "flash_svcall_int.h"
#if !defined(SPI_FLASH_C_MERGED) || defined(SPI_FLASH_C_DESTINATION)
struct spi_flash_status
{
    bool writing;
    bool xip;
}flash_stat;

bool flash_dual_mode_only;

void spi_flash_dual_mode_set(bool dual)
{
    flash_dual_mode_only= dual;
}

XIP_BANNED bool spi_flash_dual_mode_get()
{
    return flash_dual_mode_only;
}

XIP_BANNED void spi_flash_xip_status_set(bool xip)
{
    flash_stat.xip = xip;
}

XIP_BANNED void spi_flash_writing_status_set(bool writing)
{
    flash_stat.writing = writing;
}

XIP_BANNED void spi_flash_drv_var_init(bool xip,bool writing)
{
    spi_flash_xip_status_set(xip);
    spi_flash_writing_status_set(writing);
}

XIP_BANNED bool spi_flash_write_in_process()
{
    uint8_t status_reg_0;
    spi_flash_read_status_register_0(&status_reg_0);
    return status_reg_0 & 0x1 ? true : false;
}

XIP_BANNED static void spi_flash_write_status_check()
{
    while(spi_flash_write_in_process());
}

#if ROM_CODE == 1
void flash_reading_critical(void (*func)(void *),void *param)
{
    func(param);
}

void flash_writing_critical(void (*func)(void *),void *param)
{
    uint32_t cpu_stat = enter_critical();
    spi_flash_write_enable();
    func(param);
    flash_stat.writing = true;
    exit_critical(cpu_stat);
    spi_flash_write_status_check();
    flash_stat.writing = false;
}
#else
NOINLINE XIP_BANNED void flash_reading_critical(void (*func)(void *),void *param)
{
    spi_flash_xip_stop();
    func(param);
    spi_flash_xip_start();
}

#if SUSPEND_WORKAROUND == PUYA_FLASH_WORKAROUND
#include "systick.h"
XIP_BANNED void flash_writing_critical(void (*func)(void *),void *param)
{
    if(GLOBAL_INT_MASK_STATUS())
    {
        spi_flash_xip_stop();
        spi_flash_write_enable();
        func(param);
        spi_flash_write_status_check();
        spi_flash_xip_start();
    }else
    {
        uint32_t cpu_stat = enter_critical();
        spi_flash_xip_stop();
        spi_flash_write_enable();
        func(param);
        uint32_t writing_end_time = systick_get_value();
        DELAY_US(500);
        flash_stat.writing = true;
        exit_critical(cpu_stat);
        systick_poll_timeout(writing_end_time,func == do_spi_flash_prog_func ? SYSTICK_MS2TICKS(1):SYSTICK_MS2TICKS(7),NULL);
        cpu_stat = enter_critical();
        spi_flash_write_status_check();
        exit_critical(cpu_stat);
        flash_stat.writing = false;
        spi_flash_xip_start();
    }
}

#elif SUSPEND_WORKAROUND == TSINGTENG_FLASH_WORKAROUND

XIP_BANNED void flash_writing_critical(void (*func)(void *),void *param)
{
    uint32_t cpu_stat = enter_critical();
    spi_flash_xip_stop();
    spi_flash_write_enable();
    func(param);
    spi_flash_write_status_check();
    spi_flash_xip_start();
    exit_critical(cpu_stat);
}

#elif SUSPEND_WORKAROUND == 0
XIP_BANNED void flash_writing_critical(void (*func)(void *),void *param)
{
    uint32_t cpu_stat = enter_critical();
    spi_flash_xip_stop();
    spi_flash_write_enable();
    func(param);
    flash_stat.writing = true;
    exit_critical(cpu_stat);
    spi_flash_write_status_check();
    flash_stat.writing = false;
    spi_flash_xip_start();
}
#endif

#endif

XIP_BANNED void spi_flash_write_status_register(uint16_t status)
{
    flash_writing_critical(do_spi_flash_write_status_reg_func,&status);
}

void spi_flash_multi_io_read(uint32_t offset,uint8_t *data,uint16_t length)
{
    if(spi_flash_dual_mode_get())
    {
        spi_flash_dual_io_read(offset,data,length);
    }else
    {
        spi_flash_quad_io_read(offset,data,length);
    }
}

void spi_flash_multi_io_page_program(uint32_t offset,uint8_t *data,uint16_t length)
{
    if(spi_flash_dual_mode_get())
    {
        spi_flash_dual_page_program(offset,data,length);
    }else
    {
        spi_flash_quad_page_program(offset,data,length);
    }
}

void spi_flash_quad_page_program(uint32_t offset,uint8_t *data,uint16_t length)
{
    spi_flash_program_operation(offset,data,length,QUAD_WIRE);
}

void spi_flash_dual_page_program(uint32_t offset,uint8_t *data,uint16_t length)
{
    spi_flash_program_operation(offset,data,length,DUAL_WIRE);
}

void spi_flash_page_program(uint32_t offset,uint8_t *data,uint16_t length)
{
    spi_flash_program_operation(offset,data,length,SINGLE_WIRE);
}

void do_spi_flash_erase(uint32_t offset,uint8_t opcode)
{
    struct flash_erase_param param;
    param.addr[0] = offset>>16&0xff;
    param.addr[1] = offset>>8&0xff;
    param.addr[2] = offset&0xff;
    param.opcode = opcode;
    flash_writing_critical(do_spi_flash_erase_func,&param);
}

void spi_flash_page_erase(uint32_t offset)
{
    spi_flash_erase_operation(offset,PAGE_ERASE_OPCODE);
}

void spi_flash_sector_erase(uint32_t offset)
{
    spi_flash_erase_operation(offset,SECTOR_ERASE_OPCODE);
}

void do_spi_flash_chip_erase()
{
    flash_writing_critical(do_spi_flash_chip_erase_func,NULL);
}

void spi_flash_chip_erase()
{
    spi_flash_chip_erase_operation();
}

void do_spi_flash_read(void *param)
{
    flash_reading_critical(do_spi_flash_read_func,param);
}

void do_spi_flash_read_reg(void *param)
{
    flash_reading_critical(do_spi_flash_read_reg_func,param);
}

void spi_flash_read_id(uint8_t jedec_id[3])
{
    struct flash_read_reg_param param;
    param.buf = jedec_id;
    param.opcode = READ_IDENTIFICATION_OPCODE;
    param.length = 3;
    spi_flash_read_reg_operation(&param);
}

void do_spi_flash_erase_security_area(uint8_t idx)
{
    uint8_t buf[3];
    buf[0] = 0;
    buf[1] = idx<<4;
    buf[2] = 0;
    flash_writing_critical(do_spi_flash_erase_security_area_func,buf);
}

void spi_flash_erase_security_area(uint8_t idx)
{
    spi_flash_erase_security_area_operation(idx);
}

void spi_flash_program_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
{
    spi_flash_program_security_area_operation(idx, addr,data,length);
}

void spi_flash_read_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
{
    spi_flash_read_security_area_operation(idx, addr,data,length);
}

XIP_BANNED void spi_flash_qe_status_read_and_set()
{
    uint8_t status_reg[2];
    spi_flash_read_status_register_1(&status_reg[1]);
    if((status_reg[1]&0x02) == 0)
    {
        spi_flash_read_status_register_0(&status_reg[0]);
        spi_flash_write_status_register(status_reg[1]<<8|status_reg[0]|0x200);
    }
}

XIP_BANNED bool spi_flash_writing_busy()
{
    return flash_stat.writing;
}

XIP_BANNED bool spi_flash_xip_status_get()
{
    return flash_stat.xip;
}

uint32_t spi_flash_total_size_get(void)
{
    uint8_t jedec_id[3];
    spi_flash_read_id(jedec_id);
    uint8_t capacity_id = jedec_id[2];
    return 1<<capacity_id;
}

ROM_SYMBOL void spi_flash_fast_read(uint32_t offset, uint8_t * data, uint16_t length)
{
    spi_flash_read_24bit_addr_8bit_dummy(offset,data,length,FAST_READ_OPCODE);
}

ROM_SYMBOL void spi_flash_read_sfdp(uint32_t offset,uint8_t *data, uint16_t length)
{
    spi_flash_read_24bit_addr_8bit_dummy(offset,data,length,READ_SFDP_OPCODE);
}

#endif
