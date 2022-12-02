#ifndef LS_HAL_TIMER_H_
#define LS_HAL_TIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "ls_msp_timer.h"
#include "sdk_config.h"
#include "HAL_def.h"


/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSTIMER
 *  @{
 */



/**
 * @brief  TIM Time base Configuration Structure definition
 */
typedef struct
{
  uint32_t Prescaler; /*!< Specifies the prescaler value used to divide the TIM clock.
                           This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

  uint32_t CounterMode; /*!< Specifies the counter mode.
                             This parameter can be a value of @ref TIM_Counter_Mode */

  uint32_t Period; /*!< Specifies the period value to be loaded into the active
                        Auto-Reload Register at the next update event.
                        This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.  */

  uint32_t ClockDivision; /*!< Specifies the clock division.
                               This parameter can be a value of @ref TIM_ClockDivision */

  uint32_t RepetitionCounter; /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                   reaches zero, an update event is generated and counting restarts
                                   from the RCR value (N).
                                   This means in PWM mode that (N+1) corresponds to:
                                       - the number of PWM periods in edge-aligned mode
                                       - the number of half PWM period in center-aligned mode
                                    GP timers: this parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF.
                                    Advanced timers: this parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  uint32_t AutoReloadPreload; /*!< Specifies the auto-reload preload.
                                  This parameter can be a value of @ref TIM_AutoReloadPreload */
  uint32_t TrgoSource;
} TIM_Base_InitTypeDef;
/**
 * @}
 */

/**
 * @brief  TIM Output Compare Configuration Structure definition
 */
typedef struct
{
  uint32_t OCMode; /*!< Specifies the TIM mode.
                        This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  uint32_t Pulse; /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                       This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF */

  uint32_t OCPolarity; /*!< Specifies the output polarity.
                            This parameter can be a value of @ref TIM_Output_Compare_Polarity */

  uint32_t OCNPolarity; /*!< Specifies the complementary output polarity.
                             This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                             @note This parameter is valid only for timer instances supporting break feature. */

  uint32_t OCFastMode; /*!< Specifies the Fast mode state.
                            This parameter can be a value of @ref TIM_Output_Fast_State
                            @note This parameter is valid only in PWM1 and PWM2 mode. */

  uint32_t OCIdleState; /*!< Specifies the TIM Output Compare pin state during Idle state.
                             This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                             @note This parameter is valid only for timer instances supporting break feature. */

  uint32_t OCNIdleState; /*!< Specifies the TIM Output Compare pin state during Idle state.
                              This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                              @note This parameter is valid only for timer instances supporting break feature. */
} TIM_OC_InitTypeDef;
/**
 * @}
 */

/**
 * @brief  TIM Input Capture Configuration Structure definition
 */
typedef struct
{
  uint32_t ICPolarity; /*!< Specifies the active edge of the input signal.
                            This parameter can be a value of @ref TIM_Input_Capture_Polarity */

  uint32_t ICSelection; /*!< Specifies the input.
                             This parameter can be a value of @ref TIM_Input_Capture_Selection */

  uint32_t ICPrescaler; /*!< Specifies the Input Capture Prescaler.
                             This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

  uint32_t ICFilter; /*!< Specifies the input capture filter.
                          This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_IC_InitTypeDef;

/**
 * @brief  Clock Configuration Handle Structure definition
 */
typedef struct
{
  uint32_t ClockSource;    /*!< TIM clock sources
                                This parameter can be a value of @ref TIM_Clock_Source */
  uint32_t ClockPolarity;  /*!< TIM clock polarity
                                This parameter can be a value of @ref TIM_Clock_Polarity */
  uint32_t ClockPrescaler; /*!< TIM clock prescaler
                                This parameter can be a value of @ref TIM_Clock_Prescaler */
  uint32_t ClockFilter;    /*!< TIM clock filter
                                This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_ClockConfigTypeDef;

/**
 * @brief  TIM Clear Input Configuration Handle Structure definition
 */
typedef struct
{
  uint32_t ClearInputState;     /*!< TIM clear Input state
                                     This parameter can be ENABLE or DISABLE */
  uint32_t ClearInputSource;    /*!< TIM clear Input sources
                                     This parameter can be a value of @ref TIM_ClearInput_Source */
  uint32_t ClearInputPolarity;  /*!< TIM Clear Input polarity
                                     This parameter can be a value of @ref TIM_ClearInput_Polarity */
  uint32_t ClearInputPrescaler; /*!< TIM Clear Input prescaler
                                     This parameter must be 0: When OCRef clear feature is used with ETR source, ETR prescaler must be off */
  uint32_t ClearInputFilter;    /*!< TIM Clear Input filter
                                     This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
} TIM_ClearInputConfigTypeDef;

/**
 * @brief  TIM Slave configuration Structure definition
 */
typedef struct
{
  uint32_t SlaveMode;        /*!< Slave mode selection
                                  This parameter can be a value of @ref TIM_Slave_Mode */
  uint32_t InputTrigger;     /*!< Input Trigger source
                                  This parameter can be a value of @ref TIM_Trigger_Selection */
  uint32_t TriggerPolarity;  /*!< Input Trigger polarity
                                  This parameter can be a value of @ref TIM_Trigger_Polarity */
  uint32_t TriggerPrescaler; /*!< Input trigger prescaler
                                  This parameter can be a value of @ref TIM_Trigger_Prescaler */
  uint32_t TriggerFilter;    /*!< Input trigger filter
                                  This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF  */
} TIM_SlaveConfigTypeDef;

/**
 * @brief  TIM Break input(s) and Dead time configuration Structure definition
 * @note   2 break inputs can be configured (BKIN and BKIN2) with configurable
 *        filter and polarity.
 */
typedef struct
{
  uint32_t OffStateRunMode;  /*!< TIM off state in run mode
                                  This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state */
  uint32_t OffStateIDLEMode; /*!< TIM off state in IDLE mode
                                  This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state */
  uint32_t LockLevel;        /*!< TIM Lock level
                                  This parameter can be a value of @ref TIM_Lock_level */
  uint32_t DeadTime;         /*!< TIM dead Time
                                  This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF */
  uint32_t BreakState;       /*!< TIM Break State
                                  This parameter can be a value of @ref TIM_Break_Input_enable_disable */
  uint32_t BreakPolarity;    /*!< TIM Break input polarity
                                  This parameter can be a value of @ref TIM_Break_Polarity */
  uint32_t BreakFilter;      /*!< Specifies the break input filter.
                                  This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
  uint32_t AutomaticOutput;  /*!< TIM Automatic Output Enable state
                                  This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} TIM_BreakDeadTimeConfigTypeDef;

/**
 * @brief  HAL State structures definition
 */
typedef enum
{
  HAL_TIM_STATE_RESET = 0x00U,   /*!< Peripheral not yet initialized or disabled  */
  HAL_TIM_STATE_READY = 0x01U,   /*!< Peripheral Initialized and ready for use    */
  HAL_TIM_STATE_BUSY = 0x02U,    /*!< An internal process is ongoing              */
  HAL_TIM_STATE_TIMEOUT = 0x03U, /*!< Timeout state                               */
  HAL_TIM_STATE_ERROR = 0x04U    /*!< Reception process is ongoing                */
} HAL_TIM_StateTypeDef;

/**
 * @brief  HAL Active channel structures definition
 */
typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1 = 0x01U,      /*!< The active channel is 1     */
  HAL_TIM_ACTIVE_CHANNEL_2 = 0x02U,      /*!< The active channel is 2     */
  HAL_TIM_ACTIVE_CHANNEL_3 = 0x04U,      /*!< The active channel is 3     */
  HAL_TIM_ACTIVE_CHANNEL_4 = 0x08U,      /*!< The active channel is 4     */
  HAL_TIM_ACTIVE_CHANNEL_CLEARED = 0x00U /*!< All active channels cleared */
} HAL_TIM_ActiveChannel;

/**
 * @brief  TIM Time Base Handle Structure definition
 */

typedef struct __TIM_HandleTypeDef
{
  reg_timer_t *Instance;               /*!< Register base address             */
  TIM_Base_InitTypeDef Init;           /*!< TIM Time Base required parameters */
  HAL_TIM_ActiveChannel Channel;       /*!< Active channel                    */
  HAL_LockTypeDef Lock;                /*!< Locking object                    */
  volatile HAL_TIM_StateTypeDef State; /*!< TIM operation state               */
} TIM_HandleTypeDef;

/** @defgroup TIM_ClearInput_Source TIM Clear Input Source
 * @{
 */
#define TIM_CLEARINPUTSOURCE_NONE 0x00000000U /*!< OCREF_CLR is disabled */
#define TIM_CLEARINPUTSOURCE_ETR 0x00000001U  /*!< OCREF_CLR is connected to ETRF input */
/**
 * @}
 */

/** @defgroup TIM_Event_Source TIM Event Source
 * @{
 */
#define TIM_EVENTSOURCE_UPDATE TIMER_EGR_UG_MASK  /*!< Reinitialize the counter and generates an update of the registers */
#define TIM_EVENTSOURCE_CC1 TIMER_EGR_CC1G_MASK   /*!< A capture/compare event is generated on channel 1 */
#define TIM_EVENTSOURCE_CC2 TIMER_EGR_CC2G_MASK   /*!< A capture/compare event is generated on channel 2 */
#define TIM_EVENTSOURCE_CC3 TIMER_EGR_CC3G_MASK   /*!< A capture/compare event is generated on channel 3 */
#define TIM_EVENTSOURCE_CC4 TIMER_EGR_CC4G_MASK   /*!< A capture/compare event is generated on channel 4 */
#define TIM_EVENTSOURCE_COM TIMER_EGR_COMG_MASK   /*!< A commutation event is generated */
#define TIM_EVENTSOURCE_TRIGGER TIMER_EGR_TG_MASK /*!< A trigger event is generated */
#define TIM_EVENTSOURCE_BREAK TIMER_EGR_BG_MASK   /*!< A break event is generated */
/**
 * @}
 */

/** @defgroup TIM_Input_Channel_Polarity TIM Input Channel polarity
 * @{
 */
#define TIM_INPUTCHANNELPOLARITY_RISING 0x00000000U                                      /*!< Polarity for TIx source */
#define TIM_INPUTCHANNELPOLARITY_FALLING TIMER_CCER_CC1P_MASK                            /*!< Polarity for TIx source */
#define TIM_INPUTCHANNELPOLARITY_BOTHEDGE (TIMER_CCER_CC1P_MASK | TIMER_CCER_CC1NP_MASK) /*!< Polarity for TIx source */
/**
 * @}
 */

/** @defgroup TIM_ETR_Polarity TIM ETR Polarity
 * @{
 */
#define TIM_ETRPOLARITY_INVERTED TIMER_SMCR_ETP_MASK /*!< Polarity for ETR source */
#define TIM_ETRPOLARITY_NONINVERTED 0x00000000U      /*!< Polarity for ETR source */
/**
 * @}
 */

/** @defgroup TIM_ETR_Prescaler TIM ETR Prescaler
 * @{
 */
#define TIM_ETRPRESCALER_DIV1 0x00000000U       /*!< No prescaler is used */
#define TIM_ETRPRESCALER_DIV2 TIMER_SMCR_ETPS_0 /*!< ETR input source is divided by 2 */
#define TIM_ETRPRESCALER_DIV4 TIMER_SMCR_ETPS_1 /*!< ETR input source is divided by 4 */
#define TIM_ETRPRESCALER_DIV8 TIMER_SMCR_ETPS   /*!< ETR input source is divided by 8 */
/**
 * @}
 */

/** @defgroup TIM_Counter_Mode TIM Counter Mode
 * @{
 */
#define TIM_COUNTERMODE_UP 0x00000000U                 /*!< Counter used as up-counter   */
#define TIM_COUNTERMODE_DOWN TIMER_CR1_DIR_MASK        /*!< Counter used as down-counter */
#define TIM_COUNTERMODE_CENTERALIGNED1 TIMER_CR1_CMS_0 /*!< Center-aligned mode 1        */
#define TIM_COUNTERMODE_CENTERALIGNED2 TIMER_CR1_CMS_1 /*!< Center-aligned mode 2        */
#define TIM_COUNTERMODE_CENTERALIGNED3 TIMER_CR1_CMS   /*!< Center-aligned mode 3        */
/**
 * @}
 */

/** @defgroup TIM_ClockDivision TIM Clock Division
 * @{
 */
#define TIM_CLOCKDIVISION_DIV1 0x00000000U     /*!< Clock division: tDTS=tCK_INT   */
#define TIM_CLOCKDIVISION_DIV2 TIMER_CR1_CKD_0 /*!< Clock division: tDTS=2*tCK_INT */
#define TIM_CLOCKDIVISION_DIV4 TIMER_CR1_CKD_1 /*!< Clock division: tDTS=4*tCK_INT */
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_State TIM Output Compare State
 * @{
 */
#define TIM_OUTPUTSTATE_DISABLE 0x00000000U         /*!< Capture/Compare 1 output disabled */
#define TIM_OUTPUTSTATE_ENABLE TIMER_CCER_CC1E_MASK /*!< Capture/Compare 1 output enabled */
/**
 * @}
 */

/** @defgroup TIM_AutoReloadPreload TIM Auto-Reload Preload
 * @{
 */
#define TIM_AUTORELOAD_PRELOAD_DISABLE 0x00000000U        /*!< TIMx_ARR register is not buffered */
#define TIM_AUTORELOAD_PRELOAD_ENABLE TIMER_CR1_ARPE_MASK /*!< TIMx_ARR register is buffered */

/**
 * @}
 */

/** @defgroup TIM_Output_Fast_State TIM Output Fast State
 * @{
 */
#define TIM_OCFAST_DISABLE 0x00000000U           /*!< Output Compare fast disable */
#define TIM_OCFAST_ENABLE TIMER_CCMR1_OC1FE_MASK /*!< Output Compare fast enable  */
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_State TIM Complementary Output Compare State
 * @{
 */
#define TIM_OUTPUTNSTATE_DISABLE 0x00000000U          /*!< OCxN is disabled  */
#define TIM_OUTPUTNSTATE_ENABLE TIMER_CCER_CC1NE_MASK /*!< OCxN is enabled   */
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Polarity TIM Output Compare Polarity
 * @{
 */
#define TIM_OCPOLARITY_HIGH 0x00000000U         /*!< Capture/Compare output polarity  */
#define TIM_OCPOLARITY_LOW TIMER_CCER_CC1P_MASK /*!< Capture/Compare output polarity  */
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_Polarity TIM Complementary Output Compare Polarity
 * @{
 */
#define TIM_OCNPOLARITY_HIGH 0x00000000U          /*!< Capture/Compare complementary output polarity */
#define TIM_OCNPOLARITY_LOW TIMER_CCER_CC1NP_MASK /*!< Capture/Compare complementary output polarity */
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_Idle_State TIM Output Compare Idle State
 * @{
 */
#define TIM_OCIDLESTATE_SET TIMER_CR2_OIS1_MASK /*!< Output Idle state: OCx=1 when MOE=0 */
#define TIM_OCIDLESTATE_RESET 0x00000000U       /*!< Output Idle state: OCx=0 when MOE=0 */
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_N_Idle_State TIM Complementary Output Compare Idle State
 * @{
 */
#define TIM_OCNIDLESTATE_SET TIMER_CR2_OIS1N_MASK /*!< Complementary output Idle state: OCxN=1 when MOE=0 */
#define TIM_OCNIDLESTATE_RESET 0x00000000U        /*!< Complementary output Idle state: OCxN=0 when MOE=0 */
/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Polarity TIM Input Capture Polarity
 * @{
 */
#define TIM_ICPOLARITY_RISING TIM_INPUTCHANNELPOLARITY_RISING     /*!< Capture triggered by rising edge on timer input                  */
#define TIM_ICPOLARITY_FALLING TIM_INPUTCHANNELPOLARITY_FALLING   /*!< Capture triggered by falling edge on timer input                 */
#define TIM_ICPOLARITY_BOTHEDGE TIM_INPUTCHANNELPOLARITY_BOTHEDGE /*!< Capture triggered by both rising and falling edges on timer input*/
/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Selection TIM Input Capture Selection
 * @{
 */
#define TIM_ICSELECTION_DIRECTTI TIMER_CCMR1_CC1S_0   /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSELECTION_INDIRECTTI TIMER_CCMR1_CC1S_1 /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to IC2, IC1, IC4 or IC3, respectively */
#define TIM_ICSELECTION_TRC TIMER_CCMR1_CC1S_MASK     /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC */
/**
 * @}
 */

/** @defgroup TIM_Input_Capture_Prescaler TIM Input Capture Prescaler
 * @{
 */
#define TIM_ICPSC_DIV1 0x00000000U          /*!< Capture performed each time an edge is detected on the capture input */
#define TIM_ICPSC_DIV2 TIMER_CCMR1_IC1PSC_0 /*!< Capture performed once every 2 events                                */
#define TIM_ICPSC_DIV4 TIMER_CCMR1_IC1PSC_1 /*!< Capture performed once every 4 events                                */
#define TIM_ICPSC_DIV8 TIMER_CCMR1_IC1PSC   /*!< Capture performed once every 8 events                                */
/**
 * @}
 */

/** @defgroup TIM_One_Pulse_Mode TIM One Pulse Mode
 * @{
 */
#define TIM_OPMODE_SINGLE TIMER_CR1_OPM_MASK /*!< Counter stops counting at the next update event */
#define TIM_OPMODE_REPETITIVE 0x00000000U    /*!< Counter is not stopped at update event          */
/**
 * @}
 */

/** @defgroup TIM_Interrupt_definition TIM interrupt Definition
 * @{
 */
#define TIM_IT_UPDATE TIMER_IDR_UIE_MASK  /*!< Update interrupt            */
#define TIM_IT_CC1 TIMER_IDR_CC1IE_MASK   /*!< Capture/Compare 1 interrupt */
#define TIM_IT_CC2 TIMER_IDR_CC2IE_MASK   /*!< Capture/Compare 2 interrupt */
#define TIM_IT_CC3 TIMER_IDR_CC3IE_MASK   /*!< Capture/Compare 3 interrupt */
#define TIM_IT_CC4 TIMER_IDR_CC4IE_MASK   /*!< Capture/Compare 4 interrupt */
#define TIM_IT_COM TIMER_IDR_COMIE_MASK   /*!< Commutation interrupt       */
#define TIM_IT_TRIGGER TIMER_IDR_TIE_MASK /*!< Trigger interrupt           */
#define TIM_IT_BREAK TIMER_IDR_BIE_MASK   /*!< Break interrupt             */
#define TIM_IT_CC1O TIMER_IDR_CC1OIE_MASK /*!< Capture/compare 1 overcap interrupt */
#define TIM_IT_CC2O TIMER_IDR_CC2OIE_MASK /*!< Break interrupt 2 overcap interrupt */
#define TIM_IT_CC3O TIMER_IDR_CC3OIE_MASK /*!< Break interrupt 3 overcap interrupt */
#define TIM_IT_CC4O TIMER_IDR_CC4OIE_MASK /*!< Break interrupt 4 overcap interrupt */
/**
 * @}
 */

/** @defgroup TIM_Flag_definition TIM Flag Definition
 * @{
 */
#define TIM_FLAG_UPDATE TIMER_RIF_UIF   /*!< Update interrupt flag         */
#define TIM_FLAG_CC1 TIMER_RIF_CC1IF    /*!< Capture/Compare 1 interrupt flag */
#define TIM_FLAG_CC2 TIMER_RIF_CC2IF    /*!< Capture/Compare 2 interrupt flag */
#define TIM_FLAG_CC3 TIMER_RIF_CC3IF    /*!< Capture/Compare 3 interrupt flag */
#define TIM_FLAG_CC4 TIMER_RIF_CC4IF    /*!< Capture/Compare 4 interrupt flag */
#define TIM_FLAG_COM TIMER_RIF_COMIF    /*!< Commutation interrupt flag    */
#define TIM_FLAG_TRIGGER TIMER_RIF_TIF  /*!< Trigger interrupt flag        */
#define TIM_FLAG_BREAK TIMER_RIF_BIF    /*!< Break interrupt flag          */
#define TIM_FLAG_CC1OF TIMER_RIF_CC1OIF /*!< Capture 1 overcapture flag    */
#define TIM_FLAG_CC2OF TIMER_RIF_CC2OIF /*!< Capture 2 overcapture flag    */
#define TIM_FLAG_CC3OF TIMER_RIF_CC3OIF /*!< Capture 3 overcapture flag    */
#define TIM_FLAG_CC4OF TIMER_RIF_CC4OIF /*!< Capture 4 overcapture flag    */
/**
 * @}
 */

/** @defgroup TIM_Channel TIM Channel
 * @{
 */
#define TIM_CHANNEL_1 0x00000000U   /*!< Capture/compare channel 1 identifier      */
#define TIM_CHANNEL_2 0x00000004U   /*!< Capture/compare channel 2 identifier      */
#define TIM_CHANNEL_3 0x00000008U   /*!< Capture/compare channel 3 identifier      */
#define TIM_CHANNEL_4 0x0000000CU   /*!< Capture/compare channel 4 identifier      */
#define TIM_CHANNEL_ALL 0x0000003CU /*!< Global Capture/compare channel identifier  */
/**
 * @}
 */

/** @defgroup TIM_Clock_Source TIM Clock Source
 * @{
 */
#define TIM_CLOCKSOURCE_ETRMODE2 TIMER_SMCR_ETPS_1 /*!< External clock source mode 2                          */
#define TIM_CLOCKSOURCE_INTERNAL TIMER_SMCR_ETPS_0 /*!< Internal clock source                                 */
#define TIM_CLOCKSOURCE_ITR0 TIM_TS_ITR0           /*!< External clock source mode 1 (ITR0)                   */
#define TIM_CLOCKSOURCE_ITR1 TIM_TS_ITR1           /*!< External clock source mode 1 (ITR1)                   */
#define TIM_CLOCKSOURCE_ITR2 TIM_TS_ITR2           /*!< External clock source mode 1 (ITR2)                   */
#define TIM_CLOCKSOURCE_ITR3 TIM_TS_ITR3           /*!< External clock source mode 1 (ITR3)                   */
#define TIM_CLOCKSOURCE_TI1ED TIM_TS_TI1F_ED       /*!< External clock source mode 1 (TTI1FP1 + edge detect.) */
#define TIM_CLOCKSOURCE_TI1 TIM_TS_TI1FP1          /*!< External clock source mode 1 (TTI1FP1)                */
#define TIM_CLOCKSOURCE_TI2 TIM_TS_TI2FP2          /*!< External clock source mode 1 (TTI2FP2)                */
#define TIM_CLOCKSOURCE_ETRMODE1 TIM_TS_ETRF       /*!< External clock source mode 1 (ETRF)                   */
/**
 * @}
 */

/** @defgroup TIM_Clock_Polarity TIM Clock Polarity
 * @{
 */
#define TIM_CLOCKPOLARITY_INVERTED TIM_ETRPOLARITY_INVERTED          /*!< Polarity for ETRx clock sources */
#define TIM_CLOCKPOLARITY_NONINVERTED TIM_ETRPOLARITY_NONINVERTED    /*!< Polarity for ETRx clock sources */
#define TIM_CLOCKPOLARITY_RISING TIM_INPUTCHANNELPOLARITY_RISING     /*!< Polarity for TIx clock sources */
#define TIM_CLOCKPOLARITY_FALLING TIM_INPUTCHANNELPOLARITY_FALLING   /*!< Polarity for TIx clock sources */
#define TIM_CLOCKPOLARITY_BOTHEDGE TIM_INPUTCHANNELPOLARITY_BOTHEDGE /*!< Polarity for TIx clock sources */
/**
 * @}
 */

/** @defgroup TIM_Clock_Prescaler TIM Clock Prescaler
 * @{
 */
#define TIM_CLOCKPRESCALER_DIV1 TIM_ETRPRESCALER_DIV1 /*!< No prescaler is used                                                     */
#define TIM_CLOCKPRESCALER_DIV2 TIM_ETRPRESCALER_DIV2 /*!< Prescaler for External ETR Clock: Capture performed once every 2 events. */
#define TIM_CLOCKPRESCALER_DIV4 TIM_ETRPRESCALER_DIV4 /*!< Prescaler for External ETR Clock: Capture performed once every 4 events. */
#define TIM_CLOCKPRESCALER_DIV8 TIM_ETRPRESCALER_DIV8 /*!< Prescaler for External ETR Clock: Capture performed once every 8 events. */
/**
 * @}
 */

/** @defgroup TIM_ClearInput_Polarity TIM Clear Input Polarity
 * @{
 */
#define TIM_CLEARINPUTPOLARITY_INVERTED TIM_ETRPOLARITY_INVERTED       /*!< Polarity for ETRx pin */
#define TIM_CLEARINPUTPOLARITY_NONINVERTED TIM_ETRPOLARITY_NONINVERTED /*!< Polarity for ETRx pin */
/**
 * @}
 */

/** @defgroup TIM_ClearInput_Prescaler TIM Clear Input Prescaler
 * @{
 */
#define TIM_CLEARINPUTPRESCALER_DIV1 TIM_ETRPRESCALER_DIV1 /*!< No prescaler is used                                                   */
#define TIM_CLEARINPUTPRESCALER_DIV2 TIM_ETRPRESCALER_DIV2 /*!< Prescaler for External ETR pin: Capture performed once every 2 events. */
#define TIM_CLEARINPUTPRESCALER_DIV4 TIM_ETRPRESCALER_DIV4 /*!< Prescaler for External ETR pin: Capture performed once every 4 events. */
#define TIM_CLEARINPUTPRESCALER_DIV8 TIM_ETRPRESCALER_DIV8 /*!< Prescaler for External ETR pin: Capture performed once every 8 events. */
/**
 * @}
 */

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state TIM OSSR OffState Selection for Run mode state
 * @{
 */
#define TIM_OSSR_ENABLE TIMER_BDTR_OSSR /*!< When inactive, OC/OCN outputs are enabled (still controlled by the timer)           */
#define TIM_OSSR_DISABLE 0x00000000U    /*!< When inactive, OC/OCN outputs are disabled (not controlled any longer by the timer) */
/**
 * @}
 */

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state TIM OSSI OffState Selection for Idle mode state
 * @{
 */
#define TIM_OSSI_ENABLE TIMER_BDTR_OSSI /*!< When inactive, OC/OCN outputs are enabled (still controlled by the timer)           */
#define TIM_OSSI_DISABLE 0x00000000U    /*!< When inactive, OC/OCN outputs are disabled (not controlled any longer by the timer) */
/**
 * @}
 */
/** @defgroup TIM_Lock_level  TIM Lock level
 * @{
 */
#define TIM_LOCKLEVEL_OFF 0x00000000U     /*!< LOCK OFF     */
#define TIM_LOCKLEVEL_1 TIMER_BDTR_LOCK_0 /*!< LOCK Level 1 */
#define TIM_LOCKLEVEL_2 TIMER_BDTR_LOCK_1 /*!< LOCK Level 2 */
#define TIM_LOCKLEVEL_3 TIMER_BDTR_LOCK   /*!< LOCK Level 3 */
/**
 * @}
 */

/** @defgroup TIM_Break_Input_enable_disable TIM Break Input Enable
 * @{
 */
#define TIM_BREAK_ENABLE TIMER_BDTR_BKE /*!< Break input BRK is enabled  */
#define TIM_BREAK_DISABLE 0x00000000U   /*!< Break input BRK is disabled */
/**
 * @}
 */

/** @defgroup TIM_Break_Polarity TIM Break Input Polarity
 * @{
 */
#define TIM_BREAKPOLARITY_LOW 0x00000000U     /*!< Break input BRK is active low  */
#define TIM_BREAKPOLARITY_HIGH TIMER_BDTR_BKP /*!< Break input BRK is active high */
/**
 * @}
 */

/** @defgroup TIM_AOE_Bit_Set_Reset TIM Automatic Output Enable
 * @{
 */
#define TIM_AUTOMATICOUTPUT_DISABLE 0x00000000U   /*!< MOE can be set only by software */
#define TIM_AUTOMATICOUTPUT_ENABLE TIMER_BDTR_AOE /*!< MOE can be set by software or automatically at the next update event \
                                                    (if none of the break inputs BRK and BRK2 is active) */
/**
 * @}
 */

/** @defgroup TIM_Master_Mode_Selection TIM Master Mode Selection
 * @{
 */
#define TIM_TRGO_RESET 0x00000000U                                            /*!< TIMx_EGR.UG bit is used as trigger output (TRGO)              */
#define TIM_TRGO_ENABLE TIMER_CR2_MMS_0                                       /*!< TIMx_CR1.CEN bit is used as trigger output (TRGO)             */
#define TIM_TRGO_UPDATE TIMER_CR2_MMS_1                                       /*!< Update event is used as trigger output (TRGO)                 */
#define TIM_TRGO_OC1 (TIMER_CR2_MMS_1 | TIMER_CR2_MMS_0)                      /*!< Capture or a compare match 1 is used as trigger output (TRGO) */
#define TIM_TRGO_OC1REF TIMER_CR2_MMS_2                                       /*!< OC1REF signal is used as trigger output (TRGO)                */
#define TIM_TRGO_OC2REF (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_0)                   /*!< OC2REF signal is used as trigger output(TRGO)                 */
#define TIM_TRGO_OC3REF (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_1)                   /*!< OC3REF signal is used as trigger output(TRGO)                 */
#define TIM_TRGO_OC4REF (TIMER_CR2_MMS_2 | TIMER_CR2_MMS_1 | TIMER_CR2_MMS_0) /*!< OC4REF signal is used as trigger output(TRGO)                 */
/**
 * @}
 */

/** @defgroup TIM_Master_Slave_Mode TIM Master/Slave Mode
 * @{
 */
#define TIM_MASTERSLAVEMODE_ENABLE TIMER_SMCR_MSM /*!< No action */
#define TIM_MASTERSLAVEMODE_DISABLE 0x00000000U   /*!< Master/slave mode is selected */
/**
 * @}
 */

/** @defgroup TIM_Slave_Mode TIM Slave mode
 * @{
 */
#define TIM_SLAVEMODE_DISABLE 0x00000000U                                                /*!< Slave mode disabled           */
#define TIM_SLAVEMODE_RESET TIMER_SMCR_SMS_2                                             /*!< Reset Mode                    */
#define TIM_SLAVEMODE_GATED (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_0)                        /*!< Gated Mode                    */
#define TIM_SLAVEMODE_TRIGGER (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_1)                      /*!< Trigger Mode                  */
#define TIM_SLAVEMODE_EXTERNAL1 (TIMER_SMCR_SMS_2 | TIMER_SMCR_SMS_1 | TIMER_SMCR_SMS_0) /*!< External Clock Mode 1         */
/**
 * @}
 */

/** @defgroup TIM_Output_Compare_and_PWM_modes TIM Output Compare and PWM Modes
 * @{
 */
#define TIM_OCMODE_TIMING 0x00000000U                                                  /*!< Frozen                                 */
#define TIM_OCMODE_ACTIVE TIMER_CCMR1_OC1M_0                                           /*!< Set channel to active level on match   */
#define TIM_OCMODE_INACTIVE TIMER_CCMR1_OC1M_1                                         /*!< Set channel to inactive level on match */
#define TIM_OCMODE_TOGGLE (TIMER_CCMR1_OC1M_1 | TIMER_CCMR1_OC1M_0)                    /*!< Toggle                                 */
#define TIM_OCMODE_PWM1 (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_1)                      /*!< PWM mode 1                             */
#define TIM_OCMODE_PWM2 (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_1 | TIMER_CCMR1_OC1M_0) /*!< PWM mode 2                             */
#define TIM_OCMODE_FORCED_ACTIVE (TIMER_CCMR1_OC1M_2 | TIMER_CCMR1_OC1M_0)             /*!< Force active level                     */
#define TIM_OCMODE_FORCED_INACTIVE TIMER_CCMR1_OC1M_2                                  /*!< Force inactive level                   */
/**
 * @}
 */

/** @defgroup TIM_Trigger_Selection TIM Trigger Selection
 * @{
 */
#define TIM_TS_ITR0 0x00000000U                                           /*!< Internal Trigger 0 (ITR0)              */
#define TIM_TS_ITR1 TIMER_SMCR_TS_0                                       /*!< Internal Trigger 1 (ITR1)              */
#define TIM_TS_ITR2 TIMER_SMCR_TS_1                                       /*!< Internal Trigger 2 (ITR2)              */
#define TIM_TS_ITR3 (TIMER_SMCR_TS_0 | TIMER_SMCR_TS_1)                   /*!< Internal Trigger 3 (ITR3)              */
#define TIM_TS_TI1F_ED TIMER_SMCR_TS_2                                    /*!< TI1 Edge Detector (TI1F_ED)            */
#define TIM_TS_TI1FP1 (TIMER_SMCR_TS_0 | TIMER_SMCR_TS_2)                 /*!< Filtered Timer Input 1 (TI1FP1)        */
#define TIM_TS_TI2FP2 (TIMER_SMCR_TS_1 | TIMER_SMCR_TS_2)                 /*!< Filtered Timer Input 2 (TI2FP2)        */
#define TIM_TS_ETRF (TIMER_SMCR_TS_0 | TIMER_SMCR_TS_1 | TIMER_SMCR_TS_2) /*!< Filtered External Trigger input (ETRF) */
#define TIM_TS_NONE 0x0000FFFFU                                           /*!< No trigger selected                    */
/**
 * @}
 */

/** @defgroup TIM_Trigger_Polarity TIM Trigger Polarity
 * @{
 */
#define TIM_TRIGGERPOLARITY_INVERTED TIM_ETRPOLARITY_INVERTED          /*!< Polarity for ETRx trigger sources             */
#define TIM_TRIGGERPOLARITY_NONINVERTED TIM_ETRPOLARITY_NONINVERTED    /*!< Polarity for ETRx trigger sources             */
#define TIM_TRIGGERPOLARITY_RISING TIM_INPUTCHANNELPOLARITY_RISING     /*!< Polarity for TIxFPx or TI1_ED trigger sources */
#define TIM_TRIGGERPOLARITY_FALLING TIM_INPUTCHANNELPOLARITY_FALLING   /*!< Polarity for TIxFPx or TI1_ED trigger sources */
#define TIM_TRIGGERPOLARITY_BOTHEDGE TIM_INPUTCHANNELPOLARITY_BOTHEDGE /*!< Polarity for TIxFPx or TI1_ED trigger sources */
/**
 * @}
 */

/** @defgroup TIM_Trigger_Prescaler TIM Trigger Prescaler
 * @{
 */
#define TIM_TRIGGERPRESCALER_DIV1 TIM_ETRPRESCALER_DIV1 /*!< No prescaler is used                                                       */
#define TIM_TRIGGERPRESCALER_DIV2 TIM_ETRPRESCALER_DIV2 /*!< Prescaler for External ETR Trigger: Capture performed once every 2 events. */
#define TIM_TRIGGERPRESCALER_DIV4 TIM_ETRPRESCALER_DIV4 /*!< Prescaler for External ETR Trigger: Capture performed once every 4 events. */
#define TIM_TRIGGERPRESCALER_DIV8 TIM_ETRPRESCALER_DIV8 /*!< Prescaler for External ETR Trigger: Capture performed once every 8 events. */
/**
 * @}
 */

/** @defgroup TIM_TI1_Selection TIM TI1 Input Selection
 * @{
 */
#define TIM_TI1SELECTION_CH1 0x00000000U               /*!< The TIMx_CH1 pin is connected to TI1 input */
#define TIM_TI1SELECTION_XORCOMBINATION TIMER_CR2_TI1S /*!< The TIMx_CH1, CH2 and CH3 pins are connected to the TI1 input (XOR combination) */
/**
 * @}
 */

/** @defgroup Channel_CC_State TIM Capture/Compare Channel State
 * @{
 */
#define TIM_CCx_ENABLE 0x00000001U   /*!< Input or output channel is enabled */
#define TIM_CCx_DISABLE 0x00000000U  /*!< Input or output channel is disabled */
#define TIM_CCxN_ENABLE 0x00000004U  /*!< Complementary output channel is enabled */
#define TIM_CCxN_DISABLE 0x00000000U /*!< Complementary output channel is enabled */
/**
 * @}
 */

/** @brief  Reset TIM handle state.
 */
#define __HAL_TIM_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_TIM_STATE_RESET)

/**
 * @brief  Enable the TIM peripheral.
 */
#define __HAL_TIM_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR1 |= (TIMER_CR1_CEN))

/**
 * @brief  Enable the TIM main Output.
 */
#define __HAL_TIM_MOE_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->BDTR |= (TIMER_BDTR_MOE))

/**
 * @brief  Disable the TIM peripheral.
 */
#define __HAL_TIM_DISABLE(__HANDLE__)                                  \
  do                                                                   \
  {                                                                    \
    if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0UL)    \
    {                                                                  \
      if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxNE_MASK) == 0UL) \
      {                                                                \
        (__HANDLE__)->Instance->CR1 &= ~(TIMER_CR1_CEN);               \
      }                                                                \
    }                                                                  \
  } while (0)

/**
 * @brief  Disable the TIM main Output.
 * @note The Main Output Enable of a timer instance is disabled only if all the CCx and CCxN channels have been disabled
 */
#define __HAL_TIM_MOE_DISABLE(__HANDLE__)                              \
  do                                                                   \
  {                                                                    \
    if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0UL)    \
    {                                                                  \
      if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxNE_MASK) == 0UL) \
      {                                                                \
        (__HANDLE__)->Instance->BDTR &= ~(TIMER_BDTR_MOE);             \
      }                                                                \
    }                                                                  \
  } while (0)

/**
 * @brief  Disable the TIM main Output.
 * @note The Main Output Enable of a timer instance is disabled unconditionally
 */
#define __HAL_TIM_MOE_DISABLE_UNCONDITIONALLY(__HANDLE__) (__HANDLE__)->Instance->BDTR &= ~(TIMER_BDTR_MOE)

/** @brief  Enable the specified TIM interrupt.
 */
#define __HAL_TIM_ENABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/** @brief  Disable the specified TIM interrupt.
 */
#define __HAL_TIM_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IDR |= (__INTERRUPT__))

/** @brief  Check whether the specified TIM interrupt flag is set or not.
 */
#define __HAL_TIM_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->RIF & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the specified TIM interrupt flag.
 */
#define __HAL_TIM_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR |= (__FLAG__))

/**
 * @brief  Check whether the specified TIM interrupt source is enabled or not.
 */
#define __HAL_TIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->IVS & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief Clear the TIM interrupt pending bits.
 */
#define __HAL_TIM_CLEAR_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->ICR |= (__INTERRUPT__))

/**
 * @brief  Indicates whether or not the TIM Counter is used as downcounter.
 * @retval False (Counter used as upcounter) or True (Counter used as downcounter)
 * @note This macro is particularly useful to get the counting mode when the timer operates in Center-aligned mode or Encoder
 *mode.
 */
#define __HAL_TIM_IS_TIM_COUNTING_DOWN(__HANDLE__) (((__HANDLE__)->Instance->CR1 & (TIMER_CR1_DIR)) == (TIMER_CR1_DIR))

/**
 * @brief  Set the TIM Prescaler on runtime.
 */
#define __HAL_TIM_SET_PRESCALER(__HANDLE__, __PRESC__) ((__HANDLE__)->Instance->PSC = (__PRESC__))

/**
 * @brief  Set the TIM Counter Register value on runtime.
 */
#define __HAL_TIM_SET_COUNTER(__HANDLE__, __COUNTER__) ((__HANDLE__)->Instance->CNT = (__COUNTER__))

/**
 * @brief  Get the TIM Counter Register value on runtime.
 * @retval 16-bit or 32-bit value of the timer counter register (TIMx_CNT)
 */
#define __HAL_TIM_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->CNT)

/**
 * @brief  Set the TIM Autoreload Register value on runtime without calling another time any Init function.
 */
#define __HAL_TIM_SET_AUTORELOAD(__HANDLE__, __AUTORELOAD__) \
  do                                                         \
  {                                                          \
    (__HANDLE__)->Instance->ARR = (__AUTORELOAD__);          \
    (__HANDLE__)->Init.Period = (__AUTORELOAD__);            \
  } while (0)

/**
 * @brief  Get the TIM Autoreload Register value on runtime.
 * @retval 16-bit or 32-bit value of the timer auto-reload register(TIMx_ARR)
 */
#define __HAL_TIM_GET_AUTORELOAD(__HANDLE__) ((__HANDLE__)->Instance->ARR)

/**
 * @brief  Set the TIM Clock Division value on runtime without calling another time any Init function.
 */
#define __HAL_TIM_SET_CLOCKDIVISION(__HANDLE__, __CKD__) \
  do                                                     \
  {                                                      \
    (__HANDLE__)->Instance->CR1 &= (~TIMER_CR1_CKD);     \
    (__HANDLE__)->Instance->CR1 |= (__CKD__);            \
    (__HANDLE__)->Init.ClockDivision = (__CKD__);        \
  } while (0)

/**
 * @brief  Get the TIM Clock Division value on runtime.
 */
#define __HAL_TIM_GET_CLOCKDIVISION(__HANDLE__) ((__HANDLE__)->Instance->CR1 & TIMER_CR1_CKD)

/**
 * @brief  Set the TIM Input Capture prescaler on runtime without calling another time HAL_TIM_IC_ConfigChannel() function.
 */
#define __HAL_TIM_SET_ICPRESCALER(__HANDLE__, __CHANNEL__, __ICPSC__)   \
  do                                                                    \
  {                                                                     \
    TIM_RESET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__));            \
    TIM_SET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__), (__ICPSC__)); \
  } while (0)

/**
 * @brief  Get the TIM Input Capture prescaler on runtime.
 */
#define __HAL_TIM_GET_ICPRESCALER(__HANDLE__, __CHANNEL__)                                         \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 & TIMER_CCMR1_IC1PSC)         \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? (((__HANDLE__)->Instance->CCMR1 & TIMER_CCMR1_IC2PSC) >> 8U) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 & TIMER_CCMR2_IC3PSC)         \
  :(((__HANDLE__)->Instance->CCMR2 & TIMER_CCMR2_IC4PSC)) >> 8U)

/**
 * @brief  Set the TIM Capture Compare Register value on runtime without calling another time ConfigChannel function.
 */
#define __HAL_TIM_SET_COMPARE(__HANDLE__, __CHANNEL__, __COMPARE__)                  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1 = (__COMPARE__)) \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2 = (__COMPARE__)) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3 = (__COMPARE__)) \
  :((__HANDLE__)->Instance->CCR4 = (__COMPARE__)))

/**
 * @brief  Get the TIM Capture Compare Register value on runtime.
 * @retval 16-bit or 32-bit value of the capture/compare register (TIMx_CCRy)
 */
#define __HAL_TIM_GET_COMPARE(__HANDLE__, __CHANNEL__)               \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1) \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3) \
  :((__HANDLE__)->Instance->CCR4))

/**
 * @brief  Set the TIM Output compare preload.
 */
#define __HAL_TIM_ENABLE_OCxPRELOAD(__HANDLE__, __CHANNEL__)                               \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= TIMER_CCMR1_OC1PE) \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= TIMER_CCMR1_OC2PE) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= TIMER_CCMR2_OC3PE) \
  :((__HANDLE__)->Instance->CCMR2 |= TIMER_CCMR2_OC4PE))

