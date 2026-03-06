#ifndef REG_CPU1_SYS_TYPE_H_
#define REG_CPU1_SYS_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CPU1_SYS_CFG ((reg_cpu1_sys_t *)REG_CPU1_SYS_CFG_BASE)

typedef struct
{
    volatile uint32_t CLK_SGETH0_TX_CLK_DEGLITCH_SW3_REG; //0x0
    volatile uint32_t CLK_SGETH0_TX_CLK_DIV0_DIV6_REG; //0x4
    volatile uint32_t CLK_SGETH0_TX_CLK_CG0_REG; //0x8
    volatile uint32_t CLK_SGETH0_RX_CLK_DEGLITCH_SW3_REG; //0xc
    volatile uint32_t CLK_SGETH0_RX_CLK_DIV0_DIV6_REG; //0x10
    volatile uint32_t CLK_SGETH0_RX_CLK_CG0_REG; //0x14
    volatile uint32_t CLK_SGETH0_125_TX_CLK_DEGLITCH_SW3_REG; //0x18
    volatile uint32_t CLK_SGETH0_125_TX_CLK_DIV0_DIV6_REG; //0x1c
    volatile uint32_t CLK_SGETH0_125_TX_CLK_CG0_REG; //0x20
    volatile uint32_t CLK_SGETH0_125_RX_CLK_DEGLITCH_SW3_REG; //0x24
    volatile uint32_t CLK_SGETH0_125_RX_CLK_DIV0_DIV6_REG; //0x28
    volatile uint32_t CLK_SGETH0_125_RX_CLK_CG0_REG; //0x2c
    volatile uint32_t PCIE2_PCLK_CLK_DEGLITCH_SW2_REG; //0x30
    volatile uint32_t PCIE2_PCLK_CLK_CG0_REG; //0x34
    volatile uint32_t PCIE2_AUXCLK_CLK_DEGLITCH_SW4_REG; //0x38
    volatile uint32_t PCIE2_AUXCLK_CLK_DIV0_DIV4_REG; //0x3c
    volatile uint32_t PCIE2_AUXCLK_CLK_CG0_REG; //0x40
    volatile uint32_t WDT1_LRC_CLK_CLK_DEGLITCH_SW2_REG; //0x44
    volatile uint32_t WDT1_LRC_CLK_CLK_CG0_REG; //0x48
    volatile uint32_t FWSPI_SSI_CLK_CLK_DEGLITCH_SW3_REG; //0x4c
    volatile uint32_t FWSPI_SSI_CLK_CLK_DIV0_DIV4_REG; //0x50
    volatile uint32_t FWSPI_SSI_CLK_CLK_CG0_REG; //0x54
    volatile uint32_t SPI0_SSI_CLK_CLK_DEGLITCH_SW3_REG; //0x58
    volatile uint32_t SPI0_SSI_CLK_CLK_DIV0_DIV4_REG; //0x5c
    volatile uint32_t SPI0_SSI_CLK_CLK_CG0_REG; //0x60
    volatile uint32_t SPI1_SSI_CLK_CLK_DEGLITCH_SW3_REG; //0x64
    volatile uint32_t SPI1_SSI_CLK_CLK_DIV0_DIV4_REG; //0x68
    volatile uint32_t SPI1_SSI_CLK_CLK_CG0_REG; //0x6c
    volatile uint32_t SPI2_SSI_CLK_CLK_DEGLITCH_SW3_REG; //0x70
    volatile uint32_t SPI2_SSI_CLK_CLK_DIV0_DIV4_REG; //0x74
    volatile uint32_t SPI2_SSI_CLK_CLK_CG0_REG; //0x78
    volatile uint32_t WDT7_LRC_CLK_CLK_DEGLITCH_SW2_REG; //0x7c
    volatile uint32_t WDT7_LRC_CLK_CLK_CG0_REG; //0x80
    volatile uint32_t SOFT_RST_N_REG0; //0x84
    volatile uint32_t SOFT_RST_N_REG0_CLR; //0x88
    volatile uint32_t PERIPH_SYS_CRG_AXI_CLK_TOP_RST_N_REG0; //0x8c
    volatile uint32_t PERIPH_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR; //0x90
    volatile uint32_t PERIPH_SYS_CRG_SYS0_APB_CLK_TOP_RST_N_REG0; //0x94
    volatile uint32_t PERIPH_SYS_CRG_SYS0_APB_CLK_TOP_RST_N_REG0_CLR; //0x98
    volatile uint32_t PERIPH_SYS_CRG_SYS1_APB_CLK_TOP_RST_N_REG0; //0x9c
    volatile uint32_t PERIPH_SYS_CRG_SYS1_APB_CLK_TOP_RST_N_REG0_CLR; //0xa0
    volatile uint32_t PERIPH_SYS_CRG_AHB_CLK_TOP_RST_N_REG0; //0xa4
    volatile uint32_t PERIPH_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR; //0xa8
    volatile uint32_t PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0; //0xac
    volatile uint32_t PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR; //0xb0
    volatile uint32_t PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0; //0xb4
    volatile uint32_t PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_CLR; //0xb8
    volatile uint32_t PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0; //0xbc
    volatile uint32_t PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR; //0xc0
    volatile uint32_t TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0; //0xc4
    volatile uint32_t TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0_CLR; //0xc8
    volatile uint32_t TOP_DIG_CRG_TOP_SYS_AXI_CLK_TOP_RST_N_REG0; //0xcc
    volatile uint32_t TOP_DIG_CRG_TOP_SYS_AXI_CLK_TOP_RST_N_REG0_CLR; //0xd0
    volatile uint32_t TOP_DIG_CRG_TOP_SYS1_APB_CLK_TOP_RST_N_REG0; //0xd4
    volatile uint32_t TOP_DIG_CRG_TOP_SYS1_APB_CLK_TOP_RST_N_REG0_CLR; //0xd8
    volatile uint32_t DDR_SYS_CRG_DDR_SYS_APB_CLK_TOP_RST_N_REG0; //0xdc
    volatile uint32_t DDR_SYS_CRG_DDR_SYS_APB_CLK_TOP_RST_N_REG0_CLR; //0xe0
    volatile uint32_t DDR_SYS_CRG_PLL_DDR_CLK_TOP_RST_N_REG0; //0xe4
    volatile uint32_t DDR_SYS_CRG_PLL_DDR_CLK_TOP_RST_N_REG0_CLR; //0xe8
    volatile uint32_t AXI_DMAC_CSR01; //0xec
    volatile uint32_t AXI_DMAC_CSR23; //0xf0
    volatile uint32_t AXI_DMAC_CSR45; //0xf4
    volatile uint32_t AXI_DMAC_CSR67; //0xf8
    volatile uint32_t GDMA0_MODULE_EN; //0xfc
    volatile uint32_t CPU_SYS_SOFT_INT_CFG0; //0x100
    volatile uint32_t CPU_SYS_SOFT_INT_CFG1; //0x104
    volatile uint32_t CPU_SYS_SOFT_INT_CFG2; //0x108
    volatile uint32_t CPU_SYS_SOFT_INT_CFG3; //0x10c
    volatile uint32_t CPU_SYS_SOFT_INT_CFG4; //0x110
    volatile uint32_t CPU_SYS_SOFT_INT_CFG5; //0x114
    volatile uint32_t CPU_SYS_SOFT_INT_CFG6; //0x118
    volatile uint32_t CPU_SYS_SOFT_INT_CFG7; //0x11c
    volatile uint32_t CPU_SYS_SOFT_CLUSTERID; //0x120
    volatile uint32_t CPU_SYS_SOFT_DM_NEXTDM_BASE; //0x124
    volatile uint32_t CPU_SYS_RD_CORE0_MSTATUS_L; //0x128
    volatile uint32_t CPU_SYS_RD_CORE0_MSTATUS_H; //0x12c
    volatile uint32_t CPU_SYS_RD_CORE0_RETIRE0_PC_H; //0x130
    volatile uint32_t CPU_SYS_RD_CORE0_RETIRE1_PC_H; //0x134
    volatile uint32_t CPU_SYS_RD_CORE0_RETIRE0_PC_L; //0x138
    volatile uint32_t CPU_SYS_RD_CORE0_RETIRE1_PC_L; //0x13c
    volatile uint32_t CPU_SYS_RD_CORE1_RETIRE0_PC_L; //0x140
    volatile uint32_t CPU_SYS_RD_CORE1_RETIRE1_PC_L; //0x144
    volatile uint32_t CPU_SYS_RD_CORE2_RETIRE0_PC_L; //0x148
    volatile uint32_t CPU_SYS_RD_CORE2_RETIRE1_PC_L; //0x14c
    volatile uint32_t CPU_SYS_RD_CORE3_RETIRE0_PC_L; //0x150
    volatile uint32_t CPU_SYS_RD_CORE3_RETIRE1_PC_L; //0x154
    volatile uint32_t CPU_SYS_RD_CORE0_PAR_VIOLATION; //0x158
    volatile uint32_t CPU_SYS_RD_CORE0_ZONEID; //0x15c
    volatile uint32_t CPU_SYS_RD_CORE1_MSTATUS_L; //0x160
    volatile uint32_t CPU_SYS_RD_CORE1_MSTATUS_H; //0x164
    volatile uint32_t CPU_SYS_RD_CORE2_MSTATUS_L; //0x168
    volatile uint32_t CPU_SYS_RD_CORE2_MSTATUS_H; //0x16c
    volatile uint32_t CPU_SYS_RD_CORE3_MSTATUS_L; //0x170
    volatile uint32_t CPU_SYS_RD_CORE3_MSTATUS_H; //0x174
    volatile uint32_t C908_TDT_DEBUG_RESET; //0x178
    volatile uint32_t CPU1_DUMMY0; //0x17c
    volatile uint32_t CPU1_DUMMY1; //0x180
    volatile uint32_t CPU1_DUMMY2; //0x184
    volatile uint32_t CPU1_DUMMY3; //0x188
    volatile uint32_t CPU1_RD_DUMMY0; //0x18c
    volatile uint32_t CPU1_RD_DUMMY1; //0x190
    volatile uint32_t CPU1_RD_DUMMY2; //0x194
    volatile uint32_t CPU1_RD_DUMMY3; //0x198
    volatile uint32_t SOFT_TBI_SIGDET; //0x19c
    volatile uint32_t SOFT_FWSPI_XIP_EN; //0x1a0
    volatile uint32_t SOFT_FWSPI_SLAVE_SEL; //0x1a4
    volatile uint32_t SOFT_FWSPI_SS_IN_N; //0x1a8
    volatile uint32_t SOFT_FWSPI_OSCLK_INV_SEL; //0x1ac
    volatile uint32_t SOFT_FWSPI_SS_O_SEL; //0x1b0
    volatile uint32_t SOFT_FWSPI_SS_O; //0x1b4
    volatile uint32_t SOFT_FWSPI_SS_ABR; //0x1b8
    volatile uint32_t SOFT_FWSPI_SS_WPN; //0x1bc
    volatile uint32_t RD_FWSPI_SSI_SLEEP; //0x1c0
    volatile uint32_t RD_FWSPI_SPI_MODE; //0x1c4
    volatile uint32_t RD_FWSPI_SPI_ABR; //0x1c8
    volatile uint32_t RD_FWSPI_SPI_WPN; //0x1cc
    volatile uint32_t SOFT_SPI0_XIP_EN; //0x1d0
    volatile uint32_t SOFT_SPI0_SLAVE_SEL; //0x1d4
    volatile uint32_t SOFT_SPI0_SS_IN_N; //0x1d8
    volatile uint32_t SOFT_SPI0_OSCLK_INV_SEL; //0x1dc
    volatile uint32_t SOFT_SPI0_SS_O_SEL; //0x1e0
    volatile uint32_t SOFT_SPI0_SS_O; //0x1e4
    volatile uint32_t SOFT_SPI0_SS_ABR; //0x1e8
    volatile uint32_t SOFT_SPI0_SS_WPN; //0x1ec
    volatile uint32_t RD_SPI0_SSI_SLEEP; //0x1f0
    volatile uint32_t RD_SPI0_SPI_MODE; //0x1f4
    volatile uint32_t RD_SPI0_SPI_ABR; //0x1f8
    volatile uint32_t RD_SPI0_SPI_WPN; //0x1fc
    volatile uint32_t SOFT_SPI1_XIP_EN; //0x200
    volatile uint32_t SOFT_SPI1_SLAVE_SEL; //0x204
    volatile uint32_t SOFT_SPI1_SS_IN_N; //0x208
    volatile uint32_t SOFT_SPI1_OSCLK_INV_SEL; //0x20c
    volatile uint32_t SOFT_SPI1_SS_O_SEL; //0x210
    volatile uint32_t SOFT_SPI1_SS_O; //0x214
    volatile uint32_t SOFT_SPI1_SS_ABR; //0x218
    volatile uint32_t SOFT_SPI1_SS_WPN; //0x21c
    volatile uint32_t RD_SPI1_SSI_SLEEP; //0x220
    volatile uint32_t RD_SPI1_SPI_MODE; //0x224
    volatile uint32_t RD_SPI1_SPI_ABR; //0x228
    volatile uint32_t RD_SPI1_SPI_WPN; //0x22c
    volatile uint32_t SOFT_SPI2_XIP_EN; //0x230
    volatile uint32_t SOFT_SPI2_SLAVE_SEL; //0x234
    volatile uint32_t SOFT_SPI2_SS_IN_N; //0x238
    volatile uint32_t SOFT_SPI2_SS_ABR; //0x23c
    volatile uint32_t SOFT_SPI2_SS_WPN; //0x240
    volatile uint32_t RD_SPI2_SSI_IS_MST; //0x244
    volatile uint32_t SOFT_SPI2_SSI_SLV_SEL; //0x248
    volatile uint32_t SOFT_SPI2_SCLK_OE_N; //0x24c
    volatile uint32_t SOFT_SPI2_OSCLK_INV_SEL; //0x250
    volatile uint32_t SOFT_SPI2_ISCLK_INV_SEL; //0x254
    volatile uint32_t SOFT_SPI2_SS_IN_SEL; //0x258
    volatile uint32_t SOFT_SPI2_SS_OE_N; //0x25c
    volatile uint32_t SOFT_SPI2_SS_O; //0x260
    volatile uint32_t SOFT_SPI2_SS_O_SEL; //0x264
    volatile uint32_t RD_SPI2_SSI_SLEEP; //0x268
    volatile uint32_t RD_SPI2_SPI_MODE; //0x26c
    volatile uint32_t RD_SPI2_SPI_ABR; //0x270
    volatile uint32_t RD_SPI2_SPI_WPN; //0x274
    volatile uint32_t DDR_SYS_CFG_REG1; //0x278
    volatile uint32_t DDR_SYS_CFG_REG2; //0x27c
    volatile uint32_t PIPE_SYS_CFG_REG1; //0x280
    volatile uint32_t PIPE_SYS_CFG_REG2; //0x284
    volatile uint32_t PIPE_SYS_CFG_REG3; //0x288
    volatile uint32_t PERIPH_SYS_CFG_REG1; //0x28c
    volatile uint32_t PERIPH_SYS_CFG_REG2; //0x290
    volatile uint32_t PERIPH_SYS_CFG_REG3; //0x294
    volatile uint32_t PERIPH_SYS_CFG_REG4; //0x298
    volatile uint32_t TOP_SYS_CFG_REG1; //0x29c
    volatile uint32_t TOP_SYS_CFG_REG2; //0x2a0
    volatile uint32_t TOP_SYS_CFG_REG3; //0x2a4
    volatile uint32_t ARADDR_MAP_CFG_EN; //0x2a8
    volatile uint32_t AWADDR_MAP_CFG_EN; //0x2ac
    volatile uint32_t ARADDR_MAP_CFG; //0x2b0
    volatile uint32_t AWADDR_MAP_CFG; //0x2b4
    volatile uint32_t CPUC908_REG0; //0x2b8
    volatile uint32_t GDMA1_MODULE_EN; //0x2bc
    volatile uint32_t DMA_CONNECT_SEL0; //0x2c0
    volatile uint32_t CPU_SOFT0_C908_INTR; //0x2c4
    volatile uint32_t CPU_SOFT1_C908_INTR; //0x2c8
    volatile uint32_t CPU_SYS_SOFT_C_ID; //0x2cc
    volatile uint32_t CPU_SYS_SOFT_SDBGEN; //0x2d0
    volatile uint32_t DMA_CONNECT_SEL1; //0x2d4
    volatile uint32_t DMA_CONNECT_SEL2; //0x2d8
    volatile uint32_t DMA_CONNECT_SEL3; //0x2dc
    volatile uint32_t ADC0_REG0_RW; //0x2e0
    volatile uint32_t ADC0_REG0_RO; //0x2e4
    volatile uint32_t ADC0_REG1_RO; //0x2e8
    volatile uint32_t ADC0_REG2_RO; //0x2ec
    volatile uint32_t ADC0_REG3_RO; //0x2f0
    volatile uint32_t C908_SOFT_RW; //0x2f4
    volatile uint32_t C908_SOFT_RO; //0x2f8
    volatile uint32_t ADC1_REG0_RW; //0x2fc
    volatile uint32_t ADC1_REG0_RO; //0x300
    volatile uint32_t ADC1_REG1_RO; //0x304
    volatile uint32_t ADC1_REG2_RO; //0x308
    volatile uint32_t ADC1_REG3_RO; //0x30c
    volatile uint32_t DMA_CONNECT_SEL4; //0x310
    volatile uint32_t DMA_CONNECT_SEL5; //0x314
    volatile uint32_t DMA_CONNECT_SEL6; //0x318
    volatile uint32_t DMA_CONNECT_SEL7; //0x31c
    volatile uint32_t GPIORSTIND; //0x320
    volatile uint32_t C908_RSTIND_INTR_MASK; //0x324
    volatile uint32_t C908_RSTIND_INTR_CLR; //0x328
    volatile uint32_t C908_RSTIND_INTR_RAW; //0x32c
    volatile uint32_t CPU1_CPU1_SYS_CRG_PIC_CLK_TOP_RST_N_REG0; //0x330
    volatile uint32_t CPU1_CPU1_SYS_CRG_PIC_CLK_TOP_RST_N_REG0_CLR; //0x334
    volatile uint32_t CPU1_CPU1_SYS_CRG_CPU1_SYS_AHB_CLK_TOP_RST_N_REG0; //0x338
    volatile uint32_t CPU1_CPU1_SYS_CRG_CPU1_SYS_AHB_CLK_TOP_RST_N_REG0_CLR; //0x33c
    volatile uint32_t CPU1_CPU1_SYS_CRG_CPU1_SYS_PLL_CPU_CLK_TOP_RST_N_REG0; //0x340
    volatile uint32_t CPU1_CPU1_SYS_CRG_CPU1_SYS_PLL_CPU_CLK_TOP_RST_N_REG0_CLR; //0x344
    volatile uint32_t CPU1_CPU1_SYS_CRG_CPU1_SYS_APB_CLK_TOP_RST_N_REG0; //0x348
    volatile uint32_t CPU1_CPU1_SYS_CRG_CPU1_SYS_APB_CLK_TOP_RST_N_REG0_CLR; //0x34c
    volatile uint32_t CPU1_IP_SOFT_RST_N_REG0; //0x350
    volatile uint32_t CPU1_IP_SOFT_RST_N_REG0_CLR; //0x354
    volatile uint32_t CPU1_CPU1_SYS_PIC_CLK_REG0; //0x358
    volatile uint32_t CPU1_CPU1_SYS_CFG_REG1; //0x35c
    volatile uint32_t CPU1_CPU1_SYS_CFG_REG2; //0x360
    volatile uint32_t CPU1_CPU1_SYS_CFG_REG3; //0x364
    volatile uint32_t CPU1_CPU_SYS_SOFT_APB_BASE_L; //0x368
    volatile uint32_t CPU1_CPU_SYS_SOFT_APB_BASE_H; //0x36c
    volatile uint32_t CPU1_CPU_SYS_SOFT_CORE0_RVBA_H; //0x370
    volatile uint32_t CPU1_CPU_SYS_SOFT_CORE0_RVBA_L; //0x374
    volatile uint32_t CPU1_CPU_SYS_SOFT_CORE1_RVBA_L; //0x378
    volatile uint32_t CPU1_CPU_SYS_SOFT_CORE2_RVBA_L; //0x37c
    volatile uint32_t CPU1_CPU_SYS_SOFT_CORE3_RVBA_L; //0x380
    volatile uint32_t CPU1_SYS_CFG_LOCK; //0x384
    volatile uint32_t CPU1_SYS_ADJUST_BUS_EN; //0x388
    volatile uint32_t ADC2_REG0_RW; //0x38c
    volatile uint32_t ADC2_REG0_RO; //0x390
    volatile uint32_t ADC2_REG1_RO; //0x394
    volatile uint32_t ADC2_REG2_RO; //0x398
    volatile uint32_t ADC2_REG3_RO; //0x39c
    volatile uint32_t WDT7_RST_N_EN; //0x3a0
    volatile uint32_t H2X_ADJUST_AXI_EN; //0x3a4
    volatile uint32_t CORE0_EMA0; //0x3a8
    volatile uint32_t CORE0_EMA1; //0x3ac
    volatile uint32_t CORE0_EMA2; //0x3b0
    volatile uint32_t CORE1_EMA0; //0x3b4
    volatile uint32_t CORE1_EMA1; //0x3b8
    volatile uint32_t CORE1_EMA2; //0x3bc
    volatile uint32_t CORE2_EMA0; //0x3c0
    volatile uint32_t CORE2_EMA1; //0x3c4
    volatile uint32_t CORE2_EMA2; //0x3c8
    volatile uint32_t CORE3_EMA0; //0x3cc
    volatile uint32_t CORE3_EMA1; //0x3d0
    volatile uint32_t CORE3_EMA2; //0x3d4
    volatile uint32_t PCIE2_DUMMY0; //0x3d8
    volatile uint32_t PCIE2_RD_DUMMY0; //0x3dc
    volatile uint32_t PCIE2_REG0; //0x3e0
    volatile uint32_t PCIE2_REG1; //0x3e4
    volatile uint32_t PCIE2_REG2; //0x3e8
    volatile uint32_t PCIE2_REG3; //0x3ec
    volatile uint32_t PCIE2_REG4; //0x3f0
    volatile uint32_t PCIE2_REG5; //0x3f4
    volatile uint32_t PCIE2_REG6; //0x3f8
    volatile uint32_t PCIE2_REG7; //0x3fc
    volatile uint32_t PCIE2_REG8; //0x400
    volatile uint32_t PCIE2_REG9; //0x404
    volatile uint32_t PCIE2_REG10; //0x408
    volatile uint32_t PCIE2_REG11; //0x40c
    volatile uint32_t PCIE2_REG12; //0x410
    volatile uint32_t PCIE2_REG13; //0x414
    volatile uint32_t PCIE2_REG14; //0x418
    volatile uint32_t PCIE2_REG15; //0x41c
    volatile uint32_t PCIE2_REG16; //0x420
    volatile uint32_t PCIE2_REG17; //0x424
    volatile uint32_t PCIE2_REG18; //0x428
    volatile uint32_t PCIE2_REG19; //0x42c
    volatile uint32_t PCIE2_REG20; //0x430
    volatile uint32_t PCIE2_REG21; //0x434
    volatile uint32_t PCIE2_REG22; //0x438
    volatile uint32_t PCIE2_REG23; //0x43c
    volatile uint32_t PCIE2_REG24; //0x440
    volatile uint32_t PCIE2_REG25; //0x444
    volatile uint32_t PCIE2_REG26; //0x448
    volatile uint32_t PCIE2_REG27; //0x44c
    volatile uint32_t PCIE2_REG28; //0x450
    volatile uint32_t PCIE2_REG29; //0x454
    volatile uint32_t PCIE2_REG30; //0x458
    volatile uint32_t PCIE2_REG31; //0x45c
    volatile uint32_t PCIE2_REG32; //0x460
    volatile uint32_t PCIE2_REG33; //0x464
    volatile uint32_t PCIE2_REG34; //0x468
    volatile uint32_t PCIE2_REG35; //0x46c
    volatile uint32_t PCIE2_REG36; //0x470
    volatile uint32_t PCIE2_REG37; //0x474
    volatile uint32_t PCIE2_REG38; //0x478
    volatile uint32_t PCIE2_REG39; //0x47c
    volatile uint32_t PCIE2_REG40; //0x480
    volatile uint32_t PCIE2_REG41; //0x484
    volatile uint32_t PCIE2_REG42; //0x488
    volatile uint32_t PCIE2_REG43; //0x48c
    volatile uint32_t PCIE2_REG44; //0x490
    volatile uint32_t PCIE2_REG45; //0x494
    volatile uint32_t PCIE2_REG46; //0x498
    volatile uint32_t PCIE2_REG47; //0x49c
    volatile uint32_t PCIE2_REG48; //0x4a0
    volatile uint32_t PCIE2_REG49; //0x4a4
    volatile uint32_t PCIE2_REG50; //0x4a8
    volatile uint32_t PCIE2_REG51; //0x4ac
    volatile uint32_t PCIE2_REG52; //0x4b0
    volatile uint32_t PCIE2_REG53; //0x4b4
    volatile uint32_t PCIE2_REG54; //0x4b8
    volatile uint32_t PCIE2_REG55; //0x4bc
    volatile uint32_t PCIE2_REG56; //0x4c0
    volatile uint32_t PCIE2_REG57; //0x4c4
    volatile uint32_t PCIE2_REG58; //0x4c8
    volatile uint32_t PCIE2_REG59; //0x4cc
    volatile uint32_t PCIE2_REG60; //0x4d0
    volatile uint32_t PCIE2_REG61; //0x4d4
    volatile uint32_t PCIE2_REG62; //0x4d8
    volatile uint32_t PCIE2_REG63; //0x4dc
    volatile uint32_t PCIE2_REG64; //0x4e0
    volatile uint32_t PCIE2_REG65; //0x4e4
    volatile uint32_t PCIE2_REG66; //0x4e8
    volatile uint32_t PCIE2_REG67; //0x4ec
    volatile uint32_t PCIE2_REG68; //0x4f0
    volatile uint32_t PCIE2_REG69; //0x4f4
    volatile uint32_t PCIE2_REG70; //0x4f8
    volatile uint32_t PCIE2_REG71; //0x4fc
    volatile uint32_t PCIE2_REG72; //0x500
    volatile uint32_t PCIE2_REG73; //0x504
    volatile uint32_t PCIE2_REG74; //0x508
    volatile uint32_t PCIE2_REG75; //0x50c
    volatile uint32_t PCIE2_REG76; //0x510
    volatile uint32_t PCIE2_REG77; //0x514
    volatile uint32_t PCIE2_REG78; //0x518
    volatile uint32_t PCIE2_REG79; //0x51c
    volatile uint32_t PCIE2_REG80; //0x520
    volatile uint32_t PCIE2_REG81; //0x524
    volatile uint32_t PCIE2_REG82; //0x528
    volatile uint32_t PCIE2_REG83; //0x52c
    volatile uint32_t PCIE2_REG84; //0x530
    volatile uint32_t PCIE2_REG85; //0x534
    volatile uint32_t PCIE2_REG86; //0x538
    volatile uint32_t PCIE2_REG87; //0x53c
    volatile uint32_t PCIE2_REG88; //0x540
    volatile uint32_t PCIE2_REG89; //0x544
    volatile uint32_t PCIE2_REG90; //0x548
    volatile uint32_t PCIE2_REG91; //0x54c
    volatile uint32_t PCIE2_REG92; //0x550
    volatile uint32_t PCIE2_REG93; //0x554
    volatile uint32_t PCIE2_REG94; //0x558
    volatile uint32_t PCIE2_REG95; //0x55c
    volatile uint32_t PCIE2_REG96; //0x560
    volatile uint32_t PCIE2_REG97; //0x564
    volatile uint32_t PCIE2_REG98; //0x568
    volatile uint32_t PCIE2_REG99; //0x56c
    volatile uint32_t PCIE2_REG100; //0x570
    volatile uint32_t PCIE2_REG101; //0x574
    volatile uint32_t PCIE2_REG102; //0x578
    volatile uint32_t PCIE2_REG103; //0x57c
    volatile uint32_t PCIE2_REG104; //0x580
    volatile uint32_t PCIE2_REG105; //0x584
    volatile uint32_t PCIE2_REG106; //0x588
    volatile uint32_t PCIE2_REG107; //0x58c
    volatile uint32_t PCIE2_REG108; //0x590
    volatile uint32_t PCIE2_REG109; //0x594
    volatile uint32_t PCIE2_REG110; //0x598
    volatile uint32_t PCIE2_REG111; //0x59c
    volatile uint32_t PCIE2_REG112; //0x5a0
    volatile uint32_t PCIE2_REG113; //0x5a4
    volatile uint32_t PCIE2_REG114; //0x5a8
    volatile uint32_t PCIE2_REG115; //0x5ac
    volatile uint32_t PCIE2_REG116; //0x5b0
    volatile uint32_t PCIE2_REG117; //0x5b4
    volatile uint32_t PCIE2_REG118; //0x5b8
    volatile uint32_t PCIE2_REG119; //0x5bc
    volatile uint32_t PCIE2_REG120; //0x5c0
    volatile uint32_t PCIE2_REG121; //0x5c4
    volatile uint32_t PCIE2_REG122; //0x5c8
    volatile uint32_t PCIE2_REG123; //0x5cc
    volatile uint32_t PCIE2_REG124; //0x5d0
    volatile uint32_t PCIE2_REG125; //0x5d4
    volatile uint32_t PCIE2_REG126; //0x5d8
    volatile uint32_t PCIE2_REG127; //0x5dc
    volatile uint32_t PCIE2_REG128; //0x5e0
    volatile uint32_t PCIE2_REG129; //0x5e4
    volatile uint32_t PCIE2_REG130; //0x5e8
    volatile uint32_t PCIE2_REG131; //0x5ec
    volatile uint32_t PCIE2_REG132; //0x5f0
    volatile uint32_t PCIE2_REG133; //0x5f4
    volatile uint32_t PCIE2_REG134; //0x5f8
    volatile uint32_t PCIE2_REG135; //0x5fc
    volatile uint32_t PCIE2_REG136; //0x600
    volatile uint32_t PCIE2_REG137; //0x604
    volatile uint32_t PCIE2_REG138; //0x608
    volatile uint32_t PCIE2_REG139; //0x60c
    volatile uint32_t PCIE2_REG140; //0x610
    volatile uint32_t PCIE2_REG141; //0x614
    volatile uint32_t PCIE2_REG142; //0x618
    volatile uint32_t PCIE2_REG143; //0x61c
    volatile uint32_t PCIE2_REG144; //0x620
    volatile uint32_t PCIE2_REG145; //0x624
    volatile uint32_t PCIE2_REG146; //0x628
    volatile uint32_t PCIE2_REG147; //0x62c
    volatile uint32_t PCIE2_REG148; //0x630
    volatile uint32_t PCIE2_REG149; //0x634
    volatile uint32_t PCIE2_REG150; //0x638
    volatile uint32_t PCIE2_REG151; //0x63c
    volatile uint32_t PCIE2_REG152; //0x640
    volatile uint32_t PCIE2_REG153; //0x644
    volatile uint32_t PCIE2_REG154; //0x648
    volatile uint32_t PCIE2_REG155; //0x64c
    volatile uint32_t PCIE2_REG156; //0x650
    volatile uint32_t PCIE2_REG157; //0x654
    volatile uint32_t PCIE2_REG158; //0x658
    volatile uint32_t PCIE2_REG159; //0x65c
    volatile uint32_t PCIE2_REG160; //0x660
    volatile uint32_t PCIE2_REG161; //0x664
    volatile uint32_t PCIE2_REG162; //0x668
    volatile uint32_t PCIE2_REG163; //0x66c
    volatile uint32_t PCIE2_REG164; //0x670
    volatile uint32_t PCIE2_REG165; //0x674
    volatile uint32_t PCIE2_REG166; //0x678
    volatile uint32_t PCIE2_REG167; //0x67c
    volatile uint32_t PCIE2_REG168; //0x680
    volatile uint32_t PCIE2_REG169; //0x684
    volatile uint32_t PCIE2_REG170; //0x688
    volatile uint32_t PCIE2_REG171; //0x68c
    volatile uint32_t PCIE2_REG172; //0x690
    volatile uint32_t PCIE2_REG173; //0x694
    volatile uint32_t PCIE2_REG174; //0x698
    volatile uint32_t PCIE2_REG175; //0x69c
    volatile uint32_t PCIE2_REG176; //0x6a0
    volatile uint32_t PCIE2_REG177; //0x6a4
    volatile uint32_t PCIE2_REG178; //0x6a8
    volatile uint32_t PCIE2_REG179; //0x6ac
    volatile uint32_t PCIE2_REG180; //0x6b0
    volatile uint32_t PCIE2_REG181; //0x6b4
    volatile uint32_t PCIE2_REG182; //0x6b8
    volatile uint32_t PCIE2_REG183; //0x6bc
    volatile uint32_t PCIE2_REG184; //0x6c0
    volatile uint32_t PCIE2_REG185; //0x6c4
    volatile uint32_t PCIE2_REG186; //0x6c8
    volatile uint32_t PCIE2_REG187; //0x6cc
    volatile uint32_t PCIE2_REG188; //0x6d0
    volatile uint32_t PCIE2_REG189; //0x6d4
    volatile uint32_t PCIE2_REG190; //0x6d8
    volatile uint32_t PCIE2_REG191; //0x6dc
    volatile uint32_t PCIE2_REG192; //0x6e0
    volatile uint32_t PCIE2_REG193; //0x6e4
    volatile uint32_t PCIE2_REG194; //0x6e8
    volatile uint32_t PCIE2_REG195; //0x6ec
    volatile uint32_t PCIE2_REG196; //0x6f0
    volatile uint32_t PCIE2_REG197; //0x6f4
    volatile uint32_t PCIE2_REG198; //0x6f8
    volatile uint32_t PCIE2_REG199; //0x6fc
    volatile uint32_t PCIE2_REG200; //0x700
    volatile uint32_t PCIE2_REG201; //0x704
    volatile uint32_t PCIE2_REG202; //0x708
    volatile uint32_t PCIE2_REG203; //0x70c
    volatile uint32_t PCIE2_REG204; //0x710
    volatile uint32_t PCIE2_REG205; //0x714
    volatile uint32_t PCIE2_REG206; //0x718
    volatile uint32_t PCIE2_REG207; //0x71c
    volatile uint32_t PCIE2_REG208; //0x720
    volatile uint32_t PCIE2_REG209; //0x724
    volatile uint32_t PCIE2_REG210; //0x728
    volatile uint32_t PCIE2_REG211; //0x72c
    volatile uint32_t PCIE2_REG212; //0x730
    volatile uint32_t PCIE2_REG213; //0x734
    volatile uint32_t PCIE2_REG214; //0x738
    volatile uint32_t PCIE2_REG215; //0x73c
    volatile uint32_t PCIE2_REG216; //0x740
    volatile uint32_t PCIE2_REG217; //0x744
    volatile uint32_t PCIE2_REG218; //0x748
    volatile uint32_t PCIE2_REG219; //0x74c
    volatile uint32_t PCIE2_REG220; //0x750
    volatile uint32_t PCIE2_REG221; //0x754
    volatile uint32_t PCIE2_REG222; //0x758
    volatile uint32_t PCIE2_REG223; //0x75c
    volatile uint32_t PCIE2_REG224; //0x760
    volatile uint32_t PCIE2_REG225; //0x764
    volatile uint32_t PCIE2_REG226; //0x768
    volatile uint32_t PCIE2_REG227; //0x76c
    volatile uint32_t PCIE2_REG228; //0x770
    volatile uint32_t PCIE2_REG229; //0x774
    volatile uint32_t PCIE2_REG230; //0x778
    volatile uint32_t PCIE2_REG231; //0x77c
    volatile uint32_t PCIE2_REG232; //0x780
    volatile uint32_t PCIE2_REG233; //0x784
    volatile uint32_t PCIE2_REG234; //0x788
    volatile uint32_t PCIE2_REG235; //0x78c
    volatile uint32_t PCIE2_REG236; //0x790
    volatile uint32_t PCIE2_REG237; //0x794
    volatile uint32_t PCIE2_REG238; //0x798
    volatile uint32_t PCIE2_REG239; //0x79c
    volatile uint32_t PCIE2_REG240; //0x7a0
    volatile uint32_t PCIE2_REG241; //0x7a4
    volatile uint32_t PCIE2_REG242; //0x7a8
    volatile uint32_t PCIE2_REG243; //0x7ac
    volatile uint32_t PCIE2_REG244; //0x7b0
    volatile uint32_t PCIE2_REG245; //0x7b4
    volatile uint32_t PCIE2_REG246; //0x7b8
    volatile uint32_t PCIE2_REG247; //0x7bc
    volatile uint32_t PCIE2_REG248; //0x7c0
    volatile uint32_t PCIE2_REG249; //0x7c4
    volatile uint32_t PCIE2_REG250; //0x7c8
    volatile uint32_t PCIE2_REG251; //0x7cc
    volatile uint32_t PCIE2_REG252; //0x7d0
    volatile uint32_t PCIE2_REG253; //0x7d4
    volatile uint32_t PCIE2_REG254; //0x7d8
    volatile uint32_t PCIE2_REG255; //0x7dc
    volatile uint32_t PCIE2_REG256; //0x7e0
    volatile uint32_t PCIE2_REG257; //0x7e4
    volatile uint32_t PCIE2_REG258; //0x7e8
    volatile uint32_t PCIE2_REG259; //0x7ec
    volatile uint32_t PCIE2_REG260; //0x7f0
    volatile uint32_t PCIE2_REG261; //0x7f4
    volatile uint32_t PCIE2_REG262; //0x7f8
    volatile uint32_t PCIE2_REG263; //0x7fc
    volatile uint32_t PCIE2_REG264; //0x800
    volatile uint32_t PCIE2_REG265; //0x804
    volatile uint32_t PCIE2_REG266; //0x808
    volatile uint32_t PCIE2_REG267; //0x80c
    volatile uint32_t PCIE2_REG268; //0x810
    volatile uint32_t PCIE2_REG269; //0x814
    volatile uint32_t PCIE2_REG270; //0x818
    volatile uint32_t PCIE2_REG271; //0x81c
    volatile uint32_t PCIE2_REG272; //0x820
    volatile uint32_t PCIE2_REG273; //0x824
    volatile uint32_t PCIE2_REG274; //0x828
    volatile uint32_t PCIE2_REG275; //0x82c
    volatile uint32_t PCIE2_REG276; //0x830
    volatile uint32_t PCIE2_REG277; //0x834
    volatile uint32_t PCIE2_REG278; //0x838
    volatile uint32_t PCIE2_REG279; //0x83c
    volatile uint32_t PCIE2_REG280; //0x840
    volatile uint32_t PCIE2_REG281; //0x844
    volatile uint32_t PCIE2_REG282; //0x848
    volatile uint32_t PCIE2_REG283; //0x84c
    volatile uint32_t PCIE2_REG284; //0x850
    volatile uint32_t PCIE2_REG285; //0x854
    volatile uint32_t PCIE2_REG286; //0x858
    volatile uint32_t PCIE2_REG287; //0x85c
    volatile uint32_t PCIE2_REG288; //0x860
    volatile uint32_t PCIE2_RAM_REG_0; //0x864
    volatile uint32_t PCIE2_RAM_REG_1; //0x868
    volatile uint32_t PCIE2_RAM_REG_2; //0x86c
    volatile uint32_t PCIE2_RAM_REG_3; //0x870
    volatile uint32_t PCIE2_RAM_REG_4; //0x874
    volatile uint32_t PCIE2_RAM_REG_5; //0x878
    volatile uint32_t PCIE2_AXI_SLV_REG0; //0x87c
    volatile uint32_t PCIE2_AXI_SLV_REG1; //0x880
    volatile uint32_t PCIE2_AXI_SLV_REG2; //0x884
    volatile uint32_t PCIE2_AXI_SLV_REG3; //0x888
    volatile uint32_t PCIE2_AXI_SLV_REG4; //0x88c
    volatile uint32_t PCIE2_AXI_SLV_REG5; //0x890
    volatile uint32_t PCIE2_AXI_MST_REG0; //0x894
    volatile uint32_t PCIE2_AXI_MST_REG1; //0x898
    volatile uint32_t PCIE2_AXI_MST_REG2; //0x89c
    volatile uint32_t PCIE2_AXI_MST_REG3; //0x8a0
    volatile uint32_t PCIE2_AXI_MST_REG4; //0x8a4
    volatile uint32_t PCIE2_AXI_MST_REG5; //0x8a8
    volatile uint32_t PCIE2_AXI_MST_REG6; //0x8ac
    volatile uint32_t PCIE2_AXI_MST_REG7; //0x8b0
    volatile uint32_t PCIE2_DBI_SLV_REG0; //0x8b4
    volatile uint32_t PCIE2_VEN_MSG_START_T; //0x8b8
    volatile uint32_t PCIE2_VEN_MSI_START_T; //0x8bc
    volatile uint32_t PCIE2_APP_LTR_MSG_START_T; //0x8c0
    volatile uint32_t PCIE2_APP_OBFF_IDLE_MSG_START_T; //0x8c4
    volatile uint32_t PCIE2_APP_OBFF_OBFF_MSG_START_T; //0x8c8
    volatile uint32_t PCIE2_APP_OBFF_CPU_ACTIVE_MSG_START_T; //0x8cc
    volatile uint32_t PCIE2_VEN_MSG_REQ_TIMEOUT_CNT; //0x8d0
    volatile uint32_t X2H_ADJUST_AXI_EN; //0x8d4
    volatile uint32_t PCIE2_REG300; //0x8d8
    volatile uint32_t PCIE2_REG301; //0x8dc
    volatile uint32_t PCIE2_REG302; //0x8e0
    volatile uint32_t PCIE2_REG303; //0x8e4
    volatile uint32_t PCIE2_REG304; //0x8e8
    volatile uint32_t PCIE2_REG305; //0x8ec
    volatile uint32_t PCIE2_REG306; //0x8f0
    volatile uint32_t PCIE2_REG307; //0x8f4
    volatile uint32_t PCIE2_REG308; //0x8f8
    volatile uint32_t PCIE2_REG309; //0x8fc
    volatile uint32_t PCIE2_REG310; //0x900
    volatile uint32_t PCIE2_REG311; //0x904
    volatile uint32_t PCIE2_REG312; //0x908
    volatile uint32_t PCIE2_REG313; //0x90c
    volatile uint32_t PCIE2_REG314; //0x910
    volatile uint32_t PCIE2_REG315; //0x914
    volatile uint32_t PCIE2_REG316; //0x918
    volatile uint32_t PCIE2_REG317; //0x91c
    volatile uint32_t PCIE2_REG318; //0x920
    volatile uint32_t PCIE2_REG319; //0x924
    volatile uint32_t PCIE2_REG320; //0x928
    volatile uint32_t PCIE2_REG321; //0x92c
    volatile uint32_t PCIE2_REG322; //0x930
    volatile uint32_t PCIE2_CFG_PBUS_NUM_0; //0x934
    volatile uint32_t PCIE2_CFG_PBUS_NUM_1; //0x938
    volatile uint32_t PCIE2_CFG_PBUS_DEV_NUM_0; //0x93c
    volatile uint32_t PCIE2_CFG_PBUS_DEV_NUM_1; //0x940
    volatile uint32_t PCIE2_REG323; //0x944
    volatile uint32_t PCIE2_REG324; //0x948
    volatile uint32_t PCIE2_REG325; //0x94c
    volatile uint32_t C908_RST_READY_INTR_MASK; //0x950
    volatile uint32_t C908_RST_READY_INTR_CLR; //0x954
    volatile uint32_t C908_RST_READY_INTR_RAW; //0x958
    volatile uint32_t PAD_EX_RST_N_FLAG; //0x95c
    volatile uint32_t C908_PAD_CPU_RST_N_FLAG; //0x960
} reg_cpu1_sys_t;

