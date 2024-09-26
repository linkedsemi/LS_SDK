#include <string.h>
#include "ls_hal_i2c.h"
#include "ls_soc_gpio.h"
#include "platform.h"

#define I2C_ADDRESS 0x50

static uint16_t g_RegAddr = 0;
static I2C_HandleTypeDef g_i2cHandle;

enum I2c_ReadWriteStatus {
    I2C_IDLE,
    I2C_START,
    I2C_OVER,
};

/* 判断是否接收完成寄存器地址的标志 */
static uint8_t g_rxRegAddrStatus = I2C_IDLE;

/* i2c主机，从寄存器读的状态位 */
static uint8_t g_memReadStatus = I2C_IDLE;

/* i2c主机， 往寄存器写的标志位 */
static uint8_t g_memWriteStatus = I2C_IDLE;

/* 寄存器的数据 */
uint8_t g_memRegData[2] = { 0 };

static void iic_init(void)
{
    g_i2cHandle.Instance = I2C1;
    g_i2cHandle.Init.ClockSpeed = I2C_SPEED_NORMAL_100K; /* 从机的速度 */
    g_i2cHandle.Init.OwnAddress1 = I2C_ADDRESS; /* 从机的第一个地址 */
    g_i2cHandle.Init.OA1_Enable = 1; /* 使能地址1 */
    g_i2cHandle.Init.OA1_10bitMode = 0; /* 使用7bit的地址位 */
    g_i2cHandle.Init.OA2_Enable = 0;
    g_i2cHandle.Init.OwnAddress2 = 0x7E;
    g_i2cHandle.Init.OA2Mask = 0x7; //0x7: send ack to master call with any addr. 0x6: only send ack when addr matches OA2[7]
}

static void Error_Handler(void)
{
    LOG_RAW("Error_Handler\r\n");
    while (1) {};
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
    HAL_I2C_EnableListen_IT(&g_i2cHandle);
    while(1) {

    };
    return 0;
}

/* 寻址成功回调 */
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    /* 寻址成功之后，判断是否接收完成寄存器地址 */
    if (g_rxRegAddrStatus == I2C_IDLE) {
        g_rxRegAddrStatus = I2C_START;
        if (HAL_I2C_Slave_Seq_Receive_IT(hi2c, (uint8_t *)&g_RegAddr, sizeof(g_RegAddr)) != HAL_OK) {
            Error_Handler();
        }
    } else {
        /* 接受完寄存器地址之后，先发送2个字节的固定数据给主机， 然后再从对应寄存器地址，读两个字节的数据 */
        if (g_memReadStatus == I2C_IDLE) {
            g_memRegData[0] = 0x11;
            g_memRegData[1] = 0xEE;
            g_memReadStatus = I2C_START;
            /* 发送两个字节的数据给主机 */
            if (HAL_I2C_Slave_Seq_Transmit_IT(hi2c, &g_memRegData[0], sizeof(g_memRegData)) != HAL_OK) {
                /* Transfer error in reception process */
                Error_Handler();
            }
        } else {
            g_memWriteStatus = I2C_START;
            /* 从主机接收两个字节的数据 */
            if (HAL_I2C_Slave_Seq_Receive_IT(hi2c, &g_memRegData[0], sizeof(g_memRegData)) != HAL_OK) {
                Error_Handler();
            }
        }
        
    }

}
/* 从机发送完成回调 */
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    LOG_I("HAL_I2C_SlaveTxCpltCallback\r\n");
    /* 发送数据给主机完成, */
    if (g_memReadStatus == I2C_START) {
        g_memReadStatus = I2C_OVER; /* mem读成功 */
        g_rxRegAddrStatus = I2C_IDLE; /* 重新接收寄存器地址 */
    }
}

/* 从机接收完中断回调 */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{ 
    if (g_rxRegAddrStatus == I2C_START) {
        g_rxRegAddrStatus = I2C_OVER; /* 寄存器地址接收完成，可在后面增加判断，判断寄存器地址是否为从机的寄存器地址 */
        LOG_RAW("regAddr%x\r\n", g_RegAddr);
    } else if (g_memWriteStatus == I2C_START) {
        /* mem write数据成功,打印从机收到的寄存器值 */
        LOG_RAW("%x, %x\r\n", g_memRegData[0], g_memRegData[1]);
        g_memWriteStatus = I2C_OVER; /* 寄存器 写完成 */
        g_memReadStatus = I2C_IDLE; /* 重新设置寄存器读状态为空闲，等待读 */
        g_rxRegAddrStatus = I2C_IDLE; /* 重新设置寄存器地址接收转态为空闲，先接收寄存器地址 */
    }
}

/* i2c错误回调 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c, uint8_t error)
{
    LOG_RAW("HAL_I2C_ErrorCallback %x\r\r", error);
    HAL_I2C_EnableListen_IT(&g_i2cHandle);
}
