/*********************************************************************************
    _     _____  _   _  _   __  _____   _____    _____   _____   _      _   _____
   | |   |_   _|| \ | || | / / |  ___| |  _  \  |  ___| |  ___| | \    / | |_   _|
   | |     | |  |  \| || |/ /  | |__   | | \  | | |___  | |__   |  \  /  |   | |
   | |     | |  | \ ` ||    \  |  __|  | |  | | |___  | |  __|  | . \/ . |   | |
   | |___ _| |_ | |\  || |\  \ | |___  | |__/ |  ___| | | |___  | |\  /| |  _| |_
   \____/ \___/ \_| \_/\_| \_/ \____/  |_____/  |_____| \____/  \_| \/ |_/ \_____/

	********************************************************************************/
/**
  ******************************************************************************
  * @file    SPI/SPI_FullDuplex_ComPolling/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use LE501x SPI HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          Polling transfer.
  *          The communication is done using 2 Boards.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#define LOG_TAG "MAIN"
#include "ls_ble.h"
#include "platform.h"
#include "prf_diss.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include "builtin_timer.h"
#include <string.h>
#include "co_math.h"
#include "io_config.h"
#include "SEGGER_RTT.h"
#include "lsspi.h"

/*
 Uncomment this line to use the board as master, if not it is used as slave */
#define MASTER_BOARD


/* Size of buffer */
#define BUFFERSIZE                       COUNTOF(aTxBuffer)

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* SPI handler declaration */
SPI_HandleTypeDef SpiHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[] = "****SPI - Two Boards communication based on Polling ";
uint8_t aRxBuffer[BUFFERSIZE];

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);


static uint16_t Buffercmp(uint8_t* pBuff1, uint8_t* pBuff2, uint16_t Length)
{
  while (Length--)
  {
    if((*pBuff1) != *pBuff2)
    {
      return Length;
    }
    pBuff1++;
    pBuff2++;
  }

  return 0;
}


static void spi_init(void)
{
  /* Configure the GPIO AF */
  /* CLK-------------PB12 */	
  /* SSN-------------PB13 */	
  /* MOSI------------PB14 */	
  /* MISO------------PB15 */	
	spi2_clk_io_init(PB12);
    spi2_nss_io_init(PB13);
    spi2_mosi_io_init(PB14);
    spi2_miso_io_init(PB15);

  /* Set the SPI parameters */
  SpiHandle.Instance               = SPI2;
  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
  SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  SpiHandle.Init.NSS               = SPI_NSS_HARD_OUTPUT;
#ifdef MASTER_BOARD
  SpiHandle.Init.Mode 						 = SPI_MODE_MASTER;
#else
  SpiHandle.Init.Mode							 = SPI_MODE_SLAVE;
#endif /* MASTER_BOARD */

  if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

void LED_init(void)
{
    io_cfg_output(PB09);   //PB09 config output
    io_write_pin(PB09,1);  //PB09 write high power
}
void LED_flicker(void)
{
    io_toggle_pin(PB09);
	DELAY_US(500000);
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

  //switch(HAL_SPI_Transmit(&SpiHandle, (uint8_t*)aTxBuffer, BUFFERSIZE, 10000) != HAL_OK)
  //switch(HAL_SPI_Receive(&SpiHandle, (uint8_t*)aRxBuffer, BUFFERSIZE, 10000))
  switch(HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t*)aTxBuffer,(uint8_t*)aRxBuffer, BUFFERSIZE, 10000))
  {
    case HAL_OK:
      /* Compare the sent and received buffers */
      if (Buffercmp((uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, BUFFERSIZE))
      {
        /* Transfer error in transmission process */
        Error_Handler();
      }
      break;

    case HAL_TIMEOUT:
    case HAL_ERROR:
      /* Call Timeout Handler */
      Error_Handler();
      break;
    default:
      break;
  }

  /* Infinite loop */
  while (1)
  {
    LED_flicker();		
  }
}

static void Error_Handler(void)
{
  while (1)
  {
		;
  }
}
 
