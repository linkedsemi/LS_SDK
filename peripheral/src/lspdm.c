#include "lspdm.h"
#include "lspdm_msp.h"
#include "field_manipulate.h"
#include "common.h"
#define PDM_INT_CLR(hpdm) (hpdm->Instance->ICR = 0)

const uint32_t fir_coef_8khz[64] = {
    0xfffeffe6, 0xffffffe6, 0xffedffef, 0xffe20000,
    0xfff30001, 0x000effe8, 0x000affdf, 0xffe90005,
    0xffec0033, 0x00350025, 0x0074fff4, 0x004a000c,
    0x00000085, 0x003a00c4, 0x00e00060, 0x00fdfff6,
    0x00370059, 0xffa5011f, 0x004100e9, 0x0117ff99,
    0x0055fee8, 0xfe58ffe0, 0xfdb400b7, 0xff4aff2d,
    0x0020fc6d, 0xfd77fc2f, 0xf9d6fee7, 0xfaa8ffc2,
    0xffb9fb33, 0x00bcf607, 0xf6dff986, 0xe7310746,
    0x5f94146c, 0xe731146c, 0xf6df0746, 0x00bcf986,
    0xffb9f607, 0xfaa8fb33, 0xf9d6ffc2, 0xfd77fee7,
    0x0020fc2f, 0xff4afc6d, 0xfdb4ff2d, 0xfe5800b7,
    0x0055ffe0, 0x0117fee8, 0x0041ff99, 0xffa500e9,
    0x0037011f, 0x00fd0059, 0x00e0fff6, 0x003a0060,
    0x000000c4, 0x004a0085, 0x0074000c, 0x0035fff4,
    0xffec0025, 0xffe90033, 0x000a0005, 0x000effdf,
    0xfff3ffe8, 0xffe20001, 0xffed0000, 0xffffffef};

const uint32_t fir_coef_16khz[64] = {
    0x0012fffd, 0x0013fffd, 0x00010003, 0xfff70015,
    0x00040013, 0x001dfff9, 0x0010ffea, 0xffe20005,
    0xffd30024, 0x00040000, 0x0025ffb5, 0xffdaffae,
    0xff6a0000, 0xff7d0018, 0xfffcff8f, 0xfff8feff,
    0xff18ff45, 0xfe76fff7, 0xff13ffb9, 0xfff9fe6f,
    0xff59fdd7, 0xfd8ffefa, 0xfd30000d, 0xff1bfed1,
    0x0050fc6c, 0xfe0ffc93, 0xfad9ffb4, 0xfc1200f5,
    0x017cfccc, 0x02d1f7f9, 0xf932fbbd, 0xe9af09aa,
    0x61fe16e7, 0xe9af16e7, 0xf93209aa, 0x02d1fbbd,
    0x017cf7f9, 0xfc12fccc, 0xfad900f5, 0xfe0fffb4,
    0x0050fc93, 0xff1bfc6c, 0xfd30fed1, 0xfd8f000d,
    0xff59fefa, 0xfff9fdd7, 0xff13fe6f, 0xfe76ffb9,
    0xff18fff7, 0xfff8ff45, 0xfffcfeff, 0xff7dff8f,
    0xff6a0018, 0xffda0000, 0x0025ffae, 0x0004ffb5,
    0xffd30000, 0xffe20024, 0x00100005, 0x001dffea,
    0x0004fff9, 0xfff70013, 0x00010015, 0x00130003};


HAL_StatusTypeDef HAL_PDM_Init(PDM_HandleTypeDef *hpdm,PDM_Init_TypeDef *Init)
{
    HAL_PDM_MSP_Init(hpdm);
    HAL_PDM_MSP_Busy_Set(hpdm);
    hpdm->Instance->CFG = *(uint32_t *)&Init->cfg;
    REG_FIELD_WR(hpdm->Instance->CR,PDM_CR_CHN,Init->mode);
    memcpy32((uint32_t *)hpdm->Instance->FIR.COEF,Init->fir->COEF,sizeof(struct pdm_fir)/sizeof(uint32_t));
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PDM_DeInit(PDM_HandleTypeDef *hpdm)
{
    HAL_PDM_MSP_Idle_Set(hpdm);
    HAL_PDM_MSP_DeInit(hpdm);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PDM_Transfer_Config_IT(PDM_HandleTypeDef *hpdm,uint16_t *pFrameBuffer0,uint16_t *pFrameBuffer1,uint16_t FrameNum)
{
    hpdm->Env.Interrupt.pFrameBuffer[0] = pFrameBuffer0;
    hpdm->Env.Interrupt.pFrameBuffer[1] = pFrameBuffer1;
    hpdm->Env.Interrupt.FrameNum = FrameNum;
    PDM_INT_CLR(hpdm);
    hpdm->Instance->IER = 1;
    REG_FIELD_WR(hpdm->Instance->CR,PDM_CR_DMAEN,0);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PDM_Start(PDM_HandleTypeDef *hpdm)
{
    REG_FIELD_WR(hpdm->Instance->CR,PDM_CR_EN,1);
    return HAL_OK;
}

__attribute__((weak)) void HAL_PDM_PingPong_Transfer_Abort(PDM_HandleTypeDef *hpdm,bool stereo){}

HAL_StatusTypeDef HAL_PDM_Stop(PDM_HandleTypeDef *hpdm)
{
    uint32_t CR = hpdm->Instance->CR;
    hpdm->Instance->CR = 0;
    bool dma_en = CR & PDM_CR_DMAEN_MASK ? true : false;
    bool steoro = CR & PDM_CR_CHN_MASK ? true : false;
    if(dma_en)
    {
        HAL_PDM_PingPong_Transfer_Abort(hpdm,steoro);
    }
    return HAL_OK;
}

__attribute__((weak)) void HAL_PDM_CpltCallback(PDM_HandleTypeDef *hpdm){}

void HAL_PDM_IRQHandler(PDM_HandleTypeDef *hpdm)
{
    PDM_INT_CLR(hpdm);
    uint8_t stereo = REG_FIELD_RD(hpdm->Instance->CR,PDM_CR_CHN);
    if(REG_FIELD_RD(hpdm->Instance->CR,PDM_CR_DMAEN)==0)
    {
        *hpdm->Env.Interrupt.pFrameBuffer[0]++ = hpdm->Instance->DATA0;
        if(stereo)
        {
            *hpdm->Env.Interrupt.pFrameBuffer[1]++ = hpdm->Instance->DATA1;
        }
        if(--hpdm->Env.Interrupt.FrameNum==0)
        {
            hpdm->Instance->IDR = 1;
            HAL_PDM_CpltCallback(hpdm);
        }
    }
}
