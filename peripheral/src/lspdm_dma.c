#include <stddef.h>
#include "lspdm.h"
#include "lsdmac.h"
#include "field_manipulate.h"
#include "lspdm_msp.h"

static void DMA_Channel_PingPong_Update(DMA_Controller_HandleTypeDef *hdma,uint8_t ch_idx,bool alt,uint32_t *ctrl_data)
{
    struct DMA_Channel_Config cfg;
    HAL_DMA_Channel_Config_Get(hdma,ch_idx,alt,&cfg);
    cfg.ctrl_data = *(struct ctrl_data_config *)ctrl_data;
    HAL_DMA_Channel_Config_Set(hdma,ch_idx,alt,&cfg);
}

__attribute__((weak)) void HAL_PDM_DMA_CpltCallback(PDM_HandleTypeDef *hpdm,uint8_t buf_idx){}

static void PDM_DMA_CH0_Callback(void *hdma,uint32_t param,uint8_t ch_idx,bool current_alt)
{
    PDM_HandleTypeDef *hpdm = (PDM_HandleTypeDef *)param;
    DMA_Channel_PingPong_Update(hdma,ch_idx,!current_alt,&hpdm->Env.DMA.PingPong_Ctrl_Data);
    hpdm->Env.DMA.Channel_Done[0] = true;
    if(hpdm->Env.DMA.Channel_Done[1])
    {
        HAL_PDM_DMA_CpltCallback(hpdm,current_alt?0:1);
    }
}

static void PDM_DMA_CH1_Callback(void *hdma,uint32_t param,uint8_t ch_idx,bool current_alt)
{
    PDM_HandleTypeDef *hpdm = (PDM_HandleTypeDef *)param;
    DMA_Channel_PingPong_Update(hdma,ch_idx,!current_alt,&hpdm->Env.DMA.PingPong_Ctrl_Data);
    hpdm->Env.DMA.Channel_Done[1] = true;
    if(hpdm->Env.DMA.Channel_Done[0])
    {
        HAL_PDM_DMA_CpltCallback(hpdm,current_alt?0:1);
    }
}

