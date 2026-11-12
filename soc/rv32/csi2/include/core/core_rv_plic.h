/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CORE_RV_PLIC_H__
#define __CORE_RV_PLIC_H__

#include "csi_rv_common.h"

#if CONFIG_INTC_PLIC || CONFIG_INTC_CLIC_PLIC
/**
  \brief Access to the structure of a PLIC vector interrupt controller.
 */

typedef struct {
    uint32_t RESERVED0;
    __IOM uint32_t PLIC_PRIO[1023];
    __IOM uint32_t PLIC_IP[32];
    uint32_t RESERVED1[3972 / 4 - 1];
    __IOM uint32_t PLIC_H0_MIE[32];
    __IOM uint32_t PLIC_H0_SIE[32];
    __IOM uint32_t PLIC_H1_MIE[32];
    __IOM uint32_t PLIC_H1_SIE[32];
    __IOM uint32_t PLIC_H2_MIE[32];
    __IOM uint32_t PLIC_H2_SIE[32];
    __IOM uint32_t PLIC_H3_MIE[32];
    __IOM uint32_t PLIC_H3_SIE[32];
    __IOM uint32_t PLIC_H4_MIE[32];
    __IOM uint32_t PLIC_H4_SIE[32];
    __IOM uint32_t PLIC_H5_MIE[32];
    __IOM uint32_t PLIC_H5_SIE[32];
    __IOM uint32_t PLIC_H6_MIE[32];
    __IOM uint32_t PLIC_H6_SIE[32];
    __IOM uint32_t PLIC_H7_MIE[32];
    __IOM uint32_t PLIC_H7_SIE[32];

    uint32_t RESERVED2[(0x01FFFFC - 0x00027FC) / 4 - 1];
    __IOM uint32_t PLIC_PER;
    __IOM uint32_t PLIC_H0_MTH;
    __IOM uint32_t PLIC_H0_MCLAIM;
    uint32_t RESERVED3[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H0_STH;
    __IOM uint32_t PLIC_H0_SCLAIM;
    uint32_t RESERVED4[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H1_MTH;
    __IOM uint32_t PLIC_H1_MCLAIM;
    uint32_t RESERVED5[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H1_STH;
    __IOM uint32_t PLIC_H1_SCLAIM;
    uint32_t RESERVED6[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H2_MTH;
    __IOM uint32_t PLIC_H2_MCLAIM;
    uint32_t RESERVED7[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H2_STH;
    __IOM uint32_t PLIC_H2_SCLAIM;
    uint32_t RESERVED8[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H3_MTH;
    __IOM uint32_t PLIC_H3_MCLAIM;
    uint32_t RESERVED9[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H3_STH;
    __IOM uint32_t PLIC_H3_SCLAIM;
    uint32_t RESERVED10[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H4_MTH;
    __IOM uint32_t PLIC_H4_MCLAIM;
    uint32_t RESERVED11[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H4_STH;
    __IOM uint32_t PLIC_H4_SCLAIM;
    uint32_t RESERVED12[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H5_MTH;
    __IOM uint32_t PLIC_H5_MCLAIM;
    uint32_t RESERVED13[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H5_STH;
    __IOM uint32_t PLIC_H5_SCLAIM;
    uint32_t RESERVED14[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H6_MTH;
    __IOM uint32_t PLIC_H6_MCLAIM;
    uint32_t RESERVED15[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H6_STH;
    __IOM uint32_t PLIC_H6_SCLAIM;
    uint32_t RESERVED16[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H7_MTH;
    __IOM uint32_t PLIC_H7_MCLAIM;
    uint32_t RESERVED17[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H7_STH;
    __IOM uint32_t PLIC_H7_SCLAIM;
    uint32_t RESERVED18[0xFFC / 4 - 1];
} PLIC_Type;

#define PLIC_Hn_MSIE_ADDR(msie_base, hartid)        ((unsigned long)(msie_base) + 0x100 * (hartid))
#define PLIC_Hn_MSIE_VAL(msie_base, hartid)         (*(__IOM uint32_t *)(PLIC_Hn_MSIE_ADDR(msie_base, hartid)))
#define PLIC_Hn_MSTH_ADDR(msth_base, hartid)        ((unsigned long)(msth_base) + 0x2000 * (hartid))
#define PLIC_Hn_MSTH_VAL(msth_base, hartid)         (*(__IOM uint32_t *)(PLIC_Hn_MSTH_ADDR(msth_base, hartid)))
#define PLIC_Hn_MSCLAIM_ADDR(msclaim_base, hartid)  ((unsigned long)(msclaim_base) + 0x2000 * (hartid))
#define PLIC_Hn_MSCLAIM_VAL(msclaim_base, hartid)   (*(__IOM uint32_t *)(PLIC_Hn_MSCLAIM_ADDR(msclaim_base, hartid)))

/**
  \brief        Enable a specific interrupt request
  \param [in]   plic_base   Base address of the PLIC peripheral
  \param [in]   hart_id     Hart identifier for which the interrupt is enabled
  \param [in]   IRQn        Interrupt number to enable
 */
__ALWAYS_STATIC_INLINE void csi_plic_enable_irq(unsigned long plic_base, uint32_t hart_id, uint32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;

#if CONFIG_RISCV_SMODE
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hart_id) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hart_id) | (0x1 << (IRQn%32));
#else
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hart_id) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hart_id) | (0x1 << (IRQn%32));
#endif
}

/**
  \brief        Disable a specific interrupt request
  \param [in]   plic_base   Base address of the PLIC peripheral
  \param [in]   hart_id     Hart identifier for which the interrupt is disabled
  \param [in]   IRQn        Interrupt number to disable
 */
__ALWAYS_STATIC_INLINE void csi_plic_disable_irq(unsigned long plic_base, uint32_t hart_id, uint32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;

#if CONFIG_RISCV_SMODE
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hart_id) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hart_id) & (~(0x1 << (IRQn%32)));
#else
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hart_id) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hart_id) & (~(0x1 << (IRQn%32)));
#endif
}

/**
  \brief        Get the enabled status of a specific interrupt request
  \param [in]   plic_base   Base address of the PLIC peripheral
  \param [in]   hart_id     Hart identifier to check
  \param [in]   IRQn        Interrupt number to check
  \return                   1 if interrupt is enabled, 0 otherwise
 */
__ALWAYS_STATIC_INLINE uint32_t csi_plic_get_enabled_irq(unsigned long plic_base, uint32_t hart_id, uint32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;

#if CONFIG_RISCV_SMODE
    return (uint32_t)((PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hart_id) >> IRQn%32) & 0x1);
#else
    return (uint32_t)((PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hart_id) >> IRQn%32) & 0x1);
#endif
}

/**
  \brief        Get the pending status of a specific interrupt request
  \param [in]   plic_base   Base address of the PLIC peripheral
  \param [in]   IRQn        Interrupt number to check
  \return                   1 if interrupt is pending, 0 otherwise
 */
__ALWAYS_STATIC_INLINE uint32_t csi_plic_get_pending_irq(unsigned long plic_base, uint32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    return (uint32_t)((plic->PLIC_IP[IRQn/32] >> IRQn%32) & 0x1);
}

/**
  \brief        Set a specific interrupt as pending
  \param [in]   plic_base   Base address of the PLIC peripheral
  \param [in]   IRQn        Interrupt number to set as pending
 */
__ALWAYS_STATIC_INLINE void csi_plic_set_pending_irq(unsigned long plic_base, uint32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    plic->PLIC_IP[IRQn/32] = plic->PLIC_IP[IRQn/32] | (0x1 << (IRQn%32));
}

/**
  \brief        Clear the pending status of a specific interrupt
  \param [in]   plic_base   Base address of the PLIC peripheral
  \param [in]   IRQn        Interrupt number to clear
 */
__ALWAYS_STATIC_INLINE void csi_plic_clear_pending_irq(unsigned long plic_base, uint32_t IRQn)
{
    unsigned long result;
    PLIC_Type *plic = (PLIC_Type *)plic_base;

#if CONFIG_RISCV_SMODE
    result = 0;
    PLIC_Hn_MSCLAIM_VAL(&plic->PLIC_H0_SCLAIM, result) = IRQn;
#else
    __ASM volatile("csrr %0, mhartid" : "=r"(result) : : "memory");
    PLIC_Hn_MSCLAIM_VAL(&plic->PLIC_H0_MCLAIM, result) = IRQn;
#endif
}

/**
  \brief        Set the priority level for a specific interrupt
  \param [in]   plic_base   Base address of the PLIC peripheral
  \param [in]   IRQn        Interrupt number to configure
  \param [in]   priority    Priority level to assign
 */
__ALWAYS_STATIC_INLINE void csi_plic_set_prio(unsigned long plic_base, uint32_t IRQn, uint32_t priority)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    plic->PLIC_PRIO[IRQn - 1] = priority;
}

/**
  \brief        Get the priority level of a specific interrupt
  \param [in]   plic_base   Base address of the PLIC peripheral
  \param [in]   IRQn        Interrupt number to query
  \return                   Current priority level of the interrupt
 */
__ALWAYS_STATIC_INLINE uint32_t csi_plic_get_prio(unsigned long plic_base, uint32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    uint32_t prio = plic->PLIC_PRIO[IRQn - 1];
    return prio;
}

#endif /* CONFIG_INTC_PLIC || CONFIG_INTC_CLIC_PLIC */
#endif
