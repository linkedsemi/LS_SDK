
#include <stdio.h>
#include "ls_hal_uart.h"
#include "field_manipulate.h"
#include "log.h"
#include "systick.h"

static void UART_SetConfig(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{
    /* Check the UART handle allocation */
    if (huart == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }

    /* Check the parameters */
    //TODO
    HAL_UART_MSP_Init(huart);
    HAL_UART_MSP_Busy_Set(huart);
    /* Set the UART Communication parameters */
    UART_SetConfig(huart);

    /* Initialize the UART state */
    huart->gState = HAL_UART_STATE_READY;
    huart->RxState = HAL_UART_STATE_READY;

    return HAL_OK;
}

//HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart)
//HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength)
//HAL_StatusTypeDef HAL_Smartcard_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod)
//TODO

HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart)
{
    /* Check the UART handle allocation */
    if (huart == NULL)
    {
        return HAL_INVALIAD_PARAM;
    }
    while(REG_FIELD_RD(huart->UARTX->SR,UART_SR_BUSY) != 0);
    /* Check the parameters */
    //  assert_param(IS_UART_INSTANCE(huart->UARTX));
    HAL_UART_MSP_DeInit(huart);
    HAL_UART_MSP_Idle_Set(huart);

    huart->gState = HAL_UART_STATE_RESET;
    huart->RxState = HAL_UART_STATE_RESET;
    return HAL_OK;
}

static bool uart_flag_poll(va_list va)
{
      UART_HandleTypeDef *huart = va_arg(va,UART_HandleTypeDef *);
      uint32_t flag = va_arg(va,uint32_t);
      if (huart->UARTX->SR & flag)
      {
        return true;
      }
      else
      {
        return false;
      }
}

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = systick_get_value();
    /* Check that a Tx process is not already ongoing */
    if (huart->gState == HAL_UART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return  HAL_INVALIAD_PARAM;
        }

        huart->gState = HAL_UART_STATE_BUSY_TX;
        /* Init tickstart for timeout managment */
        //TODO
        huart->Tx_Env.Interrupt.XferCount = Size;
        if (Timeout != HAL_MAX_DELAY)
        {
            while (huart->Tx_Env.Interrupt.XferCount > 0U )
            {
                if(systick_poll_timeout(tickstart,timeout,uart_flag_poll,huart,UART_SR_TFEM))
                {
                    huart->gState = HAL_UART_STATE_READY;
                    return HAL_TIMEOUT;
                }
               else
                {
                    //Transmit FIFO Not Full
                    huart->Tx_Env.Interrupt.XferCount--;
                    huart->UARTX->TBR = (*pData++ & (uint8_t)0xFF);
                    if (huart->Tx_Env.Interrupt.XferCount == 0)
                    {
                        break;
                    }
                }
            }
            // Wait until TX Finish
            if(systick_poll_timeout(tickstart,timeout,uart_flag_poll,huart,UART_SR_TEMT))
            {
                huart->gState = HAL_UART_STATE_READY;
                return HAL_TIMEOUT;
            }
        }
        else
        {
            while (huart->Tx_Env.Interrupt.XferCount > 0U )
            {   
                // Wait until TX fifo not empty
                if(REG_FIELD_RD(huart->UARTX->SR,  UART_SR_TFNF))
                {
                    huart->Tx_Env.Interrupt.XferCount--;
                    huart->UARTX->TBR = (*pData++ & (uint8_t)0xFF);
                }
            }
            // Wait until TX Finish
            while(!REG_FIELD_RD(huart->UARTX->SR,  UART_SR_TEMT));
        }
        /* At end of Tx process, restore huart->gState to Ready */
        huart->gState = HAL_UART_STATE_READY;
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

    uint32_t timeout = SYSTICK_MS2TICKS(Timeout);
    uint32_t tickstart = systick_get_value();

    /* Check that a Rx process is not already ongoing */
    if (huart->RxState == HAL_UART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return  HAL_INVALIAD_PARAM;
        }
        huart->RxState = HAL_UART_STATE_BUSY_RX;

        /* Init tickstart for timeout managment */
        //todo
    
        huart->Rx_Env.Interrupt.XferCount = Size;
        if(Timeout !=HAL_MAX_DELAY)
        {
            /* Check the remain data to be received */
            while (huart->Rx_Env.Interrupt.XferCount > 0U)
            {
                if(systick_poll_timeout(tickstart,timeout,uart_flag_poll,huart,UART_SR_RFNE))
                {
                    huart->RxState = HAL_UART_STATE_READY;
                    return HAL_TIMEOUT;
                }
               else
                {
                    huart->Rx_Env.Interrupt.XferCount--;
                    *pData++ = (uint8_t)(huart->UARTX->RBR & (uint8_t)0x00FF);
                }
            }
        }
        else
        {
            while (huart->Rx_Env.Interrupt.XferCount > 0U)
            {
                if(REG_FIELD_RD(huart->UARTX->SR,  UART_SR_RFNE))
                {
                    huart->Rx_Env.Interrupt.XferCount--;
                    *pData++ = (uint8_t)(huart->UARTX->RBR & (uint8_t)0x00FF);
                }
            }
        }
        /* At end of Rx process, restore huart->RxState to Ready */
        huart->RxState = HAL_UART_STATE_READY;
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)

