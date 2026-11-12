#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "platform.h"
#include "compile_flag.h"
#include "ls_soc_gpio.h"
#include "reg_i3c.h"
#include "field_manipulate.h"
#include "core_rv32.h"
#include "ls_hal_i3c_controller.h"
#include "ls_ll_i3c_controller.h"
#include "systick.h"
#include "ls_dbg.h"
#include "ls_hal_dmacv3.h"

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Private_Define I3C Private Define
  * @{
  */

/* Private defines for control buffer prior preparation */
#define I3C_OPERATION_TYPE_MASK       (0x78000000U)
#define I3C_RESTART_STOP_MASK         (0x80000000U)
#define I3C_ARBITRATION_HEADER_MASK   (0x00000004U)
#define I3C_DEFINE_BYTE_MASK          (0x00000001U)

/* Private define for CCC command */
#define I3C_BROADCAST_RSTDAA          (0x00000006U)
#define I3C_BROADCAST_ENTDAA          (0x00000007U)
/**
  * @}
  */

/* Private define to split ENTDAA payload */
#define I3C_DCR_IN_PAYLOAD_SHIFT       56
#define I3C_PID_IN_PAYLOAD_MASK        0xFFFFFFFFFFFFU

/* Private define to split PID */
/* Bits[47:33]: MIPI Manufacturer ID */
#define I3C_MIPIMID_PID_SHIFT          33
#define I3C_MIPIMID_PID_MASK           0x7FFFU

/* Bit[32]: Provisioned ID Type Selector */
#define I3C_IDTSEL_PID_SHIFT           32
#define I3C_IDTSEL_PID_MASK            0x01U

/* Bits[31:16]: Part ID */
#define I3C_PART_ID_PID_SHIFT          16
#define I3C_PART_ID_PID_MASK           0xFFFFU

/* Bits[15:12]: MIPI Instance ID */
#define I3C_MIPIID_PID_SHIFT           12
#define I3C_MIPIID_PID_MASK            0xFU
/**
  * @}
  */
 
/* Private macro -----------------------------------------------------------------------------------------------------*/

/** @brief  Get Provisioned ID in payload (64bits) receive during ENTDAA procedure.
  * @param  __PAYLOAD__ specifies the Device Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFFFFFF.
  * @retval The value of PID Return value between Min_Data=0x00 and Max_Data=0xFFFFFFFFFFFF.
  */
#define I3C_GET_PID(__PAYLOAD__) ((uint64_t)(__PAYLOAD__) & I3C_PID_IN_PAYLOAD_MASK)

/** @brief  Get MIPI Manufacturer ID in PID (48bits).
  * @param  __PID__ specifies the Provisioned ID retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFF.
  * @retval The value of MIPI ID Return value between Min_Data=0x00 and Max_Data=0x7FFF.
  */
#define I3C_GET_MIPIMID(__PID__) ((uint16_t)((uint64_t)(__PID__) >> I3C_MIPIMID_PID_SHIFT) & \
                                  I3C_MIPIMID_PID_MASK)

/** @brief  Get Type Selector in PID (48bits).
  * @param  __PID__ specifies the Provisioned ID retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFF.
  * @retval The value of Type Selector Return 0 or 1.
  */
#define I3C_GET_IDTSEL(__PID__) ((uint8_t)((uint64_t)(__PID__) >> I3C_IDTSEL_PID_SHIFT) & \
                                 I3C_IDTSEL_PID_MASK)

/** @brief  Get Part ID in PID (48bits).
  * @param  __PID__ specifies the Provisioned ID retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFF.
  * @retval The value of Part ID Return value between Min_Data=0x00 and Max_Data=0xFFFF.
  */
#define I3C_GET_PART_ID(__PID__) ((uint16_t)((uint64_t)(__PID__) >> I3C_PART_ID_PID_SHIFT) & \
                                  I3C_PART_ID_PID_MASK)

/** @brief  Get Instance ID in PID (48bits).
  * @param  __PID__ specifies the Provisioned ID retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFF.
  * @retval The value of Instance ID Return value between Min_Data=0x00 and Max_Data=0xF.
  */
#define I3C_GET_MIPIID(__PID__) ((uint8_t)((uint64_t)(__PID__) >> I3C_MIPIID_PID_SHIFT) & \
                                 I3C_MIPIID_PID_MASK)

/** @brief  Get Device Characterics in payload (64bits) receive during ENTDAA procedure.
  * @param  __PAYLOAD__ specifies the Device Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFFFFFFFF.
  * @retval The value of BCR Return value between Min_Data=0x00 and Max_Data=0xFF.
  */
#define I3C_GET_DCR(__PAYLOAD__) (((uint32_t)((uint64_t)(__PAYLOAD__) >> I3C_DCR_IN_PAYLOAD_SHIFT)) & \
                                  I3C_DCR_DCR)

/** @brief  Get Advanced Capabilities.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval The value of advanced capabilities:
  *           ENABLE: supports optional advanced capabilities.
  *           DISABLE: not supports optional advanced capabilities.
  */
#define I3C_GET_ADVANCED_CAPABLE(__BCR__) (((((__BCR__) & I3C_BCR_BCR5_Msk) >> \
                                             I3C_BCR_BCR5_POS) == 1U) ? ENABLE : DISABLE)

/** @brief  Get virtual target support.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval The value of offline capable:
  *           ENABLE: is a Virtual Target
  *           DISABLE: is not a Virtual Target
  */
#define I3C_GET_VIRTUAL_TGT(__BCR__) (((((__BCR__) & I3C_BCR_BCR4_Msk) >> \
                                        I3C_BCR_BCR4_POS) == 1U) ? ENABLE : DISABLE)

/** @brief  Get offline capable.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval The value of offline capable
  *           ENABLE: Device will not always respond to I3C Bus commands
  *           DISABLE: Device will always respond to I3C Bus commands
  */
#define I3C_GET_OFFLINE_CAPABLE(__BCR__) (((((__BCR__) & I3C_BCR_BCR3_Msk) >> \
                                            I3C_BCR_BCR3_POS) == 1U) ? ENABLE : DISABLE)

/** @brief  Get Max data speed limitation.
  * @param  __BCR__ specifies the Bus Characteristics capabilities retrieve during ENTDAA procedure.
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @retval The value of offline capable:
  *           ENABLE: Limitation
  *           DISABLE: No Limitation
  */
#define I3C_GET_MAX_DATA_SPEED_LIMIT(__BCR__) (((((__BCR__) & I3C_BCR_BCR0_Msk) >> \
                                                 I3C_BCR_BCR0_POS) == 1U) ? ENABLE : DISABLE)

/** @brief  Change uint32_t variable form big endian to little endian.
  * @param  __DATA__ .uint32_t variable in big endian.
  *         This parameter must be a number between Min_Data=0x00(uint32_t) and Max_Data=0xFFFFFFFF.
  * @retval uint32_t variable in little endian.
  */
#define I3C_BIG_TO_LITTLE_ENDIAN(__DATA__) ((uint32_t)((((__DATA__) & 0xff000000U) >> 24) | \
                                                       (((__DATA__) & 0x00ff0000U) >> 8)  | \
                                                       (((__DATA__) & 0x0000ff00U) << 8)  | \
                                                       (((__DATA__) & 0x000000ffU) << 24)))

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @addtogroup  I3C_Private_Variables
  * @{
  */
/* Structure containing address device and message type used for the private function I3C_Ctrl_IsDevice_Ready() */
typedef struct
{
  uint8_t   Address;            /* Dynamic or Static target Address */
  uint32_t  MessageType;        /* Message Type */

} I3C_DeviceTypeDef;
/**
  * @}
  */

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @addtogroup I3C_Private_Functions
  * @{
  */
static HAL_StatusTypeDef I3C_Ctrl_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
static HAL_StatusTypeDef I3C_Ctrl_Tx_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
static HAL_StatusTypeDef I3C_Ctrl_Rx_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
static HAL_StatusTypeDef I3C_Ctrl_Multiple_Xfer_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
static HAL_StatusTypeDef I3C_Ctrl_Tx_Listen_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
static HAL_StatusTypeDef I3C_Ctrl_Rx_Listen_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
static HAL_StatusTypeDef I3C_Ctrl_Multiple_Xfer_Listen_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
static HAL_StatusTypeDef I3C_Ctrl_DAA_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);
static HAL_StatusTypeDef I3C_Abort_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks);

static HAL_StatusTypeDef I3C_WaitOnDAAUntilTimeout(I3C_HandleTypeDef *hi3c, uint32_t timeout, uint32_t tickstart);
static HAL_StatusTypeDef I3C_WaitOnFlagUntilTimeout(I3C_HandleTypeDef *hi3c, uint32_t flag, FlagStatus flagstatus,
                                                    uint32_t timeout, uint32_t tickstart);
static void I3C_TransmitByteTreatment(I3C_HandleTypeDef *hi3c);
static void I3C_ReceiveByteTreatment(I3C_HandleTypeDef *hi3c);
void I3C_ControlDataTreatment(I3C_HandleTypeDef *hi3c);
void I3C_ErrorTreatment(I3C_HandleTypeDef *hi3c);
void I3C_GetErrorSources(I3C_HandleTypeDef *hi3c);
void I3C_StateUpdate(I3C_HandleTypeDef *hi3c);
void I3C_Enable_IRQ(I3C_HandleTypeDef *hi3c, uint32_t InterruptRequest);
void I3C_Disable_IRQ(I3C_HandleTypeDef *hi3c, uint32_t InterruptRequest);
static HAL_StatusTypeDef I3C_Xfer_PriorPreparation(I3C_HandleTypeDef *hi3c, uint8_t counter, uint32_t option);
static uint32_t I3C_FillTxBuffer_CCC(I3C_HandleTypeDef *hi3c,
                                     uint32_t           indexDesc,
                                     uint32_t           txSize,
                                     uint32_t           txCurrentIndex);
static uint32_t I3C_FillTxBuffer_Private(I3C_HandleTypeDef *hi3c,
                                         uint32_t           indexDesc,
                                         uint32_t           txSize,
                                         uint32_t           txCurrentIndex);
static HAL_StatusTypeDef I3C_ControlBuffer_PriorPreparation(I3C_HandleTypeDef *hi3c,
                                                            uint8_t            counter,
                                                            uint32_t           option);
static HAL_StatusTypeDef I3C_Ctrl_IsDevice_Ready(I3C_HandleTypeDef *hi3c,
                                                 const I3C_DeviceTypeDef *pDevice,
                                                 uint32_t           trials,
                                                 uint32_t           timeout);
static void I3C_TreatErrorCallback(I3C_HandleTypeDef *hi3c);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup I3C_Exported_Functions I3C Exported Functions
  * @{
  */

/** @defgroup I3C_Exported_Functions_Group1 Initialization and de-initialization functions.
  * @brief    I3C initialization and de-initialization functions
  *
@verbatim
 =======================================================================================================================
                              ##### Initialization and de-initialization functions #####
 =======================================================================================================================
    [..]  This subsection provides a set of functions allowing to initialize and deinitialize the I3Cx peripheral:

         (+) Users must implement HAL_I3C_MspInit() function in which they configure all related peripherals
             resources (APB and Kernel CLOCK, GPIO, DMA, IT and NVIC).

         (+) Call the function HAL_I3C_Controller_Init() to configure the bus characteristic depends on the device mode
             with the selected configuration below:

             (++) Controller mode, Serial source clock wave form configuration:
                  (+++) SCL push pull low duration
                  (+++) SCL I3C high duration
                  (+++) SCL open drain low duration
                  (+++) SCL I2C high duration

             (++) Controller mode, Bus timing configuration:
                  (+++) SDA hold time
                  (+++) Wait time
                  (+++) Bus free duration
                  (+++) Bus available duration

             (++) Target mode, Bus timing configuration:
                  (+++) Bus available duration

         (+) Call the function HAL_I3C_DeInit() to restore the default configuration of the selected I3Cx peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the I3C instance by activating the low-level hardware and configuring the bus
  *         characteristic according to the specified parameters in the I3C_InitTypeDef.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Controller_Init(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t waveform_value;
  uint32_t timing_value;
  uint32_t timing2_value;
  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));
    if(hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      status = HAL_INVALIAD_PARAM;
    }
    else
    {
      /* Check the I3C state */
      if (hi3c->State == HAL_I3C_STATE_RESET)
      {
        HAL_I3C_MspInit(hi3c);
      }

      /* Update the I3C state to busy */
      hi3c->State = HAL_I3C_STATE_BUSY;
      /* Disable the selected I3C peripheral */
      LL_I3C_Disable(hi3c->Instance);

      /* Check the parameters */
      LS_ASSERT(IS_I3C_SDAHOLDTIME_VALUE(hi3c->Init.CtrlBusCharacteristic.SDAHoldTime));
      LS_ASSERT(IS_I3C_WAITTIME_VALUE(hi3c->Init.CtrlBusCharacteristic.WaitTime));

      LS_ASSERT(IS_I3C_TXFIFOTHRESHOLD_VALUE(hi3c->Init.CtrlFifoConfig.TxFifoThreshold));
      LS_ASSERT(IS_I3C_RXFIFOTHRESHOLD_VALUE(hi3c->Init.CtrlFifoConfig.RxFifoThreshold));
      LS_ASSERT(IS_I3C_STATUSFIFOSTATE_VALUE(hi3c->Init.CtrlFifoConfig.StatusFifo));

      /* Check configuration parameters values */
      // LS_ASSERT(IS_I3C_DYNAMICADDRESS_VALUE(pConfig->DynamicAddr));
      // LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(pConfig->HighKeeperSDA));
      LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(hi3c->Init.CtrlConfig.HotJoinAllowed));
      LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(hi3c->Init.CtrlConfig.ACKStallState));
      LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(hi3c->Init.CtrlConfig.CCCStallState));
      LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(hi3c->Init.CtrlConfig.TxStallState));
      LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(hi3c->Init.CtrlConfig.RxStallState));

      /* Set configuration in the CFGR register */
      MODIFY_REG(hi3c->Instance->CFGR, I3C_CFGR_TXTHRES|I3C_CFGR_RXTHRES|I3C_CFGR_SMODE,
                      hi3c->Init.CtrlFifoConfig.TxFifoThreshold | hi3c->Init.CtrlFifoConfig.RxFifoThreshold|hi3c->Init.CtrlFifoConfig.StatusFifo);

      /*----------------- SCL signal waveform configuration : I3C timing register 0 (I3C_TIMINGR0) ------------------ */
      /* Set the controller SCL waveform */
      waveform_value = ((uint32_t)hi3c->Init.CtrlBusCharacteristic.SCLPPLowDuration                                   |
                        ((uint32_t)hi3c->Init.CtrlBusCharacteristic.SCLI3CHighDuration << I3C_TIMINGR0_SCLH_I3C_POS)  |
                        ((uint32_t)hi3c->Init.CtrlBusCharacteristic.SCLODLowDuration << I3C_TIMINGR0_SCLL_OD_POS)     |
                        ((uint32_t)hi3c->Init.CtrlBusCharacteristic.SCLI2CHighDuration << I3C_TIMINGR0_SCLH_I2C_POS));

      LL_I3C_ConfigClockWaveForm(hi3c->Instance, waveform_value);

      /*------------------ Timing configuration : I3C timing register 1 (I3C_TIMINGR1) ------------------------------ */
      /* Set SDA hold time, activity state, bus free duration and bus available duration */
      timing_value = ((uint32_t)hi3c->Init.CtrlBusCharacteristic.SDAHoldTime                                 |
                      (uint32_t)hi3c->Init.CtrlBusCharacteristic.WaitTime                                    |
                      ((uint32_t)hi3c->Init.CtrlBusCharacteristic.BusFreeDuration <<  I3C_TIMINGR1_FREE_POS) |
                      (uint32_t)hi3c->Init.CtrlBusCharacteristic.BusIdleDuration);

      LL_I3C_SetCtrlBusCharacteristic(hi3c->Instance, timing_value);


      /* Calculate value to be written in timing register 2 */
      timing2_value = (((uint32_t)hi3c->Init.CtrlConfig.StallTime << I3C_TIMINGR2_STALL_POS)      |
                       ((uint32_t)hi3c->Init.CtrlConfig.ACKStallState << I3C_TIMINGR2_STALLA_POS) |
                       ((uint32_t)hi3c->Init.CtrlConfig.CCCStallState << I3C_TIMINGR2_STALLC_POS) |
                       ((uint32_t)hi3c->Init.CtrlConfig.TxStallState << I3C_TIMINGR2_STALLD_POS)  |
                       ((uint32_t)hi3c->Init.CtrlConfig.RxStallState << I3C_TIMINGR2_STALLT_POS));

      /* Set value in timing 2 register */
      WRITE_REG(hi3c->Instance->TIMINGR2, timing2_value);

      /* Set hot join acknowledge and high keeper values */
      MODIFY_REG(hi3c->Instance->CFGR, I3C_CFGR_HJACK, (uint32_t)hi3c->Init.CtrlConfig.HotJoinAllowed << I3C_CFGR_HJACK_POS);

      if(hi3c->EnableController)
      {
        /* Enable the selected I3C peripheral */
        LL_I3C_Enable(hi3c->Instance);
      }

      hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

      /* Update I3C state */
      hi3c->State = HAL_I3C_STATE_READY;
      hi3c->PreviousState = HAL_I3C_STATE_READY;
    }

  }

  return status;
}

/**
  * @brief  DeInitialize the I3C peripheral.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_DeInit(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameters */

    /* Update the I3C state to busy */
    hi3c->State = HAL_I3C_STATE_BUSY;

    /* Disable the selected I3C peripheral */
    LL_I3C_Disable(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Check on the MSP init callback */
    if (hi3c->MspDeInitCallback == NULL)
    {
      /* Legacy weak MspDeInit  */
      hi3c->MspDeInitCallback = HAL_I3C_MspDeInit;
    }

    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    hi3c->MspDeInitCallback(hi3c);
#else
    /* DeInit the low level hardware: GPIO, CLOCK, NVIC */
    HAL_I3C_MspDeInit(hi3c);

#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */

    /* Update the I3C Error code, state and mode */
    hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
    hi3c->State         = HAL_I3C_STATE_RESET;
    hi3c->PreviousState = HAL_I3C_STATE_RESET;
    hi3c->Mode          = HAL_I3C_MODE_NONE;
  }

  return status;
}

/**
  * @brief Initialize the I3C MSP.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_MspInit(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_I3C_MspInit could be implemented in the user file */
}

/**
  * @brief DeInitialize the I3C MSP.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_MspDeInit(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_I3C_MspDeInit could be implemented in the user file */
}
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group2 Interrupt and callback functions.
  * @brief    I3C interrupt and callback functions.
  *
