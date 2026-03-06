/* 自动生成的寄存器定义文件 */
/* 由RALF文件自动生成，请勿手动修改 */

#ifndef __REG_SSIV2_TYPE_H__
#define __REG_SSIV2_TYPE_H__

#include <stdint.h>

/* 各模块寄存器结构体定义 */
/* axi_ssic_memory_map_ssic_address_block 寄存器块 */
typedef struct
{
    volatile uint32_t CTRLR0                        ; // 0x0000
    volatile uint32_t CTRLR1                        ; // 0x0004
    volatile uint32_t SSIENR                        ; // 0x0008
    volatile uint32_t MWCR                          ; // 0x000C
    volatile uint32_t SER                           ; // 0x0010
    volatile uint32_t BAUDR                         ; // 0x0014
    volatile uint32_t TXFTLR                        ; // 0x0018
    volatile uint32_t RXFTLR                        ; // 0x001C
    volatile uint32_t TXFLR                         ; // 0x0020
    volatile uint32_t RXFLR                         ; // 0x0024
    volatile uint32_t SR                            ; // 0x0028
    volatile uint32_t IMR                           ; // 0x002C
    volatile uint32_t ISR                           ; // 0x0030
    volatile uint32_t RISR                          ; // 0x0034
    volatile uint32_t TXEICR                        ; // 0x0038
    volatile uint32_t RXOICR                        ; // 0x003C
    volatile uint32_t RXUICR                        ; // 0x0040
    volatile uint32_t MSTICR                        ; // 0x0044
    volatile uint32_t ICR                           ; // 0x0048
    volatile uint32_t DMACR                         ; // 0x004C
    volatile uint32_t AXIAWLEN                      ; // 0x0050
    volatile uint32_t AXIARLEN                      ; // 0x0054
    volatile uint32_t IDR                           ; // 0x0058
    volatile uint32_t SSIC_VERSION_ID               ; // 0x005C
    volatile uint32_t DR0                           ; // 0x0060
    volatile uint32_t DR1                           ; // 0x0064
    volatile uint32_t DR2                           ; // 0x0068
    volatile uint32_t DR3                           ; // 0x006C
    volatile uint32_t DR4                           ; // 0x0070
    volatile uint32_t DR5                           ; // 0x0074
    volatile uint32_t DR6                           ; // 0x0078
    volatile uint32_t DR7                           ; // 0x007C
    volatile uint32_t DR8                           ; // 0x0080
    volatile uint32_t DR9                           ; // 0x0084
    volatile uint32_t DR10                          ; // 0x0088
    volatile uint32_t DR11                          ; // 0x008C
    volatile uint32_t DR12                          ; // 0x0090
    volatile uint32_t DR13                          ; // 0x0094
    volatile uint32_t DR14                          ; // 0x0098
    volatile uint32_t DR15                          ; // 0x009C
    volatile uint32_t DR16                          ; // 0x00A0
    volatile uint32_t DR17                          ; // 0x00A4
    volatile uint32_t DR18                          ; // 0x00A8
    volatile uint32_t DR19                          ; // 0x00AC
    volatile uint32_t DR20                          ; // 0x00B0
    volatile uint32_t DR21                          ; // 0x00B4
    volatile uint32_t DR22                          ; // 0x00B8
    volatile uint32_t DR23                          ; // 0x00BC
    volatile uint32_t DR24                          ; // 0x00C0
    volatile uint32_t DR25                          ; // 0x00C4
    volatile uint32_t DR26                          ; // 0x00C8
    volatile uint32_t DR27                          ; // 0x00CC
    volatile uint32_t DR28                          ; // 0x00D0
    volatile uint32_t DR29                          ; // 0x00D4
    volatile uint32_t DR30                          ; // 0x00D8
    volatile uint32_t DR31                          ; // 0x00DC
    volatile uint32_t DR32                          ; // 0x00E0
    volatile uint32_t DR33                          ; // 0x00E4
    volatile uint32_t DR34                          ; // 0x00E8
    volatile uint32_t DR35                          ; // 0x00EC
    volatile uint32_t RX_SAMPLE_DELAY               ; // 0x00F0
    volatile uint32_t SPI_CTRLR0                    ; // 0x00F4
    volatile uint32_t RESERVED0[1]; // 0x00F8 - 0x00FB
    volatile uint32_t XIP_MODE_BITS                 ; // 0x00FC
} reg_address_block_t;

/* axi_ssic_memory_map_ssic_address_block2 寄存器块 */
typedef struct
{
    volatile uint32_t XIP_INCR_INST                 ; // 0x0000
    volatile uint32_t XIP_WRAP_INST                 ; // 0x0004
    volatile uint32_t RESERVED0[3]; // 0x0008 - 0x0013
    volatile uint32_t XIP_CNT_TIME_OUT              ; // 0x0014
    volatile uint32_t RESERVED1[2]; // 0x0018 - 0x001F
    volatile uint32_t SPIDR                         ; // 0x0020
    volatile uint32_t SPIAR                         ; // 0x0024
    volatile uint32_t AXIAR0                        ; // 0x0028
    volatile uint32_t AXIAR1                        ; // 0x002C
    volatile uint32_t AXIECR                        ; // 0x0030
    volatile uint32_t DONECR                        ; // 0x0034
} reg_address_block2_t;

