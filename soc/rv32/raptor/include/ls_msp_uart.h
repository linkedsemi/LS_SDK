#ifndef LS_MSP_UART_H_
#define LS_MSP_UART_H_
#include "reg_base_addr.h"
#include "reg_uart_type.h"
#include "reg_dwuart_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef REG_DWUART0_BASE
#define DWUART0 ((reg_dwuart_t *)REG_DWUART0_BASE)
#endif
#ifdef REG_DWUART1_BASE
#define DWUART1 ((reg_dwuart_t *)REG_DWUART1_BASE)
#endif
#ifdef REG_DWUART2_BASE
#define DWUART2 ((reg_dwuart_t *)REG_DWUART2_BASE)
#endif
#ifdef REG_DWUART3_BASE
#define DWUART3 ((reg_dwuart_t *)REG_DWUART3_BASE)
#endif
#ifdef REG_DWUART4_BASE
#define DWUART4 ((reg_dwuart_t *)REG_DWUART4_BASE)
#endif
#ifdef REG_DWUART5_BASE
#define DWUART5 ((reg_dwuart_t *)REG_DWUART5_BASE)
#endif
#ifdef REG_DWUART6_BASE
#define DWUART6 ((reg_dwuart_t *)REG_DWUART6_BASE)
#endif
#ifdef REG_DWUART7_BASE
#define DWUART7 ((reg_dwuart_t *)REG_DWUART7_BASE)
#endif
#ifdef REG_DWUART8_BASE
#define DWUART8 ((reg_dwuart_t *)REG_DWUART8_BASE)
#endif
#ifdef REG_DWUART9_BASE
#define DWUART9 ((reg_dwuart_t *)REG_DWUART9_BASE)
#endif
#ifdef REG_DWUART10_BASE
#define DWUART10 ((reg_dwuart_t *)REG_DWUART10_BASE)
#endif
#ifdef REG_DWUART11_BASE
#define DWUART11 ((reg_dwuart_t *)REG_DWUART11_BASE)
#endif
#ifdef REG_DWUART12_BASE
#define DWUART12 ((reg_dwuart_t *)REG_DWUART12_BASE)
#endif
#ifdef REG_DWUART13_BASE
#define DWUART13 ((reg_dwuart_t *)REG_DWUART13_BASE)
#endif
#ifdef REG_DWUART14_BASE
#define DWUART14 ((reg_dwuart_t *)REG_DWUART14_BASE)
#endif
#ifdef REG_DWUART15_BASE
#define DWUART15 ((reg_dwuart_t *)REG_DWUART15_BASE)
#endif

void LL_DWUART1_MSP_Init(void);
void LL_DWUART1_MSP_DeInit(void);
void LL_DWUART2_MSP_Init(void);
void LL_DWUART2_MSP_DeInit(void);
void LL_DWUART8_MSP_Init(void);
void LL_DWUART8_MSP_DeInit(void);

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