/**
 * @brief  Reset the TIM Output compare preload.
 */
#define __HAL_TIM_DISABLE_OCxPRELOAD(__HANDLE__, __CHANNEL__)                               \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_OC1PE) \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_OC2PE) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_OC3PE) \
  :((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_OC4PE))

/**
 * @brief  Enable fast mode for a given channel.
 * @note  When fast mode is enabled an active edge on the trigger input acts
 *        like a compare match on CCx output. Delay to sample the trigger
 *        input and to activate CCx output is reduced to 3 clock cycles.
 * @note  Fast mode acts only if the channel is configured in PWM1 or PWM2 mode.
 */
#define __HAL_TIM_ENABLE_OCxFAST(__HANDLE__, __CHANNEL__)                                   \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= TIMER_CCMR1_OC1FE)  \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= TIMER_CCMR1_OC2FE)  \
  :((__CHANNEL__) == TIM_CHANNEL_3)   ? ((__HANDLE__)->Instance->CCMR2 |= TIMER_CCMR2_OC3FE)\
  :((__HANDLE__)->Instance->CCMR2 |= TIMER_CCMR2_OC4FE))

/**
 * @brief  Disable fast mode for a given channel.
 * @note  When fast mode is disabled CCx output behaves normally depending
 *        on counter and CCRx values even when the trigger is ON. The minimum
 *        delay to activate CCx output when an active edge occurs on the
 *        trigger input is 5 clock cycles.
 */
