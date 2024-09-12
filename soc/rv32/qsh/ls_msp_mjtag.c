#include "ls_msp_mjtag.h"
#include "ls_hal_mjtag.h"
#include "reg_sysc_per.h"
#include "core_rv32.h"
#include "platform.h"
#include "qsh.h"

static MJTAG_HandleTypeDef *inst_env[3];

static void MJTAG1_IRQHandler()
{
    HAL_MJTAG_IRQHandler(inst_env[0]);
}
static void MJTAG2_IRQHandler()
{
    HAL_MJTAG_IRQHandler(inst_env[1]);
}
static void MJTAG3_IRQHandler()
{
    HAL_MJTAG_IRQHandler(inst_env[2]);
}

void HAL_MJTAG_MSP_Init(MJTAG_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->MJtag)
    {
    case (uint32_t)MJTAG1:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_MJTAG1_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_CLR_MJTAG1_N_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_SET_MJTAG1_N_MASK;
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_MJTAG1_MASK;
        inst_env[0] = inst;
        rv_set_int_isr(QSH_MJTAG1_IRQn, MJTAG1_IRQHandler);
        csi_vic_clear_pending_irq(QSH_MJTAG1_IRQn);
        csi_vic_enable_irq(QSH_MJTAG1_IRQn);
        break;
    case (uint32_t)MJTAG2:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_MJTAG2_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_CLR_MJTAG2_N_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_SET_MJTAG2_N_MASK;
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_MJTAG2_MASK;
        inst_env[1] = inst;
        rv_set_int_isr(QSH_MJTAG2_IRQn, MJTAG2_IRQHandler);
        csi_vic_clear_pending_irq(QSH_MJTAG2_IRQn);
        csi_vic_enable_irq(QSH_MJTAG2_IRQn);
        break;
    case (uint32_t)MJTAG3:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_MJTAG3_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_CLR_MJTAG3_N_MASK;
        SYSC_PER->PD_PER_SRST2 = SYSC_PER_SRST_SET_MJTAG3_N_MASK;
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_SET_MJTAG3_MASK;
        inst_env[2] = inst;
        rv_set_int_isr(QSH_MJTAG3_IRQn, MJTAG3_IRQHandler);
        csi_vic_clear_pending_irq(QSH_MJTAG3_IRQn);
        csi_vic_enable_irq(QSH_MJTAG3_IRQn);
        break;
    default:
        break;
    }
}

void HAL_MJTAG_MSP_DeInit(struct __MJTAG_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->MJtag)
    {
    case (uint32_t)MJTAG1:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_MJTAG1_MASK;
        csi_vic_disable_irq(QSH_MJTAG1_IRQn);
        break;
    case (uint32_t)MJTAG2:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_MJTAG2_MASK;
        csi_vic_disable_irq(QSH_MJTAG2_IRQn);
        break;
    case (uint32_t)MJTAG3:
        SYSC_PER->PD_PER_CLKG2 = SYSC_PER_CLKG_CLR_MJTAG1_MASK;
        csi_vic_disable_irq(QSH_MJTAG3_IRQn);
        break;
    default:
        break;
    }
}