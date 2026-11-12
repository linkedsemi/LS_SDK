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

#ifndef __CORE_RV_APLIC_H__
#define __CORE_RV_APLIC_H__

#if CONFIG_INTC_APLIC || CONFIG_INTC_CLIC_APLIC || CONFIG_INTC_IMSIC_APLIC

/* DOMAINCFG Register Bit Fields */
#define APLIC_DOMAINCFG_IE_POS          (8U)                                    /* Interrupt Enable bit position */
#define APLIC_DOMAINCFG_IE_MSK          (1UL << APLIC_DOMAINCFG_IE_POS)         /* Interrupt Enable: 0=Disabled, 1=Enabled */
#define APLIC_DOMAINCFG_IE              APLIC_DOMAINCFG_IE_MSK                  /* Interrupt Enable field */

#define APLIC_DOMAINCFG_DM_POS          (2U)                                    /* Delivery Mode bit position */
#define APLIC_DOMAINCFG_DM_MSK          (1UL << APLIC_DOMAINCFG_DM_POS)         /* Delivery Mode: 0=Direct, 1=MSI */
#define APLIC_DOMAINCFG_DM              APLIC_DOMAINCFG_DM_MSK                  /* Delivery Mode field */

#define APLIC_DOMAINCFG_BE_POS          (1U)                                    /* Big Endian bit position */
#define APLIC_DOMAINCFG_BE_MSK          (1UL << APLIC_DOMAINCFG_BE_POS)         /* Big Endian: 0=Little-Endian, 1=Big-Endian */
#define APLIC_DOMAINCFG_BE              APLIC_DOMAINCFG_BE_MSK                  /* Big Endian field (read-only, set by hardware) */

/* Combined field masks */
#define APLIC_DOMAINCFG_RESERVED_MSK    (~(APLIC_DOMAINCFG_IE_MSK | APLIC_DOMAINCFG_DM_MSK | APLIC_DOMAINCFG_BE_MSK))

/* Helper macros for register manipulation */
#define APLIC_DOMAINCFG_GET_IE(reg)     (((reg) & APLIC_DOMAINCFG_IE_MSK) >> APLIC_DOMAINCFG_IE_POS)
#define APLIC_DOMAINCFG_SET_IE(reg, val) (((reg) & ~APLIC_DOMAINCFG_IE_MSK) | (((val) << APLIC_DOMAINCFG_IE_POS) & APLIC_DOMAINCFG_IE_MSK))

#define APLIC_DOMAINCFG_GET_DM(reg)     (((reg) & APLIC_DOMAINCFG_DM_MSK) >> APLIC_DOMAINCFG_DM_POS)
#define APLIC_DOMAINCFG_SET_DM(reg, val) (((reg) & ~APLIC_DOMAINCFG_DM_MSK) | (((val) << APLIC_DOMAINCFG_DM_POS) & APLIC_DOMAINCFG_DM_MSK))

#define APLIC_DOMAINCFG_GET_BE(reg)     (((reg) & APLIC_DOMAINCFG_BE_MSK) >> APLIC_DOMAINCFG_BE_POS)

/* Value definitions for register fields */
#define APLIC_DOMAINCFG_IE_DISABLED     (0UL)                                   /* Interrupts disabled */
#define APLIC_DOMAINCFG_IE_ENABLED      (1UL)                                   /* Interrupts enabled */

#define APLIC_DOMAINCFG_DM_DIRECT       (0UL)                                   /* Direct delivery mode */
#define APLIC_DOMAINCFG_DM_MSI          (1UL)                                   /* MSI delivery mode */

#define APLIC_DOMAINCFG_BE_LITTLE       (0UL)                                   /* Little-endian */
#define APLIC_DOMAINCFG_BE_BIG          (1UL)                                   /* Big-endian */

/* SOURCECFG SM */
#define APLIC_SOURCECFG_SM_INACTIVE         (0U)                                /* Inactive in this domain (and not delegated) */
#define APLIC_SOURCECFG_SM_DETACHED         (1U)                                /* Active, detached from the source wire */
#define APLIC_SOURCECFG_SM_EDGE1_RISING     (4U)                                /* Active, edge-sensitive; interrupt asserted on rising edge */
#define APLIC_SOURCECFG_SM_EDGE0_FALLING    (5U)                                /* Active, edge-sensitive; interrupt asserted on falling edge */
#define APLIC_SOURCECFG_SM_LEVEL1_HIGH      (6U)                                /* Active, level-sensitive; interrupt asserted when high */
#define APLIC_SOURCECFG_SM_LEVEL0_LOW       (7U)                                /* Active, level-sensitive; interrupt asserted when low */

