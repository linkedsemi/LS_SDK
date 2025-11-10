#include "hal_flash_int.h"
#include "ls_hal_qspiv2.h"
#ifdef HAL_FLASH_C_MERGED
#define HAL_FLASH_C_DESTINATION
#include "ls_hal_flash.c"
#endif

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_init,struct hal_flash_env *env)
{
    lsqspiv2_init(env->reg);
    if(env->dual_mode_only)
    {
        lsqspiv2_direct_dual_read_config(env->reg,env->continuous_mode_enable);
    }else
    {
        lsqspiv2_direct_quad_read_config(env->reg,env->continuous_mode_enable);
    }
}

bool hal_flashx_inited(struct hal_flash_env *env)
{
    return lsqspiv2_direct_read_mode(env->reg);
}

static void XIP_BANNED_FUNC(hal_flashx_quad_continuous_mode_enter,reg_lsqspiv2_t *reg,bool addr4b)
{
    uint8_t dummy;
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = QUAD_WIRE;
    cfg.ctrl.hz_cyc = 4;
    cfg.ctrl.mw_cyc = addr4b?13:11;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = (addr4b?QUAD_IO_READ4B_OPCODE:QUAD_IO_READ_OPCODE)<<24;
    cfg.ca_low = XIP_MODE_BITS<<(addr4b?16:24);
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)&dummy&0x3;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = &dummy;
    lsqspiv2_stg_read_write(reg,&cfg);
}

static void XIP_BANNED_FUNC(hal_flashx_quad_continuous_mode_exit,reg_lsqspiv2_t *reg,bool addr4b)
{
    uint8_t dummy;
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 0;
    cfg.ctrl.sw_en = 0;
    cfg.ctrl.mw_wid = QUAD_WIRE;
    cfg.ctrl.hz_cyc = 4;
    cfg.ctrl.mw_cyc = addr4b?13:11;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = 0;
    cfg.ca_low = 0x0<<(addr4b?16:24);
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)&dummy&0x3;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = &dummy;
    lsqspiv2_stg_read_write(reg,&cfg);
}

static void XIP_BANNED_FUNC(hal_flashx_dual_continuous_mode_enter,reg_lsqspiv2_t *reg,bool addr4b)
{
    uint8_t dummy;
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = DUAL_WIRE;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_cyc = addr4b?19:15;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = (addr4b?DUAL_IO_READ4B_OPCODE:DUAL_IO_READ_OPCODE)<<24;
    cfg.ca_low = XIP_MODE_BITS<<(addr4b?16:24);
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)&dummy&0x3;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = &dummy;
    lsqspiv2_stg_read_write(reg,&cfg);
}

