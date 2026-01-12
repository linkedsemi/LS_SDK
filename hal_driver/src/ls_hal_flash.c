#include "hal_flash_int.h"
#if !defined(HAL_FLASH_C_MERGED) || defined(HAL_FLASH_C_DESTINATION)

ROM_SYMBOL bool XIP_BANNED_FUNC(hal_flashx_write_in_process,struct hal_flash_env *env)
{
    uint8_t status_reg_0;
    hal_flashx_read_status_register_0_ram(env,&status_reg_0);
    return status_reg_0 & 0x1 ? true : false;
}

static void XIP_BANNED_FUNC(hal_flashx_write_status_check,struct hal_flash_env *env)
{
    while(hal_flashx_write_in_process(env));
}

NOINLINE ROM_SYMBOL void XIP_BANNED_FUNC(flashx_reading_critical,void (*func)(struct hal_flash_env *,void *),struct hal_flash_env *env,void *param)
{
    sync_for_xip_stop(env);
    uint32_t cpu_stat = ENTER_CRITICAL();
    hal_flashx_continuous_mode_stop(env);
    func(env,param);
    hal_flashx_continuous_mode_start(env);
    EXIT_CRITICAL(cpu_stat);
}

NOINLINE ROM_SYMBOL void XIP_BANNED_FUNC(flashx_writing_critical,void (*func)(struct hal_flash_env *,void *),struct hal_flash_env *env,void *param)
{
    sync_for_xip_stop(env);
    uint32_t cpu_stat = ENTER_CRITICAL();
    hal_flashx_continuous_mode_stop(env);
    hal_flashx_write_enable(env);
    func(env,param);
    env->writing = true;
    EXIT_CRITICAL(cpu_stat);
    hal_flashx_write_status_check(env);
    cpu_stat = ENTER_CRITICAL();
    env->writing = false;
    hal_flashx_continuous_mode_start(env);
    EXIT_CRITICAL(cpu_stat);

}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_multi_io_read,struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint32_t length)
{
    if(env->dual_mode_only)
    {
        hal_flashx_dual_io_read(env,offset,data,length);
    }else
    {
        hal_flashx_quad_io_read(env,offset,data,length);
    }
}

ROM_SYMBOL void FLASH_API_SECTION(do_hal_flashx_program,struct hal_flash_env *env,void *param)
{
    flashx_writing_critical(do_hal_flashx_prog_func,env,param);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_multi_io_page_program,struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint16_t length)
{
    if(env->dual_mode_only)
    {
        hal_flashx_dual_page_program(env,offset,data,length);
    }else
    {
        hal_flashx_quad_page_program(env,offset,data,length);
    }
}

ROM_SYMBOL void FLASH_API_SECTION(do_hal_flashx_write_reg,struct hal_flash_env *env,void *param)
{
    flashx_writing_critical(do_hal_flashx_write_reg_func,env,param);
}

ROM_SYMBOL void FLASH_API_SECTION(do_hal_flashx_chip_erase,struct hal_flash_env *env,void *param)
{
    flashx_writing_critical(do_hal_flashx_chip_erase_func,env,param);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_chip_erase,struct hal_flash_env *env)
{
    hal_flashx_chip_erase_operation(env,NULL);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_write_status_register_0,struct hal_flash_env *env,uint8_t status_0)
{
    struct flash_wr_rd_reg_param param = {
        .buf = &status_0,
        .length = sizeof(status_0),
        .opcode = WRTIE_STATUS_REGISTER_0_OPCODE,
    };
    hal_flashx_write_reg_operation(env, &param);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_write_status_register_1,struct hal_flash_env *env,uint8_t status_1)
{
    struct flash_wr_rd_reg_param param = {
        .buf = &status_1,
        .length = sizeof(status_1),
        .opcode = WRITE_STATUS_REGISTER_1_OPCODE,
    };
    hal_flashx_write_reg_operation(env, &param);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_write_status_register,struct hal_flash_env *env,uint16_t status)
{
    struct flash_wr_rd_reg_param param = {
        .buf = (uint8_t *)&status,
        .length = sizeof(status),
        .opcode = WRITE_STATUS_REGISTER_OPCODE,
    };
    hal_flashx_write_reg_operation(env,&param);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_page_erase,struct hal_flash_env *env,uint32_t offset)
{
    uint8_t addr[3] = {offset>>16&0xff,offset>>8&0xff,offset&0xff};
    struct flash_wr_rd_reg_param param = {
        .buf = addr,
        .length = sizeof(addr),
        .opcode = PAGE_ERASE_OPCODE,
    };
    hal_flashx_write_reg_operation(env,&param);
}

