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

#define LED_IO PA01
#define I2C_ADDRESS 0x50
#define BUFFER_LEN 255
#define I2C_POLLING_TIMEOUT_MS 1000

enum
{
    start = 0,
    txing,
    txover,
    rxing,
    rxover,
};
#if CURRENT_ROLE == I2C_MASTER_ROLE
typedef HAL_StatusTypeDef (*iic_tx_rx_func)(I2C_HandleTypeDef *, uint16_t, uint8_t*, uint8_t, uint32_t);
typedef HAL_StatusTypeDef (*iic_tx_rx_func)(I2C_HandleTypeDef *, uint16_t, uint8_t*, uint8_t, uint32_t);
#else
typedef HAL_StatusTypeDef (*iic_tx_rx_func)(I2C_HandleTypeDef *, uint8_t*, uint8_t, uint32_t);
typedef HAL_StatusTypeDef (*iic_tx_rx_func)(I2C_HandleTypeDef *, uint8_t*, uint8_t, uint32_t);
#endif
static I2C_HandleTypeDef I2cHandle;
static uint8_t aRxBuffer[BUFFER_LEN]; //Buffer used for reception 
static uint8_t aTxBuffer[BUFFER_LEN];

#if CURRENT_ROLE == I2C_MASTER_ROLE
static iic_tx_rx_func tx_func = HAL_I2C_Master_Transmit;
static iic_tx_rx_func rx_func = HAL_I2C_Master_Receive;
#else
static iic_tx_rx_func tx_func = HAL_I2C_Slave_Transmit;
static iic_tx_rx_func rx_func = HAL_I2C_Slave_Receive;
#endif

static void simu_timer_init(void);
static void Error_Handler(void);
static void toggle_PB14_init(void);
void toggle_PB14(uint16_t);

static void iic_tx_rx_test_init(uint8_t);
static void iic_tx_rx_test_polling_run(uint8_t);
static bool iic_tx_rx_check_result(uint8_t*);

static void iic_init(void)
{
    I2cHandle.Instance = I2C1;
    I2cHandle.Init.ClockSpeed = I2C_SPEED_FAST_400K;
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
    toggle_PB14_init();
    pinmux_iic1_init(PB09, PB08); //PB08---SDA   PB09---SCL
    iic_init();
    if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
    {
        Error_Handler();
    }
    simu_timer_init();
    // uint8_t test_len = 0x57;
    while (1)
    {
        iic_tx_rx_test_init(test_len);
        iic_tx_rx_test_polling_run(test_len);
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
        aTxBuffer[i] = rand();
        aRxBuffer[i] = 0xff;
    }
#if CURRENT_ROLE == I2C_MASTER_ROLE
    DELAY_US(5000); // Slave may run at a lower AHB, so master has to delay enough to await slave ready
#endif
}
static void iic_tx_rx_test_polling_run(uint8_t len)
{
#if CURRENT_ROLE == I2C_MASTER_ROLE
    uint8_t extra_data_len = 0;
    if (len > 100 && len < 200)
    {
        extra_data_len = rand() % (255 - len);
    }
    
    uint8_t result = tx_func(&I2cHandle, (uint16_t)I2C_ADDRESS, aTxBuffer, len + extra_data_len, I2C_POLLING_TIMEOUT_MS);
    if (extra_data_len != 0) 
    {
        toggle_PB14(10);
        if (result != HAL_ERROR || extra_data_len != I2cHandle.XferCount) // Check result and XferCount when master received NACK earlier than expected during transmit
        {
            // Error_Handler();
            while(1);
        }
    }
    else
    {
        toggle_PB14(7);
        if (result != HAL_OK)
        {
            // Error_Handler();
            while(1);
        }
    }
    
    DELAY_US(1200);

    result = rx_func(&I2cHandle, (uint16_t)I2C_ADDRESS, aRxBuffer, len, I2C_POLLING_TIMEOUT_MS);
    if (result != HAL_OK)
    {
        Error_Handler();
    }
#else
    HAL_StatusTypeDef status = HAL_OK;
    do
    {
        status = rx_func(&I2cHandle, aRxBuffer, len, I2C_POLLING_TIMEOUT_MS);
    } while (status != HAL_OK);
    
    tx_func(&I2cHandle, aRxBuffer, len, I2C_POLLING_TIMEOUT_MS); // transmit the data just received
#endif
}

#define TIM_PRESCALER     (SDK_HCLK_MHZ-1)
#define TIM_PERIOD        (5*1000 - 1) /* 10ms period*/

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
    *(volatile uint32_t*)0x48000404 |= 1 << 0xE; // pull up PB14
    uint16_t time_us = rand() % 1000;
    time_us++;
    DELAY_US(time_us);
    *(volatile uint32_t*)0x48000404 &= ~(1 << 0xE); // pull down PB14
}

static void Error_Handler(void)
{
    while (1)
    {
        ;
    }
}
static void toggle_PB14_init(void)
{
    *(volatile uint32_t*)0x48000418 |= 1 << 0xE;
}
// XIP_BANNED void toggle_PB14(uint16_t num)
void XIP_BANNED_FUNC(toggle_PB14, uint16_t num)
{
    for (uint16_t i = 0; i < num; i++)
    {
        *(volatile uint32_t*)0x48000404 |= 1 << 0xE;  
        // __asm("nop");
        *(volatile uint32_t*)0x48000404 &= ~(1 << 0xE);  
    }
}
