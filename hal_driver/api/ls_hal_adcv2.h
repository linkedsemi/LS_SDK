#ifndef LS_HAL_ADCV2_H_
#define LS_HAL_ADCV2_H_
#include <stdbool.h>
#include "HAL_def.h"
#include "ls_msp_adc.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSADC
 *  @{
 */
typedef struct
{
    uint32_t DataAlign;                    /*!< Specifies ADC data alignment to right (MSB on register bit 11 and LSB on register bit 0) (default setting)
                                                or to left (MSB on register bit 15 and LSB on register bit 4).This parameter can be a value of @ref ADC_Data_align */
                                    
    FunctionalState ContinuousConvMode;    /*!< Specifies whether the conversion is performed in single mode (one conversion) or continuous mode for regular group,
                                                after the selected trigger occurred (software start or external trigger).
                                                This parameter can be set to ENABLE or DISABLE. */
    uint32_t NbrOfConversion;              /*!< Specifies the number of ranks that will be converted within the regular group sequencer.
                                                This parameter must be a number between Min_Data = 1 and Max_Data = 12. */
    FunctionalState DiscontinuousConvMode; /*!< Specifies whether the conversions sequence of regular group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                                This parameter can be set to ENABLE or DISABLE. */
    uint32_t NbrOfDiscConversion;          /*!< Specifies the number of discontinuous conversions in which the  main sequence of regular group (parameter NbrOfConversion) will be subdivided.
                                                If parameter 'DiscontinuousConvMode' is disabled, this parameter is discarded.
                                                This parameter must be a number between Min_Data = 1 and Max_Data = 8. */
    uint32_t TrigType;                     /*!< Selects the external event used to trigger the conversion start of regular group. */

    uint32_t Vref;                         /*!< Select ADC reference voltage, please refer to the type ADC_Vref_TypeDef*/

    uint32_t AdcDriveType;                 /*!< Select ADC Driving mode, please refer to the type ADC_Drv_TypeDef*/

    uint32_t AdcCkDiv;                     /*!< ADC division coefficient ranges from 1 to 0x1FFFF */
} ADC_InitTypeDef;

/**
  * @brief  ADC Injected Configuration Structure definition
  */
typedef struct 
{
  uint32_t InjectedChannel;                       /*!< Selection of ADC channel to configure
                                                       This parameter can be a value of ADC_channels */
  uint32_t InjectedRank;                          /*!< Rank in the injected group sequencer
                                                       This parameter must be a value of ADCEx_injected_rank*/
  uint32_t InjectedSamplingTime;                  /*!< Sampling time value to be set for the selected channel. */

  uint32_t InjectedOffset;                        /*!< Defines the offset to be subtracted from the raw converted data (for channels set on injected group only).
                                                       Offset value must be a positive number.
                                                       Depending of ADC resolution selected (12, 10, 8 or 6 bits),
                                                       this parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F respectively. */
  uint32_t InjectedNbrOfConversion;               /*!< Specifies the number of ranks that will be converted within the injected group sequencer.
                                                       To use the injected group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                                       This parameter must be a number between Min_Data = 1 and Max_Data = 4. */
  uint32_t InjectedClk;
  FunctionalState InjectedDiscontinuousConvMode;  /*!< Specifies whether the conversions sequence of injected group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                                       This parameter can be set to ENABLE or DISABLE. */
}ADC_InjectionConfTypeDef;

/** 
  * @brief  Structure definition of ADC channel for regular group   
  * @note   The setting of these parameters with function HAL_ADC_ConfigChannel() is conditioned to ADC state.
  *         ADC can be either disabled or enabled without conversion on going on regular group.
  */
typedef struct
{
    uint32_t    Channel;      /*!< Specifies the channel to configure into ADC regular group.  */
    uint32_t    Rank;         /*!< Specifies the rank in the regular group sequencer 
                                    This parameter can be a value of @ref ADC_regular_rank */
    uint32_t    SamplingTime; /*!< Sampling time value to be set for the selected channel.     */
    uint32_t    clk_cfg;
} ADC_ChannelConfTypeDef;

typedef struct
{
    uint32_t    Channel;
    uint32_t    Rank;
    uint32_t    SamplingTime;
    uint32_t    LoopClk;
    uint32_t    NbrOfConversion;
    uint32_t    CapIntv;
}ADC_LoopConfTypeDef;
/**
  * @brief  ADC Configuration analog watchdog definition
  * @note   The setting of these parameters with function is conditioned to ADC state.
  *         ADC state can be either disabled or enabled without conversion on going on regular and injected groups.
  */
typedef struct
{
    uint32_t WatchdogMode;   /*!< Configures the ADC analog watchdog mode: single/all channels, regular/injected group.
                                   This parameter can be a value of ADC_analog_watchdog_mode. */
    uint32_t Channel;        /*!< Selects which ADC channel to monitor by analog watchdog.
                                   This parameter has an effect only if watchdog mode is configured on single channel (parameter WatchdogMode)
                                   This parameter can be a value of ADC_channels. */
    FunctionalState ITMode;  /*!< Specifies whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */
    uint32_t HighThreshold;  /*!< Configures the ADC analog watchdog High threshold value.
                                   This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
    uint32_t LowThreshold;   /*!< Configures the ADC analog watchdog Low threshold value.
                                   This parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF. */
} ADC_AnalogWDGConfTypeDef;

/**
  * @brief  ADC DMA Environment 
  */
 struct __ADC_HandleTypeDef;
 struct AdcDMAEnv
{
    void                          (*Callback)(struct __ADC_HandleTypeDef *);
    uint8_t                       DMA_Channel;
};

/**
  * @brief  ADC Interrupt Environment   
  */
struct AdcInterruptEnv
{
    uint8_t                       *pBuffPtr;      /*!< Pointer to ADC data Buffer   */
    uint16_t                      XferCount;      /*!< UART ADC data Counter        */
};

/**
  * @brief  ADC handle Structure definition
  */
typedef struct __ADC_HandleTypeDef
{
    reg_adc_t       *Instance;              /*!< Register base address */

    ADC_InitTypeDef Init;                   /*!< ADC required parameters */

    void            *DMAC_Instance;
    union{
        struct AdcDMAEnv DMA;
        struct AdcInterruptEnv Interrupt;
    }Env;
} ADC_HandleTypeDef;

 /** 
  * @brief  driving ADC type enumeration definition 
  */
 enum ADC_Drv_TypeDef
 {
    EINBUF_DRIVE_ADC,                   /*!< En Inbuf mode */
    INRES_ONETHIRD_EINBUF_DRIVE_ADC,    /*!< 1/3 partial voltage input signal */
    BINBUF_DIRECT_DRIVE_ADC,            /*!< By Pass Inbuf */
 };

 #define LOOP_MDOE_FIFO_LVL_NUM_GET(__HANDLE__)  ((__HANDLE__)->Instance->FIFO_FLVL)

 /** 
 *  @defgroup ADC_Data_align ADC data alignment
*/
#define ADC_DATAALIGN_RIGHT 0x00000000U
#define ADC_DATAALIGN_LEFT ((uint32_t)ADC_DATA_ALIGN_MASK)

/** 
 *  @defgroup ADC_Clock_Division ADC Clock Division
*/               
#define ADC_CH_CLOCK_DIV1          0x00000000U 
#define ADC_CH_CLOCK_DIV2          0x00000001U                 
#define ADC_CH_CLOCK_DIV4          0x00000002U                 
#define ADC_CH_CLOCK_DIV8          0x00000003U 

/** 
 * @defgroup ADC_sampling_times ADC sampling times
*/
#define ADC_SAMPLETIME_1CYCLE   0x00000000U                 /*!< Sampling time 1 ADC clock cycle */
#define ADC_SAMPLETIME_2CYCLES  0x00000001U                 /*!< Sampling time 2 ADC clock cycles */
#define ADC_SAMPLETIME_4CYCLES  0x00000002U                 /*!< Sampling time 4 ADC clock cycles */
#define ADC_SAMPLETIME_15CYCLES 0x00000003U                 /*!< Sampling time 15 ADC clock cycles */

/** 
  * @brief  Reference voltage type enumeration definition 
  */
 enum ADC_Vref_TypeDef
 {
    ADC_VREF_VCC,           /*!< system power*/
    ADC_VREF_EXPOWER,       /*!< External power */
    ADC_VREF_INSIDE,        /*!< inside power */
 };

 /** 
 * @defgroup ADC_External_trigger_edge_Regular ADC external trigger enable 
*/
#define ADC_PIS_TRIG                0x00000000U
#define ADC_SOFTWARE_TRIGT         (ADC_FIF_TRIG_MASK|ADC_INJ_TRIG_MASK|ADC_REG_TRIG_MASK)        

 /** 
  * @brief  ADC_channels ADC channels
  */
#define ADC_CHANNEL_0               0x00000000U
#define ADC_CHANNEL_1               0x00000001U
#define ADC_CHANNEL_2               0x00000002U
#define ADC_CHANNEL_3               0x00000003U
#define ADC_CHANNEL_4               0x00000004U
#define ADC_CHANNEL_5               0x00000005U
#define ADC_CHANNEL_6               0x00000006U
#define ADC_CHANNEL_7               0x00000007U

#define ADC1_CHANNEL_BG             0x00000008U  /* ADC internal channel (no connection on device pin) */
#define ADC1_CHANNEL9_RESERVED      0x00000009U  /* ADC internal channel (no connection on device pin) */
#define ADC1_CHANNEL_VBAT           0x0000000AU  /* ADC internal channel (no connection on device pin) */
#define ADC1_CHANNEL_TEMPSENSOR     0x0000000BU  /* ADC internal channel (no connection on device pin) */

#define ADC2_CHANNEL8_RESERVED      0x00000008U  /* ADC internal channel (no connection on device pin) */
#define ADC2_CHANNEL_AMIC           0x00000009U  /* ADC internal channel (no connection on device pin) */
#define ADC2_CHANNEL10_RESERVED     0x0000000AU  /* ADC internal channel (no connection on device pin) */
#define ADC2_CHANNEL11_RESERVED     0x0000000BU  /* ADC internal channel (no connection on device pin) */

/** 
 * @defgroup ADC_regular_rank ADC rank into regular group
*/
#define ADC_REGULAR_RANK_1                 0x00000001U
#define ADC_REGULAR_RANK_2                 0x00000002U
#define ADC_REGULAR_RANK_3                 0x00000003U
#define ADC_REGULAR_RANK_4                 0x00000004U
#define ADC_REGULAR_RANK_5                 0x00000005U
#define ADC_REGULAR_RANK_6                 0x00000006U
#define ADC_REGULAR_RANK_7                 0x00000007U
#define ADC_REGULAR_RANK_8                 0x00000008U
#define ADC_REGULAR_RANK_9                 0x00000009U
#define ADC_REGULAR_RANK_10                0x0000000AU
#define ADC_REGULAR_RANK_11                0x0000000BU
#define ADC_REGULAR_RANK_12                0x0000000CU


/** 
 * @defgroup ADCEx_injected_rank ADCEx rank into injected group
*/
#define ADC_INJECTED_RANK_1                           0x00000001U
#define ADC_INJECTED_RANK_2                           0x00000002U
#define ADC_INJECTED_RANK_3                           0x00000003U
#define ADC_INJECTED_RANK_4                           0x00000004U


/** 
 * @defgroup ADCEx_LOOP_rank ADCEx rank into injected group
*/
#define ADC_LOOP_RANK_1                           0x00000001U
#define ADC_LOOP_RANK_2                           0x00000002U
#define ADC_LOOP_RANK_3                           0x00000003U
#define ADC_LOOP_RANK_4                           0x00000004U

/** 
 * @defgroup ADC_analog_watchdog_mode ADC analog watchdog mode
*/
#define ADC_ANALOGWATCHDOG_NONE                             0x00000000U
#define ADC_ANALOGWATCHDOG_SINGLE_REG           ((uint32_t)(ADC_AWD_SINGLE_MASK | ADC_REG_AWDEN_MASK))
#define ADC_ANALOGWATCHDOG_SINGLE_INJEC         ((uint32_t)(ADC_AWD_SINGLE_MASK | ADC_INJ_AWDEN_MASK))
#define ADC_ANALOGWATCHDOG_ALL_REG              ((uint32_t)(ADC_REG_AWDEN_MASK))
#define ADC_ANALOGWATCHDOG_ALL_INJEC            ((uint32_t)(ADC_INJ_AWDEN_MASK))
#define ADC_ANALOGWATCHDOG_ALL_REGINJEC         ((uint32_t)(ADC_REG_AWDEN_MASK | ADC_INJ_AWDEN_MASK))


/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);