/* 顶层寄存器结构体 */
typedef struct
{
    reg_address_block_t ddress_block; // 0x0000 - 0x00FF
    reg_address_block2_t ddress_block2; // 0x0100 - 0x0137
} reg_axi_ssi_t;

/* CTRLR0 寄存器字段定义 - 偏移: 0x0000 */
enum CTRLR0_FIELD
{
    CTRLR0_SSI_IS_MST_MASK = 0x80000000,  // 位[31], ro, 复位值=0
    CTRLR0_SSI_IS_MST_POS = 31,
    CTRLR0_RSVD_CTRLR0_26_31_MASK = 0x7c000000,  // 位[30:26], ro, 复位值=0
    CTRLR0_RSVD_CTRLR0_26_31_POS = 26,
    CTRLR0_SPI_DWS_EN_MASK = 0x2000000,  // 位[25], ro, 复位值=0
    CTRLR0_SPI_DWS_EN_POS = 25,
    CTRLR0_SPI_HYPERBUS_EN_MASK = 0x1000000,  // 位[24], ro, 复位值=0
    CTRLR0_SPI_HYPERBUS_EN_POS = 24,
    CTRLR0_SPI_FRF_MASK = 0xc00000,  // 位[23:22], rw, 复位值=0
    CTRLR0_SPI_FRF_POS = 22,
    CTRLR0_RSVD_CTRLR0_20_21_MASK = 0x300000,  // 位[21:20], ro, 复位值=0
    CTRLR0_RSVD_CTRLR0_20_21_POS = 20,
    CTRLR0_CFS_MASK = 0xf0000,  // 位[19:16], rw, 复位值=0
    CTRLR0_CFS_POS = 16,
    CTRLR0_RSVD_CTRLR0_15_MASK = 0x8000,  // 位[15], ro, 复位值=0
    CTRLR0_RSVD_CTRLR0_15_POS = 15,
    CTRLR0_SSTE_MASK = 0x4000,  // 位[14], rw, 复位值=1
    CTRLR0_SSTE_POS = 14,
    CTRLR0_SRL_MASK = 0x2000,  // 位[13], rw, 复位值=0
    CTRLR0_SRL_POS = 13,
    CTRLR0_SLV_OE_MASK = 0x1000,  // 位[12], rw, 复位值=0
    CTRLR0_SLV_OE_POS = 12,
    CTRLR0_TMOD_MASK = 0xc00,  // 位[11:10], rw, 复位值=0
    CTRLR0_TMOD_POS = 10,
    CTRLR0_SCPOL_MASK = 0x200,  // 位[9], ro, 复位值=0
    CTRLR0_SCPOL_POS = 9,
    CTRLR0_SCPH_MASK = 0x100,  // 位[8], ro, 复位值=0
    CTRLR0_SCPH_POS = 8,
    CTRLR0_FRF_MASK = 0xc0,  // 位[7:6], ro, 复位值=0
    CTRLR0_FRF_POS = 6,
    CTRLR0_RSVD_CTRLR0_5_MASK = 0x20,  // 位[5], ro, 复位值=0
    CTRLR0_RSVD_CTRLR0_5_POS = 5,
    CTRLR0_DFS_MASK = 0x1f,  // 位[4:0], rw, 复位值=7
    CTRLR0_DFS_POS = 0,
};

/* CTRLR1 寄存器字段定义 - 偏移: 0x0004 */
enum CTRLR1_FIELD
{
    CTRLR1_RSVD_CTRLR1_MASK = 0xffff0000,  // 位[31:16], ro, 复位值=0
    CTRLR1_RSVD_CTRLR1_POS = 16,
    CTRLR1_NDF_MASK = 0xffff,  // 位[15:0], rw, 复位值=0
    CTRLR1_NDF_POS = 0,
};

/* SSIENR 寄存器字段定义 - 偏移: 0x0008 */
enum SSIENR_FIELD
{
    SSIENR_RSVD_SSIENR_MASK = 0xfffffffe,  // 位[31:1], ru, 复位值=0
    SSIENR_RSVD_SSIENR_POS = 1,
    SSIENR_SSIC_EN_MASK = 0x1,  // 位[0], other, 复位值=0
    SSIENR_SSIC_EN_POS = 0,
};

/* MWCR 寄存器字段定义 - 偏移: 0x000C */
enum MWCR_FIELD
{
    MWCR_RSVD_MWCR_MASK = 0xfffffff8,  // 位[31:3], ro, 复位值=0
    MWCR_RSVD_MWCR_POS = 3,
    MWCR_MHS_MASK = 0x4,  // 位[2], rw, 复位值=0
    MWCR_MHS_POS = 2,
    MWCR_MDD_MASK = 0x2,  // 位[1], rw, 复位值=0
    MWCR_MDD_POS = 1,
    MWCR_MWMOD_MASK = 0x1,  // 位[0], rw, 复位值=0
    MWCR_MWMOD_POS = 0,
};

/* SER 寄存器字段定义 - 偏移: 0x0010 */
enum SER_FIELD
{
    SER_RSVD_SER_MASK = 0xfffffff0,  // 位[31:4], ro, 复位值=0
    SER_RSVD_SER_POS = 4,
    SER_SER_MASK = 0xf,  // 位[3:0], rw, 复位值=0
    SER_SER_POS = 0,
};

