#ifndef REG_SPI_TYPE_H_
#define REG_SPI_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;
    volatile uint32_t IER;
    volatile uint32_t IDR;
    volatile uint32_t IVS;
    volatile uint32_t RIF;
    volatile uint32_t IFM;
    volatile uint32_t ICR;
}reg_spi_t;

enum SPI_REG_CR1_FIELD
{
    SPI_CR1_CPHA_MASK = 0x1,
    SPI_CR1_CPHA_POS = 0,
    SPI_CR1_CPOL_MASK = 0x2,
    SPI_CR1_CPOL_POS = 1,
    SPI_CR1_MSTR_MASK = 0x4,
    SPI_CR1_MSTR_POS = 2,
    SPI_CR1_BR_MASK = 0x38,
    SPI_CR1_BR_POS = 3,
    SPI_CR1_SPE_MASK = 0x40,
    SPI_CR1_SPE_POS = 6,
    SPI_CR1_LSBFIRST_MASK = 0x80,
    SPI_CR1_LSBFIRST_POS = 7,
    SPI_CR1_SSI_MASK = 0x100,
    SPI_CR1_SSI_POS = 8,
    SPI_CR1_SSM_MASK = 0x200,
    SPI_CR1_SSM_POS = 9,
    SPI_CR1_RXONLY_MASK = 0x400,
    SPI_CR1_RXONLY_POS = 10,
    SPI_CR1_CRCL_MASK = 0x800,
    SPI_CR1_CRCL_POS = 11,
    SPI_CR1_CRCNEXT_MASK = 0x1000,
    SPI_CR1_CRCNEXT_POS = 12,
    SPI_CR1_CRCEN_MASK = 0x2000,
    SPI_CR1_CRCEN_POS = 13,
    SPI_CR1_BIDIOE_MASK = 0x4000,
    SPI_CR1_BIDIOE_POS = 14,
    SPI_CR1_BIDIMODE_MASK = 0x8000,
    SPI_CR1_BIDIMODE_POS = 15,
};

