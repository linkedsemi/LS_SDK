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

/* The address mapping of the system zone is shown as follows. */
#define ROM_BASE_ADDR 				(0x01000000)

#define LSQSPI_MEM_MAP_BASE_ADDR 	(0x08000000)
#define FLASH_BASE_ADDR 			(LSQSPI_MEM_MAP_BASE_ADDR)

#define SRAM0_BASE_ADDR 			(0x10000000)
#define SRAM1_BASE_ADDR 			(0x10018000)
#define SRAM_BASE_ADDR 				(SRAM0_BASE_ADDR)

/* The address mapping of the system peripherals is shown as follows. */
#define LSQSPIV2_BASE_ADDR 			(0x40000000)

#define LSUSB_BASE_ADDR 			(0x40001000)

#define DMAC1_BASE_ADDR 			(0x40002000)	
#define DMAC2_BASE_ADDR 			(0x40003000)	

#define ESPI_BASE_ADDR 				(0x40004000)

#define LPC_BASE_ADDR 				(0x40005000)

#define CACHE_BASE_ADDR 			(0x40008000)

#define SYSC_CPU_BASE_ADDR 			(0x40009000)
#define SYSC_AWO_BASE_ADDR 			(0x4000A000)

#define ECC_BASE_ADDR 				(0x4000C000)

#define LSSHA_BASE_ADDR 			(0x4000C400)
#define LSCRC_BASE_ADDR 			(0x4000C800)
#define CALC_BASE_ADDR 				(0x4000CC00)
#define CRYPT_BASE_ADDR 			(0x4000D000)
#define CALC_SM4_BASE_ADDR 			(0x4000D400)

#define BXCAN_BASE_ADDR 			(0x4000E000)

#define APBIF_V33_BASE_ADDR 		(0x4000F000)
#define LSIWDG_BASE_ADDR            (0x4000F120)
#define LSRTC_BASE_ADDR				(0x4000F140)

#define LSBSTIM_BASE_ADDR 			(0x40080000)

#define LSGPTIMA1_BASE_ADDR 		(0x40080400)
#define LSGPTIMA2_BASE_ADDR 		(0x40080800)
#define LSGPTIMB1_BASE_ADDR 		(0x40080C00)
#define LSGPTIMC1_BASE_ADDR 		(0x40081000)

#define LSADTIM1_BASE_ADDR 			(0x40081400)	//ADTIM1
#define LSADTIM2_BASE_ADDR 			(0x40081800)	//ADTIM2
#define LSADTIM3_BASE_ADDR 			(0x40081C00)	//ADTIM3
#define LSADTIM4_BASE_ADDR 			(0x40082000)	//ADTIM4

#define PWM_BASE_ADDR 				(0x40082400)
#define CAP_BASE_ADDR 				(0x40082800)

#define I2C1_BASE_ADDR 				(0x40083000)
#define I2C2_BASE_ADDR 				(0x40083400)
#define I2C3_BASE_ADDR 				(0x40083800)
#define I2C4_BASE_ADDR 				(0x40083C00)
#define I2C5_BASE_ADDR 				(0x40084000)
#define I2C6_BASE_ADDR 				(0x40084400)

#define UART1_BASE_ADDR 			(0x40085000)
#define UART2_BASE_ADDR 			(0x40085400)
#define UART3_BASE_ADDR 			(0x40085800)
#define DWUART1_BASE_ADDR 			(0x40085C00)
#define DWUART2_BASE_ADDR 			(0x40086000)

#define LSSSI_BASE_ADDR 			(0x40087000)
#define SPI2_BASE_ADDR 				(0x40087400)
#define SPI3_BASE_ADDR 				(0x40087800)

#define LSSPIS_BASE_ADDR 			(0x40087C00)

#define LSADC1_BASE_ADDR 			(0x40089000)	//ADC1
#define LSADC2_BASE_ADDR 			(0x40089400)	//ADC2

#define LSPDM_BASE_ADDR 			(0x4008A000)

#define EXTI0_BASE_ADDR 			(0x4008B000)
#define EXTI1_BASE_ADDR 			(0x4008B400)

#define LSWWDT_BASE_ADDR 			(0x4008C000)

#define LSPIS_BASE_ADDR 			(0x4008C400)

#define TOUCHKEY_BASE_ADDR 			(0x4008C800)

#define TRNG_BASE_ADDR 				(0x4008CC00)

#define SYSC_PER_BASE_ADDR 			(0x4008D000)

#define DAC_BASE_ADDR 				(0x4008D400)

#define KSCAN_BASE_ADDR 			(0x4008D800)

#define LSOWM_BASE_ADDR             (0x4008DC00)

#define CEC_BASE_ADDR 				(0x4008F000)

#define PS2H1_BASE_ADDR            (0x4008E000)

#define PS2H2_BASE_ADDR            (0x4008E400)

#define PS2H3_BASE_ADDR            (0x4008EB00)

#define PS2H4_BASE_ADDR            (0x4008EC00)

#ifdef __cplusplus
}
#endif

#endif
