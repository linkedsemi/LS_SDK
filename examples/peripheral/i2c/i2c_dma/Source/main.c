#include <string.h>
#include <stdlib.h>
#include "ls_hal_i2c.h"
#include "platform.h"
#include "compile_flag.h"
#include "ls_soc_gpio.h"

#include "ls_hal_timer.h"
#include "log.h"
#if DMACV2
#include "ls_hal_dmacv2.h"
#else
#include "ls_hal_dmac.h"
#endif

#define I2C_SPEED I2C_SPEED_FAST_400K
#define I2C_ADDRESS 0x50
#define BUFFER_LEN 255
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
static DMA_RAM_ATTR uint8_t aRxBuffer[BUFFER_LEN]; //Buffer used for reception 
static DMA_RAM_ATTR uint8_t aTxBuffer[BUFFER_LEN];

static void Error_Handler(void);
static void toggle_debug_IO_init(void);
void toggle_debug_IO(uint16_t);

static void iic_tx_rx_test_init(uint8_t);
static void iic_tx_rx_test_dma_run(uint8_t);
static bool iic_tx_rx_check_result(uint8_t*);

DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);

static void iic_dma_channel_init(void)
{
    DMA_CONTROLLER_INIT(dmac1_inst);
    I2cHandle.DMAC_Instance = &dmac1_inst;
    I2cHandle.Tx_Env.DMA.DMA_Channel = 0;
    I2cHandle.Rx_Env.DMA.DMA_Channel = 1;
}

static void iic_init(void)
{
    I2cHandle.Instance = I2C1;
    I2cHandle.Init.ClockSpeed = I2C_SPEED;
    I2cHandle.Init.OwnAddress1 = I2C_ADDRESS;
    I2cHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    I2cHandle.Init.OwnAddress2 = 0x7E;
}
static uint8_t test_len = 1;
int main(void)
{
    sys_init_none();
    toggle_debug_IO_init();
    pinmux_iic1_init(PB09, PB08); //PB08---SDA   PB09---SCL
    iic_init();
    iic_dma_channel_init();
    if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
    {
        Error_Handler();
    }

    while (1)
    {
        iic_tx_rx_test_init(test_len);
        iic_tx_rx_test_dma_run(test_len);
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

void HAL_I2C_DMA_TxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (Com_Sta == txing)
    {
        Com_Sta = txover;
    }
}
void HAL_I2C_DMA_RxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (Com_Sta == rxing)
    {
        Com_Sta = rxover;
    }
}

static bool iic_tx_rx_check_result(uint8_t *len)
{
    bool result = true;
    result = memcmp(aTxBuffer, aRxBuffer, *len) == 0;
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
    DELAY_US(5000); // Slave may run at a lower AHB, so master has to delay enough to await slave ready
}
static void iic_tx_rx_test_dma_run(uint8_t len)
{
    Com_Sta = txing;
    HAL_I2C_Master_Transmit_DMA(&I2cHandle, (uint16_t)I2C_ADDRESS, aTxBuffer, len);
    while (Com_Sta == txing);

    DELAY_US(1200);

    Com_Sta = rxing;
    HAL_I2C_Master_Receive_DMA(&I2cHandle, (uint16_t)I2C_ADDRESS, aRxBuffer, len);
    while (Com_Sta == rxing);
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
