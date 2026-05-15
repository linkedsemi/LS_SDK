 /*
 * Copyright (C) 2017-2026 Alibaba Group Holding Limited
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
#ifndef __CORE_RV_PMU_H__
#define __CORE_RV_PMU_H__

#include <stdint.h>
#include <limits.h>
#include "csi_rv_common.h"
#include "csi_rv_encoding.h"

/* OF bit position in mhpmevent register (bit 63) */
#define CSI_PMU_MHPMEVENT_OF_BIT    (1ULL << 63)

/* C908 valid counter range */
#define CSI_PMU_COUNTER_MCYCLE      0
#define CSI_PMU_COUNTER_MINSTRET    2
#define CSI_PMU_COUNTER_HPM_MIN     3
#define CSI_PMU_COUNTER_HPM_MAX     18

/**
  \brief    Set MCOUNTINHIBIT
  \details  Write MCOUNTINHIBIT Register.
  \param [in]    value  MCOUNTINHIBIT Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MCOUNTINHIBIT(uint32_t value)
{
    __ASM volatile("csrw mcountinhibit, %0" : : "r"(value));
}

/**
  \brief    Get MCOUNTINHIBIT
  \details  Read MCOUNTINHIBIT Register
  \return   MCOUNTINHIBIT Register value
  */
__ALWAYS_STATIC_INLINE unsigned int __get_MCOUNTINHIBIT(void)
{
    uint32_t result;
    __ASM volatile("csrr %0, mcountinhibit" : "=r"(result));
    return result;
}

