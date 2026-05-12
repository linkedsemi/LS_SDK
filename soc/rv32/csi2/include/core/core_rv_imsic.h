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

#ifndef __CORE_RV_IMSIC_H__
#define __CORE_RV_IMSIC_H__

#ifndef __ASSEMBLER__
#include <stdint.h>
#include <stdbool.h>
#include <core/csi_rv_common.h>
#include <core/csi_rv_encoding.h>
#include <drv/common.h>
#endif

#if CONFIG_INTC_IMSIC_APLIC
#ifndef CONFIG_NR_CPUS
#define CONFIG_NR_CPUS 1
#endif

#ifndef IMSIC_IPI_IRQ
#define IMSIC_IPI_IRQ 1
#endif

#define IMSIC_ALLOCATABLE_IRQ_BASE 17

/* IMSIC Base Address - Should be defined in your platform config */
#ifndef CONFIG_IMSIC_BASE
#define IMSIC              ((unsigned long*)0xF00000000000UL)
#else
#define IMSIC              ((unsigned long*)CONFIG_IMSIC_BASE)
#endif

#if CONFIG_IMSIC_S_BASE
#define IMSIC_S                    ((IMSIC_Type*)0xF00010000000UL)
#else
#define IMSIC_S                    ((unsigned long*)CONFIG_IMSIC_S_BASE)
#endif

/* IMSIC Memory Map Offsets */
#define IMSIC_SETEIPNUM_LE      0x00
#define IMSIC_SETEIPNUM_BE      0x04
#define IMSIC_SIZE_PER_HART     0x1000

/* IMSIC Interrupt File Size */
#define IMSIC_MAX_INTERRUPTS    (2048U)
#define IMSIC_MAX_EIP_REGS      (IMSIC_MAX_INTERRUPTS / 32)
#define IMSIC_MAX_EIE_REGS      (IMSIC_MAX_INTERRUPTS / 32)

/* IMSIC Indirect Register Selection Values */
#define IMSIC_EIDELIVERY        0x70
#define IMSIC_EITHRESHOLD       0x72
#define IMSIC_EIP_BASE          0x80
#define IMSIC_EIE_BASE          0xC0

/* EITHRESHOLD Register Bits */
#define IMSIC_EITHRESHOLD_MASK          0x00000FFF
#define IMSIC_EITHRESHOLD_SHIFT         0

/* TOPEI Register Bits */
#define IMSIC_TOPEI_ID_MASK             0x03FF0000
#define IMSIC_TOPEI_ID_SHIFT            16
#define IMSIC_TOPEI_PRIO_MASK           0x00000FFF
#define IMSIC_TOPEI_PRIO_SHIFT          0

/* Interrupt Priority Levels */
#define IMSIC_MAX_PRIORITY              0xFF
#define IMSIC_MIN_PRIORITY              0x01
#define IMSIC_DISABLE_PRIORITY          0x00

#ifndef __ASSEMBLER__

/* Message Source Type */
typedef enum {
    MSI_SOURCE_NONE = 0,
    MSI_SOURCE_APLIC = 1,
    MSI_SOURCE_CUSTOM = 2
} msi_source_t;

/**
  \brief        MSI (Message Signaled Interrupt) entry descriptor structure
  \details      Describes an MSI interrupt source and its associated device.
 */
struct msi_entry {
    uint32_t src_id;            /**< Interrupt source ID */
    csi_dev_t* dev;             /**< Pointer to interrupt device */
    msi_source_t source_type;   /**< Message source type */
};

typedef struct msi_entry* msi_entry_t;

/**
  \brief        IMSIC Memory Mapped Registers Structure
  \details      According to RISC-V AIA specification, this structure represents the
                memory-mapped registers for triggering MSIs via IMSIC.
 */
typedef struct {
    __IOM uint32_t SETEIPNUM_LE;    /**< Set External Interrupt Pending by Number (Little-Endian) */
    __IOM uint32_t SETEIPNUM_BE;    /**< Set External Interrupt Pending by Number (Big-Endian) */
} IMSIC_Type;

