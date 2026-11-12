#ifndef __HAL_I3C_DEINFE__
#define __HAL_I3C_DEINFE__

#include <stdio.h>
#include <stdbool.h>
#include "reg_i3c.h"
#include "HAL_def.h"


/** @defgroup I3C_FIFO_Config_Structure_definition I3C FIFO Configuration Structure definition
  * @brief    I3C FIFO configuration structure definition
  * @{
  */
typedef struct
{
  uint32_t RxFifoThreshold; /*!< Specifies the I3C Rx FIFO threshold level.
                                 This parameter must be a value of @ref I3C_RX_FIFO_THRESHOLD                         */

  uint32_t TxFifoThreshold; /*!< Specifies the I3C Tx FIFO threshold level.
                                 This parameter must be a value of @ref I3C_TX_FIFO_THRESHOLD                         */

  uint32_t StatusFifo;      /*!< Specifies the I3C status FIFO enable/disable state.
                                 This parameter is configured only with controller mode and it
                                 must be a value of @ref I3C_STATUS_FIFO_STATE                                        */
} I3C_FifoConfTypeDef;
/**
  * @}
  */

/** @defgroup I3C_Controller_Config_Structure_definition I3C Controller Configuration Structure definition
  * @brief    I3C controller configuration structure definition
  * @{
  */
typedef struct
{
  // uint8_t DynamicAddr;            /*!< Specifies the dynamic address of the controller when goes in target mode.
  //                                      This parameter must be a number between Min_Data=0x00 and Max_Data=0x7F        */

  uint8_t StallTime;              /*!< Specifies the controller clock stall time in number of kernel clock cycles.
                                       This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF        */

  FunctionalState HotJoinAllowed; /*!< Specifies the Enable/Disable state of the controller Hot Join acknowledgement
                                       when receiving a hot join request from target.
                                       This parameter can be set to ENABLE or DISABLE                                 */

  FunctionalState ACKStallState;  /*!< Specifies the Enable/Disable state of the controller clock stall
                                       on the ACK phase.
                                       This parameter can be set to ENABLE or DISABLE                                 */

  FunctionalState CCCStallState;  /*!< Specifies the Enable/Disable state of the controller clock stall on the
                                       T bit phase of a CCC communication to allow the target to decode command.
                                       This parameter can be set to ENABLE or DISABLE                                 */

  FunctionalState TxStallState;   /*!< Specifies the Enable/Disable state of the controller clock stall on
                                       parity phase of data to allow the target to read received data.
                                       This parameter can be set to ENABLE or DISABLE                                 */

  FunctionalState RxStallState;   /*!< Specifies the Enable/Disable state of the controller clock stall on the T bit
                                       phase of data enable to allow the target to prepare data to be sent.
                                       This parameter can be set to ENABLE or DISABLE                                 */

  // FunctionalState HighKeeperSDA;  /*!< Specifies the Enable/Disable state of the controller SDA high keeper.
  //                                      This parameter can be set to ENABLE or DISABLE                                 */
} I3C_CtrlConfTypeDef;
/**
  * @}
  */

/** @defgroup I3C_Target_Config_Structure_definition I3C Target Configuration Structure definition
  * @brief    I3C target configuration structure definition
  * @{
  */
