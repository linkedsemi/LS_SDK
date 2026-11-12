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

#ifndef __CORE_RV_CLINT_H__
#define __CORE_RV_CLINT_H__

#include "csi_rv_common.h"

/**
  \ingroup  CSI_core_register
  \defgroup CSI_SysTick     System Tick Timer (CORET)
  \brief    Type definitions for the System Timer Registers.
  @{
 */

/**
  \brief  The data structure of the access CLINT.
 */
 typedef struct {
     __IOM uint32_t MSIP[1024];                            /* 0x00000 - 0x00FFF: MSIP for hart 0-1023 (4 bytes each) */
     uint32_t RESERVED0[(0x4004000 - 0x4000FFC) / 4 - 1];
     __IOM uint64_t MTIMECMP[1024];                        /* 0x04000 - 0x05FFF: MTIMECMPL/MTIMECMPH for hart 0-1023 (4 + 4 bytes each) */
     uint32_t RESERVED1[(0x400BFF8 - 0x4005FFC) / 4 - 1];
     __IM uint32_t MTIMEL;
     __IM uint32_t MTIMEH;
     __IOM uint32_t SSIP[1024];                            /* 0x0C000 - 0x0CFFF: SSIP for hart 0-1023 (4 bytes each) */
     uint32_t RESERVED2[(0x400D000 - 0x400CFFC) / 4 - 1];
     __IOM uint64_t STIMECMP[1024];                        /* 0x0D000 - 0x0EFFF: STIMECMPL/STIMECMPH for hart 0-1023 (4 + 4 bytes each) */
     uint32_t RESERVED3[(0x400FFF8 - 0x400EFFC) / 4 - 1];
     __IM uint32_t STIMEL;
     __IM uint32_t STIMEH;
 } CLINT_Type;

/**
  \brief  The data structure of the access system timer.
 */
typedef struct {
    __IOM unsigned long long MTIMECMP;            /*!< Offset: 0x000 (R/W) Timer compare register */
    uint32_t RESERVED[8188];
    __IM  unsigned long long MTIME;               /*!< Offset: 0x7FF8 (R)  Timer current register */
} CORET_Type;

/*@} end of group CSI_SysTick */

/**
  \brief        Set CLINT mtimer comparator value
  \param [in]   clint_base   base address of CLINT
  \param [in]   hart_id      Hart ID
  \param [in]   val          comparator value
 */
__ALWAYS_STATIC_INLINE void csi_clint_mtimecmp_set(unsigned long clint_base, uint16_t hart_id, uint64_t val)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    __IOM unsigned long mtimecmpl_addr = (unsigned long)&clint->MTIMECMP[hart_id];
    __IOM unsigned long mtimecmph_addr = (unsigned long)&clint->MTIMECMP[hart_id] + 4;
    rv_writel(0xFFFFFFFF, mtimecmpl_addr);
    rv_writel((uint32_t)(val >> 32), mtimecmph_addr);
    rv_writel((uint32_t)(val), mtimecmpl_addr);
}

/**
  \brief        Get CLINT mtimer comparator value
  \param [in]   clint_base   base address of CLINT
  \param [in]   hart_id      Hart ID
  \return                    comparator value
 */
__ALWAYS_STATIC_INLINE uint64_t csi_clint_mtimecmp_get(unsigned long clint_base, uint16_t hart_id)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    __IOM unsigned long mtimecmpl_addr = (unsigned long)&clint->MTIMECMP[hart_id];
    __IOM unsigned long mtimecmph_addr = (unsigned long)&clint->MTIMECMP[hart_id] + 4;
    uint64_t val = *(__IOM uint32_t *)mtimecmpl_addr;
    val |= ((uint64_t)*(__IOM uint32_t *)mtimecmph_addr) << 32;
    RISCV_FENCE(ir, ir);
    return val;
}

/**
  \brief        Get CLINT mtimer value
  \param [in]   clint_base   base address of CLINT
  \return                    timer value
 */
