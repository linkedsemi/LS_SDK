#ifndef GUARD_REG_BASE_ADDR_H
#define GUARD_REG_BASE_ADDR_H

/******************************* CPU0_SYS AHB *******************************/
#define ROM_BASE                   0x00400000
#define SRAM0_BASE                 0x00500000
#define SRAM2_BASE                 0x00600000

#define REG_DEBUG0_BASE            0x01000000
#define REG_LPC0_BASE              0x01002000
#define REG_LPC1_BASE              0x01003000
#define REG_ESPI0_BASE             0x01004000
#define REG_ESPI1_BASE             0x01008000
#define REG_OTBN_BASE              0x01100000
#define REG_SHA256_BASE            0x01110000
#define REG_SHA512_BASE            0x01111000
#define REG_NIST_TRNG_BASE         0x01112000
#define REG_OTP_BASE               0x01116000
#define REG_OTFAD_AES_BASE         0x01118000
#define REG_DMA0_BASE              0x01200000
#define REG_SD_BASE                0x01204000
#define REG_AHB_IOPMP0_BASE        0x0120c000
#define REG_AHB_IOPMP1_BASE        0x0120c400

/******************************* CPU0_SYS APB *******************************/
#define REG_CPU0_SYS_CFG_BASE      0x01300000
#define REG_WDT0_BASE              0x01301000
#define REG_PECI0_BASE             0x01302000
#define REG_GPIO_BASE              0x01303000
#define REG_I3C0_BASE              0x01304000
#define REG_I3C1_BASE              0x01305000
#define REG_I3C2_BASE              0x01306000
#define REG_I3C3_BASE              0x01307000
#define REG_I3C4_BASE              0x01308000
#define REG_I3C5_BASE              0x01309000
#define REG_I3C6_BASE              0x0130a000
#define REG_I3C7_BASE              0x0130b000
#define REG_JTAGM0_BASE            0x0130c000
#define REG_LTPI0_SCM_BASE         0x0130d000
#define REG_PECI1_BASE             0x0130e000
#define REG_LTPI0_BASE             0x02000000
#define REG_LTPI1_BASE             0x22000000
#define REG_I3C8_BASE              0x42000000
#define REG_I3C9_BASE              0x42001000
#define REG_I3C10_BASE             0x42002000
#define REG_I3C11_BASE             0x42003000
#define REG_I3C12_BASE             0x42004000
#define REG_I3C13_BASE             0x42005000
#define REG_I3C14_BASE             0x42006000
#define REG_I3C15_BASE             0x42007000
#define REG_I2C12_BASE             0x42008000
#define REG_I2C13_BASE             0x42009000
#define REG_I2C14_BASE             0x4200a000
#define REG_I2C15_BASE             0x4200b000
#define REG_SGPIO_MST0_BASE        0x4200c000
#define REG_SGPIO_MST1_BASE        0x4200d000
#define REG_LTPI1_SCM_BASE         0x4200e000
#define REG_UART8_BASE             0x42100000
#define REG_UART9_BASE             0x42101000
#define REG_UART10_BASE            0x42102000
#define REG_UART11_BASE            0x42103000
#define REG_JTAGM1_BASE            0x42104000
#define REG_SGPIO_SLAVE_BASE       0x42105000
#define REG_LTPI0_CTRL_BASE        0x42106000
#define REG_LTPI1_CTRL_BASE        0x42107000
#define REG_WDT6_BASE              0x42108000
#define REG_PWM_BASE               0x42120000
#define REG_CAP_BASE               0x42121000
#define REG_ADTIMER0_BASE          0x42122000
#define REG_ADTIMER1_BASE          0x42123000
#define REG_TIMTOP_BASE            0x42124000
#define REG_GP_TIMER3_BASE         0x42125000
#define REG_RTC_BASE               0x42126000
#define REG_CAN_BASE               0x42127000
#define REG_TACH_BASE              0x42127000
#define REG_SGPIO_MONITOR_BASE     0x42128000
#define REG_LTPI0_HPM_BASE         0x42129000
#define REG_LTPI1_HPM_BASE         0x4212a000
#define REG_CALC_BLKS_CALC_CRC_BASE    0x4212b000
#define REG_CALC_BLKS_APB_CALC_BASE    0x4212b400
#define REG_CALC_BLKS_APB_CRYPT_BASE   0x4212b800
#define REG_CALC_BLKS_CALC_SM4_TOP_BASE   0x4212bc00
#define REG_SGPIO_MONITOR1_BASE    0x4212c000
#define REG_OTP_CYP_BASE           0x4212e000


/******************************* CPU1_SYS AXI *******************************/
#define REG_PCIE2_BASE             0x50000000
#define REG_PCIE2_DBI_BASE         0x60000000
#define REG_AXI_IOPMP0_BASE        0x60400000

/******************************* CPU1_SYS APB *******************************/
#define REG_CPU1_SYS_CFG_BASE      0x60500000
#define REG_WDT1_BASE              0x60501000
#define REG_GDMA0_BASE             0x60502000
#define REG_UART0_BASE             0x60503000
#define REG_UART1_BASE             0x60504000
#define REG_UART2_BASE             0x60505000
#define REG_UART3_BASE             0x60506000
#define REG_UART4_BASE             0x60507000
#define REG_UART5_BASE             0x60508000
#define REG_UART6_BASE             0x60509000
#define REG_UART7_BASE             0x6050a000
#define REG_ADC0_BASE              0x6050b000
#define REG_ADC1_BASE              0x6050c000
#define REG_ADC2_BASE              0x6050d000
#define REG_GDMA1_BASE             0x6050E000
#define REG_WDT7_BASE     	   0x6050F000
#define REG_CPU1_CACHE_BASE        0x60510000