/**
  \brief         Set MHPMEVENT
  \details       Write MHPMEVENT Register
  \param [in]    idx    Index of MHPMEVENT Register
  \param [in]    value  MHPMEVENT Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MHPMEVENT(unsigned long idx, unsigned long value)
{
    switch (idx) {
        case 0: rv_csr_write(0x7E0, value); break;
        case 2: rv_csr_write(0x7E1, value); break;
        case 3: rv_csr_write(0x323, value); break;
        case 4: rv_csr_write(0x324, value); break;
        case 5: rv_csr_write(0x325, value); break;
        case 6: rv_csr_write(0x326, value); break;
        case 7: rv_csr_write(0x327, value); break;
        case 8: rv_csr_write(0x328, value); break;
        case 9: rv_csr_write(0x329, value); break;
        case 10: rv_csr_write(0x32a, value); break;
        case 11: rv_csr_write(0x32b, value); break;
        case 12: rv_csr_write(0x32c, value); break;
        case 13: rv_csr_write(0x32d, value); break;
        case 14: rv_csr_write(0x32e, value); break;
        case 15: rv_csr_write(0x32f, value); break;
        case 16: rv_csr_write(0x330, value); break;
        case 17: rv_csr_write(0x331, value); break;
        case 18: rv_csr_write(0x332, value); break;
        case 19: rv_csr_write(0x333, value); break;
        case 20: rv_csr_write(0x334, value); break;
        case 21: rv_csr_write(0x335, value); break;
        case 22: rv_csr_write(0x336, value); break;
        case 23: rv_csr_write(0x337, value); break;
        case 24: rv_csr_write(0x338, value); break;
        case 25: rv_csr_write(0x339, value); break;
        case 26: rv_csr_write(0x33a, value); break;
        case 27: rv_csr_write(0x33b, value); break;
        case 28: rv_csr_write(0x33c, value); break;
        case 29: rv_csr_write(0x33d, value); break;
        case 30: rv_csr_write(0x33e, value); break;
        case 31: rv_csr_write(0x33F, value); break;
        default: break;
    }
}

/**
  \brief        Get MHPMEVENT
  \details      Read MHPMEVENT Register.
  \param [in]   idx    Index of MHPMEVENT Register to read.
  \return       MHPMEVENT Register Value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MHPMEVENT(unsigned long idx)
{
    switch (idx) {
        case 0: return rv_csr_read(0x7E0);
        case 2: return rv_csr_read(0x7E1);
        case 3: return rv_csr_read(0x323);
        case 4: return rv_csr_read(0x324);
        case 5: return rv_csr_read(0x325);
        case 6: return rv_csr_read(0x326);
        case 7: return rv_csr_read(0x327);
        case 8: return rv_csr_read(0x328);
        case 9: return rv_csr_read(0x329);
        case 10: return rv_csr_read(0x32a);
        case 11: return rv_csr_read(0x32b);
        case 12: return rv_csr_read(0x32c);
        case 13: return rv_csr_read(0x32d);
        case 14: return rv_csr_read(0x32e);
        case 15: return rv_csr_read(0x32f);
        case 16: return rv_csr_read(0x330);
        case 17: return rv_csr_read(0x331);
        case 18: return rv_csr_read(0x332);
        case 19: return rv_csr_read(0x333);
        case 20: return rv_csr_read(0x334);
        case 21: return rv_csr_read(0x335);
        case 22: return rv_csr_read(0x336);
        case 23: return rv_csr_read(0x337);
        case 24: return rv_csr_read(0x338);
        case 25: return rv_csr_read(0x339);
        case 26: return rv_csr_read(0x33a);
        case 27: return rv_csr_read(0x33b);
        case 28: return rv_csr_read(0x33c);
        case 29: return rv_csr_read(0x33d);
        case 30: return rv_csr_read(0x33e);
        case 31: return rv_csr_read(0x33F);
        default: return 0;
    }
}

/**
  \brief         Set MHPMEVENTH
  \details       Write MHPMEVENTH Register
  \param [in]    idx    Index of MHPMEVENT Register
  \param [in]    value  MHPMEVENTH Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MHPMEVENTH(unsigned long idx, unsigned long value)
{
    switch (idx) {
        case 3: rv_csr_write(0x723, value); break;
        case 4: rv_csr_write(0x724, value); break;
        case 5: rv_csr_write(0x725, value); break;
        case 6: rv_csr_write(0x726, value); break;
        case 7: rv_csr_write(0x727, value); break;
        case 8: rv_csr_write(0x728, value); break;
        case 9: rv_csr_write(0x729, value); break;
        case 10: rv_csr_write(0x72A, value); break;
        case 11: rv_csr_write(0x72B, value); break;
        case 12: rv_csr_write(0x72C, value); break;
        case 13: rv_csr_write(0x72D, value); break;
        case 14: rv_csr_write(0x72E, value); break;
        case 15: rv_csr_write(0x72F, value); break;
        case 16: rv_csr_write(0x730, value); break;
        case 17: rv_csr_write(0x731, value); break;
        case 18: rv_csr_write(0x732, value); break;
        case 19: rv_csr_write(0x733, value); break;
        case 20: rv_csr_write(0x734, value); break;
        case 21: rv_csr_write(0x735, value); break;
        case 22: rv_csr_write(0x736, value); break;
        case 23: rv_csr_write(0x737, value); break;
        case 24: rv_csr_write(0x738, value); break;
        case 25: rv_csr_write(0x739, value); break;
        case 26: rv_csr_write(0x73A, value); break;
        case 27: rv_csr_write(0x73B, value); break;
        case 28: rv_csr_write(0x73C, value); break;
        case 29: rv_csr_write(0x73D, value); break;
        case 30: rv_csr_write(0x73E, value); break;
        case 31: rv_csr_write(0x73F, value); break;
        default: break;
    }
}

/**
  \brief        Get MHPMEVENTH
  \details      Read MHPMEVENTH Register.
  \param [in]   idx    Index of MHPMEVENTH Register to read.
  \return       MHPMEVENTH Register Value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MHPMEVENTH(unsigned long idx)
{
    switch (idx) {
        case 3: return rv_csr_read(0x723);
        case 4: return rv_csr_read(0x724);
        case 5: return rv_csr_read(0x725);
        case 6: return rv_csr_read(0x726);
        case 7: return rv_csr_read(0x727);
        case 8: return rv_csr_read(0x728);
        case 9: return rv_csr_read(0x729);
        case 10: return rv_csr_read(0x72A);
        case 11: return rv_csr_read(0x72B);
        case 12: return rv_csr_read(0x72C);
        case 13: return rv_csr_read(0x72D);
        case 14: return rv_csr_read(0x72E);
        case 15: return rv_csr_read(0x72F);
        case 16: return rv_csr_read(0x730);
        case 17: return rv_csr_read(0x731);
        case 18: return rv_csr_read(0x732);
        case 19: return rv_csr_read(0x733);
        case 20: return rv_csr_read(0x734);
        case 21: return rv_csr_read(0x735);
        case 22: return rv_csr_read(0x736);
        case 23: return rv_csr_read(0x737);
        case 24: return rv_csr_read(0x738);
        case 25: return rv_csr_read(0x739);
        case 26: return rv_csr_read(0x73A);
        case 27: return rv_csr_read(0x73B);
        case 28: return rv_csr_read(0x73C);
        case 29: return rv_csr_read(0x73D);
        case 30: return rv_csr_read(0x73E);
        case 31: return rv_csr_read(0x73F);
        default: return 0;
    }
}

/**
  \brief         Set MHPMCOUNTER
  \details       Write MHPMCOUNTER Register
  \param [in]    idx    Index of MHPMCOUNTER Register
  \param [in]    value  MHPMCOUNTER Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MHPMCOUNTER(unsigned long idx, unsigned long value)
{
    switch (idx) {
        case 3: rv_csr_write(0xB03, (value)); break;
        case 4: rv_csr_write(0xB04, (value)); break;
        case 5: rv_csr_write(0xB05, (value)); break;
        case 6: rv_csr_write(0xB06, (value)); break;
        case 7: rv_csr_write(0xB07, (value)); break;
        case 8: rv_csr_write(0xB08, (value)); break;
        case 9: rv_csr_write(0xB09, (value)); break;
        case 10: rv_csr_write(0xB0A, (value)); break;
        case 11: rv_csr_write(0xB0B, (value)); break;
        case 12: rv_csr_write(0xB0C, (value)); break;
        case 13: rv_csr_write(0xB0D, (value)); break;
        case 14: rv_csr_write(0xB0E, (value)); break;
        case 15: rv_csr_write(0xB0F, (value)); break;
        case 16: rv_csr_write(0xB10, (value)); break;
        case 17: rv_csr_write(0xB11, (value)); break;
        case 18: rv_csr_write(0xB12, (value)); break;
        case 19: rv_csr_write(0xB13, (value)); break;
        case 20: rv_csr_write(0xB14, (value)); break;
        case 21: rv_csr_write(0xB15, (value)); break;
        case 22: rv_csr_write(0xB16, (value)); break;
        case 23: rv_csr_write(0xB17, (value)); break;
        case 24: rv_csr_write(0xB18, (value)); break;
        case 25: rv_csr_write(0xB19, (value)); break;
        case 26: rv_csr_write(0xB1A, (value)); break;
        case 27: rv_csr_write(0xB1B, (value)); break;
        case 28: rv_csr_write(0xB1C, (value)); break;
        case 29: rv_csr_write(0xB1D, (value)); break;
        case 30: rv_csr_write(0xB1E, (value)); break;
        case 31: rv_csr_write(0xB1F, (value)); break;
        default: break;
    }
}

/**
  \brief       Get MHPMCOUNTER
  \details     Write MHPMCOUNTER Register.
  \param [in]  idx      Index of MHPMCOUNTER Register
  \return      MHPMCOUNTER Register Value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MHPMCOUNTER(unsigned long idx)
{
    switch (idx) {
        case 3: return rv_csr_read(0xB03);
        case 4: return rv_csr_read(0xB04);
        case 5: return rv_csr_read(0xB05);
        case 6: return rv_csr_read(0xB06);
        case 7: return rv_csr_read(0xB07);
        case 8: return rv_csr_read(0xB08);
        case 9: return rv_csr_read(0xB09);
        case 10: return rv_csr_read(0xB0A);
        case 11: return rv_csr_read(0xB0B);
        case 12: return rv_csr_read(0xB0C);
        case 13: return rv_csr_read(0xB0D);
        case 14: return rv_csr_read(0xB0E);
        case 15: return rv_csr_read(0xB0F);
        case 16: return rv_csr_read(0xB10);
        case 17: return rv_csr_read(0xB11);
        case 18: return rv_csr_read(0xB12);
        case 19: return rv_csr_read(0xB13);
        case 20: return rv_csr_read(0xB14);
        case 21: return rv_csr_read(0xB15);
        case 22: return rv_csr_read(0xB16);
        case 23: return rv_csr_read(0xB17);
        case 24: return rv_csr_read(0xB18);
        case 25: return rv_csr_read(0xB19);
        case 26: return rv_csr_read(0xB1A);
        case 27: return rv_csr_read(0xB1B);
        case 28: return rv_csr_read(0xB1C);
        case 29: return rv_csr_read(0xB1D);
        case 30: return rv_csr_read(0xB1E);
        case 31: return rv_csr_read(0xB1F);
        default: return 0;
    }
}

/**
  \brief         Set MHPMCOUNTERH
  \details       Write MHPMCOUNTERH Register
  \param [in]    idx    Index of MHPMCOUNTERH Register
  \param [in]    value  MHPMCOUNTERH Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MHPMCOUNTERH(unsigned long idx, unsigned long value)
{
    switch (idx) {
        case 3: rv_csr_write(0xB83, (value)); break;
        case 4: rv_csr_write(0xB84, (value)); break;
        case 5: rv_csr_write(0xB85, (value)); break;
        case 6: rv_csr_write(0xB86, (value)); break;
        case 7: rv_csr_write(0xB87, (value)); break;
        case 8: rv_csr_write(0xB88, (value)); break;
        case 9: rv_csr_write(0xB89, (value)); break;
        case 10: rv_csr_write(0xB8A, (value)); break;
        case 11: rv_csr_write(0xB8B, (value)); break;
        case 12: rv_csr_write(0xB8C, (value)); break;
        case 13: rv_csr_write(0xB8D, (value)); break;
        case 14: rv_csr_write(0xB8E, (value)); break;
        case 15: rv_csr_write(0xB8F, (value)); break;
        case 16: rv_csr_write(0xB90, (value)); break;
        case 17: rv_csr_write(0xB91, (value)); break;
        case 18: rv_csr_write(0xB92, (value)); break;
        case 19: rv_csr_write(0xB93, (value)); break;
        case 20: rv_csr_write(0xB94, (value)); break;
        case 21: rv_csr_write(0xB95, (value)); break;
        case 22: rv_csr_write(0xB96, (value)); break;
        case 23: rv_csr_write(0xB97, (value)); break;
        case 24: rv_csr_write(0xB98, (value)); break;
        case 25: rv_csr_write(0xB99, (value)); break;
        case 26: rv_csr_write(0xB9A, (value)); break;
        case 27: rv_csr_write(0xB9B, (value)); break;
        case 28: rv_csr_write(0xB9C, (value)); break;
        case 29: rv_csr_write(0xB9D, (value)); break;
        case 30: rv_csr_write(0xB9E, (value)); break;
        case 31: rv_csr_write(0xB9F, (value)); break;
        default: break;
    }
}

/**
  \brief       Get MHPMCOUNTERH
  \details     Write MHPMCOUNTERH Register.
  \param [in]  idx      Index of MHPMCOUNTERH Register
  \return      MHPMCOUNTERH Register Value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MHPMCOUNTERH(unsigned long idx)
{
    switch (idx) {
        case 3: return rv_csr_read(0xB83);
        case 4: return rv_csr_read(0xB84);
        case 5: return rv_csr_read(0xB85);
        case 6: return rv_csr_read(0xB86);
        case 7: return rv_csr_read(0xB87);
        case 8: return rv_csr_read(0xB88);
        case 9: return rv_csr_read(0xB89);
        case 10: return rv_csr_read(0xB8A);
        case 11: return rv_csr_read(0xB8B);
        case 12: return rv_csr_read(0xB8C);
        case 13: return rv_csr_read(0xB8D);
        case 14: return rv_csr_read(0xB8E);
        case 15: return rv_csr_read(0xB8F);
        case 16: return rv_csr_read(0xB90);
        case 17: return rv_csr_read(0xB91);
        case 18: return rv_csr_read(0xB92);
        case 19: return rv_csr_read(0xB93);
        case 20: return rv_csr_read(0xB94);
        case 21: return rv_csr_read(0xB95);
        case 22: return rv_csr_read(0xB96);
        case 23: return rv_csr_read(0xB97);
        case 24: return rv_csr_read(0xB98);
        case 25: return rv_csr_read(0xB99);
        case 26: return rv_csr_read(0xB9A);
        case 27: return rv_csr_read(0xB9B);
        case 28: return rv_csr_read(0xB9C);
        case 29: return rv_csr_read(0xB9D);
        case 30: return rv_csr_read(0xB9E);
        case 31: return rv_csr_read(0xB9F);
        default: return 0;
    }
}

/**
  \brief    Set MCOUNTERINTEN
  \details  Write MCOUNTERINTEN Register.
  \param [in]    value  MCOUNTERINTEN Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MCOUNTERINTEN(uint32_t value)
{
    __ASM volatile("csrw 0x7ca, %0" : : "r"(value));
}

/**
  \brief    Get MCOUNTERINTEN
  \details  Read MCOUNTERINTEN Register
  \return   MCOUNTERINTEN Register value
  */