__ALWAYS_STATIC_INLINE uint64_t csi_clint_mtime_get(unsigned long clint_base)
{
#if CONFIG_NO_MTIME_MM_REG
#if __riscv_xlen == 32
    return (((uint64_t)__get_MTIMEH() << 32) | __get_MTIME());
#else
    return __get_MTIME();
#endif
#else /* !CONFIG_NO_MTIME_MM_REG */
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    uint64_t val = clint->MTIMEL;
    val |= ((uint64_t)clint->MTIMEH) << 32;
    RISCV_FENCE(ir, ir);
    return val;
#endif /* CONFIG_NO_MTIME_MM_REG */
}

/**
  \brief        Set CLINT stimer comparator value
  \param [in]   clint_base   base address of CLINT
  \param [in]   hart_id      Hart ID
  \param [in]   val          comparator value
 */
__ALWAYS_STATIC_INLINE void csi_clint_stimecmp_set(unsigned long clint_base, uint16_t hart_id, uint64_t val)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    __IOM unsigned long stimecmpl_addr = (unsigned long)&clint->STIMECMP[hart_id];
    __IOM unsigned long stimecmph_addr = (unsigned long)&clint->STIMECMP[hart_id] + 4;
    rv_writel(0xFFFFFFFF, stimecmpl_addr);
    rv_writel((uint32_t)(val >> 32), stimecmph_addr);
    rv_writel((uint32_t)(val), stimecmpl_addr);
}

/**
  \brief        Get CLINT stimer comparator value
  \param [in]   clint_base   base address of CLINT
  \param [in]   hart_id      Hart ID
  \return                    comparator value
 */
__ALWAYS_STATIC_INLINE uint64_t csi_clint_stimecmp_get(unsigned long clint_base, uint16_t hart_id)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    __IOM unsigned long stimecmpl_addr = (unsigned long)&clint->STIMECMP[hart_id];
    __IOM unsigned long stimecmph_addr = (unsigned long)&clint->STIMECMP[hart_id] + 4;
    uint64_t val = *(__IOM uint32_t *)stimecmpl_addr;
    val |= ((uint64_t)*(__IOM uint32_t *)stimecmph_addr) << 32;
    RISCV_FENCE(ir, ir);
    return val;
}

/**
  \brief        Get CLINT stimer value
  \param [in]   clint_base   base address of CLINT
  \return                    timer value
 */
__ALWAYS_STATIC_INLINE uint64_t csi_clint_stime_get(unsigned long clint_base)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    uint64_t val = clint->STIMEL;
    val |= ((uint64_t)clint->STIMEH) << 32;
    RISCV_FENCE(ir, ir);
    return val;
}

/**
  \brief        Set Inter-Processor Interrupt to a Core
  \param [in]   clint_base   base address of CLINT
  \param [in]   hart_id      Hart ID
 */
__ALWAYS_STATIC_INLINE void csi_clint_msip_set(unsigned long clint_base, uint16_t hart_id)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    clint->MSIP[hart_id] = 1;
    RISCV_FENCE(ow, ow);
}

/**
  \brief        Clear Inter-Processor Interrupt to a Core
  \param [in]   clint_base   base address of CLINT
  \param [in]   hart_id      Hart ID
 */
__ALWAYS_STATIC_INLINE void csi_clint_msip_clear(unsigned long clint_base, uint16_t hart_id)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    clint->MSIP[hart_id] = 0;
    RISCV_FENCE(ow, ow);
}

/**
  \brief        Set Supervisor Inter-Processor Interrupt to a Core
  \param [in]   clint_base   base address of CLINT
  \param [in]   hart_id      Hart ID
 */
__ALWAYS_STATIC_INLINE void csi_clint_ssip_set(unsigned long clint_base, uint16_t hart_id)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    clint->SSIP[hart_id] = 1;
    RISCV_FENCE(ow, ow);
}

/**
  \brief        Clear Supervisor Inter-Processor Interrupt to a Core
  \param [in]   clint_base   base address of CLINT
  \param [in]   hart_id      Hart ID
 */
__ALWAYS_STATIC_INLINE void csi_clint_ssip_clear(unsigned long clint_base, uint16_t hart_id)
{
    CLINT_Type *clint = (CLINT_Type *)clint_base;
    clint->SSIP[hart_id] = 0;
    RISCV_FENCE(ow, ow);
}

#endif
