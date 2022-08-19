#ifndef REG_I2C_TYPE_H_
#define REG_I2C_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t TIMINGR;
    volatile uint32_t TIMEOUTR;
    volatile uint32_t SR;
    volatile uint32_t CFR;
    volatile uint32_t PECR;
    volatile uint32_t RXDR;
    volatile uint32_t TXDR;
    volatile uint32_t IER;
    volatile uint32_t IDR;
    volatile uint32_t IVS;
    volatile uint32_t RIF;
    volatile uint32_t IFM;
    volatile uint32_t ICR;
}reg_i2c_t;

enum I2C_REG_CR1_FIELD
{
    I2C_CR1_PE_MASK = 0x1,
    I2C_CR1_PE_POS = 0,
    I2C_CR1_DNF_MASK = 0xF00,
    I2C_CR1_DNF_POS = 8,
    I2C_CR1_TXDMAEN_MASK = 0x4000,
    I2C_CR1_TXDMAEN_POS = 14,
    I2C_CR1_RXDMAEN_MASK = 0x8000,
    I2C_CR1_RXDMAEN_POS = 15,
    I2C_CR1_SBC_MASK = 0x10000,
    I2C_CR1_SBC_POS = 16,
    I2C_CR1_NOSTRETCH_MASK = 0x20000,
    I2C_CR1_NOSTRETCH_POS = 17,
    I2C_CR1_GCEN_MASK = 0x80000,
    I2C_CR1_GCEN_POS = 19,
    I2C_CR1_SMBHEN_MASK = 0x100000,
    I2C_CR1_SMBHEN_POS = 20,
    I2C_CR1_SMBDEN_MASK = 0x200000,
    I2C_CR1_MBDEN_POS = 21,
    I2C_CR1_ALERTEN_MASK = 0x400000,
    I2C_CR1_ALERTEN_POS = 22,
    I2C_CR1_PECEN_MASK = 0x800000,
    I2C_CR1_PECEN_POS = 23,
    I2C_CR1_TXFTH_MASK = 0x7000000,
    I2C_CR1_TXFTH_POS = 24,
    I2C_CR1_RXFTH_MASK = 0x70000000,
    I2C_CR1_RXFTH_POS = 28,
};

