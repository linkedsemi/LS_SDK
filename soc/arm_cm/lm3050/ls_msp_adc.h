#ifndef LS_MSP_ADC_H_
#define LS_MSP_ADC_H_
#include "reg_base_addr.h"
#include "reg_adcv2_type.h" 
#include "ls_hal_adcv2.h"

#define ADC_REG_SEQ0_RK(_CHANNELNB_, _RANKNB_)  \
    ((_CHANNELNB_) << (ADC_REG_SEQ01_POS * ((_RANKNB_)-1)))

#define ADC_REG_SEQ1_RK(_CHANNELNB_, _RANKNB_)  \
    ((_CHANNELNB_) << (ADC_REG_SEQ09_POS * ((_RANKNB_)-1)))

#define ADC_INJ_SEQ_RK(_CHANNELNB_, _RANKNB_)   \
    ((_CHANNELNB_) << (ADC_INJ_SEQ01_POS * ((_RANKNB_)-1)))

#define ADC_FIF_SEQ_RK(_CHANNELNB_, _RANKNB_)  \
    ((_CHANNELNB_) << (ADC_FIF_SEQ01_POS * ((_RANKNB_)-1)))

#define ADC_TSMP(_SAMPLETIME_, _CHANNELNB_)  \
    ((_SAMPLETIME_) << (ADC_TSMP_CTRL_CH1_POS * (_CHANNELNB_)))

#define ADC_CH_CLK_CFG(_CLOCK_,_CHANNELNB_) \
    ((_CLOCK_) << (ADC_CLOCK_CFG_CH1_POS * (_CHANNELNB_)))

#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
    (SET_BIT((__HANDLE__)->Instance->INTR_M, (__INTERRUPT__)))

#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__)  \
    ((((__HANDLE__)->Instance->INTR_R) & (__FLAG__)) == (__FLAG__))

#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  \
    (((__HANDLE__)->Instance->INTR_S & (__INTERRUPT__)) == (__INTERRUPT__))

#define __HAL_ADC_CLEAR_IT(__HANDLE__, __INTERRUPT__) \
    ((__HANDLE__)->Instance->INTR_C |= (__INTERRUPT__))

#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)  \
    ((__HANDLE__)->Instance->INTR_M &= ~(__INTERRUPT__))

#define __HAL_ADC_DISABLE(__HANDLE__)  \
    (CLEAR_BIT((__HANDLE__)->Instance->MISC_CTRL, (ADC_ADC_EN_MASK)))

#define ADC_IS_ENABLE(__HANDLE__) \
   (((((__HANDLE__)->Instance->MISC_CTRL & ADC_ADC_EN_MASK) == ADC_ADC_EN_MASK)) ? SET : RESET)


#define IS_ADC_ALL_INSTANCE(Instance) (((Instance) == LSADC1) || ((Instance) == LSADC2))

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT))

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

#define IS_VREF_SWITCH(VREF)    (((VREF) == ADC_VREF_VCC)     || \
                                ((VREF) == ADC_VREF_EXPOWER)  || \
                                ((VREF) == ADC_VREF_INSIDE)  )

#define IS_ADC_SOFTWARE_TRIGTYPE(TRIGTYPE)    ((TRIGTYPE) == ADC_SOFTWARE_TRIGT)



#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_0)  || \
                                 ((CHANNEL) == ADC_CHANNEL_1)  || \
                                 ((CHANNEL) == ADC_CHANNEL_2)  || \
                                 ((CHANNEL) == ADC_CHANNEL_3)  || \
                                 ((CHANNEL) == ADC_CHANNEL_4)  || \
                                 ((CHANNEL) == ADC_CHANNEL_5)  || \
                                 ((CHANNEL) == ADC_CHANNEL_6)  || \
                                 ((CHANNEL) == ADC_CHANNEL_7)  || \
                                 ((CHANNEL) == ADC1_CHANNEL_BG)  || \
                                 ((CHANNEL) == ADC2_CHANNEL_AMIC)  || \
                                 ((CHANNEL) == ADC1_CHANNEL_VBAT) || \
                                 ((CHANNEL) == ADC1_CHANNEL_TEMPSENSOR) )

#define IS_ADC_REGULAR_RANK(CHANNEL) (((CHANNEL) == ADC_REGULAR_RANK_1 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_2 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_3 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_4 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_5 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_6 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_7 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_8 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_9 ) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_10) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_11) || \
                                      ((CHANNEL) == ADC_REGULAR_RANK_12) )

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_1CYCLE)  || \
                                  ((TIME) == ADC_SAMPLETIME_2CYCLES) || \
                                  ((TIME) == ADC_SAMPLETIME_4CYCLES) || \
                                  ((TIME) == ADC_SAMPLETIME_15CYCLES)  )
                                  
/// LSADC1 Macro for Register Access
#ifdef LSADC1_BASE_ADDR
#define LSADC1 ((reg_adc_t *)LSADC1_BASE_ADDR)
#endif
#ifdef LSADC2_BASE_ADDR
#define LSADC2 ((reg_adc_t *)LSADC2_BASE_ADDR)
#endif

struct __ADC_HandleTypeDef;
void HAL_ADC_MSP_Init(struct __ADC_HandleTypeDef *inst);
void HAL_ADC_MSP_DeInit(struct __ADC_HandleTypeDef *inst);
void HAL_AMIC_MSP_Init();
void HAL_AMIC_MSP_DeInit();
void HAL_ADC_MSP_Busy_Set(struct __ADC_HandleTypeDef *inst);
void HAL_ADC_MSP_Idle_Set(struct __ADC_HandleTypeDef *inst);

void adc_channel_vbat_enable(void);
void adc_channel_vbat_disable(void);

uint8_t HAL_ADC_DMA_Handshake_Get(struct __ADC_HandleTypeDef *inst);

#endif
