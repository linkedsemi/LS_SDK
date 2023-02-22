#ifndef _LS_LL_TIMER_HANDLER_H
#define _LS_LL_TIMER_HANDLER_H
#include <stdbool.h>
#include "reg_timer_type.h"
#include "ls_msp_timer.h"
#include "sdk_config.h"
#include "HAL_def.h"
#include "field_manipulate.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSTIMER
 *  @{
 */
/******************************************************************************
 External Macro Definition
 ******************************************************************************/


/******************************************************************************
 External Variable Definition
 ******************************************************************************/
/** @defgroup TIM_ClearInput_Source TIM Clear Input Source
  * @{
  */
#define TIM_CLEARINPUTSOURCE_NONE           0x00000000U   /*!< OCREF_CLR is disabled */
#define TIM_CLEARINPUTSOURCE_ETR            0x00000001U   /*!< OCREF_CLR is connected to ETRF input */
/**
  * @}
  */

/** @defgroup TIM_Event_Source TIM Event Source
  * @{
  */
#define TIM_EVENTSOURCE_UPDATE              TIMER_EGR_UG_MASK     /*!< Reinitialize the counter and generates an update of the registers */
#define TIM_EVENTSOURCE_CC1                 TIMER_EGR_CC1G_MASK   /*!< A capture/compare event is generated on channel 1 */
#define TIM_EVENTSOURCE_CC2                 TIMER_EGR_CC2G_MASK   /*!< A capture/compare event is generated on channel 2 */
#define TIM_EVENTSOURCE_CC3                 TIMER_EGR_CC3G_MASK   /*!< A capture/compare event is generated on channel 3 */
#define TIM_EVENTSOURCE_CC4                 TIMER_EGR_CC4G_MASK   /*!< A capture/compare event is generated on channel 4 */
#define TIM_EVENTSOURCE_COM                 TIMER_EGR_COMG_MASK   /*!< A commutation event is generated */
#define TIM_EVENTSOURCE_TRIGGER             TIMER_EGR_TG_MASK     /*!< A trigger event is generated */
#define TIM_EVENTSOURCE_BREAK               TIMER_EGR_BG_MASK     /*!< A break event is generated */
/**
  * @}
  */

/** @defgroup TIM_Input_Channel_Polarity TIM Input Channel polarity
  * @{
  */
#define  TIM_INPUTCHANNELPOLARITY_RISING      0x00000000U                              /*!< Polarity for TIx source */
#define  TIM_INPUTCHANNELPOLARITY_FALLING     TIMER_CCER_CC1P_MASK                     /*!< Polarity for TIx source */
#define  TIM_INPUTCHANNELPOLARITY_BOTHEDGE    (TIMER_CCER_CC1P_MASK | TIMER_CCER_CC1NP_MASK)  /*!< Polarity for TIx source */
/**
  * @}
  */

/** @defgroup TIM_ETR_Polarity TIM ETR Polarity
  * @{
  */
#define TIM_ETRPOLARITY_INVERTED              TIMER_SMCR_ETP_MASK               /*!< Polarity for ETR source */
#define TIM_ETRPOLARITY_NONINVERTED           0x00000000U                       /*!< Polarity for ETR source */
/**
  * @}
  */

/** @defgroup TIM_ETR_Prescaler TIM ETR Prescaler
  * @{
  */
#define TIM_ETRPRESCALER_DIV1                 0x00000000U                       /*!< No prescaler is used */
#define TIM_ETRPRESCALER_DIV2                 TIMER_SMCR_ETPS_0                 /*!< ETR input source is divided by 2 */
#define TIM_ETRPRESCALER_DIV4                 TIMER_SMCR_ETPS_1                 /*!< ETR input source is divided by 4 */
#define TIM_ETRPRESCALER_DIV8                 TIMER_SMCR_ETPS                   /*!< ETR input source is divided by 8 */
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode TIM Counter Mode
  * @{
  */
#define TIM_COUNTERMODE_UP                 0x00000000U                          /*!< Counter used as up-counter   */
#define TIM_COUNTERMODE_DOWN               TIMER_CR1_DIR_MASK                   /*!< Counter used as down-counter */
#define TIM_COUNTERMODE_CENTERALIGNED1     TIMER_CR1_CMS_0                      /*!< Center-aligned mode 1        */
#define TIM_COUNTERMODE_CENTERALIGNED2     TIMER_CR1_CMS_1                      /*!< Center-aligned mode 2        */
#define TIM_COUNTERMODE_CENTERALIGNED3     TIMER_CR1_CMS                        /*!< Center-aligned mode 3        */
/**
  * @}
  */

/** @defgroup TIM_ClockDivision TIM Clock Division
  * @{
  */
#define TIM_CLOCKDIVISION_DIV1             0x00000000U                        /*!< Clock division: tDTS=tCK_INT   */
#define TIM_CLOCKDIVISION_DIV2             TIMER_CR1_CKD_0                    /*!< Clock division: tDTS=2*tCK_INT */
#define TIM_CLOCKDIVISION_DIV4             TIMER_CR1_CKD_1                    /*!< Clock division: tDTS=4*tCK_INT */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_State TIM Output Compare State
  * @{
  */
#define TIM_OUTPUTSTATE_DISABLE            0x00000000U                          /*!< Capture/Compare 1 output disabled */
#define TIM_OUTPUTSTATE_ENABLE             TIMER_CCER_CC1E_MASK                 /*!< Capture/Compare 1 output enabled */
/**
  * @}
  */

/** @defgroup TIM_AutoReloadPreload TIM Auto-Reload Preload
  * @{
  */
#define TIM_AUTORELOAD_PRELOAD_DISABLE                0x00000000U               /*!< TIMx_ARR register is not buffered */
#define TIM_AUTORELOAD_PRELOAD_ENABLE                 TIMER_CR1_ARPE_MASK       /*!< TIMx_ARR register is buffered */

/**
  * @}
  */

/** @defgroup TIM_Output_Fast_State TIM Output Fast State
  * @{
  */
#define TIM_OCFAST_DISABLE                 0x00000000U                          /*!< Output Compare fast disable */
#define TIM_OCFAST_ENABLE                  TIMER_CCMR1_OC1FE_MASK              /*!< Output Compare fast enable  */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_State TIM Complementary Output Compare State
  * @{
  */
#define TIM_OUTPUTNSTATE_DISABLE           0x00000000U                          /*!< OCxN is disabled  */
#define TIM_OUTPUTNSTATE_ENABLE            TIMER_CCER_CC1NE_MASK                /*!< OCxN is enabled   */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Polarity TIM Output Compare Polarity
  * @{
  */
#define TIM_OCPOLARITY_HIGH                0x00000000U                          /*!< Capture/Compare output polarity  */
#define TIM_OCPOLARITY_LOW                 TIMER_CCER_CC1P_MASK                 /*!< Capture/Compare output polarity  */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity TIM Complementary Output Compare Polarity
  * @{
  */
#define TIM_OCNPOLARITY_HIGH               0x00000000U                          /*!< Capture/Compare complementary output polarity */
#define TIM_OCNPOLARITY_LOW                TIMER_CCER_CC1NP_MASK                /*!< Capture/Compare complementary output polarity */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Idle_State TIM Output Compare Idle State
  * @{
  */
#define TIM_OCIDLESTATE_SET                TIMER_CR2_OIS1_MASK                      /*!< Output Idle state: OCx=1 when MOE=0 */
#define TIM_OCIDLESTATE_RESET              0x00000000U                          /*!< Output Idle state: OCx=0 when MOE=0 */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Idle_State TIM Complementary Output Compare Idle State
  * @{
  */
#define TIM_OCNIDLESTATE_SET               TIMER_CR2_OIS1N_MASK                     /*!< Complementary output Idle state: OCxN=1 when MOE=0 */
#define TIM_OCNIDLESTATE_RESET             0x00000000U                          /*!< Complementary output Idle state: OCxN=0 when MOE=0 */
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Polarity TIM Input Capture Polarity
  * @{
  */
#define  TIM_ICPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING      /*!< Capture triggered by rising edge on timer input                  */
#define  TIM_ICPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING     /*!< Capture triggered by falling edge on timer input                 */
#define  TIM_ICPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE    /*!< Capture triggered by both rising and falling edges on timer input*/
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Selection TIM Input Capture Selection
  * @{  
  */
#define TIM_ICSELECTION_DIRECTTI           TIMER_CCMR1_CC1S_0                     /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSELECTION_INDIRECTTI         TIMER_CCMR1_CC1S_1                     /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to IC2, IC1, IC4 or IC3, respectively */
#define TIM_ICSELECTION_TRC                TIMER_CCMR1_CC1S_MASK                  /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC */
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Prescaler TIM Input Capture Prescaler
  * @{
  */
#define TIM_ICPSC_DIV1                     0x00000000U                          /*!< Capture performed each time an edge is detected on the capture input */
#define TIM_ICPSC_DIV2                     TIMER_CCMR1_IC1PSC_0                   /*!< Capture performed once every 2 events                                */
#define TIM_ICPSC_DIV4                     TIMER_CCMR1_IC1PSC_1                   /*!< Capture performed once every 4 events                                */
#define TIM_ICPSC_DIV8                     TIMER_CCMR1_IC1PSC                     /*!< Capture performed once every 8 events                                */
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode TIM One Pulse Mode
  * @{
  */
#define TIM_OPMODE_SINGLE                  TIMER_CR1_OPM_MASK                          /*!< Counter stops counting at the next update event */
#define TIM_OPMODE_REPETITIVE              0x00000000U                          /*!< Counter is not stopped at update event          */
/**
  * @}
  */

/** @defgroup TIM_Interrupt_definition TIM interrupt Definition
  * @{
  */
#define TIM_IT_UPDATE                      TIMER_IDR_UIE_MASK                         /*!< Update interrupt            */
#define TIM_IT_CC1                         TIMER_IDR_CC1IE_MASK                       /*!< Capture/Compare 1 interrupt */
#define TIM_IT_CC2                         TIMER_IDR_CC2IE_MASK                       /*!< Capture/Compare 2 interrupt */
#define TIM_IT_CC3                         TIMER_IDR_CC3IE_MASK                       /*!< Capture/Compare 3 interrupt */
#define TIM_IT_CC4                         TIMER_IDR_CC4IE_MASK                       /*!< Capture/Compare 4 interrupt */
#define TIM_IT_COM                         TIMER_IDR_COMIE_MASK                       /*!< Commutation interrupt       */
#define TIM_IT_TRIGGER                     TIMER_IDR_TIE_MASK                         /*!< Trigger interrupt           */
#define TIM_IT_BREAK                       TIMER_IDR_BIE_MASK                         /*!< Break interrupt             */
#define TIM_IT_CC1O                        TIMER_IDR_CC1OIE_MASK                      /*!< Capture/compare 1 overcap interrupt */
#define TIM_IT_CC2O                        TIMER_IDR_CC2OIE_MASK                      /*!< Break interrupt 2 overcap interrupt */
#define TIM_IT_CC3O                        TIMER_IDR_CC3OIE_MASK                      /*!< Break interrupt 3 overcap interrupt */
#define TIM_IT_CC4O                        TIMER_IDR_CC4OIE_MASK                      /*!< Break interrupt 4 overcap interrupt */
/**
  * @}
  */

/** @defgroup TIM_Flag_definition TIM Flag Definition
  * @{
  */
#define TIM_FLAG_UPDATE                    TIMER_RIF_UIF                           /*!< Update interrupt flag         */
#define TIM_FLAG_CC1                       TIMER_RIF_CC1IF                         /*!< Capture/Compare 1 interrupt flag */
#define TIM_FLAG_CC2                       TIMER_RIF_CC2IF                         /*!< Capture/Compare 2 interrupt flag */
#define TIM_FLAG_CC3                       TIMER_RIF_CC3IF                         /*!< Capture/Compare 3 interrupt flag */
#define TIM_FLAG_CC4                       TIMER_RIF_CC4IF                         /*!< Capture/Compare 4 interrupt flag */
#define TIM_FLAG_COM                       TIMER_RIF_COMIF                         /*!< Commutation interrupt flag    */
#define TIM_FLAG_TRIGGER                   TIMER_RIF_TIF                           /*!< Trigger interrupt flag        */
#define TIM_FLAG_BREAK                     TIMER_RIF_BIF                           /*!< Break interrupt flag          */
#define TIM_FLAG_CC1OF                     TIMER_RIF_CC1OIF                         /*!< Capture 1 overcapture flag    */
#define TIM_FLAG_CC2OF                     TIMER_RIF_CC2OIF                         /*!< Capture 2 overcapture flag    */
#define TIM_FLAG_CC3OF                     TIMER_RIF_CC3OIF                         /*!< Capture 3 overcapture flag    */
#define TIM_FLAG_CC4OF                     TIMER_RIF_CC4OIF                         /*!< Capture 4 overcapture flag    */
/**
  * @}
  */

/** @defgroup TIM_Channel TIM Channel
  * @{
  */
#define TIM_CHANNEL_1                      0x00000000U                          /*!< Capture/compare channel 1 identifier      */
#define TIM_CHANNEL_2                      0x00000004U                          /*!< Capture/compare channel 2 identifier      */
#define TIM_CHANNEL_3                      0x00000008U                          /*!< Capture/compare channel 3 identifier      */
#define TIM_CHANNEL_4                      0x0000000CU                          /*!< Capture/compare channel 4 identifier      */
#define TIM_CHANNEL_ALL                    0x0000003CU                          /*!< Global Capture/compare channel identifier  */
/**
  * @}
  */

/** @defgroup TIM_Clock_Source TIM Clock Source
  * @{
  */
#define TIM_CLOCKSOURCE_ETRMODE2    TIMER_SMCR_ETPS_1    /*!< External clock source mode 2                          */
#define TIM_CLOCKSOURCE_INTERNAL    TIMER_SMCR_ETPS_0    /*!< Internal clock source                                 */
#define TIM_CLOCKSOURCE_ITR0        TIM_TS_ITR0          /*!< External clock source mode 1 (ITR0)                   */
#define TIM_CLOCKSOURCE_ITR1        TIM_TS_ITR1          /*!< External clock source mode 1 (ITR1)                   */
#define TIM_CLOCKSOURCE_ITR2        TIM_TS_ITR2          /*!< External clock source mode 1 (ITR2)                   */
#define TIM_CLOCKSOURCE_ITR3        TIM_TS_ITR3          /*!< External clock source mode 1 (ITR3)                   */
#define TIM_CLOCKSOURCE_TI1ED       TIM_TS_TI1F_ED       /*!< External clock source mode 1 (TTI1FP1 + edge detect.) */
#define TIM_CLOCKSOURCE_TI1         TIM_TS_TI1FP1        /*!< External clock source mode 1 (TTI1FP1)                */
#define TIM_CLOCKSOURCE_TI2         TIM_TS_TI2FP2        /*!< External clock source mode 1 (TTI2FP2)                */
#define TIM_CLOCKSOURCE_ETRMODE1    TIM_TS_ETRF          /*!< External clock source mode 1 (ETRF)                   */
/**
  * @}
  */

/** @defgroup TIM_Clock_Polarity TIM Clock Polarity
  * @{
  */
#define TIM_CLOCKPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED           /*!< Polarity for ETRx clock sources */
#define TIM_CLOCKPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED        /*!< Polarity for ETRx clock sources */
#define TIM_CLOCKPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING    /*!< Polarity for TIx clock sources */
#define TIM_CLOCKPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING   /*!< Polarity for TIx clock sources */
#define TIM_CLOCKPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE  /*!< Polarity for TIx clock sources */
/**
  * @}
  */

/** @defgroup TIM_Clock_Prescaler TIM Clock Prescaler
  * @{
  */
#define TIM_CLOCKPRESCALER_DIV1                 TIM_ETRPRESCALER_DIV1           /*!< No prescaler is used                                                     */
#define TIM_CLOCKPRESCALER_DIV2                 TIM_ETRPRESCALER_DIV2           /*!< Prescaler for External ETR Clock: Capture performed once every 2 events. */
#define TIM_CLOCKPRESCALER_DIV4                 TIM_ETRPRESCALER_DIV4           /*!< Prescaler for External ETR Clock: Capture performed once every 4 events. */
#define TIM_CLOCKPRESCALER_DIV8                 TIM_ETRPRESCALER_DIV8           /*!< Prescaler for External ETR Clock: Capture performed once every 8 events. */
/**
  * @}
  */

/** @defgroup TIM_ClearInput_Polarity TIM Clear Input Polarity
  * @{
  */
#define TIM_CLEARINPUTPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED      /*!< Polarity for ETRx pin */
#define TIM_CLEARINPUTPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED   /*!< Polarity for ETRx pin */
/**
  * @}
  */

/** @defgroup TIM_ClearInput_Prescaler TIM Clear Input Prescaler
  * @{
  */
#define TIM_CLEARINPUTPRESCALER_DIV1              TIM_ETRPRESCALER_DIV1         /*!< No prescaler is used                                                   */
#define TIM_CLEARINPUTPRESCALER_DIV2              TIM_ETRPRESCALER_DIV2         /*!< Prescaler for External ETR pin: Capture performed once every 2 events. */
#define TIM_CLEARINPUTPRESCALER_DIV4              TIM_ETRPRESCALER_DIV4         /*!< Prescaler for External ETR pin: Capture performed once every 4 events. */
#define TIM_CLEARINPUTPRESCALER_DIV8              TIM_ETRPRESCALER_DIV8         /*!< Prescaler for External ETR pin: Capture performed once every 8 events. */
/**
  * @}
  */

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state TIM OSSR OffState Selection for Run mode state
  * @{
  */
#define TIM_OSSR_ENABLE                          TIMER_BDTR_OSSR                  /*!< When inactive, OC/OCN outputs are enabled (still controlled by the timer)           */
#define TIM_OSSR_DISABLE                         0x00000000U                    /*!< When inactive, OC/OCN outputs are disabled (not controlled any longer by the timer) */
/**
  * @}
  */

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state TIM OSSI OffState Selection for Idle mode state
  * @{
  */
#define TIM_OSSI_ENABLE                          TIMER_BDTR_OSSI                  /*!< When inactive, OC/OCN outputs are enabled (still controlled by the timer)           */
#define TIM_OSSI_DISABLE                         0x00000000U                    /*!< When inactive, OC/OCN outputs are disabled (not controlled any longer by the timer) */
/**
  * @}
  */
/** @defgroup TIM_Lock_level  TIM Lock level
  * @{
  */
#define TIM_LOCKLEVEL_OFF                  0x00000000U                          /*!< LOCK OFF     */
#define TIM_LOCKLEVEL_1                    TIMER_BDTR_LOCK_0                      /*!< LOCK Level 1 */
#define TIM_LOCKLEVEL_2                    TIMER_BDTR_LOCK_1                      /*!< LOCK Level 2 */
#define TIM_LOCKLEVEL_3                    TIMER_BDTR_LOCK                        /*!< LOCK Level 3 */
/**
  * @}
  */

/** @defgroup TIM_Break_Input_enable_disable TIM Break Input Enable
  * @{
  */
#define TIM_BREAK_ENABLE                   TIMER_BDTR_BKE                         /*!< Break input BRK is enabled  */
#define TIM_BREAK_DISABLE                  0x00000000U                          /*!< Break input BRK is disabled */
/**
  * @}
  */

/** @defgroup TIM_Break_Polarity TIM Break Input Polarity
  * @{
  */
#define TIM_BREAKPOLARITY_LOW              0x00000000U                          /*!< Break input BRK is active low  */
#define TIM_BREAKPOLARITY_HIGH             TIMER_BDTR_BKP                         /*!< Break input BRK is active high */
/**
  * @}
  */

/** @defgroup TIM_AOE_Bit_Set_Reset TIM Automatic Output Enable
  * @{
  */
#define TIM_AUTOMATICOUTPUT_DISABLE        0x00000000U                          /*!< MOE can be set only by software */
#define TIM_AUTOMATICOUTPUT_ENABLE         TIMER_BDTR_AOE                         /*!< MOE can be set by software or automatically at the next update event 
                                                                                    (if none of the break inputs BRK and BRK2 is active) */
/**
  * @}
  */

/** @defgroup TIM_Master_Mode_Selection TIM Master Mode Selection
  * @{
  */
#define TIM_TRGO_RESET            0x00000000U                                      /*!< TIMx_EGR.UG bit is used as trigger output (TRGO)              */
#define TIM_TRGO_ENABLE           TIMER_CR2_MMS_0                                    /*!< TIMx_CR1.CEN bit is used as trigger output (TRGO)             */
#define TIM_TRGO_UPDATE           TIMER_CR2_MMS_1                                    /*!< Update event is used as trigger output (TRGO)                 */
#define TIM_TRGO_OC1              (TIMER_CR2_MMS_1 | TIMER_CR2_MMS_0)                  /*!< Capture or a compare match 1 is used as trigger output (TRGO) */
#define TIM_TRGO_OC1REF           TIMER_CR2_MMS_2                                    /*!< OC1REF signal is used as trigger output (TRGO)                */
#define TIM_TRGO_OC2REF           (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_0)                  /*!< OC2REF signal is used as trigger output(TRGO)                 */
#define TIM_TRGO_OC3REF           (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_1)                  /*!< OC3REF signal is used as trigger output(TRGO)                 */
#define TIM_TRGO_OC4REF           (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_1 | TIMER_CR2_MMS_0)  /*!< OC4REF signal is used as trigger output(TRGO)                 */
/**
  * @}
  */

/** @defgroup TIM_Master_Slave_Mode TIM Master/Slave Mode
  * @{
  */
#define TIM_MASTERSLAVEMODE_ENABLE         TIMER_SMCR_MSM                         /*!< No action */
#define TIM_MASTERSLAVEMODE_DISABLE        0x00000000U                          /*!< Master/slave mode is selected */
/**
  * @}
  */

/** @defgroup TIM_Slave_Mode TIM Slave mode
  * @{
  */
#define TIM_SLAVEMODE_DISABLE                0x00000000U                                        /*!< Slave mode disabled           */
#define TIM_SLAVEMODE_RESET                  TIMER_SMCR_SMS_2                                     /*!< Reset Mode                    */
#define TIM_SLAVEMODE_GATED                  (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_0)                  /*!< Gated Mode                    */
#define TIM_SLAVEMODE_TRIGGER                (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_1)                  /*!< Trigger Mode                  */
#define TIM_SLAVEMODE_EXTERNAL1              (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_1 | TIMER_SMCR_SMS_0) /*!< External Clock Mode 1         */
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_and_PWM_modes TIM Output Compare and PWM Modes
  * @{
  */
#define TIM_OCMODE_TIMING                   0x00000000U                                              /*!< Frozen                                 */
#define TIM_OCMODE_ACTIVE                   TIMER_CCMR1_OC1M_0                                         /*!< Set channel to active level on match   */
#define TIM_OCMODE_INACTIVE                 TIMER_CCMR1_OC1M_1                                         /*!< Set channel to inactive level on match */
#define TIM_OCMODE_TOGGLE                   (TIMER_CCMR1_OC1M_1 | TIMER_CCMR1_OC1M_0)                    /*!< Toggle                                 */
#define TIM_OCMODE_PWM1                     (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_1)                    /*!< PWM mode 1                             */
#define TIM_OCMODE_PWM2                     (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_1 | TIMER_CCMR1_OC1M_0) /*!< PWM mode 2                             */
#define TIM_OCMODE_FORCED_ACTIVE            (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_0)                    /*!< Force active level                     */
#define TIM_OCMODE_FORCED_INACTIVE          TIMER_CCMR1_OC1M_2                                         /*!< Force inactive level                   */
/**
  * @}
  */

/** @defgroup TIM_Trigger_Selection TIM Trigger Selection
  * @{
  */
#define TIM_TS_ITR0          0x00000000U                /*!< Internal Trigger 0 (ITR0)              */
#define TIM_TS_ITR1          TIMER_SMCR_TS_0                /*!< Internal Trigger 1 (ITR1)              */
#define TIM_TS_ITR2          TIMER_SMCR_TS_1                /*!< Internal Trigger 2 (ITR2)              */
#define TIM_TS_ITR3          (TIMER_SMCR_TS_0 | TIMER_SMCR_TS_1)                /*!< Internal Trigger 3 (ITR3)              */
#define TIM_TS_TI1F_ED       TIMER_SMCR_TS_2                /*!< TI1 Edge Detector (TI1F_ED)            */
#define TIM_TS_TI1FP1        (TIMER_SMCR_TS_0 | TIMER_SMCR_TS_2)                /*!< Filtered Timer Input 1 (TI1FP1)        */
#define TIM_TS_TI2FP2        (TIMER_SMCR_TS_1 | TIMER_SMCR_TS_2)                /*!< Filtered Timer Input 2 (TI2FP2)        */
#define TIM_TS_ETRF          (TIMER_SMCR_TS_0 | TIMER_SMCR_TS_1 | TIMER_SMCR_TS_2)                /*!< Filtered External Trigger input (ETRF) */
#define TIM_TS_NONE          0x0000FFFFU                /*!< No trigger selected                    */
/**
  * @}
  */

/** @defgroup TIM_Trigger_Polarity TIM Trigger Polarity
  * @{
  */
#define TIM_TRIGGERPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED               /*!< Polarity for ETRx trigger sources             */
#define TIM_TRIGGERPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED            /*!< Polarity for ETRx trigger sources             */
#define TIM_TRIGGERPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING        /*!< Polarity for TIxFPx or TI1_ED trigger sources */
#define TIM_TRIGGERPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING       /*!< Polarity for TIxFPx or TI1_ED trigger sources */
#define TIM_TRIGGERPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE      /*!< Polarity for TIxFPx or TI1_ED trigger sources */
/**
  * @}
  */

/** @defgroup TIM_Trigger_Prescaler TIM Trigger Prescaler
  * @{
  */
#define TIM_TRIGGERPRESCALER_DIV1             TIM_ETRPRESCALER_DIV1             /*!< No prescaler is used                                                       */
#define TIM_TRIGGERPRESCALER_DIV2             TIM_ETRPRESCALER_DIV2             /*!< Prescaler for External ETR Trigger: Capture performed once every 2 events. */
#define TIM_TRIGGERPRESCALER_DIV4             TIM_ETRPRESCALER_DIV4             /*!< Prescaler for External ETR Trigger: Capture performed once every 4 events. */
#define TIM_TRIGGERPRESCALER_DIV8             TIM_ETRPRESCALER_DIV8             /*!< Prescaler for External ETR Trigger: Capture performed once every 8 events. */
/**
  * @}
  */

/** @defgroup TIM_TI1_Selection TIM TI1 Input Selection
  * @{
  */
#define TIM_TI1SELECTION_CH1               0x00000000U                          /*!< The TIMx_CH1 pin is connected to TI1 input */
#define TIM_TI1SELECTION_XORCOMBINATION    TIMER_CR2_TI1S                      /*!< The TIMx_CH1, CH2 and CH3 pins are connected to the TI1 input (XOR combination) */
/**
  * @}
  */

/** @defgroup Channel_CC_State TIM Capture/Compare Channel State
  * @{
  */
#define TIM_CCx_ENABLE                   0x00000001U                            /*!< Input or output channel is enabled */
#define TIM_CCx_DISABLE                  0x00000000U                            /*!< Input or output channel is disabled */
#define TIM_CCxN_ENABLE                  0x00000004U                            /*!< Complementary output channel is enabled */
#define TIM_CCxN_DISABLE                 0x00000000U                            /*!< Complementary output channel is enabled */
/**
  * @}
  */

 /********************************************************************************************************/
/** @defgroup TIM_LL_EC_UPDATESOURCE Update Source
  * @{
  */
#define LL_TIM_UPDATESOURCE_REGULAR            0x00000000U                         /*!< Counter overflow/underflow, Setting the UG bit or Update generation through the slave mode controller generates an update request */
#define LL_TIM_UPDATESOURCE_COUNTER            (0x1 << TIMER_CR1_URS_POS)          /*!< Only counter overflow/underflow generates an update request */
/** @defgroup TIM_LL_EC_ONEPULSEMODE One Pulse Mode
  * @{
  */
#define LL_TIM_ONEPULSEMODE_SINGLE             (0x1 << TIMER_CR1_OPM_POS)           /*!< Counter stops counting at the next update event */
#define LL_TIM_ONEPULSEMODE_REPETITIVE         0x00000000U                          /*!< Counter is not stopped at update event */
/** @defgroup TIM_LL_EC_COUNTERMODE Counter Mode
  * @{
  */
#define LL_TIM_COUNTERMODE_UP                  0x00000000U                         /*!<Counter used as upcounter */
#define LL_TIM_COUNTERMODE_DOWN                (0x1 << TIMER_CR1_DIR_POS)          /*!< Counter used as downcounter */
#define LL_TIM_COUNTERMODE_CENTER_DOWN         (0x01 << TIMER_CR1_CMS_POS)         /*!< The counter counts up and down alternatively. Output compare interrupt flags of output channels  are set only when the counter is counting down. */
#define LL_TIM_COUNTERMODE_CENTER_UP           (0x10 << TIMER_CR1_CMS_POS)         /*!<The counter counts up and down alternatively. Output compare interrupt flags of output channels  are set only when the counter is counting up */
#define LL_TIM_COUNTERMODE_CENTER_UP_DOWN      (0x11 << TIMER_CR1_CMS_POS)         /*!< The counter counts up and down alternatively. Output compare interrupt flags of output channels  are set only when the counter is counting up or down. */
/** @defgroup TIM_LL_EC_CLOCKDIVISION Clock Division
  * @{
  */
#define LL_TIM_CLOCKDIVISION_DIV1              0x00000000U                        /*!< tDTS=tCK_INT */
#define LL_TIM_CLOCKDIVISION_DIV2              (0x01 << TIMER_CR1_CKD_POS)        /*!< tDTS=2*tCK_INT */
#define LL_TIM_CLOCKDIVISION_DIV4              (0x10 << TIMER_CR1_CKD_POS)        /*!< tDTS=4*tCK_INT */
/** @defgroup LL_TIM_InputCompare_CMPSEL1
  * @{
  */
#define LL_TIM_InputCompare_CMPSEL1            0x00000000U 
#define LL_TIM_InputCompare_CMPSEL2            (0x01 << TIMER_CR1_CMPSEL_POS)
#define LL_TIM_InputCompare_CMPSEL3            (0x10 << TIMER_CR1_CMPSEL_POS)
#define LL_TIM_InputCompare_CMPSEL4            (0x11 << TIMER_CR1_CMPSEL_POS)
/** @defgroup TIM_LL_EC_CCUPDATESOURCE Capture Compare  Update Source
  * @{
  */
#define LL_TIM_CCUPDATESOURCE_COMG_ONLY        0x00000000U                         /*!< Capture/compare control bits are updated by setting the COMG bit only */
#define LL_TIM_CCUPDATESOURCE_COMG_AND_TRGI    (0x1 << TIMER_CR2_CCUS_POS)         /*!< Capture/compare control bits are updated by setting the COMG bit or when a rising edge occurs on trigger input (TRGI) */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_CCDMAREQUEST Capture Compare DMA Request
  * @{
  */
#define LL_TIM_CCDMAREQUEST_CC                 0x00000000U                         /*!< CCx DMA request sent when CCx event occurs */
#define LL_TIM_CCDMAREQUEST_UPDATE             (0x1 << TIMER_CR2_CCDS_POS)         /*!< CCx DMA requests sent when update event occurs */
/** @defgroup TIM_LL_EC_LOCKLEVEL Lock Level
  * @{
  */
#define LL_TIM_LOCKLEVEL_OFF                   0x00000000U                        /*!< LOCK OFF - No bit is write protected */
#define LL_TIM_LOCKLEVEL_1                     (0x01 << TIMER_BDTR_LOCK_POS)      /*!< LOCK Level 1 */
#define LL_TIM_LOCKLEVEL_2                     (0x10 << TIMER_BDTR_LOCK_POS)      /*!< LOCK Level 2 */
#define LL_TIM_LOCKLEVEL_3                     (0x11 << TIMER_BDTR_LOCK_POS)      /*!< LOCK Level 3 */
/** @defgroup TIM_LL_EC_OCPOLARITY Output Configuration Polarity
  * @{
  */
#define LL_TIM_OCPOLARITY_HIGH                 0x00000000U                         /*!< OCxactive high*/
#define LL_TIM_OCPOLARITY_LOW                  (0x1 << TIMER_CCER_CC1P_POS)        /*!< OCxactive low*/
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OCIDLESTATE Output Configuration Idle State
  * @{
  */
#define LL_TIM_OCIDLESTATE_LOW                 0x00000000U                           /*!<OCx=0 (after a dead-time if OC is implemented) when MOE=0*/
#define LL_TIM_OCIDLESTATE_HIGH                (0x1 << TIMER_CR2_OIS1_POS)           /*!<OCx=1 (after a dead-time if OC is implemented) when MOE=0*/
//#endif /* USE_FULL_LL_DRIVER */

/** @defgroup TIM_LL_EC_OCMODE Output Configuration Mode
  * @{
  */
#define LL_TIM_OCMODE_FROZEN                   0x00000000U                                              /*!<The comparison between the output compare register TIMx_CCRy and the counter TIMx_CNT has no effect on the output channel level */
#define LL_TIM_OCMODE_ACTIVE                   (0x001 << TIMER_CCMR1_OC1M_POS)                                         /*!<OCyREF is forced high on compare match*/
#define LL_TIM_OCMODE_INACTIVE                 (0x010 << TIMER_CCMR1_OC1M_POS)                                        /*!<OCyREF is forced low on compare match*/
#define LL_TIM_OCMODE_TOGGLE                   (0x011 << TIMER_CCMR1_OC1M_POS)                    /*!<OCyREF toggles on compare match*/
#define LL_TIM_OCMODE_FORCED_INACTIVE          (0x100 << TIMER_CCMR1_OC1M_POS)                                        /*!<OCyREF is forced low*/
#define LL_TIM_OCMODE_FORCED_ACTIVE            (0x101 << TIMER_CCMR1_OC1M_POS)                    /*!<OCyREF is forced high*/
#define LL_TIM_OCMODE_PWM1                     (0x110 << TIMER_CCMR1_OC1M_POS)                    /*!<In upcounting, channel y is active as long as TIMx_CNT<TIMx_CCRy else inactive.  In downcounting, channel y is inactive as long as TIMx_CNT>TIMx_CCRy else active.*/
#define LL_TIM_OCMODE_PWM2                     (0x111 << TIMER_CCMR1_OC1M_POS) /*!<In upcounting, channel y is inactive as long as TIMx_CNT<TIMx_CCRy else active.  In downcounting, channel y is active as long as TIMx_CNT>TIMx_CCRy else inactive*/

/** @defgroup TIM_LL_EC_ACTIVEINPUT Active Input Selection
  * @{
  */
#define LL_TIM_ACTIVEINPUT_DIRECTTI            (0x01) /*!< ICx is mapped on TIx */
#define LL_TIM_ACTIVEINPUT_INDIRECTTI          (0x10) /*!< ICx is mapped on TIy */
#define LL_TIM_ACTIVEINPUT_TRC                 (0x11)   /*!< ICx is mapped on TRC */
/** @defgroup TIM_LL_EC_ICPSC Input Configuration Prescaler
  * @{
  */
#define LL_TIM_ICPSC_DIV1                      0x00000000U                    /*!< No prescaler, capture is done each time an edge is detected on the capture input */
#define LL_TIM_ICPSC_DIV2                      (0x01 << TIMER_CCMR1_IC1PSC_POS)    /*!< Capture is done once every 2 events */
#define LL_TIM_ICPSC_DIV4                      (0x10 << TIMER_CCMR1_IC1PSC_POS)    /*!< Capture is done once every 4 events */
#define LL_TIM_ICPSC_DIV8                      (0x11 << TIMER_CCMR1_IC1PSC_POS)      /*!< Capture is done once every 8 events */
/** @defgroup TIM_LL_EC_IC_FILTER Input Configuration Filter
  * @{
  */
#define LL_TIM_IC_FILTER_FDIV1                 0x00000000U                                          /*!< No filter, sampling is done at fDTS */
#define LL_TIM_IC_FILTER_FDIV1_N2              (0x0001 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fCK_INT, N=2 */
#define LL_TIM_IC_FILTER_FDIV1_N4              (0x0010 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fCK_INT, N=4 */
#define LL_TIM_IC_FILTER_FDIV1_N8              (0x0011 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fCK_INT, N=8 */
#define LL_TIM_IC_FILTER_FDIV2_N6              (0x0100 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/2, N=6 */
#define LL_TIM_IC_FILTER_FDIV2_N8              (0x0101 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/2, N=8 */
#define LL_TIM_IC_FILTER_FDIV4_N6              (0x0110 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/4, N=6 */
#define LL_TIM_IC_FILTER_FDIV4_N8              (0x0111 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/4, N=8 */
#define LL_TIM_IC_FILTER_FDIV8_N6              (0x1000 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/8, N=6 */
#define LL_TIM_IC_FILTER_FDIV8_N8              (0x1001 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/8, N=8 */
#define LL_TIM_IC_FILTER_FDIV16_N5             (0x1010 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/16, N=5 */
#define LL_TIM_IC_FILTER_FDIV16_N6             (0x1011 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/16, N=6 */
#define LL_TIM_IC_FILTER_FDIV16_N8             (0x1100 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/16, N=8 */
#define LL_TIM_IC_FILTER_FDIV32_N5             (0x1101 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/32, N=5 */
#define LL_TIM_IC_FILTER_FDIV32_N6             (0x1110 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/32, N=6 */
#define LL_TIM_IC_FILTER_FDIV32_N8             (0x1111 << TIMER_CCMR1_IC1F_POS)                     /*!< fSAMPLING=fDTS/32, N=8 */
/** @defgroup TIM_LL_EC_IC_POLARITY Input Configuration Polarity
  * @{
  */
#define LL_TIM_IC_POLARITY_RISING              0x00000000U                        /*!< The circuit is sensitive to TIxFP1 rising edge, TIxFP1 is not inverted */
#define LL_TIM_IC_POLARITY_FALLING             (0x1<<TIMER_CCER_CC1P_POS)                    /*!< The circuit is sensitive to TIxFP1 falling edge, TIxFP1 is inverted */
#define LL_TIM_IC_POLARITY_BOTHEDGE            (0x1<<TIMER_CCER_CC1NP_POS)        /*!< The circuit is sensitive to both TIxFP1 rising and falling edges, TIxFP1 is not inverted */
/** @defgroup TIM_LL_EC_CLOCKSOURCE Clock Source
  * @{
  */
#define LL_TIM_CLOCKSOURCE_INTERNAL            0x00000000U                                          /*!< The timer is clocked by the internal clock provided from the RCC */
#define LL_TIM_CLOCKSOURCE_EXT_MODE1           (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)   /*!< Counter counts at each rising or falling edge on a selected input*/
#define LL_TIM_CLOCKSOURCE_EXT_MODE2           TIM_SMCR_ECE                                         /*!< Counter counts at each rising or falling edge on the external trigger input ETR */
/** @defgroup TIM_LL_EC_TRGO Trigger Output
  * @{
  */
#define LL_TIM_TRGO_RESET                      0x00000000U                                     /*!< UG bit from the TIMx_EGR register is used as trigger output */
#define LL_TIM_TRGO_ENABLE                     TIM_CR2_MMS_0                                   /*!< Counter Enable signal (CNT_EN) is used as trigger output */
#define LL_TIM_TRGO_UPDATE                     TIM_CR2_MMS_1                                   /*!< Update event is used as trigger output */
#define LL_TIM_TRGO_CC1IF                      (TIM_CR2_MMS_1 | TIM_CR2_MMS_0)                 /*!< CC1 capture or a compare match is used as trigger output */
#define LL_TIM_TRGO_OC1REF                     TIM_CR2_MMS_2                                   /*!< OC1REF signal is used as trigger output */
#define LL_TIM_TRGO_OC2REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_0)                 /*!< OC2REF signal is used as trigger output */
#define LL_TIM_TRGO_OC3REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_1)                 /*!< OC3REF signal is used as trigger output */
#define LL_TIM_TRGO_OC4REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0) /*!< OC4REF signal is used as trigger output */
/** @defgroup TIM_LL_EC_TS Trigger Selection
  * @{
  */
#define LL_TIM_TS_ITR0                         0x00000000U                                                     /*!< Internal Trigger 0 (ITR0) is used as trigger input */
#define LL_TIM_TS_ITR1                         TIM_SMCR_TS_0                                                   /*!< Internal Trigger 1 (ITR1) is used as trigger input */
#define LL_TIM_TS_ITR2                         TIM_SMCR_TS_1                                                   /*!< Internal Trigger 2 (ITR2) is used as trigger input */
#define LL_TIM_TS_ITR3                         (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)                                 /*!< Internal Trigger 3 (ITR3) is used as trigger input */
#define LL_TIM_TS_TI1F_ED                      TIM_SMCR_TS_2                                                   /*!< TI1 Edge Detector (TI1F_ED) is used as trigger input */
#define LL_TIM_TS_TI1FP1                       (TIM_SMCR_TS_2 | TIM_SMCR_TS_0)                                 /*!< Filtered Timer Input 1 (TI1FP1) is used as trigger input */
#define LL_TIM_TS_TI2FP2                       (TIM_SMCR_TS_2 | TIM_SMCR_TS_1)                                 /*!< Filtered Timer Input 2 (TI12P2) is used as trigger input */
#define LL_TIM_TS_ETRF                         (TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0)                 /*!< Filtered external Trigger (ETRF) is used as trigger input */
/** @defgroup TIM_LL_EC_ETR_FILTER External Trigger Filter
  * @{
  */
#define LL_TIM_ETR_FILTER_FDIV1                0x00000000U                                          /*!< No filter, sampling is done at fDTS */
#define LL_TIM_ETR_FILTER_FDIV1_N2             TIM_SMCR_ETF_0                                       /*!< fSAMPLING=fCK_INT, N=2 */
#define LL_TIM_ETR_FILTER_FDIV1_N4             TIM_SMCR_ETF_1                                       /*!< fSAMPLING=fCK_INT, N=4 */
#define LL_TIM_ETR_FILTER_FDIV1_N8             (TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)                    /*!< fSAMPLING=fCK_INT, N=8 */
#define LL_TIM_ETR_FILTER_FDIV2_N6             TIM_SMCR_ETF_2                                       /*!< fSAMPLING=fDTS/2, N=6 */
#define LL_TIM_ETR_FILTER_FDIV2_N8             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)                    /*!< fSAMPLING=fDTS/2, N=8 */
#define LL_TIM_ETR_FILTER_FDIV4_N6             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)                    /*!< fSAMPLING=fDTS/4, N=6 */
#define LL_TIM_ETR_FILTER_FDIV4_N8             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)   /*!< fSAMPLING=fDTS/4, N=8 */
#define LL_TIM_ETR_FILTER_FDIV8_N6             TIM_SMCR_ETF_3                                       /*!< fSAMPLING=fDTS/8, N=8 */
#define LL_TIM_ETR_FILTER_FDIV8_N8             (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_0)                    /*!< fSAMPLING=fDTS/16, N=5 */
#define LL_TIM_ETR_FILTER_FDIV16_N5            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1)                    /*!< fSAMPLING=fDTS/16, N=6 */
#define LL_TIM_ETR_FILTER_FDIV16_N6            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)   /*!< fSAMPLING=fDTS/16, N=8 */
#define LL_TIM_ETR_FILTER_FDIV16_N8            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2)                    /*!< fSAMPLING=fDTS/16, N=5 */
#define LL_TIM_ETR_FILTER_FDIV32_N5            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)   /*!< fSAMPLING=fDTS/32, N=5 */
#define LL_TIM_ETR_FILTER_FDIV32_N6            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)   /*!< fSAMPLING=fDTS/32, N=6 */
#define LL_TIM_ETR_FILTER_FDIV32_N8            TIM_SMCR_ETF                                         /*!< fSAMPLING=fDTS/32, N=8 */
/** @defgroup TIM_LL_EC_BREAK_POLARITY break polarity
  * @{
  */
#define LL_TIM_BREAK_POLARITY_LOW              0x00000000U                              /*!< Break input BRK is active low */
#define LL_TIM_BREAK_POLARITY_HIGH             (0x1 << TIMER_BDTR_BKP_POS)              /*!< Break input BRK is active high */
/** @defgroup TIM_LL_EC_OSSI OSSI
  * @{
  */
#define LL_TIM_OSSI_DISABLE                    0x00000000U                            /*!< When inactive, OCx/OCxN outputs are disabled */
#define LL_TIM_OSSI_ENABLE                     (0x1 << TIMER_BDTR_OSSI_POS)           /*!< When inactive, OxC/OCxN outputs are first forced with their inactive level then forced to their idle level after the deadtime */
/**
  * @}
  */

/** @defgroup TIM_LL_EC_OSSR OSSR
  * @{
  */
#define LL_TIM_OSSR_DISABLE                    0x00000000U                            /*!< When inactive, OCx/OCxN outputs are disabled */
#define LL_TIM_OSSR_ENABLE                     (0x1 << TIMER_BDTR_OSSR_POS)           /*!< When inactive, OC/OCN outputs are enabled with their inactive level as soon as CCxE=1 or CCxNE=1 */
/**
  * @}
  */
/** @defgroup TIM_LL_EC_CHANNEL Channel
  * @{
  */
#define LL_TIM_CHANNEL_CH1                      (0x1 << TIMER_CCER_CC1E_POS)      /*!< Timer input/output channel 1 */
#define LL_TIM_CHANNEL_CH1N                     (0x1 << TIMER_CCER_CC1NE_POS)      /*!< Timer complementary output channel 1 */
#define LL_TIM_CHANNEL_CH2                      (0x1 << TIMER_CCER_CC2E_POS)      /*!< Timer input/output channel 2 */
#define LL_TIM_CHANNEL_CH2N                     (0x1 << TIMER_CCER_CC2NE_POS)      /*!< Timer complementary output channel 2 */
#define LL_TIM_CHANNEL_CH3                      (0x1 << TIMER_CCER_CC3E_POS)      /*!< Timer input/output channel 3 */
#define LL_TIM_CHANNEL_CH3N                     (0x1 << TIMER_CCER_CC3NE_POS)      /*!< Timer complementary output channel 3 */
#define LL_TIM_CHANNEL_CH4                      (0x1 << TIMER_CCER_CC4E_POS)      /*!< Timer input/output channel 4 */


/******************************************************************************
 External Function Definition
 ******************************************************************************/
/** @defgroup TIM_LL_Exported_Functions TIM Exported Functions
  * @{
  */

/** @defgroup TIM_LL_EF_Time_Base Time Base configuration
  * @{
  */
/**
  * @brief  Enable timer counter.
  * @rmtoll CR1          CEN           LL_TIM_EnableCounter
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCounter(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->CR1, TIMER_CR1_CEN_MASK);
}

/**
  * @brief  Disable timer counter.
  * @rmtoll CR1          CEN           LL_TIM_DisableCounter
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_DisableCounter(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIMER_CR1_CEN_MASK);
}

/**
  * @brief  Indicates whether the timer counter is enabled.
  * @rmtoll CR1          CEN           LL_TIM_IsEnabledCounter
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_IsEnabledCounter(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIMER_CR1_CEN_MASK) == (TIMER_CR1_CEN_MASK)) ? 1UL : 0UL);
}
/** @defgroup TIM_LL_Exported_Functions TIM Exported Functions
  * @{
  */

/** @defgroup TIM_LL_EF_Time_Base Time Base configuration
  * @{
  */
/**
  * @brief  Enable timer counter.
  * @rmtoll CR1          CEN           LL_TIM_EnableUpdateEvent
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableUpdateEvent(reg_timer_t *TIMx)
{
   CLEAR_BIT(TIMx->CR1, TIMER_CR1_UDIS_MASK);
}

/**
  * @brief  Disable timer counter.
  * @rmtoll CR1          CEN           LL_TIM_DisableUpdateEvent
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_DisableUpdateEvent(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->CR1, TIMER_CR1_UDIS_MASK);
}

/**
  * @brief  Indicates whether the timer counter is enabled.
  * @rmtoll CR1          CEN           LL_TIM_IsEnabledUpdateEvent
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_IsEnabledUpdateEvent(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIMER_CR1_UDIS_MASK) == (TIMER_CR1_UDIS_MASK)) ? 1UL : 0UL);
}
/**
  * @brief  Set update event source
  * @note Update event source set to LL_TIM_UPDATESOURCE_REGULAR: any of the following events
  *       generate an update interrupt or DMA request if enabled:
  *        - Counter overflow/underflow
  *        - Setting the UG bit
  *        - Update generation through the slave mode controller
  * @note Update event source set to LL_TIM_UPDATESOURCE_COUNTER: only counter
  *       overflow/underflow generates an update interrupt or DMA request if enabled.
  * @rmtoll CR1          URS           LL_TIM_SetUpdateSource
  * @param  TIMx Timer instance
  * @param  UpdateSource This parameter can be one of the following values:
  *         @arg @ref LL_TIM_UPDATESOURCE_REGULAR
  *         @arg @ref LL_TIM_UPDATESOURCE_COUNTER
  * @retval None
  */
static inline void LL_TIM_SetUpdateSource(reg_timer_t *TIMx, uint32_t UpdateSource)
{
  MODIFY_REG(TIMx->CR1, TIMER_CR1_URS_MASK, UpdateSource);
}

/**
  * @brief  Get actual event update source
  * @rmtoll CR1          URS           LL_TIM_GetUpdateSource
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_UPDATESOURCE_REGULAR
  *         @arg @ref LL_TIM_UPDATESOURCE_COUNTER
  */
static inline uint32_t LL_TIM_GetUpdateSource(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIMER_CR1_URS_MASK));
}
/**
  * @brief  Set one pulse mode (one shot v.s. repetitive).
  * @rmtoll CR1          OPM           LL_TIM_SetOnePulseMode
  * @param  TIMx Timer instance
  * @param  OnePulseMode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ONEPULSEMODE_SINGLE
  *         @arg @ref LL_TIM_ONEPULSEMODE_REPETITIVE
  * @retval None
  */
static inline void LL_TIM_SetOnePulseMode(reg_timer_t *TIMx, uint32_t OnePulseMode)
{
  MODIFY_REG(TIMx->CR1, TIMER_CR1_OPM_MASK, OnePulseMode);
}

/**
  * @brief  Get actual one pulse mode.
  * @rmtoll CR1          OPM           LL_TIM_GetOnePulseMode
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_ONEPULSEMODE_SINGLE
  *         @arg @ref LL_TIM_ONEPULSEMODE_REPETITIVE
  */
static inline uint32_t LL_TIM_GetOnePulseMode(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIMER_CR1_OPM_MASK));
}
/**
  * @brief  Set the timer counter counting mode.
  * @note Macro IS_TIM_COUNTER_MODE_SELECT_INSTANCE(TIMx) can be used to
  *       check whether or not the counter mode selection feature is supported
  *       by a timer instance.
  * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
  *       requires a timer reset to avoid unexpected direction
  *       due to DIR bit readonly in center aligned mode.
  * @rmtoll CR1          DIR           LL_TIM_SetCounterMode\n
  *         CR1          CMS           LL_TIM_SetCounterMode
  * @param  TIMx Timer instance
  * @param  CounterMode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_COUNTERMODE_UP
  *         @arg @ref LL_TIM_COUNTERMODE_DOWN
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_UP
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_DOWN
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_UP_DOWN
  * @retval None
  */
static inline void LL_TIM_SetCounterMode(reg_timer_t *TIMx, uint32_t CounterMode)
{
  MODIFY_REG(TIMx->CR1, (TIMER_CR1_DIR_MASK | TIMER_CR1_CMS_MASK), CounterMode);
}

/**
  * @brief  Get actual counter mode.
  * @note Macro IS_TIM_COUNTER_MODE_SELECT_INSTANCE(TIMx) can be used to
  *       check whether or not the counter mode selection feature is supported
  *       by a timer instance.
  * @rmtoll CR1          DIR           LL_TIM_GetCounterMode\n
  *         CR1          CMS           LL_TIM_GetCounterMode
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_COUNTERMODE_UP
  *         @arg @ref LL_TIM_COUNTERMODE_DOWN
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_UP
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_DOWN
  *         @arg @ref LL_TIM_COUNTERMODE_CENTER_UP_DOWN
  */
static inline uint32_t LL_TIM_GetCounterMode(reg_timer_t *TIMx)
{
  uint32_t counter_mode;

  counter_mode = (uint32_t)(READ_BIT(TIMx->CR1, TIMER_CR1_CMS_MASK));

  if (counter_mode == 0U)
  {
    counter_mode = (uint32_t)(READ_BIT(TIMx->CR1, TIMER_CR1_DIR_MASK));
  }

  return counter_mode;
}
/**
  * @brief  Enable auto-reload (ARR) preload.
  * @rmtoll CR1          ARPE          LL_TIM_EnableARRPreload
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableARRPreload(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->CR1, TIMER_CR1_ARPE_MASK);
}

/**
  * @brief  Disable auto-reload (ARR) preload.
  * @rmtoll CR1          ARPE          LL_TIM_DisableARRPreload
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_DisableARRPreload(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIMER_CR1_ARPE_MASK);
}

/**
  * @brief  Indicates whether auto-reload (ARR) preload is enabled.
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_IsEnabledARRPreload(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIMER_CR1_ARPE_MASK) == (TIMER_CR1_ARPE_MASK)) ? 1UL : 0UL);
}
/**
  * @brief  Set the division ratio between the timer clock  and the sampling clock used by the dead-time generators
  *         (when supported) and the digital filters.
  * @note Macro IS_TIM_CLOCK_DIVISION_INSTANCE(TIMx) can be used to check
  *       whether or not the clock division feature is supported by the timer
  *       instance.
  * @param  TIMx Timer instance
  * @param  ClockDivision This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV1
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV2
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV4
  * @retval None
  */
static inline void LL_TIM_SetClockDivision(reg_timer_t *TIMx, uint32_t ClockDivision)
{
  MODIFY_REG(TIMx->CR1, TIMER_CR1_CKD_MASK, ClockDivision);
}

/**
  * @brief  Get the actual division ratio between the timer clock  and the sampling clock used by the dead-time
  *         generators (when supported) and the digital filters.
  * @note Macro IS_TIM_CLOCK_DIVISION_INSTANCE(TIMx) can be used to check
  *       whether or not the clock division feature is supported by the timer
  *       instance.
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV1
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV2
  *         @arg @ref LL_TIM_CLOCKDIVISION_DIV4
  */
static inline uint32_t LL_TIM_GetClockDivision(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIMER_CR1_CKD_MASK));
}
/**
  * @brief  Set the division ratio between the timer clock  and the sampling clock used by the dead-time generators
  *         (when supported) and the digital filters.
  * @note Macro IS_TIM_CLOCK_DIVISION_INSTANCE(TIMx) can be used to check
  *       whether or not the clock division feature is supported by the timer
  *       instance.
  * @param  TIMx Timer instance
  * @param  InputCompare This parameter can be one of the following values:
  *         @arg @ref LL_TIM_InputCompare_CMPSEL1
  *         @arg @ref LL_TIM_InputCompare_CMPSEL2
  *         @arg @ref LL_TIM_InputCompare_CMPSEL3
  *         @arg @ref LL_TIM_InputCompare_CMPSEL4
  * @retval None
  */
static inline void LL_TIM_SetInputCompare(reg_timer_t *TIMx, uint32_t InputCompare)
{
  MODIFY_REG(TIMx->CR1, TIMER_CR1_CMPSEL_MASK, InputCompare);
}

/**
  * @brief  Get the actual division ratio between the timer clock  and the sampling clock used by the dead-time
  *         generators (when supported) and the digital filters.
  * @note Macro IS_TIM_CLOCK_DIVISION_INSTANCE(TIMx) can be used to check
  *       whether or not the clock division feature is supported by the timer
  *       instance.
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_InputCompare_CMPSEL1
  *         @arg @ref LL_TIM_InputCompare_CMPSEL2
  *         @arg @ref LL_TIM_InputCompare_CMPSEL3
  *         @arg @ref LL_TIM_InputCompare_CMPSEL4
  */
static inline uint32_t LL_TIM_GetInputCompare(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIMER_CR1_CMPSEL_MASK));
}
/**
  * @brief  Set the counter value.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @param  TIMx Timer instance
  * @param  Counter Counter value (between Min_Data=0 and Max_Data=0xFFFF or 0xFFFFFFFF)
  * @retval None
  */
static inline void LL_TIM_SetCounter(reg_timer_t *TIMx, uint32_t Counter)
{
  WRITE_REG(TIMx->CNT, Counter);
}

/**
  * @brief  Get the counter value.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @rmtoll CNT          CNT           LL_TIM_GetCounter
  * @param  TIMx Timer instance
  * @retval Counter value (between Min_Data=0 and Max_Data=0xFFFF or 0xFFFFFFFF)
  */
static inline uint32_t LL_TIM_GetCounter(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CNT));
}

/**
  * @brief  Get the current direction of the counter
  * @rmtoll CR1          DIR           LL_TIM_GetDirection
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_COUNTERDIRECTION_UP
  *         @arg @ref LL_TIM_COUNTERDIRECTION_DOWN
  */
static inline uint32_t LL_TIM_GetDirection(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIMER_CR1_DIR_MASK));
}
/**
  * @brief  Set the prescaler value.
  * @note The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
  * @note The prescaler can be changed on the fly as this control register is buffered. The new
  *       prescaler ratio is taken into account at the next update event.
  * @note Helper macro @ref __LL_TIM_CALC_PSC can be used to calculate the Prescaler parameter
  * @rmtoll PSC          PSC           LL_TIM_SetPrescaler
  * @param  TIMx Timer instance
  * @param  Prescaler between Min_Data=0 and Max_Data=65535
  * @retval None
  */
static inline void LL_TIM_SetPrescaler(reg_timer_t *TIMx, uint32_t Prescaler)
{
  WRITE_REG(TIMx->PSC, Prescaler);
}

/**
  * @brief  Get the prescaler value.
  * @rmtoll PSC          PSC           LL_TIM_GetPrescaler
  * @param  TIMx Timer instance
  * @retval  Prescaler value between Min_Data=0 and Max_Data=65535
  */
static inline uint32_t LL_TIM_GetPrescaler(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->PSC));
}

/**
  * @brief  Set the auto-reload value.
  * @note The counter is blocked while the auto-reload value is null.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Helper macro @ref __LL_TIM_CALC_ARR can be used to calculate the AutoReload parameter
  * @rmtoll ARR          ARR           LL_TIM_SetAutoReload
  * @param  TIMx Timer instance
  * @param  AutoReload between Min_Data=0 and Max_Data=65535
  * @retval None
  */
static inline void LL_TIM_SetAutoReload(reg_timer_t *TIMx, uint32_t AutoReload)
{
  WRITE_REG(TIMx->ARR, AutoReload);
}

/**
  * @brief  Get the auto-reload value.
  * @rmtoll ARR          ARR           LL_TIM_GetAutoReload
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @param  TIMx Timer instance
  * @retval Auto-reload value
  */
static inline uint32_t LL_TIM_GetAutoReload(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->ARR));
}

/**
  * @brief  Set the repetition counter value.
  * @note Macro IS_TIM_REPETITION_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a repetition counter.
  * @rmtoll RCR          REP           LL_TIM_SetRepetitionCounter
  * @param  TIMx Timer instance
  * @param  RepetitionCounter between Min_Data=0 and Max_Data=255 or 65535 for advanced timer.
  * @retval None
  */
static inline void LL_TIM_SetRepetitionCounter(reg_timer_t *TIMx, uint32_t RepetitionCounter)
{
  WRITE_REG(TIMx->REP, RepetitionCounter);
}

/**
  * @brief  Get the repetition counter value.
  * @note Macro IS_TIM_REPETITION_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a repetition counter.
  * @rmtoll RCR          REP           LL_TIM_GetRepetitionCounter
  * @param  TIMx Timer instance
  * @retval Repetition counter value
  */
static inline uint32_t LL_TIM_GetRepetitionCounter(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->REP));///////////////////////////////////////////////////////////////////////no
}
/**
  * @brief  Disable  the capture/compare control bits (CCxE, CCxNE and OCxM) preload.
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll CR2          CCPC          LL_TIM_CC_DisablePreload
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_CC_DisablePreload(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->CR2, TIMER_CR2_CCPC_MASK);
}

/**
  * @brief  Set the updated source of the capture/compare control bits (CCxE, CCxNE and OCxM).
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll CR2          CCUS          LL_TIM_CC_SetUpdate
  * @param  TIMx Timer instance
  * @param  CCUpdateSource This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CCUPDATESOURCE_COMG_ONLY
  *         @arg @ref LL_TIM_CCUPDATESOURCE_COMG_AND_TRGI
  * @retval None
  */
