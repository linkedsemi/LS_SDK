#include "core_rv32.h"
#include "sys_stat.h"
#include "ls_dbg.h"
#include "qsh.h"
#include "dmac_config.h"
#include "exception_isr.h"
#include "reg_sysc_sec_per.h"
#include "reg_sysc_app_per.h"
#include "field_manipulate.h"

#include "ls_hal_dmacv3.h"
#include "dmac_config.h"

#include "ls_hal_i3c_conmon.h"

#include "ls_msp_i3c.h"

static I3C_HandleTypeDef *i3c_inst_env[12];
void I3C_IRQHandler(I3C_HandleTypeDef *hi3cx);

uint8_t HAL_I3C_TX_DMA_Handshake_Get(I3C_TypeDef *inst)
{
    uint8_t handshake = 0;
    switch ((uint32_t)inst)
    {
    case (uint32_t)I3C9:
        handshake = DMA_I3C9_TX;
        break;
    case (uint32_t)I3C10:
        handshake = DMA_I3C10_TX;
        break;
    default :
       LS_ASSERT(0);
    }
    return handshake;
}

uint8_t HAL_I3C_RX_DMA_Handshake_Get(I3C_TypeDef *inst)
{
    uint8_t handshake = 0;
    switch ((uint32_t)inst)
    {
    case (uint32_t)I3C9:
        handshake = DMA_I3C9_RX;
        break;
    case (uint32_t)I3C10:
        handshake = DMA_I3C10_RX;
        break;
    default :
       LS_ASSERT(0);
    }
    return handshake;
}

void I3C1_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[0]);
}

void I3C2_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[1]);
}

void I3C3_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[2]);
}

void I3C4_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[3]);
}

void I3C5_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[4]);
}

void I3C6_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[5]);
}

void I3C7_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[6]);
}

void I3C8_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[7]);
}

void I3C9_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[8]);
}

void I3C10_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[9]);
}

void I3C11_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[10]);
}

void I3C12_Handler(void)
{
    I3C_IRQHandler(i3c_inst_env[11]);
}

void HAL_I3C_MspInit(I3C_HandleTypeDef *i3cx)
{
    switch ((uint32_t)i3cx->Instance)
    {
    case (uint32_t)I3C9:
        SYSC_APP_PER->PD_PER_CLKG3 |=SYSC_APP_PER_CLKG_SET_I3C9_MASK;
        i3c_inst_env[8] = i3cx;
        rv_set_int_isr(I3C9_IRQN,I3C9_Handler);
        csi_vic_clear_pending_irq(I3C9_IRQN);
        csi_vic_set_prio(I3C9_IRQN,4);
        csi_vic_enable_irq(I3C9_IRQN);
        break;
    case (uint32_t)I3C10:
        SYSC_APP_PER->PD_PER_CLKG3 |=SYSC_APP_PER_CLKG_SET_I3C10_MASK;
        i3c_inst_env[9] = i3cx;
        rv_set_int_isr(I3C10_IRQN,I3C10_Handler);
        csi_vic_set_prio(I3C10_IRQN,5);
        csi_vic_clear_pending_irq(I3C10_IRQN);
        csi_vic_enable_irq(I3C10_IRQN);
        break;
    default :
       LS_ASSERT(0);
    }
}