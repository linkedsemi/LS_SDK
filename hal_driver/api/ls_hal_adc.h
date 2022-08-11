#ifndef LS_HAL_ADC_H_
#define LS_HAL_ADC_H_
#include <stdbool.h>
#include "HAL_def.h"
#include "ls_dbg.h"
#include "sdk_config.h"
#include "ls_msp_adc.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSADC
 *  @{
 */



/// ADC CLOCK
#define ADC_CLOCK   (SDK_PCLK_MHZ*1000000)


/**
  * @brief  ADC Configuration Structure definition
  */
typedef struct
{
    uint32_t DataAlign;                    /*!< Specifies ADC data alignment to right (MSB on register bit 11 and LSB on register bit 0) (default setting)
                                                or to left (MSB on register bit 15 and LSB on register bit 4).This parameter can be a value of @ref ADC_Data_align */
    uint32_t ScanConvMode;                 /*!< Configures the sequencer of regular and injected groups.
                                                This parameter can be associated to parameter 'DiscontinuousConvMode' to have main sequence subdivided in successive parts.
                                                If enabled:  Conversions are performed in sequence mode (each channel rank). */
                                    
    FunctionalState ContinuousConvMode;    /*!< Specifies whether the conversion is performed in single mode (one conversion) or continuous mode for regular group,
                                                after the selected trigger occurred (software start or external trigger).
                                                This parameter can be set to ENABLE or DISABLE. */
    uint32_t NbrOfConversion;              /*!< Specifies the number of ranks that will be converted within the regular group sequencer.
                                                This parameter must be a number between Min_Data = 1 and Max_Data = 16. */
    FunctionalState DiscontinuousConvMode; /*!< Specifies whether the conversions sequence of regular group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                                This parameter can be set to ENABLE or DISABLE. */
    uint32_t NbrOfDiscConversion;          /*!< Specifies the number of discontinuous conversions in which the  main sequence of regular group (parameter NbrOfConversion) will be subdivided.
                                                If parameter 'DiscontinuousConvMode' is disabled, this parameter is discarded.
                                                This parameter must be a number between Min_Data = 1 and Max_Data = 8. */
    uint32_t TrigType;                     /*!< Selects the external event used to trigger the conversion start of regular group. */

    uint32_t Vref;                         /*!< Select ADC reference voltage, please refer to the type ADC_Vref_TypeDef*/

    uint32_t AdcDriveType;                 /*!< Select ADC Driving mode, please refer to the type ADC_Drv_TypeDef*/

    uint32_t AdcCkDiv;                     /*!< ADC division coefficient ranges from 1 to 128 */
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
  FunctionalState InjectedDiscontinuousConvMode;  /*!< Specifies whether the conversions sequence of injected group is performed in Complete-sequence/Discontinuous-sequence (main sequence subdivided in successive parts).
                                                       This parameter can be set to ENABLE or DISABLE. */
  FunctionalState AutoInjectedConv;               /*!< Enables or disables the selected ADC automatic injected group conversion after regular one
                                                       This parameter can be set to ENABLE or DISABLE.*/
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
} ADC_ChannelConfTypeDef;

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
    uint32_t WatchdogNumber; /*!< Reserved for future use, can be set to 0 */
} ADC_AnalogWDGConfTypeDef;

 /**
 *  @defgroup ADC_states_definition ADC states definition
 */
#define HAL_ADC_STATE_RESET 0x00000000U         /*!< ADC not yet initialized or disabled */
#define HAL_ADC_STATE_READY 0x00000001U         /*!< ADC peripheral ready for use */
#define HAL_ADC_STATE_BUSY_INTERNAL 0x00000002U /*!< ADC is busy to internal process  */
#define HAL_ADC_STATE_TIMEOUT 0x00000004U       /*!< TimeOut occurrence */

/**
 *  @defgroup ADC_errors ADC errors
 */
