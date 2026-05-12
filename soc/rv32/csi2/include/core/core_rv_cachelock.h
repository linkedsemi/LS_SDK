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

#ifndef __CORE_RV_CACHELOCK_H__
#define __CORE_RV_CACHELOCK_H__

#include <limits.h>
#include "csi_rv_common.h"
#include "csi_rv_encoding.h"

#define XRPLCNTLST_lockDFail_Pos                    17UL                                        /*!< XRPLCNTLST: lockDFail Position */
#define XRPLCNTLST_lockDFail_Msk                    (0x1UL << XRPLCNTLST_lockDFail_Pos)         /*!< XRPLCNTLST: lockDFail Mask */

#define XRPLCNTLST_lockIFail_Pos                    16UL                                        /*!< XRPLCNTLST: lockIFail Position */
#define XRPLCNTLST_lockIFail_Msk                    (0x1UL << XRPLCNTLST_lockIFail_Pos)         /*!< XRPLCNTLST: lockIFail Mask */

#define XRPLCNTLST_unlockDAll_Pos                   7UL                                         /*!< XRPLCNTLST: unlockDAll Position */
#define XRPLCNTLST_unlockDAll_Msk                   (0x1UL << XRPLCNTLST_unlockDAll_Pos)        /*!< XRPLCNTLST: unlockDAll Mask */

#define XRPLCNTLST_unlockIAll_Pos                   6UL                                         /*!< XRPLCNTLST: unlockIAll Position */
#define XRPLCNTLST_unlockIAll_Msk                   (0x1UL << XRPLCNTLST_unlockIAll_Pos)        /*!< XRPLCNTLST: unlockIAll Mask */

#define XRPLCNTLST_rlsPriDAll_Pos                   5UL                                         /*!< XRPLCNTLST: rlsPriDAll Position */
#define XRPLCNTLST_rlsPriDAll_Msk                   (0x1UL << XRPLCNTLST_rlsPriDAll_Pos)        /*!< XRPLCNTLST: rlsPriDAll Mask */

#define XRPLCNTLST_rlsPriIAll_Pos                   4UL                                         /*!< XRPLCNTLST: rlsPriIAll Position */
#define XRPLCNTLST_rlsPriIAll_Msk                   (0x1UL << XRPLCNTLST_rlsPriIAll_Pos)        /*!< XRPLCNTLST: rlsPriIAll Mask */

#define XRPLCNTLST_slocken_Pos                      1UL                                         /*!< XRPLCNTLST: slocken Position */
#define XRPLCNTLST_slocken_Msk                      (0x1UL << XRPLCNTLST_slocken_Pos)           /*!< XRPLCNTLST: slocken Mask */

#define XRPLCNTLST_ulocken_Pos                      0UL                                         /*!< XRPLCNTLST: ulocken Position */
#define XRPLCNTLST_ulocken_Msk                      (0x1UL << XRPLCNTLST_ulocken_Pos)           /*!< XRPLCNTLST: ulocken Mask */


#define XCACHERPLPRI_priority_addr_Pos              5UL                                                 /*!< XCACHERPLPRI: priority_addr Position */
#define XCACHERPLPRI_priority_addr_Msk              (ULONG_MAX << XCACHERPLPRI_priority_addr_Pos)       /*!< XCACHERPLPRI: priority_addr Mask */

#define XCACHERPLPRI_cache_sel_Pos                  1UL                                                 /*!< XCACHERPLPRI: cache_sel Position */
#define XCACHERPLPRI_cache_sel_Msk                  (1UL << XCACHERPLPRI_cache_sel_Pos)                 /*!< XCACHERPLPRI: cache_sel Mask */

#define XCACHERPLPRI_priority_en_Pos                0UL                                                 /*!< XCACHERPLPRI: priority_en Position */
#define XCACHERPLPRI_priority_en_Msk                (1UL << XCACHERPLPRI_priority_en_Pos)               /*!< XCACHERPLPRI: priority_en Mask */


#define XCACHELOCK_cacheline_addr_Pos               6UL                                                 /*!< XCACHELOCK: cacheline_addr Position */
#define XCACHELOCK_cacheline_addr_Msk               (ULONG_MAX << XCACHELOCK_cacheline_addr_Pos)        /*!< XCACHELOCK: cacheline_addr Mask */

#define XCACHELOCK_cache_sel_Pos                    2UL                                                 /*!< XCACHELOCK: cache_sel Position */
#define XCACHELOCK_cache_sel_Msk                    (1UL << XCACHELOCK_cache_sel_Pos)                   /*!< XCACHELOCK: cache_sel Mask */

