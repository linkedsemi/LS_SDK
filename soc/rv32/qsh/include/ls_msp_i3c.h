#ifndef __LS_I3C_MSP__
#define __LS_I3C_MSP__

#include "reg_base_addr.h"
#include "reg_i3c.h"


#define I3C10 ((I3C_TypeDef *)0x40095400)
#define I3C9   ((I3C_TypeDef *)0x40095000)   

uint8_t HAL_I3C_RX_DMA_Handshake_Get(I3C_TypeDef *inst);
uint8_t HAL_I3C_TX_DMA_Handshake_Get(I3C_TypeDef *inst);

void HAL_I3C_MspInit(I3C_HandleTypeDef *i3cx);



#endif //__LS_I3C_MSP__