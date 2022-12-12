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
#include "platform.h"
#include "log.h"
#include "ls_dbg.h"
#include "cpu.h"
#include <string.h>
#include "co_math.h"
#include "ls_soc_gpio.h"
#include "SEGGER_RTT.h"
#include "ls_hal_spi_i2s.h"


#define LED_IO PA01

#define SPI_CLK_PIN        PB12 
#define SPI_CS_PIN         PB13 
#define SPI_MOSI_PIN       PB14 
#define SPI_MISO_PIN       PB15 

/* Size of buffer */
#define BUFFERSIZE                       COUNTOF(aTxBuffer)

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* SPI handler declaration */
static SPI_HandleTypeDef SpiHandle;

/* Buffer used for transmission */
__attribute__((aligned(2))) uint8_t aTxBuffer[] = "****SPI - Two Boards communication based on Polling ";
__attribute__((aligned(2))) uint8_t aRxBuffer[BUFFERSIZE];

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);
static uint16_t Buffercmp(uint8_t* pBuff1, uint8_t* pBuff2, uint16_t Length);

static void spi_init(void)
{
    /* Configure the GPIO AF */
    /* CLK-------------PB12 */	
    /* CS--------------PB13 */	
    /* MOSI------------PB14 */	
    /* MISO------------PB15 */	
  
    pinmux_spi2_slave_clk_init(SPI_CLK_PIN);
    pinmux_spi2_slave_nss_init(SPI_CS_PIN);
    pinmux_spi2_slave_mosi_init(SPI_MOSI_PIN);
    pinmux_spi2_slave_miso_init(SPI_MISO_PIN);
 
    /* Set the SPI parameters */
    SpiHandle.Instance               = SPI2;
    SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
    SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
    SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
    SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
    SpiHandle.Init.Mode				 = SPI_MODE_SLAVE;

    if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
    }
}

void LED_init(void)
{
    io_cfg_output(LED_IO);   //PA01 config output
    io_write_pin(LED_IO,1);  //PBA01 write high power
}

void LED_flicker(void)
{
    io_toggle_pin(LED_IO);
	DELAY_US(500*1000);
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

    uint16_t data_length = BUFFERSIZE;
    uint8_t mult_factor = 1;
    if (SpiHandle.Init.DataSize == SPI_DATASIZE_16BIT)
    {
        data_length >>= 1;
        mult_factor = sizeof(uint16_t);
    }

    for (uint8_t i = 0; i < 10; i++)
    {
        uint8_t status;
        // status = HAL_SPI_Transmit(&SpiHandle, (uint8_t*)aTxBuffer, data_length, 10000);
        // status = HAL_SPI_Receive(&SpiHandle, (uint8_t*)aRxBuffer, data_length, 10000);
        status = HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t*)aTxBuffer,(uint8_t*)aRxBuffer, data_length, 10000);
       
        switch(status)
        {
            case HAL_OK:
            /* Compare the sent and received buffers */
            if (Buffercmp((uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, data_length * mult_factor))
            {
                /* Transfer error in transmission process */
                Error_Handler();
            }
            break;

            case HAL_TIMEOUT:
            Error_Handler();
            break;

            case HAL_ERROR:
            /* Call Timeout Handler */
            Error_Handler();
            break;
            default:
            break;
        }
    }

    /* Infinite loop */
    while (1)
    {
        /* USER CODE */	
    }
}

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

static void Error_Handler(void)
{
    while (1)
    {
        LED_flicker();
    }
}
 
