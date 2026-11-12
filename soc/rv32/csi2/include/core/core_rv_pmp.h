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

#ifndef __CORE_RV_PMP_H__
#define __CORE_RV_PMP_H__

#include <stdint.h>
#include <limits.h>
#include "csi_rv_common.h"
#include "csi_rv_encoding.h"

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_PMP Physical Memory Protection (PMP)
  \brief      Type definitions for the PMP Registers
  @{
 */

#define PMP_PMPCFG_R_Pos                       0U                                    /*!< PMP PMPCFG: R Position */
#define PMP_PMPCFG_R_Msk                       (0x1UL << PMP_PMPCFG_R_Pos)           /*!< PMP PMPCFG: R Mask */

#define PMP_PMPCFG_W_Pos                       1U                                    /*!< PMP PMPCFG: W Position */
#define PMP_PMPCFG_W_Msk                       (0x1UL << PMP_PMPCFG_W_Pos)           /*!< PMP PMPCFG: W Mask */

#define PMP_PMPCFG_X_Pos                       2U                                    /*!< PMP PMPCFG: X Position */
#define PMP_PMPCFG_X_Msk                       (0x1UL << PMP_PMPCFG_X_Pos)           /*!< PMP PMPCFG: X Mask */

#define PMP_PMPCFG_A_Pos                       3U                                    /*!< PMP PMPCFG: A Position */
#define PMP_PMPCFG_A_Msk                       (0x3UL << PMP_PMPCFG_A_Pos)           /*!< PMP PMPCFG: A Mask */

#define PMP_PMPCFG_L_Pos                       7U                                    /*!< PMP PMPCFG: L Position */
#define PMP_PMPCFG_L_Msk                       (0x1UL << PMP_PMPCFG_L_Pos)           /*!< PMP PMPCFG: L Mask */

#define PMP_MSECCFG_MML_Pos                    0U                                    /*!< MSECCFG: Machine Mode Lockdown Position */
#define PMP_MSECCFG_MML_Msk                    (0x1UL << PMP_MSECCFG_MML_Pos)        /*!< MSECCFG: Machine Mode Lockdown Mask */

#define PMP_MSECCFG_MMWP_Pos                   1U                                    /*!< MSECCFG: Machine Mode Whitelist Policy Position */
#define PMP_MSECCFG_MMWP_Msk                   (0x1UL << PMP_MSECCFG_MMWP_Pos)       /*!< MSECCFG: Machine Mode Whitelist Policy Mask */

#define PMP_MSECCFG_RLB_Pos                    2U                                    /*!< MSECCFG: Rule Locking Bypass Position */
#define PMP_MSECCFG_RLB_Msk                    (0x1UL << PMP_MSECCFG_RLB_Pos)        /*!< MSECCFG: Rule Locking Bypass Mask */

typedef enum {
    REGION_SIZE_4B       = -1,
    REGION_SIZE_8B       = 0,
    REGION_SIZE_16B      = 1,
    REGION_SIZE_32B      = 2,
    REGION_SIZE_64B      = 3,
    REGION_SIZE_128B     = 4,
    REGION_SIZE_256B     = 5,
    REGION_SIZE_512B     = 6,
    REGION_SIZE_1KB      = 7,
    REGION_SIZE_2KB      = 8,
    REGION_SIZE_4KB      = 9,
    REGION_SIZE_8KB      = 10,
    REGION_SIZE_16KB     = 11,
    REGION_SIZE_32KB     = 12,
    REGION_SIZE_64KB     = 13,
    REGION_SIZE_128KB    = 14,
    REGION_SIZE_256KB    = 15,
    REGION_SIZE_512KB    = 16,
    REGION_SIZE_1MB      = 17,
    REGION_SIZE_2MB      = 18,
    REGION_SIZE_4MB      = 19,
    REGION_SIZE_8MB      = 20,
    REGION_SIZE_16MB     = 21,
    REGION_SIZE_32MB     = 22,
    REGION_SIZE_64MB     = 23,
    REGION_SIZE_128MB    = 24,
    REGION_SIZE_256MB    = 25,
    REGION_SIZE_512MB    = 26,
    REGION_SIZE_1GB      = 27,
    REGION_SIZE_2GB      = 28,
    REGION_SIZE_4GB      = 29,
    REGION_SIZE_8GB      = 30,
    REGION_SIZE_16GB     = 31
} region_size_e;

typedef enum {
    ADDRESS_MATCHING_OFF   = 0,
    ADDRESS_MATCHING_TOR   = 1,
    ADDRESS_MATCHING_NA4   = 2,
    ADDRESS_MATCHING_NAPOT = 3
} address_matching_e;

typedef struct {
    uint32_t r: 1;           /* readable enable */
    uint32_t w: 1;           /* writeable enable */
    uint32_t x: 1;           /* execable enable */
    address_matching_e a: 2; /* address matching mode */
    uint32_t reserved: 2;    /* reserved */
    uint32_t l: 1;           /* lock enable */
} pmp_region_attr_t;

/*@} end of group CSI_PMP */

/**
  \brief        Get PMPCFGx Register
  \details      Returns the content of the PMPCFGx Register.
  \return       PMPCFGx Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG0(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg0" : "=r"(result));
    return (result);
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG1(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg1" : "=r"(result));
    return (result);
}
#endif

__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG2(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg2" : "=r"(result));
    return (result);
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG3(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg3" : "=r"(result));
    return (result);
}
#endif

__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG4(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg4" : "=r"(result));
    return (result);
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG5(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg5" : "=r"(result));
    return (result);
}
#endif

__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG6(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg6" : "=r"(result));
    return (result);
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG7(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg7" : "=r"(result));
    return (result);
}
#endif

__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG8(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg8" : "=r"(result));
    return (result);
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG9(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg9" : "=r"(result));
    return (result);
}
#endif

__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG10(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg10" : "=r"(result));
    return (result);
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG11(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg11" : "=r"(result));
    return (result);
}
#endif

__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG12(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg12" : "=r"(result));
    return (result);
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG13(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg13" : "=r"(result));
    return (result);
}
#endif

__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG14(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg14" : "=r"(result));
    return (result);
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE unsigned long __get_PMPCFG15(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, pmpcfg15" : "=r"(result));
    return (result);
}
#endif

/**
  \brief        Get PMPxCFG Register by index
  \details      Returns the content of the PMPxCFG Register.
  \param [in]   idx     PMP region index
  \return               PMPxCFG Register value
 */
__STATIC_INLINE uint8_t __get_PMPxCFG(unsigned long idx)
{
    unsigned long pmpcfgx = 0;

#if __riscv_xlen == 32
    if (idx < 4) {
        pmpcfgx = __get_PMPCFG0();
    } else if (idx >= 4 && idx < 8) {
        idx -= 4;
        pmpcfgx = __get_PMPCFG1();
    } else if (idx >= 8 && idx < 12) {
        idx -= 8;
        pmpcfgx = __get_PMPCFG2();
    } else if (idx >= 12 && idx < 16) {
        idx -= 12;
        pmpcfgx = __get_PMPCFG3();
    } else if (idx >= 16 && idx < 20) {
        idx -= 16;
        pmpcfgx = __get_PMPCFG4();
    } else if (idx >= 20 && idx < 24) {
        idx -= 20;
        pmpcfgx = __get_PMPCFG5();
    } else if (idx >= 24 && idx < 28) {
        idx -= 24;
        pmpcfgx = __get_PMPCFG6();
    } else if (idx >= 28 && idx < 32) {
        idx -= 28;
        pmpcfgx = __get_PMPCFG7();
    } else if (idx >= 32 && idx < 36) {
        idx -= 32;
        pmpcfgx = __get_PMPCFG8();
    } else if (idx >= 36 && idx < 40) {
        idx -= 36;
        pmpcfgx = __get_PMPCFG9();
    } else if (idx >= 40 && idx < 44) {
        idx -= 40;
        pmpcfgx = __get_PMPCFG10();
    } else if (idx >= 44 && idx < 48) {
        idx -= 44;
        pmpcfgx = __get_PMPCFG11();
    } else if (idx >= 48 && idx < 52) {
        idx -= 48;
        pmpcfgx = __get_PMPCFG12();
    } else if (idx >= 52 && idx < 56) {
        idx -= 52;
        pmpcfgx = __get_PMPCFG13();
    } else if (idx >= 56 && idx < 60) {
        idx -= 56;
        pmpcfgx = __get_PMPCFG14();
    } else if (idx >= 60 && idx < 64) {
        idx -= 60;
        pmpcfgx = __get_PMPCFG15();
    } else {
        return 0;
    }
#else
    if (idx < 8) {
        pmpcfgx = __get_PMPCFG0();
    } else if (idx >= 8 && idx < 16) {
        idx -= 8;
        pmpcfgx = __get_PMPCFG2();
    } else if (idx >= 16 && idx < 24) {
        idx -= 16;
        pmpcfgx = __get_PMPCFG4();
    } else if (idx >= 24 && idx < 32) {
        idx -= 24;
        pmpcfgx = __get_PMPCFG6();
    } else if (idx >= 32 && idx < 40) {
        idx -= 32;
        pmpcfgx = __get_PMPCFG8();
    } else if (idx >= 40 && idx < 48) {
        idx -= 40;
        pmpcfgx = __get_PMPCFG10();
    } else if (idx >= 48 && idx < 56) {
        idx -= 48;
        pmpcfgx = __get_PMPCFG12();
    } else if (idx >= 56 && idx < 64) {
        idx -= 56;
        pmpcfgx = __get_PMPCFG14();
    } else {
        return 0;
    }
#endif

    return (uint8_t)((pmpcfgx & (0xFFUL << (idx << 3))) >> (idx << 3));
}

/**
  \brief        Set PMPCFGx
  \details      Writes the given value to the PMPCFGx Register.
  \param [in]   pmpcfg    PMPCFGx Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_PMPCFG0(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg0, %0" : : "r"(pmpcfg));
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE void __set_PMPCFG1(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg1, %0" : : "r"(pmpcfg));
}
#endif

__ALWAYS_STATIC_INLINE void __set_PMPCFG2(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg2, %0" : : "r"(pmpcfg));
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE void __set_PMPCFG3(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg3, %0" : : "r"(pmpcfg));
}
#endif

__ALWAYS_STATIC_INLINE void __set_PMPCFG4(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg4, %0" : : "r"(pmpcfg));
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE void __set_PMPCFG5(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg5, %0" : : "r"(pmpcfg));
}
#endif

__ALWAYS_STATIC_INLINE void __set_PMPCFG6(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg6, %0" : : "r"(pmpcfg));
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE void __set_PMPCFG7(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg7, %0" : : "r"(pmpcfg));
}
#endif

__ALWAYS_STATIC_INLINE void __set_PMPCFG8(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg8, %0" : : "r"(pmpcfg));
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE void __set_PMPCFG9(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg9, %0" : : "r"(pmpcfg));
}
#endif

__ALWAYS_STATIC_INLINE void __set_PMPCFG10(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg10, %0" : : "r"(pmpcfg));
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE void __set_PMPCFG11(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg11, %0" : : "r"(pmpcfg));
}
#endif

__ALWAYS_STATIC_INLINE void __set_PMPCFG12(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg12, %0" : : "r"(pmpcfg));
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE void __set_PMPCFG13(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg13, %0" : : "r"(pmpcfg));
}
#endif

__ALWAYS_STATIC_INLINE void __set_PMPCFG14(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg14, %0" : : "r"(pmpcfg));
}

#if __riscv_xlen == 32
__ALWAYS_STATIC_INLINE void __set_PMPCFG15(unsigned long pmpcfg)
{
    __ASM volatile("csrw pmpcfg15, %0" : : "r"(pmpcfg));
}
#endif

/**
  \brief        Set PMPxCFG by index
  \details      Writes the given value to the PMPxCFG Register.
  \param [in]   idx        PMPx region index
  \param [in]   pmpxcfg    PMPxCFG Register value to set
 */
__STATIC_INLINE void __set_PMPxCFG(unsigned long idx, uint8_t pmpxcfg)
{
    unsigned long pmpcfgx = 0;

#if __riscv_xlen == 32
    if (idx < 4) {
        pmpcfgx = __get_PMPCFG0();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG0(pmpcfgx);
    } else if (idx >= 4 && idx < 8) {
        idx -= 4;
        pmpcfgx = __get_PMPCFG1();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG1(pmpcfgx);
    } else if (idx >= 8 && idx < 12) {
        idx -= 8;
        pmpcfgx = __get_PMPCFG2();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG2(pmpcfgx);
    } else if (idx >= 12 && idx < 16) {
        idx -= 12;
        pmpcfgx = __get_PMPCFG3();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG3(pmpcfgx);
    } else if (idx >= 16 && idx < 20) {
        idx -= 16;
        pmpcfgx = __get_PMPCFG4();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG4(pmpcfgx);
    } else if (idx >= 20 && idx < 24) {
        idx -= 20;
        pmpcfgx = __get_PMPCFG5();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG5(pmpcfgx);
    } else if (idx >= 24 && idx < 28) {
        idx -= 24;
        pmpcfgx = __get_PMPCFG6();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG6(pmpcfgx);
    } else if (idx >= 28 && idx < 32) {
        idx -= 28;
        pmpcfgx = __get_PMPCFG7();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG7(pmpcfgx);
    } else if (idx >= 32 && idx < 36) {
        idx -= 32;
        pmpcfgx = __get_PMPCFG8();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG8(pmpcfgx);
    } else if (idx >= 36 && idx < 40) {
        idx -= 36;
        pmpcfgx = __get_PMPCFG9();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG9(pmpcfgx);
    } else if (idx >= 40 && idx < 44) {
        idx -= 40;
        pmpcfgx = __get_PMPCFG10();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG10(pmpcfgx);
    } else if (idx >= 44 && idx < 48) {
        idx -= 44;
        pmpcfgx = __get_PMPCFG11();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG11(pmpcfgx);
    } else if (idx >= 48 && idx < 52) {
        idx -= 48;
        pmpcfgx = __get_PMPCFG12();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG12(pmpcfgx);
    } else if (idx >= 52 && idx < 56) {
        idx -= 52;
        pmpcfgx = __get_PMPCFG13();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG13(pmpcfgx);
    } else if (idx >= 56 && idx < 60) {
        idx -= 56;
        pmpcfgx = __get_PMPCFG14();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG14(pmpcfgx);
    } else if (idx >= 60 && idx < 64) {
        idx -= 60;
        pmpcfgx = __get_PMPCFG15();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG15(pmpcfgx);
    } else {
        return;
    }
#else
    if (idx < 8) {
        pmpcfgx = __get_PMPCFG0();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG0(pmpcfgx);
    } else if (idx >= 8 && idx < 16) {
        idx -= 8;
        pmpcfgx = __get_PMPCFG2();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG2(pmpcfgx);
    } else if (idx >= 16 && idx < 24) {
        idx -= 16;
        pmpcfgx = __get_PMPCFG4();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG4(pmpcfgx);
    } else if (idx >= 24 && idx < 32) {
        idx -= 24;
        pmpcfgx = __get_PMPCFG6();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG6(pmpcfgx);
    } else if (idx >= 32 && idx < 40) {
        idx -= 32;
        pmpcfgx = __get_PMPCFG8();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG8(pmpcfgx);
    } else if (idx >= 40 && idx < 48) {
        idx -= 40;
        pmpcfgx = __get_PMPCFG10();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG10(pmpcfgx);
    } else if (idx >= 48 && idx < 56) {
        idx -= 48;
        pmpcfgx = __get_PMPCFG12();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG12(pmpcfgx);
    } else if (idx >= 56 && idx < 64) {
        idx -= 56;
        pmpcfgx = __get_PMPCFG14();
        pmpcfgx = (pmpcfgx & ~(0xFFUL << (idx << 3))) | ((unsigned long)(pmpxcfg) << (idx << 3));
        __set_PMPCFG14(pmpcfgx);
    } else {
        return;
    }
#endif
}

/**
  \brief   Get PMPADDRx Register
  \details Returns the content of the PMPADDRx Register.
  \return               PMPADDRx Register value
 */
#define DECLARE_PMPADDR_GETTER(n) \
__ALWAYS_STATIC_INLINE unsigned long __get_PMPADDR##n(void) \
{ \
    unsigned long result; \
    __ASM volatile("csrr %0, pmpaddr"#n : "=r"(result)); \
    return result; \
}
DECLARE_PMPADDR_GETTER(0)
DECLARE_PMPADDR_GETTER(1)
DECLARE_PMPADDR_GETTER(2)
DECLARE_PMPADDR_GETTER(3)
DECLARE_PMPADDR_GETTER(4)
DECLARE_PMPADDR_GETTER(5)
DECLARE_PMPADDR_GETTER(6)
DECLARE_PMPADDR_GETTER(7)
DECLARE_PMPADDR_GETTER(8)
DECLARE_PMPADDR_GETTER(9)
DECLARE_PMPADDR_GETTER(10)
DECLARE_PMPADDR_GETTER(11)
DECLARE_PMPADDR_GETTER(12)
DECLARE_PMPADDR_GETTER(13)
DECLARE_PMPADDR_GETTER(14)
DECLARE_PMPADDR_GETTER(15)
DECLARE_PMPADDR_GETTER(16)
DECLARE_PMPADDR_GETTER(17)
DECLARE_PMPADDR_GETTER(18)
DECLARE_PMPADDR_GETTER(19)
DECLARE_PMPADDR_GETTER(20)
DECLARE_PMPADDR_GETTER(21)
DECLARE_PMPADDR_GETTER(22)
DECLARE_PMPADDR_GETTER(23)
DECLARE_PMPADDR_GETTER(24)
DECLARE_PMPADDR_GETTER(25)
DECLARE_PMPADDR_GETTER(26)
DECLARE_PMPADDR_GETTER(27)
DECLARE_PMPADDR_GETTER(28)
DECLARE_PMPADDR_GETTER(29)
DECLARE_PMPADDR_GETTER(30)
DECLARE_PMPADDR_GETTER(31)
DECLARE_PMPADDR_GETTER(32)
DECLARE_PMPADDR_GETTER(33)
DECLARE_PMPADDR_GETTER(34)
DECLARE_PMPADDR_GETTER(35)
DECLARE_PMPADDR_GETTER(36)
DECLARE_PMPADDR_GETTER(37)
DECLARE_PMPADDR_GETTER(38)
DECLARE_PMPADDR_GETTER(39)
DECLARE_PMPADDR_GETTER(40)
DECLARE_PMPADDR_GETTER(41)
DECLARE_PMPADDR_GETTER(42)
DECLARE_PMPADDR_GETTER(43)
DECLARE_PMPADDR_GETTER(44)
DECLARE_PMPADDR_GETTER(45)
DECLARE_PMPADDR_GETTER(46)
DECLARE_PMPADDR_GETTER(47)
DECLARE_PMPADDR_GETTER(48)
DECLARE_PMPADDR_GETTER(49)
DECLARE_PMPADDR_GETTER(50)
DECLARE_PMPADDR_GETTER(51)
DECLARE_PMPADDR_GETTER(52)
DECLARE_PMPADDR_GETTER(53)
DECLARE_PMPADDR_GETTER(54)
DECLARE_PMPADDR_GETTER(55)
DECLARE_PMPADDR_GETTER(56)
DECLARE_PMPADDR_GETTER(57)
DECLARE_PMPADDR_GETTER(58)
DECLARE_PMPADDR_GETTER(59)
DECLARE_PMPADDR_GETTER(60)
DECLARE_PMPADDR_GETTER(61)
DECLARE_PMPADDR_GETTER(62)
DECLARE_PMPADDR_GETTER(63)

/**
  \brief        Get PMPADDRx Register by index
  \details      Returns the content of the PMPADDRx Register.
  \param [in]   idx     PMP region index
  \return               PMPADDRx Register value
 */
__STATIC_INLINE unsigned long __get_PMPADDRx(unsigned long idx)
{
    switch(idx) {
        case 0: return __get_PMPADDR0();
        case 1: return __get_PMPADDR1();
        case 2: return __get_PMPADDR2();
        case 3: return __get_PMPADDR3();
        case 4: return __get_PMPADDR4();
        case 5: return __get_PMPADDR5();
        case 6: return __get_PMPADDR6();
        case 7: return __get_PMPADDR7();
        case 8: return __get_PMPADDR8();
        case 9: return __get_PMPADDR9();
        case 10: return __get_PMPADDR10();
        case 11: return __get_PMPADDR11();
        case 12: return __get_PMPADDR12();
        case 13: return __get_PMPADDR13();
        case 14: return __get_PMPADDR14();
        case 15: return __get_PMPADDR15();
        case 16: return __get_PMPADDR16();
        case 17: return __get_PMPADDR17();
        case 18: return __get_PMPADDR18();
        case 19: return __get_PMPADDR19();
        case 20: return __get_PMPADDR20();
        case 21: return __get_PMPADDR21();
        case 22: return __get_PMPADDR22();
        case 23: return __get_PMPADDR23();
        case 24: return __get_PMPADDR24();
        case 25: return __get_PMPADDR25();
        case 26: return __get_PMPADDR26();
        case 27: return __get_PMPADDR27();
        case 28: return __get_PMPADDR28();
        case 29: return __get_PMPADDR29();
        case 30: return __get_PMPADDR30();
        case 31: return __get_PMPADDR31();
        case 32: return __get_PMPADDR32();
        case 33: return __get_PMPADDR33();
        case 34: return __get_PMPADDR34();
        case 35: return __get_PMPADDR35();
        case 36: return __get_PMPADDR36();
        case 37: return __get_PMPADDR37();
        case 38: return __get_PMPADDR38();
        case 39: return __get_PMPADDR39();
        case 40: return __get_PMPADDR40();
        case 41: return __get_PMPADDR41();
        case 42: return __get_PMPADDR42();
        case 43: return __get_PMPADDR43();
        case 44: return __get_PMPADDR44();
        case 45: return __get_PMPADDR45();
        case 46: return __get_PMPADDR46();
        case 47: return __get_PMPADDR47();
        case 48: return __get_PMPADDR48();
        case 49: return __get_PMPADDR49();
        case 50: return __get_PMPADDR50();
        case 51: return __get_PMPADDR51();
        case 52: return __get_PMPADDR52();
        case 53: return __get_PMPADDR53();
        case 54: return __get_PMPADDR54();
        case 55: return __get_PMPADDR55();
        case 56: return __get_PMPADDR56();
        case 57: return __get_PMPADDR57();
        case 58: return __get_PMPADDR58();
        case 59: return __get_PMPADDR59();
        case 60: return __get_PMPADDR60();
        case 61: return __get_PMPADDR61();
        case 62: return __get_PMPADDR62();
        case 63: return __get_PMPADDR63();
        default: return 0;
    }
}

/**
  \brief   Set PMPADDRx
  \details Writes the given value to the PMPADDRx Register.
  \param [in]    pmpaddr  PMPADDRx Register value to set
 */
#define DECLARE_PMPADDR_SETTER(n) \
__ALWAYS_STATIC_INLINE void __set_PMPADDR##n(unsigned long pmpaddr) \
{ \
    __ASM volatile("csrw pmpaddr"#n", %0" : : "r"(pmpaddr)); \
}
DECLARE_PMPADDR_SETTER(0)
DECLARE_PMPADDR_SETTER(1)
DECLARE_PMPADDR_SETTER(2)
DECLARE_PMPADDR_SETTER(3)
DECLARE_PMPADDR_SETTER(4)
DECLARE_PMPADDR_SETTER(5)
DECLARE_PMPADDR_SETTER(6)
DECLARE_PMPADDR_SETTER(7)
DECLARE_PMPADDR_SETTER(8)
DECLARE_PMPADDR_SETTER(9)
DECLARE_PMPADDR_SETTER(10)
DECLARE_PMPADDR_SETTER(11)
DECLARE_PMPADDR_SETTER(12)
DECLARE_PMPADDR_SETTER(13)
DECLARE_PMPADDR_SETTER(14)
DECLARE_PMPADDR_SETTER(15)
DECLARE_PMPADDR_SETTER(16)
DECLARE_PMPADDR_SETTER(17)
DECLARE_PMPADDR_SETTER(18)
DECLARE_PMPADDR_SETTER(19)
DECLARE_PMPADDR_SETTER(20)
DECLARE_PMPADDR_SETTER(21)
DECLARE_PMPADDR_SETTER(22)
DECLARE_PMPADDR_SETTER(23)
DECLARE_PMPADDR_SETTER(24)
DECLARE_PMPADDR_SETTER(25)
DECLARE_PMPADDR_SETTER(26)
DECLARE_PMPADDR_SETTER(27)
DECLARE_PMPADDR_SETTER(28)
DECLARE_PMPADDR_SETTER(29)
DECLARE_PMPADDR_SETTER(30)
DECLARE_PMPADDR_SETTER(31)
DECLARE_PMPADDR_SETTER(32)
DECLARE_PMPADDR_SETTER(33)
DECLARE_PMPADDR_SETTER(34)
DECLARE_PMPADDR_SETTER(35)
DECLARE_PMPADDR_SETTER(36)
DECLARE_PMPADDR_SETTER(37)
DECLARE_PMPADDR_SETTER(38)
DECLARE_PMPADDR_SETTER(39)
DECLARE_PMPADDR_SETTER(40)
DECLARE_PMPADDR_SETTER(41)
DECLARE_PMPADDR_SETTER(42)
DECLARE_PMPADDR_SETTER(43)
DECLARE_PMPADDR_SETTER(44)
DECLARE_PMPADDR_SETTER(45)
DECLARE_PMPADDR_SETTER(46)
DECLARE_PMPADDR_SETTER(47)
DECLARE_PMPADDR_SETTER(48)
DECLARE_PMPADDR_SETTER(49)
DECLARE_PMPADDR_SETTER(50)
DECLARE_PMPADDR_SETTER(51)
DECLARE_PMPADDR_SETTER(52)
DECLARE_PMPADDR_SETTER(53)
DECLARE_PMPADDR_SETTER(54)
DECLARE_PMPADDR_SETTER(55)
DECLARE_PMPADDR_SETTER(56)
DECLARE_PMPADDR_SETTER(57)
DECLARE_PMPADDR_SETTER(58)
DECLARE_PMPADDR_SETTER(59)
DECLARE_PMPADDR_SETTER(60)
DECLARE_PMPADDR_SETTER(61)
DECLARE_PMPADDR_SETTER(62)
DECLARE_PMPADDR_SETTER(63)

/**
  \brief        Set PMPADDRx by index
  \details      Writes the given value to the PMPADDRx Register.
  \param [in]   idx        PMP region index
  \param [in]   pmpaddr    PMPADDRx Register value to set
 */
__STATIC_INLINE void __set_PMPADDRx(unsigned long idx, unsigned long pmpaddr)
{
    switch(idx) {
        case 0: __set_PMPADDR0(pmpaddr); return;
        case 1: __set_PMPADDR1(pmpaddr); return;
        case 2: __set_PMPADDR2(pmpaddr); return;
        case 3: __set_PMPADDR3(pmpaddr); return;
        case 4: __set_PMPADDR4(pmpaddr); return;
        case 5: __set_PMPADDR5(pmpaddr); return;
        case 6: __set_PMPADDR6(pmpaddr); return;
        case 7: __set_PMPADDR7(pmpaddr); return;
        case 8: __set_PMPADDR8(pmpaddr); return;
        case 9: __set_PMPADDR9(pmpaddr); return;
        case 10: __set_PMPADDR10(pmpaddr); return;
        case 11: __set_PMPADDR11(pmpaddr); return;
        case 12: __set_PMPADDR12(pmpaddr); return;
        case 13: __set_PMPADDR13(pmpaddr); return;
        case 14: __set_PMPADDR14(pmpaddr); return;
        case 15: __set_PMPADDR15(pmpaddr); return;
        case 16: __set_PMPADDR16(pmpaddr); return;
        case 17: __set_PMPADDR17(pmpaddr); return;
        case 18: __set_PMPADDR18(pmpaddr); return;
        case 19: __set_PMPADDR19(pmpaddr); return;
        case 20: __set_PMPADDR20(pmpaddr); return;
        case 21: __set_PMPADDR21(pmpaddr); return;
        case 22: __set_PMPADDR22(pmpaddr); return;
        case 23: __set_PMPADDR23(pmpaddr); return;
        case 24: __set_PMPADDR24(pmpaddr); return;
        case 25: __set_PMPADDR25(pmpaddr); return;
        case 26: __set_PMPADDR26(pmpaddr); return;
        case 27: __set_PMPADDR27(pmpaddr); return;
        case 28: __set_PMPADDR28(pmpaddr); return;
        case 29: __set_PMPADDR29(pmpaddr); return;
        case 30: __set_PMPADDR30(pmpaddr); return;
        case 31: __set_PMPADDR31(pmpaddr); return;
        case 32: __set_PMPADDR32(pmpaddr); return;
        case 33: __set_PMPADDR33(pmpaddr); return;
        case 34: __set_PMPADDR34(pmpaddr); return;
        case 35: __set_PMPADDR35(pmpaddr); return;
        case 36: __set_PMPADDR36(pmpaddr); return;
        case 37: __set_PMPADDR37(pmpaddr); return;
        case 38: __set_PMPADDR38(pmpaddr); return;
        case 39: __set_PMPADDR39(pmpaddr); return;
        case 40: __set_PMPADDR40(pmpaddr); return;
        case 41: __set_PMPADDR41(pmpaddr); return;
        case 42: __set_PMPADDR42(pmpaddr); return;
        case 43: __set_PMPADDR43(pmpaddr); return;
        case 44: __set_PMPADDR44(pmpaddr); return;
        case 45: __set_PMPADDR45(pmpaddr); return;
        case 46: __set_PMPADDR46(pmpaddr); return;
        case 47: __set_PMPADDR47(pmpaddr); return;
        case 48: __set_PMPADDR48(pmpaddr); return;
        case 49: __set_PMPADDR49(pmpaddr); return;
        case 50: __set_PMPADDR50(pmpaddr); return;
        case 51: __set_PMPADDR51(pmpaddr); return;
        case 52: __set_PMPADDR52(pmpaddr); return;
        case 53: __set_PMPADDR53(pmpaddr); return;
        case 54: __set_PMPADDR54(pmpaddr); return;
        case 55: __set_PMPADDR55(pmpaddr); return;
        case 56: __set_PMPADDR56(pmpaddr); return;
        case 57: __set_PMPADDR57(pmpaddr); return;
        case 58: __set_PMPADDR58(pmpaddr); return;
        case 59: __set_PMPADDR59(pmpaddr); return;
        case 60: __set_PMPADDR60(pmpaddr); return;
        case 61: __set_PMPADDR61(pmpaddr); return;
        case 62: __set_PMPADDR62(pmpaddr); return;
        case 63: __set_PMPADDR63(pmpaddr); return;
        default: return;
    }
}

/**
  \brief        Set MSECCFG
  \details      Writes the given value to the MSECCFG Register.
  \param [in]   mseccfg    MSECCFG Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSECCFG(unsigned long mseccfg)
{
    __ASM volatile("csrw mseccfg, %0" : : "r"(mseccfg));
}

/**
  \brief        Get MSECCFG
  \details      Returns the current value of the MSECCFG register.
  \return       MSECCFG Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MSECCFG(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, mseccfg" : "=r"(result));
    return result;
}

////////////////////////////////////////////////////////////////////////

/**
  \brief        Set PMPSWITCH0
  \details      Writes the given value to the PMPSWITCH0 Register.
  \param [in]   pmpswitch0    PMPSWITCH0 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_PMPSWITCH0(unsigned long pmpswitch0)
{
    __set_MISELECT(PMP_MMIO_PMPSWITCH0);
    __set_MIREG(pmpswitch0);
}

/**
  \brief        Get PMPSWITCH0
  \details      Returns the current value of the PMPSWITCH0 register.
  \return       PMPSWITCH0 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_PMPSWITCH0(void)
{
    __set_MISELECT(PMP_MMIO_PMPSWITCH0);
    return __get_MIREG();
}

/**
  \brief        Set PMPSWITCH1
  \details      Writes the given value to the PMPSWITCH1 Register.
  \param [in]   pmpswitch1    PMPSWITCH1 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_PMPSWITCH1(unsigned long pmpswitch1)
{
    __set_MISELECT(PMP_MMIO_PMPSWITCH1);
    __set_MIREG(pmpswitch1);
}

/**
  \brief        Get PMPSWITCH1
  \details      Returns the current value of the PMPSWITCH1 register.
  \return       PMPSWITCH1 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_PMPSWITCH1(void)
{
    __set_MISELECT(PMP_MMIO_PMPSWITCH1);
    return __get_MIREG();
}
////////////////////////////////////////////////////////////////////////

/* ##########################   PMP functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_PMPFunctions PMP Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/**
  \brief        Configure physical memory protection region.
  \param [in]   idx         Memory protection region (0, 1, 2, ..., 63).
  \param [in]   base_addr   Base address must be aligned with page size.
  \param [in]   size        \ref region_size_e. Memory protection region size.
  \param [in]   attr        \ref pmp_region_attr_t. Memory protection region attribute.
  \param [in]   enable      Enable or disable memory protection region.
 */
__STATIC_INLINE void csi_pmp_config_region(uint32_t idx, unsigned long base_addr, region_size_e size,
                                           pmp_region_attr_t attr, uint32_t enable)
{
    uint8_t pmpxcfg = 0;
    unsigned long addr = 0;

    if (idx > 63) {
        return;
    }

    if (!enable) {
        attr.a = (address_matching_e)0;
    }

    if (attr.a == ADDRESS_MATCHING_TOR) {
        addr = base_addr >> 2;
    } else {
        if (size == REGION_SIZE_4B) {
            addr = base_addr >> 2;
            attr.a = (address_matching_e)2;
        } else {
            addr = ((base_addr >> 2) & (ULONG_MAX - ((1 << (size + 1)) - 1))) | ((1 << size) - 1);
        }
    }

    __set_PMPADDRx(idx, addr);

    pmpxcfg |= (attr.r << PMP_PMPCFG_R_Pos) | (attr.w << PMP_PMPCFG_W_Pos) |
               (attr.x << PMP_PMPCFG_X_Pos) | (attr.a << PMP_PMPCFG_A_Pos) |
               (attr.l << PMP_PMPCFG_L_Pos);

    __set_PMPxCFG(idx, pmpxcfg);
}

/**
  \brief        Disable physical memory protection region by idx.
  \param [in]   idx    Memory protection region (0, 1, 2, ..., 63).
 */
__STATIC_INLINE void csi_pmp_disable_region(uint32_t idx)
{
    if (idx > 63) {
        return;
    }
    __set_PMPxCFG(idx, __get_PMPxCFG(idx) & (~PMP_PMPCFG_A_Msk));
}

/**
  \brief        Configure physical memory protection entry.
  \param [in]   idx         Memory protection region (0, 1, 2, ..., 63).
  \param [in]   base_addr   Base address.
  \param [in]   size        Memory protection entry size.
  \param [in]   attr        \ref pmp_region_attr_t. Memory protection region attribute.
  \param [in]   enable      Enable or disable memory protection region.
 */
__STATIC_INLINE void csi_pmp_config_entry(uint32_t idx, unsigned long base_addr, unsigned long size,
                                          pmp_region_attr_t attr, uint32_t enable)
{
    uint8_t pmpxcfg = 0;
    unsigned long addr = 0;

    if (idx > 63) {
        return;
    }

    if (!enable) {
        attr.a = (address_matching_e)0;
    }

    if (attr.a == ADDRESS_MATCHING_TOR || attr.a == ADDRESS_MATCHING_NA4) {
        addr = base_addr >> 2;
    } else {
        size = align_to_power_of_two(size);
        uint32_t bits = log2_ulong(size) - 3;
        addr = ((base_addr >> 2) & (ULONG_MAX - ((1 << (bits + 1)) - 1))) | ((1 << bits) - 1);
    }

    __set_PMPADDRx(idx, addr);

    pmpxcfg |= (attr.r << PMP_PMPCFG_R_Pos) | (attr.w << PMP_PMPCFG_W_Pos) |
               (attr.x << PMP_PMPCFG_X_Pos) | (attr.a << PMP_PMPCFG_A_Pos) |
               (attr.l << PMP_PMPCFG_L_Pos);

    __set_PMPxCFG(idx, pmpxcfg);
}

/**
  \brief        Disable physical memory protection entry by idx.
  \param [in]   idx    Memory protection region (0, 1, 2, ..., 63).
 */
__STATIC_INLINE void csi_pmp_disable_entry(uint32_t idx)
{
    if (idx > 63) {
        return;
    }
    __set_PMPxCFG(idx, __get_PMPxCFG(idx) & (~PMP_PMPCFG_A_Msk));
}

///////////////////////////////////////////////////////////////////////////////
/**
  \brief        Activate physical memory protection entry by idx in pmpswitch0/pmpswitch1.
  \param [in]   idx    Memory protection region (0, 1, 2, ..., 63).
 */
__STATIC_INLINE void csi_pmp_ctx_switching_activate_entry(uint32_t idx)
{
    /* xt extension */
    uint32_t l_idx;
    unsigned long pmpswitch;

#if __riscv_xlen == 32
    if (idx > 31) {
        l_idx = idx - 32;
        pmpswitch = __get_PMPSWITCH1();
    } else
#endif
    {
        l_idx = idx;
        pmpswitch = __get_PMPSWITCH0();
    }

    pmpswitch |= (1UL << l_idx);

#if __riscv_xlen == 32
    if (idx > 31) {
        __set_PMPSWITCH1(pmpswitch);
    } else
#endif
    {
        __set_PMPSWITCH0(pmpswitch);
    }
}

/**
  \brief        Deactivate physical memory protection entry by idx in pmpswitch0/pmpswitch1.
  \param [in]   idx    Memory protection region (0, 1, 2, ..., 63).
 */
__STATIC_INLINE void csi_pmp_ctx_switching_deactivate_entry(uint32_t idx)
{
    /* xt extension */
    uint32_t l_idx;
    unsigned long pmpswitch;

#if __riscv_xlen == 32
    if (idx > 31) {
        l_idx = idx - 32;
        pmpswitch = __get_PMPSWITCH1();
    } else
#endif
    {
        l_idx = idx;
        pmpswitch = __get_PMPSWITCH0();
    }

    pmpswitch &= ~(1UL << l_idx);

#if __riscv_xlen == 32
    if (idx > 31) {
        __set_PMPSWITCH1(pmpswitch);
    } else
#endif
    {
        __set_PMPSWITCH0(pmpswitch);
    }
}

/**
  \brief        Activate physical memory protection entries by idx in pmpswitch0/pmpswitch1.
  \param [in]   entries_idx    Array of entries indices to be activated.
  \param [in]   entries_num    Number of entries to be activated.
 */
__STATIC_INLINE void csi_pmp_ctx_switching_activate_entries(uint32_t entries_idx[], uint32_t entries_num)
{
    unsigned long pmpswitch0 = __get_PMPSWITCH0();
#if __riscv_xlen == 32
    unsigned long pmpswitch1 = __get_PMPSWITCH1();
#endif

    for (uint32_t i = 0; i < entries_num; i++) {
        uint32_t idx = entries_idx[i];
#if __riscv_xlen == 32
        if (idx < 32) {
            pmpswitch0 |= (1UL << idx);
        } else if (idx < 64) {
            pmpswitch1 |= (1UL << (idx - 32));
        }
#else
        pmpswitch0 |= (1UL << idx);
#endif
    }

#if __riscv_xlen == 32
    __set_PMPSWITCH0(pmpswitch0);
    __set_PMPSWITCH1(pmpswitch1);
#else
    __set_PMPSWITCH0(pmpswitch0);
#endif
}

/**
  \brief        Deactivate physical memory protection entries by idx in pmpswitch0/pmpswitch1.
  \param [in]   entries_idx    Array of entries indices to be deactivated.
  \param [in]   entries_num    Number of entries to be deactivated.
 */
__STATIC_INLINE void csi_pmp_ctx_switching_deactivate_entries(uint32_t entries_idx[], uint32_t entries_num)
{
    unsigned long pmpswitch0 = __get_PMPSWITCH0();
#if __riscv_xlen == 32
    unsigned long pmpswitch1 = __get_PMPSWITCH1();
#endif

    for (uint32_t i = 0; i < entries_num; i++) {
        uint32_t idx = entries_idx[i];
#if __riscv_xlen == 32
        if (idx < 32) {
            pmpswitch0 &= ~(1UL << idx);
        } else if (idx < 64) {
            pmpswitch1 &= ~(1UL << (idx - 32));
        }
#else
        pmpswitch0 &= ~(1UL << idx);
#endif
    }

#if __riscv_xlen == 32
    __set_PMPSWITCH0(pmpswitch0);
    __set_PMPSWITCH1(pmpswitch1);
#else
    __set_PMPSWITCH0(pmpswitch0);
#endif
}
///////////////////////////////////////////////////////////////////////////////

/*@} end of CSI_Core_PMPFunctions */

#endif /* CORE_RV_PMP_H */