/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef *hadc);

/**
  * @brief  Stop ADC conversion and disable the selected ADC
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped to disable the ADC.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_ConversionStop_Disable(ADC_HandleTypeDef *hadc);

/**
  * @brief  Enables ADC, starts conversion of regular group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc);

/**
  * @brief  Stop ADC conversion of regular group (and injected channels in 
  *         case of auto_injection mode), disable ADC peripheral.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc);

/**
  * @brief  Wait for regular group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);

/**
  * @brief  Enables ADC, starts conversion of injected group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc);

/**
  * @brief  Stop conversion of injected channels. Disable ADC peripheral if
  *         no regular conversion is on going.
  * @note   In case of auto-injection mode, HAL_ADC_Stop must be used.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc);

/**
  * @brief  Wait for injected group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

/**
  * @brief  Enables ADC, starts conversion of regular group with interruption.
  *         Interruptions enabled in this function:
  *          - EOC (end of conversion of regular group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc);

/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable interrution of 
  *         end-of-conversion, disable ADC peripheral.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc);

/**
  * @brief  Enables ADC, starts conversion of injected group with interruption.
  *          - JEOC (end of conversion of injected group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc);

/**
  * @brief  Stop conversion of injected channels, disable interruption of 
  *         end-of-conversion. Disable ADC peripheral if no regular conversion
  *         is on going.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc);


/**
  * @brief  Get ADC regular group conversion result.
  * @param  hadc: ADC handle
  * @retval ADC group regular conversion data
  */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc, uint32_t RegularRank);

