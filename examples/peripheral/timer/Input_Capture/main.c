#include "ls_hal_timer.h"
#include <string.h>
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#define  COMMON_INPUT_CAPTURE 0
#define  PWM_INPUT_CAPTURE 1

#define INPUT_CAPTURE_MODE (COMMON_INPUT_CAPTURE)

#define TIM_PRESCALER     (SDK_HCLK_MHZ-1)
TIM_HandleTypeDef  TIM_PWMOUTPUT_Handle;
TIM_HandleTypeDef  TIM_Capture_Handle;

#if (INPUT_CAPTURE_MODE == COMMON_INPUT_CAPTURE)
typedef struct
{
    uint8_t ucStartFlag; // Capture start flag bit
    uint16_t usCtr;      // Capture reg value
    uint16_t usPeriod;   // Automatically reload register update flags
}capture_t;
capture_t TIM_ICUserValueStructure = {0};
#else
uint16_t IC2Value = 0;
uint16_t IC1Value = 0;
uint16_t DutyCycle = 0;
uint16_t Frequency = 0;
#endif
static void PWM_Output_Config(void)
{
    pinmux_gptima1_ch1_init(PA00,true,0);
    TIM_OC_InitTypeDef  TIM_OCInitStructure = {0};  

    TIM_PWMOUTPUT_Handle.Instance = LSGPTIMA;
    TIM_PWMOUTPUT_Handle.Init.Period = 5000-1;
    TIM_PWMOUTPUT_Handle.Init.Prescaler = TIM_PRESCALER;	
    TIM_PWMOUTPUT_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM_PWMOUTPUT_Handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Init(&TIM_PWMOUTPUT_Handle);

    TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.Pulse = 2500;
    TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE;
    TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;	

    HAL_TIM_PWM_ConfigChannel(&TIM_PWMOUTPUT_Handle, &TIM_OCInitStructure, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&TIM_PWMOUTPUT_Handle,TIM_CHANNEL_1);
}

static void Input_Capture_Config(void)
{
    TIM_IC_InitTypeDef TIM_ICInitStructure = {0};
    pinmux_gptimc1_ch1_init(PA07, false, 0);

    TIM_Capture_Handle.Instance = LSGPTIMC;
    TIM_Capture_Handle.Init.Period = 0xFFFF;
    TIM_Capture_Handle.Init.Prescaler = TIM_PRESCALER;
    TIM_Capture_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM_Capture_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Init(&TIM_Capture_Handle);

    TIM_ICInitStructure.ICPolarity = TIM_ICPOLARITY_RISING;
    TIM_ICInitStructure.ICSelection = TIM_ICSELECTION_DIRECTTI;
    TIM_ICInitStructure.ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&TIM_Capture_Handle, &TIM_ICInitStructure, TIM_CHANNEL_1);

#if (INPUT_CAPTURE_MODE == COMMON_INPUT_CAPTURE)
    io_cfg_output(PA01); //Debug IO Config
    HAL_TIM_Base_Start_IT(&TIM_Capture_Handle);  
    HAL_TIM_IC_Start_IT(&TIM_Capture_Handle,TIM_CHANNEL_1);
#else
    TIM_ICInitStructure.ICPolarity = TIM_ICPOLARITY_FALLING;
    TIM_ICInitStructure.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    TIM_ICInitStructure.ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&TIM_Capture_Handle, &TIM_ICInitStructure, TIM_CHANNEL_2);

    TIM_SlaveConfigTypeDef TIM_SlaveConfigStructure = {0};
    TIM_SlaveConfigStructure.SlaveMode = TIM_SLAVEMODE_RESET;
    TIM_SlaveConfigStructure.InputTrigger = TIM_TS_TI1FP1;
    HAL_TIM_SlaveConfigSynchro(&TIM_Capture_Handle, &TIM_SlaveConfigStructure);

    HAL_TIM_IC_Start_IT(&TIM_Capture_Handle, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&TIM_Capture_Handle, TIM_CHANNEL_2);
#endif
}

#if (INPUT_CAPTURE_MODE == COMMON_INPUT_CAPTURE)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == LSGPTIMC)
    {
        TIM_ICUserValueStructure.usPeriod++;
    }
}
#endif

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
#if (INPUT_CAPTURE_MODE == COMMON_INPUT_CAPTURE)
    TIM_IC_InitTypeDef IC_Config = {0};
    if (TIM_ICUserValueStructure.ucStartFlag == 0)
    {
        io_toggle_pin(PA01);
        // clear timer counts
        TIM_ICUserValueStructure.usPeriod = 0;
        TIM_ICUserValueStructure.usCtr = 0;
        TIM_ICUserValueStructure.usCtr = HAL_TIM_ReadCapturedValue(&TIM_Capture_Handle, TIM_CHANNEL_1);

        // Configure the input capture parameters, modify the trigger level
        IC_Config.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
        IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
        IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
        IC_Config.ICFilter = 0;
        HAL_TIM_IC_ConfigChannel(&TIM_Capture_Handle, &IC_Config, TIM_CHANNEL_1);
        // Clear interrupt flag bits
        __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
        // Start input capture and enable interrupts
        HAL_TIM_IC_Start_IT(&TIM_Capture_Handle, TIM_CHANNEL_1);
        TIM_ICUserValueStructure.ucStartFlag = 1;
    }
    else
    {
        io_toggle_pin(PA01);
        // get timer counter
        TIM_ICUserValueStructure.usCtr = HAL_TIM_ReadCapturedValue(&TIM_Capture_Handle, TIM_CHANNEL_1) - TIM_ICUserValueStructure.usCtr + TIM_ICUserValueStructure .usPeriod*65535;
        // Configure the input capture parameters, modify the trigger level
        IC_Config.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
        IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
        IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
        IC_Config.ICFilter = 0;
        HAL_TIM_IC_ConfigChannel(&TIM_Capture_Handle, &IC_Config, TIM_CHANNEL_1);

        // Clear interrupt flag bits
        __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
        // Start input capture and enable interrupts
        HAL_TIM_IC_Start_IT(&TIM_Capture_Handle, TIM_CHANNEL_1);
        TIM_ICUserValueStructure.ucStartFlag = 0;

        LOG_I("IC Time:%d us",TIM_ICUserValueStructure.usCtr);
    }
#else
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        IC1Value = HAL_TIM_ReadCapturedValue(&TIM_Capture_Handle, TIM_CHANNEL_1);
        IC2Value = HAL_TIM_ReadCapturedValue(&TIM_Capture_Handle, TIM_CHANNEL_2);
        if (IC1Value != 0)
        {
            DutyCycle = ((IC2Value + 1) * 100) / (IC1Value + 1);
            Frequency = 1000000 / (IC1Value + 1);
        }
        else
        {
            DutyCycle = 0;
            Frequency = 0;
        }
    }
#endif
}
int main(void)
{
    sys_init_none();
    // PA00 <--> PA07
    PWM_Output_Config();
    Input_Capture_Config();
    while (1)
    {
        DELAY_US(500*1000);
        #if (INPUT_CAPTURE_MODE == PWM_INPUT_CAPTURE)
        LOG_I("IC1Value = %d,IC2Value = %d ", IC1Value, IC2Value);
        LOG_I("DutyCycle = %d,Frequency = %dHz\n", DutyCycle, Frequency);
        #endif
    }
}
