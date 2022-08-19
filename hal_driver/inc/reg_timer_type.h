 
#ifndef REG_TIMER_TYPE_H_
#define REG_TIMER_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t CR1; //0x0
    volatile uint32_t CR2; //0x4
    volatile uint32_t SMCR; //0x8
    volatile uint32_t IER; //0xc
    volatile uint32_t IDR; //0x10
    volatile uint32_t IVS; //0x14
    volatile uint32_t RIF; //0x18
    volatile uint32_t IFM; //0x1c
    volatile uint32_t ICR; //0x20
    volatile uint32_t EGR; //0x24
    volatile uint32_t CCMR1; //0x28
    volatile uint32_t CCMR2; //0x2c
    volatile uint32_t CCER; //0x30
    volatile uint32_t CNT; //0x34
    volatile uint32_t PSC; //0x38
    volatile uint32_t ARR; //0x3c
    volatile uint32_t REP; //0x40
    volatile uint32_t CCR1; //0x44
    volatile uint32_t CCR2; //0x48
    volatile uint32_t CCR3; //0x4c
    volatile uint32_t CCR4; //0x50
    volatile uint32_t BDTR; //0x54
    volatile uint32_t DMAEN; //0x58
}reg_timer_t;

enum TIMER_REG_CR1_FIELD
{
    TIMER_CR1_CEN_MASK = (int)0x1,
    TIMER_CR1_CEN_POS = 0,
    TIMER_CR1_CEN = TIMER_CR1_CEN_MASK,
    TIMER_CR1_UDIS_MASK = (int)0x2,
    TIMER_CR1_UDIS_POS = 1,
    TIMER_CR1_UDIS = TIMER_CR1_UDIS_MASK,
    TIMER_CR1_URS_MASK = (int)0x4,
    TIMER_CR1_URS_POS = 2,
    TIMER_CR1_URS = TIMER_CR1_URS_MASK,
    TIMER_CR1_OPM_MASK = (int)0x8,
    TIMER_CR1_OPM_POS = 3,
    TIMER_CR1_OPM = TIMER_CR1_OPM_MASK,
    TIMER_CR1_DIR_MASK = (int)0x10,
    TIMER_CR1_DIR_POS = 4,
    TIMER_CR1_DIR = TIMER_CR1_DIR_MASK,
    TIMER_CR1_CMS_MASK = (int)0x60,
    TIMER_CR1_CMS_POS = 5,
    TIMER_CR1_CMS = TIMER_CR1_CMS_MASK,
    TIMER_CR1_CMS_0 = 1 << TIMER_CR1_CMS_POS,
    TIMER_CR1_CMS_1 = 2 << TIMER_CR1_CMS_POS,
    TIMER_CR1_ARPE_MASK = (int)0x80,
    TIMER_CR1_ARPE_POS = 7,
    TIMER_CR1_ARPE = TIMER_CR1_ARPE_MASK,
    TIMER_CR1_CKD_MASK = (int)0x300,
    TIMER_CR1_CKD_POS = 8,
    TIMER_CR1_CKD = TIMER_CR1_CKD_MASK,
    TIMER_CR1_CKD_0 = 1 << TIMER_CR1_CKD_POS,
    TIMER_CR1_CKD_1 = 2 << TIMER_CR1_CKD_POS,
    TIMER_CR1_CMPSEL_MASK = (int)0xc00,
    TIMER_CR1_CMPSEL_POS = 10,
    TIMER_CR1_CMPSEL = TIMER_CR1_CMPSEL_MASK,
    TIMER_CR1_CMPSEL_0 = 1 << TIMER_CR1_CMPSEL_POS,
    TIMER_CR1_CMPSEL_1 = 2 << TIMER_CR1_CMPSEL_POS
};

enum TIMER_REG_CR2_FIELD
{
    TIMER_CR2_CCPC_MASK = (int)0x1,
    TIMER_CR2_CCPC_POS = 0,
    TIMER_CR2_CCPC = TIMER_CR2_CCPC_MASK,
    TIMER_CR2_CCUS_MASK = (int)0x4,
    TIMER_CR2_CCUS_POS = 2,
    TIMER_CR2_CCUS = TIMER_CR2_CCUS_MASK,
    TIMER_CR2_CCDS_MASK = (int)0x8,
    TIMER_CR2_CCDS_POS = 3,
    TIMER_CR2_CCDS = TIMER_CR2_CCDS_MASK,
    TIMER_CR2_MMS_MASK = (int)0x70,
    TIMER_CR2_MMS_POS = 4,
    TIMER_CR2_MMS = TIMER_CR2_MMS_MASK,
    TIMER_CR2_MMS_0 = 1 << TIMER_CR2_MMS_POS,
    TIMER_CR2_MMS_1 = 2 << TIMER_CR2_MMS_POS,
    TIMER_CR2_MMS_2 = 4 << TIMER_CR2_MMS_POS,
    TIMER_CR2_TI1S_MASK = (int)0x80,
    TIMER_CR2_TI1S_POS = 7,
    TIMER_CR2_TI1S = TIMER_CR2_TI1S_MASK,
    TIMER_CR2_OIS1_MASK = (int)0x100,
    TIMER_CR2_OIS1_POS = 8,
    TIMER_CR2_OIS1 = TIMER_CR2_OIS1_MASK,
    TIMER_CR2_OIS1N_MASK = (int)0x200,
    TIMER_CR2_OIS1N_POS = 9,
    TIMER_CR2_OIS1N = TIMER_CR2_OIS1N_MASK,
    TIMER_CR2_OIS2_MASK = (int)0x400,
    TIMER_CR2_OIS2_POS = 10,
    TIMER_CR2_OIS2 = TIMER_CR2_OIS2_MASK,
    TIMER_CR2_OIS2N_MASK = (int)0x800,
    TIMER_CR2_OIS2N_POS = 11,
    TIMER_CR2_OIS2N = TIMER_CR2_OIS2N_MASK,
    TIMER_CR2_OIS3_MASK = (int)0x1000,
    TIMER_CR2_OIS3_POS = 12,
    TIMER_CR2_OIS3 = TIMER_CR2_OIS3_MASK,
    TIMER_CR2_OIS3N_MASK = (int)0x2000,
    TIMER_CR2_OIS3N_POS = 13,
    TIMER_CR2_OIS3N = TIMER_CR2_OIS3N_MASK,
    TIMER_CR2_OIS4_MASK = (int)0x4000,
    TIMER_CR2_OIS4_POS = 14,
    TIMER_CR2_OIS4 = TIMER_CR2_OIS4_MASK,
    TIMER_CR2_OIS4N_MASK = (int)0x8000,
    TIMER_CR2_OIS4N_POS = 15,
    TIMER_CR2_OIS4N = TIMER_CR2_OIS4N_MASK
};