#define HAL_ADC_STATE_ERROR_INTERNAL 0x00000010U /*!< Internal error occurrence */
#define HAL_ADC_STATE_ERROR_CONFIG 0x00000020U   /*!< Configuration error occurrence */
#define HAL_ADC_STATE_ERROR_DMA 0x00000040U      /*!< DMA error occurrence */

/**
 *  @defgroup States_of_ADC_group_regular States of ADC group regular
 */
#define HAL_ADC_STATE_REG_BUSY 0x00000100U  /*!< A conversion on group regular is ongoing or can occur  */
#define HAL_ADC_STATE_REG_EOC 0x00000200U   /*!< Conversion data available on group regular */
#define HAL_ADC_STATE_REG_OVR 0x00000400U   /*!< Not available on  device: Overrun occurrence */
#define HAL_ADC_STATE_REG_EOSMP 0x00000800U /*!< Not available on  device: End Of Sampling flag raised  */

/**
 *  @defgroup States_of_ADC_group_injected States of ADC group injected
 */
#define HAL_ADC_STATE_INJ_BUSY 0x00001000U  /*!< A conversion on group injected is ongoing or can occur  */
#define HAL_ADC_STATE_INJ_EOC 0x00002000U   /*!< Conversion data available on group injected */
#define HAL_ADC_STATE_INJ_JQOVF 0x00004000U /*!< Not available on  device: Injected queue overflow occurrence */

/**
 *  @defgroup States_of_ADC_analog_watchdogs States of ADC analog watchdogs
 */ 
#define HAL_ADC_STATE_AWD1 0x00010000U      /*!< Out-of-window occurrence of analog watchdog 1 */
#define HAL_ADC_STATE_AWD2 0x00020000U      /*!< Not available on  device: Out-of-window occurrence of analog watchdog 2 */
#define HAL_ADC_STATE_AWD3 0x00040000U      /*!< Not available on  device: Out-of-window occurrence of analog watchdog 3 */

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

    HAL_LockTypeDef Lock;                   /*!< ADC locking object */

    volatile uint32_t State;                /*!< ADC communication state (bitmap of ADC states) */

    volatile uint32_t ErrorCode;            /*!< ADC Error code */

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

/**
  * @brief  HAL ADC Callback ID enumeration definition
  */
typedef enum
{
    HAL_ADC_CONVERSION_COMPLETE_CB_ID = 0x00U,     /*!< ADC conversion complete callback ID */
    HAL_ADC_CONVERSION_HALF_CB_ID = 0x01U,         /*!< ADC conversion DMA half-transfer callback ID */
    HAL_ADC_LEVEL_OUT_OF_WINDOW_1_CB_ID = 0x02U,   /*!< ADC analog watchdog 1 callback ID */
    HAL_ADC_ERROR_CB_ID = 0x03U,                   /*!< ADC error callback ID */
    HAL_ADC_INJ_CONVERSION_COMPLETE_CB_ID = 0x04U, /*!< ADC group injected conversion complete callback ID */
    HAL_ADC_MSPINIT_CB_ID = 0x09U,                 /*!< ADC Msp Init callback ID          */
    HAL_ADC_MSPDEINIT_CB_ID = 0x0AU                /*!< ADC Msp DeInit callback ID        */
} HAL_ADC_CallbackIDTypeDef;


/* Exported constants --------------------------------------------------------*/

/** 
 *  @defgroup ADC_Error_Code ADC Error Code
*/
#define HAL_ADC_ERROR_NONE 0x00U     /*!< No error                                              */
#define HAL_ADC_ERROR_INTERNAL 0x01U /*!< ADC IP internal error: if problem of clocking, enable/disable, erroneous state                       */
#define HAL_ADC_ERROR_OVR 0x02U      /*!< Overrun error                                         */
#define HAL_ADC_ERROR_DMA 0x04U      /*!< DMA transfer error                                    */
#define HAL_ADC_ERROR_INVALID_CALLBACK (0x10U) /*!< Invalid Callback error */


