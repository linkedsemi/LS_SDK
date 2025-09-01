#ifndef LS_MSP_ADC_H_
#define LS_MSP_ADC_H_
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

#define IS_ADC_SOFTWARE_TRIGTYPE(TRIGTYPE)    ((TRIGTYPE) == ADC_SOFTWARE_TRIGT)

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT))

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

#endif /* LS_MSP_ADC_H_ */