/* BAUDR 寄存器字段定义 - 偏移: 0x0014 */
enum BAUDR_FIELD
{
    BAUDR_RSVD_BAUDR_16_31_MASK = 0xffff0000,  // 位[31:16], ro, 复位值=0
    BAUDR_RSVD_BAUDR_16_31_POS = 16,
    BAUDR_SCKDV_MASK = 0xfffe,  // 位[15:1], rw, 复位值=0
    BAUDR_SCKDV_POS = 1,
    BAUDR_RSVD_BAUDR_0_MASK = 0x1,  // 位[0], ro, 复位值=0
    BAUDR_RSVD_BAUDR_0_POS = 0,
};

/* TXFTLR 寄存器字段定义 - 偏移: 0x0018 */
enum TXFTLR_FIELD
{
    TXFTLR_RSVD_TXFTHR_MASK = 0xff000000,  // 位[31:24], ro, 复位值=0
    TXFTLR_RSVD_TXFTHR_POS = 24,
    TXFTLR_TXFTHR_MASK = 0xff0000,  // 位[23:16], rw, 复位值=0
    TXFTLR_TXFTHR_POS = 16,
    TXFTLR_RSVD_TXFTLR_MASK = 0xffe0,  // 位[15:5], ro, 复位值=0
    TXFTLR_RSVD_TXFTLR_POS = 5,
    TXFTLR_TFT_MASK = 0x1f,  // 位[4:0], rw, 复位值=0
    TXFTLR_TFT_POS = 0,
};

/* RXFTLR 寄存器字段定义 - 偏移: 0x001C */
enum RXFTLR_FIELD
{
    RXFTLR_RSVD_RXFTLR_MASK = 0xffffffe0,  // 位[31:5], ro, 复位值=0
    RXFTLR_RSVD_RXFTLR_POS = 5,
    RXFTLR_RFT_MASK = 0x1f,  // 位[4:0], rw, 复位值=0
    RXFTLR_RFT_POS = 0,
};

/* TXFLR 寄存器字段定义 - 偏移: 0x0020 */
enum TXFLR_FIELD
{
    TXFLR_RSVD_TXFLR_MASK = 0xffffffc0,  // 位[31:6], ru, 复位值=0
    TXFLR_RSVD_TXFLR_POS = 6,
    TXFLR_TXTFL_MASK = 0x3f,  // 位[5:0], ru, 复位值=0
    TXFLR_TXTFL_POS = 0,
};

/* RXFLR 寄存器字段定义 - 偏移: 0x0024 */
enum RXFLR_FIELD
{
    RXFLR_RSVD_RXFLR_MASK = 0xffffffc0,  // 位[31:6], ru, 复位值=0
    RXFLR_RSVD_RXFLR_POS = 6,
    RXFLR_RXTFL_MASK = 0x3f,  // 位[5:0], ru, 复位值=0
    RXFLR_RXTFL_POS = 0,
};

/* SR 寄存器字段定义 - 偏移: 0x0028 */
enum SR_FIELD
{
    SR_CMPLTD_DF_MASK = 0xffff8000,  // 位[31:15], ru, 复位值=0
    SR_CMPLTD_DF_POS = 15,
    SR_RSVD_SR_MASK = 0x7f80,  // 位[14:7], ru, 复位值=0
    SR_RSVD_SR_POS = 7,
    SR_DCOL_MASK = 0x40,  // 位[6], ru, 复位值=0
    SR_DCOL_POS = 6,
    SR_TXE_MASK = 0x20,  // 位[5], ru, 复位值=0
    SR_TXE_POS = 5,
    SR_RFF_MASK = 0x10,  // 位[4], ru, 复位值=0
    SR_RFF_POS = 4,
    SR_RFNE_MASK = 0x8,  // 位[3], ru, 复位值=0
    SR_RFNE_POS = 3,
    SR_TFE_MASK = 0x4,  // 位[2], ru, 复位值=1
    SR_TFE_POS = 2,
    SR_TFNF_MASK = 0x2,  // 位[1], ru, 复位值=1
    SR_TFNF_POS = 1,
    SR_BUSY_MASK = 0x1,  // 位[0], ru, 复位值=0
    SR_BUSY_POS = 0,
};

/* IMR 寄存器字段定义 - 偏移: 0x002C */
enum IMR_FIELD
{
    IMR_RSVD_12_32_IMR_MASK = 0xfffff000,  // 位[31:12], ro, 复位值=0
    IMR_RSVD_12_32_IMR_POS = 12,
    IMR_DONEM_MASK = 0x800,  // 位[11], rw, 复位值=1
    IMR_DONEM_POS = 11,
    IMR_SPITEM_MASK = 0x400,  // 位[10], ro, 复位值=0
    IMR_SPITEM_POS = 10,
    IMR_RSVD_9_IMR_MASK = 0x200,  // 位[9], ro, 复位值=0
    IMR_RSVD_9_IMR_POS = 9,
    IMR_AXIEM_MASK = 0x100,  // 位[8], rw, 复位值=1
    IMR_AXIEM_POS = 8,
    IMR_TXUIM_MASK = 0x80,  // 位[7], rw, 复位值=1
    IMR_TXUIM_POS = 7,
    IMR_XRXOIM_MASK = 0x40,  // 位[6], ro, 复位值=0
    IMR_XRXOIM_POS = 6,
    IMR_MSTIM_MASK = 0x20,  // 位[5], rw, 复位值=1
    IMR_MSTIM_POS = 5,
    IMR_RXFIM_MASK = 0x10,  // 位[4], rw, 复位值=1
    IMR_RXFIM_POS = 4,
    IMR_RXOIM_MASK = 0x8,  // 位[3], rw, 复位值=1
    IMR_RXOIM_POS = 3,
    IMR_RXUIM_MASK = 0x4,  // 位[2], rw, 复位值=1
    IMR_RXUIM_POS = 2,
    IMR_TXOIM_MASK = 0x2,  // 位[1], rw, 复位值=1
    IMR_TXOIM_POS = 1,
    IMR_TXEIM_MASK = 0x1,  // 位[0], rw, 复位值=1
    IMR_TXEIM_POS = 0,
};

