#include "ls_msp_spis.h"
#include "ls_hal_spis.h"
#include "field_manipulate.h"
#include "platform.h"
#include "reg_sysc_per.h"
#include "exception_isr.h"
#include "reg_sysc_awo.h"
#include "dmac_config.h"


static SPIS_HandleTypeDef* spis_inst_env;

void SPIS_Handler(void)
{
    HAL_LSSPIS_IRQHandler(spis_inst_env);
}

void HAL_LSSPIS_MSP_Init(struct  __SPIS_HandleTypeDef* inst)
{
    spis_inst_env = inst;
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPIS_MASK;
    SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_CLR_SPIS_N_MASK;
    SYSC_PER->PD_PER_SRST1 = SYSC_PER_SRST_SET_SPIS_N_MASK;
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_SET_SPIS_MASK;
    rv_set_int_isr(SPIS_IRQn, SPIS_Handler);
    csi_vic_clear_pending_irq(SPIS_IRQn);
    csi_vic_enable_irq(SPIS_IRQn);
}

void HAL_LSSPIS_MSP_DeInit(struct  __SPIS_HandleTypeDef* inst)
{
    SYSC_PER->PD_PER_CLKG1 = SYSC_PER_CLKG_CLR_SPIS_MASK;
    REG_FIELD_WR(SYSC_AWO->PIN_SEL0, SYSC_AWO_SPIS_EN, 0);
    csi_vic_disable_irq(SPIS_IRQn);
}

uint8_t HAL_SPIS_TX_DMA_Handshake_Get(SPIS_HandleTypeDef *spis)
{
    return SPIS_TX;
}

uint8_t HAL_SPIS_RX_DMA_Handshake_Get(SPIS_HandleTypeDef *spis)
{
    return SPIS_RX;
} 