static void FLASH_API_SECTION(hal_flashx_erase,struct hal_flash_env *env,uint32_t offset,uint8_t opcode,uint8_t opcode_4b)
{
    if(env->addr4b)
    {
        uint8_t addr[4] = {offset>>24&0xff,offset>>16&0xff,offset>>8&0xff,offset&0xff};
        struct flash_wr_rd_reg_param param = {
            .buf = addr,
            .length = sizeof(addr),
            .opcode = opcode_4b,
        };
        hal_flashx_write_reg_operation(env,&param);
    }else{
        uint8_t addr[3] = {offset>>16&0xff,offset>>8&0xff,offset&0xff};
        struct flash_wr_rd_reg_param param = {
            .buf = addr,
            .length = sizeof(addr),
            .opcode = opcode,
        };
        hal_flashx_write_reg_operation(env,&param);
    }
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_sector_erase,struct hal_flash_env *env,uint32_t offset)
{
    hal_flashx_erase(env,offset,SECTOR_ERASE_OPCODE,SECTOR_ERASE4B_OPCODE);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_block_32K_erase,struct hal_flash_env *env,uint32_t offset)
{
    hal_flashx_erase(env,offset,BLOCK_32K_ERASE_OPCODE,BLOCK_32K_ERASE4B_OPCODE);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_block_64K_erase,struct hal_flash_env *env,uint32_t offset)
{
    hal_flashx_erase(env,offset,BLOCK_64K_ERASE_OPCODE,BLOCK_64K_ERASE4B_OPCODE);
}

ROM_SYMBOL void FLASH_API_SECTION(do_hal_flashx_read,struct hal_flash_env *env,void *param)
{
    flashx_reading_critical(do_hal_flashx_read_func,env,param);
}

ROM_SYMBOL void FLASH_API_SECTION(do_hal_flashx_read_reg,struct hal_flash_env *env,void *param)
{
    flashx_reading_critical(do_hal_flashx_read_reg_func,env,param);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_read_id,struct hal_flash_env *env,uint8_t jedec_id[3])
{
    struct flash_wr_rd_reg_param param;
    param.buf = jedec_id;
    param.opcode = READ_IDENTIFICATION_OPCODE;
    param.length = 3;
    hal_flashx_read_reg_operation(env,&param);
}

