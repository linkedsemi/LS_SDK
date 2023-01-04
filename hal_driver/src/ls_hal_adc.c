/**
  ******************************************************************************
  * @file    hal_lssdc.c
  * @author  AE Team
  * @brief   SPI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Serial Peripheral Interface (SPI) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "ls_hal_adc.h"
#include "ls_msp_adc.h" 
#include "field_manipulate.h"
#include "log.h"
#include "systick.h"

/* Includes ------------------------------------------------------------------*/

/** @addtogroup _HAL_Driver
  * @{
  */

/** @defgroup ADC ADC
  * @brief ADC HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */

/* Timeout values for ADC enable and disable settling time.                 */
/* Values defined to be higher than worst cases: low clocks freq,           */
/* maximum prescaler.                                                       */
/* Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock         */
/* prescaler 4, sampling time 12.5 ADC clock cycles, resolution 12 bits.    */
/* Unit: ms                                                                 */
#define ADC_ENABLE_TIMEOUT 2U
#define ADC_DISABLE_TIMEOUT 2U

/* Delay for ADC stabilization time.                                        */
/* Maximum delay is 1us (refer to device datasheet, parameter tSTAB).       */
/* Unit: us                                                                 */
#define ADC_STAB_DELAY_US 1U

/* Delay for temperature sensor stabilization time.                         */
/* Maximum delay is 10us (refer to device datasheet, parameter tSTART).     */
/* Unit: us                                                                 */
#define ADC_TEMPSENSOR_DELAY_US 10U

/* Delay for ADC calibration:                                               */
/* Hardware prerequisite before starting a calibration: the ADC must have   */
/* been in power-on state for at least two ADC clock cycles.                */
/* Unit: ADC clock cycles                                                   */
#define ADC_PRECALIBRATION_DELAY_ADCCLOCKCYCLES       2U

/* Timeout value for ADC calibration                                        */
/* Value defined to be higher than worst cases: low clocks freq,            */
/* maximum prescaler.                                                       */
/* Ex of profile low frequency : Clock source at 0.1 MHz, ADC clock         */
/* prescaler 4, sampling time 12.5 ADC clock cycles, resolution 12 bits.    */
/* Unit: ms                                                                 */
#define ADC_CALIBRATION_TIMEOUT          10U

/* Delay for temperature sensor stabilization time.                         */
/* Maximum delay is 10us (refer to device datasheet, parameter tSTART).     */
/* Unit: us                                                                 */
#define ADC_TEMPSENSOR_DELAY_US         10U

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */
/**
  * @}
  */


/** @defgroup ADC_Exported_Functions_Group1 Initialization/de-initialization functions 
  * @brief    Initialization and Configuration functions
  *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the ADC. 
      (+) De-initialize the ADC.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the ADC peripheral and regular group according to  
  *         parameters specified in structure "ADC_InitTypeDef".
  * @note   As prerequisite, ADC clock must be configured at RCC top level
  *         (clock source APB2).
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_InitTypeDef".
  * @note   This function configures the ADC within 2 scopes: scope of entire 
  *         ADC and scope of regular group. For parameters details, see comments 
  *         of structure "ADC_InitTypeDef".
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef tmp_hal_status = HAL_OK;
    uint32_t tmp_cr1 = 0U;
    uint32_t tmp_cr2 = 0U;
    uint32_t tmp_ccr = 0U;

    /* Check ADC handle */
    if (hadc == NULL)
    {
        return HAL_STATE_ERROR;
    }

    /* Check the parameters */
 //   LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
    LS_ASSERT(IS_ADC_DATA_ALIGN(hadc->Init.DataAlign));
    LS_ASSERT(IS_ADC_SCAN_MODE(hadc->Init.ScanConvMode));
    LS_ASSERT(IS_FUNCTIONAL_STATE(hadc->Init.ContinuousConvMode));
    LS_ASSERT(IS_VREF_SWITCH(hadc->Init.Vref));
 //   LS_ASSERT(IS_ADC_EXTTRIG(hadc->Init.ExternalTrigConv));

  if(hadc->Init.ScanConvMode != ADC_SCAN_DISABLE)
  {
    LS_ASSERT(IS_ADC_REGULAR_NB_CONV(hadc->Init.NbrOfConversion));
    LS_ASSERT(IS_FUNCTIONAL_STATE(hadc->Init.DiscontinuousConvMode));
    if(hadc->Init.DiscontinuousConvMode != DISABLE)
    {
      LS_ASSERT(IS_ADC_REGULAR_DISCONT_NUMBER(hadc->Init.NbrOfDiscConversion));
    }
  }
  /* Actions performed only if ADC is coming from state reset:                */
  /* - Initialization of ADC MSP                                              */
  if (hadc->State == HAL_ADC_STATE_RESET)
  {
    /* Initialize ADC error code */
    ADC_CLEAR_ERRORCODE(hadc);
    
    /* Allocate lock resource and initialize it */
    hadc->Lock = HAL_UNLOCKED;

  }

    HAL_ADC_MSP_Init(hadc);
    HAL_ADC_MSP_Busy_Set(hadc);

  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC peripheral */
  /* Note: In case of ADC already enabled, precaution to not launch an        */
  /*       unwanted conversion while modifying register CR2 by writing 1 to   */
  /*       bit ADON.                                                          */
  tmp_hal_status = ADC_ConversionStop_Disable(hadc);
  
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL) &&
      (tmp_hal_status == HAL_OK)                                  )
  {
    /* Set ADC state */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                      HAL_ADC_STATE_BUSY_INTERNAL);
    
    /* Set ADC parameters */
    
    /* Configuration of ADC_CR2:                                              */
    /*  - data alignment                                                      */
    /*  - continuous conversion mode                                          */  
    /*  - ADC driver type                                                     */ 
    tmp_cr2 |=hadc->Init.DataAlign;
  //  tmp_cr2 |=(0x00000003<<ADC_BATADJ_POS);
    if(hadc->Init.ContinuousConvMode == ENABLE)
    {
        tmp_cr2 |= ADC_CONT_MASK;
    }  

     tmp_cr2 |=   (hadc->Init.AdcDriveType == EINBUF_DRIVE_ADC) ?(ADC_EINBUF_MASK | ADC_BINRES_MASK):\
                   ((hadc->Init.AdcDriveType == INRES_ONETHIRD_EINBUF_DRIVE_ADC) ?(ADC_EINBUF_MASK):(ADC_BINBUF_MASK|ADC_BINRES_MASK));

    /* Update ADC configuration register CR2 with previous settings */
    MODIFY_REG(hadc->Instance->CR2,
                   ADC_CONT_MASK   |
                   ADC_BATADJ_MASK |
                   ADC_BINRES_MASK |
                   ADC_BINBUF_MASK |
                   ADC_EINBUF_MASK |
                   ADC_TEST_MASK   |
                   ADC_DIFF_MASK,
                   tmp_cr2);
    /* Configuration of ADC_CR1:                                              */
    /*  - scan mode                                                           */
    /*  - discontinuous mode disable/enable                                   */
    /*  - discontinuous mode number of conversions                            */
    tmp_cr1 |= hadc->Init.ScanConvMode;  
    /* Enable discontinuous mode only if continuous mode is disabled */
    /* Note: If parameter "Init.ScanConvMode" is set to disable, parameter    */
    /*       discontinuous is set anyway, but will have no effect on ADC HW.  */
    if (hadc->Init.DiscontinuousConvMode == ENABLE)
    {
      if (hadc->Init.ContinuousConvMode == DISABLE)
      {
        /* Enable the selected ADC regular discontinuous mode */
        /* Set the number of channels to be converted in discontinuous mode */
        tmp_cr1 |= (ADC_RDISCEN_MASK | ADC_CR1_DISCONTINUOUS_NUM(hadc->Init.NbrOfDiscConversion)) ;
      }
      else
      {
        /* ADC regular group settings continuous and sequencer discontinuous*/
        /* cannot be enabled simultaneously.                                */
        
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);
        
        /* Set ADC error code to ADC IP internal error */
        SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
      }
    }
    
    /* Update ADC configuration register CR1 with previous settings */
      MODIFY_REG(hadc->Instance->CR1,
                 ADC_SCAN_MASK    |
                 ADC_DISCNUM_MASK |
                 ADC_AWDCH_MASK  ,
                 tmp_cr1);
    
    /* Configuration of regular group sequencer:                              */
    /* - if scan mode is disabled, regular channels sequence length is set to */
    /*   0x00: 1 channel converted (channel on regular rank 1)                */
