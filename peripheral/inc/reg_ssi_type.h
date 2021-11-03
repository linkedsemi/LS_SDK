#ifndef REG_SSI_TYPE_H_
#define REG_SSI_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t CTRLR0;
    volatile uint32_t CTRLR1;
    volatile uint32_t SSIENR;
    volatile uint32_t MWCR;
    volatile uint32_t SER;
    volatile uint32_t BAUDR;
    volatile uint32_t TXFTLR;
    volatile uint32_t RXFTLR;
    volatile uint32_t TXFLR;
    volatile uint32_t RXFLR;
    volatile uint32_t SR;
    volatile uint32_t IMR;
    volatile uint32_t ISR;
    volatile uint32_t RISR;
    volatile uint32_t TXOICR;
    volatile uint32_t RXOICR;
    volatile uint32_t RXUICR;
    volatile uint32_t MSTICR;
    volatile uint32_t ICR;
    volatile uint32_t DMACR;
    volatile uint32_t DMATDLR;
    volatile uint32_t DMARDLR;
    volatile uint32_t IDR;
    volatile uint32_t SSI_COMP_VERSION;
    volatile uint32_t DR;
    volatile uint32_t reserved0[34];
    volatile uint32_t DR_REVERSED;
    volatile uint32_t RXSAMPLE_DLY;
    volatile uint32_t SPI_CTRLR0;
}reg_ssi_t;

enum SSI_CTRLR0_FIELD
{
    SSI_SPI_FRF_MASK = 0x600000,
    SSI_SPI_FRF_POS = 21,
    SSI_DFS_MASK = 0x1f0000,
    SSI_DFS_POS = 16,
    SSI_CFS_MASK = 0xf000,
    SSI_CFS_POS = 12,
    SSI_SRL_MASK = 0x800,
    SSI_SRL_POS = 11,
    SSI_SLV_OE_MASK = 0x400,
    SSI_SLV_OE_POS = 10,
    SSI_TMOD_MASK = 0x300,
    SSI_TMOD_POS = 8,
    SSI_SCPOL_MASK = 0x80,
    SSI_SCPOL_POS = 7,
    SSI_SCPH_MASK = 0x40,
    SSI_SCPH_POS = 6,
    SSI_FRF_MASK = 0x30,
    SSI_FRF_POS = 4,
};

enum SSI_CTRLR1_FIELD
{
    SSI_NDF_MASK = 0xffff,
    SSI_NDF_POS = 0,
};

enum SSI_SSIENR_FIELD
{
    SSI_SSI_EN_MASK = 0x1,
    SSI_SSI_EN_POS = 0,
};

enum SSI_MWCR_FIELD
{
    SSI_MHS_MASK = 0x4,
    SSI_MHS_POS = 2,
    SSI_MOD_MASK = 0x2,
    SSI_MOD_POS = 1,
    SSI_MWMOD_MASK = 0x1,
    SSI_MWMOD_POS = 0,
};

enum SSI_SER_FIELD
{
    SSI_SER_MASK = 0x1,
    SSI_SER_POS = 0,
};

enum SSI_BAUDR_FIELD
{
    SSI_SCKDV_MASK = 0xffff,
    SSI_SCKDV_POS = 0,
};

enum SSI_TXFTLR_FIELD
{
    SSI_TFT_MASK = 0x3f,
    SSI_TFT_POS = 0,
};

enum SSI_RXFTLR_FIELD
{
    SSI_RFT_MASK = 0x3f,
    SSI_RFT_POS = 0,
};

enum SSI_TXFLR_FIELD
{
    SSI_TXTFL_MASK = 0x7f,
    SSI_TXTFL_POS = 0,
};

enum SSI_RXFLR_FIELD
{
    SSI_RXTFL_MASK = 0x7f,
    SSI_RXTFL_POS = 0,
};

enum SSI_SR_FIELD
{
    SSI_DCOL_MASK = 0x40,
    SSI_DCOL_POS = 6,
    SSI_TXE_MASK = 0x20,
    SSI_TXE_POS = 5,
    SSI_RFF_MASK = 0x10,
    SSI_RFF_POS = 4,
    SSI_RFNE_MASK = 0x8,
    SSI_RFNE_POS = 3,
    SSI_TFE_MASK = 0x4,
    SSI_TFE_POS = 2,
    SSI_TFNF_MASK = 0x2,
    SSI_TFNF_POS = 1,
    SSI_BUSY_MASK = 0x1,
    SSI_BUSY_POS = 0,
};

