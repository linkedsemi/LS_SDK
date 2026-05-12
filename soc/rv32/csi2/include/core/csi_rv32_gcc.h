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


/******************************************************************************
 * @file     csi_rv32_gcc.h
 * @brief    CSI Header File for GCC.
 * @version  V1.0
 * @date     01. Sep 2018
 ******************************************************************************/

#ifndef _CSI_RV32_GCC_H_
#define _CSI_RV32_GCC_H_

#include <core/csi_rv_common.h>

#if CONFIG_CPU_XUANTIE_E906 || CONFIG_CPU_XUANTIE_E906F || CONFIG_CPU_XUANTIE_E906FD || CONFIG_CPU_XUANTIE_E906P || CONFIG_CPU_XUANTIE_E906FP || CONFIG_CPU_XUANTIE_E906FDP \
    || CONFIG_CPU_XUANTIE_E907 || CONFIG_CPU_XUANTIE_E907F || CONFIG_CPU_XUANTIE_E907FD || CONFIG_CPU_XUANTIE_E907P || CONFIG_CPU_XUANTIE_E907FP || CONFIG_CPU_XUANTIE_E907FDP \
    || CONFIG_CPU_XUANTIE_E902 || CONFIG_CPU_XUANTIE_E902M \
    || CONFIG_CPU_XUANTIE_E901PLUS_CP || CONFIG_CPU_XUANTIE_E901PLUS_B_CP || CONFIG_CPU_XUANTIE_E901PLUS_M_CP || CONFIG_CPU_XUANTIE_E901PLUS_BM_CP \
    || CONFIG_CPU_XUANTIE_E901_CP || CONFIG_CPU_XUANTIE_E901_B_CP || CONFIG_CPU_XUANTIE_E901_ZM_CP || CONFIG_CPU_XUANTIE_E901_BZM_CP
#define CONFIG_CPU_XUANTIE_E9XX    1
#endif

#if CONFIG_CPU_XUANTIE_C907_RV32 || CONFIG_CPU_XUANTIE_C907FD_RV32 || CONFIG_CPU_XUANTIE_C907FDV_RV32 || CONFIG_CPU_XUANTIE_C907FDVM_RV32
#define CBO_INSN_SUPPORT 1
#endif

#if CONFIG_INTC_CLIC_APLIC
#ifndef CONFIG_APLIC_IRQ_OFFSET
#define APLIC_IRQ_OFFSET 255U
#else
#define APLIC_IRQ_OFFSET CONFIG_INTC_CLIC_APLIC
#endif
#endif /* CONFIG_INTC_CLIC_APLIC */

/* ###########################  Core Function Access  ########################### */
/** \ingroup  CSI_Core_FunctionInterface
    \defgroup CSI_Core_RegAccFunctions CSI Core Register Access Functions
  @{
 */

/**
  \brief   Get CPU WORK MODE
  \details Returns CPU WORK MODE.
  \return  CPU WORK MODE
 */
__ALWAYS_STATIC_INLINE unsigned long __get_CPU_WORK_MODE(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, sxstatus" : "=r"(result));
    return ((result >> 30U) & 0x3U);
}

/**
  \brief   Enable CoreTimer(within clint) Interrupts
 */
__ALWAYS_STATIC_INLINE void __enable_coret_irq(void)
{
#if CONFIG_INTC_PLIC || CONFIG_INTC_APLIC
#if CONFIG_RISCV_SMODE
    __ASM volatile(
        "li a0, 0x20\n\t"
        "csrs sie, a0\n\t"
        :                    /* No output */
        :                    /* No input */
        : "a0"               /* Declare that a0 register is modified */
    );
#else
    __ASM volatile(
        "li a0, 0x80\n\t"
        "csrs mie, a0\n\t"
        :                    /* No output */
        :                    /* No input */
        : "a0"               /* Declare that a0 register is modified */
    );
#endif
#endif /* CONFIG_INTC_PLIC || CONFIG_INTC_APLIC */
}

/**
  \brief   Disable CoreTimer(within clint) Interrupts
 */
__ALWAYS_STATIC_INLINE void __disable_coret_irq(void)
{
#if CONFIG_RISCV_SMODE
    __ASM volatile(
        "li a0, 0x20\n\t"
        "csrc sie, a0\n\t"
        :                    /* No output */
        :                    /* No input */
        : "a0"               /* Declare that a0 register is modified */
    );
#else
    __ASM volatile(
        "li a0, 0x80\n\t"
        "csrc mie, a0\n\t"
        :                    /* No output */
        :                    /* No input */
        : "a0"               /* Declare that a0 register is modified */
    );
#endif
}

/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by setting the IE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __enable_irq(void)
{
#if CONFIG_RISCV_SMODE
    __ASM volatile(
        "csrs sstatus, 2\n\t" /* Set sstatus.SIE to enable global interrupts */
        "li a0, 0x222\n\t"    /* Load interrupt enable mask to temporary register */
        "csrs sie, a0"        /* Set sie register to enable three types of interrupts */
        :                     /* No output */
        :                     /* No input */
        : "a0"                /* Declare that a0 register is modified */
    );
#else
    __ASM volatile(
        "csrs mstatus, 8\n\t" /* Set mstatus.MIE to enable global interrupts */
        "li a0, 0x888\n\t"    /* Load interrupt enable mask to temporary register */
        "csrs mie, a0"        /* Set mie register to enable three types of interrupts */
        :                     /* No output */
        :                     /* No input */
        : "a0"                /* Declare that a0 register is modified */
    );
#endif
}

/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by clearing the IE-bit in the PSR.
  Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __disable_irq(void)
{
#if CONFIG_RISCV_SMODE
    __ASM volatile("csrc sstatus, 2");
#else
    __ASM volatile("csrc mstatus, 8");
#endif
}

/**
  \brief   Get MXSTATUS
  \details Returns the content of the MXSTATUS Register.
  \return               MXSTATUS Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MXSTATUS(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mxstatus" : "=r"(result));
    return (result);
}

/**
  \brief   Set MXSTATUS
  \details Writes the given value to the MXSTATUS Register.
  \param [in]    MXSTATUS Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MXSTATUS(unsigned long mxstatus)
{
    __ASM volatile("csrw mxstatus, %0" : : "r"(mxstatus));
}

/**
  \brief   Get MEXSTATUS
  \details Returns the content of the MEXSTATUS Register.
  \return               MEXSTATUS Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MEXSTATUS(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mexstatus" : "=r"(result));
    return (result);
}

/**
  \brief   Set MEXSTATUS
  \details Writes the given value to the MSTATUS Register.
  \param [in]    MEXSTATUS Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MEXSTATUS(unsigned long mexstatus)
{
    __ASM volatile("csrw mexstatus, %0" : : "r"(mexstatus));
}


/**
  \brief   Get MRADDR
  \details Returns the content of the MRADDR Register.
  \return               MRADDR Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MRADDR(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mraddr" : "=r"(result));
    return (result);
}

/**
  \brief   Get FXCR
  \details Returns the content of the FXCR Register.
  \return               FXCR Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_FXCR(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, fxcr" : "=r"(result));
    return (result);
}


/**
  \brief   Set FXCR
  \details Writes the given value to the FXCR Register.
  \param [in]     FXCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_FXCR(unsigned long fxcr)
{
    __ASM volatile("csrw fxcr, %0" : : "r"(fxcr));
}

/**
  \brief   Get MSTATUS
  \details Returns the content of the MSTATUS Register.
  \return               MSTATUS Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MSTATUS(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mstatus" : "=r"(result));
    return (result);
}

/**
  \brief   Set MSTATUS
  \details Writes the given value to the MSTATUS Register.
  \param [in]    mstatus  MSTATUS Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSTATUS(unsigned long mstatus)
{
    __ASM volatile("csrw mstatus, %0" : : "r"(mstatus));
}

/**
  \brief   Get MHCR
  \details Returns the content of the MHCR Register.
  \return               MHCR Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MHCR(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mhcr" : "=r"(result));
    return (result);
}

/**
  \brief   Set MHCR
  \details Writes the given value to the MHCR Register.
  \param [in]           MHCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MHCR(unsigned long mhcr)
{
    __ASM volatile("csrw mhcr, %0" : : "r"(mhcr));
}

/**
  \brief   Get MCER
  \details Returns the current value of the MCER.
  \return               MCER Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MCER(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, mcer" : "=r"(result));
    return (result);
}

/**
  \brief   Get MCERH
  \details Returns the current value of the MCERH.
  \return               MCERH Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MCERH(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, mcerh" : "=r"(result));
    return (result);
}

/**
  \brief   Set MCERH
  \details Assigns the given value to the MCERH.
  \param [in]    mcerh  MCERH value to set
  */
__ALWAYS_STATIC_INLINE void __set_MCERH(unsigned long mcerh)
{
    __ASM volatile("csrw mcerh, %0" : : "r"(mcerh));
}

/**
  \brief   Get MCCR2
  \details Returns the content of the MCCR2 Register.
  \return               MCCR2 Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCCR2(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mccr2" : "=r"(result));
    return (result);
}

/**
  \brief   Set MCCR2
  \details Writes the given value to the MCCR2 Register.
  \param [in]    mstatus  MCCR2 Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCCR2(unsigned long mccr2)
{
    __ASM volatile("csrw mccr2, %0" : : "r"(mccr2));
}


/**
  \brief   Get MCER2
  \details Returns the current value of the MCER2.
  \return               MCER2 Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MCER2(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, mcer2" : "=r"(result));
    return (result);
}

/**
  \brief   Set MCCR2h
  \details Writes the given value to the MCCR2h Register.
  \param [in]    mstatus  MCCR2 Register value to set
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCER2H(void)
{
    register unsigned long result;
    __ASM volatile("csrr %0, mcer2h" : "=r"(result));
    return (result);
}

/**
  \brief   Set MCER
  \details Assigns the given value to the MCER.
  \param [in]    mcer  MCER value to set
  */
__ALWAYS_STATIC_INLINE void __set_MCER(unsigned long mcer)
{
    __ASM volatile("csrw mcer, %0" : : "r"(mcer));
}

/**
  \brief   Set MCER2
  \details Assigns the given value to the MCER2.
  \param [in]    mcer2  MCER2 value to set
  */