/**
  \brief        EITHRESHOLD Register Structure
  \details      According to RISC-V AIA specification, this register sets the priority
                threshold for external interrupt delivery.
 */
typedef union {
    struct {
        uint32_t THRESHOLD : 12;     /**< Interrupt priority threshold (bits 11:0) */
        uint32_t reserved : 20;      /**< Reserved bits (bits 31:12) */
    } b;
    uint32_t w;                      /**< Word access to entire register */
} IMSIC_EITHRESHOLD_Type;

/**
  \brief        TOPEI Register Structure
  \details      According to RISC-V AIA specification, this register contains the identity
                and priority of the highest-priority pending external interrupt.
 */
typedef union {
    struct {
        uint32_t PRIO : 12;          /**< Priority of top external interrupt (bits 11:0) */
        uint32_t reserved0 : 4;      /**< Reserved (bits 15:12) */
        uint32_t ID : 10;            /**< Identity of top external interrupt (bits 25:16) */
        uint32_t reserved1 : 6;      /**< Reserved (bits 31:26) */
    } b;
    uint32_t w;                      /**< Word access to entire register */
} IMSIC_TOPEI_Type;

/**
  \brief        Global IRQ table for each CPU
  \details      Table storing device pointers for each IMSIC interrupt on each CPU.
 */
extern csi_dev_t* g_cpu_irq_table[CONFIG_NR_CPUS][IMSIC_MAX_INTERRUPTS];

/**
  \brief        Bitmap for tracking allocated interrupts per CPU
  \details      Bitmap tracking which IMSIC interrupts have been allocated on each CPU.
 */
extern uint32_t g_irq_allocated_bitmap[CONFIG_NR_CPUS][IMSIC_MAX_EIP_REGS];

/**
  \brief        MSI mapping table for each CPU
  \details      Table storing MSI entry information for each interrupt on each CPU.
 */
extern volatile msi_entry_t g_msi_map[CONFIG_NR_CPUS][IMSIC_MAX_INTERRUPTS];

/**
  \brief        Currently handling MSI number for each CPU
  \details      Tracks which MSI interrupt is currently being handled on each CPU.
 */
extern volatile uint32_t g_handing_msi_num[CONFIG_NR_CPUS];
/**
  \brief        Allocate an IMSIC interrupt number for a specific CPU
  \details      According to RISC-V AIA specification, this function allocates an interrupt number
                from the IMSIC interrupt file for the specified CPU.
  \param [in]   cpu_id              Target CPU ID
  \param [in]   irq_msg_ctrl_type   Message source type (APLIC or custom)
  \param [in]   aplic_line_id       APLIC line ID for the interrupt source
  \return                           Allocated IMSIC interrupt number on success, negative value on failure
 */
int csi_imsic_irqnum_alloc(int cpu_id, msi_source_t irq_msg_ctrl_type, uint32_t aplic_line_id);

/**
  \brief        Free an allocated IMSIC interrupt number
  \details      Releases an IMSIC interrupt number back to the pool for reuse.
  \param [in]   cpu_id            Target CPU ID
  \param [in]   imsic_irqnum      IMSIC interrupt number to free
  \return                         0 on success, negative value on failure
 */
int csi_imsic_irqnum_free(int cpu_id, int imsic_irqnum);

/**
  \brief        Attach an interrupt handler to an IMSIC interrupt
  \details      Registers a simple interrupt handler function for the specified IMSIC interrupt.
  \param [in]   cpuid          Target CPU ID
  \param [in]   msi_num        IMSIC interrupt number
  \param [in]   irq_handler    Pointer to the interrupt handler function
 */
void csi_imsic_irq_attach(int cpuid, int msi_num, void *irq_handler);

/**
  \brief        Attach an interrupt handler with argument to an IMSIC interrupt
  \details      Registers an interrupt handler function with an argument for the specified IMSIC interrupt.
  \param [in]   cpuid           Target CPU ID
  \param [in]   msi_num         IMSIC interrupt number
  \param [in]   irq_handler2    Pointer to the interrupt handler function with argument
  \param [in]   arg             Argument to be passed to the interrupt handler
 */