enum CPU1_SYS_REG_CLK_SGETH0_TX_CLK_DEGLITCH_SW3_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_TX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    CPU1_SYS_CLK_SGETH0_TX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_TX_CLK_DIV0_DIV6_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_TX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    CPU1_SYS_CLK_SGETH0_TX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_TX_CLK_CG0_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_TX_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_CLK_SGETH0_TX_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_RX_CLK_DEGLITCH_SW3_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_RX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    CPU1_SYS_CLK_SGETH0_RX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_RX_CLK_DIV0_DIV6_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_RX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    CPU1_SYS_CLK_SGETH0_RX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_RX_CLK_CG0_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_RX_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_CLK_SGETH0_RX_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_125_TX_CLK_DEGLITCH_SW3_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_125_TX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    CPU1_SYS_CLK_SGETH0_125_TX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_125_TX_CLK_DIV0_DIV6_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_125_TX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    CPU1_SYS_CLK_SGETH0_125_TX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_125_TX_CLK_CG0_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_125_TX_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_CLK_SGETH0_125_TX_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_125_RX_CLK_DEGLITCH_SW3_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_125_RX_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    CPU1_SYS_CLK_SGETH0_125_RX_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_125_RX_CLK_DIV0_DIV6_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_125_RX_CLK_DIV0_DIV6_REG_MASK = (int)0x3f,
    CPU1_SYS_CLK_SGETH0_125_RX_CLK_DIV0_DIV6_REG_POS = 0,
};

