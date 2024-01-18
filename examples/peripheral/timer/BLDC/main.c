#include "ls_hal_timer.h"
#include <string.h>
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#if defined(LE501X)
#define OUTPUT_PWM_TIMER LSADTIM
#elif defined(LM3050)
#define OUTPUT_PWM_TIMER LSADTIM1
#endif

#define HALL_TIM  LSGPTIMA
#define HALL_PRESCALER_COUNT (SDK_HCLK_MHZ - 1)
#define HALL_PERIOD_COUNT     (60000)

#define HALL_INPUTU  PA00
#define HALL_INPUTV  PA01
#define HALL_INPUTW  PA02

#define PWM_PRESCALER_COUNT     (2)
#define PWM_PERIOD_COUNT        (2200)
#define PWM_MAX_PERIOD_COUNT    (PWM_PERIOD_COUNT - 100)

#define MOTOR_OCPWM1_PIN    PB08
#define MOTOR_OCNPWM1_PIN   PB07

#define MOTOR_OCPWM2_PIN    PB06
#define MOTOR_OCNPWM2_PIN   PB05

#define MOTOR_OCPWM3_PIN    PB04
#define MOTOR_OCNPWM3_PIN   PB03

#define KEY_1 PB15
#define KEY_2 PB14

/* 电机方向控制枚举 */
typedef enum
{
  MOTOR_FWD = 0,
  MOTOR_REV,
}motor_dir_t;

typedef struct
{
  motor_dir_t direction;    // 电机方向
  uint16_t dutyfactor;      // PWM 输出占空比
  uint8_t is_enable;        // 使能电机
  uint32_t lock_timeout;    // 电机堵转计时
}bldcm_data_t;

int update = 0;     // 定时器更新计数
static bldcm_data_t bldcm_data;
static uint16_t bldcm_pulse = 0;

TIM_HandleTypeDef  htimx_bldcm;
TIM_OC_InitTypeDef TIM_OCInitStructure;

/* 霍尔传感器相关定时器初始出 */
TIM_HandleTypeDef htimx_hall;


void set_bldcm_direction(motor_dir_t dir)
{
    bldcm_data.direction = dir;
}

motor_dir_t get_bldcm_direction(void)
{
    return bldcm_data.direction;
}


uint8_t get_hall_state(void)
{
    uint8_t state = 0;

    if(io_read_pin(HALL_INPUTU) != RESET)
    {
        state |= 0x01U << 0;
    }
    if(io_read_pin(HALL_INPUTV) != RESET)
    {
        state |= 0x01U << 1;
    }
    if(io_read_pin(HALL_INPUTW) != RESET)
    {
        state |= 0x01U << 2;
    }

    return state;
}
static void TIMx_GPIO_Config(void) 
{
    pinmux_adtim1_ch1_init(MOTOR_OCPWM1_PIN,true,0);
    pinmux_adtim1_ch2_init(MOTOR_OCPWM2_PIN,true,0);
    pinmux_adtim1_ch3_init(MOTOR_OCPWM3_PIN,true,0);

    // pinmux_adtim1_ch1n_init(MOTOR_OCNPWM1_PIN);
    // pinmux_adtim1_ch2n_init(MOTOR_OCNPWM2_PIN);
    // pinmux_adtim1_ch2n_init(MOTOR_OCNPWM3_PIN);
    io_cfg_output(MOTOR_OCNPWM1_PIN);
    io_cfg_output(MOTOR_OCNPWM2_PIN);
    io_cfg_output(MOTOR_OCNPWM3_PIN);

}

static void TIM_Mode_Config(void)
{
    htimx_bldcm.Instance = OUTPUT_PWM_TIMER;
    htimx_bldcm.Init.Period = PWM_PERIOD_COUNT - 1;
    htimx_bldcm.Init.Prescaler = PWM_PRESCALER_COUNT - 1;
    htimx_bldcm.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htimx_bldcm.Init.CounterMode = TIM_COUNTERMODE_UP;
    htimx_bldcm.Init.RepetitionCounter = 0;
    HAL_TIM_Init(&htimx_bldcm);

    /*PWM模式配置*/
    // 配置为PWM模式1
    TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.Pulse = 0; // 默认必须要初始为0
    TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
    TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;
    TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    HAL_TIM_PWM_ConfigChannel(&htimx_bldcm, &TIM_OCInitStructure, TIM_CHANNEL_1); // 初始化通道 1 输出 PWM
    HAL_TIM_PWM_ConfigChannel(&htimx_bldcm, &TIM_OCInitStructure, TIM_CHANNEL_2); // 初始化通道 2 输出 PWM
    HAL_TIM_PWM_ConfigChannel(&htimx_bldcm, &TIM_OCInitStructure, TIM_CHANNEL_3); // 初始化通道 3 输出 PWM

    /* 开启定时器通道1输出PWM */
    HAL_TIM_PWM_Start(&htimx_bldcm, TIM_CHANNEL_1);

    /* 开启定时器通道2输出PWM */
    HAL_TIM_PWM_Start(&htimx_bldcm, TIM_CHANNEL_2);

    /* 开启定时器通道3输出PWM */
    HAL_TIM_PWM_Start(&htimx_bldcm, TIM_CHANNEL_3);
}

