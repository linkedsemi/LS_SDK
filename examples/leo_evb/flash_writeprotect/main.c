#include "ls_hal_flash.h"
#include "platform.h"
#include "log.h"
#include <stdio.h>

int main(void)
{
    sys_init_none();
    uint8_t status_reg_0;
    hal_flash_read_status_register_0(&status_reg_0);
    LOG_I("status_reg0 = %x\n",status_reg_0);

    uint8_t status_reg_1;
    hal_flash_read_status_register_1(&status_reg_1);
    LOG_I("status_reg1 = %x\n",status_reg_1);

    uint16_t old_status = (status_reg_1 << 8) | status_reg_0;
    uint16_t new_status1 = old_status | 0x68;       // Block Protect：The first 8k
    // uint16_t new_status2 = new_status1 | 0x180;  // one-time programmable  谨慎使用，配置之后不可修改

    LOG_I("old_status = %x\n",old_status);
    LOG_I("new_status1 = %x\n",new_status1);
    // LOG_I("new_status2 = %x\n",new_status2);

    hal_flash_write_status_register(new_status1);

    hal_flash_read_status_register_0(&status_reg_0);
    LOG_I("new status_reg0 = %x\n",status_reg_0);

    hal_flash_read_status_register_1(&status_reg_1);
    LOG_I("new status_reg1 = %x\n",status_reg_1);

    uint16_t final_status = (status_reg_1 << 8) | status_reg_0;
    LOG_I("final_status = %x\n",final_status);

    while(1)
    {
    }
}