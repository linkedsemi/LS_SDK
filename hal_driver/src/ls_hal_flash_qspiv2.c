#include "hal_flash_int.h"
#include "ls_hal_qspiv2.h"
#ifdef HAL_FLASH_C_MERGED
#define HAL_FLASH_C_DESTINATION
#include "ls_hal_flash.c"
#endif

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_init)
{
    lsqspiv2_init();
}

static void XIP_BANNED_FUNC(hal_flash_quad_xip_mode_enter,)
{
    uint8_t dummy;
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = QUAD_WIRE;
    cfg.ctrl.hz_cyc = 4;
    cfg.ctrl.mw_cyc = 11;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = QUAD_IO_READ_OPCODE<<24;
    cfg.ca_low = 0x20<<24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)&dummy&0x3;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = &dummy;
    lsqspiv2_stg_read_write(&cfg);
    #ifndef FLASH_PROG_ALGO
    LS_RAM_ASSERT(dummy == DUMMY_BYTE_VAL);
    #endif
}

static void XIP_BANNED_FUNC(hal_flash_quad_xip_mode_exit,)
{
    uint8_t dummy;
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 0;
    cfg.ctrl.sw_en = 0;
    cfg.ctrl.mw_wid = QUAD_WIRE;
    cfg.ctrl.hz_cyc = 4;
    cfg.ctrl.mw_cyc = 11;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = 0;
    cfg.ca_low = 0x0<<24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)&dummy&0x3;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = &dummy;
    lsqspiv2_stg_read_write(&cfg);
    #ifndef FLASH_PROG_ALGO
    LS_RAM_ASSERT(dummy == DUMMY_BYTE_VAL);
    #endif
}

#if DUAL_CONTINUOUS_MODE_OFF
static void XIP_BANNED_FUNC(hal_flash_dual_xip_mode_enter,){}
static void XIP_BANNED_FUNC(hal_flash_dual_xip_mode_exit,){}
#else
static void XIP_BANNED_FUNC(hal_flash_dual_xip_mode_enter,)
{
    uint8_t dummy;
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = DUAL_WIRE;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_cyc = 15;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = DUAL_IO_READ_OPCODE<<24;
    cfg.ca_low = 0x20<<24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)&dummy&0x3;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = &dummy;
    lsqspiv2_stg_read_write(&cfg);
    #ifndef FLASH_PROG_ALGO
    LS_RAM_ASSERT(dummy == DUMMY_BYTE_VAL);
    #endif
}

static void XIP_BANNED_FUNC(hal_flash_dual_xip_mode_exit,)
{
    uint8_t dummy;
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 0;
    cfg.ctrl.sw_en = 0;
    cfg.ctrl.mw_wid = DUAL_WIRE;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_cyc = 15;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = 0;
    cfg.ca_low = 0x0<<24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)&dummy&0x3;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = &dummy;
    lsqspiv2_stg_read_write(&cfg);
    #ifndef FLASH_PROG_ALGO
    LS_RAM_ASSERT(dummy == DUMMY_BYTE_VAL);
    #endif
}
#endif

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_xip_start,)
{
    if(hal_flash_xip_status_get())
    {
        return;
    }
    uint32_t cpu_stat = enter_critical();
    if(hal_flash_dual_mode_get())
    {
        hal_flash_dual_xip_mode_enter();
        lsqspiv2_direct_dual_read_config();
    }else
    {
        hal_flash_quad_xip_mode_enter();
        lsqspiv2_direct_quad_read_config();
    } 
    hal_flash_xip_status_set(true);
    exit_critical(cpu_stat);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_xip_stop,)
{
    if(hal_flash_xip_status_get() == false)
    {
        return;
    }
    uint32_t cpu_stat = enter_critical();
    sync_for_xip_stop();
    if(hal_flash_dual_mode_get())
    {
        hal_flash_dual_xip_mode_exit();
    }else
    {
        hal_flash_quad_xip_mode_exit();
    }
    hal_flash_xip_status_set(false);
    exit_critical(cpu_stat);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_write_enable,)
{
    lsqspiv2_stg_send_command(WRITE_ENABLE_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_read_status_register_0,uint8_t *status_reg_0)
{
    lsqspiv2_stg_read_register(READ_STATUS_REGISTER_0_OPCODE,status_reg_0,sizeof(uint8_t));
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_read_status_register_1,uint8_t *status_reg_1)
{
    lsqspiv2_stg_read_register(READ_STATUS_REGISTER_1_OPCODE,status_reg_1,sizeof(uint8_t));
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_write_status_reg_func,void * param)
{
    lsqspiv2_stg_write_register(WRITE_STATUS_REGISTER_OPCODE,param, sizeof(uint16_t));
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_xip_mode_reset,)
{
    uint8_t data = CONTINUOUS_READ_MODE_RESET;
    lsqspiv2_stg_write_register(CONTINUOUS_READ_MODE_RESET,&data,sizeof(data));
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_prog_func,void *param)
{
    lsqspiv2_stg_read_write(param);
}

ROM_SYMBOL void do_hal_flash_program(uint32_t offset,uint8_t *data,uint16_t length,uint8_t multi_type)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 31;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = multi_type;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_cyc = 0;
    cfg.ctrl.mw_en = 0;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    uint8_t opcode = 0;
    switch(multi_type)
    {
    case SINGLE_WIRE:
        opcode = PAGE_PROGRAM_OPCODE;
    break;
    case DUAL_WIRE:
        opcode = DUAL_PAGE_PROGRAM_OPCODE;
    break;
    case QUAD_WIRE:
        opcode = QUAD_PAGE_PROGRAM_OPCODE;
    break;
    }
    cfg.ca_high = opcode << 24 | offset;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_bytes = length - 1;
    cfg.dat_ctrl.dat_dir = WRITE_TO_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = data;
    flash_writing_critical(do_hal_flash_prog_func,&cfg);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_erase_func,void *param)
{
    struct flash_erase_param *erase_param = param;
    lsqspiv2_stg_write_register(erase_param->opcode, erase_param->addr, 3);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_chip_erase_func,void *param)
{
    lsqspiv2_stg_send_command(CHIP_ERASE_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_read_func,void *param)
{
    lsqspiv2_stg_read_write(param);
}

static void hal_flash_read_loop(struct lsqspiv2_stg_cfg *cfg,uint8_t opcode,uint32_t offset,uint16_t length)
{
    while(length)
    {
        cfg->ca_high = opcode << 24 | offset;
        if(length>4096)
        {
            cfg->dat_ctrl.dat_bytes = 4095;
            length -= 4096;
            offset += 4096;
        }else{
            cfg->dat_ctrl.dat_bytes = length - 1;
            length = 0;
        }
        hal_flash_read_operation(cfg);
        cfg->data += 4096;
    }
}

ROM_SYMBOL void hal_flash_quad_io_read(uint32_t offset, uint8_t * data, uint16_t length)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = QUAD_WIRE;
    cfg.ctrl.hz_cyc = 4;
    cfg.ctrl.mw_cyc = 11;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_low = 0<<24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.data = data;
    hal_flash_read_loop(&cfg,QUAD_IO_READ_OPCODE,offset,length);
}