__ALWAYS_STATIC_INLINE void __set_MCER2(unsigned long mcer2)
{
    __ASM volatile("csrw mcer2, %0" : : "r"(mcer2));
}

/**
  \brief   Set MCER2H
  \details Assigns the given value to the MCER2H.
  \param [in]    mcer2h  MCER2H value to set
  */
__ALWAYS_STATIC_INLINE void __set_MCER2H(unsigned long mcer2h)
{
    __ASM volatile("csrw mcer2h, %0" : : "r"(mcer2h));
}

/**
  \brief   Get MHINT
  \details Returns the content of the MHINT Register.
  \return               MHINT Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MHINT(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mhint" : "=r"(result));
    return (result);
}

/**
  \brief   Set MHINT
  \details Writes the given value to the MHINT Register.
  \param [in]           MHINT Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MHINT(unsigned long mhint)
{
    __ASM volatile("csrw mhint, %0" : : "r"(mhint));
}

/**
  \brief   Get MISA Register
  \details Returns the content of the MISA Register.
  \return               MISA Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MISA(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, misa" : "=r"(result));
    return (result);
}

/**
  \brief   Set MISA
  \details Writes the given value to the MISA Register.
  \param [in]    misa  MISA Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MISA(unsigned long misa)
{
    __ASM volatile("csrw misa, %0" : : "r"(misa));
}

/**
  \brief   Get MIE Register
  \details Returns the content of the MIE Register.
  \return               MIE Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MIE(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mie" : "=r"(result));
    return (result);
}

/**
  \brief   Set MIE
  \details Writes the given value to the MIE Register.
  \param [in]    mie  MIE Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MIE(unsigned long mie)
{
    __ASM volatile("csrw mie, %0" : : "r"(mie));
}

/**
  \brief   Get MTVEC Register
  \details Returns the content of the MTVEC Register.
  \return               MTVEC Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MTVEC(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mtvec" : "=r"(result));
    return (result);
}

/**
  \brief   Set MTVEC
  \details Writes the given value to the MTVEC Register.
  \param [in]    mtvec  MTVEC Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MTVEC(unsigned long mtvec)
{
    __ASM volatile("csrw mtvec, %0" : : "r"(mtvec));
}

/**
  \brief   Set STVAC Register
  \details Writes the given value to the STVEC Register.
 */
__ALWAYS_STATIC_INLINE void __set_STVEC(unsigned long x)
{
    __ASM volatile("csrw stvec, %0"::"r"(x));
}

/**
  \brief   Get STVEC Register
  \details Returns the content of the MTVEC Register.
  \return               MTVEC Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_STVEC(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, stvec" : "=r"(result));
    return (result);
}

/**
  \brief   Get MTIME
  \details Returns the content of the MTIME Register.
  \return               MTIME Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MTIME(void)
{
    unsigned long result;
    __ASM volatile("rdtime %0" : "=r"(result));
    return (result);
}

/**
  \brief   Get MTIMEH
  \details Returns the content of the MTIME Register.
  \return               MTIME Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MTIMEH(void)
{
    unsigned long result;
    __ASM volatile("rdtimeh %0" : "=r"(result));
    return (result);
}

/**
  \brief   Get SP
  \details Returns the content of the SP Register.
  \return               SP Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SP(void)
{
    unsigned long result;

    __ASM volatile("mv %0, sp" : "=r"(result));
    return (result);
}

/**
  \brief   Set SP
  \details Writes the given value to the SP Register.
  \param [in]    sp  SP Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SP(unsigned long sp)
{
    __ASM volatile("mv sp, %0" : : "r"(sp): "sp");
}

/**
  \brief   Get MSCRATCH Register
  \details Returns the content of the MSCRATCH Register.
  \return               MSCRATCH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MSCRATCH(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mscratch" : "=r"(result));
    return (result);
}

/**
  \brief   Set MSCRATCH
  \details Writes the given value to the MSCRATCH Register.
  \param [in]    mscratch  MSCRATCH Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MSCRATCH(unsigned long mscratch)
{
    __ASM volatile("csrw mscratch, %0" : : "r"(mscratch));
}

/**
  \brief   Get SSCRATCH Register
  \details Returns the content of the SSCRATCH Register.
  \return               SSCRATCH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SSCRATCH(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, sscratch" : "=r"(result));
    return (result);
}

/**
  \brief   Set SSCRATCH
  \details Writes the given value to the SSCRATCH Register.
  \param [in]    sscratch  SSCRATCH Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SSCRATCH(unsigned long sscratch)
{
    __ASM volatile("csrw sscratch, %0" : : "r"(sscratch));
}

/**
  \brief   Get MEPC Register
  \details Returns the content of the MEPC Register.
  \return               MEPC Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MEPC(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mepc" : "=r"(result));
    return (result);
}

/**
  \brief   Set MEPC
  \details Writes the given value to the MEPC Register.
  \param [in]    mepc  MEPC Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MEPC(unsigned long mepc)
{
    __ASM volatile("csrw mepc, %0" : : "r"(mepc));
}

/**
  \brief   Set SEPC
  \details Writes the given value to the SEPC Register.
  \param [in]    sepc  SEPC Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_SEPC(unsigned long sepc)
{
    __ASM volatile("csrw sepc, %0" : : "r"(sepc));
}

/**
  \brief   Get SEPC
  \details Returns the content of the SEPC Register.
  \return               SEPC Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SEPC(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, sepc" : "=r"(result));
    return (result);
}

/**
  \brief   Get MCAUSE Register
  \details Returns the content of the MCAUSE Register.
  \return               MCAUSE Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCAUSE(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mcause" : "=r"(result));
    return (result);
}

/**
  \brief   Get SCAUSE Register
  \details Returns the content of the SCAUSE Register.
  \return               SCAUSE Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SCAUSE(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, scause" : "=r"(result));
    return (result);
}

/**
  \brief   Get MTVAL Register
  \details Returns the content of the MTVAL Register.
  \return               MTVAL Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MTVAL(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mtval" : "=r"(result));
    return (result);
}

/**
  \brief   Get MIP Register
  \details Returns the content of the MIP Register.
  \return               MIP Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MIP(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mip" : "=r"(result));
    return (result);
}

/**
  \brief   Set MIP
  \details Writes the given value to the MIP Register.
  \param [in]    mip  MIP Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MIP(unsigned long mip)
{
    __ASM volatile("csrw mip, %0" : : "r"(mip));
}

/**
  \brief   Get MCYCLEL Register
  \details Returns the content of the MCYCLEL Register.
  \return               MCYCLE Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCYCLE(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mcycle" : "=r"(result));
    return (result);
}

/**
  \brief         Set MCYCLE
  \details       Write MCYCLE Register
  \param [in]    value  MCYCLE Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MCYCLE(unsigned long value)
{
    __ASM volatile("csrw mcycle, %0" : : "r"(value));
}

/**
  \brief   Get MCYCLEH Register
  \details Returns the content of the MCYCLEH Register.
  \return               MCYCLEH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCYCLEH(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mcycleh" : "=r"(result));
    return (result);
}

/**
  \brief         Set MCYCLEH
  \details       Write MCYCLEH Register
  \param [in]    value  MCYCLEH Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MCYCLEH(unsigned long value)
{
    __ASM volatile("csrw mcycleh, %0" : : "r"(value));
}

/**
  \brief   Get MINSTRET Register
  \details Returns the content of the MINSTRET Register.
  \return               MINSTRET Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MINSTRET(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, minstret" : "=r"(result));
    return (result);
}

/**
  \brief   Set MINSTRET
  \details Write MINSTRET Register
  \param [in]    value  MINSTRET Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MINSTRET(unsigned long value)
{
    __ASM volatile("csrw minstret, %0" : : "r"(value));
}

/**
  \brief   Get MINSTRETH Register
  \details Returns the content of the MINSTRETH Register.
  \return               MINSTRETH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MINSTRETH(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, minstreth" : "=r"(result));
    return (result);
}

/**
  \brief   Set MINSTRETH
  \details Write MINSTRETH Register
  \param [in]    value  MINSTRETH Register value to set
  */
__ALWAYS_STATIC_INLINE void __set_MINSTRETH(unsigned long value)
{
    __ASM volatile("csrw minstreth, %0" : : "r"(value));
}

#if (CONFIG_CPU_XUANTIE_E907 || CONFIG_CPU_XUANTIE_E907F || CONFIG_CPU_XUANTIE_E907FD || CONFIG_CPU_XUANTIE_E907P || CONFIG_CPU_XUANTIE_E907FP || CONFIG_CPU_XUANTIE_E907FDP)
/**
  \brief   Get MEICR2
  \details Returns the current value of the MEICR2.
  \return               MEICR2 Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MEICR2(void)
{
    register unsigned long result;

    __ASM volatile("csrr %0, meicr2" : "=r"(result));
    return (result);
}

/**
  \brief   Set MEICR2
  \details Assigns the given value to the MEICR2.
  \param [in]    errinjcr  MEICR2 value to set
  */
__ALWAYS_STATIC_INLINE void __set_MEICR2(unsigned long meicr2)
{
    __ASM volatile("csrw meicr2, %0" : : "r"(meicr2));
}

/**
  \brief   Get MEICR
  \details Returns the current value of the MEICR.
  \return               MEICR Register value
  */
__ALWAYS_STATIC_INLINE unsigned long __get_MEICR(void)
{
    register unsigned long result;

    __ASM volatile("csrr %0, meicr" : "=r"(result));
    return (result);
}

/**
  \brief   Set MEICR
  \details Assigns the given value to the MEICR.
  \param [in]    errinjcr  MEICR value to set
  */
__ALWAYS_STATIC_INLINE void __set_MEICR(unsigned long meicr)
{
    __ASM volatile("csrw meicr, %0" : : "r"(meicr));
}

/**
 \brief   Get MITCMCR
 \details Returns the content of the MITCMCR Register.
 \return               MITCMCR Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MITCMCR(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, mitcmcr" : "=r"(result));

    return (result);
}

/**
 \brief   Set MITCMCR
 \details Writes the given value to the MITCMCR Register.
 \param [in]    itcmcr  MITCMCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MITCMCR(unsigned long mitcmcr)
{
    __ASM volatile("csrw mitcmcr, %0" : : "r"(mitcmcr));
}

/**
 \brief   Get MDTCMCR
 \details Returns the content of the MDTCMCR Register.
 \return               MDTCMCR Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MDTCMCR(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, mdtcmcr" : "=r"(result));
    return (result);
}

/**
 \brief   Set MDTCMCR
 \details Writes the given value to the MDTCMCR Register.
 \param [in]    dtcmcr  MDTCMCR Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MDTCMCR(unsigned long mdtcmcr)
{
    __ASM volatile("csrw mdtcmcr, %0" : : "r"(mdtcmcr));
}
#endif /* end e907xx */