/* ISR 寄存器字段定义 - 偏移: 0x0030 */
enum ISR_FIELD
{
    ISR_RSVD_12_32_RISR_MASK = 0xfffff000,  // 位[31:12], ru, 复位值=0
    ISR_RSVD_12_32_RISR_POS = 12,
    ISR_DONES_MASK = 0x800,  // 位[11], ru, 复位值=0
    ISR_DONES_POS = 11,
    ISR_SPITES_MASK = 0x400,  // 位[10], ru, 复位值=0
    ISR_SPITES_POS = 10,
    ISR_RSVD_9_RISR_MASK = 0x200,  // 位[9], ru, 复位值=0
    ISR_RSVD_9_RISR_POS = 9,
    ISR_AXIES_MASK = 0x100,  // 位[8], ru, 复位值=1
    ISR_AXIES_POS = 8,
    ISR_TXUIS_MASK = 0x80,  // 位[7], ru, 复位值=1
    ISR_TXUIS_POS = 7,
    ISR_XRXOIS_MASK = 0x40,  // 位[6], ru, 复位值=0
    ISR_XRXOIS_POS = 6,
    ISR_MSTIS_MASK = 0x20,  // 位[5], ru, 复位值=0
    ISR_MSTIS_POS = 5,
    ISR_RXFIS_MASK = 0x10,  // 位[4], ru, 复位值=0
    ISR_RXFIS_POS = 4,
    ISR_RXOIS_MASK = 0x8,  // 位[3], ru, 复位值=0
    ISR_RXOIS_POS = 3,
    ISR_RXUIS_MASK = 0x4,  // 位[2], ru, 复位值=0
    ISR_RXUIS_POS = 2,
    ISR_TXOIS_MASK = 0x2,  // 位[1], ru, 复位值=0
    ISR_TXOIS_POS = 1,
    ISR_TXEIS_MASK = 0x1,  // 位[0], ru, 复位值=0
    ISR_TXEIS_POS = 0,
};

/* RISR 寄存器字段定义 - 偏移: 0x0034 */
enum RISR_FIELD
{
    RISR_RSVD_12_32_RISR_MASK = 0xfffff000,  // 位[31:12], ru, 复位值=0
    RISR_RSVD_12_32_RISR_POS = 12,
    RISR_DONER_MASK = 0x800,  // 位[11], ru, 复位值=0
    RISR_DONER_POS = 11,
    RISR_SPITER_MASK = 0x400,  // 位[10], ru, 复位值=0
    RISR_SPITER_POS = 10,
    RISR_RSVD_9_RISR_MASK = 0x200,  // 位[9], ru, 复位值=0
    RISR_RSVD_9_RISR_POS = 9,
    RISR_AXIER_MASK = 0x100,  // 位[8], ru, 复位值=0
    RISR_AXIER_POS = 8,
    RISR_TXUIR_MASK = 0x80,  // 位[7], ru, 复位值=0
    RISR_TXUIR_POS = 7,
    RISR_XRXOIR_MASK = 0x40,  // 位[6], ru, 复位值=0
    RISR_XRXOIR_POS = 6,
    RISR_MSTIR_MASK = 0x20,  // 位[5], ru, 复位值=0
    RISR_MSTIR_POS = 5,
    RISR_RXFIR_MASK = 0x10,  // 位[4], ru, 复位值=0
    RISR_RXFIR_POS = 4,
    RISR_RXOIR_MASK = 0x8,  // 位[3], ru, 复位值=0
    RISR_RXOIR_POS = 3,
    RISR_RXUIR_MASK = 0x4,  // 位[2], ru, 复位值=0
    RISR_RXUIR_POS = 2,
    RISR_TXOIR_MASK = 0x2,  // 位[1], ru, 复位值=0
    RISR_TXOIR_POS = 1,
    RISR_TXEIR_MASK = 0x1,  // 位[0], ru, 复位值=0
    RISR_TXEIR_POS = 0,
};

/* TXEICR 寄存器字段定义 - 偏移: 0x0038 */
enum TXEICR_FIELD
{
    TXEICR_RSVD_TXEICR_MASK = 0xfffffffe,  // 位[31:1], ru, 复位值=0
    TXEICR_RSVD_TXEICR_POS = 1,
    TXEICR_TXEICR_MASK = 0x1,  // 位[0], ru, 复位值=0
    TXEICR_TXEICR_POS = 0,
};

/* RXOICR 寄存器字段定义 - 偏移: 0x003C */
enum RXOICR_FIELD
{
    RXOICR_RSVD_RXOICR_MASK = 0xfffffffe,  // 位[31:1], ru, 复位值=0
    RXOICR_RSVD_RXOICR_POS = 1,
    RXOICR_RXOICR_MASK = 0x1,  // 位[0], ru, 复位值=0
    RXOICR_RXOICR_POS = 0,
};