enum TIMER_REG_SMCR_FIELD
{
    TIMER_SMCR_SMS_MASK = (int)0x7,
    TIMER_SMCR_SMS_POS = 0,
    TIMER_SMCR_SMS = TIMER_SMCR_SMS_MASK,
    TIMER_SMCR_SMS_0 = 1 << TIMER_SMCR_SMS_POS,
    TIMER_SMCR_SMS_1 = 2 << TIMER_SMCR_SMS_POS,
    TIMER_SMCR_SMS_2 = 4 << TIMER_SMCR_SMS_POS,
    TIMER_SMCR_TS_MASK = (int)0x70,
    TIMER_SMCR_TS_POS = 4,
    TIMER_SMCR_TS = TIMER_SMCR_TS_MASK,
    TIMER_SMCR_TS_0 = 1 << TIMER_SMCR_TS_POS,
    TIMER_SMCR_TS_1 = 2 << TIMER_SMCR_TS_POS,
    TIMER_SMCR_TS_2 = 4 << TIMER_SMCR_TS_POS,
    TIMER_SMCR_MSM_MASK = (int)0x80,
    TIMER_SMCR_MSM_POS = 7,
    TIMER_SMCR_MSM = TIMER_SMCR_MSM_MASK,
    TIMER_SMCR_ETF_MASK = (int)0xf00,
    TIMER_SMCR_ETF_POS = 8,
    TIMER_SMCR_ETF = TIMER_SMCR_ETF_MASK,
    TIMER_SMCR_ETF_0 = 1 << TIMER_SMCR_ETF_POS,
    TIMER_SMCR_ETF_1 = 2 << TIMER_SMCR_ETF_POS,
    TIMER_SMCR_ETF_2 = 4 << TIMER_SMCR_ETF_POS,
    TIMER_SMCR_ETF_3 = 8 << TIMER_SMCR_ETF_POS,
    TIMER_SMCR_ETPS_MASK = (int)0x3000,
    TIMER_SMCR_ETPS_POS = 12,
    TIMER_SMCR_ETPS = TIMER_SMCR_ETPS_MASK,
    TIMER_SMCR_ETPS_0 = 1 << TIMER_SMCR_ETPS_POS,
    TIMER_SMCR_ETPS_1 = 2 << TIMER_SMCR_ETPS_POS,
    TIMER_SMCR_ECE_MASK = (int)0x4000,
    TIMER_SMCR_ECE_POS = 14,
    TIMER_SMCR_ECE = TIMER_SMCR_ECE_MASK,
    TIMER_SMCR_ETP_MASK = (int)0x8000,
    TIMER_SMCR_ETP_POS = 15,
    TIMER_SMCR_ETP = TIMER_SMCR_ETP_MASK
};

enum TIMER_REG_IER_FIELD
{
    TIMER_IER_UIE_MASK = (int)0x1,
    TIMER_IER_UIE_POS = 0,
    TIMER_IER_UIE = TIMER_IER_UIE_MASK,
    TIMER_IER_CC1IE_MASK = (int)0x2,
    TIMER_IER_CC1IE_POS = 1,
    TIMER_IER_CC1IE = TIMER_IER_CC1IE_MASK,
    TIMER_IER_CC2IE_MASK = (int)0x4,
    TIMER_IER_CC2IE_POS = 2,
    TIMER_IER_CC2IE = TIMER_IER_CC2IE_MASK,
    TIMER_IER_CC3IE_MASK = (int)0x8,
    TIMER_IER_CC3IE_POS = 3,
    TIMER_IER_CC3IE = TIMER_IER_CC3IE_MASK,
    TIMER_IER_CC4IE_MASK = (int)0x10,
    TIMER_IER_CC4IE_POS = 4,
    TIMER_IER_CC4IE = TIMER_IER_CC4IE_MASK,
    TIMER_IER_COMIE_MASK = (int)0x20,
    TIMER_IER_COMIE_POS = 5,
    TIMER_IER_COMIE = TIMER_IER_COMIE_MASK,
    TIMER_IER_TIE_MASK = (int)0x40,
    TIMER_IER_TIE_POS = 6,
    TIMER_IER_TIE = TIMER_IER_TIE_MASK,
    TIMER_IER_BIE_MASK = (int)0x80,
    TIMER_IER_BIE_POS = 7,
    TIMER_IER_BIE = TIMER_IER_BIE_MASK,
    TIMER_IER_CC1OIE_MASK = (int)0x200,
    TIMER_IER_CC1OIE_POS = 9,
    TIMER_IER_CC1OIE = TIMER_IER_CC1OIE_MASK,
    TIMER_IER_CC2OIE_MASK = (int)0x400,
    TIMER_IER_CC2OIE_POS = 10,
    TIMER_IER_CC2OIE = TIMER_IER_CC2OIE_MASK,
    TIMER_IER_CC3OIE_MASK = (int)0x800,
    TIMER_IER_CC3OIE_POS = 11,
    TIMER_IER_CC3OIE = TIMER_IER_CC3OIE_MASK,
    TIMER_IER_CC4OIE_MASK = (int)0x1000,
    TIMER_IER_CC4OIE_POS = 12,
    TIMER_IER_CC4OIE = TIMER_IER_CC4OIE_MASK
};

enum TIMER_REG_IDR_FIELD
{
    TIMER_IDR_UIE_MASK = (int)0x1,
    TIMER_IDR_UIE_POS = 0,
    TIMER_IDR_UIE = TIMER_IDR_UIE_MASK,
    TIMER_IDR_CC1IE_MASK = (int)0x2,
    TIMER_IDR_CC1IE_POS = 1,
    TIMER_IDR_CC1IE = TIMER_IDR_CC1IE_MASK,
    TIMER_IDR_CC2IE_MASK = (int)0x4,
    TIMER_IDR_CC2IE_POS = 2,
    TIMER_IDR_CC2IE = TIMER_IDR_CC2IE_MASK,
    TIMER_IDR_CC3IE_MASK = (int)0x8,
    TIMER_IDR_CC3IE_POS = 3,
    TIMER_IDR_CC3IE = TIMER_IDR_CC3IE_MASK,
    TIMER_IDR_CC4IE_MASK = (int)0x10,
    TIMER_IDR_CC4IE_POS = 4,
    TIMER_IDR_CC4IE = TIMER_IDR_CC4IE_MASK,
    TIMER_IDR_COMIE_MASK = (int)0x20,
    TIMER_IDR_COMIE_POS = 5,
    TIMER_IDR_COMIE = TIMER_IDR_COMIE_MASK,
    TIMER_IDR_TIE_MASK = (int)0x40,
    TIMER_IDR_TIE_POS = 6,
    TIMER_IDR_TIE = TIMER_IDR_TIE_MASK,
    TIMER_IDR_BIE_MASK = (int)0x80,
    TIMER_IDR_BIE_POS = 7,
    TIMER_IDR_BIE = TIMER_IDR_BIE_MASK,
    TIMER_IDR_CC1OIE_MASK = (int)0x200,
    TIMER_IDR_CC1OIE_POS = 9,
    TIMER_IDR_CC1OIE = TIMER_IDR_CC1OIE_MASK,
    TIMER_IDR_CC2OIE_MASK = (int)0x400,
    TIMER_IDR_CC2OIE_POS = 10,
    TIMER_IDR_CC2OIE = TIMER_IDR_CC2OIE_MASK,
    TIMER_IDR_CC3OIE_MASK = (int)0x800,
    TIMER_IDR_CC3OIE_POS = 11,
    TIMER_IDR_CC3OIE = TIMER_IDR_CC3OIE_MASK,
    TIMER_IDR_CC4OIE_MASK = (int)0x1000,
    TIMER_IDR_CC4OIE_POS = 12,
    TIMER_IDR_CC4OIE = TIMER_IDR_CC4OIE_MASK
};