static inline void LL_TIM_CC_SetUpdate(reg_timer_t *TIMx, uint32_t CCUpdateSource)
{
  MODIFY_REG(TIMx->CR2, TIMER_CR2_CCUS_MASK, CCUpdateSource);
}

/**
  * @brief  Set the trigger of the capture/compare DMA request.
  * @rmtoll CR2          CCDS          LL_TIM_CC_SetDMAReqTrigger
  * @param  TIMx Timer instance
  * @param  DMAReqTrigger This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CCDMAREQUEST_CC
  *         @arg @ref LL_TIM_CCDMAREQUEST_UPDATE
  * @retval None
  */
static inline void LL_TIM_CC_SetDMAReqTrigger(reg_timer_t *TIMx, uint32_t DMAReqTrigger)
{
  MODIFY_REG(TIMx->CR2, TIMER_CR2_CCDS_MASK, DMAReqTrigger);
}

/**
  * @brief  Get actual trigger of the capture/compare DMA request.
  * @rmtoll CR2          CCDS          LL_TIM_CC_GetDMAReqTrigger
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_CCDMAREQUEST_CC
  *         @arg @ref LL_TIM_CCDMAREQUEST_UPDATE
  */
static inline uint32_t LL_TIM_CC_GetDMAReqTrigger(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR2, TIMER_CR2_CCDS_MASK));
}
/**
  * @brief  Set the lock level to freeze the
  *         configuration of several capture/compare parameters.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       the lock mechanism is supported by a timer instance.
  * @rmtoll BDTR         LOCK          LL_TIM_CC_SetLockLevel
  * @param  TIMx Timer instance
  * @param  LockLevel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_LOCKLEVEL_OFF
  *         @arg @ref LL_TIM_LOCKLEVEL_1
  *         @arg @ref LL_TIM_LOCKLEVEL_2
  *         @arg @ref LL_TIM_LOCKLEVEL_3
  * @retval None
  */
