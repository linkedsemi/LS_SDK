#ifndef LS_MSP_UART_H_
#define LS_MSP_UART_H_
#include "reg_base_addr.h"
#include "reg_uart_type.h"
#include "reg_dwuart_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef QSH_APB_UART1_ADDR
#define UART1 ((reg_uart_t *)QSH_APB_UART1_ADDR) /*!< LSUART Macro for Register Access*/
#endif
#ifdef QSH_APB_UART2_ADDR
#define UART2 ((reg_uart_t *)QSH_APB_UART2_ADDR)
#endif
#ifdef QSH_APB_DWUART1_ADDR
#define DWUART1 ((reg_dwuart_t *)QSH_APB_DWUART1_ADDR)
#endif
#ifdef QSH_APB_DWUART2_ADDR
#define DWUART2 ((reg_dwuart_t *)QSH_APB_DWUART2_ADDR)
#endif


void LL_UART1_MSP_Init(void);
void LL_UART1_MSP_DeInit(void);
void LL_UART2_MSP_Init(void);
void LL_UART2_MSP_DeInit(void);
void LL_UART3_MSP_Init(void);
void LL_UART3_MSP_DeInit(void);
void LL_DWUART1_MSP_Init(void);
void LL_DWUART1_MSP_DeInit(void);
void LL_DWUART2_MSP_Init(void);
void LL_DWUART2_MSP_DeInit(void);

struct __UART_HandleTypeDef;
void HAL_UART_MSP_Init(struct __UART_HandleTypeDef *inst);
void HAL_UART_MSP_DeInit(struct __UART_HandleTypeDef *inst);
void HAL_UART_MSP_Busy_Set(struct __UART_HandleTypeDef *inst);
void HAL_UART_MSP_Idle_Set(struct __UART_HandleTypeDef *inst);
uint8_t HAL_UART_TX_DMA_Handshake_Get(struct __UART_HandleTypeDef *inst);
uint8_t HAL_UART_RX_DMA_Handshake_Get(struct __UART_HandleTypeDef *inst);

struct __DWUART_HandleTypeDef;
void HAL_DWUART_MSP_Init(struct __DWUART_HandleTypeDef *inst);
void HAL_DWUART_MSP_DeInit(struct __DWUART_HandleTypeDef *inst);
void HAL_DWUART_MSP_Busy_Set(struct __DWUART_HandleTypeDef *inst);
void HAL_DWUART_MSP_Idle_Set(struct __DWUART_HandleTypeDef *inst);
uint8_t HAL_DWUART_TX_DMA_Handshake_Get(struct __DWUART_HandleTypeDef *inst);
uint8_t HAL_DWUART_RX_DMA_Handshake_Get(struct __DWUART_HandleTypeDef *inst);

#ifdef __cplusplus
}
#endif

#endif