enum TIMER_REG_IVS_FIELD
{
    TIMER_IVS_UIE_MASK = (int)0x1,
    TIMER_IVS_UIE_POS = 0,
    TIMER_IVS_UIE = TIMER_IVS_UIE_MASK,
    TIMER_IVS_CC1IE_MASK = (int)0x2,
    TIMER_IVS_CC1IE_POS = 1,
    TIMER_IVS_CC1IE = TIMER_IVS_CC1IE_MASK,
    TIMER_IVS_CC2IE_MASK = (int)0x4,
    TIMER_IVS_CC2IE_POS = 2,
    TIMER_IVS_CC2IE = TIMER_IVS_CC2IE_MASK,
    TIMER_IVS_CC3IE_MASK = (int)0x8,
    TIMER_IVS_CC3IE_POS = 3,
    TIMER_IVS_CC3IE = TIMER_IVS_CC3IE_MASK,
    TIMER_IVS_CC4IE_MASK = (int)0x10,
    TIMER_IVS_CC4IE_POS = 4,
    TIMER_IVS_CC4IE = TIMER_IVS_CC4IE_MASK,
    TIMER_IVS_COMIE_MASK = (int)0x20,
    TIMER_IVS_COMIE_POS = 5,
    TIMER_IVS_COMIE = TIMER_IVS_COMIE_MASK,
    TIMER_IVS_TIE_MASK = (int)0x40,
    TIMER_IVS_TIE_POS = 6,
    TIMER_IVS_TIE = TIMER_IVS_TIE_MASK,
    TIMER_IVS_BIE_MASK = (int)0x80,
    TIMER_IVS_BIE_POS = 7,
    TIMER_IVS_BIE = TIMER_IVS_BIE_MASK,
    TIMER_IVS_CC1OIE_MASK = (int)0x200,
    TIMER_IVS_CC1OIE_POS = 9,
    TIMER_IVS_CC1OIE = TIMER_IVS_CC1OIE_MASK,
    TIMER_IVS_CC2OIE_MASK = (int)0x400,
    TIMER_IVS_CC2OIE_POS = 10,
    TIMER_IVS_CC2OIE = TIMER_IVS_CC2OIE_MASK,
    TIMER_IVS_CC3OIE_MASK = (int)0x800,
    TIMER_IVS_CC3OIE_POS = 11,
    TIMER_IVS_CC3OIE = TIMER_IVS_CC3OIE_MASK,
    TIMER_IVS_CC4OIE_MASK = (int)0x1000,
    TIMER_IVS_CC4OIE_POS = 12,
    TIMER_IVS_CC4OIE = TIMER_IVS_CC4OIE_MASK
};

enum TIMER_REG_RIF_FIELD
{
    TIMER_RIF_UIF_MASK = (int)0x1,
    TIMER_RIF_UIF_POS = 0,
    TIMER_RIF_UIF = TIMER_RIF_UIF_MASK,
    TIMER_RIF_CC1IF_MASK = (int)0x2,
    TIMER_RIF_CC1IF_POS = 1,
    TIMER_RIF_CC1IF = TIMER_RIF_CC1IF_MASK,
    TIMER_RIF_CC2IF_MASK = (int)0x4,
    TIMER_RIF_CC2IF_POS = 2,
    TIMER_RIF_CC2IF = TIMER_RIF_CC2IF_MASK,
    TIMER_RIF_CC3IF_MASK = (int)0x8,
    TIMER_RIF_CC3IF_POS = 3,
    TIMER_RIF_CC3IF = TIMER_RIF_CC3IF_MASK,
    TIMER_RIF_CC4IF_MASK = (int)0x10,
    TIMER_RIF_CC4IF_POS = 4,
    TIMER_RIF_CC4IF = TIMER_RIF_CC4IF_MASK,
    TIMER_RIF_COMIF_MASK = (int)0x20,
    TIMER_RIF_COMIF_POS = 5,
    TIMER_RIF_COMIF = TIMER_RIF_COMIF_MASK,
    TIMER_RIF_TIF_MASK = (int)0x40,
    TIMER_RIF_TIF_POS = 6,
    TIMER_RIF_TIF = TIMER_RIF_TIF_MASK,
    TIMER_RIF_BIF_MASK = (int)0x80,
    TIMER_RIF_BIF_POS = 7,
    TIMER_RIF_BIF = TIMER_RIF_BIF_MASK,
    TIMER_RIF_CC1OIF_MASK = (int)0x200,
    TIMER_RIF_CC1OIF_POS = 9,
    TIMER_RIF_CC1OIF = TIMER_RIF_CC1OIF_MASK,
    TIMER_RIF_CC2OIF_MASK = (int)0x400,
    TIMER_RIF_CC2OIF_POS = 10,
    TIMER_RIF_CC2OIF = TIMER_RIF_CC2OIF_MASK,
    TIMER_RIF_CC3OIF_MASK = (int)0x800,
    TIMER_RIF_CC3OIF_POS = 11,
    TIMER_RIF_CC3OIF = TIMER_RIF_CC3OIF_MASK,
    TIMER_RIF_CC4OIF_MASK = (int)0x1000,
    TIMER_RIF_CC4OIF_POS = 12,
    TIMER_RIF_CC4OIF = TIMER_RIF_CC4OIF_MASK
};