#define XCACHELOCK_command_Pos                      0UL                                                 /*!< XCACHELOCK: command Position */
#define XCACHELOCK_command_Msk                      (3UL << XCACHELOCK_command_Pos)                     /*!< XCACHELOCK: command Mask */


/**
  \brief        Get MRPLCNTLST
  \details      Returns the content of the MRPLCNTLST Register.
  \return       MRPLCNTLST Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MRPLCNTLST(void)
{
    return rv_csr_read(CSR_MRPLCNTLST);
}

/**
  \brief        Set MRPLCNTLST
  \details      Writes the given value to the MRPLCNTLST Register.
  \param [in]   mrplcntlst    MRPLCNTLST Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MRPLCNTLST(unsigned long mrplcntlst)
{
    rv_csr_write(CSR_MRPLCNTLST, mrplcntlst);
}

/**
  \brief        Get MCACHELOCK
  \details      Returns the content of the MCACHELOCK Register.
  \return       MCACHELOCK Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCACHELOCK(void)
{
    return rv_csr_read(CSR_MCACHELOCK);
}

/**
  \brief        Set MCACHELOCK
  \details      Writes the given value to the MCACHELOCK Register.
  \param [in]   mcachelock    MCACHELOCK Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCACHELOCK(unsigned long mcachelock)
{
    rv_csr_write(CSR_MCACHELOCK, mcachelock);
}

/**
  \brief        Get MCACHERPLPRI0
  \details      Returns the content of the MCACHERPLPRI0 Register.
  \return       MCACHERPLPRI0 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCACHERPLPRI0(void)
{
    return rv_csr_read(CSR_MCACHERPLPRI0);
}

/**
  \brief        Set MCACHERPLPRI0
  \details      Writes the given value to the MCACHERPLPRI0 Register.
  \param [in]   mcacherplpri0  MCACHERPLPRI0 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCACHERPLPRI0(unsigned long mcacherplpri0)
{
    rv_csr_write(CSR_MCACHERPLPRI0, mcacherplpri0);
}

/**
  \brief        Get MCACHERPLPRI1
  \details      Returns the content of the MCACHERPLPRI1 Register.
  \return       MCACHERPLPRI1 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCACHERPLPRI1(void)
{
    return rv_csr_read(CSR_MCACHERPLPRI1);
}

/**
  \brief        Set MCACHERPLPRI1
  \details      Writes the given value to the MCACHERPLPRI1 Register.
  \param [in]   mcacherplpri1  MCACHERPLPRI1 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCACHERPLPRI1(unsigned long mcacherplpri1)
{
    rv_csr_write(CSR_MCACHERPLPRI1, mcacherplpri1);
}

/**
  \brief        Get MCACHERPLPRI2
  \details      Returns the content of the MCACHERPLPRI2 Register.
  \return       MCACHERPLPRI2 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCACHERPLPRI2(void)
{
    return rv_csr_read(CSR_MCACHERPLPRI2);
}

/**
  \brief        Set MCACHERPLPRI2
  \details      Writes the given value to the MCACHERPLPRI2 Register.
  \param [in]   mcacherplpri2  MCACHERPLPRI2 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCACHERPLPRI2(unsigned long mcacherplpri2)
{
    rv_csr_write(CSR_MCACHERPLPRI2, mcacherplpri2);
}

/**
  \brief        Get MCACHERPLPRI3
  \details      Returns the content of the MCACHERPLPRI3 Register.
  \return       MCACHERPLPRI3 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCACHERPLPRI3(void)
{
    return rv_csr_read(CSR_MCACHERPLPRI3);
}

/**
  \brief        Set MCACHERPLPRI3
  \details      Writes the given value to the MCACHERPLPRI3 Register.
  \param [in]   mcacherplpri3  MCACHERPLPRI3 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCACHERPLPRI3(unsigned long mcacherplpri3)
{
    rv_csr_write(CSR_MCACHERPLPRI3, mcacherplpri3);
}

/**
  \brief        Get MCACHERPLPRI4
  \details      Returns the content of the MCACHERPLPRI4 Register.
  \return       MCACHERPLPRI4 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCACHERPLPRI4(void)
{
    return rv_csr_read(CSR_MCACHERPLPRI4);
}

/**
  \brief        Set MCACHERPLPRI4
  \details      Writes the given value to the MCACHERPLPRI4 Register.
  \param [in]   mcacherplpri4  MCACHERPLPRI4 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCACHERPLPRI4(unsigned long mcacherplpri4)
{
    rv_csr_write(CSR_MCACHERPLPRI4, mcacherplpri4);
}

/**
  \brief        Get MCACHERPLPRI5
  \details      Returns the content of the MCACHERPLPRI5 Register.
  \return       MCACHERPLPRI5 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCACHERPLPRI5(void)
{
    return rv_csr_read(CSR_MCACHERPLPRI5);
}

/**
  \brief        Set MCACHERPLPRI5
  \details      Writes the given value to the MCACHERPLPRI5 Register.
  \param [in]   mcacherplpri5  MCACHERPLPRI5 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCACHERPLPRI5(unsigned long mcacherplpri5)
{
    rv_csr_write(CSR_MCACHERPLPRI5, mcacherplpri5);
}

/**
  \brief        Get SRPLCNTLST
  \details      Returns the content of the SRPLCNTLST Register.
  \return       SRPLCNTLST Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SRPLCNTLST(void)
{
    return rv_csr_read(CSR_SRPLCNTLST);
}

/**
  \brief        Set SRPLCNTLST
  \details      Writes the given value to the SRPLCNTLST Register.
  \param [in]   srplcntlst  SRPLCNTLST Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SRPLCNTLST(unsigned long srplcntlst)
{
    rv_csr_write(CSR_SRPLCNTLST, srplcntlst);
}

/**
  \brief        Get SCACHELOCK
  \details      Returns the content of the SCACHELOCK Register.
  \return       SCACHELOCK Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCACHELOCK(void)
{
    return rv_csr_read(CSR_SCACHELOCK);
}

/**
  \brief        Set SCACHELOCK
  \details      Writes the given value to the SCACHELOCK Register.
  \param [in]   scachelock  SCACHELOCK Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SCACHELOCK(unsigned long scachelock)
{
    rv_csr_write(CSR_SCACHELOCK, scachelock);
}

/**
  \brief        Get SCACHERPLPRI0
  \details      Returns the content of the SCACHERPLPRI0 Register.
  \return       SCACHERPLPRI0 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCACHERPLPRI0(void)
{
    return rv_csr_read(CSR_SCACHERPLPRI0);
}

/**
  \brief        Set SCACHERPLPRI0
  \details      Writes the given value to the SCACHERPLPRI0 Register.
  \param [in]   scacherplpri0  SCACHERPLPRI0 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SCACHERPLPRI0(unsigned long scacherplpri0)
{
    rv_csr_write(CSR_SCACHERPLPRI0, scacherplpri0);
}

/**
  \brief        Get SCACHERPLPRI1
  \details      Returns the content of the SCACHERPLPRI1 Register.
  \return       SCACHERPLPRI1 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCACHERPLPRI1(void)
{
    return rv_csr_read(CSR_SCACHERPLPRI1);
}

/**
  \brief        Set SCACHERPLPRI1
  \details      Writes the given value to the SCACHERPLPRI1 Register.
  \param [in]   scacherplpri1  SCACHERPLPRI1 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SCACHERPLPRI1(unsigned long scacherplpri1)
{
    rv_csr_write(CSR_SCACHERPLPRI1, scacherplpri1);
}

/**
  \brief        Get SCACHERPLPRI2
  \details      Returns the content of the SCACHERPLPRI2 Register.
  \return       SCACHERPLPRI2 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCACHERPLPRI2(void)
{
    return rv_csr_read(CSR_SCACHERPLPRI2);
}

/**
  \brief        Set SCACHERPLPRI2
  \details      Writes the given value to the SCACHERPLPRI2 Register.
  \param [in]   scacherplpri2  SCACHERPLPRI2 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SCACHERPLPRI2(unsigned long scacherplpri2)
{
    rv_csr_write(CSR_SCACHERPLPRI2, scacherplpri2);
}

/**
  \brief        Get SCACHERPLPRI3
  \details      Returns the content of the SCACHERPLPRI3 Register.
  \return       SCACHERPLPRI3 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCACHERPLPRI3(void)
{
    return rv_csr_read(CSR_SCACHERPLPRI3);
}

/**
  \brief        Set SCACHERPLPRI3
  \details      Writes the given value to the SCACHERPLPRI3 Register.
  \param [in]   scacherplpri3  SCACHERPLPRI3 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SCACHERPLPRI3(unsigned long scacherplpri3)
{
    rv_csr_write(CSR_SCACHERPLPRI3, scacherplpri3);
}

/**
  \brief        Get SCACHERPLPRI4
  \details      Returns the content of the SCACHERPLPRI4 Register.
  \return       SCACHERPLPRI4 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCACHERPLPRI4(void)
{
    return rv_csr_read(CSR_SCACHERPLPRI4);
}

/**
  \brief        Set SCACHERPLPRI4
  \details      Writes the given value to the SCACHERPLPRI4 Register.
  \param [in]   scacherplpri4  SCACHERPLPRI4 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SCACHERPLPRI4(unsigned long scacherplpri4)
{
    rv_csr_write(CSR_SCACHERPLPRI4, scacherplpri4);
}

/**
  \brief        Get SCACHERPLPRI5
  \details      Returns the content of the SCACHERPLPRI5 Register.
  \return       SCACHERPLPRI5 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCACHERPLPRI5(void)
{
    return rv_csr_read(CSR_SCACHERPLPRI5);
}

/**
  \brief        Set SCACHERPLPRI5
  \details      Writes the given value to the SCACHERPLPRI5 Register.
  \param [in]   scacherplpri5  SCACHERPLPRI5 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SCACHERPLPRI5(unsigned long scacherplpri5)
{
    rv_csr_write(CSR_SCACHERPLPRI5, scacherplpri5);
}

/**
  \brief        Get URPLCNTLST
  \details      Returns the content of the URPLCNTLST Register.
  \return       URPLCNTLST Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_URPLCNTLST(void)
{
    return rv_csr_read(CSR_URPLCNTLST);
}

/**
  \brief        Set URPLCNTLST
  \details      Writes the given value to the URPLCNTLST Register.
  \param [in]   urplcntlst  URPLCNTLST Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_URPLCNTLST(unsigned long urplcntlst)
{
    rv_csr_write(CSR_URPLCNTLST, urplcntlst);
}

/**
  \brief        Get UCACHELOCK
  \details      Returns the content of the UCACHELOCK Register.
  \return       UCACHELOCK Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_UCACHELOCK(void)
{
    return rv_csr_read(CSR_UCACHELOCK);
}

/**
  \brief        Set UCACHELOCK
  \details      Writes the given value to the UCACHELOCK Register.
  \param [in]   ucachelock  UCACHELOCK Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_UCACHELOCK(unsigned long ucachelock)
{
    rv_csr_write(CSR_UCACHELOCK, ucachelock);
}

/**
  \brief        Get UCACHERPLPRI0
  \details      Returns the content of the UCACHERPLPRI0 Register.
  \return       UCACHERPLPRI0 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_UCACHERPLPRI0(void)
{
    return rv_csr_read(CSR_UCACHERPLPRI0);
}

/**
  \brief        Set UCACHERPLPRI0
  \details      Writes the given value to the UCACHERPLPRI0 Register.
  \param [in]   ucacherplpri0  UCACHERPLPRI0 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_UCACHERPLPRI0(unsigned long ucacherplpri0)
{
    rv_csr_write(CSR_UCACHERPLPRI0, ucacherplpri0);
}

/**
  \brief        Get UCACHERPLPRI1
  \details      Returns the content of the UCACHERPLPRI1 Register.
  \return       UCACHERPLPRI1 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_UCACHERPLPRI1(void)
{
    return rv_csr_read(CSR_UCACHERPLPRI1);
}

/**
  \brief        Set UCACHERPLPRI1
  \details      Writes the given value to the UCACHERPLPRI1 Register.
  \param [in]   ucacherplpri1  UCACHERPLPRI1 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_UCACHERPLPRI1(unsigned long ucacherplpri1)
{
    rv_csr_write(CSR_UCACHERPLPRI1, ucacherplpri1);
}

/**
  \brief        Get UCACHERPLPRI2
  \details      Returns the content of the UCACHERPLPRI2 Register.
  \return       UCACHERPLPRI2 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_UCACHERPLPRI2(void)
{
    return rv_csr_read(CSR_UCACHERPLPRI2);
}

/**
  \brief        Set UCACHERPLPRI2
  \details      Writes the given value to the UCACHERPLPRI2 Register.
  \param [in]   ucacherplpri2  UCACHERPLPRI2 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_UCACHERPLPRI2(unsigned long ucacherplpri2)
{
    rv_csr_write(CSR_UCACHERPLPRI2, ucacherplpri2);
}

/**
  \brief        Get UCACHERPLPRI3
  \details      Returns the content of the UCACHERPLPRI3 Register.
  \return       UCACHERPLPRI3 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_UCACHERPLPRI3(void)
{
    return rv_csr_read(CSR_UCACHERPLPRI3);
}

/**
  \brief        Set UCACHERPLPRI3
  \details      Writes the given value to the UCACHERPLPRI3 Register.
  \param [in]   ucacherplpri3  UCACHERPLPRI3 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_UCACHERPLPRI3(unsigned long ucacherplpri3)
{
    rv_csr_write(CSR_UCACHERPLPRI3, ucacherplpri3);
}

/**
  \brief        Get UCACHERPLPRI4
  \details      Returns the content of the UCACHERPLPRI4 Register.
  \return       UCACHERPLPRI4 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_UCACHERPLPRI4(void)
{
    return rv_csr_read(CSR_UCACHERPLPRI4);
}

/**
  \brief        Set UCACHERPLPRI4
  \details      Writes the given value to the UCACHERPLPRI4 Register.
  \param [in]   ucacherplpri4  UCACHERPLPRI4 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_UCACHERPLPRI4(unsigned long ucacherplpri4)
{
    rv_csr_write(CSR_UCACHERPLPRI4, ucacherplpri4);
}

/**
  \brief        Get UCACHERPLPRI5
  \details      Returns the content of the UCACHERPLPRI5 Register.
  \return       UCACHERPLPRI5 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_UCACHERPLPRI5(void)
{
    return rv_csr_read(CSR_UCACHERPLPRI5);
}

/**
  \brief        Set UCACHERPLPRI5
  \details      Writes the given value to the UCACHERPLPRI5 Register.
  \param [in]   ucacherplpri5  UCACHERPLPRI5 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_UCACHERPLPRI5(unsigned long ucacherplpri5)
{
    rv_csr_write(CSR_UCACHERPLPRI5, ucacherplpri5);
}

/**
  \brief        Configure DCache priority in machine mode
  \param [in]   index      DCache priority entry index (0 ~ 5)
  \param [in]   base_addr  The base address of DCache priority configuration, must be aligned with size
  \param [in]   size       The size of DCache priority, 64B ~ 32MB, must be power of 2
  \param [in]   enable     DCache priority enable, 0: disable, 1: enable
  \return                       0: success, -1: fail
 */
