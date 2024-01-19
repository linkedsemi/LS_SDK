#ifndef LS_HAL_PS2H_H_
#define LS_HAL_PS2H_H_
#include "HAL_def.h"
#include "reg_ps2h_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PS2H_INIT_DRIVER_DELY
#define PS2H_INIT_DRIVER_DELY          1
#endif
#ifndef PS2H_INIT_CAPTURE_DELY
#define PS2H_INIT_CAPTURE_DELY         1
#endif

#define FIFO_RECEIVE_TRIGGER_0BYTE     0x00U
#define FIFO_RECEIVE_TRIGGER_3BYTE     0x03U

typedef enum
{
    PS2_ERROR_START_BIT                = 0x00,
    PS2_ERROR_STOP_BIT                 = 0x01,
    PS2_ERROR_PARITY_BIT               = 0x02,
    PS2_ERROR_RXFIFO_OVERRUN           = 0x04,
} RxErrorMode;

typedef enum
{
    HAL_PS2H_STATE_RESET               = 0x00U,
    HAL_PS2H_STATE_READY               = 0x01U,
    HAL_PS2H_STATE_BUSY                = 0x02U,
} HAL_PS2H_StateTypeDef;

typedef enum
{
    PS2_TXMODE_NOW                     = 0x00U, // 00 :the controller will start TX request by pulling the clock to low more than 100us at any time if tx_req is  set to high even if the controller is receiving data from the PS2 device.
    PS2_TXMODE_EXCEPT_RXLASTBIT        = 0x01U, // 01:the controller will start TX request by pulling the clock to low more than 100us at any time if tx_req is  set to high except that the controller is receiving the last bit of current RX frame.
    PS2_TXMODE_WAIT_RXEND              = 0x02U, // 10:the controller will only start TX request by pulling the clock to low more than 100us when the controller is not receiving.
} PS2H_TxMode;

typedef enum
{
    PS2_TO_IDLE_SATE                   = 0x00, //the controller will return to IDLE state when the stop bit is not as expected 
    PS2_TO_ERROR_SATE                  = 0x01, // the controller will stay in ERROR state when the (stop bit/parity bit/start bit) is not as expected until the err_clr register is set to high
} PS2H_ErrorMode;

typedef enum
{
    PS2_FLTNUM_1CLK                    = 0x01,
    PS2_FLTNUM_5CLK                    = 0x05,
    PS2_FLTNUM_7CLK                    = 0x07,
    PS2_FLTNUM_8CLK                    = 0x08,
} PS2_Flt_Num;

typedef struct
{
    uint8_t                            flt_num; // Glitches narrower than clk_period*flt_num will be blocked by the internal input filter
    uint8_t                            tx_mode;
    uint8_t                            err_mode;
} PS2H_Param;

typedef struct __PS2H_HandleTypeDef
{
    reg_ps2h_t                         *PS2HX;

    uint8_t                            *pBuffPtr;

    uint16_t                           XferCount;
    
    HAL_PS2H_StateTypeDef              State;
} PS2H_HandleTypeDef;

/**
 * @brief  Initializes the PS2H mode according to the specified parameters in
 *         the PS2H_HandleTypeDef and create the associated handle
 * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
 *               the configuration information for the specified PS2H module.
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_PS2H_Init(PS2H_HandleTypeDef *hps2h, PS2H_Param *param);

/**
 * @brief  DeInitializes the PS2H peripheral.
 * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
 *               the configuration information for the specified PS2H module.
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_PS2H_DeInit(PS2H_HandleTypeDef *hps2h);

/**
  * @brief  Sends an amount of data in blocking mode.
  * @note   
  * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
  *               the configuration information for the specified PS2H module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PS2H_Transmit(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint16_t Size);

/**
  * @brief  Receives an amount of data in blocking mode.
  * @note   
  * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
  *               the configuration information for the specified PS2H module.
  * @param  pData Pointer to data buffer (uint8_t data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PS2H_Receive(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
  *               the configuration information for the specified PS2H module.
  * @param  pData Pointer to data buffer (uint8_t  data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PS2H_Transmit_IT(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint16_t Size);

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
  *               the configuration information for the specified PS2H module.
  * @param  pData Pointer to data buffer (uint8_t  data elements).
  * @param  Size  Amount of data elements (uint8_t) to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_PS2H_Receive_IT(PS2H_HandleTypeDef *hps2h, uint8_t *pData, uint16_t Size);

/**
  * @brief  TX Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_PS2H_TxCallBack could be implemented in the user file
  * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
  *               the configuration information for the specified PS2H module.
  */
void HAL_PS2H_TxCpltCallback(PS2H_HandleTypeDef *hps2h);

/**
  * @brief  RX Transfer completed callbacks.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_PS2H_RXCallBack could be implemented in the user file
  * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
  *               the configuration information for the specified PS2H module.
  */
void HAL_PS2H_RxCpltCallback(PS2H_HandleTypeDef *hps2h);

/**
  * @brief  TX Transfer Error callbacks, including ack error
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_PS2H_RXCallBack could be implemented in the user file
  * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
  *               the configuration information for the specified PS2H module.
  */
void HAL_PS2H_TxErrorCallBack(PS2H_HandleTypeDef *hps2h);
/**
  * @brief  RX Transfer Error callbacks
  *         including stop bit error, parity bit error, start bit error, fifo over.
  * @note  This function needs to be implemented when the callback is needed,
           the HAL_PS2H_RXCallBack could be implemented in the user file
  * @param  hps2h Pointer to a PS2H_HandleTypeDef structure that contains
  *               the configuration information for the specified PS2H module.
  */
void HAL_PS2H_RxErrorCallBack(PS2H_HandleTypeDef *hps2h, RxErrorMode errmode);

void HAL_PS2H_IRQHandler(PS2H_HandleTypeDef *hps2h);

#ifdef __cplusplus
}
#endif

#endif