enum SPI_REG_CR2_FIELD
{
    SPI_CR2_RXDMAEN_MASK = 0x1,
    SPI_CR2_RXDMAEN_POS = 0,
    SPI_CR2_TXDMAEN_MASK = 0x2,
    SPI_CR2_TXDMAEN_POS = 1,
    SPI_CR2_SSOE_MASK = 0x4,
    SPI_CR2_SSOE_POS = 2,
    SPI_CR2_NSSP_MASK = 0x8,
    SPI_CR2_NSSP_POS = 3,
    SPI_CR2_FRF_MASK = 0x10,
    SPI_CR2_FRF_POS = 4,
    SPI_CR2_DS_MASK = 0xF00,
    SPI_CR2_DS_POS = 8,
    SPI_CR2_TXFTH_MASK = 0xf0000,
    SPI_CR2_TXFTH_POS = 16,
    SPI_CR2_RXFTH_MASK = 0xf000000,
    SPI_CR2_RXFTH_POS = 24,	
};
enum SPI_REG_SR_FIELD
{
    SPI_SR_RXNE_MASK = 0x1,
    SPI_SR_RXNE_POS = 0,
    SPI_SR_TXE_MASK = 0x2,
    SPI_SR_TXE_POS = 1,
    SPI_SR_CHSIDE_MASK = 0x4,
    SPI_SR_CHSIDE_POS = 2,
    SPI_SR_UDR_MASK = 0x8,
    SPI_SR_UDR_POS = 3,
    SPI_SR_CRCERR_MASK = 0x10,
    SPI_SR_CRCERR_POS = 4,
    SPI_SR_MODF_MASK = 0x20,
    SPI_SR_MODF_POS = 5,
    SPI_SR_OVR_MASK = 0x40,
    SPI_SR_OVR_POS = 6,
    SPI_SR_BSY_MASK = 0x80,
    SPI_SR_BSY_POS = 7,
    SPI_SR_FRE_MASK = 0x100,
    SPI_SR_FRE_POS = 8,
    SPI_SR_TXFLV_MASK = 0x1F0000,
    SPI_SR_TXFLV_POS = 16,
    SPI_SR_RXFLV_MASK = 0x1F000000,
    SPI_SR_RXFLV_POS = 24,	
};
enum SPI_REG_DR_FIELD
{
    SPI_DR_DR_MASK = 0xFFFF,
    SPI_DR_DR_POS = 0,
};
enum SPI_REG_CRCPR_FIELD
{
    SPI_CRCPR_CRCPOLY_MASK = 0xFFFF,
    SPI_CRCPR_CRCPOLY_POS = 0,
};
enum SPI_REG_RXCRCR_FIELD
{
    SPI_RXCRCR_RXCRC_MASK = 0xFFFF,
    SPI_RXCRCR_RXCRC_POS = 0,
};
enum SPI_REG_TXCRCR_FIELD
{
    SPI_TXCRCR_TXCRC_MASK = 0xFFFF,
    SPI_TXCRCR_TXCRC_POS = 0,
};
enum SPI_REG_I2SCFGR_FIELD
{
    SPI_I2SCFGR_CHLEN_MASK = 0x1,
    SPI_I2SCFGR_CHLEN_POS = 0,
    SPI_I2SCFGR_DATLEN_MASK = 0x6,
    SPI_I2SCFGR_DATLEN_POS = 1,
    SPI_I2SCFGR_CKPOL_MASK = 0x8,
    SPI_I2SCFGR_CKPOL_POS = 3,
    SPI_I2SCFGR_I2SSTD_MASK = 0x30,
    SPI_I2SCFGR_I2SSTD_POS = 4,
    SPI_I2SCFGR_PCMSYNC_MASK = 0x80,
    SPI_I2SCFGR_PCMSYNC_POS = 7,
    SPI_I2SCFGR_I2SCFG_MASK = 0x300,
    SPI_I2SCFGR_I2SCFG_POS = 8,	
    SPI_I2SCFGR_I2SE_MASK = 0x400,
    SPI_I2SCFGR_I2SE_POS = 10,	
    SPI_I2SCFGR_I2SMOD_MASK = 0x800,
    SPI_I2SCFGR_I2SMOD_POS = 11,	
};

enum SPI_REG_I2SPR_FIELD
{
    SPI_I2SPR_I2SDIV_MASK = 0xFF,
    SPI_I2SPR_I2SDIV_POS = 0,
    SPI_I2SPR_ODD_MASK = 0x100,
    SPI_I2SPR_ODD_POS = 8,
    SPI_I2SPR_MCKOE_MASK = 0x200,
    SPI_I2SPR_MCKOE_POS = 9,
    SPI_I2SPR_EXTCKEN_MASK = 0x400,
    SPI_I2SPR_EXTCKEN_POS = 10,
};

enum SPI_REG_IER_FIELD
{
    SPI_IER_RXNEIE_MASK = 0x1,
    SPI_IER_RXNEIE_POS = 0,
    SPI_IER_TXEIE_MASK = 0x2,
    SPI_IER_TXEIE_POS = 1,
    SPI_IER_UDRIE_MASK = 0x8,
    SPI_IER_UDRIE_POS = 3,
    SPI_IER_CRCERRIE_MASK = 0x10,
    SPI_IER_CRCERRIE_POS = 4,
    SPI_IER_MODFIE_MASK = 0x20,
    SPI_IER_MODFIE_POS = 5,
    SPI_IER_OVRIE_MASK = 0x40,
    SPI_IER_OVRIE_POS = 6,
    SPI_IER_FREIE_MASK = 0x100,
    SPI_IER_FREIE_POS = 8,
};

