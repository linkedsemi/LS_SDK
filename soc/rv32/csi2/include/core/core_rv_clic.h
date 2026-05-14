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

#ifndef __CORE_RV_CLIC_H__
#define __CORE_RV_CLIC_H__

#include "csi_rv_common.h"

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_CLIC Core-Local Interrupt Controller (CLIC)
  \brief      Type definitions for the CLIC Registers
  @{
 */

/**
  \brief Access to the structure of a vector interrupt controller.
 */

#if CLIC_SPEC_VERSION_010

/* clicintip[i] and clicintie[i] address calculation */
#define CLIC_INTIP_OFFSET(irq)    (0x1400 + ((irq) >> 5))                        /* 32 interrupts share one 32-bit register */
#define CLIC_INTIE_OFFSET(irq)    (0x1400 + ((irq) >> 5))                        /* Same as above, accessed via mireg2 */
#define CLIC_IP_IE_POS(irq)       ((uint32_t)(irq % 32))                         /* IP/IE bit position in 32-bit register */
#define CLIC_IP_IE_BIT(irq)       ((uint32_t)(0x01 << CLIC_IP_IE_POS(irq)))      /* IP/IE bit position in 32-bit register */

/* clicintctl[i] and clicintattr[i] address calculation */
#define CLIC_INTCTL_OFFSET(irq)   (0x1000 + ((irq) >> 2))            /* 4 interrupts share one 32-bit register */
#define CLIC_INTATTR_OFFSET(irq)  (0x1000 + ((irq) >> 2))            /* Same as above, accessed via mireg2 */

/* clicinttrig[i] address calculation */
#define CLIC_INTTRIG_OFFSET(irq)  (0x1800 + (irq))                   /* One 32-bit register per interrupt */

/* mclicfg */
#define CLIC_MCLICCFG_OFFSET      (0x14a0)

/* Bit position and mask calculation macros */
#define CLIC_CTL_ATTR_BYTE(irq)   (((irq) & 0x3) * 8)                /* CTL/ATTR byte position in 32-bit register */
#define CLIC_CTL_ATTR_MASK(irq)   (0xFF << CLIC_CTL_ATTR_BYTE(irq))  /* Byte mask */

typedef union {
    uint8_t byte[4];
    uint32_t word;
} clic_intctl_t;

typedef union {
    uint8_t byte[4];
    uint32_t word;
} clic_intattr_t;

#else /* CLIC_SPEC_VERSION_010 */

typedef struct {
    __IOM uint8_t IP;           /*!< Offset: 0x000 (R/W)  Interrupt set pending register */
    __IOM uint8_t IE;           /*!< Offset: 0x004 (R/W)  Interrupt set enable register */
    __IOM uint8_t ATTR;         /*!< Offset: 0x008 (R/W)  Interrupt set attribute register */
    __IOM uint8_t CTL;          /*!< Offset: 0x00C (R/W)  Interrupt control register */
} CLIC_INT_Control;

typedef struct {
    __IOM uint32_t CLICCFG:8;                 /*!< Offset: 0x000 (R/W)  CLIC configure register */
    __IM  uint32_t CLICINFO;
    __IOM uint32_t MINTTHRESH;
    uint32_t RESERVED[1021];
    CLIC_INT_Control CLICINT[4096];
} CLIC_Type;

#endif /* CLIC_SPEC_VERSION_010 */

#define CLIC_INFO_CLICINTCTLBITS_Pos           21U
#define CLIC_INFO_CLICINTCTLBITS_Msk           (0xFUL << CLIC_INFO_CLICINTCTLBITS_Pos)

#define CLIC_INTIP_IP_Pos                      0U                                    /*!< CLIC INTIP: IP Position */
#define CLIC_INTIP_IP_Msk                      (0x1UL << CLIC_INTIP_IP_Pos)          /*!< CLIC INTIP: IP Mask */

#define CLIC_INTIE_IE_Pos                      0U                                    /*!< CLIC INTIE: IE Position */
#define CLIC_INTIE_IE_Msk                      (0x1UL << CLIC_INTIE_IE_Pos)          /*!< CLIC INTIE: IE Mask */

#define CLIC_INTIE_T_Pos                       7U                                    /*!< CLIC INTIE: T Position */
#define CLIC_INTIE_T_Msk                       (0x1UL << CLIC_INTIE_T_Pos)           /*!< CLIC INTIE: T Mask */

#define CLIC_INTATTR_TRIG_Pos                  1U                                    /*!< CLIC INTATTR: TRIG Position */
#define CLIC_INTATTR_TRIG_Msk                  (0x3UL << CLIC_INTATTR_TRIG_Pos)      /*!< CLIC INTATTR: TRIG Mask */

#define CLIC_INTATTR_SHV_Pos                   0U                                    /*!< CLIC INTATTR: SHV Position */
#define CLIC_INTATTR_SHV_Msk                   (0x1UL << CLIC_INTATTR_SHV_Pos)       /*!< CLIC INTATTR: SHV Mask */

#define CLIC_INTATTR_MODE_Pos                  6U                                    /*!< CLIC INTATTR: MODE Position */
#define CLIC_INTATTR_MODE_Msk                  (0x3UL << CLIC_INTATTR_MODE_Pos)      /*!< CLIC INTATTR: MODE Mask */

#define CLIC_INTCFG_NVBIT_Pos                  5U                                    /*!< CLIC INTCFG: NVBIT Position */
#define CLIC_INTCFG_NVBIT_Msk                  (0x1UL << CLIC_INTCFG_NVBIT_Pos)      /*!< CLIC INTCFG: NVBIT Mask */

#define CLIC_INTCFG_PRIO_Pos                   5U                                    /*!< CLIC INTCFG: INTCFG Position */
#define CLIC_INTCFG_PRIO_Msk                   (0x7UL << CLIC_INTCFG_PRIO_Pos)       /*!< CLIC INTCFG: INTCFG Mask */

#define CLIC_CLICCFG_NVBIT_Pos                 0U                                    /*!< CLIC CLICCFG: NVBIT Position */
#define CLIC_CLICCFG_NVBIT_Msk                 (0x1UL << CLIC_CLICCFG_NVBIT_Pos)     /*!< CLIC CLICCFG: NVBIT Mask */

#define CLIC_CLICCFG_NLBIT_Pos                 1U                                    /*!< CLIC CLICCFG: NLBIT Position */
#define CLIC_CLICCFG_NLBIT_Msk                 (0xFUL << CLIC_CLICCFG_NLBIT_Pos)     /*!< CLIC CLICCFG: NLBIT Mask */

#define CLIC_CLICCFG_NMBIT_Pos                 5U                                    /*!< CLIC CLICCFG: NMBIT Position */
#define CLIC_CLICCFG_NMBIT_Msk                 (0x3UL << CLIC_CLICCFG_NMBIT_Pos)     /*!< CLIC CLICCFG: NMBIT Mask */


#define CLIC_ATTR_SHV_SOFT_VECTORED                 0U                               /*!< CLIC ATTR SHV: software vectored */
#define CLIC_ATTR_SHV_HARD_VECTORED                 1U                               /*!< CLIC ATTR SHV: hardware vectored */

#define CLIC_ATTR_TRIG_POSITIVE_LEVEL               0U                               /*!< CLIC ATTR TRIG: positive level-triggered */
#define CLIC_ATTR_TRIG_POSITIVE_EDGE                1U                               /*!< CLIC ATTR TRIG: positive edge-triggered */
#define CLIC_ATTR_TRIG_NEGATIVE_LEVEL               2U                               /*!< CLIC ATTR TRIG: negative level-triggered */
#define CLIC_ATTR_TRIG_NEGATIVE_EDGE                3U                               /*!< CLIC ATTR TRIG: negative edge-triggered */

#define CLIC_ATTR_MODE_U                            0U                               /*!< CLIC ATTR MODE: interrupt operates in User mode */
#define CLIC_ATTR_MODE_S                            1U                               /*!< CLIC ATTR MODE: interrupt operates in Supervisor mode */
#define CLIC_ATTR_MODE_M                            3U                               /*!< CLIC ATTR MODE: interrupt operates in Machine mode */

/*@} end of group CSI_CLIC */

#if !CLIC_SPEC_VERSION_010
#ifndef CONFIG_CLIC_BASE
#define CONFIG_CLIC_BASE           (CONFIG_TCIP_BASE + 0x800000UL)       /*!< CLIC Base Address */
#endif
#define CLIC                       ((CLIC_Type *)CONFIG_CLIC_BASE)       /*!< CLIC configuration struct */
#endif

/**
  \brief        Get MCLICCFG
  \details      Returns the current value of the MCLICCFG.
  \return       MCLICCFG Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCLICCFG(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, mcliccfg" : "=r"(result));
    return (result);
}

/**
  \brief        Set MCLICCFG
  \details      Assigns the given value to the MCLICCFG.
  \param [in]   mcliccfg    MCLICCFG value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCLICCFG(unsigned long mcliccfg)
{
    __ASM volatile("csrw mcliccfg, %0" : : "r"(mcliccfg));
}

/**
  \brief        Get SCLICCFG
  \details      Returns the current value of the SCLICCFG.
  \return       SCLICCFG Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCLICCFG(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, scliccfg" : "=r"(result));
    return (result);
}

/**
  \brief        Set SCLICCFG
  \details      Assigns the given value to the SCLICCFG.
  \param [in]   scliccfg    SCLICCFG value to set
 */
__ALWAYS_STATIC_INLINE void __set_SCLICCFG(unsigned long scliccfg)
{
    __ASM volatile("csrw scliccfg, %0" : : "r"(scliccfg));
}

/**
  \brief        Set MTVT
  \details      Writes the given value to the MTVT Register.
  \param [in]   mtvt    MTVT Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MTVT(unsigned long mtvt)
{
    rv_csr_write(CSR_MTVT, mtvt);
}

/**
  \brief        Get MTVT Register
  \details      Returns the content of the MTVT Register.
  \return       MTVT Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MTVT(void)
{
    return rv_csr_read(CSR_MTVT);
}

/**
  \brief        Get STVT
  \details      Returns the current value of the STVT.
  \return       STVT Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_STVT(void)
{
    return rv_csr_read(CSR_STVT);
}

/**
  \brief        Set STVT
  \details      Assigns the given value to the STVT.
  \param [in]   stvt    STVT value to set
 */
__ALWAYS_STATIC_INLINE void __set_STVT(unsigned long stvt)
{
    rv_csr_write(CSR_STVT, stvt);
}

/**
  \brief        Get MINTTHRESH
  \details      Returns the current value of the MINTTHRESH.
  \return       MINTTHRESH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MINTTHRESH(void)
{
    return rv_csr_read(CSR_MINTTHRESH);
}

/**
  \brief        Set MINTTHRESH
  \details      Assigns the given value to the MINTTHRESH.
  \param [in]   mintthresh    MINTTHRESH value to set
 */
__ALWAYS_STATIC_INLINE void __set_MINTTHRESH(unsigned long mintthresh)
{
    rv_csr_write(CSR_MINTTHRESH, mintthresh);
}

/**
  \brief        Get SINTTHRESH
  \details      Returns the current value of the SINTTHRESH.
  \return       SINTTHRESH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SINTTHRESH(void)
{
    return rv_csr_read(CSR_SINTTHRESH);
}

/**
  \brief        Set SINTTHRESH
  \details      Assigns the given value to the SINTTHRESH.
  \param [in]   sintthresh    SINTTHRESH value to set
 */
__ALWAYS_STATIC_INLINE void __set_SINTTHRESH(unsigned long sintthresh)
{
    rv_csr_write(CSR_SINTTHRESH, sintthresh);
}

/**
  \brief        Get MINTSTATUS Register
  \details      Returns the content of the MINTSTATUS Register.
  \return       MINTSTATUS Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MINTSTATUS(void)
{
    return rv_csr_read(CSR_MINTSTATUS);
}

/**
  \brief        Set MINTSTATUS
  \details      Assigns the given value to the MINTSTATUS.
  \param [in]   mintstatus    MINTSTATUS value to set
 */
__ALWAYS_STATIC_INLINE void __set_MINTSTATUS(unsigned long mintstatus)
{
    rv_csr_write(CSR_MINTSTATUS, mintstatus);
}

/**
  \brief        Get SINTSTATUS
  \details      Returns the current value of the SINTSTATUS.
  \return       SINTSTATUS Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SINTSTATUS(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, sintstatus" : "=r"(result));
    return (result);
}

/**
  \brief        Set SINTSTATUS
  \details      Assigns the given value to the SINTSTATUS.
  \param [in]   sintstatus    SINTSTATUS value to set
 */
__ALWAYS_STATIC_INLINE void __set_SINTSTATUS(unsigned long sintstatus)
{
    __ASM volatile("csrw sintstatus, %0" : : "r"(sintstatus));
}

/**
  \brief        Get MNXTI Register
  \details      Returns the content of the MNXTI Register.
  \return       MNXTI Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MNXTI(void)
{
    return rv_csr_read(CSR_MNXTI);
}

/**
  \brief        Set MNXTI
  \details      Writes the given value to the MNXTI Register.
  \param [in]   mnxti    MNXTI Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MNXTI(unsigned long mnxti)
{
    rv_csr_write(CSR_MNXTI, mnxti);
}

/**
  \brief        Get SNXTI
  \details      Returns the current value of the SNXTI.
  \return       SNXTI Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SNXTI(void)
{
    return rv_csr_read(CSR_SNXTI);
}

/**
  \brief        Set SNXTI
  \details      Assigns the given value to the SNXTI.
  \param [in]   snxti    SNXTI value to set
 */
__ALWAYS_STATIC_INLINE void __set_SNXTI(unsigned long snxti)
{
    rv_csr_write(CSR_SNXTI, snxti);
}

/**
  \brief        Get MSCRATCHCSW
  \details      Returns the current value of the MSCRATCHCSW.
  \return       MSCRATCHCSW Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MSCRATCHCSW(void)
{
    return rv_csr_read(CSR_MSCRATCHCSW);
}

/**
  \brief        Set MSCRATCHCSW
  \details      Assigns the given value to the MSCRATCHCSW.
  \param [in]   mscratchcsw    MSCRATCHCSW value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSCRATCHCSW(unsigned long mscratchcsw)
{
    rv_csr_write(CSR_MSCRATCHCSW, mscratchcsw);
}

/**
  \brief        Get SSCRATCHCSW
  \details      Returns the current value of the SSCRATCHCSW.
  \return       SSCRATCHCSW Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SSCRATCHCSW(void)
{
    return rv_csr_read(CSR_SSCRATCHCSW);
}

/**
  \brief        Set SSCRATCHCSW
  \details      Assigns the given value to the SSCRATCHCSW.
  \param [in]   sscratchcsw    SSCRATCHCSW value to set
 */
__ALWAYS_STATIC_INLINE void __set_SSCRATCHCSW(unsigned long sscratchcsw)
{
    rv_csr_write(CSR_SSCRATCHCSW, sscratchcsw);
}

/**
  \brief        Get MSCRATCHCSWL
  \details      Returns the current value of the MSCRATCHCSWL.
  \return       MSCRATCHCSWL Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MSCRATCHCSWL(void)
{
    return rv_csr_read(CSR_MSCRATCHCSWL);
}

/**
  \brief        Set MSCRATCHCSWL
  \details      Assigns the given value to the MSCRATCHCSWL.
  \param [in]   mscratchcswl    MSCRATCHCSWL value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSCRATCHCSWL(unsigned long mscratchcswl)
{
    rv_csr_write(CSR_MSCRATCHCSWL, mscratchcswl);
}

/**
  \brief        Get SSCRATCHCSWL
  \details      Returns the current value of the SSCRATCHCSWL.
  \return       SSCRATCHCSWL Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SSCRATCHCSWL(void)
{
    return rv_csr_read(CSR_SSCRATCHCSWL);
}

/**
  \brief        Set SSCRATCHCSWL
  \details      Assigns the given value to the SSCRATCHCSWL.
  \param [in]   sscratchcswl    SSCRATCHCSWL value to set
 */
__ALWAYS_STATIC_INLINE void __set_SSCRATCHCSWL(unsigned long sscratchcswl)
{
    rv_csr_write(CSR_SSCRATCHCSWL, sscratchcswl);
}

/**
  \brief        Enable a specific interrupt request
  \param [in]   IRQn    Interrupt number to enable
 */
__ALWAYS_STATIC_INLINE void csi_clic_enable_irq(uint32_t IRQn)
{
#if CLIC_SPEC_VERSION_010
    uint32_t bit;
    __set_MISELECT(CLIC_INTIE_OFFSET(IRQn));
    bit = (__get_MIREG2() | CLIC_IP_IE_BIT(IRQn));
    __set_MIREG2(bit);
#else
    CLIC->CLICINT[IRQn].IE |= CLIC_INTIE_IE_Msk;
#endif
}

/**
  \brief        Disable a specific interrupt request
  \param [in]   IRQn    Interrupt number to disable
 */
__ALWAYS_STATIC_INLINE void csi_clic_disable_irq(uint32_t IRQn)
{
#if CLIC_SPEC_VERSION_010
    uint32_t bit;
    __set_MISELECT(CLIC_INTIE_OFFSET(IRQn));
    bit = __get_MIREG2() & (~CLIC_IP_IE_BIT(IRQn));
    __set_MIREG2(bit);
#else
    CLIC->CLICINT[IRQn].IE &= ~CLIC_INTIE_IE_Msk;
#endif
}

/**
  \brief        Get the enabled status of a specific interrupt request
  \param [in]   IRQn    Interrupt number to check
  \return               1 if interrupt is enabled, 0 otherwise
 */
__ALWAYS_STATIC_INLINE uint32_t csi_clic_get_enabled_irq(uint32_t IRQn)
{
#if CLIC_SPEC_VERSION_010
    uint32_t val;
    __set_MISELECT(CLIC_INTIE_OFFSET(IRQn));
    val = __get_MIREG2() & CLIC_IP_IE_BIT(IRQn);
    return val;
#else
    return (uint32_t)(CLIC->CLICINT[IRQn].IE & CLIC_INTIE_IE_Msk);
#endif
}

/**
  \brief        Get the pending status of a specific interrupt request
  \param [in]   IRQn    Interrupt number to check
  \return               1 if interrupt is pending, 0 otherwise
 */
__ALWAYS_STATIC_INLINE uint32_t csi_clic_get_pending_irq(uint32_t IRQn)
{
#if CLIC_SPEC_VERSION_010
    __set_MISELECT(CLIC_INTIP_OFFSET(IRQn));
    return (__get_MIREG() & CLIC_IP_IE_BIT(IRQn));
#else
    return (uint32_t)(CLIC->CLICINT[IRQn].IP & CLIC_INTIP_IP_Msk);
#endif
}

/**
  \brief        Set a specific interrupt as pending
  \param [in]   IRQn    Interrupt number to set as pending
 */
__ALWAYS_STATIC_INLINE void csi_clic_set_pending_irq(uint32_t IRQn)
{
#if CLIC_SPEC_VERSION_010
    __set_MISELECT(CLIC_INTIP_OFFSET(IRQn));
    uint32_t ip = __get_MIREG() | CLIC_IP_IE_BIT(IRQn);
    __set_MIREG(ip);
#else
    CLIC->CLICINT[IRQn].IP |= CLIC_INTIP_IP_Msk;
#endif
}

/**
  \brief        Clear the pending status of a specific interrupt
  \param [in]   IRQn    Interrupt number to clear
 */
__ALWAYS_STATIC_INLINE void csi_clic_clear_pending_irq(uint32_t IRQn)
{
#if CLIC_SPEC_VERSION_010
    uint8_t ip_val;
    /* clear pending bit */
    __set_MISELECT(CLIC_INTIP_OFFSET(IRQn));
    ip_val = __get_MIREG() & (~CLIC_INTIP_IP_Msk);
    __set_MIREG(ip_val);
#else
    CLIC->CLICINT[IRQn].IP &= ~CLIC_INTIP_IP_Msk;
#endif
}

/**
  \brief        Set the priority level for a specific interrupt
  \param [in]   IRQn        Interrupt number to configure
  \param [in]   priority    Priority level to assign
 */
__ALWAYS_STATIC_INLINE void csi_clic_set_prio(uint32_t IRQn, uint32_t priority)
{
#if CLIC_SPEC_VERSION_010
    uint8_t nlbits;

    /* get mnlbits */
    __set_MISELECT(CLIC_MCLICCFG_OFFSET);
    nlbits = __get_MIREG() & 0xF;

    /* set priority */
    /* four 8-bits registers are packed into a 32-bit csr */
    int byte_index = IRQn % 4;
    clic_intctl_t intctl;
    __set_MISELECT(CLIC_INTCTL_OFFSET(IRQn));
    intctl.word = __get_MIREG();
    intctl.byte[byte_index] = (priority << (8 - nlbits));
    __set_MIREG(intctl.word);
#else
    uint8_t nlbits = (CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
    uint8_t ctl = CLIC->CLICINT[IRQn].CTL;
    ctl <<= nlbits;
    ctl >>= nlbits;
    CLIC->CLICINT[IRQn].CTL = ctl | (priority << (8 - nlbits));
#endif
}

/**
  \brief        Get the priority level of a specific interrupt
  \param [in]   IRQn    Interrupt number to query
  \return               Current priority level of the interrupt
 */
__ALWAYS_STATIC_INLINE uint32_t csi_clic_get_prio(uint32_t IRQn)
{
#if CLIC_SPEC_VERSION_010
    uint8_t nlbits;

    /* get mnlbits */
    __set_MISELECT(CLIC_MCLICCFG_OFFSET);
    nlbits = __get_MIREG() & 0xF;

    /* get priority */
    /* four 8-bits registers are packed into a 32-bit csr */
    int byte_index = IRQn % 4;
    clic_intctl_t intctl;
    __set_MISELECT(CLIC_INTCTL_OFFSET(IRQn));
    intctl.word = __get_MIREG();
    return intctl.byte[byte_index] >> (8 - nlbits);
#else
    uint8_t nlbits = (CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
    return CLIC->CLICINT[IRQn].CTL >> (8 - nlbits);
#endif
}

/**
  \brief        Get the interrupt attributes for a specific interrupt
  \param [in]   IRQn    Interrupt number to query
  \return               Interrupt attribute value (8-bit value containing trig and shv fields)
 */
__ALWAYS_STATIC_INLINE uint8_t csi_clic_get_intattr(uint32_t IRQn)
{
#if CLIC_SPEC_VERSION_010
    /* four 8-bit registers are packed into a 32-bit csr */
    int byte_index = IRQn % 4;
    clic_intattr_t intattr;

    __set_MISELECT(CLIC_INTATTR_OFFSET(IRQn));
    intattr.word = __get_MIREG2();
    return intattr.byte[byte_index];
#else
    return CLIC->CLICINT[IRQn].ATTR;
#endif
}

/**
  \brief        Set the interrupt attributes for a specific interrupt
  \param [in]   IRQn    Interrupt number to configure
  \param [in]   attr    Interrupt attribute value containing:
                        - bit[0]: shv (selective hardware vectoring)
                        - bit[2:1]: trig (trigger type: 00=positive level, 01=positive edge,
                                         10=negative level, 11=negative edge)
                        - bit[7:3]: reserved (write 0)
 */
__ALWAYS_STATIC_INLINE void csi_clic_set_intattr(uint32_t IRQn, uint8_t attr)
{
#if CLIC_SPEC_VERSION_010
    /* four 8-bit registers are packed into a 32-bit csr */
    int byte_index = IRQn % 4;
    clic_intattr_t intattr;

    __set_MISELECT(CLIC_INTATTR_OFFSET(IRQn));
    intattr.word = __get_MIREG2();
    intattr.byte[byte_index] = attr;
    __set_MIREG2(intattr.word);
#else
    CLIC->CLICINT[IRQn].ATTR = attr;
#endif
}

/**
  \brief        Set the trigger type for a specific interrupt
  \param [in]   IRQn    Interrupt number to configure
  \param [in]   trig    Trigger type (0=pos level, 1=pos edge, 2=neg level, 3=neg edge)
 */
__ALWAYS_STATIC_INLINE void csi_clic_set_trig(uint32_t IRQn, uint8_t trig)
{
    uint8_t attr = csi_clic_get_intattr(IRQn);
    attr = (attr & ~CLIC_INTATTR_TRIG_Msk) | ((trig & 0x3) << CLIC_INTATTR_TRIG_Pos);
    csi_clic_set_intattr(IRQn, attr);
}

/**
  \brief        Get the trigger type for a specific interrupt
  \param [in]   IRQn    Interrupt number to query
  \return               Trigger type (0=pos level, 1=pos edge, 2=neg level, 3=neg edge)
 */
__ALWAYS_STATIC_INLINE uint8_t csi_clic_get_trig(uint32_t IRQn)
{
    uint8_t attr = csi_clic_get_intattr(IRQn);
    return (attr & CLIC_INTATTR_TRIG_Msk) >> CLIC_INTATTR_TRIG_Pos;
}

/**
  \brief        Set selective hardware vectoring for a specific interrupt
  \param [in]   IRQn    Interrupt number to configure
  \param [in]   shv     1 to enable hardware vectoring, 0 for software vectoring
 */
__ALWAYS_STATIC_INLINE void csi_clic_set_shv(uint32_t IRQn, uint8_t shv)
{
    uint8_t attr = csi_clic_get_intattr(IRQn);
    attr = (attr & ~CLIC_INTATTR_SHV_Msk) | ((shv & 0x1) << CLIC_INTATTR_SHV_Pos);
    csi_clic_set_intattr(IRQn, attr);
}

/**
  \brief        Get selective hardware vectoring status for a specific interrupt
  \param [in]   IRQn    Interrupt number to query
  \return               1 if hardware vectoring is enabled, 0 otherwise
 */
__ALWAYS_STATIC_INLINE uint8_t csi_clic_get_shv(uint32_t IRQn)
{
    uint8_t attr = csi_clic_get_intattr(IRQn);
    return (attr & CLIC_INTATTR_SHV_Msk) >> CLIC_INTATTR_SHV_Pos;
}

/**
  \brief        Get the privilege mode for a specific interrupt
  \param [in]   IRQn    Interrupt number to query
  \return               Privilege mode (0=U-mode, 1=S-mode, 3=M-mode)
 */
__ALWAYS_STATIC_INLINE uint8_t csi_clic_get_mode(uint32_t IRQn)
{
    uint8_t attr = csi_clic_get_intattr(IRQn);
    return (attr >> CLIC_INTATTR_MODE_Pos) & CLIC_INTATTR_MODE_Msk;  // mode is in bits[7:6]
}

/**
  \brief        Set the privilege mode for a specific interrupt
  \param [in]   IRQn    Interrupt number to configure
  \param [in]   mode    Privilege mode to set:
                        - 0: U-mode (user mode)
                        - 1: S-mode (supervisor mode)
                        - 3: M-mode (machine mode)
  \note         Mode value 2 is reserved
 */
__ALWAYS_STATIC_INLINE void csi_clic_set_mode(uint32_t IRQn, uint8_t mode)
{
    uint8_t attr = csi_clic_get_intattr(IRQn);
    attr = (attr & 0x3F) | ((mode & CLIC_INTATTR_MODE_Msk) << CLIC_INTATTR_MODE_Pos);  // Clear bits[7:6] and set new mode
    csi_clic_set_intattr(IRQn, attr);
}

#endif