__STATIC_INLINE int csi_dcache_config_m_mode_priority(int index, unsigned long base_addr, uint32_t size, uint8_t enable)
{
    unsigned long priority_cfg;
    unsigned long priority_addr;

    if (size < 64 || size > 32 * 1024 * 1024) {
        return -1;
    }
    if (!is_power_of_two(size)) {
        return -1;
    }
    if (base_addr & (size -1)) {
        return -1;
    }

    uint32_t bits = log2_ulong(size);

    priority_addr = base_addr >> bits;
    priority_addr <<= (bits - 5);
    priority_addr |= ((size - 1) >> 6);

    priority_cfg = 0;
    priority_cfg |= priority_addr << XCACHERPLPRI_priority_addr_Pos;
    if (enable) {
        priority_cfg |= 1UL << XCACHERPLPRI_priority_en_Pos;
    }

    switch (index)
    {
    case 0:
        __set_MCACHERPLPRI0(priority_cfg);
        break;
    case 1:
        __set_MCACHERPLPRI1(priority_cfg);
        break;
    case 2:
        __set_MCACHERPLPRI2(priority_cfg);
        break;
    case 3:
        __set_MCACHERPLPRI3(priority_cfg);
        break;
    case 4:
        __set_MCACHERPLPRI4(priority_cfg);
        break;
    case 5:
        __set_MCACHERPLPRI5(priority_cfg);
        break;
    default:
        return -1;
    }

    return 0;
}