/** 
 *  @defgroup ADC_Data_align ADC data alignment
*/
#define ADC_DATAALIGN_RIGHT 0x00000000U
#define ADC_DATAALIGN_LEFT ((uint32_t)ADC_ALIGN_MASK)


/**
 *  @defgroup ADC_Scan_mode ADC scan mode
*/
#define ADC_SCAN_DISABLE 0x00000000U
#define ADC_SCAN_ENABLE ((uint32_t)ADC_SCAN_MASK)


/** 
 * @defgroup ADC_External_trigger_edge_Regular ADC external trigger enable 
*/
#define ADC_PIS_TRIG                       0x00000000U
#define ADC_REGULAR_SOFTWARE_TRIGT         ADC_RTRIG_MASK
#define ADC_INJECTED_SOFTWARE_TRIGT        ADC_JTRIG_MASK 


/** 
 *  @defgroup ADC_Clock_Division ADC Clock Division
*/               
#define ADC_CLOCK_DIV2          0x00000001U                 
#define ADC_CLOCK_DIV4          0x00000002U                 
#define ADC_CLOCK_DIV8          0x00000003U                 
#define ADC_CLOCK_DIV16         0x00000004U               
#define ADC_CLOCK_DIV32         0x00000005U                 
#define ADC_CLOCK_DIV64         0x00000006U                 
#define ADC_CLOCK_DIV128        0x00000007U  

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
  * @brief  ADC conversion cycles
  * @note   Selected sampling time + conversion time of 15 ADC clock cycles, with resolution 12 bits
  */
#define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_1CYCLE                  13U
#define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_2CYCLES                 14U
#define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_4CYCLES                 16U
#define ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_15CYCLES                27U

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
#define ADC_CHANNEL_8               0x00000008U
#define ADC_CHANNEL_TEMPSENSOR      0x00000009U  /* ADC internal channel (no connection on device pin) */
#define ADC_CHANNEL_VBAT            0x0000000AU  /* ADC internal channel (no connection on device pin) */
#define ADC_CHANNEL_VREFINT         0x0000000BU  /* ADC internal channel (no connection on device pin) */


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
 * @defgroup ADC_analog_watchdog_mode ADC analog watchdog mode
*/
#define ADC_ANALOGWATCHDOG_NONE                             0x00000000U
#define ADC_ANALOGWATCHDOG_SINGLE_REG           ((uint32_t)(ADC_AWDSGL_MASK | ADC_RAWDEN_MASK))
#define ADC_ANALOGWATCHDOG_SINGLE_INJEC         ((uint32_t)(ADC_AWDSGL_MASK | ADC_JAWDEN_MASK))
#define ADC_ANALOGWATCHDOG_SINGLE_REGINJEC      ((uint32_t)(ADC_AWDSGL_MASK | ADC_RAWDEN_MASK | ADC_JAWDEN_MASK))
#define ADC_ANALOGWATCHDOG_ALL_REG              ((uint32_t)ADC_RAWDEN_MASK)
#define ADC_ANALOGWATCHDOG_ALL_INJEC            ((uint32_t)ADC_JAWDEN_MASK)
#define ADC_ANALOGWATCHDOG_ALL_REGINJEC         ((uint32_t)(ADC_RAWDEN_MASK | ADC_JAWDEN_MASK))


/** 
 * @defgroup ADC_interrupts_definition ADC interrupts definition
*/
#define ADC_IT_EOC   ADC_REOCIE_MASK       /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_EOS   ADC_REOSIE_MASK       /*!< ADC regular end of sequence conversions interrupt source */
#define ADC_IT_JEOC  ADC_JEOCIE_MASK       /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IT_JEOS  ADC_JEOSIE_MASK       /*!< ADC Injected end of sequence conversions interrupt source */
#define ADC_IT_AWD   ADC_AWDIE_MASK        /*!< ADC Analog watchdog interrupt source */