enum CPU1_SYS_REG_CLK_SGETH0_125_RX_CLK_CG0_REG_FIELD
{
    CPU1_SYS_CLK_SGETH0_125_RX_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_CLK_SGETH0_125_RX_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_PCLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    CPU1_SYS_PCIE2_PCLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    CPU1_SYS_PCIE2_PCLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_PCLK_CLK_CG0_REG_FIELD
{
    CPU1_SYS_PCIE2_PCLK_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_PCIE2_PCLK_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AUXCLK_CLK_DEGLITCH_SW4_REG_FIELD
{
    CPU1_SYS_PCIE2_AUXCLK_CLK_DEGLITCH_SW4_REG_MASK = (int)0x1ff,
    CPU1_SYS_PCIE2_AUXCLK_CLK_DEGLITCH_SW4_REG_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AUXCLK_CLK_DIV0_DIV4_REG_FIELD
{
    CPU1_SYS_PCIE2_AUXCLK_CLK_DIV0_DIV4_REG_MASK = (int)0xf,
    CPU1_SYS_PCIE2_AUXCLK_CLK_DIV0_DIV4_REG_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AUXCLK_CLK_CG0_REG_FIELD
{
    CPU1_SYS_PCIE2_AUXCLK_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_PCIE2_AUXCLK_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_WDT1_LRC_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    CPU1_SYS_WDT1_LRC_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    CPU1_SYS_WDT1_LRC_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum CPU1_SYS_REG_WDT1_LRC_CLK_CLK_CG0_REG_FIELD
{
    CPU1_SYS_WDT1_LRC_CLK_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_WDT1_LRC_CLK_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_FWSPI_SSI_CLK_CLK_DEGLITCH_SW3_REG_FIELD
{
    CPU1_SYS_FWSPI_SSI_CLK_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    CPU1_SYS_FWSPI_SSI_CLK_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum CPU1_SYS_REG_FWSPI_SSI_CLK_CLK_DIV0_DIV4_REG_FIELD
{
    CPU1_SYS_FWSPI_SSI_CLK_CLK_DIV0_DIV4_REG_MASK = (int)0xf,
    CPU1_SYS_FWSPI_SSI_CLK_CLK_DIV0_DIV4_REG_POS = 0,
};

enum CPU1_SYS_REG_FWSPI_SSI_CLK_CLK_CG0_REG_FIELD
{
    CPU1_SYS_FWSPI_SSI_CLK_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_FWSPI_SSI_CLK_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI0_SSI_CLK_CLK_DEGLITCH_SW3_REG_FIELD
{
    CPU1_SYS_SPI0_SSI_CLK_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    CPU1_SYS_SPI0_SSI_CLK_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI0_SSI_CLK_CLK_DIV0_DIV4_REG_FIELD
{
    CPU1_SYS_SPI0_SSI_CLK_CLK_DIV0_DIV4_REG_MASK = (int)0xf,
    CPU1_SYS_SPI0_SSI_CLK_CLK_DIV0_DIV4_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI0_SSI_CLK_CLK_CG0_REG_FIELD
{
    CPU1_SYS_SPI0_SSI_CLK_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_SPI0_SSI_CLK_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI1_SSI_CLK_CLK_DEGLITCH_SW3_REG_FIELD
{
    CPU1_SYS_SPI1_SSI_CLK_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    CPU1_SYS_SPI1_SSI_CLK_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI1_SSI_CLK_CLK_DIV0_DIV4_REG_FIELD
{
    CPU1_SYS_SPI1_SSI_CLK_CLK_DIV0_DIV4_REG_MASK = (int)0xf,
    CPU1_SYS_SPI1_SSI_CLK_CLK_DIV0_DIV4_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI1_SSI_CLK_CLK_CG0_REG_FIELD
{
    CPU1_SYS_SPI1_SSI_CLK_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_SPI1_SSI_CLK_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI2_SSI_CLK_CLK_DEGLITCH_SW3_REG_FIELD
{
    CPU1_SYS_SPI2_SSI_CLK_CLK_DEGLITCH_SW3_REG_MASK = (int)0x7f,
    CPU1_SYS_SPI2_SSI_CLK_CLK_DEGLITCH_SW3_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI2_SSI_CLK_CLK_DIV0_DIV4_REG_FIELD
{
    CPU1_SYS_SPI2_SSI_CLK_CLK_DIV0_DIV4_REG_MASK = (int)0xf,
    CPU1_SYS_SPI2_SSI_CLK_CLK_DIV0_DIV4_REG_POS = 0,
};

enum CPU1_SYS_REG_SPI2_SSI_CLK_CLK_CG0_REG_FIELD
{
    CPU1_SYS_SPI2_SSI_CLK_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_SPI2_SSI_CLK_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_WDT7_LRC_CLK_CLK_DEGLITCH_SW2_REG_FIELD
{
    CPU1_SYS_WDT7_LRC_CLK_CLK_DEGLITCH_SW2_REG_MASK = (int)0x1f,
    CPU1_SYS_WDT7_LRC_CLK_CLK_DEGLITCH_SW2_REG_POS = 0,
};

enum CPU1_SYS_REG_WDT7_LRC_CLK_CLK_CG0_REG_FIELD
{
    CPU1_SYS_WDT7_LRC_CLK_CLK_CG0_REG_MASK = (int)0x1,
    CPU1_SYS_WDT7_LRC_CLK_CLK_CG0_REG_POS = 0,
};

enum CPU1_SYS_REG_SOFT_RST_N_REG0_FIELD
{
    CPU1_SYS_CLK_SGETH0_TX_SOFT_RST_N_REG0_MASK = (int)0x1,
    CPU1_SYS_CLK_SGETH0_TX_SOFT_RST_N_REG0_POS = 0,
    CPU1_SYS_CLK_SGETH0_RX_SOFT_RST_N_REG0_MASK = (int)0x2,
    CPU1_SYS_CLK_SGETH0_RX_SOFT_RST_N_REG0_POS = 1,
    CPU1_SYS_CLK_SGETH0_125_TX_SOFT_RST_N_REG0_MASK = (int)0x4,
    CPU1_SYS_CLK_SGETH0_125_TX_SOFT_RST_N_REG0_POS = 2,
    CPU1_SYS_CLK_SGETH0_125_RX_SOFT_RST_N_REG0_MASK = (int)0x8,
    CPU1_SYS_CLK_SGETH0_125_RX_SOFT_RST_N_REG0_POS = 3,
    CPU1_SYS_PCIE2_PCLK_SOFT_RST_N_REG0_MASK = (int)0x10,
    CPU1_SYS_PCIE2_PCLK_SOFT_RST_N_REG0_POS = 4,
    CPU1_SYS_PCIE2_AUXCLK_SOFT_RST_N_REG0_MASK = (int)0x20,
    CPU1_SYS_PCIE2_AUXCLK_SOFT_RST_N_REG0_POS = 5,
    CPU1_SYS_FWSPI_SSI_CLK_SOFT_RST_N_REG0_MASK = (int)0x40,
    CPU1_SYS_FWSPI_SSI_CLK_SOFT_RST_N_REG0_POS = 6,
    CPU1_SYS_SPI0_SSI_CLK_SOFT_RST_N_REG0_MASK = (int)0x80,
    CPU1_SYS_SPI0_SSI_CLK_SOFT_RST_N_REG0_POS = 7,
    CPU1_SYS_SPI1_SSI_CLK_SOFT_RST_N_REG0_MASK = (int)0x100,
    CPU1_SYS_SPI1_SSI_CLK_SOFT_RST_N_REG0_POS = 8,
    CPU1_SYS_SPI2_SSI_CLK_SOFT_RST_N_REG0_MASK = (int)0x200,
    CPU1_SYS_SPI2_SSI_CLK_SOFT_RST_N_REG0_POS = 9,
    CPU1_SYS_SOFT_RST_N_REG0_MASK = (int)0x3ff,
    CPU1_SYS_SOFT_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_SOFT_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_CLK_SGETH0_TX_SOFT_RST_N_REG0_CLR_MASK = (int)0x1,
    CPU1_SYS_CLK_SGETH0_TX_SOFT_RST_N_REG0_CLR_POS = 0,
    CPU1_SYS_CLK_SGETH0_RX_SOFT_RST_N_REG0_CLR_MASK = (int)0x2,
    CPU1_SYS_CLK_SGETH0_RX_SOFT_RST_N_REG0_CLR_POS = 1,
    CPU1_SYS_CLK_SGETH0_125_TX_SOFT_RST_N_REG0_CLR_MASK = (int)0x4,
    CPU1_SYS_CLK_SGETH0_125_TX_SOFT_RST_N_REG0_CLR_POS = 2,
    CPU1_SYS_CLK_SGETH0_125_RX_SOFT_RST_N_REG0_CLR_MASK = (int)0x8,
    CPU1_SYS_CLK_SGETH0_125_RX_SOFT_RST_N_REG0_CLR_POS = 3,
    CPU1_SYS_PCIE2_PCLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x10,
    CPU1_SYS_PCIE2_PCLK_SOFT_RST_N_REG0_CLR_POS = 4,
    CPU1_SYS_PCIE2_AUXCLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x20,
    CPU1_SYS_PCIE2_AUXCLK_SOFT_RST_N_REG0_CLR_POS = 5,
    CPU1_SYS_FWSPI_SSI_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x40,
    CPU1_SYS_FWSPI_SSI_CLK_SOFT_RST_N_REG0_CLR_POS = 6,
    CPU1_SYS_SPI0_SSI_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x80,
    CPU1_SYS_SPI0_SSI_CLK_SOFT_RST_N_REG0_CLR_POS = 7,
    CPU1_SYS_SPI1_SSI_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x100,
    CPU1_SYS_SPI1_SSI_CLK_SOFT_RST_N_REG0_CLR_POS = 8,
    CPU1_SYS_SPI2_SSI_CLK_SOFT_RST_N_REG0_CLR_MASK = (int)0x200,
    CPU1_SYS_SPI2_SSI_CLK_SOFT_RST_N_REG0_CLR_POS = 9,
    CPU1_SYS_SOFT_RST_N_REG0_CLR_MASK = (int)0x3ff,
    CPU1_SYS_SOFT_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_PERIPH_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_PERIPH_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_PERIPH_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_PERIPH_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CRG_SYS0_APB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_PERIPH_SYS_CRG_SYS0_APB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_PERIPH_SYS_CRG_SYS0_APB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CRG_SYS0_APB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_PERIPH_SYS_CRG_SYS0_APB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_PERIPH_SYS_CRG_SYS0_APB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CRG_SYS1_APB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_PERIPH_SYS_CRG_SYS1_APB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_PERIPH_SYS_CRG_SYS1_APB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CRG_SYS1_APB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_PERIPH_SYS_CRG_SYS1_APB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_PERIPH_SYS_CRG_SYS1_APB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_PERIPH_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_PERIPH_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_PERIPH_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_PERIPH_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_PIPE_SYS_CRG_AXI_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_PIPE_SYS_CRG_APB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_PIPE_SYS_CRG_AHB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS0_APB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_TOP_DIG_CRG_TOP_SYS_AXI_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS_AXI_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS_AXI_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_TOP_DIG_CRG_TOP_SYS_AXI_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS_AXI_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS_AXI_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_TOP_DIG_CRG_TOP_SYS1_APB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS1_APB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS1_APB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_TOP_DIG_CRG_TOP_SYS1_APB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS1_APB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_TOP_DIG_CRG_TOP_SYS1_APB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_DDR_SYS_CRG_DDR_SYS_APB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_DDR_SYS_CRG_DDR_SYS_APB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_DDR_SYS_CRG_DDR_SYS_APB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_DDR_SYS_CRG_DDR_SYS_APB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_DDR_SYS_CRG_DDR_SYS_APB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_DDR_SYS_CRG_DDR_SYS_APB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_DDR_SYS_CRG_PLL_DDR_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_DDR_SYS_CRG_PLL_DDR_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_DDR_SYS_CRG_PLL_DDR_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_DDR_SYS_CRG_PLL_DDR_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_DDR_SYS_CRG_PLL_DDR_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_DDR_SYS_CRG_PLL_DDR_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_AXI_DMAC_CSR01_FIELD
{
    CPU1_SYS_AXI_DMAC_CSR01_MASK = (int)0xffffffff,
    CPU1_SYS_AXI_DMAC_CSR01_POS = 0,
};

enum CPU1_SYS_REG_AXI_DMAC_CSR23_FIELD
{
    CPU1_SYS_AXI_DMAC_CSR23_MASK = (int)0xffffffff,
    CPU1_SYS_AXI_DMAC_CSR23_POS = 0,
};

enum CPU1_SYS_REG_AXI_DMAC_CSR45_FIELD
{
    CPU1_SYS_AXI_DMAC_CSR45_MASK = (int)0xffffffff,
    CPU1_SYS_AXI_DMAC_CSR45_POS = 0,
};

enum CPU1_SYS_REG_AXI_DMAC_CSR67_FIELD
{
    CPU1_SYS_AXI_DMAC_CSR67_MASK = (int)0xffffffff,
    CPU1_SYS_AXI_DMAC_CSR67_POS = 0,
};

enum CPU1_SYS_REG_GDMA0_MODULE_EN_FIELD
{
    CPU1_SYS_GDMA0_MODULE_EN_MASK = (int)0x1,
    CPU1_SYS_GDMA0_MODULE_EN_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_INT_CFG0_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG0_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_INT_CFG1_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG1_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG1_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_INT_CFG2_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG2_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG2_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_INT_CFG3_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG3_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG3_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_INT_CFG4_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG4_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG4_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_INT_CFG5_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG5_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG5_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_INT_CFG6_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG6_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG6_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_INT_CFG7_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG7_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_INT_CFG7_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_CLUSTERID_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_CLUSTERID_MASK = (int)0xf,
    CPU1_SYS_CPU_SYS_SOFT_CLUSTERID_POS = 0,
    CPU1_SYS_CPU_SYS_SOFT_DM_CORE_UNAVAIL_MASK = (int)0xf0,
    CPU1_SYS_CPU_SYS_SOFT_DM_CORE_UNAVAIL_POS = 4,
    CPU1_SYS_CPU_SYS_SOFT_ZDBGEN_MASK = (int)0xffff00,
    CPU1_SYS_CPU_SYS_SOFT_ZDBGEN_POS = 8,
    CPU1_SYS_CPU_SYS_SOFT_MDBGEN_MASK = (int)0x1000000,
    CPU1_SYS_CPU_SYS_SOFT_MDBGEN_POS = 24,
    CPU1_SYS_CPU_SYS_SOFT_JTAG2_SEL_MASK = (int)0x2000000,
    CPU1_SYS_CPU_SYS_SOFT_JTAG2_SEL_POS = 25,
    CPU1_SYS_CPU_SYS_SOFT_L2CACHE_FLUSH_REQ_MASK = (int)0x4000000,
    CPU1_SYS_CPU_SYS_SOFT_L2CACHE_FLUSH_REQ_POS = 26,
    CPU1_SYS_CPU_SYS_SOFT_L2CACHE_INIT_DISABLE_MASK = (int)0x8000000,
    CPU1_SYS_CPU_SYS_SOFT_L2CACHE_INIT_DISABLE_POS = 27,
    CPU1_SYS_CPU_SYS_RD_NO_OP_MASK = (int)0x10000000,
    CPU1_SYS_CPU_SYS_RD_NO_OP_POS = 28,
    CPU1_SYS_CPU_SYS_RD_L2CACHE_FLUSH_DONE_MASK = (int)0x20000000,
    CPU1_SYS_CPU_SYS_RD_L2CACHE_FLUSH_DONE_POS = 29,
    CPU1_SYS_CPU_SYS_RD_PIC_VIOLATION_MASK = (int)0x40000000,
    CPU1_SYS_CPU_SYS_RD_PIC_VIOLATION_POS = 30,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_DM_NEXTDM_BASE_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_DM_NEXTDM_BASE_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_SOFT_DM_NEXTDM_BASE_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE0_MSTATUS_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE0_MSTATUS_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE0_MSTATUS_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE0_MSTATUS_H_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE0_MSTATUS_H_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE0_MSTATUS_H_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE0_RETIRE0_PC_H_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE0_PC_H_MASK = (int)0xff,
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE0_PC_H_POS = 0,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE0_PC_H_MASK = (int)0xff00,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE0_PC_H_POS = 8,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE0_PC_H_MASK = (int)0xff0000,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE0_PC_H_POS = 16,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE0_PC_H_MASK = (int)0xff000000,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE0_PC_H_POS = 24,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE0_RETIRE1_PC_H_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE1_PC_H_MASK = (int)0xff,
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE1_PC_H_POS = 0,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE1_PC_H_MASK = (int)0xff00,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE1_PC_H_POS = 8,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE1_PC_H_MASK = (int)0xff0000,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE1_PC_H_POS = 16,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE1_PC_H_MASK = (int)0xff000000,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE1_PC_H_POS = 24,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE0_RETIRE0_PC_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE0_PC_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE0_PC_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE0_RETIRE1_PC_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE1_PC_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE1_PC_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE1_RETIRE0_PC_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE0_PC_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE0_PC_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE1_RETIRE1_PC_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE1_PC_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE1_PC_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE2_RETIRE0_PC_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE0_PC_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE0_PC_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE2_RETIRE1_PC_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE1_PC_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE1_PC_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE3_RETIRE0_PC_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE0_PC_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE0_PC_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE3_RETIRE1_PC_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE1_PC_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE1_PC_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE0_PAR_VIOLATION_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE0_PAR_VIOLATION_MASK = (int)0x1f,
    CPU1_SYS_CPU_SYS_RD_CORE0_PAR_VIOLATION_POS = 0,
    CPU1_SYS_CPU_SYS_RD_CORE1_PAR_VIOLATION_MASK = (int)0x3e0,
    CPU1_SYS_CPU_SYS_RD_CORE1_PAR_VIOLATION_POS = 5,
    CPU1_SYS_CPU_SYS_RD_CORE2_PAR_VIOLATION_MASK = (int)0x7c00,
    CPU1_SYS_CPU_SYS_RD_CORE2_PAR_VIOLATION_POS = 10,
    CPU1_SYS_CPU_SYS_RD_CORE3_PAR_VIOLATION_MASK = (int)0xf8000,
    CPU1_SYS_CPU_SYS_RD_CORE3_PAR_VIOLATION_POS = 15,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE0_ZONEID_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE0_ZONEID_MASK = (int)0xf,
    CPU1_SYS_CPU_SYS_RD_CORE0_ZONEID_POS = 0,
    CPU1_SYS_CPU_SYS_RD_CORE0_HALTED_MASK = (int)0x10,
    CPU1_SYS_CPU_SYS_RD_CORE0_HALTED_POS = 4,
    CPU1_SYS_CPU_SYS_RD_CORE0_LPMD_B_MASK = (int)0x20,
    CPU1_SYS_CPU_SYS_RD_CORE0_LPMD_B_POS = 5,
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE0_MASK = (int)0x40,
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE0_POS = 6,
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE1_MASK = (int)0x80,
    CPU1_SYS_CPU_SYS_RD_CORE0_RETIRE1_POS = 7,
    CPU1_SYS_CPU_SYS_RD_CORE1_ZONEID_MASK = (int)0xf00,
    CPU1_SYS_CPU_SYS_RD_CORE1_ZONEID_POS = 8,
    CPU1_SYS_CPU_SYS_RD_CORE1_HALTED_MASK = (int)0x1000,
    CPU1_SYS_CPU_SYS_RD_CORE1_HALTED_POS = 12,
    CPU1_SYS_CPU_SYS_RD_CORE1_LPMD_B_MASK = (int)0x2000,
    CPU1_SYS_CPU_SYS_RD_CORE1_LPMD_B_POS = 13,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE0_MASK = (int)0x4000,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE0_POS = 14,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE1_MASK = (int)0x8000,
    CPU1_SYS_CPU_SYS_RD_CORE1_RETIRE1_POS = 15,
    CPU1_SYS_CPU_SYS_RD_CORE2_ZONEID_MASK = (int)0xf0000,
    CPU1_SYS_CPU_SYS_RD_CORE2_ZONEID_POS = 16,
    CPU1_SYS_CPU_SYS_RD_CORE2_HALTED_MASK = (int)0x100000,
    CPU1_SYS_CPU_SYS_RD_CORE2_HALTED_POS = 20,
    CPU1_SYS_CPU_SYS_RD_CORE2_LPMD_B_MASK = (int)0x200000,
    CPU1_SYS_CPU_SYS_RD_CORE2_LPMD_B_POS = 21,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE0_MASK = (int)0x400000,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE0_POS = 22,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE1_MASK = (int)0x800000,
    CPU1_SYS_CPU_SYS_RD_CORE2_RETIRE1_POS = 23,
    CPU1_SYS_CPU_SYS_RD_CORE3_ZONEID_MASK = (int)0xf000000,
    CPU1_SYS_CPU_SYS_RD_CORE3_ZONEID_POS = 24,
    CPU1_SYS_CPU_SYS_RD_CORE3_HALTED_MASK = (int)0x10000000,
    CPU1_SYS_CPU_SYS_RD_CORE3_HALTED_POS = 28,
    CPU1_SYS_CPU_SYS_RD_CORE3_LPMD_B_MASK = (int)0x20000000,
    CPU1_SYS_CPU_SYS_RD_CORE3_LPMD_B_POS = 29,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE0_MASK = (int)0x40000000,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE0_POS = 30,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE1_MASK = (int)0x80000000,
    CPU1_SYS_CPU_SYS_RD_CORE3_RETIRE1_POS = 31,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE1_MSTATUS_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE1_MSTATUS_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE1_MSTATUS_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE1_MSTATUS_H_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE1_MSTATUS_H_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE1_MSTATUS_H_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE2_MSTATUS_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE2_MSTATUS_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE2_MSTATUS_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE2_MSTATUS_H_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE2_MSTATUS_H_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE2_MSTATUS_H_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE3_MSTATUS_L_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE3_MSTATUS_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE3_MSTATUS_L_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_RD_CORE3_MSTATUS_H_FIELD
{
    CPU1_SYS_CPU_SYS_RD_CORE3_MSTATUS_H_MASK = (int)0xffffffff,
    CPU1_SYS_CPU_SYS_RD_CORE3_MSTATUS_H_POS = 0,
};

enum CPU1_SYS_REG_C908_TDT_DEBUG_RESET_FIELD
{
    CPU1_SYS_TDT_DM_PAD_NDMRESET_N_MASK = (int)0x1,
    CPU1_SYS_TDT_DM_PAD_NDMRESET_N_POS = 0,
    CPU1_SYS_TDT_DM_PAD_HARTRESET_CORE0_N_MASK = (int)0x2,
    CPU1_SYS_TDT_DM_PAD_HARTRESET_CORE0_N_POS = 1,
    CPU1_SYS_TDT_DM_PAD_HARTRESET_CORE1_N_MASK = (int)0x4,
    CPU1_SYS_TDT_DM_PAD_HARTRESET_CORE1_N_POS = 2,
    CPU1_SYS_TDT_DM_PAD_HARTRESET_CORE2_N_MASK = (int)0x8,
    CPU1_SYS_TDT_DM_PAD_HARTRESET_CORE2_N_POS = 3,
    CPU1_SYS_TDT_DM_PAD_HARTRESET_CORE3_N_MASK = (int)0x10,
    CPU1_SYS_TDT_DM_PAD_HARTRESET_CORE3_N_POS = 4,
};

enum CPU1_SYS_REG_CPU1_DUMMY0_FIELD
{
    CPU1_SYS_CPU1_DUMMY0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_DUMMY0_POS = 0,
};

enum CPU1_SYS_REG_CPU1_DUMMY1_FIELD
{
    CPU1_SYS_CPU1_DUMMY1_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_DUMMY1_POS = 0,
};

enum CPU1_SYS_REG_CPU1_DUMMY2_FIELD
{
    CPU1_SYS_CPU1_DUMMY2_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_DUMMY2_POS = 0,
};

enum CPU1_SYS_REG_CPU1_DUMMY3_FIELD
{
    CPU1_SYS_CPU1_DUMMY3_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_DUMMY3_POS = 0,
};

enum CPU1_SYS_REG_CPU1_RD_DUMMY0_FIELD
{
    CPU1_SYS_CPU1_RD_DUMMY0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_RD_DUMMY0_POS = 0,
};

enum CPU1_SYS_REG_CPU1_RD_DUMMY1_FIELD
{
    CPU1_SYS_CPU1_RD_DUMMY1_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_RD_DUMMY1_POS = 0,
};

enum CPU1_SYS_REG_CPU1_RD_DUMMY2_FIELD
{
    CPU1_SYS_CPU1_RD_DUMMY2_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_RD_DUMMY2_POS = 0,
};

enum CPU1_SYS_REG_CPU1_RD_DUMMY3_FIELD
{
    CPU1_SYS_CPU1_RD_DUMMY3_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_RD_DUMMY3_POS = 0,
};

enum CPU1_SYS_REG_SOFT_TBI_SIGDET_FIELD
{
    CPU1_SYS_SOFT_SGETH0_TBI_SIGDET_MASK = (int)0x3,
    CPU1_SYS_SOFT_SGETH0_TBI_SIGDET_POS = 0,
    CPU1_SYS_SGETH0_MAC_SPEED_O_MASK = (int)0xc,
    CPU1_SYS_SGETH0_MAC_SPEED_O_POS = 2,
    CPU1_SYS_SGETH0_SGMII_SPEED_O_MASK = (int)0x30,
    CPU1_SYS_SGETH0_SGMII_SPEED_O_POS = 4,
};

enum CPU1_SYS_REG_SOFT_FWSPI_XIP_EN_FIELD
{
    CPU1_SYS_SOFT_FWSPI_XIP_EN_MASK = (int)0x1,
    CPU1_SYS_SOFT_FWSPI_XIP_EN_POS = 0,
};

enum CPU1_SYS_REG_SOFT_FWSPI_SLAVE_SEL_FIELD
{
    CPU1_SYS_SOFT_FWSPI_SLAVE_SEL_MASK = (int)0x3,
    CPU1_SYS_SOFT_FWSPI_SLAVE_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_FWSPI_SS_IN_N_FIELD
{
    CPU1_SYS_SOFT_FWSPI_SS_IN_N_MASK = (int)0x1,
    CPU1_SYS_SOFT_FWSPI_SS_IN_N_POS = 0,
};

enum CPU1_SYS_REG_SOFT_FWSPI_OSCLK_INV_SEL_FIELD
{
    CPU1_SYS_SOFT_FWSPI_OSCLK_INV_SEL_MASK = (int)0x1,
    CPU1_SYS_SOFT_FWSPI_OSCLK_INV_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_FWSPI_SS_O_SEL_FIELD
{
    CPU1_SYS_SOFT_FWSPI_SS_O_SEL_MASK = (int)0xf,
    CPU1_SYS_SOFT_FWSPI_SS_O_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_FWSPI_SS_O_FIELD
{
    CPU1_SYS_SOFT_FWSPI_SS_O_MASK = (int)0xf,
    CPU1_SYS_SOFT_FWSPI_SS_O_POS = 0,
};

enum CPU1_SYS_REG_SOFT_FWSPI_SS_ABR_FIELD
{
    CPU1_SYS_SOFT_FWSPI_SS_ABR_MASK = (int)0x3,
    CPU1_SYS_SOFT_FWSPI_SS_ABR_POS = 0,
};

enum CPU1_SYS_REG_SOFT_FWSPI_SS_WPN_FIELD
{
    CPU1_SYS_SOFT_FWSPI_SS_WPN_MASK = (int)0x3,
    CPU1_SYS_SOFT_FWSPI_SS_WPN_POS = 0,
};

enum CPU1_SYS_REG_RD_FWSPI_SSI_SLEEP_FIELD
{
    CPU1_SYS_RD_FWSPI_SSI_SLEEP_MASK = (int)0x1,
    CPU1_SYS_RD_FWSPI_SSI_SLEEP_POS = 0,
};

enum CPU1_SYS_REG_RD_FWSPI_SPI_MODE_FIELD
{
    CPU1_SYS_RD_FWSPI_SPI_MODE_MASK = (int)0x3,
    CPU1_SYS_RD_FWSPI_SPI_MODE_POS = 0,
};

enum CPU1_SYS_REG_RD_FWSPI_SPI_ABR_FIELD
{
    CPU1_SYS_RD_FWSPI_SPI_ABR_MASK = (int)0x1,
    CPU1_SYS_RD_FWSPI_SPI_ABR_POS = 0,
};

enum CPU1_SYS_REG_RD_FWSPI_SPI_WPN_FIELD
{
    CPU1_SYS_RD_FWSPI_SPI_WPN_MASK = (int)0x1,
    CPU1_SYS_RD_FWSPI_SPI_WPN_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI0_XIP_EN_FIELD
{
    CPU1_SYS_SOFT_SPI0_XIP_EN_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI0_XIP_EN_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI0_SLAVE_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI0_SLAVE_SEL_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI0_SLAVE_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI0_SS_IN_N_FIELD
{
    CPU1_SYS_SOFT_SPI0_SS_IN_N_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI0_SS_IN_N_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI0_OSCLK_INV_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI0_OSCLK_INV_SEL_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI0_OSCLK_INV_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI0_SS_O_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI0_SS_O_SEL_MASK = (int)0xf,
    CPU1_SYS_SOFT_SPI0_SS_O_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI0_SS_O_FIELD
{
    CPU1_SYS_SOFT_SPI0_SS_O_MASK = (int)0xf,
    CPU1_SYS_SOFT_SPI0_SS_O_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI0_SS_ABR_FIELD
{
    CPU1_SYS_SOFT_SPI0_SS_ABR_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI0_SS_ABR_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI0_SS_WPN_FIELD
{
    CPU1_SYS_SOFT_SPI0_SS_WPN_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI0_SS_WPN_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI0_SSI_SLEEP_FIELD
{
    CPU1_SYS_RD_SPI0_SSI_SLEEP_MASK = (int)0x1,
    CPU1_SYS_RD_SPI0_SSI_SLEEP_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI0_SPI_MODE_FIELD
{
    CPU1_SYS_RD_SPI0_SPI_MODE_MASK = (int)0x3,
    CPU1_SYS_RD_SPI0_SPI_MODE_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI0_SPI_ABR_FIELD
{
    CPU1_SYS_RD_SPI0_SPI_ABR_MASK = (int)0x1,
    CPU1_SYS_RD_SPI0_SPI_ABR_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI0_SPI_WPN_FIELD
{
    CPU1_SYS_RD_SPI0_SPI_WPN_MASK = (int)0x1,
    CPU1_SYS_RD_SPI0_SPI_WPN_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI1_XIP_EN_FIELD
{
    CPU1_SYS_SOFT_SPI1_XIP_EN_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI1_XIP_EN_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI1_SLAVE_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI1_SLAVE_SEL_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI1_SLAVE_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI1_SS_IN_N_FIELD
{
    CPU1_SYS_SOFT_SPI1_SS_IN_N_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI1_SS_IN_N_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI1_OSCLK_INV_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI1_OSCLK_INV_SEL_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI1_OSCLK_INV_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI1_SS_O_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI1_SS_O_SEL_MASK = (int)0xf,
    CPU1_SYS_SOFT_SPI1_SS_O_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI1_SS_O_FIELD
{
    CPU1_SYS_SOFT_SPI1_SS_O_MASK = (int)0xf,
    CPU1_SYS_SOFT_SPI1_SS_O_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI1_SS_ABR_FIELD
{
    CPU1_SYS_SOFT_SPI1_SS_ABR_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI1_SS_ABR_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI1_SS_WPN_FIELD
{
    CPU1_SYS_SOFT_SPI1_SS_WPN_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI1_SS_WPN_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI1_SSI_SLEEP_FIELD
{
    CPU1_SYS_RD_SPI1_SSI_SLEEP_MASK = (int)0x1,
    CPU1_SYS_RD_SPI1_SSI_SLEEP_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI1_SPI_MODE_FIELD
{
    CPU1_SYS_RD_SPI1_SPI_MODE_MASK = (int)0x3,
    CPU1_SYS_RD_SPI1_SPI_MODE_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI1_SPI_ABR_FIELD
{
    CPU1_SYS_RD_SPI1_SPI_ABR_MASK = (int)0x1,
    CPU1_SYS_RD_SPI1_SPI_ABR_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI1_SPI_WPN_FIELD
{
    CPU1_SYS_RD_SPI1_SPI_WPN_MASK = (int)0x1,
    CPU1_SYS_RD_SPI1_SPI_WPN_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_XIP_EN_FIELD
{
    CPU1_SYS_SOFT_SPI2_XIP_EN_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI2_XIP_EN_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SLAVE_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI2_SLAVE_SEL_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI2_SLAVE_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SS_IN_N_FIELD
{
    CPU1_SYS_SOFT_SPI2_SS_IN_N_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI2_SS_IN_N_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SS_ABR_FIELD
{
    CPU1_SYS_SOFT_SPI2_SS_ABR_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI2_SS_ABR_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SS_WPN_FIELD
{
    CPU1_SYS_SOFT_SPI2_SS_WPN_MASK = (int)0x3,
    CPU1_SYS_SOFT_SPI2_SS_WPN_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI2_SSI_IS_MST_FIELD
{
    CPU1_SYS_RD_SPI2_SSI_IS_MST_MASK = (int)0x1,
    CPU1_SYS_RD_SPI2_SSI_IS_MST_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SSI_SLV_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI2_SSI_SLV_SEL_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI2_SSI_SLV_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SCLK_OE_N_FIELD
{
    CPU1_SYS_SOFT_SPI2_SCLK_OE_N_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI2_SCLK_OE_N_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_OSCLK_INV_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI2_OSCLK_INV_SEL_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI2_OSCLK_INV_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_ISCLK_INV_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI2_ISCLK_INV_SEL_MASK = (int)0x1,
    CPU1_SYS_SOFT_SPI2_ISCLK_INV_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SS_IN_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI2_SS_IN_SEL_MASK = (int)0x7,
    CPU1_SYS_SOFT_SPI2_SS_IN_SEL_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SS_OE_N_FIELD
{
    CPU1_SYS_SOFT_SPI2_SS_OE_N_MASK = (int)0xf,
    CPU1_SYS_SOFT_SPI2_SS_OE_N_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SS_O_FIELD
{
    CPU1_SYS_SOFT_SPI2_SS_O_MASK = (int)0xf,
    CPU1_SYS_SOFT_SPI2_SS_O_POS = 0,
};

enum CPU1_SYS_REG_SOFT_SPI2_SS_O_SEL_FIELD
{
    CPU1_SYS_SOFT_SPI2_SS_O_SEL_MASK = (int)0xf,
    CPU1_SYS_SOFT_SPI2_SS_O_SEL_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI2_SSI_SLEEP_FIELD
{
    CPU1_SYS_RD_SPI2_SSI_SLEEP_MASK = (int)0x1,
    CPU1_SYS_RD_SPI2_SSI_SLEEP_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI2_SPI_MODE_FIELD
{
    CPU1_SYS_RD_SPI2_SPI_MODE_MASK = (int)0x3,
    CPU1_SYS_RD_SPI2_SPI_MODE_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI2_SPI_ABR_FIELD
{
    CPU1_SYS_RD_SPI2_SPI_ABR_MASK = (int)0x1,
    CPU1_SYS_RD_SPI2_SPI_ABR_POS = 0,
};

enum CPU1_SYS_REG_RD_SPI2_SPI_WPN_FIELD
{
    CPU1_SYS_RD_SPI2_SPI_WPN_MASK = (int)0x1,
    CPU1_SYS_RD_SPI2_SPI_WPN_POS = 0,
};

enum CPU1_SYS_REG_DDR_SYS_CFG_REG1_FIELD
{
    DDR_SYS_APB_CLK_CLK_CG0_0_MASK = (int)0x1,
    DDR_SYS_APB_CLK_CLK_CG0_0_POS = 0,
    DDR_SYS_APB_CLK_CLK_DEGLITCH_SW2_MASK = (int)0x3e,
    DDR_SYS_APB_CLK_CLK_DEGLITCH_SW2_POS = 1,
    DDR_SYS_APB_CLK_CLK_DIV0_DIV4_MASK = (int)0x3c0,
    DDR_SYS_APB_CLK_CLK_DIV0_DIV4_POS = 6,
    DDR_SYS_DDRPHY_PCLK_CLK_CG0_1_MASK = (int)0x400,
    DDR_SYS_DDRPHY_PCLK_CLK_CG0_1_POS = 10,
    DDR_SYS_DDR_CFG_CLK_CLK_CG0_2_MASK = (int)0x800,
    DDR_SYS_DDR_CFG_CLK_CLK_CG0_2_POS = 11,
    DDR_SYS_WDT2_APB_CLK_CLK_CG0_3_MASK = (int)0x1000,
    DDR_SYS_WDT2_APB_CLK_CLK_CG0_3_POS = 12
};

enum CPU1_SYS_REG_DDR_SYS_CFG_REG2_FIELD
{
    DDR_SYS_AXI_CLK_CLK_CG0_0_MASK = (int)0x1,
    DDR_SYS_AXI_CLK_CLK_CG0_0_POS = 0,
    DDR_SYS_AXI_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    DDR_SYS_AXI_CLK_CLK_DEGLITCH_SW3_POS = 1,
    DDR_SYS_AXI_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    DDR_SYS_AXI_CLK_CLK_DIV0_DIV4_POS = 8,
    DDR_SYS_AXI_DMC_CLK_CLK_CG0_1_MASK = (int)0x1000,
    DDR_SYS_AXI_DMC_CLK_CLK_CG0_1_POS = 12,
    DDR_SYS_AXI_SRAM_CLK_CLK_CG0_2_MASK = (int)0x2000,
    DDR_SYS_AXI_SRAM_CLK_CLK_CG0_2_POS = 13,
};

enum CPU1_SYS_REG_PIPE_SYS_CFG_REG1_FIELD
{
    PIPE_SYS_AXI_CLK_CLK_CG0_0_MASK = (int)0x1,
    PIPE_SYS_AXI_CLK_CLK_CG0_0_POS = 0,
    PIPE_SYS_AXI_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    PIPE_SYS_AXI_CLK_CLK_DEGLITCH_SW3_POS = 1,
    PIPE_SYS_AXI_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    PIPE_SYS_AXI_CLK_CLK_DIV0_DIV4_POS = 8,
    PIPE_SYS_PCIE0_AXI_CLK_CLK_CG0_1_MASK = (int)0x1000,
    PIPE_SYS_PCIE0_AXI_CLK_CLK_CG0_1_POS = 12,
    PIPE_SYS_PCIE1_AXI_CLK_CLK_CG0_2_MASK = (int)0x2000,
    PIPE_SYS_PCIE1_AXI_CLK_CLK_CG0_2_POS = 13,
    PIPE_SYS_VP0_AXI_CLK_CLK_CG0_3_MASK = (int)0x4000,
    PIPE_SYS_VP0_AXI_CLK_CLK_CG0_3_POS = 14,
    PIPE_SYS_VP1_AXI_CLK_CLK_CG0_4_MASK = (int)0x8000,
    PIPE_SYS_VP1_AXI_CLK_CLK_CG0_4_POS = 15,
    PIPE_SYS_EMMC_AXI_CLK_CLK_CG0_5_MASK = (int)0x10000,
    PIPE_SYS_EMMC_AXI_CLK_CLK_CG0_5_POS = 16,
    //PIPE_SYS_SD_AXI_CLK_CLK_CG0_6_MASK = (int)0x20000,
    //PIPE_SYS_SD_AXI_CLK_CLK_CG0_6_POS = 17,
    PIPE_SYS_JPEG0_AXI_CLK_CLK_CG0_7_MASK = (int)0x20000,
    PIPE_SYS_JPEG0_AXI_CLK_CLK_CG0_7_POS = 17,
    PIPE_SYS_JPEG1_AXI_CLK_CLK_CG0_8_MASK = (int)0x40000,
    PIPE_SYS_JPEG1_AXI_CLK_CLK_CG0_8_POS = 18,
    PIPE_SYS_SGETH1_AXI_CLK_CLK_CG0_9_MASK = (int)0x80000,
    PIPE_SYS_SGETH1_AXI_CLK_CLK_CG0_9_POS = 19,
    PIPE_SYS_SGETH2_AXI_CLK_CLK_CG0_10_MASK = (int)0x100000,
    PIPE_SYS_SGETH2_AXI_CLK_CLK_CG0_10_POS = 20,
    PIPE_SYS_GDMA2_AXI_CLK_CLK_CG0_11_MASK = (int)0x200000,
    PIPE_SYS_GDMA2_AXI_CLK_CLK_CG0_11_POS = 21,
    PIPE_SYS_GRAPHIC2D_AXI_CLK_CLK_CG0_12_MASK = (int)0x400000,
    PIPE_SYS_GRAPHIC2D_AXI_CLK_CLK_CG0_12_POS = 22,
};

enum CPU1_SYS_REG_PIPE_SYS_CFG_REG2_FIELD
{
    PIPE_SYS_APB_CLK_CLK_CG0_0_MASK = (int)0x1,
    PIPE_SYS_APB_CLK_CLK_CG0_0_POS = 0,
    PIPE_SYS_APB_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    PIPE_SYS_APB_CLK_CLK_DEGLITCH_SW3_POS = 1,
    PIPE_SYS_APB_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    PIPE_SYS_APB_CLK_CLK_DIV0_DIV4_POS = 8,
    PIPE_SYS_VP0_APB_CLK_CLK_CG0_1_MASK = (int)0x1000,
    PIPE_SYS_VP0_APB_CLK_CLK_CG0_1_POS = 12,
    PIPE_SYS_VP1_APB_CLK_CLK_CG0_2_MASK = (int)0x2000,
    PIPE_SYS_VP1_APB_CLK_CLK_CG0_2_POS = 13,
    PIPE_SYS_PIPE_CFG_APB_CLK_CLK_CG0_3_MASK = (int)0x4000,
    PIPE_SYS_PIPE_CFG_APB_CLK_CLK_CG0_3_POS = 14,
    PIPE_SYS_WDT3_APB_CLK_CLK_CG0_4_MASK = (int)0x8000,
    PIPE_SYS_WDT3_APB_CLK_CLK_CG0_4_POS = 15,
    PIPE_SYS_JPEG0_APB_CLK_CLK_CG0_5_MASK = (int)0x10000,
    PIPE_SYS_JPEG0_APB_CLK_CLK_CG0_5_POS = 16,
    PIPE_SYS_JPEG1_APB_CLK_CLK_CG0_6_MASK = (int)0x20000,
    PIPE_SYS_JPEG1_APB_CLK_CLK_CG0_6_POS = 17,
    PIPE_SYS_GDMA2_APB_CLK_CLK_CG0_7_MASK = (int)0x40000,
    PIPE_SYS_GDMA2_APB_CLK_CLK_CG0_7_POS = 18,
    PIPE_SYS_GRAPHIC2D_APB_CLK_CLK_CG0_8_MASK = (int)0x80000,
    PIPE_SYS_GRAPHIC2D_APB_CLK_CLK_CG0_8_POS = 19,
    PIPE_SYS_DPTX_APB_CLK_CLK_CG0_9_MASK = (int)0x100000,
    PIPE_SYS_DPTX_APB_CLK_CLK_CG0_9_POS = 20,
};
    
enum CPU1_SYS_REG_PIPE_SYS_CFG_REG3_FIELD
{
    PIPE_SYS_AHB_CLK_CLK_CG0_0_MASK = (int)0x1,
    PIPE_SYS_AHB_CLK_CLK_CG0_0_POS = 0,
    PIPE_SYS_AHB_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    PIPE_SYS_AHB_CLK_CLK_DEGLITCH_SW3_POS = 1,
    PIPE_SYS_AHB_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    PIPE_SYS_AHB_CLK_CLK_DIV0_DIV4_POS = 8,
    PIPE_SYS_EMMC_AHB_CLK_CLK_CG0_1_MASK = (int)0x1000,
    PIPE_SYS_EMMC_AHB_CLK_CLK_CG0_1_POS = 12,
    //PIPE_SYS_SD_AHB_CLK_CLK_CG0_2_MASK = (int)0x2000,
    //PIPE_SYS_SD_AHB_CLK_CLK_CG0_2_POS = 13,
    PIPE_SYS_SGETH1_AHB_CLK_CLK_CG0_3_MASK = (int)0x2000,
    PIPE_SYS_SGETH1_AHB_CLK_CLK_CG0_3_POS = 13,
    PIPE_SYS_SGETH2_AHB_CLK_CLK_CG0_4_MASK = (int)0x4000,
    PIPE_SYS_SGETH2_AHB_CLK_CLK_CG0_4_POS = 14,
};

enum CPU1_SYS_REG_PERIPH_SYS_CFG_REG1_FIELD
{
    PERIPH_SYS_AXI_CLK_CLK_CG0_0_MASK = (int)0x1,
    PERIPH_SYS_AXI_CLK_CLK_CG0_0_POS = 0,
    PERIPH_SYS_AXI_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    PERIPH_SYS_AXI_CLK_CLK_DEGLITCH_SW3_POS = 1,
    PERIPH_SYS_AXI_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    PERIPH_SYS_AXI_CLK_CLK_DIV0_DIV4_POS = 8,
    PERIPH_SYS_USB200_AXI_CLK_CLK_CG0_1_MASK = (int)0x1000,
    PERIPH_SYS_USB200_AXI_CLK_CLK_CG0_1_POS = 12,
    PERIPH_SYS_USB201_AXI_CLK_CLK_CG0_2_MASK = (int)0x2000,
    PERIPH_SYS_USB201_AXI_CLK_CLK_CG0_2_POS = 13,
    PERIPH_SYS_USB300_AXI_CLK_CLK_CG0_3_MASK = (int)0x4000,
    PERIPH_SYS_USB300_AXI_CLK_CLK_CG0_3_POS = 14,
    PERIPH_SYS_USB301_AXI_CLK_CLK_CG0_4_MASK = (int)0x8000,
    PERIPH_SYS_USB301_AXI_CLK_CLK_CG0_4_POS = 15,
    PERIPH_SYS_ETH0_AXI_CLK_CLK_CG0_5_MASK = (int)0x10000,
    PERIPH_SYS_ETH0_AXI_CLK_CLK_CG0_5_POS = 16,
    PERIPH_SYS_ETH1_AXI_CLK_CLK_CG0_6_MASK = (int)0x20000,
    PERIPH_SYS_ETH1_AXI_CLK_CLK_CG0_6_POS = 17,
    PERIPH_SYS_PERIPH_SYS_CFG_REG1_MASK = (int)0x3ffff,
    PERIPH_SYS_PERIPH_SYS_CFG_REG1_POS = 0,
};

enum CPU1_SYS_REG_PERIPH_SYS_CFG_REG2_FIELD
{
    PERIPH_SYS_SYS0_APB_CLK_CLK_CG0_0_MASK = (int)0x1,
    PERIPH_SYS_SYS0_APB_CLK_CLK_CG0_0_POS = 0,
    PERIPH_SYS_SYS0_APB_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    PERIPH_SYS_SYS0_APB_CLK_CLK_DEGLITCH_SW3_POS = 1,
    PERIPH_SYS_SYS0_APB_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    PERIPH_SYS_SYS0_APB_CLK_CLK_DIV0_DIV4_POS = 8,
    PERIPH_SYS_WDT4_APB_CLK_CLK_CG0_1_MASK = (int)0x1000,           // ???UART0 ? WDT4
    PERIPH_SYS_WDT4_APB_CLK_CLK_CG0_1_POS = 12,
    PERIPH_SYS_PERIPH_SYS_CFG_APB_CLK_CLK_CG0_2_MASK = (int)0x2000, // ???UART1 ? PERIPH_SYS_CFG
    PERIPH_SYS_PERIPH_SYS_CFG_APB_CLK_CLK_CG0_2_POS = 13,
    PERIPH_SYS_UART12_APB_CLK_CLK_CG0_3_MASK = (int)0x4000,         // ???UART2 ? UART12
    PERIPH_SYS_UART12_APB_CLK_CLK_CG0_3_POS = 14,
    PERIPH_SYS_UART13_APB_CLK_CLK_CG0_4_MASK = (int)0x8000,         // ???UART3 ? UART13
    PERIPH_SYS_UART13_APB_CLK_CLK_CG0_4_POS = 15,
    PERIPH_SYS_I2C0_APB_CLK_CLK_CG0_5_MASK = (int)0x10000,
    PERIPH_SYS_I2C0_APB_CLK_CLK_CG0_5_POS = 16,
    PERIPH_SYS_I2C1_APB_CLK_CLK_CG0_6_MASK = (int)0x20000,
    PERIPH_SYS_I2C1_APB_CLK_CLK_CG0_6_POS = 17,
    PERIPH_SYS_I2C2_APB_CLK_CLK_CG0_7_MASK = (int)0x40000,
    PERIPH_SYS_I2C2_APB_CLK_CLK_CG0_7_POS = 18,
    PERIPH_SYS_I2C3_APB_CLK_CLK_CG0_8_MASK = (int)0x80000,
    PERIPH_SYS_I2C3_APB_CLK_CLK_CG0_8_POS = 19,
    PERIPH_SYS_I2C4_APB_CLK_CLK_CG0_9_MASK = (int)0x100000,
    PERIPH_SYS_I2C4_APB_CLK_CLK_CG0_9_POS = 20,
    PERIPH_SYS_I2C5_APB_CLK_CLK_CG0_10_MASK = (int)0x200000,
    PERIPH_SYS_I2C5_APB_CLK_CLK_CG0_10_POS = 21,
    PERIPH_SYS_I2C6_APB_CLK_CLK_CG0_11_MASK = (int)0x400000,
    PERIPH_SYS_I2C6_APB_CLK_CLK_CG0_11_POS = 22,
    PERIPH_SYS_I2C7_APB_CLK_CLK_CG0_12_MASK = (int)0x800000,
    PERIPH_SYS_I2C7_APB_CLK_CLK_CG0_12_POS = 23,
    PERIPH_SYS_I2C8_APB_CLK_CLK_CG0_13_MASK = (int)0x1000000,
    PERIPH_SYS_I2C8_APB_CLK_CLK_CG0_13_POS = 24,
    PERIPH_SYS_I2C9_APB_CLK_CLK_CG0_14_MASK = (int)0x2000000,
    PERIPH_SYS_I2C9_APB_CLK_CLK_CG0_14_POS = 25,
    PERIPH_SYS_I2C10_APB_CLK_CLK_CG0_15_MASK = (int)0x4000000,
    PERIPH_SYS_I2C10_APB_CLK_CLK_CG0_15_POS = 26,
    PERIPH_SYS_I2C11_APB_CLK_CLK_CG0_16_MASK = (int)0x8000000,      // ???I2C11 ?? CG0_16
    PERIPH_SYS_I2C11_APB_CLK_CLK_CG0_16_POS = 27,
};

enum CPU1_SYS_REG_PERIPH_SYS_CFG_REG3_FIELD
{
    PERIPH_SYS_SYS1_APB_CLK_CLK_CG0_0_MASK = (int)0x1,
    PERIPH_SYS_SYS1_APB_CLK_CLK_CG0_0_POS = 0,
    PERIPH_SYS_SYS1_APB_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    PERIPH_SYS_SYS1_APB_CLK_CLK_DEGLITCH_SW3_POS = 1,
    PERIPH_SYS_SYS1_APB_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    PERIPH_SYS_SYS1_APB_CLK_CLK_DIV0_DIV4_POS = 8,
    PERIPH_SYS_UART14_APB_CLK_CLK_CG0_1_MASK = (int)0x1000,        // 修改：WDT4 → UART14
    PERIPH_SYS_UART14_APB_CLK_CLK_CG0_1_POS = 12,
    PERIPH_SYS_UART15_APB_CLK_CLK_CG0_2_MASK = (int)0x2000,        // 修改：USB300 → UART15
    PERIPH_SYS_UART15_APB_CLK_CLK_CG0_2_POS = 13,
    PERIPH_SYS_VUSB0_APB_CLK_CLK_CG0_3_MASK = (int)0x4000,        
    PERIPH_SYS_VUSB0_APB_CLK_CLK_CG0_3_POS = 14,
    PERIPH_SYS_VUSB1_APB_CLK_CLK_CG0_4_MASK = (int)0x8000,        
    PERIPH_SYS_VUSB1_APB_CLK_CLK_CG0_4_POS = 15,
};

enum CPU1_SYS_REG_PERIPH_SYS_CFG_REG4_FIELD
{
    PERIPH_SYS_AHB_CLK_CLK_CG0_0_MASK = (int)0x1,
    PERIPH_SYS_AHB_CLK_CLK_CG0_0_POS = 0,
    PERIPH_SYS_AHB_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    PERIPH_SYS_AHB_CLK_CLK_DEGLITCH_SW3_POS = 1,
    PERIPH_SYS_AHB_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    PERIPH_SYS_AHB_CLK_CLK_DIV0_DIV4_POS = 8,
    PERIPH_SYS_ETH0_AHB_CLK_CLK_CG0_1_MASK = (int)0x1000,
    PERIPH_SYS_ETH0_AHB_CLK_CLK_CG0_1_POS = 12,
    PERIPH_SYS_ETH1_AHB_CLK_CLK_CG0_2_MASK = (int)0x2000,
    PERIPH_SYS_ETH1_AHB_CLK_CLK_CG0_2_POS = 13,
    PERIPH_SYS_PERIPH_SYS_CFG_REG4_MASK = (int)0x3fff,
    PERIPH_SYS_PERIPH_SYS_CFG_REG4_POS = 0,
};

enum CPU1_SYS_REG_TOP_SYS_CFG_REG1_FIELD
{
    TOP_SYS_SYS0_APB_CLK_CLK_CG0_0_MASK = (int)0x1,
    TOP_SYS_SYS0_APB_CLK_CLK_CG0_0_POS = 0,
    TOP_SYS_SYS0_APB_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    TOP_SYS_SYS0_APB_CLK_CLK_DEGLITCH_SW3_POS = 1,      // bit7:1
    TOP_SYS_SYS0_APB_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    TOP_SYS_SYS0_APB_CLK_CLK_DIV0_DIV4_POS = 8,         // bit11:8
    TOP_SYS_ANA_PIPE_CFG_APB_CLK_CLK_CG0_1_MASK = (int)0x1000,
    TOP_SYS_ANA_PIPE_CFG_APB_CLK_CLK_CG0_1_POS = 12,    // bit12
    TOP_SYS_ANA_TOP_CRG_CFG_APB_CLK_CLK_CG0_2_MASK = (int)0x2000,
    TOP_SYS_ANA_TOP_CRG_CFG_APB_CLK_CLK_CG0_2_POS = 13, // bit13
    TOP_SYS_PIN_MUX_APB_CLK_CLK_CG0_3_MASK = (int)0x4000,
    TOP_SYS_PIN_MUX_APB_CLK_CLK_CG0_3_POS = 14,         // bit14
    TOP_SYS_PCIE0_PHY_APB_CLK_CLK_CG0_4_MASK = (int)0x8000,
    TOP_SYS_PCIE0_PHY_APB_CLK_CLK_CG0_4_POS = 15,       // bit15
    TOP_SYS_PCIE1_PHY_APB_CLK_CLK_CG0_5_MASK = (int)0x10000,
    TOP_SYS_PCIE1_PHY_APB_CLK_CLK_CG0_5_POS = 16,       // bit16
    TOP_SYS_PCIE2_PHY_APB_CLK_CLK_CG0_6_MASK = (int)0x20000,
    TOP_SYS_PCIE2_PHY_APB_CLK_CLK_CG0_6_POS = 17,       // bit17
    TOP_SYS_ANA_CPU_CFG_APB_CLK_CLK_CG0_7_MASK = (int)0x40000,
    TOP_SYS_ANA_CPU_CFG_APB_CLK_CLK_CG0_7_POS = 18,     // bit18
    TOP_SYS_DPSG0_APB_CLK_CLK_CG0_8_MASK = (int)0x80000,
    TOP_SYS_DPSG0_APB_CLK_CLK_CG0_8_POS = 19,           // bit19
    TOP_SYS_DPSG1_APB_CLK_CLK_CG0_9_MASK = (int)0x100000,
    TOP_SYS_DPSG1_APB_CLK_CLK_CG0_9_POS = 20,            // bit20
};

enum CPU1_SYS_REG_TOP_SYS_CFG_REG2_FIELD
{
    TOP_SYS_AXI_CLK_CLK_CG0_MASK = (int)0x1,
    TOP_SYS_AXI_CLK_CLK_CG0_POS = 0,
    TOP_SYS_AXI_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    TOP_SYS_AXI_CLK_CLK_DEGLITCH_SW3_POS = 1,
    TOP_SYS_AXI_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    TOP_SYS_AXI_CLK_CLK_DIV0_DIV4_POS = 8,
    TOP_SYS_TOP_SYS_CFG_REG2_MASK = (int)0xfff,
    TOP_SYS_TOP_SYS_CFG_REG2_POS = 0,
};

enum CPU1_SYS_REG_TOP_SYS_CFG_REG3_FIELD
{
    TOP_SYS_SYS1_APB_CLK_CLK_CG0_0_MASK = (int)0x1,
    TOP_SYS_SYS1_APB_CLK_CLK_CG0_0_POS = 0,
    TOP_SYS_SYS1_APB_CLK_CLK_DEGLITCH_SW3_MASK = (int)0xfe,
    TOP_SYS_SYS1_APB_CLK_CLK_DEGLITCH_SW3_POS = 1,      // bit7:1
    TOP_SYS_SYS1_APB_CLK_CLK_DIV0_DIV4_MASK = (int)0xf00,
    TOP_SYS_SYS1_APB_CLK_CLK_DIV0_DIV4_POS = 8,         // bit11:8
    TOP_SYS_ANA_PERIPH_CFG_APB_CLK_CLK_CG0_1_MASK = (int)0x1000,
    TOP_SYS_ANA_PERIPH_CFG_APB_CLK_CLK_CG0_1_POS = 12,  // bit12
    TOP_SYS_USB300_PHY_APB_CLK_CLK_CG0_2_MASK = (int)0x2000,
    TOP_SYS_USB300_PHY_APB_CLK_CLK_CG0_2_POS = 13,      // bit13
    TOP_SYS_USB301_PHY_APB_CLK_CLK_CG0_3_MASK = (int)0x4000,
    TOP_SYS_USB301_PHY_APB_CLK_CLK_CG0_3_POS = 14,      // bit14
    TOP_SYS_WDT5_APB_CLK_CLK_CG0_4_MASK = (int)0x8000,
    TOP_SYS_WDT5_APB_CLK_CLK_CG0_4_POS = 15,            // bit15
    TOP_SYS_TOP_DIG_CFG_APB_CLK_CLK_CG0_5_MASK = (int)0x10000,
    TOP_SYS_TOP_DIG_CFG_APB_CLK_CLK_CG0_5_POS = 16,            // bit16
};

enum CPU1_SYS_REG_ARADDR_MAP_CFG_EN_FIELD
{
    CPU1_SYS_ARADDR_MAP_CFG_EN_MASK = (int)0x1,
    CPU1_SYS_ARADDR_MAP_CFG_EN_POS = 0,
};

enum CPU1_SYS_REG_AWADDR_MAP_CFG_EN_FIELD
{
    CPU1_SYS_AWADDR_MAP_CFG_EN_MASK = (int)0x1,
    CPU1_SYS_AWADDR_MAP_CFG_EN_POS = 0,
};

enum CPU1_SYS_REG_ARADDR_MAP_CFG_FIELD
{
    CPU1_SYS_ARADDR_MAP_CFG_MASK = (int)0xf,
    CPU1_SYS_ARADDR_MAP_CFG_POS = 0,
    CPU1_SYS_ARADDR_MAP_CFG_HIGH_MASK = (int)0x10,
    CPU1_SYS_ARADDR_MAP_CFG_HIGH_POS = 4,
};

enum CPU1_SYS_REG_AWADDR_MAP_CFG_FIELD
{
    CPU1_SYS_AWADDR_MAP_CFG_MASK = (int)0xf,
    CPU1_SYS_AWADDR_MAP_CFG_POS = 0,
    CPU1_SYS_AWADDR_MAP_CFG_HIGH_MASK = (int)0x10,
    CPU1_SYS_AWADDR_MAP_CFG_HIGH_POS = 4,
};

enum CPU1_SYS_REG_CPUC908_REG0_FIELD
{
    CPU1_SYS_CPUC908_SOFT_WDT_DBG_MASK = (int)0x1,
    CPU1_SYS_CPUC908_SOFT_WDT_DBG_POS = 0,
};

enum CPU1_SYS_REG_GDMA1_MODULE_EN_FIELD
{
    CPU1_SYS_GDMA1_MODULE_EN_MASK = (int)0x1,
    CPU1_SYS_GDMA1_MODULE_EN_POS = 0,
};

enum CPU1_SYS_REG_DMA_CONNECT_SEL0_FIELD
{
    CPU1_SYS_DMA_CONNECT_SEL0_MASK = (int)0xffffffff,
    CPU1_SYS_DMA_CONNECT_SEL0_POS = 0,
};

enum CPU1_SYS_REG_CPU_SOFT0_C908_INTR_FIELD
{
    CPU1_SYS_CPU_SOFT0_C908_INTR_MASK = (int)0x1,
    CPU1_SYS_CPU_SOFT0_C908_INTR_POS = 0,
};

enum CPU1_SYS_REG_CPU_SOFT1_C908_INTR_FIELD
{
    CPU1_SYS_CPU_SOFT1_C908_INTR_MASK = (int)0x1,
    CPU1_SYS_CPU_SOFT1_C908_INTR_POS = 0,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_C_ID_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_C0_ID_MASK = (int)0xff,
    CPU1_SYS_CPU_SYS_SOFT_C0_ID_POS = 0,
    CPU1_SYS_CPU_SYS_SOFT_C1_ID_MASK = (int)0xff00,
    CPU1_SYS_CPU_SYS_SOFT_C1_ID_POS = 8,
    CPU1_SYS_CPU_SYS_SOFT_C2_ID_MASK = (int)0xff0000,
    CPU1_SYS_CPU_SYS_SOFT_C2_ID_POS = 16,
    CPU1_SYS_CPU_SYS_SOFT_C3_ID_MASK = (int)0xff000000,
    CPU1_SYS_CPU_SYS_SOFT_C3_ID_POS = 24,
};

enum CPU1_SYS_REG_CPU_SYS_SOFT_SDBGEN_FIELD
{
    CPU1_SYS_CPU_SYS_SOFT_SDBGEN_MASK = (int)0xffff,
    CPU1_SYS_CPU_SYS_SOFT_SDBGEN_POS = 0,
};

enum CPU1_SYS_REG_DMA_CONNECT_SEL1_FIELD
{
    CPU1_SYS_DMA_CONNECT_SEL1_MASK = (int)0xffffffff,
    CPU1_SYS_DMA_CONNECT_SEL1_POS = 0,
};

enum CPU1_SYS_REG_DMA_CONNECT_SEL2_FIELD
{
    CPU1_SYS_DMA_CONNECT_SEL2_MASK = (int)0xffffffff,
    CPU1_SYS_DMA_CONNECT_SEL2_POS = 0,
};

enum CPU1_SYS_REG_DMA_CONNECT_SEL3_FIELD
{
    CPU1_SYS_DMA_CONNECT_SEL3_MASK = (int)0xffffffff,
    CPU1_SYS_DMA_CONNECT_SEL3_POS = 0,
};

enum CPU1_SYS_REG_ADC0_REG0_RW_FIELD
{
    CPU1_SYS_ADC0_REG_TRIG_EXT_MASK = (int)0x1,
    CPU1_SYS_ADC0_REG_TRIG_EXT_POS = 0,
    CPU1_SYS_ADC0_INJ_TRIG_EXT_MASK = (int)0x2,
    CPU1_SYS_ADC0_INJ_TRIG_EXT_POS = 1,
    CPU1_SYS_ADC0_RSI_REQ_MASK = (int)0x4,
    CPU1_SYS_ADC0_RSI_REQ_POS = 2,
    CPU1_SYS_ADC0_TRIG_EN_MASK = (int)0x8,
    CPU1_SYS_ADC0_TRIG_EN_POS = 3,
};

enum CPU1_SYS_REG_ADC0_REG0_RO_FIELD
{
    CPU1_SYS_ADC0_EN_MASK = (int)0x1,
    CPU1_SYS_ADC0_EN_POS = 0,
    CPU1_SYS_ADC0_SAMPLE_MASK = (int)0x6,
    CPU1_SYS_ADC0_SAMPLE_POS = 1,
    CPU1_SYS_ADC0_SMPL_EN_MASK = (int)0x18,
    CPU1_SYS_ADC0_SMPL_EN_POS = 3,
    CPU1_SYS_ADC0_CONV_EN_MASK = (int)0x60,
    CPU1_SYS_ADC0_CONV_EN_POS = 5,
    CPU1_SYS_ADC0_BUF_BYP_MASK = (int)0x180,
    CPU1_SYS_ADC0_BUF_BYP_POS = 7,
    CPU1_SYS_ADC0_RES_BYP_MASK = (int)0x600,
    CPU1_SYS_ADC0_RES_BYP_POS = 9,
};

enum CPU1_SYS_REG_ADC0_REG1_RO_FIELD
{
    CPU1_SYS_ADC0_CTRL_MASK = (int)0xffffff,
    CPU1_SYS_ADC0_CTRL_POS = 0,
};

enum CPU1_SYS_REG_ADC0_REG2_RO_FIELD
{
    CPU1_SYS_ADC0_AMIC_CTRL_MASK = (int)0x7fff,
    CPU1_SYS_ADC0_AMIC_CTRL_POS = 0,
    CPU1_SYS_ADC0_AMIC_TSTEN_MASK = (int)0x8000,
    CPU1_SYS_ADC0_AMIC_TSTEN_POS = 15,
    CPU1_SYS_ADC0_AWD_HIGH_MASK = (int)0x10000,
    CPU1_SYS_ADC0_AWD_HIGH_POS = 16,
    CPU1_SYS_ADC0_AWD_LOW_MASK = (int)0x20000,
    CPU1_SYS_ADC0_AWD_LOW_POS = 17,
    CPU1_SYS_ADC0_RSI_ACK_MASK = (int)0x40000,
    CPU1_SYS_ADC0_RSI_ACK_POS = 18,
    CPU1_SYS_ADC0_RSI_DAT_MASK = (int)0x7ff80000,
    CPU1_SYS_ADC0_RSI_DAT_POS = 19,
};

enum CPU1_SYS_REG_ADC0_REG3_RO_FIELD
{
    CPU1_SYS_ADC0_TRIM_DATA_MASK = (int)0xfff,
    CPU1_SYS_ADC0_TRIM_DATA_POS = 0,
};

enum CPU1_SYS_REG_C908_SOFT_RW_FIELD
{
    CPU1_SYS_MATRIX_CPU1_MSTIF_CSYSREQ_MASK = (int)0x1,
    CPU1_SYS_MATRIX_CPU1_MSTIF_CSYSREQ_POS = 0,
    CPU1_SYS_PAD_CORE0_SLEEP_IN_MASK = (int)0x2,
    CPU1_SYS_PAD_CORE0_SLEEP_IN_POS = 1,
    CPU1_SYS_PAD_CORE1_SLEEP_IN_MASK = (int)0x4,
    CPU1_SYS_PAD_CORE1_SLEEP_IN_POS = 2,
    CPU1_SYS_PAD_CORE2_SLEEP_IN_MASK = (int)0x8,
    CPU1_SYS_PAD_CORE2_SLEEP_IN_POS = 3,
    CPU1_SYS_PAD_CORE3_SLEEP_IN_MASK = (int)0x10,
    CPU1_SYS_PAD_CORE3_SLEEP_IN_POS = 4,
    CPU1_SYS_PAD_CPU_SLEEP_IN_MASK = (int)0x20,
    CPU1_SYS_PAD_CPU_SLEEP_IN_POS = 5,
    CPU1_SYS_PAD_TDT_SLEEP_IN_MASK = (int)0x40,
    CPU1_SYS_PAD_TDT_SLEEP_IN_POS = 6,
};

enum CPU1_SYS_REG_C908_SOFT_RO_FIELD
{
    CPU1_SYS_CPU1_MATRIX_MSTIF_CACTIVE_MASK = (int)0x1,
    CPU1_SYS_CPU1_MATRIX_MSTIF_CACTIVE_POS = 0,
    CPU1_SYS_CPU1_MATRIX_MSTIF_CSYSACK_MASK = (int)0x2,
    CPU1_SYS_CPU1_MATRIX_MSTIF_CSYSACK_POS = 1,
    CPU1_SYS_CORE2_PAD_SLEEP_OUT_MASK = (int)0x4,
    CPU1_SYS_CORE2_PAD_SLEEP_OUT_POS = 2,
    CPU1_SYS_TDT_PAD_SLEEP_OUT_MASK = (int)0x8,
    CPU1_SYS_TDT_PAD_SLEEP_OUT_POS = 3,
    CPU1_SYS_CPU_PAD_SLEEP_OUT_MASK = (int)0x10,
    CPU1_SYS_CPU_PAD_SLEEP_OUT_POS = 4,
    CPU1_SYS_CORE3_PAD_SLEEP_OUT_MASK = (int)0x20,
    CPU1_SYS_CORE3_PAD_SLEEP_OUT_POS = 5,
    CPU1_SYS_CORE0_PAD_SLEEP_OUT_MASK = (int)0x40,
    CPU1_SYS_CORE0_PAD_SLEEP_OUT_POS = 6,
    CPU1_SYS_CORE1_PAD_SLEEP_OUT_MASK = (int)0x80,
    CPU1_SYS_CORE1_PAD_SLEEP_OUT_POS = 7,
};

enum CPU1_SYS_REG_ADC1_REG0_RW_FIELD
{
    CPU1_SYS_ADC1_REG_TRIG_EXT_MASK = (int)0x1,
    CPU1_SYS_ADC1_REG_TRIG_EXT_POS = 0,
    CPU1_SYS_ADC1_INJ_TRIG_EXT_MASK = (int)0x2,
    CPU1_SYS_ADC1_INJ_TRIG_EXT_POS = 1,
    CPU1_SYS_ADC1_RSI_REQ_MASK = (int)0x4,
    CPU1_SYS_ADC1_RSI_REQ_POS = 2,
    CPU1_SYS_ADC1_TRIG_EN_MASK = (int)0x8,
    CPU1_SYS_ADC1_TRIG_EN_POS = 3,
};

enum CPU1_SYS_REG_ADC1_REG0_RO_FIELD
{
    CPU1_SYS_ADC1_EN_MASK = (int)0x1,
    CPU1_SYS_ADC1_EN_POS = 0,
    CPU1_SYS_ADC1_SAMPLE_MASK = (int)0x6,
    CPU1_SYS_ADC1_SAMPLE_POS = 1,
    CPU1_SYS_ADC1_SMPL_EN_MASK = (int)0x18,
    CPU1_SYS_ADC1_SMPL_EN_POS = 3,
    CPU1_SYS_ADC1_CONV_EN_MASK = (int)0x60,
    CPU1_SYS_ADC1_CONV_EN_POS = 5,
    CPU1_SYS_ADC1_BUF_BYP_MASK = (int)0x180,
    CPU1_SYS_ADC1_BUF_BYP_POS = 7,
    CPU1_SYS_ADC1_RES_BYP_MASK = (int)0x600,
    CPU1_SYS_ADC1_RES_BYP_POS = 9,
};

enum CPU1_SYS_REG_ADC1_REG1_RO_FIELD
{
    CPU1_SYS_ADC1_CTRL_MASK = (int)0xffffff,
    CPU1_SYS_ADC1_CTRL_POS = 0,
};

enum CPU1_SYS_REG_ADC1_REG2_RO_FIELD
{
    CPU1_SYS_ADC1_AMIC_CTRL_MASK = (int)0x7fff,
    CPU1_SYS_ADC1_AMIC_CTRL_POS = 0,
    CPU1_SYS_ADC1_AMIC_TSTEN_MASK = (int)0x8000,
    CPU1_SYS_ADC1_AMIC_TSTEN_POS = 15,
    CPU1_SYS_ADC1_AWD_HIGH_MASK = (int)0x10000,
    CPU1_SYS_ADC1_AWD_HIGH_POS = 16,
    CPU1_SYS_ADC1_AWD_LOW_MASK = (int)0x20000,
    CPU1_SYS_ADC1_AWD_LOW_POS = 17,
    CPU1_SYS_ADC1_RSI_ACK_MASK = (int)0x40000,
    CPU1_SYS_ADC1_RSI_ACK_POS = 18,
    CPU1_SYS_ADC1_RSI_DAT_MASK = (int)0x7ff80000,
    CPU1_SYS_ADC1_RSI_DAT_POS = 19,
};

enum CPU1_SYS_REG_ADC1_REG3_RO_FIELD
{
    CPU1_SYS_ADC1_TRIM_DATA_MASK = (int)0xfff,
    CPU1_SYS_ADC1_TRIM_DATA_POS = 0,
};

enum CPU1_SYS_REG_DMA_CONNECT_SEL4_FIELD
{
    CPU1_SYS_DMA_CONNECT_SEL4_MASK = (int)0xffffffff,
    CPU1_SYS_DMA_CONNECT_SEL4_POS = 0,
};

enum CPU1_SYS_REG_DMA_CONNECT_SEL5_FIELD
{
    CPU1_SYS_DMA_CONNECT_SEL5_MASK = (int)0xffffffff,
    CPU1_SYS_DMA_CONNECT_SEL5_POS = 0,
};

enum CPU1_SYS_REG_DMA_CONNECT_SEL6_FIELD
{
    CPU1_SYS_DMA_CONNECT_SEL6_MASK = (int)0xffffffff,
    CPU1_SYS_DMA_CONNECT_SEL6_POS = 0,
};

enum CPU1_SYS_REG_DMA_CONNECT_SEL7_FIELD
{
    CPU1_SYS_DMA_CONNECT_SEL7_MASK = (int)0xffffffff,
    CPU1_SYS_DMA_CONNECT_SEL7_POS = 0,
};

enum CPU1_SYS_REG_GPIORSTIND_FIELD
{
    CPU1_SYS_GPIORSTIND_DS0_MASK = (int)0x1,
    CPU1_SYS_GPIORSTIND_DS0_POS = 0,
    CPU1_SYS_GPIORSTIND_DS1_MASK = (int)0x2,
    CPU1_SYS_GPIORSTIND_DS1_POS = 1,
    CPU1_SYS_GPIORSTIND_DS2_MASK = (int)0x4,
    CPU1_SYS_GPIORSTIND_DS2_POS = 2,
    CPU1_SYS_GPIORSTIND_DS3_MASK = (int)0x8,
    CPU1_SYS_GPIORSTIND_DS3_POS = 3,
    CPU1_SYS_GPIORSTIND_REN_MASK = (int)0x10,
    CPU1_SYS_GPIORSTIND_REN_POS = 4,
    CPU1_SYS_GPIORSTIND_IE_MASK = (int)0x20,
    CPU1_SYS_GPIORSTIND_IE_POS = 5,
    CPU1_SYS_GPIORSTIND_OE_MASK = (int)0x40,
    CPU1_SYS_GPIORSTIND_OE_POS = 6,
    CPU1_SYS_GPIORSTIND_PU_MASK = (int)0x80,
    CPU1_SYS_GPIORSTIND_PU_POS = 7,
    CPU1_SYS_GPIORSTIND_PD_MASK = (int)0x100,
    CPU1_SYS_GPIORSTIND_PD_POS = 8,
    CPU1_SYS_GPIORSTIND_ST_MASK = (int)0x200,
    CPU1_SYS_GPIORSTIND_ST_POS = 9,
    CPU1_SYS_GPIORSTIND_SL_MASK = (int)0x400,
    CPU1_SYS_GPIORSTIND_SL_POS = 10,
    CPU1_SYS_GPIORSTIND_ODE_MASK = (int)0x800,
    CPU1_SYS_GPIORSTIND_ODE_POS = 11,
    CPU1_SYS_GPIORSTIND_O_MASK = (int)0x1000,
    CPU1_SYS_GPIORSTIND_O_POS = 12,
    CPU1_SYS_GPIORSTIND_O_EN_MASK = (int)0x2000,
    CPU1_SYS_GPIORSTIND_O_EN_POS = 13,
};

enum CPU1_SYS_REG_C908_RSTIND_INTR_MASK_FIELD
{
    CPU1_SYS_C908_RSTIND_INTR_MASK_MASK = (int)0x1,
    CPU1_SYS_C908_RSTIND_INTR_MASK_POS = 0,
};

enum CPU1_SYS_REG_C908_RSTIND_INTR_CLR_FIELD
{
    CPU1_SYS_C908_RSTIND_INTR_CLR_MASK = (int)0x1,
    CPU1_SYS_C908_RSTIND_INTR_CLR_POS = 0,
};

enum CPU1_SYS_REG_C908_RSTIND_INTR_RAW_FIELD
{
    CPU1_SYS_C908_RSTIND_INTR_RAW_MASK = (int)0x1,
    CPU1_SYS_C908_RSTIND_INTR_RAW_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CRG_PIC_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CRG_PIC_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CRG_PIC_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CRG_PIC_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CRG_PIC_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CRG_PIC_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CRG_CPU1_SYS_AHB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_AHB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_AHB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CRG_CPU1_SYS_AHB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_AHB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_AHB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CRG_CPU1_SYS_PLL_CPU_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_PLL_CPU_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_PLL_CPU_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CRG_CPU1_SYS_PLL_CPU_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_PLL_CPU_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_PLL_CPU_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CRG_CPU1_SYS_APB_CLK_TOP_RST_N_REG0_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_APB_CLK_TOP_RST_N_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_APB_CLK_TOP_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CRG_CPU1_SYS_APB_CLK_TOP_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_APB_CLK_TOP_RST_N_REG0_CLR_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CRG_CPU1_SYS_APB_CLK_TOP_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_CPU1_IP_SOFT_RST_N_REG0_FIELD
{
    CPU1_SYS_CPU1_IP_SOFT_RST_N_REG0_MASK = (int)0x1f,
    CPU1_SYS_CPU1_IP_SOFT_RST_N_REG0_POS = 0,
};

enum CPU1_SYS_REG_CPU1_IP_SOFT_RST_N_REG0_CLR_FIELD
{
    CPU1_SYS_CPU1_IP_SOFT_RST_N_REG0_CLR_MASK = (int)0x1f,
    CPU1_SYS_CPU1_IP_SOFT_RST_N_REG0_CLR_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_PIC_CLK_REG0_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_PIC_CLK_REG0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_PIC_CLK_REG0_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CFG_REG1_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CFG_REG1_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CFG_REG1_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CFG_REG2_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CFG_REG2_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CFG_REG2_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU1_SYS_CFG_REG3_FIELD
{
    CPU1_SYS_CPU1_CPU1_SYS_CFG_REG3_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU1_SYS_CFG_REG3_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU_SYS_SOFT_APB_BASE_L_FIELD
{
    CPU1_SYS_CPU1_CPU_SYS_SOFT_APB_BASE_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_APB_BASE_L_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU_SYS_SOFT_APB_BASE_H_FIELD
{
    CPU1_SYS_CPU1_CPU_SYS_SOFT_APB_BASE_H_MASK = (int)0xff,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_APB_BASE_H_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU_SYS_SOFT_CORE0_RVBA_H_FIELD
{
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE0_RVBA_H_MASK = (int)0xff,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE0_RVBA_H_POS = 0,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE1_RVBA_H_MASK = (int)0xff00,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE1_RVBA_H_POS = 8,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE2_RVBA_H_MASK = (int)0xff0000,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE2_RVBA_H_POS = 16,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE3_RVBA_H_MASK = (int)0xff000000,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE3_RVBA_H_POS = 24,
};

enum CPU1_SYS_REG_CPU1_CPU_SYS_SOFT_CORE0_RVBA_L_FIELD
{
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE0_RVBA_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE0_RVBA_L_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU_SYS_SOFT_CORE1_RVBA_L_FIELD
{
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE1_RVBA_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE1_RVBA_L_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU_SYS_SOFT_CORE2_RVBA_L_FIELD
{
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE2_RVBA_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE2_RVBA_L_POS = 0,
};

enum CPU1_SYS_REG_CPU1_CPU_SYS_SOFT_CORE3_RVBA_L_FIELD
{
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE3_RVBA_L_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_CPU_SYS_SOFT_CORE3_RVBA_L_POS = 0,
};

enum CPU1_SYS_REG_CPU1_SYS_CFG_LOCK_FIELD
{
    CPU1_SYS_CPU1_SYS_CFG_LOCK_MASK = (int)0x1,
    CPU1_SYS_CPU1_SYS_CFG_LOCK_POS = 0,
};

enum CPU1_SYS_REG_CPU1_SYS_ADJUST_BUS_EN_FIELD
{
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_M16_DDR_EN_MASK = (int)0x1,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_M16_DDR_EN_POS = 0,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_DDR_EN_MASK = (int)0x2,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_DDR_EN_POS = 1,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_PIPE_EN_MASK = (int)0x4,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_PIPE_EN_POS = 2,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_PERIPH_EN_MASK = (int)0x8,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_PERIPH_EN_POS = 3,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_ANA_EN_MASK = (int)0x10,
    CPU1_SYS_ADJUST_ADB400_SLV_CPU_ANA_EN_POS = 4,
    CPU1_SYS_ADJUST_ADB400_MST_PIPE_CPU_EN_MASK = (int)0x20,
    CPU1_SYS_ADJUST_ADB400_MST_PIPE_CPU_EN_POS = 5,
    CPU1_SYS_ADJUST_ADB400_MST_PERIPH_CPU_EN_MASK = (int)0x40,
    CPU1_SYS_ADJUST_ADB400_MST_PERIPH_CPU_EN_POS = 6,
    CPU1_SYS_ADJUST_CPU0_CPU1_H2X_AHB_EN_MASK = (int)0x80,
    CPU1_SYS_ADJUST_CPU0_CPU1_H2X_AHB_EN_POS = 7,
    CPU1_SYS_ADJUST_CPU0_CPU1_H2X_AXI_EN_MASK = (int)0x100,
    CPU1_SYS_ADJUST_CPU0_CPU1_H2X_AXI_EN_POS = 8,
    CPU1_SYS_ADJUST_CPU1_CPU0_X2H_AHB_EN_MASK = (int)0x200,
    CPU1_SYS_ADJUST_CPU1_CPU0_X2H_AHB_EN_POS = 9,
    CPU1_SYS_ADJUST_CPU1_CPU0_X2H_AXI_EN_MASK = (int)0x400,
    CPU1_SYS_ADJUST_CPU1_CPU0_X2H_AXI_EN_POS = 10,
};

enum CPU1_SYS_REG_ADC2_REG0_RW_FIELD
{
    CPU1_SYS_ADC2_REG_TRIG_EXT_MASK = (int)0x1,
    CPU1_SYS_ADC2_REG_TRIG_EXT_POS = 0,
    CPU1_SYS_ADC2_INJ_TRIG_EXT_MASK = (int)0x2,
    CPU1_SYS_ADC2_INJ_TRIG_EXT_POS = 1,
    CPU1_SYS_ADC2_RSI_REQ_MASK = (int)0x4,
    CPU1_SYS_ADC2_RSI_REQ_POS = 2,
    CPU1_SYS_ADC2_TRIG_EN_MASK = (int)0x8,
    CPU1_SYS_ADC2_TRIG_EN_POS = 3,
};

enum CPU1_SYS_REG_ADC2_REG0_RO_FIELD
{
    CPU1_SYS_ADC2_EN_MASK = (int)0x1,
    CPU1_SYS_ADC2_EN_POS = 0,
    CPU1_SYS_ADC2_SAMPLE_MASK = (int)0x6,
    CPU1_SYS_ADC2_SAMPLE_POS = 1,
    CPU1_SYS_ADC2_SMPL_EN_MASK = (int)0x18,
    CPU1_SYS_ADC2_SMPL_EN_POS = 3,
    CPU1_SYS_ADC2_CONV_EN_MASK = (int)0x60,
    CPU1_SYS_ADC2_CONV_EN_POS = 5,
    CPU1_SYS_ADC2_BUF_BYP_MASK = (int)0x180,
    CPU1_SYS_ADC2_BUF_BYP_POS = 7,
    CPU1_SYS_ADC2_RES_BYP_MASK = (int)0x600,
    CPU1_SYS_ADC2_RES_BYP_POS = 9,
};

enum CPU1_SYS_REG_ADC2_REG1_RO_FIELD
{
    CPU1_SYS_ADC2_CTRL_MASK = (int)0xffffff,
    CPU1_SYS_ADC2_CTRL_POS = 0,
};

enum CPU1_SYS_REG_ADC2_REG2_RO_FIELD
{
    CPU1_SYS_ADC2_AMIC_CTRL_MASK = (int)0x7fff,
    CPU1_SYS_ADC2_AMIC_CTRL_POS = 0,
    CPU1_SYS_ADC2_AMIC_TSTEN_MASK = (int)0x8000,
    CPU1_SYS_ADC2_AMIC_TSTEN_POS = 15,
    CPU1_SYS_ADC2_AWD_HIGH_MASK = (int)0x10000,
    CPU1_SYS_ADC2_AWD_HIGH_POS = 16,
    CPU1_SYS_ADC2_AWD_LOW_MASK = (int)0x20000,
    CPU1_SYS_ADC2_AWD_LOW_POS = 17,
    CPU1_SYS_ADC2_RSI_ACK_MASK = (int)0x40000,
    CPU1_SYS_ADC2_RSI_ACK_POS = 18,
    CPU1_SYS_ADC2_RSI_DAT_MASK = (int)0x7ff80000,
    CPU1_SYS_ADC2_RSI_DAT_POS = 19,
};

enum CPU1_SYS_REG_ADC2_REG3_RO_FIELD
{
    CPU1_SYS_ADC2_TRIM_DATA_MASK = (int)0xfff,
    CPU1_SYS_ADC2_TRIM_DATA_POS = 0,
};

enum CPU1_SYS_REG_WDT7_RST_N_EN_FIELD
{
    CPU1_SYS_WDT7_RST_N_EN_MASK = (int)0x1,
    CPU1_SYS_WDT7_RST_N_EN_POS = 0,
};

enum CPU1_SYS_REG_H2X_ADJUST_AXI_EN_FIELD
{
    CPU1_SYS_H2X_ADJUST_AXI_EN_MASK = (int)0x1,
    CPU1_SYS_H2X_ADJUST_AXI_EN_POS = 0,
};

enum CPU1_SYS_REG_CORE0_EMA0_FIELD
{
    CPU1_SYS_CPU_64_52_00EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_64_52_00EMA_POS = 0,
    CPU1_SYS_CPU_64_52_0EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_64_52_0EMAW_POS = 3,
    CPU1_SYS_CPU_64_52_0EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_64_52_0EMAS_POS = 5,
    CPU1_SYS_CPU_64_152_00EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_64_152_00EMA_POS = 6,
    CPU1_SYS_CPU_64_152_0EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_64_152_0EMAW_POS = 9,
    CPU1_SYS_CPU_64_152_0EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_64_152_0EMAS_POS = 11,
    CPU1_SYS_CPU_128_26_00EMA_MASK = (int)0x7000,
    CPU1_SYS_CPU_128_26_00EMA_POS = 12,
    CPU1_SYS_CPU_128_26_0EMAW_MASK = (int)0x18000,
    CPU1_SYS_CPU_128_26_0EMAW_POS = 15,
    CPU1_SYS_CPU_128_26_0EMAS_MASK = (int)0x20000,
    CPU1_SYS_CPU_128_26_0EMAS_POS = 17,
    CPU1_SYS_CPU_128_48_00EMA_MASK = (int)0x1c0000,
    CPU1_SYS_CPU_128_48_00EMA_POS = 18,
    CPU1_SYS_CPU_128_48_0EMAW_MASK = (int)0x600000,
    CPU1_SYS_CPU_128_48_0EMAW_POS = 21,
    CPU1_SYS_CPU_128_48_0EMAS_MASK = (int)0x800000,
    CPU1_SYS_CPU_128_48_0EMAS_POS = 23,
    CPU1_SYS_CPU_128_152_00EMA_MASK = (int)0x7000000,
    CPU1_SYS_CPU_128_152_00EMA_POS = 24,
    CPU1_SYS_CPU_128_152_0EMAW_MASK = (int)0x18000000,
    CPU1_SYS_CPU_128_152_0EMAW_POS = 27,
    CPU1_SYS_CPU_128_152_0EMAS_MASK = (int)0x20000000,
    CPU1_SYS_CPU_128_152_0EMAS_POS = 29,
};

enum CPU1_SYS_REG_CORE0_EMA1_FIELD
{
    CPU1_SYS_CPU_128_60_00EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_128_60_00EMA_POS = 0,
    CPU1_SYS_CPU_128_60_0EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_128_60_0EMAW_POS = 3,
    CPU1_SYS_CPU_128_60_0EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_128_60_0EMAS_POS = 5,
    CPU1_SYS_CPU_256_110_00EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_256_110_00EMA_POS = 6,
    CPU1_SYS_CPU_256_110_0EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_256_110_0EMAW_POS = 9,
    CPU1_SYS_CPU_256_110_0EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_256_110_0EMAS_POS = 11,
    CPU1_SYS_CPU_256_21_00EMA_MASK = (int)0x7000,
    CPU1_SYS_CPU_256_21_00EMA_POS = 12,
    CPU1_SYS_CPU_256_21_0EMAW_MASK = (int)0x18000,
    CPU1_SYS_CPU_256_21_0EMAW_POS = 15,
    CPU1_SYS_CPU_256_21_0EMAS_MASK = (int)0x20000,
    CPU1_SYS_CPU_256_21_0EMAS_POS = 17,
    CPU1_SYS_CPU_256_32_00EMA_MASK = (int)0x1c0000,
    CPU1_SYS_CPU_256_32_00EMA_POS = 18,
    CPU1_SYS_CPU_256_32_0EMAW_MASK = (int)0x600000,
    CPU1_SYS_CPU_256_32_0EMAW_POS = 21,
    CPU1_SYS_CPU_256_32_0EMAS_MASK = (int)0x800000,
    CPU1_SYS_CPU_256_32_0EMAS_POS = 23,
    CPU1_SYS_CPU_256_88_00EMA_MASK = (int)0x7000000,
    CPU1_SYS_CPU_256_88_00EMA_POS = 24,
    CPU1_SYS_CPU_256_88_0EMAW_MASK = (int)0x18000000,
    CPU1_SYS_CPU_256_88_0EMAW_POS = 27,
    CPU1_SYS_CPU_256_88_0EMAS_MASK = (int)0x20000000,
    CPU1_SYS_CPU_256_88_0EMAS_POS = 29,
};

enum CPU1_SYS_REG_CORE0_EMA2_FIELD
{
    CPU1_SYS_CPU_512_39_00EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_512_39_00EMA_POS = 0,
    CPU1_SYS_CPU_512_39_0EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_512_39_0EMAW_POS = 3,
    CPU1_SYS_CPU_512_39_0EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_512_39_0EMAS_POS = 5,
    CPU1_SYS_CPU_512_70_00EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_512_70_00EMA_POS = 6,
    CPU1_SYS_CPU_512_70_0EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_512_70_0EMAW_POS = 9,
    CPU1_SYS_CPU_512_70_0EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_512_70_0EMAS_POS = 11,
};

enum CPU1_SYS_REG_CORE1_EMA0_FIELD
{
    CPU1_SYS_CPU_64_52_10EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_64_52_10EMA_POS = 0,
    CPU1_SYS_CPU_64_52_1EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_64_52_1EMAW_POS = 3,
    CPU1_SYS_CPU_64_52_1EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_64_52_1EMAS_POS = 5,
    CPU1_SYS_CPU_64_152_10EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_64_152_10EMA_POS = 6,
    CPU1_SYS_CPU_64_152_1EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_64_152_1EMAW_POS = 9,
    CPU1_SYS_CPU_64_152_1EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_64_152_1EMAS_POS = 11,
    CPU1_SYS_CPU_128_26_10EMA_MASK = (int)0x7000,
    CPU1_SYS_CPU_128_26_10EMA_POS = 12,
    CPU1_SYS_CPU_128_26_1EMAW_MASK = (int)0x18000,
    CPU1_SYS_CPU_128_26_1EMAW_POS = 15,
    CPU1_SYS_CPU_128_26_1EMAS_MASK = (int)0x20000,
    CPU1_SYS_CPU_128_26_1EMAS_POS = 17,
    CPU1_SYS_CPU_128_48_10EMA_MASK = (int)0x1c0000,
    CPU1_SYS_CPU_128_48_10EMA_POS = 18,
    CPU1_SYS_CPU_128_48_1EMAW_MASK = (int)0x600000,
    CPU1_SYS_CPU_128_48_1EMAW_POS = 21,
    CPU1_SYS_CPU_128_48_1EMAS_MASK = (int)0x800000,
    CPU1_SYS_CPU_128_48_1EMAS_POS = 23,
    CPU1_SYS_CPU_128_152_10EMA_MASK = (int)0x7000000,
    CPU1_SYS_CPU_128_152_10EMA_POS = 24,
    CPU1_SYS_CPU_128_152_1EMAW_MASK = (int)0x18000000,
    CPU1_SYS_CPU_128_152_1EMAW_POS = 27,
    CPU1_SYS_CPU_128_152_1EMAS_MASK = (int)0x20000000,
    CPU1_SYS_CPU_128_152_1EMAS_POS = 29,
};

enum CPU1_SYS_REG_CORE1_EMA1_FIELD
{
    CPU1_SYS_CPU_128_60_10EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_128_60_10EMA_POS = 0,
    CPU1_SYS_CPU_128_60_1EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_128_60_1EMAW_POS = 3,
    CPU1_SYS_CPU_128_60_1EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_128_60_1EMAS_POS = 5,
    CPU1_SYS_CPU_256_110_10EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_256_110_10EMA_POS = 6,
    CPU1_SYS_CPU_256_110_1EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_256_110_1EMAW_POS = 9,
    CPU1_SYS_CPU_256_110_1EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_256_110_1EMAS_POS = 11,
    CPU1_SYS_CPU_256_21_10EMA_MASK = (int)0x7000,
    CPU1_SYS_CPU_256_21_10EMA_POS = 12,
    CPU1_SYS_CPU_256_21_1EMAW_MASK = (int)0x18000,
    CPU1_SYS_CPU_256_21_1EMAW_POS = 15,
    CPU1_SYS_CPU_256_21_1EMAS_MASK = (int)0x20000,
    CPU1_SYS_CPU_256_21_1EMAS_POS = 17,
    CPU1_SYS_CPU_256_32_10EMA_MASK = (int)0x1c0000,
    CPU1_SYS_CPU_256_32_10EMA_POS = 18,
    CPU1_SYS_CPU_256_32_1EMAW_MASK = (int)0x600000,
    CPU1_SYS_CPU_256_32_1EMAW_POS = 21,
    CPU1_SYS_CPU_256_32_1EMAS_MASK = (int)0x800000,
    CPU1_SYS_CPU_256_32_1EMAS_POS = 23,
    CPU1_SYS_CPU_256_88_10EMA_MASK = (int)0x7000000,
    CPU1_SYS_CPU_256_88_10EMA_POS = 24,
    CPU1_SYS_CPU_256_88_1EMAW_MASK = (int)0x18000000,
    CPU1_SYS_CPU_256_88_1EMAW_POS = 27,
    CPU1_SYS_CPU_256_88_1EMAS_MASK = (int)0x20000000,
    CPU1_SYS_CPU_256_88_1EMAS_POS = 29,
};

enum CPU1_SYS_REG_CORE1_EMA2_FIELD
{
    CPU1_SYS_CPU_512_39_10EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_512_39_10EMA_POS = 0,
    CPU1_SYS_CPU_512_39_1EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_512_39_1EMAW_POS = 3,
    CPU1_SYS_CPU_512_39_1EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_512_39_1EMAS_POS = 5,
    CPU1_SYS_CPU_512_70_10EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_512_70_10EMA_POS = 6,
    CPU1_SYS_CPU_512_70_1EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_512_70_1EMAW_POS = 9,
    CPU1_SYS_CPU_512_70_1EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_512_70_1EMAS_POS = 11,
};

enum CPU1_SYS_REG_CORE2_EMA0_FIELD
{
    CPU1_SYS_CPU_64_52_20EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_64_52_20EMA_POS = 0,
    CPU1_SYS_CPU_64_52_2EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_64_52_2EMAW_POS = 3,
    CPU1_SYS_CPU_64_52_2EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_64_52_2EMAS_POS = 5,
    CPU1_SYS_CPU_64_152_20EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_64_152_20EMA_POS = 6,
    CPU1_SYS_CPU_64_152_2EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_64_152_2EMAW_POS = 9,
    CPU1_SYS_CPU_64_152_2EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_64_152_2EMAS_POS = 11,
    CPU1_SYS_CPU_128_26_20EMA_MASK = (int)0x7000,
    CPU1_SYS_CPU_128_26_20EMA_POS = 12,
    CPU1_SYS_CPU_128_26_2EMAW_MASK = (int)0x18000,
    CPU1_SYS_CPU_128_26_2EMAW_POS = 15,
    CPU1_SYS_CPU_128_26_2EMAS_MASK = (int)0x20000,
    CPU1_SYS_CPU_128_26_2EMAS_POS = 17,
    CPU1_SYS_CPU_128_48_20EMA_MASK = (int)0x1c0000,
    CPU1_SYS_CPU_128_48_20EMA_POS = 18,
    CPU1_SYS_CPU_128_48_2EMAW_MASK = (int)0x600000,
    CPU1_SYS_CPU_128_48_2EMAW_POS = 21,
    CPU1_SYS_CPU_128_48_2EMAS_MASK = (int)0x800000,
    CPU1_SYS_CPU_128_48_2EMAS_POS = 23,
    CPU1_SYS_CPU_128_152_20EMA_MASK = (int)0x7000000,
    CPU1_SYS_CPU_128_152_20EMA_POS = 24,
    CPU1_SYS_CPU_128_152_2EMAW_MASK = (int)0x18000000,
    CPU1_SYS_CPU_128_152_2EMAW_POS = 27,
    CPU1_SYS_CPU_128_152_2EMAS_MASK = (int)0x20000000,
    CPU1_SYS_CPU_128_152_2EMAS_POS = 29,
};

enum CPU1_SYS_REG_CORE2_EMA1_FIELD
{
    CPU1_SYS_CPU_128_60_20EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_128_60_20EMA_POS = 0,
    CPU1_SYS_CPU_128_60_2EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_128_60_2EMAW_POS = 3,
    CPU1_SYS_CPU_128_60_2EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_128_60_2EMAS_POS = 5,
    CPU1_SYS_CPU_256_110_20EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_256_110_20EMA_POS = 6,
    CPU1_SYS_CPU_256_110_2EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_256_110_2EMAW_POS = 9,
    CPU1_SYS_CPU_256_110_2EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_256_110_2EMAS_POS = 11,
    CPU1_SYS_CPU_256_21_20EMA_MASK = (int)0x7000,
    CPU1_SYS_CPU_256_21_20EMA_POS = 12,
    CPU1_SYS_CPU_256_21_2EMAW_MASK = (int)0x18000,
    CPU1_SYS_CPU_256_21_2EMAW_POS = 15,
    CPU1_SYS_CPU_256_21_2EMAS_MASK = (int)0x20000,
    CPU1_SYS_CPU_256_21_2EMAS_POS = 17,
    CPU1_SYS_CPU_256_32_20EMA_MASK = (int)0x1c0000,
    CPU1_SYS_CPU_256_32_20EMA_POS = 18,
    CPU1_SYS_CPU_256_32_2EMAW_MASK = (int)0x600000,
    CPU1_SYS_CPU_256_32_2EMAW_POS = 21,
    CPU1_SYS_CPU_256_32_2EMAS_MASK = (int)0x800000,
    CPU1_SYS_CPU_256_32_2EMAS_POS = 23,
    CPU1_SYS_CPU_256_88_20EMA_MASK = (int)0x7000000,
    CPU1_SYS_CPU_256_88_20EMA_POS = 24,
    CPU1_SYS_CPU_256_88_2EMAW_MASK = (int)0x18000000,
    CPU1_SYS_CPU_256_88_2EMAW_POS = 27,
    CPU1_SYS_CPU_256_88_2EMAS_MASK = (int)0x20000000,
    CPU1_SYS_CPU_256_88_2EMAS_POS = 29,
};

enum CPU1_SYS_REG_CORE2_EMA2_FIELD
{
    CPU1_SYS_CPU_512_39_20EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_512_39_20EMA_POS = 0,
    CPU1_SYS_CPU_512_39_2EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_512_39_2EMAW_POS = 3,
    CPU1_SYS_CPU_512_39_2EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_512_39_2EMAS_POS = 5,
    CPU1_SYS_CPU_512_70_20EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_512_70_20EMA_POS = 6,
    CPU1_SYS_CPU_512_70_2EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_512_70_2EMAW_POS = 9,
    CPU1_SYS_CPU_512_70_2EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_512_70_2EMAS_POS = 11,
};

enum CPU1_SYS_REG_CORE3_EMA0_FIELD
{
    CPU1_SYS_CPU_64_52_30EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_64_52_30EMA_POS = 0,
    CPU1_SYS_CPU_64_52_3EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_64_52_3EMAW_POS = 3,
    CPU1_SYS_CPU_64_52_3EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_64_52_3EMAS_POS = 5,
    CPU1_SYS_CPU_64_152_30EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_64_152_30EMA_POS = 6,
    CPU1_SYS_CPU_64_152_3EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_64_152_3EMAW_POS = 9,
    CPU1_SYS_CPU_64_152_3EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_64_152_3EMAS_POS = 11,
    CPU1_SYS_CPU_128_26_30EMA_MASK = (int)0x7000,
    CPU1_SYS_CPU_128_26_30EMA_POS = 12,
    CPU1_SYS_CPU_128_26_3EMAW_MASK = (int)0x18000,
    CPU1_SYS_CPU_128_26_3EMAW_POS = 15,
    CPU1_SYS_CPU_128_26_3EMAS_MASK = (int)0x20000,
    CPU1_SYS_CPU_128_26_3EMAS_POS = 17,
    CPU1_SYS_CPU_128_48_30EMA_MASK = (int)0x1c0000,
    CPU1_SYS_CPU_128_48_30EMA_POS = 18,
    CPU1_SYS_CPU_128_48_3EMAW_MASK = (int)0x600000,
    CPU1_SYS_CPU_128_48_3EMAW_POS = 21,
    CPU1_SYS_CPU_128_48_3EMAS_MASK = (int)0x800000,
    CPU1_SYS_CPU_128_48_3EMAS_POS = 23,
    CPU1_SYS_CPU_128_152_30EMA_MASK = (int)0x7000000,
    CPU1_SYS_CPU_128_152_30EMA_POS = 24,
    CPU1_SYS_CPU_128_152_3EMAW_MASK = (int)0x18000000,
    CPU1_SYS_CPU_128_152_3EMAW_POS = 27,
    CPU1_SYS_CPU_128_152_3EMAS_MASK = (int)0x20000000,
    CPU1_SYS_CPU_128_152_3EMAS_POS = 29,
};

enum CPU1_SYS_REG_CORE3_EMA1_FIELD
{
    CPU1_SYS_CPU_128_60_30EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_128_60_30EMA_POS = 0,
    CPU1_SYS_CPU_128_60_3EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_128_60_3EMAW_POS = 3,
    CPU1_SYS_CPU_128_60_3EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_128_60_3EMAS_POS = 5,
    CPU1_SYS_CPU_256_110_30EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_256_110_30EMA_POS = 6,
    CPU1_SYS_CPU_256_110_3EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_256_110_3EMAW_POS = 9,
    CPU1_SYS_CPU_256_110_3EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_256_110_3EMAS_POS = 11,
    CPU1_SYS_CPU_256_21_30EMA_MASK = (int)0x7000,
    CPU1_SYS_CPU_256_21_30EMA_POS = 12,
    CPU1_SYS_CPU_256_21_3EMAW_MASK = (int)0x18000,
    CPU1_SYS_CPU_256_21_3EMAW_POS = 15,
    CPU1_SYS_CPU_256_21_3EMAS_MASK = (int)0x20000,
    CPU1_SYS_CPU_256_21_3EMAS_POS = 17,
    CPU1_SYS_CPU_256_32_30EMA_MASK = (int)0x1c0000,
    CPU1_SYS_CPU_256_32_30EMA_POS = 18,
    CPU1_SYS_CPU_256_32_3EMAW_MASK = (int)0x600000,
    CPU1_SYS_CPU_256_32_3EMAW_POS = 21,
    CPU1_SYS_CPU_256_32_3EMAS_MASK = (int)0x800000,
    CPU1_SYS_CPU_256_32_3EMAS_POS = 23,
    CPU1_SYS_CPU_256_88_30EMA_MASK = (int)0x7000000,
    CPU1_SYS_CPU_256_88_30EMA_POS = 24,
    CPU1_SYS_CPU_256_88_3EMAW_MASK = (int)0x18000000,
    CPU1_SYS_CPU_256_88_3EMAW_POS = 27,
    CPU1_SYS_CPU_256_88_3EMAS_MASK = (int)0x20000000,
    CPU1_SYS_CPU_256_88_3EMAS_POS = 29,
};

enum CPU1_SYS_REG_CORE3_EMA2_FIELD
{
    CPU1_SYS_CPU_512_39_30EMA_MASK = (int)0x7,
    CPU1_SYS_CPU_512_39_30EMA_POS = 0,
    CPU1_SYS_CPU_512_39_3EMAW_MASK = (int)0x18,
    CPU1_SYS_CPU_512_39_3EMAW_POS = 3,
    CPU1_SYS_CPU_512_39_3EMAS_MASK = (int)0x20,
    CPU1_SYS_CPU_512_39_3EMAS_POS = 5,
    CPU1_SYS_CPU_512_70_30EMA_MASK = (int)0x1c0,
    CPU1_SYS_CPU_512_70_30EMA_POS = 6,
    CPU1_SYS_CPU_512_70_3EMAW_MASK = (int)0x600,
    CPU1_SYS_CPU_512_70_3EMAW_POS = 9,
    CPU1_SYS_CPU_512_70_3EMAS_MASK = (int)0x800,
    CPU1_SYS_CPU_512_70_3EMAS_POS = 11,
};

enum CPU1_SYS_REG_PCIE2_DUMMY0_FIELD
{
    CPU1_SYS_PCIE2_DUMMY0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DUMMY0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_RD_DUMMY0_FIELD
{
    CPU1_SYS_PCIE2_RD_DUMMY0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_RD_DUMMY0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG0_FIELD
{
    CPU1_SYS_PCIE2_SURPRISE_DOWN_ERR_MASK = (int)0xff,
    CPU1_SYS_PCIE2_SURPRISE_DOWN_ERR_POS = 0,
    CPU1_SYS_PCIE2_POWER_UP_RST_N_MASK = (int)0x100,
    CPU1_SYS_PCIE2_POWER_UP_RST_N_POS = 8,
    CPU1_SYS_PCIE2_BUTTON_RST_N_MASK = (int)0x200,
    CPU1_SYS_PCIE2_BUTTON_RST_N_POS = 9,
    CPU1_SYS_PCIE2_SYS_AUX_PWR_DET_MASK = (int)0x400,
    CPU1_SYS_PCIE2_SYS_AUX_PWR_DET_POS = 10,
    CPU1_SYS_PCIE2_APP_LTSSM_ENABLE_MASK = (int)0x800,
    CPU1_SYS_PCIE2_APP_LTSSM_ENABLE_POS = 11,
    CPU1_SYS_PCIE2_APP_HOLD_PHY_RST_MASK = (int)0x1000,
    CPU1_SYS_PCIE2_APP_HOLD_PHY_RST_POS = 12,
    CPU1_SYS_PCIE2_APP_CLK_REQ_N_MASK = (int)0x2000,
    CPU1_SYS_PCIE2_APP_CLK_REQ_N_POS = 13,
    CPU1_SYS_PCIE2_APP_CLK_PM_EN_MASK = (int)0x4000,
    CPU1_SYS_PCIE2_APP_CLK_PM_EN_POS = 14,
    CPU1_SYS_PCIE2_APP_INIT_RST_MASK = (int)0x8000,
    CPU1_SYS_PCIE2_APP_INIT_RST_POS = 15,
    CPU1_SYS_PCIE2_APP_REQ_ENTR_L1_MASK = (int)0x10000,
    CPU1_SYS_PCIE2_APP_REQ_ENTR_L1_POS = 16,
    CPU1_SYS_PCIE2_APP_READY_ENTR_L23_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_APP_READY_ENTR_L23_POS = 17,
    CPU1_SYS_PCIE2_APP_REQ_EXIT_L1_MASK = (int)0x40000,
    CPU1_SYS_PCIE2_APP_REQ_EXIT_L1_POS = 18,
    CPU1_SYS_PCIE2_APP_XFER_PENDING_MASK = (int)0x80000,
    CPU1_SYS_PCIE2_APP_XFER_PENDING_POS = 19,
    CPU1_SYS_PCIE2_EXP_ROM_VALIDATION_STATUS_STROBE_MASK = (int)0xff00000,
    CPU1_SYS_PCIE2_EXP_ROM_VALIDATION_STATUS_STROBE_POS = 20,
};

enum CPU1_SYS_REG_PCIE2_REG1_FIELD
{
    CPU1_SYS_PCIE2_EXP_ROM_VALIDATION_STATUS_MASK = (int)0xffffff,
    CPU1_SYS_PCIE2_EXP_ROM_VALIDATION_STATUS_POS = 0,
    CPU1_SYS_PCIE2_EXP_ROM_VALIDATION_DETAILS_STROBE_MASK = (int)0xff000000,
    CPU1_SYS_PCIE2_EXP_ROM_VALIDATION_DETAILS_STROBE_POS = 24,
};

enum CPU1_SYS_REG_PCIE2_REG2_FIELD
{
    CPU1_SYS_PCIE2_EXP_ROM_VALIDATION_DETAILS_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_EXP_ROM_VALIDATION_DETAILS_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG3_FIELD
{
    CPU1_SYS_PCIE2_APP_REQ_RETRY_EN_MASK = (int)0x1,
    CPU1_SYS_PCIE2_APP_REQ_RETRY_EN_POS = 0,
    CPU1_SYS_PCIE2_APP_PF_REQ_RETRY_EN_MASK = (int)0x1fe,
    CPU1_SYS_PCIE2_APP_PF_REQ_RETRY_EN_POS = 1,
    CPU1_SYS_PCIE2_CFG_HP_SLOT_CTRL_ACCESS_MASK = (int)0x1fe00,
    CPU1_SYS_PCIE2_CFG_HP_SLOT_CTRL_ACCESS_POS = 9,
    CPU1_SYS_PCIE2_CFG_DLL_STATE_CHGED_EN_MASK = (int)0x1fe0000,
    CPU1_SYS_PCIE2_CFG_DLL_STATE_CHGED_EN_POS = 17,
};

enum CPU1_SYS_REG_PCIE2_REG4_FIELD
{
    CPU1_SYS_PCIE2_CFG_CMD_CPLED_INT_EN_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_CMD_CPLED_INT_EN_POS = 0,
    CPU1_SYS_PCIE2_CFG_HP_INT_EN_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_CFG_HP_INT_EN_POS = 8,
    CPU1_SYS_PCIE2_CFG_PRE_DET_CHGED_EN_MASK = (int)0xff0000,
    CPU1_SYS_PCIE2_CFG_PRE_DET_CHGED_EN_POS = 16,
    CPU1_SYS_PCIE2_CFG_MRL_SENSOR_CHGED_EN_MASK = (int)0xff000000,
    CPU1_SYS_PCIE2_CFG_MRL_SENSOR_CHGED_EN_POS = 24,
};

enum CPU1_SYS_REG_PCIE2_REG5_FIELD
{
    CPU1_SYS_PCIE2_CFG_PWR_FAULT_DET_EN_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_PWR_FAULT_DET_EN_POS = 0,
    CPU1_SYS_PCIE2_CFG_ATTEN_BUTTON_PRESSED_EN_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_CFG_ATTEN_BUTTON_PRESSED_EN_POS = 8,
    CPU1_SYS_PCIE2_LOCAL_REF_CLK_REQ_N_MASK = (int)0x10000,
    CPU1_SYS_PCIE2_LOCAL_REF_CLK_REQ_N_POS = 16,
    CPU1_SYS_PCIE2_CLKREQ_IN_N_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_CLKREQ_IN_N_POS = 17,
    CPU1_SYS_PCIE2_CFG_HW_AUTO_SP_DIS_MASK = (int)0x40000,
    CPU1_SYS_PCIE2_CFG_HW_AUTO_SP_DIS_POS = 18,
    CPU1_SYS_PCIE2_RADM_TRGT1_VC_MASK = (int)0x380000,
    CPU1_SYS_PCIE2_RADM_TRGT1_VC_POS = 19,
    CPU1_SYS_PCIE2_APP_DBI_RO_WR_DISABLE_MASK = (int)0x400000,
    CPU1_SYS_PCIE2_APP_DBI_RO_WR_DISABLE_POS = 22,
    CPU1_SYS_PCIE2_VEN_MSI_FUNC_NUM_MASK = (int)0x3800000,
    CPU1_SYS_PCIE2_VEN_MSI_FUNC_NUM_POS = 23,
    CPU1_SYS_PCIE2_VEN_MSI_TC_MASK = (int)0x1c000000,
    CPU1_SYS_PCIE2_VEN_MSI_TC_POS = 26,
};

enum CPU1_SYS_REG_PCIE2_REG6_FIELD
{
    CPU1_SYS_PCIE2_VEN_MSI_VECTOR_MASK = (int)0x1f,
    CPU1_SYS_PCIE2_VEN_MSI_VECTOR_POS = 0,
    CPU1_SYS_PCIE2_CFG_MSI_EN_MASK = (int)0x1fe0,
    CPU1_SYS_PCIE2_CFG_MSI_EN_POS = 5,
};

enum CPU1_SYS_REG_PCIE2_REG7_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_MASK_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_MASK_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG8_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_MASK_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_MASK_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG9_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_MASK_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_MASK_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG10_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_MASK_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_MASK_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG11_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_MASK_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_MASK_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG12_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_MASK_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_MASK_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG13_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_MASK_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_MASK_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG14_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_MASK_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_MASK_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG15_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG16_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG17_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG18_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG19_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG20_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG21_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG22_FIELD
{
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_MSI_PENDING_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG23_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_M_EN_MASK = (int)0x1,
    CPU1_SYS_PCIE2_CFG_LTR_M_EN_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG24_FIELD
{
    CPU1_SYS_PCIE2_APP_LTR_MSG_LATENCY_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_APP_LTR_MSG_LATENCY_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG25_FIELD
{
    CPU1_SYS_PCIE2_APP_LTR_MSG_FUNC_NUM_MASK = (int)0x7,
    CPU1_SYS_PCIE2_APP_LTR_MSG_FUNC_NUM_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG26_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG27_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG28_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG29_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG30_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG31_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG32_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG33_FIELD
{
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_LTR_MAX_LATENCY_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG34_FIELD
{
    CPU1_SYS_PCIE2_CFG_DISABLE_LTR_CLR_MSG_MASK = (int)0x1,
    CPU1_SYS_PCIE2_CFG_DISABLE_LTR_CLR_MSG_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG35_FIELD
{
    CPU1_SYS_PCIE2_APP_LTR_LATENCY_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_APP_LTR_LATENCY_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG36_FIELD
{
    CPU1_SYS_PCIE2_RADM_MSG_LTR_MASK = (int)0x1,
    CPU1_SYS_PCIE2_RADM_MSG_LTR_POS = 0,
    CPU1_SYS_PCIE2_VEN_MSG_FMT_MASK = (int)0x6,
    CPU1_SYS_PCIE2_VEN_MSG_FMT_POS = 1,
    CPU1_SYS_PCIE2_VEN_MSG_TYPE_MASK = (int)0xf8,
    CPU1_SYS_PCIE2_VEN_MSG_TYPE_POS = 3,
    CPU1_SYS_PCIE2_VEN_MSG_TC_MASK = (int)0x700,
    CPU1_SYS_PCIE2_VEN_MSG_TC_POS = 8,
    CPU1_SYS_PCIE2_VEN_MSG_TD_MASK = (int)0x800,
    CPU1_SYS_PCIE2_VEN_MSG_TD_POS = 11,
    CPU1_SYS_PCIE2_VEN_MSG_EP_MASK = (int)0x1000,
    CPU1_SYS_PCIE2_VEN_MSG_EP_POS = 12,
    CPU1_SYS_PCIE2_VEN_MSG_ATTR_MASK = (int)0x6000,
    CPU1_SYS_PCIE2_VEN_MSG_ATTR_POS = 13,
    CPU1_SYS_PCIE2_VEN_MSG_LEN_MASK = (int)0x1ff8000,
    CPU1_SYS_PCIE2_VEN_MSG_LEN_POS = 15,
    CPU1_SYS_PCIE2_VEN_MSG_FUNC_NUM_MASK = (int)0xe000000,
    CPU1_SYS_PCIE2_VEN_MSG_FUNC_NUM_POS = 25,
};

enum CPU1_SYS_REG_PCIE2_REG37_FIELD
{
    CPU1_SYS_PCIE2_VEN_MSG_TAG_MASK = (int)0xff,
    CPU1_SYS_PCIE2_VEN_MSG_TAG_POS = 0,
    CPU1_SYS_PCIE2_VEN_MSG_CODE_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_VEN_MSG_CODE_POS = 8,
};

enum CPU1_SYS_REG_PCIE2_REG38_FIELD
{
    CPU1_SYS_PCIE2_VEN_MSG_DATA_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_VEN_MSG_DATA_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG39_FIELD
{
    CPU1_SYS_PCIE2_VEN_MSG_DATA_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_VEN_MSG_DATA_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG40_FIELD
{
    CPU1_SYS_PCIE2_SYS_INT_MASK = (int)0xff,
    CPU1_SYS_PCIE2_SYS_INT_POS = 0,
    CPU1_SYS_PCIE2_APPS_PM_XMT_PME_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_APPS_PM_XMT_PME_POS = 8,
    CPU1_SYS_PCIE2_SYS_ATTEN_BUTTON_PRESSED_MASK = (int)0xff0000,
    CPU1_SYS_PCIE2_SYS_ATTEN_BUTTON_PRESSED_POS = 16,
    CPU1_SYS_PCIE2_SYS_PRE_DET_STATE_MASK = (int)0xff000000,
    CPU1_SYS_PCIE2_SYS_PRE_DET_STATE_POS = 24,
};

enum CPU1_SYS_REG_PCIE2_REG41_FIELD
{
    CPU1_SYS_PCIE2_SYS_MRL_SENSOR_STATE_MASK = (int)0xff,
    CPU1_SYS_PCIE2_SYS_MRL_SENSOR_STATE_POS = 0,
    CPU1_SYS_PCIE2_SYS_PWR_FAULT_DET_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_SYS_PWR_FAULT_DET_POS = 8,
    CPU1_SYS_PCIE2_SYS_MRL_SENSOR_CHGED_MASK = (int)0xff0000,
    CPU1_SYS_PCIE2_SYS_MRL_SENSOR_CHGED_POS = 16,
    CPU1_SYS_PCIE2_SYS_PRE_DET_CHGED_MASK = (int)0xff000000,
    CPU1_SYS_PCIE2_SYS_PRE_DET_CHGED_POS = 24,
};

enum CPU1_SYS_REG_PCIE2_REG42_FIELD
{
    CPU1_SYS_PCIE2_SYS_CMD_CPLED_INT_MASK = (int)0xff,
    CPU1_SYS_PCIE2_SYS_CMD_CPLED_INT_POS = 0,
    CPU1_SYS_PCIE2_SYS_EML_INTERLOCK_ENGAGED_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_SYS_EML_INTERLOCK_ENGAGED_POS = 8,
    CPU1_SYS_PCIE2_APP_UNLOCK_MSG_MASK = (int)0x10000,
    CPU1_SYS_PCIE2_APP_UNLOCK_MSG_POS = 16,
    CPU1_SYS_PCIE2_APPS_PM_XMT_TURNOFF_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_APPS_PM_XMT_TURNOFF_POS = 17,
};

enum CPU1_SYS_REG_PCIE2_REG43_FIELD
{
    CPU1_SYS_PCIE2_CFG_PWR_IND_MASK = (int)0xffff,
    CPU1_SYS_PCIE2_CFG_PWR_IND_POS = 0,
    CPU1_SYS_PCIE2_CFG_ATTEN_IND_MASK = (int)0xffff0000,
    CPU1_SYS_PCIE2_CFG_ATTEN_IND_POS = 16,
};

enum CPU1_SYS_REG_PCIE2_REG44_FIELD
{
    CPU1_SYS_PCIE2_CFG_PWR_CTRLER_CTRL_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_PWR_CTRLER_CTRL_POS = 0,
    CPU1_SYS_PCIE2_CFG_SYS_ERR_RC_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_CFG_SYS_ERR_RC_POS = 8,
    CPU1_SYS_PCIE2_CFG_AER_RC_ERR_INT_MASK = (int)0xff0000,
    CPU1_SYS_PCIE2_CFG_AER_RC_ERR_INT_POS = 16,
    CPU1_SYS_PCIE2_CFG_AER_RC_ERR_MSI_MASK = (int)0xff000000,
    CPU1_SYS_PCIE2_CFG_AER_RC_ERR_MSI_POS = 24,
};

enum CPU1_SYS_REG_PCIE2_REG45_FIELD
{
    CPU1_SYS_PCIE2_CFG_AER_INT_MSG_NUM_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_AER_INT_MSG_NUM_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG46_FIELD
{
    CPU1_SYS_PCIE2_CFG_AER_INT_MSG_NUM_1_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_AER_INT_MSG_NUM_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG47_FIELD
{
    CPU1_SYS_PCIE2_CFG_PME_INT_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_PME_INT_POS = 0,
    CPU1_SYS_PCIE2_CFG_PME_MSI_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_CFG_PME_MSI_POS = 8,
    CPU1_SYS_PCIE2_CFG_CRS_SW_VIS_EN_MASK = (int)0xff0000,
    CPU1_SYS_PCIE2_CFG_CRS_SW_VIS_EN_POS = 16,
};

enum CPU1_SYS_REG_PCIE2_REG48_FIELD
{
    CPU1_SYS_PCIE2_CFG_PCIE_CAP_INT_MSG_NUM_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_PCIE_CAP_INT_MSG_NUM_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG49_FIELD
{
    CPU1_SYS_PCIE2_CFG_PCIE_CAP_INT_MSG_NUM_1_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_PCIE_CAP_INT_MSG_NUM_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG50_FIELD
{
    CPU1_SYS_PCIE2_CFG_EML_CONTROL_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_EML_CONTROL_POS = 0,
    CPU1_SYS_PCIE2_RTLH_RFC_UPD_MASK = (int)0x100,
    CPU1_SYS_PCIE2_RTLH_RFC_UPD_POS = 8,
};

enum CPU1_SYS_REG_PCIE2_REG51_FIELD
{
    CPU1_SYS_PCIE2_RTLH_RFC_DATA_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_RTLH_RFC_DATA_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG52_FIELD
{
    CPU1_SYS_PCIE2_RADM_INTA_ASSERTED_MASK = (int)0x1,
    CPU1_SYS_PCIE2_RADM_INTA_ASSERTED_POS = 0,
    CPU1_SYS_PCIE2_RADM_INTB_ASSERTED_MASK = (int)0x2,
    CPU1_SYS_PCIE2_RADM_INTB_ASSERTED_POS = 1,
    CPU1_SYS_PCIE2_RADM_INTC_ASSERTED_MASK = (int)0x4,
    CPU1_SYS_PCIE2_RADM_INTC_ASSERTED_POS = 2,
    CPU1_SYS_PCIE2_RADM_INTD_ASSERTED_MASK = (int)0x8,
    CPU1_SYS_PCIE2_RADM_INTD_ASSERTED_POS = 3,
    CPU1_SYS_PCIE2_RADM_INTA_DEASSERTED_MASK = (int)0x10,
    CPU1_SYS_PCIE2_RADM_INTA_DEASSERTED_POS = 4,
    CPU1_SYS_PCIE2_RADM_INTB_DEASSERTED_MASK = (int)0x20,
    CPU1_SYS_PCIE2_RADM_INTB_DEASSERTED_POS = 5,
    CPU1_SYS_PCIE2_RADM_INTC_DEASSERTED_MASK = (int)0x40,
    CPU1_SYS_PCIE2_RADM_INTC_DEASSERTED_POS = 6,
    CPU1_SYS_PCIE2_RADM_INTD_DEASSERTED_MASK = (int)0x80,
    CPU1_SYS_PCIE2_RADM_INTD_DEASSERTED_POS = 7,
    CPU1_SYS_PCIE2_RADM_CORRECTABLE_ERR_MASK = (int)0x100,
    CPU1_SYS_PCIE2_RADM_CORRECTABLE_ERR_POS = 8,
    CPU1_SYS_PCIE2_RADM_NONFATAL_ERR_MASK = (int)0x200,
    CPU1_SYS_PCIE2_RADM_NONFATAL_ERR_POS = 9,
    CPU1_SYS_PCIE2_RADM_FATAL_ERR_MASK = (int)0x400,
    CPU1_SYS_PCIE2_RADM_FATAL_ERR_POS = 10,
    CPU1_SYS_PCIE2_RADM_PM_PME_MASK = (int)0x800,
    CPU1_SYS_PCIE2_RADM_PM_PME_POS = 11,
    CPU1_SYS_PCIE2_RADM_PM_TO_ACK_MASK = (int)0x1000,
    CPU1_SYS_PCIE2_RADM_PM_TO_ACK_POS = 12,
    CPU1_SYS_PCIE2_HP_PME_MASK = (int)0x1fe000,
    CPU1_SYS_PCIE2_HP_PME_POS = 13,
    CPU1_SYS_PCIE2_HP_INT_MASK = (int)0x1fe00000,
    CPU1_SYS_PCIE2_HP_INT_POS = 21,
};

enum CPU1_SYS_REG_PCIE2_REG53_FIELD
{
    CPU1_SYS_PCIE2_HP_MSI_MASK = (int)0xff,
    CPU1_SYS_PCIE2_HP_MSI_POS = 0,
    CPU1_SYS_PCIE2_RADM_Q_NOT_EMPTY_MASK = (int)0x100,
    CPU1_SYS_PCIE2_RADM_Q_NOT_EMPTY_POS = 8,
    CPU1_SYS_PCIE2_RADM_QOVERFLOW_MASK = (int)0x200,
    CPU1_SYS_PCIE2_RADM_QOVERFLOW_POS = 9,
    CPU1_SYS_PCIE2_PM_XTLH_BLOCK_TLP_MASK = (int)0x400,
    CPU1_SYS_PCIE2_PM_XTLH_BLOCK_TLP_POS = 10,
};

enum CPU1_SYS_REG_PCIE2_REG54_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG55_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG56_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG57_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG58_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG59_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG60_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG61_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG62_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG63_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_9_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_9_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG64_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_10_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_10_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG65_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_11_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_11_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG66_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_12_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_12_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG67_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_13_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_13_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG68_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_14_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_14_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG69_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_START_15_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_START_15_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG70_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG71_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG72_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG73_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG74_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG75_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG76_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG77_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG78_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG79_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_9_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_9_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG80_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_10_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_10_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG81_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_11_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_11_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG82_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_12_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_12_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG83_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_13_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_13_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG84_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_14_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_14_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG85_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_15_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR0_LIMIT_15_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG86_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_START_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_START_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG87_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_START_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_START_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG88_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_START_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_START_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG89_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_START_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_START_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG90_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_START_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_START_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG91_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_START_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_START_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG92_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_START_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_START_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG93_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_START_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_START_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG94_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG95_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG96_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG97_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG98_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG99_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG100_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG101_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR1_LIMIT_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG102_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG103_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG104_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG105_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG106_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG107_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG108_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG109_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG110_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG111_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_9_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_9_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG112_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_10_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_10_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG113_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_11_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_11_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG114_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_12_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_12_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG115_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_13_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_13_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG116_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_14_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_14_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG117_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_START_15_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_START_15_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG118_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG119_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG120_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG121_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG122_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG123_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG124_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG125_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG126_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG127_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_9_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_9_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG128_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_10_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_10_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG129_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_11_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_11_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG130_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_12_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_12_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG131_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_13_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_13_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG132_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_14_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_14_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG133_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_15_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR2_LIMIT_15_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG134_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_START_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_START_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG135_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_START_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_START_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG136_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_START_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_START_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG137_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_START_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_START_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG138_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_START_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_START_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG139_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_START_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_START_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG140_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_START_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_START_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG141_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_START_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_START_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG142_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG143_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG144_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG145_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG146_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG147_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG148_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG149_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR3_LIMIT_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG150_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG151_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG152_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG153_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG154_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG155_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG156_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG157_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG158_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG159_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_9_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_9_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG160_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_10_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_10_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG161_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_11_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_11_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG162_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_12_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_12_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG163_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_13_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_13_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG164_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_14_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_14_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG165_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_START_15_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_START_15_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG166_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG167_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG168_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG169_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG170_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG171_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG172_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG173_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG174_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG175_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_9_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_9_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG176_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_10_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_10_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG177_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_11_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_11_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG178_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_12_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_12_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG179_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_13_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_13_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG180_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_14_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_14_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG181_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_15_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR4_LIMIT_15_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG182_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_START_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_START_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG183_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_START_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_START_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG184_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_START_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_START_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG185_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_START_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_START_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG186_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_START_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_START_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG187_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_START_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_START_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG188_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_START_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_START_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG189_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_START_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_START_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG190_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG191_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG192_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG193_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG194_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG195_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG196_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG197_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_BAR5_LIMIT_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG198_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG199_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG200_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG201_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG202_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG203_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG204_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG205_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_START_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG206_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG207_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG208_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG209_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG210_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG211_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG212_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG213_FIELD
{
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_EXP_ROM_LIMIT_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG214_FIELD
{
    CPU1_SYS_PCIE2_CFG_BUS_MASTER_EN_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_BUS_MASTER_EN_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG215_FIELD
{
    CPU1_SYS_PCIE2_CFG_2NDBUS_NUM_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_2NDBUS_NUM_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG216_FIELD
{
    CPU1_SYS_PCIE2_CFG_2NDBUS_NUM_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_2NDBUS_NUM_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG217_FIELD
{
    CPU1_SYS_PCIE2_CFG_SUBBUS_NUM_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_SUBBUS_NUM_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG218_FIELD
{
    CPU1_SYS_PCIE2_CFG_SUBBUS_NUM_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_SUBBUS_NUM_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG219_FIELD
{
    CPU1_SYS_PCIE2_CFG_2ND_RESET_MASK = (int)0x1,
    CPU1_SYS_PCIE2_CFG_2ND_RESET_POS = 0,
    CPU1_SYS_PCIE2_CFG_MAX_PAYLOAD_SIZE_MASK = (int)0x1fffffe,
    CPU1_SYS_PCIE2_CFG_MAX_PAYLOAD_SIZE_POS = 1,
};

enum CPU1_SYS_REG_PCIE2_REG220_FIELD
{
    CPU1_SYS_PCIE2_CFG_RCB_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_RCB_POS = 0,
    CPU1_SYS_PCIE2_CFG_MEM_SPACE_EN_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_CFG_MEM_SPACE_EN_POS = 8,
};

enum CPU1_SYS_REG_PCIE2_REG221_FIELD
{
    CPU1_SYS_PCIE2_CFG_MAX_RD_REQ_SIZE_MASK = (int)0xffffff,
    CPU1_SYS_PCIE2_CFG_MAX_RD_REQ_SIZE_POS = 0,
    CPU1_SYS_PCIE2_RDLH_LINK_UP_MASK = (int)0x1000000,
    CPU1_SYS_PCIE2_RDLH_LINK_UP_POS = 24,
    CPU1_SYS_PCIE2_SMLH_LTSSM_STATE_MASK = (int)0x7e000000,
    CPU1_SYS_PCIE2_SMLH_LTSSM_STATE_POS = 25,
};

enum CPU1_SYS_REG_PCIE2_REG222_FIELD
{
    CPU1_SYS_PCIE2_PM_CURNT_STATE_MASK = (int)0x7,
    CPU1_SYS_PCIE2_PM_CURNT_STATE_POS = 0,
    CPU1_SYS_PCIE2_SMLH_LINK_UP_MASK = (int)0x8,
    CPU1_SYS_PCIE2_SMLH_LINK_UP_POS = 3,
    CPU1_SYS_PCIE2_SMLH_REQ_RST_NOT_MASK = (int)0x10,
    CPU1_SYS_PCIE2_SMLH_REQ_RST_NOT_POS = 4,
    CPU1_SYS_PCIE2_LINK_REQ_RST_NOT_MASK = (int)0x20,
    CPU1_SYS_PCIE2_LINK_REQ_RST_NOT_POS = 5,
    CPU1_SYS_PCIE2_BRDG_SLV_XFER_PENDING_MASK = (int)0x40,
    CPU1_SYS_PCIE2_BRDG_SLV_XFER_PENDING_POS = 6,
    CPU1_SYS_PCIE2_BRDG_DBI_XFER_PENDING_MASK = (int)0x80,
    CPU1_SYS_PCIE2_BRDG_DBI_XFER_PENDING_POS = 7,
    CPU1_SYS_PCIE2_EDMA_XFER_PENDING_MASK = (int)0x100,
    CPU1_SYS_PCIE2_EDMA_XFER_PENDING_POS = 8,
    CPU1_SYS_PCIE2_RADM_XFER_PENDING_MASK = (int)0x200,
    CPU1_SYS_PCIE2_RADM_XFER_PENDING_POS = 9,
    CPU1_SYS_PCIE2_CFG_REG_SERREN_MASK = (int)0x3fc00,
    CPU1_SYS_PCIE2_CFG_REG_SERREN_POS = 10,
    CPU1_SYS_PCIE2_CFG_COR_ERR_RPT_EN_MASK = (int)0x3fc0000,
    CPU1_SYS_PCIE2_CFG_COR_ERR_RPT_EN_POS = 18,
};

enum CPU1_SYS_REG_PCIE2_REG223_FIELD
{
    CPU1_SYS_PCIE2_CFG_NF_ERR_RPT_EN_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_NF_ERR_RPT_EN_POS = 0,
    CPU1_SYS_PCIE2_CFG_F_ERR_RPT_EN_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_CFG_F_ERR_RPT_EN_POS = 8,
    CPU1_SYS_PCIE2_DIAG_CTRL_BUS_MASK = (int)0x70000,
    CPU1_SYS_PCIE2_DIAG_CTRL_BUS_POS = 16,
};

enum CPU1_SYS_REG_PCIE2_REG224_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG225_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG226_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG227_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG228_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG229_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG230_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG231_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG232_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG233_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_9_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_9_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG234_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_10_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_10_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG235_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_11_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_11_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG236_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_12_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_12_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG237_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_13_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_13_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG238_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_14_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_14_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG239_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_15_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_15_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG240_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_16_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_16_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG241_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_17_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_17_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG242_FIELD
{
    CPU1_SYS_PCIE2_APP_RAS_DES_SD_HOLD_LTSSM_MASK = (int)0x1,
    CPU1_SYS_PCIE2_APP_RAS_DES_SD_HOLD_LTSSM_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG243_FIELD
{
    CPU1_SYS_PCIE2_CXPL_DEBUG_INFO_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CXPL_DEBUG_INFO_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG244_FIELD
{
    CPU1_SYS_PCIE2_CXPL_DEBUG_INFO_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CXPL_DEBUG_INFO_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG245_FIELD
{
    CPU1_SYS_PCIE2_CXPL_DEBUG_INFO_EI_MASK = (int)0xffff,
    CPU1_SYS_PCIE2_CXPL_DEBUG_INFO_EI_POS = 0,
    CPU1_SYS_PCIE2_TRAINING_RST_N_MASK = (int)0x10000,
    CPU1_SYS_PCIE2_TRAINING_RST_N_POS = 16,
    CPU1_SYS_PCIE2_RADM_PM_TURNOFF_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_RADM_PM_TURNOFF_POS = 17,
    CPU1_SYS_PCIE2_RADM_MSG_UNLOCK_MASK = (int)0x40000,
    CPU1_SYS_PCIE2_RADM_MSG_UNLOCK_POS = 18,
    CPU1_SYS_PCIE2_OUTBAND_PWRUP_CMD_MASK = (int)0x7f80000,
    CPU1_SYS_PCIE2_OUTBAND_PWRUP_CMD_POS = 19,
};

enum CPU1_SYS_REG_PCIE2_REG246_FIELD
{
    CPU1_SYS_PCIE2_PM_DSTATE_MASK = (int)0xffffff,
    CPU1_SYS_PCIE2_PM_DSTATE_POS = 0,
    CPU1_SYS_PCIE2_AUX_PM_EN_MASK = (int)0xff000000,
    CPU1_SYS_PCIE2_AUX_PM_EN_POS = 24,
};

enum CPU1_SYS_REG_PCIE2_REG247_FIELD
{
    CPU1_SYS_PCIE2_PM_PME_EN_MASK = (int)0xff,
    CPU1_SYS_PCIE2_PM_PME_EN_POS = 0,
    CPU1_SYS_PCIE2_PM_LINKST_IN_L0S_MASK = (int)0x100,
    CPU1_SYS_PCIE2_PM_LINKST_IN_L0S_POS = 8,
    CPU1_SYS_PCIE2_PM_LINKST_IN_L1_MASK = (int)0x200,
    CPU1_SYS_PCIE2_PM_LINKST_IN_L1_POS = 9,
    CPU1_SYS_PCIE2_PM_L1_ENTRY_STARTED_MASK = (int)0x400,
    CPU1_SYS_PCIE2_PM_L1_ENTRY_STARTED_POS = 10,
    CPU1_SYS_PCIE2_PM_LINKST_IN_L2_MASK = (int)0x800,
    CPU1_SYS_PCIE2_PM_LINKST_IN_L2_POS = 11,
    CPU1_SYS_PCIE2_PM_LINKST_L2_EXIT_MASK = (int)0x1000,
    CPU1_SYS_PCIE2_PM_LINKST_L2_EXIT_POS = 12,
    CPU1_SYS_PCIE2_PM_LINKST_IN_L1SUB_MASK = (int)0x2000,
    CPU1_SYS_PCIE2_PM_LINKST_IN_L1SUB_POS = 13,
    CPU1_SYS_PCIE2_CFG_L1SUB_EN_MASK = (int)0x4000,
    CPU1_SYS_PCIE2_CFG_L1SUB_EN_POS = 14,
    CPU1_SYS_PCIE2_PM_STATUS_MASK = (int)0x7f8000,
    CPU1_SYS_PCIE2_PM_STATUS_POS = 15,
};

enum CPU1_SYS_REG_PCIE2_REG248_FIELD
{
    CPU1_SYS_PCIE2_CFG_OBFF_EN_MASK = (int)0x60,
    CPU1_SYS_PCIE2_CFG_OBFF_EN_POS = 5,
    CPU1_SYS_PCIE2_RADM_MSG_CPU_ACTIVE_MASK = (int)0x80,
    CPU1_SYS_PCIE2_RADM_MSG_CPU_ACTIVE_POS = 7,
    CPU1_SYS_PCIE2_RADM_MSG_OBFF_MASK = (int)0x100,
    CPU1_SYS_PCIE2_RADM_MSG_OBFF_POS = 8,
    CPU1_SYS_PCIE2_RADM_MSG_IDLE_MASK = (int)0x200,
    CPU1_SYS_PCIE2_RADM_MSG_IDLE_POS = 9,
    CPU1_SYS_PCIE2_RADM_VENDOR_MSG_MASK = (int)0x400,
    CPU1_SYS_PCIE2_RADM_VENDOR_MSG_POS = 10,
};

enum CPU1_SYS_REG_PCIE2_REG249_FIELD
{
    CPU1_SYS_PCIE2_RADM_MSG_PAYLOAD_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_RADM_MSG_PAYLOAD_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG250_FIELD
{
    CPU1_SYS_PCIE2_RADM_MSG_PAYLOAD_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_RADM_MSG_PAYLOAD_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG251_FIELD
{
    CPU1_SYS_PCIE2_WAKE_MASK = (int)0x1,
    CPU1_SYS_PCIE2_WAKE_POS = 0,
    CPU1_SYS_PCIE2_RADM_MSG_REQ_ID_MASK = (int)0x1fffe,
    CPU1_SYS_PCIE2_RADM_MSG_REQ_ID_POS = 1,
    CPU1_SYS_PCIE2_TRGT_CPL_TIMEOUT_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_TRGT_CPL_TIMEOUT_POS = 17,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_CPL_FUNC_NUM_MASK = (int)0x1c0000,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_CPL_FUNC_NUM_POS = 18,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_CPL_TC_MASK = (int)0xe00000,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_CPL_TC_POS = 21,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_CPL_ATTR_MASK = (int)0x3000000,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_CPL_ATTR_POS = 24,
};

enum CPU1_SYS_REG_PCIE2_REG252_FIELD
{
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_CPL_LEN_MASK = (int)0xfff,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_CPL_LEN_POS = 0,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_LOOKUP_ID_MASK = (int)0xff000,
    CPU1_SYS_PCIE2_TRGT_TIMEOUT_LOOKUP_ID_POS = 12,
    CPU1_SYS_PCIE2_TRGT_LOOKUP_ID_MASK = (int)0xff00000,
    CPU1_SYS_PCIE2_TRGT_LOOKUP_ID_POS = 20,
    CPU1_SYS_PCIE2_TRGT_LOOKUP_EMPTY_MASK = (int)0x10000000,
    CPU1_SYS_PCIE2_TRGT_LOOKUP_EMPTY_POS = 28,
    CPU1_SYS_PCIE2_RADM_CPL_TIMEOUT_MASK = (int)0x20000000,
    CPU1_SYS_PCIE2_RADM_CPL_TIMEOUT_POS = 29,
};

enum CPU1_SYS_REG_PCIE2_REG253_FIELD
{
    CPU1_SYS_PCIE2_RADM_TIMEOUT_FUNC_NUM_MASK = (int)0x7,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_FUNC_NUM_POS = 0,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_CPL_TC_MASK = (int)0x38,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_CPL_TC_POS = 3,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_CPL_ATTR_MASK = (int)0xc0,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_CPL_ATTR_POS = 6,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_CPL_LEN_MASK = (int)0xfff00,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_CPL_LEN_POS = 8,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_CPL_TAG_MASK = (int)0xff00000,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_CPL_TAG_POS = 20,
};

enum CPU1_SYS_REG_PCIE2_REG254_FIELD
{
    CPU1_SYS_PCIE2_EDMA_INT_MASK = (int)0xffff,
    CPU1_SYS_PCIE2_EDMA_INT_POS = 0,
    CPU1_SYS_PCIE2_ASSERT_INTA_GRT_MASK = (int)0x10000,
    CPU1_SYS_PCIE2_ASSERT_INTA_GRT_POS = 16,
    CPU1_SYS_PCIE2_ASSERT_INTB_GRT_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_ASSERT_INTB_GRT_POS = 17,
    CPU1_SYS_PCIE2_ASSERT_INTC_GRT_MASK = (int)0x40000,
    CPU1_SYS_PCIE2_ASSERT_INTC_GRT_POS = 18,
    CPU1_SYS_PCIE2_ASSERT_INTD_GRT_MASK = (int)0x80000,
    CPU1_SYS_PCIE2_ASSERT_INTD_GRT_POS = 19,
    CPU1_SYS_PCIE2_DEASSERT_INTA_GRT_MASK = (int)0x100000,
    CPU1_SYS_PCIE2_DEASSERT_INTA_GRT_POS = 20,
    CPU1_SYS_PCIE2_DEASSERT_INTB_GRT_MASK = (int)0x200000,
    CPU1_SYS_PCIE2_DEASSERT_INTB_GRT_POS = 21,
    CPU1_SYS_PCIE2_DEASSERT_INTC_GRT_MASK = (int)0x400000,
    CPU1_SYS_PCIE2_DEASSERT_INTC_GRT_POS = 22,
    CPU1_SYS_PCIE2_DEASSERT_INTD_GRT_MASK = (int)0x800000,
    CPU1_SYS_PCIE2_DEASSERT_INTD_GRT_POS = 23,
};

enum CPU1_SYS_REG_PCIE2_REG255_FIELD
{
    CPU1_SYS_PCIE2_CFG_INT_PIN_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_INT_PIN_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG256_FIELD
{
    CPU1_SYS_PCIE2_CFG_INT_PIN_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_INT_PIN_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG257_FIELD
{
    CPU1_SYS_PCIE2_CFG_SEND_COR_ERR_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_SEND_COR_ERR_POS = 0,
    CPU1_SYS_PCIE2_CFG_SEND_NF_ERR_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_CFG_SEND_NF_ERR_POS = 8,
    CPU1_SYS_PCIE2_CFG_SEND_F_ERR_MASK = (int)0xff0000,
    CPU1_SYS_PCIE2_CFG_SEND_F_ERR_POS = 16,
    CPU1_SYS_PCIE2_CFG_INT_DISABLE_MASK = (int)0xff000000,
    CPU1_SYS_PCIE2_CFG_INT_DISABLE_POS = 24,
};

enum CPU1_SYS_REG_PCIE2_REG258_FIELD
{
    CPU1_SYS_PCIE2_CFG_NO_SNOOP_EN_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_NO_SNOOP_EN_POS = 0,
    CPU1_SYS_PCIE2_CFG_RELAX_ORDER_EN_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_CFG_RELAX_ORDER_EN_POS = 8,
    CPU1_SYS_PCIE2_CFG_LINK_AUTO_BW_INT_MASK = (int)0x10000,
    CPU1_SYS_PCIE2_CFG_LINK_AUTO_BW_INT_POS = 16,
    CPU1_SYS_PCIE2_CFG_LINK_AUTO_BW_MSI_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_CFG_LINK_AUTO_BW_MSI_POS = 17,
    CPU1_SYS_PCIE2_CFG_BW_MGT_INT_MASK = (int)0x40000,
    CPU1_SYS_PCIE2_CFG_BW_MGT_INT_POS = 18,
    CPU1_SYS_PCIE2_CFG_BW_MGT_MSI_MASK = (int)0x80000,
    CPU1_SYS_PCIE2_CFG_BW_MGT_MSI_POS = 19,
};

enum CPU1_SYS_REG_PCIE2_REG259_FIELD
{
    CPU1_SYS_PCIE2_MSI_CTRL_IO_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_MSI_CTRL_IO_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG260_FIELD
{
    CPU1_SYS_PCIE2_MSI_CTRL_INT_MASK = (int)0x1,
    CPU1_SYS_PCIE2_MSI_CTRL_INT_POS = 0,
    CPU1_SYS_PCIE2_MSI_CTRL_INT_VEC_MASK = (int)0x1fe,
    CPU1_SYS_PCIE2_MSI_CTRL_INT_VEC_POS = 1,
    CPU1_SYS_PCIE2_DEVICE_TYPE_MASK = (int)0x1e00,
    CPU1_SYS_PCIE2_DEVICE_TYPE_POS = 9,
    CPU1_SYS_PCIE2_RBAR_CTRL_UPDATE_MASK = (int)0x1fe000,
    CPU1_SYS_PCIE2_RBAR_CTRL_UPDATE_POS = 13,
};

enum CPU1_SYS_REG_PCIE2_REG261_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG262_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG263_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG264_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG265_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG266_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG267_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG268_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG269_FIELD
{
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_RBAR_SIZE_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG270_FIELD
{
    CPU1_SYS_PCIE2_VF_RBAR_CTRL_UPDATE_MASK = (int)0xff,
    CPU1_SYS_PCIE2_VF_RBAR_CTRL_UPDATE_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG271_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG272_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG273_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_2_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_2_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG274_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_3_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_3_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG275_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_4_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_4_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG276_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_5_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_5_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG277_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_6_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_6_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG278_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_7_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_7_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG279_FIELD
{
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_8_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_VF_RBAR_SIZE_8_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG280_FIELD
{
    CPU1_SYS_PCIE2_CFG_BR_CTRL_SERREN_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_BR_CTRL_SERREN_POS = 0,
    CPU1_SYS_PCIE2_PM_L1SUB_STATE_MASK = (int)0x700,
    CPU1_SYS_PCIE2_PM_L1SUB_STATE_POS = 8,
    CPU1_SYS_PCIE2_APP_L1SUB_DISABLE_MASK = (int)0x800,
    CPU1_SYS_PCIE2_APP_L1SUB_DISABLE_POS = 11,
    CPU1_SYS_PCIE2_PM_MASTER_STATE_MASK = (int)0x1f000,
    CPU1_SYS_PCIE2_PM_MASTER_STATE_POS = 12,
    CPU1_SYS_PCIE2_PM_SLAVE_STATE_MASK = (int)0x3e0000,
    CPU1_SYS_PCIE2_PM_SLAVE_STATE_POS = 17,
    CPU1_SYS_PCIE2_CFG_UNCOR_INTERNAL_ERR_STS_MASK = (int)0x400000,
    CPU1_SYS_PCIE2_CFG_UNCOR_INTERNAL_ERR_STS_POS = 22,
    CPU1_SYS_PCIE2_CFG_RCVR_OVERFLOW_ERR_STS_MASK = (int)0x800000,
    CPU1_SYS_PCIE2_CFG_RCVR_OVERFLOW_ERR_STS_POS = 23,
    CPU1_SYS_PCIE2_CFG_FC_PROTOCOL_ERR_STS_MASK = (int)0x1000000,
    CPU1_SYS_PCIE2_CFG_FC_PROTOCOL_ERR_STS_POS = 24,
    CPU1_SYS_PCIE2_CFG_MLF_TLP_ERR_STS_MASK = (int)0x2000000,
    CPU1_SYS_PCIE2_CFG_MLF_TLP_ERR_STS_POS = 25,
    CPU1_SYS_PCIE2_CFG_SURPRISE_DOWN_ER_STS_MASK = (int)0x4000000,
    CPU1_SYS_PCIE2_CFG_SURPRISE_DOWN_ER_STS_POS = 26,
    CPU1_SYS_PCIE2_CFG_DL_PROTOCOL_ERR_STS_MASK = (int)0x8000000,
    CPU1_SYS_PCIE2_CFG_DL_PROTOCOL_ERR_STS_POS = 27,
    CPU1_SYS_PCIE2_CFG_ECRC_ERR_STS_MASK = (int)0x10000000,
    CPU1_SYS_PCIE2_CFG_ECRC_ERR_STS_POS = 28,
    CPU1_SYS_PCIE2_CFG_CORRECTED_INTERNAL_ERR_STS_MASK = (int)0x20000000,
    CPU1_SYS_PCIE2_CFG_CORRECTED_INTERNAL_ERR_STS_POS = 29,
    CPU1_SYS_PCIE2_CFG_REPLAY_NUMBER_ROLLOVER_ERR_STS_MASK = (int)0x40000000,
    CPU1_SYS_PCIE2_CFG_REPLAY_NUMBER_ROLLOVER_ERR_STS_POS = 30,
    CPU1_SYS_PCIE2_CFG_REPLAY_TIMER_TIMEOUT_ERR_STS_MASK = (int)0x80000000,
    CPU1_SYS_PCIE2_CFG_REPLAY_TIMER_TIMEOUT_ERR_STS_POS = 31,
};

enum CPU1_SYS_REG_PCIE2_REG281_FIELD
{
    CPU1_SYS_PCIE2_CFG_BAD_DLLP_ERR_STS_MASK = (int)0x1,
    CPU1_SYS_PCIE2_CFG_BAD_DLLP_ERR_STS_POS = 0,
    CPU1_SYS_PCIE2_CFG_BAD_TLP_ERR_STS_MASK = (int)0x2,
    CPU1_SYS_PCIE2_CFG_BAD_TLP_ERR_STS_POS = 1,
    CPU1_SYS_PCIE2_CFG_RCVR_ERR_STS_MASK = (int)0x4,
    CPU1_SYS_PCIE2_CFG_RCVR_ERR_STS_POS = 2,
    CPU1_SYS_PCIE2_APP_DEV_NUM_MASK = (int)0xf8,
    CPU1_SYS_PCIE2_APP_DEV_NUM_POS = 3,
    CPU1_SYS_PCIE2_APP_BUS_NUM_MASK = (int)0xff00,
    CPU1_SYS_PCIE2_APP_BUS_NUM_POS = 8,
};

enum CPU1_SYS_REG_PCIE2_REG282_FIELD
{
    CPU1_SYS_PCIE2_RADM_TRGT1_ATU_SLOC_MATCH_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_RADM_TRGT1_ATU_SLOC_MATCH_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG283_FIELD
{
    CPU1_SYS_PCIE2_RADM_TRGT1_ATU_CBUF_ERR_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_RADM_TRGT1_ATU_CBUF_ERR_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG284_FIELD
{
    CPU1_SYS_PCIE2_CFG_PHY_CONTROL_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_PHY_CONTROL_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG285_FIELD
{
    CPU1_SYS_PCIE2_PHY_CFG_STATUS_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PHY_CFG_STATUS_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG286_FIELD
{
    CPU1_SYS_PCIE2_PM_ASPM_L1_ENTER_READY_MASK = (int)0x1,
    CPU1_SYS_PCIE2_PM_ASPM_L1_ENTER_READY_POS = 0,
    CPU1_SYS_PCIE2_RADM_SLOT_PWR_LIMIT_MASK = (int)0x2,
    CPU1_SYS_PCIE2_RADM_SLOT_PWR_LIMIT_POS = 1,
};

enum CPU1_SYS_REG_PCIE2_REG287_FIELD
{
    CPU1_SYS_PCIE2_RADM_SLOT_PWR_PAYLOAD_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_RADM_SLOT_PWR_PAYLOAD_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG288_FIELD
{
    CPU1_SYS_PCIE2_PERST_N_REG_MASK = (int)0x1,
    CPU1_SYS_PCIE2_PERST_N_REG_POS = 0,
    CPU1_SYS_PCIE2_PERST_O_CTL_REG_MASK = (int)0x6,
    CPU1_SYS_PCIE2_PERST_O_CTL_REG_POS = 1,
    CPU1_SYS_PCIE2_PHY_RST_REG_MASK = (int)0x8,
    CPU1_SYS_PCIE2_PHY_RST_REG_POS = 3,
    CPU1_SYS_PAD_PCIE2_PERST_OE_MASK = (int)0x10,
    CPU1_SYS_PAD_PCIE2_PERST_OE_POS = 4,
    CPU1_SYS_PCIE2_PERST_CTL_REG_MASK = (int)0x60,
    CPU1_SYS_PCIE2_PERST_CTL_REG_POS = 5,
};

enum CPU1_SYS_REG_PCIE2_RAM_REG_0_FIELD
{
    CPU1_SYS_PCIE2_EDMA_RD_ENG_MSI_EMAA_MASK = (int)0x1c0000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_MSI_EMAA_POS = 18,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_MSI_EMAB_MASK = (int)0x38000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_MSI_EMAB_POS = 15,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_MSI_EMASA_MASK = (int)0x4000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_MSI_EMASA_POS = 14,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_MSI_EMAA_MASK = (int)0x3800,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_MSI_EMAA_POS = 11,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_MSI_EMAB_MASK = (int)0x700,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_MSI_EMAB_POS = 8,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_MSI_EMASA_MASK = (int)0x80,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_MSI_EMASA_POS = 7,
    CPU1_SYS_PCIE2_IB_MCPL_SB_RAM_EMA_MASK = (int)0x70,
    CPU1_SYS_PCIE2_IB_MCPL_SB_RAM_EMA_POS = 4,
    CPU1_SYS_PCIE2_IB_MCPL_SB_RAM_EMAW_MASK = (int)0xc,
    CPU1_SYS_PCIE2_IB_MCPL_SB_RAM_EMAW_POS = 2,
    CPU1_SYS_PCIE2_IB_MCPL_SB_RAM_EMAS_MASK = (int)0x2,
    CPU1_SYS_PCIE2_IB_MCPL_SB_RAM_EMAS_POS = 1,
    CPU1_SYS_PCIE2_IB_MCPL_SB_RAM_EMAP_MASK = (int)0x1,
    CPU1_SYS_PCIE2_IB_MCPL_SB_RAM_EMAP_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_RAM_REG_1_FIELD
{
    CPU1_SYS_PCIE2_IB_MCPL_A2C_CDC_RAM_EMAA_MASK = (int)0x70000000,
    CPU1_SYS_PCIE2_IB_MCPL_A2C_CDC_RAM_EMAA_POS = 28,
    CPU1_SYS_PCIE2_IB_MCPL_A2C_CDC_RAM_EMAB_MASK = (int)0xe000000,
    CPU1_SYS_PCIE2_IB_MCPL_A2C_CDC_RAM_EMAB_POS = 25,
    CPU1_SYS_PCIE2_IB_MCPL_A2C_CDC_RAM_EMASA_MASK = (int)0x1000000,
    CPU1_SYS_PCIE2_IB_MCPL_A2C_CDC_RAM_EMASA_POS = 24,
    CPU1_SYS_PCIE2_IB_RREQ_C2A_CDC_RAM_EMAA_MASK = (int)0xe00000,
    CPU1_SYS_PCIE2_IB_RREQ_C2A_CDC_RAM_EMAA_POS = 21,
    CPU1_SYS_PCIE2_IB_RREQ_C2A_CDC_RAM_EMAB_MASK = (int)0x1c0000,
    CPU1_SYS_PCIE2_IB_RREQ_C2A_CDC_RAM_EMAB_POS = 18,
    CPU1_SYS_PCIE2_IB_RREQ_C2A_CDC_RAM_EMASA_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_IB_RREQ_C2A_CDC_RAM_EMASA_POS = 17,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_L_EMAA_MASK = (int)0x1c000,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_L_EMAA_POS = 14,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_L_EMAB_MASK = (int)0x3800,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_L_EMAB_POS = 11,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_L_EMASA_MASK = (int)0x400,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_L_EMASA_POS = 10,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_H_EMAA_MASK = (int)0x380,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_H_EMAA_POS = 7,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_H_EMAB_MASK = (int)0x70,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_H_EMAB_POS = 4,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_H_EMASA_MASK = (int)0x8,
    CPU1_SYS_PCIE2_IB_WREQ_C2A_CDC_RAM_H_EMASA_POS = 3,
    CPU1_SYS_PCIE2_OB_CCMP_DATA_RAM_EMAA_MASK = (int)0x7,
    CPU1_SYS_PCIE2_OB_CCMP_DATA_RAM_EMAA_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_RAM_REG_2_FIELD
{
    CPU1_SYS_PCIE2_OB_CCMP_DATA_RAM_EMAB_MASK = (int)0x38000000,
    CPU1_SYS_PCIE2_OB_CCMP_DATA_RAM_EMAB_POS = 27,
    CPU1_SYS_PCIE2_OB_CCMP_DATA_RAM_EMASA_MASK = (int)0x4000000,
    CPU1_SYS_PCIE2_OB_CCMP_DATA_RAM_EMASA_POS = 26,
    CPU1_SYS_PCIE2_SLV_NPW_SAB_RAM_EMA_MASK = (int)0x3800000,
    CPU1_SYS_PCIE2_SLV_NPW_SAB_RAM_EMA_POS = 23,
    CPU1_SYS_PCIE2_SLV_NPW_SAB_RAM_EMAW_MASK = (int)0x600000,
    CPU1_SYS_PCIE2_SLV_NPW_SAB_RAM_EMAW_POS = 21,
    CPU1_SYS_PCIE2_SLV_NPW_SAB_RAM_EMAS_MASK = (int)0x100000,
    CPU1_SYS_PCIE2_SLV_NPW_SAB_RAM_EMAS_POS = 20,
    CPU1_SYS_PCIE2_SLV_NPW_SAB_RAM_EMAP_MASK = (int)0x80000,
    CPU1_SYS_PCIE2_SLV_NPW_SAB_RAM_EMAP_POS = 19,
    CPU1_SYS_PCIE2_OB_PDCMP_DATA_RAM_EMAA_MASK = (int)0x70000,
    CPU1_SYS_PCIE2_OB_PDCMP_DATA_RAM_EMAA_POS = 16,
    CPU1_SYS_PCIE2_OB_PDCMP_DATA_RAM_EMAB_MASK = (int)0xe000,
    CPU1_SYS_PCIE2_OB_PDCMP_DATA_RAM_EMAB_POS = 13,
    CPU1_SYS_PCIE2_OB_PDCMP_DATA_RAM_EMASA_MASK = (int)0x1000,
    CPU1_SYS_PCIE2_OB_PDCMP_DATA_RAM_EMASA_POS = 12,
    CPU1_SYS_PCIE2_OB_PDCMP_HDR_RAM_EMAA_MASK = (int)0xe00,
    CPU1_SYS_PCIE2_OB_PDCMP_HDR_RAM_EMAA_POS = 9,
    CPU1_SYS_PCIE2_OB_PDCMP_HDR_RAM_EMAB_MASK = (int)0x1c0,
    CPU1_SYS_PCIE2_OB_PDCMP_HDR_RAM_EMAB_POS = 6,
    CPU1_SYS_PCIE2_OB_PDCMP_HDR_RAM_EMASA_MASK = (int)0x20,
    CPU1_SYS_PCIE2_OB_PDCMP_HDR_RAM_EMASA_POS = 5,
    CPU1_SYS_PCIE2_CDM_RAS_DES_EC_RAM_EMA_MASK = (int)0x1c,
    CPU1_SYS_PCIE2_CDM_RAS_DES_EC_RAM_EMA_POS = 2,
    CPU1_SYS_PCIE2_CDM_RAS_DES_EC_RAM_EMAW_MASK = (int)0x3,
    CPU1_SYS_PCIE2_CDM_RAS_DES_EC_RAM_EMAW_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_RAM_REG_3_FIELD
{
    CPU1_SYS_PCIE2_CDM_RAS_DES_EC_RAM_EMAS_MASK = (int)0x20000000,
    CPU1_SYS_PCIE2_CDM_RAS_DES_EC_RAM_EMAS_POS = 29,
    CPU1_SYS_PCIE2_CDM_RAS_DES_EC_RAM_EMAP_MASK = (int)0x10000000,
    CPU1_SYS_PCIE2_CDM_RAS_DES_EC_RAM_EMAP_POS = 28,
    CPU1_SYS_PCIE2_EDMARBUFF2RAM_EMA_MASK = (int)0xe000000,
    CPU1_SYS_PCIE2_EDMARBUFF2RAM_EMA_POS = 25,
    CPU1_SYS_PCIE2_EDMARBUFF2RAM_EMAW_MASK = (int)0x1800000,
    CPU1_SYS_PCIE2_EDMARBUFF2RAM_EMAW_POS = 23,
    CPU1_SYS_PCIE2_EDMARBUFF2RAM_EMAS_MASK = (int)0x400000,
    CPU1_SYS_PCIE2_EDMARBUFF2RAM_EMAS_POS = 22,
    CPU1_SYS_PCIE2_EDMARBUFF2RAM_EMAP_MASK = (int)0x200000,
    CPU1_SYS_PCIE2_EDMARBUFF2RAM_EMAP_POS = 21,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_C2W_LUT_EMAA_MASK = (int)0x1c0000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_C2W_LUT_EMAA_POS = 18,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_C2W_LUT_EMAB_MASK = (int)0x38000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_C2W_LUT_EMAB_POS = 15,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_C2W_LUT_EMASA_MASK = (int)0x4000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_C2W_LUT_EMASA_POS = 14,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_H_EMA_MASK = (int)0x3800,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_H_EMA_POS = 11,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_H_EMAW_MASK = (int)0x600,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_H_EMAW_POS = 9,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_H_EMAS_MASK = (int)0x100,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_H_EMAS_POS = 8,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_H_EMAP_MASK = (int)0x80,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_H_EMAP_POS = 7,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_L_EMA_MASK = (int)0x70,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_L_EMA_POS = 4,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_L_EMAW_MASK = (int)0xc,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_L_EMAW_POS = 2,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_L_EMAS_MASK = (int)0x2,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_L_EMAS_POS = 1,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_L_EMAP_MASK = (int)0x1,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_OVRL_L_EMAP_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_RAM_REG_4_FIELD
{
    CPU1_SYS_PCIE2_EDMA_RD_ENG_STSH_LUT_EMAA_MASK = (int)0x70000000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_STSH_LUT_EMAA_POS = 28,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_STSH_LUT_EMAB_MASK = (int)0xe000000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_STSH_LUT_EMAB_POS = 25,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_STSH_LUT_EMASA_MASK = (int)0x1000000,
    CPU1_SYS_PCIE2_EDMA_RD_ENG_STSH_LUT_EMASA_POS = 24,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_C2W_LUT_EMAA_MASK = (int)0xe00000,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_C2W_LUT_EMAA_POS = 21,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_C2W_LUT_EMAB_MASK = (int)0x1c0000,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_C2W_LUT_EMAB_POS = 18,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_C2W_LUT_EMASA_MASK = (int)0x20000,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_C2W_LUT_EMASA_POS = 17,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_L_EMA_MASK = (int)0x1c000,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_L_EMA_POS = 14,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_L_EMAW_MASK = (int)0x3000,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_L_EMAW_POS = 12,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_L_EMAS_MASK = (int)0x800,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_L_EMAS_POS = 11,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_L_EMAP_MASK = (int)0x400,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_L_EMAP_POS = 10,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_H_EMA_MASK = (int)0x380,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_H_EMA_POS = 7,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_H_EMAW_MASK = (int)0x60,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_H_EMAW_POS = 5,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_H_EMAS_MASK = (int)0x10,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_H_EMAS_POS = 4,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_H_EMAP_MASK = (int)0x8,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_OVRL_H_EMAP_POS = 3,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_STSH_LUT_EMAA_MASK = (int)0x7,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_STSH_LUT_EMAA_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_RAM_REG_5_FIELD
{
    CPU1_SYS_PCIE2_EDMA_WR_ENG_STSH_LUT_EMAB_MASK = (int)0x70000000,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_STSH_LUT_EMAB_POS = 28,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_STSH_LUT_EMASA_MASK = (int)0x8000000,
    CPU1_SYS_PCIE2_EDMA_WR_ENG_STSH_LUT_EMASA_POS = 27,
    CPU1_SYS_PCIE2_P_DATAQ_EMA_MASK = (int)0x7000000,
    CPU1_SYS_PCIE2_P_DATAQ_EMA_POS = 24,
    CPU1_SYS_PCIE2_P_DATAQ_EMAW_MASK = (int)0xc00000,
    CPU1_SYS_PCIE2_P_DATAQ_EMAW_POS = 22,
    CPU1_SYS_PCIE2_P_DATAQ_EMAS_MASK = (int)0x200000,
    CPU1_SYS_PCIE2_P_DATAQ_EMAS_POS = 21,
    CPU1_SYS_PCIE2_P_DATAQ_EMAP_MASK = (int)0x100000,
    CPU1_SYS_PCIE2_P_DATAQ_EMAP_POS = 20,
    CPU1_SYS_PCIE2_P_HDRQ_EMA_MASK = (int)0xe0000,
    CPU1_SYS_PCIE2_P_HDRQ_EMA_POS = 17,
    CPU1_SYS_PCIE2_P_HDRQ_EMAW_MASK = (int)0x18000,
    CPU1_SYS_PCIE2_P_HDRQ_EMAW_POS = 15,
    CPU1_SYS_PCIE2_P_HDRQ_EMAS_MASK = (int)0x4000,
    CPU1_SYS_PCIE2_P_HDRQ_EMAS_POS = 14,
    CPU1_SYS_PCIE2_P_HDRQ_EMAP_MASK = (int)0x2000,
    CPU1_SYS_PCIE2_P_HDRQ_EMAP_POS = 13,
    CPU1_SYS_PCIE2_XDLH_RETRYRAM_EMA_MASK = (int)0x1c00,
    CPU1_SYS_PCIE2_XDLH_RETRYRAM_EMA_POS = 10,
    CPU1_SYS_PCIE2_XDLH_RETRYRAM_EMAW_MASK = (int)0x300,
    CPU1_SYS_PCIE2_XDLH_RETRYRAM_EMAW_POS = 8,
    CPU1_SYS_PCIE2_XDLH_RETRYRAM_EMAS_MASK = (int)0x80,
    CPU1_SYS_PCIE2_XDLH_RETRYRAM_EMAS_POS = 7,
    CPU1_SYS_PCIE2_OB_NPDCMP_RAM_EMAA_MASK = (int)0x70,
    CPU1_SYS_PCIE2_OB_NPDCMP_RAM_EMAA_POS = 4,
    CPU1_SYS_PCIE2_OB_NPDCMP_RAM_EMAB_MASK = (int)0xe,
    CPU1_SYS_PCIE2_OB_NPDCMP_RAM_EMAB_POS = 1,
    CPU1_SYS_PCIE2_OB_NPDCMP_RAM_EMASA_MASK = (int)0x1,
    CPU1_SYS_PCIE2_OB_NPDCMP_RAM_EMASA_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_SLV_REG0_FIELD
{
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_HDR_34DW_1_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_HDR_34DW_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_SLV_REG1_FIELD
{
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_HDR_34DW_0_MASK = (int)0xffffffff,
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_HDR_34DW_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_SLV_REG2_FIELD
{
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_P_TAG_MASK = (int)0x1fe00,
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_P_TAG_POS = 9,
    CPU1_SYS_CPU1_PCIE2_S_ARMISC_INFO_ATU_BYPASS_MASK = (int)0x100,
    CPU1_SYS_CPU1_PCIE2_S_ARMISC_INFO_ATU_BYPASS_POS = 8,
    CPU1_SYS_CPU1_PCIE2_S_WMISC_INFO_SILENTDROP_MASK = (int)0x80,
    CPU1_SYS_CPU1_PCIE2_S_WMISC_INFO_SILENTDROP_POS = 7,
    CPU1_SYS_CPU1_PCIE2_S_WMISC_INFO_EP_MASK = (int)0x40,
    CPU1_SYS_CPU1_PCIE2_S_WMISC_INFO_EP_POS = 6,
    CPU1_SYS_CPU1_PCIE2_S_CSYSREQ_MASK = (int)0x20,
    CPU1_SYS_CPU1_PCIE2_S_CSYSREQ_POS = 5,
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_ATU_BYPASS_MASK = (int)0x10,
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_ATU_BYPASS_POS = 4,
    CPU1_SYS_CPU1_PCIE2_S_AWQOS_MASK = (int)0xf,
    CPU1_SYS_CPU1_PCIE2_S_AWQOS_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_SLV_REG3_FIELD
{
    CPU1_SYS_CPU1_PCIE2_S_ARMISC_INFO_MASK = (int)0x1ffffff0,
    CPU1_SYS_CPU1_PCIE2_S_ARMISC_INFO_POS = 4,
    CPU1_SYS_CPU1_PCIE2_S_ARQOS_MASK = (int)0xf,
    CPU1_SYS_CPU1_PCIE2_S_ARQOS_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_SLV_REG4_FIELD
{
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_MASK = (int)0x1ffffff,
    CPU1_SYS_CPU1_PCIE2_S_AWMISC_INFO_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_SLV_REG5_FIELD
{
    CPU1_SYS_PCIE2_CPU1_S_CACTIVE_MASK = (int)0x20000000,
    CPU1_SYS_PCIE2_CPU1_S_CACTIVE_POS = 29,
    CPU1_SYS_PCIE2_CPU1_S_CSYSACK_MASK = (int)0x10000000,
    CPU1_SYS_PCIE2_CPU1_S_CSYSACK_POS = 28,
    CPU1_SYS_PCIE2_CPU1_S_RMISC_INFO_MASK = (int)0xfffc000,
    CPU1_SYS_PCIE2_CPU1_S_RMISC_INFO_POS = 14,
    CPU1_SYS_PCIE2_CPU1_S_BMISC_INFO_MASK = (int)0x3fff,
    CPU1_SYS_PCIE2_CPU1_S_BMISC_INFO_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_MST_REG0_FIELD
{
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_HDR_34DW_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_HDR_34DW_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_MST_REG1_FIELD
{
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_HDR_34DW_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_HDR_34DW_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_MST_REG2_FIELD
{
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_1_MASK = (int)0xffff,
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_MST_REG3_FIELD
{
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_MST_REG4_FIELD
{
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_1_MASK = (int)0xffff,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_MST_REG5_FIELD
{
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_MST_REG6_FIELD
{
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_DMA_MASK = (int)0xfc0000,
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_DMA_POS = 18,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_DMA_MASK = (int)0x3f000,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_DMA_POS = 12,
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_LAST_DCMP_TLP_MASK = (int)0x800,
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_LAST_DCMP_TLP_POS = 11,
    CPU1_SYS_PCIE2_MATRIX6_M_CACTIVE_MASK = (int)0x400,
    CPU1_SYS_PCIE2_MATRIX6_M_CACTIVE_POS = 10,
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_ZEROREAD_MASK = (int)0x200,
    CPU1_SYS_PCIE2_MATRIX6_M_ARMISC_INFO_ZEROREAD_POS = 9,
    CPU1_SYS_PCIE2_MATRIX6_M_ARQOS_MASK = (int)0x1e0,
    CPU1_SYS_PCIE2_MATRIX6_M_ARQOS_POS = 5,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_LAST_DCMP_TLP_MASK = (int)0x10,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_LAST_DCMP_TLP_POS = 4,
    CPU1_SYS_PCIE2_MATRIX6_M_AWQOS_MASK = (int)0xf,
    CPU1_SYS_PCIE2_MATRIX6_M_AWQOS_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_AXI_MST_REG7_FIELD
{
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_EP_MASK = (int)0x80000000,
    CPU1_SYS_PCIE2_MATRIX6_M_AWMISC_INFO_EP_POS = 31,
    CPU1_SYS_PCIE2_MATRIX6_M_CSYSACK_MASK = (int)0x100000,
    CPU1_SYS_PCIE2_MATRIX6_M_CSYSACK_POS = 20,
    CPU1_SYS_MATRIX6_PCIE2_M_RMISC_INFO_MASK = (int)0xfff80,
    CPU1_SYS_MATRIX6_PCIE2_M_RMISC_INFO_POS = 7,
    CPU1_SYS_MATRIX6_PCIE2_M_CSYSREQ_MASK = (int)0x40,
    CPU1_SYS_MATRIX6_PCIE2_M_CSYSREQ_POS = 6,
    CPU1_SYS_MATRIX6_PCIE2_M_BMISC_INFO_CPL_STAT_MASK = (int)0x38,
    CPU1_SYS_MATRIX6_PCIE2_M_BMISC_INFO_CPL_STAT_POS = 3,
    CPU1_SYS_MATRIX6_PCIE2_M_RMISC_INFO_CPL_STAT_MASK = (int)0x7,
    CPU1_SYS_MATRIX6_PCIE2_M_RMISC_INFO_CPL_STAT_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_DBI_SLV_REG0_FIELD
{
    CPU1_SYS_CPU1_PCIE2_DBI_S_CSYSREQ_MASK = (int)0x400,
    CPU1_SYS_CPU1_PCIE2_DBI_S_CSYSREQ_POS = 10,
    CPU1_SYS_CPU1_PCIE2_DBI_S_ARQOS_MASK = (int)0x3c0,
    CPU1_SYS_CPU1_PCIE2_DBI_S_ARQOS_POS = 6,
    CPU1_SYS_CPU1_PCIE2_DBI_S_AWQOS_MASK = (int)0x3c,
    CPU1_SYS_CPU1_PCIE2_DBI_S_AWQOS_POS = 2,
    CPU1_SYS_PCIE2_DBI_CPU1_S_CACTIVE_MASK = (int)0x2,
    CPU1_SYS_PCIE2_DBI_CPU1_S_CACTIVE_POS = 1,
    CPU1_SYS_PCIE2_DBI_CPU1_S_CSYSACK_MASK = (int)0x1,
    CPU1_SYS_PCIE2_DBI_CPU1_S_CSYSACK_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_VEN_MSG_START_T_FIELD
{
    CPU1_SYS_PCIE2_VEN_MSG_START_T_MASK = (int)0x1,
    CPU1_SYS_PCIE2_VEN_MSG_START_T_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_VEN_MSI_START_T_FIELD
{
    CPU1_SYS_PCIE2_VEN_MSI_START_T_MASK = (int)0x1,
    CPU1_SYS_PCIE2_VEN_MSI_START_T_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_APP_LTR_MSG_START_T_FIELD
{
    CPU1_SYS_PCIE2_APP_LTR_MSG_START_T_MASK = (int)0x1,
    CPU1_SYS_PCIE2_APP_LTR_MSG_START_T_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_APP_OBFF_IDLE_MSG_START_T_FIELD
{
    CPU1_SYS_PCIE2_APP_OBFF_IDLE_MSG_START_T_MASK = (int)0x1,
    CPU1_SYS_PCIE2_APP_OBFF_IDLE_MSG_START_T_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_APP_OBFF_OBFF_MSG_START_T_FIELD
{
    CPU1_SYS_PCIE2_APP_OBFF_OBFF_MSG_START_T_MASK = (int)0x1,
    CPU1_SYS_PCIE2_APP_OBFF_OBFF_MSG_START_T_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_APP_OBFF_CPU_ACTIVE_MSG_START_T_FIELD
{
    CPU1_SYS_PCIE2_APP_OBFF_CPU_ACTIVE_MSG_START_T_MASK = (int)0x1,
    CPU1_SYS_PCIE2_APP_OBFF_CPU_ACTIVE_MSG_START_T_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_VEN_MSG_REQ_TIMEOUT_CNT_FIELD
{
    CPU1_SYS_PCIE2_VEN_MSG_REQ_TIMEOUT_CNT_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_VEN_MSG_REQ_TIMEOUT_CNT_POS = 0,
};

enum CPU1_SYS_REG_X2H_ADJUST_AXI_EN_FIELD
{
    CPU1_SYS_X2H_ADJUST_AXI_EN_MASK = (int)0x1,
    CPU1_SYS_X2H_ADJUST_AXI_EN_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG300_FIELD
{
    CPU1_SYS_PCIE2_RADM_INT_CLR_MASK = (int)0xf,
    CPU1_SYS_PCIE2_RADM_INT_CLR_POS = 0,
    CPU1_SYS_PCIE2_MSG_INTR_CLR_MASK = (int)0xfff0,
    CPU1_SYS_PCIE2_MSG_INTR_CLR_POS = 4,
    CPU1_SYS_PCIE2_RADM_ERR_INT_CLR_MASK = (int)0x70000,
    CPU1_SYS_PCIE2_RADM_ERR_INT_CLR_POS = 16,
};

enum CPU1_SYS_REG_PCIE2_REG301_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_CLR_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_CLR_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG302_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_CLR_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_CLR_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG303_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_CLR_2_MASK = (int)0x3,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_CLR_2_POS = 0,
    CPU1_SYS_PCIE2_ASSERT_INT_CLR_MASK = (int)0x3c,
    CPU1_SYS_PCIE2_ASSERT_INT_CLR_POS = 2,
    CPU1_SYS_PCIE2_MCTP_RFIFO_RD_MASK = (int)0x40,
    CPU1_SYS_PCIE2_MCTP_RFIFO_RD_POS = 6,
    CPU1_SYS_PCIE2_MCTP_SOFT_RFIFO_WCLR_MASK = (int)0x80,
    CPU1_SYS_PCIE2_MCTP_SOFT_RFIFO_WCLR_POS = 7,
    CPU1_SYS_PCIE2_MCTP_SOFT_RFIFO_RCLR_MASK = (int)0x100,
    CPU1_SYS_PCIE2_MCTP_SOFT_RFIFO_RCLR_POS = 8,
};

enum CPU1_SYS_REG_PCIE2_REG304_FIELD
{
    CPU1_SYS_PCIE2_RADM_TIMEOUT_INT_CLR_MASK = (int)0x1fffffff,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_INT_CLR_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG305_FIELD
{
    CPU1_SYS_PCIE2_MSG_REQ_TIMEOUT_CHECK_MASK = (int)0x3f,
    CPU1_SYS_PCIE2_MSG_REQ_TIMEOUT_CHECK_POS = 0,
    CPU1_SYS_PCIE2_MSG_INTR_MSK_MASK = (int)0x3ffc0,
    CPU1_SYS_PCIE2_MSG_INTR_MSK_POS = 6,
    CPU1_SYS_PCIE2_MSG_INTR_RAW_MASK = (int)0x3ffc0000,
    CPU1_SYS_PCIE2_MSG_INTR_RAW_POS = 18,
};

enum CPU1_SYS_REG_PCIE2_REG306_FIELD
{
    CPU1_SYS_PCIE2_MSG_INTR_STT_MASK = (int)0xfff,
    CPU1_SYS_PCIE2_MSG_INTR_STT_POS = 0,
    CPU1_SYS_PCIE2_RADM_ERR_INT_MASK_MASK = (int)0x7000,
    CPU1_SYS_PCIE2_RADM_ERR_INT_MASK_POS = 12,
    CPU1_SYS_PCIE2_ASSERT_INT_MASK_MASK = (int)0x78000,
    CPU1_SYS_PCIE2_ASSERT_INT_MASK_POS = 15,
    CPU1_SYS_PCIE2_RADM_INT_MASK_MASK = (int)0x780000,
    CPU1_SYS_PCIE2_RADM_INT_MASK_POS = 19,
};

enum CPU1_SYS_REG_PCIE2_REG307_FIELD
{
    CPU1_SYS_PCIE2_PCIE_IP_INT_MASK_MASK = (int)0x7ffffff,
    CPU1_SYS_PCIE2_PCIE_IP_INT_MASK_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG308_FIELD
{
    CPU1_SYS_PCIE2_RADM_TIMEOUT_INT_MASK_MASK = (int)0x1fffffff,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_INT_MASK_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG309_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_MASK_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_MASK_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG310_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_MASK_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_MASK_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG311_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_MASK_2_MASK = (int)0x3,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_MASK_2_POS = 0,
    CPU1_SYS_PCIE2_ASSERT_INT_CLR_CTL_MASK = (int)0x4,
    CPU1_SYS_PCIE2_ASSERT_INT_CLR_CTL_POS = 2,
    CPU1_SYS_PCIE2_RADM_INT_CLR_CTL_MASK = (int)0x8,
    CPU1_SYS_PCIE2_RADM_INT_CLR_CTL_POS = 3,
    CPU1_SYS_PCIE2_RADM_ERR_INT_RAW_MASK = (int)0x70,
    CPU1_SYS_PCIE2_RADM_ERR_INT_RAW_POS = 4,
    CPU1_SYS_PCIE2_ASSERT_INT_RAW_MASK = (int)0x780,
    CPU1_SYS_PCIE2_ASSERT_INT_RAW_POS = 7,
    CPU1_SYS_PCIE2_RADM_INT_RAW_MASK = (int)0x7800,
    CPU1_SYS_PCIE2_RADM_INT_RAW_POS = 11,
    CPU1_SYS_PCIE2_RADM_ERR_INT_STA_MASK = (int)0x38000,
    CPU1_SYS_PCIE2_RADM_ERR_INT_STA_POS = 15,
    CPU1_SYS_PCIE2_ASSERT_INT_STA_MASK = (int)0x3c0000,
    CPU1_SYS_PCIE2_ASSERT_INT_STA_POS = 18,
    CPU1_SYS_PCIE2_RADM_INT_STA_MASK = (int)0x3c00000,
    CPU1_SYS_PCIE2_RADM_INT_STA_POS = 22,
};

enum CPU1_SYS_REG_PCIE2_REG312_FIELD
{
    CPU1_SYS_PCIE2_RADM_TIMEOUT_INT_RAW_MASK = (int)0x1fffffff,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_INT_RAW_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG313_FIELD
{
    CPU1_SYS_PCIE2_RADM_TIMEOUT_INT_STA_MASK = (int)0x1fffffff,
    CPU1_SYS_PCIE2_RADM_TIMEOUT_INT_STA_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG314_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_RAW_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_RAW_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG315_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_STA_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_STA_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG316_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_RAW_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_RAW_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG317_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_STA_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_STA_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG318_FIELD
{
    CPU1_SYS_PCIE2_PCIE_AUX_INT_RAW_2_MASK = (int)0x3,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_RAW_2_POS = 0,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_STA_2_MASK = (int)0xc,
    CPU1_SYS_PCIE2_PCIE_AUX_INT_STA_2_POS = 2,
    CPU1_SYS_PCIE2_MCTP_FIFO_WARN_LEVEL_REG_MASK = (int)0x3f0,
    CPU1_SYS_PCIE2_MCTP_FIFO_WARN_LEVEL_REG_POS = 4,
};

enum CPU1_SYS_REG_PCIE2_REG319_FIELD
{
    CPU1_SYS_PCIE2_RADM_TRGT1_ATU_SLOC_MATCH_MASK_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_RADM_TRGT1_ATU_SLOC_MATCH_MASK_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG320_FIELD
{
    CPU1_SYS_PCIE2_MCTP_RFIFO_RDAT_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_MCTP_RFIFO_RDAT_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG321_FIELD
{
    CPU1_SYS_PCIE2_MCTP_RFIFO_RDAT_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_MCTP_RFIFO_RDAT_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG322_FIELD
{
    CPU1_SYS_PCIE2_MCTP_RFIFO_RFLVL_MASK = (int)0x3f,
    CPU1_SYS_PCIE2_MCTP_RFIFO_RFLVL_POS = 0,
    CPU1_SYS_PCIE2_MCTP_RD_RFIFO_WFLVL_MASK = (int)0xfc0,
    CPU1_SYS_PCIE2_MCTP_RD_RFIFO_WFLVL_POS = 6,
    CPU1_SYS_PCIE2_RX_MCTP_INTR_MSK_MASK = (int)0x7000,
    CPU1_SYS_PCIE2_RX_MCTP_INTR_MSK_POS = 12,
    CPU1_SYS_PCIE2_RX_MCTP_INTR_RAW_MASK = (int)0x38000,
    CPU1_SYS_PCIE2_RX_MCTP_INTR_RAW_POS = 15,
    CPU1_SYS_PCIE2_RX_MCTP_INTR_STT_MASK = (int)0x1c0000,
    CPU1_SYS_PCIE2_RX_MCTP_INTR_STT_POS = 18,
};

enum CPU1_SYS_REG_PCIE2_CFG_PBUS_NUM_0_FIELD
{
    CPU1_SYS_PCIE2_CFG_PBUS_NUM_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_PBUS_NUM_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_CFG_PBUS_NUM_1_FIELD
{
    CPU1_SYS_PCIE2_CFG_PBUS_NUM_1_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_PBUS_NUM_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_CFG_PBUS_DEV_NUM_0_FIELD
{
    CPU1_SYS_PCIE2_CFG_PBUS_DEV_NUM_0_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_CFG_PBUS_DEV_NUM_0_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_CFG_PBUS_DEV_NUM_1_FIELD
{
    CPU1_SYS_PCIE2_CFG_PBUS_DEV_NUM_1_MASK = (int)0xff,
    CPU1_SYS_PCIE2_CFG_PBUS_DEV_NUM_1_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG323_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_18_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_18_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG324_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_19_MASK = (int)0xffffffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_19_POS = 0,
};

enum CPU1_SYS_REG_PCIE2_REG325_FIELD
{
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_20_MASK = (int)0x3ffff,
    CPU1_SYS_PCIE2_DIAG_STATUS_BUS_20_POS = 0,
};

enum CPU1_SYS_REG_C908_RST_READY_INTR_MASK_FIELD
{
    CPU1_SYS_C908_RST_READY_INTR_MASK_MASK = (int)0x1,
    CPU1_SYS_C908_RST_READY_INTR_MASK_POS = 0,
};

enum CPU1_SYS_REG_C908_RST_READY_INTR_CLR_FIELD
{
    CPU1_SYS_C908_RST_READY_INTR_CLR_MASK = (int)0x1,
    CPU1_SYS_C908_RST_READY_INTR_CLR_POS = 0,
};

enum CPU1_SYS_REG_C908_RST_READY_INTR_RAW_FIELD
{
    CPU1_SYS_C908_RST_READY_INTR_RAW_MASK = (int)0x1,
    CPU1_SYS_C908_RST_READY_INTR_RAW_POS = 0,
};

enum CPU1_SYS_REG_PAD_EX_RST_N_FLAG_FIELD
{
    CPU1_SYS_PAD_EX_RST_N_FLAG_MASK = (int)0x1,
    CPU1_SYS_PAD_EX_RST_N_FLAG_POS = 0,
};

enum CPU1_SYS_REG_C908_PAD_CPU_RST_N_FLAG_FIELD
{
    CPU1_SYS_C908_PAD_CPU_RST_N_FLAG_MASK = (int)0x1,
    CPU1_SYS_C908_PAD_CPU_RST_N_FLAG_POS = 0,
};


#ifdef __cplusplus
}
#endif

#endif

