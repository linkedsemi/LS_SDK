#ifndef LS_HAL_SPIS_H_
#define LS_HAL_SPIS_H_
#include <stdbool.h>
#include "HAL_def.h"
#include "ls_msp_spis.h"

#define SPIS_FIFO_DEPTH                   15

/**
  * @brief  SPIS Configuration Structure definition
  */
typedef struct
{
    uint32_t Frame_Size;             /*!< indicates the frame size of the SPIS.(A frame consists of several bits).
                                      range: 0~31, expression: 1bit~32bits. unit: bit */

    uint32_t FirstBit;               /*!< Specifies whether data transfers start from MSB or LSB bit.
                                     This parameter can be a value of @ref SPIS_MSB_LSB_transmission */

    uint8_t CLKPolarity;              /*!< SPIS Clock Polarity. This parameter can be a value of @ref SPIS_Clock_Polarity*/

    uint8_t CLKPhase;                /*!< SPIS Clock Phase. This parameter can be a value of @refSPIS_Clock_Phase*/
}SPIS_InitTypeDef;


/**
  * @brief  Interrupt Environment
  */
struct Interrupt_Env
{
    uint8_t                     *pBuffPtr;
    uint32_t                    XferCount;
};

/**
  * @brief  DMA Environment
  */
struct SPIS_DMA_Env
{
    uint8_t Channel;             /**< Configure the number of DMA channels */
};

/**
  * @brief SPIS handle Structure definition
  */
typedef struct __SPIS_HandleTypeDef
{
    reg_spis_t                  *Instance;          /*!< SPIS registers base address               */
    SPIS_InitTypeDef            Init;               /*!< SPIS communication parameters             */
    void                        *DMAC_Instance;
    union{
          struct Interrupt_Env  Interrupt;            /*!< Interrupt Env  */
          struct SPIS_DMA_Env        DMA;                  /*!< DMA Env  */
    }Tx_Env,Rx_Env;                                 /*!< Tx Rx Environment */
}SPIS_HandleTypeDef;

// CAP_DIS
#define SPIS_RX_EN                      (0x00000000U)
#define SPIS_RX_DIS                     SPIS_CAP_DIS_MASK

// DRV_DIS 
#define SPIS_TX_EN                      (0x00000000U)
#define SPIS_TX_DIS                     SPIS_DRV_DIS_MASK


/** @defgroup SPIS_Clock_Polarity SPIS Clock Polarity
  * @{
  */
#define SPIS_POLARITY_LOW                (0x00000000U)       /*!< The SPI Clock Polarity is LOW    */
#define SPIS_POLARITY_HIGH               (0x00000001U)          //SPIS_TX_POL_MASK   /*!< The SPI Clock Polarity is HIGH   */

// SPIS_Clock_Phase SPIS Clock Phase
#define SPIS_PHASE_1EDGE                (0x00000000U)              /*!< The SPIS Clock Phase is 1 edge    */
#define SPIS_PHASE_2EDGE                (0x00000001U)               //SPIS_TX_START_IDX_MASK     /*!< The SPIS Clock Phase is 2 edge    */

// SPIS_MSB_LSB_transmission SPIS MSB LSB Transmission

#define SPIS_FIRSTBIT_LSB               (0x00000000U)              /*!< SPIS LSB Transmission  */
#define SPIS_FIRSTBIT_MSB               SPIS_TX_MSB_MASK           /*!< SPIS MSB Transmission  */

// Cap_Infnt
#define CAP_INFNT_DepOn_CAP_IDX         (0x00000000U)               /*!< The frame number to be received is depending on cap_idx  */
#define RECEIVE_ALL_FRAMES              SPIS_CAP_INFNT_MASK         /*!< All of the frames are to be received.  */

/**
 * @brief Initialize the SPIS.
 * 
 * @param spis 
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_Init(SPIS_HandleTypeDef *spis);

/**
 * @brief De-Initialize the SPIS.
 * 
 * @param spis
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_LSSPIS_DeInit(SPIS_HandleTypeDef *spis);

/**
 * @brief Initialize the SPIS Tx.
 * 
 * @param spis 
 */
void spis_tx_cfg(SPIS_HandleTypeDef *spis);

/**
 * @brief Initialize the SPIS Rx.
 * 
 * @param spis 
 */
void spis_rx_cfg(SPIS_HandleTypeDef *spis);

/**
 * @brief Initialize the SPIS Tx and Rx.
 * 
 * @param spis 
 */
void spis_tx_rx_cfg(SPIS_HandleTypeDef *spis);

/**
  * @brief  Send data in polling mode.
  * @param  spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
  * @param  pTxData pointer to Tx data buffer
  * @param  Size Transmitted word count
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPIS_Transmit(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint16_t Size, uint32_t Timeout);

/**
 * @brief Receive data in polling mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @param pRxData pointer to Rx data buffer
 * @param Size Transmitted word count
 * @param Timeout Timeout duration
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_Receive(SPIS_HandleTypeDef *spis, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);

/**
 * @brief Send and receive data in polling mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @param pTxData pointer to Tx data buffer
 * @param pRxData pointer to Rx data buffer
 * @param Size Transmitted word count
 * @param Timeout Timeout duration
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_TransmitReceive(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);

/**
 * @brief Send data in interrupt mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @param pTxData pointer to Tx data buffer
 * @param Size Transmitted word count
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_Transmit_IT(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint16_t Size);

/**
 * @brief Receive data in interrupt mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @param pRxData pointer to Rx data buffer
 * @param Size Transmitted word count
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_Receive_IT(SPIS_HandleTypeDef *spis, uint8_t *pRxData, uint16_t Size);

/**
 * @brief Send and receive data in interrupt mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @param pTxData pointer to Tx data buffer
 * @param pRxData pointer to Rx data buffer
 * @param Size Transmitted word count
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_TransmitReceive_IT(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);

/**
 * @brief Send data in dma mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @param pTxData pointer to Tx data buffer
 * @param Size Transmitted word count
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_Transmit_DMA(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint16_t Size);

/**
 * @brief Receive data in dma mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @param pRxData pointer to Rx data buffer
 * @param Size Transmitted word count
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_Receive_DMA(SPIS_HandleTypeDef *spis, uint8_t *pRxData, uint16_t Size);

/**
 * @brief Send and receive data in dma mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @param pTxData pointer to Tx data buffer
 * @param pRxData pointer to Rx data buffer
 * @param Size Transmitted word count
 * @return HAL_StatusTypeDef 
 */
HAL_StatusTypeDef HAL_SPIS_TransmitReceive_DMA(SPIS_HandleTypeDef *spis, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);

/**
 * @brief Stop receiving data in dma mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @retval The length of the data received
 */
uint32_t HAL_SPIS_Receive_DMA_Abort(SPIS_HandleTypeDef *spis);

/**
 * @brief Stop transmit data in dma mode
 * 
 * @param spis pointer to a SPIS_HandleTypeDef structure that contains the configuration information for SPIS module.
 * @retval The length of the data transmit
 */
uint32_t HAL_SPIS_Transmit_DMA_Abort(SPIS_HandleTypeDef *spis);

void HAL_SPIS_TxCpltCallback();
void HAL_SPIS_RxCpltCallback();
void HAL_SPIS_Tx_UDR_Callback();
void HAL_SPIS_Rx_OVR_Callback();
void HAL_SPIS_DMA_TxCpltCallback();
void HAL_SPIS_DMA_RxCpltCallback();
void HAL_SPIS_DMA_TxRxCpltCallback();
void HAL_LSSPIS_IRQHandler(SPIS_HandleTypeDef* spis);

#endif