enum TIMER_REG_IFM_FIELD
{
    TIMER_IFM_UIE_MASK = (int)0x1,
    TIMER_IFM_UIE_POS = 0,
    TIMER_IFM_UIE = TIMER_IFM_UIE_MASK,
    TIMER_IFM_CC1IE_MASK = (int)0x2,
    TIMER_IFM_CC1IE_POS = 1,
    TIMER_IFM_CC1IE = TIMER_IFM_CC1IE_MASK,
    TIMER_IFM_CC2IE_MASK = (int)0x4,
    TIMER_IFM_CC2IE_POS = 2,
    TIMER_IFM_CC2IE = TIMER_IFM_CC2IE_MASK,
    TIMER_IFM_CC3IE_MASK = (int)0x8,
    TIMER_IFM_CC3IE_POS = 3,
    TIMER_IFM_CC3IE = TIMER_IFM_CC3IE_MASK,
    TIMER_IFM_CC4IE_MASK = (int)0x10,
    TIMER_IFM_CC4IE_POS = 4,
    TIMER_IFM_CC4IE = TIMER_IFM_CC4IE_MASK,
    TIMER_IFM_COMIE_MASK = (int)0x20,
    TIMER_IFM_COMIE_POS = 5,
    TIMER_IFM_COMIE = TIMER_IFM_COMIE_MASK,
    TIMER_IFM_TIE_MASK = (int)0x40,
    TIMER_IFM_TIE_POS = 6,
    TIMER_IFM_TIE = TIMER_IFM_TIE_MASK,
    TIMER_IFM_BIE_MASK = (int)0x80,
    TIMER_IFM_BIE_POS = 7,
    TIMER_IFM_BIE = TIMER_IFM_BIE_MASK,
    TIMER_IFM_CC1OIE_MASK = (int)0x200,
    TIMER_IFM_CC1OIE_POS = 9,
    TIMER_IFM_CC1OIE = TIMER_IFM_CC1OIE_MASK,
    TIMER_IFM_CC2OIE_MASK = (int)0x400,
    TIMER_IFM_CC2OIE_POS = 10,
    TIMER_IFM_CC2OIE = TIMER_IFM_CC2OIE_MASK,
    TIMER_IFM_CC3OIE_MASK = (int)0x800,
    TIMER_IFM_CC3OIE_POS = 11,
    TIMER_IFM_CC3OIE = TIMER_IFM_CC3OIE_MASK,
    TIMER_IFM_CC4OIE_MASK = (int)0x1000,
    TIMER_IFM_CC4OIE_POS = 12,
    TIMER_IFM_CC4OIE = TIMER_IFM_CC4OIE_MASK
};

enum TIMER_REG_ICR_FIELD
{
    TIMER_ICR_UIE_MASK = (int)0x1,
    TIMER_ICR_UIE_POS = 0,
    TIMER_ICR_UIE = TIMER_ICR_UIE_MASK,
    TIMER_ICR_CC1IE_MASK = (int)0x2,
    TIMER_ICR_CC1IE_POS = 1,
    TIMER_ICR_CC1IE = TIMER_ICR_CC1IE_MASK,
    TIMER_ICR_CC2IE_MASK = (int)0x4,
    TIMER_ICR_CC2IE_POS = 2,
    TIMER_ICR_CC2IE = TIMER_ICR_CC2IE_MASK,
    TIMER_ICR_CC3IE_MASK = (int)0x8,
    TIMER_ICR_CC3IE_POS = 3,
    TIMER_ICR_CC3IE = TIMER_ICR_CC3IE_MASK,
    TIMER_ICR_CC4IE_MASK = (int)0x10,
    TIMER_ICR_CC4IE_POS = 4,
    TIMER_ICR_CC4IE = TIMER_ICR_CC4IE_MASK,
    TIMER_ICR_COMIE_MASK = (int)0x20,
    TIMER_ICR_COMIE_POS = 5,
    TIMER_ICR_COMIE = TIMER_ICR_COMIE_MASK,
    TIMER_ICR_TIE_MASK = (int)0x40,
    TIMER_ICR_TIE_POS = 6,
    TIMER_ICR_TIE = TIMER_ICR_TIE_MASK,
    TIMER_ICR_BIE_MASK = (int)0x80,
    TIMER_ICR_BIE_POS = 7,
    TIMER_ICR_BIE = TIMER_ICR_BIE_MASK,
    TIMER_ICR_CC1OIE_MASK = (int)0x200,
    TIMER_ICR_CC1OIE_POS = 9,
    TIMER_ICR_CC1OIE = TIMER_ICR_CC1OIE_MASK,
    TIMER_ICR_CC2OIE_MASK = (int)0x400,
    TIMER_ICR_CC2OIE_POS = 10,
    TIMER_ICR_CC2OIE = TIMER_ICR_CC2OIE_MASK,
    TIMER_ICR_CC3OIE_MASK = (int)0x800,
    TIMER_ICR_CC3OIE_POS = 11,
    TIMER_ICR_CC3OIE = TIMER_ICR_CC3OIE_MASK,
    TIMER_ICR_CC4OIE_MASK = (int)0x1000,
    TIMER_ICR_CC4OIE_POS = 12,
    TIMER_ICR_CC4OIE = TIMER_ICR_CC4OIE_MASK
};

enum TIMER_REG_EGR_FIELD
{
    TIMER_EGR_UG_MASK = (int)0x1,
    TIMER_EGR_UG_POS = 0,
    TIMER_EGR_UG = TIMER_EGR_UG_MASK,
    TIMER_EGR_CC1G_MASK = (int)0x2,
    TIMER_EGR_CC1G_POS = 1,
    TIMER_EGR_CC1G = TIMER_EGR_CC1G_MASK,
    TIMER_EGR_CC2G_MASK = (int)0x4,
    TIMER_EGR_CC2G_POS = 2,
    TIMER_EGR_CC2G = TIMER_EGR_CC2G_MASK,
    TIMER_EGR_CC3G_MASK = (int)0x8,
    TIMER_EGR_CC3G_POS = 3,
    TIMER_EGR_CC3G = TIMER_EGR_CC3G_MASK,
    TIMER_EGR_CC4G_MASK = (int)0x10,
    TIMER_EGR_CC4G_POS = 4,
    TIMER_EGR_CC4G = TIMER_EGR_CC4G_MASK,
    TIMER_EGR_COMG_MASK = (int)0x20,
    TIMER_EGR_COMG_POS = 5,
    TIMER_EGR_COMG = TIMER_EGR_COMG_MASK,
    TIMER_EGR_TG_MASK = (int)0x40,
    TIMER_EGR_TG_POS = 6,
    TIMER_EGR_TG = TIMER_EGR_TG_MASK,
    TIMER_EGR_BG_MASK = (int)0x80,
    TIMER_EGR_BG_POS = 7,
    TIMER_EGR_BG = TIMER_EGR_BG_MASK
};

