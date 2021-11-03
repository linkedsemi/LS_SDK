#include "lspis.h"
#include "lspis_msp.h"
#include "field_manipulate.h"

HAL_StatusTypeDef HAL_PIS_Init(void)
{
    HAL_PIS_MSP_Init();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PIS_DeInit(void)
{
    HAL_PIS_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PIS_Config(uint8_t channel,enum pis_src src,enum pis_dst dst,enum pis_sync_mode sync,enum pis_edge_sel edge)
{
    LSPIS->CH[channel] = FIELD_BUILD(PIS_SYNC,sync)|FIELD_BUILD(PIS_EDGE,edge)|FIELD_BUILD(PIS_SRC,src)|FIELD_BUILD(PIS_DST,dst);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_PIS_Output(uint8_t channel,bool enable)
{
   if(enable)
   {
       LSPIS->OER |= 1<<channel;
   }else{
       LSPIS->OER &= ~(1<<channel);
   }
   return HAL_OK;
}
