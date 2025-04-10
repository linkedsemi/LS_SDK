#include <string.h>
#include "ls_hal_i2c.h"
#include "ls_soc_gpio.h"
#include "platform.h"

#define I2C_ADDRESS 0x50

static I2C_HandleTypeDef g_i2cHandle;

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
    HAL_StatusTypeDef retVal = HAL_OK;
    while(1) {
        /* 从寄存器地址0x1234，读取两个字节的数据 */
        uint8_t regData[2] = {0};
        retVal = HAL_I2C_Mem_Read(&g_i2cHandle, I2C_ADDRESS, regAddr, sizeof(regAddr), &regData[0], sizeof(regData));
        if (retVal != HAL_OK) {
            LOG_RAW("mem read fail %x\r\n", retVal);
        } else {     
            /* 打印读到的寄存器数据 */
            LOG_RAW("rxData: ");
            for (uint8_t i = 0; i < 2; i++) {
                LOG_RAW("%lx, ", regData[i]);
            }
            LOG_RAW("\r\n");
        }
        DELAY_US(1000);
        /* 往寄存器地址0x1234，写入两个字节的数据0x55和0xAA */
        regData[0] = 0x55;
        regData[1] = 0xAA;
        retVal = HAL_I2C_Mem_Write(&g_i2cHandle, I2C_ADDRESS, regAddr, sizeof(regAddr), &regData[0], sizeof(regData));
        if (retVal != HAL_OK) {
            LOG_RAW("mem write fail %x\r\n", retVal);
        }

        /* 延迟1s */
        DELAY_US(1000 * 1000);
    }

    return 0;
}

/* i2c错误回调 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c, uint8_t error)
{
    LOG_RAW("HAL_I2C_ErrorCallback %x\r\r", error);
}

