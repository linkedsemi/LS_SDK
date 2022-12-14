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

volatile uint32_t ComState = COM_WAIT;

static void i2s_init(void)
{
    /* Configure the GPIO AF */
    /* CK--------------PB12 */	
    /* WS--------------PB13 */	
    /* SD--------------PB14 */	
    /* MCK-------------PB15 */

    pinmux_iis2_master_ck_init(I2S_CK_PIN);
    pinmux_iis2_master_ws_init(I2S_WS_PIN);
    pinmux_iis2_master_sd_init(I2S_SD_PIN, 1); 
    pinmux_iis2_master_mck_init(I2S_MCK_PIN);

    I2sHandle.Instance                  = SPI2;
    I2sHandle.Init.Mode                 = I2S_MODE_MASTER_TX;
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
    /* init spi and GPIO   */
    i2s_init();

    for (uint8_t i = 0; i < BUFFERSIZE; i++)
    {
        aTxBuffer[i] = i;
    } 

    for (uint8_t i = 0; i < 10; i++)
    {
        ComState = COM_WAIT;
        HAL_I2S_Transmit_IT(&I2sHandle, (uint16_t *)aTxBuffer, BUFFERSIZE);
        while(ComState != COM_COMPLETE);
        DELAY_US(200*1000);
    }

    /* Infinite loop */
    while (1)
    {
        /* USER CODE */	
    }
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    ComState = COM_COMPLETE;
}
 