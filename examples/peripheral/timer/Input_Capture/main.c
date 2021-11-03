#include "lstimer.h"
#include <string.h>
#include "io_config.h"
#include "platform.h"
#include "log.h"

#define TIM_PRESCALER     (SDK_HCLK_MHZ-1)

TIM_HandleTypeDef TimHandle;
typedef struct
{
    uint8_t ucStartFlag; // Capture start flag bit
    uint16_t usCtr;      // Capture reg value
    uint16_t usPeriod;   // Automatically reload register update flags
}capture_t;
capture_t TIM_ICUserValueStructure = {0};

static void Input_Capture_Measurement_Cfg(void)
{
    TIM_IC_InitTypeDef ICConfig = {0};
    //Toggle IO Cfg
    io_cfg_output(PA01);
    io_write_pin(PA01,0);
    //Input Capture IO Cfg 
    gptimc1_ch1_io_init(PA00,false,0);
    io_pull_write(PA00,IO_PULL_DOWN);

    TimHandle.Instance = LSGPTIMC;
    TimHandle.Init.Prescaler = TIM_PRESCALER;
    TimHandle.Init.Period = 0xFFFF;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Init(&TimHandle);

    ICConfig.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    ICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
    ICConfig.ICPrescaler = TIM_ICPSC_DIV1;
    ICConfig.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&TimHandle, &ICConfig, TIM_CHANNEL_1);

    HAL_TIM_Base_Start_IT(&TimHandle);  
    HAL_TIM_IC_Start_IT(&TimHandle,TIM_CHANNEL_1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == LSGPTIMC)
    {
        TIM_ICUserValueStructure.usPeriod++;
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    TIM_IC_InitTypeDef IC_Config = {0};
    if (TIM_ICUserValueStructure.ucStartFlag == 0)
    {
        io_toggle_pin(PA01);
        // clear timer counts
        TIM_ICUserValueStructure.usPeriod = 0;
        TIM_ICUserValueStructure.usCtr = 0;
        TIM_ICUserValueStructure.usCtr = HAL_TIM_ReadCapturedValue(&TimHandle, TIM_CHANNEL_1);

        // Configure the input capture parameters, modify the trigger level
        IC_Config.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
        IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
        IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
        IC_Config.ICFilter = 0;
        HAL_TIM_IC_ConfigChannel(&TimHandle, &IC_Config, TIM_CHANNEL_1);
        // Clear interrupt flag bits
        __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
        // Start input capture and enable interrupts
        HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL_1);
        TIM_ICUserValueStructure.ucStartFlag = 1;
    }
    else
    {
        io_toggle_pin(PA01);
        // get timer counter
        TIM_ICUserValueStructure.usCtr = HAL_TIM_ReadCapturedValue(&TimHandle, TIM_CHANNEL_1) - TIM_ICUserValueStructure.usCtr + TIM_ICUserValueStructure .usPeriod*65535;
        // Configure the input capture parameters, modify the trigger level
        IC_Config.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
        IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
        IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
        IC_Config.ICFilter = 0;
        HAL_TIM_IC_ConfigChannel(&TimHandle, &IC_Config, TIM_CHANNEL_1);

        // Clear interrupt flag bits
        __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
        // Start input capture and enable interrupts
        HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL_1);
        TIM_ICUserValueStructure.ucStartFlag = 0;

        LOG_I("IC Time:%d us",TIM_ICUserValueStructure.usCtr);
    }
}

int main(void)
{
    sys_init_none();
    Input_Capture_Measurement_Cfg();
    while (1);
}