static inline void LL_TIM_CC_SetLockLevel(reg_timer_t *TIMx, uint32_t LockLevel)
{
  MODIFY_REG(TIMx->BDTR, TIMER_BDTR_LOCK_MASK, LockLevel);
}

/**
  * @brief  Enable capture/compare channels.
  * @rmtoll CCER         CC1E          LL_TIM_CC_EnableChannel\n
  *         CCER         CC1NE         LL_TIM_CC_EnableChannel\n
  *         CCER         CC2E          LL_TIM_CC_EnableChannel\n
  *         CCER         CC2NE         LL_TIM_CC_EnableChannel\n
  *         CCER         CC3E          LL_TIM_CC_EnableChannel\n
  *         CCER         CC3NE         LL_TIM_CC_EnableChannel\n
  *         CCER         CC4E          LL_TIM_CC_EnableChannel
  * @param  TIMx Timer instance
  * @param  Channels This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval None
  */
static inline void LL_TIM_CC_EnableChannel(reg_timer_t *TIMx, uint32_t Channels)
{
  SET_BIT(TIMx->CCER, Channels);
}
/**
  * @brief  Disable capture/compare channels.
  * @rmtoll CCER         CC1E          LL_TIM_CC_DisableChannel\n
  *         CCER         CC1NE         LL_TIM_CC_DisableChannel\n
  *         CCER         CC2E          LL_TIM_CC_DisableChannel\n
  *         CCER         CC2NE         LL_TIM_CC_DisableChannel\n
  *         CCER         CC3E          LL_TIM_CC_DisableChannel\n
  *         CCER         CC3NE         LL_TIM_CC_DisableChannel\n
  *         CCER         CC4E          LL_TIM_CC_DisableChannel
  * @param  TIMx Timer instance
  * @param  Channels This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval None
  */
