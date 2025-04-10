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
    g_i2cHandle.Init.OA2Mask = 0x7;
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
    pinmux_iic1_init(PB08, PB09); //PB09---SDA   PB08---SCL
    iic_init();
    if (HAL_I2C_Init(&g_i2cHandle) != HAL_OK)
    {
        Error_Handler();
    }

    /* 寄存器地址 */
    uint16_t regAddr = 0x1234;

    while(1) {
        /* 从寄存器地址0x1234，读取两个字节的数据 */
        uint8_t regData[2] = {0};
        g_memReadOverFlag = 0;
        HAL_I2C_Mem_Read_IT(&g_i2cHandle, I2C_ADDRESS, regAddr, sizeof(regAddr), &regData[0], sizeof(regData));
        while (g_memReadOverFlag == 0); /* 等待读寄存器操作完成 */

        /* 打印读到的寄存器数据 */
        LOG_RAW("rxData: ");
        for (uint8_t i = 0; i < 2; i++) {
            LOG_RAW("%lx, ", regData[i]);
        }
        LOG_RAW("\r\n");
        DELAY_US(1000);
        /* 往寄存器地址0x1234，写入两个字节的数据0x55和0xAA */
        regData[0] = 0x55;
        regData[1] = 0xAA;
        g_memWriteOverFlag = 0;
        HAL_I2C_Mem_Write_IT(&g_i2cHandle, I2C_ADDRESS, regAddr, sizeof(regAddr), &regData[0], sizeof(regData));
        while (g_memWriteOverFlag == 0); /* 等待写寄存器操作完成 */

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
        hi2c->State = 0; /* 主机发送完成，清除状态 */
    }
}

/* 主机接收完中断回调 */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{ 
    LOG_RAW("HAL_I2C_MasterRxCpltCallback\r\n");
    if (g_memReadOverFlag == 0) {
        g_memReadOverFlag = 1;
        hi2c->State = 0; /* 主机接收完成，清除状态 */
    }

}

/* i2c错误回调 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c, uint8_t error)
{
    /* 主机写状态，收到了ncak的标志，判断当前是否还存在没有接收的字节 */
    /* 如果所有字节都接收完了，则该nack表示的是，从机所有数据已经收到,返回的nack，并非错误，直接返回 */
    if (error == HAL_I2C_ERROR_NACKF) {
        if ((g_memWriteOverFlag == 0) && (hi2c->Rx_Env.XferCount == 0)) {
            return;
        }
    }
    LOG_RAW("HAL_I2C_ErrorCallback %x\r\r", error);
}

