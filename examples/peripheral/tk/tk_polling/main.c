/******************************************************************************
 * File: main.c
 * Author: luojunyang
 * Overview: ls touch main process
 *
 * Date: Created on 2021-12-30, 19:45
 ******************************************************************************/

/******************************************************************************
 Include
 ******************************************************************************/
#include <stdbool.h>
#include "lstk.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"

/******************************************************************************
 External Const Definition
 ******************************************************************************/

/******************************************************************************
 External Variable Declaration
 ******************************************************************************/

/******************************************************************************
 Local Macro Definition
 ******************************************************************************/

/******************************************************************************
 Local Type Definition
 ******************************************************************************/

/******************************************************************************
 Local Const Definition
 ******************************************************************************/

/******************************************************************************
 Local Variable Definition
 ******************************************************************************/
static volatile uint8_t RxBUFF[256] = {0};
static TK_HandleTypeDef tkHandle;
static uint8_t BUf0_ctl_io[] = {PB12, PC01, PC00, PA06, PA07, PA09, PA08, PA15};
static uint8_t BUf1_ctl_io[] = {PB02, PB04, PB10, PB11, PB13, PA04};
/******************************************************************************
 Local Function Declaration
 ******************************************************************************/
static bool lsTK_Init(void);
static void Error_TKHandle(void);
static void Init_GPIO(void);
/******************************************************************************
 Local Function Definition
 ******************************************************************************/

/**
 * @brief init TK
 * 
 * @return true 
 * @return false 
 */
static bool lsTK_Init(void)
{
    /* touch initialize start */
    tkHandle.Init.NPRR = 0;                         // Set the noise ratio to 4 times
    tkHandle.Init.DNPR = TK_DNPR_DISABLE;           // Disable noise protection
    tkHandle.Init.MultiOn = TK_MULTION_DISABLE;     // Disable multichannel detection
    tkHandle.Init.Debounce = 3;                     // Set the anti-jitter value to 3
    tkHandle.Init.ChannelEN = 0x3FFF;               // Open all channels
    tkHandle.Init.GbSen = 0xA0;                     // Set global sensitivity to 0xda
    tkHandle.Init.LP = TK_LP_DISABLE;               // DISENABLE automatic low-power scan mode
    tkHandle.Init.IComGS = 0x28;                    // Set group scan compensation current to 0x28
    tkHandle.Init.CdcFswDiv = 0x07;                 // Set the CDC module scanning frequency to 0x07
    tkHandle.Init.LowPowerScanPeriod = TK_LPSP_500; // set the low-power scan period to 500ms
    tkHandle.Init.KeyDebounceCount = 1;             // Set the number of jitters to 1
    tkHandle.Init.LpDelay = 4;                      // Set the time for automatic low-power scanning to 4*1S
    tkHandle.Init.ScanPeriod = 1;                   // Set the scan period
    tkHandle.Init.GsMask = 0x00;                  // ENABLE low-power scanning for all channels
    tkHandle.Init.LSenseGS = 0x68;                  // Set group scan sensitivity to 0x68

    if (HAL_TK_Init(&tkHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_TKHandle();
    }

    return 0;
    /* touch initialize end */
}

/**
 * @brief init gpio
 * 
 */
static void Init_GPIO(void)
{
    /*LED io initial*/
    for (uint8_t i = 0; i < 8; i++)
    {
        if (i < sizeof(BUf1_ctl_io))
        {
            io_set_pin(BUf1_ctl_io[i]);
            io_cfg_output(BUf1_ctl_io[i]);
        }
        io_set_pin(BUf0_ctl_io[i]);
        io_cfg_output(BUf0_ctl_io[i]);
    }
}

/** 
 * @brief MAIN
 * 
 */

int main(void)
{
    /*TODO Chip System Initialize*/
    sys_init_none();
    /*TODO GPIO Initialize*/
    Init_GPIO();
    /*TODO touch initialize*/
    lsTK_Init();
    LOG_I("start tk_polling test");
    while (1)
    {
        /*Reads the number of the channel being touched*/
        HAL_TK_Get_Reg(CNTLR, (uint8_t *)&RxBUFF, 2);
        /* Prints the number of channels to be touched */
        LOG_I("TK_CNTLR:%x  TK_CNTHR:%x", RxBUFF[0], RxBUFF[1] & 0x3f);
        /*light up the LED*/
        for (uint8_t i = 0; i < 8; i++)
        {
            if (i < sizeof(BUf1_ctl_io))
            {
                if ((RxBUFF[1] >> i) & 0x01)
                {
                    io_clr_pin(BUf1_ctl_io[i]);//led on
                }
                else
                {
                    io_set_pin(BUf1_ctl_io[i]);//led off
                }
            }

            if ((RxBUFF[0] >> i) & 0x01)
            {
                io_clr_pin(BUf0_ctl_io[i]);
            }
            else
            {
                io_set_pin(BUf0_ctl_io[i]);
            }
        }
        DELAY_US(5000);
    }
}
/**
 * @brief Run  error to enter this function
 */
static void Error_TKHandle(void)
{
    while (1)
    {
        ;
    }
}
/*******************************************************************************
 End of File
 ****************************************************************************/