/**
  \brief   Get MVENDORID Register
  \details Returns the content of the MVENDROID Register.
  \return               MVENDORID Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MVENDORID(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mvendorid" : "=r"(result));
    return (result);
}

/**
  \brief   Get MARCHID Register
  \details Returns the content of the MARCHID Register.
  \return               MARCHID Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MARCHID(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, marchid" : "=r"(result));
    return (result);
}

/**
  \brief   Get MIMPID Register
  \details Returns the content of the MIMPID Register.
  \return               MIMPID Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MIMPID(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mimpid" : "=r"(result));
    return (result);
}

/**
  \brief   Get MCOUNTEREN
  \details Returns the content of the MCOUNTEREN Register.
  \return               MCOUNTEREN Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCOUNTEREN(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mcounteren" : "=r"(result));
    return (result);
}

/**
  \brief   Set MCOUNTEREN
  \details Writes the given value to the MCOUNTEREN Register.
  \param [in]    mcounteren  MCOUNTEREN Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCOUNTEREN(uint32_t mcounteren)
{
    __ASM volatile("csrw mcounteren, %0" : : "r"(mcounteren));
}

/**
  \brief   Get MCOUNTERWEN
  \details Returns the content of the MCOUNTERWEN Register.
  \return               MCOUNTERWEN Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MCOUNTERWEN(void)
{
    uint32_t result;

    __ASM volatile("csrr %0, mcounterwen" : "=r"(result));
    return (result);
}

/**
  \brief   Set MCOUNTERWEN
  \details Writes the given value to the MCOUNTERWEN Register.
  \param [in]    mcounterwen  MCOUNTERWEN Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MCOUNTERWEN(uint32_t mcounterwen)
{
    __ASM volatile("csrw mcounterwen, %0" : : "r"(mcounterwen));
}

/**
  \brief   Set MEDELEG Register
  \details Writes the given value to the MEDELEG Register.
 */
__ALWAYS_STATIC_INLINE void __set_MEDELEG(unsigned long x)
{
    __ASM volatile("csrw medeleg, %0"::"r"(x));
}

/**
  \brief   Set MEDELEG Register
  \details Writes the given value to the MEDELEG Register.
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MEDELEG(void)
{
    unsigned long x;
    __ASM volatile("csrr %0, medeleg":"=r"(x));
    return x;
}

/**
  \brief   Set MIDELEG Register
  \details Writes the given value to the MIDELEG Register.
 */
__ALWAYS_STATIC_INLINE void __set_MIDELEG(unsigned long x)
{
    __ASM volatile("csrw mideleg, %0"::"r"(x));
}

/**
  \brief   Get MIDELEG Register
  \details Returns the content of the MIDELEG Register.
  \return               MIDELEG Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MIDELEG(void)
{
    unsigned long x;
    __ASM volatile("csrr %0, mideleg":"=r"(x));
    return x;
}

/**
  \brief   Set SSTATUS Register
  \details Writes the given value to the SSTATUS Register.
 */
__ALWAYS_STATIC_INLINE void __set_SSTATUS(unsigned long x)
{
    __ASM volatile("csrw sstatus, %0"::"r"(x));
}

/**
  \brief   Get SSTATUS Register
  \details Returns the content of the SSTATUS Register.
  \return               SSTATUS Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SSTATUS(void)
{
    unsigned long x;
    __ASM volatile("csrr %0, sstatus":"=r"(x));
    return x;
}

/**
  \brief   Set SXSTATUS Register
  \details Writes the given value to the SXSTATUS Register.
 */
__ALWAYS_STATIC_INLINE void __set_SXSTATUS(unsigned long x)
{
    __ASM volatile("csrw sxstatus, %0"::"r"(x));
}

/**
  \brief   Get SXSTATUS Register
  \details Returns the content of the SXSTATUS Register.
  \return               SXSTATUS Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SXSTATUS(void)
{
    unsigned long x;
    __ASM volatile("csrr %0, sxstatus":"=r"(x));
    return x;
}

/**
  \brief   Get MENVCFGH
  \details Returns the content of the MENVCFGH Register.
  \return               MENVCFGH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MENVCFGH(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, menvcfgh" : "=r"(result));
    return (result);
}

/**
  \brief   Set MENVCFGH
  \details Writes the given value to the MENVCFGH Register.
  \param [in]    menvcfgh  MENVCFGH Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MENVCFGH(unsigned long menvcfgh)
{
    __ASM volatile("csrw menvcfgh, %0" : : "r"(menvcfgh));
}

/**
  \brief   Get MENVCFG
  \details Returns the content of the MENVCFG Register.
  \return               MENVCFG Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MENVCFG(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, menvcfg" : "=r"(result));
    return (result);
}

/**
  \brief   Set MENVCFG
  \details Writes the given value to the MENVCFG Register.
  \param [in]    menvcfg  MENVCFG Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MENVCFG(unsigned long menvcfg)
{
    __ASM volatile("csrw menvcfg, %0" : : "r"(menvcfg));
}

/**
  \brief   Set SIE Register
  \details Writes the given value to the SIE Register.
 */
__ALWAYS_STATIC_INLINE void __set_SIE(unsigned long x)
{
    __ASM volatile("csrw sie, %0"::"r"(x));
}

/**
  \brief   Get SIE Register
  \details Returns the content of the SIE Register.
  \return               SIE Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SIE(void)
{
    unsigned long x;
    __ASM volatile("csrr %0, sie":"=r"(x));
    return x;
}

/**
  \brief   Set SIP Register
  \details Writes the given value to the SIP Register.
 */
__ALWAYS_STATIC_INLINE void __set_SIP(unsigned long x)
{
    __ASM volatile("csrw sip, %0"::"r"(x));
}

/**
  \brief   Get SIP Register
  \details Returns the content of the SIP Register.
  \return               SIP Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_SIP(void)
{
    unsigned long x;
    __ASM volatile("csrr %0, sip":"=r"(x));
    return x;
}

/**
  \brief   Get MHARTID Register
  \details Returns the content of the MHARTID Register.
  \return               MHARTID Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MHARTID(void)
{
    unsigned long result;

    __ASM volatile("csrr %0, mhartid" : "=r"(result));
    return (result);
}

/**
  \brief   Set MERRINJ
  \details Writes the given value to the MERRINJ Register.
  \param [in]    merrinj  MERRINJ Register value to set
 */
__ALWAYS_STATIC_INLINE void __set_MERRINJ(unsigned long merrinj)
{
    __ASM volatile("csrw merrinj, %0" : : "r"(merrinj));
}

/**
  \brief   Get MERRINJ by index
  \details Read the given value to the MERRINJ Register.
  \return               MERRINJ Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MERRINJ(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, merrinj" : "=r"(result));
    return result;
}

/**
  \brief   Set STIMECMP
  \details Writes the given value to the STIMECMP Register.
 */
__ALWAYS_STATIC_INLINE void __set_STIMECMP(uint32_t value)
{
    __ASM volatile("csrw stimecmp, %0" : : "r"(value));
}

/**
  \brief   Get STIMECMP
  \details Read the given value to the STIMECMP Register.
  \return               STIMECMP Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_STIMECMP(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, stimecmp" : "=r"(result));
    return result;
}

/**
  \brief   Set STIMECMPH
  \details Writes the given value to the STIMECMPH Register.
 */
__ALWAYS_STATIC_INLINE void __set_STIMECMPH(uint32_t value)
{
    __ASM volatile("csrw stimecmph, %0" : : "r"(value));
}

/**
  \brief   Get STIMECMPH
  \details Read the given value to the STIMECMPH Register.
  \return               STIMECMPH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_STIMECMPH(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, stimecmph" : "=r"(result));
    return result;
}

/**
  \brief   Set MVMID
  \details Writes the given value to the MVMID Register.
 */
__ALWAYS_STATIC_INLINE void __set_MVMID(uint32_t value)
{
    __ASM volatile("csrw mvmid, %0" : : "r"(value));
}

/**
  \brief   Get MVMID
  \details Read the given value to the MVMID Register.
  \return               MVMID Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MVMID(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, mvmid" : "=r"(result));
    return result;
}

/**
  \brief   Set MTIMEDELTA
  \details Writes the given value to the MTIMEDELTA Register.
 */
__ALWAYS_STATIC_INLINE void __set_MTIMEDELTA(uint32_t value)
{
    __ASM volatile("csrw mtimedelta, %0" : : "r"(value));
}

/**
  \brief   Get MTIMEDELTA
  \details Read the given value to the MTIMEDELTA Register.
  \return               MTIMEDELTA Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MTIMEDELTA(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, mtimedelta" : "=r"(result));
    return result;
}

/**
  \brief   Set MTIMEDELTAH
  \details Writes the given value to the MTIMEDELTAH Register.
 */
__ALWAYS_STATIC_INLINE void __set_MTIMEDELTAH(uint32_t value)
{
    __ASM volatile("csrw mtimedeltah, %0" : : "r"(value));
}

/**
  \brief   Get MTIMEDELTAH
  \details Read the given value to the MTIMEDELTAH Register.
  \return               MTIMEDELTAH Register value
 */
__ALWAYS_STATIC_INLINE unsigned long __get_MTIMEDELTAH(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, mtimedeltah" : "=r"(result));
    return result;
}

/**
  \brief   Enable interrupts and exceptions
  \details Enables interrupts and exceptions by setting the IE-bit and EE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __enable_excp_irq(void)
{
    __enable_irq();
}

/**
  \brief   Disable interrupts and exceptions
  \details Disables interrupts and exceptions by clearing the IE-bit and EE-bit in the PSR.
           Can only be executed in Privileged modes.
 */
__ALWAYS_STATIC_INLINE void __disable_excp_irq(void)
{
    __disable_irq();
}