/* MMSIADDRCFGH Register Bit Fields */
#define APLIC_MMSIADDRCFGH_L_POS              (31U)
#define APLIC_MMSIADDRCFGH_L_MSK              (1UL << APLIC_MMSIADDRCFGH_L_POS)
#define APLIC_MMSIADDRCFGH_HHXS_POS           (24U)
#define APLIC_MMSIADDRCFGH_HHXS_MSK           (0x1FUL << APLIC_MMSIADDRCFGH_HHXS_POS)
#define APLIC_MMSIADDRCFGH_LHXS_POS           (20U)
#define APLIC_MMSIADDRCFGH_LHXS_MSK           (0x7UL << APLIC_MMSIADDRCFGH_LHXS_POS)
#define APLIC_MMSIADDRCFGH_HHXW_POS           (16U)
#define APLIC_MMSIADDRCFGH_HHXW_MSK           (0x7UL << APLIC_MMSIADDRCFGH_HHXW_POS)
#define APLIC_MMSIADDRCFGH_LHXW_POS           (12U)
#define APLIC_MMSIADDRCFGH_LHXW_MSK           (0xFUL << APLIC_MMSIADDRCFGH_LHXW_POS)
#define APLIC_MMSIADDRCFGH_HIGH_BASE_PPN_POS  (0x0UL)
#define APLIC_MMSIADDRCFGH_HIGH_BASE_PPN_MSK  (0xFFFUL << APLIC_MMSIADDRCFGH_HIGH_BASE_PPN_POS)

/* MMSIADDRCFG Register Bit Fields */
#define APLIC_MMSIADDRCFG_LOW_BASE_PPN_POS    (0x0UL)
#define APLIC_MMSIADDRCFG_LOW_BASE_PPN_MSK    (0xFFFFFFFFUL << APLIC_MMSIADDRCFG_LOW_BASE_PPN_POS)

/* SMSIADDRCFGH Register Bit Fields */
#define APLIC_SMSIADDRCFGH_LHXS_POS           (20U)
#define APLIC_SMSIADDRCFGH_LHXS_MSK           (0x7UL << APLIC_SMSIADDRCFGH_LHXS_POS)
#define APLIC_SMSIADDRCFGH_HIGH_BASE_PPN_POS  (20U)
#define APLIC_SMSIADDRCFGH_HIGH_BASE_PPN_MSK  (0x7UL << APLIC_SMSIADDRCFGH_HIGH_BASE_PPN_POS)

/* SMSIADDRCFG Register Bit Fields */
#define APLIC_SMSIADDRCFG_LOW_BASE_PPN_POS    (0x0UL)
#define APLIC_SMSIADDRCFG_LOW_BASE_PPN_MSK    (0xFFFFFFFFUL << APLIC_SMSIADDRCFG_LOW_BASE_PPN_POS)

/* interrupt delivery control region, a set of registers, 32 bytes for each core */
#define APLIC_IDC_OFFSET(hart_id)        (0x4000UL + (hart_id) * 32)

/**
  \brief Access to the structure of an APLIC.
 */