ROM_SYMBOL void hal_flash_dual_io_read(uint32_t offset,uint8_t *data,uint16_t length)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = DUAL_WIRE;
    cfg.ctrl.hz_cyc = 1;
    cfg.ctrl.mw_cyc = 15;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_low = 0<<24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.data = data;
    hal_flash_read_loop(&cfg,DUAL_IO_READ_OPCODE,offset,length);
}

ROM_SYMBOL void hal_flash_read_24bit_addr_8bit_dummy(uint32_t offset, uint8_t * data, uint16_t length,uint8_t opcode)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 39;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.hz_cyc = 8;
    cfg.ctrl.mw_wid = SINGLE_WIRE;
    cfg.ctrl.mw_cyc = 0;
    cfg.ctrl.mw_en = 0;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_low = 0<<24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.data = data;
    hal_flash_read_loop(&cfg,opcode,offset,length);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_deep_power_down,)
{
    lsqspiv2_stg_send_command( DEEP_POWER_DOWN_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_release_from_deep_power_down,)
{
    lsqspiv2_stg_send_command(RELEASE_FROM_DEEP_POWER_DOWN_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_read_reg_func,void *param)
{
    struct flash_read_reg_param *ptr = param;
    lsqspiv2_stg_read_register(ptr->opcode,ptr->buf,ptr->length);
}

ROM_SYMBOL void hal_flash_read_unique_id(uint8_t unique_serial_id[16])
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 39;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.hz_cyc = 8;
    cfg.ctrl.mw_wid = SINGLE_WIRE;
    cfg.ctrl.mw_cyc = 0;
    cfg.ctrl.mw_en = 0;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = READ_UNIQUE_ID_OPCODE<<24;
    cfg.ca_low = 0<<24;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)unique_serial_id&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.dat_ctrl.dat_bytes = 15;
    cfg.data = unique_serial_id;
    hal_flash_read_operation(&cfg);
}


ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_erase_security_area_func,void *param)
{
    lsqspiv2_stg_write_register(ERASE_SECURITY_AREA_OPCODE,param,3);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_program_security_area_func,void *param)
{
    lsqspiv2_stg_read_write( param);
}

ROM_SYMBOL void do_hal_flash_program_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 31;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = SINGLE_WIRE;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_cyc = 0;
    cfg.ctrl.mw_en = 0;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = PROGRAM_SECURITY_AREA_OPCODE << 24 | idx<<12 | addr;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_bytes = length - 1;
    cfg.dat_ctrl.dat_dir = WRITE_TO_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = data;
    flash_writing_critical(do_hal_flash_program_security_area_func, &cfg);
}


ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flash_read_security_area_func,void *param)
{
    lsqspiv2_stg_read_write( param);
}

ROM_SYMBOL void do_hal_flash_read_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 39;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = SINGLE_WIRE;
    cfg.ctrl.hz_cyc = 8;
    cfg.ctrl.mw_cyc = 0;
    cfg.ctrl.mw_en = 0;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = READ_SECURITY_AREA_OPCODE << 24 | idx<<12 | addr;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_bytes = length - 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = data;
    flash_reading_critical(do_hal_flash_read_security_area_func,&cfg);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_software_reset)
{
    lsqspiv2_stg_send_command(RESET_EN_OPCODE);
    lsqspiv2_stg_send_command(RESET_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_prog_erase_suspend)
{
    lsqspiv2_stg_send_command(PROG_ERASE_SUSPEND);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flash_prog_erase_resume)
{
    lsqspiv2_stg_send_command(PROG_ERASE_RESUME);
}