#define __HAL_TIM_DISABLE_OCxFAST(__HANDLE__, __CHANNEL__)                                  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_OC1FE) \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_OC2FE) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_OC3FE) \
  :((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_OC4FE))

/**
 * @brief  Set the Update Request Source (URS) bit of the TIMx_CR1 register.
 * @note  When the URS bit of the TIMx_CR1 register is set, only counter
 *        overflow/underflow generates an update interrupt or DMA request (if
 *        enabled)
 */
#define __HAL_TIM_URS_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR1 |= TIMER_CR1_URS)

/**
 * @brief  Reset the Update Request Source (URS) bit of the TIMx_CR1 register.
 * @note  When the URS bit of the TIMx_CR1 register is reset, any of the
 *        following events generate an update interrupt or DMA request (if
 *        enabled):
 *           _ Counter overflow underflow
 *           _ Setting the UG bit
 *           _ Update generation through the slave mode controller
 */
#define __HAL_TIM_URS_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR1 &= ~TIMER_CR1_URS)

/**
 * @brief  Set the TIM Capture x input polarity on runtime.
 */
#define __HAL_TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__) \
  do                                                                         \
  {                                                                          \
    TIM_RESET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__));                  \
    TIM_SET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__), (__POLARITY__));    \
  } while (0)

