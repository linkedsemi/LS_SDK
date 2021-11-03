#ifndef UART_MISC_H_
#define UART_MISC_H_
// UART FIFO Control - FCR
#define UART_RXFIFORST      0x2     // Receiver FIFO reset
#define UART_TXFIFORST      0x4     // Transmit FIFO reset
#define UART_FIFO_RL_1      0x0     // FIFO trigger level   
#define UART_FIFO_RL_4      0x1
#define UART_FIFO_RL_8      0x2
#define UART_FIFO_RL_14     0x3
#define UART_FIFO_TL_0      0x0     // FIFO trigger level 
#define UART_FIFO_TL_2      0x1     // FIFO trigger level 
#define UART_FIFO_TL_4      0x2     // FIFO trigger level 
#define UART_FIFO_TL_8      0x3


#define HAL_UART_ERROR_NONE              0x00000000U   /*!< No error            */
#define HAL_UART_ERROR_OE                0x00000002U   /*!< Overrun error       */
#define HAL_UART_ERROR_PE                0x00000004U   /*!< Parity error        */
#define HAL_UART_ERROR_FE                0x00000008U   /*!< Frame error         */
#define HAL_UART_ERROR_DMA               0x00000010U   /*!< DMA transfer error  */

#define UART_IT_RXRD                     (0X0001)
#define UART_IT_TXS                      (0x0002)
#define UART_IT_RXS                      (0x0004)
#define UART_IT_MDDS                     (0x0008)
#define UART_IT_RTO                      (0x0010)
#define UART_IT_BUSY                     (0x0020)
#define UART_IT_ABE                      (0x0040)
#define UART_IT_ABTO                     (0x0080)
#define UART_ITLINBK                     (0x0100)
#define UART_IT_TC                       (0x0200)
#define UART_IT_EOB                      (0x0400)
#define UART_IT_CM                       (0x0800)

#define UART_SR_DR                       (0X0001)
#define UART_SR_OE                       (0X0002)
#define UART_SR_PE                       (0X0004)
#define UART_SR_FE                       (0X0008)
#define UART_SR_BI                       (0X0010)
#define UART_SR_TBEM                     (0X0020)
#define UART_SR_TEMT                     (0X0040)
#define UART_SR_RFE                      (0X0080)
#define UART_SR_BUSY                     (0X0100)
#define UART_SR_TFNF                     (0X0200)
#define UART_SR_TFEN                     (0X0400)
#define UART_SR_RFNE                     (0X0800)
#define UART_SR_RFF                      (0X1000)
#define UART_SR_DCTS                     (0X2000)
#define UART_SR_CTS                      (0X4000)

#define UART_FCR_RX_DEPTH                (0X0)

#endif //END UART_MISC_H_