void csi_imsic_irq_attach2(int cpuid, int msi_num, void (*irq_handler2)(uint32_t, void*), void* arg);

/**
  \brief        Detach an interrupt handler from an IMSIC interrupt
  \details      Unregisters the interrupt handler for the specified IMSIC interrupt.
  \param [in]   cpuid     Target CPU ID
  \param [in]   msi_num   IMSIC interrupt number
  \return                 CSI_OK on success, error code on failure
 */
csi_error_t csi_imsic_irq_detach(int cpuid, int msi_num);

/* Direct CSR access macros */
#define __get_MTOPEI()          rv_csr_read(CSR_MTOPEI)
#define __set_MTOPEI(val)       rv_csr_write(CSR_MTOPEI, val)
#define __get_STOPEI()          rv_csr_read(CSR_STOPEI)
#define __set_STOPEI(val)       rv_csr_write(CSR_MTOPEI, val)

/**
  \brief        IMSIC CSR Access Functions
  \defgroup     IMSIC_CSR_Access
  \details      Direct and indirect CSR access functions for IMSIC registers
  @{
 */

/**
  \brief        Read the TOPEI (Top External Interrupt) CSR
  \details      According to RISC-V AIA specification, TOPEI CSR contains the identity and priority
                of the highest-priority pending external interrupt.
  \return       TOPEI register value containing top interrupt ID and priority
 */
__ALWAYS_STATIC_INLINE uint32_t csi_imsic_read_topei(void)
{
#if CONFIG_RISCV_SMODE
    return __get_STOPEI();
#else
    return __get_MTOPEI();
#endif
}

/**
  \brief        Write to the TOPEI (Top External Interrupt) CSR
  \details      Writes a value to the TOPEI CSR to claim or complete an interrupt.
  \param [in]   value    Value to write to TOPEI register
 */
__ALWAYS_STATIC_INLINE void csi_imsic_write_topei(uint32_t value)
{
#if CONFIG_RISCV_SMODE
    __set_STOPEI(value);
#else
    __set_MTOPEI(value);
#endif
}

/**
  \brief        Read the EIDELIVERY (External Interrupt Delivery) register
  \details      According to RISC-V AIA specification, EIDELIVERY controls the delivery of
                external interrupts to the hart.
  \return       EIDELIVERY register value
 */
__ALWAYS_STATIC_INLINE uint32_t csi_imsic_read_eidelivery(void)
{
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EIDELIVERY);
    return __get_SIREG();
#else
    __set_MISELECT(IMSIC_EIDELIVERY);
    return __get_MIREG();
#endif
}

/**
  \brief        Write to the EIDELIVERY (External Interrupt Delivery) register
  \details      Enables or disables external interrupt delivery to the hart.
  \param [in]   value    Value to write (0x1 to enable, 0x0 to disable)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_write_eidelivery(uint32_t value)
{
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EIDELIVERY);
    __set_SIREG(value);
#else
    __set_MISELECT(IMSIC_EIDELIVERY);
    __set_MIREG(value);
#endif
}

/**
  \brief        Read the EITHRESHOLD (External Interrupt Threshold) register
  \details      According to RISC-V AIA specification, EITHRESHOLD sets the priority threshold
                for external interrupt delivery.
  \return       EITHRESHOLD register value (12-bit priority threshold)
 */
__ALWAYS_STATIC_INLINE uint32_t csi_imsic_read_eithreshold(void)
{
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EITHRESHOLD);
    return __get_SIREG();
#else
    __set_MISELECT(IMSIC_EITHRESHOLD);
    return __get_MIREG();
#endif
}

/**
  \brief        Write to the EITHRESHOLD (External Interrupt Threshold) register
  \details      Sets the priority threshold for external interrupt delivery.
                Interrupts with priority <= threshold will not be delivered.
  \param [in]   value    Priority threshold value (12-bit, masked with IMSIC_EITHRESHOLD_MASK)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_write_eithreshold(uint32_t value)
{
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EITHRESHOLD);
    __set_SIREG(value & IMSIC_EITHRESHOLD_MASK);
#else
    __set_MISELECT(IMSIC_EITHRESHOLD);
    __set_MIREG(value & IMSIC_EITHRESHOLD_MASK);
#endif
}

/**
  \brief        Read an EIP (External Interrupt Pending) register
  \details      According to RISC-V AIA specification, EIP registers indicate which external
                interrupts are pending.
  \param [in]   reg_index    EIP register index (0 to IMSIC_MAX_EIP_REGS-1)
  \return                    EIP register value (bitmask of pending interrupts)
 */
