#include <string.h>
#include <stdlib.h>
#include "ls_hal_i2c.h"
#include "platform.h"
#include "compile_flag.h"
#include "ls_soc_gpio.h"

#include "ls_hal_timer.h"
#include "log.h"

#define I2C_MASTER_ROLE 0
#define I2C_SLAVE_ROLE 1

#define CURRENT_ROLE I2C_SLAVE_ROLE
#define I2C_SPEED I2C_SPEED_FAST_400K
#define I2C_ADDRESS 0x50
#define BUFFER_LEN 255
#define SIMU_IRQ_EN 0
#ifdef LE501X
#define LED_IO PA01
// Set PB14 as debug IO
#define DEBUG_IO_HIGH (*(volatile uint32_t*)0x48000404 |= 1 << 0xE)
#define DEBUG_IO_LOW (*(volatile uint32_t*)0x48000404 &= ~(1 << 0xE))
#elif defined LM3050
#define LED_IO PB06
// Set PA15 as debug IO
#define DEBUG_IO_HIGH (*(volatile uint32_t*)0x4000d064 |= 1 << 15)
#define DEBUG_IO_LOW (*(volatile uint32_t*)0x4000d064 &= ~(1 << 15))
#else
#error "Error config for platform!"
#endif

enum
{
    start = 0,
    txing,
    txover,
    rxing,
    rxover,
};
static volatile uint8_t Com_Sta = start;
static I2C_HandleTypeDef I2cHandle;
static uint8_t aRxBuffer[BUFFER_LEN]; //Buffer used for reception 
#if CURRENT_ROLE == I2C_MASTER_ROLE
static uint8_t aTxBuffer[BUFFER_LEN];
#endif

#if SIMU_IRQ_EN == 1
static void simu_timer_init(void);
#endif
static void Error_Handler(void);
static void toggle_debug_IO_init(void);
void toggle_debug_IO(uint16_t);

static void iic_tx_rx_test_init(uint8_t);
static void iic_tx_rx_test_it_run(uint8_t);
static bool iic_tx_rx_check_result(uint8_t*);

static void iic_init(void)
{
    I2cHandle.Instance = I2C1;
    I2cHandle.Init.ClockSpeed = I2C_SPEED;
    I2cHandle.Init.OwnAddress1 = I2C_ADDRESS;
    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
#if CURRENT_ROLE == I2C_MASTER_ROLE
    I2cHandle.Init.OwnAddress2 = 0x7E;
#else 
    I2cHandle.Init.OwnAddress2 = 0x7E;
    I2cHandle.Init.Oar2msk_Mask = 0x7; //0x7: send ack to master call with any addr. 0x6: only send ack when addr matches OA2[7]
#endif
}
static uint8_t test_len = 1;
int main(void)
{
    sys_init_none();
    toggle_debug_IO_init();
    pinmux_iic1_init(PB09, PB08); //PB08---SDA   PB09---SCL
    iic_init();
    if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
    {
        Error_Handler();
    }
#if SIMU_IRQ_EN == 1
    simu_timer_init();
    __NVIC_SetPriority(I2C1_IRQn,3); 
    __NVIC_SetPriority(GPTIMA1_IRQn,2); 
#endif
    while (1)
    {
        iic_tx_rx_test_init(test_len);
        iic_tx_rx_test_it_run(test_len);
        if (iic_tx_rx_check_result(&test_len))
        {
            static uint16_t led_count = 0;
            if (led_count++ > 5)
            {
                io_cfg_output(LED_IO);
                io_toggle_pin(LED_IO);
                led_count = 0;
            }
            DELAY_US(200);
        }
        else
        {
            Error_Handler();
        }
    }
}