@verbatim
 =======================================================================================================================
                                    ##### Interrupt and callback functions #####
 =======================================================================================================================
    [..]  This subsection provides a set of functions allowing to manage callbacks and interrupts request:

         (+) Register/Unregister callback function:
             (++) Call the function HAL_I3C_RegisterCallback() to register an I3C user callback.
             (++) Call the function HAL_I3C_RegisterNotifyCallback() to register an I3C user notification callback.
             (++) Call the function HAL_I3C_RegisterDynamicAddrCallback() to register an I3C user address callback.
             (++) Call the function HAL_I3C_RegisterHotJoinCallback() to register an I3C user hot join callback.
             (++) Call the function HAL_I3C_UnRegisterCallback() to unregister an I3C user callback.

         (+) Notification management function:
             (++) Call the function HAL_I3C_Controller_ActivateNotification() to activate the I3C notifications.
             (++) Call the function HAL_I3C_Controller_DeactivateNotification() to deactivate the I3C notifications.

         (+) Controller callback functions:
             (++) Users must implement HAL_I3C_CtrlTxCpltCallback() function when the transmission of private data or
                  Tx CCC transfer is completed.
             (++) Users must implement HAL_I3C_CtrlRxCpltCallback() function when the reception of private data or
                  Rx CCC transfer is completed.
             (++) Users must implement HAL_I3C_CtrlMultipleXferCpltCallback() function when the multiple
                  transfer of CCC, I3C private or I2C transfer is completed.
             (++) Users must implement HAL_I3C_CtrlDAACpltCallback() function when Dynamic Address Assignment
                  procedure is completed.
             (++) Users must implement HAL_I3C_TgtReqDynamicAddrCallback() function in the controller application
                  when a target sent its payload to the controller during Dynamic Address Assignment procedure.

         (+) Target callback functions:
             (++) Users must implement HAL_I3C_TgtTxCpltCallback() function when the transmission of private
                  data is completed.
             (++) Users must implement HAL_I3C_TgtRxCpltCallback() function when the reception of private
                  data is completed.
             (++) Users must implement HAL_I3C_TgtHotJoinCallback() function when a target hot join process
                  is completed.

         (+) Common callback functions:
             (++) Users must implement HAL_I3C_NotifyCallback() function when the device receives
                  an asynchronous event like IBI, a Hot-join, CCC command for target...
             (++) Users must implement HAL_I3C_AbortCpltCallback() function when an abort process is completed.
             (++) Users must implement HAL_I3C_ErrorCallback() function when an error is occurred.

         (+) Interrupt and event function:
             (++) Call the function HAL_I3C_ER_IRQHandler() in the ISR file to handle I3C error interrupts request.
             (++) Call the function HAL_I3C_EV_IRQHandler() in the ISR file to handle I3C event interrupts request.
@endverbatim
  * @{
  */

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register a User I3C Callback to be used instead of the weak predefined callback.
  * @note   The HAL_I3C_RegisterCallback() may be called before HAL_I3C_Controller_Init() in HAL_I3C_STATE_RESET
  *         to register callbacks for HAL_I3C_MSPINIT_CB_ID and HAL_I3C_MSPDEINIT_CB_ID
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  callbackID : [IN]  ID of the callback to be registered.
  *                            This parameter can be one of the following values:
  *                            @arg @ref HAL_I3C_CTRL_TX_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_CTRL_RX_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_CTRL_MULTIPLE_XFER_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_CTRL_DAA_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_TGT_TX_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_TGT_RX_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_ERROR_CB_ID
  *                            @arg @ref HAL_I3C_ABORT_CB_ID
  *                            @arg @ref HAL_I3C_MSPINIT_CB_ID
  *                            @arg @ref HAL_I3C_MSPDEINIT_CB_ID
  * @param  pCallback  : [IN]  Pointer to the Callback function.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_RegisterCallback(I3C_HandleTypeDef *hi3c,
                                           HAL_I3C_CallbackIDTypeDef callbackID,
                                           pI3C_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the user callback allocation */
    if (pCallback == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    else if (HAL_I3C_STATE_READY == hi3c->State)
    {
      switch (callbackID)
      {
        case HAL_I3C_CTRL_TX_COMPLETE_CB_ID :
          hi3c->CtrlTxCpltCallback = pCallback;
          break;

        case HAL_I3C_CTRL_RX_COMPLETE_CB_ID :
          hi3c->CtrlRxCpltCallback = pCallback;
          break;

        case HAL_I3C_CTRL_MULTIPLE_XFER_COMPLETE_CB_ID :
          hi3c->CtrlMultipleXferCpltCallback = pCallback;
          break;

        case HAL_I3C_CTRL_DAA_COMPLETE_CB_ID :
          hi3c->CtrlDAACpltCallback = pCallback;
          break;

        case HAL_I3C_TGT_TX_COMPLETE_CB_ID :
          hi3c->TgtTxCpltCallback = pCallback;
          break;

        case HAL_I3C_TGT_RX_COMPLETE_CB_ID :
          hi3c->TgtRxCpltCallback = pCallback;
          break;

        case HAL_I3C_ERROR_CB_ID :
          hi3c->ErrorCallback = pCallback;
          break;

        case HAL_I3C_ABORT_CB_ID :
          hi3c->AbortCpltCallback = pCallback;
          break;

        case HAL_I3C_MSPINIT_CB_ID :
          hi3c->MspInitCallback = pCallback;
          break;

        case HAL_I3C_MSPDEINIT_CB_ID :
          hi3c->MspDeInitCallback = pCallback;
          break;

        default :
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_CALLBACK;
          status =  HAL_ERROR;
          break;
      }
    }
    else if (HAL_I3C_STATE_RESET == hi3c->State)
    {
      switch (callbackID)
      {
        case HAL_I3C_MSPINIT_CB_ID :
          hi3c->MspInitCallback = pCallback;
          break;

        case HAL_I3C_MSPDEINIT_CB_ID :
          hi3c->MspDeInitCallback = pCallback;
          break;

        default :
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_CALLBACK;
          status =  HAL_ERROR;
          break;
      }
    }
    else
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status =  HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Register a User I3C Notify Callback to be used instead of the weak predefined callback.
  * @param  hi3c            : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                 information for the specified I3C.
  * @param  pNotifyCallback : [IN]  Pointer to the Callback function.
  * @retval HAL Status      :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_RegisterNotifyCallback(I3C_HandleTypeDef *hi3c, pI3C_NotifyCallbackTypeDef pNotifyCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the user callback allocation */
    if (pNotifyCallback == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    else if (HAL_I3C_STATE_READY == hi3c->State)
    {
      hi3c->NotifyCallback = pNotifyCallback;
    }
    else
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Register a User I3C dynamic address Callback to be used instead of the weak predefined callback.
  * @param  hi3c                : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                     information for the specified I3C.
  * @param  pTgtReqAddrCallback : [IN]  Pointer to the Callback function.
  * @retval HAL Status          :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_RegisterTgtReqDynamicAddrCallback(I3C_HandleTypeDef *hi3c,
                                                            pI3C_TgtReqDynamicAddrCallbackTypeDef pTgtReqAddrCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the user callback allocation */
    if (pTgtReqAddrCallback == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    else if (HAL_I3C_STATE_READY == hi3c->State)
    {
      hi3c->TgtReqDynamicAddrCallback = pTgtReqAddrCallback;
    }
    else
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Register a User I3C hot join Callback to be used instead of the weak predefined callback.
  * @param  hi3c                : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                     information for the specified I3C.
  * @param  pTgtHotJoinCallback : [IN]  Pointer to the Callback function.
  * @retval HAL Status          :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_RegisterTgtHotJoinCallback(I3C_HandleTypeDef *hi3c,
                                                     pI3C_TgtHotJoinCallbackTypeDef pTgtHotJoinCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the user callback allocation */
    if (pTgtHotJoinCallback == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    else if (HAL_I3C_STATE_READY == hi3c->State)
    {
      hi3c->TgtHotJoinCallback = pTgtHotJoinCallback;
    }
    else
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Unregister a user I3C Callback.
  *         The I3C callback is redirected to the weak predefined callback
  * @note   The HAL_I3C_UnRegisterCallback() may be called before HAL_I3C_Controller_Init() in HAL_I3C_STATE_RESET
  *         to un-register callbacks for HAL_I3C_MSPINIT_CB_ID and HAL_I3C_MSPDEINIT_CB_ID
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  callbackID : [IN]  ID of the callback to be unregistered.
  *                            This parameter can be one of the following values:
  *                            @arg @ref HAL_I3C_CTRL_TX_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_CTRL_RX_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_CTRL_MULTIPLE_XFER_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_CTRL_DAA_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_TGT_REQ_DYNAMIC_ADDR_CB_ID
  *                            @arg @ref HAL_I3C_TGT_TX_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_TGT_RX_COMPLETE_CB_ID
  *                            @arg @ref HAL_I3C_TGT_HOTJOIN_CB_ID
  *                            @arg @ref HAL_I3C_NOTIFY_CB_ID
  *                            @arg @ref HAL_I3C_ERROR_CB_ID
  *                            @arg @ref HAL_I3C_ABORT_CB_ID
  *                            @arg @ref HAL_I3C_MSPINIT_CB_ID
  *                            @arg @ref HAL_I3C_MSPDEINIT_CB_ID
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_UnRegisterCallback(I3C_HandleTypeDef *hi3c, HAL_I3C_CallbackIDTypeDef callbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    if (HAL_I3C_STATE_READY == hi3c->State)
    {
      switch (callbackID)
      {
        case HAL_I3C_CTRL_TX_COMPLETE_CB_ID :
          /* Legacy weak CtrlTxCpltCallback               */
          hi3c->CtrlTxCpltCallback = HAL_I3C_CtrlTxCpltCallback;
          break;

        case HAL_I3C_CTRL_RX_COMPLETE_CB_ID :
          /* Legacy weak CtrlRxCpltCallback               */
          hi3c->CtrlRxCpltCallback = HAL_I3C_CtrlRxCpltCallback;
          break;

        case HAL_I3C_CTRL_MULTIPLE_XFER_COMPLETE_CB_ID :
          /* Legacy weak CtrlMultipleXferCpltCallback     */
          hi3c->CtrlMultipleXferCpltCallback = HAL_I3C_CtrlMultipleXferCpltCallback;
          break;

        case HAL_I3C_CTRL_DAA_COMPLETE_CB_ID :
          /* Legacy weak CtrlDAACpltCallback              */
          hi3c->CtrlDAACpltCallback = HAL_I3C_CtrlDAACpltCallback;
          break;

        case HAL_I3C_TGT_REQ_DYNAMIC_ADDR_CB_ID :
          /*Legacy weak TgtReqDynamicAddrCallback          */
          hi3c->TgtReqDynamicAddrCallback = HAL_I3C_TgtReqDynamicAddrCallback;
          break;

        case HAL_I3C_TGT_TX_COMPLETE_CB_ID :
          /* Legacy weak TgtTxCpltCallback                 */
          hi3c->TgtTxCpltCallback = HAL_I3C_TgtTxCpltCallback;
          break;

        case HAL_I3C_TGT_RX_COMPLETE_CB_ID :
          /* Legacy weak TgtRxCpltCallback                 */
          hi3c->TgtRxCpltCallback = HAL_I3C_TgtRxCpltCallback;
          break;

        case HAL_I3C_TGT_HOTJOIN_CB_ID :
          /* Legacy weak TgtHotJoinCallback                */
          hi3c->TgtHotJoinCallback = HAL_I3C_TgtHotJoinCallback;
          break;

        case HAL_I3C_NOTIFY_CB_ID :
          /* Legacy weak NotifyCallback                    */
          hi3c->NotifyCallback = HAL_I3C_NotifyCallback;
          break;

        case HAL_I3C_ERROR_CB_ID :
          /* Legacy weak ErrorCallback                     */
          hi3c->ErrorCallback = HAL_I3C_ErrorCallback;
          break;

        case HAL_I3C_ABORT_CB_ID :
          /* Legacy weak AbortCpltCallback                 */
          hi3c->AbortCpltCallback = HAL_I3C_AbortCpltCallback;
          break;

        case HAL_I3C_MSPINIT_CB_ID :
          /* Legacy weak MspInit                           */
          hi3c->MspInitCallback = HAL_I3C_MspInit;
          break;

        case HAL_I3C_MSPDEINIT_CB_ID :
          /* Legacy weak MspDeInit                         */
          hi3c->MspDeInitCallback = HAL_I3C_MspDeInit;
          break;

        default :
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_CALLBACK;
          status =  HAL_ERROR;
          break;
      }
    }
    else if (HAL_I3C_STATE_RESET == hi3c->State)
    {
      switch (callbackID)
      {
        case HAL_I3C_MSPINIT_CB_ID :
          /* Legacy weak MspInit                           */
          hi3c->MspInitCallback = HAL_I3C_MspInit;
          break;

        case HAL_I3C_MSPDEINIT_CB_ID :
          /* Legacy weak MspDeInit                         */
          hi3c->MspDeInitCallback = HAL_I3C_MspDeInit;
          break;

        default :
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_CALLBACK;
          status =  HAL_ERROR;
          break;
      }
    }
    else
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status =  HAL_ERROR;
    }
  }

  return status;
}
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */

/**
  * @brief  This function permits to activate the I3C notifications.
  * @param  hi3c          : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                               information for the specified I3C.
  * @param  pXferData     : [IN/OUT] Pointer to an I3C_XferTypeDef structure that contains the reception buffer to
  *                               retrieve data during broadcast CCC DEFTGTS and DEFGRPA when Target mode only.
  * @param  interruptMask : [IN]  Parameter indicates which interrupts will be enabled.
  *                               This parameter can be any combination of @arg I3C_TARGET_INTERRUPT when
  *                               the I3C is in target mode or a combination of @arg I3C_CONTROLLER_INTERRUPT
  *                               when it is in controller mode.
  * @retval HAL Status    :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Controller_ActivateNotification(I3C_HandleTypeDef *hi3c, I3C_XferTypeDef *pXferData,
                                               uint32_t interruptMask)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));
    LS_ASSERT(IS_I3C_INTERRUPTMASK(hi3c->Mode, interruptMask));

    /* Check the I3C state and mode */
    if ((hi3c->State == HAL_I3C_STATE_RESET) ||
        ((hi3c->Mode != HAL_I3C_MODE_CONTROLLER) && (hi3c->Mode != HAL_I3C_MODE_TARGET)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {

      /* Store the controller event treatment function */
      hi3c->XferISR = I3C_Ctrl_Event_ISR;

      /* Update handle parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      hi3c->State         = HAL_I3C_STATE_LISTEN;
      hi3c->PreviousState = HAL_I3C_STATE_LISTEN;

      /* Note : The I3C interrupts must be enabled after unlocking current process to avoid the risk
      of I3C interrupt handle execution before current process unlock */
      /* Enable selected notifications */
      I3C_Enable_IRQ(hi3c, (interruptMask | I3C_XFER_LISTEN_IT));
    }
  }

  return status;
}

/**
  * @brief  This function permits to deactivate the I3C notifications.
  * @param  hi3c          : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                               information for the specified I3C.
  * @param  interruptMask : [IN]  Parameter indicates which interrupts will be disabled.
  *                               This parameter can be any combination of @arg I3C_TARGET_INTERRUPT when
  *                               the I3C is in target mode or a combination of @arg I3C_CONTROLLER_INTERRUPT
  *                               when it is in controller mode.
  * @retval HAL Status    :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Controller_DeactivateNotification(I3C_HandleTypeDef *hi3c, uint32_t interruptMask)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance parameter */


    /* Check on the State */
    if (hi3c->State == HAL_I3C_STATE_RESET)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Disable selected notifications */
      I3C_Disable_IRQ(hi3c, (interruptMask | I3C_XFER_LISTEN_IT));

      if (READ_REG(hi3c->Instance->IER) == 0U)
      {
        /* Update the XferISR pointer */
        hi3c->XferISR = NULL;

        /* Update I3C state */
        hi3c->State         = HAL_I3C_STATE_READY;
        hi3c->PreviousState = HAL_I3C_STATE_READY;
      }
    }
  }

  return status;
}

/**
  * @brief  Controller Transmission Complete callback.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_CtrlTxCpltCallback(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_CtrlTxCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Controller Reception Complete callback.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_CtrlRxCpltCallback(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_CtrlRxCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Controller multiple Direct CCC Command, I3C private or I2C transfer Complete callback.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_CtrlMultipleXferCpltCallback(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_CtrlMultipleXferCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Controller dynamic address assignment Complete callback.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_CtrlDAACpltCallback(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_CtrlDAACpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Target Request Dynamic Address callback.
  * @param  hi3c          : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                              for the specified I3C.
  * @param  targetPayload : [IN] Parameter indicates the target payload.
  * @retval None
  */
__weak void HAL_I3C_TgtReqDynamicAddrCallback(I3C_HandleTypeDef *hi3c, uint64_t targetPayload)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);
  UNUSED(targetPayload);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_TgtReqDynamicAddrCallback could be implemented in the user file
   */
}

/**
  * @brief  Target Transmission Complete callback.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_TgtTxCpltCallback(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_TgtTxCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Target Reception Complete callback.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_TgtRxCpltCallback(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_TgtRxCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Target Hot join process Complete callback.
  * @param  hi3c           : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                               information for the specified I3C.
  * @param  dynamicAddress : [IN] The returned dynamic address value after the hot join process.
  * @retval None
  */
__weak void HAL_I3C_TgtHotJoinCallback(I3C_HandleTypeDef *hi3c, uint8_t dynamicAddress)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);
  UNUSED(dynamicAddress);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_TgtHotJoinCallback could be implemented in the user file
   */
}

/**
  * @brief  Target/Controller Notification event callback.
  * @param  hi3c     : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                         for the specified I3C.
  * @param  eventId  : [IN] Parameter indicates which notification is signaled.
  *                         It can be a combination value of @ref HAL_I3C_Notification_ID_definition.
  * @retval None
  */
__weak void HAL_I3C_NotifyCallback(I3C_HandleTypeDef *hi3c, uint32_t eventId)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);
  UNUSED(eventId);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_NotifyCallback could be implemented in the user file
   */
}

/**
  * @brief  Abort complete callback.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_AbortCpltCallback(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_AbortCpltCallback could be implemented in the user file
   */
}

/**
  * @brief  Error callback.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                     for the specified I3C.
  * @retval None
  */
__weak void HAL_I3C_ErrorCallback(I3C_HandleTypeDef *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi3c);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_I3C_ErrorCallback could be implemented in the user file
   */
}

/**
  * @brief  This function handles I3C error interrupt request.
  * @param  hi3c : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                      for the specified I3C.
  * @retval None
  */
void HAL_I3C_ER_IRQHandler(I3C_HandleTypeDef *hi3c)
{
  uint32_t it_flag   = READ_REG(hi3c->Instance->EVR);
  uint32_t it_source = READ_REG(hi3c->Instance->IER);

  /* Check on the error interrupt flag and source */
  if ((I3C_CHECK_FLAG(it_flag, HAL_I3C_FLAG_ERRF) != RESET) &&
      (I3C_CHECK_IT_SOURCE(it_source, HAL_I3C_IT_ERRIE) != RESET))
  {
    if (hi3c->State != HAL_I3C_STATE_ABORT)
    {
      /* Get error sources */
      I3C_GetErrorSources(hi3c);
    }
    /* Clear the error flag */
    LL_I3C_ClearFlag_ERR(hi3c->Instance);
    /* Errors treatment */
    I3C_ErrorTreatment(hi3c);
  }
}