/** 
 * @defgroup ADC_flags_definition ADC flags definition
*/
#define ADC_FLAG_STRT   ADC_RSTRTC_MASK   /*!< ADC Regular group start flag */
#define ADC_FLAG_JSTRT  ADC_JSTRTC_MASK   /*!< ADC Injected group start flag */
#define ADC_FLAG_EOC    ADC_REOC_MASK     /*!< ADC End of Regular conversion flag */
#define ADC_FLAG_EOS    ADC_REOS_MASK     /*!< ADC regular end of sequence conversions flag */
#define ADC_FLAG_JEOC   ADC_JEOC_MASK     /*!< ADC End of Injected conversion flag */
#define ADC_FLAG_JEOS   ADC_JEOS_MASK     /*!< ADC Injected end of sequence conversions flag */
#define ADC_FLAG_AWD    ADC_AWD_MASK      /*!< ADC Analog watchdog flag */

/** 
  * @brief ADC Event type
  */
#define ADC_AWD_EVENT ((uint32_t)ADC_FLAG_AWD) /*!< ADC Analog watchdog event */
#define ADC_AWD1_EVENT ADC_AWD_EVENT /*!< ADC Analog watchdog 1 event: Alternate naming for compatibility with other devices having several analog watchdogs */


/* Combination of all post-conversion flags bits: EOC/EOS, JEOC/JEOS, OVR, AWDx */
#define ADC_FLAG_POSTCONV_ALL (ADC_FLAG_EOS | ADC_FLAG_EOC | ADC_FLAG_JEOC | ADC_FLAG_JEOS | ADC_FLAG_AWD)


/**
  * @brief Enable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_ENABLE(__HANDLE__) \
    (SET_BIT((__HANDLE__)->Instance->CR2, (ADC_ADEN_MASK)))

/**
  * @brief Disable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_DISABLE(__HANDLE__) \
    (CLEAR_BIT((__HANDLE__)->Instance->CR2, (ADC_ADEN_MASK)))

/** @brief Enable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  *          This parameter can be any combination of the following values:
  *            @arg ADC_IT_EOC: ADC End of Regular Conversion interrupt source
  *            @arg ADC_IT_EOS：ADC regular end of sequence conversions interrupt source 
  *            @arg ADC_IT_JEOC: ADC End of Injected Conversion interrupt source
  *            @arg ADC_IT_JEOS：ADC Injected end of sequence conversions interrupt source
  *            @arg ADC_IT_AWD: ADC Analog watchdog interrupt source
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
    (SET_BIT((__HANDLE__)->Instance->CR1, (__INTERRUPT__)))

/** @brief Disable the ADC end of conversion interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt
  *          This parameter can be any combination of the following values:
  *            @arg ADC_IT_EOC: ADC End of Regular Conversion interrupt source
  *            @arg ADC_IT_EOS：ADC regular end of sequence conversions interrupt source 
  *            @arg ADC_IT_JEOC: ADC End of Injected Conversion interrupt source
  *            @arg ADC_IT_JEOS：ADC Injected end of sequence conversions interrupt source
  *            @arg ADC_IT_AWD: ADC Analog watchdog interrupt source
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__) \
    (CLEAR_BIT((__HANDLE__)->Instance->CR1, (__INTERRUPT__)))

/** @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC interrupt source to check
  *          This parameter can be any combination of the following values:
  *            @arg ADC_IT_EOC: ADC End of Regular Conversion interrupt source
  *            @arg ADC_IT_EOS：ADC regular end of sequence conversions interrupt source 
  *            @arg ADC_IT_JEOC: ADC End of Injected Conversion interrupt source
  *            @arg ADC_IT_JEOS：ADC Injected end of sequence conversions interrupt source
  *            @arg ADC_IT_AWD: ADC Analog watchdog interrupt source
  * @retval None
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) \
    (((__HANDLE__)->Instance->CR1 & (__INTERRUPT__)) == (__INTERRUPT__))


/** @brief Get the selected ADC's flag status.
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  *          This parameter can be any combination of the following values:
  *            @arg ADC_FLAG_STRT: ADC Regular group start flag
  *            @arg ADC_FLAG_JSTRT: ADC Injected group start flag
  *            @arg ADC_FLAG_EOC: ADC End of Regular conversion flag
  *            @arg ADC_FLAG_EOS：ADC regular end of sequence conversions flag 
  *            @arg ADC_FLAG_JEOC: ADC End of Injected conversion flag
  *            @arg ADC_FLAG_JEOS：ADC Injected end of sequence conversions flag 
  *            @arg ADC_FLAG_AWD: ADC Analog watchdog flag
  * @retval None
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__) \
    ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))


/** @brief Clear the ADC's pending flags
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag
  *          This parameter can be any combination of the following values:
  *            @arg ADC_FLAG_STRT: ADC Regular group start flag
  *            @arg ADC_FLAG_JSTRT: ADC Injected group start flag
  *            @arg ADC_FLAG_EOC: ADC End of Regular conversion flag
  *            @arg ADC_FLAG_EOS：ADC regular end of sequence conversions flag 
  *            @arg ADC_FLAG_JEOC: ADC End of Injected conversion flag
  *            @arg ADC_FLAG_JEOS：ADC Injected end of sequence conversions flag 
  *            @arg ADC_FLAG_AWD: ADC Analog watchdog flag
  * @retval None
  */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__) \
    (WRITE_REG((__HANDLE__)->Instance->SFCR, __FLAG__))