static void FLASH_API_SECTION(hal_flashx_read_status_register_1_byte,struct hal_flash_env *env,uint8_t *buf,uint8_t opcode)
{
    struct flash_wr_rd_reg_param param;
    param.buf = buf;
    param.opcode = opcode;
    param.length = 1;
    hal_flashx_read_reg_operation(env,&param);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_read_status_register_0,struct hal_flash_env *env,uint8_t *status_reg_0)
{
    hal_flashx_read_status_register_1_byte(env,status_reg_0,READ_STATUS_REGISTER_0_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_read_status_register_1,struct hal_flash_env *env,uint8_t *status_reg_1)
{
    hal_flashx_read_status_register_1_byte(env,status_reg_1,READ_STATUS_REGISTER_1_OPCODE);
}

static void XIP_BANNED_FUNC(hal_flashx_read_status_register_1_byte_ram,struct hal_flash_env *env,uint8_t *buf,uint8_t opcode)
{
    struct flash_wr_rd_reg_param param;
    param.buf = buf;
    param.opcode = opcode;
    param.length = 1;
    do_hal_flashx_read_reg_func(env,&param);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_read_status_register_0_ram,struct hal_flash_env *env,uint8_t *status_reg_0)
{
    hal_flashx_read_status_register_1_byte_ram(env,status_reg_0,READ_STATUS_REGISTER_0_OPCODE);
}

ROM_SYMBOL void XIP_BANNED_FUNC(hal_flashx_read_status_register_1_ram,struct hal_flash_env *env,uint8_t *status_reg_1)
{
    hal_flashx_read_status_register_1_byte_ram(env,status_reg_1,READ_STATUS_REGISTER_1_OPCODE);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_erase_security_area,struct hal_flash_env *env,uint8_t idx)
{
    uint8_t addr[3] = {0,idx<<4,0};
    struct flash_wr_rd_reg_param param = {
        .buf = addr,
        .length = sizeof(addr),
        .opcode = ERASE_SECURITY_AREA_OPCODE,
    };
    hal_flashx_write_reg_operation(env,&param);
}

ROM_SYMBOL bool FLASH_API_SECTION(hal_flashx_qe_status_read,struct hal_flash_env *env)
{
    uint8_t status_reg[2];
    hal_flashx_read_status_register_1(env,&status_reg[1]);
    return (0x02 == (status_reg[1]&0x02));
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_qe_status_read_and_set,struct hal_flash_env *env)
{
    uint8_t status_reg[2];
    hal_flashx_read_status_register_1_ram(env,&status_reg[1]);
    if((status_reg[1]&0x02) == 0)
    {
        hal_flashx_read_status_register_0_ram(env,&status_reg[0]);
        hal_flashx_write_status_register(env,status_reg[1]<<8|status_reg[0]|0x200);
    }
}

ROM_SYMBOL uint32_t FLASH_API_SECTION(hal_flashx_total_size_get,struct hal_flash_env *env)
{
    uint8_t jedec_id[3];
    hal_flashx_read_id(env,jedec_id);
    uint8_t capacity_id = jedec_id[2];
    return 1<<capacity_id;
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_fast_read,struct hal_flash_env *env,uint32_t offset, uint8_t * data, uint32_t length)
{
    hal_flashx_read_addr_8bit_dummy(env,offset,data,length,env->addr4b?FAST_READ4B_OPCODE:FAST_READ_OPCODE,env->addr4b);
}

ROM_SYMBOL void FLASH_API_SECTION(hal_flashx_read_sfdp,struct hal_flash_env *env,uint32_t offset,uint8_t *data, uint32_t length)
{
    hal_flashx_read_addr_8bit_dummy(env,offset,data,length,READ_SFDP_OPCODE,false);
}

void XIP_BANNED_FUNC(hal_flashx_prog_erase_suspend_isr,struct hal_flash_env *env)
{
    if(env->writing)
    {
        if(env->suspend_count==0)
        {
            hal_flashx_prog_erase_suspend(env);
            uint8_t status_reg1;
            do{
                hal_flashx_read_status_register_1_ram(env,&status_reg1);
            }while(hal_flashx_write_in_process(env)&&(status_reg1&(STATUS_REG1_SUS1_MASK|STATUS_REG1_SUS2_MASK))==0);
            hal_flashx_continuous_mode_start(env);
        }
        env->suspend_count++;
    }
}

void XIP_BANNED_FUNC(hal_flashx_prog_erase_resume_isr,struct hal_flash_env *env)
{
    if(env->writing)
    {
        env->suspend_count--;
        if(env->suspend_count==0)
        {
            sync_for_xip_stop(env);
            hal_flashx_continuous_mode_stop(env);
            hal_flashx_prog_erase_resume(env);
            DELAY_US(20);
        }
    }
}

uint8_t hal_flashx_read_ear(struct hal_flash_env *env)
{
    uint8_t ear = 0;

    struct flash_wr_rd_reg_param param;
    param.buf = &ear;
    param.opcode = RDEAR_OPCODE;
    param.length = 1;
    hal_flashx_read_reg_operation(env, &param);

    return ear;
}

void hal_flashx_write_ear(struct hal_flash_env *env, uint8_t ear)
{
    struct flash_wr_rd_reg_param param = {
        .buf = &ear,
        .length = 1,
        .opcode = WREAR_OPCODE,
    };
    hal_flashx_write_reg_operation(env, &param);
}

#endif