/**
  \brief        Configure DCache priority in supervisor mode
  \param [in]   index      DCache priority entry index (0 ~ 5)
  \param [in]   base_addr  The base address of DCache priority configuration, must be aligned with size
  \param [in]   size       The size of DCache priority, 64B ~ 32MB, must be power of 2
  \param [in]   enable     DCache priority enable, 0: disable, 1: enable
  \return                       0: success, -1: fail
 */
__STATIC_INLINE int csi_dcache_config_s_mode_priority(int index, unsigned long base_addr, uint32_t size, uint8_t enable)
{
    unsigned long priority_cfg;
    unsigned long priority_addr;

    if (size < 64 || size > 32 * 1024 * 1024) {
        return -1;
    }
    if (!is_power_of_two(size)) {
        return -1;
    }
    if (base_addr & (size -1)) {
        return -1;
    }

    uint32_t bits = log2_ulong(size);

    priority_addr = base_addr >> bits;
    priority_addr <<= (bits - 5);
    priority_addr |= ((size - 1) >> 6);

    priority_cfg = 0;
    priority_cfg |= priority_addr << XCACHERPLPRI_priority_addr_Pos;
    if (enable) {
        priority_cfg |= 1UL << XCACHERPLPRI_priority_en_Pos;
    }

    switch (index)
    {
    case 0:
        __set_SCACHERPLPRI0(priority_cfg);
        break;
    case 1:
        __set_SCACHERPLPRI1(priority_cfg);
        break;
    case 2:
        __set_SCACHERPLPRI2(priority_cfg);
        break;
    case 3:
        __set_SCACHERPLPRI3(priority_cfg);
        break;
    case 4:
        __set_SCACHERPLPRI4(priority_cfg);
        break;
    case 5:
        __set_SCACHERPLPRI5(priority_cfg);
        break;
    default:
        return -1;
    }

    return 0;
}