/**
  * @brief  This function handles I3C event interrupt request.
  * @param  hi3c : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                      for the specified I3C.
  * @retval None
  */
void HAL_I3C_EV_IRQHandler(I3C_HandleTypeDef *hi3c) /* Derogation MISRAC2012-Rule-8.13 */
{
  uint32_t it_flags   = READ_REG(hi3c->Instance->EVR);
  uint32_t it_sources = READ_REG(hi3c->Instance->IER);

  uint32_t it_masks   = (uint32_t)(it_flags & it_sources);

  /* I3C events treatment */
  if (hi3c->XferISR != NULL)
  {
    hi3c->XferISR(hi3c, it_masks);
  }
}
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group3 Configuration functions.
  * @brief    I3C configuration functions.
  *
@verbatim
 =======================================================================================================================
                                       ##### Configuration functions #####
 =======================================================================================================================
    [..]  This subsection provides a set of functions allowing to configure the I3C instances.

         (+) Call the function HAL_I3C_Ctrl_BusCharacteristicConfig() to modify the controller Bus Characteristics
             after initialize the bus through HAL_I3C_Controller_Init.

         (+) Call the function HAL_I3C_Tgt_BusCharacteristicConfig() to modify the target Bus Characteristics
             after initialize the bus through HAL_I3C_Controller_Init.

         (+) Call the function HAL_I3C_SetConfigFifo() to set FIFOs configuration (enabled FIFOs and
             threshold level) with the selected parameters in the configuration structure I3C_FifoConfTypeDef.

         (+) Call the function HAL_I3C_Ctrl_Config() to configure the I3C Controller instances with the selected
             parameters in the configuration structure I3C_CtrlConfTypeDef.
             This function is called only when mode is Controller.

         (+) Call the function HAL_I3C_Tgt_Config() to configure the I3C Target instances with the selected
             parameters in the configuration structure I3C_TgtConfTypeDef.
             This function is called only when mode is Target.

         (+) Call the function HAL_I3C_Ctrl_ConfigBusDevices() to configure Hardware device characteristics register
             with Devices capabilities present on the Bus.
             All different characteristics must be fill through structure I3C_DeviceConfTypeDef.
             This function is called only when mode is Controller.

         (+) Call the function HAL_I3C_AddDescToFrame() to prepare the full transfer usecase in a transfer descriptor
             which contained different buffer pointers and their associated size through I3C_XferTypeDef.
             This function must be called before initiate any communication transfer.
         (+) Call the function HAL_I3C_Ctrl_SetConfigResetPattern() to configure the insertion of the reset pattern
             at the end of a Frame.
         (+) Call the function HAL_I3C_Ctrl_GetConfigResetPattern() to get the current reset pattern configuration

     [..]
       (@) Users must call all above functions after I3C initialization.

@endverbatim
  * @{
  */

/**
  * @brief  Configure the Controller Bus characterics.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pConfig    : [IN]  Pointer to an LL_I3C_CtrlBusConfTypeDef structure contains controller bus configuration.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_BusCharacteristicConfig(I3C_HandleTypeDef *hi3c,
                                                       const LL_I3C_CtrlBusConfTypeDef *pConfig)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t waveform_value;
  uint32_t timing_value;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check on user parameters */
    if (pConfig == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* Check the I3C state and mode */
    else if ((hi3c->State != HAL_I3C_STATE_READY) || (hi3c->Mode != HAL_I3C_MODE_CONTROLLER))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Check the parameters */
      LS_ASSERT(IS_I3C_SDAHOLDTIME_VALUE(pConfig->SDAHoldTime));
      LS_ASSERT(IS_I3C_WAITTIME_VALUE(pConfig->WaitTime));

      /* Disable the selected I3C peripheral */
      LL_I3C_Disable(hi3c->Instance);

      /*----------------- SCL signal waveform configuration : I3C timing register 0 (I3C_TIMINGR0) ------------------ */
      /* Set the controller SCL waveform */
      waveform_value = ((uint32_t)pConfig->SCLPPLowDuration                                    |
                        ((uint32_t)pConfig->SCLI3CHighDuration << I3C_TIMINGR0_SCLH_I3C_POS)   |
                        ((uint32_t)pConfig->SCLODLowDuration << I3C_TIMINGR0_SCLL_OD_POS)      |
                        ((uint32_t)pConfig->SCLI2CHighDuration << I3C_TIMINGR0_SCLH_I2C_POS));

      LL_I3C_ConfigClockWaveForm(hi3c->Instance, waveform_value);

      /*------------------ Timing configuration : I3C timing register 1 (I3C_TIMINGR1) ------------------------------ */
      /* Set SDA hold time, activity state, bus free duration and bus available duration */
      timing_value = ((uint32_t)pConfig->SDAHoldTime                                 |
                      (uint32_t)pConfig->WaitTime                                    |
                      ((uint32_t)pConfig->BusFreeDuration <<  I3C_TIMINGR1_FREE_POS) |
                      (uint32_t)pConfig->BusIdleDuration);

      LL_I3C_SetCtrlBusCharacteristic(hi3c->Instance, timing_value);

      /* Enable the selected I3C peripheral */
      LL_I3C_Enable(hi3c->Instance);
    }
  }

  return status;
}

/**
  * @brief  Set I3C bus devices configuration.
  * @note   This function is called only when the I3C instance is initialized as controller.
  *         This function can be called by the controller application to help the automatic treatment when target have
  *         capability of IBI and/or Control-Role.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pDesc      : [IN]  Pointer to an I3C_DeviceConfTypeDef descriptor that contains the bus devices
  *                            configurations.
  * @param  nbDevice   : [IN]  Value specifies the number of devices to be treated.
  *                            This parameter must be a number between Min_Data=1U and Max_Data=4U.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_ConfigBusDevices(I3C_HandleTypeDef           *hi3c,
                                                const I3C_DeviceConfTypeDef *pDesc,
                                                uint8_t                      nbDevice)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t write_value;

  /* Check the I3C handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check on user parameters */
    if (pDesc == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* Check the I3C state and mode */
    else if ((hi3c->State == HAL_I3C_STATE_RESET) || (hi3c->Mode != HAL_I3C_MODE_CONTROLLER))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Check the instance and the mode parameters */
  
      LS_ASSERT(IS_I3C_MODE(hi3c->Mode));
      LS_ASSERT(IS_I3C_DEVICE_VALUE(nbDevice));

      /* Loop on the nbDevice to be treated */
      for (uint32_t index = 0U; index < nbDevice; index++)
      {
        /* Check configuration parameters values */
        LS_ASSERT(IS_I3C_DEVICE_VALUE(pDesc[index].DeviceIndex));
        LS_ASSERT(IS_I3C_DYNAMICADDRESS_VALUE(pDesc[index].TargetDynamicAddr));
        LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(pDesc[index].IBIAck));
        LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(pDesc[index].CtrlRoleReqAck));
        LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(pDesc[index].CtrlStopTransfer));
        LS_ASSERT(IS_I3C_FUNCTIONALSTATE_VALUE(pDesc[index].IBIPayload));

        /* Set value to be written */
        write_value = (((uint32_t)pDesc[index].TargetDynamicAddr << I3C_DEVRX_DA_POS)     |
                       ((uint32_t)pDesc[index].IBIAck            << I3C_DEVRX_IBIACK_POS) |
                       ((uint32_t)pDesc[index].CtrlRoleReqAck    << I3C_DEVRX_CRACK_POS)  |
                       ((uint32_t)pDesc[index].CtrlStopTransfer  << I3C_DEVRX_SUSP_POS)   |
                       ((uint32_t)pDesc[index].IBIPayload        << I3C_DEVRX_IBIDEN_POS));

        /* Write configuration in the DEVRx register */
        WRITE_REG(hi3c->Instance->DEVRX[(pDesc[index].DeviceIndex - 1U)], write_value);
      }
    }
  }

  return status;
}

/**
  * @brief  Add Private or CCC descriptor in the user data transfer descriptor.
  * @note   This function must be called before initiate any communication transfer. This function help the preparation
  *         of the full transfer usecase in a transfer descriptor which contained different buffer pointers
  *         and their associated size through I3C_XferTypeDef.
  * @note   The Tx FIFO threshold @ref HAL_I3C_TXFIFO_THRESHOLD_4_4 is not allowed when the transfer descriptor contains
  *         multiple transmission frames.
  * @param  hi3c          : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                               for the specified I3C.
  * @param  pCCCDesc      : [IN]  Pointer to an I3C_CCCTypeDef structure that contains the CCC descriptor information.
  * @param  pPrivateDesc  : [IN]  Pointer to an I3C_PrivateTypeDef structure that contains the transfer descriptor.
  * @param  pXferData     : [IN/OUT] Pointer to an I3C_XferTypeDef structure that contains required transmission buffers
  *                                  (control buffer, data buffer and status buffer).
  * @param  nbFrame       : [IN]  The number of CCC commands or the number of device to treat.
  * @param  option        : [IN]  Value indicates the transfer option. It can be one value of @ref I3C_OPTION_DEFINITION
  * @retval HAL Status    :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_AddDescToFrame(I3C_HandleTypeDef         *hi3c,
                                         const I3C_CCCTypeDef      *pCCCDesc,
                                         const I3C_PrivateTypeDef  *pPrivateDesc,
                                         I3C_XferTypeDef           *pXferData,
                                         uint8_t                    nbFrame,
                                         uint32_t                   option)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Set handle transfer parameters */
    hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
    hi3c->pCCCDesc      = pCCCDesc;
    hi3c->pPrivateDesc  = pPrivateDesc;
    hi3c->pXferData     = pXferData;
    hi3c->RxXferCount   = 0;
    hi3c->TxXferCount   = 0;

    /* Prepare Direction, and Check on user parameters */
    if (((option & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_CCC) ||
        ((option & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT))
    {
      /* Check on user parameters */
      if ((pCCCDesc == NULL)  ||
          (pXferData == NULL) ||
          (nbFrame < 1U)      ||
          (((option & (I3C_OPERATION_TYPE_MASK        | I3C_DEFINE_BYTE_MASK)) == \
            (LL_I3C_CONTROLLER_MTYPE_DIRECT | I3C_DEFINE_BYTE_MASK)) && (pCCCDesc->CCCBuf.Size == 0U)))
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
        status = HAL_ERROR;
      }
    }
    else
    {
      /* Check on user parameters */
      if ((pPrivateDesc == NULL) || (pXferData == NULL) || (nbFrame <= 0U))
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
        status = HAL_ERROR;
      }
    }

    if (status == HAL_OK)
    {
      /* check on the State */
      if ((handle_state == HAL_I3C_STATE_READY) || (handle_state == HAL_I3C_STATE_LISTEN))
      {
        /* I3C control buffer prior preparation */
        if (I3C_ControlBuffer_PriorPreparation(hi3c, nbFrame, option) != HAL_OK)
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
          status = HAL_ERROR;
        }

        /* I3C Tx Buffer prior preparation, set and check RxCount */
        if (I3C_Xfer_PriorPreparation(hi3c, nbFrame, option) != HAL_OK)
        {
          status = HAL_ERROR;
        }
      }
      else
      {
        status = HAL_BUSY;
      }
    }
  }

  return status;
}

/**
  * @brief Set the configuration of the inserted reset pattern at the end of a Frame.
  * @note  When the transfer descriptor contains multiple frames with RESTART option, the reset pattern at the end of
  *        RSTACT CCC frame is not possible.
  * @param  hi3c         : [IN] Pointer to an I3C_HandleTypeDef structure that contains
  *                             the configuration information for the specified I3C.
  * @param  resetPattern : [IN] Specifies the reset pattern configuration.
  *                             It can be a value of @ref I3C_RESET_PATTERN
  * @retval HAL Status   :      Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_SetConfigResetPattern(I3C_HandleTypeDef *hi3c, uint32_t resetPattern)
{
  HAL_StatusTypeDef status = HAL_OK;
  HAL_I3C_StateTypeDef handle_state;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));
    LS_ASSERT(IS_I3C_RESET_PATTERN(resetPattern));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* check on the Mode */
    if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      hi3c->State = HAL_I3C_STATE_BUSY;

      if (resetPattern == HAL_I3C_RESET_PATTERN_ENABLE)
      {
        LL_I3C_EnableResetPattern(hi3c->Instance);
      }
      else
      {
        LL_I3C_DisableResetPattern(hi3c->Instance);
      }

      /* At the end of process update state to Previous state */
      I3C_StateUpdate(hi3c);
    }
  }

  return status;
}

/**
  * @brief Get the configuration of the inserted reset pattern at the end of a Frame.
  * @param  hi3c          : [IN] Pointer to an I3C_HandleTypeDef structure that contains
  *                              the configuration information for the specified I3C.
  * @param  pResetPattern : [OUT] Pointer to the current reset pattern configuration.
  *                               It can be a value of @ref I3C_RESET_PATTERN
  * @retval HAL Status    :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_GetConfigResetPattern(I3C_HandleTypeDef *hi3c, uint32_t *pResetPattern)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  /* Check on user parameters */
  else if (pResetPattern == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check if the reset pattern configuration is enabled */
    if (LL_I3C_IsEnabledResetPattern(hi3c->Instance) == 1U)
    {
      *pResetPattern     = HAL_I3C_RESET_PATTERN_ENABLE;
    }
    else
    {
      *pResetPattern     = HAL_I3C_RESET_PATTERN_DISABLE;
    }
  }

  return status;
}

/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group4 FIFO Management functions.
  * @brief    I3C FIFO management functions.
  *
@verbatim
 =======================================================================================================================
                                      ##### FIFO Management functions #####
 =======================================================================================================================
    [..]  This subsection provides a set of functions allowing to manage I3C FIFOs.

         (+) Call the function HAL_I3C_FlushAllFifo() to flush the content of all used FIFOs (Control, Status,
             Tx and Rx FIFO).
         (+) Call the function HAL_I3C_FlushTxFifo() to flush only the content of Tx FIFO.
         (+) Call the function HAL_I3C_FlushRxFifo() to flush only the content of Rx FIFO.
         (+) Call the function HAL_I3C_FlushControlFifo() to flush only the content of Control FIFO.
             This function is called only when mode is controller.
         (+) Call the function HAL_I3C_FlushStatusFifo() to flush only the content of Status FIFO.
             This function is called only when mode is controller.
         (+) Call the function HAL_I3C_ClearConfigFifo() to clear the FIFOs configuration and set it to default values.
         (+) Call the function HAL_I3C_GetConfigFifo() to get the current FIFOs configuration (enabled FIFOs and
             threshold level).

         (+) Users must not call all above functions before I3C initialization.

         (+) Users should call Flush APIs after an end of process, before starting a transfer or in case of bus
             failure and error detection.

@endverbatim
  * @{
  */

/**
  * @brief  Flush all I3C FIFOs content.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_FlushAllFifo(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t cfgr_value;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check the I3C state */
    if (hi3c->State == HAL_I3C_STATE_RESET)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Flush the content of Tx and Rx Fifo */
      cfgr_value = (I3C_CFGR_TXFLUSH | I3C_CFGR_RXFLUSH);

      /* Check on the I3C mode: Control and status FIFOs available only with controller mode */
      if (hi3c->Mode == HAL_I3C_MODE_CONTROLLER)
      {
        /* Flush the content of Control and Status Fifo */
        cfgr_value = I3C_CFGR_CFLUSH|I3C_CFGR_SFLUSH;
      }

      /* Set configuration in the CFGR register */
      MODIFY_REG(hi3c->Instance->CFGR, cfgr_value, cfgr_value);
    }
  }

  return status;
}

/**
  * @brief  Flush I3C Tx FIFO content.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_FlushTxFifo(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check the I3C state */
    if (hi3c->State == HAL_I3C_STATE_RESET)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Flush the content of Tx Fifo */
      LL_I3C_RequestTxFIFOFlush(hi3c->Instance);
    }
  }

  return status;
}

/**
  * @brief  Flush I3C Rx FIFO content.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_FlushRxFifo(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {

    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check the I3C state */
    if (hi3c->State == HAL_I3C_STATE_RESET)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Flush the content of Rx Fifo */
      LL_I3C_RequestRxFIFOFlush(hi3c->Instance);
    }
  }

  return status;
}

/**
  * @brief  Flush I3C control FIFO content.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_FlushControlFifo(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check the I3C state and mode */
    if ((hi3c->State == HAL_I3C_STATE_RESET) || (hi3c->Mode != HAL_I3C_MODE_CONTROLLER))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Flush the content of Control Fifo */
      LL_I3C_RequestControlFIFOFlush(hi3c->Instance);
    }
  }

  return status;
}

/**
  * @brief  Flush I3C status FIFO content.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_FlushStatusFifo(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check the I3C state and mode */
    if ((hi3c->State == HAL_I3C_STATE_RESET) || (hi3c->Mode != HAL_I3C_MODE_CONTROLLER))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Flush the content of Control Fifo */
      LL_I3C_RequestStatusFIFOFlush(hi3c->Instance);
    }
  }

  return status;
}

/**
  * @brief  Clear I3C FIFOs configuration and set it to default values.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_ClearConfigFifo(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t cfgr_value;
  uint32_t cfgr_mask;

  /* Check the I3C handle allocation */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check the I3C state */
    if (hi3c->State == HAL_I3C_STATE_RESET)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Clear Tx Fifo and Rx Fifo threshold and set it to default value */
      cfgr_value = (LL_I3C_TXFIFO_THRESHOLD_1_4 | LL_I3C_RXFIFO_THRESHOLD_1_4);
      cfgr_mask  = (I3C_CFGR_TXTHRES | I3C_CFGR_RXTHRES);

      /* Check on the I3C mode: Control and status FIFOs available only with controller mode */
      if (hi3c->Mode == HAL_I3C_MODE_CONTROLLER)
      {
        /* Disable the status and Control Fifo state */
        cfgr_value |= (HAL_I3C_STATUSFIFO_DISABLE);
        cfgr_mask  |= I3C_CFGR_SMODE;
      }

      /* Set configuration in the CFGR register */
      MODIFY_REG(hi3c->Instance->CFGR, cfgr_mask, cfgr_value);
    }
  }

  return status;
}

