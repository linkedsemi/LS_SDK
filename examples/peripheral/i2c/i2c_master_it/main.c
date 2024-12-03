#include <string.h>
#include "ls_hal_i2c.h"
#include "ls_soc_gpio.h"
#include "platform.h"

#define I2C_ADDRESS 0x50

static I2C_HandleTypeDef g_i2cHandle;

static volatile uint8_t g_materTxOver = 0;
static volatile uint8_t g_materRxOver = 0;

static void iic_init(void)
{
    g_i2cHandle.Instance = I2C1;
    g_i2cHandle.Init.ClockSpeed = I2C_SPEED_NORMAL_100K; /* 主机的速度 */
    g_i2cHandle.Init.OwnAddress1 = I2C_ADDRESS;
    g_i2cHandle.Init.OA1_Enable = 1;
    g_i2cHandle.Init.OA1_10bitMode = 0;
    g_i2cHandle.Init.OA2_Enable = 0;
    g_i2cHandle.Init.OwnAddress2 = 0x7E;
    g_i2cHandle.Init.OA2Mask = 0x7;
}

static void Error_Handler(void)
{
    LOG_RAW("Error_Handler\r\n");
    while (1) {
    }
}

int main()
{
    sys_init_none();
    LOG_RAW("sys_init_none\r\n");

    /* 初始化i2c对应的gpio，以及对i2c进行配置 */
    pinmux_iic1_init(PB08, PB09); //PB09---SDA   PB08---SCL
    iic_init();
    if (HAL_I2C_Init(&g_i2cHandle) != HAL_OK)
    {
        Error_Handler();
    }

    uint8_t regData[2] = {0};
    while(1) {
        regData[0] = 0x55;
        regData[1] = 0xAA;

        /* 往从机发送两个字节的数据 */
        HAL_I2C_Master_Transmit_IT(&g_i2cHandle, I2C_ADDRESS, &regData[0], sizeof(regData));
        while (g_materTxOver == 0);
        g_materTxOver = 0;


        /* 从从机回读2个字节的数据 */
        HAL_I2C_Master_Receive_IT(&g_i2cHandle, I2C_ADDRESS, &regData[0], sizeof(regData));
        while (g_materRxOver == 0);
        g_materRxOver = 0;

        /* 延迟1s打印回读到的数据 */
        DELAY_US(1000 * 1000);
        LOG_RAW("rxData: ");
        for (uint8_t i = 0; i < 2; i++) {
            LOG_RAW("%lx, ", regData[i]);
        }
        LOG_RAW("\r\n");
    }

    
    return 0;
}

/* 主机发送完成回调 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    LOG_I("HAL_I2C_MasterTxCpltCallback\r\n");
    g_materTxOver = 1; /* 主机发送完毕 */
}

/* 主机接收完中断回调 */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{ 
    LOG_RAW("HAL_I2C_MasterRxCpltCallback\r\n");
    g_materRxOver = 1;
}

/* i2c错误回调 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c, uint8_t error)
{
    LOG_RAW("HAL_I2C_ErrorCallback %x\r\r", error);
}
