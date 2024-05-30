#include <stdio.h>
#include "ls_hal_uart.h"
#include "field_manipulate.h"
#include "log.h"
#include "systick.h"

extern void UART_CharReceptionCallback(void);
extern void UART_TXEmptyCallback(void);
extern void UART_CharTransmitCompleteCallback(void);
/**
 * @}
 */

void LL_UART1_Handler(void)
{
    if (LL_UART_IsActiveFlagIT(UART1, UART_IT_RXRD) && LL_UART_IsEnabledIT(UART1, UART_IT_RXRD))
    {
        LL_UART_ClearFlagIT(UART1, UART_IT_RXRD);
        UART_CharReceptionCallback();
    }
    else if (LL_UART_IsActiveFlagIT(UART1, UART_IT_TXS) && LL_UART_IsEnabledIT(UART1, UART_IT_TXS))
    {
        LL_UART_ClearFlagIT(UART1, UART_IT_TXS);
        UART_TXEmptyCallback();
    }
    else if (LL_UART_IsActiveFlagIT(UART1, UART_IT_TC) && LL_UART_IsEnabledIT(UART1, UART_IT_TC))
    {
        LL_UART_ClearFlagIT(UART1, UART_IT_TC);
        UART_CharTransmitCompleteCallback();
    }
}

void LL_UART2_Handler(void)
{
    ;
}

void LL_UART3_Handler(void)
{
    ;
}

/**
 * @}
 */
