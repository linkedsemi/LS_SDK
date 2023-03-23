/******************************************************************************
 * File: keyscan.c
 * Author: jyluo
 * Overview: matrix keyboard scan source file
 *
 * Date: Created on 2023-03-13, 10:20
 ******************************************************************************/

/******************************************************************************
 Include
 ******************************************************************************/
#include "keyscan.h"

/******************************************************************************
 External Const Declaration
 ******************************************************************************/

/******************************************************************************
 External Variable Declaration
 ******************************************************************************/

/******************************************************************************
 External Function Declaration
 ******************************************************************************/

/******************************************************************************
 Local Macro Definition
 ******************************************************************************/
#define TRUE 1
#define FALSE 0
/******************************************************************************
 Local Type Definition
 ******************************************************************************/
typedef struct keyscan
{
    uint8_t rowPinNum;
    uint8_t colPinNum;
    const uint8_t *rowPinArray;
    const uint8_t *colPinArray;
    uint32_t scanPeriod;
    KS_KEY_CALLBACK ks_Key_CallBack;
}KEYSCAN_CTIL_st;
/******************************************************************************
 Local Const Definition
 ******************************************************************************/

/******************************************************************************
 Local function Declaration
 ******************************************************************************/
static void vKey_Init(void);
static void vScan_Key(void);
static void Basic_Timer_Cfg(uint32_t period_ms);
/******************************************************************************
 Local Variable Definition
 ******************************************************************************/
#if  LONG_KEY_EN == 1
uint16_t g_usLongKey_Press;			// long key press value
uint16_t g_usLongKey_PressIng = 0; 	// long key press 
#endif
uint16_t g_usShortKey_Press;// short key press value
TIM_HandleTypeDef TimHandle;
KEYSCAN_CTIL_st _KEYSCAN_Controller = {0};

/******************************************************************************
 * Function:
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:
 * Note:
 ******************************************************************************/
static void Basic_Timer_Cfg(uint32_t period_ms)
{
    TimHandle.Instance = LSGPTIMA;
    TimHandle.Init.Prescaler = TIM_PRESCALER;
    TimHandle.Init.Period = period_ms*TIM_PERIOD;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Init(&TimHandle);
}
/******************************************************************************
 * Function:
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:
 * Note:
 ******************************************************************************/
static void vKey_Init(void)
{
    for (uint8_t i = 0; i < KEYSCAN_COL_NUM; i++)
    {
        io_pull_write(_KEYSCAN_Controller.colPinArray[i], IO_PULL_UP);
        io_cfg_input(_KEYSCAN_Controller.colPinArray[i]);
    }
    for (uint8_t i = 0; i < KEYSCAN_ROW_NUM; i++)
    {
        io_cfg_output(_KEYSCAN_Controller.rowPinArray[i]);
        io_cfg_pushpull(_KEYSCAN_Controller.rowPinArray[i]);
        io_cfg_opendrain(_KEYSCAN_Controller.rowPinArray[i]);
        io_set_pin(_KEYSCAN_Controller.rowPinArray[i]);
    }
}
/******************************************************************************
 * Function:
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:
 * Note:
 ******************************************************************************/
void Craet_ScanKey(const uint8_t *row_pin_array, uint8_t row_pin_num,const uint8_t *col_pin_array, \
                        uint8_t col_pin_num,uint32_t scan_period_ms, void (*keyscan_callback)(uint16_t))
{
    _KEYSCAN_Controller.rowPinArray = row_pin_array;
    _KEYSCAN_Controller.colPinArray = col_pin_array;
    _KEYSCAN_Controller.rowPinNum = row_pin_num;
    _KEYSCAN_Controller.colPinNum = col_pin_num;
    _KEYSCAN_Controller.scanPeriod = scan_period_ms;
    _KEYSCAN_Controller.ks_Key_CallBack = keyscan_callback;
    Basic_Timer_Cfg(_KEYSCAN_Controller.scanPeriod);
    vKey_Init();
}
/******************************************************************************
 * Function:
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:
 * Note:
 ******************************************************************************/
bool keyscan_Start(bool scan)
{
    bool res = false;
	if (_KEYSCAN_Controller.scanPeriod) {
		if (scan) {
			HAL_TIM_Base_Start_IT(&TimHandle);
		}
		else {
			HAL_TIM_Base_Stop_IT(&TimHandle);
		}
		res = true;
	}
	return res;
}

/******************************************************************************
 * Function:
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:
 * Note:
 ******************************************************************************/
static void vScan_Key(void)
{
    static uint16_t s_usOldKeyStatus = 0;
    static uint16_t s_usCurruntKeyStatus = 0;
    static uint16_t s_usKeyinStatus = 0;
    static uint16_t s_usButtoKeepTime = 0;
    static uint16_t s_usRKeycvtbuf = 0;
    static uint16_t s_usComDelete = 0;
    static bool fKeyIn = FALSE;
    volatile uint8_t r = 0;
    volatile uint8_t c = 0;


/***********************************************************
*scan key
***********************************************************/
    uint16_t usKeytemp = 1;
    s_usCurruntKeyStatus = 0;

    for (r = 0; r < KEYSCAN_ROW_NUM; r++)
    {
        io_clr_pin(_KEYSCAN_Controller.rowPinArray[r]);
        DELAY_US(10);
        for (c = 0; c < KEYSCAN_COL_NUM; c++)
        {
            if (!io_read_pin(_KEYSCAN_Controller.colPinArray[c]))
                s_usCurruntKeyStatus |= usKeytemp;
            usKeytemp <<= 1;
        }
        io_set_pin(_KEYSCAN_Controller.rowPinArray[r]);
    }

/***********************************************************
*key debounce
***********************************************************/
    if (s_usCurruntKeyStatus==s_usKeyinStatus)
    {
        if (fKeyIn)
        {
            s_usButtoKeepTime--;
            if(!s_usButtoKeepTime)
            {
                s_usRKeycvtbuf = s_usKeyinStatus;
                fKeyIn = FALSE;
            }
        }
    }
    else
    {
        s_usKeyinStatus = s_usCurruntKeyStatus;
        fKeyIn = TRUE;
        s_usButtoKeepTime = BUTTON_KEEP_TIME_MAX;
    }
/***********************************************************
*short press
***********************************************************/
    if (s_usRKeycvtbuf != s_usOldKeyStatus)
    {
        g_usShortKey_Press = s_usRKeycvtbuf;
        s_usOldKeyStatus = s_usRKeycvtbuf;
/***********************************************************
 *compound key delete
***********************************************************/

        if (g_usShortKey_Press > s_usComDelete)
        {
            s_usOldKeyStatus = g_usShortKey_Press;
            g_usShortKey_Press &= ~s_usComDelete;
            s_usComDelete = s_usOldKeyStatus;
        }
        else
        {
            if (g_usShortKey_Press)
                s_usComDelete = g_usShortKey_Press;
            else
                s_usComDelete = 0;
            g_usShortKey_Press = 0;
        }
/***********************************************************
 * Output short key value and callback
***********************************************************/
        _KEYSCAN_Controller.ks_Key_CallBack(g_usShortKey_Press);
        
    }
}
/******************************************************************************
 * Function:
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:
 * Note:
 ******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == LSGPTIMA)
    {
        vScan_Key();
    }
}


