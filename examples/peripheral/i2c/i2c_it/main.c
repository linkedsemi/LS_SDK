#include <string.h>
#include <stdlib.h>
#include "ls_hal_i2c.h"
#include "platform.h"
#include "compile_flag.h"
#include "ls_soc_gpio.h"

#include "log.h"

#define I2C_MASTER_ROLE 0
#define I2C_SLAVE_ROLE 1

#define CURRENT_ROLE I2C_MASTER_ROLE

#define LED_IO PA01
#define I2C_ADDRESS 0x50
#define BUFFER_LEN 255

enum
{
    start = 0,
    txing,
    txover,
    rxing,
    rxover,
};
#if CURRENT_ROLE == I2C_MASTER_ROLE
typedef HAL_StatusTypeDef (*iic_tx_rx_func)(I2C_HandleTypeDef *, uint16_t, uint8_t*, uint16_t);
typedef HAL_StatusTypeDef (*iic_tx_rx_func)(I2C_HandleTypeDef *, uint16_t, uint8_t*, uint16_t);
#else
typedef HAL_StatusTypeDef (*iic_tx_rx_func)(I2C_HandleTypeDef *, uint8_t*, uint16_t);
typedef HAL_StatusTypeDef (*iic_tx_rx_func)(I2C_HandleTypeDef *, uint8_t*, uint16_t);
#endif
static volatile uint8_t Com_Sta = start;
static I2C_HandleTypeDef I2cHandle;
static uint8_t aRxBuffer[BUFFER_LEN]; //Buffer used for reception 
static uint8_t aTxBuffer[BUFFER_LEN];

#if CURRENT_ROLE == I2C_MASTER_ROLE
static iic_tx_rx_func tx_func = HAL_I2C_Master_Transmit_IT;
static iic_tx_rx_func rx_func = HAL_I2C_Master_Receive_IT;
#else
static iic_tx_rx_func tx_func = HAL_I2C_Slave_Transmit_IT;
static iic_tx_rx_func rx_func = HAL_I2C_Slave_Receive_IT;
#endif

static void Error_Handler(void);
static void toggle_PB14_init(void);

static void iic_tx_rx_test_init(uint8_t);
static void iic_tx_rx_test_it_run(uint8_t);
static bool iic_tx_rx_check_result(uint8_t*);

static void iic_init(void)
{
    I2cHandle.Instance = I2C1;
    I2cHandle.Init.ClockSpeed = I2C_SPEED_FAST_ULTRA_1M;
    I2cHandle.Init.OwnAddress1 = I2C_ADDRESS;
    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
#if CURRENT_ROLE == I2C_MASTER_ROLE
    I2cHandle.Init.OwnAddress2 = 0xFE;
#else 
    I2cHandle.Init.OwnAddress2 = 0x8E;
    I2cHandle.Init.Oar2msk_Mask = 0x7; //0x7: send ack to master call with any addr. 0x6: only send ack when addr matches OA2[7]
#endif
}

int main(void)
{
    sys_init_none();
    toggle_PB14_init();
    pinmux_iic1_init(PB09, PB08);//PA08---SDA   PA09---SCL
    iic_init();
    if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
    {
        Error_Handler();
    }
    uint8_t test_len = 0x59;
    while (1)
    {
        iic_tx_rx_test_init(test_len);
        iic_tx_rx_test_it_run(test_len);
        if (iic_tx_rx_check_result(&test_len))
        {
            static uint16_t led_count = 0;
            if (led_count++ > 20)
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
    // if (Com_Sta == txing)
    // {
    //     Com_Sta = txover;
    // }
    // else if (Com_Sta == rxing)
    // {
    //     Com_Sta = rxover;
    // }
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
static void iic_tx_rx_test_it_run(uint8_t len)
{
#if CURRENT_ROLE == I2C_MASTER_ROLE
    Com_Sta = txing;
    tx_func(&I2cHandle, (uint16_t)I2C_ADDRESS, aTxBuffer, len);
    while (Com_Sta == txing);

    DELAY_US(100);

    Com_Sta = rxing;
    rx_func(&I2cHandle, (uint16_t)I2C_ADDRESS, aRxBuffer, len);
    while (Com_Sta == rxing);
#else
    Com_Sta = rxing;
    rx_func(&I2cHandle, aRxBuffer, len);
    while (Com_Sta == rxing);

    Com_Sta = txing;
    tx_func(&I2cHandle, aRxBuffer, len); // transmit the data just received
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
static void toggle_PB14_init(void)
{
    *(volatile uint32_t*)0x48000418 |= 1 << 0xE;
}
// XIP_BANNED void toggle_PB14(uint16_t num)
void XIP_BANNED_FUNC(toggle_PB14, uint16_t num, ...)
{
    for (uint16_t i = 0; i < num; i++)
    {
        *(volatile uint32_t*)0x48000404 |= 1 << 0xE;  
        // __asm("nop");
        *(volatile uint32_t*)0x48000404 &= ~(1 << 0xE);  
    }
}