/**
  \brief        Configure DCache priority in user mode
  \param [in]   index      DCache priority entry index (0 ~ 5)
  \param [in]   base_addr  The base address of DCache priority configuration, must be aligned with size
  \param [in]   size       The size of DCache priority, 64B ~ 32MB, must be power of 2
  \param [in]   enable     DCache priority enable, 0: disable, 1: enable
  \return                       0: success, -1: fail
 */
__STATIC_INLINE int csi_dcache_config_u_mode_priority(int index, unsigned long base_addr, uint32_t size, uint8_t enable)
{
    unsigned long priority_cfg;
    unsigned long priority_addr;

    if (size < 64 || size > 32 * 1024 * 1024) {
        return -1;
    }
    if (!is_power_of_two(size)) {
        return -1;
    }
    if (base_addr & (size -1)) {
        return -1;
    }

    uint32_t bits = log2_ulong(size);

    priority_addr = base_addr >> bits;
    priority_addr <<= (bits - 5);
    priority_addr |= ((size - 1) >> 6);

    priority_cfg = 0;
    priority_cfg |= priority_addr << XCACHERPLPRI_priority_addr_Pos;
    if (enable) {
        priority_cfg |= 1UL << XCACHERPLPRI_priority_en_Pos;
    }

    switch (index)
    {
    case 0:
        __set_UCACHERPLPRI0(priority_cfg);
        break;
    case 1:
        __set_UCACHERPLPRI1(priority_cfg);
        break;
    case 2:
        __set_UCACHERPLPRI2(priority_cfg);
        break;
    case 3:
        __set_UCACHERPLPRI3(priority_cfg);
        break;
    case 4:
        __set_UCACHERPLPRI4(priority_cfg);
        break;
    case 5:
        __set_UCACHERPLPRI5(priority_cfg);
        break;
    default:
        return -1;
    }

    return 0;
}