typedef struct {
    /* Domain configuration register, 0x0000 */
    __IOM uint32_t DOMAINCFG;
    /* Source configuration registers, 0x0004+(source_id*4), 0x0004~0x1000 */
    __IOM uint32_t SOURCECFG[1023];
    __IM uint32_t RESERVED0[(0x1bc0 - 0x1000) / 4];

    /* Memory-Mapped Interrupt Address Configuration */
    __IOM uint32_t MMSIADDRCFG;                         /* machine, low, 0x1bc0 */
    __IOM uint32_t MMSIADDRCFGH;                        /* machine, high, 0x1bc4 */
    __IOM uint32_t SMSIADDRCFG;                         /* supervisor, low, 0x1bc8 */
    __IOM uint32_t SMSIADDRCFGH;                        /* supervisor, high, 0x1bcc */
    __IM uint32_t RESERVED1[(0x1c00 - 0x1bd0) / 4];

    /* pending bits, each register contains 32 sources, 0x1c00~0x1c7c  */
    __IOM uint32_t SETIP[32];
    __IM uint32_t RESERVED2[(0x1cdc - 0x1c80) / 4]; /* 0x1cdc */
    __OM uint32_t SETIPNUM;
    __IM uint32_t RESERVED3[(0x1d00 - 0x1ce0) / 4];

    /* irq pending bit clearing, 0x1d00+(index*4), 0x1d00~0x1d7c */
    __IOM uint32_t IN_CLRIP[32];
    __IM uint32_t RESERVED4[(0x1ddc - 0x1d80) / 4];

    /* clearing pending num, 0x1ddc */
    __OM uint32_t CLRIPNUM;
    __IM uint32_t RESERVED5[(0x1e00 - 0x1de0) / 4];

    /* Interrupt enable registers */
    __IOM uint32_t SETIE[32];                           /* Set interrupt enable, 0x1e00~0x1e7c */
    __IM uint32_t RESERVED6[(0x1edc - 0x1e80) / 4];
    __OM uint32_t SETIENUM;                             /* Set interrupt enable by number, 0x1edc */
    __IM uint32_t RESERVED7[(0x1f00 - 0x1ee0) / 4];

    /* clearing interrupt enable registers */
    __OM uint32_t CLRIE[32];                            /* Clear interrupt enable, 0x1f00+4*index , 0x1f00~0x1f7c */
    __IM uint32_t RESERVED8[(0x1fdc - 0x1f80) / 4];
    __OM uint32_t CLRIENUM;                             /* Clear interrupt enable by number, 0x1fdc */
    __IM uint32_t RESERVED9[(0x2000 - 0x1fe0) / 4];

    /* set pending num */
    __OM uint32_t SETIPNUM_LE;                          /* little endian, 0x2000 */
    __OM uint32_t SETIPNUM_BE;                          /* big endian, 0x2004 */
    __IM uint32_t RESERVED10[(0x3000 - 0x2008) / 4];
    __IOM uint32_t GENMSI;                              /* 0x3000 */

    /* Target configuration registers, 0x3004 ~ 0x3FFC */
    __IOM uint32_t TARGET[1023];
} APLIC_Type;

/* Interrupt Delivery Control structure */
typedef struct {
    __IOM uint32_t IDELIVERY;   /* 0x00 - Enable/disable interrupt delivery to hart */
    __IOM uint32_t IFORCE;      /* 0x04 - Force interrupt (for testing) */
    __IOM uint32_t ITHRESHOLD;  /* 0x08 - Interrupt priority threshold */
    __IM  uint32_t RESERVED[3]; /* 0x0C-0x14 - Reserved space  */
    __IM  uint32_t TOPI;        /* 0x18 - Top pending interrupt ID, read only */
    __IM  uint32_t CLAIMI;      /* 0x1C - Claim interrupt, read only (read clears pending) */
} APLIC_IDC_Type;

/**
  \brief        Configure APLIC domain configuration register
  \param [in]   aplic_base      APLIC base address
  \param [in]   enable          Whether to enable interrupts in this domain
  \param [in]   msi_mode        Whether to use MSI mode (true) or Direct mode (false)
 */
__ALWAYS_STATIC_INLINE void csi_aplic_set_domaincfg(unsigned long aplic_base, uint8_t enable, uint8_t msi_mode)
{
    uint32_t val = 0;
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    if (enable) {
        val |= APLIC_DOMAINCFG_IE;
    }

    if (msi_mode) {
        val |= APLIC_DOMAINCFG_DM;
    }

    rv_writel(val, (uintptr_t)&aplic->DOMAINCFG);
}

/**
  \brief        Configure interrupt source characteristics(source mode)
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Interrupt source ID to configure (1-1023)
  \param [in]   src_mode        Source Mode (inactive, detached, edge, level)
 */
__ALWAYS_STATIC_INLINE void csi_aplic_set_sourcecfg_sm(unsigned long aplic_base, uint32_t irq_num, uint8_t src_mode)
{
    uint32_t val = 0;
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num (1-1023, 0 is invalid)
    if (irq_num == 0 || irq_num > 1023) {
        return;
    }

    // D = 0, (bit 10)
    val &= ~(1UL << 10);
    // Set the source mode (bits 0-2)
    val &= ~0x7;
    val |= src_mode & 0x7;

    rv_writel(val, (uintptr_t)&aplic->SOURCECFG[irq_num - 1]);
}

/**
  \brief        Configure interrupt source characteristics(delegate)
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Interrupt source ID to configure (1-1023)
  \param [in]   child_idx       Child domain index
 */
__ALWAYS_STATIC_INLINE void csi_aplic_set_sourcecfg_delegate(unsigned long aplic_base, uint32_t irq_num, uint16_t child_idx)
{
    uint32_t val = 0;
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num (1-1023, 0 is invalid)
    if (irq_num == 0 || irq_num > 1023) {
        return;
    }
    // D = 1, Set delegation bit (bit 10)
    val |= (1UL << 10);
    // set Child Index (bits 0-9)
    val &= ~(0x3FF);
    val |= child_idx & 0x3FF;

    rv_writel(val, (uintptr_t)&aplic->SOURCECFG[irq_num - 1]);
}