/**
  * @brief  Get I3C FIFOs current configuration.
  * @param  hi3c       : [IN]     Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                               for the specified I3C.
  * @param  pConfig    : [IN/OUT] Pointer to an I3C_FifoConfTypeDef structure that returns current FIFOs configuration.
  * @retval HAL Status :          Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_GetConfigFifo(I3C_HandleTypeDef *hi3c, I3C_FifoConfTypeDef *pConfig)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the I3C handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Check on user parameters */
    if (pConfig == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* Check the I3C state */
    else if (hi3c->State == HAL_I3C_STATE_RESET)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Get Tx Fifo threshold */
      pConfig->TxFifoThreshold = LL_I3C_GetTxFIFOThreshold(hi3c->Instance);

      /* Get Rx Fifo threshold */
      pConfig->RxFifoThreshold = LL_I3C_GetRxFIFOThreshold(hi3c->Instance);

      /* Get the status Fifo state */
      pConfig->StatusFifo = (uint32_t)(LL_I3C_IsEnabledStatusFIFO(hi3c->Instance) << I3C_CFGR_SMODE_POS);
    }
  }

  return status;
}
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group5 Controller operational functions.
  * @brief    I3C controller operational functions.
  *
@verbatim
 =======================================================================================================================
                                  ##### Controller operational functions #####
 =======================================================================================================================
    [..]  This subsection provides a set of functions allowing to manage controller I3C operation.

         (+) Call the function HAL_I3C_Ctrl_TransmitCCC() to transmit direct write or a broadcast
             CCC command in polling mode.
         (+) Call the function HAL_I3C_Ctrl_TransmitCCC_IT() to transmit direct write or a broadcast
             CCC command in interrupt mode.
         (+) Call the function HAL_I3C_Ctrl_TransmitCCC_DMA() to transmit direct write or a broadcast
             CCC command in DMA mode.
         (+) Call the function HAL_I3C_Ctrl_ReceiveCCC() to transmit direct read CCC command in polling mode.
         (+) Call the function HAL_I3C_Ctrl_ReceiveCCC_IT() to transmit direct read CCC command in interrupt mode.
         (+) Call the function HAL_I3C_Ctrl_ReceiveCCC_DMA() to transmit direct read CCC command in DMA mode.
         (+) Call the function HAL_I3C_Ctrl_Transmit() to transmit private data in polling mode.
         (+) Call the function HAL_I3C_Ctrl_Transmit_IT() to transmit private data in interrupt mode.
         (+) Call the function HAL_I3C_Ctrl_Transmit_DMA() to transmit private data in DMA mode.
         (+) Call the function HAL_I3C_Ctrl_Receive() to receive private data in polling mode.
         (+) Call the function HAL_I3C_Ctrl_Receive_IT() to receive private data in interrupt mode.
         (+) Call the function HAL_I3C_Ctrl_Receive_DMA() to receive private data in DMA mode.
         (+) Call the function HAL_I3C_Ctrl_MultipleTransfer_IT() to transfer I3C or I2C private data or CCC command
             in multiple direction in interrupt mode.
         (+) Call the function HAL_I3C_Ctrl_MultipleTransfer_DMA() to transfer I3C or I2C private data or CCC command
             in multiple direction in DMA mode.
         (+) Call the function HAL_I3C_Ctrl_DynAddrAssign() to send a broadcast ENTDAA CCC
             command in polling mode.
         (+) Call the function HAL_I3C_Ctrl_DynAddrAssign_IT() to send a broadcast ENTDAA CCC
             command in interrupt mode.
         (+) Call the function HAL_I3C_Ctrl_SetDynAddr() to set, asscociate the target dynamic address
             during the Dynamic Address Assignment processus.
         (+) Call the function HAL_I3C_Ctrl_IsDeviceI3C_Ready() to check if I3C target device is ready.
         (+) Call the function HAL_I3C_Ctrl_IsDeviceI2C_Ready() to check if I2C target device is ready.
         (+) Call the function HAL_I3C_Ctrl_GenerateArbitration to send arbitration
            (message header {S + 0x7E + W + STOP}) in polling mode

         (+) Those functions are called only when mode is Controller.

@endverbatim
  * @{
  */

/**
  * @brief  Controller transmit direct write or a broadcast CCC command in polling mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The Tx FIFO threshold @ref HAL_I3C_TXFIFO_THRESHOLD_4_4 is not allowed when the transfer descriptor contains
  *         multiple transmission frames.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required transmission buffers
  *                            (control buffer, data buffer and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @param  timeout    : [IN]  Timeout duration in millisecond.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_TransmitCCC(I3C_HandleTypeDef *hi3c,
                                           I3C_XferTypeDef   *pXferData,
                                           uint32_t           timeout)
{
  uint32_t tickstart;
  uint32_t exit_condition;
  HAL_StatusTypeDef status = HAL_OK;
  HAL_I3C_StateTypeDef handle_state;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL) ||
        ((hi3c->TxXferCount != 0U) && (pXferData->TxBuf.pBuffer == NULL)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      /* Update returned status value */
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode = HAL_I3C_ERROR_NONE;
      hi3c->State     = HAL_I3C_STATE_BUSY_TX;
      hi3c->pXferData = pXferData;

      hi3c->ptrTxFunc = &I3C_TransmitByteTreatment;

      /* Init tickstart for timeout management */
      tickstart = systick_get_value();

      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);

      /* Do while until FC (Frame Complete) is set or timeout */
      do
      {
        /* Check if hardware asks for control data */
        if (hi3c->ControlXferCount > 0U)
        {
          /* Call control data treatment function */
          I3C_ControlDataTreatment(hi3c);
        }

        /* Check if hardware asks for Tx data */
        if (hi3c->TxXferCount > 0U)
        {
          /* Call transmit treatment function */
          hi3c->ptrTxFunc(hi3c);
        }

        /* Check for the timeout */
        if (timeout != HAL_MAX_DELAY)
        {
          if (((systick_get_value() - tickstart) > timeout) || (timeout == 0U))
          {
            hi3c->ErrorCode = HAL_I3C_ERROR_TIMEOUT;
            status = HAL_TIMEOUT;
            break;
          }
        }

        if ((__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET) && (hi3c->ControlXferCount > 0U))
        {
          /* Clear frame complete flag */
          LL_I3C_ClearFlag_FC(hi3c->Instance);

          /* Then Initiate a Start condition */
          LL_I3C_RequestTransfer(hi3c->Instance);
        }

        /* Calculate exit_condition value based on Frame complete and error flags */
        exit_condition = (READ_REG(hi3c->Instance->EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
      } while ((exit_condition == 0U) ||
               ((exit_condition == I3C_EVR_FCF) && (hi3c->ControlXferCount > 0U)));

      /* Clear frame complete flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET)
      {
        LL_I3C_ClearFlag_FC(hi3c->Instance);
      }

      /* Check on error flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_ERRF) == SET)
      {
        /* Clear error flag */
        LL_I3C_ClearFlag_ERR(hi3c->Instance);

        /* Update handle error code parameter */
        I3C_GetErrorSources(hi3c);

        /* Update returned status value */
        status = HAL_ERROR;
      }

      /* At the end of Tx process update state to Previous state */
      I3C_StateUpdate(hi3c);
    }
  }

  return status;
}

/**
  * @brief  Controller transmit direct write or a broadcast CCC command in interrupt mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The Tx FIFO threshold @ref HAL_I3C_TXFIFO_THRESHOLD_4_4 is not allowed when the transfer descriptor contains
  *         multiple transmission frames.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required transmission buffers
  *                            (control buffer, data buffer and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_TransmitCCC_IT(I3C_HandleTypeDef *hi3c,
                                              I3C_XferTypeDef   *pXferData)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL) ||
        ((hi3c->TxXferCount != 0U) && (pXferData->TxBuf.pBuffer == NULL)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

      if (handle_state == HAL_I3C_STATE_LISTEN)
      {
        hi3c->XferISR = I3C_Ctrl_Tx_Listen_Event_ISR;
      }
      else
      {
        hi3c->XferISR = I3C_Ctrl_Tx_ISR;
      }

      hi3c->pXferData = pXferData;
      hi3c->State     = HAL_I3C_STATE_BUSY_TX;


      hi3c->ptrTxFunc = &I3C_TransmitByteTreatment;

      /* Note : The I3C interrupts must be enabled after unlocking current process to avoid the risk
      of I3C interrupt handle execution before current process unlock */

      /* Enable Tx process interrupts */
      I3C_Enable_IRQ(hi3c, I3C_XFER_CONTROLLER_TX_IT);

      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);
    }
  }

  return status;
}

/**
  * @brief  Controller transmit direct read CCC command in polling mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The RxBuf.Size must be equal to the sum of all RxBuf.Size exist in the descriptor.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required transmission buffers
  *                            (control buffer, data buffer and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @param  timeout    : [IN]  Timeout duration in millisecond.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_ReceiveCCC(I3C_HandleTypeDef *hi3c,
                                          I3C_XferTypeDef   *pXferData,
                                          uint32_t           timeout)
{
  uint32_t tickstart;
  uint32_t exit_condition;
  HAL_StatusTypeDef status = HAL_OK;
  HAL_I3C_StateTypeDef handle_state;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL)                     ||
        (pXferData->RxBuf.pBuffer == NULL)      ||
        ((pXferData->TxBuf.pBuffer == NULL) && (hi3c->TxXferCount != 0U)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode   = HAL_I3C_ERROR_NONE;
      hi3c->State       = HAL_I3C_STATE_BUSY_RX;
      hi3c->pXferData   = pXferData;
      hi3c->RxXferCount = hi3c->pXferData->RxBuf.Size;

      /* Check on CCC defining byte */
      if (hi3c->TxXferCount != 0U)
      {
        /* Set byte treatment function pointer */
        hi3c->ptrTxFunc = &I3C_TransmitByteTreatment;
      }

      hi3c->ptrRxFunc = &I3C_ReceiveByteTreatment;

      /* Init tickstart for timeout management */
      tickstart = systick_get_value();

      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);

      /* Do while until FC (Frame Complete) is set or timeout */
      do
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);

        if (hi3c->TxXferCount != 0U)
        {
          /* Call transmit treatment function */
          hi3c->ptrTxFunc(hi3c);
        }

        /* Call receive treatment function */
        hi3c->ptrRxFunc(hi3c);

        /* Check for the timeout */
        if (timeout != HAL_MAX_DELAY)
        {
          if (((systick_get_value() - tickstart) > timeout) || (timeout == 0U))
          {
            hi3c->ErrorCode = HAL_I3C_ERROR_TIMEOUT;
            status = HAL_TIMEOUT;

            break;
          }
        }

        if ((__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET) && (hi3c->ControlXferCount > 0U))
        {
          /* Clear frame complete flag */
          LL_I3C_ClearFlag_FC(hi3c->Instance);

          /* Then Initiate a Start condition */
          LL_I3C_RequestTransfer(hi3c->Instance);
        }

        /* Calculate exit_condition value based on Frame complete and error flags */
        exit_condition = (READ_REG(hi3c->Instance->EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
      } while ((exit_condition == 0U) ||
               ((exit_condition == I3C_EVR_FCF) && (hi3c->ControlXferCount > 0U)));

      /* Clear frame complete flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET)
      {
        LL_I3C_ClearFlag_FC(hi3c->Instance);
      }

      /* Check if all data bytes are received */
      if ((hi3c->RxXferCount != 0U) && (status == HAL_OK))
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_SIZE;
        status = HAL_ERROR;
      }

      /* Check on error flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_ERRF) == SET)
      {
        /* Clear error flag */
        LL_I3C_ClearFlag_ERR(hi3c->Instance);

        /* Update handle error code parameter */
        I3C_GetErrorSources(hi3c);

        /* Update returned status value */
        status = HAL_ERROR;
      }

      /* At the end of Rx process update state to Previous state */
      I3C_StateUpdate(hi3c);
    }
  }

  return status;
}

/**
  * @brief  Controller transmit direct read CCC command in interrupt mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The RxBuf.Size must be equal to the sum of all RxBuf.Size exist in the descriptor.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required transmission buffers
  *                            (control buffer, data buffer and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_ReceiveCCC_IT(I3C_HandleTypeDef *hi3c,
                                             I3C_XferTypeDef   *pXferData)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL)                     ||
        (pXferData->RxBuf.pBuffer == NULL)      ||
        ((pXferData->TxBuf.pBuffer == NULL) && (hi3c->TxXferCount != 0U)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode   = HAL_I3C_ERROR_NONE;
      if (handle_state == HAL_I3C_STATE_LISTEN)
      {
        hi3c->XferISR   = I3C_Ctrl_Rx_Listen_Event_ISR;
      }
      else
      {
        hi3c->XferISR   = I3C_Ctrl_Rx_ISR;
      }
      hi3c->pXferData   = pXferData;
      hi3c->RxXferCount = pXferData->RxBuf.Size;
      hi3c->State       = HAL_I3C_STATE_BUSY_RX;

      /* Check on CCC defining byte */
      if (hi3c->TxXferCount != 0U)
      {
        /* Set byte treatment function pointer */
        hi3c->ptrTxFunc = &I3C_TransmitByteTreatment;
      }

      hi3c->ptrRxFunc = &I3C_ReceiveByteTreatment;

      /* Note : The I3C interrupts must be enabled after unlocking current process to avoid the risk
      of I3C interrupt handle execution before current process unlock */

      /* Enable Rx process interrupts */
      I3C_Enable_IRQ(hi3c, I3C_XFER_CONTROLLER_RX_CCC_IT);

      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);

    }
  }

  return status;
}

/**
  * @brief  Controller private write in polling mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The Tx FIFO threshold @ref HAL_I3C_TXFIFO_THRESHOLD_4_4 is not allowed when the transfer descriptor contains
  *         multiple transmission frames.
  * @note   The TxBuf.Size must be equal to the sum of all TxBuf.Size exist in the descriptor.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required transmission buffers
  *                            (control buffer, data buffer and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @param  timeout    : [IN]  Timeout duration in millisecond.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_Transmit(I3C_HandleTypeDef   *hi3c,
                                        I3C_XferTypeDef     *pXferData,
                                        uint32_t             timeout)
{
  uint32_t tickstart;
  uint32_t exit_condition;
  HAL_StatusTypeDef status = HAL_OK;
  HAL_I3C_StateTypeDef handle_state;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL) ||
        ((hi3c->TxXferCount != 0U) && (pXferData->TxBuf.pBuffer == NULL)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      hi3c->State         = HAL_I3C_STATE_BUSY_TX;
      hi3c->pXferData     = pXferData;

      hi3c->ptrTxFunc = &I3C_TransmitByteTreatment;

      /* Init tickstart for timeout management */
      tickstart = systick_get_value();

      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);


      /* Do while until FC (Frame Complete) is set or timeout */
      do
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);

        /* Call transmit treatment function */
        hi3c->ptrTxFunc(hi3c);

        /* Check for the timeout */
        if (timeout != HAL_MAX_DELAY)
        {
          if (((systick_get_value() - tickstart) > timeout) || (timeout == 0U))
          {
            hi3c->ErrorCode = HAL_I3C_ERROR_TIMEOUT;
            status = HAL_TIMEOUT;

            break;
          }
        }

        while((__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_SFNEF) == SET))
        {
          LL_I3C_GetXferDataCount(hi3c->Instance);
        }
        
        if ((__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET) && (hi3c->ControlXferCount > 0U))
        {
          /* Clear frame complete flag */
          LL_I3C_ClearFlag_FC(hi3c->Instance);

          /* Then Initiate a Start condition */
          LL_I3C_RequestTransfer(hi3c->Instance);
        }

        /* Calculate exit_condition value based on Frame complete and error flags */
        exit_condition = (READ_REG(hi3c->Instance->EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
      } while ((exit_condition == 0U) ||
               ((exit_condition == I3C_EVR_FCF) && (hi3c->ControlXferCount > 0U)));

      while((__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_SFNEF) == SET))
      {
        LL_I3C_GetXferDataCount(hi3c->Instance);
      }
      /* Clear frame complete flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET)
      {
        LL_I3C_ClearFlag_FC(hi3c->Instance);
      }

      /* Check if all data bytes are transmitted */
      if ((hi3c->TxXferCount != 0U) && (status == HAL_OK))
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_SIZE;
        status = HAL_ERROR;
      }

      /* Check on error flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_ERRF) == SET)
      {
        /* Clear error flag */
        LL_I3C_ClearFlag_ERR(hi3c->Instance);

        /* Update handle error code parameter */
        I3C_GetErrorSources(hi3c);

        /* Update returned status value */
        status = HAL_ERROR;
      }

      /* At the end of Tx process update state to Previous state */
      I3C_StateUpdate(hi3c);
    }
  }

  return status;
}

/**
  * @brief  Controller private write in interrupt mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The Tx FIFO threshold @ref HAL_I3C_TXFIFO_THRESHOLD_4_4 is not allowed when the transfer descriptor contains
  *         multiple transmission frames.
  * @note   The TxBuf.Size must be equal to the sum of all TxBuf.Size exist in the descriptor.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required transmission buffers
  *                            (control buffer, data buffer and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_Transmit_IT(I3C_HandleTypeDef   *hi3c,
                                           I3C_XferTypeDef     *pXferData)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL) ||
        ((hi3c->TxXferCount != 0U) && (pXferData->TxBuf.pBuffer == NULL)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      if (handle_state == HAL_I3C_STATE_LISTEN)
      {
        hi3c->XferISR     = I3C_Ctrl_Tx_Listen_Event_ISR;
      }
      else
      {
        hi3c->XferISR     = I3C_Ctrl_Tx_ISR;
      }
      hi3c->pXferData     = pXferData;
      hi3c->State         = HAL_I3C_STATE_BUSY_TX;

      hi3c->ptrTxFunc = &I3C_TransmitByteTreatment;

      /* Note : The I3C interrupts must be enabled after unlocking current process to avoid the risk
      of I3C interrupt handle execution before current process unlock */

      /* Enable Tx process interrupts */
      I3C_Enable_IRQ(hi3c, I3C_XFER_CONTROLLER_TX_IT|(HAL_I3C_IT_IBIIE | I3C_XFER_LISTEN_IT));

      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);
    }
  }
  return status;
}