/**
  \brief        Configure ICache priority in machine mode
  \param [in]   index      ICache priority entry index (0 ~ 5)
  \param [in]   base_addr  The base address of ICache priority configuration, must be aligned with size
  \param [in]   size       The size of ICache priority, 64B ~ 32MB, must be power of 2
  \param [in]   enable     ICache priority enable, 0: disable, 1: enable
  \return                       0: success, -1: fail
 */
__STATIC_INLINE int csi_icache_config_m_mode_priority(int index, unsigned long base_addr, uint32_t size, uint8_t enable)
{
    unsigned long priority_cfg;
    unsigned long priority_addr;

    if (size < 64 || size > 32 * 1024 * 1024) {
        return -1;
    }
    if (!is_power_of_two(size)) {
        return -1;
    }
    if (base_addr & (size -1)) {
        return -1;
    }

    uint32_t bits = log2_ulong(size);

    priority_addr = base_addr >> bits;
    priority_addr <<= (bits - 5);
    priority_addr |= ((size - 1) >> 6);

    priority_cfg = 0;
    priority_cfg |= priority_addr << XCACHERPLPRI_priority_addr_Pos;
    priority_cfg |= 1UL << XCACHERPLPRI_cache_sel_Pos;
    if (enable) {
        priority_cfg |= 1UL << XCACHERPLPRI_priority_en_Pos;
    }

    switch (index)
    {
    case 0:
        __set_MCACHERPLPRI0(priority_cfg);
        break;
    case 1:
        __set_MCACHERPLPRI1(priority_cfg);
        break;
    case 2:
        __set_MCACHERPLPRI2(priority_cfg);
        break;
    case 3:
        __set_MCACHERPLPRI3(priority_cfg);
        break;
    case 4:
        __set_MCACHERPLPRI4(priority_cfg);
        break;
    case 5:
        __set_MCACHERPLPRI5(priority_cfg);
        break;
    default:
        return -1;
    }

    return 0;
}