typedef struct
{
  uint8_t Identifier;                  /*!< Specifies the target characteristic ID (MIPI named reference DCR).
                                            This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF   */

  uint8_t MIPIIdentifier;              /*!< Specifies the bits [12-15] of the 48-provisioned ID
                                            (MIPI named reference PID), other 48-provisioned ID are hardcoded.
                                            This parameter must be a number between Min_Data=0x00 and Max_Data=0x0F   */

  FunctionalState CtrlRoleRequest;     /*!< Specifies the Enable/Disable state of the target authorization request
                                            for a second master Chip.
                                            This parameter can be set to ENABLE or DISABLE                            */

  FunctionalState HotJoinRequest;      /*!< Specifies the Enable/Disable state of the target hot join
                                            authorization request.
                                            This parameter can be set to ENABLE or DISABLE                            */

  FunctionalState IBIRequest;          /*!< Specifies the Enable/Disable state of the target in Band Interrupt
                                            authorization request.
                                            This parameter can be set to ENABLE or DISABLE                            */

  FunctionalState IBIPayload;          /*!< Specifies the Enable/Disable state of sending data payload after
                                            an accepted IBI.
                                            This parameter can be set to ENABLE or DISABLE                            */

  uint32_t IBIPayloadSize;             /*!< Specifies the I3C target payload data size.
                                            This parameter must be a value of @ref I3C_PAYLOAD_SIZE                   */

  uint16_t MaxReadDataSize;            /*!< Specifies the numbers of data bytes that the target can read at maximum.
                                            This parameter must be a number between Min_Data=0x00 and Max_Data=0xFFFF */

  uint16_t MaxWriteDataSize;           /*!< Specifies the numbers of data bytes that the target can write at maximum.
                                            This parameter must be a number between Min_Data=0x00 and Max_Data=0xFFFF */

  FunctionalState CtrlCapability;      /*!< Specifies the Enable/Disable state of the target controller capability.
                                            This parameter can be set to ENABLE or DISABLE                            */

  FunctionalState GroupAddrCapability; /*!< Specifies the Enable/Disable state of the target support of group address
                                            after a controller role hand-off.
                                            This parameter can be set to ENABLE or DISABLE                            */

  uint32_t DataTurnAroundDuration;     /*!< Specifies the I3C target clock-to-data turnaround time.
                                            This parameter must be a value of @ref I3C_TURNAROUND_TIME_TSCO           */

  uint8_t MaxReadTurnAround;           /*!< Specifies the target maximum read turnaround byte.
                                            This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF   */

  uint32_t MaxDataSpeed;               /*!< Specifies the I3C target returned GETMXDS CCC format.
                                            This parameter must be a value of @ref I3C_GETMXDS_FORMAT                 */

  FunctionalState MaxSpeedLimitation;  /*!< Specifies the Enable/Disable state of the target max data speed limitation.
                                            This parameter can be set to ENABLE or DISABLE                            */

  uint32_t HandOffActivityState;       /*!< Specifies the I3C target activity state when becoming controller.
                                            This parameter must be a value of @ref I3C_HANDOFF_ACTIVITY_STATE         */

  FunctionalState HandOffDelay;        /*!< Specifies the Enable/Disable state of the target need of delay to process
                                            the controller role hand-off.
                                            This parameter can be set to ENABLE or DISABLE                            */

  FunctionalState PendingReadMDB;      /*!< Specifies the Enable/Disable state of the transmission of a mandatory
                                            data bytes indicating a pending read notification for GETCAPR CCC command.
                                            This parameter can be set to ENABLE or DISABLE                            */
} I3C_TgtConfTypeDef;
/**
  * @}
  */

/** @defgroup I3C_Device_Config_Structure_definition I3C Device Configuration Structure definition
  * @brief    I3C device configuration structure definition
  * @{
  */
typedef struct
{
  uint8_t         DeviceIndex;       /*!< Specifies the index value of the device in the DEVRx register.
                                          This parameter must be a number between Min_Data=1 and Max_Data=4           */

  uint8_t         TargetDynamicAddr; /*!< Specifies the dynamic address of the target x (1 to 4) connected on the bus.
                                          This parameter must be a number between Min_Data=0x00 and Max_Data=0x7F     */

  FunctionalState IBIAck;            /*!< Specifies the Enable/Disable state of the controller's ACK when receiving
                                          an IBI from a target x (1 to 4) connected on the bus.
                                          This parameter can be set to ENABLE or DISABLE                              */

  FunctionalState IBIPayload;        /*!< Specifies the Enable/Disable state of the controller's receiving IBI payload
                                          after acknowledging an IBI requested from a target x (1 to 4) connected
                                          on the bus.
                                          This parameter can be set to ENABLE or DISABLE                              */

  FunctionalState CtrlRoleReqAck;    /*!< Specifies the Enable/Disable state of the controller's ACK when receiving
                                          a control request from a target x (1 to 4) connected on the bus.
                                          This parameter can be set to ENABLE or DISABLE                              */

  FunctionalState CtrlStopTransfer;  /*!< Specifies the Enable/Disable state of the controller's stop transfer after
                                          receiving an IBI request from a target x (1 to 4) connected on the bus.
                                          This parameter can be set to ENABLE or DISABLE                              */

} I3C_DeviceConfTypeDef;
/**
  * @}
  */

