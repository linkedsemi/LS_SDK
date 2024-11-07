/**
 * @file reg_base_addr.h
 * @author ls
 * @brief the base address mapping for the system address space
 * @version 0.1
 * @date 2022-01-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef REG_BASE_ADDR_H_
#define REG_BASE_ADDR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define QSH_MEM_ROM_ADDR           (0x01000000)
#define QSH_MEM_CACHE1_ADDR        (0x08000000)
#define QSH_MEM_CACHE2_ADDR        (0x0C000000)
#define QSH_MEM_SRAM1_ADDR         (0x10000000)
#define QSH_MEM_SRAM2_ADDR         (0x10080000)
#define QSH_MEM_PERIPH_ADDR        (0x40000000)

#define FLASH_BASE_ADDR            (0x08000000)
#define QSH_PER_QSPI1_ADDR         (0x40000000)
#define QSH_PER_QSPI2_ADDR         (0x40001000)
#define QSH_PER_USB1_ADDR          (0x40002000)
#define QSH_PER_USB2_ADDR          (0x40003000)

#define QSH_SYSC_CACHE1_ADDR       (0x40010000)
#define QSH_SYSC_CACHE2_ADDR       (0x40011000)
#define QSH_SYSC_CPU_ADDR          (0x40012000)
#define QSH_SYSC_AWO_ADDR          (0x40013000)

#define QSH_PER_ECC_ADDR           (0x40018000)
#define QSH_PER_SHA_ADDR           (0x40018400)
#define QSH_PER_CRC_ADDR           (0x40018800)
#define QSH_PER_CALC_ADDR          (0x40018C00)
#define QSH_PER_CRYPT_ADDR         (0x40019000)
#define QSH_PER_SM4_ADDR           (0x40019400)

#define QSH_PMU_RG_ADDR            (0x4001F000)
#define QSH_PMU_TIM_ADDR           (0x4001F400)
#define QSH_PMU_WDT_ADDR           (0x4001F800)
#define QSH_PMU_RTC_ADDR           (0x4001FC00)
#define QSH_PER_OTBN_ADDR          (0x40020000)

#define QSH_PER_UART1_ADDR         (0x40087000)
#define QSH_PER_UART2_ADDR         (0x40087400)
#define QSH_PER_DWUART1_ADDR       (0x40087800)
#define QSH_PER_DWUART2_ADDR       (0x40087C00)
#define QSH_PER_DWUART3_ADDR       (0x40088000)
#define QSH_PER_DWUART4_ADDR       (0x40088400)

#define QSH_SYSC_PER_ADDR          (0x4008FC00)

#define QSH_PER_MJTAG1_ADDR        (0x40092000)
#define QSH_PER_MJTAG2_ADDR        (0x40092400)
#define QSH_PER_MJTAG3_ADDR        (0x40092800)

#ifdef __cplusplus
}
#endif

#endif