enum TIMER_REG_CCMR1_FIELD
{
    TIMER_CCMR1_CC1S_MASK = (int)0x3,
    TIMER_CCMR1_CC1S_POS = 0,
    TIMER_CCMR1_CC1S = TIMER_CCMR1_CC1S_MASK,
    TIMER_CCMR1_CC1S_0 = 1 << TIMER_CCMR1_CC1S_POS,
    TIMER_CCMR1_CC1S_1 = 2 << TIMER_CCMR1_CC1S_POS,
    TIMER_CCMR1_OC1FE_MASK = (int)0x4,
    TIMER_CCMR1_OC1FE_POS = 2,
    TIMER_CCMR1_OC1FE = TIMER_CCMR1_OC1FE_MASK,
    TIMER_CCMR1_OC1PE_MASK = (int)0x8,
    TIMER_CCMR1_OC1PE_POS = 3,
    TIMER_CCMR1_OC1PE = TIMER_CCMR1_OC1PE_MASK,
    TIMER_CCMR1_OC1M_MASK = (int)0x70,
    TIMER_CCMR1_OC1M_POS = 4,
    TIMER_CCMR1_OC1M = TIMER_CCMR1_OC1M_MASK,
    TIMER_CCMR1_OC1M_0 = 1 << TIMER_CCMR1_OC1M_POS,
    TIMER_CCMR1_OC1M_1 = 2 << TIMER_CCMR1_OC1M_POS,
    TIMER_CCMR1_OC1M_2 = 4 << TIMER_CCMR1_OC1M_POS,
    TIMER_CCMR1_OC1CE_MASK = (int)0x80,
    TIMER_CCMR1_OC1CE_POS = 7,
    TIMER_CCMR1_OC1CE = TIMER_CCMR1_OC1CE_MASK,
    TIMER_CCMR1_CC2S_MASK = (int)0x300,
    TIMER_CCMR1_CC2S_POS = 8,
    TIMER_CCMR1_CC2S = TIMER_CCMR1_CC2S_MASK,
    TIMER_CCMR1_CC2S_0 = 1 << TIMER_CCMR1_CC2S_POS,
    TIMER_CCMR1_CC2S_1 = 2 << TIMER_CCMR1_CC2S_POS,
    TIMER_CCMR1_OC2FE_MASK = (int)0x400,
    TIMER_CCMR1_OC2FE_POS = 10,
    TIMER_CCMR1_OC2FE = TIMER_CCMR1_OC2FE_MASK,
    TIMER_CCMR1_OC2PE_MASK = (int)0x800,
    TIMER_CCMR1_OC2PE_POS = 11,
    TIMER_CCMR1_OC2PE = TIMER_CCMR1_OC2PE_MASK,
    TIMER_CCMR1_OC2M_MASK = (int)0x7000,
    TIMER_CCMR1_OC2M_POS = 12,
    TIMER_CCMR1_OC2M = TIMER_CCMR1_OC2M_MASK,
    TIMER_CCMR1_OC2M_0 = 1 << TIMER_CCMR1_OC2M_POS,
    TIMER_CCMR1_OC2M_1 = 2 << TIMER_CCMR1_OC2M_POS,
    TIMER_CCMR1_OC2M_2 = 4 << TIMER_CCMR1_OC2M_POS,
    TIMER_CCMR1_OC2CE_MASK = (int)0x8000,
    TIMER_CCMR1_OC2CE_POS = 15,
    TIMER_CCMR1_OC2CE = TIMER_CCMR1_OC2CE_MASK,
    TIMER_CCMR1_IC1PSC_MASK = (int)0xc,
    TIMER_CCMR1_IC1PSC_POS = 2,
    TIMER_CCMR1_IC1PSC = TIMER_CCMR1_IC1PSC_MASK,
    TIMER_CCMR1_IC1PSC_0 = 1 << TIMER_CCMR1_IC1PSC_POS,
    TIMER_CCMR1_IC1PSC_1 = 2 << TIMER_CCMR1_IC1PSC_POS,
    TIMER_CCMR1_IC1F_MASK = (int)0xf0,
    TIMER_CCMR1_IC1F_POS = 4,
    TIMER_CCMR1_IC1F = TIMER_CCMR1_IC1F_MASK,
    TIMER_CCMR1_IC1F_0 = 1 << TIMER_CCMR1_IC1F_POS,
    TIMER_CCMR1_IC1F_1 = 2 << TIMER_CCMR1_IC1F_POS,
    TIMER_CCMR1_IC1F_2 = 4 << TIMER_CCMR1_IC1F_POS,
    TIMER_CCMR1_IC1F_3 = 8 << TIMER_CCMR1_IC1F_POS,
    TIMER_CCMR1_IC2PSC_MASK = (int)0xc00,
    TIMER_CCMR1_IC2PSC_POS = 10,
    TIMER_CCMR1_IC2PSC = TIMER_CCMR1_IC2PSC_MASK,
    TIMER_CCMR1_IC2PSC_0 = 1 << TIMER_CCMR1_IC2PSC_POS,
    TIMER_CCMR1_IC2PSC_1 = 2 << TIMER_CCMR1_IC2PSC_POS,
    TIMER_CCMR1_IC2F_MASK = (int)0xf000,
    TIMER_CCMR1_IC2F_POS = 12,
    TIMER_CCMR1_IC2F = TIMER_CCMR1_IC2F_MASK,
    TIMER_CCMR1_IC2F_0 = 1 << TIMER_CCMR1_IC2F_POS,
    TIMER_CCMR1_IC2F_1 = 2 << TIMER_CCMR1_IC2F_POS,
    TIMER_CCMR1_IC2F_2 = 4 << TIMER_CCMR1_IC2F_POS,
    TIMER_CCMR1_IC2F_3 = 8 << TIMER_CCMR1_IC2F_POS
};

