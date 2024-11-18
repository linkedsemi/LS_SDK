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
#define QSH_AHB_QSPI1_ADDR         (0x40000000)
#define QSH_AHB_QSPI2_ADDR         (0x40001000)
#define QSH_AHB_USB1_ADDR          (0x40002000)
#define QSH_AHB_USB2_ADDR          (0x40003000)
#define QSH_AHB_DWDMAC0_ADDR       (0x40004000)
#define QSH_AHB_DWDMAC1_ADDR       (0x40005000)
#define QSH_AHB_ESPI1_ADDR         (0x40006000)
#define QSH_AHB_ESPI2_ADDR         (0x40007000)
#define QSH_AHB_LPC1_ADDR          (0x40008000)
#define QSH_AHB_EMMC1_ADDR         (0x40009000)
#define QSH_AHB_LPC2_ADDR          (0x4000A000)
#define QSH_AHB_DWTRNG_ADDR        (0x4000B000)
#define QSH_AHB_SPID1_ADDR         (0x4000C000)
#define QSH_AHB_SPID2_ADDR         (0x4000E000)
#define QSH_APB_CACHE1_ADDR        (0x40010000)
#define QSH_APB_CACHE2_ADDR        (0x40011000)
#define QSH_SYSC_CPU_ADDR          (0x40012000)
#define QSH_SYSC_AWO_ADDR          (0x40013000)
#define QSH_APB_IOPMP_ADDR         (0x40014000)
#define QSH_APB_OTP_CTRL_ADDR      (0x40015000)
#define QSH_APB_SHA_ADDR           (0x40018400)
#define QSH_APB_CRC_ADDR           (0x40018800)
#define QSH_APB_CALC_ADDR          (0x40018C00)
#define QSH_APB_CRYPT_ADDR         (0x40019000)
#define QSH_APB_SM4_ADDR           (0x40019400)
#define QSH_APB_ETH1_ADDR          (0x4001A000)
#define QSH_APB_ETH2_ADDR          (0x4001C000)
#define QSH_APB_FDCAN_ADDR         (0x4001E000)
#define QSH_PMU_RG_ADDR            (0x4001F000)
#define QSH_PMU_TIM_ADDR           (0x4001F400)
#define QSH_PMU_WDT_ADDR           (0x4001F800)
#define QSH_PMU_RTC_ADDR           (0x4001FC00)
#define QSH_AHB_OTBN_ADDR          (0x40020000)
#define QSH_APB_LTPI_SCM_CFG_ADDR  (0x40030000)
#define QSH_APB_LTPI_HPM_CFG_ADDR  (0x40031000)
#define QSH_APB_LTPI_PHY_CFG_ADDR  (0x40032000)
#define QSH_AHB_EMMC2_ADDR         (0x40040000)
#define QSH_APB_BSTIM1_ADDR        (0x40080000)
#define QSH_APB_BSTIM2_ADDR        (0x40080400)
#define QSH_APB_GPTIMA1_ADDR       (0x40080800)
#define QSH_APB_GPTIMA2_ADDR       (0x40080C00)
#define QSH_APB_GPTIMB1_ADDR       (0x40081000)
#define QSH_APB_GPTIMB2_ADDR       (0x40081400)
#define QSH_APB_ADTIM1_ADDR        (0x40081800)
#define QSH_APB_ADTIM2_ADDR        (0x40081C00)
#define QSH_APB_PWM_ADDR           (0x40082000)
#define QSH_APB_CAP_ADDR           (0x40082400)
#define QSH_APB_I2C1_ADDR          (0x40083000)
#define QSH_APB_I2C2_ADDR          (0x40083400)
#define QSH_APB_I2C3_ADDR          (0x40083800)
#define QSH_APB_I2C4_ADDR          (0x40083C00)
#define QSH_APB_I2C5_ADDR          (0x40084000)
#define QSH_APB_I2C6_ADDR          (0x40084400)
#define QSH_APB_I2C7_ADDR          (0x40084800)
#define QSH_APB_I2C8_ADDR          (0x40084C00)
#define QSH_APB_I2C9_ADDR          (0x40085000)
#define QSH_APB_I2C10_ADDR         (0x40085400)
#define QSH_APB_I2C11_ADDR         (0x40085800)
#define QSH_APB_I2C12_ADDR         (0x40085C00)
#define QSH_APB_I2C13_ADDR         (0x40086000)
#define QSH_APB_I2C14_ADDR         (0x40086400)
#define QSH_APB_UART1_ADDR         (0x40087000)
#define QSH_APB_UART2_ADDR         (0x40087400)
#define QSH_APB_DWUART1_ADDR       (0x40087800)
#define QSH_APB_DWUART2_ADDR       (0x40087C00)
#define QSH_APB_DWUART3_ADDR       (0x40088000)
#define QSH_APB_DWUART4_ADDR       (0x40088400)
#define QSH_APB_SPI1_ADDR          (0x40089000)
#define QSH_APB_SPI2_ADDR          (0x40089400)
#define QSH_APB_DWSPI1_ADDR        (0x40089800)
#define QSH_APB_DWSPI2_ADDR        (0x40089C00)
#define QSH_APB_SPIS1_ADDR         (0x4008A000)
#define QSH_APB_SPIS2_ADDR         (0x4008A400)
#define QSH_APB_ADC1_ADDR          (0x4008B000)
#define QSH_APB_ADC2_ADDR          (0x4008B400)
#define QSH_APB_ADC3_ADDR          (0x4008B800)
#define QSH_SYSC_PER_ADDR          (0x4008FC00)
#define QSH_APB_MJTAG1_ADDR        (0x40092000)
#define QSH_APB_MJTAG2_ADDR        (0x40092400)
#define QSH_APB_MJTAG3_ADDR        (0x40092800)

#ifdef __cplusplus
}
#endif

#endif