enum I2C_REG_CR2_FIELD
{
    I2C_CR2_SADD0_MASK = 0x1,
    I2C_CR2_SADD0_POS = 0,
    I2C_CR2_SADD1_7_MASK = 0xFE,
    I2C_CR2_SADD1_7_POS = 1,
    I2C_CR2_SADD8_9_MASK = 0x300,
    I2C_CR2_SADD8_9_POS = 8,
    I2C_CR2_RD_WEN_MASK = 0x400,
    I2C_CR2_RD_WEN_POS = 10,
    I2C_CR2_SADD10_MASK = 0x800,
    I2C_CR2_SADD10_POS = 11,
    I2C_CR2_HEAD10R_MASK = 0x1000,
    I2C_CR2_HEAD10R_POS = 12,
    I2C_CR2_START_MASK = 0x2000,
    I2C_CR2_START_POS = 13,
    I2C_CR2_STOP_MASK = 0x4000,
    I2C_CR2_STOP_POS = 14,
    I2C_CR2_NACK_MASK = 0x8000,
    I2C_CR2_NACK_POS = 15,
    I2C_CR2_NBYTES_MASK = 0xFF0000,
    I2C_CR2_NBYTES_POS = 16,
    I2C_CR2_RELOAD_MASK = 0x1000000,
    I2C_CR2_RELOAD_POS = 24, 
    I2C_CR2_AUTOEND_MASK = 0x2000000,
    I2C_CR2_AUTOEND_POS = 25,
    I2C_CR2_PECBYTE_MASK = 0x4000000,
    I2C_CR2_PECBYTE_POS = 26,
};
enum I2C_REG_OAR1_FIELD
{
    I2C_OAR1_OA10_MASK = 0x1,
    I2C_OAR1_OA10_POS = 0,
    I2C_OAR1_OA11_7_MASK = 0xFE,
    I2C_OAR1_OA11_7_POS = 1,
    I2C_OAR1_OA18_9_MASK = 0x300,
    I2C_OAR1_OA18_9_POS = 8,
    I2C_OAR1_OA1MODE_MASK = 0x400,
    I2C_OAR1_OA1MODE_POS = 10,
    I2C_OAR1_OA1EN_MASK = 0x8000,
    I2C_OAR1_OA1EN_POS = 15,
};
enum I2C_REG_OAR2_FIELD
{
    I2C_OAR2_OA21_7_MASK = 0xFE,
    I2C_OAR2_OA21_7_POS = 1,
    I2C_OAR2_OA2MSK_MASK = 0x700,
    I2C_OAR2_OA2MSK_POS = 8,
    I2C_OAR2_OA2EN_MASK = 0x8000,
    I2C_OAR2_OA2EN_POS = 15,
};
enum I2C_REG_TIMINGR_FIELD
{
    I2C_TIMINGR_SCLL_MASK = 0xFF,
    I2C_TIMINGR_SCLL_POS = 0,
    I2C_TIMINGR_SCLH_MASK = 0xFF00,
    I2C_TIMINGR_SCLH_POS = 8,
    I2C_TIMINGR_SDADEL_MASK = 0xF0000,
    I2C_TIMINGR_SDADEL_POS = 16,
    I2C_TIMINGR_SCLDEL_MASK = 0xF00000,
    I2C_TIMINGR_SCLDEL_POS = 20,
    I2C_TIMINGR_PRESC_MASK = (int)0xF0000000,
    I2C_TIMINGR_PRESC_POS = 28,
};
enum I2C_REG_TIMEOUTR_FIELD
{
    I2C_TIMEOUTR_TIMEOUTA_MASK = 0xFFF,
    I2C_TIMEOUTR_TIMEOUTA_POS = 0,
    I2C_TIMEOUTR_TIDLE_MASK = 0x1000,
    I2C_TIMEOUTR_TIDLE_POS = 12,
    I2C_TIMEOUTR_TIMEOUTEN_MASK = 0x8000,
    I2C_TIMEOUTR_TIMEOUTEN_POS = 15,
    I2C_TIMEOUTR_TIMEOUTB_MASK = 0xFFF0000,
    I2C_TIMEOUTR_TIMEOUTB_POS = 16,
    I2C_TIMEOUTR_TEXTEN_MASK = (int)0x80000000,
    I2C_TIMEOUTR_TEXTEN_POS = 31,
};
enum I2C_REG_SR_FIELD
{
    I2C_SR_TXE_MASK = 0x1,
    I2C_SR_TXE_POS = 0,
    I2C_SR_RXNE_MASK = 0x4,
    I2C_SR_RXNE_POS = 2,
    I2C_SR_ADDR_MASK = 0x8,
    I2C_SR_ADDR_POS = 3,
    I2C_SR_NACKF_MASK = 0x10,
    I2C_SR_NACKF_POS = 4,
    I2C_SR_STOPF_MASK = 0x20,
    I2C_SR_STOPF_POS = 5,
    I2C_SR_TC_MASK = 0x40,
    I2C_SR_TC_POS = 6,
    I2C_SR_TCR_MASK = 0x80,
    I2C_SR_TCR_POS = 7,
    I2C_SR_BERR_MASK = 0x100,
    I2C_SR_BERR_POS = 8,
    I2C_SR_ARLO_MASK = 0x200,
    I2C_SR_ARLO_POS = 9,
    I2C_SR_OVR_MASK = 0x400,
    I2C_SR_OVR_POS = 10,
    I2C_SR_PECERR_MASK = 0x800,
    I2C_SR_PECERR_POS = 11,
    I2C_SR_TIMEOUT_MASK = 0x1000,
    I2C_SR_TIMEOUT_POS = 12,
    I2C_SR_ALERT_MASK = 0x2000,
    I2C_SR_ALERT_POS = 13,
    I2C_SR_BUSY_MASK = 0x8000,
    I2C_SR_BUSY_POS = 15,
    I2C_SR_DIR_MASK = 0x10000,
    I2C_SR_DIR_POS = 16,
    I2C_SR_ADDCODE_MASK = 0xFE0000,
    I2C_SR_ADDCODE_POS = 17,    
    I2C_SR_TXFLV_MASK = 0xF000000,
    I2C_SR_TXFLV_POS = 24, 
    I2C_SR_RXFLV_MASK = (int)0xF0000000,
    I2C_SR_RXFLV_POS = 28,
};
enum I2C_REG_CFR_FIELD
{
    I2C_CFR_ADDRCF_MASK = 0x8,
    I2C_CFR_ADDRCF_POS = 3,
    I2C_CFR_NACKCF_MASK = 0x10,
    I2C_CFR_NACKCF_POS = 4,
    I2C_CFR_STOPCF_MASK = 0x20,
    I2C_CFR_STOPCF_POS = 5,
    I2C_CFR_BERRCF_MASK = 0x100,
    I2C_CFR_BERRCF_POS = 8,
    I2C_CFR_ARLOCF_MASK = 0x200,
    I2C_CFR_ARLOCF_POS = 9,
    I2C_CFR_OVRCF_MASK = 0x400,
    I2C_CFR_OVRCF_POS = 10,
    I2C_CFR_FECCF_MASK = 0x800,
    I2C_CFR_FECCF_POS = 11,
    I2C_CFR_TIMEOUTCF_MASK = 0x1000,
    I2C_CFR_TIMEOUTCF_POS = 12,
    I2C_CFR_ALERTCF_MASK = 0x2000,
    I2C_CFR_ALERTCF_POS = 13,	
};
enum I2C_REG_PECR_FIELD
{
    I2C_PECR_PEC_MASK = 0xFF,
    I2C_PECR_PEC_POS = 0,
};
enum I2C_REG_RXDR_FIELD
{
    I2C_RXDR_RXDATA_MASK = 0xFF,
    I2C_RXDR_RXDATA_POS = 0,
};
enum I2C_REG_TXDR_FIELD
{
    I2C_TXDR_TXDATA_MASK = 0xFF,
    I2C_TXDR_TXDATA_POS = 0,
};

