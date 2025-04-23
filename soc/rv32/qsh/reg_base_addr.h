/**
 * @file reg_base_addr.h
 * @author ls
 * @brief the base address mapping for the system address space
 * @version 0.1
 * @date 2024-12-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef REG_BASE_ADDR_H_
#define REG_BASE_ADDR_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BROM_SEC_ADDR           0x01000000
#define CACHE1_ADDR             0x08000000
#define SRAM1_ADDR              0x10000000
#define SRAM2_ADDR              0x10080000
#define PSRAM_ADDR              0x18000000
#define CACHE2_ADDR             0x1c000000
#define PERIPH_ADDR             0x40000000
#define LTPI_SCM_SLV_ADDR       0x80000000
#define SEC_QSPI1_ADDR          0x40000000
#define SEC_IOPMP_ADDR          0x40001000
#define SEC_IOPMP1_ADDR         0x40001000
#define SEC_IOPMP2_ADDR         0x40001400
#define SEC_IOPMP3_ADDR         0x40001800
#define SEC_IOPMP4_ADDR         0x40001C00
#define SEC_IOPMP5_ADDR         0x40002000
#define SEC_CALC_SHA_ADDR       0x40002800
#define SEC_OTP_CTRL_ADDR       0x40003000
#define SEC_NIST_TRNG_ADDR      0x40004000
#define SEC_CALC_SHA512_ADDR    0x40005000
#define SEC_OTBN_ADDR           0x40010000
#define SEC_QSPI1_CCH_ADDR      0x40020000
#define SEC_SYSC_AWO_SEC_ADDR   0x40021000
#define SEC_SYSC_CPU_SEC_ADDR   0x40022000
#define SEC_CALC_CRC_ADDR       0x40028800
#define SEC_CALC_ADDR           0x4002a000
#define SEC_CALC_AES_ADDR       0x40029000
#define SEC_CALC_SM4_ADDR       0x40029400
#define SEC_PMU_RG_SEC_ADDR     0x4002f000
#define APP_QSPI2_ADDR          0x40040000
#define APP_DWDMAC1_ADDR        0x40041000
#define APP_DWDMAC2_ADDR        0x40042000
#define APP_USB1_ADDR           0x40043000
#define APP_USB2_ADDR           0x40044000
#define APP_ESPI1_ADDR          0x40045000
#define APP_ESPI2_ADDR          0x40046000
#define APP_LPC1_ADDR           0x40047000
#define APP_LPC2_ADDR           0x40048000
#define APP_EMMC1_CFG_ADDR      0x40049000
#define APP_EMMC2_CFG_ADDR      0x4004a000
#define APP_PSRAM_CFG_ADDR      0x4004b000
#define APP_QSPI2_CCH_ADDR      0x40060000
#define APP_SYSC_AWO_APP_ADDR   0x40061000
#define APP_SYSC_CPU_APP_ADDR   0x40062000
#define APP_PSRAM_CCH_ADDR      0x40063000
#define APP_ETH1_ADDR           0x40064000
#define APP_ETH2_ADDR           0x40066000
#define APP_FDCAN_ADDR          0x40068000
#define APP_LTPI_SCM_CFG_ADDR   0x40069000
#define APP_LTPI_HPM_CFG_ADDR   0x4006a000
#define APP_LTPI_PHY_CTL_ADDR   0x4006b000
#define APP_DWSPI3_ADDR         0x4006e000
#define APP_DWSPI4_ADDR         0x4006e400
#define APP_SPIS1_ADDR          0x4006e800
#define APP_SPIS2_ADDR          0x4006ec00
#define APP_PMU_RG_APP_ADDR     0x4006f000
#define APP_PMU_TIM_ADDR        0x4006f400
#define APP_PMU_RTC_ADDR        0x4006f800
#define APP_BSTIM1_ADDR         0x40080000
#define APP_BSTIM2_ADDR         0x40080400
#define APP_GPTIMA1_ADDR        0x40080800
#define APP_GPTIMA2_ADDR        0x40080c00
#define APP_GPTIMB1_ADDR        0x40081000
#define APP_GPTIMC1_ADDR        0x40081400
#define APP_ADTIM1_ADDR         0x40081800
#define APP_ADTIM2_ADDR         0x40081c00
#define APP_PWM_ADDR            0x40082000
#define APP_CAP_ADDR            0x40082400
#define APP_I2C2_ADDR           0x40083400
#define APP_I2C3_ADDR           0x40083800
#define APP_I2C4_ADDR           0x40083c00
#define APP_I2C5_ADDR           0x40084000
#define APP_I2C6_ADDR           0x40084400
#define APP_I2C7_ADDR           0x40084800
#define APP_I2C8_ADDR           0x40084c00
#define APP_I2C9_ADDR           0x40085000
#define APP_I2C10_ADDR          0x40085400
#define APP_I2C11_ADDR          0x40085800
#define APP_I2C12_ADDR          0x40085c00
#define APP_I2C13_ADDR          0x40086000
#define APP_I2C14_ADDR          0x40086400
#define APP_I2C15_ADDR          0x40086800
#define APP_I2C16_ADDR          0x40086c00
#define APP_UART2_ADDR          0x40087400
#define APP_DWUART3_ADDR        0x40087800
#define APP_DWUART4_ADDR        0x40087c00
#define APP_DWUART5_ADDR        0x40088000
#define APP_DWUART6_ADDR        0x40088400
#define APP_DWUART7_ADDR        0x40088800
#define APP_DWUART8_ADDR        0x40088c00
#define APP_DWUART9_ADDR        0x40089000
#define APP_DWUART10_ADDR       0x40089400
#define APP_DWUART11_ADDR       0x40089800
#define APP_DWUART12_ADDR       0x40089c00
#define APP_SPI1_ADDR           0x4008a000
#define APP_SPI2_ADDR           0x4008a400
#define APP_ADC1_ADDR           0x4008b000
#define APP_ADC2_ADDR           0x4008b400
#define APP_FILTER_ADDR         0x4008c000
#define APP_CEC_ADDR            0x4008c800
#define APP_KSCAN_ADDR          0x4008cc00
#define APP_OWM_ADDR            0x4008d000
#define APP_TRNG_ADDR           0x4008d400
#define APP_PECI1_ADDR          0x4008d800
#define APP_PECI2_ADDR          0x4008dc00
#define APP_EXT_INTR1_ADDR      0x4008e000
#define APP_EXT_INTR2_ADDR      0x4008e400
#define APP_EXT_INTR3_ADDR      0x4008e800
#define APP_EXT_INTR4_ADDR      0x4008ec00
#define APP_PARAL_ADDR          0x4008f400
#define APP_PDM_ADDR            0x4008f800
#define APP_SYSC_APP_PER_ADDR   0x4008fc00
#define APP_MJTAG1_ADDR         0x40092000
#define APP_MJTAG2_ADDR         0x40092400
#define APP_MJTAG3_ADDR         0x40092800
#define APP_I3C2_ADDR           0x40093400
#define APP_I3C3_ADDR           0x40093800
#define APP_I3C4_ADDR           0x40093c00
#define APP_I3C5_ADDR           0x40094000
#define APP_I3C6_ADDR           0x40094400
#define APP_I3C7_ADDR           0x40094800
#define APP_I3C8_ADDR           0x40094c00
#define APP_I3C9_ADDR           0x40095000
#define APP_I3C10_ADDR          0x40095400
#define APP_I3C11_ADDR          0x40095800
#define APP_I3C12_ADDR          0x40095c00
#define APP_I3C13_ADDR          0x40096000
#define APP_I3C14_ADDR          0x40096400
#define APP_SGPIO1_MASTER_ADDR  0x40097000
#define APP_SGPIO2_MASTER_ADDR  0x40097400
#define APP_SGPIO1_MONITOR_ADDR 0x40097800
#define APP_SGPIO2_MONITOR_ADDR 0x40097c00
#define APP_PS2IF1_ADDR         0x40098000
#define APP_PS2IF2_ADDR         0x40098400
#define APP_IWDT2_ADDR          0x40099000
#define APP_WWDT2_ADDR          0x40099400
#define APP_PIS_ADDR            0x4009a000
#define SEC_I2C1_ADDR           0x400a0000
#define SEC_I3C1_ADDR           0x400a0800
#define SEC_UART1_ADDR          0x400a1000
#define SEC_IWDT1_ADDR          0x400a1800
#define SEC_WWDT1_ADDR          0x400a1c00
#define SEC_TRNG_ADDR           0x400a2000
#define SEC_SYSC_SEC_PER_ADDR   0x400a7c00
#define FLASH_BASE_ADDR         CACHE1_ADDR

#ifdef __cplusplus
}
#endif

#endif