/** @brief  Reset ADC handle state
  * @param  __HANDLE__: ADC handle
  * @retval None
  */

#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__)   \
    do                                             \
    {                                              \
        (__HANDLE__)->State = HAL_ADC_STATE_RESET; \
        (__HANDLE__)->MspInitCallback = NULL;      \
        (__HANDLE__)->MspDeInitCallback = NULL;    \
    } while (0)


/* Private macro ------------------------------------------------------------*/

/** 
 * @defgroup ADC_Private_Macros ADC Private Macros
*/


/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

#define ADC_CONVCYCLES_MAX_RANGE(__HANDLE__)  ADC_CONVERSIONCLOCKCYCLES_SAMPLETIME_15CYCLES
/**
  * @brief Verification of ADC state: enabled or disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
#define ADC_IS_ENABLE(__HANDLE__) \
    (((((__HANDLE__)->Instance->CR2 & ADC_ADEN_MASK) == ADC_ADEN_MASK)) ? SET : RESET)

/**
  * @brief Test if conversion trigger of regular group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define ADC_IS_SOFTWARE_START_REGULAR(__HANDLE__) \
    ((__HANDLE__)->Init.TrigType == ADC_RTRIG_MASK)

/**
  * @brief Test if conversion trigger of injected group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define ADC_IS_SOFTWARE_START_INJECTED(__HANDLE__) \
    ((__HANDLE__)->Init.TrigType == ADC_JTRIG_MASK)

/**
  * @brief Simultaneously clears and sets specific bits of the handle State
  * @note: ADC_STATE_CLR_SET() macro is merely aliased to generic macro MODIFY_REG(),
  *        the first parameter is the ADC handle State, the second parameter is the
  *        bit field to clear, the third and last parameter is the bit field to set.
  * @retval None
  */
#define ADC_STATE_CLR_SET MODIFY_REG
/**
  * @brief Clear ADC error code (set it to error code: "no error")
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define ADC_CLEAR_ERRORCODE(__HANDLE__) \
    ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)
/**
  * @brief Configures the number of discontinuous conversions for the regular group channels.
  * @param _NBR_DISCONTINUOUS_CONV_: Number of discontinuous conversions.
  * @retval None
  */
#define ADC_CR1_DISCONTINUOUS_NUM(_NBR_DISCONTINUOUS_CONV_) \
    (((_NBR_DISCONTINUOUS_CONV_)-1) << ADC_DISCNUM_POS)

/**
  * @brief Set ADC number of conversions into regular channel sequence length.
  * @param _NbrOfConversion_: Regular channel sequence length 
  * @retval None
  */
