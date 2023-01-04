#include "ls_hal_comp.h"
#include "ls_dbg.h"
#include "platform.h"

static COMP_HandleTypeDef *COMP_inst_env[3];

static void COMP_Handler(void)
{
    uint32_t comp_stat = V33_RG->COMP_STAT;
    enum comp_intr_edge edge = 0;
    for (uint8_t i = 0; i < 3; i++)
    {
        edge = (comp_stat >> (COMP_STAT_COMP1_RINTR_POS + 2 * i)) & 0x3;
        if (edge != 0)
        {
            HAL_COMP_IRQHandler(COMP_inst_env[i], edge, (comp_stat >> (COMP_STAT_COMP1_OUT_POS + i)) & 0x1);
        }
    }
}

void HAL_COMP_MSP_Init(COMP_HandleTypeDef *inst)
{
    switch ((uint32_t)inst->COMP)
    {
    case (uint32_t)LSCOMP1:
        COMP_inst_env[0] = inst;
        break;
    case (uint32_t)LSCOMP2:
        COMP_inst_env[1] = inst;
        break;
    case (uint32_t)LSCOMP3:
        COMP_inst_env[2] = inst;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
    V33_RG->CLKG_SRST = V33_RG_CLKG_SET_CMP_MASK;
    arm_cm_set_int_isr(COMP_IRQn, COMP_Handler);
    __NVIC_ClearPendingIRQ(COMP_IRQn);
    __NVIC_EnableIRQ(COMP_IRQn);
}

void HAL_COMP_MSP_DeInit(void)
{
    V33_RG->CLKG_SRST = V33_RG_CLKG_CLR_CMP_MASK;
    __NVIC_DisableIRQ(COMP_IRQn);
}