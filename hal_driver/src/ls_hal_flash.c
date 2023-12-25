#include "hal_flash_int.h"
#if !defined(HAL_FLASH_C_MERGED) || defined(HAL_FLASH_C_DESTINATION)
ROM_SYMBOL struct hal_flash_status
{
    bool writing;
    bool xip;
}flash_stat;

ROM_SYMBOL bool flash_dual_mode_only;

ROM_SYMBOL void (*hal_flash_xip_stop_fn)();
ROM_SYMBOL void (*hal_flash_xip_start_fn)();

static void xip_dummy(){}

ROM_SYMBOL void hal_flash_xip_func_ptr_dummy()
{
    hal_flash_xip_start_fn = xip_dummy;
    hal_flash_xip_stop_fn = xip_dummy;
}

ROM_SYMBOL void hal_flash_xip_func_ptr_init()
{
    hal_flash_xip_start_fn = hal_flash_xip_start;
    hal_flash_xip_stop_fn = hal_flash_xip_stop;
}

ROM_SYMBOL void hal_flash_dual_mode_set(bool dual)
{
    flash_dual_mode_only= dual;
}

ROM_SYMBOL bool XIP_BANNED_FUNC(hal_flash_dual_mode_get,)
{
    return flash_dual_mode_only;
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_xip_status_set,bool xip)
{
    flash_stat.xip = xip;
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_writing_status_set,bool writing)
{
    flash_stat.writing = writing;
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_drv_var_init,bool xip,bool writing)
{
    hal_flash_xip_status_set(xip);
    hal_flash_writing_status_set(writing);
}

ROM_SYMBOL bool XIP_BANNED_FUNC(hal_flash_write_in_process,)
{
    uint8_t status_reg_0;
    hal_flash_read_status_register_0_ram(&status_reg_0);
    return status_reg_0 & 0x1 ? true : false;
}

static void XIP_BANNED_FUNC(hal_flash_write_status_check,)
{
    while(hal_flash_write_in_process());
}

#if ROM_CODE == 1
void flash_reading_critical(void (*func)(void *),void *param)
{
    hal_flash_xip_stop_fn();
    func(param);
    hal_flash_xip_start_fn();
}

void flash_writing_critical(void (*func)(void *),void *param)
{
    uint32_t cpu_stat = ENTER_CRITICAL();
    hal_flash_xip_stop_fn();
    hal_flash_write_enable();
    func(param);
    flash_stat.writing = true;
    EXIT_CRITICAL(cpu_stat);
    hal_flash_write_status_check();
    flash_stat.writing = false;
    hal_flash_xip_start_fn();
}
#else
NOINLINE ROM_SYMBOL void XIP_BANNED_FUNC(flash_reading_critical,void (*func)(void *),void *param)
{
    hal_flash_xip_stop();
    func(param);
    hal_flash_xip_start();
}

#if SUSPEND_WORKAROUND == PUYA_FLASH_WORKAROUND
#include "systick.h"
extern bool flash_55nm;
ROM_SYMBOL void XIP_BANNED_FUNC(flash_writing_critical,void (*func)(void *),void *param)
{
    if(flash_55nm){
        if(GLOBAL_INT_MASK_STATUS())
        {
            hal_flash_xip_stop();
            hal_flash_write_enable();
            func(param);
            hal_flash_write_status_check();
            hal_flash_xip_start();
        }else
        {
            uint32_t cpu_stat = ENTER_CRITICAL();
            hal_flash_xip_stop();
            hal_flash_write_enable();
            func(param);
            uint32_t writing_end_time = systick_get_value();
            DELAY_US(500);
            flash_stat.writing = true;
            EXIT_CRITICAL(cpu_stat);
            systick_poll_timeout(writing_end_time,func == do_hal_flash_prog_func ? SYSTICK_MS2TICKS(1):SYSTICK_MS2TICKS(7),NULL);
            cpu_stat = ENTER_CRITICAL();
            hal_flash_write_status_check();
            EXIT_CRITICAL(cpu_stat);
            flash_stat.writing = false;
            hal_flash_xip_start();
        }
    }else
    {
        uint32_t cpu_stat = ENTER_CRITICAL();
        hal_flash_xip_stop();
        hal_flash_write_enable();
        func(param);
        flash_stat.writing = true;
        EXIT_CRITICAL(cpu_stat);
        hal_flash_write_status_check();
        flash_stat.writing = false;
        hal_flash_xip_start();
    }

}

