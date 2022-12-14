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
  * @file    SPI/SPI_IT/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use LE501x SPI HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          INT transfer.
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

#define SPI_CS_LOW()      io_write_pin(SPI_CS_PIN,0);
#define SPI_CS_HIGH()     io_write_pin(SPI_CS_PIN,1);

enum {
	COM_WAIT,
	COM_COMPLETE
};

/* Size of buffer */
#define BUFFERSIZE                       COUNTOF(aTxBuffer)

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* SPI handler declaration */
SPI_HandleTypeDef SpiHandle;

/* Buffer used for transmission */
__attribute__((aligned(2))) uint8_t aTxBuffer[] = "****SPI - Two Boards communication based on IT ";

/* Buffer used for reception */
__attribute__((aligned(2))) uint8_t aRxBuffer[BUFFERSIZE];

/* transfer state */
volatile uint32_t ComState = COM_WAIT;

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);
static uint16_t Buffercmp(uint8_t* pBuff1, uint8_t* pBuff2, uint16_t Length);

static void spi2_master_cs_init(uint8_t cs)
{
    io_set_pin(cs);
    io_pull_write(cs,IO_PULL_UP);
    io_cfg_output(cs);
}

static void spi_init(void)
{
    /* Configure the GPIO AF */
    /* CLK-------------PB12 */	
    /* CS--------------PB13 */	
    /* MOSI------------PB14 */	
    /* MISO------------PB15 */	
	
    pinmux_spi2_master_clk_init(SPI_CLK_PIN);
    pinmux_spi2_master_mosi_init(SPI_MOSI_PIN); 
    pinmux_spi2_master_miso_init(SPI_MISO_PIN);
    spi2_master_cs_init(SPI_CS_PIN);

    /* Set the SPI parameters */
    SpiHandle.Instance               = SPI2;
    SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
    SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
    SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
    SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
    SpiHandle.Init.Mode 			 = SPI_MODE_MASTER;

    if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
    }
}

void LED_init(void)
{
    io_cfg_output(LED_IO);   //PA01 config output
    io_write_pin(LED_IO,1);  //PA01  write high
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

    for (uint8_t i = 0; i < 10; i++)
    {
        ComState = COM_WAIT;
        SPI_CS_LOW();
        // if(HAL_SPI_Transmit_IT(&SpiHandle, (uint8_t*)aTxBuffer, BUFFERSIZE) != HAL_OK)
        // if(HAL_SPI_Receive_IT(&SpiHandle, (uint8_t*)aRxBuffer, BUFFERSIZE) != HAL_OK)
        if(HAL_SPI_TransmitReceive_IT(&SpiHandle, (uint8_t*)aTxBuffer, (uint8_t *)aRxBuffer, BUFFERSIZE) != HAL_OK)
        {
            /* Transfer error in transmission process */
            Error_Handler();
        }

        while(ComState != COM_COMPLETE);
        switch(ComState)
        {
            case COM_COMPLETE :
            if(Buffercmp((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, BUFFERSIZE))
            {
                /* Processing Error */
                Error_Handler();     
            }
            break;
            default : 
            Error_Handler();
            break;
        }
        DELAY_US(100*1000);
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

void HAL_SPI_CpltCallback(SPI_HandleTypeDef *hspi)
{
    SPI_CS_HIGH();
    /* Turn LED on: Transfer in transmission/reception process is correct */
    io_set_pin(LED_IO);
    ComState = COM_COMPLETE;
}