/**
  * @brief  Controller private read in polling mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The RxBuf.Size must be equal to the sum of all RxBuf.Size exist in the descriptor.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required reception buffers
  *                            (control buffer, data buffer and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @param  timeout    : [IN]  Timeout duration in millisecond.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_Receive(I3C_HandleTypeDef   *hi3c,
                                       I3C_XferTypeDef     *pXferData,
                                       uint32_t             timeout)
{
  uint32_t tickstart;
  uint32_t exit_condition;
  HAL_StatusTypeDef status = HAL_OK;
  HAL_I3C_StateTypeDef handle_state;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL) || (pXferData->RxBuf.pBuffer == NULL))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      hi3c->State         = HAL_I3C_STATE_BUSY_RX;
      hi3c->pXferData     = pXferData;
      hi3c->RxXferCount   = hi3c->pXferData->RxBuf.Size;

      hi3c->ptrRxFunc = &I3C_ReceiveByteTreatment;

      /* Init tickstart for timeout management */
      tickstart = systick_get_value();


      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);

      /* Do while until FC (Frame Complete) is set or timeout */
      do
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);

        /* Call receive treatment function */
        hi3c->ptrRxFunc(hi3c);

        /* Check for the timeout */
        if (timeout != HAL_MAX_DELAY)
        {
          if (((systick_get_value() - tickstart) > timeout) || (timeout == 0U))
          {
            hi3c->ErrorCode = HAL_I3C_ERROR_TIMEOUT;
            status = HAL_TIMEOUT;

            break;
          }
        }
        if ((__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET) && (hi3c->ControlXferCount > 0U))
        {
          /* Clear frame complete flag */
          LL_I3C_ClearFlag_FC(hi3c->Instance);

          /* Then Initiate a Start condition */
          LL_I3C_RequestTransfer(hi3c->Instance);
        }

        /* Calculate exit_condition value based on Frame complete and error flags */
        exit_condition = (READ_REG(hi3c->Instance->EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
      } while ((exit_condition == 0U) ||
               ((exit_condition == I3C_EVR_FCF) && (hi3c->ControlXferCount > 0U)));


      while((__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_SFNEF) == SET))
      {
        LL_I3C_GetXferDataCount(hi3c->Instance);
      }
      /* Clear frame complete flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET)
      {
        LL_I3C_ClearFlag_FC(hi3c->Instance);
      }
      
      /* Clear target end flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_RXTGTENDF) == SET)
      {
        LL_I3C_ClearFlag_RXTGTEND(hi3c->Instance);
      }
      
      hi3c->ptrRxFunc(hi3c);

      /* Check if all data bytes are received */
      if ((hi3c->RxXferCount != 0U) && (status == HAL_OK))
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_SIZE;
        status = HAL_ERROR;
      }

      /* Check on error flag */
      if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_ERRF) == SET)
      {
        /* Clear error flag */
        LL_I3C_ClearFlag_ERR(hi3c->Instance);

        /* Update handle error code parameter */
        I3C_GetErrorSources(hi3c);

        /* Update returned status value */
        status = HAL_ERROR;
      }

      /* At the end of Rx process update state to Previous state */
      I3C_StateUpdate(hi3c);
    }
  }

  return status;
}

/**
  * @brief  Controller private read in interrupt mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The RxBuf.Size must be equal to the sum of all RxBuf.Size exist in the descriptor.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required reception buffers
  *                            (control buffer, data buffer and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_Receive_IT(I3C_HandleTypeDef   *hi3c,
                                          I3C_XferTypeDef     *pXferData)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL) || (pXferData->RxBuf.pBuffer == NULL))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      if (handle_state == HAL_I3C_STATE_LISTEN)
      {
        hi3c->XferISR     = I3C_Ctrl_Rx_Listen_Event_ISR;
      }
      else
      {
        hi3c->XferISR     = I3C_Ctrl_Rx_ISR;
      }
      hi3c->pXferData     = pXferData;
      hi3c->RxXferCount   = hi3c->pXferData->RxBuf.Size;
      hi3c->State         = HAL_I3C_STATE_BUSY_RX;

      hi3c->ptrRxFunc = &I3C_ReceiveByteTreatment;

      /* Note : The I3C interrupts must be enabled after unlocking current process to avoid the risk
      of I3C interrupt handle execution before current process unlock */

      /* Enable Rx process interrupts */
      I3C_Enable_IRQ(hi3c, I3C_XFER_CONTROLLER_RX_IT);

      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);
    }
  }

  return status;
}

/**
  * @brief  Controller multiple Direct CCC Command, I3C private or I2C transfer in interrupt mode.
  * @note   The function @ref HAL_I3C_AddDescToFrame() must be called before initiate a transfer.
  * @note   The Tx FIFO threshold @ref HAL_I3C_TXFIFO_THRESHOLD_4_4 is not allowed when the transfer descriptor contains
  *         multiple transmission frames.
  * @note   This function must be called to transfer read/write I3C or I2C private data or a direct read/write CCC.
  * @note   The TxBuf.Size must be equal to the sum of all TxBuf.Size exist in the descriptor.
  * @note   The RxBuf.Size must be equal to the sum of all RxBuf.Size exist in the descriptor.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  pXferData  : [IN]  Pointer to an I3C_XferTypeDef structure that contains required transmit and receive
  *                            buffers (control buffer, data buffers and status buffer).
  *                            This value contain transfer data after called @ref HAL_I3C_AddDescToFrame().
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_MultipleTransfer_IT(I3C_HandleTypeDef   *hi3c,
                                                   I3C_XferTypeDef     *pXferData)
{
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* Check on user parameters */
    if ((pXferData == NULL)                                               ||
        ((pXferData->RxBuf.pBuffer == NULL) && (hi3c->RxXferCount != 0U)) ||
        ((pXferData->TxBuf.pBuffer == NULL) && (hi3c->TxXferCount != 0U)))
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Set handle transfer parameters */
      hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
      if (handle_state == HAL_I3C_STATE_LISTEN)
      {
        hi3c->XferISR     = I3C_Ctrl_Multiple_Xfer_Listen_Event_ISR;
      }
      else
      {
        hi3c->XferISR     = I3C_Ctrl_Multiple_Xfer_ISR;
      }
      hi3c->pXferData     = pXferData;
      hi3c->TxXferCount   = hi3c->pXferData->TxBuf.Size;
      hi3c->RxXferCount   = hi3c->pXferData->RxBuf.Size;
      hi3c->State         = HAL_I3C_STATE_BUSY_TX_RX;

      hi3c->ptrTxFunc = &I3C_TransmitByteTreatment;

      hi3c->ptrRxFunc = &I3C_ReceiveByteTreatment;

      /* Note : The I3C interrupts must be enabled after unlocking current process to avoid the risk
      of I3C interrupt handle execution before current process unlock */

      /* Enable Tx and Rx process interrupts */
      I3C_Enable_IRQ(hi3c, (I3C_XFER_CONTROLLER_TX_IT | I3C_XFER_CONTROLLER_RX_IT));

      /* Initiate a Start condition */
      LL_I3C_RequestTransfer(hi3c->Instance);
    }
  }
  return status;
}

/**
  * @brief  Controller assign dynamic address (send a broadcast ENTDAA CCC command) in polling mode.
  * @param  hi3c           : [IN]     Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                   information for the specified I3C.
  * @param  target_payload : [IN/OUT] Pointer to the returned target payload value.
  * @param  dynOption      : [IN]     Parameter indicates the Dynamic address assignment option.
  *                                   It can be one value of @ref I3C_DYNAMIC_ADDRESS_OPTION_DEFINITION.
  * @param  timeout        : [IN]     Timeout duration in millisecond.
  * @retval HAL Status     :          Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_DynAddrAssign(I3C_HandleTypeDef  *hi3c,
                                             uint64_t           *target_payload,
                                             uint32_t            dynOption,
                                             uint32_t            timeout)
{
  uint32_t tickstart;
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on parameters */
  LS_ASSERT(IS_I3C_ENTDAA_OPTION(dynOption));

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    if (target_payload == NULL)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* check on the Mode */
    else if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Launch a RSTDAA procedure before launch ENTDAA */
      if ((dynOption == I3C_RSTDAA_THEN_ENTDAA) &&
          ((handle_state == HAL_I3C_STATE_READY) || (handle_state == HAL_I3C_STATE_LISTEN)))
      {
        /* Set handle transfer parameters */
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;
        hi3c->State     = HAL_I3C_STATE_BUSY_DAA;

        /* Init tickstart for timeout management */
        tickstart = systick_get_value();

        /* Enable arbitration header */
        LL_I3C_EnableArbitrationHeader(hi3c->Instance);

        /* Write CCC information in the control register */
        LL_I3C_ControllerHandleCCC(hi3c->Instance, I3C_BROADCAST_RSTDAA, 0U, LL_I3C_GENERATE_STOP);

        /* Wait Frame completion flag */
        status = I3C_WaitOnFlagUntilTimeout(hi3c, HAL_I3C_FLAG_FCF, RESET, timeout, tickstart);

        /* Clear frame complete flag */
        if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET)
        {
          LL_I3C_ClearFlag_FC(hi3c->Instance);
        }

        /* Check on error flag */
        if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_ERRF) == SET)
        {
          /* Clear error flag */
          LL_I3C_ClearFlag_ERR(hi3c->Instance);

          /* Update handle error code parameter */
          I3C_GetErrorSources(hi3c);

          status = HAL_ERROR;
        }

        /* Update handle state parameter */
        I3C_StateUpdate(hi3c);
      }

      if (status == HAL_OK)
      {
        /* check on the State */
        if ((handle_state == HAL_I3C_STATE_READY) || (handle_state == HAL_I3C_STATE_LISTEN) ||
            (handle_state == HAL_I3C_STATE_BUSY_DAA))
        {
          /* Check on the state */
          if (handle_state != HAL_I3C_STATE_BUSY_DAA)
          {
            /* Set handle transfer parameters */
            hi3c->ErrorCode = HAL_I3C_ERROR_NONE;
            hi3c->State     = HAL_I3C_STATE_BUSY_DAA;

            /* Init tickstart for timeout management */
            tickstart = systick_get_value();

            /* Enable arbitration header */
            LL_I3C_EnableArbitrationHeader(hi3c->Instance);

            /* Write CCC information in the control register */
            LL_I3C_ControllerHandleCCC(hi3c->Instance, I3C_BROADCAST_ENTDAA, 0U, LL_I3C_GENERATE_STOP);
          }
          else
          {
            /* Init tickstart for timeout management */
            tickstart = systick_get_value();
          }

          /* Wait frame complete flag or TX FIFO not full flag until timeout */
          status = I3C_WaitOnDAAUntilTimeout(hi3c, timeout, tickstart);

          /* Check TX FIFO not full flag */
          if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_TXFNFF) == SET)
          {
            /* Check on the Rx FIFO threshold to know the Rx treatment process : byte */
              /* For loop to get target payload */
              for (uint32_t index = 0U; index < 8U; index++)
              {
                /* Retrieve payload byte by byte */
                *target_payload |= (uint64_t)((uint64_t)LL_I3C_ReceiveData8(hi3c->Instance) << (index * 8U));
              }
            status = HAL_BUSY;
          }
          /* Check on frame complete flag */
          else
          {
            /* Clear frame complete flag */
            if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET)
            {
              /* Clear frame complete flag */
              LL_I3C_ClearFlag_FC(hi3c->Instance);
            }
            /* Update handle state parameter */
            I3C_StateUpdate(hi3c);
          }
        }
        else
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
          status = HAL_ERROR;
        }
      }
    }
  }

  return status;
}

/**
  * @brief  Controller assign dynamic address (send a broadcast ENTDAA CCC command) in interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  dynOption  : [IN]  Parameter indicates the Dynamic address assignment option.
  *                            It can be one value of @ref I3C_DYNAMIC_ADDRESS_OPTION_DEFINITION.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_DynAddrAssign_IT(I3C_HandleTypeDef *hi3c, uint32_t dynOption)
{
  uint32_t tickstart;
  uint32_t timeout = SYSTICK_MS2TICKS(100); 
  HAL_I3C_StateTypeDef handle_state;
  HAL_StatusTypeDef status = HAL_OK;

  /* check on parameters */
  LS_ASSERT(IS_I3C_ENTDAA_OPTION(dynOption));

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* check on the Mode */
    if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      /* Launch a RSTDAA procedure before launch ENTDAA */
      if ((dynOption == I3C_RSTDAA_THEN_ENTDAA) &&
          ((handle_state == HAL_I3C_STATE_READY) || (handle_state == HAL_I3C_STATE_LISTEN)))
      {
        /* Set handle transfer parameters */
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;
        hi3c->State     = HAL_I3C_STATE_BUSY_DAA;

        /* Init tickstart for timeout management */
        tickstart = systick_get_value();

        /* Enable arbitration header */
        LL_I3C_EnableArbitrationHeader(hi3c->Instance);

        /* Write CCC information in the control register */
        LL_I3C_ControllerHandleCCC(hi3c->Instance, I3C_BROADCAST_RSTDAA, 0U, LL_I3C_GENERATE_STOP);

        /* Wait Frame completion flag */
        status = I3C_WaitOnFlagUntilTimeout(hi3c, HAL_I3C_FLAG_FCF, RESET, timeout, tickstart);

        /* Clear frame complete flag */
        if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_FCF) == SET)
        {
          LL_I3C_ClearFlag_FC(hi3c->Instance);
        }

        /* Check on error flag */
        if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_ERRF) == SET)
        {
          /* Clear error flag */
          LL_I3C_ClearFlag_ERR(hi3c->Instance);

          /* Update handle error code parameter */
          I3C_GetErrorSources(hi3c);
          /* Flush all FIFOs */
          /* Flush the content of Tx Fifo */
          LL_I3C_RequestTxFIFOFlush(hi3c->Instance);

          /* Flush the content of Rx Fifo */
          LL_I3C_RequestRxFIFOFlush(hi3c->Instance);

          /* Check on the I3C mode: Control and status FIFOs available only with controller mode */
          if (hi3c->Mode == HAL_I3C_MODE_CONTROLLER)
          {
            /* Flush the content of Control Fifo */
            LL_I3C_RequestControlFIFOFlush(hi3c->Instance);

            /* Flush the content of Status Fifo */
            LL_I3C_RequestStatusFIFOFlush(hi3c->Instance);
          }

          status = HAL_ERROR;
        }

        /* Update handle state parameter */
        I3C_StateUpdate(hi3c);
      }

      if(status == HAL_OK)
      {
        /* Set handle transfer parameters */
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;
        hi3c->PreviousState = hi3c->State;
        hi3c->State     = HAL_I3C_STATE_BUSY_DAA;
        hi3c->XferISR   = I3C_Ctrl_DAA_ISR;

        /* Note : The I3C interrupts must be enabled after unlocking current process to avoid the risk
        of I3C interrupt handle execution before current process unlock */

        /* Enable Dynamic Address Assignment process interrupts */
        I3C_Enable_IRQ(hi3c, I3C_XFER_CONTROLLER_DAA_IT);

        /* Enable arbitration header */
        LL_I3C_EnableArbitrationHeader(hi3c->Instance);

          /* Write ENTDAA CCC information in the control register */
        LL_I3C_ControllerHandleCCC(hi3c->Instance, I3C_BROADCAST_ENTDAA, 0U, LL_I3C_GENERATE_STOP);

      }

    }
  }

  return status;
}

/**
  * @brief  Controller set dynamic address.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  devAddress : [IN]  Value of the dynamic address to be assigned.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_SetDynAddr(I3C_HandleTypeDef *hi3c, uint8_t devAddress)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check if Tx FIFO requests data */
    if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_TXFNFF) == SET)
    {
      /* Write device address in the TDR register */
      LL_I3C_TransmitData8(hi3c->Instance, devAddress);
    }
    else
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

/**
  * @brief  Check if I3C target device is ready for communication.
  * @param  hi3c       : [IN] Pointer to a I3C_HandleTypeDef structure that contains
  *                           the configuration information for the specified I3C.
  * @param  devAddress : [IN] Value of the device dynamic address.
  * @param  trials     : [IN] Number of trials
  * @param  timeout    : [IN] Timeout duration
  * @retval HAL Status :      Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_IsDeviceI3C_Ready(I3C_HandleTypeDef *hi3c,
                                                 uint8_t            devAddress,
                                                 uint32_t           trials,
                                                 uint32_t           timeout)
{
  I3C_DeviceTypeDef device;
  HAL_StatusTypeDef status;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Initiate a device address */
    device.Address = devAddress;

    /* Initiate a message type */
    device.MessageType = LL_I3C_CONTROLLER_MTYPE_PRIVATE;

    /* Check if the device is ready*/
    status = I3C_Ctrl_IsDevice_Ready(hi3c, &device, trials, timeout);
  }

  return status;
}

/**
  * @brief  Check if I2C target device is ready for communication.
  * @param  hi3c       : [IN] Pointer to a I3C_HandleTypeDef structure that contains
  *                           the configuration information for the specified I3C.
  * @param  devAddress : [IN] Value of the device dynamic address.
  * @param  trials     : [IN] Number of trials
  * @param  timeout    : [IN] Timeout duration
  * @retval HAL Status :      Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_IsDeviceI2C_Ready(I3C_HandleTypeDef *hi3c,
                                                 uint8_t            devAddress,
                                                 uint32_t           trials,
                                                 uint32_t           timeout)
{
  I3C_DeviceTypeDef device;
  HAL_StatusTypeDef status;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Initiate a device address */
    device.Address = devAddress;

    /* Initiate a message type */
    device.MessageType = LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C;

    /* Check if the device is ready*/
    status = I3C_Ctrl_IsDevice_Ready(hi3c, &device, trials, timeout);
  }

  return status;
}

/**
  * @brief Controller generates arbitration (message header {S/Sr + 0x7E addr + W}) in polling mode.
  * @param  hi3c       : [IN] Pointer to an I3C_HandleTypeDef structure that contains
  *                           the configuration information for the specified I3C.
  * @param  timeout    : [IN] Timeout duration
  * @retval HAL Status :      Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Ctrl_GenerateArbitration(I3C_HandleTypeDef *hi3c, uint32_t timeout)
{
  HAL_StatusTypeDef status = HAL_OK;
  HAL_I3C_StateTypeDef handle_state;
  __IO uint32_t exit_condition;
  uint32_t tickstart;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the instance and the mode parameters */

    LS_ASSERT(IS_I3C_MODE(hi3c->Mode));

    /* Get I3C handle state */
    handle_state = hi3c->State;

    /* check on the Mode */
    if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    /* check on the State */
    else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
    {
      status = HAL_BUSY;
    }
    else
    {
      hi3c->State = HAL_I3C_STATE_BUSY;

      /* Disable exit pattern */
      LL_I3C_DisableExitPattern(hi3c->Instance);
      /* Disable reset pattern */
      LL_I3C_DisableResetPattern(hi3c->Instance);

      /* Write message control register */
      WRITE_REG(hi3c->Instance->CR, LL_I3C_CONTROLLER_MTYPE_HEADER | LL_I3C_GENERATE_STOP);

      /* Calculate exit_condition value based on Frame complete and error flags */
      exit_condition = (READ_REG(hi3c->Instance->EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));

      tickstart = systick_get_value();

      while (exit_condition == 0U)
      {
        if (timeout != HAL_MAX_DELAY)
        {
          if (((systick_get_value() - tickstart) > timeout) || (timeout == 0U))
          {
            /* Update I3C error code */
            hi3c->ErrorCode |= HAL_I3C_ERROR_TIMEOUT;
            status = HAL_TIMEOUT;

            break;
          }
        }
        /* Calculate exit_condition value based on Frame complete and error flags */
        exit_condition = (READ_REG(hi3c->Instance->EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
      }

      if (status == HAL_OK)
      {
        /* Check if the FCF flag has been set */
        if (__HAL_I3C_GET_FLAG(hi3c, I3C_EVR_FCF) == SET)
        {
          /* Clear frame complete flag */
          LL_I3C_ClearFlag_FC(hi3c->Instance);
        }
        else
        {
          /* Clear error flag */
          LL_I3C_ClearFlag_ERR(hi3c->Instance);

          /* Update handle error code parameter */
          I3C_GetErrorSources(hi3c);

          /* Update returned status value */
          status = HAL_ERROR;
        }
      }

      /* At the end of Rx process update state to Previous state */
      I3C_StateUpdate(hi3c);
    }
  }

  return status;
}