__ALWAYS_STATIC_INLINE uint32_t csi_imsic_read_eip(uint32_t reg_index)
{
    if (reg_index >= IMSIC_MAX_EIP_REGS) {
        return 0;
    }
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EIP_BASE + reg_index);
    return __get_SIREG();
#else
    __set_MISELECT(IMSIC_EIP_BASE + reg_index);
    return __get_MIREG();
#endif
}

/**
  \brief        Write to an EIP (External Interrupt Pending) register
  \details      Used to clear pending external interrupts by writing 1 to specific bits.
  \param [in]   reg_index    EIP register index (0 to IMSIC_MAX_EIP_REGS-1)
  \param [in]   value        Value to write (1s clear corresponding pending bits)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_write_eip(uint32_t reg_index, unsigned long value)
{
    if (reg_index >= IMSIC_MAX_EIP_REGS) {
        return;
    }
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EIP_BASE + reg_index);
    __set_SIREG(value);
#else
    __set_MISELECT(IMSIC_EIP_BASE + reg_index);
    __set_MIREG(value);
#endif
}

/**
  \brief        Read an EIE (External Interrupt Enable) register
  \details      According to RISC-V AIA specification, EIE registers control which external
                interrupts are enabled.
  \param [in]   reg_index    EIE register index (0 to IMSIC_MAX_EIE_REGS-1)
  \return                    EIE register value (bitmask of enabled interrupts)
 */
__ALWAYS_STATIC_INLINE uint32_t csi_imsic_read_eie(uint32_t reg_index)
{
    if (reg_index >= IMSIC_MAX_EIE_REGS) {
        return 0;
    }
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EIE_BASE + reg_index);
    return __get_SIREG();
#else
    __set_MISELECT(IMSIC_EIE_BASE + reg_index);
    return __get_MIREG();
#endif
}

/**
  \brief        Write to an EIE (External Interrupt Enable) register
  \details      Enables or disables external interrupts by setting/clearing bits.
  \param [in]   reg_index    EIE register index (0 to IMSIC_MAX_EIE_REGS-1)
  \param [in]   value        Value to write (1s enable corresponding interrupts)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_write_eie(uint32_t reg_index, unsigned long value)
{
    if (reg_index >= IMSIC_MAX_EIE_REGS) {
        return;
    }
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EIE_BASE + reg_index);
    __set_SIREG(value);
#else
    __set_MISELECT(IMSIC_EIE_BASE + reg_index);
    __set_MIREG(value);
#endif
}

/**
  \brief        Send an MSI (Message Signaled Interrupt) to a specific CPU via IMSIC
  \details      According to RISC-V AIA specification, this function triggers an MSI by writing
                to the SETEIPNUM_LE register of the target hart's IMSIC interrupt file.
  \param [in]   cpuid    Target CPU ID (hart ID)
  \param [in]   IRQ      IMSIC interrupt number to trigger (1 to IMSIC_MAX_INTERRUPTS-1)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_mirq_send(int cpuid, int IRQ)
{
    IMSIC_Type* imsic = (IMSIC_Type*)((unsigned long)IMSIC + cpuid * IMSIC_SIZE_PER_HART);
    rv_writel(IRQ, (uintptr_t)(&imsic->SETEIPNUM_LE));
}

/**
  \brief        Send IPI (Inter-Processor Interrupt) to multiple CPUs
  \details      Sends an IPI to all CPUs specified in the bitmask. Uses interrupt number
                IMSIC_IPI_IRQ (typically 1) as defined by the AIA specification.
  \param [in]   cpu_mask    Bitmask of target CPUs (bit i set = send to CPU i)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_ipi_send(uint32_t cpu_mask)
{
    for (int i = 0; i < CONFIG_NR_CPUS; i++) {
        if (cpu_mask & (1U << i)) {
            csi_imsic_mirq_send(i, IMSIC_IPI_IRQ);
        }
    }
}

/**
  \brief        Check if an interrupt is enabled in EIE registers
  \details      Reads the appropriate EIE register and checks if the specified interrupt
                is enabled.
  \param [in]   IRQ      Interrupt number to check
  \return                true if interrupt is enabled, false otherwise
 */