/** @defgroup I3C_mode_structure_definition I3C mode structure definition
  * @brief    I3C Mode structure definition
  * @{
  */
typedef enum
{
  HAL_I3C_MODE_NONE       = 0x00U,  /*!< No I3C communication on going             */
  HAL_I3C_MODE_CONTROLLER = 0x01U,  /*!< I3C communication is in controller Mode   */
  HAL_I3C_MODE_TARGET     = 0x02U,  /*!< I3C communication is in target Mode       */

} HAL_I3C_ModeTypeDef;
/**
  * @}
  */

/** @defgroup HAL_state_structure_definition HAL state structure definition
  * @brief    HAL State structure definition
  * @{
  */
typedef enum
{
  HAL_I3C_STATE_RESET       = 0x00U,   /*!< Peripheral is not yet Initialized                   */
  HAL_I3C_STATE_READY       = 0x10U,   /*!< Peripheral Initialized and ready for use            */
  HAL_I3C_STATE_BUSY        = 0x20U,   /*!< An internal process is ongoing                      */
  HAL_I3C_STATE_BUSY_TX     = 0x21U,   /*!< Data Transmission process is ongoing                */
  HAL_I3C_STATE_BUSY_RX     = 0x22U,   /*!< Data Reception process is ongoing                   */
  HAL_I3C_STATE_BUSY_TX_RX  = 0x23U,   /*!< Data Multiple Transfer process is ongoing           */
  HAL_I3C_STATE_BUSY_DAA    = 0x24U,   /*!< Dynamic address assignment process is ongoing       */
  HAL_I3C_STATE_LISTEN      = 0x30U,   /*!< Listen process is ongoing                           */
  HAL_I3C_STATE_ABORT       = 0x60U,   /*!< Abort user request ongoing                          */
  HAL_I3C_STATE_ERROR       = 0xE0U,   /*!< Error                                               */

} HAL_I3C_StateTypeDef;

/**
  * @}
  */

/** @defgroup I3C_CCCInfoTypeDef_Structure_definition I3C CCCInfoTypeDef Structure definition
  * @brief    I3C CCCInfoTypeDef Structure definition
  * @{
  */
typedef struct
{
  uint32_t DynamicAddrValid;    /*!< I3C target Dynamic Address Valid (updated during ENTDAA/RSTDAA/SETNEWDA CCC)
                                     This parameter can be Valid=1U or Not Valid=0U                                   */
  uint32_t DynamicAddr;         /*!< I3C target Dynamic Address (updated during ENTDAA/RSTDAA/SETNEWDA CCC)           */
  uint32_t MaxWriteLength;      /*!< I3C target Maximum Write Length (updated during SETMWL CCC)                      */
  uint32_t MaxReadLength;       /*!< I3C target Maximum Read Length (updated during SETMRL CCC)                       */
  uint32_t ResetAction;         /*!< I3C target Reset Action level (updated during RSTACT CCC)                        */
  uint32_t ActivityState;       /*!< I3C target Activity State (updated during ENTASx CCC)                            */
  uint32_t HotJoinAllowed;      /*!< I3C target Hot Join (updated during ENEC/DISEC CCC)
                                     This parameter can be Allowed=1U or Not Allowed=0U                               */
  uint32_t InBandAllowed;       /*!< I3C target In Band Interrupt (updated during ENEC/DISEC CCC)
                                     This parameter can be Allowed=1U or Not Allowed=0U                               */
  uint32_t CtrlRoleAllowed;     /*!< I3C target Controller Role Request (updated during ENEC/DISEC CCC)
                                     This parameter can be Allowed=1U or Not Allowed=0U                               */
  uint32_t IBICRTgtAddr;        /*!< I3C controller receive Target Address during IBI or Controller Role Request event*/
  uint32_t IBITgtNbPayload;     /*!< I3C controller get Number of Data Payload after an IBI event                     */
  uint32_t IBITgtPayload;       /*!< I3C controller receive IBI Payload after an IBI event                            */

} I3C_CCCInfoTypeDef;
/**
  * @}
  */

