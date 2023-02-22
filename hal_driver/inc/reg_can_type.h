#ifndef REG_BXCAN_TYPE_H_
#define REG_BXCAN_TYPE_H_
#include <stdint.h>

#define LSBXCAN ((reg_bxcan_t *)0x4000E000)

typedef struct
{
    volatile uint32_t TIR;
    volatile uint32_t TDTR;
    volatile uint32_t TDLR;
    volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;

typedef struct
{
    volatile uint32_t RIR;
    volatile uint32_t RDTR;
    volatile uint32_t RDLR;
    volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;

typedef struct
{
    volatile uint32_t FR1;
    volatile uint32_t FR2;
}CAN_FilterRegister_TypeDef;

typedef struct
{
    volatile uint32_t CAN_MCR; //0x0
    volatile uint32_t CAN_MSR; //0x4
    volatile uint32_t CAN_TSR; //0x8
    volatile uint32_t CAN_RF0R; //0xc
    volatile uint32_t CAN_RF1R; //0x10
    volatile uint32_t CAN_IER; //0x14
    volatile uint32_t CAN_ESR; //0x18
    volatile uint32_t CAN_BTR; //0x1c
    volatile uint32_t RESERVED0[88];
    CAN_TxMailBox_TypeDef sTxMailBox[3];
    CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
    volatile uint32_t RESERVED1[12];
    volatile uint32_t CAN_FMR; //0x200
    volatile uint32_t CAN_FM1R; //0x204
    volatile uint32_t RESERVED2[1];
    volatile uint32_t CAN_FS1R; //0x20c
    volatile uint32_t RESERVED3[1];
    volatile uint32_t CAN_FFA1R; //0x214
    volatile uint32_t RESERVED4[1];
    volatile uint32_t CAN_FA1R; //0x21c
    volatile uint32_t RESERVED5[8];
    CAN_FilterRegister_TypeDef sFilterRegister[14];
}reg_bxcan_t;

enum BXCAN_REG_CAN_MCR_FIELD
{
    BXCAN_DBF_MASK = (int)0x10000,
    BXCAN_DBF_POS = 16,
    BXCAN_RESET_MASK = (int)0x8000,
    BXCAN_RESET_POS = 15,
    BXCAN_TTCM_MASK = (int)0x80,
    BXCAN_TTCM_POS = 7,
    BXCAN_ABOM_MASK = (int)0x40,
    BXCAN_ABOM_POS = 6,
    BXCAN_AWUM_MASK = (int)0x20,
    BXCAN_AWUM_POS = 5,
    BXCAN_NART_MASK = (int)0x10,
    BXCAN_NART_POS = 4,
    BXCAN_RFLM_MASK = (int)0x8,
    BXCAN_RFLM_POS = 3,
    BXCAN_TXFP_MASK = (int)0x4,
    BXCAN_TXFP_POS = 2,
    BXCAN_SLEEP_MASK = (int)0x2,
    BXCAN_SLEEP_POS = 1,
    BXCAN_INRQ_MASK = (int)0x1,
    BXCAN_INRQ_POS = 0,
};

enum BXCAN_REG_CAN_MSR_FIELD
{
    BXCAN_RX_MASK = (int)0x800,
    BXCAN_RX_POS = 11,
    BXCAN_SAMP_MASK = (int)0x400,
    BXCAN_SAMP_POS = 10,
    BXCAN_RXM_MASK = (int)0x200,
    BXCAN_RXM_POS = 9,
    BXCAN_TXM_MASK = (int)0x100,
    BXCAN_TXM_POS = 8,
    BXCAN_SLAKI_MASK = (int)0x10,
    BXCAN_SLAKI_POS = 4,
    BXCAN_WKUI_MASK = (int)0x8,
    BXCAN_WKUI_POS = 3,
    BXCAN_ERRI_MASK = (int)0x4,
    BXCAN_ERRI_POS = 2,
    BXCAN_SLAK_MASK = (int)0x2,
    BXCAN_SLAK_POS = 1,
    BXCAN_INAK_MASK = (int)0x1,
    BXCAN_INAK_POS = 0,
};

enum BXCAN_REG_CAN_TSR_FIELD
{
    BXCAN_LOW2_MASK = (int)0x80000000,
    BXCAN_LOW2_POS = 31,
    BXCAN_LOW1_MASK = (int)0x40000000,
    BXCAN_LOW1_POS = 30,
    BXCAN_LOW0_MASK = (int)0x20000000,
    BXCAN_LOW0_POS = 29,
    BXCAN_TME2_MASK = (int)0x10000000,
    BXCAN_TME2_POS = 28,
    BXCAN_TME1_MASK = (int)0x8000000,
    BXCAN_TME1_POS = 27,
    BXCAN_TME0_MASK = (int)0x4000000,
    BXCAN_TME0_POS = 26,
    BXCAN_CODE_MASK = (int)0x3000000,
    BXCAN_CODE_POS = 24,
    BXCAN_ABRQ2_MASK = (int)0x800000,
    BXCAN_ABRQ2_POS = 23,
    BXCAN_TERR2_MASK = (int)0x80000,
    BXCAN_TERR2_POS = 19,
    BXCAN_ALST2_MASK = (int)0x40000,
    BXCAN_ALST2_POS = 18,
    BXCAN_TXOK2_MASK = (int)0x20000,
    BXCAN_TXOK2_POS = 17,
    BXCAN_RQCP2_MASK = (int)0x10000,
    BXCAN_RQCP2_POS = 16,
    BXCAN_ABRQ1_MASK = (int)0x8000,
    BXCAN_ABRQ1_POS = 15,
    BXCAN_TERR1_MASK = (int)0x800,
    BXCAN_TERR1_POS = 11,
    BXCAN_ALST1_MASK = (int)0x400,
    BXCAN_ALST1_POS = 10,
    BXCAN_TXOK1_MASK = (int)0x200,
    BXCAN_TXOK1_POS = 9,
    BXCAN_RQCP1_MASK = (int)0x100,
    BXCAN_RQCP1_POS = 8,
    BXCAN_ABRQ0_MASK = (int)0x80,
    BXCAN_ABRQ0_POS = 7,
    BXCAN_TERR0_MASK = (int)0x8,
    BXCAN_TERR0_POS = 3,
    BXCAN_ALST0_MASK = (int)0x4,
    BXCAN_ALST0_POS = 2,
    BXCAN_TXOK0_MASK = (int)0x2,
    BXCAN_TXOK0_POS = 1,
    BXCAN_RQCP0_MASK = (int)0x1,
    BXCAN_RQCP0_POS = 0,
};

enum BXCAN_REG_CAN_RF0R_FIELD
{
    BXCAN_RFOM0_MASK = (int)0x20,
    BXCAN_RFOM0_POS = 5,
    BXCAN_FOVR0_MASK = (int)0x10,
    BXCAN_FOVR0_POS = 4,
    BXCAN_FULL0_MASK = (int)0x8,
    BXCAN_FULL0_POS = 3,
    BXCAN_FMP0_MASK = (int)0x3,
    BXCAN_FMP0_POS = 0,
};

enum BXCAN_REG_CAN_RF1R_FIELD
{
    BXCAN_RFOM1_MASK = (int)0x20,
    BXCAN_RFOM1_POS = 5,
    BXCAN_FOVR1_MASK = (int)0x10,
    BXCAN_FOVR1_POS = 4,
    BXCAN_FULL1_MASK = (int)0x8,
    BXCAN_FULL1_POS = 3,
    BXCAN_FMP1_MASK = (int)0x3,
    BXCAN_FMP1_POS = 0,
};

enum BXCAN_REG_CAN_IER_FIELD
{
    BXCAN_SLKIE_MASK = (int)0x20000,
    BXCAN_SLKIE_POS = 17,
    BXCAN_WKUIE_MASK = (int)0x10000,
    BXCAN_WKUIE_POS = 16,
    BXCAN_ERRIE_MASK = (int)0x8000,
    BXCAN_ERRIE_POS = 15,
    BXCAN_LECIE_MASK = (int)0x800,
    BXCAN_LECIE_POS = 11,
    BXCAN_BOFIE_MASK = (int)0x400,
    BXCAN_BOFIE_POS = 10,
    BXCAN_EPVIE_MASK = (int)0x200,
    BXCAN_EPVIE_POS = 9,
    BXCAN_EWGIE_MASK = (int)0x100,
    BXCAN_EWGIE_POS = 8,
    BXCAN_FOVIE1_MASK = (int)0x40,
    BXCAN_FOVIE1_POS = 6,
    BXCAN_FFIE1_MASK = (int)0x20,
    BXCAN_FFIE1_POS = 5,
    BXCAN_FMPIE1_MASK = (int)0x10,
    BXCAN_FMPIE1_POS = 4,
    BXCAN_FOVIE0_MASK = (int)0x8,
    BXCAN_FOVIE0_POS = 3,
    BXCAN_FFIE0_MASK = (int)0x4,
    BXCAN_FFIE0_POS = 2,
    BXCAN_FMPIE0_MASK = (int)0x2,
    BXCAN_FMPIE0_POS = 1,
    BXCAN_TMEIE_MASK = (int)0x1,
    BXCAN_TMEIE_POS = 0,
};

enum BXCAN_REG_CAN_ESR_FIELD
{
    BXCAN_REC_MASK = (int)0xff000000,
    BXCAN_REC_POS = 24,
    BXCAN_TEC_MASK = (int)0xff0000,
    BXCAN_TEC_POS = 16,
    BXCAN_LEC_MASK = (int)0x70,
    BXCAN_LEC_POS = 4,
    BXCAN_LEC_0 = 1 << BXCAN_LEC_POS,
    BXCAN_LEC_1 = 2 << BXCAN_LEC_POS,
    BXCAN_LEC_2 = 4 << BXCAN_LEC_POS,
    BXCAN_BOFF_MASK = (int)0x4,
    BXCAN_BOFF_POS = 2,
    BXCAN_EPVF_MASK = (int)0x2,
    BXCAN_EPVF_POS = 1,
    BXCAN_EWGF_MASK = (int)0x1,
    BXCAN_EWGF_POS = 0,
};

enum BXCAN_REG_CAN_BTR_FIELD
{
    BXCAN_SILM_MASK = (int)0x80000000,
    BXCAN_SILM_POS = 31,
    BXCAN_LBKM_MASK = (int)0x40000000,
    BXCAN_LBKM_POS = 30,
    BXCAN_SJW_MASK = (int)0x3000000,
    BXCAN_SJW_POS = 24,
    BXCAN_TS2_MASK = (int)0x700000,
    BXCAN_TS2_POS = 20,
    BXCAN_TS2_0 = 1 << BXCAN_TS2_POS,
    BXCAN_TS2_1 = 2 << BXCAN_TS2_POS,
    BXCAN_TS2_2 = 4 << BXCAN_TS2_POS,
    BXCAN_TS1_MASK = (int)0xf0000,
    BXCAN_TS1_POS = 16,
    BXCAN_TS1_0 = 1 << BXCAN_TS1_POS,
    BXCAN_TS1_1 = 2 << BXCAN_TS1_POS,
    BXCAN_TS1_2 = 4 << BXCAN_TS1_POS,
    BXCAN_TS1_3 = 8 << BXCAN_TS1_POS,
    BXCAN_BRP_MASK = (int)0x3ff,
    BXCAN_BRP_POS = 0,
};

enum BXCAN_REG_CAN_TI0R_FIELD
{
    BXCAN_T0STID_MASK = (int)0xffe00000,
    BXCAN_T0STID_POS = 21,
    BXCAN_T0EXID_MASK = (int)0x1ffff8,
    BXCAN_T0EXID_POS = 3,
    BXCAN_T0IDE_MASK = (int)0x4,
    BXCAN_T0IDE_POS = 2,
    BXCAN_T0RTR_MASK = (int)0x2,
    BXCAN_T0RTR_POS = 1,
    BXCAN_T0TXRQ_MASK = (int)0x1,
    BXCAN_T0TXRQ_POS = 0,
};

enum BXCAN_REG_CAN_TDT0R_FIELD
{
    BXCAN_T0TIME_MASK = (int)0xffff0000,
    BXCAN_T0TIME_POS = 16,
    BXCAN_T0TGT_MASK = (int)0x100,
    BXCAN_T0TGT_POS = 8,
    BXCAN_T0DLC_MASK = (int)0xf,
    BXCAN_T0DLC_POS = 0,
};

enum BXCAN_REG_CAN_TDLR_FIELD
{
    CAN_TDLR_DATA3_MASK = (int)0xff000000,
    CAN_TDLR_DATA3_POS = 24,
    CAN_TDLR_DATA2_MASK = (int)0xff0000,
    CAN_TDLR_DATA2_POS = 16,
    CAN_TDLR_DATA1_MASK = (int)0xff00,
    CAN_TDLR_DATA1_POS = 8,
    CAN_TDLR_DATA0_MASK = (int)0xff,
    CAN_TDLR_DATA0_POS = 0,
};

enum BXCAN_REG_CAN_TDHR_FIELD
{
    CAN_TDHR_DATA3_MASK = (int)0xff000000,
    CAN_TDHR_DATA3_POS = 24,
    CAN_TDHR_DATA2_MASK = (int)0xff0000,
    CAN_TDHR_DATA2_POS = 16,
    CAN_TDHR_DATA1_MASK = (int)0xff00,
    CAN_TDHR_DATA1_POS = 8,
    CAN_TDHR_DATA0_MASK = (int)0xff,
    CAN_TDHR_DATA0_POS = 0,
};

enum BXCAN_REG_CAN_TI1R_FIELD
{
    BXCAN_T1STID_MASK = (int)0xffe00000,
    BXCAN_T1STID_POS = 21,
    BXCAN_T1EXID_MASK = (int)0x1ffff8,
    BXCAN_T1EXID_POS = 3,
    BXCAN_T1IDE_MASK = (int)0x4,
    BXCAN_T1IDE_POS = 2,
    BXCAN_T1RTR_MASK = (int)0x2,
    BXCAN_T1RTR_POS = 1,
    BXCAN_T1TXRQ_MASK = (int)0x1,
    BXCAN_T1TXRQ_POS = 0,
};

enum BXCAN_REG_CAN_TDT1R_FIELD
{
    BXCAN_T1TIME_MASK = (int)0xffff0000,
    BXCAN_T1TIME_POS = 16,
    BXCAN_T1TGT_MASK = (int)0x100,
    BXCAN_T1TGT_POS = 8,
    BXCAN_T1DLC_MASK = (int)0xf,
    BXCAN_T1DLC_POS = 0,
};

enum BXCAN_REG_CAN_TI2R_FIELD
{
    BXCAN_T2STID_MASK = (int)0xffe00000,
    BXCAN_T2STID_POS = 21,
    BXCAN_T2EXID_MASK = (int)0x1ffff8,
    BXCAN_T2EXID_POS = 3,
    BXCAN_T2IDE_MASK = (int)0x4,
    BXCAN_T2IDE_POS = 2,
    BXCAN_T2RTR_MASK = (int)0x2,
    BXCAN_T2RTR_POS = 1,
    BXCAN_T2TXRQ_MASK = (int)0x1,
    BXCAN_T2TXRQ_POS = 0,
};

enum BXCAN_REG_CAN_TDT2R_FIELD
{
    BXCAN_T2TIME_MASK = (int)0xffff0000,
    BXCAN_T2TIME_POS = 16,
    BXCAN_T2TGT_MASK = (int)0x100,
    BXCAN_T2TGT_POS = 8,
    BXCAN_T2DLC_MASK = (int)0xf,
    BXCAN_T2DLC_POS = 0,
};

enum BXCAN_REG_CAN_RI0R_FIELD
{
    BXCAN_R0STID_MASK = (int)0xffe00000,
    BXCAN_R0STID_POS = 21,
    BXCAN_R0EXID_MASK = (int)0x1ffff8,
    BXCAN_R0EXID_POS = 3,
    BXCAN_R0IDE_MASK = (int)0x4,
    BXCAN_R0IDE_POS = 2,
    BXCAN_R0RTR_MASK = (int)0x2,
    BXCAN_R0RTR_POS = 1,
};

enum BXCAN_REG_CAN_RDT0R_FIELD
{
    BXCAN_R0TIME_MASK = (int)0xffff0000,
    BXCAN_R0TIME_POS = 16,
    BXCAN_R0FMI_MASK = (int)0xff00,
    BXCAN_R0FMI_POS = 8,
    BXCAN_R0DLC_MASK = (int)0xf,
    BXCAN_R0DLC_POS = 0,
};

enum BXCAN_REG_CAN_RI1R_FIELD
{
    BXCAN_R1STID_MASK = (int)0xffe00000,
    BXCAN_R1STID_POS = 21,
    BXCAN_R1EXID_MASK = (int)0x1ffff8,
    BXCAN_R1EXID_POS = 3,
    BXCAN_R1IDE_MASK = (int)0x4,
    BXCAN_R1IDE_POS = 2,
    BXCAN_R1RTR_MASK = (int)0x2,
    BXCAN_R1RTR_POS = 1,
};

enum BXCAN_REG_CAN_RDT1R_FIELD
{
    BXCAN_R1TIME_MASK = (int)0xffff0000,
    BXCAN_R1TIME_POS = 16,
    BXCAN_R1FMI_MASK = (int)0xff00,
    BXCAN_R1FMI_POS = 8,
    BXCAN_R1DLC_MASK = (int)0xf,
    BXCAN_R1DLC_POS = 0,
};

enum BXCAN_REG_CAN_FMR_FIELD
{
    BXCAN_FINIT_MASK = (int)0x1,
    BXCAN_FINIT_POS = 0,
};

enum BXCAN_REG_CAN_FM1R_FIELD
{
    BXCAN_FBM_MASK = (int)0x3fff,
    BXCAN_FBM_POS = 0,
};

enum BXCAN_REG_CAN_FS1R_FIELD
{
    BXCAN_FSC_MASK = (int)0x3fff,
    BXCAN_FSC_POS = 0,
};

enum BXCAN_REG_CAN_FFA1R_FIELD
{
    BXCAN_FFA_MASK = (int)0x3fff,
    BXCAN_FFA_POS = 0,
};

enum BXCAN_REG_CAN_FA1R_FIELD
{
    BXCAN_FACT_MASK = (int)0x3fff,
    BXCAN_FACT_POS = 0,
};

#endif