static inline void LL_TIM_CC_DisableChannel(reg_timer_t *TIMx, uint32_t Channels)
{
  CLEAR_BIT(TIMx->CCER, Channels);
}

/**
  * @brief  Indicate whether channel(s) is(are) enabled.
  * @rmtoll CCER         CC1E          LL_TIM_CC_IsEnabledChannel\n
  *         CCER         CC1NE         LL_TIM_CC_IsEnabledChannel\n
  *         CCER         CC2E          LL_TIM_CC_IsEnabledChannel\n
  *         CCER         CC2NE         LL_TIM_CC_IsEnabledChannel\n
  *         CCER         CC3E          LL_TIM_CC_IsEnabledChannel\n
  *         CCER         CC3NE         LL_TIM_CC_IsEnabledChannel\n
  *         CCER         CC4E          LL_TIM_CC_IsEnabledChannel
  * @param  TIMx Timer instance
  * @param  Channels This parameter can be a combination of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_CC_IsEnabledChannel(reg_timer_t *TIMx, uint32_t Channels)
{
  return ((READ_BIT(TIMx->CCER, Channels) == (Channels)) ? 1UL : 0UL);
}
/**
  * @}
  */

/** @defgroup TIM_LL_EF_Output_Channel Output channel configuration
  * @{
  */