//    if (ADC_CR1_SCAN_SET(hadc->Init.ScanConvMode) == ADC_SCAN_ENABLE)
    {
        MODIFY_REG(hadc->Instance->SQLR,ADC_RSQL_MASK,
                                        ADC_SQLR_SHIFT(hadc->Init.NbrOfConversion));
    }
    /* Check back that ADC registers have effectively been configured to      */
    /* ensure of no potential problem of ADC core IP clocking.                */
    /* Check through register CR2 (excluding bits set in other functions:     */
    /* execution control bits (ADON, JSWSTART, SWSTART), regular group bits   */
    /* (DMA), injected group bits (JEXTTRIG and JEXTSEL), channel internal    */
    /* measurement path bit (TSVREFE).                                        */
    if (READ_BIT(hadc->Instance->CR2, ~(ADC_ADEN_MASK | ADC_DMAEN_MASK |
                                        ADC_RTRIG_MASK | ADC_JTRIG_MASK ))
         == tmp_cr2)
    {
      /* Set ADC error code to none */
      ADC_CLEAR_ERRORCODE(hadc);
      
      /* Set the ADC state */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_BUSY_INTERNAL,
                        HAL_ADC_STATE_READY);
    }
    else
    {
      /* Update ADC state machine to error */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_BUSY_INTERNAL,
                        HAL_ADC_STATE_ERROR_INTERNAL);
      
      /* Set ADC error code to ADC IP internal error */
      SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
      
      tmp_hal_status = HAL_ERROR;
    }
  
  }
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
        
    tmp_hal_status = HAL_ERROR;
  }

    /* Configuration of ADC_CCR:                                              */
    /*  - reference voltage                                                  */
    /*  - adc clk                                                             */
    /*  - discontinuous mode number of conversions                            */

    switch(hadc->Init.Vref)
    {
        case ADC_VREF_VCC:
            tmp_ccr = FIELD_BUILD(ADC_VRPS,1) | FIELD_BUILD(ADC_BP,1) | FIELD_BUILD(ADC_VRBUFEN,0) | FIELD_BUILD(ADC_VCMEN,1) | FIELD_BUILD(ADC_VREFEN,0);
         break;
         case ADC_VREF_EXPOWER:
            tmp_ccr = FIELD_BUILD(ADC_VRPS,2) | FIELD_BUILD(ADC_BP,1) | FIELD_BUILD(ADC_VRBUFEN,0) | FIELD_BUILD(ADC_VCMEN,1) | FIELD_BUILD(ADC_VREFEN,0);
         break;
         case ADC_VREF_INSIDE: //default
         default:
            tmp_ccr = FIELD_BUILD(ADC_VRPS,4) | FIELD_BUILD(ADC_BP,1) | FIELD_BUILD(ADC_VRBUFEN,1) | FIELD_BUILD(ADC_VCMEN,1) | FIELD_BUILD(ADC_VREFEN,1);
           break;
    }

     tmp_ccr |= FIELD_BUILD(ADC_MSBCAL, 2)  |
                FIELD_BUILD(ADC_LPCTL, 1)   |
                FIELD_BUILD(ADC_GCALV, 0)   |
                FIELD_BUILD(ADC_OCALV, 0)   |
	            FIELD_BUILD(ADC_CKDIV, (hadc->Init.AdcCkDiv==0)?(ADC_CLOCK_DIV32):hadc->Init.AdcCkDiv);

    MODIFY_REG(hadc->Instance->CCR,
                ADC_MSBCAL_MASK      |
                    ADC_VRPS_MASK   |
                    ADC_VRBUFEN_MASK |
                    ADC_BP_MASK      |
                    ADC_VCMEN_MASK   |
                    ADC_LPCTL_MASK   |
                    ADC_GCALV_MASK   |
                    ADC_OCALV_MASK   |
                    ADC_CKDIV_MASK,
                tmp_ccr);
    /* Return function status */
    return tmp_hal_status;
}
/**
  * @brief  Deinitialize the ADC peripheral registers to their default reset
  *         values, with deinitialization of the ADC MSP.
  *         If needed, the example code can be copied and uncommented into
  *         function HAL_ADC_MspDeInit().
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check ADC handle */
  if(hadc == NULL)
  {
     return HAL_ERROR;
  }
  
  /* Check the parameters */
 // LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Set ADC state */
  SET_BIT(hadc->State, HAL_ADC_STATE_BUSY_INTERNAL);
  
  /* Stop potential conversion on going, on regular and injected groups */
  /* Disable ADC peripheral */
  tmp_hal_status = ADC_ConversionStop_Disable(hadc);
  
  /* Configuration of ADC parameters if previous preliminary actions are      */ 
  /* correctly completed.                                                     */
  if (tmp_hal_status == HAL_OK)
  {
    /* ========== Reset ADC registers ========== */
    /* Reset register SR */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_POSTCONV_ALL);
                         
    /* Reset register CR1 */
    CLEAR_BIT(hadc->Instance->CR1, (ADC_RAWDEN_MASK  | ADC_JAWDEN_MASK  | ADC_DISCNUM_MASK | 
                                    ADC_JDISCEN_MASK | ADC_RDISCEN_MASK | ADC_JAUTO_MASK   | 
                                    ADC_AWDSGL_MASK  | ADC_SCAN_MASK    | ADC_JEOCIE_MASK  |   
                                    ADC_AWDIE_MASK   | ADC_REOCIE_MASK  | ADC_AWDCH_MASK    ));
    
    /* Reset register CR2 */
    CLEAR_BIT(hadc->Instance->CR2, (ADC_ALIGN_MASK   | ADC_DMAEN_MASK   |        
                                    ADC_CONT_MASK   |  ADC_ADEN_MASK   ));
    
    /* Reset register SMPR1 */
    CLEAR_BIT(hadc->Instance->SMPR1, 0xFFFFFF);

    /* Reset register JOFR1 */
    CLEAR_BIT(hadc->Instance->JOFR1, ADC_JOFF1_MASK);
    /* Reset register JOFR2 */
    CLEAR_BIT(hadc->Instance->JOFR2, ADC_JOFF2_MASK);
    /* Reset register JOFR3 */
    CLEAR_BIT(hadc->Instance->JOFR3, ADC_JOFF3_MASK);
    /* Reset register JOFR4 */
    CLEAR_BIT(hadc->Instance->JOFR4, ADC_JOFF4_MASK);
    
    /* Reset register HTR */
    CLEAR_BIT(hadc->Instance->HTR, ADC_HT_MASK);
    /* Reset register LTR */
    CLEAR_BIT(hadc->Instance->LTR, ADC_LT_MASK);
    
    /* Reset register SQR1 */
    CLEAR_BIT(hadc->Instance->RSQR1, ADC_RSQ1_MASK | ADC_RSQ2_MASK | ADC_RSQ3_MASK |
                                     ADC_RSQ4_MASK | ADC_RSQ5_MASK | ADC_RSQ6_MASK |
                                     ADC_RSQ7_MASK | ADC_RSQ8_MASK  );
    
    /* Reset register SQR2 */
    CLEAR_BIT(hadc->Instance->RSQR2, ADC_RSQ9_MASK | ADC_RSQ10_MASK | ADC_RSQ11_MASK | 
                                    ADC_RSQ12_MASK);
    
    /* Reset register JSQR */
    CLEAR_BIT(hadc->Instance->JSQR, ADC_JSQ1_MASK | ADC_JSQ2_MASK | ADC_JSQ3_MASK | 
                                    ADC_JSQ4_MASK);

    HAL_ADC_MSP_DeInit(hadc);
    HAL_ADC_MSP_Idle_Set(hadc);  

    /* Set ADC error code to none */
    ADC_CLEAR_ERRORCODE(hadc);
    
    /* Set ADC state */
    hadc->State = HAL_ADC_STATE_RESET; 
  
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Enables ADC, starts conversion of regular group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef tmp_hal_status = HAL_OK;

    /* Check the parameters */
   // LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
    
    /* Process locked */
    __HAL_LOCK(hadc);
    
    /* Enable the ADC peripheral */
    tmp_hal_status = ADC_Enable(hadc);
    
    /* Start conversion if ADC is effectively enabled */
    if (tmp_hal_status == HAL_OK)
    {
        /* Set ADC state                                                          */
        /* - Clear state bitfield related to regular group conversion results     */
        /* - Set state bitfield related to regular operation                      */
        ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_READY | HAL_ADC_STATE_REG_EOC,
                        HAL_ADC_STATE_REG_BUSY);
        
        /* If conversions on group regular are also triggering group injected,  */
        /* update ADC state.                                                    */
        if (READ_BIT(hadc->Instance->CR1, ADC_JAUTO_MASK) != RESET)
        {
            ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_INJ_EOC, HAL_ADC_STATE_INJ_BUSY);  
        }

        
        /* State machine update: Check if an injected conversion is ongoing */
        if (HAL_IS_BIT_SET(hadc->State, HAL_ADC_STATE_INJ_BUSY))
        {
            /* Reset ADC error code fields related to conversions on group regular */
            CLEAR_BIT(hadc->ErrorCode, (HAL_ADC_ERROR_OVR | HAL_ADC_ERROR_DMA));         
        }
        else
        {
        /* Reset ADC all error code fields */
        ADC_CLEAR_ERRORCODE(hadc);
        }
        
        /* Process unlocked */
        /* Unlock before starting ADC conversions: in case of potential           */
        /* interruption, to let the process to ADC IRQ Handler.                   */
        __HAL_UNLOCK(hadc);
    
        /* Clear regular group conversion flag */
        /* (To ensure of no unknown state from potential previous ADC operations) */
        __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOS | ADC_FLAG_EOC);
        
        /* Enable conversion of regular group.                                    */
        /* If software start has been selected, conversion starts immediately.    */
        /* If external trigger has been selected, conversion will start at next   */
        /* trigger event.                                                         */
        if ( ADC_IS_SOFTWARE_START_REGULAR(hadc)) 
        {
            /* Start ADC conversion on regular group with SW start */
            SET_BIT(hadc->Instance->CR2, ADC_RTRIG_MASK);
        }

    }
    else
    {
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
    }
    
    /* Return function status */
    return tmp_hal_status;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected channels in 
  *         case of auto_injection mode), disable ADC peripheral.
  * @note:  ADC peripheral disable is forcing stop of potential 
  *         conversion on injected group. If injected group is under use, it
  *         should be preliminarily stopped using HAL_ADCEx_InjectedStop function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef tmp_hal_status = HAL_OK;

    /* Check the parameters */
    //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
        
    /* Process locked */
    __HAL_LOCK(hadc);
    
    /* Stop potential conversion on going, on regular and injected groups */
    /* Disable ADC peripheral */
    tmp_hal_status = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
        /* Set ADC state */
        ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                        HAL_ADC_STATE_READY);
    }
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    
    /* Return function status */
    return tmp_hal_status;
}