#elif SUSPEND_WORKAROUND == TSINGTENG_FLASH_WORKAROUND

ROM_SYMBOL void XIP_BANNED_FUNC(flash_writing_critical,void (*func)(void *),void *param)
{
    uint32_t cpu_stat = ENTER_CRITICAL();
    hal_flash_xip_stop();
    hal_flash_write_enable();
    func(param);
    hal_flash_write_status_check();
    hal_flash_xip_start();
    EXIT_CRITICAL(cpu_stat);
}

#elif SUSPEND_WORKAROUND == 0
ROM_SYMBOL void XIP_BANNED_FUNC(flash_writing_critical,void (*func)(void *),void *param)
{
    uint32_t cpu_stat = ENTER_CRITICAL();
    hal_flash_xip_stop();
    hal_flash_write_enable();
    func(param);
    flash_stat.writing = true;
    EXIT_CRITICAL(cpu_stat);
    hal_flash_write_status_check();
    flash_stat.writing = false;
    hal_flash_xip_start();
}
#endif

#endif

ROM_SYMBOL void hal_flash_multi_io_read(uint32_t offset,uint8_t *data,uint16_t length)
{
    if(hal_flash_dual_mode_get())
    {
        hal_flash_dual_io_read(offset,data,length);
    }else
    {
        hal_flash_quad_io_read(offset,data,length);
    }
}

ROM_SYMBOL void do_hal_flash_program(void *param)
{
    flash_writing_critical(do_hal_flash_prog_func,param);
}

ROM_SYMBOL void hal_flash_multi_io_page_program(uint32_t offset,uint8_t *data,uint16_t length)
{
    if(hal_flash_dual_mode_get())
    {
        hal_flash_dual_page_program(offset,data,length);
    }else
    {
        hal_flash_quad_page_program(offset,data,length);
    }
}

ROM_SYMBOL void do_hal_flash_write_reg(void *param)
{
    flash_writing_critical(do_hal_flash_write_reg_func,param);
}

ROM_SYMBOL void do_hal_flash_chip_erase(void *param)
{
    flash_writing_critical(do_hal_flash_chip_erase_func,param);
}

ROM_SYMBOL void hal_flash_chip_erase()
{
    hal_flash_chip_erase_operation(NULL);
}

ROM_SYMBOL void hal_flash_write_status_register(uint16_t status)
{
    struct flash_wr_rd_reg_param param = {
        .buf = (uint8_t *)&status,
        .length = sizeof(status),
        .opcode = WRITE_STATUS_REGISTER_OPCODE,
    };
    hal_flash_write_reg_operation(&param);
}

ROM_SYMBOL void hal_flash_page_erase(uint32_t offset)
{
    uint8_t addr[3] = {offset>>16&0xff,offset>>8&0xff,offset&0xff};
    struct flash_wr_rd_reg_param param = {
        .buf = addr,
        .length = sizeof(addr),
        .opcode = PAGE_ERASE_OPCODE,
    };
    hal_flash_write_reg_operation(&param);
}

ROM_SYMBOL void hal_flash_sector_erase(uint32_t offset)
{
    uint8_t addr[3] = {offset>>16&0xff,offset>>8&0xff,offset&0xff};
    struct flash_wr_rd_reg_param param = {
        .buf = addr,
        .length = sizeof(addr),
        .opcode = SECTOR_ERASE_OPCODE,
    };
    hal_flash_write_reg_operation(&param);
}

