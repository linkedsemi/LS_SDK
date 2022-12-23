#include "ls_msp_dac.h"
#include "field_manipulate.h"
#include "platform.h"
#include "reg_sysc_per_type.h"
#include "ls_hal_dac.h"
#include "dmac_config.h"
#include "ls_msp_dmacv2.h"
#include "reg_v33_rg_type.h"

void HAL_LSDAC_MSP_Init(void)
{
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_DAC12_MASK, 0 << V33_RG_PD_DAC12_POS);
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_DAC12_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_CLR_DAC12_N_MASK;
    SYSC_PER->PD_PER_SRST3 = SYSC_PER_SRST_SET_DAC12_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_DAC12_MASK;
}
void HAL_LSDAC_MSP_DeInit(void)
{
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_DAC12_MASK;
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_DAC12_MASK, 1 << V33_RG_PD_DAC12_POS);
}

uint8_t HAL_DAC_DMA_Handshake_Get(uint8_t DACx)
{
	  uint8_t val = 0;
    switch (DACx)
    {
    case (uint32_t)DAC1:
        val = CH_DAC_CH1;
        break;
    case (uint32_t)DAC2:
        val = CH_DAC_CH2;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
		return val;
}