#define ADC_SQLR_SHIFT(_NbrOfConversion_)                                    \
  (((_NbrOfConversion_) - (uint8_t)1) << ADC_RSQL_POS)

#define GET_SQLR_SHIFT(_NbrOfConversion_)                                    \
  ((_NbrOfConversion_) >> ADC_RSQL_POS)

/**
  * @brief Set the ADC's sample time for channel numbers between 0 and 11.
  * @param _SAMPLETIME_: Sample time parameter.
  * @param _CHANNELNB_: Channel number.  
  * @retval None
  */
#define ADC_SMPR1(_SAMPLETIME_, _CHANNELNB_) \
    ((_SAMPLETIME_) << (ADC_SMP1_POS * (_CHANNELNB_)))


/**
  * @brief Set the selected regular channel rank for rank between 7 and 12.
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.    
  * @retval None
  */
#define ADC_SQR1_RK(_CHANNELNB_, _RANKNB_)                                     \
  ((_CHANNELNB_) << (ADC_RSQ2_POS * ((_RANKNB_)-1)))

#define ADC_SQR2_RK(_CHANNELNB_, _RANKNB_)                                     \
  ((_CHANNELNB_) << (ADC_RSQ10_POS * ((_RANKNB_) - 9)))


/**
  * @brief Set the injected sequence length.
  * @param _JSQR_JL_: Sequence length.
  * @retval None
  */
#define ADC_JSQR_JL_SHIFT(_JSQR_JL_)                                           \
  (((_JSQR_JL_) -1) << ADC_JSQL_POS)


/**
  * @brief Set the selected injected channel rank
  * @param _CHANNELNB_: Channel number.
  * @param _RANKNB_: Rank number.
  * @retval None
  */
#define ADC_JSQR_RK_JL(_CHANNELNB_, _RANKNB_)                       \
  ((_CHANNELNB_) << (ADC_JSQ2_POS * ((_RANKNB_)-1)))

/**
  * @brief Enable ADC scan mode to convert multiple ranks with sequencer.
  * @param _SCAN_MODE_: Scan conversion mode.
  * @retval None
  */

#define ADC_CR1_SCAN_SET(_SCAN_MODE_) \
    ((((_SCAN_MODE_) == ADC_SCAN_ENABLE) || ((_SCAN_MODE_) == ENABLE)) ? (ADC_SCAN_ENABLE) : (ADC_SCAN_DISABLE))

#define IS_ADC_ALL_INSTANCE(Instance) ((Instance) == LSADC)

#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                  ((ALIGN) == ADC_DATAALIGN_LEFT))

#define IS_ADC_SCAN_MODE(SCAN_MODE) (((SCAN_MODE) == ADC_SCAN_DISABLE) || \
                                     ((SCAN_MODE) == ADC_SCAN_ENABLE))

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

#define IS_ADC_TRIGTYPE_EDGE(EDGE) (((EDGE) == ADC_TRIGCONVEDGE_PIS)  || \
                                   ((EDGE) == ADC_TRIGType_SOFTWARE)  )

#define IS_ADC_EVENT_TYPE(EVENT) ((EVENT) == ADC_AWD_EVENT)

#define IS_VREF_SWITCH(VREF)    (((VREF) == ADC_VREF_VCC)     || \
                                ((VREF) == ADC_VREF_EXPOWER)  || \
                                ((VREF) == ADC_VREF_INSIDE)  )

/**  
  * @brief ADC_range_verification ADC range verification For a unique ADC resolution: 12 bits
  */
#define IS_ADC_RANGE(ADC_VALUE) ((ADC_VALUE) <= 0x0FFFU)

/**  
  * @brief ADC_regular_nb_conv_verification ADC regular nb conv verification
  */
#define IS_ADC_REGULAR_NB_CONV(LENGTH) (((LENGTH) >= 1U) && ((LENGTH) <= 16U))