/**
  \brief        Controls whether interrupts that are targeted to the corresponding hart
  \details      This function configures the IDC (Interrupt Delivery Control) structure
  \param [in]   aplic_base      APLIC base address
  \param [in]   hart_id         Hart index number (0 to max supported harts-1)
  \param [in]   idelivery       0: disable interrupt delivery, 1: enable interrupt delivery
 */
__ALWAYS_STATIC_INLINE void csi_aplic_set_idc_delivery(unsigned long aplic_base, uint32_t hart_id, uint32_t idelivery)
{
    // IDC structures start at offset 0x4000 from APLIC base
    // Each IDC is 32 bytes, so IDC[n] is at offset 0x4000 + n*32
    APLIC_IDC_Type* IDC = (APLIC_IDC_Type*)((uintptr_t)aplic_base + APLIC_IDC_OFFSET(hart_id));
    rv_writel(idelivery & 0x1, (uintptr_t)&IDC->IDELIVERY);
}

/**
  \brief        Set the interrupt threshold for an interrupt to be signaled to the corresponding hart
  \param [in]   aplic_base      APLIC base address
  \param [in]   hart_id         Hart index number (0 to max supported harts-1)
  \param [in]   ithreshold      Priority numbers from 0 to 2^IPRIOLEN-1
 */
__ALWAYS_STATIC_INLINE void csi_aplic_set_idc_ithreshold(unsigned long aplic_base, uint32_t hart_id, uint32_t ithreshold)
{
    // IDC structures start at offset 0x4000 from APLIC base
    // Each IDC is 32 bytes, so IDC[n] is at offset 0x4000 + n*32
    APLIC_IDC_Type* IDC = (APLIC_IDC_Type*)((uintptr_t)aplic_base + APLIC_IDC_OFFSET(hart_id));
    rv_writel(ithreshold, (uintptr_t)&IDC->ITHRESHOLD);
}

/**
  \brief        Get the max interrupt priority number
  \details      Probe by writing all 1s and reading back to determine implemented bits
  \param [in]   aplic_base      APLIC base address
  \return                       The max interrupt priority number
 */
__ALWAYS_STATIC_INLINE int csi_aplic_max_ipriority_number_probe(unsigned long aplic_base)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Use any valid TARGET register to probe IPRIOLEN
    // Write all 1s to the iprio field (bits 0-7 or 0-15 depending on implementation)
    uint32_t original = rv_readl((uintptr_t)&aplic->TARGET[1]);

    // Write maximum possible priority value
    rv_writel(0xFF, (uintptr_t)&aplic->TARGET[1]);

    // Read back to see which bits are implemented
    uint32_t readback = rv_readl((uintptr_t)&aplic->TARGET[1]);

    // Restore original value
    rv_writel(original, (uintptr_t)&aplic->TARGET[1]);

    // Extract iprio field (lower bits)
    uint32_t max_priority = readback & 0xFF;

    // If no bits are implemented, return 0
    if (max_priority == 0) {
        return 0;
    }

    // Count the number of implemented bits to determine max priority
    int bits = 0;
    uint32_t temp = max_priority;
    while (temp) {
        if (temp & 1) bits++;
        temp >>= 1;
    }

    return (1 << bits) - 1;
}

/**
  \brief        Set APLIC target register, this function is only used in direct mode
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
  \param [in]   hart_id         Hart index in target register
  \param [in]   iprio           The priority of interrupt
 */
__ALWAYS_STATIC_INLINE void csi_aplic_set_target_direct(unsigned long aplic_base, uint32_t irq_num, uint32_t hart_id, uint32_t iprio)
{
    uint32_t val = 0;
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return;
    }

    // In direct mode:
    // Bits 31:18: Hart Index (14 bits)
    // Bits 17:8: Reserved (should be 0)
    // Bits 7:0: IPRIO (interrupt priority)

    val = ((hart_id & 0x3FFF) << 18) | (iprio & 0xFF);

    rv_writel(val, (uintptr_t)&aplic->TARGET[irq_num - 1]);
}

/**
  \brief        Enable an APLIC interrupt
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
 */
__ALWAYS_STATIC_INLINE void csi_aplic_enable_irq(unsigned long aplic_base, uint32_t irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return;
    }

    rv_writel(irq_num, (uintptr_t)&aplic->SETIENUM);
}