enum SPI_REG_IDR_FIELD
{
    SPI_IDR_RXNEID_MASK = 0x1,
    SPI_IDR_RXNEID_POS = 0,
    SPI_IDR_TXEID_MASK = 0x2,
    SPI_IDR_TXEID_POS = 1,
    SPI_IDR_UDRID_MASK = 0x8,
    SPI_IDR_UDRID_POS = 3,
    SPI_IDR_CRCERRID_MASK = 0x10,
    SPI_IDR_CRCERRID_POS = 4,
    SPI_IDR_MODFID_MASK = 0x20,
    SPI_IDR_MODFID_POS = 5,
    SPI_IDR_OVRID_MASK = 0x40,
    SPI_IDR_OVRID_POS = 6,
    SPI_IDR_FREID_MASK = 0x100,
    SPI_IDR_FREID_POS = 8,
};

enum SPI_REG_IVS_FIELD
{
    SPI_IVS_RXNEIV_MASK = 0x1,
    SPI_IVS_RXNEIV_POS = 0,
    SPI_IVS_TXEIV_MASK = 0x2,
    SPI_IVS_TXEIV_POS = 1,
    SPI_IVS_UDRIV_MASK = 0x8,
    SPI_IVS_UDRIV_POS = 3,
    SPI_IVS_CRCERRIV_MASK = 0x10,
    SPI_IVS_CRCERRIV_POS = 4,
    SPI_IVS_MODFIV_MASK = 0x20,
    SPI_IVS_MODFIV_POS = 5,
    SPI_IVS_OVRIV_MASK = 0x40,
    SPI_IVS_OVRIV_POS = 6,
    SPI_IVS_FREIV_MASK = 0x100,
    SPI_IVS_FREIV_POS = 8,
};

enum SPI_REG_RIF_FIELD
{
    SPI_RIF_RXNERI_MASK = 0x1,
    SPI_RIF_RXNERI_POS = 0,
    SPI_RIF_TXERI_MASK = 0x2,
    SPI_RIF_TXERI_POS = 1,
    SPI_RIF_UDRRI_MASK = 0x8,
    SPI_RIF_UDRRI_POS = 3,
    SPI_RIF_CRCERRRI_MASK = 0x10,
    SPI_RIF_CRCERRRI_POS = 4,
    SPI_RIF_MODFRI_MASK = 0x20,
    SPI_RIF_MODFRI_POS = 5,
    SPI_RIF_OVRRI_MASK = 0x40,
    SPI_RIF_OVRRI_POS = 6,
    SPI_RIF_FRERI_MASK = 0x100,
    SPI_RIF_FRERI_POS = 8,
};

enum SPI_REG_IFM_FIELD
{
    SPI_IFM_RXNEFM_MASK = 0x1,
    SPI_IFM_RXNEFM_POS = 0,
    SPI_IFM_TXEFM_MASK = 0x2,
    SPI_IFM_TXEFM_POS = 1,
    SPI_IFM_UDRFM_MASK = 0x8,
    SPI_IFM_UDRFM_POS = 3,
    SPI_IFM_CRCERRFM_MASK = 0x10,
    SPI_IFM_CRCERRFM_POS = 4,
    SPI_IFM_MODFFM_MASK = 0x20,
    SPI_IFM_MODFFM_POS = 5,
    SPI_IFM_OVRFM_MASK = 0x40,
    SPI_IFM_OVRFM_POS = 6,
    SPI_IFM_FREFM_MASK = 0x100,
    SPI_IFM_FREFM_POS = 8,
};

enum SPI_REG_ICR_FIELD
{
    SPI_ICR_RXNEIC_MASK = 0x1,
    SPI_ICR_RXNEIC_POS = 0,
    SPI_ICR_TXEIC_MASK = 0x2,
    SPI_ICR_TXEIC_POS = 1,
    SPI_ICR_UDRIC_MASK = 0x8,
    SPI_ICR_UDRIC_POS = 3,
    SPI_ICR_CRCERRIC_MASK = 0x10,
    SPI_ICR_CRCERRIC_POS = 4,
    SPI_ICR_MODFIC_MASK = 0x20,
    SPI_ICR_MODFIC_POS = 5,
    SPI_ICR_OVRIC_MASK = 0x40,
    SPI_ICR_OVRIC_POS = 6,
    SPI_ICR_FREIC_MASK = 0x100,
    SPI_ICR_FREIC_POS = 8,
};

#ifdef __cplusplus
}
#endif

#endif
