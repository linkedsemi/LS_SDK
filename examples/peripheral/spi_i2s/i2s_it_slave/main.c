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
  * @file    I2S/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use I2S HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          interrupt transfer.
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

#define     I2S_CK_PIN        PB12 
#define     I2S_WS_PIN        PB13 
#define     I2S_SD_PIN        PB14 
#define     I2S_MCK_PIN       PB15 

enum {
	COM_WAIT,
	COM_COMPLETE
};

#define     BUFFERSIZE        32
/* I2S handler declaration */
static I2S_HandleTypeDef I2sHandle;

/* Buffer used for transmission */
uint16_t aTxBuffer[BUFFERSIZE];
uint16_t aRxBuffer[BUFFERSIZE];
static void Error_Handler(void);
static uint16_t Buffercmp(uint16_t* pBuff1, uint16_t* pBuff2, uint16_t Length);
void LED_init(void)
{
    io_cfg_output(LED_IO);   
    io_write_pin(LED_IO,1); 
}

void LED_flicker(void)
{
    io_toggle_pin(LED_IO);
	DELAY_US(500*1000);
}

volatile uint32_t ComState = COM_WAIT;

static void i2s_init(void)
{
    /* Configure the GPIO AF */
    /* CK--------------PB12 */	
    /* WS--------------PB13 */	
    /* SD--------------PB14 */	
    /* MCK-------------PB15 */

    pinmux_iis2_slave_ck_init(I2S_CK_PIN);
    pinmux_iis2_slave_ws_init(I2S_WS_PIN);
    pinmux_iis2_slave_sd_init(I2S_SD_PIN, 0); 
    pinmux_iis2_slave_mck_init(I2S_MCK_PIN);

    I2sHandle.Instance                  = SPI2;
    I2sHandle.Init.Mode                 = I2S_MODE_SLAVE_RX;
    I2sHandle.Init.Standard             = I2S_STANDARD_PCM_LONG;
    I2sHandle.Init.DataFormat           = I2S_DATAFORMAT_16BIT;
    I2sHandle.Init.MCLKOutput           = I2S_MCLKOUTPUT_DISABLE;
    I2sHandle.Init.OddPrescaler         = I2S_ODDPRESCALER_DEFAULT;
    I2sHandle.Init.DivPrescaler         = I2S_DIVPRESCALER_DEFAULT;
    I2sHandle.Init.CPOL                 = I2S_CPOL_LOW;
    HAL_I2S_Init(&I2sHandle);
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
    /* init I2S and GPIO   */
    i2s_init();
    LED_init();

    for (uint8_t i = 0; i < BUFFERSIZE; i++)
    {
        aTxBuffer[i] = i;
    } 

    for (uint8_t i = 0; i < 10; i++)
    {
        ComState = COM_WAIT;
        HAL_I2S_Receive_IT(&I2sHandle, (uint16_t *)aRxBuffer, BUFFERSIZE);
        while(ComState != COM_COMPLETE);
    }
    LOG_I("receive success!---");

    /* Infinite loop */
    while (1)
    {
        /* USER CODE */	
    }
}


void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    ComState = COM_COMPLETE;
    if (Buffercmp((uint16_t *)aTxBuffer, (uint16_t *)aRxBuffer, BUFFERSIZE))
    {
        Error_Handler();
    }
}

static uint16_t Buffercmp(uint16_t* pBuff1, uint16_t* pBuff2, uint16_t Length)
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
