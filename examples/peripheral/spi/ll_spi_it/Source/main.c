/******************************************************************************
 Include
 ******************************************************************************/
#define LOG_TAG "MAIN"
#include "platform.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include <string.h>
#include "co_math.h"
#include "ls_soc_gpio.h"
#include "SEGGER_RTT.h"
#include "ls_hal_spi_i2s.h"
/******************************************************************************
 Macro definition
 ******************************************************************************/
/* Uncomment this line to use the board as master, if not it is used as slave */
#define MASTER_BOARD 0

#define BUFFERSIZE COUNTOF(aTxBuffer)
#define COUNTOF(__BUFFER__) (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/******************************************************************************
 Function declaration
 ******************************************************************************/
static void Error_Handler(void);
void LL_SPI_TxCpltCallback(void);
void LL_SPI_RxCpltCallback(void);
uint32_t LL_SPI_Transmit_IT(reg_spi_t *SPIx, uint8_t *pData, uint16_t Size);
uint32_t LL_SPI_Receive_IT(reg_spi_t *SPIx, uint8_t *pData, uint16_t Size);


/******************************************************************************
 Global variable declaration
 ******************************************************************************/
/* transfer state */
enum
{
  COM_WAIT,
  COM_COMPLETE,
  COM_ERROR
};
volatile uint32_t ComState = COM_WAIT;

/* Buffer used for transmission */
// uint16_t aTxBuffer[] = {0x1234,0x5678 , 0x9ABC, 0xDEF0, 0x1234, 0x5678, 0x9ABC, 0xDEF0, 0x1234};
uint8_t aTxBuffer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

/* Buffer used for reception */
uint8_t aRxBuffer[BUFFERSIZE];

/*Transfer data cache and data size*/
volatile uint8_t *qBuf;
volatile uint8_t DataOfSize;

#if MASTER_BOARD 
#else
/**
 * @brief Data comparison function
 * 
 * @param pBuff1 Data for comparison 
 * @param pBuff2 Data for comparison 
 * @param Length The length of the data
 * @return uint16_t 
 */
static uint16_t Buffercmp(uint8_t *pBuff1, uint8_t *pBuff2, uint16_t Length)
{
  while (Length--)
  {
    if ((*pBuff1) != *pBuff2)
    {
      return Length;
    }
    pBuff1++;
    pBuff2++;
  }

  return 0;
}
#endif /* MASTER_BOARD */

/**
 * @brief spi Initialization function
 * 
 */
static void spi_init(void)
{
  /* Configure the GPIO AF */
  /* CLK-------------PA00 */
  /* SSN-------------PA01 */
  /* MOSI------------PA02 */
  /* MISO------------PA03 */

#if MASTER_BOARD
  pinmux_spi2_master_clk_init(PA00);
  pinmux_spi2_master_nss_init(PA01);
  pinmux_spi2_master_mosi_init(PA02);
  pinmux_spi2_master_miso_init(PA03);

#else
  pinmux_spi2_slave_clk_init(PB12);
  pinmux_spi2_slave_nss_init(PB13);
  pinmux_spi2_slave_mosi_init(PB14);
  pinmux_spi2_slave_miso_init(PB15);

#endif /* MASTER_BOARD */

  LL_SPI2_MSP_Init();
  clr_pending_irq(SPI2_IRQn);
  enable_irq(SPI2_IRQn);
  /* Set the SPI parameters */
  LOG_I("clk init\n");
  LL_SPI_Disable(SPI2);
  LL_SPI_SetTransferDirection(SPI2, LL_SPI_FULL_DUPLEX);
  LL_SPI_SetClockPolarity(SPI2, LL_SPI_POLARITY_HIGH);
  LL_SPI_SetClockPhase(SPI2, LL_SPI_PHASE_2EDGE);
  LL_SPI_SetBaudRatePrescaler(SPI2, LL_SPI_BAUDRATEPRESCALER_256);
  LL_SPI_SetTransferBitOrder(SPI2, LL_SPI_MSB_FIRST);
#if MASTER_BOARD
  LL_SPI_SetMode(SPI2, LL_SPI_MODE_MASTER);

#else
  LL_SPI_SetMode(SPI2, LL_SPI_MODE_SLAVE);

#endif /* MASTER_BOARD */
  LL_SPI_SetNSSMode(SPI2, LL_SPI_NSS_HARD_OUTPUT);
  LL_SPI_SetDataSize(SPI2, LL_SPI_DATASIZE_8BIT);
}

void LED_init(void)
{
  io_cfg_output(PA09);   // PA09 config output
  io_write_pin(PA09, 1); // PA09 write high power
  io_pull_write(PB15, IO_PULL_UP);
  io_cfg_input(PB15);
}
void LED_flicker(void)
{
  io_toggle_pin(PA09);
  DELAY_US(100000);
}

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
  /* system init app     */
  sys_init_none();
  /* init spi and GPIO   */
  spi_init();
  LED_init();