/* RXUICR 寄存器字段定义 - 偏移: 0x0040 */
enum RXUICR_FIELD
{
    RXUICR_RSVD_RXUICR_MASK = 0xfffffffe,  // 位[31:1], ru, 复位值=0
    RXUICR_RSVD_RXUICR_POS = 1,
    RXUICR_RXUICR_MASK = 0x1,  // 位[0], ru, 复位值=0
    RXUICR_RXUICR_POS = 0,
};

/* MSTICR 寄存器字段定义 - 偏移: 0x0044 */
enum MSTICR_FIELD
{
    MSTICR_RSVD_MSTICR_MASK = 0xfffffffe,  // 位[31:1], ru, 复位值=0
    MSTICR_RSVD_MSTICR_POS = 1,
    MSTICR_MSTICR_MASK = 0x1,  // 位[0], ru, 复位值=0
    MSTICR_MSTICR_POS = 0,
};

/* ICR 寄存器字段定义 - 偏移: 0x0048 */
enum ICR_FIELD
{
    ICR_RSVD_ICR_MASK = 0xfffffffe,  // 位[31:1], ru, 复位值=0
    ICR_RSVD_ICR_POS = 1,
    ICR_ICR_MASK = 0x1,  // 位[0], ru, 复位值=0
    ICR_ICR_POS = 0,
};

/* DMACR 寄存器字段定义 - 偏移: 0x004C */
enum DMACR_FIELD
{
    DMACR_RSVD_DMACR_MASK = 0xfff80000,  // 位[31:19], ro, 复位值=0
    DMACR_RSVD_DMACR_POS = 19,
    DMACR_AID_MASK = 0x78000,  // 位[18:15], rw, 复位值=0
    DMACR_AID_POS = 15,
    DMACR_APROT_MASK = 0x7000,  // 位[14:12], rw, 复位值=0
    DMACR_APROT_POS = 12,
    DMACR_ACACHE_MASK = 0xf00,  // 位[11:8], rw, 复位值=0
    DMACR_ACACHE_POS = 8,
    DMACR_RSVD_DMACR7_MASK = 0x80,  // 位[7], ro, 复位值=0
    DMACR_RSVD_DMACR7_POS = 7,
    DMACR_AINC_MASK = 0x40,  // 位[6], rw, 复位值=0
    DMACR_AINC_POS = 6,
    DMACR_RSVD_DMACR5_MASK = 0x20,  // 位[5], ro, 复位值=0
    DMACR_RSVD_DMACR5_POS = 5,
    DMACR_ATW_MASK = 0x18,  // 位[4:3], rw, 复位值=0
    DMACR_ATW_POS = 3,
    DMACR_IDMAE_MASK = 0x4,  // 位[2], rw, 复位值=0
    DMACR_IDMAE_POS = 2,
    DMACR_TDMAE_MASK = 0x2,  // 位[1], ro, 复位值=0
    DMACR_TDMAE_POS = 1,
    DMACR_RDMAE_MASK = 0x1,  // 位[0], ro, 复位值=0
    DMACR_RDMAE_POS = 0,
};

/* AXIAWLEN 寄存器字段定义 - 偏移: 0x0050 */
enum AXIAWLEN_FIELD
{
    AXIAWLEN_RSVD_AXIAWLEN2_MASK = 0xffff0000,  // 位[31:16], ro, 复位值=0
    AXIAWLEN_RSVD_AXIAWLEN2_POS = 16,
    AXIAWLEN_AWLEN_MASK = 0xff00,  // 位[15:8], rw, 复位值=7
    AXIAWLEN_AWLEN_POS = 8,
    AXIAWLEN_RSVD_AXIAWLEN_MASK = 0xff,  // 位[7:0], ro, 复位值=0
    AXIAWLEN_RSVD_AXIAWLEN_POS = 0,
};

/* AXIARLEN 寄存器字段定义 - 偏移: 0x0054 */
enum AXIARLEN_FIELD
{
    AXIARLEN_RSVD_AXIARLEN2_MASK = 0xffff0000,  // 位[31:16], ro, 复位值=0
    AXIARLEN_RSVD_AXIARLEN2_POS = 16,
    AXIARLEN_ARLEN_MASK = 0xff00,  // 位[15:8], rw, 复位值=7
    AXIARLEN_ARLEN_POS = 8,
    AXIARLEN_RSVD_AXIARLEN_MASK = 0xff,  // 位[7:0], ro, 复位值=0
    AXIARLEN_RSVD_AXIARLEN_POS = 0,
};

/* IDR 寄存器字段定义 - 偏移: 0x0058 */
enum IDR_FIELD
{
    IDR_IDCODE_MASK = 0xffffffff,  // 位[31:0], ro, 复位值=ffffffff
    IDR_IDCODE_POS = 0,
};

/* SSIC_VERSION_ID 寄存器字段定义 - 偏移: 0x005C */
enum SSIC_VERSION_ID_FIELD
{
    SSIC_VERSION_ID_SSIC_COMP_VERSION_MASK = 0xffffffff,  // 位[31:0], ro, 复位值=3130332a
    SSIC_VERSION_ID_SSIC_COMP_VERSION_POS = 0,
};

