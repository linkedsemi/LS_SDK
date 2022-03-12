#include "i2c_msp.h"
#include "field_manipulate.h"
#include "taurus.h"
#include "HAL_def.h"
#include "core_rv32.h"
#include "platform.h"

#include <stddef.h>
#include "exception_isr.h"

static I2C_HandleTypeDef *i2c_inst_env[3];

void I2C1_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[0]);
}

void I2C2_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[1]);
}

void I2C3_Handler(void)
{
    HAL_I2C_IRQHandler( i2c_inst_env[2]);
}

void HAL_I2C_MSP_Init(I2C_HandleTypeDef *inst)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:


        rv_set_int_isr(I2C1_IRQn,I2C1_Handler);
        i2c_inst_env[0] = inst;
        csi_vic_clear_pending_irq(I2C1_IRQn);
        csi_vic_enable_irq(I2C1_IRQn);
        
    break;
    case (uint32_t)I2C2:

        rv_set_int_isr(I2C2_IRQn,I2C2_Handler);
        i2c_inst_env[1] = inst;
        csi_vic_clear_pending_irq(I2C2_IRQn);
        csi_vic_enable_irq(I2C2_IRQn);

    break;
    case (uint32_t)I2C3:

        rv_set_int_isr(I2C3_IRQn,I2C3_Handler);
        i2c_inst_env[2] = inst;
        csi_vic_clear_pending_irq(I2C3_IRQn);
        csi_vic_enable_irq(I2C3_IRQn);

    break;
    }
}

void HAL_I2C_MSP_DeInit(I2C_HandleTypeDef *inst)
{
    switch((uint32_t)inst->Instance)
    {
    case (uint32_t)I2C1:

        csi_vic_disable_irq(I2C1_IRQn);
    break;
    case (uint32_t)I2C2:

        csi_vic_disable_irq(I2C2_IRQn);
    break;
    case (uint32_t)I2C3:

        csi_vic_disable_irq(I2C3_IRQn);
    break;
    }
}

static void i2c_status_set(I2C_HandleTypeDef *inst,bool status)
{

}

void HAL_I2C_MSP_Busy_Set(I2C_HandleTypeDef *inst)
{
    i2c_status_set(inst,true);
}

void HAL_I2C_MSP_Idle_Set(I2C_HandleTypeDef *inst)
{
    i2c_status_set(inst,false);
}