/**
  \brief        Disable an APLIC interrupt
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
 */
__ALWAYS_STATIC_INLINE void csi_aplic_disable_irq(unsigned long aplic_base, uint32_t irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return;
    }

    rv_writel(irq_num, (uintptr_t)&aplic->CLRIENUM);
}

/**
  \brief        Check Interrupt is Enabled
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
  \return                       0  Interrupt status is not enabled.
                                1  Interrupt status is enabled.
 */
__ALWAYS_STATIC_INLINE uint32_t csi_aplic_get_enabled_irq(unsigned long aplic_base, uint32_t irq_num)
{
    uint32_t reg_idx;
    uint32_t bit_pos;
    uint32_t val;
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return 0;
    }

    // Calculate register index and bit position
    reg_idx = irq_num / 32;
    bit_pos = irq_num % 32;

    // Read from SETIE register (reading SETIE returns current enable bits)
    val = rv_readl((uintptr_t)&aplic->SETIE[reg_idx]);

    return (val >> bit_pos) & 0x1;
}

/**
  \brief        Check Interrupt is Pending or not
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
  \return                       0  Interrupt status is not pending.
                               1  Interrupt status is pending.
 */
__ALWAYS_STATIC_INLINE uint32_t csi_aplic_get_pending_irq(unsigned long aplic_base, uint32_t irq_num)
{
    uint32_t reg_idx;
    uint32_t bit_pos;
    uint32_t val;
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return 0;
    }

    // Calculate register index and bit position
    reg_idx = irq_num / 32;
    bit_pos = irq_num % 32;

    // Read from SETIP register (reading SETIP returns current pending bits)
    val = rv_readl((uintptr_t)&aplic->SETIP[reg_idx]);

    return (val >> bit_pos) & 0x1;
}

/**
  \brief        Set Pending Interrupt
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
 */
__ALWAYS_STATIC_INLINE void csi_aplic_set_pending_irq(unsigned long aplic_base, uint32_t irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return;
    }

    rv_writel(irq_num, (uintptr_t)&aplic->SETIPNUM);
}

/**
  \brief        Clear Pending Interrupt
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
 */
__ALWAYS_STATIC_INLINE void csi_aplic_clear_pending_irq(unsigned long aplic_base, uint32_t irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return;
    }

    rv_writel(irq_num, (uintptr_t)&aplic->CLRIPNUM);
}

/**
  \brief        Set Interrupt Priority
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
  \param [in]   priority        The priority to set
 */
__ALWAYS_STATIC_INLINE void csi_aplic_set_prio(unsigned long aplic_base, uint32_t irq_num, uint32_t priority)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return;
    }

    uint32_t val = (rv_readl((uintptr_t)&aplic->TARGET[irq_num - 1]) & 0xFFFFFF00);
    val |= (priority & 0xFF);
    rv_writel(val, (uintptr_t)&aplic->TARGET[irq_num - 1]);
}

/**
  \brief        Get Interrupt Priority
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC (1-1023)
  \return                       The priority
 */
__ALWAYS_STATIC_INLINE uint32_t csi_aplic_get_prio(unsigned long aplic_base, uint32_t irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    // Validate irq_num
    if (irq_num == 0 || irq_num > 1023) {
        return 0;
    }

    uint32_t val = (rv_readl((uintptr_t)&aplic->TARGET[irq_num - 1]) & 0xFF);
    return val;
}

/**
  \brief        Set APLIC target register EIID field (MSI identity)
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC
  \param [in]   eiid            MSI identity number (bits 10:0)
 */
__STATIC_INLINE void csi_aplic_set_target_eiid(unsigned long aplic_base, uint32_t irq_num, uint32_t eiid)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;
    uint32_t val = rv_readl((uintptr_t)&aplic->TARGET[irq_num - 1]);
    val &= ~0x7FF;               /* Clear bits 10:0 (EIID field) */
    val |= (eiid & 0x3FF);       /* Set new EIID value */
    rv_writel(val, (uintptr_t)&aplic->TARGET[irq_num - 1]);
}

/**
  \brief        Read EIID from target register, only used in msi mode (DM=1)
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC
  \return                       EIID of target register
 */
__STATIC_INLINE uint32_t csi_aplic_get_target_eiid(unsigned long aplic_base, uint32_t irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;
    return (rv_readl((uintptr_t)&aplic->TARGET[irq_num - 1])& 0x3FF);
}