enum I2C_REG_IER_FIELD
{
    I2C_IER_TXEIE_MASK = 0x1,
    I2C_IER_TXEIE_POS = 0,
    I2C_IER_RXNEIE_MASK = 0x4,
    I2C_IER_RXNEIE_POS = 2,
    I2C_IER_ADDRIE_MASK = 0x8,
    I2C_IER_ADDRIE_POS = 3,
    I2C_IER_NACKIE_MASK = 0x10,
    I2C_IER_NACKIE_POS = 4,
    I2C_IER_STOPIE_MASK = 0x20,
    I2C_IER_STOPIE_POS = 5,
    I2C_IER_TCIE_MASK = 0x40,
    I2C_IER_TCIE_POS = 6,
    I2C_IER_TCRIE_MASK = 0x80,
    I2C_IER_TCRIE_POS = 7,
    I2C_IER_BERRIE_MASK = 0x100,
    I2C_IER_BERRIE_POS = 8,
    I2C_IER_ARLOIE_MASK = 0x200,
    I2C_IER_ARLOIE_POS = 9,
    I2C_IER_OVRIE_MASK = 0x400,
    I2C_IER_OVRIE_POS = 10,
    I2C_IER_PECEIE_MASK = 0x800,
    I2C_IER_PECEIE_POS = 11,
    I2C_IER_TOUTIE_MASK = 0x1000,
    I2C_IER_TOUTIE_POS = 12,
    I2C_IER_ALERTIE_MASK = 0x2000,
    I2C_IER_ALERTIE_POS = 13,
};

