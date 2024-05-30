/******************************************************************************
 Include
 ******************************************************************************/
#include "ls_hal_uart.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "cpu.h"

/******************************************************************************
 Macro definition
 ******************************************************************************/
#define BUF_SIZE 256

/******************************************************************************
 Function declaration
 ******************************************************************************/
void UART_CharReceptionCallback(void);
void UART_TXEmptyCallback(void);
void UART_CharTransmitCompleteCallback(void);

/******************************************************************************
 Global variable declaration
 ******************************************************************************/
uint8_t ubButtonPress = 0;
uint8_t ubSend = 0;
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
    LL_UART_EnableIT(UART1, UART_IT_RXRD);
    LL_UART_EnableIT(UART1, UART_IT_TXS);
    LL_UART_TransmitData(UART1, aStringToSend[ubSend++]);
    while (1)
    {
    }
}

/**
 * @brief  Function called from USART IRQ Handler when RXNE flag is set
 *         Function is in charge of reading character received on USART RX line.
 * @param  None
 * @retval None
 */
void UART_CharReceptionCallback(void)
{
    uint32_t received_char;

    /* Read Received character. RXNE flag is cleared by reading of DR register */
    received_char = LL_UART_ReceiveData(UART1);
    /* Echo received character on TX */
    LL_UART_TransmitData(UART1, received_char);
}

/**
 * @brief  Function called for achieving next TX Byte sending
 * @param  None
 * @retval None
 */
void UART_TXEmptyCallback(void)
{
    if (ubSend == (ubSizeToSend - 1))
    {
        /* Disable TXE interrupt */
        LL_UART_DisableIT(UART1, UART_IT_TXS);
        /* Enable TC interrupt */
        LL_UART_EnableIT(UART1, UART_IT_TC);
    }
    /* Fill DR with a new char */
    LL_UART_TransmitData(UART1, aStringToSend[ubSend++]);
}

/**
 * @brief  Function called at completion of last byte transmission
 * @param  None
 * @retval None
 */
void UART_CharTransmitCompleteCallback(void)
{
    if (ubSend == sizeof(aStringToSend))
    {
        ubSend = 0;
        /* Disable TC interrupt */
        LL_UART_DisableIT(UART1, UART_IT_TC);
    }
}