enum TIMER_REG_CCMR2_FIELD
{
    TIMER_CCMR2_CC3S_MASK = (int)0x3,
    TIMER_CCMR2_CC3S_POS = 0,
    TIMER_CCMR2_CC3S = TIMER_CCMR2_CC3S_MASK,
    TIMER_CCMR2_CC3S_0 = 1 << TIMER_CCMR2_CC3S_POS,
    TIMER_CCMR2_CC3S_1 = 2 << TIMER_CCMR2_CC3S_POS,
    TIMER_CCMR2_OC3FE_MASK = (int)0x4,
    TIMER_CCMR2_OC3FE_POS = 2,
    TIMER_CCMR2_OC3FE = TIMER_CCMR2_OC3FE_MASK,
    TIMER_CCMR2_OC3PE_MASK = (int)0x8,
    TIMER_CCMR2_OC3PE_POS = 3,
    TIMER_CCMR2_OC3PE = TIMER_CCMR2_OC3PE_MASK,
    TIMER_CCMR2_OC3M_MASK = (int)0x70,
    TIMER_CCMR2_OC3M_POS = 4,
    TIMER_CCMR2_OC3M = TIMER_CCMR2_OC3M_MASK,
    TIMER_CCMR2_OC3M_0 = 1 << TIMER_CCMR2_OC3M_POS,
    TIMER_CCMR2_OC3M_1 = 2 << TIMER_CCMR2_OC3M_POS,
    TIMER_CCMR2_OC3M_2 = 4 << TIMER_CCMR2_OC3M_POS,
    TIMER_CCMR2_OC3CE_MASK = (int)0x80,
    TIMER_CCMR2_OC3CE_POS = 7,
    TIMER_CCMR2_OC3CE = TIMER_CCMR2_OC3CE_MASK,
    TIMER_CCMR2_CC4S_MASK = (int)0x300,
    TIMER_CCMR2_CC4S_POS = 8,
    TIMER_CCMR2_CC4S = TIMER_CCMR2_CC4S_MASK,
    TIMER_CCMR2_CC4S_0 = 1 << TIMER_CCMR2_CC4S_POS,
    TIMER_CCMR2_CC4S_1 = 2 << TIMER_CCMR2_CC4S_POS,
    TIMER_CCMR2_OC4FE_MASK = (int)0x400,
    TIMER_CCMR2_OC4FE_POS = 10,
    TIMER_CCMR2_OC4FE = TIMER_CCMR2_OC4FE_MASK,
    TIMER_CCMR2_OC4PE_MASK = (int)0x800,
    TIMER_CCMR2_OC4PE_POS = 11,
    TIMER_CCMR2_OC4PE = TIMER_CCMR2_OC4PE_MASK,
    TIMER_CCMR2_OC4M_MASK = (int)0x7000,
    TIMER_CCMR2_OC4M_POS = 12,
    TIMER_CCMR2_OC4M = TIMER_CCMR2_OC4M_MASK,
    TIMER_CCMR2_OC4M_0 = 1 << TIMER_CCMR2_OC4M_POS,
    TIMER_CCMR2_OC4M_1 = 2 << TIMER_CCMR2_OC4M_POS,
    TIMER_CCMR2_OC4M_2 = 4 << TIMER_CCMR2_OC4M_POS,
    TIMER_CCMR2_OC4CE_MASK = (int)0x8000,
    TIMER_CCMR2_OC4CE_POS = 15,
    TIMER_CCMR2_OC4CE = TIMER_CCMR2_OC4CE_MASK,
    TIMER_CCMR2_IC3PSC_MASK = (int)0xc,
    TIMER_CCMR2_IC3PSC_POS = 2,
    TIMER_CCMR2_IC3PSC = TIMER_CCMR2_IC3PSC_MASK,
    TIMER_CCMR2_IC3PSC_0 = 1 << TIMER_CCMR2_IC3PSC_POS,
    TIMER_CCMR2_IC3PSC_1 = 2 << TIMER_CCMR2_IC3PSC_POS,
    TIMER_CCMR2_IC3F_MASK = (int)0xf0,
    TIMER_CCMR2_IC3F_POS = 4,
    TIMER_CCMR2_IC3F = TIMER_CCMR2_IC3F_MASK,
    TIMER_CCMR2_IC3F_0 = 1 << TIMER_CCMR2_IC3F_POS,
    TIMER_CCMR2_IC3F_1 = 2 << TIMER_CCMR2_IC3F_POS,
    TIMER_CCMR2_IC3F_2 = 4 << TIMER_CCMR2_IC3F_POS,
    TIMER_CCMR2_IC3F_3 = 8 << TIMER_CCMR2_IC3F_POS,
    TIMER_CCMR2_IC4PSC_MASK = (int)0xc00,
    TIMER_CCMR2_IC4PSC_POS = 10,
    TIMER_CCMR2_IC4PSC = TIMER_CCMR2_IC4PSC_MASK,
    TIMER_CCMR2_IC4PSC_0 = 1 << TIMER_CCMR2_IC4PSC_POS,
    TIMER_CCMR2_IC4PSC_1 = 2 << TIMER_CCMR2_IC4PSC_POS,
    TIMER_CCMR2_IC4F_MASK = (int)0xf000,
    TIMER_CCMR2_IC4F_POS = 12,
    TIMER_CCMR2_IC4F = TIMER_CCMR2_IC4F_MASK,
    TIMER_CCMR2_IC4F_0 = 1 << TIMER_CCMR2_IC4F_POS,
    TIMER_CCMR2_IC4F_1 = 2 << TIMER_CCMR2_IC4F_POS,
    TIMER_CCMR2_IC4F_2 = 4 << TIMER_CCMR2_IC4F_POS,
    TIMER_CCMR2_IC4F_3 = 8 << TIMER_CCMR2_IC4F_POS
};

enum TIMER_REG_CCER_FIELD
{
    TIMER_CCER_CC1E_MASK = (int)0x1,
    TIMER_CCER_CC1E_POS = 0,
    TIMER_CCER_CC1E = TIMER_CCER_CC1E_MASK,
    TIMER_CCER_CC1P_MASK = (int)0x2,
    TIMER_CCER_CC1P_POS = 1,
    TIMER_CCER_CC1P = TIMER_CCER_CC1P_MASK,
    TIMER_CCER_CC1NE_MASK = (int)0x4,
    TIMER_CCER_CC1NE_POS = 2,
    TIMER_CCER_CC1NE = TIMER_CCER_CC1NE_MASK,
    TIMER_CCER_CC1NP_MASK = (int)0x8,
    TIMER_CCER_CC1NP_POS = 3,
    TIMER_CCER_CC1NP = TIMER_CCER_CC1NP_MASK,
    TIMER_CCER_CC2E_MASK = (int)0x10,
    TIMER_CCER_CC2E_POS = 4,
    TIMER_CCER_CC2E = TIMER_CCER_CC2E_MASK,
    TIMER_CCER_CC2P_MASK = (int)0x20,
    TIMER_CCER_CC2P_POS = 5,
    TIMER_CCER_CC2P = TIMER_CCER_CC2P_MASK,
    TIMER_CCER_CC2NE_MASK = (int)0x40,
    TIMER_CCER_CC2NE_POS = 6,
    TIMER_CCER_CC2NE = TIMER_CCER_CC2NE_MASK,
    TIMER_CCER_CC2NP_MASK = (int)0x80,
    TIMER_CCER_CC2NP_POS = 7,
    TIMER_CCER_CC2NP = TIMER_CCER_CC2NP_MASK,
    TIMER_CCER_CC3E_MASK = (int)0x100,
    TIMER_CCER_CC3E_POS = 8,
    TIMER_CCER_CC3E = TIMER_CCER_CC3E_MASK,
    TIMER_CCER_CC3P_MASK = (int)0x200,
    TIMER_CCER_CC3P_POS = 9,
    TIMER_CCER_CC3P = TIMER_CCER_CC3P_MASK,
    TIMER_CCER_CC3NE_MASK = (int)0x400,
    TIMER_CCER_CC3NE_POS = 10,
    TIMER_CCER_CC3NE = TIMER_CCER_CC3NE_MASK,
    TIMER_CCER_CC3NP_MASK = (int)0x800,
    TIMER_CCER_CC3NP_POS = 11,
    TIMER_CCER_CC3NP = TIMER_CCER_CC3NP_MASK,
    TIMER_CCER_CC4E_MASK = (int)0x1000,
    TIMER_CCER_CC4E_POS = 12,
    TIMER_CCER_CC4E = TIMER_CCER_CC4E_MASK,
    TIMER_CCER_CC4P_MASK = (int)0x2000,
    TIMER_CCER_CC4P_POS = 13,
    TIMER_CCER_CC4P = TIMER_CCER_CC4P_MASK
};