{
    /* Check that a Tx process is not already ongoing */
    if (huart->gState == HAL_UART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }
        REG_FIELD_WR(huart->UARTX->MCR,UART_MCR_DMAEN,0);
        huart->Tx_Env.Interrupt.pBuffPtr = pData;
        huart->Tx_Env.Interrupt.XferCount = Size;
        huart->gState = HAL_UART_STATE_BUSY_TX;
        LL_UART_SetTXTL(huart->UARTX,FIFO_TRABSMIT_TRIGGER_0BYTE);
        huart->UARTX->ICR = UART_IT_TXS;
        huart->Tx_Env.Interrupt.XferCount--; 
        huart->UARTX->TBR = (*huart->Tx_Env.Interrupt.pBuffPtr++ & (uint8_t)0xFF);
        huart->UARTX->IER = UART_IT_TXS;
        return HAL_OK;
    }
    else
    {
        LOG_I("UART_Transmit_busy");
        return HAL_BUSY;
    }
}

HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    /* Check that a Rx process is not already ongoing */
    if (huart->RxState == HAL_UART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0U))
        {
            return HAL_INVALIAD_PARAM;
        }
        REG_FIELD_WR(huart->UARTX->MCR,UART_MCR_DMAEN,0);
        huart->Rx_Env.Interrupt.pBuffPtr = pData;
        huart->Rx_Env.Interrupt.XferCount = Size;
        huart->RxState = HAL_UART_STATE_BUSY_RX;
        if(huart->Rx_Env.Interrupt.XferCount<8)
        {
            LL_UART_SetRXTL(huart->UARTX,FIFO_RECEIVE_TRIGGER_1BYTE);
        }
        else
        {
            LL_UART_SetRXTL(huart->UARTX,FIFO_RECEIVE_TRIGGER_8BYTE);
        } 
        /* Enable the UART Data Register not empty Interrupt */
        huart->UARTX->IER = UART_IT_RXRD;
        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}


static void UART_SetConfig(UART_HandleTypeDef *huart)
{
    /* Check the parameters */
    //TODO
    /* Configure the UART Stop Bits: Set STOP[13:12] bits
        Configure the UART Word Length, Parity and mode:
        Set the M bits according to huart->Init.WordLength value
        Set PCE and PS bits according to huart->Init.Parity value
        Set TE and RE bits according to huart->Init.Mode value
        Set OVER8 bit according to huart->Init.OverSampling value*/
    REG_FIELD_WR(huart->UARTX->LCR,UART_LCR_BRWEN,1);
    huart->UARTX->BRR  =  huart->Init.BaudRate;
    REG_FIELD_WR(huart->UARTX->LCR,UART_LCR_BRWEN,0);
    huart->UARTX->FCR = UART_FCR_TFRST_MASK | UART_FCR_RFRST_MASK | UART_FCR_FIFOEN_MASK;
    huart->UARTX->LCR = FIELD_BUILD(UART_LCR_DLS,huart->Init.WordLength)|FIELD_BUILD(UART_LCR_STOP,huart->Init.StopBits)
                                  |FIELD_BUILD(UART_LCR_PARITY,huart->Init.Parity)|FIELD_BUILD(UART_LCR_MSB,huart->Init.MSBEN)
                                  |FIELD_BUILD(UART_LCR_RXEN,1)|FIELD_BUILD(UART_LCR_BRWEN,0);
}



__attribute__((weak)) void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */
}

__attribute__((weak)) void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
}

static void UART_Transmit_IT(UART_HandleTypeDef *huart)
{
    /* Check that a Tx process is ongoing */
    if (huart->gState == HAL_UART_STATE_BUSY_TX)
    {
        if(!REG_FIELD_RD(huart->UARTX->FCR, UART_FCR_TXFL))
        {
            if (huart->Tx_Env.Interrupt.XferCount == 0U)
            {
                huart->UARTX->IDR = UART_IT_TXS;
                /* Tx process is ended, restore huart->gState to Ready */
                huart->gState = HAL_UART_STATE_READY;
                HAL_UART_TxCpltCallback(huart);
            }
            else
            {
                while(REG_FIELD_RD(huart->UARTX->SR,  UART_SR_TFNF))
                {
                    if (huart->Tx_Env.Interrupt.XferCount == 0U)
                    {
                        break;
                    }
                    huart->Tx_Env.Interrupt.XferCount--;
                    huart->UARTX->TBR = (*huart->Tx_Env.Interrupt.pBuffPtr++ & (uint8_t)0xFF);
                }
            }
        }
    }
}