static bool adc_flag_poll(va_list va)
{
    ADC_HandleTypeDef *hadc = va_arg(va,ADC_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
      if (hadc->Instance->SR & flag)
      {
        return true;
      }
      else
      {
        return false;
      }
}

/**
  * @brief  Wait for regular group conversion to be completed.
  * @note   This function cannot be used in a particular setup: ADC configured 
  *         in DMA mode.
  *         In this case, DMA resets the flag EOC and polling cannot be
  *         performed on each conversion.
  * @note   Limitation in case of sequencer enabled
  *         (several ranks selected): polling cannot be done on each 
  *         conversion inside the sequence. In this case, polling is replaced by
  *         wait for maximum conversion time.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart = 0U;
  uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
  /* Check the parameters */
  //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Get tick count */
  tickstart = systick_get_value();
  
  /* Verification that ADC configuration is compliant with polling for        */
  /* each conversion:                                                         */
  /* Particular case is ADC configured in DMA mode                            */
  if (HAL_IS_BIT_SET(hadc->Instance->CR2, ADC_DMAEN_MASK))
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    
    return HAL_ERROR;
  }
  
  /* Polling for end of conversion: differentiation if single/sequence        */
  /* conversion.                                                              */
  /*  - If single conversion for regular group (Scan mode disabled or enabled */
  /*    with NbrOfConversion =1), flag EOC is used to determine the           */
  /*    conversion completion.                                                */
  /*  - If sequence conversion for regular group (scan mode enabled and       */
  /*    NbrOfConversion >=2), flag EOC is set only at the end of the          */
  /*    sequence.                                                             */
  /*    To poll for each conversion, the maximum conversion time is computed  */
  /*    from ADC conversion time (selected sampling time + conversion time of */
  /*    12.5 ADC clock cycles) and APB2/ADC clock prescalers (depending on    */
  /*    settings, conversion time range can be from 28 to 32256 CPU cycles).  */
  /*    As flag EOC is not set after each conversion, no timeout status can   */
  /*    be set.                                                               */
  if (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_SCAN_MASK) &&
      HAL_IS_BIT_CLR(GET_SQLR_SHIFT(hadc->Instance->SQLR), ADC_RSQL_MASK)    )
  {
    /* Wait until End of Conversion flag is raised */
    if(systick_poll_timeout(tickstart,timeout,adc_flag_poll,hadc,ADC_FLAG_EOC))
    {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
    }   
  }
  else
  {
    if(systick_poll_timeout(tickstart,timeout,adc_flag_poll,hadc,ADC_FLAG_EOS))
    {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
    } 
  }
  
  /* Clear regular group conversion flag */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOS | ADC_FLAG_EOC);
  
  /* Update ADC state machine */
  SET_BIT(hadc->State, HAL_ADC_STATE_REG_EOC);
  
  /* Determine whether any further conversion upcoming on group regular       */
  /* by external trigger, continuous mode or scan sequence on going.          */
  if(hadc->Init.ContinuousConvMode == DISABLE)
  {   
    /* Set ADC state */
    CLEAR_BIT(hadc->State, HAL_ADC_STATE_REG_BUSY);   

    if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_INJ_BUSY))
    { 
      SET_BIT(hadc->State, HAL_ADC_STATE_READY);
    }
  }
  
  /* Return ADC state */
  return HAL_OK;
}


