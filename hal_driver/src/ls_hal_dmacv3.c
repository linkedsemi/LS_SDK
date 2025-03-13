#include "ls_hal_dmacv3.h"

void HAL_DMA_Controller_Init(DMA_Controller_HandleTypeDef *hdma)
{
    HAL_DMA_Controller_MSP_Init(hdma);
    HAL_DMA_Controller_MSP_Busy_Set(hdma);
    hdma->Instance->EN = 1;
    hdma->Instance->MASKERR = 0xffff;
}

void HAL_DMA_Controller_DeInit(DMA_Controller_HandleTypeDef *hdma)
{
    hdma->Instance->EN = 0;
    HAL_DMA_Controller_MSP_Idle_Set(hdma);
    HAL_DMA_Controller_MSP_DeInit(hdma);
}

void HAL_DMA_Channel_Start_IT(DMA_Controller_HandleTypeDef *hdma,struct ch_reg *reg_cfg,void (*callback)(DMA_Controller_HandleTypeDef *,uint32_t,uint8_t,uint32_t *,bool,uint32_t),uint32_t param)
{
    uint8_t ch_idx = reg_cfg->ch_idx;
    hdma->channel_callback[ch_idx] = callback;
    hdma->param[ch_idx] = param;
    hdma->Instance->CH[ch_idx].SAR = reg_cfg->sar;
    hdma->Instance->CH[ch_idx].DAR = reg_cfg->dar;
    hdma->Instance->CH[ch_idx].LLP = reg_cfg->llp;
    uint64_t *ctl = (uint64_t *)&reg_cfg->ctl;
    volatile uint64_t *CTL = (void *)hdma->Instance->CH[ch_idx].CTL;
    *CTL = *ctl;
    uint64_t *cfg = (uint64_t *)&reg_cfg->cfg;
    volatile uint64_t *CFG = (void *)hdma->Instance->CH[ch_idx].CFG;
    *CFG = *cfg;
    uint32_t *sgr = (uint32_t *)&reg_cfg->sgr;
    hdma->Instance->CH[ch_idx].SGR = *sgr;
    uint32_t *dsr = (uint32_t *)&reg_cfg->dsr;
    hdma->Instance->CH[ch_idx].DSR = *dsr;
    HAL_DMA_Channel_Handshake_Set(hdma,ch_idx,reg_cfg->handshake);
    hdma->Instance->CLEARBLOCK = 1<<ch_idx;
    hdma->Instance->CLEARTFR = 1<<ch_idx;
    hdma->Instance->MASKBLOCK = 1<<8<<ch_idx|1<<ch_idx;
    hdma->Instance->MASKTFR = 1<<8<<ch_idx|1<<ch_idx;
    hdma->Instance->CHEN = 1<<8<<ch_idx|1<<ch_idx;
}

uint32_t HAL_DMA_Channel_Abort(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx)
{
    hdma->Instance->MASKBLOCK = 1<<8<<ch_idx;
    hdma->Instance->MASKTFR = 1<<8<<ch_idx;
    hdma->Instance->CHEN = 1<<8<<ch_idx;
    return hdma->Instance->CH[ch_idx].CTL[1] & 0xfff;
}

static void int_process(DMA_Controller_HandleTypeDef *hdma,volatile uint32_t *REG_STATUS,volatile uint32_t *REG_CLR,bool tfr_end,uint32_t status_int)
{
    uint8_t status = *REG_STATUS;
    uint8_t i;
    for(i=0;i<8;++i)
    {
        if(status&1<<i)
        {
            *REG_CLR = 1<<i;
            hdma->channel_callback[i](hdma,hdma->param[i],i,(uint32_t *)(hdma->Instance->CH[i].LLP&~0x3),tfr_end,status_int);
        }
    }
}

__attribute__((weak)) void HAL_DMA_Controller_Error_Handler(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_err){}

void HAL_DMA_Controller_IRQHandler(DMA_Controller_HandleTypeDef *hdma)
{
    while(1)
    {
        uint32_t status_int = hdma->Instance->STATUSINT;
        if(!status_int) break;
        if(status_int & DMAC_ERR_MASK)
        {
            HAL_DMA_Controller_Error_Handler(hdma,hdma->Instance->STATUSERR);
        }
        if(status_int & DMAC_DSTT_MASK)
        {
            int_process(hdma,&hdma->Instance->STATUSDSTTRAN,&hdma->Instance->CLEARDSTTRAN,false,DMAC_DSTT_MASK);
        }
        if(status_int & DMAC_SRCT_MASK)
        {

        }
        if(status_int & DMAC_BLOCK_MASK)
        {
            int_process(hdma,&hdma->Instance->STATUSBLOCK,&hdma->Instance->CLEARBLOCK,false,DMAC_SRCT_MASK);
        }
        if(status_int & DMAC_TFR_MASK)
        {
            int_process(hdma,&hdma->Instance->STATUSTFR,&hdma->Instance->CLEARTFR,true,DMAC_TFR_MASK);
        }
    }
    
}