__ALWAYS_STATIC_INLINE bool csi_imsic_check_enable(uint32_t IRQ)
{
    // Calculate which EIE register contains this interrupt
    // For XLEN=32: each EIE register contains 32 interrupt enable bits
    // For XLEN=64: each even EIE register contains 64 interrupt enable bits
#if __riscv_xlen == 32
    uint32_t reg_index = IRQ / 32;
    uint32_t bit_position = IRQ % 32;
#else  // __riscv_xlen == 64
    uint32_t reg_index = (IRQ / 64) * 2;  // Only even indices are valid for RV64
    uint32_t bit_position = IRQ % 64;
#endif

    // Check if register index is valid
    if (reg_index >= IMSIC_MAX_EIE_REGS) {
        return false;
    }

    // Read the appropriate EIE register
#if CONFIG_RISCV_SMODE
    __set_SISELECT(IMSIC_EIE_BASE + reg_index);
    unsigned long eie_value = __get_SIREG();
#else
    __set_MISELECT(IMSIC_EIE_BASE + reg_index);
    unsigned long eie_value = __get_MIREG();
#endif

    // Check if the specific bit is set
    return (eie_value & (1UL << bit_position)) != 0;
}

/**
  \brief        Clear a pending interrupt in EIP registers
  \details      Clears the pending bit for the specified interrupt by writing to the
                corresponding EIP register.
  \param [in]   IRQ    Interrupt number to clear
 */
__ALWAYS_STATIC_INLINE void csi_imsic_clear_pending(int IRQ)
{
    if (IRQ < 1 || IRQ >= IMSIC_MAX_INTERRUPTS) {
        return;
    }

    // Calculate which EIE register contains this interrupt
    // For XLEN=32: each EIE register contains 32 interrupt enable bits
    // For XLEN=64: each even EIE register contains 64 interrupt enable bits
#if __riscv_xlen == 32
    uint32_t reg_index = IRQ / 32;
    uint32_t bit_position = IRQ % 32;
#else  // __riscv_xlen == 64
    uint32_t reg_index = (IRQ / 64) * 2;  // Only even indices are valid for RV64
    uint32_t bit_position = IRQ % 64;
#endif

    unsigned long val = csi_imsic_read_eip(reg_index);
    val = ~(1UL << bit_position);

    /* Write 1 to clear pending bit */
    csi_imsic_write_eip(reg_index, val);
}

/**
  \brief        Clear the IPI pending bit
  \details      Clears the pending bit for the IPI interrupt (IMSIC_IPI_IRQ).
 */
__ALWAYS_STATIC_INLINE void csi_imsic_ipi_clear(void)
{
    /* Write 1 to clear pending bit */
    csi_imsic_clear_pending(IMSIC_IPI_IRQ);
}

/**
  \brief        Check if an interrupt is pending
  \details      Reads the appropriate EIP register and checks if the specified interrupt
                is pending.
  \param [in]   IRQ      Interrupt number to check
  \return                true if interrupt is pending, false otherwise
 */
__ALWAYS_STATIC_INLINE bool csi_imsic_is_pending(int IRQ)
{
    if (IRQ < 1 || IRQ >= IMSIC_MAX_INTERRUPTS) {
        return false;
    }

    // Calculate which EIE register contains this interrupt
    // For XLEN=32: each EIE register contains 32 interrupt enable bits
    // For XLEN=64: each even EIE register contains 64 interrupt enable bits
#if __riscv_xlen == 32
    uint32_t reg_index = IRQ / 32;
    uint32_t bit_position = IRQ % 32;
#else  // __riscv_xlen == 64
    uint32_t reg_index = (IRQ / 64) * 2;  // Only even indices are valid for RV64
    uint32_t bit_position = IRQ % 64;
#endif

    uint32_t eip = csi_imsic_read_eip(reg_index);
    return (eip & (1U << bit_position)) != 0;
}

