#ifndef LS_HAL_SPI_H_
#define LS_HAL_SPI_H_
#include <stdbool.h>
#include "ls_ll_spi.h"
#include "HAL_def.h"
#include "ls_msp_spi_i2s.h"
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
  * @brief  Interrupt Environment
  */
struct Interrupt_Env
{
  uint8_t                    *pBuffPtr;                         /*!< Pointer to transfer Buffer */
  uint16_t              	 Count;                             /*!< SPI Transfer Counter */
  void (*transfer_Fun)(struct __SPI_HandleTypeDef *hspi);       /*!< function pointer on transfer_Fun */
  void (*i2s_transfer_Fun)(struct __I2S_HandleTypeDef *hi2s);   /*!< function pointer on transfer_Fun */
};

/**
  * @brief  DMA Environment
  */
struct DMA_Env
{
  uint8_t DMA_Channel;
  uint8_t dummy;
};

/**
  * @brief SPI handle Structure definition
  */
typedef struct __SPI_HandleTypeDef
{
  reg_spi_t               	 *Instance;      /*!< SPI registers base address               */

  SPI_InitTypeDef            Init;           /*!< SPI communication parameters             */

  void                       *DMAC_Instance;

  union{
        struct Interrupt_Env  Interrupt;         /*!< Interrupt Env  */
        struct DMA_Env        DMA;               /*!< DMA Env  */
  }Tx_Env,Rx_Env;                                /*!< Tx Rx Environment */

} SPI_HandleTypeDef;
/**
  * @}
  */

 /**
  * @brief I2S Init structure definition
  */
typedef struct
{
  uint32_t Mode;                /*!< Specifies the I2S operating mode.
                                     This parameter can be a value of @ref I2S_Mode */

  uint32_t Standard;            /*!< Specifies the standard used for the I2S communication.
                                     This parameter can be a value of @ref I2S_Standard */

  uint32_t DataFormat;          /*!< Specifies the data format for the I2S communication.
                                     This parameter can be a value of @ref I2S_Data_Format */

  uint32_t MCLKOutput;          /*!< Specifies whether the I2S MCLK output is enabled or not.
                                     This parameter can be a value of @ref I2S_MCLK_Output */

  uint32_t OddPrescaler;        /*!< Specifies the Odd factor prescaler for the I2S communication.
                                     This parameter can be a value of @ref I2S_Odd_Prescaler */
                            
  uint32_t DivPrescaler;        /*!< Specifies the I2S linear prescaler for the I2S communication.
                                     This parameter can be a value of @ref I2S_Div_Prescaler */

  uint32_t CPOL;                /*!< Specifies the idle state of the I2S clock.
                                     This parameter can be a value of @ref I2S_Clock_Polarity */
} I2S_InitTypeDef;

/**
  * @brief I2S handle Structure definition
  */
typedef struct __I2S_HandleTypeDef
{
  reg_spi_t                 *Instance;     /*!< I2S registers base address  */

  I2S_InitTypeDef            Init;         /*!< I2S communication parameters */

  void                       *DMAC_Instance;    /*!< I2S DMA Instance  */

  union{
        struct Interrupt_Env  Interrupt;         /*!< Interrupt Env  */
        struct DMA_Env        DMA;               /*!< DMA Env  */
  }Tx_Env,Rx_Env;                                /*!< Tx Rx Environment */

} I2S_HandleTypeDef;

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
#define SPI_IT_ERR                      (SPI_IER_FREIE_MASK | SPI_IER_OVRIE_MASK | SPI_IER_MODFIE_MASK \
                                         | SPI_IER_CRCERRIE_MASK | SPI_IER_UDRIE_MASK)                      /*!< SPI ERR Interrupt Definition  */
/**
  * @}
  */

 /** @defgroup I2S_Mode I2S Mode
  * @{
  */
#define I2S_MODE_SLAVE_TX                (0x00000000U)
#define I2S_MODE_SLAVE_RX                (0x1UL << SPI_I2SCFGR_I2SCFG_POS)
#define I2S_MODE_MASTER_TX               (0x2UL << SPI_I2SCFGR_I2SCFG_POS)
#define I2S_MODE_MASTER_RX               (0x3UL << SPI_I2SCFGR_I2SCFG_POS)
/**
  * @}
  */

/** @defgroup I2S_Standard I2S Standard
  * @{
  */
#define I2S_STANDARD_PHILIPS             (0x00000000U)
#define I2S_STANDARD_MSB                 (0x1UL << SPI_I2SCFGR_I2SSTD_POS)
#define I2S_STANDARD_LSB                 (0x2UL << SPI_I2SCFGR_I2SSTD_POS)
#define I2S_STANDARD_PCM_SHORT           (0x3UL << SPI_I2SCFGR_I2SSTD_POS)
#define I2S_STANDARD_PCM_LONG            (0x3UL << SPI_I2SCFGR_I2SSTD_POS | SPI_I2SCFGR_PCMSYNC_MASK)
/**
  * @}
  */

/** @defgroup I2S_Data_Format I2S Data Format
  * @{
  */
#define I2S_DATAFORMAT_16BIT               (0x00000000U)
#define I2S_DATAFORMAT_16BIT_EXTENDED      (SPI_I2SCFGR_CHLEN_MASK)
#define I2S_DATAFORMAT_24BIT               (SPI_I2SCFGR_CHLEN_MASK | 0x1UL << SPI_I2SCFGR_DATLEN_POS)
#define I2S_DATAFORMAT_32BIT               (SPI_I2SCFGR_CHLEN_MASK | 0x2UL << SPI_I2SCFGR_DATLEN_POS)
/**
  * @}
  */

/** @defgroup I2S_MCLK_Output I2S MCLK Output
  * @{
  */