static void UART_Receive_IT(UART_HandleTypeDef *huart)
{
    uint8_t fifo_level;
    /* Check that a Rx process is ongoing */
    if (huart->RxState == HAL_UART_STATE_BUSY_RX)
    {
        fifo_level = REG_FIELD_RD(huart->UARTX->FCR, UART_FCR_RXFL);
        for (;fifo_level>0;fifo_level--)
        {
            *huart->Rx_Env.Interrupt.pBuffPtr++ = (uint8_t)(huart->UARTX->RBR & (uint8_t)0x00FF);
            if (--huart->Rx_Env.Interrupt.XferCount == 0U)
            {
                LL_UART_SetRXTL(huart->UARTX,FIFO_RECEIVE_TRIGGER_8BYTE);
                huart->RxState = HAL_UART_STATE_READY;
                huart->UARTX->IDR = UART_IT_RXRD;
                HAL_UART_RxCpltCallback(huart);
                return;
            }
            if(huart->Rx_Env.Interrupt.XferCount<0x08)
            {
                LL_UART_SetRXTL(huart->UARTX,FIFO_RECEIVE_TRIGGER_1BYTE);
            }
            else
            {
                LL_UART_SetRXTL(huart->UARTX,FIFO_RECEIVE_TRIGGER_8BYTE);
            }
        }
    }
}

__attribute__((weak)) void UART_Transmit_IT_DMA(UART_HandleTypeDef *huart){}

__attribute__((weak)) void HAL_UART_BaudRateDetectCpltCallback(UART_HandleTypeDef *huart,uint8_t detect_byte){}

static uint8_t UART_AutoBaudRate_Detect_End(UART_HandleTypeDef *huart)
{
    huart->UARTX->ICR = UART_ABE_MASK;
    REG_FIELD_WR(huart->UARTX->MCR,UART_MCR_ABREN,0);
    REG_FIELD_WR(huart->UARTX->LCR,UART_LCR_BRWEN,0);
    return huart->UARTX->RBR;
}

static void UART_BaudRate_Detect_IT(UART_HandleTypeDef *huart)
{
    huart->UARTX->IDR = UART_IT_RXRD;
    uint8_t detect_byte = UART_AutoBaudRate_Detect_End(huart);
    HAL_UART_BaudRateDetectCpltCallback(huart,detect_byte);
}

void HAL_UARTx_IRQHandler(UART_HandleTypeDef *huart)
{
    uint32_t isrflags   = huart->UARTX->IFM;  
    uint32_t status_reg = huart->UARTX->SR;
    
    if(REG_FIELD_RD(huart->UARTX->MCR,UART_MCR_DMAEN))
    {
        if (( isrflags& UART_IT_TXS) != 0) 
        {
            huart->UARTX->ICR = UART_IT_TXS;
            UART_Transmit_IT_DMA(huart);
        }
    }else
    {
        if (( isrflags& UART_IT_TXS) != 0) 
        {
            huart->UARTX->ICR = UART_IT_TXS;
            UART_Transmit_IT(huart);
        }
    }
    /* UART in mode Receive ------------------------------------------------*/
    if ((isrflags & UART_IT_RXRD) != 0) 
    {
        if(REG_FIELD_RD(huart->UARTX->RIF,UART_ABE))
        {
            UART_BaudRate_Detect_IT(huart);
        }else{
            UART_Receive_IT(huart);
        }
    }
    if ((status_reg & 0x02) != 0)
    {
        LOG_I("uart_rx overrun!!!");
    }
}

static void UART_AutoBaudRate_Detect_Start(UART_HandleTypeDef *huart,uint8_t mode)
{
    REG_FIELD_WR(huart->UARTX->LCR,UART_LCR_BRWEN,1);
    MODIFY_REG(huart->UARTX->MCR, UART_MCR_ABRMOD_MASK | UART_MCR_ABREN_MASK, mode<<UART_MCR_ABRMOD_POS | 1<<UART_MCR_ABREN_POS);
}

HAL_StatusTypeDef HAL_UART_AutoBaudRate_Detect(UART_HandleTypeDef *huart,uint8_t mode,uint8_t *detect_byte)
{
    UART_AutoBaudRate_Detect_Start(huart,mode);
    while(REG_FIELD_RD(huart->UARTX->SR,UART_SR_RFNE)==false);
    *detect_byte = UART_AutoBaudRate_Detect_End(huart);
    return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_AutoBaudRate_Detect_IT(UART_HandleTypeDef * huart,uint8_t mode)
{
    UART_AutoBaudRate_Detect_Start(huart,mode);
    LL_UART_SetRXTL(huart->UARTX,FIFO_RECEIVE_TRIGGER_1BYTE);
    huart->UARTX->IER = UART_IT_RXRD;
    return HAL_OK;
}