#define __CSI_GCC_OUT_REG(r) "=r" (r)
#define __CSI_GCC_USE_REG(r) "r" (r)

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
__ALWAYS_STATIC_INLINE void __NOP(void)
{
    __ASM volatile("nop");
}


/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
__ALWAYS_STATIC_INLINE void __WFI(void)
{
    __ASM volatile("wfi");
}

/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __WAIT(void)
{
    __ASM volatile("wfi");
}

/**
  \brief   Doze For Interrupt
  \details Doze For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __DOZE(void)
{
    __ASM volatile("wfi");
}

/**
  \brief   Stop For Interrupt
  \details Stop For Interrupt is a hint instruction that suspends execution until one interrupt occurs.
 */
__ALWAYS_STATIC_INLINE void __STOP(void)
{
    __ASM volatile("wfi");
}

/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__ALWAYS_STATIC_INLINE void __ISB(void)
{
    __ASM volatile("fence.i");
    __ASM volatile("fence r, r");
}


/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__ALWAYS_STATIC_INLINE void __DSB(void)
{
    __ASM volatile("fence iorw, iorw");
#if __riscv_xtheadsync
    __ASM volatile("sync");
#endif
}

/**
  \brief   Invalid all icache
  \details invalid all icache.
 */
__ALWAYS_STATIC_INLINE void __ICACHE_IALL(void)
{
#if __riscv_xtheadcmo
    __ASM volatile("icache.iall");
#endif
}

/**
  \brief   Invalid Icache by addr
  \details Invalid Icache by addr.
  \param [in] addr  operate addr
 */
__ALWAYS_STATIC_INLINE void __ICACHE_IPA(unsigned long addr)
{
#if __riscv_xtheadcmo
    __ASM volatile("icache.ipa %0" : : "r"(addr));
#endif
}

/**
  \brief   Invalid all dcache
  \details invalid all dcache.
 */
__ALWAYS_STATIC_INLINE void __DCACHE_IALL(void)
{
#if __riscv_xtheadcmo
    __ASM volatile("dcache.iall");
#endif
}

/**
  \brief   Clear all dcache
  \details clear all dcache.
 */
__ALWAYS_STATIC_INLINE void __DCACHE_CALL(void)
{
#if __riscv_xtheadcmo
    __ASM volatile("dcache.call");
#endif
}

/**
  \brief   Clear&invalid all dcache
  \details clear & invalid all dcache.
 */
__ALWAYS_STATIC_INLINE void __DCACHE_CIALL(void)
{
#if __riscv_xtheadcmo
    __ASM volatile("dcache.ciall");
#endif
}

/**
  \brief   Invalid Dcache by addr
  \details Invalid Dcache by addr.
  \param [in] addr  operate addr
 */
__ALWAYS_STATIC_INLINE void __DCACHE_IPA(unsigned long addr)
{
#if __riscv_xtheadcmo
    __ASM volatile("dcache.ipa %0" : : "r"(addr));
#endif
}

/**
  \brief   Clear Dcache by addr
  \details Clear Dcache by addr.
  \param [in] addr  operate addr
 */
__ALWAYS_STATIC_INLINE void __DCACHE_CPA(unsigned long addr)
{
#if __riscv_xtheadcmo
    __ASM volatile("dcache.cpa %0" : : "r"(addr));
#endif
}

/**
  \brief   Clear & Invalid Dcache by addr
  \details Clear & Invalid Dcache by addr.
  \param [in] addr  operate addr
 */
__ALWAYS_STATIC_INLINE void __DCACHE_CIPA(unsigned long addr)
{
#if __riscv_xtheadcmo
    __ASM volatile("dcache.cipa %0" : : "r"(addr));
#endif
}


/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__ALWAYS_STATIC_INLINE void __DMB(void)
{
    __ASM volatile("fence");
}

/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in integer value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE unsigned long __REV(unsigned long value)
{
    return __builtin_bswap32(value);
}


/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order in two unsigned short values.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE unsigned long __REV16(unsigned long value)
{
    unsigned long result;

    result = ((value & 0xFF000000) >> 8) | ((value & 0x00FF0000) << 8) |
             ((value & 0x0000FF00) >> 8) | ((value & 0x000000FF) << 8);

    return (result);
}


/**
  \brief   Reverse byte order in signed short value
  \details Reverses the byte order in a signed short value with sign extension to integer.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE int32_t __REVSH(int32_t value)
{
    return (short)(((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8));
}


/**
  \brief   Rotate Right in unsigned value (32 bit)
  \details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
__ALWAYS_STATIC_INLINE unsigned long __ROR(unsigned long op1, unsigned long op2)
{
    return (op1 >> op2) | (op1 << (32U - op2));
}


/**
  \brief   Breakpoint
  \details Causes the processor to enter Debug state
           Debug tools can use this to investigate system state when the instruction at a particular address is reached.
 */
__ALWAYS_STATIC_INLINE void __BKPT(void)
{
    __ASM volatile("ebreak");
}

/**
  \brief   Reverse bit order of value
  \details Reverses the bit order of the given value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__ALWAYS_STATIC_INLINE unsigned long __RBIT(unsigned long value)
{
    unsigned long result;

    int32_t s = 4 /*sizeof(v)*/ * 8 - 1; /* extra shift needed at end */

    result = value;                      /* r will be reversed bits of v; first get LSB of v */

    for (value >>= 1U; value; value >>= 1U) {
        result <<= 1U;
        result |= value & 1U;
        s--;
    }

    result <<= s;                        /* shift when v's highest bits are zero */

    return (result);
}


/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
#define __CLZ             __builtin_clz
/**
  \details This function saturates a signed value.
  \param [in]    x   Value to be saturated
  \param [in]    y   Bit position to saturate to [1..32]
  \return            Saturated value.
 */
__ALWAYS_STATIC_INLINE int32_t __SSAT(int32_t x, unsigned long y)
{
    int32_t posMax, negMin;
    unsigned long i;

    posMax = 1;

    for (i = 0; i < (y - 1); i++) {
        posMax = posMax * 2;
    }

    if (x > 0) {
        posMax = (posMax - 1);

        if (x > posMax) {
            x = posMax;
        }

//    x &= (posMax * 2 + 1);
    } else {
        negMin = -posMax;

        if (x < negMin) {
            x = negMin;
        }

//    x &= (posMax * 2 - 1);
    }

    return (x);
}

/**
  \brief   Unsigned Saturate
  \details Saturates an unsigned value.
  \param [in]  value  Value to be saturated
  \param [in]    sat  Bit position to saturate to (0..31)
  \return             Saturated value
 */
__ALWAYS_STATIC_INLINE unsigned long __USAT(unsigned long value, unsigned long sat)
{
    unsigned long result;

    if ((((0xFFFFFFFF >> sat) << sat) & value) != 0) {
        result = 0xFFFFFFFF >> (32 - sat);
    } else {
        result = value;
    }

    return (result);
}

/**
  \brief   Unsigned Saturate for internal use
  \details Saturates an unsigned value, should not call directly.
  \param [in]  value  Value to be saturated
  \param [in]    sat  Bit position to saturate to (0..31)
  \return             Saturated value
 */
__ALWAYS_STATIC_INLINE unsigned long __IUSAT(unsigned long value, unsigned long sat)
{
    unsigned long result;

    if (value & 0x80000000) { /* only overflow set bit-31 */
        result = 0;
    } else if ((((0xFFFFFFFF >> sat) << sat) & value) != 0) {
        result = 0xFFFFFFFF >> (32 - sat);
    } else {
        result = value;
    }

    return (result);
}

/**
  \brief   Rotate Right with Extend
  \details This function moves each bit of a bitstring right by one bit.
           The carry input is shifted in at the left end of the bitstring.
  \note    carry input will always 0.
  \param [in]    op1  Value to rotate
  \return               Rotated value
 */
__ALWAYS_STATIC_INLINE unsigned long __RRX(unsigned long op1)
{
    return 0;
}

/**
  \brief   LDRT Unprivileged (8 bit)
  \details Executes a Unprivileged LDRT instruction for 8 bit value.
  \param [in]    addr  Pointer to location
  \return             value of type uint8_t at (*ptr)
 */
__ALWAYS_STATIC_INLINE uint8_t __LDRBT(volatile uint8_t *addr)
{
    unsigned long result;

    __ASM volatile("lb %0, 0(%1)" : "=r"(result) : "r"(addr));

    return ((uint8_t) result);    /* Add explicit type cast here */
}


/**
  \brief   LDRT Unprivileged (16 bit)
  \details Executes a Unprivileged LDRT instruction for 16 bit values.
  \param [in]    addr  Pointer to location
  \return        value of type uint16_t at (*ptr)
 */
__ALWAYS_STATIC_INLINE uint16_t __LDRHT(volatile uint16_t *addr)
{
    unsigned long result;

    __ASM volatile("lh %0, 0(%1)" : "=r"(result) : "r"(addr));

    return ((uint16_t) result);    /* Add explicit type cast here */
}


/**
  \brief   LDRT Unprivileged (32 bit)
  \details Executes a Unprivileged LDRT instruction for 32 bit values.
  \param [in]    addr  Pointer to location
  \return        value of type unsigned long at (*ptr)
 */
__ALWAYS_STATIC_INLINE unsigned long __LDRT(volatile unsigned long *addr)
{
    unsigned long result;

    __ASM volatile("lw %0, 0(%1)" : "=r"(result) : "r"(addr));

    return (result);
}


/**
  \brief   STRT Unprivileged (8 bit)
  \details Executes a Unprivileged STRT instruction for 8 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRBT(uint8_t value, volatile uint8_t *addr)
{
    __ASM volatile("sb %1, 0(%0)" :: "r"(addr), "r"((unsigned long)value) : "memory");
}


/**
  \brief   STRT Unprivileged (16 bit)
  \details Executes a Unprivileged STRT instruction for 16 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRHT(uint16_t value, volatile uint16_t *addr)
{
    __ASM volatile("sh %1, 0(%0)" :: "r"(addr), "r"((unsigned long)value) : "memory");
}


/**
  \brief   STRT Unprivileged (32 bit)
  \details Executes a Unprivileged STRT instruction for 32 bit values.
  \param [in]  value  Value to store
  \param [in]    addr  Pointer to location
 */