/**
  \brief        Set APLIC target register, this function is only used in msi mode (DM=1)
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC
  \param [in]   hart_id         Hart index in target register
  \param [in]   guest_index     Guest id in target register
  \param [in]   eiid            Namely the corresponding msi number written to IMSIC, also the priority of MSI
 */
__STATIC_INLINE void csi_aplic_set_target_msi(unsigned long aplic_base, uint32_t irq_num, uint32_t hart_id, uint32_t guest_index, uint32_t eiid)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;
    rv_writel(((hart_id & 0x3f) << 18) | (guest_index & 0x3f) << 12 | (eiid & 0x3ff), (uintptr_t)&aplic->TARGET[irq_num - 1]);
}

/**
  \brief        Set APLIC target register Hart Index field
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC
  \param [in]   hart_id         Hart index (bits 31:18)
 */
__STATIC_INLINE void csi_aplic_set_target_hart(unsigned long aplic_base, uint32_t irq_num, uint32_t hart_id)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;
    uint32_t val = rv_readl((uintptr_t)&aplic->TARGET[irq_num - 1]);
    val &= ~(0x3FFF << 18);           /* Clear bits 31:18 (Hart Index field) */
    val |= ((hart_id & 0x3FFF) << 18);  /* Set new Hart Index value */
    rv_writel(val, (uintptr_t)&aplic->TARGET[irq_num - 1]);
}

/**
  \brief        Read target hart from target register, only used in msi mode (DM=1)
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC
  \return                       Target hart
 */
__STATIC_INLINE uint32_t csi_aplic_get_target_hart(unsigned long aplic_base, uint32_t irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;
    return ((rv_readl((uintptr_t)&aplic->TARGET[irq_num - 1]) >> 18) & 0x3FFF);
}

/**
  \brief        Set APLIC target register Guest Index field
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC
  \param [in]   guest_index     Guest index (bits 17:12)
 */
__STATIC_INLINE void csi_aplic_set_target_guest(unsigned long aplic_base, uint32_t irq_num, uint32_t guest_index)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;
    uint32_t val = rv_readl((uintptr_t)&aplic->TARGET[irq_num - 1]);
    val &= ~(0x3F << 12);             /* Clear bits 17:12 (Guest Index field) */
    val |= ((guest_index & 0x3F) << 12);  /* Set new Guest Index value */
    rv_writel(val, (uintptr_t)&aplic->TARGET[irq_num - 1]);
}

/**
  \brief        Get APLIC target register Guest Index field
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         Number of interrupt source connected to APLIC
  \return                       Guest index value (bits 17:12)
 */
__STATIC_INLINE uint32_t csi_aplic_get_target_guest(unsigned long aplic_base, uint32_t irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;
    uint32_t val = rv_readl((uintptr_t)&aplic->TARGET[irq_num - 1]);
    return ((val >> 12) & 0x3F);  /* Extract bits 17:12 */
}

/**
  \brief        Indicates the current highest-priority pending-and-enabled interrupt targeted to this hart
  \param [in]   aplic_base      APLIC base address
  \param [in]   hart_id         Hart index number (0 to max supported harts-1)
  \return                       The current highest-priority pending-and-enabled interrupt ID
 */
__ALWAYS_STATIC_INLINE uint32_t csi_aplic_read_topi(unsigned long aplic_base, uint32_t hart_id)
{
    // IDC structures start at offset 0x4000 from APLIC base
    // Each IDC is 32 bytes, so IDC[n] is at offset 0x4000 + n*32
    APLIC_IDC_Type* IDC = (APLIC_IDC_Type*)((uintptr_t)aplic_base + APLIC_IDC_OFFSET(hart_id));
    uint32_t irqno = rv_readl((uintptr_t)&IDC->TOPI);
    return (irqno >> 16) & 0x3FF;
}

/**
  \brief        Indicates the current highest-priority pending-and-enabled interrupt targeted to this hart
  \details      When this value is not zero, reading claimi has the simultaneous side effect of clearing the pending bit for the reported interrupt identity
  \param [in]   aplic_base      APLIC base address
  \param [in]   hart_id         Hart index number (0 to max supported harts-1)
  \return                       The current highest-priority pending-and-enabled interrupt ID
 */
__ALWAYS_STATIC_INLINE uint32_t csi_aplic_read_claimi(unsigned long aplic_base, uint32_t hart_id)
{
    // IDC structures start at offset 0x4000 from APLIC base
    // Each IDC is 32 bytes, so IDC[n] is at offset 0x4000 + n*32
    APLIC_IDC_Type* IDC = (APLIC_IDC_Type*)((uintptr_t)aplic_base + APLIC_IDC_OFFSET(hart_id));
    uint32_t irqno = rv_readl((uintptr_t)&IDC->CLAIMI);
    return (irqno >> 16) & 0x3FF;
}

