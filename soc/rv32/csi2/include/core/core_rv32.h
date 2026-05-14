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
 * @file     core_rv32.h
 * @brief    CSI RV32 Core Peripheral Access Layer Header File
 * @version  V1.0
 * @date     01. Sep 2018
 ******************************************************************************/

#ifndef __CORE_RV32_H_GENERIC
#define __CORE_RV32_H_GENERIC

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *                 CSI definitions
 ******************************************************************************/
/**
  \ingroup RV32
  @{
 */

#ifndef __RV32
#define __RV32                (0x01U)
#endif

/** __FPU_USED indicates whether an FPU is used or not.
    This core does not support an FPU at all
*/
#define __FPU_USED       0U

#if defined ( __GNUC__ )
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
#error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RV32_H_GENERIC */

#ifndef __CSI_GENERIC

#ifndef __CORE_RV32_H_DEPENDANT
#define __CORE_RV32_H_DEPENDANT

#ifdef __cplusplus
extern "C" {
#endif

/* check device defines and use defaults */
#ifndef __RV32_REV
#define __RV32_REV               0x0000U
#endif

#ifndef __VIC_PRIO_BITS
#define __VIC_PRIO_BITS           2U
#endif

#ifndef __Vendor_SysTickConfig
#define __Vendor_SysTickConfig    1U
#endif

#ifndef __MPU_PRESENT
#define __MPU_PRESENT             1U
#endif

#ifndef __ICACHE_PRESENT
#define __ICACHE_PRESENT          1U
#endif

#ifndef __DCACHE_PRESENT
#define __DCACHE_PRESENT          1U
#endif

/* Memory mapping of XuanTie CPU */
#ifndef CONFIG_TCIP_BASE
#define CONFIG_TCIP_BASE 0xE0000000UL
#endif

#include <core/csi_rv32_gcc.h>
#include <core/core_rv_pmp.h>
#include <core/core_rv_spmp.h>
#include <core/core_rv_clint.h>
#include <core/core_rv_clic.h>
#include <core/core_rv_plic.h>
#include <core/core_rv_aplic.h>
#include <core/core_rv_aclint.h>
#include <core/core_rv_atomic.h>
#include <core/core_rv_tcm.h>
#include <core/core_rv_cachelock.h>
#include <core/core_rv_pmu.h>

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CSI_glob_defs CSI Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/

/*@} end of group RV32 */

/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core CLIC Register
 ******************************************************************************/
/**
  \defgroup CSI_core_register Defines and Type Definitions
  \brief Type definitions and defines for CK80X processor based devices.
*/

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */

/* CACHE Register Definitions */
#define CACHE_MHCR_BTB_Pos                     12U                                           /*!< CACHE MHCR: BTB Position */
#define CACHE_MHCR_BTB_Msk                     (0x1UL << CACHE_MHCR_BTB_Pos)                 /*!< CACHE MHCR: WA Mask */

#define CACHE_MHCR_BPE_Pos                     5U                                            /*!< CACHE MHCR: BPE Position */
#define CACHE_MHCR_BPE_Msk                     (0x1UL << CACHE_MHCR_BPE_Pos)                 /*!< CACHE MHCR: BPE Mask */

#define CACHE_MHCR_RS_Pos                      4U                                            /*!< CACHE MHCR: RS Position */
#define CACHE_MHCR_RS_Msk                      (0x1UL << CACHE_MHCR_RS_Pos)                  /*!< CACHE MHCR: RS Mask */

#define CACHE_MHCR_WA_Pos                      3U                                            /*!< CACHE MHCR: WA Position */
#define CACHE_MHCR_WA_Msk                      (0x1UL << CACHE_MHCR_WA_Pos)                  /*!< CACHE MHCR: WA Mask */

#define CACHE_MHCR_WB_Pos                      2U                                            /*!< CACHE MHCR: WB Position */
#define CACHE_MHCR_WB_Msk                      (0x1UL << CACHE_MHCR_WB_Pos)                  /*!< CACHE MHCR: WB Mask */

#define CACHE_MHCR_DE_Pos                      1U                                            /*!< CACHE MHCR: DE Position */
#define CACHE_MHCR_DE_Msk                      (0x1UL << CACHE_MHCR_DE_Pos)                  /*!< CACHE MHCR: DE Mask */

#define CACHE_MHCR_IE_Pos                      0U                                            /*!< CACHE MHCR: IE Position */
#define CACHE_MHCR_IE_Msk                      (0x1UL << CACHE_MHCR_IE_Pos)                  /*!< CACHE MHCR: IE Mask */

#if CONFIG_CPU_XUANTIE_E902 || CONFIG_CPU_XUANTIE_E902M \
    || CONFIG_CPU_XUANTIE_E901PLUS_CP || CONFIG_CPU_XUANTIE_E901PLUS_B_CP || CONFIG_CPU_XUANTIE_E901PLUS_M_CP || CONFIG_CPU_XUANTIE_E901PLUS_BM_CP \
    || CONFIG_CPU_XUANTIE_E901_CP || CONFIG_CPU_XUANTIE_E901_B_CP || CONFIG_CPU_XUANTIE_E901_ZM_CP || CONFIG_CPU_XUANTIE_E901_BZM_CP
#define CACHE_INV_ADDR_Pos                     4U
#else
#define CACHE_INV_ADDR_Pos                     5U
#define MCER_ECC_FATAL_Pos           30U
#define MCER_ECC_FATAL_Msk           (0x1UL << MCER_ECC_FATAL_Pos)
#define MCER_ECC_VLD_Pos             31U
#define MCER_ECC_VLD_Msk             (0x1UL << MCER_ECC_VLD_Pos)
#define MCER_RAMID_Pos               21U
#define MCER_RAMID_Msk               (0x7UL << MCER_RAMID_Pos)
#endif
#define CACHE_INV_ADDR_Msk                     (0xFFFFFFFFUL << CACHE_INV_ADDR_Pos)

enum MCER_FAULT_RAMID {
    /* L1 Cache, JTLB and TCM (RAMID of MCER)*/
    MCER_FAULT_RAMID_L1_ICACHE_TAG = 0,
    MCER_FAULT_RAMID_L1_ICACHE_DATA,
    MCER_FAULT_RAMID_L1_DCACHE_TAG,
    MCER_FAULT_RAMID_L1_DCACHE_DATA,
    MCER_FAULT_RAMID_JTLB_TAG,
    MCER_FAULT_RAMID_JTLB_DATA,
    MCER_FAULT_RAMID_DTCM,
    MCER_FAULT_RAMID_ITCM
};

enum MCER2_FAULT_RAMID {
    MCER2_FAULT_RAMID_L2_CACHE_TAG = 0,
    MCER2_FAULT_RAMID_L2_CACHE_DATA,
    MCER2_FAULT_RAMID_L2_CACHE_DIRTY
};

/*@} end of group CSI_CACHE */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_SYSMAP system map (SYSMAP)
  \brief      Type definitions for the SYSMAP Registers
  @{
 */
#define SYSMAP_SYSMAPCFG_H_Pos                       0U                                    /*!< SYSMAP SYSMAPCFG: H Position */
#define SYSMAP_SYSMAPCFG_H_Msk                       (0x1UL << SYSMAP_SYSMAPCFG_H_Pos)           /*!< SYSMAP SYSMAPCFG: H Mask */

#define SYSMAP_SYSMAPCFG_B_Pos                       2U                                    /*!< SYSMAP SYSMAPCFG: B Position */
#define SYSMAP_SYSMAPCFG_B_Msk                       (0x1UL << SYSMAP_SYSMAPCFG_B_Pos)           /*!< SYSMAP SYSMAPCFG: B Mask */

#define SYSMAP_SYSMAPCFG_C_Pos                       3U                                    /*!< SYSMAP SYSMAPCFG: C Position */
#define SYSMAP_SYSMAPCFG_C_Msk                       (0x1UL << SYSMAP_SYSMAPCFG_C_Pos)           /*!< SYSMAP SYSMAPCFG: C Mask */

#define SYSMAP_SYSMAPCFG_SO_Pos                      4U                                    /*!< SYSMAP SYSMAPCFG: SO Position */
#define SYSMAP_SYSMAPCFG_SO_Msk                      (0x1UL << SYSMAP_SYSMAPCFG_SO_Pos)          /*!< SYSMAP SYSMAPCFG: SO Mask */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_SYSMAP system map (SYSMAP)
  \brief      Type definitions for the SYSMAP Registers
  @{
 */
typedef struct {
    __IOM uint32_t SYSMAPADDR0;               /*!< Offset: 0x000 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG0;              /*!< Offset: 0x004 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR1;               /*!< Offset: 0x008 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG1;              /*!< Offset: 0x00c (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR2;               /*!< Offset: 0x010 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG2;              /*!< Offset: 0x014 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR3;               /*!< Offset: 0x018 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG3;              /*!< Offset: 0x01c (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR4;               /*!< Offset: 0x020 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG4;              /*!< Offset: 0x024 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR5;               /*!< Offset: 0x028 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG5;              /*!< Offset: 0x02c (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR6;               /*!< Offset: 0x030 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG6;              /*!< Offset: 0x034 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPADDR7;               /*!< Offset: 0x038 (R/W)  SYSMAP configure register */
    __IOM uint32_t SYSMAPCFG7;              /*!< Offset: 0x03c (R/W)  SYSMAP configure register */
} SYSMAP_Type;


/*@} end of group CSI_SYSMAP */

// MSTATUS Register
#define MSTATUS_TVM_MASK (1UL << 20)     // mstatus.TVM                      [20]
#define MSTATUS_MPP_MASK (3UL << 11)     // mstatus.SPP                      [11:12]
#ifndef MSTATUS_MPP_M
#define MSTATUS_MPP_M    (3UL << 11)     // Machine mode                     11
#endif
#define MSTATUS_MPP_S    (1UL << 11)     // Supervisor mode                  01
#define MSTATUS_MPP_U    (0UL << 11)     // User mode                        00

// SSTATUS Register
#define SSTATUS_SPP_MASK (1UL << 8)      // sstatus.SPP                      [8]
#define SSTATUS_SPP_S    (1UL << 8)      // Supervisor mode                  01
#define SSTATUS_SPP_U    (0UL << 8)      // User mode                        00

typedef enum {
    USER_MODE        = 0,
    SUPERVISOR_MODE  = 1,
    MACHINE_MODE     = 3,
} cpu_work_mode_t;

/**
  \brief   Get CPU WORK MODE
  \details Returns CPU WORK MODE.
  \return  CPU WORK MODE
 */
__STATIC_INLINE int csi_get_cpu_work_mode(void)
{
    return (int)__get_CPU_WORK_MODE();
}

/**
  \ingroup  CSI_core_register
  \defgroup CSI_DCC
  \brief    Type definitions for the DCC.
  @{
 */

/**
  \brief  Access to the data structure of DCC.
 */
typedef struct {
    uint32_t RESERVED0[13U];
    __IOM uint32_t HCR;                    /*!< Offset: 0x034 (R/W) */
    __IM  uint32_t EHSR;                   /*!< Offset: 0x03C (R/ ) */
    uint32_t RESERVED1[6U];
    union {
        __IM uint32_t DERJW;               /*!< Offset: 0x058 (R/ )  Data exchange register CPU read*/
        __OM uint32_t DERJR;               /*!< Offset: 0x058 ( /W)  Data exchange register CPU writer*/
    };

} DCC_Type;

#define DCC_HCR_JW_Pos                   18U                                            /*!< DCC HCR: jw_int_en Position */
#define DCC_HCR_JW_Msk                   (1UL << DCC_HCR_JW_Pos)                        /*!< DCC HCR: jw_int_en Mask */

#define DCC_HCR_JR_Pos                   19U                                            /*!< DCC HCR: jr_int_en Position */
#define DCC_HCR_JR_Msk                   (1UL << DCC_HCR_JR_Pos)                        /*!< DCC HCR: jr_int_en Mask */

#define DCC_EHSR_JW_Pos                  1U                                             /*!< DCC EHSR: jw_vld Position */
#define DCC_EHSR_JW_Msk                  (1UL << DCC_EHSR_JW_Pos)                       /*!< DCC EHSR: jw_vld Mask */

#define DCC_EHSR_JR_Pos                  2U                                             /*!< DCC EHSR: jr_vld Position */
#define DCC_EHSR_JR_Msk                  (1UL << DCC_EHSR_JR_Pos)                       /*!< DCC EHSR: jr_vld Mask */

/*@} end of group CSI_DCC */


/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_bitfield     Core register bit field macros
  \brief      Macros for use with bit field definitions (xxx_Pos, xxx_Msk).
  @{
 */

/**
  \brief   Mask and shift a bit field value for use in a register bit range.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of the bit field.
  \return           Masked and shifted value.
*/
#define _VAL2FLD(field, value)    ((value << field ## _Pos) & field ## _Msk)

/**
  \brief     Mask and shift a register value to extract a bit filed value.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of register.
  \return           Masked and shifted bit field value.
*/
#define _FLD2VAL(field, value)    ((value & field ## _Msk) >> field ## _Pos)

/*@} end of group CSI_core_bitfield */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */

#if CONFIG_RISCV_SMODE
#define APLIC_BASE                  (CONFIG_APLIC_S_BASE)
#else
#define APLIC_BASE                  (CONFIG_APLIC_BASE)
#endif

#if !defined(CLINT_BASE)
#if defined(CONFIG_CLINT_BASE)
#define CLINT_BASE                  (CONFIG_CLINT_BASE)                            /*!< CLINT Base Address */
#else
#if defined(CONFIG_PLIC_BASE)
#define CLINT_BASE                  (CONFIG_PLIC_BASE + 0x4000000UL)               /*!< CLINT Base Address */
#else
#define CLINT_BASE                  (CONFIG_TCIP_BASE)                             /*!< CLINT Base Address */
#endif /* CONFIG_PLIC_BASE */
#endif
#endif /* !defined(CLINT_BASE) */

#ifdef CONFIG_ACLINT_BASE
#define ACLINT_BASE                 (CONFIG_ACLINT_BASE)
#endif

#if CONFIG_ACLINT_MTIME_BASE
#define ACLINT_MTIME_BASE           (CONFIG_ACLINT_MTIME_BASE)
#else
#define ACLINT_MTIME_BASE           ((unsigned long)&(((ACLINT_Type *)ACLINT_BASE)->MTIME))
#endif

#if CONFIG_ACLINT_MTIMECMP_BASE
#define ACLINT_MTIMECMP_BASE        (CONFIG_ACLINT_MTIMECMP_BASE)
#else
#define ACLINT_MTIMECMP_BASE        ((unsigned long)&(((ACLINT_Type *)ACLINT_BASE)->MTIMECMP[0]))
#endif

#if CONFIG_ACLINT_MSWI_BASE
#define ACLINT_MSWI_BASE            (CONFIG_ACLINT_MSWI_BASE)
#else
#define ACLINT_MSWI_BASE            ((unsigned long)&(((ACLINT_Type *)ACLINT_BASE)->MSIP[0]))
#endif

#if CONFIG_ACLINT_SSWI_BASE
#define ACLINT_SSWI_BASE            (CONFIG_ACLINT_SSWI_BASE)
#else
#define ACLINT_SSWI_BASE            ((unsigned long)&(((ACLINT_Type *)ACLINT_BASE)->SSIP[0]))
#endif

#define CORET_BASE          (CLINT_BASE + 0x4000UL)                   /*!< CORET Base Address */

#define SYSMAP_BASE         (0xEFFFF000UL)                            /*!< SYSMAP Base Address */

#define CORET               ((CORET_Type   *)     CORET_BASE  )       /*!< SysTick configuration struct */

#define SYSMAP              ((SYSMAP_Type  *)     SYSMAP_BASE )       /*!< SYSMAP configuration struct */

/*@} */

/*******************************************************************************
 *                Hardware Abstraction Layer
  Core Function Interface contains:
  - Core VIC Functions
  - Core CORET Functions
  - Core Register Access Functions
 ******************************************************************************/
/**
  \defgroup CSI_Core_FunctionInterface Functions and Instructions Reference
*/

/**
  \brief   Get current hartid
  \return  hartid
 */
__STATIC_INLINE int csi_get_cpu_id(void)
{
    unsigned long result;

#if CONFIG_RISCV_SMODE
    return 0;
#endif
    __ASM volatile("csrr %0, mhartid" : "=r"(result) : : "memory");
    return result;
}

/**
  \brief   Get cache line size
  \return  cache line size
 */
__STATIC_INLINE int csi_get_cache_line_size(void)
{
#if CONFIG_CPU_XUANTIE_E902 || CONFIG_CPU_XUANTIE_E902M \
    || CONFIG_CPU_XUANTIE_E901PLUS_CP || CONFIG_CPU_XUANTIE_E901PLUS_B_CP || CONFIG_CPU_XUANTIE_E901PLUS_M_CP || CONFIG_CPU_XUANTIE_E901PLUS_BM_CP \
    || CONFIG_CPU_XUANTIE_E901_CP || CONFIG_CPU_XUANTIE_E901_B_CP || CONFIG_CPU_XUANTIE_E901_ZM_CP || CONFIG_CPU_XUANTIE_E901_BZM_CP
    return 16;
#else
    return 32;
#endif
}

/* ##########################   VIC functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_VICFunctions VIC Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn)         (  ((((uint32_t)(int32_t)(IRQn))         )      &  0x03UL) * 8UL)
#define _IP_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    5UL)      )
#define _IP2_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    2UL)      )

/**
    \brief   Enable External Interrupt
    \details Enable a device-specific interrupt in the VIC interrupt controller.
    \param [in]      IRQn         External interrupt number. Value cannot be negative.
    */
__STATIC_INLINE void csi_vic_enable_irq(int32_t IRQn)
{
#if CONFIG_INTC_CLIC
    csi_clic_enable_irq(IRQn);
    return;
#endif

#if CONFIG_INTC_CLIC_APLIC
    if (IRQn > APLIC_IRQ_OFFSET) {
        IRQn -= APLIC_IRQ_OFFSET;
        csi_aplic_enable_irq(APLIC_BASE, IRQn);
    } else {
        csi_clic_enable_irq(IRQn);
    }
    return;
#endif

#if CONFIG_INTC_APLIC
    csi_aplic_enable_irq(APLIC_BASE, IRQn);
    return;
#endif
}

/**
  \brief   Disable External Interrupt
  \details Disable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn         External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_irq(int32_t IRQn)
{
#if CONFIG_INTC_CLIC
    csi_clic_disable_irq(IRQn);
    return;
#endif

#if CONFIG_INTC_CLIC_APLIC
    if ((uint32_t)IRQn > APLIC_IRQ_OFFSET) {
        IRQn -= APLIC_IRQ_OFFSET;
        csi_aplic_disable_irq(APLIC_BASE, IRQn);
    } else {
        csi_clic_disable_irq(IRQn);
    }
    return;
#endif

#if CONFIG_INTC_APLIC
    csi_aplic_disable_irq(APLIC_BASE, IRQn);
    return;
#endif
}

/**
  \brief   Check Interrupt is Enabled or not
  \details Read the enabled register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn         External interrupt number.
  \return             0  Interrupt status is not enabled.
  \return             1  Interrupt status is enabled.
 */
__STATIC_INLINE uint32_t csi_vic_get_enabled_irq(int32_t IRQn)
{
    uint32_t ret;
#if CONFIG_INTC_CLIC
    ret = csi_clic_get_enabled_irq(IRQn);
    return ret;
#endif

#if CONFIG_INTC_CLIC_APLIC
    if (IRQn > APLIC_IRQ_OFFSET) {
        IRQn -= APLIC_IRQ_OFFSET;
        ret = csi_aplic_get_enabled_irq(APLIC_BASE, IRQn);
    } else {
        ret = csi_clic_get_enabled_irq(IRQn);
    }
    return ret;
#endif

#if CONFIG_INTC_APLIC
    ret = csi_aplic_get_enabled_irq(APLIC_BASE, IRQn);
    return ret;
#endif
}

/**
  \brief   Check Interrupt is Pending or not
  \details Read the pending register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
 */
__STATIC_INLINE uint32_t csi_vic_get_pending_irq(int32_t IRQn)
{
    uint32_t ret;

#if CONFIG_INTC_CLIC
    ret = csi_clic_get_pending_irq(IRQn);
    return ret;
#endif

#if CONFIG_INTC_CLIC_APLIC
    if ((uint32_t)IRQn > APLIC_IRQ_OFFSET) {
        IRQn -= APLIC_IRQ_OFFSET;
        ret = csi_aplic_get_pending_irq(APLIC_BASE, IRQn);
    } else {
        ret = csi_clic_get_pending_irq(IRQn);
    }
    return ret;
#endif

#if CONFIG_INTC_APLIC
    ret = csi_aplic_get_pending_irq(APLIC_BASE, IRQn);
    return ret;
#endif
}

/**
  \brief   Set Pending Interrupt
  \details Set the pending bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_set_pending_irq(int32_t IRQn)
{
#if CONFIG_INTC_CLIC
    csi_clic_set_pending_irq(IRQn);
    return;
#endif

#if CONFIG_INTC_CLIC_APLIC
    if ((uint32_t)IRQn > APLIC_IRQ_OFFSET) {
        IRQn -= APLIC_IRQ_OFFSET;
        csi_aplic_set_pending_irq(APLIC_BASE, IRQn);
    } else {
        csi_clic_set_pending_irq(IRQn);
    }
    return;
#endif

#if CONFIG_INTC_PLIC
    csi_aplic_set_pending_irq(APLIC_BASE, IRQn);
    return;
#endif
}

/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_clear_pending_irq(int32_t IRQn)
{
#if CONFIG_INTC_CLIC
    csi_clic_clear_pending_irq(IRQn);
    return;
#endif

#if CONFIG_INTC_CLIC_APLIC
    if ((uint32_t)IRQn > APLIC_IRQ_OFFSET) {
        IRQn -= APLIC_IRQ_OFFSET;
        csi_aplic_clear_pending_irq(APLIC_BASE, IRQn);
    } else {
        csi_clic_clear_pending_irq(IRQn);
    }
    return;
#endif

#if CONFIG_INTC_PLIC
    csi_aplic_clear_pending_irq(APLIC_BASE, IRQn);
    return;
#endif
}

/**
  \brief   Set Interrupt Priority
  \details Set the priority of an interrupt.
  \note    The priority cannot be set for every core interrupt.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
 */
__STATIC_INLINE void csi_vic_set_prio(int32_t IRQn, uint32_t priority)
{
#if CONFIG_INTC_CLIC
    csi_clic_set_prio(IRQn, priority);
    return;
#endif

#if CONFIG_INTC_CLIC_APLIC
    if ((uint32_t)IRQn > APLIC_IRQ_OFFSET) {
        IRQn -= APLIC_IRQ_OFFSET;
        csi_aplic_set_prio(APLIC_BASE, IRQn, priority);
    } else {
        csi_clic_set_prio(IRQn, priority);
    }
    return;
#endif

#if CONFIG_INTC_APLIC
    csi_aplic_set_prio(APLIC_BASE, IRQn, priority);
    return;
#endif
}

/**
  \brief   Get Interrupt Priority
  \details Read the priority of an interrupt.
           The interrupt number can be positive to specify an external (device specific) interrupt,
           or negative to specify an internal (core) interrupt.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t csi_vic_get_prio(int32_t IRQn)
{
    uint32_t ret;
#if CONFIG_INTC_CLIC
    ret = csi_clic_get_prio(IRQn);
    return ret;
#endif

#if CONFIG_INTC_CLIC_APLIC
if ((uint32_t)IRQn > APLIC_IRQ_OFFSET) {
        IRQn -= APLIC_IRQ_OFFSET;
        ret = csi_aplic_get_prio(APLIC_BASE, IRQn);
    } else {
        ret = csi_clic_get_prio(IRQn);
    }
    return ret;
#endif

#if CONFIG_INTC_APLIC
    ret = csi_aplic_get_prio(APLIC_BASE, IRQn);
    return ret;
#endif
}

/**
  \brief   Get Interrupt thresh
  \details Read the thresh of interrupt
           Only the interrupt priority is greater than the value of thresh, the interrupt can be responded to
  \return             Interrupt thresh value(0~255).
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t csi_vic_get_thresh(void)
{
    uint32_t val = 0;
#if CONFIG_INTC_CLIC_APLIC || CONFIG_INTC_CLIC
#if CLIC_SPEC_VERSION_010
    val = __get_MINTTHRESH() >> 24;
#else
    val = CLIC->MINTTHRESH >> 24;
#endif
#endif
    return val;
}

/**
  \brief   Set Interrupt thresh
  \details Write the thresh of interrupt
           Only the interrupt priority is greater than the value of thresh, the interrupt can be responded to
  \param [in]      Interrupt thresh value(0~255).
  \return          The thresh before set.
 */
__STATIC_INLINE uint32_t csi_vic_set_thresh(uint32_t thresh)
{
    uint32_t temp = 0;
#if CLIC_SPEC_VERSION_010
#else
    temp = CLIC->MINTTHRESH;
    uint8_t nlbits = (CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;

    if(!nlbits)
        CLIC->MINTTHRESH = 0xff << 24;

    CLIC->MINTTHRESH = thresh << 24;
#endif
    return temp;
}

/*@} end of CSI_Core_VICFunctions */

/* ##################################    SysTick function  ############################################ */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SysTickFunctions SysTick Functions
  \brief    Functions that configure the System.
  @{
 */

/**
  \brief   CORE timer Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \param [in]  IRQn   core timer Interrupt number.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
__STATIC_INLINE uint32_t csi_coret_config(uint64_t ticks, int32_t IRQn)
{
#if CONFIG_INTC_ACLINT
#if CONFIG_RISCV_SMODE
#ifdef __riscv_sstc
#if __riscv_xlen == 32
    uint64_t stimecmp_val = (((uint64_t)__get_MTIMEH() << 32) | __get_MTIME()) + ticks;
    __set_STIMECMPH(stimecmp_val >> 32);
    __set_STIMECMP(stimecmp_val & 0xFFFFFFFF);
#else
    uint64_t stimecmp_val = __get_MTIME() + ticks;
    __set_STIMECMP(stimecmp_val);
#endif
#endif /* __riscv_sstc */
#else /* !CONFIG_RISCV_SMODE */
#if __riscv_xlen == 32
    csi_aclint_mtimecmp_set(ACLINT_MTIMECMP_BASE, csi_get_cpu_id(), (((uint64_t)__get_MTIMEH() << 32) | __get_MTIME()) + ticks);
#else
    csi_aclint_mtimecmp_set(ACLINT_MTIMECMP_BASE, csi_get_cpu_id(), __get_MTIME() + ticks);
#endif
#endif /* CONFIG_RISCV_SMODE */
#else /* !CONFIG_INTC_ACLINT */
#if CONFIG_RISCV_SMODE
    uint64_t value = csi_clint_stimecmp_get(CLINT_BASE, csi_get_cpu_id());
    if ((value != 0) && (value != 0xFFFFFFFFFFFFFFFFULL)) {
        value = value + ticks;
    } else {
        value = csi_clint_stime_get(CLINT_BASE) + ticks;
    }
    csi_clint_stimecmp_set(CLINT_BASE, csi_get_cpu_id(), value);
#else
    uint64_t value = csi_clint_mtimecmp_get(CLINT_BASE, csi_get_cpu_id());
    if ((value != 0) && (value != 0xFFFFFFFFFFFFFFFFULL)) {
        value = value + ticks;
    } else {
        value = csi_clint_mtime_get(CLINT_BASE) + ticks;
    }
    csi_clint_mtimecmp_set(CLINT_BASE, csi_get_cpu_id(), value);
#endif /* CONFIG_RISCV_SMODE */
#endif /* CONFIG_INTC_ACLINT */
    return 0;
}

/**
  \brief   get CORE timer reload value
  \return          CORE timer counter value(64bit).
 */
__STATIC_INLINE uint64_t csi_coret_get_load2(void)
{
#if CONFIG_INTC_ACLINT
#if CONFIG_RISCV_SMODE
    uint64_t stimecmp_val = 0;
#ifdef __riscv_sstc
#if __riscv_xlen == 32
    stimecmp_val = __get_STIMECMPH();
    stimecmp_val <<= 32;
    stimecmp_val |= __get_STIMECMP();
#else
    stimecmp_val = __get_STIMECMP();
#endif
#endif /* __riscv_sstc */
    return stimecmp_val;
#else
    return csi_aclint_mtimecmp_get(ACLINT_MTIMECMP_BASE, csi_get_cpu_id());
#endif /* CONFIG_RISCV_SMODE */
#else /* !CONFIG_INTC_ACLINT */
#if CONFIG_RISCV_SMODE
    return csi_clint_stimecmp_get(CLINT_BASE, csi_get_cpu_id());
#else
    return csi_clint_mtimecmp_get(CLINT_BASE, csi_get_cpu_id());
#endif
#endif /* CONFIG_INTC_ACLINT */
}

/**
  \brief   get CORE timer counter value
  \return          CORE timer counter value(64bit).
 */
__STATIC_INLINE uint64_t csi_coret_get_value2(void)
{
#if CONFIG_INTC_ACLINT
#if CONFIG_RISCV_SMODE
#if __riscv_xlen == 32
    uint64_t timeval = ((uint64_t)__get_MTIMEH() << 32) | __get_MTIME();
#else
    uint64_t timeval = __get_MTIME();
#endif
    return timeval;
#else /* !CONFIG_RISCV_SMODE */
    return csi_aclint_mtime_get(ACLINT_MTIME_BASE);
#endif /* CONFIG_RISCV_SMODE */
#else /* !CONFIG_INTC_ACLINT */
#if CONFIG_RISCV_SMODE
    return csi_clint_stime_get(CLINT_BASE);
#else
    return csi_clint_mtime_get(CLINT_BASE);
#endif /* CONFIG_RISCV_SMODE */
#endif /* CONFIG_INTC_ACLINT */
}

__STATIC_INLINE void csi_coret_reset_value2()
{
#if CONFIG_INTC_ACLINT
#if CONFIG_RISCV_SMODE
#ifdef __riscv_sstc
#if __riscv_xlen == 32
    __set_STIMECMPH(0);
    __set_STIMECMP(0);
#else
    __set_STIMECMP(0);
#endif
#endif /* __riscv_sstc */
#else
    csi_aclint_mtimecmp_set(ACLINT_MTIMECMP_BASE, csi_get_cpu_id(), 0);
#endif /* CONFIG_RISCV_SMODE */
#else /* !CONFIG_INTC_ACLINT */
#if CONFIG_RISCV_SMODE
    csi_clint_stimecmp_set(CLINT_BASE, csi_get_cpu_id(), 0);
#else
    csi_clint_mtimecmp_set(CLINT_BASE, csi_get_cpu_id(), 0);
#endif
#endif /* CONFIG_INTC_ACLINT */
}

/**
  \brief   Enable CoreTimer(within clint) Interrupts
 */
__ALWAYS_STATIC_INLINE void csi_coret_irq_enable(void)
{
#if CONFIG_INTC_CLIC || CONFIG_INTC_CLIC_PLIC || CONFIG_INTC_CLIC_APLIC
    extern void soc_irq_enable(uint32_t irq_num);
#if CONFIG_RISCV_SMODE
    soc_irq_enable(5);
#else
    soc_irq_enable(7);
#endif
#else
    __enable_coret_irq();
#endif
}

/**
  \brief   Disable CoreTimer(within clint) Interrupts
 */
__ALWAYS_STATIC_INLINE void csi_coret_irq_disable(void)
{
#if CONFIG_INTC_CLIC || CONFIG_INTC_CLIC_PLIC || CONFIG_INTC_CLIC_APLIC
    extern void soc_irq_disable(uint32_t irq_num);
#if CONFIG_RISCV_SMODE
    soc_irq_disable(5);
#else
    soc_irq_disable(7);
#endif
#else
    __disable_coret_irq();
#endif
}

/*@} end of CSI_Core_SysTickFunctions */

/* ##########################   SYSMAP functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SYSMAPFunctions SYSMAP Functions
  \brief    Functions that manage system map attribute
  @{
 */

/**
  \brief   Get SYSMAPCFGx Register by index
  \details Returns the content of the SYSMAPxCFG Register.
  \param [in]    idx    SYSMAP region index
  \return               SYSMAPxCFG Register value
 */
__STATIC_INLINE uint8_t __get_SYSMAPCFGx(uint32_t idx)
{
    switch (idx) {
    case 0:
        return SYSMAP->SYSMAPCFG0;
    case 1:
        return SYSMAP->SYSMAPCFG1;
    case 2:
        return SYSMAP->SYSMAPCFG2;
    case 3:
        return SYSMAP->SYSMAPCFG3;
    case 4:
        return SYSMAP->SYSMAPCFG4;
    case 5:
        return SYSMAP->SYSMAPCFG5;
    case 6:
        return SYSMAP->SYSMAPCFG6;
    case 7:
        return SYSMAP->SYSMAPCFG7;
    default:
        return 0;
    }
}

/**
  \brief   Set SYSMAPCFGx by index
  \details Writes the given value to the SYSMAPxCFG Register.
  \param [in]    idx      SYSMAPx region index
  \param [in]    sysmapxcfg  SYSMAPxCFG Register value to set
 */
__STATIC_INLINE void __set_SYSMAPCFGx(uint32_t idx, uint32_t sysmapxcfg)
{
    switch (idx) {
    case 0:
        SYSMAP->SYSMAPCFG0 = sysmapxcfg;
        break;
    case 1:
        SYSMAP->SYSMAPCFG1 = sysmapxcfg;
        break;
    case 2:
        SYSMAP->SYSMAPCFG2 = sysmapxcfg;
        break;
    case 3:
        SYSMAP->SYSMAPCFG3 = sysmapxcfg;
        break;
    case 4:
        SYSMAP->SYSMAPCFG4 = sysmapxcfg;
        break;
    case 5:
        SYSMAP->SYSMAPCFG5 = sysmapxcfg;
        break;
    case 6:
        SYSMAP->SYSMAPCFG6 = sysmapxcfg;
        break;
    case 7:
        SYSMAP->SYSMAPCFG7 = sysmapxcfg;
        break;
    default:
        return;
    }
}

/**
  \brief   Get SYSMAPADDRx Register by index
  \details Returns the content of the SYSMAPADDRx Register.
  \param [in]    idx    SYSMAP region index
  \return               SYSMAPADDRx Register value
 */
__STATIC_INLINE uint32_t __get_SYSMAPADDRx(uint32_t idx)
{
    switch(idx) {
    case 0:
        return SYSMAP->SYSMAPADDR0;
    case 1:
        return SYSMAP->SYSMAPADDR1;
    case 2:
        return SYSMAP->SYSMAPADDR2;
    case 3:
        return SYSMAP->SYSMAPADDR3;
    case 4:
        return SYSMAP->SYSMAPADDR4;
    case 5:
        return SYSMAP->SYSMAPADDR5;
    case 6:
        return SYSMAP->SYSMAPADDR6;
    case 7:
        return SYSMAP->SYSMAPADDR7;
    default:
        return 0;
    }
}

/**
  \brief   Set SYSMAPADDRx by index
  \details Writes the given value to the SYSMAPADDRx Register.
  \param [in]    idx      SYSMAP region index
  \param [in]    sysmapaddr  SYSMAPADDRx Register value to set
 */
__STATIC_INLINE void __set_SYSMAPADDRx(uint32_t idx, uint32_t sysmapxaddr)
{
    switch (idx) {
    case 0:
        SYSMAP->SYSMAPADDR0 = sysmapxaddr;
        break;
    case 1:
        SYSMAP->SYSMAPADDR1 = sysmapxaddr;
        break;
    case 2:
        SYSMAP->SYSMAPADDR2 = sysmapxaddr;
        break;
    case 3:
        SYSMAP->SYSMAPADDR3 = sysmapxaddr;
        break;
    case 4:
        SYSMAP->SYSMAPADDR4 = sysmapxaddr;
        break;
    case 5:
        SYSMAP->SYSMAPADDR5 = sysmapxaddr;
        break;
    case 6:
        SYSMAP->SYSMAPADDR6 = sysmapxaddr;
        break;
    case 7:
        SYSMAP->SYSMAPADDR7 = sysmapxaddr;
        break;
    default:
        return;
    }
}

/**
  \brief  configure system map attribute.
  \details
  \param [in]  idx        system map region (0, 1, 2, ..., 7).
  \param [in]  base_addr  base address must be aligned with page size.
  \param [in]  attr       the SYSMAPCFG mask, SYSMAP_SYSMAPCFG_H_Msk/SYSMAP_SYSMAPCFG_B_Msk/SYSMAP_SYSMAPCFG_C_Msk/SYSMAP_SYSMAPCFG_SO_Msk
  */
__STATIC_INLINE void csi_sysmap_config_region(uint32_t idx, uint32_t base_addr, uint32_t attr)
{
    uint32_t addr = 0;

    if (idx > 7) {
        return;
    }

    addr = base_addr >> 12;

    __set_SYSMAPADDRx(idx, addr);
    __set_SYSMAPCFGx(idx, attr);
}

/*@} end of CSI_Core_SYSMAPFunctions */

/* ##########################  Cache functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_CacheFunctions Cache Functions
  \brief    Functions that configure Instruction and Data cache.
  @{
 */

/**
  \brief   whether I-Cache enable
  */
__STATIC_INLINE int csi_icache_is_enable()
{
    uint32_t cache = __get_MHCR();
    return (cache & CACHE_MHCR_IE_Msk) >> CACHE_MHCR_IE_Pos;
}

/**
  \brief   Enable I-Cache
  \details Turns on I-Cache
  */
__STATIC_INLINE void csi_icache_enable (void)
{
#if (__ICACHE_PRESENT == 1U)
    if (!csi_icache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ICACHE_IALL();
        cache = __get_MHCR();
        cache |= CACHE_MHCR_IE_Msk;
        __set_MHCR(cache);
        __DSB();
    }
#endif
}


/**
  \brief   Disable I-Cache
  \details Turns off I-Cache
  */
__STATIC_INLINE void csi_icache_disable (void)
{
#if (__ICACHE_PRESENT == 1U)
    if (csi_icache_is_enable()) {
        uint32_t cache;
        __DSB();
        cache = __get_MHCR();
        cache &= ~CACHE_MHCR_IE_Msk;            /* disable icache */
        __set_MHCR(cache);
        __ICACHE_IALL();                        /* invalidate all icache */
        __DSB();
    }
#endif
}


/**
  \brief   Invalidate I-Cache
  \details Invalidates I-Cache
  */
__STATIC_INLINE void csi_icache_invalid (void)
{
#if (__ICACHE_PRESENT == 1U)
    __DSB();
    __ICACHE_IALL();                        /* invalidate all icache */
    __DSB();
#endif
}

/**
  \brief   whether D-Cache enable
  */
__STATIC_INLINE int csi_dcache_is_enable()
{
    uint32_t cache = __get_MHCR();
    return (cache & CACHE_MHCR_DE_Msk) >> CACHE_MHCR_DE_Pos;
}

/**
  \brief   Enable D-Cache
  \details Turns on D-Cache
  */
__STATIC_INLINE void csi_dcache_enable (void)
{
#if (__DCACHE_PRESENT == 1U)
    if (!csi_dcache_is_enable()) {
        uint32_t cache;
        __DSB();
        __DCACHE_IALL();                        /* invalidate all dcache */
        cache = __get_MHCR();
        cache |= CACHE_MHCR_DE_Msk;             /* enable dcache */
        __set_MHCR(cache);

        __DSB();
    }
#endif
}


/**
  \brief   Disable D-Cache
  \details Turns off D-Cache
  */
__STATIC_INLINE void csi_dcache_disable (void)
{
#if (__DCACHE_PRESENT == 1U)
    if (csi_dcache_is_enable()) {
        uint32_t cache;
        __DSB();
        cache = __get_MHCR();
        cache &= ~(uint32_t)CACHE_MHCR_DE_Msk; /* disable all Cache */
        __set_MHCR(cache);
        __DCACHE_IALL();                             /* invalidate all Cache */
        __DSB();
    }
#endif
}


/**
  \brief   Invalidate D-Cache
  \details Invalidates D-Cache
  */
__STATIC_INLINE void csi_dcache_invalid (void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __DCACHE_IALL();                            /* invalidate all Cache */
    __DSB();
#endif
}


/**
  \brief   Clean D-Cache
  \details Cleans D-Cache
  */
__STATIC_INLINE void csi_dcache_clean (void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __DCACHE_CALL();                                     /* clean all Cache */
    __DSB();
#endif
}


/**
  \brief   Clean & Invalidate D-Cache
  \details Cleans and Invalidates D-Cache
  */
__STATIC_INLINE void csi_dcache_clean_invalid (void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __DCACHE_CIALL();                                   /* clean and inv all Cache */
    __DSB();
#endif
}


/**
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_invalid_range (unsigned long *addr, size_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int linesize = csi_get_cache_line_size();
    long op_size = dsize + (unsigned long)addr % linesize;
    unsigned long op_addr = (unsigned long)addr & CACHE_INV_ADDR_Msk;

    __DSB();

    while (op_size > 0) {
        __DCACHE_IPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
#endif
}


/**
  \brief   D-Cache Clean by address
  \details Cleans D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_clean_range (unsigned long *addr, size_t dsize)
{

#if (__DCACHE_PRESENT == 1U)
    int linesize = csi_get_cache_line_size();
    long op_size = dsize + (unsigned long)addr % linesize;
    unsigned long op_addr = (unsigned long) addr & CACHE_INV_ADDR_Msk;

    __DSB();

    while (op_size > 0) {
        __DCACHE_CPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
#endif

}


/**
  \brief   D-Cache Clean and Invalidate by address
  \details Cleans and invalidates D_Cache for the given address
  \param[in]   addr    address (aligned to 16-byte boundary)
  \param[in]   dsize   size of memory block (aligned to 16-byte boundary)
*/
__STATIC_INLINE void csi_dcache_clean_invalid_range (unsigned long *addr, size_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int linesize = csi_get_cache_line_size();
    long op_size = dsize + (unsigned long)addr % linesize;
    unsigned long op_addr = (unsigned long) addr & CACHE_INV_ADDR_Msk;

    __DSB();

    while (op_size > 0) {
        __DCACHE_CIPA(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }

    __DSB();
#endif
}

/*@} end of CSI_Core_CacheFunctions */


/*@} end of CSI_core_DebugFunctions */

/* ##################################    IRQ Functions  ############################################ */

/**
  \brief   Save the Irq context
  \details save the psr result before disable irq.
 */
__STATIC_INLINE unsigned long csi_irq_save(void)
{
    unsigned long result;
#if CONFIG_RISCV_SMODE
    result = __get_SSTATUS();
#else
    result = __get_MSTATUS();
#endif
    __disable_irq();
    return(result);
}

/**
  \brief   Restore the Irq context
  \details restore saved primask state.
  \param [in]      irq_state  psr irq state.
 */
__STATIC_INLINE void csi_irq_restore(uint32_t irq_state)
{
#if CONFIG_RISCV_SMODE
    __set_SSTATUS(irq_state);
#else
    __set_MSTATUS(irq_state);
#endif
}

/*@} end of IRQ Functions */

/**
  \brief   Get the byte-width of vector register
  \return  the byte-width of vector register
 */
__STATIC_INLINE int csi_vlenb_get_value(void)
{
    int result;
    __ASM volatile("csrr %0, vlenb" : "=r"(result) : : "memory");
    return result;
}

#include "csi_port.h"

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RV32_H_DEPENDANT */

#endif /* __CSI_GENERIC */
