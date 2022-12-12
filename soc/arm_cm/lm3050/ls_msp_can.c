#include "lm3050.h"
#include "ls_msp_can.h"
#include "ls_hal_can.h"
#include "platform.h"
#include "lm3050.h"
#include "reg_sysc_cpu_type.h"
#include "field_manipulate.h"
#include "sys_stat.h"

static CAN_HandleTypeDef* can_inst_env;

void CAN_Handler(void)
{
    HAL_CAN_IRQHandler(can_inst_env);
}

void HAL_BXCAN_MSP_Init(CAN_HandleTypeDef* inst)
{
    can_inst_env = inst;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_BXCAN_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_CLR_BXCAN_MASK;
    SYSC_CPU->PD_CPU_SRST = SYSC_CPU_SRST_SET_BXCAN_MASK;
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_SET_BXCAN_MASK;
    arm_cm_set_int_isr(CAN_IRQn,CAN_Handler);
    __NVIC_ClearPendingIRQ(CAN_IRQn);
    __NVIC_EnableIRQ(CAN_IRQn);
}

void HAL_BXCAN_MSP_DeInit(CAN_HandleTypeDef* inst)
{
    SYSC_CPU->PD_CPU_CLKG = SYSC_CPU_CLKG_CLR_BXCAN_MASK;
    __NVIC_DisableIRQ(CAN_IRQn);
}

void HAL_BXCAN_MSP_Busy_Set(void)
{
    bxcan_status_set(true);
}

void HAL_BXCAN_MSP_Idle_Set(void)
{
    bxcan_status_set(false);
}