/**
  \brief        Configure ICache priority in supervisor mode
  \param [in]   index      ICache priority entry index (0 ~ 5)
  \param [in]   base_addr  The base address of ICache priority configuration, must be aligned with size
  \param [in]   size       The size of ICache priority, 64B ~ 32MB, must be power of 2
  \param [in]   enable     ICache priority enable, 0: disable, 1: enable
  \return                       0: success, -1: fail
 */
__STATIC_INLINE int csi_icache_config_s_mode_priority(int index, unsigned long base_addr, uint32_t size, uint8_t enable)
{
    unsigned long priority_cfg;
    unsigned long priority_addr;

    if (size < 64 || size > 32 * 1024 * 1024) {
        return -1;
    }
    if (!is_power_of_two(size)) {
        return -1;
    }
    if (base_addr & (size -1)) {
        return -1;
    }

    uint32_t bits = log2_ulong(size);

    priority_addr = base_addr >> bits;
    priority_addr <<= (bits - 5);
    priority_addr |= ((size - 1) >> 6);

    priority_cfg = 0;
    priority_cfg |= priority_addr << XCACHERPLPRI_priority_addr_Pos;
    priority_cfg |= 1UL << XCACHERPLPRI_cache_sel_Pos;
    if (enable) {
        priority_cfg |= 1UL << XCACHERPLPRI_priority_en_Pos;
    }

    switch (index)
    {
    case 0:
        __set_SCACHERPLPRI0(priority_cfg);
        break;
    case 1:
        __set_SCACHERPLPRI1(priority_cfg);
        break;
    case 2:
        __set_SCACHERPLPRI2(priority_cfg);
        break;
    case 3:
        __set_SCACHERPLPRI3(priority_cfg);
        break;
    case 4:
        __set_SCACHERPLPRI4(priority_cfg);
        break;
    case 5:
        __set_SCACHERPLPRI5(priority_cfg);
        break;
    default:
        return -1;
    }

    return 0;
}

/**
  \brief        Configure ICache priority in user mode
  \param [in]   index      ICache priority entry index (0 ~ 5)
  \param [in]   base_addr  The base address of ICache priority configuration, must be aligned with size
  \param [in]   size       The size of ICache priority, 64B ~ 32MB, must be power of 2
  \param [in]   enable     ICache priority enable, 0: disable, 1: enable
  \return                       0: success, -1: fail
 */
__STATIC_INLINE int csi_icache_config_u_mode_priority(int index, unsigned long base_addr, uint32_t size, uint8_t enable)
{
    unsigned long priority_cfg;
    unsigned long priority_addr;

    if (size < 64 || size > 32 * 1024 * 1024) {
        return -1;
    }
    if (!is_power_of_two(size)) {
        return -1;
    }
    if (base_addr & (size -1)) {
        return -1;
    }

    uint32_t bits = log2_ulong(size);

    priority_addr = base_addr >> bits;
    priority_addr <<= (bits - 5);
    priority_addr |= ((size - 1) >> 6);

    priority_cfg = 0;
    priority_cfg |= priority_addr << XCACHERPLPRI_priority_addr_Pos;
    priority_cfg |= 1UL << XCACHERPLPRI_cache_sel_Pos;
    if (enable) {
        priority_cfg |= 1UL << XCACHERPLPRI_priority_en_Pos;
    }

    switch (index)
    {
    case 0:
        __set_UCACHERPLPRI0(priority_cfg);
        break;
    case 1:
        __set_UCACHERPLPRI1(priority_cfg);
        break;
    case 2:
        __set_UCACHERPLPRI2(priority_cfg);
        break;
    case 3:
        __set_UCACHERPLPRI3(priority_cfg);
        break;
    case 4:
        __set_UCACHERPLPRI4(priority_cfg);
        break;
    case 5:
        __set_UCACHERPLPRI5(priority_cfg);
        break;
    default:
        return -1;
    }

    return 0;
}

/**
  \brief        Configure DCache lock for a cacheline in machine mode
  \param [in]   base_addr  The base address of DCache lock configuration
  \param [in]   enable     DCache lock enable, 0: disable, 1: enable
 */
__STATIC_INLINE void csi_dcache_config_m_mode_lock(unsigned long base_addr, uint8_t enable)
{
    unsigned long cachelock_cfg;

    cachelock_cfg = 0;
    cachelock_cfg |= (base_addr & XCACHELOCK_cacheline_addr_Msk);
    if (enable) {
        cachelock_cfg |= 1UL << XCACHELOCK_command_Pos;
    } else {
        cachelock_cfg &= ~XCACHELOCK_command_Msk;
        cachelock_cfg |= 2UL << XCACHELOCK_command_Pos;
    }
    __set_MCACHELOCK(cachelock_cfg);
}