/**  
  * @brief ADC_regular_discontinuous_mode_number_verification ADC regular discontinuous mode number verification
  */
#define IS_ADC_REGULAR_DISCONT_NUMBER(NUMBER) (((NUMBER) >= 1U) && ((NUMBER) <= 8U))


#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_CHANNEL_0)           || \
                                 ((CHANNEL) == ADC_CHANNEL_1)           || \
                                 ((CHANNEL) == ADC_CHANNEL_2)           || \
                                 ((CHANNEL) == ADC_CHANNEL_3)           || \
                                 ((CHANNEL) == ADC_CHANNEL_4)           || \
                                 ((CHANNEL) == ADC_CHANNEL_5)           || \
                                 ((CHANNEL) == ADC_CHANNEL_6)           || \
                                 ((CHANNEL) == ADC_CHANNEL_7)           || \
                                 ((CHANNEL) == ADC_CHANNEL_8)           || \
                                 ((CHANNEL) == ADC_CHANNEL_TEMPSENSOR)  || \
                                 ((CHANNEL) == ADC_CHANNEL_VREFINT)     || \
                                 ((CHANNEL) == ADC_CHANNEL_VBAT)       )

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_1CYCLE)    || \
                                  ((TIME) == ADC_SAMPLETIME_2CYCLES)    || \
                                  ((TIME) == ADC_SAMPLETIME_4CYCLES)    || \
                                  ((TIME) == ADC_SAMPLETIME_15CYCLES)  )

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

#define IS_ADC_ANALOG_WATCHDOG_MODE(WATCHDOG) (((WATCHDOG) == ADC_ANALOGWATCHDOG_NONE)             || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REG)       || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)     || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)  || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REG)          || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_INJEC)        || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REGINJEC)       )


#define ADC_MULTIMODE_AUTO_INJECTED(__HANDLE__)         (ADC1->CR1 & ADC_CR1_JAUTO)                                                \


#define IS_ADC_INJECTED_RANK(CHANNEL) (((CHANNEL) == ADC_INJECTED_RANK_1) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_2) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_3) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_4))

/**
 * @brief ADCEx_injected_nb_conv_verification ADCEx injected nb conv verification
 */
#define IS_ADC_INJECTED_NB_CONV(LENGTH)  (((LENGTH) >= 1U) && ((LENGTH) <= 4U))

/**
 * @brief Converts the sampled value of the temperature channel to the temperature value
 * @return  signed int16_t
 */
#define GET_ADC_TEMPSENSOR_VREF_INSIDE(adc_value)  (((((adc_value*140000)>>12)-27000)/118)-45)
#define GET_ADC_TEMPSENSOR_VREF_VCC(adc_value)     (((((adc_value*330000)>>12)-27000)/118)-45)


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
  * @brief  Enables ADC, starts conversion of regular group and transfers result through DMA.
  * @param  hadc: ADC handle
  * @param  pData: The destination Buffer address.
  * @param  Length: The length of data to be transferred from ADC peripheral to memory.
  * @param  Callback: function pointer.
  * @retval HAL status.
  */
 HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint16_t* pData, uint32_t Length, void (*Callback)(ADC_HandleTypeDef* hadc));

 /**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable ADC DMA transfer, disable 
  *         ADC peripheral.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
 HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);


/**
  * @brief  Get ADC regular group conversion result.
  * @param  hadc: ADC handle
  * @retval ADC group regular conversion data
  */
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);

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
  * @brief  ADC error callback in non blocking mode
  * @param  hadc: ADC handle
  */
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);

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
  * @brief  return the ADC state
  * @param  hadc: ADC handle
  * @retval HAL state
  */
uint32_t HAL_ADC_GetState(ADC_HandleTypeDef *hadc);

/**
  * @brief  Return the ADC error code
  * @param  hadc: ADC handle
  * @retval ADC Error Code
  */
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc);

/**
  * @brief  Injected conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  */
void  HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc);


/** @}*/


/** @}*/


#endif /* (_LSADC_H_) */