/**
  * @brief  Abort an I3C IT or DMA process communication with Interrupt.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                            information for the specified I3C.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Abort_IT(I3C_HandleTypeDef *hi3c)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    if (hi3c->State != HAL_I3C_STATE_ABORT)
    {
      /* Set State at HAL_I3C_STATE_ABORT */
      hi3c->State     = HAL_I3C_STATE_ABORT;

      /* Disable Error Interrupts */
      __HAL_I3C_DISABLE_IT(hi3c, HAL_I3C_IT_ERRIE);

      hi3c->XferISR   = I3C_Abort_ISR;

      /* Flush the different Fifos to generate an automatic stop mode link to underflow or overflow detection timeout */
      /* Flush the content of Tx Fifo */
      LL_I3C_RequestTxFIFOFlush(hi3c->Instance);

      /* Flush the content of Rx Fifo */
      LL_I3C_RequestRxFIFOFlush(hi3c->Instance);

      /* Check on the I3C mode: Control and status FIFOs available only with controller mode */
      if (hi3c->Mode == HAL_I3C_MODE_CONTROLLER)
      {
        /* Flush the content of Control Fifo */
        LL_I3C_RequestControlFIFOFlush(hi3c->Instance);

        /* Flush the content of Status Fifo */
        LL_I3C_RequestStatusFIFOFlush(hi3c->Instance);
      }

      /* Disable all DMA Requests */
      // LL_I3C_DisableDMAReq_RX(hi3c->Instance);
      // LL_I3C_DisableDMAReq_TX(hi3c->Instance);

      /* Note : The I3C interrupts must be enabled after unlocking current process
      to avoid the risk of I3C interrupt handle execution before current
      process unlock */
      I3C_Enable_IRQ(hi3c, I3C_XFER_CONTROLLER_RX_CCC_IT);
  }
    else
    {
      return HAL_BUSY;
    }
  }

  return status;
}

/**
  * @brief  Return the I3C handle state.
  * @param  hi3c      : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                           information for the specified I3C.
  * @retval HAL State : [OUT] Value from HAL_I3C_StateTypeDef enumeration.
  */
HAL_I3C_StateTypeDef HAL_I3C_GetState(const I3C_HandleTypeDef *hi3c)
{
  return hi3c->State;
}

/**
  * @brief  Returns the I3C handle mode.
  * @param  hi3c     : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                          information for the specified I3C.
  * @retval HAL Mode : [OUT] Value from HAL_I3C_ModeTypeDef enumeratio  n.
  */
HAL_I3C_ModeTypeDef HAL_I3C_GetMode(const I3C_HandleTypeDef *hi3c)
{
  return hi3c->Mode;
}

/**
  * @brief  Return the I3C error code.
  * @param  hi3c           : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                information for the specified I3C.
  * @retval I3C Error Code : [OUT] Value from @ref I3C_ERROR_CODE_DEFINITION.
  */
uint32_t HAL_I3C_GetError(const I3C_HandleTypeDef *hi3c)
{
  return hi3c->ErrorCode;
}

/**
  * @brief  Target/Controller Get Common Command Code Information updated after event.
  * @param  hi3c     : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                         for the specified I3C.
  * @param  notifyId : [IN] Parameter indicates which notification is signaled.
  *                         It can be a combination of value of @ref HAL_I3C_Notification_ID_definition.
  * @param  pCCCInfo : [IN/OUT] Pointer to an I3C_CCCInfoTypeDef structure that contains the CCC information
  *                             updated after CCC event.
  * @retval HAL Status : Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_GetCCCInfo(I3C_HandleTypeDef *hi3c,
                                     uint32_t notifyId,
                                     I3C_CCCInfoTypeDef *pCCCInfo)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check on user parameters */
    if (pCCCInfo == NULL)
    {
      /* Update handle error code parameter */
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    /* Check the I3C state */
    else if (hi3c->State == HAL_I3C_STATE_RESET)
    {
      /* Update handle error code parameter */
      hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
      status = HAL_ERROR;
    }
    else
    {
      /* Retrieve In Band Interrupt information (controller) */
      if ((notifyId & EVENT_ID_IBI) == EVENT_ID_IBI)
      {
        pCCCInfo->IBICRTgtAddr = LL_I3C_GetIBITargetAddr(hi3c->Instance);
        pCCCInfo->IBITgtNbPayload = LL_I3C_GetNbIBIAddData(hi3c->Instance);
        pCCCInfo->IBITgtPayload = LL_I3C_GetIBIPayload(hi3c->Instance);
      }

      /* Retrieve Controller role request Interrupt information (controller) */
      if ((notifyId & EVENT_ID_CR) == EVENT_ID_CR)
      {
        pCCCInfo->IBICRTgtAddr = LL_I3C_GetIBITargetAddr(hi3c->Instance);
      }
    }
  }

  return status;
}

/**
  * @brief  Get BCR, DCR and PID information after ENTDAA.
  * @param  hi3c     : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                         for the specified I3C.
  * @param  ENTDAA_payload  :[IN] Payload received after ENTDAA
  * @param  pENTDAA_payload :[OUT] Pointer to an I3C_ENTDAAPayloadTypeDef structure that contains the BCR, DCR and PID
  *                          information.
  * @retval HAL Status : Value from HAL_StatusTypeDef enumeration.
  */
HAL_StatusTypeDef HAL_I3C_Get_ENTDAA_Payload_Info(I3C_HandleTypeDef *hi3c,
                                                  uint64_t ENTDAA_payload,
                                                  I3C_ENTDAAPayloadTypeDef *pENTDAA_payload)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t BCR;
  uint64_t PID;

  /* check on the handle */
  if (hi3c == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check on user parameters */
    if (pENTDAA_payload == NULL)
    {
      /* Update handle error code parameter */
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    else
    {
      /* Get Bus Characterics */
      BCR = __HAL_I3C_GET_BCR(ENTDAA_payload);

      /* Retrieve BCR information */
      pENTDAA_payload->BCR.IBIPayload = __HAL_I3C_GET_IBI_PAYLOAD(BCR);
      pENTDAA_payload->BCR.IBIRequestCapable = __HAL_I3C_GET_IBI_CAPABLE(BCR);
      pENTDAA_payload->BCR.DeviceRole = __HAL_I3C_GET_CR_CAPABLE(BCR);
      pENTDAA_payload->BCR.AdvancedCapabilities = I3C_GET_ADVANCED_CAPABLE(BCR);
      pENTDAA_payload->BCR.OfflineCapable = I3C_GET_OFFLINE_CAPABLE(BCR);
      pENTDAA_payload->BCR.VirtualTargetSupport = I3C_GET_VIRTUAL_TGT(BCR);
      pENTDAA_payload->BCR.MaxDataSpeedLimitation = I3C_GET_MAX_DATA_SPEED_LIMIT(BCR);

      /* Get Device Characterics */
      pENTDAA_payload->DCR = I3C_GET_DCR(ENTDAA_payload);

      /* Get Provisioned ID */
      PID = I3C_GET_PID(ENTDAA_payload);

      /* Change PID from BigEndian to litlleEndian */
      PID = (uint64_t)((((uint64_t)I3C_BIG_TO_LITTLE_ENDIAN((uint32_t) PID) << 32)   |
                        ((uint64_t)I3C_BIG_TO_LITTLE_ENDIAN((uint32_t)(PID >> 32)))) >> 16);

      /* Retrieve PID information*/
      pENTDAA_payload->PID.MIPIMID = I3C_GET_MIPIMID(PID);
      pENTDAA_payload->PID.IDTSEL = I3C_GET_IDTSEL(PID);
      pENTDAA_payload->PID.PartID = I3C_GET_PART_ID(PID);
      pENTDAA_payload->PID.MIPIID = I3C_GET_MIPIID(PID);
    }
  }

  return status;
}

/**
  * @brief  Interrupt Sub-Routine which handles Controller received events.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* I3C controller receive IBI event management ---------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_IBIF) != RESET)
  {
    /* Clear IBI request flag */
    LL_I3C_ClearFlag_IBI(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_IBI);
#else
    /* Asynchronous IBI event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_IBI);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* I3C controller controller-role request event management ---------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CRF) != RESET)
  {
    /* Clear controller-role request flag */
    LL_I3C_ClearFlag_CR(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_CR);
#else
    /* Asynchronous controller-role event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_CR);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* I3C controller hot-join event management ------------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_HJF) != RESET)
  {
    /* Clear hot-join flag */
    LL_I3C_ClearFlag_HJ(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_HJ);
#else
    /* Asynchronous hot-join event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_HJ);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* Update handle state parameter */
  I3C_StateUpdate(hi3c);

  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles controller transmission in interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Tx_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* Check that a Tx process is ongoing */
  if (hi3c->State == HAL_I3C_STATE_BUSY_TX)
  {
    /* Check if Control FIFO requests data */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CFNFF) != RESET)
    {
      if (hi3c->ControlXferCount > 0U)
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);
      }
    }

    /* I3C Tx FIFO not full interrupt Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_TXFNFF) != RESET)
    {
      if (hi3c->TxXferCount > 0U)
      {
        /* Call Transmit treatment function */
        hi3c->ptrTxFunc(hi3c);
      }
    }

    /* I3C target frame complete event Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_FCF) != RESET)
    {
      /* Clear frame complete flag */
      LL_I3C_ClearFlag_FC(hi3c->Instance);

      if (hi3c->ControlXferCount == 0U)
      {
        /* Disable Tx process interrupts */
        I3C_Disable_IRQ(hi3c, I3C_XFER_CONTROLLER_TX_IT);

        /* Update handle state parameter */
        I3C_StateUpdate(hi3c);

        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

        /* Call the transmit complete callback to inform upper layer of End of Transfer */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
        hi3c->CtrlTxCpltCallback(hi3c);
#else
        HAL_I3C_CtrlTxCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
      }
      else
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

        /* Call the transmit complete callback */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
        hi3c->CtrlTxCpltCallback(hi3c);
#else
        HAL_I3C_CtrlTxCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */

        /* Then Initiate a Start condition */
        LL_I3C_RequestTransfer(hi3c->Instance);

      }
    }
  }
  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles controller reception in interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Rx_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* Check that an Rx process is ongoing */
  if (hi3c->State == HAL_I3C_STATE_BUSY_RX)
  {
    /* Check if Control FIFO requests data */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CFNFF) != RESET)
    {
      if (hi3c->ControlXferCount > 0U)
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);
      }
    }

    /* I3C Rx FIFO not empty interrupt Check */
    if (I3C_CHECK_FLAG(itMasks, HAL_I3C_FLAG_RXFNEF) != RESET)
    {
      if (hi3c->RxXferCount > 0U)
      {
        /* Call receive treatment function */
        hi3c->ptrRxFunc(hi3c);
      }
    }

    /* I3C Tx FIFO not full interrupt Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_TXFNFF) != RESET)
    {
      if (hi3c->TxXferCount > 0U)
      {
        /* Call Transmit treatment function */
        hi3c->ptrTxFunc(hi3c);
      }
    }

    /* I3C target frame complete event Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_FCF) != RESET)
    {
      /* Clear frame complete flag */
      LL_I3C_ClearFlag_FC(hi3c->Instance);

      if (hi3c->ControlXferCount == 0U)
      {
        /* Disable Rx process interrupts */
        I3C_Disable_IRQ(hi3c, I3C_XFER_CONTROLLER_RX_CCC_IT);

        /* Update handle state parameter */
        I3C_StateUpdate(hi3c);

        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

        /* Call the receive complete callback */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
        hi3c->CtrlRxCpltCallback(hi3c);
#else
        HAL_I3C_CtrlRxCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
      }
      else
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

        /* Call the receive complete callback */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
        hi3c->CtrlRxCpltCallback(hi3c);
#else
        HAL_I3C_CtrlRxCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */

        /* Then Initiate a Start condition */
        LL_I3C_RequestTransfer(hi3c->Instance);
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles controller multiple transmission/reception in interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Multiple_Xfer_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* Check that a Tx/Rx process is ongoing */
  if (hi3c->State == HAL_I3C_STATE_BUSY_TX_RX)
  {
    /* Check if Control FIFO requests data */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CFNFF) != RESET)
    {
      if (hi3c->ControlXferCount > 0U)
      {
        /* Call control data treatment function */
        I3C_ControlDataTreatment(hi3c);
      }
    }

    /* I3C Tx FIFO not full interrupt Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_TXFNFF) != RESET)
    {
      if (hi3c->TxXferCount > 0U)
      {
        /* Call Transmit treatment function */
        hi3c->ptrTxFunc(hi3c);
      }
    }

    /* I3C Rx FIFO not empty interrupt Check */
    if (I3C_CHECK_FLAG(itMasks, HAL_I3C_FLAG_RXFNEF) != RESET)
    {
      if (hi3c->RxXferCount > 0U)
      {
        /* Call receive treatment function */
        hi3c->ptrRxFunc(hi3c);
      }
    }

    /* I3C target frame complete event Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_FCF) != RESET)
    {
      /* Clear frame complete flag */
      LL_I3C_ClearFlag_FC(hi3c->Instance);

      if (hi3c->ControlXferCount == 0U)
      {
        /* Disable Tx process interrupts */
        I3C_Disable_IRQ(hi3c, I3C_XFER_CONTROLLER_TX_IT);

        /* Disable Rx process interrupts */
        I3C_Disable_IRQ(hi3c, I3C_XFER_CONTROLLER_RX_CCC_IT);

        /* Update handle state parameter */
        I3C_StateUpdate(hi3c);

        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

        /* Call the transmit, receive complete callback to inform upper layer of End of Transfer */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
        hi3c->CtrlMultipleXferCpltCallback(hi3c);
#else
        HAL_I3C_CtrlMultipleXferCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
      }
      else
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

        /* Then Initiate a Start condition */
        LL_I3C_RequestTransfer(hi3c->Instance);
      }
    }
  }
  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles controller transmission and Controller received events
  *         in interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Tx_Listen_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* I3C controller receive IBI event management ---------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_IBIF) != RESET)
  {
    /* Clear IBI request flag */
    LL_I3C_ClearFlag_IBI(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_IBI);
#else
    /* Asynchronous IBI event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_IBI);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* I3C controller controller-role request event management ---------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CRF) != RESET)
  {
    /* Clear controller-role request flag */
    LL_I3C_ClearFlag_CR(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_CR);
#else
    /* Asynchronous controller-role event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_CR);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* I3C controller hot-join event management ------------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_HJF) != RESET)
  {
    /* Clear hot-join flag */
    LL_I3C_ClearFlag_HJ(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_HJ);
#else
    /* Asynchronous hot-join event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_HJ);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* ISR controller transmission */
  return (I3C_Ctrl_Tx_ISR(hi3c, itMasks));
}

/**
  * @brief  Interrupt Sub-Routine which handles controller reception and Controller received events in interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Rx_Listen_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* I3C controller receive IBI event management ---------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_IBIF) != RESET)
  {
    /* Clear IBI request flag */
    LL_I3C_ClearFlag_IBI(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_IBI);
#else
    /* Asynchronous IBI event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_IBI);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* I3C controller controller-role request event management ---------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CRF) != RESET)
  {
    /* Clear controller-role request flag */
    LL_I3C_ClearFlag_CR(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_CR);
#else
    /* Asynchronous controller-role event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_CR);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* I3C controller hot-join event management ------------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_HJF) != RESET)
  {
    /* Clear hot-join flag */
    LL_I3C_ClearFlag_HJ(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_HJ);
#else
    /* Asynchronous hot-join event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_HJ);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* ISR controller reception */
  return (I3C_Ctrl_Rx_ISR(hi3c, itMasks));
}

/**
  * @brief  Interrupt Sub-Routine which handles controller multiple transmission/reception  and
  *         Controller received eventsin interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_Multiple_Xfer_Listen_Event_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* I3C controller receive IBI event management ---------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_IBIF) != RESET)
  {
    /* Clear IBI request flag */
    LL_I3C_ClearFlag_IBI(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_IBI);
#else
    /* Asynchronous IBI event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_IBI);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* I3C controller controller-role request event management ---------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CRF) != RESET)
  {
    /* Clear controller-role request flag */
    LL_I3C_ClearFlag_CR(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_CR);
#else
    /* Asynchronous controller-role event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_CR);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* I3C controller hot-join event management ------------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(itMasks, I3C_EVR_HJF) != RESET)
  {
    /* Clear hot-join flag */
    LL_I3C_ClearFlag_HJ(hi3c->Instance);

#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
    /* Call registered callback */
    hi3c->NotifyCallback(hi3c, EVENT_ID_HJ);
#else
    /* Asynchronous hot-join event Callback */
    HAL_I3C_NotifyCallback(hi3c, EVENT_ID_HJ);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
  }

  /* ISR controller transmission/reception */
  return (I3C_Ctrl_Multiple_Xfer_ISR(hi3c, itMasks));
}
/**
  * @brief  Interrupt Sub-Routine which handles controller CCC Dynamic Address Assignment command in interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_DAA_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  uint64_t target_payload = 0U;

  /* Check that a Dynamic Address Assignment process is ongoing */
  if (hi3c->State == HAL_I3C_STATE_BUSY_DAA)
  {
    /* I3C Control FIFO not full interrupt Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_CFNFF) != RESET)
    {
      /* Write ENTDAA CCC information in the control register */
      LL_I3C_ControllerHandleCCC(hi3c->Instance, I3C_BROADCAST_ENTDAA, 0U, LL_I3C_GENERATE_STOP);
    }

    /* I3C Tx FIFO not full interrupt Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_TXFNFF) != RESET)
    {
      /* Check on the Rx FIFO threshold to know the Dynamic Address Assignment treatment process : byte or word */
      if (LL_I3C_GetRxFIFOThreshold(hi3c->Instance) == LL_I3C_RXFIFO_THRESHOLD_1_4)
      {
        /* For loop to get target payload */
        for (uint32_t index = 0U; index < 8U; index++)
        {
          /* Retrieve payload byte by byte */
          target_payload |= (uint64_t)((uint64_t)LL_I3C_ReceiveData8(hi3c->Instance) << (index * 8U));
        }
      }
      else
      {
        for (uint32_t index = 0U; index < 8U; index++)
        {
          /* Retrieve payload byte by byte */
          target_payload |= (uint64_t)((uint64_t)LL_I3C_ReceiveData8(hi3c->Instance) << (index * 8U));
        }
      }

      /* Call the corresponding callback */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
      hi3c->TgtReqDynamicAddrCallback(hi3c, target_payload);