__ALWAYS_STATIC_INLINE uint32_t __get_MCOUNTERINTEN(void)
{
    uint32_t result;
    __ASM volatile("csrr %0, 0x7ca" : "=r"(result));
    return result;
}

__STATIC_INLINE uint64_t csi_pmu_read_mcycle(void)
{
    uint64_t result;
#if __riscv_xlen == 64
    result = __get_MCYCLE();
#else
    result = ((uint64_t)__get_MCYCLEH() << 32) | __get_MCYCLE();
#endif
    return result;
}

__STATIC_INLINE void csi_pmu_write_minstret(uint64_t value)
{
#if __riscv_xlen == 64
    __set_MINSTRET(value);
#else
    __set_MINSTRET((uint32_t)(value & 0x0ffff));
    __set_MINSTRETH((uint32_t)((value >> 32) & 0x0ffff));
#endif
}

__STATIC_INLINE uint64_t csi_pmu_read_minstret(void)
{
    uint64_t result;
#if __riscv_xlen == 64
    result = __get_MINSTRET();
#else
    result = ((uint64_t)__get_MINSTRETH() << 32) | __get_MINSTRET();
#endif
    return result;
}

__STATIC_INLINE uint64_t csi_pmu_read_mtime(void)
{
    uint64_t result;
#if __riscv_xlen == 64
    result = __get_MTIME();
#else
    result = ((uint64_t)__get_MTIMEH() << 32) | __get_MTIME();
#endif
    return result;
}