/** @defgroup I3C_ControlTypeDef_Structure_definition I3C ControlTypeDef Structure definition
  * @brief    I3C ControlTypeDef Structure definition
  * @{
  */
typedef struct
{
  uint32_t *pBuffer;  /*!< Pointer to the buffer containing the control or status register values */
  uint32_t  Size;     /*!< The size of pBuffer in words                                           */

} I3C_ControlTypeDef;
/**
  * @}
  */

/** @defgroup I3C_DataTypeDef_Structure_definition I3C DataTypeDef Structure definition
  * @brief    I3C DataTypeDef Structure definition
  * @{
  */
typedef struct
{
  uint8_t   *pBuffer;  /*!< Pointer to the buffer containing all data values to transfer */
  uint32_t  Size;      /*!< The size of pBuffer in bytes                                 */

} I3C_DataTypeDef;

/**
  * @}
  */

/** @defgroup I3C_CCCTypeDef_Structure_definition I3C CCCTypeDef Structure definition
  * @brief    I3C CCCTypeDef Structure definition
  * @{
  */
typedef struct
{
  uint8_t            TargetAddr; /*!< Dynamic or Static target Address                                      */
  uint8_t            CCC;        /*!< CCC value code                                                        */
  I3C_DataTypeDef    CCCBuf;     /*!< Contain size of associated data and size of defining byte if any.
                                      Contain pointer to CCC associated data                                */
  uint32_t           Direction;  /*!< CCC read and/or write direction message                               */

} I3C_CCCTypeDef;
/**
  * @}
  */

/** @defgroup I3C_BCRTypeDef_Structure_definition I3C BCRTypeDef Structure definition
  * @brief    I3C BCRTypeDef Structure definition
  * @{
  */
typedef struct
{
  FunctionalState         MaxDataSpeedLimitation;  /*!< Max data speed limitation */
  FunctionalState         IBIRequestCapable;       /*!< IBI request capable */
  FunctionalState         IBIPayload;              /*!< IBI payload data */
  FunctionalState         OfflineCapable;          /*!< Offline capable */
  FunctionalState         VirtualTargetSupport;    /*!< Virtual target support */
  FunctionalState         AdvancedCapabilities;    /*!< Advanced capabilities */
  FunctionalState         DeviceRole;              /*!< Device role */

} I3C_BCRTypeDef;
/**
  * @}
  */

/** @defgroup I3C_PIDTypeDef_Structure_definition I3C PIDTypeDef Structure definition
  * @brief    I3C_PIDTypeDef Structure definition
  * @{
  */