#else
      HAL_I3C_TgtReqDynamicAddrCallback(hi3c, target_payload);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
    }

    /* I3C frame complete event Check */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_FCF) != RESET)
    {
      /* Clear frame complete flag */
      LL_I3C_ClearFlag_FC(hi3c->Instance);

      /* Disable Dynamic Address Assignment process interrupts */
      I3C_Disable_IRQ(hi3c, I3C_XFER_CONTROLLER_DAA_IT);

      /* Update handle state parameter */
      I3C_StateUpdate(hi3c);

      hi3c->ErrorCode = HAL_I3C_ERROR_NONE;

      /* Call the Dynamic Address Assignment complete callback */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
      hi3c->CtrlDAACpltCallback(hi3c);
#else
      HAL_I3C_CtrlDAACpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS == 1U */
    }
  }
  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles abort process in interrupt mode.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration information
  *                            for the specified I3C.
  * @param  itMasks    : [IN]  Flag Interrupt Masks flags to handle.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Abort_ISR(struct __I3C_HandleTypeDef *hi3c, uint32_t itMasks)
{
  /* Check that an Abort process is ongoing */
  if (hi3c->State == HAL_I3C_STATE_ABORT)
  {
    /* I3C Rx FIFO not empty interrupt Check */
    if (I3C_CHECK_FLAG(itMasks, HAL_I3C_FLAG_RXFNEF) != RESET)
    {
      if (LL_I3C_IsActiveFlag_DOVR(hi3c->Instance) == 1U)
      {
        /* Flush remaining Rx data */
        LL_I3C_RequestRxFIFOFlush(hi3c->Instance);
      }
    }

    /* I3C Abort frame complete event Check */
    /* Evenif abort is called, the Frame completion can arrive if abort is requested at the end of the processus */
    /* Evenif completion occurs, treat this end of processus as abort completion process */
    if (I3C_CHECK_FLAG(itMasks, I3C_EVR_FCF) != RESET)
    {
      /* Clear frame complete flag */
      LL_I3C_ClearFlag_FC(hi3c->Instance);

      /* Call error treatment function */
      I3C_ErrorTreatment(hi3c);
    }
  }
  return HAL_OK;
}

/**
  * @brief  This function handles I3C Communication Timeout.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                            information for the specified I3C.
  * @param  flag       : [IN]  Specifies the I3C flag to check.
  * @param  flagstatus : [IN]  The new Flag status (SET or RESET).
  * @param  timeout    : [IN]  Timeout duration in millisecond.
  * @param  tickstart  : [IN]  Tick start value
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_WaitOnFlagUntilTimeout(I3C_HandleTypeDef *hi3c, uint32_t flag, FlagStatus flagstatus,
                                                    uint32_t timeout, uint32_t tickstart)
{
  HAL_StatusTypeDef status = HAL_OK;

  while ((__HAL_I3C_GET_FLAG(hi3c, flag) == flagstatus) && (status == HAL_OK))
  {
    /* Check for the Timeout */
    if (timeout != HAL_MAX_DELAY)
    {
      if (((systick_get_value() - tickstart) > timeout) || (timeout == 0U))
      {
        if (__HAL_I3C_GET_FLAG(hi3c, flag) == flagstatus)
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_TIMEOUT;
          status = HAL_TIMEOUT;
        }
      }
    }

    /* Check if an error occurs during Flag waiting */
    if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_ERRF) == SET)
    {
      /* Clear error flag */
      // LL_I3C_ClearFlag_ERR(hi3c->Instance);

      /* Update handle error code parameter */
      I3C_GetErrorSources(hi3c);

      status = HAL_ERROR;
    }
  }
  return status;
}

/**
  * @brief  This function handles I3C Dynamic Address Assignment timeout.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                            information for the specified I3C.
  * @param  timeout    : [IN]  Timeout duration in millisecond.
  * @param  tickstart  : [IN]  Tick start value
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_WaitOnDAAUntilTimeout(I3C_HandleTypeDef *hi3c, uint32_t timeout, uint32_t tickstart)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t active_flags = READ_REG(hi3c->Instance->EVR);

  while (((active_flags & (HAL_I3C_FLAG_FCF | HAL_I3C_FLAG_TXFNFF)) == 0U) && (status == HAL_OK))
  {
    /* Check for the Timeout */
    if (timeout != HAL_MAX_DELAY)
    {
      if (((systick_get_value() - tickstart) > timeout) || (timeout == 0U))
      {
        if ((active_flags & (HAL_I3C_FLAG_FCF | HAL_I3C_FLAG_TXFNFF)) == 0U)
        {
          hi3c->ErrorCode |= HAL_I3C_ERROR_TIMEOUT;
          status = HAL_TIMEOUT;
        }
      }
    }

    /* Check if an error occurs during Flag waiting */
    if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_ERRF) == SET)
    {
      /* Clear error flag */
      LL_I3C_ClearFlag_ERR(hi3c->Instance);

      /* Update handle error code parameter */
      I3C_GetErrorSources(hi3c);

      status = HAL_ERROR;
    }

    /* Read active flags from EVR register */
    active_flags = READ_REG(hi3c->Instance->EVR);
  }
  return status;
}

/**
  * @brief  I3C transmit by byte.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                     information for the specified I3C.
  * @retval None
  */
static void I3C_TransmitByteTreatment(I3C_HandleTypeDef *hi3c)
{
  /* Check TX FIFO not full flag */
  while ( (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_TXFNFF) == SET) &&(hi3c->TxXferCount > 0U))//
  {
    /* Write Tx buffer data to transmit register */
    LL_I3C_TransmitData8(hi3c->Instance, *hi3c->pXferData->TxBuf.pBuffer);
    /* Increment Buffer pointer */
    hi3c->pXferData->TxBuf.pBuffer++;

    /* Decrement remaining bytes counter */
    hi3c->TxXferCount--;
  }
}

/**
  * @brief  I3C receive by byte.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                     information for the specified I3C.
  * @retval None
  */
static void I3C_ReceiveByteTreatment(I3C_HandleTypeDef *hi3c)
{
  /* Check RX FIFO not empty flag */
  while (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_RXFNEF) == SET)
  {
    /* Store received bytes in the Rx buffer */
    *hi3c->pXferData->RxBuf.pBuffer = LL_I3C_ReceiveData8(hi3c->Instance);

    /* Increment Buffer pointer */
    hi3c->pXferData->RxBuf.pBuffer++;

    /* Decrement remaining bytes counter */
    hi3c->RxXferCount--;
  }
}

/**
  * @brief  I3C Control data treatment.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                     information for the specified I3C.
  * @retval None
  */
void I3C_ControlDataTreatment(I3C_HandleTypeDef *hi3c)
{
  /* Check if Control FIFO requests data */
  if (__HAL_I3C_GET_FLAG(hi3c, HAL_I3C_FLAG_CFNFF) == SET)
  {
    /* Decrement remaining control buffer data counter */
    hi3c->ControlXferCount--;

    /* Write Control buffer data to control register */
    WRITE_REG(hi3c->Instance->CR, *hi3c->pXferData->CtrlBuf.pBuffer);

    /* Increment Buffer pointer */
    hi3c->pXferData->CtrlBuf.pBuffer++;
  }
}

/**
  * @brief  I3C state update.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                     information for the specified I3C.
  * @retval None
  */
void I3C_StateUpdate(I3C_HandleTypeDef *hi3c)
{
  /* Check on previous state */
  if (hi3c->PreviousState == HAL_I3C_STATE_LISTEN)
  {
    /* Set state to listen */
    hi3c->State = HAL_I3C_STATE_LISTEN;

    /* Store the controller event treatment function */
    hi3c->XferISR = I3C_Ctrl_Event_ISR;
  }
  else
  {
    /* Set state to ready */
    hi3c->State = HAL_I3C_STATE_READY;

    /* Reset XferISR */
    hi3c->XferISR = NULL;
  }
}

/**
  * @brief  I3C get error source.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                     information for the specified I3C.
  * @retval None
  */
void I3C_GetErrorSources(I3C_HandleTypeDef *hi3c)
{
  /* Check on the I3C mode */
  switch (hi3c->Mode)
  {
    case HAL_I3C_MODE_CONTROLLER:
    {
      /* I3C data error during controller-role hand-off procedure */
      if (LL_I3C_IsActiveFlag_DERR(hi3c->Instance) == 1U)
      {
        hi3c->ErrorCode |= HAL_I3C_ERROR_DATA_HAND_OFF;
      }

      /* I3C data not acknowledged error */
      if (LL_I3C_IsActiveFlag_DNACK(hi3c->Instance) == 1U)
      {
        hi3c->ErrorCode |= HAL_I3C_ERROR_DATA_NACK;
      }

      /* I3C address not acknowledged error */
      if (LL_I3C_IsActiveFlag_ANACK(hi3c->Instance) == 1U)
      {
        hi3c->ErrorCode |= HAL_I3C_ERROR_ADDRESS_NACK;
      }

      /* I3C Status FIFO Over-Run or Control FIFO Under-Run error */
      if (LL_I3C_IsActiveFlag_COVR(hi3c->Instance) == 1U)
      {
        hi3c->ErrorCode |= HAL_I3C_ERROR_COVR;
      }

      break;
    }

    case HAL_I3C_MODE_TARGET:
    {

      break;
    }

    default:
    {
      break;
    }
  }

  /* I3C Rx FIFO Over-Run or Tx FIFO Under-Run error */
  if (LL_I3C_IsActiveFlag_DOVR(hi3c->Instance) == 1U)
  {
    hi3c->ErrorCode |= HAL_I3C_ERROR_DOVR;
  }

  /* I3C Protocol error */
  if (LL_I3C_IsActiveFlag_PERR(hi3c->Instance) == 1U)
  {
    hi3c->ErrorCode |= (I3C_SER_PERR | LL_I3C_GetMessageErrorCode(hi3c->Instance));
  }
}

/**
  * @brief  I3C transfer prior preparation.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                            information for the specified I3C.
  * @param  counter    : [IN]  Number of devices or commands to treat.
  * @param  option     : [IN]  Parameter indicates the transfer option.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Xfer_PriorPreparation(I3C_HandleTypeDef *hi3c, uint8_t counter, uint32_t option)
{
  HAL_StatusTypeDef status  = HAL_OK;
  uint32_t current_tx_index = 0U;
  uint32_t global_tx_size   = 0U;
  uint32_t global_rx_size   = 0U;
  uint32_t nb_tx_frame      = 0U;
  uint32_t direction;

  for (uint32_t descr_index = 0U; descr_index < counter; descr_index++)
  {
    /* Direct CCC command */
    if ((option & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT)
    {
      /* Update direction of frame */
      direction = hi3c->pCCCDesc[descr_index].Direction;

      /* Direction read with Define byte */
      if (((option & I3C_DEFINE_BYTE_MASK) != 0U) && (direction == HAL_I3C_DIRECTION_READ))
      {
        nb_tx_frame += 1U;

        global_tx_size += 1U;

        global_rx_size += hi3c->pCCCDesc[descr_index].CCCBuf.Size - 1U;

        /* Check on the global size and on the Tx buffer pointer */
        if ((global_tx_size > hi3c->pXferData->TxBuf.Size)    || \
            (current_tx_index > hi3c->pXferData->TxBuf.Size)  || \
            (hi3c->pXferData->TxBuf.pBuffer == NULL))
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;

          status = HAL_ERROR;
        }
        else
        {
          /* Fill global Tx buffer with data and update the current index of the Tx buffer */
          current_tx_index = I3C_FillTxBuffer_CCC(hi3c, descr_index, 1U, current_tx_index);
        }
      }
      else if (direction == HAL_I3C_DIRECTION_WRITE)
      {
        nb_tx_frame += 1U;

        global_tx_size += hi3c->pCCCDesc[descr_index].CCCBuf.Size;

        /* Check on the global size and on the Tx buffer pointer */
        if ((global_tx_size > hi3c->pXferData->TxBuf.Size)    || \
            (current_tx_index > hi3c->pXferData->TxBuf.Size)  || \
            (hi3c->pXferData->TxBuf.pBuffer == NULL))
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;

          status = HAL_ERROR;
        }
        else
        {
          /* Fill global Tx buffer with data and update the current index of the Tx buffer */
          current_tx_index = I3C_FillTxBuffer_CCC(hi3c,
                                                  descr_index,
                                                  hi3c->pCCCDesc[descr_index].CCCBuf.Size,
                                                  current_tx_index);
        }
      }
      /* Direction read without Define byte */
      else
      {
        global_rx_size += hi3c->pCCCDesc[descr_index].CCCBuf.Size;
      }
    }
    /* Broadcast CCC command */
    else if ((option & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_CCC)
    {
      /* Update direction of frame */
      direction = hi3c->pCCCDesc[descr_index].Direction;

      if (direction == HAL_I3C_DIRECTION_WRITE)
      {
        nb_tx_frame += 1U;

        global_tx_size += hi3c->pCCCDesc[descr_index].CCCBuf.Size;

        /* Check on the global size and on the Tx buffer pointer */
        if ((global_tx_size > hi3c->pXferData->TxBuf.Size)    || \
            (current_tx_index > hi3c->pXferData->TxBuf.Size)  || \
            (hi3c->pXferData->TxBuf.pBuffer == NULL))
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;

          status = HAL_ERROR;
        }
        else
        {
          /* Fill global Tx buffer with data and update the current index of the Tx buffer */
          current_tx_index = I3C_FillTxBuffer_CCC(hi3c,
                                                  descr_index,
                                                  hi3c->pCCCDesc[descr_index].CCCBuf.Size,
                                                  current_tx_index);
        }
      }
      else
      {
        status = HAL_ERROR;
      }
    }
    /* Private */
    else
    {
      /* Update direction of frame */
      direction = hi3c->pPrivateDesc[descr_index].Direction;

      if (direction == HAL_I3C_DIRECTION_WRITE)
      {
        nb_tx_frame += 1U;

        global_tx_size += hi3c->pPrivateDesc[descr_index].TxBuf.Size;

        /* Check on the global size and on the Tx buffer pointer */
        if ((global_tx_size > hi3c->pXferData->TxBuf.Size)    || \
            (current_tx_index > hi3c->pXferData->TxBuf.Size)  || \
            (hi3c->pXferData->TxBuf.pBuffer == NULL))
        {
          hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;

          status = HAL_ERROR;
        }
        else
        {
          /* Fill global Tx buffer with data and update the current index of the Tx buffer */
          current_tx_index = I3C_FillTxBuffer_Private(hi3c,
                                                      descr_index,
                                                      hi3c->pPrivateDesc[descr_index].TxBuf.Size,
                                                      current_tx_index);
        }
      }
      else
      {
        global_rx_size += hi3c->pPrivateDesc[descr_index].RxBuf.Size;
      }
    }

    /* Check if there is an error in the Tx Buffer*/
    if (status == HAL_ERROR)
    {
      break;
    }
  }

  if (status == HAL_OK)
  {
    /* Check on the size Rx buffer */
    if (global_rx_size > hi3c->pXferData->RxBuf.Size)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
      status = HAL_ERROR;
    }
    else
    {
      hi3c->RxXferCount = global_rx_size;
    }

    /* Set handle transfer parameters */
    hi3c->TxXferCount = global_tx_size;
  }

  return status;
}

/**
  * @brief  I3C fill Tx Buffer with data from CCC Descriptor.
  * @param  hi3c           : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                information for the specified I3C.
  * @param  indexDesc      : [IN]  Index of descriptor.
  * @param  txSize         : [IN]  Size of Tx data.
  * @param  txCurrentIndex : [IN]  Current Index of TxBuffer.
  * @retval index_tx       : [OUT] New current Index of TxBuffer.
  */
static uint32_t I3C_FillTxBuffer_CCC(I3C_HandleTypeDef *hi3c,
                                     uint32_t           indexDesc,
                                     uint32_t           txSize,
                                     uint32_t           txCurrentIndex)
{
  uint32_t index_tx = txCurrentIndex;

  for (uint32_t index = 0U; index < txSize; index++)
  {
    hi3c->pXferData->TxBuf.pBuffer[index_tx] = hi3c->pCCCDesc[indexDesc].CCCBuf.pBuffer[index];

    index_tx++;
  }

  return index_tx;
}

/**
  * @brief  I3C fill Tx Buffer with data from Private Descriptor.
  * @param  hi3c           : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                information for the specified I3C.
  * @param  indexDesc      : [IN]  Index of descriptor.
  * @param  txSize         : [IN]  Size of Tx data.
  * @param  txCurrentIndex : [IN]  Current Index of TxBuffer.
  * @retval index_tx       : [OUT] New current Index of TxBuffer.
  */
static uint32_t I3C_FillTxBuffer_Private(I3C_HandleTypeDef *hi3c,
                                         uint32_t           indexDesc,
                                         uint32_t           txSize,
                                         uint32_t           txCurrentIndex)
{
  uint32_t index_tx = txCurrentIndex;

  for (uint32_t index = 0U; index < txSize; index++)
  {
    hi3c->pXferData->TxBuf.pBuffer[index_tx] = hi3c->pPrivateDesc[indexDesc].TxBuf.pBuffer[index];

    index_tx++;
  }

  return index_tx;
}