/**
  * @brief  Configure an output channel.
  * @rmtoll CCMR1        CC1S          LL_TIM_OC_ConfigOutput\n
  *         CCMR1        CC2S          LL_TIM_OC_ConfigOutput\n
  *         CCMR2        CC3S          LL_TIM_OC_ConfigOutput\n
  *         CCMR2        CC4S          LL_TIM_OC_ConfigOutput\n
  *         CCER         CC1P          LL_TIM_OC_ConfigOutput\n
  *         CCER         CC2P          LL_TIM_OC_ConfigOutput\n
  *         CCER         CC3P          LL_TIM_OC_ConfigOutput\n
  *         CCER         CC4P          LL_TIM_OC_ConfigOutput\n
  *         CR2          OIS1          LL_TIM_OC_ConfigOutput\n
  *         CR2          OIS2          LL_TIM_OC_ConfigOutput\n
  *         CR2          OIS3          LL_TIM_OC_ConfigOutput\n
  *         CR2          OIS4          LL_TIM_OC_ConfigOutput
  * @param  TIMx Timer instance
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_TIM_OCPOLARITY_HIGH or @ref LL_TIM_OCPOLARITY_LOW
  *         @arg @ref LL_TIM_OCIDLESTATE_LOW or @ref LL_TIM_OCIDLESTATE_HIGH
  * @retval None
  */
static inline void LL_TIM_OC_ConfigOutput(reg_timer_t *TIMx, uint32_t Configuration)
{
  CLEAR_BIT(TIMx->CCMR1, TIMER_CCMR1_CC1S_MASK);
  MODIFY_REG(TIMx->CCER, (TIMER_CCMR1_OC1PE_MASK),
             (Configuration & TIMER_CCMR1_OC1PE_MASK) << TIMER_CCMR1_CC1S_POS);
  MODIFY_REG(TIMx->CR2, (TIMER_CR2_OIS1_MASK ),
             (Configuration & TIMER_CR2_OIS1_MASK) << TIMER_CR2_OIS1_POS);
}

/**
  * @brief  Define the behavior of the output reference signal OCxREF from which
  *         OCx and OCxN (when relevant) are derived.
  * @rmtoll CCMR1        OC1M          LL_TIM_OC_SetMode\n
  *         CCMR1        OC2M          LL_TIM_OC_SetMode\n
  *         CCMR2        OC3M          LL_TIM_OC_SetMode\n
  *         CCMR2        OC4M          LL_TIM_OC_SetMode
  * @param  TIMx Timer instance
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OCMODE_FROZEN
  *         @arg @ref LL_TIM_OCMODE_ACTIVE
  *         @arg @ref LL_TIM_OCMODE_INACTIVE
  *         @arg @ref LL_TIM_OCMODE_TOGGLE
  *         @arg @ref LL_TIM_OCMODE_FORCED_INACTIVE
  *         @arg @ref LL_TIM_OCMODE_FORCED_ACTIVE
  *         @arg @ref LL_TIM_OCMODE_PWM1
  *         @arg @ref LL_TIM_OCMODE_PWM2
  * @retval None
  */
static inline void LL_TIM_OC_SetMode(reg_timer_t *TIMx, uint32_t Mode)//<< (TIMER_CCMR1_CC1S_MASK | TIMER_CCMR1_OC1M_MASK)
{
  MODIFY_REG(TIMx->CCMR1, (TIMER_CCMR1_OC1M_MASK  | TIMER_CCMR1_CC1S_MASK), Mode );
}

/**
  * @brief  Get the output compare mode of an output channel.
  * @rmtoll CCMR1        OC1M          LL_TIM_OC_GetMode\n
  *         CCMR1        OC2M          LL_TIM_OC_GetMode\n
  *         CCMR2        OC3M          LL_TIM_OC_GetMode\n
  *         CCMR2        OC4M          LL_TIM_OC_GetMode
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_OCMODE_FROZEN
  *         @arg @ref LL_TIM_OCMODE_ACTIVE
  *         @arg @ref LL_TIM_OCMODE_INACTIVE
  *         @arg @ref LL_TIM_OCMODE_TOGGLE
  *         @arg @ref LL_TIM_OCMODE_FORCED_INACTIVE
  *         @arg @ref LL_TIM_OCMODE_FORCED_ACTIVE
  *         @arg @ref LL_TIM_OCMODE_PWM1
  *         @arg @ref LL_TIM_OCMODE_PWM2
  */
static inline uint32_t LL_TIM_OC_GetMode(reg_timer_t *TIMx)
{
  return (READ_BIT(TIMx->CCMR1, TIMER_CCMR1_OC1M_MASK | TIMER_CCMR1_CC1S_MASK));
}
/**
  * @brief  Set the polarity of an output channel.
  * @rmtoll CCER         CC1P          LL_TIM_OC_SetPolarity\n
  *         CCER         CC1NP         LL_TIM_OC_SetPolarity\n
  *         CCER         CC2P          LL_TIM_OC_SetPolarity\n
  *         CCER         CC2NP         LL_TIM_OC_SetPolarity\n
  *         CCER         CC3P          LL_TIM_OC_SetPolarity\n
  *         CCER         CC3NP         LL_TIM_OC_SetPolarity\n
  *         CCER         CC4P          LL_TIM_OC_SetPolarity
  * @param  TIMx Timer instance
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OCPOLARITY_HIGH
  *         @arg @ref LL_TIM_OCPOLARITY_LOW
  * @retval None
  */
static inline void LL_TIM_OC_SetPolarity(reg_timer_t *TIMx, uint32_t Polarity)
{
  MODIFY_REG(TIMx->CCER, (TIMER_CCER_CC1P_MASK ),  Polarity << TIMER_CCER_CC1P_POS);
}

/**
  * @brief  Get the polarity of an output channel.
  * @rmtoll CCER         CC1P          LL_TIM_OC_GetPolarity\n
  *         CCER         CC1NP         LL_TIM_OC_GetPolarity\n
  *         CCER         CC2P          LL_TIM_OC_GetPolarity\n
  *         CCER         CC2NP         LL_TIM_OC_GetPolarity\n
  *         CCER         CC3P          LL_TIM_OC_GetPolarity\n
  *         CCER         CC3NP         LL_TIM_OC_GetPolarity\n
  *         CCER         CC4P          LL_TIM_OC_GetPolarity
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_OCPOLARITY_HIGH
  *         @arg @ref LL_TIM_OCPOLARITY_LOW
  */
static inline uint32_t LL_TIM_OC_GetPolarity(reg_timer_t *TIMx)
{
  return (READ_BIT(TIMx->CCER, TIMER_CCER_CC1P_MASK ));
}
/**
  * @brief  Set the IDLE state of an output channel
  * @note This function is significant only for the timer instances
  *       supporting the break feature. Macro IS_TIM_BREAK_INSTANCE(TIMx)
  *       can be used to check whether or not a timer instance provides
  *       a break input.
  * @rmtoll CR2         OIS1          LL_TIM_OC_SetIdleState\n
  *         CR2         OIS1N         LL_TIM_OC_SetIdleState\n
  *         CR2         OIS2          LL_TIM_OC_SetIdleState\n
  *         CR2         OIS2N         LL_TIM_OC_SetIdleState\n
  *         CR2         OIS3          LL_TIM_OC_SetIdleState\n
  *         CR2         OIS3N         LL_TIM_OC_SetIdleState\n
  *         CR2         OIS4          LL_TIM_OC_SetIdleState
  * @param  TIMx Timer instance
  * @param  IdleState This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OCIDLESTATE_LOW
  *         @arg @ref LL_TIM_OCIDLESTATE_HIGH
  * @retval None
  */
static inline void LL_TIM_OC_SetIdleState(reg_timer_t *TIMx, uint32_t IdleState)
{
  MODIFY_REG(TIMx->CR2, TIMER_CR2_OIS1_MASK ,  IdleState);
}

/**
  * @brief  Get the IDLE state of an output channel
  * @rmtoll CR2         OIS1          LL_TIM_OC_GetIdleState\n
  *         CR2         OIS1N         LL_TIM_OC_GetIdleState\n
  *         CR2         OIS2          LL_TIM_OC_GetIdleState\n
  *         CR2         OIS2N         LL_TIM_OC_GetIdleState\n
  *         CR2         OIS3          LL_TIM_OC_GetIdleState\n
  *         CR2         OIS3N         LL_TIM_OC_GetIdleState\n
  *         CR2         OIS4          LL_TIM_OC_GetIdleState
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_OCIDLESTATE_LOW
  *         @arg @ref LL_TIM_OCIDLESTATE_HIGH
  */
