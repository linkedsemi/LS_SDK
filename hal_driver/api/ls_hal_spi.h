#ifndef LS_HAL_SPI_H_
#define LS_HAL_SPI_H_
#include <stdbool.h>
#include "ls_ll_spi.h"
#include "HAL_def.h"
#include "ls_msp_spi.h"
#include "field_manipulate.h"
#include "log.h"
#include "systick.h"
#include "ls_dbg.h"
#include "common.h"


/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSSPI
 *  @{
 */

/**
  * @brief  SPI Configuration Structure definition
  */
typedef struct
{
  uint32_t Mode;                /*!< Specifies the SPI operating mode.
                                     This parameter can be a value of @ref SPI_Mode */

  uint32_t DataSize;            /*!< Specifies the SPI data size.
                                     This parameter can be a value of @ref SPI_Data_Size */

  uint32_t CLKPolarity;         /*!< Specifies the serial clock steady state.
                                     This parameter can be a value of @ref SPI_Clock_Polarity */

  uint32_t CLKPhase;            /*!< Specifies the clock active edge for the bit capture.
                                     This parameter can be a value of @ref SPI_Clock_Phase */

  uint32_t BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                     used to configure the transmit and receive SCK clock.
                                     This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                     @note The communication clock is derived from the master
                                     clock. The slave clock does not need to be set. */

  uint32_t FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                     This parameter can be a value of @ref SPI_MSB_LSB_transmission */

  uint32_t TIMode;              /*!< Specifies if the TI mode is enabled or not.
                                     This parameter can be a value of @ref SPI_TI_mode */
} SPI_InitTypeDef;
/**
  * @}
  */

/**
  * @brief  SPI Interrupt Environment
  */
struct Interrupt_Env
{
  uint8_t                    *pBuffPtr;                     /*!< Pointer to SPI transfer Buffer */
  uint16_t              	 Count;                         /*!< SPI Transfer Counter           */
  void (*transfer_Fun)(struct __SPI_HandleTypeDef *hspi);   /*!< function pointer on Rx_Fun     */
};

/**
  * @brief  SPI DMA Environment
  */
struct SPI_DMA_Env
{
    uint8_t DMA_Channel;
    uint8_t dummy;
};

/**
  * @brief  SPI handle Structure definition
  */
typedef struct __SPI_HandleTypeDef
{
  reg_spi_t               	 *Instance;      /*!< SPI registers base address               */
  SPI_InitTypeDef            Init;           /*!< SPI communication parameters             */
  void                       *DMAC_Instance;
  union{
        struct Interrupt_Env Interrupt;
        struct SPI_DMA_Env      DMA;
  }Tx_Env,Rx_Env;
} SPI_HandleTypeDef;
/**
  * @}
  */

/** @defgroup SPI_Error_Code SPI Error Code
  * @{
  */
#define HAL_SPI_ERROR_NONE              (0x00000000U)   /*!< No error                               */
#define HAL_SPI_ERROR_MODF              (0x00000001U)   /*!< MODF error                             */
#define HAL_SPI_ERROR_CRC               (0x00000002U)   /*!< CRC error                              */
#define HAL_SPI_ERROR_OVR               (0x00000004U)   /*!< OVR error                              */
#define HAL_SPI_ERROR_DMA               (0x00000010U)   /*!< DMA transfer error                     */
#define HAL_SPI_ERROR_FLAG              (0x00000020U)   /*!< Error on RXNE/TXE/BSY Flag             */
#define HAL_SPI_ERROR_ABORT             (0x00000040U)   /*!< Error during SPI Abort procedure       */
/**
  * @}
  */

/** @defgroup SPI_Mode SPI Mode
  * @{
  */
#define SPI_MODE_SLAVE                  (0x00000000U)                           /*!< The mode is slave      */
#define SPI_MODE_MASTER                 (SPI_CR1_MSTR_MASK | SPI_CR1_SSI_MASK)  /*!< The mode is master     */
/**
  * @}
  */

/** @defgroup SPI_Data_Size SPI Data Size
  * @{
  */
#define SPI_DATASIZE_8BIT               (0x00000007U<<SPI_CR2_DS_POS)   /*!< The SPI Data Size is 8BIT     */
#define SPI_DATASIZE_16BIT              SPI_CR2_DS_MASK                 /*!< The SPI Data Size is 16BIT    */
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
  * @{
  */
#define SPI_POLARITY_LOW                (0x00000000U)       /*!< The SPI Clock Polarity is LOW    */
#define SPI_POLARITY_HIGH               SPI_CR1_CPOL_MASK   /*!< The SPI Clock Polarity is HIGH   */
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase SPI Clock Phase
  * @{
  */
#define SPI_PHASE_1EDGE                 (0x00000000U)       /*!< The SPI Clock Phase is 1 edge    */
#define SPI_PHASE_2EDGE                 SPI_CR1_CPHA_MASK   /*!< The SPI Clock Phase is 2 edge    */
/**
  * @}
  */

/** @defgroup SPI_BaudRate_Prescaler SPI BaudRate Prescaler
  * @{
  */
#define SPI_BAUDRATEPRESCALER_8         (0x00000002<<SPI_CR1_BR_POS)    /*!< The BaudRate is 8 frequency of the SPI clock   */
#define SPI_BAUDRATEPRESCALER_16        (0x00000003<<SPI_CR1_BR_POS)    /*!< The BaudRate is 16 frequency of the SPI clock  */
#define SPI_BAUDRATEPRESCALER_32        (0x00000004<<SPI_CR1_BR_POS)    /*!< The BaudRate is 32 frequency of the SPI clock  */
#define SPI_BAUDRATEPRESCALER_64        (0x00000005<<SPI_CR1_BR_POS)    /*!< The BaudRate is 64 frequency of the SPI clock  */
#define SPI_BAUDRATEPRESCALER_128       (0x00000006<<SPI_CR1_BR_POS)    /*!< The BaudRate is 128 frequency of the SPI clock */
#define SPI_BAUDRATEPRESCALER_256       (0x00000007<<SPI_CR1_BR_POS)    /*!< The BaudRate is 256 frequency of the SPI clock */
/**
  * @}
  */

/** @defgroup SPI_MSB_LSB_transmission SPI MSB LSB Transmission
  * @{
  */
#define SPI_FIRSTBIT_MSB                (0x00000000U)           /*!< SPI MSB Transmission  */
#define SPI_FIRSTBIT_LSB                SPI_CR1_LSBFIRST_MASK   /*!< SPI LSB Transmission  */
/**
  * @}
  */

/** @defgroup SPI_TI_mode SPI TI Mode
  * @{
  */
#define SPI_TIMODE_DISABLE              (0x00000000U)
/**
  * @}
  */

/** @defgroup SPI_Interrupt_definition SPI Interrupt Definition
  * @{
  */
#define SPI_IT_TXE                      SPI_IER_TXEIE_MASK                                                  /*!< SPI TX Interrupt Definition  */
#define SPI_IT_RXNE                     SPI_IER_RXNEIE_MASK                                                 /*!< SPI RX Interrupt Definition  */
#define SPI_IT_ERR                      (SPI_IFM_MODFFM_MASK | SPI_IFM_OVRFM_MASK | SPI_IFM_UDRFM_MASK \
                                         | SPI_IFM_CRCERRFM_MASK | SPI_IFM_FREFM_MASK)                      /*!< SPI ERR Interrupt Definition  */
/**
  * @}
  */

/* Initialization/de-initialization functions  ********************************/
/**
  * @brief  Initialize the SPI according to the specified parameters
  *         in the SPI_InitTypeDef and initialize the associated handle.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);

/**
  * @brief  De-Initialize the SPI peripheral.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi);

/**
  * @brief  Initialize the SPI MSP.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);

/**
  * @brief  De-Initialize the SPI MSP.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);

/**
  * @brief  Transmit an amount of data in blocking mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData pointer to data buffer
  * @param  Size amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pRxData pointer to data buffer
  * @param  Size amount of data to be received
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pRxData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Transmit and Receive an amount of data in blocking mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData pointer to transmission data buffer
  * @param  pRxData pointer to reception data buffer
  * @param  Size amount of data to be sent and received
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
                                          uint32_t Timeout);

/**
  * @brief  Transmit an amount of data in non-blocking mode with Interrupt.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData pointer to data buffer
  * @param  Size amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint16_t Size);

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pRxData pointer to data buffer
  * @param  Size amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pRxData, uint16_t Size);

/**
  * @brief  Transmit and Receive an amount of data in non-blocking mode with Interrupt.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  pTxData pointer to transmission data buffer
  * @param  pRxData pointer to reception data buffer
  * @param  Size amount of data to be sent and received
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData,
                                             uint16_t Size);

/**
  * @brief  Transmit an amount of data in DMA mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains.
  *               the configuration information for SPI module.
  * @param  Data pointer to data buffer.
  * @param  Count amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi,void *Data,uint16_t Count);

/**
  * @brief  Receive an amount of data in DMA mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  Data pointer to data buffer.
  * @param  Count amount of data to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi,void *Data,uint16_t Count);

/**
  * @brief  Transmit and Receive an amount of data in DMA mode.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @param  TX_Data pointer to transmission data buffer.
  * @param  RX_Data pointer to reception data buffer.
  * @param  Count amount of data to be sent and received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi,void *TX_Data,void *RX_Data,uint16_t Count);

/**
  * @brief  This function handles SPI interrupt request.
  * @param  hspi  Pointer to a SPI_HandleTypeDef structure that contains
  *                the configuration information for the specified SPI module.
  * @retval None
  */
void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi);

/**
  * @brief  Transfer completed callback.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_CpltCallback(SPI_HandleTypeDef *hspi);

/**
  * @brief  Transfer completed callback in DMA.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_DMACpltCallback(SPI_HandleTypeDef *hspi);

#endif

/************************ (C) COPYRIGHT linkedsemi *************END OF FILE****/
