#include "ls_hal_timer.h"
#include <string.h>
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define TIM_PRESCALER     (SDK_HCLK_MHZ-1)
#define TIM_PERIOD        (5000 - 1) /* Period Value  */
#define TIM_PULSE1        2500       /* Capture Compare 1 Value  */

#define ENCODER_TIM_PERIOD      500
#define ENCODER_MODE            TIM_ENCODERMODE_TI12
#define CAPTRUE_COUNT           ENCODER_TIM_PERIOD*4
/*
 * if(ENCODER_MODE == TIM_ENCODERMODE_TI12)
 * {
 *     Capture_Count = CAPTRUE_COUNT*2;
 * }
 * else{
 *     Capture_Count = CAPTRUE_COUNT；
 * }
*/

TIM_HandleTypeDef Timhdl;
TIM_HandleTypeDef TIM_EncoderHandle;

__IO int16_t Encoder_Overflow_Count = 0;
__IO int32_t Capture_Count = 0;
__IO int8_t Count_Direction = 0;

static void PWM_Output_Cfg(void)
{
    io_cfg_output(PA00);
    pinmux_gptimb1_ch1_init(PA01, true, 0);
    TIM_OC_InitTypeDef sConfig = {0};
    Timhdl.Instance = LSGPTIMB;
    Timhdl.Init.Prescaler = TIM_PRESCALER; 
    Timhdl.Init.Period = TIM_PERIOD;
    Timhdl.Init.ClockDivision = 0;
    Timhdl.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
    Timhdl.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Init(&Timhdl);

    sConfig.OCMode = TIM_OCMODE_PWM1;
    sConfig.OCPolarity = TIM_OCPOLARITY_LOW;
    sConfig.OCFastMode = TIM_OCFAST_DISABLE;
    sConfig.Pulse = TIM_PULSE1;      
    HAL_TIM_PWM_ConfigChannel(&Timhdl, &sConfig, TIM_CHANNEL_1);

    // HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&Timhdl, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&Timhdl);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == LSGPTIMB){
        static uint16_t i = 0;
        if(i<CAPTRUE_COUNT){
            io_toggle_pin(PA00);
            i++;
        }
        if(i==CAPTRUE_COUNT){
            HAL_TIM_PWM_Stop(&Timhdl,TIM_CHANNEL_1);
        }
    }
    else if(htim->Instance == LSGPTIMA){
        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM_EncoderHandle)){
            Encoder_Overflow_Count--;
        }
        else{
            Encoder_Overflow_Count++;
        }
    }
}

static void TIM_Encoder_Init(void)
{ 
    pinmux_gptima1_ch1_init(PB10,false,0);
    pinmux_gptima1_ch2_init(PB11,false,0);
    TIM_Encoder_InitTypeDef Encoder_ConfigStructure;

    TIM_EncoderHandle.Instance = LSGPTIMA;
    TIM_EncoderHandle.Init.Prescaler = 0;
    TIM_EncoderHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM_EncoderHandle.Init.Period = ENCODER_TIM_PERIOD - 1;
    TIM_EncoderHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM_EncoderHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    Encoder_ConfigStructure.EncoderMode = ENCODER_MODE;

    Encoder_ConfigStructure.IC1Polarity = TIM_ICPOLARITY_RISING;
    Encoder_ConfigStructure.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    Encoder_ConfigStructure.IC1Prescaler = TIM_ICPSC_DIV1;
    Encoder_ConfigStructure.IC1Filter = 0;

    Encoder_ConfigStructure.IC2Polarity = TIM_ICPOLARITY_RISING;
    Encoder_ConfigStructure.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    Encoder_ConfigStructure.IC2Prescaler = TIM_ICPSC_DIV1;
    Encoder_ConfigStructure.IC2Filter = 0;

    HAL_TIM_Encoder_Init(&TIM_EncoderHandle, &Encoder_ConfigStructure);
    HAL_TIM_Base_Start_IT(&TIM_EncoderHandle);
    HAL_TIM_Encoder_Start(&TIM_EncoderHandle, TIM_CHANNEL_ALL);
}
/* 
*  PA00 -- PB11
*  PA01 -- PB10
*/
int main(void)
{
    sys_init_none();
    LOG_I("TIM_Encoder_Init TEST");
    TIM_Encoder_Init();
    PWM_Output_Cfg();
    while (1)
    {
        Count_Direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM_EncoderHandle);
        Capture_Count = __HAL_TIM_GET_COUNTER(&TIM_EncoderHandle) + (Encoder_Overflow_Count * ENCODER_TIM_PERIOD);
        LOG_I("%d,%d",Count_Direction,Capture_Count);
        DELAY_US(50000);
    }
}

