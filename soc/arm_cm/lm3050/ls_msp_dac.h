#ifndef LS_MSP_DAC_H_
#define LS_MSP_DAC_H_
#include "reg_base_addr.h"
#include "reg_dac_type.h"

// LSDAC12 Macro for Register Access
#ifdef LSDAC_BASE_ADDR
#define LSDAC12   ((reg_dac_t *)LSDAC_BASE_ADDR)
#endif

#define DAC1_IS_ENABLE(__HANDLE__) \
    (((((__HANDLE__)->Instance->DAC_ANA & DAC_EN_DAC1_MASK) == DAC_EN_DAC1_MASK)) ? SET : RESET)

#define DAC2_IS_ENABLE(__HANDLE__) \
    (((((__HANDLE__)->Instance->DAC_ANA & DAC_EN_DAC2_MASK) == DAC_EN_DAC2_MASK)) ? SET : RESET)

#define __HAL_DAC1_DISABLE(__HANDLE__)  \
    (CLEAR_BIT((__HANDLE__)->Instance->DAC_ANA, (DAC_EN_DAC1_MASK))) 

#define __HAL_DAC2_DISABLE(__HANDLE__)  \
    (CLEAR_BIT((__HANDLE__)->Instance->DAC_ANA, (DAC_EN_DAC2_MASK))) 

#define DAC_DHR12R1_ALIGNMENT(__ALIGNMENT__) (0x00000008UL + (__ALIGNMENT__))

#define DAC_DHR12R2_ALIGNMENT(__ALIGNMENT__) (0x00000014UL + (__ALIGNMENT__))

#define DAC_DHR12RD_ALIGNMENT(__ALIGNMENT__) (0x00000020UL + (__ALIGNMENT__))

struct __DAC_HandleTypeDef;
void HAL_LSDAC_MSP_Init(void);
void HAL_LSDAC_MSP_DeInit(void);
uint8_t HAL_DAC_DMA_Handshake_Get(uint8_t DACx);

#endif