typedef struct
{
  uint16_t  MIPIMID;         /*!< MIPI Manufacturer ID */
  uint8_t   IDTSEL;          /*!< Provisioned ID Type Selector */
  uint16_t  PartID;          /*!< Part ID device vendor to define */
  uint8_t   MIPIID;          /*!< Instance ID */

} I3C_PIDTypeDef;
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup I3C_LL_ES_CONTROLLER_BUS_CONFIG_STRUCTURE_DEFINITION I3C Controller Bus Configuration Structure definition
  * @brief    I3C LL Controller Bus Configuration Structure definition
  * @{
  */
typedef struct
{
  uint32_t SDAHoldTime;         /*!< Specifies the I3C SDA hold time.
                                     This parameter must be a value of @ref I3C_LL_EC_SDA_HOLD_TIME                   */

  uint32_t WaitTime;            /*!< Specifies the time that the main and the new controllers should wait before
                                     issuing a start.
                                     This parameter must be a value of @ref I3C_LL_EC_OWN_ACTIVITY_STATE              */

  uint8_t SCLPPLowDuration;     /*!< Specifies the I3C SCL low duration in number of kernel clock cycles
                                     in I3C push-pull phases.
                                     This parameter must be a number between Min_Data=0 and Max_Data=0xFF.            */

  uint8_t SCLI3CHighDuration;   /*!< Specifies the I3C SCL high duration in number of kernel clock cycles,
                                     used for I3C messages for I3C open-drain and push pull phases.
                                     This parameter must be a number between Min_Data=0 and Max_Data=0xFF.            */

  uint8_t SCLODLowDuration;     /*!< Specifies the I3C SCL low duration in number of kernel clock cycles in
                                     open-drain phases, used for legacy I2C commands and for I3C open-drain phases.
                                     This parameter must be a number between Min_Data=0 and Max_Data=0xFF.            */

  uint8_t SCLI2CHighDuration;   /*!< Specifies the I3C SCL high duration in number of kernel clock cycles, used
                                     for legacy I2C commands.
                                     This parameter must be a number between Min_Data=0 and Max_Data=0xFF.            */

  uint8_t BusFreeDuration;      /*!< Specifies the I3C controller duration in number of kernel clock cycles, after
                                     a stop and before a start.
                                     This parameter must be a number between Min_Data=0 and Max_Data=0xFF.            */

  uint8_t BusIdleDuration;      /*!< Specifies the I3C controller duration in number of kernel clock cycles to be
                                     elapsed, after that both SDA and SCL are continuously high and stable
                                     before issuing a hot-join event.
                                     This parameter must be a number between Min_Data=0 and Max_Data=0xFF.            */
} LL_I3C_CtrlBusConfTypeDef;

/*!
 * @brief Structure with settings to initialize the I3C slave module.
 *
 * This structure holds configuration settings for the I3C peripheral. To initialize this
 * structure to reasonable defaults, call the I3C_TargetGetDefaultConfig() function and
 * pass a pointer to your configuration structure instance.
 *
 * The configuration structure can be made constant so it resides in flash.
 */
typedef struct
{
    uint8_t dnamicAddress;
    uint8_t matchCount;
    bool isHotJoin;     /*!< Whether to enable slave hotjoin before enable slave. */
    uint8_t staticAddr; /*!< Static address. */
    uint16_t vendorID;  /*!< Device vendor ID(manufacture ID). */
    bool enableRandomPart; /*!< Whether to generate random part number, if using random part number,
                                the partNumber variable setting is meaningless. */
    uint32_t partNumber;  /*!< Device part number info */
    uint8_t dcr;          /*!< Device characteristics register information. */
    uint8_t bcr;          /*!< Bus characteristics register information. */
    // uint8_t hdrMode;      /*!< not support hdr mode */
    bool nakAllRequest;   /*!< Whether to reply NAK to all requests except broadcast CCC. */
    bool ignoreS0S1Error; /*!< Whether to ignore S0/S1 error in SDR mode. */
    bool offline; /*!< Whether to wait 60 us of bus quiet or HDR request to ensure slave track SDR mode safely. */
    bool matchTargetStartStop; /*!< Whether to assert start/stop status only the time slave is addressed. */
    uint32_t maxWriteLength;  /*!< Maximum write length. */
    uint32_t maxReadLength;   /*!< Maximum read length. */
} LL_I3C_TgtBusConfTypeDef;


/** @defgroup I3C_XferTypeDef_Structure_definition I3C XferTypeDef Structure definition
  * @brief    I3C XferTypeDef Structure definition
  * @{
  */
typedef struct
{
  I3C_ControlTypeDef CtrlBuf;      /*!< Buffer structure containing the control register values  */
  I3C_ControlTypeDef StatusBuf;    /*!< Buffer structure containing the status register values   */
  I3C_DataTypeDef    TxBuf;        /*!< Buffer structure containing the data to transmit         */
  I3C_DataTypeDef    RxBuf;        /*!< Buffer structure containing the data to receive          */

} I3C_XferTypeDef;
/**
  * @}
  */

/** @defgroup I3C_ENTDAAPayloadTypeDef_Structure_definition I3C ENTDAAPayloadTypeDef Structure definition
  * @brief    I3C ENTDAAPayloadTypeDef Structure definition
  * @{
  */
typedef struct
{
  I3C_BCRTypeDef   BCR;             /*!< Bus Characteristics Register */
  uint32_t         DCR;             /*!< Device Characteristics Register */
  I3C_PIDTypeDef   PID;             /*!< Provisioned ID */

} I3C_ENTDAAPayloadTypeDef;

/** @defgroup I3C_PrivateTypeDef_Structure_definition I3C PrivateTypeDef Structure definition
  * @brief    I3C PrivateTypeDef Structure definition
  * @{
  */
typedef struct
{
  uint8_t            TargetAddr;  /*!< Dynamic or Static target Address                                 */
  I3C_DataTypeDef    TxBuf;       /*!< Buffer structure containing the data to transmit (little endian) */
  I3C_DataTypeDef    RxBuf;       /*!< Buffer structure containing the data to receive (little endian)  */
  uint32_t           Direction;   /*!< Read and/or write message                                        */

} I3C_PrivateTypeDef;
/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Exported_Types I3C Exported Types
  * @{
  */
/** @defgroup I3C_Init_Structure_definition I3C Init Structure definition
  * @brief    I3C Init Structure definition
  * @{
  */
typedef struct
{
  LL_I3C_CtrlBusConfTypeDef CtrlBusCharacteristic; /*!< Specifies the I3C controller bus characteristic configuration
                                                        when Controller mode                                          */

  I3C_FifoConfTypeDef CtrlFifoConfig;
                        
  I3C_CtrlConfTypeDef CtrlConfig;

  LL_I3C_TgtBusConfTypeDef  TgtBusCharacteristic;  /*!< Specifies the I3C target bus characteristic configuration
                                                        when Target mode                                              */
} I3C_InitTypeDef;


typedef struct 
{
    uint8_t TX_DMA_Channel;
    uint8_t RX_DMA_Channel;
}I3C_DMA_ChannelTypeDef;

/** @defgroup I3C_handle_Structure_definition I3C handle Structure definition
  * @brief    I3C handle Structure definition
  * @{
  */
typedef struct __I3C_HandleTypeDef
{
  I3C_TypeDef                *Instance;                           /*!< I3C registers base address                */

  I3C_InitTypeDef            Init;                                /*!< I3C communication parameters              */

  bool EnableTarget;                                              /*!< Whether to enable target. */

  bool EnableController;                                          /*!< Whether to enable controller. */

  void                        *DMAC_Instance;  

  volatile I3C_DMA_ChannelTypeDef  DMA_channel;              

  HAL_I3C_ModeTypeDef        Mode;                                /*!< I3C communication mode.
                                            1                           This parameter must be a value of
                                                                       @ref I3C_mode_structure_definition        */

  I3C_XferTypeDef            *pXferData;                          /*!< I3C transfer buffers pointer              */

  const I3C_CCCTypeDef       *pCCCDesc;                           /*!< I3C CCC descriptor pointer                */

  const I3C_PrivateTypeDef   *pPrivateDesc;                       /*!< I3C private transfer descriptor pointer   */

  uint32_t                   ControlXferCount;                    /*!< I3C counter indicating the remaining
                                                                       control data bytes to write in
                                                                       the control register                      */

  uint32_t                   RxXferCount;                         /*!< I3C counter indicating the remaining
                                                                       data bytes to receive                     */

  uint32_t                   TxXferCount;                         /*!< I3C counter indicating the remaining
                                                                       data bytes to transmit                    */

  HAL_LockTypeDef            Lock;                                /*!< I3C locking object                        */

  volatile HAL_I3C_StateTypeDef  State;                               /*!< I3C communication state                   */

  volatile HAL_I3C_StateTypeDef  PreviousState;                       /*!< I3C communication previous state          */

  volatile uint32_t              ErrorCode;                           /*!< I3C Error code                            */

  HAL_StatusTypeDef(*XferISR)(struct __I3C_HandleTypeDef *hi3c,
                              uint32_t itMasks);                  /*!< I3C transfer IRQ handler function pointer */

  HAL_StatusTypeDef(*XferISR2)(struct __I3C_HandleTypeDef *hi3c);                  /*!< I3C transfer IRQ handler function pointer */

  void(*ptrTxFunc)(struct __I3C_HandleTypeDef *hi3c);             /*!< I3C transmit function pointer             */

  void(*ptrRxFunc)(struct __I3C_HandleTypeDef *hi3c);             /*!< I3C receive function pointer              */

} I3C_HandleTypeDef;



#endif