ROM_SYMBOL void do_hal_flash_read(void *param)
{
    flash_reading_critical(do_hal_flash_read_func,param);
}

ROM_SYMBOL void do_hal_flash_read_reg(void *param)
{
    flash_reading_critical(do_hal_flash_read_reg_func,param);
}

ROM_SYMBOL void hal_flash_read_id(uint8_t jedec_id[3])
{
    struct flash_wr_rd_reg_param param;
    param.buf = jedec_id;
    param.opcode = READ_IDENTIFICATION_OPCODE;
    param.length = 3;
    hal_flash_read_reg_operation(&param);
}

static void hal_flash_read_status_register_1_byte(uint8_t *buf,uint8_t opcode)
{
    struct flash_wr_rd_reg_param param;
    param.buf = buf;
    param.opcode = opcode;
    param.length = 1;
    hal_flash_read_reg_operation(&param);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_read_status_register_0,uint8_t *status_reg_0)
{
    hal_flash_read_status_register_1_byte(status_reg_0,READ_STATUS_REGISTER_0_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_read_status_register_1,uint8_t *status_reg_1)
{
    hal_flash_read_status_register_1_byte(status_reg_1,READ_STATUS_REGISTER_1_OPCODE);
}

static void XIP_BANNED_FUNC(hal_flash_read_status_register_1_byte_ram,uint8_t *buf,uint8_t opcode)
{
    struct flash_wr_rd_reg_param param;
    param.buf = buf;
    param.opcode = opcode;
    param.length = 1;
    do_hal_flash_read_reg_func(&param);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_read_status_register_0_ram,uint8_t *status_reg_0)
{
    hal_flash_read_status_register_1_byte_ram(status_reg_0,READ_STATUS_REGISTER_0_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_read_status_register_1_ram,uint8_t *status_reg_1)
{
    hal_flash_read_status_register_1_byte_ram(status_reg_1,READ_STATUS_REGISTER_1_OPCODE);
}

ROM_SYMBOL void hal_flash_erase_security_area(uint8_t idx)
{
    uint8_t addr[3] = {0,idx<<4,0};
    struct flash_wr_rd_reg_param param = {
        .buf = addr,
        .length = sizeof(addr),
        .opcode = ERASE_SECURITY_AREA_OPCODE,
    };
    hal_flash_write_reg_operation(&param);
}

ROM_SYMBOL void hal_flash_qe_status_read_and_set()
{
    uint8_t status_reg[2];
    hal_flash_read_status_register_1_ram(&status_reg[1]);
    if((status_reg[1]&0x02) == 0)
    {
        hal_flash_read_status_register_0_ram(&status_reg[0]);
        hal_flash_write_status_register(status_reg[1]<<8|status_reg[0]|0x200);
    }
}

ROM_SYMBOL bool XIP_BANNED_FUNC(hal_flash_writing_busy,)
{
    return flash_stat.writing;
}

ROM_SYMBOL bool XIP_BANNED_FUNC(hal_flash_xip_status_get,)
{
    return flash_stat.xip;
}

ROM_SYMBOL uint32_t hal_flash_total_size_get(void)
{
    uint8_t jedec_id[3];
    hal_flash_read_id(jedec_id);
    uint8_t capacity_id = jedec_id[2];
    return 1<<capacity_id;
}

ROM_SYMBOL void hal_flash_fast_read(uint32_t offset, uint8_t * data, uint16_t length)
{
    hal_flash_read_24bit_addr_8bit_dummy(offset,data,length,FAST_READ_OPCODE);
}

ROM_SYMBOL void hal_flash_read_sfdp(uint32_t offset,uint8_t *data, uint16_t length)
{
    hal_flash_read_24bit_addr_8bit_dummy(offset,data,length,READ_SFDP_OPCODE);
}

#endif