/**
  \brief        Retrigger a level interrupt in APLIC
  \details      For level-type interrupts, this function writes to the APLIC's setipnum register
                to ensure that an active interrupt can be triggered again. A write to setipnum is
                ignored if the value written is not an active interrupt source.
  \param [in]   aplic_base      APLIC base address
  \param [in]   irq_num         The interrupt source number to trigger
  \note         According to RISC-V AIA specification, writing to setipnum will set the
                pending bit for the specified interrupt in APLIC.
 */
__STATIC_INLINE void csi_aplic_retrigger_level_irq(unsigned long aplic_base, unsigned int irq_num)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    /* Calculate register index and bit position */
    uint32_t reg_idx = irq_num / 32;
    uint32_t bit_pos = irq_num % 32;

    /* Check if interrupt source is valid (sourcecfg should not be 0/inactive) */
    uint32_t sourcecfg = rv_readl((uintptr_t)&aplic->SOURCECFG[irq_num - 1]);
    uint32_t source_mode = sourcecfg & 0x7;  /* SM field is bits [2:0] */

    /* Check if it's a level-triggered interrupt
     * Source Mode: 6 (0b110) = Level1 (high level active)
     *              7 (0b111) = Level0 (low level active)
     */
    if (source_mode != APLIC_SOURCECFG_SM_LEVEL1_HIGH
        && source_mode != APLIC_SOURCECFG_SM_LEVEL0_LOW) {
        /* Not a level-triggered interrupt, no need to retrigger */
        return;
    }

    /* Check if the rectified input is still asserted (IN_CLRIP bit is 1)
     * According to AIA spec section 4.9.2:
     * "Write the APLIC's source identity number to setipnum register.
     *  This will cause the interrupt's pending bit to be set to one again
     *  if the source is still asserting an interrupt."
     */
    if (rv_readl((uintptr_t)&aplic->IN_CLRIP[reg_idx]) & (1U << bit_pos)) {
        /* Input signal is still asserted, retrigger by writing to setipnum */
        rv_writel(irq_num, (uintptr_t)&aplic->SETIPNUM);
    }

    /* If IN_CLRIP bit is 0, the input level has been de-asserted,
     * no need to retrigger. The next low-to-high transition will
     * automatically trigger a new interrupt.
     */
}

/**
  \brief        Set Machine-level MSI address configuration
  \details      This configures the base address where APLIC sends MSIs to target IMSICs.
                Should be configured by trusted M-mode software at boot and then locked.
  \param [in]   aplic_base      APLIC base address
  \param [in]   base_ppn        Base Physical Page Number of IMSIC region (bits [43:0] of PPN)
  \param [in]   lhxw            Width of low hart index field
  \param [in]   hhxw            Width of high hart index field
  \param [in]   lhxs            Shift amount for low hart index
  \param [in]   hhxs            Shift amount for high hart index
 */
__STATIC_INLINE void csi_aplic_set_mmsiaddrcfg(unsigned long aplic_base,
                                                uint64_t base_ppn,
                                                uint8_t lhxw,
                                                uint8_t hhxw,
                                                uint8_t lhxs,
                                                uint8_t hhxs)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    /* Low 32 bits: base_ppn[31:0] */
    uint32_t cfg_lo = (uint32_t)(base_ppn & 0xFFFFFFFFUL);

    /* High 32 bits: L=0 (unlocked), HHXS, LHXS, HHXW, LHXW, base_ppn[43:32] */
    uint32_t cfg_hi = 0;
    cfg_hi |= ((hhxs & 0x1F) << APLIC_MMSIADDRCFGH_HHXS_POS);
    cfg_hi |= ((lhxs & 0x7) << APLIC_MMSIADDRCFGH_LHXS_POS);
    cfg_hi |= ((hhxw & 0x7) << APLIC_MMSIADDRCFGH_HHXW_POS);
    cfg_hi |= ((lhxw & 0xF) << APLIC_MMSIADDRCFGH_LHXW_POS);
    cfg_hi |= (uint32_t)((base_ppn >> 32) & 0xFFF);

    rv_writel(cfg_lo, (uintptr_t)&aplic->MMSIADDRCFG);
    rv_writel(cfg_hi, (uintptr_t)&aplic->MMSIADDRCFGH);
}