/**
  * @brief  Poll for conversion event.
  * @param  hadc: ADC handle
  * @param  EventType: the ADC event type.
  *          This parameter can be one of the following values:
  *            @arg ADC_AWD_EVENT: ADC Analog watchdog event.
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout)
{
  uint32_t tickstart = 0U; 
  uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
  /* Check the parameters */
  //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
  LS_ASSERT(IS_ADC_EVENT_TYPE(EventType));
  
  /* Get tick count */
  tickstart = systick_get_value();
  
  /* Check selected event flag */
    if(systick_poll_timeout(tickstart,timeout,adc_flag_poll,hadc,EventType))
    {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
    }
  
  /* Analog watchdog (level out of window) event */
  /* Set ADC state */
  SET_BIT(hadc->State, HAL_ADC_STATE_AWD1);
    
  /* Clear ADC analog watchdog flag */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_AWD);
  
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Enables ADC, starts conversion of injected group.
  *         Interruptions enabled in this function: None.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Set ADC state                                                          */
    /* - Clear state bitfield related to injected group conversion results    */
    /* - Set state bitfield related to injected operation                     */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_INJ_EOC,
                      HAL_ADC_STATE_INJ_BUSY);
     
    /* Check if a regular conversion is ongoing */
    /* Note: On this device, there is no ADC error code fields related to     */
    /*       conversions on group injected only. In case of conversion on     */
    /*       going on group regular, no error code is reset.                  */
    if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_REG_BUSY))
    {
      /* Reset ADC all error code fields */
      ADC_CLEAR_ERRORCODE(hadc);
    }
    
    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential           */
    /* interruption, to let the process to ADC IRQ Handler.                   */
    __HAL_UNLOCK(hadc);
    
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOC | ADC_FLAG_JEOS);
        
    /* Enable conversion of injected group.                                   */
    /* If software start has been selected, conversion starts immediately.    */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* If automatic injected conversion is enabled, conversion will start     */
    /* after next regular group conversion.                                   */
    /* Case of multimode enabled (for devices with several ADCs): if ADC is   */
    /* slave, ADC is enabled only (conversion is not started). If ADC is      */
    /* master, ADC is enabled and conversion is started.                      */
    if (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_JAUTO_MASK))
    {
      if (ADC_IS_SOFTWARE_START_INJECTED(hadc))
      {
        /* Start ADC conversion on injected group with SW start */
        SET_BIT(hadc->Instance->CR2, ADC_JTRIG_MASK );
      }
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Stop conversion of injected channels. Disable ADC peripheral if
  *         no regular conversion is on going.
  * @note   If ADC must be disabled and if conversion is on going on 
  *         regular group, function HAL_ADC_Stop must be used to stop both
  *         injected and regular groups, and disable the ADC.
  * @note   If injected group mode auto-injection is enabled,
  *         function HAL_ADC_Stop must be used.
  * @note   In case of auto-injection mode, HAL_ADC_Stop must be used.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Stop potential conversion and disable ADC peripheral                     */
  /* Conditioned to:                                                          */
  /* - No conversion on the other group (regular group) is intended to        */
  /*   continue (injected and regular groups stop conversion and ADC disable  */
  /*   are common)                                                            */
  /* - In case of auto-injection mode, HAL_ADC_Stop must be used.             */
  if(((hadc->State & HAL_ADC_STATE_REG_BUSY) == RESET)  &&
     HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_JAUTO_MASK)   )
  {
    /* Stop potential conversion on going, on regular and injected groups */
    /* Disable ADC peripheral */
    tmp_hal_status = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                        HAL_ADC_STATE_READY);
    }
  }
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);
      
    tmp_hal_status = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}


/**
  * @brief  Wait for injected group conversion to be completed.
  * @param  hadc: ADC handle
  * @param  Timeout: Timeout value in millisecond.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t timeout = SYSTICK_MS2TICKS(Timeout);

  /* Variables for polling in case of scan mode enabled and polling for each  */
  /* conversion.                                                              */
  uint32_t Conversion_Timeout_CPU_cycles = 0U;
  uint32_t Conversion_Timeout_CPU_cycles_max = 0U;
  
  /* Check the parameters */
  //assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Get timeout */
  tickstart = systick_get_value(); 
     
  if ((hadc->Instance->SQLR & ADC_JSQL_MASK) == RESET)
  {
    /* Wait until End of Conversion flag is raised */
    if(systick_poll_timeout(tickstart,timeout,adc_flag_poll,hadc,ADC_FLAG_JEOC | ADC_FLAG_JEOS))
    {
        /* Update ADC state machine to timeout */
        SET_BIT(hadc->State, HAL_ADC_STATE_TIMEOUT);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
        
        return HAL_TIMEOUT;
    }
  }
  else
  {
    /* Replace polling by wait for maximum conversion time */
    /*  - Computation of CPU clock cycles corresponding to ADC clock cycles   */
    /*    and ADC maximum conversion cycles on all channels.                  */
    /*  - Wait for the expected ADC clock cycles delay                        */
    Conversion_Timeout_CPU_cycles_max = (ADC_CLOCK * ADC_CONVCYCLES_MAX_RANGE(hadc));
    
    while(Conversion_Timeout_CPU_cycles < Conversion_Timeout_CPU_cycles_max)
    {
      /* Check if timeout is disabled (set to infinite wait) */
      Conversion_Timeout_CPU_cycles ++;
    }
  }

  /* Clear injected group conversion flag */
  /* simultaneously.                                                          */
  __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JSTRT | ADC_FLAG_JEOC | ADC_FLAG_EOC);
  
  /* Update ADC state machine */
  SET_BIT(hadc->State, HAL_ADC_STATE_INJ_EOC);
  
  /* Determine whether any further conversion upcoming on group injected      */
  /* by external trigger or by automatic injected conversion                  */
  /* from group regular.                                                      */
  if(ADC_IS_SOFTWARE_START_INJECTED(hadc)                     || 
     (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_JAUTO_MASK) &&     
     (ADC_IS_SOFTWARE_START_REGULAR(hadc)        &&
      (hadc->Init.ContinuousConvMode == DISABLE)   )        )   )
  {
    /* Set ADC state */
    CLEAR_BIT(hadc->State, HAL_ADC_STATE_INJ_BUSY);   
    
    if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_REG_BUSY))
    {
      SET_BIT(hadc->State, HAL_ADC_STATE_READY);
    }
  }
  
  /* Return ADC state */
  return HAL_OK;
}