/* DR0 寄存器字段定义 - 偏移: 0x0060 */
enum DR0_FIELD
{
    DR0_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR0_DR_POS = 0,
};

/* DR1 寄存器字段定义 - 偏移: 0x0064 */
enum DR1_FIELD
{
    DR1_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR1_DR_POS = 0,
};

/* DR2 寄存器字段定义 - 偏移: 0x0068 */
enum DR2_FIELD
{
    DR2_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR2_DR_POS = 0,
};

/* DR3 寄存器字段定义 - 偏移: 0x006C */
enum DR3_FIELD
{
    DR3_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR3_DR_POS = 0,
};

/* DR4 寄存器字段定义 - 偏移: 0x0070 */
enum DR4_FIELD
{
    DR4_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR4_DR_POS = 0,
};

/* DR5 寄存器字段定义 - 偏移: 0x0074 */
enum DR5_FIELD
{
    DR5_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR5_DR_POS = 0,
};

/* DR6 寄存器字段定义 - 偏移: 0x0078 */
enum DR6_FIELD
{
    DR6_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR6_DR_POS = 0,
};

/* DR7 寄存器字段定义 - 偏移: 0x007C */
enum DR7_FIELD
{
    DR7_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR7_DR_POS = 0,
};

/* DR8 寄存器字段定义 - 偏移: 0x0080 */
enum DR8_FIELD
{
    DR8_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR8_DR_POS = 0,
};

/* DR9 寄存器字段定义 - 偏移: 0x0084 */
enum DR9_FIELD
{
    DR9_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR9_DR_POS = 0,
};

/* DR10 寄存器字段定义 - 偏移: 0x0088 */
enum DR10_FIELD
{
    DR10_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR10_DR_POS = 0,
};

/* DR11 寄存器字段定义 - 偏移: 0x008C */
enum DR11_FIELD
{
    DR11_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR11_DR_POS = 0,
};

/* DR12 寄存器字段定义 - 偏移: 0x0090 */
enum DR12_FIELD
{
    DR12_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR12_DR_POS = 0,
};

/* DR13 寄存器字段定义 - 偏移: 0x0094 */
enum DR13_FIELD
{
    DR13_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR13_DR_POS = 0,
};

/* DR14 寄存器字段定义 - 偏移: 0x0098 */
enum DR14_FIELD
{
    DR14_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR14_DR_POS = 0,
};

/* DR15 寄存器字段定义 - 偏移: 0x009C */
enum DR15_FIELD
{
    DR15_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR15_DR_POS = 0,
};

/* DR16 寄存器字段定义 - 偏移: 0x00A0 */
enum DR16_FIELD
{
    DR16_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR16_DR_POS = 0,
};

/* DR17 寄存器字段定义 - 偏移: 0x00A4 */
enum DR17_FIELD
{
    DR17_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR17_DR_POS = 0,
};

/* DR18 寄存器字段定义 - 偏移: 0x00A8 */
enum DR18_FIELD
{
    DR18_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR18_DR_POS = 0,
};

/* DR19 寄存器字段定义 - 偏移: 0x00AC */
enum DR19_FIELD
{
    DR19_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR19_DR_POS = 0,
};

/* DR20 寄存器字段定义 - 偏移: 0x00B0 */
enum DR20_FIELD
{
    DR20_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR20_DR_POS = 0,
};

/* DR21 寄存器字段定义 - 偏移: 0x00B4 */
enum DR21_FIELD
{
    DR21_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR21_DR_POS = 0,
};

/* DR22 寄存器字段定义 - 偏移: 0x00B8 */
enum DR22_FIELD
{
    DR22_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR22_DR_POS = 0,
};

/* DR23 寄存器字段定义 - 偏移: 0x00BC */
enum DR23_FIELD
{
    DR23_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR23_DR_POS = 0,
};

/* DR24 寄存器字段定义 - 偏移: 0x00C0 */
enum DR24_FIELD
{
    DR24_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR24_DR_POS = 0,
};

/* DR25 寄存器字段定义 - 偏移: 0x00C4 */
enum DR25_FIELD
{
    DR25_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR25_DR_POS = 0,
};

/* DR26 寄存器字段定义 - 偏移: 0x00C8 */
enum DR26_FIELD
{
    DR26_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR26_DR_POS = 0,
};

/* DR27 寄存器字段定义 - 偏移: 0x00CC */
enum DR27_FIELD
{
    DR27_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR27_DR_POS = 0,
};

/* DR28 寄存器字段定义 - 偏移: 0x00D0 */
enum DR28_FIELD
{
    DR28_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR28_DR_POS = 0,
};

/* DR29 寄存器字段定义 - 偏移: 0x00D4 */
enum DR29_FIELD
{
    DR29_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR29_DR_POS = 0,
};

/* DR30 寄存器字段定义 - 偏移: 0x00D8 */
enum DR30_FIELD
{
    DR30_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR30_DR_POS = 0,
};

/* DR31 寄存器字段定义 - 偏移: 0x00DC */
enum DR31_FIELD
{
    DR31_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR31_DR_POS = 0,
};

/* DR32 寄存器字段定义 - 偏移: 0x00E0 */
enum DR32_FIELD
{
    DR32_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR32_DR_POS = 0,
};

/* DR33 寄存器字段定义 - 偏移: 0x00E4 */
enum DR33_FIELD
{
    DR33_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR33_DR_POS = 0,
};