__STATIC_INLINE void csi_pmu_hpmcounter_disable(uint32_t id)
{
    uint64_t mask = __get_MCOUNTINHIBIT();
    mask |= (1 << id);
    __set_MCOUNTINHIBIT(mask);
}

__STATIC_INLINE void csi_pmu_hpmcounter_enable(uint32_t id)
{
    uint64_t mask = __get_MCOUNTINHIBIT();
    mask &= ~(1 << id);
    __set_MCOUNTINHIBIT(mask);
}

__STATIC_INLINE void csi_pmu_hpmcounter_write_value(int idx, uint64_t value)
{
#if __riscv_xlen == 64
    __set_MHPMCOUNTER(idx, value);
#else
    __set_MHPMCOUNTER(idx, (uint32_t)(value & 0x0ffff));
    __set_MHPMCOUNTERH(idx, (uint32_t)((value >> 32) & 0x0ffff));
#endif
}

__STATIC_INLINE uint64_t csi_pmu_hpmcounter_read_value(uint16_t idx)
{
    uint64_t result;
#if __riscv_xlen == 64
    result = __get_MHPMCOUNTER(idx);
#else
    result = ((uint64_t)__get_MHPMCOUNTERH(idx) << 32) | __get_MHPMCOUNTER(idx);
#endif
    return result;
}