static inline uint32_t LL_TIM_OC_GetIdleState(reg_timer_t *TIMx)
{
  return (READ_BIT(TIMx->CR2, TIMER_CR2_OIS1_MASK));
}
/**
  * @brief  Enable fast mode for the output channel.
  * @note Acts only if the channel is configured in PWM1 or PWM2 mode.
  * @rmtoll CCMR1        OC1FE          LL_TIM_OC_EnableFast\n
  *         CCMR1        OC2FE          LL_TIM_OC_EnableFast\n
  *         CCMR2        OC3FE          LL_TIM_OC_EnableFast\n
  *         CCMR2        OC4FE          LL_TIM_OC_EnableFast
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval None
  */
static inline void LL_TIM_OC_EnableFast(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->CCMR1, (TIMER_CCMR1_OC1FE_MASK << TIMER_CCMR1_OC1FE_POS));
}

/**
  * @brief  Disable fast mode for the output channel.
  * @rmtoll CCMR1        OC1FE          LL_TIM_OC_DisableFast\n
  *         CCMR1        OC2FE          LL_TIM_OC_DisableFast\n
  *         CCMR2        OC3FE          LL_TIM_OC_DisableFast\n
  *         CCMR2        OC4FE          LL_TIM_OC_DisableFast
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval None
  */
static inline void LL_TIM_OC_DisableFast(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->CCMR1, (TIMER_CCMR1_OC1FE_MASK << TIMER_CCMR1_OC1FE_POS));
}

/**
  * @brief  Indicates whether fast mode is enabled for the output channel.
  * @rmtoll CCMR1        OC1FE          LL_TIM_OC_IsEnabledFast\n
  *         CCMR1        OC2FE          LL_TIM_OC_IsEnabledFast\n
  *         CCMR2        OC3FE          LL_TIM_OC_IsEnabledFast\n
  *         CCMR2        OC4FE          LL_TIM_OC_IsEnabledFast\n
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_OC_IsEnabledFast(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->CCMR1, TIMER_CCMR1_OC1FE_MASK) == TIMER_CCMR1_OC1FE_MASK) ? 1UL : 0UL);
}
/**
  * @brief  Enable compare register (TIMx_CCRx) preload for the output channel.
  * @rmtoll CCMR1        OC1PE          LL_TIM_OC_EnablePreload\n
  *         CCMR1        OC2PE          LL_TIM_OC_EnablePreload\n
  *         CCMR2        OC3PE          LL_TIM_OC_EnablePreload\n
  *         CCMR2        OC4PE          LL_TIM_OC_EnablePreload
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @retval None
  */
static inline void LL_TIM_OC_EnablePreload(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->CCMR1, (TIMER_CCMR1_OC1PE_MASK << TIMER_CCMR1_OC1PE_POS));
}

/**
  * @brief  Disable compare register (TIMx_CCRx) preload for the output channel.
  * @rmtoll CCMR1        OC1PE          LL_TIM_OC_DisablePreload\n
  *         CCMR1        OC2PE          LL_TIM_OC_DisablePreload\n
  *         CCMR2        OC3PE          LL_TIM_OC_DisablePreload\n
  *         CCMR2        OC4PE          LL_TIM_OC_DisablePreload
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_OC_DisablePreload(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->CCMR1, (TIMER_CCMR1_OC1PE_MASK << TIMER_CCMR1_OC1PE_POS));
}

/**
  * @brief  Indicates whether compare register (TIMx_CCRx) preload is enabled for the output channel.
  * @rmtoll CCMR1        OC1PE          LL_TIM_OC_IsEnabledPreload\n
  *         CCMR1        OC2PE          LL_TIM_OC_IsEnabledPreload\n
  *         CCMR2        OC3PE          LL_TIM_OC_IsEnabledPreload\n
  *         CCMR2        OC4PE          LL_TIM_OC_IsEnabledPreload\n
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_OC_IsEnabledPreload(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->CCMR1, TIMER_CCMR1_OC1PE_MASK) == TIMER_CCMR1_OC1PE_MASK) );
}
/**
  * @brief  Enable clearing the output channel on an external event.
  * @note This function can only be used in Output compare and PWM modes. It does not work in Forced mode.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll CCMR1        OC1CE          LL_TIM_OC_EnableClear\n
  *         CCMR1        OC2CE          LL_TIM_OC_EnableClear\n
  *         CCMR2        OC3CE          LL_TIM_OC_EnableClear\n
  *         CCMR2        OC4CE          LL_TIM_OC_EnableClear
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_OC_EnableClear(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->CCMR1, TIMER_CCMR1_OC1CE_MASK);
}

/**
  * @brief  Disable clearing the output channel on an external event.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll CCMR1        OC1CE          LL_TIM_OC_DisableClear\n
  *         CCMR1        OC2CE          LL_TIM_OC_DisableClear\n
  *         CCMR2        OC3CE          LL_TIM_OC_DisableClear\n
  *         CCMR2        OC4CE          LL_TIM_OC_DisableClear
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_OC_DisableClear(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->CCMR1, (TIMER_CCMR1_OC1CE_MASK ));
}

/**
  * @brief  Indicates clearing the output channel on an external event is enabled for the output channel.
  * @note This function enables clearing the output channel on an external event.
  * @note This function can only be used in Output compare and PWM modes. It does not work in Forced mode.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll CCMR1        OC1CE          LL_TIM_OC_IsEnabledClear\n
  *         CCMR1        OC2CE          LL_TIM_OC_IsEnabledClear\n
  *         CCMR2        OC3CE          LL_TIM_OC_IsEnabledClear\n
  *         CCMR2        OC4CE          LL_TIM_OC_IsEnabledClear\n
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_OC_IsEnabledClear(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->CCMR1, TIMER_CCMR1_OC1CE_MASK) == TIMER_CCMR1_OC1CE_MASK));
}
/**
  * @brief  Set the dead-time delay (delay inserted between the rising edge of the OCxREF signal and the rising edge of
  *         the Ocx and OCxN signals).
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       dead-time insertion feature is supported by a timer instance.
  * @note Helper macro @ref __LL_TIM_CALC_DEADTIME can be used to calculate the DeadTime parameter
  * @rmtoll BDTR         DTG           LL_TIM_OC_SetDeadTime
  * @param  TIMx Timer instance
  * @param  DeadTime between Min_Data=0 and Max_Data=255
  * @retval None
  */
static inline void LL_TIM_OC_SetDeadTime(reg_timer_t *TIMx, uint32_t DeadTime)
{
  MODIFY_REG(TIMx->BDTR, TIMER_BDTR_DTG_MASK, DeadTime);
}

/**
  * @brief  Set compare value for output channel 1 (TIMx_CCR1).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 1 is supported by a timer instance.
  * @rmtoll CCR1         CCR1          LL_TIM_OC_SetCompareCH1
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
static inline void LL_TIM_OC_SetCompareCH1(reg_timer_t *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR1, CompareValue);
}

/**
  * @brief  Set compare value for output channel 2 (TIMx_CCR2).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 2 is supported by a timer instance.
  * @rmtoll CCR2         CCR2          LL_TIM_OC_SetCompareCH2
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
static inline void LL_TIM_OC_SetCompareCH2(reg_timer_t *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR2, CompareValue);
}

/**
  * @brief  Set compare value for output channel 3 (TIMx_CCR3).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(TIMx) can be used to check whether or not
  *       output channel is supported by a timer instance.
  * @rmtoll CCR3         CCR3          LL_TIM_OC_SetCompareCH3
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
static inline void LL_TIM_OC_SetCompareCH3(reg_timer_t *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR3, CompareValue);
}

/**
  * @brief  Set compare value for output channel 4 (TIMx_CCR4).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 4 is supported by a timer instance.
  * @rmtoll CCR4         CCR4          LL_TIM_OC_SetCompareCH4
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
static inline void LL_TIM_OC_SetCompareCH4(reg_timer_t *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR4, CompareValue);
}

/**
  * @brief  Get compare value (TIMx_CCR1) set for  output channel 1.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 1 is supported by a timer instance.
  * @rmtoll CCR1         CCR1          LL_TIM_OC_GetCompareCH1
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
static inline uint32_t LL_TIM_OC_GetCompareCH1(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR1));
}
/**
  * @brief  Get compare value (TIMx_CCR2) set for  output channel 2.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 2 is supported by a timer instance.
  * @rmtoll CCR2         CCR2          LL_TIM_OC_GetCompareCH2
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
static inline uint32_t LL_TIM_OC_GetCompareCH2(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR2));
}

/**
  * @brief  Get compare value (TIMx_CCR3) set for  output channel 3.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 3 is supported by a timer instance.
  * @rmtoll CCR3         CCR3          LL_TIM_OC_GetCompareCH3
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
static inline uint32_t LL_TIM_OC_GetCompareCH3(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR3));
}

/**
  * @brief  Get compare value (TIMx_CCR4) set for  output channel 4.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 4 is supported by a timer instance.
  * @rmtoll CCR4         CCR4          LL_TIM_OC_GetCompareCH4
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
static inline uint32_t LL_TIM_OC_GetCompareCH4(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR4));
}
/** @defgroup TIM_LL_EF_Input_Channel Input channel configuration
  * @{
  */
/**
  * @brief  Configure input channel.
  * @rmtoll CCMR1        CC1S          LL_TIM_IC_Config\n
  *         CCMR1        IC1PSC        LL_TIM_IC_Config\n
  *         CCMR1        IC1F          LL_TIM_IC_Config\n
  *         CCMR1        CC2S          LL_TIM_IC_Config\n
  *         CCMR1        IC2PSC        LL_TIM_IC_Config\n
  *         CCMR1        IC2F          LL_TIM_IC_Config\n
  *         CCMR2        CC3S          LL_TIM_IC_Config\n
  *         CCMR2        IC3PSC        LL_TIM_IC_Config\n
  *         CCMR2        IC3F          LL_TIM_IC_Config\n
  *         CCMR2        CC4S          LL_TIM_IC_Config\n
  *         CCMR2        IC4PSC        LL_TIM_IC_Config\n
  *         CCMR2        IC4F          LL_TIM_IC_Config\n
  *         CCER         CC1P          LL_TIM_IC_Config\n
  *         CCER         CC1NP         LL_TIM_IC_Config\n
  *         CCER         CC2P          LL_TIM_IC_Config\n
  *         CCER         CC2NP         LL_TIM_IC_Config\n
  *         CCER         CC3P          LL_TIM_IC_Config\n
  *         CCER         CC3NP         LL_TIM_IC_Config\n
  *         CCER         CC4P          LL_TIM_IC_Config\n
  *         CCER         CC4NP         LL_TIM_IC_Config
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH4
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref LL_TIM_ACTIVEINPUT_DIRECTTI or @ref LL_TIM_ACTIVEINPUT_INDIRECTTI or @ref LL_TIM_ACTIVEINPUT_TRC
  *         @arg @ref LL_TIM_ICPSC_DIV1 or ... or @ref LL_TIM_ICPSC_DIV8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1 or ... or @ref LL_TIM_IC_FILTER_FDIV32_N8
  *         @arg @ref LL_TIM_IC_POLARITY_RISING or @ref LL_TIM_IC_POLARITY_FALLING or @ref LL_TIM_IC_POLARITY_BOTHEDGE
  * @retval None
  */
static inline void LL_TIM_IC_Config(reg_timer_t *TIMx, uint32_t Configuration)
{
  MODIFY_REG(TIMx->CCMR1, (TIMER_CCMR1_IC1F_MASK | TIMER_CCMR1_IC1F_MASK | TIMER_CCMR1_CC1S_MASK),Configuration);
  MODIFY_REG(TIMx->CCER, (TIMER_CCER_CC1NP_MASK | TIMER_CCER_CC1P_MASK),Configuration);
}

/**
  * @brief  Set the active input.
  * @rmtoll CCMR1        CC1S          LL_TIM_IC_SetActiveInput\n
  *         CCMR1        CC2S          LL_TIM_IC_SetActiveInput\n
  *         CCMR2        CC3S          LL_TIM_IC_SetActiveInput\n
  *         CCMR2        CC4S          LL_TIM_IC_SetActiveInput
  * @param  TIMx Timer instance
  * @param  ICActiveInput This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ACTIVEINPUT_DIRECTTI
  *         @arg @ref LL_TIM_ACTIVEINPUT_INDIRECTTI
  *         @arg @ref LL_TIM_ACTIVEINPUT_TRC
  * @retval None
  */
static inline void LL_TIM_IC_SetActiveInput(reg_timer_t *TIMx, uint32_t ICActiveInput)
{
  MODIFY_REG(TIMx->CCMR1, TIMER_CCMR1_CC1S_MASK, ICActiveInput);
}

/**
  * @brief  Get the current active input.
  * @rmtoll CCMR1        CC1S          LL_TIM_IC_GetActiveInput\n
  *         CCMR1        CC2S          LL_TIM_IC_GetActiveInput\n
  *         CCMR2        CC3S          LL_TIM_IC_GetActiveInput\n
  *         CCMR2        CC4S          LL_TIM_IC_GetActiveInput
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_ACTIVEINPUT_DIRECTTI
  *         @arg @ref LL_TIM_ACTIVEINPUT_INDIRECTTI
  *         @arg @ref LL_TIM_ACTIVEINPUT_TRC
  */
static inline uint32_t LL_TIM_IC_GetActiveInput(reg_timer_t *TIMx)
{
  return (READ_BIT(TIMx->CCMR1, TIMER_CCMR1_CC1S_MASK));
}
/**
  * @brief  Set the prescaler of input channel.
  * @rmtoll CCMR1        IC1PSC        LL_TIM_IC_SetPrescaler\n
  *         CCMR1        IC2PSC        LL_TIM_IC_SetPrescaler\n
  *         CCMR2        IC3PSC        LL_TIM_IC_SetPrescaler\n
  *         CCMR2        IC4PSC        LL_TIM_IC_SetPrescaler
  * @param  TIMx Timer instance
  * @param  ICPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ICPSC_DIV1
  *         @arg @ref LL_TIM_ICPSC_DIV2
  *         @arg @ref LL_TIM_ICPSC_DIV4
  *         @arg @ref LL_TIM_ICPSC_DIV8
  * @retval None
  */
static inline void LL_TIM_IC_SetPrescaler(reg_timer_t *TIMx,  uint32_t ICPrescaler)
{
  MODIFY_REG(TIMx->CCMR1, TIMER_CCMR1_IC1PSC_MASK , ICPrescaler);
}

/**
  * @brief  Get the current prescaler value acting on an  input channel.
  * @rmtoll CCMR1        IC1PSC        LL_TIM_IC_GetPrescaler\n
  *         CCMR1        IC2PSC        LL_TIM_IC_GetPrescaler\n
  *         CCMR2        IC3PSC        LL_TIM_IC_GetPrescaler\n
  *         CCMR2        IC4PSC        LL_TIM_IC_GetPrescaler
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_TIM_ICPSC_DIV1
  *         @arg @ref LL_TIM_ICPSC_DIV2
  *         @arg @ref LL_TIM_ICPSC_DIV4
  *         @arg @ref LL_TIM_ICPSC_DIV8
  */