/******************************* CPU1_SYS AHB *******************************/
#define REG_FWSPI_BASE             0x61000000
#define REG_QSPI0_BASE             0x62000000
#define REG_QSPI1_BASE             0x63000000
#define REG_QSPI2_BASE             0x64000000
#define REG_SGMII_BASE             0x65000000
#define REG_DMA1_BASE              0x65100000
#define REG_DEBUG1_BASE            0x65104000

/******************************* PIPE_SYS AXI *******************************/
#define REG_PCIE0_BASE             0x70000000
#define REG_PCIE1_BASE             0x80000000
#define REG_PCIE0_DBI_BASE         0x90000000
#define REG_PCIE1_DBI_BASE         0x90400000
#define REG_AXI_IOPMP1_BASE        0x90800000

/******************************* PIPE_SYS APB *******************************/
#define REG_VPN0_BASE              0x90900000
#define REG_VPN1_BASE              0x90910000
#define REG_JPEG0_BASE             0x90920000
#define REG_JPEG1_BASE             0x90924000
#define REG_PIPE_SYS_CFG_BASE      0x90928000
#define REG_WDT3_BASE              0x90929000
#define REG_DPTX_BASE              0x9092a000
#define REG_GDMA2_BASE             0x9092b000
#define REG_2D_GRAPHIC_BASE        0x90940000

/******************************* PIPE_SYS AHB *******************************/
#define REG_EMMC0_BASE             0x92000000
#define REG_SGMII1_BASE            0x92100000
#define REG_SGMII2_BASE            0x92200000

/******************************* PERIPH_SYS AXI *******************************/
#define REG_USB0_BASE              0x94000000
#define REG_USB1_BASE              0x94100000  
#define REG_USB2P00_BASE           0x94200000
#define REG_USB2P01_BASE           0x94280000
#define REG_AXI_IOPMP2_BASE        0x94300000

/******************************* PERIPH_SYS AHB *******************************/
#define REG_MAC0_BASE              0x95000000
#define REG_MAC1_BASE              0x95004000

/******************************* PERIPH_SYS APB *******************************/
#define REG_PERIPH_SYS_CFG_BASE    0x96000000
#define REG_WDT4_BASE              0x96001000
#define REG_I2C0_BASE              0x96002000
#define REG_I2C1_BASE              0x96003000
#define REG_I2C2_BASE              0x96004000  
#define REG_I2C3_BASE              0x96005000
#define REG_I2C4_BASE              0x96006000
#define REG_I2C5_BASE              0x96007000
#define REG_I2C6_BASE              0x96008000
#define REG_I2C7_BASE              0x96009000
#define REG_I2C8_BASE              0x9600a000
#define REG_I2C9_BASE              0x9600b000
#define REG_I2C10_BASE             0x9600c000
#define REG_I2C11_BASE             0x9600d000
#define REG_UART12_BASE            0x9600e000
#define REG_UART13_BASE            0x9600f000
#define REG_UART14_BASE            0x96010000
#define REG_UART15_BASE            0x96011000
#define REG_VIRTUAL_USB0_BASE      0x96012000
#define REG_VIRTUAL_USB1_BASE      0x96013000

/******************************* TOP_SYS AXI *******************************/
#define REG_TOP_SYS_CFG0_ANA_PIPE_BASE     0xa0000000
#define REG_TOP_SYS_CFG4_ANA_CPU_BASE      0xa0001000
#define REG_TOP_SYS_CFG2_ANA_TOP_CRG_BASE  0xa0002000
#define REG_TOP_SYS_CFG3_PIN_MUX_BASE      0xa0003000
#define REG_PIN_MUX_APB_EXTI3_BASE         0xa0003c00
#define REG_PIN_MUX_APB_EXTI2_BASE         0xa0003d00
#define REG_PIN_MUX_APB_EXTI1_BASE         0xa0003e00
#define REG_PIN_MUX_APB_EXTI0_BASE         0xa0003f00
#define REG_PCIE0_PHY_BASE                 0xa0004000
#define REG_PCIE1_PHY_BASE                 0xa0005000
#define REG_PCIE2_PHY_BASE                 0xa0006000
#define REG_DPSG0_PHY_BASE                 0xa0007000
#define REG_DPSG1_PHY_BASE                 0xa0008000
#define REG_TOP_SYS_CFG1_ANA_PERIPH_BASE   0xa0010000
#define REG_USB300_PHY_BASE                0xa0011000
#define REG_USB301_PHY_BASE                0xa0012000
#define REG_WDT5_BASE                      0xa0013000
#define REG_TOP_DIG_APB_CFG_BASE           0xa0014000
/******************************* DDR_SYS APB *******************************/
#define REG_UMCTL_BASE              0xa4000000
#define REG_DDR_SYS_CFG_BASE        0xa4020000
#define REG_WDT2_BASE               0xa4021000

/******************************* DDR_SYS AXI *******************************/
#define AXI2SRAM_128_BASE           0xb0000000
#define DDR_CACHEABLE_BASE          0xc0000000

#endif

