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

#ifndef __CORE_RV_ACLINT_H__
#define __CORE_RV_ACLINT_H__

#include "csi_rv_common.h"

/* Bit definitions for PIC_ICQ_EN register */
#define ACLINT_PIC_ICQ_EN_MASK  0x00000007U  /* Bits [2:0] are valid */

typedef struct {
    /* MSIP (Machine Software Interrupt Pending) registers - 0x00000 */
    volatile uint32_t MSIP[1024];          /* 0x00000 - 0x00FFF: MSIP for hart 0-1023 (4 bytes each) */

    /* Reserved space */
    uint8_t RESERVED0[0x3000];             /* 0x01000 - 0x03FFF: Reserved */

    /* MTIMECMP (Machine Timer Compare) registers - 0x04000 */
    volatile uint64_t MTIMECMP[1024];      /* 0x04000 - 0x05FFF: MTIMECMP for hart 0-1023 (8 bytes each) */

    /* Reserved space */
    uint8_t RESERVED1[0x5FF0];             /* 0x06000 - 0x0BFEF: Reserved */

    /* PIC and timer control registers - 0x0BFF0 */
    volatile uint32_t PICID;               /* 0x0BFF0: PIC version info */
    volatile uint32_t PIC_ICQ_EN;          /* 0x0BFF4: PIC module ICQ enable (bit[2:0] valid) */
    volatile uint64_t MTIME;               /* 0x0BFF8: MTIME for all harts (read-only) */

    /* SSIP (Supervisor Software Interrupt Pending) registers - 0x0C000 */
    volatile uint32_t SSIP[1024];          /* 0x0C000 - 0x0CFFF: SSIP for hart 0-1023 (4 bytes each) */
} ACLINT_Type;

/**
  \brief        Set ACLINT mtimer comparator value
  \param [in]   mtimecmp_base   base address of ACLINT MTIME Compare device register
  \param [in]   hart_id         Hart ID
  \param [in]   val             comparator value
 */
__ALWAYS_STATIC_INLINE void csi_aclint_mtimecmp_set(unsigned long mtimecmp_base, uint16_t hart_id, uint64_t val)
{
#if CONFIG_CPU_XUANTIE_XT_C930_CP || CONFIG_CPU_XUANTIE_XT_C930V_CP
    rv_writel(0xFFFFFFFF, mtimecmp_base + 0x20000 * hart_id);
    rv_writel((uint32_t)(val >> 32), mtimecmp_base + 0x20000 * hart_id + 4);
    rv_writel((uint32_t)(val), mtimecmp_base + 0x20000 * hart_id);
#else
    rv_writel(0xFFFFFFFF, mtimecmp_base + 8 * hart_id);
    rv_writel((uint32_t)(val >> 32), mtimecmp_base + 8 * hart_id + 4);
    rv_writel((uint32_t)(val), mtimecmp_base + 8 * hart_id);
#endif
}

/**
  \brief        Get ACLINT mtimer comparator value
  \param [in]   mtimecmp_base   base address of ACLINT MTIME Compare device register
  \param [in]   hart_id         Hart ID
  \return                       comparator value
 */
__ALWAYS_STATIC_INLINE uint64_t csi_aclint_mtimecmp_get(unsigned long mtimecmp_base, uint16_t hart_id)
{
    uint64_t value;
#if CONFIG_CPU_XUANTIE_XT_C930_CP || CONFIG_CPU_XUANTIE_XT_C930V_CP
    value = rv_readq(mtimecmp_base + 0x20000 * hart_id);
    return value;
#else
    value = rv_readl(mtimecmp_base + 8 * hart_id);
    value |= (uint64_t)rv_readl(mtimecmp_base + 8 * hart_id + 4) << 32;
    return value;
#endif
}

/**
  \brief        Get ACLINT mtimer value
  \param [in]   mtime_base      base address of ACLINT MTIME device register
  \return                       timer value
 */
__ALWAYS_STATIC_INLINE uint64_t csi_aclint_mtime_get(unsigned long mtime_base)
{
#if CONFIG_CPU_XUANTIE_XT_C930_CP || CONFIG_CPU_XUANTIE_XT_C930V_CP
    uint64_t value = rv_readq(mtime_base);
    return value;
#else
    uint64_t value = rv_readl(mtime_base);
    value |= (uint64_t)rv_readl(mtime_base + 4) << 32;
    return value;
#endif
}

/**
  \brief        Set Inter-Processor Interrupt to a Core
  \param [in]   mswi_base       base address of ACLINT MSWI device register
  \param [in]   hart_id         Hart ID
 */
__ALWAYS_STATIC_INLINE void csi_aclint_msip_set(unsigned long mswi_base, uint16_t hart_id)
{
    rv_writel(1, mswi_base + 4 * hart_id);
}

/**
  \brief        Clear Inter-Processor Interrupt to a Core
  \param [in]   mswi_base       base address of ACLINT MSWI device register
  \param [in]   hart_id         Hart ID
 */
__ALWAYS_STATIC_INLINE void csi_aclint_msip_clear(unsigned long mswi_base, uint16_t hart_id)
{
    rv_writel(0, mswi_base + 4 * hart_id);
}

/**
  \brief        Set Supervisor Inter-Processor Interrupt to a Core
  \param [in]   sswi_base       base address of ACLINT SSWI device register
  \param [in]   hart_id         Hart ID
 */
__ALWAYS_STATIC_INLINE void csi_aclint_ssip_set(unsigned long sswi_base, uint16_t hart_id)
{
    rv_writel(1, sswi_base + 4 * hart_id);
}

/**
  \brief        Clear Supervisor Software Interrupt
 */
__ALWAYS_STATIC_INLINE void csi_aclint_ssip_clear(void)
{
    /* clear SSIP bit in sip */
    unsigned long val;
    __ASM volatile("csrr %0, sip" : "=r"(val));
    val &= ~(1UL << 1);
    __ASM volatile("csrw sip, %0" ::"r"(val));
}

#endif