/**
  * @brief  Enables ADC, starts conversion of regular group with interruption.
  *         Interruptions enabled in this function:
  *          - EOC (end of conversion of regular group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef tmp_hal_status = HAL_OK;

    /* Check the parameters */
    //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));

    /* Process locked */
    __HAL_LOCK(hadc);

    /* Enable the ADC peripheral */
    tmp_hal_status = ADC_Enable(hadc);

    /* Start conversion if ADC is effectively enabled */
    if (tmp_hal_status == HAL_OK)
    {
        /* Set ADC state                                                          */
        /* - Clear state bitfield related to regular group conversion results     */
        /* - Set state bitfield related to regular operation                      */
        ADC_STATE_CLR_SET(hadc->State,
                            HAL_ADC_STATE_READY | HAL_ADC_STATE_REG_EOC | HAL_ADC_STATE_REG_OVR | HAL_ADC_STATE_REG_EOSMP,
                            HAL_ADC_STATE_REG_BUSY);

        /* If conversions on group regular are also triggering group injected,  */
        /* update ADC state.                                                    */
        if (READ_BIT(hadc->Instance->CR1, ADC_JAUTO_MASK) != RESET)
        {
            ADC_STATE_CLR_SET(hadc->State, HAL_ADC_STATE_INJ_EOC, HAL_ADC_STATE_INJ_BUSY);  
        }


        /* State machine update: Check if an injected conversion is ongoing */
        if (HAL_IS_BIT_SET(hadc->State, HAL_ADC_STATE_INJ_BUSY))
        {
            /* Reset ADC error code fields related to conversions on group regular */
            CLEAR_BIT(hadc->ErrorCode, (HAL_ADC_ERROR_OVR | HAL_ADC_ERROR_DMA));         
        }
        else
        {
            /* Reset ADC all error code fields */
            ADC_CLEAR_ERRORCODE(hadc);
        }

        /* Process unlocked */
        /* Unlock before starting ADC conversions: in case of potential           */
        /* interruption, to let the process to ADC IRQ Handler.                   */
        __HAL_UNLOCK(hadc);

        /* Clear regular group conversion flag and overrun flag */
        /* (To ensure of no unknown state from potential previous ADC operations) */
        __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_EOC);

        /* Enable end of conversion interrupt for regular group */
        __HAL_ADC_ENABLE_IT(hadc, ADC_IT_EOC);

        /* Enable conversion of regular group.                                    */
        /* If software start has been selected, conversion starts immediately.    */
        /* If external trigger has been selected, conversion will start at next   */
        /* trigger event.                                                         */
        /* Case of multimode enabled:                                             */ 
        /*  - if ADC is slave, ADC is enabled only (conversion is not started).   */
        /*  - if ADC is master, ADC is enabled and conversion is started.         */
        if ( ADC_IS_SOFTWARE_START_REGULAR(hadc))
        {
            /* Start ADC conversion on regular group with SW start */
            SET_BIT(hadc->Instance->CR2, ADC_RTRIG_MASK);
        }
    }
    else
    {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    }

    /* Return function status */
    return tmp_hal_status;
}

/**
  * @brief  Stop ADC conversion of regular group (and injected group in 
  *         case of auto_injection mode), disable interrution of 
  *         end-of-conversion, disable ADC peripheral.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc)
{
    HAL_StatusTypeDef tmp_hal_status = HAL_OK;

    /* Check the parameters */
    //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
        
    /* Process locked */
    __HAL_LOCK(hadc);
    
    /* Stop potential conversion on going, on regular and injected groups */
    /* Disable ADC peripheral */
    tmp_hal_status = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
        /* Disable ADC end of conversion interrupt for regular group */
        __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC);
        
        /* Set ADC state */
        ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                        HAL_ADC_STATE_READY);
    }
    
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
    
    /* Return function status */
    return tmp_hal_status;
}
/**
  * @brief  Enables ADC, starts conversion of injected group with interruption.
  *          - JEOC (end of conversion of injected group)
  *         Each of these interruptions has its dedicated callback function.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
 // assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));
  
  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Enable the ADC peripheral */
  tmp_hal_status = ADC_Enable(hadc);
  
  /* Start conversion if ADC is effectively enabled */
  if (tmp_hal_status == HAL_OK)
  {
    /* Set ADC state                                                          */
    /* - Clear state bitfield related to injected group conversion results    */
    /* - Set state bitfield related to injected operation                     */
    ADC_STATE_CLR_SET(hadc->State,
                      HAL_ADC_STATE_READY | HAL_ADC_STATE_INJ_EOC,
                      HAL_ADC_STATE_INJ_BUSY);
    
    /* Check if a regular conversion is ongoing */
    /* Note: On this device, there is no ADC error code fields related to     */
    /*       conversions on group injected only. In case of conversion on     */
    /*       going on group regular, no error code is reset.                  */
    if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_REG_BUSY))
    {
      /* Reset ADC all error code fields */
      ADC_CLEAR_ERRORCODE(hadc);
    }
    
    /* Process unlocked */
    /* Unlock before starting ADC conversions: in case of potential           */
    /* interruption, to let the process to ADC IRQ Handler.                   */
    __HAL_UNLOCK(hadc);
    
    /* Clear injected group conversion flag */
    /* (To ensure of no unknown state from potential previous ADC operations) */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_FLAG_JEOS | ADC_FLAG_JEOC);
    
    /* Enable end of conversion interrupt for injected channels */
    if((hadc->Init.ScanConvMode == ADC_SCAN_ENABLE) || (hadc->Init.ContinuousConvMode == ENABLE))
        __HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOS);
    else
        __HAL_ADC_ENABLE_IT(hadc, ADC_IT_JEOC);
    
    /* Start conversion of injected group if software start has been selected */
    /* and if automatic injected conversion is disabled.                      */
    /* If external trigger has been selected, conversion will start at next   */
    /* trigger event.                                                         */
    /* If automatic injected conversion is enabled, conversion will start     */
    /* after next regular group conversion.                                   */
    if (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_JAUTO_MASK))
    {
      if (ADC_IS_SOFTWARE_START_INJECTED(hadc))
      {
        /* Start ADC conversion on injected group with SW start */
        SET_BIT(hadc->Instance->CR2, ADC_JTRIG_MASK );
      }
    }
  }
  else
  {
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  }
  
  /* Return function status */
  return tmp_hal_status;
}

/**
  * @brief  Stop conversion of injected channels, disable interruption of 
  *         end-of-conversion. Disable ADC peripheral if no regular conversion
  *         is on going.
  * @note   If ADC must be disabled and if conversion is on going on 
  *         regular group, function HAL_ADC_Stop must be used to stop both
  *         injected and regular groups, and disable the ADC.
  * @note   If injected group mode auto-injection is enabled,
  *         function HAL_ADC_Stop must be used.
  * @param  hadc: ADC handle
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
 // assert_param(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Process locked */
  __HAL_LOCK(hadc);
    
  /* Stop potential conversion and disable ADC peripheral                     */
  /* Conditioned to:                                                          */
  /* - No conversion on the other group (regular group) is intended to        */
  /*   continue (injected and regular groups stop conversion and ADC disable  */
  /*   are common)                                                            */
  /* - In case of auto-injection mode, HAL_ADC_Stop must be used.             */ 
  if(((hadc->State & HAL_ADC_STATE_REG_BUSY) == RESET)  &&
     HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_JAUTO_MASK)   )
  {
    /* Stop potential conversion on going, on regular and injected groups */
    /* Disable ADC peripheral */
    tmp_hal_status = ADC_ConversionStop_Disable(hadc);
    
    /* Check if ADC is effectively disabled */
    if (tmp_hal_status == HAL_OK)
    {
      /* Disable ADC end of conversion interrupt for injected channels */
      __HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOC);
      
      /* Set ADC state */
      ADC_STATE_CLR_SET(hadc->State,
                        HAL_ADC_STATE_REG_BUSY | HAL_ADC_STATE_INJ_BUSY,
                        HAL_ADC_STATE_READY);
    }
  }
  else
  {
    /* Update ADC state machine to error */
    SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);
      
    tmp_hal_status = HAL_ERROR;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}


uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc)
{
  /* Check the parameters */
  //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));

  /* Return ADC converted value */ 
  return hadc->Instance->RDR;
}
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank)
{
  uint32_t tmp_jdr = 0U;
  
  /* Check the parameters */
  //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
  LS_ASSERT(IS_ADC_INJECTED_RANK(InjectedRank));
  
  /* Get ADC converted value */ 
  switch(InjectedRank)
  {  
    case ADC_INJECTED_RANK_4: 
      tmp_jdr = hadc->Instance->JDR4;
      break;
    case ADC_INJECTED_RANK_3: 
      tmp_jdr = hadc->Instance->JDR3;
      break;
    case ADC_INJECTED_RANK_2: 
      tmp_jdr = hadc->Instance->JDR2;
      break;
    case ADC_INJECTED_RANK_1:
    default:
      tmp_jdr = hadc->Instance->JDR1;
      break;
  }
  
  /* Return ADC converted value */ 
  return tmp_jdr;
}

/**
  * @brief  Handles ADC interrupt request  
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc)
{

    /* ========== Check End of Conversion flag for regular group ========== */
    if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_EOC))
    {
        if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_EOC) )
        {
            /* Clear regular group conversion flag */
            __HAL_ADC_CLEAR_FLAG(hadc, ADC_RSTRTCC_MASK | ADC_REOCC_MASK);
            /* Update state machine on conversion status if not in error state */
            if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL))
            {
                /* Set ADC state */
                SET_BIT(hadc->State, HAL_ADC_STATE_REG_EOC); 
            }
            
            /* Determine whether any further conversion upcoming on group regular   */
            /* by external trigger, continuous mode or scan sequence on going.      */
            if(ADC_IS_SOFTWARE_START_REGULAR(hadc)        && 
                (hadc->Init.ContinuousConvMode == DISABLE)   )
            {
                /* Disable ADC end of conversion interrupt on group regular */
                __HAL_ADC_DISABLE_IT(hadc, ADC_IT_EOC | ADC_IT_EOS);
                
                /* Set ADC state */
                CLEAR_BIT(hadc->State, HAL_ADC_STATE_REG_BUSY);   
                
                if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_INJ_BUSY))
                {
                    SET_BIT(hadc->State, HAL_ADC_STATE_READY);
                }
            }
            /* Conversion complete callback */
            HAL_ADC_ConvCpltCallback(hadc);
        }
    }

    /* ========== Check End of Conversion flag for injected group ========== */
    if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_JEOS) || __HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_JEOC))
    {
        if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOS) || __HAL_ADC_GET_FLAG(hadc, ADC_FLAG_JEOC))
        {
            /* Update state machine on conversion status if not in error state */
            if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL))
            {
                /* Set ADC state */
                SET_BIT(hadc->State, HAL_ADC_STATE_INJ_EOC);
            }

            /* Determine whether any further conversion upcoming on group injected  */
            /* by external trigger, scan sequence on going or by automatic injected */
            /* conversion from group regular (same conditions as group regular      */
            /* interruption disabling above).                                       */
            /* Note: On STM32F1 devices, in case of sequencer enabled               */
            /*       (several ranks selected), end of conversion flag is raised     */
            /*       at the end of the sequence.                                    */
            if(ADC_IS_SOFTWARE_START_INJECTED(hadc)                     || 
                (HAL_IS_BIT_CLR(hadc->Instance->CR1, ADC_JAUTO_MASK) &&     
                (ADC_IS_SOFTWARE_START_REGULAR(hadc)        &&
                (hadc->Init.ContinuousConvMode == DISABLE)   )        )   )
            {
                /* Disable ADC end of conversion interrupt on group injected */
                __HAL_ADC_DISABLE_IT(hadc, ADC_IT_JEOS);
                
                /* Set ADC state */
                CLEAR_BIT(hadc->State, HAL_ADC_STATE_INJ_BUSY);   

                if (HAL_IS_BIT_CLR(hadc->State, HAL_ADC_STATE_REG_BUSY))
                { 
                    SET_BIT(hadc->State, HAL_ADC_STATE_READY);
                }
            }
            /* Clear injected group conversion flag */
            __HAL_ADC_CLEAR_FLAG(hadc, (ADC_JSTRTCC_MASK | ADC_JEOCC_MASK | ADC_JEOSC_MASK));
            /* Conversion complete callback */ 
            HAL_ADCEx_InjectedConvCpltCallback(hadc);
            
        }
    }
    /* ========== Check Analog watchdog flags ========== */
    if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IT_AWD))
    {
        if(__HAL_ADC_GET_FLAG(hadc, ADC_FLAG_AWD))
        {
        /* Set ADC state */
        SET_BIT(hadc->State, HAL_ADC_STATE_AWD1);
        /* Clear the ADC analog watchdog flag */
        __HAL_ADC_CLEAR_FLAG(hadc, ADC_AWDC_MASK);
        /* Level out of window callback */ 
        HAL_ADC_LevelOutOfWindowCallback(hadc);
        }
    }

}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ConvCpltCallback must be implemented in the user file.
   */
}

/**
  * @brief  Injected conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_ADCEx_InjectedConvCpltCallback could be implemented in the user file
  */
}

/**
  * @brief  Analog watchdog callback in non blocking mode. 
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_LevelOutOfWindowCallback must be implemented in the user file.
  */
}

/**
  * @brief  ADC error callback in non blocking mode
  *        (ADC conversion with interruption or transfer by DMA)
  * @param  hadc: ADC handle
  * @retval None
  */
__weak void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADC_ErrorCallback must be implemented in the user file.
  */
}


/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Group3 Peripheral Control functions
 *  @brief    Peripheral Control functions
 *
@verbatim   
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================  
    [..]  This section provides functions allowing to:
      (+) Configure channels on regular group
      (+) Configure the analog watchdog
      
