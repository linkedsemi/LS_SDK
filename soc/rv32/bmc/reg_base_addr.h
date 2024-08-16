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

#define BMC_MEM_ROM_ADDR           (0x01000000)
#define BMC_MEM_FLASH_ADDR         (0x08000000)
#define BMC_MEM_CACHE_ADDR         (0x0C000000)
#define BMC_MEM_SRAM1_ADDR         (0x10000000)
#define BMC_MEM_SRAM2_ADDR         (0x10080000)
#define BMC_MEM_PERIPH_ADDR        (0x40000000)

#define BMC_PER_QSPI1_ADDR         (0x40000000)
#define BMC_PER_QSPI2_ADDR         (0x40001000)
#define BMC_PER_USB1_ADDR          (0x40002000)
#define BMC_PER_USB2_ADDR          (0x40003000)

#define BMC_SYSC_CACHE1_ADDR       (0x40010000)
#define BMC_SYSC_CACHE2_ADDR       (0x40011000)
#define BMC_SYSC_CPU_ADDR          (0x40012000)
#define BMC_SYSC_AWO_ADDR          (0x40013000)

#define BMC_PER_ECC_ADDR           (0x40018000)
#define BMC_PER_SHA_ADDR           (0x40018400)
#define BMC_PER_CRC_ADDR           (0x40018800)
#define BMC_PER_CALC_ADDR          (0x40018C00)
#define BMC_PER_CRYPT_ADDR         (0x40019000)
#define BMC_PER_SM4_ADDR           (0x40019400)

#define BMC_PMU_RG_ADDR            (0x4001F000)
#define BMC_PMU_TIM_ADDR           (0x4001F400)
#define BMC_PMU_WDT_ADDR           (0x4001F800)
#define BMC_PMU_RTC_ADDR           (0x4001FC00)

#define BMC_PER_UART1_ADDR         (0x40087000)
#define BMC_PER_UART2_ADDR         (0x40087400)
#define BMC_PER_DWUART1_ADDR       (0x40087800)
#define BMC_PER_DWUART2_ADDR       (0x40087C00)
#define BMC_PER_DWUART3_ADDR       (0x40088000)
#define BMC_PER_DWUART4_ADDR       (0x40088400)

#define BMC_SYSC_PER_ADDR          (0x4008FC00)

#ifdef __cplusplus
}
#endif

#endif