/**
  * @brief  Get ADC injected group conversion result.
  * @param  hadc: ADC handle
  * @param  InjectedRank: the converted ADC injected rank.
  *          This parameter can be one of the following values:
  *            @arg ADC_INJECTED_RANK_1: Injected Channel1 selected
  *            @arg ADC_INJECTED_RANK_2: Injected Channel2 selected
  *            @arg ADC_INJECTED_RANK_3: Injected Channel3 selected
  *            @arg ADC_INJECTED_RANK_4: Injected Channel4 selected
  * @retval ADC group injected conversion data
  */
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank);

/**
  * @brief  Handles ADC interrupt request  
  * @param  hadc: ADC handle
  */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc);

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

/**
  * @brief  Analog watchdog callback in non blocking mode. 
  * @param  hadc: ADC handle
  */
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc);

/**
  * @brief  Configures the the selected channel to be linked to the regular
  *         group.
  * @param  hadc: ADC handle
  * @param  sConfig: Structure of ADC channel for regular group.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig);

/**
  * @brief  Configures the ADC injected group and the selected channel to be
  *         linked to the injected group.
  * @param  hadc: ADC handle
  * @param  sConfigInjected: Structure of ADC injected group and ADC channel for
  *         injected group.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc,ADC_InjectionConfTypeDef* sConfigInjected);

/**
  * @brief  Injected conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  */
