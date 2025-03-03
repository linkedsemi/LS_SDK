#ifndef __LL_I3C_TARGET__
#define __LL_I3C_TARGET__


#include <string.h>
#include <stdlib.h>
#include "platform.h"
#include "reg_i3c.h"


static inline uint32_t I3C_TargetGetStatusFlags(I3C_TypeDef *base)
{
    return base->SSTATUS & ~(I3C_SSTATUS_EVDET_MASK | I3C_SSTATUS_ACTSTATE_MASK | I3C_SSTATUS_TIMECTRL_MASK);
}

static inline uint32_t I3C_TargetGetErrorStatusFlags(I3C_TypeDef *base)
{
    return base->SERRWARN;
}

static inline uint32_t I3C_TargetGetPendingInterrupts(I3C_TypeDef *base)
{
    return base->SINTMASKED;
}


static inline void I3C_TargetClearErrorStatusFlags(I3C_TypeDef *base, uint32_t statusMask)
{
    base->SERRWARN = statusMask;
}

static inline void I3C_TargetClearStatusFlags(I3C_TypeDef *base, uint32_t statusMask)
{
    base->SSTATUS = statusMask;
}

static inline void I3C_TargetFlushRxFifo(I3C_TypeDef *base)
{
    base->SDATACTRL |= I3C_SDATACTRL_FLUSHFB_MASK;
}

static inline void I3C_TargetFlushTxFifo(I3C_TypeDef *base)
{
    base->SDATACTRL |= I3C_SDATACTRL_FLUSHTB_MASK;
}


static inline void I3C_TargetGetFifoCounts(I3C_TypeDef *base, uint8_t *rxCount, uint8_t *txCount)
{
    if (NULL != txCount)
    {
        *txCount = (base->SDATACTRL & I3C_SDATACTRL_TXCOUNT_MASK) >> I3C_SDATACTRL_TXCOUNT_POS;
    }
    if (NULL != rxCount)
    {
        *rxCount = (base->SDATACTRL & I3C_SDATACTRL_RXCOUNT_MASK) >> I3C_SDATACTRL_RXCOUNT_POS;
    }
}

static inline uint32_t I3C_TargetGetEnabledInterrupts(I3C_TypeDef *base)
{
    return base->SINTSET;
}

static inline void I3C_TargetDisableInterrupts(I3C_TypeDef *base, uint32_t interruptMask)
{
    base->SINTCLR = interruptMask;
}

static inline void I3C_TargetEnableInterrupts(I3C_TypeDef *base, uint32_t interruptMask)
{
    base->SINTSET |= interruptMask;
}

static inline void I3C_TargetEnableDMA(I3C_TypeDef *base, bool enableTx, bool enableRx)
{
    base->SDMACTRL =
        ((enableRx ? 2U : 0U)<< I3C_SDMAC_DMAFB_POS) | ((enableTx ? 2U : 0U)<<I3C_SDMAC_DMATB_POS) | (1 << I3C_SDMAC_DMAWIDTH_POS);
}

static inline bool I3C_TargetEnabledTxDMA(I3C_TypeDef *base)
{
    if((base->SDMACTRL&I3C_SDMAC_DMATB_MASK) != 0)
    {
        return true;
    }
    return false;

}

static inline bool I3C_TargetEnabledRxDMA(I3C_TypeDef *base)
{
    if((base->SDMACTRL&I3C_SDMAC_DMAFB_MASK) != 0)
    {
        return true;
    }
    return false;
}


static inline bool I3C_TargetDynAddressValid(I3C_TypeDef *base)
{
    return (((base->SDYNADDR & I3C_SDYNADDR_DAVALID_MASK) == I3C_SDYNADDR_DAVALID_MASK) ? true:false);
}


#endif