__ALWAYS_STATIC_INLINE void __STRT(unsigned long value, volatile unsigned long *addr)
{
    __ASM volatile("sw %1, 0(%0)" :: "r"(addr), "r"(value) : "memory");
}

/*@}*/ /* end of group CSI_Core_InstructionInterface */

/* ###################  Compiler specific Intrinsics  ########################### */
/** \defgroup CSI_SIMD_intrinsics CSI SIMD Intrinsics
  Access to dedicated SIMD instructions \n
  Single Instruction Multiple Data (SIMD) extensions are provided to simplify development of application software. SIMD extensions increase the processing capability without materially increasing the power consumption. The SIMD extensions are completely transparent to the operating system (OS), allowing existing OS ports to be used.

  @{
*/

/**
  \brief   Halfword packing instruction. Combines bits[15:0] of val1 with bits[31:16]
           of val2 levitated with the val3.
  \details Combine a halfword from one register with a halfword from another register.
           The second argument can be left-shifted before extraction of the halfword.
  \param [in]    val1   first 16-bit operands
  \param [in]    val2   second 16-bit operands
  \param [in]    val3   value for left-shifting val2. Value range [0..31].
  \return               the combination of halfwords.
  \remark
                 res[15:0]  = val1[15:0]              \n
                 res[31:16] = val2[31:16] << val3
 */
__ALWAYS_STATIC_INLINE unsigned long __PKHBT(unsigned long val1, unsigned long val2, unsigned long val3)
{
    return ((((int32_t)(val1) << 0) & (int32_t)0x0000FFFF) | (((int32_t)(val2) << val3) & (int32_t)0xFFFF0000));
}

/**
  \brief   Halfword packing instruction. Combines bits[31:16] of val1 with bits[15:0]
           of val2 right-shifted with the val3.
  \details Combine a halfword from one register with a halfword from another register.
           The second argument can be right-shifted before extraction of the halfword.
  \param [in]    val1   first 16-bit operands
  \param [in]    val2   second 16-bit operands
  \param [in]    val3   value for right-shifting val2. Value range [1..32].
  \return               the combination of halfwords.
  \remark
                 res[15:0]  = val2[15:0] >> val3        \n
                 res[31:16] = val1[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __PKHTB(unsigned long val1, unsigned long val2, unsigned long val3)
{
    return ((((int32_t)(val1) << 0) & (int32_t)0xFFFF0000) | (((int32_t)(val2) >> val3) & (int32_t)0x0000FFFF));
}

/**
  \brief   Dual 16-bit signed saturate.
  \details This function saturates a signed value.
  \param [in]    x   two signed 16-bit values to be saturated.
  \param [in]    y   bit position for saturation, an integral constant expression in the range 1 to 16.
  \return        the sum of the absolute differences of the following bytes, added to the accumulation value:\n
                 the signed saturation of the low halfword in val1, saturated to the bit position specified in
                 val2 and returned in the low halfword of the return value.\n
                 the signed saturation of the high halfword in val1, saturated to the bit position specified in
                 val2 and returned in the high halfword of the return value.
 */
__ALWAYS_STATIC_INLINE unsigned long __SSAT16(int32_t x, const unsigned long y)
{
    int32_t r = 0, s = 0;

    r = __SSAT((((int32_t)x << 16) >> 16), y) & (int32_t)0x0000FFFF;
    s = __SSAT((((int32_t)x) >> 16), y) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturate.
  \details This function enables you to saturate two signed 16-bit values to a selected unsigned range.
  \param [in]    x   two signed 16-bit values to be saturated.
  \param [in]    y   bit position for saturation, an integral constant expression in the range 1 to 16.
  \return        the saturation of the two signed 16-bit values, as non-negative values:
                 the saturation of the low halfword in val1, saturated to the bit position specified in
                 val2 and returned in the low halfword of the return value.\n
                 the saturation of the high halfword in val1, saturated to the bit position specified in
                 val2 and returned in the high halfword of the return value.
 */
__ALWAYS_STATIC_INLINE unsigned long __USAT16(unsigned long x, const unsigned long y)
{
    int32_t r = 0, s = 0;

    r = __IUSAT(((x << 16) >> 16), y) & 0x0000FFFF;
    s = __IUSAT(((x) >> 16), y) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit saturating addition.
  \details This function enables you to perform four 8-bit integer additions,
           saturating the results to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the saturated addition of the first byte of each operand in the first byte of the return value.\n
                 the saturated addition of the second byte of each operand in the second byte of the return value.\n
                 the saturated addition of the third byte of each operand in the third byte of the return value.\n
                 the saturated addition of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE unsigned long __QADD8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = __SSAT(((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((int32_t)x) >> 24) + (((int32_t)y) >> 24)), 8) & (int32_t)0x000000FF;

    return ((unsigned long)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned saturating addition.
  \details This function enables you to perform four unsigned 8-bit integer additions,
           saturating the results to the 8-bit unsigned integer range 0 < x < 2^8 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the saturated addition of the first byte of each operand in the first byte of the return value.\n
                 the saturated addition of the second byte of each operand in the second byte of the return value.\n
                 the saturated addition of the third byte of each operand in the third byte of the return value.\n
                 the saturated addition of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range 0 <= x <= 2^8 - 1.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE unsigned long __UQADD8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = __IUSAT((((x << 24) >> 24) + ((y << 24) >> 24)), 8) & 0x000000FF;
    s = __IUSAT((((x << 16) >> 24) + ((y << 16) >> 24)), 8) & 0x000000FF;
    t = __IUSAT((((x <<  8) >> 24) + ((y <<  8) >> 24)), 8) & 0x000000FF;
    u = __IUSAT((((x) >> 24) + ((y) >> 24)), 8) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit signed addition.
  \details This function performs four 8-bit signed integer additions.
  \param [in]    x  first four 8-bit summands.
  \param [in]    y  second four 8-bit summands.
  \return        the addition of the first bytes from each operand, in the first byte of the return value.\n
                 the addition of the second bytes of each operand, in the second byte of the return value.\n
                 the addition of the third bytes of each operand, in the third byte of the return value.\n
                 the addition of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE unsigned long __SADD8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = ((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)) & (int32_t)0x000000FF;
    s = ((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)) & (int32_t)0x000000FF;
    t = ((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)) & (int32_t)0x000000FF;
    u = ((((int32_t)x) >> 24) + (((int32_t)y) >> 24)) & (int32_t)0x000000FF;

    return ((unsigned long)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned addition.
  \details This function performs four unsigned 8-bit integer additions.
  \param [in]    x  first four 8-bit summands.
  \param [in]    y  second four 8-bit summands.
  \return        the addition of the first bytes from each operand, in the first byte of the return value.\n
                 the addition of the second bytes of each operand, in the second byte of the return value.\n
                 the addition of the third bytes of each operand, in the third byte of the return value.\n
                 the addition of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   + val2[7:0]        \n
                 res[15:8]  = val1[15:8]  + val2[15:8]       \n
                 res[23:16] = val1[23:16] + val2[23:16]      \n
                 res[31:24] = val1[31:24] + val2[31:24]
 */
__ALWAYS_STATIC_INLINE unsigned long __UADD8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) + ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) + ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) + ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) + ((y) >> 24)) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit saturating subtract.
  \details This function enables you to perform four 8-bit integer subtractions,
           saturating the results to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the subtraction of the first byte of each operand in the first byte of the return value.\n
                 the subtraction of the second byte of each operand in the second byte of the return value.\n
                 the subtraction of the third byte of each operand in the third byte of the return value.\n
                 the subtraction of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit signed integer range -2^7 <= x <= 2^7 - 1.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE unsigned long __QSUB8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = __SSAT(((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((int32_t)x) >> 24) - (((int32_t)y) >> 24)), 8) & (int32_t)0x000000FF;

    return ((unsigned long)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned saturating subtraction.
  \details This function enables you to perform four unsigned 8-bit integer subtractions,
           saturating the results to the 8-bit unsigned integer range 0 < x < 2^8 - 1.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the subtraction of the first byte of each operand in the first byte of the return value.\n
                 the subtraction of the second byte of each operand in the second byte of the return value.\n
                 the subtraction of the third byte of each operand in the third byte of the return value.\n
                 the subtraction of the fourth byte of each operand in the fourth byte of the return value.\n
                 The returned results are saturated to the 8-bit unsigned integer range 0 <= x <= 2^8 - 1.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE unsigned long __UQSUB8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = __IUSAT((((x << 24) >> 24) - ((y << 24) >> 24)), 8) & 0x000000FF;
    s = __IUSAT((((x << 16) >> 24) - ((y << 16) >> 24)), 8) & 0x000000FF;
    t = __IUSAT((((x <<  8) >> 24) - ((y <<  8) >> 24)), 8) & 0x000000FF;
    u = __IUSAT((((x) >> 24) - ((y) >> 24)), 8) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Quad 8-bit signed subtraction.
  \details This function enables you to perform four 8-bit signed integer subtractions.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE unsigned long __SSUB8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = ((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)) & (int32_t)0x000000FF;
    s = ((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)) & (int32_t)0x000000FF;
    t = ((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)) & (int32_t)0x000000FF;
    u = ((((int32_t)x) >> 24) - (((int32_t)y) >> 24)) & (int32_t)0x000000FF;

    return ((unsigned long)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned subtract.
  \details This function enables you to perform four 8-bit unsigned integer subtractions.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = val1[7:0]   - val2[7:0]        \n
                 res[15:8]  = val1[15:8]  - val2[15:8]       \n
                 res[23:16] = val1[23:16] - val2[23:16]      \n
                 res[31:24] = val1[31:24] - val2[31:24]
 */
__ALWAYS_STATIC_INLINE unsigned long __USUB8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) - ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) - ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) - ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) - ((y) >> 24)) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Unsigned sum of quad 8-bit unsigned absolute difference.
  \details This function enables you to perform four unsigned 8-bit subtractions, and add the absolute values
           of the differences together, returning the result as a single unsigned integer.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \return        the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.\n
                 The sum is returned as a single unsigned integer.
  \remark
                 absdiff1   = val1[7:0]   - val2[7:0]        \n
                 absdiff2   = val1[15:8]  - val2[15:8]       \n
                 absdiff3   = val1[23:16] - val2[23:16]      \n
                 absdiff4   = val1[31:24] - val2[31:24]      \n
                 res[31:0]  = absdiff1 + absdiff2 + absdiff3 + absdiff4
 */