/**
  * @brief  I3C Control buffer prior preparation.
  * @param  hi3c       : [IN]  Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                            information for the specified I3C.
  * @param  counter    : [IN]  Number of devices or commands to treat.
  * @param  option     : [IN]  Parameter indicates the transfer option.
  * @retval HAL Status :       Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_ControlBuffer_PriorPreparation(I3C_HandleTypeDef *hi3c,
                                                            uint8_t            counter,
                                                            uint32_t           option)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t nb_define_bytes;
  uint32_t stop_condition;
  uint32_t nb_data_bytes;
  uint32_t index;

  /* Check on the control buffer pointer */
  if (hi3c->pXferData->CtrlBuf.pBuffer == NULL)
  {
    hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
    status = HAL_ERROR;
  }
  else
  {
    /* Extract from option required information */
    nb_define_bytes = (option & I3C_DEFINE_BYTE_MASK);
    stop_condition  = (option & I3C_RESTART_STOP_MASK);

    /* Check on the deactivation of the arbitration */
    if ((option & I3C_ARBITRATION_HEADER_MASK) == I3C_ARBITRATION_HEADER_MASK)
    {
      /* Disable arbitration header */
      LL_I3C_DisableArbitrationHeader(hi3c->Instance);
    }
    else
    {
      /* Enable arbitration header */
      LL_I3C_EnableArbitrationHeader(hi3c->Instance);
    }

    /* Check on the operation type */
    if ((option & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_CCC)
    {
      /*------------------------------------------ Broadcast CCC -----------------------------------------------------*/
      /* Check on the control buffer size */
      if (hi3c->pXferData->CtrlBuf.Size < (uint32_t)counter)
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
        status = HAL_ERROR;
      }
      else
      {
        /* Set remaining control buffer data counter */
        hi3c->ControlXferCount = (uint32_t)counter;

        /* For loop on the number of commands */
        for (index = 0U; index < ((uint32_t)counter - 1U); index++)
        {
          /* Update control buffer value */
          hi3c->pXferData->CtrlBuf.pBuffer[index] = ((uint32_t)hi3c->pCCCDesc[index].CCCBuf.Size              |
                                                     ((uint32_t)hi3c->pCCCDesc[index].CCC  << I3C_CR_CCC_POS) |
                                                     LL_I3C_CONTROLLER_MTYPE_CCC | stop_condition);
        }

        /* At the last device we should generate a stop condition */
        hi3c->pXferData->CtrlBuf.pBuffer[index] = ((uint32_t)hi3c->pCCCDesc[index].CCCBuf.Size              |
                                                   ((uint32_t)hi3c->pCCCDesc[index].CCC  << I3C_CR_CCC_POS) |
                                                   LL_I3C_CONTROLLER_MTYPE_CCC | LL_I3C_GENERATE_STOP);
      }
    }
    else if ((option & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT)
    {
      /*------------------------------------------ Direct CCC --------------------------------------------------------*/
      /* Check on the control buffer size */
      if (hi3c->pXferData->CtrlBuf.Size < ((uint32_t)counter * 2U))
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
        status = HAL_ERROR;
      }
      else
      {
        /* Set remaining control buffer data counter */
        hi3c->ControlXferCount = ((uint32_t)counter * 2U);

        /* For loop on the number of (devices or commands) * 2 */
        for (index = 0U; index < (((uint32_t)counter * 2U) - 2U); index += 2U)
        {
          /* Step 1 : update control buffer value for the CCC command */
          hi3c->pXferData->CtrlBuf.pBuffer[index] = (nb_define_bytes                                               |
                                                     ((uint32_t)hi3c->pCCCDesc[index / 2U].CCC  << I3C_CR_CCC_POS) |
                                                     LL_I3C_CONTROLLER_MTYPE_CCC | LL_I3C_GENERATE_RESTART);

          /* Step 2 : update control buffer value for target address */
          hi3c->pXferData->CtrlBuf.pBuffer[index + 1U] =
            (((uint32_t)hi3c->pCCCDesc[index / 2U].CCCBuf.Size - nb_define_bytes) |
             hi3c->pCCCDesc[index / 2U].Direction                                            |
             ((uint32_t)hi3c->pCCCDesc[index / 2U].TargetAddr << I3C_CR_ADD_POS)  |
             LL_I3C_CONTROLLER_MTYPE_DIRECT | stop_condition);
        }

        /* Update control buffer value for the last CCC command */
        hi3c->pXferData->CtrlBuf.pBuffer[index] = (nb_define_bytes                                               |
                                                   ((uint32_t)hi3c->pCCCDesc[index / 2U].CCC  << I3C_CR_CCC_POS) |
                                                   LL_I3C_CONTROLLER_MTYPE_CCC | LL_I3C_GENERATE_RESTART);

        /* At the last device we should generate a stop condition */
        hi3c->pXferData->CtrlBuf.pBuffer[index + 1U] =
          (((uint32_t)hi3c->pCCCDesc[index / 2U].CCCBuf.Size - nb_define_bytes) |
           hi3c->pCCCDesc[index / 2U].Direction                                            |
           ((uint32_t)hi3c->pCCCDesc[index / 2U].TargetAddr << I3C_CR_ADD_POS)  |
           LL_I3C_CONTROLLER_MTYPE_DIRECT | LL_I3C_GENERATE_STOP);
      }
    }
    else
    {
      /*------------------------------------------ Private I3C/I2C ---------------------------------------------------*/
      /* Check on the control buffer size */
      if (hi3c->pXferData->CtrlBuf.Size < (uint32_t)counter)
      {
        hi3c->ErrorCode = HAL_I3C_ERROR_INVALID_PARAM;
        status = HAL_ERROR;
      }
      else
      {
        /* Set remaining control buffer data counter */
        hi3c->ControlXferCount = (uint32_t)counter;

        /* For loop on the number of devices */
        for (index = 0U; index < ((uint32_t)counter - 1U); index++)
        {
          /* Check on transfer direction */
          if (hi3c->pPrivateDesc[index].Direction == HAL_I3C_DIRECTION_READ)
          {
            nb_data_bytes = hi3c->pPrivateDesc[index].RxBuf.Size;
          }
          else
          {
            nb_data_bytes = hi3c->pPrivateDesc[index].TxBuf.Size;
          }

          /* Update control buffer value */
          hi3c->pXferData->CtrlBuf.pBuffer[index] =
            (nb_data_bytes | hi3c->pPrivateDesc[index].Direction                |
             ((uint32_t)hi3c->pPrivateDesc[index].TargetAddr << I3C_CR_ADD_POS) |
             (option & I3C_OPERATION_TYPE_MASK) | stop_condition);
        }

        /* Check on transfer direction */
        if (hi3c->pPrivateDesc[index].Direction == HAL_I3C_DIRECTION_READ)
        {
          nb_data_bytes = hi3c->pPrivateDesc[index].RxBuf.Size;
        }
        else
        {
          nb_data_bytes = hi3c->pPrivateDesc[index].TxBuf.Size;
        }

        /* At the last device we should generate a stop condition */
        hi3c->pXferData->CtrlBuf.pBuffer[index] =
          (nb_data_bytes | hi3c->pPrivateDesc[index].Direction                |
           ((uint32_t)hi3c->pPrivateDesc[index].TargetAddr << I3C_CR_ADD_POS) |
           (option & I3C_OPERATION_TYPE_MASK) | LL_I3C_GENERATE_STOP);
      }
    }
  }

  return status;
}

/**
  * @brief  Check if target device is ready for communication.
  * @param  hi3c    : Pointer to a I3C_HandleTypeDef structure that contains
  *         the configuration information for the specified I3C.
  * @param  pDevice : [IN] Structure to define the device address and the device type.
  * @param  trials  : [IN] Number of trials
  * @param  timeout : [IN] Timeout duration
  * @retval HAL Status :   Value from HAL_StatusTypeDef enumeration.
  */
static HAL_StatusTypeDef I3C_Ctrl_IsDevice_Ready(I3C_HandleTypeDef *hi3c,
                                                 const I3C_DeviceTypeDef *pDevice,
                                                 uint32_t           trials,
                                                 uint32_t           timeout)
{
  __IO uint32_t I3C_Trials = 0UL;
  __IO uint32_t exit_condition;
  uint32_t CR_tmp;
  uint32_t tickstart;
  HAL_StatusTypeDef status = HAL_OK;
  HAL_I3C_StateTypeDef handle_state;
  uint32_t arbitration_previous_state;

  /* Get I3C handle state */
  handle_state = hi3c->State;

  /* check on the Mode */
  if (hi3c->Mode != HAL_I3C_MODE_CONTROLLER)
  {
    hi3c->ErrorCode = HAL_I3C_ERROR_NOT_ALLOWED;
    status = HAL_ERROR;
  }
  /* check on the State */
  else if ((handle_state != HAL_I3C_STATE_READY) && (handle_state != HAL_I3C_STATE_LISTEN))
  {
    status = HAL_BUSY;
  }
  else
  {
    /* Set handle transfer parameters */
    hi3c->ErrorCode     = HAL_I3C_ERROR_NONE;
    hi3c->State         = HAL_I3C_STATE_BUSY;

    /* Before modify the arbitration, get the current arbitration state */
    arbitration_previous_state = LL_I3C_IsEnabledArbitrationHeader(hi3c->Instance);

    /* Disable arbitration header */
    LL_I3C_DisableArbitrationHeader(hi3c->Instance);

    CR_tmp = (HAL_I3C_DIRECTION_WRITE                                   |
              ((uint32_t)pDevice->Address << I3C_CR_ADD_POS)      |
              pDevice->MessageType | LL_I3C_GENERATE_STOP);

    do
    {
      /* Initiate a start condition by writing in the CR register */
      WRITE_REG(hi3c->Instance->CR, CR_tmp);

      /* Calculate exit_condition value based on Frame complete and error flags */
      exit_condition = (READ_REG(hi3c->Instance->EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));

      tickstart = systick_get_value();

      while (exit_condition == 0U)
      {
        if (timeout != HAL_MAX_DELAY)
        {
          if (((systick_get_value() - tickstart) > timeout) || (timeout == 0U))
          {
            /* Update I3C error code */
            hi3c->ErrorCode |= HAL_I3C_ERROR_TIMEOUT;
            status = HAL_TIMEOUT;

            break;
          }
        }
        /* Calculate exit_condition value based on Frame complete and error flags */
        exit_condition = (READ_REG(hi3c->Instance->EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
      }

      if (status == HAL_OK)
      {
        /* Check if the FCF flag has been set */
        if (__HAL_I3C_GET_FLAG(hi3c, I3C_EVR_FCF) == SET)
        {
          /* Clear frame complete flag */
          LL_I3C_ClearFlag_FC(hi3c->Instance);

          /* Device is ready */
          break;
        }
        else
        {
          /* Clear ERR flag */
          LL_I3C_ClearFlag_ERR(hi3c->Instance);
        }
      }

      /* Increment Trials */
      I3C_Trials++;

    } while ((I3C_Trials < trials) && (status == HAL_OK));

    /* Device is not ready */
    if (trials == I3C_Trials)
    {
      hi3c->ErrorCode = HAL_I3C_ERROR_ADDRESS_NACK;
      status = HAL_ERROR;
    }

    /* update state to Previous state */
    I3C_StateUpdate(hi3c);

    /* Check if previous arbitration state is enabled */
    if (arbitration_previous_state == 1U)
    {
      LL_I3C_EnableArbitrationHeader(hi3c->Instance);
    }
  }

  return status;
}

/**
  * @brief  Manage the enabling of Interrupts.
  * @param  hi3c             : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                 information for the specified I3C.
  * @param  InterruptRequest : [IN] Value of the interrupt request
  * @retval None
  */
void I3C_Enable_IRQ(I3C_HandleTypeDef *hi3c, uint32_t InterruptRequest)
{
  uint32_t tmpisr = 0U;
  
  /* Check if requested interrupts are related to listening mode */
  if ((InterruptRequest & I3C_XFER_LISTEN_IT) != 0U)
  {
    tmpisr |= ((InterruptRequest & (~I3C_XFER_LISTEN_IT)) | HAL_I3C_IT_ERRIE);
  }

  /* Check if requested interrupts are related to transmit/receive in DMA mode */
  if ((InterruptRequest & I3C_XFER_DMA) != 0U)
  {
    /* Enable frame complete and error interrupts */
    tmpisr |= (HAL_I3C_IT_CFNFIE | HAL_I3C_IT_FCIE | HAL_I3C_IT_ERRIE);
  }

  /* Check if requested interrupts are related to controller transmit in IT mode */
  if ((InterruptRequest & I3C_XFER_CONTROLLER_TX_IT) != 0U)
  {
    /* Enable frame complete, control FIFO not full, transmit FIFO not full and error interrupts */
    tmpisr |= (HAL_I3C_IT_FCIE | HAL_I3C_IT_CFNFIE | HAL_I3C_IT_TXFNFIE | HAL_I3C_IT_ERRIE);
  }

  /* Check if requested interrupts are related to controller receive in IT mode */
  if ((InterruptRequest & I3C_XFER_CONTROLLER_RX_IT) != 0U)
  {
    /* Enable frame complete, control FIFO not full, receive FIFO not empty and error interrupts */
    tmpisr |= (HAL_I3C_IT_FCIE | HAL_I3C_IT_CFNFIE | HAL_I3C_IT_RXFNEIE | HAL_I3C_IT_ERRIE);
  }

  /* Check if requested interrupts are related to controller transmit read or a broadcast CCC in IT mode */
  if ((InterruptRequest & I3C_XFER_CONTROLLER_RX_CCC_IT) != 0U)
  {
    /* Enable frame complete, transmit FIFO not full, control FIFO not full,
       receive FIFO not empty and error interrupts */
    tmpisr |= (HAL_I3C_IT_FCIE | HAL_I3C_IT_TXFNFIE | HAL_I3C_IT_CFNFIE | HAL_I3C_IT_RXFNEIE | HAL_I3C_IT_ERRIE);
  }

  /* Check if requested interrupts are related to controller transmit broadcast ENTDAA CCC in IT mode */
  if ((InterruptRequest & I3C_XFER_CONTROLLER_DAA_IT) != 0U)
  {
    /* Enable frame complete, control FIFO not full, transmit FIFO not full and error interrupts */
    tmpisr |= (HAL_I3C_IT_FCIE | HAL_I3C_IT_CFNFIE | HAL_I3C_IT_TXFNFIE | HAL_I3C_IT_ERRIE);
  }
  /* Enable requested interrupts */
  __HAL_I3C_ENABLE_IT(hi3c, tmpisr);
}

/**
  * @brief  Manage the disabling of Interrupts.
  * @param  hi3c             : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                                 information for the specified I3C.
  * @param  InterruptRequest : [IN] Value of the interrupt request
  * @retval None
  */
void I3C_Disable_IRQ(I3C_HandleTypeDef *hi3c, uint32_t InterruptRequest)
{
  uint32_t tmpisr = 0U;

  /* Check if requested interrupts are related to listening mode */
  if ((InterruptRequest & I3C_XFER_LISTEN_IT) != 0U)
  {
    tmpisr |= ((InterruptRequest & (~I3C_XFER_LISTEN_IT)) | HAL_I3C_IT_ERRIE);
  }

  /* Check if requested interrupts are related to transmit/receive in DMA mode */
  if ((InterruptRequest & I3C_XFER_DMA) != 0U)
  {
    /* Disable frame complete and error interrupts */
    tmpisr |= (HAL_I3C_IT_FCIE | HAL_I3C_IT_ERRIE | HAL_I3C_IT_CFNFIE);
  }

  /* Check if requested interrupts are related to controller transmit in IT mode */
  if ((InterruptRequest & I3C_XFER_CONTROLLER_TX_IT) != 0U)
  {
    /* Disable frame complete, control FIFO not full, transmit FIFO not full and error interrupts */
    tmpisr |= (HAL_I3C_IT_FCIE | HAL_I3C_IT_CFNFIE | HAL_I3C_IT_TXFNFIE | HAL_I3C_IT_ERRIE);
  }

  /* Check if requested interrupts are related to controller transmit read or a broadcast CCC in IT mode */
  if ((InterruptRequest & I3C_XFER_CONTROLLER_RX_CCC_IT) != 0U)
  {
    /* Disable frame complete, transmit FIFO not full, control FIFO not full,
       receive FIFO not empty and error interrupts */
    tmpisr |= (HAL_I3C_IT_FCIE | HAL_I3C_IT_TXFNFIE | HAL_I3C_IT_CFNFIE | HAL_I3C_IT_RXFNEIE | HAL_I3C_IT_ERRIE);
  }

  /* Check if requested interrupts are related to controller transmit broadcast ENTDAA CCC in IT mode */
  if ((InterruptRequest & I3C_XFER_CONTROLLER_DAA_IT) != 0U)
  {
    /* Disable frame complete, control FIFO not full, transmit FIFO not full and error interrupts */
    tmpisr |= (HAL_I3C_IT_FCIE | HAL_I3C_IT_CFNFIE | HAL_I3C_IT_TXFNFIE | HAL_I3C_IT_ERRIE);
  }
  /* Disable requested interrupts */
  __HAL_I3C_DISABLE_IT(hi3c, tmpisr);
}

/**
  * @brief  I3C error treatment.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                     information for the specified I3C.
  * @retval None
  */
void I3C_ErrorTreatment(I3C_HandleTypeDef *hi3c)
{
  HAL_I3C_StateTypeDef tmpstate = hi3c->State;

  /* Check on the state */
  if (tmpstate == HAL_I3C_STATE_BUSY)
  {
    /* Update handle state parameter */
    I3C_StateUpdate(hi3c);

    /* Disable all interrupts related to busy state */
    I3C_Disable_IRQ(hi3c, (I3C_XFER_TARGET_IBI | I3C_XFER_TARGET_HOTJOIN | I3C_XFER_TARGET_CTRLROLE));
  }
  else
  {
    /* Disable all interrupts related to busy Tx and Rx state */
    I3C_Disable_IRQ(hi3c, I3C_XFER_CONTROLLER_RX_CCC_IT);

    /* Reset Tx counter */
    hi3c->TxXferCount = 0U;

    /* Reset Rx counter */
    hi3c->RxXferCount = 0U;

    /* Reset Control counter */
    hi3c->ControlXferCount = 0U;

    /* Reset Tx function pointer */
    hi3c->ptrTxFunc = NULL;

    /* Reset Rx function pointer */
    hi3c->ptrRxFunc = NULL;

    /* Reset Context pointer */
    hi3c->pXferData = NULL;
    hi3c->pCCCDesc = NULL;
    hi3c->pPrivateDesc = NULL;

    /* Flush all FIFOs */
    /* Flush the content of Tx Fifo */
    LL_I3C_RequestTxFIFOFlush(hi3c->Instance);

    /* Flush the content of Rx Fifo */
    LL_I3C_RequestRxFIFOFlush(hi3c->Instance);

    /* Check on the I3C mode: Control and status FIFOs available only with controller mode */
    if (hi3c->Mode == HAL_I3C_MODE_CONTROLLER)
    {
      /* Flush the content of Control Fifo */
      LL_I3C_RequestControlFIFOFlush(hi3c->Instance);

      /* Flush the content of Status Fifo */
      LL_I3C_RequestStatusFIFOFlush(hi3c->Instance);
    }
  }

  if(hi3c->DMAC_Instance != NULL)
  {
    if(LL_I3C_IsEnabledDMAReq_TX(hi3c->Instance))
    {
      LL_I3C_DisableDMAReq_TX(hi3c->Instance);
      HAL_DMA_Channel_Abort(hi3c->DMAC_Instance,hi3c->DMA_channel.TX_DMA_Channel);
    }
    if(LL_I3C_IsEnabledDMAReq_RX(hi3c->Instance))
    {
      LL_I3C_DisableDMAReq_RX(hi3c->Instance);
      HAL_DMA_Channel_Abort(hi3c->DMAC_Instance,hi3c->DMA_channel.RX_DMA_Channel);
    }
  }

  /* Call Error callback if there is no DMA abort on going */
  I3C_TreatErrorCallback(hi3c);
  
}

/**
  * @brief  I3C Error callback treatment.
  * @param  hi3c : [IN] Pointer to an I3C_HandleTypeDef structure that contains the configuration
  *                     information for the specified I3C.
  * @retval None
  */
static void I3C_TreatErrorCallback(I3C_HandleTypeDef *hi3c)
{
  if (hi3c->State == HAL_I3C_STATE_ABORT)
  {
    /* Update handle state parameter */
    I3C_StateUpdate(hi3c);

    /* Call the corresponding callback to inform upper layer of End of Transfer */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->AbortCpltCallback(hi3c);
#else
    HAL_I3C_AbortCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }
  else
  {
    /* Update handle state parameter */
    I3C_StateUpdate(hi3c);

    /* Call the corresponding callback to inform upper layer of End of Transfer */
#if (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->ErrorCallback(hi3c);
#else
    HAL_I3C_ErrorCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