void stop_pwm_output(void)
{
    /* 关闭定时器通道1输出PWM */
    __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0);

    /* 关闭定时器通道2输出PWM */
    __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0);
    
    /* 关闭定时器通道3输出PWM */
    __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0);
    
    io_clr_pin(MOTOR_OCNPWM1_PIN);    // 关闭下桥臂
    io_clr_pin(MOTOR_OCNPWM2_PIN);    // 关闭下桥臂
    io_clr_pin(MOTOR_OCNPWM3_PIN);    // 关闭下桥臂
}

void set_pwm_pulse(uint16_t pulse)
{
    /* 设置定时器通道输出 PWM 的占空比 */
    bldcm_pulse = pulse;
}

void TIMx_Configuration(void)
{
	TIMx_GPIO_Config();
	TIM_Mode_Config();
}

static void hall_tim_init(void)
{
    TIM_HallSensor_InitTypeDef  hall_sensor_cfg; 

    pinmux_gptima1_ch1_init(HALL_INPUTU,false,0);
    pinmux_gptima1_ch2_init(HALL_INPUTV,false,0);
    pinmux_gptima1_ch3_init(HALL_INPUTW,false,0);

    /* 定时器基本功能配置 */
    htimx_hall.Instance = HALL_TIM;
    htimx_hall.Init.Prescaler = HALL_PRESCALER_COUNT - 1;   // 预分频
    htimx_hall.Init.CounterMode = TIM_COUNTERMODE_UP;       // 向上计数
    htimx_hall.Init.Period = HALL_PERIOD_COUNT - 1;         // 计数周期
    htimx_hall.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 时钟分频

    hall_sensor_cfg.IC1Prescaler = TIM_ICPSC_DIV1;         // 输入捕获分频
    hall_sensor_cfg.IC1Polarity = TIM_ICPOLARITY_BOTHEDGE; // 输入捕获极性
    hall_sensor_cfg.IC1Filter = 10;                         // 输入滤波
    hall_sensor_cfg.Commutation_Delay = 0U;                // 不使用延迟触发
    HAL_TIMEx_HallSensor_Init(&htimx_hall, &hall_sensor_cfg);
}

void hall_enable(void)
{
    /* 使能霍尔传感器接口 */
    __HAL_TIM_ENABLE_IT(&htimx_hall, TIM_IT_TRIGGER);
    __HAL_TIM_ENABLE_IT(&htimx_hall, TIM_IT_UPDATE);
    
    HAL_TIMEx_HallSensor_Start(&htimx_hall);

    HAL_TIM_TriggerCallback(&htimx_hall); 
}

void hall_disable(void)
{
    /* 禁用霍尔传感器接口 */
    __HAL_TIM_DISABLE_IT(&htimx_hall, TIM_IT_TRIGGER);
    __HAL_TIM_DISABLE_IT(&htimx_hall, TIM_IT_UPDATE);
    HAL_TIMEx_HallSensor_Stop(&htimx_hall);
}