#define I2S_MCLKOUTPUT_ENABLE            (SPI_I2SPR_MCKOE_MASK)
#define I2S_MCLKOUTPUT_DISABLE           (0x00000000U)
/**
  * @}
  */

/** @defgroup I2S_Div_Prescaler I2S Default Div Prescaler Frequency
  * @{
  */
#define I2S_DIVPRESCALER_DEFAULT            (64U)
/**
  * @}
  */

 /** @defgroup I2S_Odd_Prescaler I2S Default Odd Prescaler Frequency
  * @{
  */
#define I2S_ODDPRESCALER_DEFAULT            (0U)
/**
  * @}
  */

/** @defgroup I2S_Clock_Polarity I2S Clock Polarity
  * @{
  */
#define I2S_CPOL_LOW                     (0x00000000U)
#define I2S_CPOL_HIGH                    (SPI_I2SCFGR_CKPOL_MASK)
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
void HAL_SPI_MSP_Init(SPI_HandleTypeDef *hspi);

/**
  * @brief  De-Initialize the SPI MSP.
  * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
  *               the configuration information for SPI module.
  * @retval None
  */
void HAL_SPI_MSP_DeInit(SPI_HandleTypeDef *hspi);

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
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);

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

/**
  * @brief  Initializes the I2S according to the specified parameters
  *         in the I2S_InitTypeDef and create the associated handle.
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Init(I2S_HandleTypeDef *hi2s);

/**
  * @brief DeInitializes the I2S peripheral
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_DeInit(I2S_HandleTypeDef *hi2s);

/**
  * @brief  Transmit an amount of data in blocking mode
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param  pTxData a 16-bit pointer to data buffer.
  * @param  Size number of data sample to be sent:
  * @note   When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *         configuration phase, the Size parameter means the number of 16-bit data length
  *         in the transaction and when a 24-bit data frame or a 32-bit data frame is selected
  *         the Size parameter means the number of 24-bit or 32-bit data length.
  * @param  Timeout Timeout duration
  * @note   The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization
  *         between Master and Slave(example: audio streaming).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Transmit(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Receive an amount of data in blocking mode
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param  pRxData a 16-bit pointer to data buffer.
  * @param  Size number of data sample to be sent:
  * @note   When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *         configuration phase, the Size parameter means the number of 16-bit data length
  *         in the transaction and when a 24-bit data frame or a 32-bit data frame is selected
  *         the Size parameter means the number of 24-bit or 32-bit data length.
  * @param  Timeout Timeout duration
  * @note   The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization
  *         between Master and Slave(example: audio streaming).
  * @note   In I2S Master Receiver mode, just after enabling the peripheral the clock will be generate
  *         in continuous way and as the I2S is not disabled at the end of the I2S transaction.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Receive(I2S_HandleTypeDef *hi2s, uint16_t *pRxData, uint16_t Size, uint32_t Timeout);

/**
  * @brief  Transmit an amount of data in non-blocking mode with Interrupt
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param  pTxData a 16-bit pointer to data buffer.
  * @param  Size number of data sample to be sent:
  * @note   When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *         configuration phase, the Size parameter means the number of 16-bit data length
  *         in the transaction and when a 24-bit data frame or a 32-bit data frame is selected
  *         the Size parameter means the number of 24-bit or 32-bit data length.
  * @note   The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization
  *         between Master and Slave(example: audio streaming).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Transmit_IT(I2S_HandleTypeDef *hi2s, uint16_t *pTxData, uint16_t Size);

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @param  pRxData a 16-bit pointer to the Receive data buffer.
  * @param  Size number of data sample to be sent:
  * @note   When a 16-bit data frame or a 16-bit data frame extended is selected during the I2S
  *         configuration phase, the Size parameter means the number of 16-bit data length
  *         in the transaction and when a 24-bit data frame or a 32-bit data frame is selected
  *         the Size parameter means the number of 24-bit or 32-bit data length.
  * @note   The I2S is kept enabled at the end of transaction to avoid the clock de-synchronization
  *         between Master and Slave(example: audio streaming).
  * @note   It is recommended to use DMA for the I2S receiver to avoid de-synchronization
  * between Master and Slave otherwise the I2S interrupt should be optimized.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Receive_IT(I2S_HandleTypeDef *hi2s, uint16_t *pRxData, uint16_t Size);

/**
  * @brief  Transmit an amount of data in DMA mode.
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains.
  *               the configuration information for I2S module.
  * @param  Data pointer to data buffer.
  * @param  Count amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Transmit_DMA(I2S_HandleTypeDef *hi2s, void *Data, uint16_t Count);

/**
  * @brief  Receive an amount of data in DMA mode.
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *               the configuration information for I2S module.
  * @param  Data pointer to data buffer.
  * @param  Count amount of data to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_I2S_Receive_DMA(I2S_HandleTypeDef *hi2s, void *Data, uint16_t Count);

/**
  * @brief  This function handles I2S interrupt request.
  * @param  hi2s: pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
void HAL_I2S_IRQHandler(I2S_HandleTypeDef *hi2s);

/**
  * @brief  Tx Transfer completed callbacks
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s);

/**
  * @brief  Rx Transfer completed callbacks
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s);

/**
  * @brief  Transfer completed callback in DMA.
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *               the configuration information for I2S module.
  * @retval None
  */
void HAL_I2S_TxDMACpltCallback(I2S_HandleTypeDef *hi2s);

/**
  * @brief  Transfer completed callback in DMA.
  * @param  hi2s pointer to a I2S_HandleTypeDef structure that contains
  *               the configuration information for I2S module.
  * @retval None
  */
void HAL_I2S_RxDMACpltCallback(I2S_HandleTypeDef *hi2s);

#endif

/************************ (C) COPYRIGHT linkedsemi *************END OF FILE****/
