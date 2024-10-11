#include <string.h>
#include "ls_hal_i2c.h"
#include "ls_soc_gpio.h"
#include "platform.h"

#define I2C_ADDRESS 0x50

static I2C_HandleTypeDef g_i2cHandle;

static volatile uint8_t g_memReadOverFlag = 0;
static volatile uint8_t g_memWriteOverFlag = 0;

static void iic_init(void)
{
    g_i2cHandle.Instance = I2C1;
    g_i2cHandle.Init.ClockSpeed = I2C_SPEED_NORMAL_100K; /* 主机的速度 */
    g_i2cHandle.Init.OwnAddress1 = I2C_ADDRESS;
    g_i2cHandle.Init.OA1_Enable = 1;
    g_i2cHandle.Init.OA1_10bitMode = 0;
    g_i2cHandle.Init.OA2_Enable = 0;
    g_i2cHandle.Init.OwnAddress2 = 0x7E;
    g_i2cHandle.Init.OA2Mask = 0x7; //0x7: send ack to master call with any addr. 0x6: only send ack when addr matches OA2[7]
}

static void Error_Handler(void)
{
    LOG_RAW("Error_Handler\r\n");
    while (1) { };
}

int main()
{
    sys_init_none();
    LOG_RAW("sys_init_none\r\n");

    /* 初始化i2c对应的gpio，以及对i2c进行配置 */
    pinmux_iic1_init(PB09, PB08); //PB08---SDA   PB09---SCL
    iic_init();
    if (HAL_I2C_Init(&g_i2cHandle) != HAL_OK)
    {
        Error_Handler();
    }

    /* 寄存器地址 */
    uint16_t regAddr = 0x1234;

    while(1) {
        /* 从寄存器地址0x1010，读取两个字节的数据 */
        uint8_t regData[2] = {0};
        g_memReadOverFlag = 0;
        HAL_I2C_Mem_Read_IT(&g_i2cHandle, I2C_ADDRESS, regAddr, sizeof(regAddr), &regData[0], sizeof(regData));
        while (g_memReadOverFlag == 0);

        /* 打印读到的寄存器数据 */
        LOG_RAW("rxData: ");
        for (uint8_t i = 0; i < 2; i++) {
            LOG_RAW("%lx, ", regData[i]);
        }
        LOG_RAW("\r\n");

        /* 往寄存器地址0x1010，写入两个字节的数据0x55和0xAA */
        regData[0] = 0x55;
        regData[1] = 0xAA;
        g_memWriteOverFlag = 0;
        HAL_I2C_Mem_Write_IT(&g_i2cHandle, I2C_ADDRESS, regAddr, sizeof(regAddr), &regData[0], sizeof(regData));
        while (g_memWriteOverFlag == 0);

        /* 延迟1s */
        DELAY_US(1000 * 1000);
    }

    
    return 0;
}

/* 主机发送完成回调 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    LOG_I("HAL_I2C_MasterTxCpltCallback\r\n");
    if (g_memWriteOverFlag == 0) {
        g_memWriteOverFlag = 1;
    }
}

/* 主机接收完中断回调 */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{ 
    LOG_RAW("HAL_I2C_MasterRxCpltCallback\r\n");
    if (g_memReadOverFlag == 0) {
        g_memReadOverFlag = 1;
    }

}

/* i2c错误回调 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c, uint8_t error)
{
    LOG_RAW("HAL_I2C_ErrorCallback %x\r\r", error);
    HAL_I2C_EnableListen_IT(&g_i2cHandle);
}