static void XIP_BANNED_FUNC(hal_flashx_dual_continuous_mode_exit,reg_lsqspiv2_t *reg,bool addr4b)
{
    uint8_t dummy;
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 0;
    cfg.ctrl.sw_en = 0;
    cfg.ctrl.mw_wid = DUAL_WIRE;
    cfg.ctrl.hz_cyc = 0;
    cfg.ctrl.mw_cyc = addr4b?19:15;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.ca_high = 0;
    cfg.ca_low = 0x0<<(addr4b?16:24);
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)&dummy&0x3;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = &dummy;
    lsqspiv2_stg_read_write(reg,&cfg);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_continuous_mode_start,struct hal_flash_env *env)
{
    if(env->continuous_mode_enable == false)
    {
        return;
    }
    LS_RAM_ASSERT(env->continuous_mode_on == false);
    uint32_t cpu_stat = enter_critical();
    if(env->dual_mode_only)
    {
        hal_flashx_dual_continuous_mode_enter(env->reg,env->addr4b);
    }else
    {
        hal_flashx_quad_continuous_mode_enter(env->reg,env->addr4b);
    }
    env->continuous_mode_on = true;
    exit_critical(cpu_stat);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_continuous_mode_stop,struct hal_flash_env *env)
{
    if(env->continuous_mode_enable == false)
    {
        return;
    }
    LS_RAM_ASSERT(env->continuous_mode_on);
    uint32_t cpu_stat = enter_critical();
    if(env->dual_mode_only)
    {
        hal_flashx_dual_continuous_mode_exit(env->reg,env->addr4b);
    }else
    {
        hal_flashx_quad_continuous_mode_exit(env->reg,env->addr4b);
    }
    env->continuous_mode_on = false;
    exit_critical(cpu_stat);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_write_enable,struct hal_flash_env *env)
{
    lsqspiv2_stg_send_command(env->reg,WRITE_ENABLE_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_continuous_mode_reset,struct hal_flash_env *env)
{
    uint8_t data = CONTINUOUS_READ_MODE_RESET;
    lsqspiv2_stg_write_register(env->reg,CONTINUOUS_READ_MODE_RESET,&data,sizeof(data));
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flashx_prog_func,struct hal_flash_env *env,void *param)
{
    lsqspiv2_stg_read_write(env->reg,param);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flashx_write_reg_func,struct hal_flash_env *env,void *param)
{
    struct flash_wr_rd_reg_param *ptr = param;
    lsqspiv2_stg_write_register(env->reg,ptr->opcode,ptr->buf,ptr->length);
}

static void FLASH_API_SECTION(cfg_ca_high_low_set,bool addr4b,uint8_t opcode,uint32_t offset,struct lsqspiv2_stg_cfg *cfg)
{
    if(addr4b)
    {
        cfg->ca_high = opcode << 24 | offset>>8;
        cfg->ca_low = offset << 24;
    }else
    {
        cfg->ca_high = opcode << 24 | offset;
        cfg->ca_low = 0<<24;
    }
}

static void FLASH_API_SECTION(flash_program_param_set,uint32_t offset,uint8_t *data,uint16_t length,uint8_t multi_type,bool addr4b,struct lsqspiv2_stg_cfg *cfg)
{
    cfg->ctrl.sw_cyc = addr4b?39:31;
    cfg->ctrl.sw_en = 1;
    cfg->ctrl.mw_wid = multi_type;
    cfg->ctrl.hz_cyc = 0;
    cfg->ctrl.mw_cyc = 0;
    cfg->ctrl.mw_en = 0;
    cfg->ctrl.reserved0 = 0;
    cfg->ctrl.reserved1 = 0;
    cfg->ctrl.reserved2 = 0;
    cfg->ctrl.reserved3 = 0;
    cfg->ctrl.reserved4 = 0;
    uint8_t opcode = 0;
    switch(multi_type)
    {
    case SINGLE_WIRE:
        opcode = addr4b?PAGE_PROGRAM4B_OPCODE:PAGE_PROGRAM_OPCODE;
    break;
    case DUAL_WIRE:
        opcode = addr4b?DUAL_PAGE_PROGRAM4B_OPCODE:DUAL_PAGE_PROGRAM_OPCODE;
    break;
    case QUAD_WIRE:
        opcode = addr4b?QUAD_PAGE_PROGRAM4B_OPCODE:QUAD_PAGE_PROGRAM_OPCODE;
    break;
    }
    cfg_ca_high_low_set(addr4b,opcode,offset,cfg);
    cfg->dat_ctrl.dat_en = 1;
    cfg->dat_ctrl.dat_bytes = length - 1;
    cfg->dat_ctrl.dat_dir = WRITE_TO_FLASH;
    cfg->dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg->dat_ctrl.reserved0 = 0;
    cfg->dat_ctrl.reserved1 = 0;
    cfg->dat_ctrl.reserved2 = 0;
    cfg->data = data;
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_quad_page_program,struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint16_t length)
{
    struct lsqspiv2_stg_cfg param;
    flash_program_param_set(offset,data,length,QUAD_WIRE,env->addr4b,&param);
    hal_flashx_program_operation(env,&param);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_dual_page_program,struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint16_t length)
{
    struct lsqspiv2_stg_cfg param;
    flash_program_param_set(offset,data,length,DUAL_WIRE,env->addr4b,&param);
    hal_flashx_program_operation(env,&param);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_page_program,struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint16_t length)
{
    struct lsqspiv2_stg_cfg param;
    flash_program_param_set(offset,data,length,SINGLE_WIRE,env->addr4b,&param);
    hal_flashx_program_operation(env,&param);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flashx_chip_erase_func,struct hal_flash_env *env,void *param)
{
    lsqspiv2_stg_send_command(env->reg,CHIP_ERASE_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flashx_read_func,struct hal_flash_env *env,void *param)
{
    lsqspiv2_stg_read_write(env->reg,param);
}

static void FLASH_API_SECTION(hal_flashx_read_loop,struct hal_flash_env *env,struct lsqspiv2_stg_cfg *cfg,uint8_t opcode,uint32_t offset,uint32_t length,bool addr4b)
{
    while(length)
    {
        cfg_ca_high_low_set(addr4b,opcode,offset,cfg);
        if(length>4096)
        {
            cfg->dat_ctrl.dat_bytes = 4095;
            length -= 4096;
            offset += 4096;
        }else{
            cfg->dat_ctrl.dat_bytes = length - 1;
            length = 0;
        }
        hal_flashx_read_operation(env,cfg);
        cfg->data += 4096;
    }
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_quad_io_read,struct hal_flash_env *env,uint32_t offset, uint8_t * data, uint32_t length)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = QUAD_WIRE;
    cfg.ctrl.hz_cyc = 4;
    cfg.ctrl.mw_cyc = env->addr4b?13:11;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.data = data;
    hal_flashx_read_loop(env,&cfg,env->addr4b?QUAD_IO_READ4B_OPCODE:QUAD_IO_READ_OPCODE,offset,length,env->addr4b);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_dual_io_read,struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint32_t length)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = 7;
    cfg.ctrl.sw_en = 1;
    cfg.ctrl.mw_wid = DUAL_WIRE;
    cfg.ctrl.hz_cyc = 1;
    cfg.ctrl.mw_cyc = env->addr4b?19:15;
    cfg.ctrl.mw_en = 1;
    cfg.ctrl.reserved0 = 0;
    cfg.ctrl.reserved1 = 0;
    cfg.ctrl.reserved2 = 0;
    cfg.ctrl.reserved3 = 0;
    cfg.ctrl.reserved4 = 0;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.data = data;
    hal_flashx_read_loop(env,&cfg,env->addr4b?DUAL_IO_READ4B_OPCODE:DUAL_IO_READ_OPCODE,offset,length,env->addr4b);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_read_addr_8bit_dummy,struct hal_flash_env *env,uint32_t offset, uint8_t * data, uint32_t length,uint8_t opcode,bool addr4b)
{
    struct lsqspiv2_stg_cfg cfg;
    cfg.ctrl.sw_cyc = addr4b?47:39;
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
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.dat_ctrl.dat_bytes = 0;
    cfg.data = data;
    hal_flashx_read_loop(env,&cfg,opcode,offset,length,addr4b);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_deep_power_down,struct hal_flash_env *env)
{
    lsqspiv2_stg_send_command(env->reg,DEEP_POWER_DOWN_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_release_from_deep_power_down,struct hal_flash_env *env)
{
    lsqspiv2_stg_send_command(env->reg,RELEASE_FROM_DEEP_POWER_DOWN_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(do_hal_flashx_read_reg_func,struct hal_flash_env *env,void *param)
{
    struct flash_wr_rd_reg_param *ptr = param;
    lsqspiv2_stg_read_register(env->reg,ptr->opcode,ptr->buf,ptr->length);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_read_unique_id,struct hal_flash_env *env,uint8_t unique_serial_id[16])
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
    hal_flashx_read_operation(env,&cfg);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_program_security_area,struct hal_flash_env *env,uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
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
    hal_flashx_program_operation(env,&cfg);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_read_security_area,struct hal_flash_env *env,uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length)
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
    cfg.ca_low = 0;
    cfg.dat_ctrl.dat_en = 1;
    cfg.dat_ctrl.dat_bytes = length - 1;
    cfg.dat_ctrl.dat_dir = READ_FROM_FLASH;
    cfg.dat_ctrl.dat_offset = (uint32_t)data&0x3;
    cfg.dat_ctrl.reserved0 = 0;
    cfg.dat_ctrl.reserved1 = 0;
    cfg.dat_ctrl.reserved2 = 0;
    cfg.data = data;
    hal_flashx_read_operation(env,&cfg);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_software_reset,struct hal_flash_env *env)
{
    lsqspiv2_stg_send_command(env->reg,RESET_EN_OPCODE);
    lsqspiv2_stg_send_command(env->reg,RESET_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_prog_erase_suspend,struct hal_flash_env *env)
{
    lsqspiv2_stg_send_command(env->reg,PROG_ERASE_SUSPEND);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_prog_erase_resume,struct hal_flash_env *env)
{
    lsqspiv2_stg_send_command(env->reg,PROG_ERASE_RESUME);
}
