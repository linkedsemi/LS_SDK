#include <string.h>
#include "ls_hal_i2c.h"
#include "ls_soc_gpio.h"
#include "platform.h"

#define I2C_ADDRESS 0x50
#define I2C_RX_DATA_LEN_BYTE 200

static uint8_t g_slaveRxData[I2C_RX_DATA_LEN_BYTE] = { 0 };
static I2C_HandleTypeDef g_i2cHandle;

enum I2c_ReadWriteStatus {
    I2C_IDLE, /* 空闲转态 */
    I2C_RX_START, /* 接收寄存器地址 */
    I2C_RX_OVER, /* 寄存器气质接收完毕 */
    I2C_REG_DATA_TX_START, /* 发送寄存器数据 */
    I2C_REG_DATA_RX_START, /* 接收寄存器数据 */
    I2C_OVER,
};

/* 判断是否接收完成寄存器地址的标志 */
static uint8_t g_slaveStatus = I2C_IDLE;

/* 寄存器的数据，固定为2个字节 */
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
    g_i2cHandle.Init.OA2Mask = 0x7;
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
    pinmux_iic1_init(PB08, PB09); //PB09---SDA   PB08---SCL
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
    /* 寻址成功之后，如果是空闲转态，判断是否接受寄存器地址 */
    if (g_slaveStatus == I2C_IDLE) {
        if (TransferDirection == HAL_I2C_WRITE_DIR) {
            g_slaveStatus = I2C_RX_START;
            if (HAL_I2C_Slave_Seq_Receive_IT(hi2c, &g_slaveRxData[0], I2C_RX_DATA_LEN_BYTE) != HAL_OK) {
                Error_Handler();
            }
        } else {
            LOG_RAW("error dir\r\n");
            Error_Handler();
        }

    } else {
        /* 接受完寄存器地址之后，先发送2个字节的固定数据给主机， 然后再从对应寄存器地址，读两个字节的数据 */
        if (TransferDirection == HAL_I2C_WRITE_DIR) {
            g_slaveStatus = I2C_REG_DATA_RX_START;
            if (HAL_I2C_Slave_Seq_Receive_IT(hi2c, &g_memRegData[0], sizeof(g_memRegData)) != HAL_OK) {
                Error_Handler();
            }
        } else {
            g_slaveStatus = I2C_REG_DATA_TX_START;
            g_memRegData[0] = 0x11;
            g_memRegData[1] = 0xEE;
            /* 发送两个字节的数据给主机 */
            if (HAL_I2C_Slave_Seq_Transmit_IT(hi2c, &g_memRegData[0], sizeof(g_memRegData)) != HAL_OK) {
                /* Transfer error in reception process */
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
    if (g_slaveStatus == I2C_REG_DATA_TX_START) {
        g_slaveStatus = I2C_IDLE; /* mem读成功 */
    }
}

/* 从机接收完中断回调 */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{ 
    if (g_slaveStatus == I2C_RX_START) {
        g_slaveStatus = I2C_RX_OVER; /* 寄存器地址接收完成 */
    } else if (g_slaveStatus == I2C_REG_DATA_RX_START) {
        g_slaveStatus = I2C_IDLE; /* mem写成功 */
        /* mem write数据成功,打印从机收到的寄存器值 */
        LOG_RAW("%x, %x\r\n", g_memRegData[0], g_memRegData[1]);
    }
}

/* i2c错误回调 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c, uint8_t error)
{
    LOG_RAW("HAL_I2C_ErrorCallback %x\r\r", error);
    /* 如果长度错误，打印还有剩余多少长度没有接收或者发送 */
    if (error == HAL_I2C_ERROR_SIZE) {
        /* 如果长度错误是rx的话，是正常的情况，因为设置的rx len是200字节，主机在mem寻址的时候，发送的是2个字节的寄存器地址 */
        LOG_RAW("rx remain %x, tx remain %x \r\r", hi2c->Rx_Env.XferCount,  hi2c->Tx_Env.XferCount);
        /* 长度错误，这个时候已经收到停止信号，重新清空状态 */
        g_slaveStatus = I2C_IDLE;
    }
}