void  HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc);

/**
  * @brief  Configures the ADC LOOP group and the selected channel to be 
  *         linked to the LOOP group.
  * @param  hadc: ADC handle
  * @param  sConfig: Structure of ADC channel for LOOP group.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_LoopConfigChannel(ADC_HandleTypeDef* hadc,ADC_LoopConfTypeDef* sConfig);

/**
  * @brief  Get ADC Loop group conversion result.
  * @param  hadc: ADC handle
  * @retval ADC group Loop conversion data
  */
uint32_t HAL_ADCx_LoopGetValue(ADC_HandleTypeDef* hadc);

/**
  * @brief  Enables ADC, starts conversion of loop group with interruption.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADCx_LoopStart_IT(ADC_HandleTypeDef *hadc);

/**
  * @brief  Stop ADC conversion of loop channels,disable interrution of 
  *         end-of-conversion, disable ADC peripheral.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCx_LoopStop_IT(ADC_HandleTypeDef *hadc);

/**
  * @brief  Enables ADC, starts conversion of injected group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCx_LoopStart(ADC_HandleTypeDef* hadc);

/**
  * @brief  Wait for loop group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCx_LoopPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

/**
  * @brief  Stop conversion of injected channels. Disable ADC peripheral.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCx_LoopStop(ADC_HandleTypeDef *hadc);

/**
  * @brief  Loop conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  */
void HAL_ADCx_LoopConvCpltCallback(ADC_HandleTypeDef* hadc);

/**
  * @brief  Configures the analog watchdog.
  * @note   Analog watchdog thresholds can be modified while ADC conversion
  *         is on going.
  *         In this case, some constraints must be taken into account:
  *         the programmed threshold values are effective from the next
  *         ADC EOC (end of unitary conversion).
  *         Considering that registers write delay may happen due to
  *         bus activity, this might cause an uncertainty on the
  *         effective timing of the new programmed threshold values.
  * @param  hadc: ADC handle
  * @param  AnalogWDGConfig: Structure of ADC analog watchdog configuration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);

/**
  * @brief  Enables ADC, starts conversion of regular group and transfers result through DMA.
  * @param  hadc: ADC handle
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @param  Callback: function pointer.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_LoopChannel_Start_DMA(ADC_HandleTypeDef* hadc, uint16_t* pData, uint32_t Length,void (*Callback)(ADC_HandleTypeDef* hadc));

 /**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_AD_LoopChannelC_Stop_DMA(ADC_HandleTypeDef* hadc);

/** @}*/


/** @}*/
#endif