/**
  \brief        Configure DCache lock for a cacheline in supervisor mode
  \param [in]   base_addr  The base address of DCache lock configuration
  \param [in]   enable     DCache lock enable, 0: disable, 1: enable
 */
__STATIC_INLINE void csi_dcache_config_s_mode_lock(unsigned long base_addr, uint8_t enable)
{
    unsigned long cachelock_cfg;

    cachelock_cfg = 0;
    cachelock_cfg |= (base_addr & XCACHELOCK_cacheline_addr_Msk);
    if (enable) {
        cachelock_cfg |= 1UL << XCACHELOCK_command_Pos;
    } else {
        cachelock_cfg &= ~XCACHELOCK_command_Msk;
        cachelock_cfg |= 2UL << XCACHELOCK_command_Pos;
    }
    __set_SCACHELOCK(cachelock_cfg);
}

/**
  \brief        Configure DCache lock for a cacheline in user mode
  \param [in]   base_addr  The base address of DCache lock configuration
  \param [in]   enable     DCache lock enable, 0: disable, 1: enable
 */
__STATIC_INLINE void csi_dcache_config_u_mode_lock(unsigned long base_addr, uint8_t enable)
{
    unsigned long cachelock_cfg;

    cachelock_cfg = 0;
    cachelock_cfg |= (base_addr & XCACHELOCK_cacheline_addr_Msk);
    if (enable) {
        cachelock_cfg |= 1UL << XCACHELOCK_command_Pos;
    } else {
        cachelock_cfg &= ~XCACHELOCK_command_Msk;
        cachelock_cfg |= 2UL << XCACHELOCK_command_Pos;
    }
    __set_UCACHELOCK(cachelock_cfg);
}

/**
  \brief        Configure ICache lock for a cacheline in machine mode
  \param [in]   base_addr  The base address of ICache lock configuration
  \param [in]   enable     ICache lock enable, 0: disable, 1: enable
 */
__STATIC_INLINE void csi_icache_config_m_mode_lock(unsigned long base_addr, uint8_t enable)
{
    unsigned long cachelock_cfg;

    cachelock_cfg = 0;
    cachelock_cfg |= (base_addr & XCACHELOCK_cacheline_addr_Msk);
    cachelock_cfg |= 1UL << XCACHELOCK_cache_sel_Pos;
    if (enable) {
        cachelock_cfg |= 1UL << XCACHELOCK_command_Pos;
    } else {
        cachelock_cfg &= ~XCACHELOCK_command_Msk;
        cachelock_cfg |= 2UL << XCACHELOCK_command_Pos;
    }
    __set_MCACHELOCK(cachelock_cfg);
}

/**
  \brief        Configure ICache lock for a cacheline in supervisor mode
  \param [in]   base_addr  The base address of ICache lock configuration
  \param [in]   enable     ICache lock enable, 0: disable, 1: enable
 */
__STATIC_INLINE void csi_icache_config_s_mode_lock(unsigned long base_addr, uint8_t enable)
{
    unsigned long cachelock_cfg;

    cachelock_cfg = 0;
    cachelock_cfg |= (base_addr & XCACHELOCK_cacheline_addr_Msk);
    cachelock_cfg |= 1UL << XCACHELOCK_cache_sel_Pos;
    if (enable) {
        cachelock_cfg |= 1UL << XCACHELOCK_command_Pos;
    } else {
        cachelock_cfg &= ~XCACHELOCK_command_Msk;
        cachelock_cfg |= 2UL << XCACHELOCK_command_Pos;
    }
    __set_SCACHELOCK(cachelock_cfg);
}

/**
  \brief        Configure ICache lock for a cacheline in user mode
  \param [in]   base_addr  The base address of ICache lock configuration
  \param [in]   enable     ICache lock enable, 0: disable, 1: enable
 */
__STATIC_INLINE void csi_icache_config_u_mode_lock(unsigned long base_addr, uint8_t enable)
{
    unsigned long cachelock_cfg;

    cachelock_cfg = 0;
    cachelock_cfg |= (base_addr & XCACHELOCK_cacheline_addr_Msk);
    cachelock_cfg |= 1UL << XCACHELOCK_cache_sel_Pos;
    if (enable) {
        cachelock_cfg |= 1UL << XCACHELOCK_command_Pos;
    } else {
        cachelock_cfg &= ~XCACHELOCK_command_Msk;
        cachelock_cfg |= 2UL << XCACHELOCK_command_Pos;
    }
    __set_UCACHELOCK(cachelock_cfg);
}

#endif