/* The counter of a timer instance is disabled only if all the CCx and CCxN
   channels have been disabled */
#define TIM_CCER_CCxE_MASK ((uint32_t)(TIMER_CCER_CC1E | TIMER_CCER_CC2E | TIMER_CCER_CC3E | TIMER_CCER_CC4E))
#define TIM_CCER_CCxNE_MASK ((uint32_t)(TIMER_CCER_CC1NE | TIMER_CCER_CC2NE | TIMER_CCER_CC3NE))

#define TIM_SET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__, __ICPSC__)                         \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= (__ICPSC__))         \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= ((__ICPSC__) << 8U)) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= (__ICPSC__))         \
  :((__HANDLE__)->Instance->CCMR2 |= ((__ICPSC__) << 8U)))

#define TIM_RESET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__)                                  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_IC1PSC) \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIMER_CCMR1_IC2PSC) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_IC3PSC) \
  :((__HANDLE__)->Instance->CCMR2 &= ~TIMER_CCMR2_IC4PSC))

#define TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__)                         \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER |= (__POLARITY__))         \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 4U)) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 8U)) \
  :((__HANDLE__)->Instance->CCER |= (((__POLARITY__) << 12U))))

#define TIM_RESET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__)                                                    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER &= ~(TIMER_CCER_CC1P | TIMER_CCER_CC1NP)) \
  :((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER &= ~(TIMER_CCER_CC2P | TIMER_CCER_CC2NP)) \
  :((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER &= ~(TIMER_CCER_CC3P))                    \
  :((__HANDLE__)->Instance->CCER &= ~(TIMER_CCER_CC4P)))

/**
 * @brief  Initializes the TIM Time base Unit according to the specified
 *         parameters in the TIM_HandleTypeDef and initialize the associated handle.
 * @note   Switching from Center Aligned counter mode to Edge counter mode (or reverse)
 *         requires a timer reset to avoid unexpected direction
 *         due to DIR bit readonly in center aligned mode.
 * @param  htim TIM Base handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Init(TIM_HandleTypeDef *htim);

/**
 * @brief  DeInitializes the TIM peripheral
 * @param  htim TIM Base handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_DeInit(TIM_HandleTypeDef *htim);

/**
 * @brief  Starts the TIM Base generation.
 * @param  htim TIM Base handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);

/**
 * @brief  Stops the TIM Base generation.
 * @param  htim TIM Base handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);

/**
 * @brief  Starts the TIM Base generation in interrupt mode.
 * @param  htim TIM Base handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);

/**
 * @brief  Stops the TIM Base generation in interrupt mode.
 * @param  htim TIM Base handle
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);

/**
 * @brief  Starts the TIM Output Compare signal generation.
 * @param  htim TIM Output Compare handle
 * @param  Channel TIM Channel to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the TIM Output Compare signal generation.
 * @param  htim TIM Output Compare handle
 * @param  Channel TIM Channel to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Starts the TIM Output Compare signal generation in interrupt mode.
 * @param  htim TIM Output Compare handle
 * @param  Channel TIM Channel to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the TIM Output Compare signal generation in interrupt mode.
 * @param  htim TIM Output Compare handle
 * @param  Channel TIM Channel to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Starts the PWM signal generation.
 * @param  htim TIM handle
 * @param  Channel TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the PWM signal generation.
 * @param  htim TIM PWM handle
 * @param  Channel TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Starts the PWM signal generation in interrupt mode.
 * @param  htim TIM PWM handle
 * @param  Channel TIM Channel to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the PWM signal generation in interrupt mode.
 * @param  htim TIM PWM handle
 * @param  Channel TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Starts the TIM Input Capture measurement.
 * @param  htim TIM Input Capture handle
 * @param  Channel TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the TIM Input Capture measurement.
 * @param  htim TIM Input Capture handle
 * @param  Channel TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Starts the TIM Input Capture measurement in interrupt mode.
 * @param  htim TIM Input Capture handle
 * @param  Channel TIM Channels to be enabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the TIM Input Capture measurement in interrupt mode.
 * @param  htim TIM Input Capture handle
 * @param  Channel TIM Channels to be disabled
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Initializes the TIM One Pulse Time Base according to the specified
 *         parameters in the TIM_HandleTypeDef and initializes the associated handle.
 * @note   Switching from Center Aligned counter mode to Edge counter mode (or reverse)
 *         requires a timer reset to avoid unexpected direction
 *         due to DIR bit readonly in center aligned mode.
 * @param  htim TIM One Pulse handle
 * @param  OnePulseMode Select the One pulse mode.
 *         This parameter can be one of the following values:
 *            @arg TIM_OPMODE_SINGLE: Only one pulse will be generated.
 *            @arg TIM_OPMODE_REPETITIVE: Repetitive pulses will be generated.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);

/**
 * @brief  This function handles TIM interrupts requests.
 * @param  htim TIM  handle
 * @retval None
 */
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);