#if CURRENT_ROLE == I2C_MASTER_ROLE
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (Com_Sta == txing)
    {
        Com_Sta = txover;
    }
}
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (Com_Sta == rxing)
    {
        Com_Sta = rxover;
    }
}
#else
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (Com_Sta == txing)
    {
        Com_Sta = txover;
    }
}
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{ 
    if (Com_Sta == rxing)
    {
        Com_Sta = rxover;
    }
}
#endif
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
    if (Com_Sta == txing)
    {
        Com_Sta = txover;
    }
    else if (Com_Sta == rxing)
    {
        Com_Sta = rxover;
    }
}
static bool iic_tx_rx_check_result(uint8_t *len)
{
    bool result = true;
#if CURRENT_ROLE == I2C_MASTER_ROLE
    result = memcmp(aTxBuffer, aRxBuffer, *len) == 0;
#endif
    *len = aRxBuffer[0];
    if (*len == 0)
    {
        (*len)++;
    }
    return result;
}
static void iic_tx_rx_test_init(uint8_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
    #if CURRENT_ROLE == I2C_MASTER_ROLE
        aTxBuffer[i] = rand();
    #endif
        aRxBuffer[i] = 0xff;
    }
#if CURRENT_ROLE == I2C_MASTER_ROLE
    DELAY_US(5000); // Slave may run at a lower AHB, so master has to delay enough to await slave ready
#endif
}
static void iic_tx_rx_test_it_run(uint8_t len)
{
#if CURRENT_ROLE == I2C_MASTER_ROLE
    uint8_t extra_data_len = 0;
    if (len > 100 && len < 200)
    {
        extra_data_len = rand() % (255 - len);
    }
    
    Com_Sta = txing;
    HAL_I2C_Master_Transmit_IT(&I2cHandle, (uint16_t)I2C_ADDRESS, aTxBuffer, len + extra_data_len);
    while (Com_Sta == txing);
    if (extra_data_len != 0)
    {
        if (extra_data_len != I2cHandle.XferCount)
        {
            // Error_Handler();
            while(1);
        }
    }

    DELAY_US(1200);

    Com_Sta = rxing;
    HAL_I2C_Master_Receive_IT(&I2cHandle, (uint16_t)I2C_ADDRESS, aRxBuffer, len);
    while (Com_Sta == rxing);
    if (I2cHandle.XferCount != 0)
    {
        // Error_Handler();
        while(1);
    }
    
#else
    Com_Sta = rxing;
    HAL_I2C_Slave_Receive_IT(&I2cHandle, aRxBuffer, len);
    while (Com_Sta == rxing);

    Com_Sta = txing;
    HAL_I2C_Slave_Transmit_IT(&I2cHandle, aRxBuffer, len); // transmit the data just received
    while (Com_Sta == txing);    
#endif
}


static void Error_Handler(void)
{
    while (1)
    {
        ;
    }
}
static void toggle_debug_IO_init(void)
{
#ifdef LE501X
    *(volatile uint32_t*)0x48000418 |= 1 << 0xE; // Set PB14 as debug IO
#elif defined LM3050
    *(volatile uint32_t*)0x4000d064 |= 1 << 31; // Set PA15 as debug IO
#else
#error "Error config for platform!"
#endif
}
void XIP_BANNED_FUNC(toggle_debug_IO, uint16_t num)
{
    for (uint16_t i = 0; i < num; i++)
    {
    #ifdef LE501X
        DEBUG_IO_HIGH;
        DEBUG_IO_LOW;
    #elif defined LM3050
        DEBUG_IO_HIGH;
        DEBUG_IO_LOW;
    #else
    #endif
    }
}

#if SIMU_IRQ_EN == 1
#define TIM_PRESCALER     (SDK_HCLK_MHZ-1)
#define TIM_PERIOD        (5*1000 - 1)

static TIM_HandleTypeDef TimHandle;

static void simu_timer_init(void)
{ 
    TimHandle.Instance           = LSGPTIMA;
    TimHandle.Init.Prescaler     = TIM_PRESCALER;
    TimHandle.Init.Period        = TIM_PERIOD;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode   = TIM_COUNTERMODE_UP;
    HAL_TIM_Init(&TimHandle);
    HAL_TIM_Base_Start_IT(&TimHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    DEBUG_IO_HIGH;
    uint16_t time_us = rand() % 1000;
    time_us++;
    DELAY_US(time_us);
    time_us *= 10;
    if (time_us < 3000)
    {
        time_us += 3000; // 3ms minimum
    }
    __HAL_TIM_SET_AUTORELOAD(htim, time_us);
    DEBUG_IO_LOW;
}
#endif
