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

#ifndef __CORE_RV_SPMP_H__
#define __CORE_RV_SPMP_H__

#include <stdint.h>
#include <limits.h>
#include "csi_rv_common.h"
#include "csi_rv_encoding.h"

#define SPMP_SPEC_VERSION_100_RC4 1
#if SPMP_SPEC_VERSION_100_RC4

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_SPMP S-level Physical Memory Protection (SPMP)
  \brief      Type definitions for the SPMP Registers
  @{
 */

#define SPMP_PMPCFG_R_Pos                       0UL                                   /*!< SPMP SPMPCFG: R Position */
#define SPMP_PMPCFG_R_Msk                       (0x1UL << SPMP_PMPCFG_R_Pos)          /*!< SPMP SPMPCFG: R Mask */

#define SPMP_PMPCFG_W_Pos                       1UL                                   /*!< SPMP SPMPCFG: W Position */
#define SPMP_PMPCFG_W_Msk                       (0x1UL << SPMP_PMPCFG_W_Pos)          /*!< SPMP SPMPCFG: W Mask */

#define SPMP_PMPCFG_X_Pos                       2UL                                   /*!< SPMP SPMPCFG: X Position */
#define SPMP_PMPCFG_X_Msk                       (0x1UL << SPMP_PMPCFG_X_Pos)          /*!< SPMP SPMPCFG: X Mask */

#define SPMP_PMPCFG_A_Pos                       3UL                                   /*!< SPMP SPMPCFG: A Position */
#define SPMP_PMPCFG_A_Msk                       (0x3UL << SPMP_PMPCFG_A_Pos)          /*!< SPMP SPMPCFG: A Mask */

#define SPMP_PMPCFG_L_Pos                       7UL                                   /*!< SPMP SPMPCFG: L Position */
#define SPMP_PMPCFG_L_Msk                       (0x1UL << SPMP_PMPCFG_L_Pos)          /*!< SPMP SPMPCFG: L Mask */

#define SPMP_PMPCFG_U_Pos                       8UL                                   /*!< SPMP SPMPCFG: U Position */
#define SPMP_PMPCFG_U_Msk                       (0x1UL << SPMP_PMPCFG_U_Pos)          /*!< SPMP SPMPCFG: U Mask */

#define SPMP_PMPCFG_SHARED_Pos                  9UL                                   /*!< SPMP SPMPCFG: SHARED Position */
#define SPMP_PMPCFG_SHARED_Msk                  (0x1UL << SPMP_PMPCFG_SHARED_Pos)     /*!< SPMP SPMPCFG: SHARED Mask */

typedef struct {
    uint32_t r: 1;           /* readable enable */
    uint32_t w: 1;           /* writeable enable */
    uint32_t x: 1;           /* execable enable */
    address_matching_e a: 2; /* address matching mode */
    uint32_t reserved: 2;    /* reserved */
    uint32_t l: 1;           /* lock enable */
    uint32_t u: 1;           /* determines if it is U-mode-only (when set) or S-mode-only (when clear) */
    uint32_t shared: 1;      /* identifies a rule as a Shared-Region rule */
    uint32_t reserved2: 6;   /* reserved */
} spmp_region_attr_t;

#if CONFIG_RISCV_SMODE
#define __set_xISELECT(val)     __set_SISELECT(val)
#define __set_xIREG(val)        __set_SIREG(val)
#define __set_xIREG2(val)       __set_SIREG2(val)
#define __get_xIREG()           __get_SIREG()
#define __get_xIREG2()          __get_SIREG2()
#else
#define __set_xISELECT(val)     __set_MISELECT(val)
#define __set_xIREG(val)        __set_MIREG(val)
#define __set_xIREG2(val)       __set_MIREG2(val)
#define __get_xIREG()           __get_MIREG()
#define __get_xIREG2()          __get_MIREG2()
#endif

/**
  \brief        Get SPMPCFGx Register
  \details      Returns the content of the SPMPCFGx Register.
  \return       SPMPCFGx Register value
 */
#define DECLARE_SPMPCFG_GETTER(n) \
__ALWAYS_STATIC_INLINE unsigned long __get_SPMPCFG##n(void) \
{ \
    unsigned long result; \
    __set_xISELECT(SPMP_MMIO_SPMPADDR##n##_SPMPCFG##n); \
    result = __get_xIREG2(); \
    return result; \
}
DECLARE_SPMPCFG_GETTER(0)
DECLARE_SPMPCFG_GETTER(1)
DECLARE_SPMPCFG_GETTER(2)
DECLARE_SPMPCFG_GETTER(3)
DECLARE_SPMPCFG_GETTER(4)
DECLARE_SPMPCFG_GETTER(5)
DECLARE_SPMPCFG_GETTER(6)
DECLARE_SPMPCFG_GETTER(7)
DECLARE_SPMPCFG_GETTER(8)
DECLARE_SPMPCFG_GETTER(9)
DECLARE_SPMPCFG_GETTER(10)
DECLARE_SPMPCFG_GETTER(11)
DECLARE_SPMPCFG_GETTER(12)
DECLARE_SPMPCFG_GETTER(13)
DECLARE_SPMPCFG_GETTER(14)
DECLARE_SPMPCFG_GETTER(15)
DECLARE_SPMPCFG_GETTER(16)
DECLARE_SPMPCFG_GETTER(17)
DECLARE_SPMPCFG_GETTER(18)
DECLARE_SPMPCFG_GETTER(19)
DECLARE_SPMPCFG_GETTER(20)
DECLARE_SPMPCFG_GETTER(21)
DECLARE_SPMPCFG_GETTER(22)
DECLARE_SPMPCFG_GETTER(23)
DECLARE_SPMPCFG_GETTER(24)
DECLARE_SPMPCFG_GETTER(25)
DECLARE_SPMPCFG_GETTER(26)
DECLARE_SPMPCFG_GETTER(27)
DECLARE_SPMPCFG_GETTER(28)
DECLARE_SPMPCFG_GETTER(29)
DECLARE_SPMPCFG_GETTER(30)
DECLARE_SPMPCFG_GETTER(31)
DECLARE_SPMPCFG_GETTER(32)
DECLARE_SPMPCFG_GETTER(33)
DECLARE_SPMPCFG_GETTER(34)
DECLARE_SPMPCFG_GETTER(35)
DECLARE_SPMPCFG_GETTER(36)
DECLARE_SPMPCFG_GETTER(37)
DECLARE_SPMPCFG_GETTER(38)
DECLARE_SPMPCFG_GETTER(39)
DECLARE_SPMPCFG_GETTER(40)
DECLARE_SPMPCFG_GETTER(41)
DECLARE_SPMPCFG_GETTER(42)
DECLARE_SPMPCFG_GETTER(43)
DECLARE_SPMPCFG_GETTER(44)
DECLARE_SPMPCFG_GETTER(45)
DECLARE_SPMPCFG_GETTER(46)
DECLARE_SPMPCFG_GETTER(47)
DECLARE_SPMPCFG_GETTER(48)
DECLARE_SPMPCFG_GETTER(49)
DECLARE_SPMPCFG_GETTER(50)
DECLARE_SPMPCFG_GETTER(51)
DECLARE_SPMPCFG_GETTER(52)
DECLARE_SPMPCFG_GETTER(53)
DECLARE_SPMPCFG_GETTER(54)
DECLARE_SPMPCFG_GETTER(55)
DECLARE_SPMPCFG_GETTER(56)
DECLARE_SPMPCFG_GETTER(57)
DECLARE_SPMPCFG_GETTER(58)
DECLARE_SPMPCFG_GETTER(59)
DECLARE_SPMPCFG_GETTER(60)
DECLARE_SPMPCFG_GETTER(61)
DECLARE_SPMPCFG_GETTER(62)
DECLARE_SPMPCFG_GETTER(63)

/**
  \brief        Get SPMPxCFG Register by index
  \details      Returns the content of the SPMPxCFG Register.
  \param [in]   idx         SPMP region index
  \return                   SPMPxCFG Register value
 */
__STATIC_INLINE unsigned long __get_SPMPxCFG(unsigned long idx)
{
    unsigned long spmpcfgx = 0;

    switch (idx) {
        case 0:
            spmpcfgx = __get_SPMPCFG0();
            break;
        case 1:
            spmpcfgx = __get_SPMPCFG1();
            break;
        case 2:
            spmpcfgx = __get_SPMPCFG2();
            break;
        case 3:
            spmpcfgx = __get_SPMPCFG3();
            break;
        case 4:
            spmpcfgx = __get_SPMPCFG4();
            break;
        case 5:
            spmpcfgx = __get_SPMPCFG5();
            break;
        case 6:
            spmpcfgx = __get_SPMPCFG6();
            break;
        case 7:
            spmpcfgx = __get_SPMPCFG7();
            break;
        case 8:
            spmpcfgx = __get_SPMPCFG8();
            break;
        case 9:
            spmpcfgx = __get_SPMPCFG9();
            break;
        case 10:
            spmpcfgx = __get_SPMPCFG10();
            break;
        case 11:
            spmpcfgx = __get_SPMPCFG11();
            break;
        case 12:
            spmpcfgx = __get_SPMPCFG12();
            break;
        case 13:
            spmpcfgx = __get_SPMPCFG13();
            break;
        case 14:
            spmpcfgx = __get_SPMPCFG14();
            break;
        case 15:
            spmpcfgx = __get_SPMPCFG15();
            break;
        case 16:
            spmpcfgx = __get_SPMPCFG16();
            break;
        case 17:
            spmpcfgx = __get_SPMPCFG17();
            break;
        case 18:
            spmpcfgx = __get_SPMPCFG18();
            break;
        case 19:
            spmpcfgx = __get_SPMPCFG19();
            break;
        case 20:
            spmpcfgx = __get_SPMPCFG20();
            break;
        case 21:
            spmpcfgx = __get_SPMPCFG21();
            break;
        case 22:
            spmpcfgx = __get_SPMPCFG22();
            break;
        case 23:
            spmpcfgx = __get_SPMPCFG23();
            break;
        case 24:
            spmpcfgx = __get_SPMPCFG24();
            break;
        case 25:
            spmpcfgx = __get_SPMPCFG25();
            break;
        case 26:
            spmpcfgx = __get_SPMPCFG26();
            break;
        case 27:
            spmpcfgx = __get_SPMPCFG27();
            break;
        case 28:
            spmpcfgx = __get_SPMPCFG28();
            break;
        case 29:
            spmpcfgx = __get_SPMPCFG29();
            break;
        case 30:
            spmpcfgx = __get_SPMPCFG30();
            break;
        case 31:
            spmpcfgx = __get_SPMPCFG31();
            break;
        case 32:
            spmpcfgx = __get_SPMPCFG32();
            break;
        case 33:
            spmpcfgx = __get_SPMPCFG33();
            break;
        case 34:
            spmpcfgx = __get_SPMPCFG34();
            break;
        case 35:
            spmpcfgx = __get_SPMPCFG35();
            break;
        case 36:
            spmpcfgx = __get_SPMPCFG36();
            break;
        case 37:
            spmpcfgx = __get_SPMPCFG37();
            break;
        case 38:
            spmpcfgx = __get_SPMPCFG38();
            break;
        case 39:
            spmpcfgx = __get_SPMPCFG39();
            break;
        case 40:
            spmpcfgx = __get_SPMPCFG40();
            break;
        case 41:
            spmpcfgx = __get_SPMPCFG41();
            break;
        case 42:
            spmpcfgx = __get_SPMPCFG42();
            break;
        case 43:
            spmpcfgx = __get_SPMPCFG43();
            break;
        case 44:
            spmpcfgx = __get_SPMPCFG44();
            break;
        case 45:
            spmpcfgx = __get_SPMPCFG45();
            break;
        case 46:
            spmpcfgx = __get_SPMPCFG46();
            break;
        case 47:
            spmpcfgx = __get_SPMPCFG47();
            break;
        case 48:
            spmpcfgx = __get_SPMPCFG48();
            break;
        case 49:
            spmpcfgx = __get_SPMPCFG49();
            break;
        case 50:
            spmpcfgx = __get_SPMPCFG50();
            break;
        case 51:
            spmpcfgx = __get_SPMPCFG51();
            break;
        case 52:
            spmpcfgx = __get_SPMPCFG52();
            break;
        case 53:
            spmpcfgx = __get_SPMPCFG53();
            break;
        case 54:
            spmpcfgx = __get_SPMPCFG54();
            break;
        case 55:
            spmpcfgx = __get_SPMPCFG55();
            break;
        case 56:
            spmpcfgx = __get_SPMPCFG56();
            break;
        case 57:
            spmpcfgx = __get_SPMPCFG57();
            break;
        case 58:
            spmpcfgx = __get_SPMPCFG58();
            break;
        case 59:
            spmpcfgx = __get_SPMPCFG59();
            break;
        case 60:
            spmpcfgx = __get_SPMPCFG60();
            break;
        case 61:
            spmpcfgx = __get_SPMPCFG61();
            break;
        case 62:
            spmpcfgx = __get_SPMPCFG62();
            break;
        case 63:
            spmpcfgx = __get_SPMPCFG63();
            break;
        default:
            break;
    }
    return spmpcfgx;
}

/**
  \brief        Set SPMPCFGx
  \details      Writes the given value to the SPMPCFGx Register.
  \param [in]   spmpcfg     SPMPCFGx Register value to set
 */
#define DECLARE_SPMPCFG_SETTER(n) \
__ALWAYS_STATIC_INLINE void __set_SPMPCFG##n(unsigned long spmpcfg) \
{ \
    __set_xISELECT(SPMP_MMIO_SPMPADDR##n##_SPMPCFG##n); \
    __set_xIREG2(spmpcfg); \
}
DECLARE_SPMPCFG_SETTER(0)
DECLARE_SPMPCFG_SETTER(1)
DECLARE_SPMPCFG_SETTER(2)
DECLARE_SPMPCFG_SETTER(3)
DECLARE_SPMPCFG_SETTER(4)
DECLARE_SPMPCFG_SETTER(5)
DECLARE_SPMPCFG_SETTER(6)
DECLARE_SPMPCFG_SETTER(7)
DECLARE_SPMPCFG_SETTER(8)
DECLARE_SPMPCFG_SETTER(9)
DECLARE_SPMPCFG_SETTER(10)
DECLARE_SPMPCFG_SETTER(11)
DECLARE_SPMPCFG_SETTER(12)
DECLARE_SPMPCFG_SETTER(13)
DECLARE_SPMPCFG_SETTER(14)
DECLARE_SPMPCFG_SETTER(15)
DECLARE_SPMPCFG_SETTER(16)
DECLARE_SPMPCFG_SETTER(17)
DECLARE_SPMPCFG_SETTER(18)
DECLARE_SPMPCFG_SETTER(19)
DECLARE_SPMPCFG_SETTER(20)
DECLARE_SPMPCFG_SETTER(21)
DECLARE_SPMPCFG_SETTER(22)
DECLARE_SPMPCFG_SETTER(23)
DECLARE_SPMPCFG_SETTER(24)
DECLARE_SPMPCFG_SETTER(25)
DECLARE_SPMPCFG_SETTER(26)
DECLARE_SPMPCFG_SETTER(27)
DECLARE_SPMPCFG_SETTER(28)
DECLARE_SPMPCFG_SETTER(29)
DECLARE_SPMPCFG_SETTER(30)
DECLARE_SPMPCFG_SETTER(31)
DECLARE_SPMPCFG_SETTER(32)
DECLARE_SPMPCFG_SETTER(33)
DECLARE_SPMPCFG_SETTER(34)
DECLARE_SPMPCFG_SETTER(35)
DECLARE_SPMPCFG_SETTER(36)
DECLARE_SPMPCFG_SETTER(37)
DECLARE_SPMPCFG_SETTER(38)
DECLARE_SPMPCFG_SETTER(39)
DECLARE_SPMPCFG_SETTER(40)
DECLARE_SPMPCFG_SETTER(41)
DECLARE_SPMPCFG_SETTER(42)
DECLARE_SPMPCFG_SETTER(43)
DECLARE_SPMPCFG_SETTER(44)
DECLARE_SPMPCFG_SETTER(45)
DECLARE_SPMPCFG_SETTER(46)
DECLARE_SPMPCFG_SETTER(47)
DECLARE_SPMPCFG_SETTER(48)
DECLARE_SPMPCFG_SETTER(49)
DECLARE_SPMPCFG_SETTER(50)
DECLARE_SPMPCFG_SETTER(51)
DECLARE_SPMPCFG_SETTER(52)
DECLARE_SPMPCFG_SETTER(53)
DECLARE_SPMPCFG_SETTER(54)
DECLARE_SPMPCFG_SETTER(55)
DECLARE_SPMPCFG_SETTER(56)
DECLARE_SPMPCFG_SETTER(57)
DECLARE_SPMPCFG_SETTER(58)
DECLARE_SPMPCFG_SETTER(59)
DECLARE_SPMPCFG_SETTER(60)
DECLARE_SPMPCFG_SETTER(61)
DECLARE_SPMPCFG_SETTER(62)
DECLARE_SPMPCFG_SETTER(63)

/**
  \brief        Set SPMPxCFG by index
  \details      Writes the given value to the SPMPxCFG Register.
  \param [in]   idx         SPMPx region index
  \param [in]   pmpxcfg     SPMPxCFG Register value to set
 */
__STATIC_INLINE void __set_SPMPxCFG(unsigned long idx, unsigned long spmpcfg)
{
    switch (idx) {
        case 0:
            __set_SPMPCFG0(spmpcfg);
            break;
        case 1:
            __set_SPMPCFG1(spmpcfg);
            break;
        case 2:
            __set_SPMPCFG2(spmpcfg);
            break;
        case 3:
            __set_SPMPCFG3(spmpcfg);
            break;
        case 4:
            __set_SPMPCFG4(spmpcfg);
            break;
        case 5:
            __set_SPMPCFG5(spmpcfg);
            break;
        case 6:
            __set_SPMPCFG6(spmpcfg);
            break;
        case 7:
            __set_SPMPCFG7(spmpcfg);
            break;
        case 8:
            __set_SPMPCFG8(spmpcfg);
            break;
        case 9:
            __set_SPMPCFG9(spmpcfg);
            break;
        case 10:
            __set_SPMPCFG10(spmpcfg);
            break;
        case 11:
            __set_SPMPCFG11(spmpcfg);
            break;
        case 12:
            __set_SPMPCFG12(spmpcfg);
            break;
        case 13:
            __set_SPMPCFG13(spmpcfg);
            break;
        case 14:
            __set_SPMPCFG14(spmpcfg);
            break;
        case 15:
            __set_SPMPCFG15(spmpcfg);
            break;
        case 16:
            __set_SPMPCFG16(spmpcfg);
            break;
        case 17:
            __set_SPMPCFG17(spmpcfg);
            break;
        case 18:
            __set_SPMPCFG18(spmpcfg);
            break;
        case 19:
            __set_SPMPCFG19(spmpcfg);
            break;
        case 20:
            __set_SPMPCFG20(spmpcfg);
            break;
        case 21:
            __set_SPMPCFG21(spmpcfg);
            break;
        case 22:
            __set_SPMPCFG22(spmpcfg);
            break;
        case 23:
            __set_SPMPCFG23(spmpcfg);
            break;
        case 24:
            __set_SPMPCFG24(spmpcfg);
            break;
        case 25:
            __set_SPMPCFG25(spmpcfg);
            break;
        case 26:
            __set_SPMPCFG26(spmpcfg);
            break;
        case 27:
            __set_SPMPCFG27(spmpcfg);
            break;
        case 28:
            __set_SPMPCFG28(spmpcfg);
            break;
        case 29:
            __set_SPMPCFG29(spmpcfg);
            break;
        case 30:
            __set_SPMPCFG30(spmpcfg);
            break;
        case 31:
            __set_SPMPCFG31(spmpcfg);
            break;
        case 32:
            __set_SPMPCFG32(spmpcfg);
            break;
        case 33:
            __set_SPMPCFG33(spmpcfg);
            break;
        case 34:
            __set_SPMPCFG34(spmpcfg);
            break;
        case 35:
            __set_SPMPCFG35(spmpcfg);
            break;
        case 36:
            __set_SPMPCFG36(spmpcfg);
            break;
        case 37:
            __set_SPMPCFG37(spmpcfg);
            break;
        case 38:
            __set_SPMPCFG38(spmpcfg);
            break;
        case 39:
            __set_SPMPCFG39(spmpcfg);
            break;
        case 40:
            __set_SPMPCFG40(spmpcfg);
            break;
        case 41:
            __set_SPMPCFG41(spmpcfg);
            break;
        case 42:
            __set_SPMPCFG42(spmpcfg);
            break;
        case 43:
            __set_SPMPCFG43(spmpcfg);
            break;
        case 44:
            __set_SPMPCFG44(spmpcfg);
            break;
        case 45:
            __set_SPMPCFG45(spmpcfg);
            break;
        case 46:
            __set_SPMPCFG46(spmpcfg);
            break;
        case 47:
            __set_SPMPCFG47(spmpcfg);
            break;
        case 48:
            __set_SPMPCFG48(spmpcfg);
            break;
        case 49:
            __set_SPMPCFG49(spmpcfg);
            break;
        case 50:
            __set_SPMPCFG50(spmpcfg);
            break;
        case 51:
            __set_SPMPCFG51(spmpcfg);
            break;
        case 52:
            __set_SPMPCFG52(spmpcfg);
            break;
        case 53:
            __set_SPMPCFG53(spmpcfg);
            break;
        case 54:
            __set_SPMPCFG54(spmpcfg);
            break;
        case 55:
            __set_SPMPCFG55(spmpcfg);
            break;
        case 56:
            __set_SPMPCFG56(spmpcfg);
            break;
        case 57:
            __set_SPMPCFG57(spmpcfg);
            break;
        case 58:
            __set_SPMPCFG58(spmpcfg);
            break;
        case 59:
            __set_SPMPCFG59(spmpcfg);
            break;
        case 60:
            __set_SPMPCFG60(spmpcfg);
            break;
        case 61:
            __set_SPMPCFG61(spmpcfg);
            break;
        case 62:
            __set_SPMPCFG62(spmpcfg);
            break;
        case 63:
            __set_SPMPCFG63(spmpcfg);
            break;
        default:
            break;
    }
}

/**
  \brief        Get SPMPADDRx Register
  \details      Returns the content of the SPMPADDRx Register.
  \return       SPMPADDRx Register value
 */
#define DECLARE_SPMPADDR_GETTER(n) \
__ALWAYS_STATIC_INLINE unsigned long __get_SPMPADDR##n(void) \
{ \
    unsigned long result; \
    __set_xISELECT(SPMP_MMIO_SPMPADDR##n##_SPMPCFG##n); \
    result = __get_xIREG(); \
    return result; \
}
DECLARE_SPMPADDR_GETTER(0)
DECLARE_SPMPADDR_GETTER(1)
DECLARE_SPMPADDR_GETTER(2)
DECLARE_SPMPADDR_GETTER(3)
DECLARE_SPMPADDR_GETTER(4)
DECLARE_SPMPADDR_GETTER(5)
DECLARE_SPMPADDR_GETTER(6)
DECLARE_SPMPADDR_GETTER(7)
DECLARE_SPMPADDR_GETTER(8)
DECLARE_SPMPADDR_GETTER(9)
DECLARE_SPMPADDR_GETTER(10)
DECLARE_SPMPADDR_GETTER(11)
DECLARE_SPMPADDR_GETTER(12)
DECLARE_SPMPADDR_GETTER(13)
DECLARE_SPMPADDR_GETTER(14)
DECLARE_SPMPADDR_GETTER(15)
DECLARE_SPMPADDR_GETTER(16)
DECLARE_SPMPADDR_GETTER(17)
DECLARE_SPMPADDR_GETTER(18)
DECLARE_SPMPADDR_GETTER(19)
DECLARE_SPMPADDR_GETTER(20)
DECLARE_SPMPADDR_GETTER(21)
DECLARE_SPMPADDR_GETTER(22)
DECLARE_SPMPADDR_GETTER(23)
DECLARE_SPMPADDR_GETTER(24)
DECLARE_SPMPADDR_GETTER(25)
DECLARE_SPMPADDR_GETTER(26)
DECLARE_SPMPADDR_GETTER(27)
DECLARE_SPMPADDR_GETTER(28)
DECLARE_SPMPADDR_GETTER(29)
DECLARE_SPMPADDR_GETTER(30)
DECLARE_SPMPADDR_GETTER(31)
DECLARE_SPMPADDR_GETTER(32)
DECLARE_SPMPADDR_GETTER(33)
DECLARE_SPMPADDR_GETTER(34)
DECLARE_SPMPADDR_GETTER(35)
DECLARE_SPMPADDR_GETTER(36)
DECLARE_SPMPADDR_GETTER(37)
DECLARE_SPMPADDR_GETTER(38)
DECLARE_SPMPADDR_GETTER(39)
DECLARE_SPMPADDR_GETTER(40)
DECLARE_SPMPADDR_GETTER(41)
DECLARE_SPMPADDR_GETTER(42)
DECLARE_SPMPADDR_GETTER(43)
DECLARE_SPMPADDR_GETTER(44)
DECLARE_SPMPADDR_GETTER(45)
DECLARE_SPMPADDR_GETTER(46)
DECLARE_SPMPADDR_GETTER(47)
DECLARE_SPMPADDR_GETTER(48)
DECLARE_SPMPADDR_GETTER(49)
DECLARE_SPMPADDR_GETTER(50)
DECLARE_SPMPADDR_GETTER(51)
DECLARE_SPMPADDR_GETTER(52)
DECLARE_SPMPADDR_GETTER(53)
DECLARE_SPMPADDR_GETTER(54)
DECLARE_SPMPADDR_GETTER(55)
DECLARE_SPMPADDR_GETTER(56)
DECLARE_SPMPADDR_GETTER(57)
DECLARE_SPMPADDR_GETTER(58)
DECLARE_SPMPADDR_GETTER(59)
DECLARE_SPMPADDR_GETTER(60)
DECLARE_SPMPADDR_GETTER(61)
DECLARE_SPMPADDR_GETTER(62)
DECLARE_SPMPADDR_GETTER(63)

/**
  \brief        Get SPMPADDRx Register by index
  \details      Returns the content of the SPMPADDRx Register.
  \param [in]   idx         SPMP region index
  \return                   SPMPADDRx Register value
 */
__STATIC_INLINE unsigned long __get_SPMPADDRx(unsigned long idx)
{
    unsigned long spmpaddr = 0;

    switch (idx) {
        case 0:
            spmpaddr = __get_SPMPADDR0();
            break;
        case 1:
            spmpaddr = __get_SPMPADDR1();
            break;
        case 2:
            spmpaddr = __get_SPMPADDR2();
            break;
        case 3:
            spmpaddr = __get_SPMPADDR3();
            break;
        case 4:
            spmpaddr = __get_SPMPADDR4();
            break;
        case 5:
            spmpaddr = __get_SPMPADDR5();
            break;
        case 6:
            spmpaddr = __get_SPMPADDR6();
            break;
        case 7:
            spmpaddr = __get_SPMPADDR7();
            break;
        case 8:
            spmpaddr = __get_SPMPADDR8();
            break;
        case 9:
            spmpaddr = __get_SPMPADDR9();
            break;
        case 10:
            spmpaddr = __get_SPMPADDR10();
            break;
        case 11:
            spmpaddr = __get_SPMPADDR11();
            break;
        case 12:
            spmpaddr = __get_SPMPADDR12();
            break;
        case 13:
            spmpaddr = __get_SPMPADDR13();
            break;
        case 14:
            spmpaddr = __get_SPMPADDR14();
            break;
        case 15:
            spmpaddr = __get_SPMPADDR15();
            break;
        case 16:
            spmpaddr = __get_SPMPADDR16();
            break;
        case 17:
            spmpaddr = __get_SPMPADDR17();
            break;
        case 18:
            spmpaddr = __get_SPMPADDR18();
            break;
        case 19:
            spmpaddr = __get_SPMPADDR19();
            break;
        case 20:
            spmpaddr = __get_SPMPADDR20();
            break;
        case 21:
            spmpaddr = __get_SPMPADDR21();
            break;
        case 22:
            spmpaddr = __get_SPMPADDR22();
            break;
        case 23:
            spmpaddr = __get_SPMPADDR23();
            break;
        case 24:
            spmpaddr = __get_SPMPADDR24();
            break;
        case 25:
            spmpaddr = __get_SPMPADDR25();
            break;
        case 26:
            spmpaddr = __get_SPMPADDR26();
            break;
        case 27:
            spmpaddr = __get_SPMPADDR27();
            break;
        case 28:
            spmpaddr = __get_SPMPADDR28();
            break;
        case 29:
            spmpaddr = __get_SPMPADDR29();
            break;
        case 30:
            spmpaddr = __get_SPMPADDR30();
            break;
        case 31:
            spmpaddr = __get_SPMPADDR31();
            break;
        case 32:
            spmpaddr = __get_SPMPADDR32();
            break;
        case 33:
            spmpaddr = __get_SPMPADDR33();
            break;
        case 34:
            spmpaddr = __get_SPMPADDR34();
            break;
        case 35:
            spmpaddr = __get_SPMPADDR35();
            break;
        case 36:
            spmpaddr = __get_SPMPADDR36();
            break;
        case 37:
            spmpaddr = __get_SPMPADDR37();
            break;
        case 38:
            spmpaddr = __get_SPMPADDR38();
            break;
        case 39:
            spmpaddr = __get_SPMPADDR39();
            break;
        case 40:
            spmpaddr = __get_SPMPADDR40();
            break;
        case 41:
            spmpaddr = __get_SPMPADDR41();
            break;
        case 42:
            spmpaddr = __get_SPMPADDR42();
            break;
        case 43:
            spmpaddr = __get_SPMPADDR43();
            break;
        case 44:
            spmpaddr = __get_SPMPADDR44();
            break;
        case 45:
            spmpaddr = __get_SPMPADDR45();
            break;
        case 46:
            spmpaddr = __get_SPMPADDR46();
            break;
        case 47:
            spmpaddr = __get_SPMPADDR47();
            break;
        case 48:
            spmpaddr = __get_SPMPADDR48();
            break;
        case 49:
            spmpaddr = __get_SPMPADDR49();
            break;
        case 50:
            spmpaddr = __get_SPMPADDR50();
            break;
        case 51:
            spmpaddr = __get_SPMPADDR51();
            break;
        case 52:
            spmpaddr = __get_SPMPADDR52();
            break;
        case 53:
            spmpaddr = __get_SPMPADDR53();
            break;
        case 54:
            spmpaddr = __get_SPMPADDR54();
            break;
        case 55:
            spmpaddr = __get_SPMPADDR55();
            break;
        case 56:
            spmpaddr = __get_SPMPADDR56();
            break;
        case 57:
            spmpaddr = __get_SPMPADDR57();
            break;
        case 58:
            spmpaddr = __get_SPMPADDR58();
            break;
        case 59:
            spmpaddr = __get_SPMPADDR59();
            break;
        case 60:
            spmpaddr = __get_SPMPADDR60();
            break;
        case 61:
            spmpaddr = __get_SPMPADDR61();
            break;
        case 62:
            spmpaddr = __get_SPMPADDR62();
            break;
        case 63:
            spmpaddr = __get_SPMPADDR63();
            break;
        default:
            break;
    }
    return spmpaddr;
}

/**
  \brief        Set SPMPADDRx
  \details      Writes the given value to the SPMPADDRx Register.
  \param [in]   pmpaddr     SPMPADDRx Register value to set
 */
#define DECLARE_SPMPADDR_SETTER(n) \
__ALWAYS_STATIC_INLINE void __set_SPMPADDR##n(unsigned long spmpaddr) \
{ \
    __set_xISELECT(SPMP_MMIO_SPMPADDR##n##_SPMPCFG##n); \
    __set_xIREG(spmpaddr); \
}
DECLARE_SPMPADDR_SETTER(0)
DECLARE_SPMPADDR_SETTER(1)
DECLARE_SPMPADDR_SETTER(2)
DECLARE_SPMPADDR_SETTER(3)
DECLARE_SPMPADDR_SETTER(4)
DECLARE_SPMPADDR_SETTER(5)
DECLARE_SPMPADDR_SETTER(6)
DECLARE_SPMPADDR_SETTER(7)
DECLARE_SPMPADDR_SETTER(8)
DECLARE_SPMPADDR_SETTER(9)
DECLARE_SPMPADDR_SETTER(10)
DECLARE_SPMPADDR_SETTER(11)
DECLARE_SPMPADDR_SETTER(12)
DECLARE_SPMPADDR_SETTER(13)
DECLARE_SPMPADDR_SETTER(14)
DECLARE_SPMPADDR_SETTER(15)
DECLARE_SPMPADDR_SETTER(16)
DECLARE_SPMPADDR_SETTER(17)
DECLARE_SPMPADDR_SETTER(18)
DECLARE_SPMPADDR_SETTER(19)
DECLARE_SPMPADDR_SETTER(20)
DECLARE_SPMPADDR_SETTER(21)
DECLARE_SPMPADDR_SETTER(22)
DECLARE_SPMPADDR_SETTER(23)
DECLARE_SPMPADDR_SETTER(24)
DECLARE_SPMPADDR_SETTER(25)
DECLARE_SPMPADDR_SETTER(26)
DECLARE_SPMPADDR_SETTER(27)
DECLARE_SPMPADDR_SETTER(28)
DECLARE_SPMPADDR_SETTER(29)
DECLARE_SPMPADDR_SETTER(30)
DECLARE_SPMPADDR_SETTER(31)
DECLARE_SPMPADDR_SETTER(32)
DECLARE_SPMPADDR_SETTER(33)
DECLARE_SPMPADDR_SETTER(34)
DECLARE_SPMPADDR_SETTER(35)
DECLARE_SPMPADDR_SETTER(36)
DECLARE_SPMPADDR_SETTER(37)
DECLARE_SPMPADDR_SETTER(38)
DECLARE_SPMPADDR_SETTER(39)
DECLARE_SPMPADDR_SETTER(40)
DECLARE_SPMPADDR_SETTER(41)
DECLARE_SPMPADDR_SETTER(42)
DECLARE_SPMPADDR_SETTER(43)
DECLARE_SPMPADDR_SETTER(44)
DECLARE_SPMPADDR_SETTER(45)
DECLARE_SPMPADDR_SETTER(46)
DECLARE_SPMPADDR_SETTER(47)
DECLARE_SPMPADDR_SETTER(48)
DECLARE_SPMPADDR_SETTER(49)
DECLARE_SPMPADDR_SETTER(50)
DECLARE_SPMPADDR_SETTER(51)
DECLARE_SPMPADDR_SETTER(52)
DECLARE_SPMPADDR_SETTER(53)
DECLARE_SPMPADDR_SETTER(54)
DECLARE_SPMPADDR_SETTER(55)
DECLARE_SPMPADDR_SETTER(56)
DECLARE_SPMPADDR_SETTER(57)
DECLARE_SPMPADDR_SETTER(58)
DECLARE_SPMPADDR_SETTER(59)
DECLARE_SPMPADDR_SETTER(60)
DECLARE_SPMPADDR_SETTER(61)
DECLARE_SPMPADDR_SETTER(62)
DECLARE_SPMPADDR_SETTER(63)

/**
  \brief        Set SPMPADDRx by index
  \details      Writes the given value to the SPMPADDRx Register.
  \param [in]   idx         SPMP region index
  \param [in]   spmpaddr    SPMPADDRx Register value to set
 */
__STATIC_INLINE void __set_SPMPADDRx(unsigned long idx, unsigned long spmpaddr)
{
    switch (idx) {
        case 0:
            __set_SPMPADDR0(spmpaddr);
            break;
        case 1:
            __set_SPMPADDR1(spmpaddr);
            break;
        case 2:
            __set_SPMPADDR2(spmpaddr);
            break;
        case 3:
            __set_SPMPADDR3(spmpaddr);
            break;
        case 4:
            __set_SPMPADDR4(spmpaddr);
            break;
        case 5:
            __set_SPMPADDR5(spmpaddr);
            break;
        case 6:
            __set_SPMPADDR6(spmpaddr);
            break;
        case 7:
            __set_SPMPADDR7(spmpaddr);
            break;
        case 8:
            __set_SPMPADDR8(spmpaddr);
            break;
        case 9:
            __set_SPMPADDR9(spmpaddr);
            break;
        case 10:
            __set_SPMPADDR10(spmpaddr);
            break;
        case 11:
            __set_SPMPADDR11(spmpaddr);
            break;
        case 12:
            __set_SPMPADDR12(spmpaddr);
            break;
        case 13:
            __set_SPMPADDR13(spmpaddr);
            break;
        case 14:
            __set_SPMPADDR14(spmpaddr);
            break;
        case 15:
            __set_SPMPADDR15(spmpaddr);
            break;
        case 16:
            __set_SPMPADDR16(spmpaddr);
            break;
        case 17:
            __set_SPMPADDR17(spmpaddr);
            break;
        case 18:
            __set_SPMPADDR18(spmpaddr);
            break;
        case 19:
            __set_SPMPADDR19(spmpaddr);
            break;
        case 20:
            __set_SPMPADDR20(spmpaddr);
            break;
        case 21:
            __set_SPMPADDR21(spmpaddr);
            break;
        case 22:
            __set_SPMPADDR22(spmpaddr);
            break;
        case 23:
            __set_SPMPADDR23(spmpaddr);
            break;
        case 24:
            __set_SPMPADDR24(spmpaddr);
            break;
        case 25:
            __set_SPMPADDR25(spmpaddr);
            break;
        case 26:
            __set_SPMPADDR26(spmpaddr);
            break;
        case 27:
            __set_SPMPADDR27(spmpaddr);
            break;
        case 28:
            __set_SPMPADDR28(spmpaddr);
            break;
        case 29:
            __set_SPMPADDR29(spmpaddr);
            break;
        case 30:
            __set_SPMPADDR30(spmpaddr);
            break;
        case 31:
            __set_SPMPADDR31(spmpaddr);
            break;
        case 32:
            __set_SPMPADDR32(spmpaddr);
            break;
        case 33:
            __set_SPMPADDR33(spmpaddr);
            break;
        case 34:
            __set_SPMPADDR34(spmpaddr);
            break;
        case 35:
            __set_SPMPADDR35(spmpaddr);
            break;
        case 36:
            __set_SPMPADDR36(spmpaddr);
            break;
        case 37:
            __set_SPMPADDR37(spmpaddr);
            break;
        case 38:
            __set_SPMPADDR38(spmpaddr);
            break;
        case 39:
            __set_SPMPADDR39(spmpaddr);
            break;
        case 40:
            __set_SPMPADDR40(spmpaddr);
            break;
        case 41:
            __set_SPMPADDR41(spmpaddr);
            break;
        case 42:
            __set_SPMPADDR42(spmpaddr);
            break;
        case 43:
            __set_SPMPADDR43(spmpaddr);
            break;
        case 44:
            __set_SPMPADDR44(spmpaddr);
            break;
        case 45:
            __set_SPMPADDR45(spmpaddr);
            break;
        case 46:
            __set_SPMPADDR46(spmpaddr);
            break;
        case 47:
            __set_SPMPADDR47(spmpaddr);
            break;
        case 48:
            __set_SPMPADDR48(spmpaddr);
            break;
        case 49:
            __set_SPMPADDR49(spmpaddr);
            break;
        case 50:
            __set_SPMPADDR50(spmpaddr);
            break;
        case 51:
            __set_SPMPADDR51(spmpaddr);
            break;
        case 52:
            __set_SPMPADDR52(spmpaddr);
            break;
        case 53:
            __set_SPMPADDR53(spmpaddr);
            break;
        case 54:
            __set_SPMPADDR54(spmpaddr);
            break;
        case 55:
            __set_SPMPADDR55(spmpaddr);
            break;
        case 56:
            __set_SPMPADDR56(spmpaddr);
            break;
        case 57:
            __set_SPMPADDR57(spmpaddr);
            break;
        case 58:
            __set_SPMPADDR58(spmpaddr);
            break;
        case 59:
            __set_SPMPADDR59(spmpaddr);
            break;
        case 60:
            __set_SPMPADDR60(spmpaddr);
            break;
        case 61:
            __set_SPMPADDR61(spmpaddr);
            break;
        case 62:
            __set_SPMPADDR62(spmpaddr);
            break;
        case 63:
            __set_SPMPADDR63(spmpaddr);
            break;
        default:
            break;
    }
}

/**
  \brief        Set MPMPDELEG
  \details      Writes the given value to the MPMPDELEG Register.
  \param [in]   mpmpdeleg   MPMPDELEG Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MPMPDELEG(unsigned long mpmpdeleg)
{
    __set_MISELECT(SPMP_MMIO_MPMPDELEG);
    __set_MIREG(mpmpdeleg);
    // __ASM volatile("csrw mpmpdeleg, %0" : : "r"(mpmpdeleg));
}

/**
  \brief        Get MPMPDELEG
  \details      Returns the content of the MPMPDELEG Register.
  \return       MPMPDELEG Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MPMPDELEG(void)
{
    unsigned long result;
    __set_MISELECT(SPMP_MMIO_MPMPDELEG);
    result = __get_MIREG();
    return result;
    // unsigned long result;
    // __ASM volatile("csrr %0, mpmpdeleg" : "=r"(result));
    // return result;
}

/**
  \brief        Set SSPMPSWITCH
  \details      Writes the given value to the SSPMPSWITCH Register.
  \param [in]   sspmpswitch   SSPMPSWITCH Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SSPMPSWITCH(unsigned long sspmpswitch)
{
    __set_xISELECT(SPMP_MMIO_SSPMP_SWITCH_SWITCHH);
    __set_xIREG(sspmpswitch);
}

/**
  \brief        Get SSPMPSWITCH
  \details      Returns the content of the SSPMPSWITCH Register.
  \return       SSPMPSWITCH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SSPMPSWITCH(void)
{
    unsigned long result;
    __set_xISELECT(SPMP_MMIO_SSPMP_SWITCH_SWITCHH);
    result = __get_xIREG();
    return result;
}

/**
  \brief        Set SSPMPSWITCHH
  \details      Writes the given value to the SSPMPSWITCHH Register.
  \param [in]   sspmpswitchh   SSPMPSWITCHH Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SSPMPSWITCHH(unsigned long sspmpswitchh)
{
    __set_xISELECT(SPMP_MMIO_SSPMP_SWITCH_SWITCHH);
    __set_xIREG2(sspmpswitchh);
}

/**
  \brief        Get SSPMPSWITCHH
  \details      Returns the content of the SSPMPSWITCHH Register.
  \return       SSPMPSWITCHH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SSPMPSWITCHH(void)
{
    unsigned long result;
    __set_xISELECT(SPMP_MMIO_SSPMP_SWITCH_SWITCHH);
    result = __get_xIREG2();
    return result;
}

/* ##########################   SPMP functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SPMPFunctions SPMP Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/**
  \brief        Configure PMP/SPMP allocation
  \details      Configure how many PMP entries will be delegated to S-mode as SPMP by setting the mpmpdeleg CSR.
                All PMP entries with an index equal to or greater than pmpnum will be allocated to SPMP.
                This function is used in M-mode.
  \param [in]   start_index   The starting index of PMP entries allocated to SPMP
  \return       0: success, non-zero: failure (e.g., requested pmpnum exceeds the actual supported number of PMP entries)
  */
__STATIC_INLINE int csi_spmp_alloc_entries_start_from(unsigned long start_index)
{
    if (start_index > 63)
        return -1;
    __set_MPMPDELEG(start_index);
    return 0;
}

/**
  \brief        Get current PMP/SPMP allocation start entry
  \details      Read the pmpnum field in the mpmpdeleg CSR, which indicates from which index PMP entries are assigned for SPMP use.
                This function is used in M-mode.
  \return       Pmpnum value, representing the starting index of PMP entries allocated to SPMP
 */
__STATIC_INLINE int csi_spmp_get_allocated_start_entry(void)
{
    return __get_MPMPDELEG() & 0x7F;
}

/**
  \brief        Configure S-level physical memory protection region.
  \param [in]   idx         Memory protection region (0, 1, 2, ..., 63).
  \param [in]   base_addr   Base address.
  \param [in]   size        Memory protection entry size.
  \param [in]   attr        \ref spmp_region_attr_t. Memory protection region attribute.
  \param [in]   enable      Enable or disable memory protection region.
  */
__STATIC_INLINE void csi_spmp_config_entry(uint32_t idx, unsigned long base_addr, unsigned long size,
                                           spmp_region_attr_t attr, uint32_t enable)
{
    unsigned long pmpxcfg = 0;
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

    __set_SPMPADDRx(idx, addr);

    pmpxcfg |= (attr.r << SPMP_PMPCFG_R_Pos) | (attr.w << SPMP_PMPCFG_W_Pos) |
               (attr.x << SPMP_PMPCFG_X_Pos) | (attr.a << SPMP_PMPCFG_A_Pos) |
               (attr.l << SPMP_PMPCFG_L_Pos) | (attr.u << SPMP_PMPCFG_U_Pos) |
               (attr.shared << SPMP_PMPCFG_SHARED_Pos);

    __set_SPMPxCFG(idx, pmpxcfg);
}

/**
  \brief        Disable S-level physical memory protection entry by idx.
  \param [in]   idx         Memory protection region (0, 1, 2, ..., 63).
  */
__STATIC_INLINE void csi_spmp_disable_entry(uint32_t idx)
{
    if (idx > 63) {
        return;
    }
    __set_SPMPxCFG(idx, __get_SPMPxCFG(idx) & (~SPMP_PMPCFG_A_Msk));
}

/**
  \brief        Activate physical memory protection entry by idx in sspmpswitch/sspmpswitchh.
  \param [in]   idx         Memory protection region (0, 1, 2, ..., 63).
  */
__STATIC_INLINE void csi_spmp_ctx_switching_activate_entry(uint32_t idx)
{
    /* Sspmpsw extension */
    uint32_t l_idx;
    unsigned long sspmpswitch;

#if __riscv_xlen == 32
    if (idx > 31) {
        l_idx = idx - 32;
        sspmpswitch = __get_SSPMPSWITCHH();
    } else
#endif
    {
        l_idx = idx;
        sspmpswitch = __get_SSPMPSWITCH();
    }

    sspmpswitch |= (1UL << l_idx);

#if __riscv_xlen == 32
    if (idx > 31) {
        __set_SSPMPSWITCHH(sspmpswitch);
    } else
#endif
    {
        __set_SSPMPSWITCH(sspmpswitch);
    }
}

/**
  \brief        Deactivate physical memory protection entry by idx in sspmpswitch/sspmpswitchh.
  \param [in]   idx         Memory protection region (0, 1, 2, ..., 63).
  */
__STATIC_INLINE void csi_spmp_ctx_switching_deactivate_entry(uint32_t idx)
{
    /* Sspmpsw extension */
    uint32_t l_idx;
    unsigned long sspmpswitch;

#if __riscv_xlen == 32
    if (idx > 31) {
        l_idx = idx - 32;
        sspmpswitch = __get_SSPMPSWITCHH();
    } else
#endif
    {
        l_idx = idx;
        sspmpswitch = __get_SSPMPSWITCH();
    }

    sspmpswitch &= ~(1UL << l_idx);

#if __riscv_xlen == 32
    if (idx > 31) {
        __set_SSPMPSWITCHH(sspmpswitch);
    } else
#endif
    {
        __set_SSPMPSWITCH(sspmpswitch);
    }
}

/**
  \brief        Activate physical memory protection entries by idx in sspmpswitch/sspmpswitchh.
  \param [in]   entries_idx   Array of entries indices to be activated
  \param [in]   entries_num   Number of entries to be activated
  */
__STATIC_INLINE void csi_spmp_ctx_switching_activate_entries(uint32_t entries_idx[], uint32_t entries_num)
{
    unsigned long sspmpswitch = __get_SSPMPSWITCH();
#if __riscv_xlen == 32
    unsigned long sspmpswitchh = __get_SSPMPSWITCHH();
#endif

    for (uint32_t i = 0; i < entries_num; i++) {
        uint32_t idx = entries_idx[i];
#if __riscv_xlen == 32
        if (idx < 32) {
            sspmpswitch |= (1UL << idx);
        } else if (idx < 64) {
            sspmpswitchh |= (1UL << (idx - 32));
        }
#else
        sspmpswitch |= (1UL << idx);
#endif
    }

#if __riscv_xlen == 32
    __set_SSPMPSWITCH(sspmpswitch);
    __set_SSPMPSWITCHH(sspmpswitchh);
#else
    __set_SSPMPSWITCH(sspmpswitch);
#endif
}

/**
  \brief        Deactivate physical memory protection entries by idx in sspmpswitch/sspmpswitchh.
  \param [in]   entries_idx   Array of entries indices to be deactivated
  \param [in]   entries_num   Number of entries to be deactivated
  */
__STATIC_INLINE void csi_spmp_ctx_switching_deactivate_entries(uint32_t entries_idx[], uint32_t entries_num)
{
    unsigned long sspmpswitch = __get_SSPMPSWITCH();
#if __riscv_xlen == 32
    unsigned long sspmpswitchh = __get_SSPMPSWITCHH();
#endif

    for (uint32_t i = 0; i < entries_num; i++) {
        uint32_t idx = entries_idx[i];
#if __riscv_xlen == 32
        if (idx < 32) {
            sspmpswitch &= ~(1UL << idx);
        } else if (idx < 64) {
            sspmpswitchh &= ~(1UL << (idx - 32));
        }
#else
        sspmpswitch &= ~(1UL << idx);
#endif
    }

#if __riscv_xlen == 32
    __set_SSPMPSWITCH(sspmpswitch);
    __set_SSPMPSWITCHH(sspmpswitchh);
#else
    __set_SSPMPSWITCH(sspmpswitch);
#endif
}

/*@} end of CSI_Core_SPMPFunctions */

#endif /* SPMP_SPEC_VERSION_100_RC4 */

#endif /* __CORE_RV_SPMP_H__ */