/**
  \brief        Enable an external interrupt
  \details      Sets the enable bit for the specified interrupt in the appropriate EIE register.
  \param [in]   IRQ    Interrupt number to enable (1 to IMSIC_MAX_INTERRUPTS-1)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_enable_interrupt(int IRQ)
{
    if (IRQ < 1 || IRQ >= IMSIC_MAX_INTERRUPTS) {
        return;
    }

    // Calculate which EIE register contains this interrupt
    // For XLEN=32: each EIE register contains 32 interrupt enable bits
    // For XLEN=64: each even EIE register contains 64 interrupt enable bits
#if __riscv_xlen == 32
    uint32_t reg_index = IRQ / 32;
    uint32_t bit_position = IRQ % 32;
#else  // __riscv_xlen == 64
    uint32_t reg_index = (IRQ / 64) * 2;  // Only even indices are valid for RV64
    uint32_t bit_position = IRQ % 64;
#endif

    uint32_t eie = csi_imsic_read_eie(reg_index);
    eie |= (1U << bit_position);
    csi_imsic_write_eie(reg_index, eie);
}

/**
  \brief        Disable an external interrupt
  \details      Clears the enable bit for the specified interrupt in the appropriate EIE register.
  \param [in]   IRQ    Interrupt number to disable (1 to IMSIC_MAX_INTERRUPTS-1)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_disable_interrupt(int IRQ)
{
    if (IRQ < 1 || IRQ >= IMSIC_MAX_INTERRUPTS) {
        return;
    }

    // Calculate which EIE register contains this interrupt
    // For XLEN=32: each EIE register contains 32 interrupt enable bits
    // For XLEN=64: each even EIE register contains 64 interrupt enable bits
#if __riscv_xlen == 32
    uint32_t reg_index = IRQ / 32;
    uint32_t bit_position = IRQ % 32;
#else  // __riscv_xlen == 64
    uint32_t reg_index = (IRQ / 64) * 2;  // Only even indices are valid for RV64
    uint32_t bit_position = IRQ % 64;
#endif

    uint32_t eie = csi_imsic_read_eie(reg_index);
    eie &= ~(1U << bit_position);
    csi_imsic_write_eie(reg_index, eie);
}

/**
  \brief        Set the interrupt priority threshold
  \details      Sets the priority threshold for external interrupt delivery.
                Only interrupts with priority > threshold will be delivered.
  \param [in]   threshold    Priority threshold value (0 to IMSIC_EITHRESHOLD_MASK)
 */
__ALWAYS_STATIC_INLINE void csi_imsic_set_threshold(uint32_t threshold)
{
    csi_imsic_write_eithreshold(threshold & IMSIC_EITHRESHOLD_MASK);
}

/**
  \brief        Get the current interrupt priority threshold
  \return       Current priority threshold value
 */
__ALWAYS_STATIC_INLINE uint32_t csi_imsic_get_threshold(void)
{
    return csi_imsic_read_eithreshold() & IMSIC_EITHRESHOLD_MASK;
}

/**
  \brief        Enable external interrupt delivery
  \details      Enables the delivery of external interrupts to the hart by setting EIDELIVERY to 1.
 */
__ALWAYS_STATIC_INLINE void csi_imsic_enable_delivery(void)
{
    csi_imsic_write_eidelivery(0x1);
}

/**
  \brief        Disable external interrupt delivery
  \details      Disables the delivery of external interrupts to the hart by setting EIDELIVERY to 0.
 */
__ALWAYS_STATIC_INLINE void csi_imsic_disable_delivery(void)
{
    csi_imsic_write_eidelivery(0x0);
}

#endif /* __ASSEMBLER__*/
#endif /* CONFIG_INTC_IMSIC_APLIC */
#endif /* __CORE_RV_IMSIC_H__ */