#if MASTER_BOARD
  /* Configure User push-button button */

  /* Wait for User push-button press before starting the Communication */
  // while (io_read_pin(PB15))
  // {
  //   LED_flicker();
  // }
  io_write_pin(PA09, 1); // PA09 write high power
  /*##-2- Start the Full Duplex Communication process ########################*/

  if (LL_SPI_Transmit_IT(SPI2, (uint8_t *)aTxBuffer, BUFFERSIZE) != SUCCESS)
  {
    /* Transfer error in transmission process */
    Error_Handler();
  }
#else
  if (LL_SPI_Receive_IT(SPI2, (uint8_t *)aRxBuffer, BUFFERSIZE) != SUCCESS)
  {
    /* Transfer error in transmission process */
    Error_Handler();
  }
  while (ComState == COM_WAIT)
  {
  }

  switch (ComState)
  {
  case COM_COMPLETE:
    /*##-3- Compare the sent and received buffers ##############################*/
    /* Compare the sent and received buffers */
    if (Buffercmp((uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, COUNTOF(aTxBuffer)))
    {
      /* Transfer error in transmission process */
      Error_Handler();
    }
    else
    {
      /* Turn LED2 on: Transfer in transmission/Reception process is correct */
      io_write_pin(PA09, 0); // PA09 write high power
    }
    break;
  default:
    Error_Handler();
    break;
  }
    for (int i = 0; i < BUFFERSIZE; i++)
  {
    LOG_I("%d", aRxBuffer[i]);
  }
#endif /* MASTER_BOARD */

  /* Infinite loop */
  while (1)
  {
  }
}

/**
 * @brief Data sending function
 * @param  SPIx SPI Instance
 * @param pData Data to be sent
 * @param Size Data length
 * @return uint32_t 
 */
uint32_t LL_SPI_Transmit_IT(reg_spi_t *SPIx, uint8_t *pData, uint16_t Size)
{
  if ((pData == NULL) || (Size == 0U))
  {
    return ERROR;
  }
  /* Set the transaction information */
  qBuf = pData;
  DataOfSize = Size;

  LL_SPI_ClearFlagIT(SPI2, SPI_ITIC_TXE | SPI_ITIC_OVR | SPI_ITIC_MODF);
  LL_I2S_EnableIT(SPI2, SPI_ITEN_TXE | SPI_ITEN_OVR | SPI_ITEN_MODF);

  /* Check if the SPI is already enabled */
  /* Enable SPI peripheral */
  LL_SPI_Enable(SPI2);

  /* Transmit and Receive data in 16 Bit mode */
  LL_SPI_TransmitData8(SPI2, *qBuf);
  DataOfSize--;
  qBuf++;

  return SUCCESS;
}

/**
 * @brief Receiving data function
 * @param  SPIx SPI Instance
 * @param pData Received data
 * @param Size  Data length
 * @return uint32_t 
 */
uint32_t LL_SPI_Receive_IT(reg_spi_t *SPIx, uint8_t *pData, uint16_t Size)
{
  if ((pData == NULL) || (Size == 0U))
  {
    return ERROR;
  }
  /* Set the transaction information */
  qBuf = pData;
  DataOfSize = Size;
  LL_SPI_ClearFlagIT(SPI2, SPI_ITIC_RXNE | SPI_ITIC_OVR | SPI_ITIC_MODF);
  LL_I2S_EnableIT(SPI2, SPI_ITEN_RXNE | SPI_ITEN_OVR | SPI_ITEN_MODF);
  /* Enable SPI peripheral */
  LL_SPI_Enable(SPI2);

  return SUCCESS;
}

/**
 * @brief Send the callback function
 * 
 */
void LL_SPI_TxCpltCallback(void)
{
  DataOfSize--;
  LL_SPI_TransmitData8(SPI2, *qBuf);
  qBuf++;
  if (DataOfSize == 0)
  {
    LL_SPI_DisableIT(SPI2, SPI_ITDEN_RXNE);
    LL_SPI_DisableIT(SPI2, SPI_ITDEN_TXE);
    ComState = COM_COMPLETE;
  }
}

/**
 * @brief Receive the callback function
 * 
 */
void LL_SPI_RxCpltCallback(void)
{
  DataOfSize--;
  *qBuf = LL_SPI_ReceiveData8(SPI2);
#if LM3050 
  DELAY_US(50);
#endif
  qBuf++;
  if (DataOfSize == 0)
  {
    LL_SPI_DisableIT(SPI2, SPI_ITDEN_RXNE);
    LL_SPI_DisableIT(SPI2, SPI_ITDEN_TXE);
    ComState = COM_COMPLETE;
  }
}

/**
 * @brief Error handler
 * 
 */
static void Error_Handler(void)
{
  while (1)
  {
    ;
  }
}