enum I2C_REG_IDR_FIELD
{
    I2C_IDR_TXEID_MASK = 0x1,
    I2C_IDR_TXEID_POS = 0,
    I2C_IDR_RXNEID_MASK = 0x4,
    I2C_IDR_RXNEID_POS = 2,
    I2C_IDR_ADDRID_MASK = 0x8,
    I2C_IDR_ADDRID_POS = 3,
    I2C_IDR_NACKID_MASK = 0x10,
    I2C_IDR_NACKID_POS = 4,
    I2C_IDR_STOPID_MASK = 0x20,
    I2C_IDR_STOPID_POS = 5,
    I2C_IDR_TCID_MASK = 0x40,
    I2C_IDR_TCID_POS = 6,
    I2C_IDR_TCRID_MASK = 0x80,
    I2C_IDR_TCRID_POS = 7,
    I2C_IDR_BERRID_MASK = 0x100,
    I2C_IDR_BERRID_POS = 8,
    I2C_IDR_ARLOID_MASK = 0x200,
    I2C_IDR_ARLOID_POS = 9,
    I2C_IDR_OVRID_MASK = 0x400,
    I2C_IDR_OVRID_POS = 10,
    I2C_IDR_PECEID_MASK = 0x800,
    I2C_IDR_PECEID_POS = 11,
    I2C_IDR_TOUTID_MASK = 0x1000,
    I2C_IDR_TOUTID_POS = 12,
    I2C_IDR_ALERTID_MASK = 0x2000,
    I2C_IDR_ALERTID_POS = 13,
};

enum I2C_REG_IVS_FIELD
{
    I2C_IVS_TXEIV_MASK = 0x1,
    I2C_IVS_TXEIV_POS = 0,
    I2C_IVS_RXNEIV_MASK = 0x4,
    I2C_IVS_RXNEIV_POS = 2,
    I2C_IVS_ADDRIV_MASK = 0x8,
    I2C_IVS_ADDRIV_POS = 3,
    I2C_IVS_NACKIV_MASK = 0x10,
    I2C_IVS_NACKIV_POS = 4,
    I2C_IVS_STOPIV_MASK = 0x20,
    I2C_IVS_STOPIV_POS = 5,
    I2C_IVS_TCIV_MASK = 0x40,
    I2C_IVS_TCIV_POS = 6,
    I2C_IVS_TCRIV_MASK = 0x80,
    I2C_IVS_TCRIV_POS = 7,
    I2C_IVS_BERRIV_MASK = 0x100,
    I2C_IVS_BERRIV_POS = 8,
    I2C_IVS_ARLOIV_MASK = 0x200,
    I2C_IVS_ARLOIV_POS = 9,
    I2C_IVS_OVRIV_MASK = 0x400,
    I2C_IVS_OVRIV_POS = 10,
    I2C_IVS_PECEIV_MASK = 0x800,
    I2C_IVS_PECEIV_POS = 11,
    I2C_IVS_TOUTIV_MASK = 0x1000,
    I2C_IVS_TOUTIV_POS = 12,
    I2C_IVS_ALERTIV_MASK = 0x2000,
    I2C_IVS_ALERTIV_POS = 13,
};

enum I2C_REG_RIF_FIELD
{
    I2C_RIF_TXERI_MASK = 0x1,
    I2C_RIF_TXERI_POS = 0,
    I2C_RIF_RXNERI_MASK = 0x4,
    I2C_RIF_RXNERI_POS = 2,
    I2C_RIF_ADDRRI_MASK = 0x8,
    I2C_RIF_ADDRRI_POS = 3,
    I2C_RIF_NACKRI_MASK = 0x10,
    I2C_RIF_NACKRI_POS = 4,
    I2C_RIF_STOPRI_MASK = 0x20,
    I2C_RIF_STOPRI_POS = 5,
    I2C_RIF_TCRI_MASK = 0x40,
    I2C_RIF_TCRI_POS = 6,
    I2C_RIF_TCRRI_MASK = 0x80,
    I2C_RIF_TCRRI_POS = 7,
    I2C_RIF_BERRRI_MASK = 0x100,
    I2C_RIF_BERRRI_POS = 8,
    I2C_RIF_ARLORI_MASK = 0x200,
    I2C_RIF_ARLORI_POS = 9,
    I2C_RIF_OVRRI_MASK = 0x400,
    I2C_RIF_OVRRI_POS = 10,
    I2C_RIF_PECERI_MASK = 0x800,
    I2C_RIF_PECERI_POS = 11,
    I2C_RIF_TOUTRI_MASK = 0x1000,
    I2C_RIF_TOUTRI_POS = 12,
    I2C_RIF_ALERTRI_MASK = 0x2000,
    I2C_RIF_ALERTRI_POS = 13,
};