/**
  \brief        Lock Machine-level MSI address configuration
  \details      Once locked, MMSIADDRCFG/MMSIADDRCFGH cannot be modified until system reset.
                This prevents malicious software from redirecting MSIs.
  \param [in]   aplic_base      APLIC base address
 */
__STATIC_INLINE void csi_aplic_lock_mmsiaddrcfg(unsigned long aplic_base)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    uint32_t cfg_hi = rv_readl((uintptr_t)&aplic->MMSIADDRCFGH);
    cfg_hi |= APLIC_MMSIADDRCFGH_L_MSK;  /* Set Lock bit */
    rv_writel(cfg_hi, (uintptr_t)&aplic->MMSIADDRCFGH);
}

/**
  \brief        Check if Machine-level MSI address configuration is locked
  \param [in]   aplic_base      APLIC base address
  \return                       1 if locked, 0 if unlocked
 */
__STATIC_INLINE uint32_t csi_aplic_is_mmsiaddrcfg_locked(unsigned long aplic_base)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    uint32_t cfg_hi = rv_readl((uintptr_t)&aplic->MMSIADDRCFGH);
    return (cfg_hi & APLIC_MMSIADDRCFGH_L_MSK) ? 1 : 0;
}

/**
  \brief        Get Machine-level MSI address configuration
  \param [in]   aplic_base      APLIC base address
  \param [out]  base_ppn        Pointer to store base PPN (can be NULL)
  \param [out]  lhxw            Pointer to store LHXW (can be NULL)
  \param [out]  hhxw            Pointer to store HHXW (can be NULL)
  \param [out]  lhxs            Pointer to store LHXS (can be NULL)
  \param [out]  hhxs            Pointer to store HHXS (can be NULL)
  \return                       1 if locked, 0 if unlocked
 */
__STATIC_INLINE uint32_t csi_aplic_get_mmsiaddrcfg(unsigned long aplic_base,
                                                    uint64_t *base_ppn,
                                                    uint8_t *lhxw,
                                                    uint8_t *hhxw,
                                                    uint8_t *lhxs,
                                                    uint8_t *hhxs)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    uint32_t cfg_lo = rv_readl((uintptr_t)&aplic->MMSIADDRCFG);
    uint32_t cfg_hi = rv_readl((uintptr_t)&aplic->MMSIADDRCFGH);

    if (base_ppn) {
        *base_ppn = ((uint64_t)(cfg_hi & 0xFFF) << 32) | cfg_lo;
    }
    if (lhxw) {
        *lhxw = (cfg_hi >> APLIC_MMSIADDRCFGH_LHXW_POS) & 0xF;
    }
    if (hhxw) {
        *hhxw = (cfg_hi >> APLIC_MMSIADDRCFGH_HHXW_POS) & 0x7;
    }
    if (lhxs) {
        *lhxs = (cfg_hi >> APLIC_MMSIADDRCFGH_LHXS_POS) & 0x7;
    }
    if (hhxs) {
        *hhxs = (cfg_hi >> APLIC_MMSIADDRCFGH_HHXS_POS) & 0x1F;
    }

    return (cfg_hi & APLIC_MMSIADDRCFGH_L_MSK) ? 1 : 0;
}

/**
  \brief        Set Supervisor-level MSI address configuration
  \param [in]   aplic_base      APLIC base address
  \param [in]   base_ppn        Base Physical Page Number of S-mode IMSIC region
  \param [in]   lhxs            Shift amount for low hart index
 */
__STATIC_INLINE void csi_aplic_set_smsiaddrcfg(unsigned long aplic_base,
                                                uint64_t base_ppn,
                                                uint8_t lhxs)
{
    APLIC_Type *aplic = (APLIC_Type *)aplic_base;

    /* Low 32 bits: base_ppn[31:0] */
    uint32_t cfg_lo = (uint32_t)(base_ppn & 0xFFFFFFFFUL);

    /* High 32 bits: LHXS and base_ppn[43:32] */
    uint32_t cfg_hi = 0;
    cfg_hi |= ((lhxs & 0x7) << APLIC_SMSIADDRCFGH_LHXS_POS);
    cfg_hi |= (uint32_t)((base_ppn >> 32) & 0xFFF);

    rv_writel(cfg_lo, (uintptr_t)&aplic->SMSIADDRCFG);
    rv_writel(cfg_hi, (uintptr_t)&aplic->SMSIADDRCFGH);
}

#endif /* CONFIG_INTC_APLIC || CONFIG_INTC_CLIC_APLIC || CONFIG_INTC_IMSIC_APLIC */
#endif
