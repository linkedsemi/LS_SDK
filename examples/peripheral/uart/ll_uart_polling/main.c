/******************************************************************************
 Include
 ******************************************************************************/
#include <stdio.h>
#include "ls_hal_uart.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "cpu.h"
#include "systick.h"
#include "field_manipulate.h"
/******************************************************************************
 Macro definition
 ******************************************************************************/
#define BUF_SIZE 256

/******************************************************************************
 Function declaration
 ******************************************************************************/
uint32_t LL_UART_Transmit(reg_uart_t *UARTx, uint8_t *pData, uint16_t Size, uint32_t Timeout);
uint32_t LL_UART_Receive(reg_uart_t *UARTx, uint8_t *pData, uint16_t Size, uint32_t Timeout);
/******************************************************************************
 Global variable declaration
 ******************************************************************************/
uint8_t aStringToSend[] = "USART LL API Example : TX in Polling mode\r\nConfiguration UART 115200 bps, 8 data bit/1 stop bit/No parity/No HW flow control\r\n";
uint8_t ubSizeToSend = sizeof(aStringToSend);
uint8_t test_zone_a[BUF_SIZE];

/**
 * @brief Uart initialization function
 *
 */
static void uart_init(void)
{

    LL_UART1_MSP_Init();
    clr_pending_irq(UART1_IRQn);
    enable_irq(UART1_IRQn);
    LL_UART_SetBaudRate(UART1, UART_BAUDRATE_115200);
    LL_UART_EnableTFRST(UART1);
    LL_UART_EnableRFRST(UART1);
    LL_UART_EnableFIFO(UART1);

    LL_UART_SetDataWidth(UART1, LL_UART_DATAWIDTH_8B);
    LL_UART_SetParity(UART1, LL_UART_PARITY_NONE);
    LL_UART_EnableLSB(UART1);
    LL_UART_EnableDirectionRx(UART1);
    LL_UART_DisableBRWEN(UART1);
    LL_UART_DisableHWFlowCtrl(UART1);
    LL_UART_SetStopBitsLength(UART1, LL_UART_STOPBITS_1);
}

/**
 * @brief main
 *
 * @return int
 */
int main()
{
    sys_init_none();
    pinmux_uart1_init(PB00, PB01);
    io_pull_write(PB01, IO_PULL_UP);
    uart_init();
    // LL_UART_Receive(UART1, test_zone_a, 5, 10000);
    // LL_UART_Transmit(UART1, test_zone_a, 5, 1000);
    while (1)
    {
        LL_UART_Transmit(UART1, aStringToSend, ubSizeToSend, 1000);
    }
}

static bool uart_flag_poll(va_list va)
{
    reg_uart_t *UARTx = va_arg(va, reg_uart_t *);
    uint32_t flag = va_arg(va, uint32_t);
    if (LL_UART_IsActiveFlag(UARTx, flag))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Function called for achieving TX buffer sending
 * 
 * @param UARTx UART Instance
 * @param pData Pointer to data buffer (uint8_t data elements).
 * @param Size  Amount of data elements (uint8_t) to be sent
 * @param Timeout  Timeout duration
 * @return uint32_t status
 */
uint32_t LL_UART_Transmit(reg_uart_t *UARTx, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = systick_get_value();
    /* Check that a Tx process is not already ongoing */
    if (!LL_UART_IsActiveFlag(UARTx, UART_SR_BUSY))
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return ERROR;
        }

        /* Init tickstart for timeout managment */
        if (Timeout != HAL_MAX_DELAY)
        {
            while (Size > 0U)
            {
                if (systick_poll_timeout(tickstart, timeout, uart_flag_poll, UARTx, UART_SR_TFNF))
                {
                    return ERROR;
                }
                else
                {
                    // Transmit FIFO Not Full
                    Size--;
                    LL_UART_TransmitData(UARTx, *pData++);
                    if (Size == 0)
                    {
                        break;
                    }
                }
            }
            // Wait until TX Finish
            if (systick_poll_timeout(tickstart, timeout, uart_flag_poll, UARTx, UART_SR_TEMT))
            {
                return ERROR;
            }
        }
        else
        {
            while (Size > 0U)
            {
                // Wait until TX fifo empty
                if (LL_UART_IsActiveFlag(UARTx, UART_SR_TFNF))
                {
                    Size--;
                    LL_UART_TransmitData(UARTx, *pData++);
                }
            }
            // Wait until TX Finish
            while (!LL_UART_IsActiveFlag(UARTx, UART_SR_TEMT))
                ;
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief Function called for achieving RX buffer 
 * 
 * @param UARTx UART Instance
 * @param pData Pointer to data buffer (uint8_t data elements).
 * @param Size  Amount of data elements (uint8_t) to be sent
 * @param Timeout  Timeout duration
 * @return uint32_t status
 */
uint32_t LL_UART_Receive(reg_uart_t *UARTx, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = systick_get_value();

    /* Check that a Rx process is not already ongoing */
    if (!LL_UART_IsActiveFlag(UARTx, UART_SR_BUSY))
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return ERROR;
        }

        /* Init tickstart for timeout managment */
        // todo
        if (Timeout != HAL_MAX_DELAY)
        {
            /* Check the remain data to be received */
            while (Size > 0U)
            {
                if (systick_poll_timeout(tickstart, timeout, uart_flag_poll, UARTx, UART_SR_RFNE))
                {
                    return ERROR;
                }
                else
                {
                    Size--;
                    *pData++ = LL_UART_ReceiveData(UART1);
                }
            }
        }
        else
        {
            while (Size > 0U)
            {
                if (LL_UART_IsActiveFlag(UARTx, UART_SR_RFNE))
                {
                    Size--;
                    *pData++ = LL_UART_ReceiveData(UART1);
                }
            }
        }
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}