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

#ifndef __CORE_RV_ATOMIC_H__
#define __CORE_RV_ATOMIC_H__

#include "csi_rv_common.h"

/**
  \brief        Atomically load a value from memory with acquire semantics
  \param [in]   ptr     Pointer to the memory location to load from
  \return               The value loaded from the memory location
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_load(volatile unsigned long *ptr)
{
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile ("amoor.w.aq %0, x0, (%1)" : "=r"(result) : "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoor.d.aq %0, x0, (%1)" : "=r"(result) : "r"(ptr) : "memory");
#endif
    return result;
}

/**
  \brief        Atomically store a value to memory with release semantics
  \param [in]   ptr     Pointer to the memory location to store to
  \param [in]   val     Value to store into the memory location
 */
__ALWAYS_STATIC_INLINE void csi_atomic_store(volatile unsigned long *ptr, unsigned long val)
{
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile ("amoswap.w.rl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoswap.d.rl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#endif
}

/**
  \brief        Atomically add a value to a memory location and return the previous value
  \param [in]   ptr     Pointer to the memory location to add to
  \param [in]   val     Value to add
  \return               The value of the memory location before the operation
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_add(volatile unsigned long *ptr, unsigned long val)
{
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile ("amoadd.w.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoadd.d.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#endif
    return result;
}

/**
  \brief        Atomically subtract a value from a memory location and return the previous value
  \param [in]   ptr     Pointer to the memory location to subtract from
  \param [in]   val     Value to subtract
  \return               The value of the memory location before the operation
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_sub(volatile unsigned long *ptr, unsigned long val)
{
    unsigned long result = 0;
    val = -val;
#if __riscv_xlen == 32
    asm volatile ("amoadd.w.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoadd.d.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#endif
    return result;
}

/**
  \brief        Atomically perform a bitwise AND operation and return the previous value
  \param [in]   ptr     Pointer to the memory location for the AND operation
  \param [in]   val     Value to AND with the memory location
  \return               The value of the memory location before the operation
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_and(volatile unsigned long *ptr, unsigned long val)
{
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile ("amoand.w.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoand.d.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#endif
    return result;
}

/**
  \brief        Atomically perform a bitwise OR operation and return the previous value
  \param [in]   ptr     Pointer to the memory location for the OR operation
  \param [in]   val     Value to OR with the memory location
  \return               The value of the memory location before the operation
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_or(volatile unsigned long *ptr, unsigned long val)
{
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile ("amoor.w.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoor.d.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#endif
    return result;
}

/**
  \brief        Atomically perform a bitwise XOR operation and return the previous value
  \param [in]   ptr     Pointer to the memory location for the XOR operation
  \param [in]   val     Value to XOR with the memory location
  \return               The value of the memory location before the operation
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_xor(volatile unsigned long *ptr, unsigned long val)
{
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile ("amoxor.w.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoxor.d.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#endif
    return result;
}

/**
  \brief        Atomically exchange a value with a memory location and return the previous value
  \param [in]   ptr     Pointer to the memory location to exchange with
  \param [in]   val     Value to store into the memory location
  \return               The value of the memory location before the exchange
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_exchange(volatile unsigned long *ptr, unsigned long val)
{
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile ("amoswap.w.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoswap.d.aqrl %0, %1, (%2)" : "=r"(result) : "r"(val), "r"(ptr) : "memory");
#endif
    return result;
}

/**
  \brief        Atomically clear a flag (set to 0)
  \param [in]   ptr     Pointer to the flag to clear
 */
__ALWAYS_STATIC_INLINE void csi_atomic_flag_clear(volatile unsigned long *ptr)
{
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile ("amoand.w.rl %0, x0, (%1)" : "=r"(result) : "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoand.d.rl %0, x0, (%1)" : "=r"(result) : "r"(ptr) : "memory");
#endif
}

/**
  \brief        Atomically test if a flag is set and set it if it's not
  \param [in]   ptr     Pointer to the flag to test and set
  \return               1 if the flag was already set, 0 if it was successfully set by this operation
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_flag_test_and_set(volatile unsigned long *ptr)
{
    unsigned long result = 0;
    unsigned long temp = 1;
#if __riscv_xlen == 32
    asm volatile ("amoor.w.aqrl %0, %1, (%2)" : "=r"(result) : "r"(temp), "r"(ptr) : "memory");
#elif __riscv_xlen == 64
    asm volatile ("amoor.d.aqrl %0, %1, (%2)" : "=r"(result) : "r"(temp), "r"(ptr) : "memory");
#endif
    return result;
}

/**
  \brief        Atomically compare and exchange values if they match the expected value
  \param [in]      ptr        Pointer to the memory location to compare and exchange
  \param [in,out]  expected   Pointer to the expected value; updated with actual value if comparison fails
  \param [in]      desired    Value to store if the comparison succeeds
  \return                     1 if the exchange was performed, 0 if the exchange failed
 */
__ALWAYS_STATIC_INLINE unsigned long csi_atomic_compare_exchange_strong(volatile unsigned long *ptr, volatile unsigned long *expected, unsigned long desired)
{
    unsigned long tmp = *expected;
    unsigned long result = 0;
#if __riscv_xlen == 32
    asm volatile(
            " fence iorw, ow\n"
            "1: lr.w.aq  %[result], (%[ptr])\n"
            "   bne      %[result], %[tmp], 2f\n"
            "   sc.w.rl  %[tmp], %[desired], (%[ptr])\n"
            "   bnez     %[tmp], 1b\n"
            "   li       %[result], 1\n"
            "   j        3f\n"
            "2: sw       %[result], (%[expected])\n"
            "   li       %[result], 0\n"
            "3:\n"
            : [result]"+r" (result), [tmp]"+r" (tmp), [ptr]"+r" (ptr)
            : [desired]"r" (desired), [expected]"r"(expected)
            : "memory");
#elif __riscv_xlen == 64
    asm volatile(
            " fence iorw, ow\n"
            "1: lr.d.aq  %[result], (%[ptr])\n"
            "   bne      %[result], %[tmp], 2f\n"
            "   sc.d.rl  %[tmp], %[desired], (%[ptr])\n"
            "   bnez     %[tmp], 1b\n"
            "   li       %[result], 1\n"
            "   j        3f\n"
            "2: sd       %[result], (%[expected])\n"
            "   li       %[result], 0\n"
            "3:\n"
            : [result]"+r" (result), [tmp]"+r" (tmp), [ptr]"+r" (ptr)
            : [desired]"r" (desired), [expected]"r"(expected)
            : "memory");
#endif
    return result;
}


#endif