@endverbatim
  * @{
  */

/**
  * @brief  Configures the the selected channel to be linked to the regular
  *         group.
  * @note   In case of usage of internal measurement channels:
  *         Vbat/VrefInt/TempSensor.
  *         These internal paths can be be disabled using function 
  *         HAL_ADC_DeInit().
  * @note   Possibility to update parameters on the fly:
  *         This function initializes channel into regular group, following  
  *         calls to this function can be used to reconfigure some parameters 
  *         of structure "ADC_ChannelConfTypeDef" on the fly, without reseting 
  *         the ADC.
  *         The setting of these parameters is conditioned to ADC state.
  *         For parameters constraints, see comments of structure 
  *         "ADC_ChannelConfTypeDef".
  * @param  hadc: ADC handle
  * @param  sConfig: Structure of ADC channel for regular group.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig)
{
    HAL_StatusTypeDef tmp_hal_status = HAL_OK;
    
    /* Check the parameters */
    //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
    LS_ASSERT(IS_ADC_CHANNEL(sConfig->Channel));
    LS_ASSERT(IS_ADC_REGULAR_RANK(sConfig->Rank));
    LS_ASSERT(IS_ADC_SAMPLE_TIME(sConfig->SamplingTime));

    /* Process locked */
    __HAL_LOCK(hadc);
    
    
    /* Regular sequence configuration */
    /* For Rank 1 to 8 */
    if (sConfig->Rank <= ADC_REGULAR_RANK_8)
    {
        MODIFY_REG(hadc->Instance->RSQR1                     ,
                ADC_SQR1_RK(ADC_RSQ1_MASK, sConfig->Rank)    ,
                ADC_SQR1_RK(sConfig->Channel, sConfig->Rank) );
    }
    /* For Rank 9 to 12 */
    else 
    {
        MODIFY_REG(hadc->Instance->RSQR2                     ,
                ADC_SQR2_RK(ADC_RSQ9_MASK, sConfig->Rank)    ,
                ADC_SQR2_RK(sConfig->Channel, sConfig->Rank) );
    }

    /* Channel sampling time configuration */
    /* For channels 0 to 11 */
    MODIFY_REG(hadc->Instance->SMPR1                          ,
            ADC_SMPR1(ADC_SMP0_MASK, sConfig->Channel)      ,
            ADC_SMPR1(sConfig->SamplingTime, sConfig->Channel) );
    if (sConfig->Channel == ADC_CHANNEL_VBAT)
    {
        adc_channel_vbat_enable();
    }

   if (sConfig->Channel == ADC_CHANNEL_TEMPSENSOR)
   {
       adc_channel_tempsensor_enable(); 
   }
    /* Process unlocked */
    __HAL_UNLOCK(hadc);
  
    /* Return function status */
    return tmp_hal_status;
}

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
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{
  /* Check the parameters */
  //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
  LS_ASSERT(IS_ADC_ANALOG_WATCHDOG_MODE(AnalogWDGConfig->WatchdogMode));
  LS_ASSERT(IS_FUNCTIONAL_STATE(AnalogWDGConfig->ITMode));
  LS_ASSERT(IS_ADC_RANGE(AnalogWDGConfig->HighThreshold));
  LS_ASSERT(IS_ADC_RANGE(AnalogWDGConfig->LowThreshold));
  
  if((AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REG)     ||
     (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_INJEC)   ||
     (AnalogWDGConfig->WatchdogMode == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)  )
  {
    LS_ASSERT(IS_ADC_CHANNEL(AnalogWDGConfig->Channel));
  }
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
  /* Analog watchdog configuration */

  /* Configure ADC Analog watchdog interrupt */
  if(AnalogWDGConfig->ITMode == ENABLE)
  {
    /* Enable the ADC Analog watchdog interrupt */
    __HAL_ADC_ENABLE_IT(hadc, ADC_IT_AWD);
  }
  else
  {
    /* Disable the ADC Analog watchdog interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IT_AWD);
  }
  
  /* Configuration of analog watchdog:                                        */
  /*  - Set the analog watchdog enable mode: regular and/or injected groups,  */
  /*    one or all channels.                                                  */
  /*  - Set the Analog watchdog channel (is not used if watchdog              */
  /*    mode "all channels": ADC_CFGR_AWD1SGL=0).                             */
  MODIFY_REG(hadc->Instance->CR1            ,
             ADC_AWDSGL_MASK |
             ADC_JAWDEN_MASK |
             ADC_RAWDEN_MASK  |
             ADC_AWDCH_MASK                  ,
             AnalogWDGConfig->WatchdogMode |
             AnalogWDGConfig->Channel        );
  
  /* Set the high threshold */
  WRITE_REG(hadc->Instance->HTR, AnalogWDGConfig->HighThreshold);
  
  /* Set the low threshold */
  WRITE_REG(hadc->Instance->LTR, AnalogWDGConfig->LowThreshold);

  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Configures the ADC injected group and the selected channel to be
  *         linked to the injected group.
  * @note   Possibility to update parameters on the fly:
  *         This function initializes injected group, following calls to this 
  *         function can be used to reconfigure some parameters of structure
  *         "ADC_InjectionConfTypeDef" on the fly, without reseting the ADC.
  *         The setting of these parameters is conditioned to ADC state: 
  *         this function must be called when ADC is not under conversion.
  * @param  hadc: ADC handle
  * @param  sConfigInjected: Structure of ADC injected group and ADC channel for
  *         injected group.
  * @retval None
  */
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc, ADC_InjectionConfTypeDef* sConfigInjected)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  
  /* Check the parameters */
  //LS_ASSERT(IS_ADC_ALL_INSTANCE(hadc->Instance));
  LS_ASSERT(IS_ADC_CHANNEL(sConfigInjected->InjectedChannel));
  LS_ASSERT(IS_ADC_SAMPLE_TIME(sConfigInjected->InjectedSamplingTime));
  LS_ASSERT(IS_FUNCTIONAL_STATE(sConfigInjected->AutoInjectedConv));
  LS_ASSERT(IS_ADC_RANGE(sConfigInjected->InjectedOffset));
  
  if(hadc->Init.ScanConvMode != ADC_SCAN_DISABLE)
  {
    LS_ASSERT(IS_ADC_INJECTED_RANK(sConfigInjected->InjectedRank));
    LS_ASSERT(IS_ADC_INJECTED_NB_CONV(sConfigInjected->InjectedNbrOfConversion));
    LS_ASSERT(IS_FUNCTIONAL_STATE(sConfigInjected->InjectedDiscontinuousConvMode));
  }
  
  /* Process locked */
  __HAL_LOCK(hadc);
  
    /* Since injected channels rank conv. order depends on total number of   */
    /* injected conversions, selected rank must be below or equal to total   */
    /* number of injected conversions to be updated.                         */
    if (sConfigInjected->InjectedRank <= sConfigInjected->InjectedNbrOfConversion)
    {
      /* Clear the old SQx bits for the selected rank */
      /* Set the SQx bits for the selected rank */
      MODIFY_REG(hadc->Instance->SQLR, ADC_JSQL_MASK ,ADC_JSQR_JL_SHIFT(sConfigInjected->InjectedNbrOfConversion));	
      MODIFY_REG(hadc->Instance->JSQR                                         ,
                 ADC_JSQR_RK_JL(ADC_JSQ1_MASK,                         
                                  sConfigInjected->InjectedRank)   ,
                 ADC_JSQR_RK_JL(sConfigInjected->InjectedChannel,      
                                  sConfigInjected->InjectedRank)    );

        if(sConfigInjected->InjectedChannel == ADC_CHANNEL_VBAT) 
        {
            adc_channel_vbat_enable();
        }

       if (sConfigInjected->InjectedChannel == ADC_CHANNEL_TEMPSENSOR)
       {
           adc_channel_tempsensor_enable(); 
       }
    }
    else
    {
      /* Clear the old SQx bits for the selected rank */
			CLEAR_BIT(hadc->Instance->SQLR, ADC_JSQL_MASK);
      MODIFY_REG(hadc->Instance->JSQR                                       ,
                 ADC_JSQR_RK_JL(ADC_JSQ1_MASK,                         
                                  sConfigInjected->InjectedRank) ,              
                 0x00000000U);
    }
    
  /* Configuration of injected group                                          */
  /* Parameters update conditioned to ADC state:                              */
  /* Parameters that can be updated only when ADC is disabled:                */
  /*  - external trigger to start conversion                                  */
  /* Parameters update not conditioned to ADC state:                          */
  /*  - Automatic injected conversion                                         */
  /*  - Injected discontinuous mode                                           */
  if (ADC_IS_ENABLE(hadc) == RESET)
  {    
    MODIFY_REG(hadc->Instance->CR2, ADC_ADEN_MASK,0x00000000U);
  }

    /* Automatic injected conversion can be enabled if injected group         */
    /* external triggers are disabled.                                        */
    if (sConfigInjected->AutoInjectedConv == ENABLE)
    {
       SET_BIT(hadc->Instance->CR1, ADC_JAUTO_MASK);
    }
    
    /* Injected discontinuous can be enabled only if auto-injected mode is    */
    /* disabled.                                                              */  
    if (sConfigInjected->InjectedDiscontinuousConvMode == ENABLE)
    {
      if (sConfigInjected->AutoInjectedConv == DISABLE)
      {
        SET_BIT(hadc->Instance->CR1, ADC_JDISCEN_MASK);
      } 
      else
      {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_CONFIG);
        
        tmp_hal_status = HAL_ERROR;
      }
    }


  /* InjectedChannel sampling time configuration */
	/* For channels 0 to 11 */
	MODIFY_REG(hadc->Instance->SMPR1                          ,
					ADC_SMPR1(ADC_SMP0_MASK, sConfigInjected->InjectedChannel)      ,
					ADC_SMPR1(sConfigInjected->InjectedSamplingTime, sConfigInjected->InjectedChannel) ); 
   if(sConfigInjected->InjectedChannel == ADC_CHANNEL_VBAT)
   {
    //    adc_channel_vbat_init();
   }
  /* Configure the offset: offset enable/disable, InjectedChannel, offset value */
  switch(sConfigInjected->InjectedRank)
  {
    case 1:
      /* Set injected channel 1 offset */
      MODIFY_REG(hadc->Instance->JOFR1,
                 ADC_JOFF1_MASK,
                 sConfigInjected->InjectedOffset);
      break;
    case 2:
      /* Set injected channel 2 offset */
      MODIFY_REG(hadc->Instance->JOFR2,
                 ADC_JOFF2_MASK,
                 sConfigInjected->InjectedOffset);
      break;
    case 3:
      /* Set injected channel 3 offset */
      MODIFY_REG(hadc->Instance->JOFR3,
                 ADC_JOFF3_MASK,
                 sConfigInjected->InjectedOffset);
      break;
    case 4:
    default:
      MODIFY_REG(hadc->Instance->JOFR4,
                 ADC_JOFF4_MASK,
                 sConfigInjected->InjectedOffset);
      break;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hadc);
  
  /* Return function status */
  return tmp_hal_status;
}

