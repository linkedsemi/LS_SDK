#ifndef LS_HAL_CEC_H_
#define LS_HAL_CEC_H_

#include "sdk_config.h"
#include <stdbool.h>
#include "HAL_def.h"
#include "reg_base_addr.h"
#include "ls_msp_cec.h"
#include "ls_soc_gpio.h"

#define MAXNUM_RECEIVE_ONCE           16

#define CEC_INITIATOR_ADDRESS_0       0x0
#define CEC_INITIATOR_ADDRESS_1       0x1
#define CEC_INITIATOR_ADDRESS_2       0x2
#define CEC_INITIATOR_ADDRESS_3       0x3
#define CEC_INITIATOR_ADDRESS_4       0x4
#define CEC_INITIATOR_ADDRESS_5       0x5
#define CEC_INITIATOR_ADDRESS_6       0x6
#define CEC_INITIATOR_ADDRESS_7       0x7
#define CEC_INITIATOR_ADDRESS_8       0x8
#define CEC_INITIATOR_ADDRESS_9       0x9
#define CEC_INITIATOR_ADDRESS_10      0xA
#define CEC_INITIATOR_ADDRESS_11      0xB
#define CEC_INITIATOR_ADDRESS_12      0xC
#define CEC_INITIATOR_ADDRESS_13      0xD
#define CEC_INITIATOR_ADDRESS_14      0xE

#define CEC_DESTINATION_ADDRESS       0x00

#define CEC_CLKRATE           (15 * (SDK_HCLK_MHZ) - 1)

#define CEC_ENABLE            (0x00000001U)
#define CEC_DISABLE           (0x00000000U)


enum cec_free_time_sel
{
    NORMAL_DATA_3 = 0x00,
    NORMAL_DATA_5 = 0x01,
    NORMAL_DATA_7 = 0x02
};

typedef struct
{
  uint32_t  FrameType;
  uint8_t   MasterAddress;
  uint8_t   SlaveAddress;
} CEC_InitTypeDef;

typedef struct
{
  uint32_t *rxbuf;
  uint32_t *txbuf;
  uint8_t size;
} CEC_Recv_t;

/**
 * @brief  CEC handle Structure definition
 */
typedef struct __CEC_HandleTypeDef
{
    reg_cec_t *Instance;  /*!< CEC registers base address        */
    CEC_InitTypeDef Init; /*!< CEC communication parameters      */
    CEC_Recv_t recv;
    uint8_t cbk_index;
} CEC_HandleTypeDef;

/**
 * @brief  Sends an amount of data in non blocking mode.
 * @param  hcec Pointer to a CEC_HandleTypeDef structure that contains
 *              the configuration information for the specified CEC module.
 * @param  SlaveAddress The address of the destination
 * @param  buffer Pointer to data buffer (uint8_t  data elements).
 * @param  Size  Amount of data elements (uint8_t) to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_CEC_Transmit(CEC_HandleTypeDef *hcec,uint8_t SlaveAddress, uint32_t *buffer, uint8_t Size);

/**
 * @brief  Receive an amount of data in non blocking mode.
 * @param  hcec Pointer to a CEC_HandleTypeDef structure that contains
 *              the configuration information for the specified CEC module.
 * @param  buffer Pointer to data buffer (uint8_t  data elements).
 * @param  Size  Amount of data elements (uint8_t) to be receive
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_CEC_Receive(CEC_HandleTypeDef *hcec, uint32_t *buffer, uint8_t *Size);

/**
 * @brief Initializes the CEC mode according to the specified parameters in
 *         the CEC_InitTypeDef and create the associated handle.
 * @param  hcec Pointer to a CEC_HandleTypeDef structure that contains
 *              the configuration information for the specified CEC module.
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_CEC_Init(CEC_HandleTypeDef *hcec);

/**
 * @brief  HAL_CEC_DeInit
 * @param hcec 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_CEC_DeInit(CEC_HandleTypeDef *hcec);

/**
 * @brief  Handles CEC interrupt request
 * @param  hcec Pointer to a CEC_HandleTypeDef structure that contains
 *              the configuration information for the specified CEC module.
 * @retval
 */
void HAL_CEC_IRQHandler(CEC_HandleTypeDef *hcec);

/**
 * @brief  HAL_CEC_TX_DONE_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_CEC_TX_DONE_Callback could be implemented in the user file
 */
void HAL_CEC_TX_DONE_Callback(void);

/**
 * @brief  HAL_CEC_RX_FINISH_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_CEC_RX_FINISH_Callback could be implemented in the user file
 * @param count The number of data received by the CEC
 */
void HAL_CEC_RX_FINISH_Callback(uint8_t count);

/**
 * @brief  HAL_CEC_NACK_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_CEC_NACK_Callback could be implemented in the user file
 */
void HAL_CEC_NACK_Callback(void);

/**
 * @brief  HAL_CEC_ARB_LOST_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_CEC_ARB_LOST_Callback could be implemented in the user file
 */
void HAL_CEC_ARB_LOST_Callback(void);

/**
 * @brief  HAL_CEC_TX_ERR_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_CEC_TX_ERR_Callback could be implemented in the user file
 */
void HAL_CEC_TX_ERR_Callback(void);

/**
 * @brief  HAL_CEC_LBIT_ERR_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_CEC_LBIT_ERR_Callback could be implemented in the user file
 */
void HAL_CEC_LBIT_ERR_Callback(void);

/**
 * @brief  HAL_CEC_WAKE_EN_Callback
 * NOTE: This function should not be modified, when the callback is needed,
 *         the HAL_CEC_WAKE_EN_Callback could be implemented in the user file
 */
void HAL_CEC_WAKE_EN_Callback(void);

/**
 * @brief  Sends an amount of data in non blocking mode.
 * @param  hcec Pointer to a CEC_HandleTypeDef structure that contains
 *              the configuration information for the specified CEC module.
 * @param  SlaveAddress The address of the destination
 * @param  buffer Pointer to data buffer (uint8_t  data elements).
 * @param  Size  Amount of data elements (uint8_t) to be sent
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_CEC_Transmit_IT( CEC_HandleTypeDef *hcec, uint8_t SlaveAddress, uint32_t *buffer, uint16_t Size);

/**
 * @brief  Receive an amount of data in non blocking mode.
 * @param  hcec Pointer to a CEC_HandleTypeDef structure that contains
 *              the configuration information for the specified CEC module.
 * @param  buffer Pointer to data buffer (uint8_t  data elements).
 * @retval HAL status
 */
HAL_StatusTypeDef HAL_CEC_Receive_IT( CEC_HandleTypeDef *hcec, uint32_t *buffer);

#endif