static inline uint32_t LL_TIM_IC_GetPrescaler(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CCMR1, TIMER_CCMR1_IC1PSC_MASK));
}
/**
  * @brief  Set the prescaler of input channel.
  * @rmtoll CCMR1        IC1PSC        LL_TIM_IC_SetFilter\n
  *         CCMR1        IC2PSC        LL_TIM_IC_SetFilter\n
  *         CCMR2        IC3PSC        LL_TIM_IC_SetFilter\n
  *         CCMR2        IC4PSC        LL_TIM_IC_SetFilter
  * @param  TIMx Timer instance
  * @param  ICFilter This parameter can be one of the following values:
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N8
  * @retval None
  */
static inline void LL_TIM_IC_SetFilter(reg_timer_t *TIMx,  uint32_t ICFilter)
{
  MODIFY_REG(TIMx->CCMR1, TIMER_CCMR1_IC1F_MASK , ICFilter);
}

/**
  * @brief  Get the current prescaler value acting on an  input channel.
  * @rmtoll CCMR1        IC1PSC        LL_TIM_IC_GetFilter\n
  *         CCMR1        IC2PSC        LL_TIM_IC_GetPrescaler\n
  *         CCMR2        IC3PSC        LL_TIM_IC_GetPrescaler\n
  *         CCMR2        IC4PSC        LL_TIM_IC_GetPrescaler
  * @param  TIMx Timer instance
  * @param  ICFilter This parameter can be one of the following values:
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_IC_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_IC_FILTER_FDIV32_N8
  */
static inline uint32_t LL_TIM_IC_GetFilter(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CCMR1, TIMER_CCMR1_IC1F_MASK));
}
/**
  * @brief  Set the prescaler of input channel.
  * @rmtoll CCMR1        IC1PSC        LL_TIM_IC_SetFilter\n
  *         CCMR1        IC2PSC        LL_TIM_IC_SetFilter\n
  *         CCMR2        IC3PSC        LL_TIM_IC_SetFilter\n
  *         CCMR2        IC4PSC        LL_TIM_IC_SetFilter
  * @param  TIMx Timer instance
  * @param  ICPolarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_IC_POLARITY_RISING
  *         @arg @ref LL_TIM_IC_POLARITY_FALLING
  *         @arg @ref LL_TIM_IC_POLARITY_BOTHEDGE
  * @retval None
  */
static inline void LL_TIM_IC_SetPolarity(reg_timer_t *TIMx,  uint32_t ICPolarity)/////////////////////////////////
{
  MODIFY_REG(TIMx->CCER, TIMER_CCER_CC1P_MASK | TIMER_CCER_CC1NP_MASK , ICPolarity);
}

/**
  * @brief  Get the current prescaler value acting on an  input channel.
  * @rmtoll CCMR1        IC1PSC        LL_TIM_IC_GetPolarity\n
  *         CCMR1        IC2PSC        LL_TIM_IC_GetPolarity\n
  *         CCMR2        IC3PSC        LL_TIM_IC_GetPolarity\n
  *         CCMR2        IC4PSC        LL_TIM_IC_GetPolarity
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  */
static inline uint32_t LL_TIM_IC_GetPolarity(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CCER, TIMER_CCER_CC1P_MASK | TIMER_CCER_CC1NP_MASK));
}
/**
  * @brief  Connect the TIMx_CH1, CH2 and CH3 pins  to the TI1 input (XOR combination).
  * @note Macro IS_TIM_XOR_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an XOR input.
  * @rmtoll CR2          TI1S          LL_TIM_IC_EnableXORCombination
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_IC_EnableXORCombination(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->CR2, TIMER_CR2_TI1S_MASK);
}

/**
  * @brief  Disconnect the TIMx_CH1, CH2 and CH3 pins  from the TI1 input.
  * @note Macro IS_TIM_XOR_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an XOR input.
  * @rmtoll CR2          TI1S          LL_TIM_IC_DisableXORCombination
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_IC_DisableXORCombination(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->CR2, TIMER_CR2_TI1S_MASK);
}

/**
  * @brief  Indicates whether the TIMx_CH1, CH2 and CH3 pins are connectected to the TI1 input.
  * @note Macro IS_TIM_XOR_INSTANCE(TIMx) can be used to check whether or not
  * a timer instance provides an XOR input.
  * @rmtoll CR2          TI1S          LL_TIM_IC_IsEnabledXORCombination
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_IC_IsEnabledXORCombination(reg_timer_t *TIMx)
{
  return (READ_BIT(TIMx->CR2, TIMER_CR2_TI1S_MASK));
}
/**
  * @brief  Get captured value for input channel 1.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(TIMx) can be used to check whether or not
  *       input channel 1 is supported by a timer instance.
  * @rmtoll CCR1         CCR1          LL_TIM_IC_GetCaptureCH1
  * @param  TIMx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
static inline uint32_t LL_TIM_IC_GetCaptureCH1(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR1));
}

/**
  * @brief  Get captured value for input channel 2.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(TIMx) can be used to check whether or not
  *       input channel 2 is supported by a timer instance.
  * @rmtoll CCR2         CCR2          LL_TIM_IC_GetCaptureCH2
  * @param  TIMx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
static inline uint32_t LL_TIM_IC_GetCaptureCH2(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR2));
}

/**
  * @brief  Get captured value for input channel 3.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(TIMx) can be used to check whether or not
  *       input channel 3 is supported by a timer instance.
  * @rmtoll CCR3         CCR3          LL_TIM_IC_GetCaptureCH3
  * @param  TIMx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
static inline uint32_t LL_TIM_IC_GetCaptureCH3(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR3));
}

/**
  * @brief  Get captured value for input channel 4.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(TIMx) can be used to check whether or not
  *       input channel 4 is supported by a timer instance.
  * @rmtoll CCR4         CCR4          LL_TIM_IC_GetCaptureCH4
  * @param  TIMx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
static inline uint32_t LL_TIM_IC_GetCaptureCH4(reg_timer_t *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR4));
}
/** @defgroup TIM_LL_EF_Clock_Selection Counter clock selection
  * @{
  */
/**
  * @brief  Enable external clock mode 2.
  * @note When external clock mode 2 is enabled the counter is clocked by any active edge on the ETRF signal.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll SMCR         ECE           LL_TIM_EnableExternalClock
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableExternalClock(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->SMCR, TIMER_SMCR_ECE_MASK);
}

/**
  * @brief  Disable external clock mode 2.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll SMCR         ECE           LL_TIM_DisableExternalClock
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_DisableExternalClock(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->SMCR, TIMER_SMCR_ECE_MASK);
}

/**
  * @brief  Indicate whether external clock mode 2 is enabled.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll SMCR         ECE           LL_TIM_IsEnabledExternalClock
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_IsEnabledExternalClock(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->SMCR, TIMER_SMCR_ECE_MASK) == (TIMER_SMCR_ECE_MASK)) ? 1UL : 0UL);
}
/**
  * @brief  Set the clock source of the counter clock.
  * @note when selected clock source is external clock mode 1, the timer input
  *       the external clock is applied is selected by calling the @ref LL_TIM_SetTriggerInput()
  *       function. This timer input must be configured by calling
  *       the @ref LL_TIM_IC_Config() function.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode1.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll SMCR         SMS           LL_TIM_SetClockSource\n
  *         SMCR         ECE           LL_TIM_SetClockSource
  * @param  TIMx Timer instance
  * @param  ClockSource This parameter can be one of the following values:
  *         @arg @ref LL_TIM_CLOCKSOURCE_INTERNAL
  *         @arg @ref LL_TIM_CLOCKSOURCE_EXT_MODE1
  *         @arg @ref LL_TIM_CLOCKSOURCE_EXT_MODE2
  * @retval None
  */
static inline void LL_TIM_SetClockSource(reg_timer_t *TIMx, uint32_t ClockSource)
{
  MODIFY_REG(TIMx->SMCR, TIMER_SMCR_SMS_MASK | TIMER_SMCR_ECE_MASK, ClockSource);
}

/**
  * @brief  Set the encoder interface mode.
  * @note Macro IS_TIM_ENCODER_INTERFACE_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports the encoder mode.
  * @rmtoll SMCR         SMS           LL_TIM_SetEncoderMode
  * @param  TIMx Timer instance
  * @param  EncoderMode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ENCODERMODE_X2_TI1
  *         @arg @ref LL_TIM_ENCODERMODE_X2_TI2
  *         @arg @ref LL_TIM_ENCODERMODE_X4_TI12
  * @retval None
  */