enum I2C_REG_IFM_FIELD
{
    I2C_IFM_TXEFM_MASK = 0x1,
    I2C_IFM_TXEFM_POS = 0,
    I2C_IFM_RXNEFM_MASK = 0x4,
    I2C_IFM_RXNEFM_POS = 2,
    I2C_IFM_ADDRFM_MASK = 0x8,
    I2C_IFM_ADDRFM_POS = 3,
    I2C_IFM_NACKFM_MASK = 0x10,
    I2C_IFM_NACKFM_POS = 4,
    I2C_IFM_STOPFM_MASK = 0x20,
    I2C_IFM_STOPFM_POS = 5,
    I2C_IFM_TCFM_MASK = 0x40,
    I2C_IFM_TCFM_POS = 6,
    I2C_IFM_TCRFM_MASK = 0x80,
    I2C_IFM_TCRFM_POS = 7,
    I2C_IFM_BERRFM_MASK = 0x100,
    I2C_IFM_BERRFM_POS = 8,
    I2C_IFM_ARLOFM_MASK = 0x200,
    I2C_IFM_ARLOFM_POS = 9,
    I2C_IFM_OVRFM_MASK = 0x400,
    I2C_IFM_OVRFM_POS = 10,
    I2C_IFM_PECEFM_MASK = 0x800,
    I2C_IFM_PECEFM_POS = 11,
    I2C_IFM_TOUTFM_MASK = 0x1000,
    I2C_IFM_TOUTFM_POS = 12,
    I2C_IFM_ALERTFM_MASK = 0x2000,
    I2C_IFM_ALERTFM_POS = 13,
};

enum I2C_REG_ICR_FIELD
{
    I2C_ICR_TXEIC_MASK = 0x1,
    I2C_ICR_TXEIC_POS = 0,
    I2C_ICR_RXNEIC_MASK = 0x4,
    I2C_ICR_RXNEIC_POS = 2,
    I2C_ICR_ADDRIC_MASK = 0x8,
    I2C_ICR_ADDRIC_POS = 3,
    I2C_ICR_NACKIC_MASK = 0x10,
    I2C_ICR_NACKIC_POS = 4,
    I2C_ICR_STOPIC_MASK = 0x20,
    I2C_ICR_STOPIC_POS = 5,
    I2C_ICR_TCIC_MASK = 0x40,
    I2C_ICR_TCIC_POS = 6,
    I2C_ICR_TCRIC_MASK = 0x80,
    I2C_ICR_TCRIC_POS = 7,
    I2C_ICR_BERRIC_MASK = 0x100,
    I2C_ICR_BERRIC_POS = 8,
    I2C_ICR_ARLOIC_MASK = 0x200,
    I2C_ICR_ARLOIC_POS = 9,
    I2C_ICR_OVRIC_MASK = 0x400,
    I2C_ICR_OVRIC_POS = 10,
    I2C_ICR_PECEIC_MASK = 0x800,
    I2C_ICR_PECEIC_POS = 11,
    I2C_ICR_TOUTIC_MASK = 0x1000,
    I2C_ICR_TOUTIC_POS = 12,
    I2C_ICR_ALERTIC_MASK = 0x2000,
    I2C_ICR_ALERTIC_POS = 13,
};

#endif