/* DR34 寄存器字段定义 - 偏移: 0x00E8 */
enum DR34_FIELD
{
    DR34_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR34_DR_POS = 0,
};

/* DR35 寄存器字段定义 - 偏移: 0x00EC */
enum DR35_FIELD
{
    DR35_DR_MASK = 0xffffffff,  // 位[31:0], other, 复位值=0
    DR35_DR_POS = 0,
};

/* RX_SAMPLE_DELAY 寄存器字段定义 - 偏移: 0x00F0 */
enum RX_SAMPLE_DELAY_FIELD
{
    RX_SAMPLE_DELAY_RSVD1_RX_SAMPLE_DLY_MASK = 0xfffe0000,  // 位[31:17], ro, 复位值=0
    RX_SAMPLE_DELAY_RSVD1_RX_SAMPLE_DLY_POS = 17,
    RX_SAMPLE_DELAY_SE_MASK = 0x10000,  // 位[16], rw, 复位值=0
    RX_SAMPLE_DELAY_SE_POS = 16,
    RX_SAMPLE_DELAY_RSVD0_RX_SAMPLE_DLY_MASK = 0xff00,  // 位[15:8], ro, 复位值=0
    RX_SAMPLE_DELAY_RSVD0_RX_SAMPLE_DLY_POS = 8,
    RX_SAMPLE_DELAY_RSD_MASK = 0xff,  // 位[7:0], rw, 复位值=0
    RX_SAMPLE_DELAY_RSD_POS = 0,
};

/* SPI_CTRLR0 寄存器字段定义 - 偏移: 0x00F4 */
enum SPI_CTRLR0_FIELD
{
    SPI_CTRLR0_RSVD_SPI_CTRLR0_MASK = 0x80000000,  // 位[31], ro, 复位值=0
    SPI_CTRLR0_RSVD_SPI_CTRLR0_POS = 31,
    SPI_CTRLR0_CLK_STRETCH_EN_MASK = 0x40000000,  // 位[30], rw, 复位值=0
    SPI_CTRLR0_CLK_STRETCH_EN_POS = 30,
    SPI_CTRLR0_XIP_PREFETCH_EN_MASK = 0x20000000,  // 位[29], ro, 复位值=0
    SPI_CTRLR0_XIP_PREFETCH_EN_POS = 29,
    SPI_CTRLR0_RSVD_SPI_CTRLR0_28_MASK = 0x10000000,  // 位[28], ro, 复位值=0
    SPI_CTRLR0_RSVD_SPI_CTRLR0_28_POS = 28,
    SPI_CTRLR0_XIP_MBL_MASK = 0xc000000,  // 位[27:26], rw, 复位值=2
    SPI_CTRLR0_XIP_MBL_POS = 26,
    SPI_CTRLR0_SPI_RXDS_SIG_EN_MASK = 0x2000000,  // 位[25], ro, 复位值=0
    SPI_CTRLR0_SPI_RXDS_SIG_EN_POS = 25,
    SPI_CTRLR0_SPI_DM_EN_MASK = 0x1000000,  // 位[24], ro, 复位值=0
    SPI_CTRLR0_SPI_DM_EN_POS = 24,
    SPI_CTRLR0_RSVD_SPI_CTRLR0_22_23_MASK = 0xc00000,  // 位[23:22], ro, 复位值=0
    SPI_CTRLR0_RSVD_SPI_CTRLR0_22_23_POS = 22,
    SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN_MASK = 0x200000,  // 位[21], rw, 复位值=0
    SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN_POS = 21,
    SPI_CTRLR0_XIP_INST_EN_MASK = 0x100000,  // 位[20], rw, 复位值=0
    SPI_CTRLR0_XIP_INST_EN_POS = 20,
    SPI_CTRLR0_XIP_DFS_HC_MASK = 0x80000,  // 位[19], rw, 复位值=0
    SPI_CTRLR0_XIP_DFS_HC_POS = 19,
    SPI_CTRLR0_SPI_RXDS_EN_MASK = 0x40000,  // 位[18], ro, 复位值=0
    SPI_CTRLR0_SPI_RXDS_EN_POS = 18,
    SPI_CTRLR0_INST_DDR_EN_MASK = 0x20000,  // 位[17], ro, 复位值=0
    SPI_CTRLR0_INST_DDR_EN_POS = 17,
    SPI_CTRLR0_SPI_DDR_EN_MASK = 0x10000,  // 位[16], ro, 复位值=0
    SPI_CTRLR0_SPI_DDR_EN_POS = 16,
    SPI_CTRLR0_WAIT_CYCLES_MASK = 0xf800,  // 位[15:11], rw, 复位值=0
    SPI_CTRLR0_WAIT_CYCLES_POS = 11,
    SPI_CTRLR0_RSVD_SPI_CTRLR0_10_MASK = 0x400,  // 位[10], ro, 复位值=0
    SPI_CTRLR0_RSVD_SPI_CTRLR0_10_POS = 10,
    SPI_CTRLR0_INST_L_MASK = 0x300,  // 位[9:8], rw, 复位值=2
    SPI_CTRLR0_INST_L_POS = 8,
    SPI_CTRLR0_XIP_MD_BIT_EN_MASK = 0x80,  // 位[7], rw, 复位值=0
    SPI_CTRLR0_XIP_MD_BIT_EN_POS = 7,
    SPI_CTRLR0_RSVD_SPI_CTRLR0_6_MASK = 0x40,  // 位[6], ro, 复位值=0
    SPI_CTRLR0_RSVD_SPI_CTRLR0_6_POS = 6,
    SPI_CTRLR0_ADDR_L_MASK = 0x3c,  // 位[5:2], rw, 复位值=0
    SPI_CTRLR0_ADDR_L_POS = 2,
    SPI_CTRLR0_TRANS_TYPE_MASK = 0x3,  // 位[1:0], rw, 复位值=0
    SPI_CTRLR0_TRANS_TYPE_POS = 0,
};