static inline void LL_TIM_SetEncoderMode(reg_timer_t *TIMx, uint32_t EncoderMode)
{
  MODIFY_REG(TIMx->SMCR, TIMER_SMCR_SMS_MASK, EncoderMode);
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_Timer_Synchronization Timer synchronisation configuration
  * @{
  */
/**
  * @brief  Set the trigger output (TRGO) used for timer synchronization .
  * @note Macro IS_TIM_MASTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance can operate as a master timer.
  * @rmtoll CR2          MMS           LL_TIM_SetTriggerOutput
  * @param  TIMx Timer instance
  * @param  TimerSynchronization This parameter can be one of the following values:
  *         @arg @ref LL_TIM_TRGO_RESET
  *         @arg @ref LL_TIM_TRGO_ENABLE
  *         @arg @ref LL_TIM_TRGO_UPDATE
  *         @arg @ref LL_TIM_TRGO_CC1IF
  *         @arg @ref LL_TIM_TRGO_OC1REF
  *         @arg @ref LL_TIM_TRGO_OC2REF
  *         @arg @ref LL_TIM_TRGO_OC3REF
  *         @arg @ref LL_TIM_TRGO_OC4REF
  * @retval None
  */
static inline void LL_TIM_SetTriggerOutput(reg_timer_t *TIMx, uint32_t TimerSynchronization)
{
  MODIFY_REG(TIMx->CR2, TIMER_CR2_MMS_MASK, TimerSynchronization);
}

/**
  * @brief  Set the synchronization mode of a slave timer.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll SMCR         SMS           LL_TIM_SetSlaveMode
  * @param  TIMx Timer instance
  * @param  SlaveMode This parameter can be one of the following values:
  *         @arg @ref LL_TIM_SLAVEMODE_DISABLED
  *         @arg @ref LL_TIM_SLAVEMODE_RESET
  *         @arg @ref LL_TIM_SLAVEMODE_GATED
  *         @arg @ref LL_TIM_SLAVEMODE_TRIGGER
  * @retval None
  */
static inline void LL_TIM_SetSlaveMode(reg_timer_t *TIMx, uint32_t SlaveMode)
{
  MODIFY_REG(TIMx->SMCR, TIMER_SMCR_SMS_MASK, SlaveMode);
}

/**
  * @brief  Set the selects the trigger input to be used to synchronize the counter.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll SMCR         TS            LL_TIM_SetTriggerInput
  * @param  TIMx Timer instance
  * @param  TriggerInput This parameter can be one of the following values:
  *         @arg @ref LL_TIM_TS_ITR0
  *         @arg @ref LL_TIM_TS_ITR1
  *         @arg @ref LL_TIM_TS_ITR2
  *         @arg @ref LL_TIM_TS_ITR3
  *         @arg @ref LL_TIM_TS_TI1F_ED
  *         @arg @ref LL_TIM_TS_TI1FP1
  *         @arg @ref LL_TIM_TS_TI2FP2
  *         @arg @ref LL_TIM_TS_ETRF
  * @retval None
  */
static inline void LL_TIM_SetTriggerInput(reg_timer_t *TIMx, uint32_t TriggerInput)
{
  MODIFY_REG(TIMx->SMCR, TIMER_SMCR_TS_MASK, TriggerInput);
}

/**
  * @brief  Enable the Master/Slave mode.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll SMCR         MSM           LL_TIM_EnableMasterSlaveMode
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableMasterSlaveMode(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->SMCR, TIMER_SMCR_MSM_MASK);
}

/**
  * @brief  Disable the Master/Slave mode.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll SMCR         MSM           LL_TIM_DisableMasterSlaveMode
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_DisableMasterSlaveMode(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->SMCR, TIMER_SMCR_MSM_MASK);
}

/**
  * @brief Indicates whether the Master/Slave mode is enabled.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  * a timer instance can operate as a slave timer.
  * @rmtoll SMCR         MSM           LL_TIM_IsEnabledMasterSlaveMode
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_IsEnabledMasterSlaveMode(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->SMCR, TIMER_SMCR_MSM_MASK) == (TIMER_SMCR_MSM_MASK)) ? 1UL : 0UL);
}
/**
  * @brief  Configure the external trigger (ETR) input.
  * @note Macro IS_TIM_ETR_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an external trigger input.
  * @rmtoll SMCR         ETP           LL_TIM_ConfigETR\n
  *         SMCR         ETPS          LL_TIM_ConfigETR\n
  *         SMCR         ETF           LL_TIM_ConfigETR
  * @param  TIMx Timer instance
  * @param  ETRPolarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ETR_POLARITY_NONINVERTED
  *         @arg @ref LL_TIM_ETR_POLARITY_INVERTED
  * @param  ETRPrescaler This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV1
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV2
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV4
  *         @arg @ref LL_TIM_ETR_PRESCALER_DIV8
  * @param  ETRFilter This parameter can be one of the following values:
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N2
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N4
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV1_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV2_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV2_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV4_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV4_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV8_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV8_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N5
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV16_N8
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N5
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N6
  *         @arg @ref LL_TIM_ETR_FILTER_FDIV32_N8
  * @retval None
  */
static inline void LL_TIM_ConfigETR(reg_timer_t *TIMx, uint32_t ETRPolarity, uint32_t ETRPrescaler,
                                      uint32_t ETRFilter)
{
  MODIFY_REG(TIMx->SMCR, TIMER_SMCR_ETP_MASK | TIMER_SMCR_ETPS_MASK | TIMER_SMCR_ETF_MASK, ETRPolarity | ETRPrescaler | ETRFilter);
}

/**
  * @}
  */

/** @defgroup TIM_LL_EF_Break_Function Break function configuration
  * @{
  */
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableBRK
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableBRK(reg_timer_t *TIMx)
{
  uint32_t tmpreg;
  SET_BIT(TIMx->BDTR, TIMER_BDTR_BKE_MASK);
  /* Note: Any write operation to this bit takes a delay of 1 APB clock cycle to become effective. */
  tmpreg = READ_REG(TIMx->BDTR);
  (void)(tmpreg);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableBRK
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableBRK(reg_timer_t *TIMx)
{
  uint32_t tmpreg;
  CLEAR_BIT(TIMx->BDTR, TIMER_BDTR_BKE_MASK);
  /* Note: Any write operation to this bit takes a delay of 1 APB clock cycle to become effective. */
  tmpreg = READ_REG(TIMx->BDTR);
  (void)(tmpreg);
}

/**
  * @brief  Configure the break input.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKP           LL_TIM_ConfigBRK
  * @param  TIMx Timer instance
  * @param  BreakPolarity This parameter can be one of the following values:
  *         @arg @ref LL_TIM_BREAK_POLARITY_LOW
  *         @arg @ref LL_TIM_BREAK_POLARITY_HIGH
  * @retval None
  */
static inline void LL_TIM_ConfigBRK(reg_timer_t *TIMx, uint32_t BreakPolarity)
{
  uint32_t tmpreg;
  MODIFY_REG(TIMx->BDTR, TIMER_BDTR_BKP_MASK, BreakPolarity);
  /* Note: Any write operation to BKP bit takes a delay of 1 APB clock cycle to become effective. */
  tmpreg = READ_REG(TIMx->BDTR);
  (void)(tmpreg);
}

/**
  * @brief  Select the outputs off state (enabled v.s. disabled) in Idle and Run modes.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         OSSI          LL_TIM_SetOffStates\n
  *         BDTR         OSSR          LL_TIM_SetOffStates
  * @param  TIMx Timer instance
  * @param  OffStateIdle This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OSSI_DISABLE
  *         @arg @ref LL_TIM_OSSI_ENABLE
  * @param  OffStateRun This parameter can be one of the following values:
  *         @arg @ref LL_TIM_OSSR_DISABLE
  *         @arg @ref LL_TIM_OSSR_ENABLE
  * @retval None
  */
static inline void LL_TIM_SetOffStates(reg_timer_t *TIMx, uint32_t OffStateIdle, uint32_t OffStateRun)
{
  MODIFY_REG(TIMx->BDTR, TIMER_BDTR_OSSI_MASK | TIMER_BDTR_OSSR_MASK, OffStateIdle | OffStateRun);
}

/**
  * @brief  Enable automatic output (MOE can be set by software or automatically when a break input is active).
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         AOE           LL_TIM_EnableAutomaticOutput
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableAutomaticOutput(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->BDTR, TIMER_BDTR_AOE_MASK);
}

/**
  * @brief  Disable automatic output (MOE can be set only by software).
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         AOE           LL_TIM_DisableAutomaticOutput
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_DisableAutomaticOutput(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIMER_BDTR_AOE_MASK);
}

/**
  * @brief  Indicate whether automatic output is enabled.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         AOE           LL_TIM_IsEnabledAutomaticOutput
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_IsEnabledAutomaticOutput(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->BDTR, TIMER_BDTR_AOE_MASK) == (TIMER_BDTR_AOE_MASK)) ? 1UL : 0UL);
}
/**
  * @brief  Enable the outputs (set the MOE bit in TIMx_BDTR register).
  * @note The MOE bit in TIMx_BDTR register allows to enable /disable the outputs by
  *       software and is reset in case of break or break2 event
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         MOE           LL_TIM_EnableAllOutputs
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableAllOutputs(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->BDTR, TIMER_BDTR_MOE_MASK);
}

/**
  * @brief  Disable the outputs (reset the MOE bit in TIMx_BDTR register).
  * @note The MOE bit in TIMx_BDTR register allows to enable /disable the outputs by
  *       software and is reset in case of break or break2 event.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         MOE           LL_TIM_DisableAllOutputs
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_DisableAllOutputs(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIMER_BDTR_MOE_MASK);
}

/**
  * @brief  Indicates whether outputs are enabled.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         MOE           LL_TIM_IsEnabledAllOutputs
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
static inline uint32_t LL_TIM_IsEnabledAllOutputs(reg_timer_t *TIMx)
{
  return ((READ_BIT(TIMx->BDTR, TIMER_BDTR_MOE_MASK) == (TIMER_BDTR_MOE_MASK)) ? 1UL : 0UL);
}
////////////////////////////////////////////////////////////3029---3196
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableUIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableUIE(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IER, TIMER_IER_UIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableUIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableUIE(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IER, TIMER_IER_UIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCIE(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IER, TIMER_IER_CC1IE_MASK | TIMER_IER_CC2IE_MASK |TIMER_IER_CC3IE_MASK | TIMER_IER_CC4IE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCIE(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IER, TIMER_IER_CC1IE_MASK | TIMER_IER_CC2IE_MASK |TIMER_IER_CC3IE_MASK | TIMER_IER_CC4IE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableTIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableTIE(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IER, TIMER_IER_TIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableTIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableTIE(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IER, TIMER_IER_TIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableBIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableBIE(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IER, TIMER_IER_BIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableBIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableBIE(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IER, TIMER_IER_BIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCOIE(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IER, TIMER_IER_CC1OIE_MASK | TIMER_IER_CC2OIE_MASK |TIMER_IER_CC3OIE_MASK | TIMER_IER_CC4OIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCOIE(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IER, TIMER_IER_CC1OIE_MASK | TIMER_IER_CC2OIE_MASK |TIMER_IER_CC3OIE_MASK | TIMER_IER_CC4OIE_MASK);
}
///////////////////
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableUIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableUID(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IDR, TIMER_IDR_UIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableUIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableUID(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IDR, TIMER_IDR_UIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCID(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IDR, TIMER_IDR_CC1IE_MASK | TIMER_IDR_CC2IE_MASK |TIMER_IDR_CC3IE_MASK | TIMER_IDR_CC4IE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCID(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IDR, TIMER_IDR_CC1IE_MASK | TIMER_IDR_CC2IE_MASK |TIMER_IDR_CC3IE_MASK | TIMER_IDR_CC4IE_MASK);
}

static inline uint32_t LL_TIM_EnableIT(reg_timer_t *TIMx, uint32_t RegisterBit)
{
    return ((READ_BIT(TIMx->IVS, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_SOURCE(reg_timer_t *TIMx, uint32_t SOURCE)
{
  SET_BIT(TIMx->ICR, SOURCE);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None    TIMER_IDR_CC1IE_MASK | TIMER_IDR_CC2IE_MASK |TIMER_IDR_CC3IE_MASK | TIMER_IDR_CC4IE_MASK
  */
static inline void LL_TIM_CLEAR(reg_timer_t *TIMx,uint32_t CLEAR)
{
  CLEAR_BIT(TIMx->IDR, CLEAR);
}




/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableTIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableTID(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IDR, TIMER_IDR_TIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableTIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableTID(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IDR, TIMER_IDR_TIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableBIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableBID(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IDR, TIMER_IDR_BIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableBIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableBID(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IDR, TIMER_IDR_BIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCOID(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IDR, TIMER_IDR_CC1OIE_MASK | TIMER_IDR_CC2OIE_MASK |TIMER_IDR_CC3OIE_MASK | TIMER_IDR_CC4OIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCOID(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IDR, TIMER_IDR_CC1OIE_MASK | TIMER_IDR_CC2OIE_MASK |TIMER_IDR_CC3OIE_MASK | TIMER_IDR_CC4OIE_MASK);
}
///////////////////////
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableUIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableUIV(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IVS, TIMER_IVS_UIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableUIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableUIV(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IVS, TIMER_IVS_UIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCIV(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IVS, TIMER_IVS_CC1IE_MASK | TIMER_IVS_CC2IE_MASK |TIMER_IVS_CC3IE_MASK | TIMER_IVS_CC4IE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCIV(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IVS, TIMER_IVS_CC1IE_MASK | TIMER_IVS_CC2IE_MASK |TIMER_IVS_CC3IE_MASK | TIMER_IVS_CC4IE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableTIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableTIV(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IVS, TIMER_IVS_TIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableTIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableTIV(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IVS, TIMER_IVS_TIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableBIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableBIV(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IVS, TIMER_IVS_BIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableBIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableBIV(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IVS, TIMER_IVS_BIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCOIV(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IVS, TIMER_IVS_CC1OIE_MASK | TIMER_IVS_CC2OIE_MASK |TIMER_IVS_CC3OIE_MASK | TIMER_IVS_CC4OIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCOIV(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IVS, TIMER_IVS_CC1OIE_MASK | TIMER_IVS_CC2OIE_MASK |TIMER_IVS_CC3OIE_MASK | TIMER_IVS_CC4OIE_MASK);
}
///////////////////////
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableUIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableUIF(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->RIF, TIMER_RIF_UIF_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableUIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableUIF(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->RIF, TIMER_RIF_UIF_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCIF(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->RIF, TIMER_RIF_CC1IF_MASK | TIMER_RIF_CC2IF_MASK |TIMER_RIF_CC3IF_MASK | TIMER_RIF_CC4IF_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCIFF(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->RIF, TIMER_RIF_CC1IF_MASK | TIMER_RIF_CC2IF_MASK |TIMER_RIF_CC3IF_MASK | TIMER_RIF_CC4IF_MASK);
}

static inline uint32_t LL_TIM_DisableCCIF(reg_timer_t *TIMx, uint32_t RegisterBit)
{
    return ((READ_BIT(TIMx->RIF, RegisterBit) == (RegisterBit)) ? 1UL : 0UL);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableTIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableTIF(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->RIF, TIMER_RIF_TIF_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableTIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableTIF(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->RIF, TIMER_RIF_TIF_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableBIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableBIF(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->RIF, TIMER_RIF_BIF_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableBIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableBIF(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->RIF, TIMER_RIF_BIF_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCOIF(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->RIF, TIMER_RIF_CC1OIF_MASK | TIMER_RIF_CC2OIF_MASK |TIMER_RIF_CC3OIF_MASK | TIMER_RIF_CC4OIF_MASK);
}
/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCOIF(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->RIF, TIMER_RIF_CC1OIF_MASK | TIMER_RIF_CC2OIF_MASK |TIMER_RIF_CC3OIF_MASK | TIMER_RIF_CC4OIF_MASK);
}
///////////////////////
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableUIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableUIM(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IFM, TIMER_IFM_UIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableUIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableUIM(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IFM, TIMER_IFM_UIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCIM(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IFM, TIMER_IFM_CC1IE_MASK | TIMER_IFM_CC2IE_MASK |TIMER_IFM_CC3IE_MASK | TIMER_IFM_CC4IE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCIM(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IFM, TIMER_IFM_CC1IE_MASK | TIMER_IFM_CC2IE_MASK |TIMER_IFM_CC3IE_MASK | TIMER_IFM_CC4IE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableTIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableTIM(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IFM, TIMER_IFM_TIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableTIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableTIM(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IFM, TIMER_IFM_TIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableBIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableBIM(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IFM, TIMER_IFM_BIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableBIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableBIM(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IFM, TIMER_IFM_BIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCOIM(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->IFM, TIMER_IFM_CC1OIE_MASK | TIMER_IFM_CC2OIE_MASK |TIMER_IFM_CC3OIE_MASK | TIMER_IFM_CC4OIE_MASK);
}
/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCOIM(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->IFM, TIMER_IFM_CC1OIE_MASK | TIMER_IFM_CC2OIE_MASK |TIMER_IFM_CC3OIE_MASK | TIMER_IFM_CC4OIE_MASK);
}
///////////////////////
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableUIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableUIC(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->ICR, TIMER_ICR_UIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableUIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableUIC(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->ICR, TIMER_ICR_UIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCIC(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->ICR, TIMER_ICR_CC1IE_MASK | TIMER_ICR_CC2IE_MASK |TIMER_ICR_CC3IE_MASK | TIMER_ICR_CC4IE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCIC(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->ICR, TIMER_ICR_CC1IE_MASK | TIMER_ICR_CC2IE_MASK |TIMER_ICR_CC3IE_MASK | TIMER_ICR_CC4IE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableTIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableTIC(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->ICR, TIMER_ICR_TIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableTIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableTIC(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->ICR, TIMER_ICR_TIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableBIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableBIC(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->ICR, TIMER_ICR_BIE_MASK);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableBIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableBIC(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->ICR, TIMER_ICR_BIE_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCOIC(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->ICR, TIMER_ICR_CC1OIE_MASK | TIMER_IFM_CC2OIE_MASK |TIMER_ICR_CC3OIE_MASK | TIMER_ICR_CC4OIE_MASK);
}
/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCOIC(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->ICR, TIMER_ICR_CC1OIE_MASK | TIMER_ICR_CC2OIE_MASK |TIMER_ICR_CC3OIE_MASK | TIMER_ICR_CC4OIE_MASK);
}
////////////////
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableUG(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_UG_MASK );
}
/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableUG(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->EGR, TIMER_EGR_UG_MASK );
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCCG(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_CC1G_MASK | TIMER_EGR_CC2G_MASK |TIMER_EGR_CC3G_MASK | TIMER_EGR_CC4G_MASK);
}
/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCCG(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->EGR, TIMER_EGR_CC1G_MASK | TIMER_EGR_CC2G_MASK |TIMER_EGR_CC3G_MASK | TIMER_EGR_CC4G_MASK);
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableCOMG(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_COMG_MASK );
}
/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableCOMG(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->EGR, TIMER_EGR_COMG_MASK );
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableTG(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_TG_MASK );
}
/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableTG(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->EGR, TIMER_EGR_TG_MASK );
}
/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           LL_TIM_EnableCCIE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_EnableBG(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_BG_MASK );
}
/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           LL_TIM_DisableCCIE
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
static inline void LL_TIM_DisableBG(reg_timer_t *TIMx)
{
  CLEAR_BIT(TIMx->EGR, TIMER_EGR_BG_MASK );
}
/** @defgroup TIM_LL_EF_EVENT_Management EVENT-Management
  * @{
  */
/**
  * @brief  Generate an update event.
  * @rmtoll EGR          UG            LL_TIM_GenerateEvent_UPDATE
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_GenerateEvent_UPDATE(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_UG_MASK);
}

/**
  * @brief  Generate Capture/Compare 1 event.
  * @rmtoll EGR          CC1G          LL_TIM_GenerateEvent_CC1
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_GenerateEvent_CC1(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_CC1G_MASK);
}

/**
  * @brief  Generate Capture/Compare 2 event.
  * @rmtoll EGR          CC2G          LL_TIM_GenerateEvent_CC2
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_GenerateEvent_CC2(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_CC2G_MASK);
}

/**
  * @brief  Generate Capture/Compare 3 event.
  * @rmtoll EGR          CC3G          LL_TIM_GenerateEvent_CC3
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_GenerateEvent_CC3(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_CC3G_MASK);
}

/**
  * @brief  Generate Capture/Compare 4 event.
  * @rmtoll EGR          CC4G          LL_TIM_GenerateEvent_CC4
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_GenerateEvent_CC4(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_CC4G_MASK);
}

/**
  * @brief  Generate commutation event.
  * @rmtoll EGR          COMG          LL_TIM_GenerateEvent_COM
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_GenerateEvent_COM(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_COMG_MASK);
}

/**
  * @brief  Generate trigger event.
  * @rmtoll EGR          TG            LL_TIM_GenerateEvent_TRIG
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_GenerateEvent_TRIG(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_TG_MASK);
}

/**
  * @brief  Generate break event.
  * @rmtoll EGR          BG            LL_TIM_GenerateEvent_BRK
  * @param  TIMx Timer instance
  * @retval None
  */
static inline void LL_TIM_GenerateEvent_BRK(reg_timer_t *TIMx)
{
  SET_BIT(TIMx->EGR, TIMER_EGR_BG_MASK);
}




/** @}*/

/** @}*/

#endif