/**
 * @brief  Initializes the TIM Output Compare Channels according to the specified
 *         parameters in the TIM_OC_InitTypeDef.
 * @param  htim TIM Output Compare handle
 * @param  sConfig TIM Output Compare configuration structure
 * @param  Channel TIM Channels to configure
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel);

/**
 * @brief  Initializes the TIM PWM  channels according to the specified
 *         parameters in the TIM_OC_InitTypeDef.
 * @param  htim TIM PWM handle
 * @param  sConfig TIM PWM configuration structure
 * @param  Channel TIM Channels to be configured
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel);

/**
 * @brief  Initializes the TIM Input Capture Channels according to the specified
 *         parameters in the TIM_IC_InitTypeDef.
 * @param  htim TIM IC handle
 * @param  sConfig TIM Input Capture configuration structure
 * @param  Channel TIM Channel to configure
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
 *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
 *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
 *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, TIM_IC_InitTypeDef *sConfig, uint32_t Channel);
/**
 * @brief  Configures the OCRef clear feature
 * @param  htim TIM handle
 * @param  sClearInputConfig pointer to a TIM_ClearInputConfigTypeDef structure that
 *         contains the OCREF clear feature and parameters for the TIM peripheral.
 * @param  Channel specifies the TIM Channel
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1
 *            @arg TIM_CHANNEL_2: TIM Channel 2
 *            @arg TIM_CHANNEL_3: TIM Channel 3
 *            @arg TIM_CHANNEL_4: TIM Channel 4
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim, TIM_ClearInputConfigTypeDef *sClearInputConfig, uint32_t Channel);

/**
 * @brief   Configures the clock source to be used
 * @param  htim TIM handle
 * @param  sClockSourceConfig pointer to a TIM_ClockConfigTypeDef structure that
 *         contains the clock source information for the TIM peripheral.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef *sClockSourceConfig);

/**
 * @brief  Selects the signal connected to the TI1 input: direct from CH1_input
 *         or a XOR combination between CH1_input, CH2_input & CH3_input
 * @param  htim TIM handle.
 * @param  TI1_Selection Indicate whether or not channel 1 is connected to the
 *         output of a XOR gate.
 *          This parameter can be one of the following values:
 *            @arg TIM_TI1SELECTION_CH1: The TIMx_CH1 pin is connected to TI1 input
 *            @arg TIM_TI1SELECTION_XORCOMBINATION: The TIMx_CH1, CH2 and CH3
 *            pins are connected to the TI1 input (XOR combination)
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);

/**
 * @brief  Generate a software event
 * @param  htim TIM handle
 * @param  EventSource specifies the event source.
 *          This parameter can be one of the following values:
 *            @arg TIM_EVENTSOURCE_UPDATE: Timer update Event source
 *            @arg TIM_EVENTSOURCE_CC1: Timer Capture Compare 1 Event source
 *            @arg TIM_EVENTSOURCE_CC2: Timer Capture Compare 2 Event source
 *            @arg TIM_EVENTSOURCE_CC3: Timer Capture Compare 3 Event source
 *            @arg TIM_EVENTSOURCE_CC4: Timer Capture Compare 4 Event source
 *            @arg TIM_EVENTSOURCE_COM: Timer COM event source
 *            @arg TIM_EVENTSOURCE_TRIGGER: Timer Trigger Event source
 *            @arg TIM_EVENTSOURCE_BREAK: Timer Break event source
 * @note   Basic timers can only generate an update event.
 * @note   TIM_EVENTSOURCE_COM is relevant only with advanced timer instances.
 * @note   TIM_EVENTSOURCE_BREAK are relevant only for timer instances
 *         supporting a break input.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);

/**
 * @brief  Read the captured value from Capture Compare unit
 * @param  htim TIM handle.
 * @param  Channel TIM Channels to be enabled
 * @retval Captured value
 */
