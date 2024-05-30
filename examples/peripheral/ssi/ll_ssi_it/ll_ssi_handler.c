#include "ls_hal_ssi.h"
#include "field_manipulate.h"
#include "log.h"
#include "ls_dbg.h"

extern void LL_SSI_TxRxCpltCallback(reg_ssi_t *ssi);
extern void LL_SSI_RxCpltCallback(reg_ssi_t *ssi);
extern void LL_SSI_TxCpltCallback(reg_ssi_t *ssi);

extern uint8_t *TxqBuf;
extern uint8_t *RxqBuf;
extern uint8_t SizeOfTxqBuf;
extern uint8_t SizeOfRxqBuf;


static void ssi_rx_full_isr(reg_ssi_t *ssi)
{
    do
    {
        if (LL_SSI_GetDataFrameSize(ssi) <= DFS_32_8_BITS)
        {

            *(uint8_t *)RxqBuf = (uint8_t)LL_SSI_GetDataRegister8(ssi);
            RxqBuf += 1;
        }
        else if (LL_SSI_GetDataFrameSize(ssi) <= DFS_32_16_BITS)
        {
            *(uint16_t *)RxqBuf = (uint16_t)LL_SSI_GetDataRegister16(ssi);
            RxqBuf += 2;
        }
        else
        {
            *(uint32_t *)RxqBuf = (uint32_t)LL_SSI_GetDataRegister32(ssi);
            RxqBuf += 4;
        }
        --SizeOfRxqBuf;
    } while (LL_SSI_IsActiveFlag(ssi, SSI_FLAG_RFNE));

    if (SizeOfRxqBuf == 0)
    {
        LL_SSI_Disable(ssi);
        LL_SSI_SetSlaveSelect(ssi, 0);

        if (LL_SSI_GetTransferMode(ssi) == RECEIVE_ONLY)
        {
            LL_SSI_RxCpltCallback(ssi);
        }
        else if (LL_SSI_GetTransferMode(ssi) == TRANSMIT_AND_RECEIVE)
        {
            LL_SSI_TxRxCpltCallback(ssi);
        }
    }
}

void ssi_tx_empty_isr(reg_ssi_t *ssi)
{
    if (SizeOfTxqBuf)
    {
        do
        {
            --SizeOfTxqBuf;
            if (LL_SSI_GetDataFrameSize(ssi) <= DFS_32_8_BITS)
            {
                LL_SSI_SetDataRegister8(ssi, *(uint8_t *)TxqBuf);
                TxqBuf++;
            }
            else if (LL_SSI_GetDataFrameSize(ssi) <= DFS_32_16_BITS)
            {
                LL_SSI_SetDataRegister16(ssi, *(uint16_t *)TxqBuf);
                TxqBuf += 2;
            }
            else if (LL_SSI_GetDataFrameSize(ssi) > DFS_32_16_BITS)
            {
                LL_SSI_SetDataRegister32(ssi, *(uint32_t *)TxqBuf);
                TxqBuf += 4;
            }

        } while (LL_SSI_IsActiveFlag(ssi, SSI_FLAG_TFNF) && SizeOfTxqBuf);
    }
    else
    {
        if (LL_SSI_GetTxFifoThreshoid(ssi))
        {
            LL_SSI_SetTxFifoThreshoid(ssi, 0);
        }
        else
        {
            LL_SSI_DisableMaskIT(ssi, SSI_ITIM_TXE);
            if (LL_SSI_GetDataFrameSize(ssi) == TRANSMIT_ONLY)
            {
                while (LL_SSI_IsActiveFlag(ssi, SSI_FLAG_BUSY))
                    ;
                LL_SSI_Disable(ssi);
                LL_SSI_SetSlaveSelect(ssi, 0);
                LL_SSI_TxCpltCallback(ssi);
            }
        }
    }
}

/**
 * @brief SSI中断处理函数
 *
 * @param ssi
 */
void LL_SSI_IRQHandler(void)
{
    while (1)
    {
        if (LL_SSI_IsActiveFlagIT_Mask(LSSSI, SSI_ITIS_MST))
        {
            LOG_W("ssi0x%x,multi_master contention", LSSSI);
            LSSSI->MSTICR;
            LS_ASSERT(0);
        }
        else if (LL_SSI_IsActiveFlagIT_Mask(LSSSI, SSI_ITIS_RXF))
        {
            ssi_rx_full_isr(LSSSI);
        }
        else if (LL_SSI_IsActiveFlagIT_Mask(LSSSI, SSI_ITIS_RXO))
        {
            LOG_W("ssi0x%x,Receive FIFO Overflow", LSSSI);
            LSSSI->RXOICR;
            LS_ASSERT(0);
        }
        else if (LL_SSI_IsActiveFlagIT_Mask(LSSSI, SSI_ITIS_RXU))
        {
            LOG_W("ssi0x%x,Receive FIFO Underflow", LSSSI);
            LSSSI->RXUICR;
            LS_ASSERT(0);
        }
        else if (LL_SSI_IsActiveFlagIT_Mask(LSSSI, SSI_ITIS_TXO))
        {
            LOG_W("si0x%x,Transmit FIFO Overflow", LSSSI);
            LSSSI->TXOICR;
            LS_ASSERT(0);
        }
        else if (LL_SSI_IsActiveFlagIT_Mask(LSSSI, SSI_ITIS_TXE))
        {
            if (LL_SSI_IsEnabledDMAReq_TX(LSSSI))
            {
                // ssi_tx_empty_dma_isr(ssi);
                ;
            }
            else
            {
                ssi_tx_empty_isr(LSSSI);
            }
        }
        else
            break;
    }
}
