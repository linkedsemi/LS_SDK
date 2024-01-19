#include "ls_msp_dac.h"
#include "field_manipulate.h"
#include "platform.h"
#include "reg_sysc_per.h"
#include "ls_hal_dac.h"
#include "dmac_config.h"
#include "reg_v33_rg.h"
#include "ls_dbg.h"
#include "ls_hal_flash.h"

void HAL_LSDAC_MSP_Init(void)
{
    uint32_t dac_ana_trim_value[2] = {0};
    MODIFY_REG(V33_RG->MISC_CTRL1, V33_RG_PD_DAC12_MASK, 0 << V33_RG_PD_DAC12_POS);
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_CLR_DAC12_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_SRST_CLR_DAC12_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_SRST_SET_DAC12_N_MASK;
    SYSC_PER->PD_PER_CLKG3 = SYSC_PER_CLKG_SET_DAC12_MASK;

    hal_flash_read_security_area(1,0x50,(uint8_t *)dac_ana_trim_value,sizeof(dac_ana_trim_value));
    if(dac_ana_trim_value[0]==~dac_ana_trim_value[1])
    {
        LSDAC12->DAC_ANA = dac_ana_trim_value[0];
    }
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
        val = DAC_CH1;
        break;
    case (uint32_t)DAC2:
        val = DAC_CH2;
        break;
    default:
        LS_ASSERT(0);
        break;
    }
		return val;
}