uint32_t HAL_TIM_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Return the TIM Base handle state.
 * @param  htim TIM Base handle
 * @retval HAL state
 */
HAL_TIM_StateTypeDef HAL_TIM_GetState(TIM_HandleTypeDef *htim);

/**
 * @brief  Starts the TIM Output Compare signal generation on the complementary
 *         output.
 * @param  htim TIM Output Compare handle
 * @param  Channel TIM Channel to be enabled
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_OCN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the TIM Output Compare signal generation on the complementary
 *         output.
 * @param  htim TIM handle
 * @param  Channel TIM Channel to be disabled
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Starts the TIM Output Compare signal generation in interrupt mode
 *         on the complementary output.
 * @param  htim TIM OC handle
 * @param  Channel TIM Channel to be enabled
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the TIM Output Compare signal generation in interrupt mode
 *         on the complementary output.
 * @param  htim TIM Output Compare handle
 * @param  Channel TIM Channel to be disabled
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Starts the PWM signal generation on the complementary output.
 * @param  htim TIM handle
 * @param  Channel TIM Channel to be enabled
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the PWM signal generation on the complementary output.
 * @param  htim TIM handle
 * @param  Channel TIM Channel to be disabled
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
/**
 * @brief  Starts the PWM signal generation in interrupt mode on the
 *         complementary output.
 * @param  htim TIM handle
 * @param  Channel TIM Channel to be disabled
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Stops the PWM signal generation in interrupt mode on the
 *         complementary output.
 * @param  htim TIM handle
 * @param  Channel TIM Channel to be disabled
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @brief  Configures the Break feature, dead time, Lock level, OSSI/OSSR State
 *         and the AOE(automatic output enable).
 * @param  htim TIM handle
 * @param  sBreakDeadTimeConfig pointer to a TIM_ConfigBreakDeadConfigTypeDef structure that
 *         contains the BDTR Register configuration  information for the TIM peripheral.
 * @note   Interrupts can be generated when an active level is detected on the
 *         break input, the break 2 input or the system break input. Break
 *         interrupt can be enabled by calling the __HAL_TIM_ENABLE_IT macro.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim, TIM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);

/**
 * @brief  Hall commutation changed callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Hall commutation changed half complete callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Hall Break detection callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Period elapsed callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Period elapsed half complete callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Output Compare callback in non-blocking mode
 * @param  htim TIM OC handle
 * @retval None
 */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Input Capture callback in non-blocking mode
 * @param  htim TIM IC handle
 * @retval None
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Input Capture half complete callback in non-blocking mode
 * @param  htim TIM IC handle
 * @retval None
 */
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  PWM Pulse finished callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  PWM Pulse finished half complete callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Hall Trigger detection callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Hall Trigger detection half complete callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Timer error callback in non-blocking mode
 * @param  htim TIM handle
 * @retval None
 */
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);

/**
 * @brief  Configures the TIM in Slave mode
 * @param  htim TIM handle.
 * @param  sSlaveConfig pointer to a TIM_SlaveConfigTypeDef structure that
 *         contains the selected trigger (internal trigger input, filtered
 *         timer input or external trigger input) and the Slave mode
 *         (Disable, Reset, Gated, Trigger, External clock mode 1).
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig);
#endif /* LSTIMER_H_ */

/*****************************END OF FILE****************************/
