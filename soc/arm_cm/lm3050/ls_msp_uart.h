#ifndef LS_MSP_UART_H_
#define LS_MSP_UART_H_
#include "reg_base_addr.h"
#include "reg_uart_type.h"

#ifdef UART1_BASE_ADDR
#define UART1 ((reg_uart_t *)UART1_BASE_ADDR) /*!< LSUART Macro for Register Access*/
#endif
#ifdef UART2_BASE_ADDR
#define UART2 ((reg_uart_t *)UART2_BASE_ADDR)
#endif
#ifdef UART3_BASE_ADDR
#define UART3 ((reg_uart_t *)UART3_BASE_ADDR)
#endif
#ifdef UART4_BASE_ADDR
#define UART4 ((reg_uart_t *)UART4_BASE_ADDR)
#endif
#ifdef UART5_BASE_ADDR
#define UART5 ((reg_uart_t *)UART5_BASE_ADDR)
#endif


void LL_UART1_MSP_Init(void);
void LL_UART1_MSP_DeInit(void);
void LL_UART2_MSP_Init(void);
void LL_UART2_MSP_DeInit(void);
void LL_UART3_MSP_Init(void);
void LL_UART3_MSP_DeInit(void);
void LL_UART4_MSP_Init(void);
void LL_UART4_MSP_DeInit(void);
void LL_UART5_MSP_Init(void);
void LL_UART5_MSP_DeInit(void);

struct __UART_HandleTypeDef;
void HAL_UART_MSP_Init(struct __UART_HandleTypeDef *inst);
void HAL_UART_MSP_DeInit(struct __UART_HandleTypeDef *inst);
void HAL_UART_MSP_Busy_Set(struct __UART_HandleTypeDef *inst);
void HAL_UART_MSP_Idle_Set(struct __UART_HandleTypeDef *inst);
uint8_t HAL_UART_TX_DMA_Handshake_Get(struct __UART_HandleTypeDef *inst);
uint8_t HAL_UART_RX_DMA_Handshake_Get(struct __UART_HandleTypeDef *inst);


#endif