enum TIMER_REG_CNT_FIELD
{
    TIMER_CNT_CNT_MASK = (int)0xffffffff,
    TIMER_CNT_CNT_POS = 0,
    TIMER_CNT_CNT = TIMER_CNT_CNT_MASK,
    TIMER_CNT_CNT_0 = 1 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_1 = 2 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_2 = 4 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_3 = 8 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_4 = 16 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_5 = 32 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_6 = 64 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_7 = 128 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_8 = 256 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_9 = 512 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_10 = 1024 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_11 = 2048 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_12 = 4096 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_13 = 8192 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_14 = 16384 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_15 = 32768 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_16 = 65536 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_17 = 131072 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_18 = 262144 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_19 = 524288 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_20 = 1048576 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_21 = 2097152 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_22 = 4194304 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_23 = 8388608 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_24 = 16777216 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_25 = 33554432 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_26 = 67108864 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_27 = 134217728 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_28 = 268435456 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_29 = 536870912 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_30 = 1073741824 << TIMER_CNT_CNT_POS,
    TIMER_CNT_CNT_31 = -2147483648 << TIMER_CNT_CNT_POS
};

enum TIMER_REG_PSC_FIELD
{
    TIMER_PSC_PSC_MASK = (int)0xffff,
    TIMER_PSC_PSC_POS = 0,
    TIMER_PSC_PSC = TIMER_PSC_PSC_MASK,
    TIMER_PSC_PSC_0 = 1 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_1 = 2 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_2 = 4 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_3 = 8 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_4 = 16 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_5 = 32 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_6 = 64 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_7 = 128 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_8 = 256 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_9 = 512 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_10 = 1024 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_11 = 2048 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_12 = 4096 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_13 = 8192 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_14 = 16384 << TIMER_PSC_PSC_POS,
    TIMER_PSC_PSC_15 = 32768 << TIMER_PSC_PSC_POS
};

enum TIMER_REG_ARR_FIELD
{
    TIMER_ARR_ARR_MASK = (int)0xffff,
    TIMER_ARR_ARR_POS = 0,
    TIMER_ARR_ARR = TIMER_ARR_ARR_MASK,
    TIMER_ARR_ARR_0 = 1 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_1 = 2 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_2 = 4 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_3 = 8 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_4 = 16 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_5 = 32 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_6 = 64 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_7 = 128 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_8 = 256 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_9 = 512 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_10 = 1024 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_11 = 2048 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_12 = 4096 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_13 = 8192 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_14 = 16384 << TIMER_ARR_ARR_POS,
    TIMER_ARR_ARR_15 = 32768 << TIMER_ARR_ARR_POS
};

enum TIMER_REG_REP_FIELD
{
    TIMER_REP_REP_MASK = (int)0xffff,
    TIMER_REP_REP_POS = 0,
    TIMER_REP_REP = TIMER_REP_REP_MASK,
    TIMER_REP_REP_0 = 1 << TIMER_REP_REP_POS,
    TIMER_REP_REP_1 = 2 << TIMER_REP_REP_POS,
    TIMER_REP_REP_2 = 4 << TIMER_REP_REP_POS,
    TIMER_REP_REP_3 = 8 << TIMER_REP_REP_POS,
    TIMER_REP_REP_4 = 16 << TIMER_REP_REP_POS,
    TIMER_REP_REP_5 = 32 << TIMER_REP_REP_POS,
    TIMER_REP_REP_6 = 64 << TIMER_REP_REP_POS,
    TIMER_REP_REP_7 = 128 << TIMER_REP_REP_POS,
    TIMER_REP_REP_8 = 256 << TIMER_REP_REP_POS,
    TIMER_REP_REP_9 = 512 << TIMER_REP_REP_POS,
    TIMER_REP_REP_10 = 1024 << TIMER_REP_REP_POS,
    TIMER_REP_REP_11 = 2048 << TIMER_REP_REP_POS,
    TIMER_REP_REP_12 = 4096 << TIMER_REP_REP_POS,
    TIMER_REP_REP_13 = 8192 << TIMER_REP_REP_POS,
    TIMER_REP_REP_14 = 16384 << TIMER_REP_REP_POS,
    TIMER_REP_REP_15 = 32768 << TIMER_REP_REP_POS
};

enum TIMER_REG_CCR1_FIELD
{
    TIMER_CCR1_CCR1_MASK = (int)0xffffffff,
    TIMER_CCR1_CCR1_POS = 0,
    TIMER_CCR1_CCR1 = TIMER_CCR1_CCR1_MASK,
    TIMER_CCR1_CCR1_0 = 1 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_1 = 2 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_2 = 4 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_3 = 8 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_4 = 16 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_5 = 32 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_6 = 64 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_7 = 128 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_8 = 256 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_9 = 512 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_10 = 1024 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_11 = 2048 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_12 = 4096 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_13 = 8192 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_14 = 16384 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_15 = 32768 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_16 = 65536 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_17 = 131072 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_18 = 262144 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_19 = 524288 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_20 = 1048576 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_21 = 2097152 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_22 = 4194304 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_23 = 8388608 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_24 = 16777216 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_25 = 33554432 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_26 = 67108864 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_27 = 134217728 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_28 = 268435456 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_29 = 536870912 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_30 = 1073741824 << TIMER_CCR1_CCR1_POS,
    TIMER_CCR1_CCR1_31 = -2147483648 << TIMER_CCR1_CCR1_POS
};

enum TIMER_REG_CCR2_FIELD
{
    TIMER_CCR2_CCR2_MASK = (int)0xffffffff,
    TIMER_CCR2_CCR2_POS = 0,
    TIMER_CCR2_CCR2 = TIMER_CCR2_CCR2_MASK,
    TIMER_CCR2_CCR2_0 = 1 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_1 = 2 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_2 = 4 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_3 = 8 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_4 = 16 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_5 = 32 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_6 = 64 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_7 = 128 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_8 = 256 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_9 = 512 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_10 = 1024 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_11 = 2048 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_12 = 4096 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_13 = 8192 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_14 = 16384 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_15 = 32768 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_16 = 65536 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_17 = 131072 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_18 = 262144 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_19 = 524288 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_20 = 1048576 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_21 = 2097152 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_22 = 4194304 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_23 = 8388608 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_24 = 16777216 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_25 = 33554432 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_26 = 67108864 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_27 = 134217728 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_28 = 268435456 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_29 = 536870912 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_30 = 1073741824 << TIMER_CCR2_CCR2_POS,
    TIMER_CCR2_CCR2_31 = -2147483648 << TIMER_CCR2_CCR2_POS
};