__ALWAYS_STATIC_INLINE unsigned long __USAD8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = (((x << 24) >> 24) - ((y << 24) >> 24)) & 0x000000FF;
    s = (((x << 16) >> 24) - ((y << 16) >> 24)) & 0x000000FF;
    t = (((x <<  8) >> 24) - ((y <<  8) >> 24)) & 0x000000FF;
    u = (((x) >> 24) - ((y) >> 24)) & 0x000000FF;

    return (u + t + s + r);
}

#if 0
/**
  \brief   Unsigned sum of quad 8-bit unsigned absolute difference with 32-bit accumulate.
  \details This function enables you to perform four unsigned 8-bit subtractions, and add the absolute values
           of the differences to a 32-bit accumulate operand.
  \param [in]    x  first four 8-bit operands of each subtraction.
  \param [in]    y  second four 8-bit operands of each subtraction.
  \param [in]  sum  accumulation value.
  \return        the sum of the absolute differences of the following bytes, added to the accumulation value:
                 the subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the subtraction of the second bytes of each operand, in the second byte of the return value.\n
                 the subtraction of the third bytes of each operand, in the third byte of the return value.\n
                 the subtraction of the fourth bytes of each operand, in the fourth byte of the return value.
  \remark
                 absdiff1 = val1[7:0]   - val2[7:0]        \n
                 absdiff2 = val1[15:8]  - val2[15:8]       \n
                 absdiff3 = val1[23:16] - val2[23:16]      \n
                 absdiff4 = val1[31:24] - val2[31:24]      \n
                 sum = absdiff1 + absdiff2 + absdiff3 + absdiff4 \n
                 res[31:0] = sum[31:0] + val3[31:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __USADA8(unsigned long x, unsigned long y, unsigned long sum)
{
    int32_t r, s, t, u;

#ifdef __cplusplus
    r = (abs((long long)((x << 24) >> 24) - ((y << 24) >> 24))) & 0x000000FF;
    s = (abs((long long)((x << 16) >> 24) - ((y << 16) >> 24))) & 0x000000FF;
    t = (abs((long long)((x <<  8) >> 24) - ((y <<  8) >> 24))) & 0x000000FF;
    u = (abs((long long)((x) >> 24) - ((y) >> 24))) & 0x000000FF;
#else
    r = (abs(((x << 24) >> 24) - ((y << 24) >> 24))) & 0x000000FF;
    s = (abs(((x << 16) >> 24) - ((y << 16) >> 24))) & 0x000000FF;
    t = (abs(((x <<  8) >> 24) - ((y <<  8) >> 24))) & 0x000000FF;
    u = (abs(((x) >> 24) - ((y) >> 24))) & 0x000000FF;
#endif
    return (u + t + s + r + sum);
}
#endif

/**
  \brief   Dual 16-bit saturating addition.
  \details This function enables you to perform two 16-bit integer arithmetic additions in parallel,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated addition of the low halfwords, in the low halfword of the return value.\n
                 the saturated addition of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __QADD16(unsigned long x, unsigned long y)
{
    int32_t r = 0, s = 0;

    r = __SSAT(((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) + (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating addition.
  \details This function enables you to perform two unsigned 16-bit integer additions, saturating
           the results to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated addition of the low halfwords, in the low halfword of the return value.\n
                 the saturated addition of the high halfwords, in the high halfword of the return value.\n
                 The results are saturated to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __UQADD16(unsigned long x, unsigned long y)
{
    int32_t r = 0, s = 0;

    r = __IUSAT((((x << 16) >> 16) + ((y << 16) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) + ((y) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed addition.
  \details This function enables you to perform two 16-bit signed integer additions.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the addition of the low halfwords in the low halfword of the return value.\n
                 the addition of the high halfwords in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __SADD16(unsigned long x, unsigned long y)
{
    int32_t r = 0, s = 0;

    r = ((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) + (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition
  \details This function enables you to perform two 16-bit unsigned integer additions.
  \param [in]    x   first two 16-bit summands for each addition.
  \param [in]    y   second two 16-bit summands for each addition.
  \return        the addition of the low halfwords in the low halfword of the return value.\n
                 the addition of the high halfwords in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  + val2[15:0]        \n
                 res[31:16] = val1[31:16] + val2[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __UADD16(unsigned long x, unsigned long y)
{
    int32_t r = 0, s = 0;

    r = (((x << 16) >> 16) + ((y << 16) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) + ((y) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}


/**
  \brief   Dual 16-bit signed addition with halved results.
  \details This function enables you to perform two signed 16-bit integer additions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved addition of the low halfwords, in the low halfword of the return value.\n
                 the halved addition of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __SHADD16(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) + (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) + (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition with halved results.
  \details This function enables you to perform two unsigned 16-bit integer additions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved addition of the low halfwords, in the low halfword of the return value.\n
                 the halved addition of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __UHADD16(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) + ((y << 16) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) + ((y) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit signed addition with halved results.
  \details This function enables you to perform four signed 8-bit integer additions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved addition of the first bytes from each operand, in the first byte of the return value.\n
                 the halved addition of the second bytes from each operand, in the second byte of the return value.\n
                 the halved addition of the third bytes from each operand, in the third byte of the return value.\n
                 the halved addition of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   + val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  + val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] + val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] + val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __SHADD8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = (((((int32_t)x << 24) >> 24) + (((int32_t)y << 24) >> 24)) >> 1) & (int32_t)0x000000FF;
    s = (((((int32_t)x << 16) >> 24) + (((int32_t)y << 16) >> 24)) >> 1) & (int32_t)0x000000FF;
    t = (((((int32_t)x <<  8) >> 24) + (((int32_t)y <<  8) >> 24)) >> 1) & (int32_t)0x000000FF;
    u = (((((int32_t)x) >> 24) + (((int32_t)y) >> 24)) >> 1) & (int32_t)0x000000FF;

    return ((unsigned long)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned addition with halved results.
  \details This function enables you to perform four unsigned 8-bit integer additions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved addition of the first bytes from each operand, in the first byte of the return value.\n
                 the halved addition of the second bytes from each operand, in the second byte of the return value.\n
                 the halved addition of the third bytes from each operand, in the third byte of the return value.\n
                 the halved addition of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   + val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  + val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] + val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] + val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __UHADD8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = ((((x << 24) >> 24) + ((y << 24) >> 24)) >> 1) & 0x000000FF;
    s = ((((x << 16) >> 24) + ((y << 16) >> 24)) >> 1) & 0x000000FF;
    t = ((((x <<  8) >> 24) + ((y <<  8) >> 24)) >> 1) & 0x000000FF;
    u = ((((x) >> 24) + ((y) >> 24)) >> 1) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Dual 16-bit saturating subtract.
  \details This function enables you to perform two 16-bit integer subtractions in parallel,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the saturated subtraction of the low halfwords, in the low halfword of the return value.\n
                 the saturated subtraction of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __QSUB16(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) - (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating subtraction.
  \details This function enables you to perform two unsigned 16-bit integer subtractions,
           saturating the results to the 16-bit unsigned integer range 0 < x < 2^16 - 1.
  \param [in]    x   first two 16-bit operands for each subtraction.
  \param [in]    y   second two 16-bit operands for each subtraction.
  \return        the saturated subtraction of the low halfwords, in the low halfword of the return value.\n
                 the saturated subtraction of the high halfwords, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __UQSUB16(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) - ((y << 16) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) - ((y) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction.
  \details This function enables you to perform two 16-bit signed integer subtractions.
  \param [in]    x   first two 16-bit operands of each subtraction.
  \param [in]    y   second two 16-bit operands of each subtraction.
  \return        the subtraction of the low halfword in the second operand from the low
                 halfword in the first operand, in the low halfword of the return value. \n
                 the subtraction of the high halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __SSUB16(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) - (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtract.
  \details This function enables you to perform two 16-bit unsigned integer subtractions.
  \param [in]    x   first two 16-bit operands of each subtraction.
  \param [in]    y   second two 16-bit operands of each subtraction.
  \return        the subtraction of the low halfword in the second operand from the low
                 halfword in the first operand, in the low halfword of the return value. \n
                 the subtraction of the high halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[15:0]        \n
                 res[31:16] = val1[31:16] - val2[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __USUB16(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) - ((y << 16) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) - ((y) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction with halved results.
  \details This function enables you to perform two signed 16-bit integer subtractions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved subtraction of the low halfwords, in the low halfword of the return value.\n
                 the halved subtraction of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __SHSUB16(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) - (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) - (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtraction with halved results.
  \details This function enables you to perform two unsigned 16-bit integer subtractions, halving the results.
  \param [in]    x   first two 16-bit summands.
  \param [in]    y   second two 16-bit summands.
  \return        the halved subtraction of the low halfwords, in the low halfword of the return value.\n
                 the halved subtraction of the high halfwords, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[15:0]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[31:16]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __UHSUB16(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) - ((y << 16) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) - ((y) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Quad 8-bit signed addition with halved results.
  \details This function enables you to perform four signed 8-bit integer subtractions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the halved subtraction of the second bytes from each operand, in the second byte of the return value.\n
                 the halved subtraction of the third bytes from each operand, in the third byte of the return value.\n
                 the halved subtraction of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   - val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  - val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] - val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] - val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __SHSUB8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = (((((int32_t)x << 24) >> 24) - (((int32_t)y << 24) >> 24)) >> 1) & (int32_t)0x000000FF;
    s = (((((int32_t)x << 16) >> 24) - (((int32_t)y << 16) >> 24)) >> 1) & (int32_t)0x000000FF;
    t = (((((int32_t)x <<  8) >> 24) - (((int32_t)y <<  8) >> 24)) >> 1) & (int32_t)0x000000FF;
    u = (((((int32_t)x) >> 24) - (((int32_t)y) >> 24)) >> 1) & (int32_t)0x000000FF;

    return ((unsigned long)((u << 24) | (t << 16) | (s <<  8) | (r)));
}

/**
  \brief   Quad 8-bit unsigned subtraction with halved results.
  \details This function enables you to perform four unsigned 8-bit integer subtractions, halving the results.
  \param [in]    x   first four 8-bit summands.
  \param [in]    y   second four 8-bit summands.
  \return        the halved subtraction of the first bytes from each operand, in the first byte of the return value.\n
                 the halved subtraction of the second bytes from each operand, in the second byte of the return value.\n
                 the halved subtraction of the third bytes from each operand, in the third byte of the return value.\n
                 the halved subtraction of the fourth bytes from each operand, in the fourth byte of the return value.
  \remark
                 res[7:0]   = (val1[7:0]   - val2[7:0]  ) >> 1    \n
                 res[15:8]  = (val1[15:8]  - val2[15:8] ) >> 1    \n
                 res[23:16] = (val1[23:16] - val2[23:16]) >> 1    \n
                 res[31:24] = (val1[31:24] - val2[31:24]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __UHSUB8(unsigned long x, unsigned long y)
{
    int32_t r, s, t, u;

    r = ((((x << 24) >> 24) - ((y << 24) >> 24)) >> 1) & 0x000000FF;
    s = ((((x << 16) >> 24) - ((y << 16) >> 24)) >> 1) & 0x000000FF;
    t = ((((x <<  8) >> 24) - ((y <<  8) >> 24)) >> 1) & 0x000000FF;
    u = ((((x) >> 24) - ((y) >> 24)) >> 1) & 0x000000FF;

    return ((u << 24) | (t << 16) | (s <<  8) | (r));
}

/**
  \brief   Dual 16-bit add and subtract with exchange.
  \details This function enables you to exchange the halfwords of the one operand,
           then add the high halfwords and subtract the low halfwords,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the saturated subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the saturated addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __QASX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating addition and subtraction with exchange.
  \details This function enables you to exchange the halfwords of the second operand and
           perform one unsigned 16-bit integer addition and one unsigned 16-bit subtraction,
           saturating the results to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the saturated subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the saturated addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __UQASX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) - ((y) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) + ((y << 16) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit addition and subtraction with exchange.
  \details It enables you to exchange the halfwords of the second operand, add the high halfwords
           and subtract the low halfwords.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __SASX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition and subtraction with exchange.
  \details This function enables you to exchange the two halfwords of the second operand,
           add the high halfwords and subtract the low halfwords.
  \param [in]    x   first operand for the subtraction in the low halfword,
                     and the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword,
                     and the second operand for the addition in the low halfword.
  \return        the subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the addition of the high halfword in the first operand and the
                 low halfword in the second operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = val1[15:0]  - val2[31:16]        \n
                 res[31:16] = val1[31:16] + val2[15:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __UASX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) - ((y) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) + ((y << 16) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed addition and subtraction with halved results.
  \details This function enables you to exchange the two halfwords of one operand, perform one
           signed 16-bit integer addition and one signed 16-bit subtraction, and halve the results.
  \param [in]    x   first 16-bit operands.
  \param [in]    y   second 16-bit operands.
  \return        the halved subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the halved addition of the low halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __SHASX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) - (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) + (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned addition and subtraction with halved results and exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           add the high halfwords and subtract the low halfwords, halving the results.
  \param [in]    x   first operand for the subtraction in the low halfword, and
                     the first operand for the addition in the high halfword.
  \param [in]    y   second operand for the subtraction in the high halfword, and
                     the second operand for the addition in the low halfword.
  \return        the halved subtraction of the high halfword in the second operand from the
                 low halfword in the first operand, in the low halfword of the return value.\n
                 the halved addition of the low halfword in the second operand from the high
                 halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  - val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] + val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __UHASX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) - ((y) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) + ((y << 16) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit subtract and add with exchange.
  \details This function enables you to exchange the halfwords of one operand,
           then subtract the high halfwords and add the low halfwords,
           saturating the results to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the saturated addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the saturated subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit signed integer range -2^15 <= x <= 2^15 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __QSAX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = __SSAT(((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned saturating subtraction and addition with exchange.
  \details This function enables you to exchange the halfwords of the second operand and perform
           one unsigned 16-bit integer subtraction and one unsigned 16-bit addition, saturating
           the results to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the saturated addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the saturated subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
                 The returned results are saturated to the 16-bit unsigned integer range 0 <= x <= 2^16 - 1.
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __UQSAX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = __IUSAT((((x << 16) >> 16) + ((y) >> 16)), 16) & 0x0000FFFF;
    s = __IUSAT((((x) >> 16) - ((y << 16) >> 16)), 16) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit unsigned subtract and add with exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           subtract the high halfwords and add the low halfwords.
  \param [in]    x   first operand for the addition in the low halfword,
                     and the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword,
                     and the second operand for the subtraction in the low halfword.
  \return        the addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __USAX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = (((x << 16) >> 16) + ((y) >> 16)) & 0x0000FFFF;
    s = (((x) >> 16) - ((y << 16) >> 16)) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed subtraction and addition with exchange.
  \details This function enables you to exchange the two halfwords of one operand and perform one
           16-bit integer subtraction and one 16-bit addition.
  \param [in]    x   first operand for the addition in the low halfword, and the first operand
                     for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword, and the second
                     operand for the subtraction in the low halfword.
  \return        the addition of the low halfword of the first operand and the high
                 halfword of the second operand, in the low halfword of the return value.\n
                 the subtraction of the low halfword of the second operand from the
                 high halfword of the first operand, in the high halfword of the return value.\n
  \remark
                 res[15:0]  = val1[15:0]  + val2[31:16]        \n
                 res[31:16] = val1[31:16] - val2[15:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __SSAX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = ((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)) & (int32_t)0x0000FFFF;
    s = ((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}


/**
  \brief   Dual 16-bit signed subtraction and addition with halved results.
  \details This function enables you to exchange the two halfwords of one operand, perform one signed
           16-bit integer subtraction and one signed 16-bit addition, and halve the results.
  \param [in]    x   first 16-bit operands.
  \param [in]    y   second 16-bit operands.
  \return        the halved addition of the low halfword in the first operand and the
                 high halfword in the second operand, in the low halfword of the return value.\n
                 the halved subtraction of the low halfword in the second operand from the
                 high halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __SHSAX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = (((((int32_t)x << 16) >> 16) + (((int32_t)y) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((int32_t)x) >> 16) - (((int32_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((unsigned long)((s << 16) | (r)));
}

/**
  \brief   Dual 16-bit unsigned subtraction and addition with halved results and exchange.
  \details This function enables you to exchange the halfwords of the second operand,
           subtract the high halfwords and add the low halfwords, halving the results.
  \param [in]    x   first operand for the addition in the low halfword, and
                     the first operand for the subtraction in the high halfword.
  \param [in]    y   second operand for the addition in the high halfword, and
                     the second operand for the subtraction in the low halfword.
  \return        the halved addition of the low halfword in the first operand and the
                 high halfword in the second operand, in the low halfword of the return value.\n
                 the halved subtraction of the low halfword in the second operand from the
                 high halfword in the first operand, in the high halfword of the return value.
  \remark
                 res[15:0]  = (val1[15:0]  + val2[31:16]) >> 1        \n
                 res[31:16] = (val1[31:16] - val2[15:0]) >> 1
 */