/**
  \brief         Write MHPMEVENT Register
  \details       Set MHPMEVENT Register value for specified index
  \param [in]    idx    Index of MHPMEVENT Register (0, 2, or 3-31)
  \param [in]    value  MHPMEVENT Register value to set (64-bit)
  */
__STATIC_INLINE void csi_pmu_hpmcounter_write_event(uint16_t idx, uint64_t value)
{
#if __riscv_xlen == 64
    __set_MHPMEVENT(idx, value);
#else
    __set_MHPMEVENT(idx, (uint32_t)(value & 0xFFFFFFFF));
#if !CONFIG_CPU_XUANTIE_E9XX
    __set_MHPMEVENTH(idx, (uint32_t)((value >> 32) & 0xFFFFFFFF));
#endif
#endif
}

/**
  \brief         Read MHPMEVENT Register
  \details       Get MHPMEVENT Register value for specified index
  \param [in]    idx    Index of MHPMEVENT Register (0, 2, or 3-31)
  \return        MHPMEVENT Register Value (64-bit)
  */
__STATIC_INLINE uint64_t csi_pmu_hpmcounter_read_event(uint16_t idx)
{
    uint64_t result;
#if __riscv_xlen == 64
    result = __get_MHPMEVENT(idx);
#else
#if CONFIG_CPU_XUANTIE_E9XX
    result = (uint64_t)__get_MHPMEVENT(idx);
#else
    result = ((uint64_t)__get_MHPMEVENTH(idx) << 32) | __get_MHPMEVENT(idx);
#endif
#endif
    return result;
}