enum SSI_IMR_FIELD
{
    SSI_MSTIM_MASK = 0x20,
    SSI_MSTIM_POS = 5,
    SSI_RXFIM_MASK = 0x10,
    SSI_RXFIM_POS = 4,
    SSI_RXOIM_MASK = 0x8,
    SSI_RXOIM_POS = 3,
    SSI_RXUIM_MASK = 0x4,
    SSI_RXUIM_POS = 2,
    SSI_TXOIM_MASK = 0x2,
    SSI_TXOIM_POS = 1,
    SSI_TXEIM_MASK = 0x1,
    SSI_TXEIM_POS = 0,
};

enum SSI_ISR_FIELD
{
    SSI_MSTIS_MASK = 0x20,
    SSI_MSTIS_POS = 5,
    SSI_RXFIS_MASK = 0x10,
    SSI_RXFIS_POS = 4,
    SSI_RXOIS_MASK = 0x8,
    SSI_RXOIS_POS = 3,
    SSI_RXUIS_MASK = 0x4,
    SSI_RXUIS_POS = 2,
    SSI_TXOIS_MASK = 0x2,
    SSI_TXOIS_POS = 1,
    SSI_TXEIS_MASK = 0x1,
    SSI_TXEIS_POS = 0,
};

enum SSI_RISR_FIELD
{
    SSI_MSTIR_MASK = 0x20,
    SSI_MSTIR_POS = 5,
    SSI_RXFIR_MASK = 0x10,
    SSI_RXFIR_POS = 4,
    SSI_RXOIR_MASK = 0x8,
    SSI_RXOIR_POS = 3,
    SSI_RXUIR_MASK = 0x4,
    SSI_RXUIR_POS = 2,
    SSI_TXOIR_MASK = 0x2,
    SSI_TXOIR_POS = 1,
    SSI_TXEIR_MASK = 0x1,
    SSI_TXEIR_POS = 0,
};

enum SSI_TXOICR_FIELD
{
    SSI_TXOICR_MASK = 0x1,
    SSI_TXOICR_POS = 0,
};

enum SSI_RXOICR_FIELD
{
    SSI_RXOICR_MASK = 0x1,
    SSI_RXOICR_POS = 0,
};

enum SSI_RXUICR_FIELD
{
    SSI_RXUICR_MASK = 0x1,
    SSI_RXUICR_POS = 0,
};

enum SSI_MSTICR_FIELD
{
    SSI_MSTICR_MASK = 0x1,
    SSI_MSTICR_POS = 0,
};

enum SSI_ICR_FIELD
{
    SSI_ICR_MASK = 0x1,
    SSI_ICR_POS = 0,
};

enum SSI_DMACR_FIELD
{
    SSI_TDMAE_MASK = 0x2,
    SSI_TDMAE_POS = 1,
    SSI_RDMAE_MASK = 0x1,
    SSI_RDMAE_POS = 0,
};

enum SSI_DMATDLR_FIELD
{
    SSI_DMATDL_MASK = 0x3f,
    SSI_DMATDL_POS = 0,
};

enum SSI_DMARDLR_FIELD
{
    SSI_DMARDL_MASK = 0x3f,
    SSI_DMARDL_POS = 0,
};

enum SSI_IDR_FIELD
{
    SSI_IDCODE_MASK = (int)0xffffffffL,
    SSI_IDCODE_POS = 0,
};

enum SSI_SSI_COMP_VERSION_FIELD
{
    SSI_SSI_COMP_VERSION_MASK = (int)0xffffffffL,
    SSI_SSI_COMP_VERSION_POS = 0,
};

enum SSI_DR_FIELD
{
    SSI_DR_MASK = (int)0xffffffffL,
    SSI_DR_POS = 0,
};

enum SSI_DR_REVERSED_FIELD
{
    SSI_DR_REVERSED_MASK = (int)0xffffffffL,
    SSI_DR_REVERSED_POS = 0,
};

enum SSI_RXSAMPLE_DLY_FIELD
{
    SSI_RSD_MASK = 0xff,
    SSI_RSD_POS = 0,
};

enum SSI_SPI_CTRLR0_FIELD
{
    SSI_WAIT_CYCLES_MASK = 0x7800,
    SSI_WAIT_CYCLES_POS = 11,
    SSI_INST_L_MASK = 0x300,
    SSI_INST_L_POS = 8,
    SSI_ADDR_L_MASK = 0x3c,
    SSI_ADDR_L_POS = 2,
    SSI_TRANS_TYPE_MASK = 0x3,
    SSI_TRANS_TYPE_POS = 0,
};

#endif