HAL_StatusTypeDef HAL_PDM_Transfer_Config_DMA(PDM_HandleTypeDef *hpdm,uint16_t *pFrameBuffer0,uint16_t *pFrameBuffer1,uint16_t FrameNum)
{
    struct DMA_Channel_Config prim = {
        .ctrl_data = {
            .cycle_ctrl = DMA_Cycle_Basic,
            .next_useburst = 0,
            .n_minus_1 = FrameNum - 1,
            .R_power = 0,
            .src_prot_ctrl = 0,
            .dst_prot_ctrl = 0,
            .src_size = 1,
            .src_inc = 3,
            .dst_size = 1,
            .dst_inc = 1,
        },
    };
    hpdm->Env.DMA.Channel_Done[0] = false;
    prim.src_data_end_ptr = (uint32_t)&hpdm->Instance->DATA0;
    prim.dst_data_end_ptr = (uint32_t)&pFrameBuffer0[FrameNum-1];
    prim.dummy = (uint32_t)PDM_DMA_CH0_Callback,
    HAL_DMA_Channel_Config_Set(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[0],false,&prim);
    HAL_DMA_Channel_Start_IT(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[0],HAL_PDM_CH0_Handshake_Get(hpdm),(uint32_t)hpdm);
    if(REG_FIELD_RD(hpdm->Instance->CR,PDM_CR_CHN))
    {
        hpdm->Env.DMA.Channel_Done[1] = false;
        prim.src_data_end_ptr = (uint32_t)&hpdm->Instance->DATA1;
        prim.dst_data_end_ptr = (uint32_t)&pFrameBuffer1[FrameNum-1];
        prim.dummy = (uint32_t)PDM_DMA_CH1_Callback;
        HAL_DMA_Channel_Config_Set(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[1],false,&prim);
        HAL_DMA_Channel_Start_IT(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[1],HAL_PDM_CH1_Handshake_Get(hpdm),(uint32_t)hpdm);
    }else
    {
        hpdm->Env.DMA.Channel_Done[1] = true;
    }
    REG_FIELD_WR(hpdm->Instance->CR,PDM_CR_DMAEN,1);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PDM_PingPong_Transfer_Config_DMA(PDM_HandleTypeDef *hpdm,struct PDM_PingPong_Bufptr *CH0_Buf,struct PDM_PingPong_Bufptr *CH1_Buf,uint16_t FrameNum)
{
    struct ctrl_data_config *ctrl = (struct ctrl_data_config *)&hpdm->Env.DMA.PingPong_Ctrl_Data;
    ctrl->cycle_ctrl = DMA_Cycle_PingPong;
    ctrl->next_useburst = 0;
    ctrl->n_minus_1 = FrameNum - 1;
    ctrl->R_power = 0;
    ctrl->src_prot_ctrl = 0;
    ctrl->dst_prot_ctrl = 0;
    ctrl->src_size = 1;
    ctrl->src_inc = 3;
    ctrl->dst_size = 1;
    ctrl->dst_inc = 1;
    hpdm->Env.DMA.Channel_Done[0] = false;
    struct DMA_Channel_Config prim;
    prim.src_data_end_ptr = (uint32_t)&hpdm->Instance->DATA0;
    prim.dst_data_end_ptr = (uint32_t)&CH0_Buf->Bufptr[0][FrameNum-1];
    prim.ctrl_data = *ctrl;
    prim.dummy = (uint32_t)PDM_DMA_CH0_Callback;
    struct DMA_Channel_Config alt;
    alt.src_data_end_ptr = (uint32_t)&hpdm->Instance->DATA0;
    alt.dst_data_end_ptr = (uint32_t)&CH0_Buf->Bufptr[1][FrameNum-1];
    alt.ctrl_data = *ctrl;
    alt.dummy = (uint32_t)PDM_DMA_CH0_Callback;
    HAL_DMA_Channel_Config_Set(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[0],false,&prim);
    HAL_DMA_Channel_Config_Set(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[0],true,&alt);
    HAL_DMA_Channel_Start_IT(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[0],HAL_PDM_CH0_Handshake_Get(hpdm),(uint32_t)hpdm);
    if(REG_FIELD_RD(hpdm->Instance->CR,PDM_CR_CHN))
    {
        hpdm->Env.DMA.Channel_Done[1] = false;
        prim.src_data_end_ptr = (uint32_t)&hpdm->Instance->DATA1;
        prim.dst_data_end_ptr = (uint32_t)&CH1_Buf->Bufptr[0][FrameNum-1];
        prim.ctrl_data = *ctrl;
        prim.dummy = (uint32_t)PDM_DMA_CH1_Callback;
        alt.src_data_end_ptr = (uint32_t)&hpdm->Instance->DATA1;
        alt.dst_data_end_ptr = (uint32_t)&CH1_Buf->Bufptr[1][FrameNum-1];
        alt.ctrl_data = *ctrl;
        alt.dummy = (uint32_t)PDM_DMA_CH1_Callback;
        HAL_DMA_Channel_Config_Set(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[1],false,&prim);
        HAL_DMA_Channel_Config_Set(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[1],true,&alt);
        HAL_DMA_Channel_Start_IT(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[1],HAL_PDM_CH1_Handshake_Get(hpdm),(uint32_t)hpdm);
    }else
    {
        hpdm->Env.DMA.Channel_Done[1] = true;
    }
    REG_FIELD_WR(hpdm->Instance->CR,PDM_CR_DMAEN,1);
    return HAL_OK;
}

void HAL_PDM_PingPong_Transfer_Abort(PDM_HandleTypeDef *hpdm,bool stereo)
{
    HAL_DMA_Channel_Abort(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[0]);
    if(stereo)
    {
        HAL_DMA_Channel_Abort(hpdm->DMAC_Instance,hpdm->Env.DMA.Channel[1]);
    }
}