/**
  \brief         Enable PMU counter overflow interrupt
  \details       Enable overflow interrupt for specified counter
  \param [in]    id    Counter index (0=mcycle, 2=minstret, 3-31=hpmcounter)
  */
__STATIC_INLINE void csi_pmu_hpmcounter_enable_interrupt(uint32_t id)
{
    uint32_t mask = __get_MCOUNTERINTEN();
    mask |= (1U << id);
    __set_MCOUNTERINTEN(mask);
}

/**
  \brief         Disable PMU counter overflow interrupt
  \details       Disable overflow interrupt for specified counter
  \param [in]    id    Counter index (0=mcycle, 2=minstret, 3-31=hpmcounter)
  */
__STATIC_INLINE void csi_pmu_hpmcounter_disable_interrupt(uint32_t id)
{
    uint32_t mask = __get_MCOUNTERINTEN();
    mask &= ~(1U << id);
    __set_MCOUNTERINTEN(mask);
}

/**
  \brief         Get PMU counter overflow interrupt status
  \details       Check if overflow interrupt is enabled for specified counter
  \param [in]    id    Counter index (0=mcycle, 2=minstret, 3-31=hpmcounter)
  \return        1 if enabled, 0 if disabled
  */
__STATIC_INLINE uint32_t csi_pmu_hpmcounter_get_interrupt_status(uint32_t id)
{
    uint32_t mask = __get_MCOUNTERINTEN();
    return (mask >> id) & 0x1U;
}

/**
  \brief         Enable all PMU counter overflow interrupts
  \details       Enable overflow interrupt for all counters (except bit 1 reserved)
  */
__STATIC_INLINE void csi_pmu_hpmcounter_enable_all_interrupts(void)
{
    __set_MCOUNTERINTEN(0xFFFFFFFD);  /* bit 1 is reserved */
}

/**
  \brief         Disable all PMU counter overflow interrupts
  \details       Disable overflow interrupt for all counters
  */
__STATIC_INLINE void csi_pmu_hpmcounter_disable_all_interrupts(void)
{
    __set_MCOUNTERINTEN(0x0);
}

/**
  \brief         Check if PMU counter overflow flag is set
  \details       Check OF bit (bit 63) in MHPMEVENT register for specified counter
  \param [in]    idx    Counter index (3-31 for hpmcounter)
  \return        1 if overflow occurred, 0 otherwise
  */
__STATIC_INLINE uint32_t csi_pmu_hpmcounter_get_overflow_flag(uint16_t idx)
{
    uint64_t event = csi_pmu_hpmcounter_read_event(idx);
    return (event & CSI_PMU_MHPMEVENT_OF_BIT) ? 1U : 0U;
}

/**
  \brief         Clear PMU counter overflow flag
  \details       Clear OF bit (bit 63) in MHPMEVENT register for specified counter
  \param [in]    idx    Counter index (3-31 for hpmcounter)
  */
__STATIC_INLINE void csi_pmu_hpmcounter_clear_overflow_flag(uint16_t idx)
{
    uint64_t event = csi_pmu_hpmcounter_read_event(idx);
    event &= ~CSI_PMU_MHPMEVENT_OF_BIT;
    csi_pmu_hpmcounter_write_event(idx, event);
}

/**
  \brief         Get all PMU counters overflow status
  \details       Get overflow flags for all hpmcounters (3-31)
  \return        Bitmask of overflow flags, bit N corresponds to counter N
  */
__STATIC_INLINE uint32_t csi_pmu_hpmcounter_get_all_overflow_flags(void)
{
    uint32_t flags = 0U;
    uint16_t idx;

    for (idx = CSI_PMU_COUNTER_HPM_MIN; idx <= CSI_PMU_COUNTER_HPM_MAX; idx++) {
        if (csi_pmu_hpmcounter_get_overflow_flag(idx)) {
            flags |= (1U << idx);
        }
    }
    return flags;
}

/**
  \brief         Clear all PMU counters overflow flags
  \details       Clear OF bit for all hpmcounters (3-31)
  */
__STATIC_INLINE void csi_pmu_hpmcounter_clear_all_overflow_flags(void)
{
    uint16_t idx;

    for (idx = CSI_PMU_COUNTER_HPM_MIN; idx <= CSI_PMU_COUNTER_HPM_MAX; idx++) {
        csi_pmu_hpmcounter_clear_overflow_flag(idx);
    }
}

#endif