__ALWAYS_STATIC_INLINE unsigned long __UHSAX(unsigned long x, unsigned long y)
{
    int32_t r, s;

    r = ((((x << 16) >> 16) + ((y) >> 16)) >> 1) & 0x0000FFFF;
    s = ((((x) >> 16) - ((y << 16) >> 16)) >> 1) & 0x0000FFFF;

    return ((s << 16) | (r));
}

/**
  \brief   Dual 16-bit signed multiply with exchange returning difference.
  \details This function enables you to perform two 16-bit signed multiplications, subtracting
           one of the products from the other. The halfwords of the second operand are exchanged
           before performing the arithmetic. This produces top * bottom and bottom * top multiplication.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the difference of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[31:16]       \n
                 p2 = val1[31:16] * val2[15:0]        \n
                 res[31:0] = p1 - p2
 */
__ALWAYS_STATIC_INLINE unsigned long __SMUSDX(unsigned long x, unsigned long y)
{
    return ((unsigned long)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16))));
}

/**
  \brief   Sum of dual 16-bit signed multiply with exchange.
  \details This function enables you to perform two 16-bit signed multiplications with exchanged
           halfwords of the second operand, adding the products together.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the sum of the products of the two 16-bit signed multiplications with exchanged halfwords of the second operand.
  \remark
                 p1 = val1[15:0]  * val2[31:16]       \n
                 p2 = val1[31:16] * val2[15:0]        \n
                 res[31:0] = p1 + p2
 */
__ALWAYS_STATIC_INLINE unsigned long __SMUADX(unsigned long x, unsigned long y)
{
    return ((unsigned long)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16))));
}


/**
  \brief   Saturating add.
  \details This function enables you to obtain the saturating add of two integers.
  \param [in]    x   first summand of the saturating add operation.
  \param [in]    y   second summand of the saturating add operation.
  \return        the saturating addition of val1 and val2.
  \remark
                 res[31:0] = SAT(val1 + SAT(val2))
 */
__ALWAYS_STATIC_INLINE int32_t __QADD(int32_t x, int32_t y)
{
    int32_t result;

    if (y >= 0) {
        if ((int32_t)((unsigned long)x + (unsigned long)y) >= x) {
            result = x + y;
        } else {
            result = 0x7FFFFFFF;
        }
    } else {
        if ((int32_t)((unsigned long)x + (unsigned long)y) < x) {
            result = x + y;
        } else {
            result = 0x80000000;
        }
    }

    return result;
}

/**
  \brief   Saturating subtract.
  \details This function enables you to obtain the saturating add of two integers.
  \param [in]    x   first summand of the saturating add operation.
  \param [in]    y   second summand of the saturating add operation.
  \return        the saturating addition of val1 and val2.
  \remark
                 res[31:0] = SAT(val1 - SAT(val2))
 */
__ALWAYS_STATIC_INLINE int32_t __QSUB(int32_t x, int32_t y)
{
    int64_t tmp;
    int32_t result;

    tmp = (int64_t)x - (int64_t)y;

    if (tmp > 0x7fffffff) {
        tmp = 0x7fffffff;
    } else if (tmp < (-2147483647 - 1)) {
        tmp = -2147483647 - 1;
    }

    result = tmp;
    return result;
}