/** @defgroup ADC_Exported_Functions_Group4 Peripheral State functions
 *  @brief    Peripheral State functions
 *
@verbatim
 ===============================================================================
            ##### Peripheral State and Errors functions #####
 ===============================================================================  
    [..]
    This subsection provides functions to get in run-time the status of the  
    peripheral.
      (+) Check the ADC state
      (+) Check the ADC error code

@endverbatim
  * @{
  */

/**
  * @brief  return the ADC state
  * @param  hadc: ADC handle
  * @retval HAL state
  */
uint32_t HAL_ADC_GetState(ADC_HandleTypeDef* hadc)
{
  /* Return ADC state */
  return hadc->State;
}

/**
  * @brief  Return the ADC error code
  * @param  hadc: ADC handle
  * @retval ADC Error Code
  */
uint32_t HAL_ADC_GetError(ADC_HandleTypeDef *hadc)
{
  return hadc->ErrorCode;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_Private_Functions ADC Private Functions
  * @{
  */
static bool adc_isenable_poll(va_list va)
{
    ADC_HandleTypeDef *hadc = va_arg(va,ADC_HandleTypeDef *);
    uint32_t flag = va_arg(va,uint32_t);
    if (ADC_IS_ENABLE(hadc) == flag)
    {
    return true;
    }
    else
    {
    return false;
    }
}
/**
  * @brief  Enable the selected ADC.
  * @note   Prerequisite condition to use this function: ADC must be disabled
  *         and voltage regulator must be enabled (done into HAL_ADC_Init()).
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0U;
  uint32_t wait_loop_index = 0U;
  uint32_t timeout = SYSTICK_MS2TICKS(ADC_DISABLE_TIMEOUT);

  /* ADC enable and wait for ADC ready (in case of ADC is disabled or         */
  /* enabling phase not yet completed: flag ADC ready not yet set).           */
  /* Timeout implemented to not be stuck if ADC cannot be enabled (possible   */
  /* causes: ADC clock not running, ...).                                     */
  if (ADC_IS_ENABLE(hadc) == RESET)
  {
    /* Enable the Peripheral */
    __HAL_ADC_ENABLE(hadc);
    
    /* Delay for ADC stabilization time */
    /* Compute number of CPU cycles to wait for */
    wait_loop_index = (ADC_STAB_DELAY_US * (ADC_CLOCK / 1000000U));
    while(wait_loop_index != 0U)
    {
      wait_loop_index--;
    }
    
    /* Get tick count */
    tickstart = systick_get_value();

    /* Wait for ADC effectively enabled */
    if(systick_poll_timeout(tickstart,timeout,adc_isenable_poll,hadc,SET))
    {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
      
        /* Set ADC error code to ADC IP internal error */
        SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
        
        /* Process unlocked */
        __HAL_UNLOCK(hadc);
      
        return HAL_ERROR;

    }
  } 
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @brief  Stop ADC conversion and disable the selected ADC
  * @note   Prerequisite condition to use this function: ADC conversions must be
  *         stopped to disable the ADC.
  * @param  hadc: ADC handle
  * @retval HAL status.
  */
HAL_StatusTypeDef ADC_ConversionStop_Disable(ADC_HandleTypeDef* hadc)
{
  uint32_t tickstart = 0U;
  uint32_t timeout = SYSTICK_MS2TICKS(ADC_DISABLE_TIMEOUT);

  /* Verification if ADC is not already disabled */
  if (ADC_IS_ENABLE(hadc) != RESET)
  {
    /* Disable the ADC peripheral */
    __HAL_ADC_DISABLE(hadc);
     
    /* Get tick count */
    tickstart = systick_get_value();
    
    /* Wait for ADC effectively disabled */
    if(systick_poll_timeout(tickstart,timeout,adc_isenable_poll,hadc,RESET))
    {
        /* Update ADC state machine to error */
        SET_BIT(hadc->State, HAL_ADC_STATE_ERROR_INTERNAL);
        
        /* Set ADC error code to ADC IP internal error */
        SET_BIT(hadc->ErrorCode, HAL_ADC_ERROR_INTERNAL);
        
        return HAL_ERROR;
        
    }
  }
  
  /* Return HAL status */
  return HAL_OK;
}

/**
  * @}
  */

 /************************ (C) COPYRIGHT Linkedsemi ***********END OF FILE****/