/* XIP_MODE_BITS 寄存器字段定义 - 偏移: 0x00FC */
enum XIP_MODE_BITS_FIELD
{
    XIP_MODE_BITS_RSVD_XIP_MD_BITS_MASK = 0xffff0000,  // 位[31:16], ru, 复位值=0
    XIP_MODE_BITS_RSVD_XIP_MD_BITS_POS = 16,
    XIP_MODE_BITS_XIP_MD_BITS_MASK = 0xffff,  // 位[15:0], other, 复位值=0
    XIP_MODE_BITS_XIP_MD_BITS_POS = 0,
};

/* XIP_INCR_INST 寄存器字段定义 - 偏移: 0x0000 */
enum XIP_INCR_INST_FIELD
{
    XIP_INCR_INST_RSVD_INCR_INST_MASK = 0xffff0000,  // 位[31:16], ro, 复位值=0
    XIP_INCR_INST_RSVD_INCR_INST_POS = 16,
    XIP_INCR_INST_INCR_INST_MASK = 0xffff,  // 位[15:0], rw, 复位值=0
    XIP_INCR_INST_INCR_INST_POS = 0,
};

/* XIP_WRAP_INST 寄存器字段定义 - 偏移: 0x0004 */
enum XIP_WRAP_INST_FIELD
{
    XIP_WRAP_INST_RSVD_WRAP_INST_MASK = 0xffff0000,  // 位[31:16], ro, 复位值=0
    XIP_WRAP_INST_RSVD_WRAP_INST_POS = 16,
    XIP_WRAP_INST_WRAP_INST_MASK = 0xffff,  // 位[15:0], rw, 复位值=0
    XIP_WRAP_INST_WRAP_INST_POS = 0,
};

/* XIP_CNT_TIME_OUT 寄存器字段定义 - 偏移: 0x0014 */
enum XIP_CNT_TIME_OUT_FIELD
{
    XIP_CNT_TIME_OUT_RSVD_XTOC_MASK = 0xffffff00,  // 位[31:8], ru, 复位值=0
    XIP_CNT_TIME_OUT_RSVD_XTOC_POS = 8,
    XIP_CNT_TIME_OUT_XTOC_MASK = 0xff,  // 位[7:0], other, 复位值=0
    XIP_CNT_TIME_OUT_XTOC_POS = 0,
};

/* SPIDR 寄存器字段定义 - 偏移: 0x0020 */
enum SPIDR_FIELD
{
    SPIDR_RSVD_SPIDR_MASK = 0xffff0000,  // 位[31:16], ro, 复位值=0
    SPIDR_RSVD_SPIDR_POS = 16,
    SPIDR_SPI_INST_MASK = 0xffff,  // 位[15:0], rw, 复位值=0
    SPIDR_SPI_INST_POS = 0,
};

/* SPIAR 寄存器字段定义 - 偏移: 0x0024 */
enum SPIAR_FIELD
{
    SPIAR_SDAR_MASK = 0xffffffff,  // 位[31:0], rw, 复位值=0
    SPIAR_SDAR_POS = 0,
};

/* AXIAR0 寄存器字段定义 - 偏移: 0x0028 */
enum AXIAR0_FIELD
{
    AXIAR0_AXIAR_0_31_MASK = 0xffffffff,  // 位[31:0], rw, 复位值=0
    AXIAR0_AXIAR_0_31_POS = 0,
};

/* AXIAR1 寄存器字段定义 - 偏移: 0x002C */
enum AXIAR1_FIELD
{
    AXIAR1_RSVD_AXIAR1_MASK = 0xfffffffc,  // 位[31:2], ro, 复位值=0
    AXIAR1_RSVD_AXIAR1_POS = 2,
    AXIAR1_AXIAR_32_63_MASK = 0x3,  // 位[1:0], rw, 复位值=0
    AXIAR1_AXIAR_32_63_POS = 0,
};

/* AXIECR 寄存器字段定义 - 偏移: 0x0030 */
enum AXIECR_FIELD
{
    AXIECR_RSVD_AXIECR_MASK = 0xfffffffe,  // 位[31:1], ru, 复位值=0
    AXIECR_RSVD_AXIECR_POS = 1,
    AXIECR_AXIECR_MASK = 0x1,  // 位[0], ru, 复位值=0
    AXIECR_AXIECR_POS = 0,
};

/* DONECR 寄存器字段定义 - 偏移: 0x0034 */
enum DONECR_FIELD
{
    DONECR_RSVD_DONECR_MASK = 0xfffffffe,  // 位[31:1], ru, 复位值=0
    DONECR_RSVD_DONECR_POS = 1,
    DONECR_DONECR_MASK = 0x1,  // 位[0], ru, 复位值=0
    DONECR_DONECR_POS = 0,
};

#endif /* __REG_SSIV2_TYPE_H__ */