enum TIMER_REG_CCR3_FIELD
{
    TIMER_CCR3_CCR3_MASK = (int)0xffffffff,
    TIMER_CCR3_CCR3_POS = 0,
    TIMER_CCR3_CCR3 = TIMER_CCR3_CCR3_MASK,
    TIMER_CCR3_CCR3_0 = 1 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_1 = 2 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_2 = 4 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_3 = 8 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_4 = 16 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_5 = 32 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_6 = 64 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_7 = 128 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_8 = 256 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_9 = 512 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_10 = 1024 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_11 = 2048 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_12 = 4096 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_13 = 8192 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_14 = 16384 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_15 = 32768 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_16 = 65536 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_17 = 131072 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_18 = 262144 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_19 = 524288 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_20 = 1048576 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_21 = 2097152 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_22 = 4194304 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_23 = 8388608 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_24 = 16777216 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_25 = 33554432 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_26 = 67108864 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_27 = 134217728 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_28 = 268435456 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_29 = 536870912 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_30 = 1073741824 << TIMER_CCR3_CCR3_POS,
    TIMER_CCR3_CCR3_31 = -2147483648 << TIMER_CCR3_CCR3_POS
};

enum TIMER_REG_CCR4_FIELD
{
    TIMER_CCR4_CCR4_MASK = (int)0xffffffff,
    TIMER_CCR4_CCR4_POS = 0,
    TIMER_CCR4_CCR4 = TIMER_CCR4_CCR4_MASK,
    TIMER_CCR4_CCR4_0 = 1 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_1 = 2 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_2 = 4 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_3 = 8 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_4 = 16 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_5 = 32 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_6 = 64 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_7 = 128 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_8 = 256 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_9 = 512 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_10 = 1024 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_11 = 2048 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_12 = 4096 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_13 = 8192 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_14 = 16384 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_15 = 32768 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_16 = 65536 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_17 = 131072 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_18 = 262144 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_19 = 524288 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_20 = 1048576 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_21 = 2097152 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_22 = 4194304 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_23 = 8388608 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_24 = 16777216 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_25 = 33554432 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_26 = 67108864 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_27 = 134217728 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_28 = 268435456 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_29 = 536870912 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_30 = 1073741824 << TIMER_CCR4_CCR4_POS,
    TIMER_CCR4_CCR4_31 = -2147483648 << TIMER_CCR4_CCR4_POS
};

enum TIMER_REG_BDTR_FIELD
{
    TIMER_BDTR_DTG_MASK = (int)0xff,
    TIMER_BDTR_DTG_POS = 0,
    TIMER_BDTR_DTG = TIMER_BDTR_DTG_MASK,
    TIMER_BDTR_DTG_0 = 1 << TIMER_BDTR_DTG_POS,
    TIMER_BDTR_DTG_1 = 2 << TIMER_BDTR_DTG_POS,
    TIMER_BDTR_DTG_2 = 4 << TIMER_BDTR_DTG_POS,
    TIMER_BDTR_DTG_3 = 8 << TIMER_BDTR_DTG_POS,
    TIMER_BDTR_DTG_4 = 16 << TIMER_BDTR_DTG_POS,
    TIMER_BDTR_DTG_5 = 32 << TIMER_BDTR_DTG_POS,
    TIMER_BDTR_DTG_6 = 64 << TIMER_BDTR_DTG_POS,
    TIMER_BDTR_DTG_7 = 128 << TIMER_BDTR_DTG_POS,
    TIMER_BDTR_LOCK_MASK = (int)0x300,
    TIMER_BDTR_LOCK_POS = 8,
    TIMER_BDTR_LOCK = TIMER_BDTR_LOCK_MASK,
    TIMER_BDTR_LOCK_0 = 1 << TIMER_BDTR_LOCK_POS,
    TIMER_BDTR_LOCK_1 = 2 << TIMER_BDTR_LOCK_POS,
    TIMER_BDTR_OSSI_MASK = (int)0x400,
    TIMER_BDTR_OSSI_POS = 10,
    TIMER_BDTR_OSSI = TIMER_BDTR_OSSI_MASK,
    TIMER_BDTR_OSSR_MASK = (int)0x800,
    TIMER_BDTR_OSSR_POS = 11,
    TIMER_BDTR_OSSR = TIMER_BDTR_OSSR_MASK,
    TIMER_BDTR_BKE_MASK = (int)0x1000,
    TIMER_BDTR_BKE_POS = 12,
    TIMER_BDTR_BKE = TIMER_BDTR_BKE_MASK,
    TIMER_BDTR_BKP_MASK = (int)0x2000,
    TIMER_BDTR_BKP_POS = 13,
    TIMER_BDTR_BKP = TIMER_BDTR_BKP_MASK,
    TIMER_BDTR_AOE_MASK = (int)0x4000,
    TIMER_BDTR_AOE_POS = 14,
    TIMER_BDTR_AOE = TIMER_BDTR_AOE_MASK,
    TIMER_BDTR_MOE_MASK = (int)0x8000,
    TIMER_BDTR_MOE_POS = 15,
    TIMER_BDTR_MOE = TIMER_BDTR_MOE_MASK
};

enum TIMER_REG_DMAEN_FIELD
{
    TIMER_DMAEN_UDE_MASK = (int)0x1,
    TIMER_DMAEN_UDE_POS = 0,
    TIMER_DMAEN_UDE = TIMER_DMAEN_UDE_MASK,
    TIMER_DMAEN_CC1DE_MASK = (int)0x2,
    TIMER_DMAEN_CC1DE_POS = 1,
    TIMER_DMAEN_CC1DE = TIMER_DMAEN_CC1DE_MASK,
    TIMER_DMAEN_CC2DE_MASK = (int)0x4,
    TIMER_DMAEN_CC2DE_POS = 2,
    TIMER_DMAEN_CC2DE = TIMER_DMAEN_CC2DE_MASK,
    TIMER_DMAEN_CC3DE_MASK = (int)0x8,
    TIMER_DMAEN_CC3DE_POS = 3,
    TIMER_DMAEN_CC3DE = TIMER_DMAEN_CC3DE_MASK,
    TIMER_DMAEN_CC4DE_MASK = (int)0x10,
    TIMER_DMAEN_CC4DE_POS = 4,
    TIMER_DMAEN_CC4DE = TIMER_DMAEN_CC4DE_MASK,
    TIMER_DMAEN_COMDE_MASK = (int)0x20,
    TIMER_DMAEN_COMDE_POS = 5,
    TIMER_DMAEN_COMDE = TIMER_DMAEN_COMDE_MASK,
    TIMER_DMAEN_TDE_MASK = (int)0x40,
    TIMER_DMAEN_TDE_POS = 6,
    TIMER_DMAEN_TDE = TIMER_DMAEN_TDE_MASK
};

#endif