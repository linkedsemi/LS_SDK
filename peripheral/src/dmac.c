#include "lsdmac.h"
#include "dmac_msp.h"
#include "field_manipulate.h"
#include "cpu.h"

static void DMA_Handshake_Config(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,uint8_t handshake)
{
    MODIFY_REG(hdma->Instance->CHSEL[ch_idx/4],0xff<< 8 * (ch_idx % 4),handshake<< 8 * (ch_idx%4));
}

void HAL_DMA_Controller_Init(DMA_Controller_HandleTypeDef *hdma,void *cs_ptr)
{
    HAL_DMA_Controller_MSP_Init(hdma);
    HAL_DMA_Controller_MSP_Busy_Set(hdma);
    hdma->Instance->CFG = 1;
    hdma->Instance->BPTR = (uint32_t)cs_ptr;
}

void HAL_DMA_Controller_DeInit(DMA_Controller_HandleTypeDef *hdma)
{
    hdma->Instance->CFG = 0;
    HAL_DMA_Controller_MSP_Idle_Set(hdma);
    HAL_DMA_Controller_MSP_DeInit(hdma);
}

static void DMA_Enable_IT(reg_dmac_t *reg,uint8_t ch_idx)
{
    uint32_t cpu_stat = enter_critical();
    reg->DONEIEF |= 1<<ch_idx;
    exit_critical(cpu_stat);
}

void HAL_DMA_Channel_Start_IT(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,uint8_t handshake,uint32_t param)
{
    hdma->channel_param[ch_idx] = param;
    DMA_Handshake_Config(hdma,ch_idx,handshake);
    hdma->Instance->DONEICF = 1<<ch_idx;
    DMA_Enable_IT(hdma->Instance,ch_idx);
    hdma->Instance->ENSET = 1<<ch_idx;
}

static struct DMA_Channel_Config *Get_DMA_CS_Base(DMA_Controller_HandleTypeDef *hdma,bool alt)
{
    struct DMA_Channel_Config *ptr;
    if(alt)
    {
        ptr = (struct DMA_Channel_Config *)hdma->Instance->ALTBPTR;
    }else
    {
        ptr = (struct DMA_Channel_Config *)hdma->Instance->BPTR;
    }
    return ptr;
}

void HAL_DMA_Channel_Config_Set(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,bool alt,struct DMA_Channel_Config *cfg)
{
    struct DMA_Channel_Config *ptr = Get_DMA_CS_Base(hdma,alt);
    ptr[ch_idx] = *cfg;
}

void HAL_DMA_Channel_Config_Get(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,bool alt,struct DMA_Channel_Config *cfg)
{
    struct DMA_Channel_Config *ptr = Get_DMA_CS_Base(hdma,alt);
    *cfg = ptr[ch_idx];
}

static void DMA_Disable_IT(reg_dmac_t *reg,uint8_t ch_idx)
{
    uint32_t cpu_stat = enter_critical();
    reg->DONEIEF &= ~(1<<ch_idx);
    exit_critical(cpu_stat);
}

void HAL_DMA_Channel_Abort(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx)
{
    hdma->Instance->ENCLR = 1<<ch_idx;
    DMA_Disable_IT(hdma->Instance,ch_idx);
}

void HAL_DMA_Controller_IRQHandler(DMA_Controller_HandleTypeDef *hdma)
{
    uint8_t i;
    uint32_t current_cs = hdma->Instance->PRIALTSET;
    uint32_t irq = hdma->Instance->DONERIF & hdma->Instance->DONEIEF;
    uint8_t dma_ch_num = hdma->Instance->SR >> 16 & 0x1f;
    for(i=0;i<dma_ch_num;++i)
    {
        if(irq&1<<i)
        {
            struct DMA_Channel_Config *ptr;
            bool alt;
            hdma->Instance->DONEICF = 1<<i;
            if(current_cs & 1<<i)
            {
                ptr = (struct DMA_Channel_Config *)hdma->Instance->ALTBPTR;
                alt = true;
            }else
            {
                ptr = (struct DMA_Channel_Config *)hdma->Instance->BPTR;
                alt = false;
            }
            switch(ptr[i].ctrl_data.cycle_ctrl)
            {
            case DMA_Cycle_Stop:
            case DMA_Cycle_Basic:
                DMA_Disable_IT(hdma->Instance,i);
            break;
            default:
            break;
            }
            void (*cb)(DMA_Controller_HandleTypeDef *,uint32_t,uint8_t,bool) = (void (*)(DMA_Controller_HandleTypeDef *,uint32_t,uint8_t,bool))ptr[i].dummy;
            cb(hdma,hdma->channel_param[i],i,alt);
        }
    }
}
