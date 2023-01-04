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
#include "systick.h"
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

/******************************************************************************
 Global variable declaration
 ******************************************************************************/
/* Buffer used for transmission */
// uint16_t aTxBuffer[] = {0x1234,0x5678 , 0x9ABC, 0xDEF0, 0x1234, 0x5678, 0x9ABC, 0xDEF0, 0x1234};
uint8_t aTxBuffer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
uint8_t ubNbDataToTransmit = BUFFERSIZE;
uint8_t ubTransmitIndex = 0;

/* Buffer used for reception */
uint8_t aRxBuffer[BUFFERSIZE] = {0};
uint8_t ubNbDataToReceive = BUFFERSIZE;
uint8_t ubReceiveIndex = 0;

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
  while (io_read_pin(PB15))
  {
    LED_flicker();
  }
  io_write_pin(PA09, 1); // PA09 write high power
  /*##-2- Start the Full Duplex Communication process ########################*/
  /* Enable SPI before start transmission */
  LL_SPI_Enable(SPI2);

  while (ubNbDataToReceive > 0)
  {
    if ((LL_SPI_IsActiveFlag(SPI2, SPI_FLAG_TXE)) && (ubNbDataToTransmit > 0))
    {
      /* Transmit 8bit Data */
      LL_SPI_TransmitData8(SPI2, aTxBuffer[ubTransmitIndex++]);
      ubNbDataToTransmit--;
    }
  }

#else

  /*##-2- Start the Full Duplex Communication process ########################*/
  /* Enable SPI before start transmission */
  LL_SPI_Enable(SPI2);

  while (ubNbDataToReceive > 0)
  {
    /* Check RXE flag */
    if (LL_SPI_IsActiveFlag(SPI2, SPI_FLAG_RXNE))
    {
      /* Receive 8bit Data */
      aRxBuffer[ubReceiveIndex++] = LL_SPI_ReceiveData8(SPI2);
      ubNbDataToReceive--;
    }
  }
#endif /* MASTER_BOARD */

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
  for (uint8_t i = 0; i < COUNTOF(aTxBuffer); i++)
  {
    LOG_I("%d", aRxBuffer[i]);
  }
  /* Infinite loop */
  while (1)
  {
  }
}

/**
 * @brief Error handler
 *
 */
static void Error_Handler(void)
{
  for (uint8_t i = 0; i < COUNTOF(aTxBuffer); i++)
  {
    LOG_I("%d", aRxBuffer[i]);
  }
  while (1)
  {
    ;
  }
}