void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim)
{
    /* 获取霍尔传感器引脚状态,作为换相的依据 */
    uint8_t step = 0;
    step = get_hall_state();
    if(get_bldcm_direction() == MOTOR_FWD)
    {
        switch (step)
        {
        case 1:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0); // 通道 2 配置为 0
            io_clr_pin(MOTOR_OCNPWM2_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0); // 通道 3 配置为 0
            io_clr_pin(MOTOR_OCNPWM1_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, bldcm_pulse); //通道 1 配置的占空比
            io_set_pin(MOTOR_OCNPWM3_PIN); // 开启下桥臂
            break;
        case 2:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0);// 通道 3 配置为 0
            io_clr_pin(MOTOR_OCNPWM3_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0);// 通道 1 配置为 0
            io_clr_pin(MOTOR_OCNPWM2_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, bldcm_pulse);// 通道 2 配置的占空比
            io_set_pin(MOTOR_OCNPWM1_PIN); // 开启下桥臂
            break;
        case 3:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0);  // 通道 1 配置为 0
            io_clr_pin(MOTOR_OCNPWM1_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0); // 通道 3 配置为 0
            io_clr_pin(MOTOR_OCNPWM2_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, bldcm_pulse); // 通道 2 配置的占空比
            io_set_pin(MOTOR_OCNPWM3_PIN); // 开启下桥臂
            break;
        case 4:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0); // 通道 1 配置为 0
            io_clr_pin(MOTOR_OCNPWM1_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0); // 通道 2 配置为 0
            io_clr_pin(MOTOR_OCNPWM3_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, bldcm_pulse); // 通道 3 配置的占空比
            io_set_pin(MOTOR_OCNPWM2_PIN); // 开启下桥臂
            break;
        case 5:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0); // 通道 3 配置为 0
            io_clr_pin(MOTOR_OCNPWM3_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0);// 通道 2 配置为 0
            io_clr_pin(MOTOR_OCNPWM1_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, bldcm_pulse); // 通道 1 配置的占空比
            io_set_pin(MOTOR_OCNPWM2_PIN); // 开启下桥臂
            break;
        case 6:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0);// 通道 2 配置为 0
            io_clr_pin(MOTOR_OCNPWM2_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0); // 通道 1 配置为 0
            io_clr_pin(MOTOR_OCNPWM3_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, bldcm_pulse);// 通道 3 配置的占空比
            io_set_pin(MOTOR_OCNPWM1_PIN); // 开启下桥臂
            break;
        default:
            break;
        }
    }
    else{
        switch (step)
        {
        case 1:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0); // 通道 2 配置为 0
            io_clr_pin(MOTOR_OCNPWM2_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0); // 通道 1 配置为 0
            io_clr_pin(MOTOR_OCNPWM3_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, bldcm_pulse); // 通道 3 配置的占空比
            io_set_pin(MOTOR_OCNPWM1_PIN); // 开启下桥臂
            break;
        case 2:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0);  // 通道 3 配置为 0
            io_clr_pin(MOTOR_OCNPWM3_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0);  // 通道 2 配置为 0
            io_clr_pin(MOTOR_OCNPWM1_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, bldcm_pulse); // 通道 1 配置的占空比
            io_set_pin(MOTOR_OCNPWM2_PIN); // 开启下桥臂
            break;
        case 3:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0); // 通道 1 配置为 0
            io_clr_pin(MOTOR_OCNPWM1_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0); // 通道 2 配置为 0
            io_clr_pin(MOTOR_OCNPWM3_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, bldcm_pulse);// 通道 3 配置的占空比
            io_set_pin(MOTOR_OCNPWM2_PIN); // 开启下桥臂
            break;
        case 4:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0); // 通道 1 配置为 0
            io_clr_pin(MOTOR_OCNPWM1_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0);  // 通道 3 配置为 0
            io_clr_pin(MOTOR_OCNPWM2_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, bldcm_pulse); // 通道 2 配置的占空比
            io_set_pin(MOTOR_OCNPWM3_PIN); // 开启下桥臂
            break;
        case 5:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0);  // 通道 3 配置为 0
            io_clr_pin(MOTOR_OCNPWM3_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, 0);  // 通道 1 配置为 0
            io_clr_pin(MOTOR_OCNPWM2_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, bldcm_pulse);  // 通道 2 配置的占空比
            io_set_pin(MOTOR_OCNPWM1_PIN); // 开启下桥臂
            break;
        case 6:
            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_2, 0);  // 通道 2 配置为 0
            io_clr_pin(MOTOR_OCNPWM2_PIN);    // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_3, 0);   // 通道 3 配置为 0
            io_clr_pin(MOTOR_OCNPWM1_PIN); // 关闭下桥臂

            __HAL_TIM_SET_COMPARE(&htimx_bldcm, TIM_CHANNEL_1, bldcm_pulse);   // 通道 1 配置的占空比
            io_set_pin(MOTOR_OCNPWM3_PIN); // 开启下桥臂
            break;
        default:
            break;
        }
    }
    LOG_I("h_s %d",step);
    update = 0;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (update++ > 1)    // 有一次在产生更新中断前霍尔传感器没有捕获到值
    {
        update = 0;
        LOG_I("timeout");
        hall_disable();
        stop_pwm_output(); 
    }
}

void set_bldcm_speed(uint16_t v)
{
    bldcm_data.dutyfactor = v;
    set_pwm_pulse(v); // 设置速度
}

void set_bldcm_enable(void)
{
	DELAY_US(1000);
    hall_enable();
}

void set_bldcm_disable(void)
{
    /* 禁用霍尔传感器接口 */
    hall_disable();
    
    /* 停止 PWM 输出 */
    stop_pwm_output();
}

void bldcm_init(void)
{
    TIMx_Configuration();
    hall_tim_init();
}

void key_init()
{
    io_cfg_input(KEY_1);
    io_cfg_input(KEY_2);
}

uint8_t Key_Scan(uint16_t pin)
{	
	if(io_read_pin(pin) == 0 )  
	{	
		while(io_read_pin(pin) == 0);  
		return 	1;
	}
	else
		return 0;
}

int main(void)
{
    __IO uint16_t ChannelPulse = PWM_MAX_PERIOD_COUNT/10;
    sys_init_none();
    bldcm_init();
    key_init();
    while (1)
    {
        if(Key_Scan(KEY_1))
        {
            set_bldcm_speed(ChannelPulse);
            set_bldcm_enable();
        }
        if(Key_Scan(KEY_2))
        {
            static int is_run_flag;
            if (ChannelPulse == 0) // 占空比从零增加后 重新使能一次
            {
                is_run_flag = 1;
            }
            /* 增大占空比 */
            ChannelPulse += PWM_MAX_PERIOD_COUNT / 10;

            if (ChannelPulse > PWM_MAX_PERIOD_COUNT)
                ChannelPulse = PWM_MAX_PERIOD_COUNT;

            set_bldcm_speed(ChannelPulse);
            if (is_run_flag == 1)
            {
                set_bldcm_enable();
                is_run_flag = 0;
            }
        }
    }
}