/**
  \brief   Dual 16-bit signed multiply with single 32-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications,
           adding both results to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value, as a 32-bit integer.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 + p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __SMLAD(unsigned long x, unsigned long y, unsigned long sum)
{
    return ((unsigned long)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Pre-exchanged dual 16-bit signed multiply with single 32-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications with exchanged
           halfwords of the second operand, adding both results to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication with exchanged halfwords of the second
                 operand added to the accumulate value, as a 32-bit integer.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 res[31:0] = p1 + p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __SMLADX(unsigned long x, unsigned long y, unsigned long sum)
{
    return ((unsigned long)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.
  \details This function enables you to perform two 16-bit signed multiplications, take the
           difference of the products, subtracting the high halfword product from the low
           halfword product, and add the difference to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]       \n
                 p2 = val1[31:16] * val2[31:16]      \n
                 res[31:0] = p1 - p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __SMLSD(unsigned long x, unsigned long y, unsigned long sum)
{
    return ((unsigned long)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 32-bit accumulate.
  \details This function enables you to exchange the halfwords in the second operand, then perform two 16-bit
           signed multiplications. The difference of the products is added to a 32-bit accumulate operand.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 res[31:0] = p1 - p2 + val3[31:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __SMLSDX(unsigned long x, unsigned long y, unsigned long sum)
{
    return ((unsigned long)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((int32_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with single 64-bit accumulator.
  \details This function enables you to perform two signed 16-bit multiplications, adding both results
           to a 64-bit accumulate operand. Overflow is only possible as a result of the 64-bit addition.
           This overflow is not detected if it occurs. Instead, the result wraps around modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 sum = p1 + p2 + val3[63:32][31:0]  \n
                 res[63:32] = sum[63:32]            \n
                 res[31:0]  = sum[31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLALD(unsigned long x, unsigned long y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange with single 64-bit accumulator.
  \details This function enables you to exchange the halfwords of the second operand, and perform two
           signed 16-bit multiplications, adding both results to a 64-bit accumulate operand. Overflow
           is only possible as a result of the 64-bit addition. This overflow is not detected if it occurs.
           Instead, the result wraps around modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of each multiplication added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]     \n
                 p2 = val1[31:16] * val2[15:0]      \n
                 sum = p1 + p2 + val3[63:32][31:0]  \n
                 res[63:32] = sum[63:32]            \n
                 res[31:0]  = sum[31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLALDX(unsigned long x, unsigned long y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   dual 16-bit signed multiply subtract with 64-bit accumulate.
  \details This function It enables you to perform two 16-bit signed multiplications, take the difference
           of the products, subtracting the high halfword product from the low halfword product, and add the
           difference to a 64-bit accumulate operand. Overflow cannot occur during the multiplications or the
           subtraction. Overflow can occur as a result of the 64-bit addition, and this overflow is not
           detected. Instead, the result wraps round to modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[63:32][31:0] = p1 - p2 + val3[63:32][31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLSLD(unsigned long x, unsigned long y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   Dual 16-bit signed multiply with exchange subtract with 64-bit accumulate.
  \details This function enables you to exchange the halfwords of the second operand, perform two 16-bit multiplications,
           adding the difference of the products to a 64-bit accumulate operand. Overflow cannot occur during the
           multiplications or the subtraction. Overflow can occur as a result of the 64-bit addition, and this overflow
           is not detected. Instead, the result wraps round to modulo2^64.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \param [in]  sum   accumulate value.
  \return        the difference of the product of each multiplication, added to the accumulate value.
  \remark
                 p1 = val1[15:0]  * val2[31:16]      \n
                 p2 = val1[31:16] * val2[15:0]       \n
                 res[63:32][31:0] = p1 - p2 + val3[63:32][31:0]
 */
__ALWAYS_STATIC_INLINE uint64_t __SMLSLDX(unsigned long x, unsigned long y, uint64_t sum)
{
    return ((uint64_t)(((((int32_t)x << 16) >> 16) * (((int32_t)y) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y << 16) >> 16)) +
                       (((uint64_t)sum))));
}

/**
  \brief   32-bit signed multiply with 32-bit truncated accumulator.
  \details This function enables you to perform a signed 32-bit multiplications, adding the most
           significant 32 bits of the 64-bit result to a 32-bit accumulate operand.
  \param [in]    x   first operand for multiplication.
  \param [in]    y   second operand for multiplication.
  \param [in]  sum   accumulate value.
  \return        the product of multiplication (most significant 32 bits) is added to the accumulate value, as a 32-bit integer.
  \remark
                 p = val1 * val2      \n
                 res[31:0] = p[63:32] + val3[31:0]
 */
__ALWAYS_STATIC_INLINE unsigned long __SMMLA(int32_t x, int32_t y, int32_t sum)
{
    return (unsigned long)((int32_t)((int64_t)((int64_t)x * (int64_t)y) >> 32) + sum);
}

/**
  \brief   Sum of dual 16-bit signed multiply.
  \details This function enables you to perform two 16-bit signed multiplications, adding the products together.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the sum of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 + p2
 */
__ALWAYS_STATIC_INLINE unsigned long __SMUAD(unsigned long x, unsigned long y)
{
    return ((unsigned long)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) +
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

/**
  \brief   Dual 16-bit signed multiply returning difference.
  \details This function enables you to perform two 16-bit signed multiplications, taking the difference
           of the products by subtracting the high halfword product from the low halfword product.
  \param [in]    x   first 16-bit operands for each multiplication.
  \param [in]    y   second 16-bit operands for each multiplication.
  \return        the difference of the products of the two 16-bit signed multiplications.
  \remark
                 p1 = val1[15:0]  * val2[15:0]      \n
                 p2 = val1[31:16] * val2[31:16]     \n
                 res[31:0] = p1 - p2
 */
__ALWAYS_STATIC_INLINE unsigned long __SMUSD(unsigned long x, unsigned long y)
{
    return ((unsigned long)(((((int32_t)x << 16) >> 16) * (((int32_t)y << 16) >> 16)) -
                       ((((int32_t)x) >> 16) * (((int32_t)y) >> 16))));
}

/**
  \brief   Dual extracted 8-bit to 16-bit signed addition.
  \details This function enables you to extract two 8-bit values from the second operand (at bit positions
           [7:0] and [23:16]), sign-extend them to 16-bits each, and add the results to the first operand.
  \param [in]    x   values added to the sign-extended to 16-bit values.
  \param [in]    y   two 8-bit values to be extracted and sign-extended.
  \return        the addition of val1 and val2, where the 8-bit values in val2[7:0] and
                 val2[23:16] have been extracted and sign-extended prior to the addition.
  \remark
                 res[15:0]  = val1[15:0] + SignExtended(val2[7:0])      \n
                 res[31:16] = val1[31:16] + SignExtended(val2[23:16])
 */
__ALWAYS_STATIC_INLINE unsigned long __SXTAB16(unsigned long x, unsigned long y)
{
    return ((unsigned long)((((((int32_t)y << 24) >> 24) + (((int32_t)x << 16) >> 16)) & (int32_t)0x0000FFFF) |
                       (((((int32_t)y <<  8) >>  8)  + (((int32_t)x >> 16) << 16)) & (int32_t)0xFFFF0000)));
}

/**
  \brief   Extracted 16-bit to 32-bit unsigned addition.
  \details This function enables you to extract two 8-bit values from one operand, zero-extend
           them to 16 bits each, and add the results to two 16-bit values from another operand.
  \param [in]    x   values added to the zero-extended to 16-bit values.
  \param [in]    y   two 8-bit values to be extracted and zero-extended.
  \return        the addition of val1 and val2, where the 8-bit values in val2[7:0] and
                 val2[23:16] have been extracted and zero-extended prior to the addition.
  \remark
                 res[15:0]  = ZeroExt(val2[7:0]   to 16 bits) + val1[15:0]      \n
                 res[31:16] = ZeroExt(val2[31:16] to 16 bits) + val1[31:16]
 */
__ALWAYS_STATIC_INLINE unsigned long __UXTAB16(unsigned long x, unsigned long y)
{
    return ((unsigned long)(((((y << 24) >> 24) + ((x << 16) >> 16)) & 0x0000FFFF) |
                       ((((y <<  8) >>  8) + ((x >> 16) << 16)) & 0xFFFF0000)));
}

/**
  \brief   Dual extract 8-bits and sign extend each to 16-bits.
  \details This function enables you to extract two 8-bit values from an operand and sign-extend them to 16 bits each.
  \param [in]    x   two 8-bit values in val[7:0] and val[23:16] to be sign-extended.
  \return        the 8-bit values sign-extended to 16-bit values.\n
                 sign-extended value of val[7:0] in the low halfword of the return value.\n
                 sign-extended value of val[23:16] in the high halfword of the return value.
  \remark
                 res[15:0]  = SignExtended(val[7:0])       \n
                 res[31:16] = SignExtended(val[23:16])
 */
__ALWAYS_STATIC_INLINE unsigned long __SXTB16(unsigned long x)
{
    return ((unsigned long)(((((int32_t)x << 24) >> 24) & (int32_t)0x0000FFFF) |
                       ((((int32_t)x <<  8) >>  8) & (int32_t)0xFFFF0000)));
}

/**
  \brief   Dual extract 8-bits and zero-extend to 16-bits.
  \details This function enables you to extract two 8-bit values from an operand and zero-extend them to 16 bits each.
  \param [in]    x   two 8-bit values in val[7:0] and val[23:16] to be zero-extended.
  \return        the 8-bit values sign-extended to 16-bit values.\n
                 sign-extended value of val[7:0] in the low halfword of the return value.\n
                 sign-extended value of val[23:16] in the high halfword of the return value.
  \remark
                 res[15:0]  = SignExtended(val[7:0])       \n
                 res[31:16] = SignExtended(val[23:16])
 */
__ALWAYS_STATIC_INLINE unsigned long __UXTB16(unsigned long x)
{
    return ((unsigned long)((((x << 24) >> 24) & 0x0000FFFF) |
                       (((x <<  8) >>  8) & 0xFFFF0000)));
}

#endif /* _CSI_RV32_GCC_H_ */
