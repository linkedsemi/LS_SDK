#ifndef REG_FDCAN_TYPE_H_
#define REG_FDCAN_TYPE_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t ID_VER; //0x0
    volatile uint32_t MODE_CFG; //0x4
    volatile uint32_t STT; //0x8
    volatile uint32_t CMD; //0xc
    volatile uint32_t INT_STT; //0x10
    volatile uint32_t INT_SET; //0x14
    volatile uint32_t INT_CLR; //0x18
    volatile uint32_t IMSK_SET; //0x1c
    volatile uint32_t IMSK_CLR; //0x20
    volatile uint32_t BTR; //0x24
    volatile uint32_t BTR_FD; //0x28
    volatile uint32_t EWL_ERP; //0x2c
    volatile uint32_t REC_TEC; //0x30
    volatile uint32_t ERR; //0x34
    volatile uint32_t CTR_PRES; //0x38
    volatile uint32_t FILTER_A_MSK; //0x3c
    volatile uint32_t FILTER_A_VAL; //0x40
    volatile uint32_t FILTER_B_MSK; //0x44
    volatile uint32_t FILTER_B_VAL; //0x48
    volatile uint32_t FILTER_C_MSK; //0x4c
    volatile uint32_t FILTER_C_VAL; //0x50
    volatile uint32_t FILTER_RANGE_L; //0x54
    volatile uint32_t FILTER_RANGE_H; //0x58
    volatile uint32_t FILTER_CTRL_STT; //0x5c
    volatile uint32_t RX_MEM_INFO; //0x60
    volatile uint32_t RX_PTR; //0x64
    volatile uint32_t RX_STT; //0x68
    volatile uint32_t RX_DATA; //0x6c
    volatile uint32_t TX_STT; //0x70
    volatile uint32_t TX_CMD_INFO; //0x74
    volatile uint32_t TX_PRI; //0x78
    volatile uint32_t ERR_CTR; //0x7c
    volatile uint32_t TRV_SSP; //0x80
    volatile uint32_t RX_FR_CTR; //0x84
    volatile uint32_t TX_FR_CTR; //0x88
    volatile uint32_t DBG_REG; //0x8c
    volatile uint32_t YOLO_REG; //0x90
    volatile uint32_t TIMESTAMP_L; //0x94
    volatile uint32_t TIMESTAMP_H; //0x98
    volatile uint32_t RESERVED0[25];
    volatile uint32_t TXTB1_DATA_1; //0x100
    volatile uint32_t TXTB1_DATA_2; //0x104
    volatile uint32_t TXTB1_DATA_3; //0x108
    volatile uint32_t TXTB1_DATA_4; //0x10c
    volatile uint32_t TXTB1_DATA_FRAME[16]; //0x110
    volatile uint32_t TXTB1_DATA_21; //0x150
    volatile uint32_t RESERVED1[43];
    volatile uint32_t TXTB2_DATA_1; //0x200
    volatile uint32_t TXTB2_DATA_2; //0x204
    volatile uint32_t TXTB2_DATA_3; //0x208
    volatile uint32_t TXTB2_DATA_4; //0x20c
    volatile uint32_t TXTB2_DATA_FRAME[16];//0x210
    volatile uint32_t TXTB2_DATA_21; //0x250
    volatile uint32_t RESERVED2[43];
    volatile uint32_t TXTB3_DATA_1; //0x300
    volatile uint32_t TXTB3_DATA_2; //0x304
    volatile uint32_t TXTB3_DATA_3; //0x308
    volatile uint32_t TXTB3_DATA_4; //0x30c
    volatile uint32_t TXTB3_DATA_FRAME[16]; //0x310
    volatile uint32_t TXTB3_DATA_21; //0x350
    volatile uint32_t RESERVED3[43];
    volatile uint32_t TXTB4_DATA_1; //0x400
    volatile uint32_t TXTB4_DATA_2; //0x404
    volatile uint32_t TXTB4_DATA_3; //0x408
    volatile uint32_t TXTB4_DATA_4; //0x40c
    volatile uint32_t TXTB4_DATA_FRAME[16]; //0x410
    volatile uint32_t TXTB4_DATA_21; //0x450
    volatile uint32_t RESERVED4[299];
    volatile uint32_t TST_CTRL; //0x900
    volatile uint32_t TST_DEST; //0x904
    volatile uint32_t TST_WDATA; //0x908
    volatile uint32_t TST_RDATA; //0x90c
}reg_fdcan_t;

enum FDCAN_REG_ID_VER_FIELD
{
    FDCAN_VER_MAJ_MASK = (int)0xff000000,
    FDCAN_VER_MAJ_POS = 24,
    FDCAN_VER_MIN_MASK = (int)0xff0000,
    FDCAN_VER_MIN_POS = 16,
    FDCAN_DEV_ID_MASK = (int)0xffff,
    FDCAN_DEV_ID_POS = 0,
};

enum FDCAN_REG_MODE_CFG_FIELD
{
    FDCAN_PCHKE_MASK = (int)0x8000000,
    FDCAN_PCHKE_POS = 27,
    FDCAN_FDRF_MASK = (int)0x4000000,
    FDCAN_FDRF_POS = 26,
    FDCAN_TBFBO_MASK = (int)0x2000000,
    FDCAN_TBFBO_POS = 25,
    FDCAN_PEX_MASK = (int)0x1000000,
    FDCAN_PEX_POS = 24,
    FDCAN_NISOFD_MASK = (int)0x800000,
    FDCAN_NISOFD_POS = 23,
    FDCAN_ENA_MASK = (int)0x400000,
    FDCAN_ENA_POS = 22,
    FDCAN_ILBP_MASK = (int)0x200000,
    FDCAN_ILBP_POS = 21,
    FDCAN_RTRTH_MASK = (int)0x1e0000,
    FDCAN_RTRTH_POS = 17,
    FDCAN_RTRLE_MASK = (int)0x10000,
    FDCAN_RTRLE_POS = 16,
    FDCAN_SAM_MASK = (int)0x800,
    FDCAN_SAM_POS = 11,
    FDCAN_TXBBM_MASK = (int)0x400,
    FDCAN_TXBBM_POS = 10,
    FDCAN_RXBAM_MASK = (int)0x200,
    FDCAN_RXBAM_POS = 9,
    FDCAN_TSTM_MASK = (int)0x100,
    FDCAN_TSTM_POS = 8,
    FDCAN_ACF_MASK = (int)0x80,
    FDCAN_ACF_POS = 7,
    FDCAN_ROM_MASK = (int)0x40,
    FDCAN_ROM_POS = 6,
    FDCAN_TTTM_MASK = (int)0x20,
    FDCAN_TTTM_POS = 5,
    FDCAN_FDE_MASK = (int)0x10,
    FDCAN_FDE_POS = 4,
    FDCAN_AFM_MASK = (int)0x8,
    FDCAN_AFM_POS = 3,
    FDCAN_STM_MASK = (int)0x4,
    FDCAN_STM_POS = 2,
    FDCAN_BMM_MASK = (int)0x2,
    FDCAN_BMM_POS = 1,
    FDCAN_RST_MASK = (int)0x1,
    FDCAN_RST_POS = 0,
};

enum FDCAN_REG_STT_FIELD
{
    FDCAN_SPRT_MASK = (int)0x40000,
    FDCAN_SPRT_POS = 18,
    FDCAN_STRGS_MASK = (int)0x1e0000,
    FDCAN_STRGS_POS = 17,
    FDCAN_STCNT_MASK = (int)0x10000,
    FDCAN_STCNT_POS = 16,
    FDCAN_TXDPE_MASK = (int)0x800,
    FDCAN_TXDPE_POS = 11,
    FDCAN_TXPE_MASK = (int)0x400,
    FDCAN_TXPE_POS = 10,
    FDCAN_RXPE_MASK = (int)0x200,
    FDCAN_RXPE_POS = 9,
    FDCAN_PEXS_MASK = (int)0x100,
    FDCAN_PEXS_POS = 8,
    FDCAN_IDLE_MASK = (int)0x80,
    FDCAN_IDLE_POS = 7,
    FDCAN_EWL_MASK = (int)0x40,
    FDCAN_EWL_POS = 6,
    FDCAN_TXS_MASK = (int)0x20,
    FDCAN_TXS_POS = 5,
    FDCAN_RXS_MASK = (int)0x10,
    FDCAN_RXS_POS = 4,
    FDCAN_EFT_MASK = (int)0x8,
    FDCAN_EFT_POS = 3,
    FDCAN_TXNF_MASK = (int)0x4,
    FDCAN_TXNF_POS = 2,
    FDCAN_DOR_MASK = (int)0x2,
    FDCAN_DOR_POS = 1,
    FDCAN_RXNE_MASK = (int)0x1,
    FDCAN_RXNE_POS = 0,
};

enum FDCAN_REG_CMD_FIELD
{
    FDCAN_CTXDPE_MASK = (int)0x400,
    FDCAN_CTXDPE_POS = 10,
    FDCAN_CTXPE_MASK = (int)0x200,
    FDCAN_CTXPE_POS = 9,
    FDCAN_CRXPE_MASK = (int)0x100,
    FDCAN_CRXPE_POS = 8,
    FDCAN_CPEXS_MASK = (int)0x80,
    FDCAN_CPEXS_POS = 7,
    FDCAN_TXFCRST_MASK = (int)0x40,
    FDCAN_TXFCRST_POS = 6,
    FDCAN_RXFCRST_MASK = (int)0x20,
    FDCAN_RXFCRST_POS = 5,
    FDCAN_ERCRST_MASK = (int)0x10,
    FDCAN_ERCRST_POS = 4,
    FDCAN_CDO_MASK = (int)0x8,
    FDCAN_CDO_POS = 3,
    FDCAN_RRB_MASK = (int)0x4,
    FDCAN_RRB_POS = 2,
    FDCAN_RXRPMV_MASK = (int)0x2,
    FDCAN_RXRPMV_POS = 1,
};

enum FDCAN_REG_INT_STT_FIELD
{
    FDCAN_TXBHCI_MASK = (int)0x800,
    FDCAN_TXBHCI_POS = 11,
    FDCAN_RBNEI_MASK = (int)0x400,
    FDCAN_RBNEI_POS = 10,
    FDCAN_BSI_MASK = (int)0x200,
    FDCAN_BSI_POS = 9,
    FDCAN_RXFI_MASK = (int)0x100,
    FDCAN_RXFI_POS = 8,
    FDCAN_OFI_MASK = (int)0x80,
    FDCAN_OFI_POS = 7,
    FDCAN_BEI_MASK = (int)0x40,
    FDCAN_BEI_POS = 6,
    FDCAN_ALI_MASK = (int)0x20,
    FDCAN_ALI_POS = 5,
    FDCAN_FCSI_MASK = (int)0x10,
    FDCAN_FCSI_POS = 4,
    FDCAN_DOI_MASK = (int)0x8,
    FDCAN_DOI_POS = 3,
    FDCAN_EWLI_MASK = (int)0x4,
    FDCAN_EWLI_POS = 2,
    FDCAN_TXI_MASK = (int)0x2,
    FDCAN_TXI_POS = 1,
    FDCAN_RXI_MASK = (int)0x1,
    FDCAN_RXI_POS = 0,
};

enum FDCAN_REG_BTR_FIELD
{
    FDCAN_SJW_MASK = (int)0xf8000000,
    FDCAN_SJW_POS = 27,
    FDCAN_BRP_MASK = (int)0x7f80000,
    FDCAN_BRP_POS = 19,
    FDCAN_PH2_MASK = (int)0x7e000,
    FDCAN_PH2_POS = 13,
    FDCAN_PH1_MASK = (int)0x1f80,
    FDCAN_PH1_POS = 7,
    FDCAN_RPOP_MASK = (int)0x7f,
    FDCAN_RPOP_POS = 0,
};

enum FDCAN_REG_BTR_FD_FIELD
{
    FDCAN_SJW_FD_MASK = (int)0xf8000000,
    FDCAN_SJW_FD_POS = 27,
    FDCAN_BRP_FD_MASK = (int)0x7f80000,
    FDCAN_BRP_FD_POS = 19,
    FDCAN_PH2_FD_MASK = (int)0x3e000,
    FDCAN_PH2_FD_POS = 13,
    FDCAN_PH1_FD_MASK = (int)0xf80,
    FDCAN_PH1_FD_POS = 7,
    FDCAN_PROP_FD_MASK = (int)0x3f,
    FDCAN_PROP_FD_POS = 0,
};

enum FDCAN_REG_EWL_ERP_FIELD
{
    FDCAN_BOF_MASK = (int)0x40000,
    FDCAN_BOF_POS = 18,
    FDCAN_ERP_MASK = (int)0x20000,
    FDCAN_ERP_POS = 17,
    FDCAN_ERA_MASK = (int)0x10000,
    FDCAN_ERA_POS = 16,
    FDCAN_ERP_LIMIT_MASK = (int)0xff00,
    FDCAN_ERP_LIMIT_POS = 8,
    FDCAN_EW_LIMIT_MASK = (int)0xff,
    FDCAN_EW_LIMIT_POS = 0,
};

enum FDCAN_REG_REC_TEC_FIELD
{
    FDCAN_TEC_VAL_MASK = (int)0x1ff0000,
    FDCAN_TEC_VAL_POS = 16,
    FDCAN_REC_VAL_MASK = (int)0x1ff,
    FDCAN_REC_VAL_POS = 0,
};

enum FDCAN_REG_ERR_FIELD
{
    FDCAN_ERR_FD_MASK = (int)0xffff0000,
    FDCAN_ERR_FD_POS = 16,
    FDCAN_ERR_NORM_MASK = (int)0xffff,
    FDCAN_ERR_NORM_POS = 0,
};

enum FDCAN_REG_CTR_PRES_FIELD
{
    FDCAN_EFD_MASK = (int)0x1000,
    FDCAN_EFD_POS = 12,
    FDCAN_ENORM_MASK = (int)0x800,
    FDCAN_ENORM_POS = 11,
    FDCAN_PRX_MASK = (int)0x400,
    FDCAN_PRX_POS = 10,
    FDCAN_PTX_MASK = (int)0x200,
    FDCAN_PTX_POS = 9,
    FDCAN_CTPV_MASK = (int)0x1ff,
    FDCAN_CTPV_POS = 0,
};

enum FDCAN_REG_FILTER_A_MSK_FIELD
{
    FDCAN_FILTER_A_MSK_MASK = (int)0x1fffffff,
    FDCAN_FILTER_A_MSK_POS = 0,
};

enum FDCAN_REG_FILTER_A_VAL_FIELD
{
    FDCAN_FILTER_A_VAL_MASK = (int)0x1fffffff,
    FDCAN_FILTER_A_VAL_POS = 0,
};

enum FDCAN_REG_FILTER_B_MSK_FIELD
{
    FDCAN_FILTER_B_MSK_MASK = (int)0x1fffffff,
    FDCAN_FILTER_B_MSK_POS = 0,
};

enum FDCAN_REG_FILTER_B_VAL_FIELD
{
    FDCAN_FILTER_B_VAL_MASK = (int)0x1fffffff,
    FDCAN_FILTER_B_VAL_POS = 0,
};

enum FDCAN_REG_FILTER_C_MSK_FIELD
{
    FDCAN_FILTER_C_MSK_MASK = (int)0x1fffffff,
    FDCAN_FILTER_C_MSK_POS = 0,
};

enum FDCAN_REG_FILTER_C_VAL_FIELD
{
    FDCAN_FILTER_C_VAL_MASK = (int)0x1fffffff,
    FDCAN_FILTER_C_VAL_POS = 0,
};

enum FDCAN_REG_FILTER_RANGE_L_FIELD
{
    FDCAN_FILTER_RANGE_L_MASK = (int)0x1fffffff,
    FDCAN_FILTER_RANGE_L_POS = 0,
};

enum FDCAN_REG_FILTER_RANGE_H_FIELD
{
    FDCAN_FILTER_RANGE_H_MASK = (int)0x1fffffff,
    FDCAN_FILTER_RANGE_H_POS = 0,
};

enum FDCAN_REG_FILTER_CTRL_STT_FIELD
{
    FDCAN_SFR_MASK = (int)0x80000,
    FDCAN_SFR_POS = 19,
    FDCAN_SFC_MASK = (int)0x40000,
    FDCAN_SFC_POS = 18,
    FDCAN_SFB_MASK = (int)0x20000,
    FDCAN_SFB_POS = 17,
    FDCAN_SFA_MASK = (int)0x10000,
    FDCAN_SFA_POS = 16,
    FDCAN_FRFE_MASK = (int)0x8000,
    FDCAN_FRFE_POS = 15,
    FDCAN_FRFB_MASK = (int)0x4000,
    FDCAN_FRFB_POS = 14,
    FDCAN_FRNE_MASK = (int)0x2000,
    FDCAN_FRNE_POS = 13,
    FDCAN_FRNB_MASK = (int)0x1000,
    FDCAN_FRNB_POS = 12,
    FDCAN_FCFE_MASK = (int)0x800,
    FDCAN_FCFE_POS = 11,
    FDCAN_FCFB_MASK = (int)0x400,
    FDCAN_FCFB_POS = 10,
    FDCAN_FCNE_MASK = (int)0x200,
    FDCAN_FCNE_POS = 9,
    FDCAN_FCNB_MASK = (int)0x100,
    FDCAN_FCNB_POS = 8,
    FDCAN_FBFE_MASK = (int)0x80,
    FDCAN_FBFE_POS = 7,
    FDCAN_FBFB_MASK = (int)0x40,
    FDCAN_FBFB_POS = 6,
    FDCAN_FBNE_MASK = (int)0x20,
    FDCAN_FBNE_POS = 5,
    FDCAN_FBNB_MASK = (int)0x10,
    FDCAN_FBNB_POS = 4,
    FDCAN_FAFE_MASK = (int)0x8,
    FDCAN_FAFE_POS = 3,
    FDCAN_FAFB_MASK = (int)0x4,
    FDCAN_FAFB_POS = 2,
    FDCAN_FANE_MASK = (int)0x2,
    FDCAN_FANE_POS = 1,
    FDCAN_FANB_MASK = (int)0x1,
    FDCAN_FANB_POS = 0,
};

enum FDCAN_REG_RX_MEM_INFO_FIELD
{
    FDCAN_MEM_FREE_MASK = (int)0x1fff0000,
    FDCAN_MEM_FREE_POS = 16,
    FDCAN_BUF_SIZE_MASK = (int)0x1fff,
    FDCAN_BUF_SIZE_POS = 0,
};

enum FDCAN_REG_RX_PTR_FIELD
{
    FDCAN_RX_RPP_MASK = (int)0xfff0000,
    FDCAN_RX_RPP_POS = 16,
    FDCAN_RX_WPP_MASK = (int)0xfff,
    FDCAN_RX_WPP_POS = 0,
};

enum FDCAN_REG_RX_STT_FIELD
{
    FDCAN_RTSOP_MASK = (int)0x10000,
    FDCAN_RTSOP_POS = 16,
    FDCAN_RXFRC_MASK = (int)0x7ff0,
    FDCAN_RXFRC_POS = 4,
    FDCAN_RXMOF_MASK = (int)0x4,
    FDCAN_RXMOF_POS = 2,
    FDCAN_RXF_MASK = (int)0x2,
    FDCAN_RXF_POS = 1,
    FDCAN_RXE_MASK = (int)0x1,
    FDCAN_RXE_POS = 0,
};

enum FDCAN_REG_TX_STT_FIELD
{
    FDCAN_TX8S_MASK = (int)0xf0000000,
    FDCAN_TX8S_POS = 28,
    FDCAN_TX7S_MASK = (int)0xf000000,
    FDCAN_TX7S_POS = 24,
    FDCAN_TX6S_MASK = (int)0xf00000,
    FDCAN_TX6S_POS = 20,
    FDCAN_TX5S_MASK = (int)0xf0000,
    FDCAN_TX5S_POS = 16,
    FDCAN_TX4S_MASK = (int)0xf000,
    FDCAN_TX4S_POS = 12,
    FDCAN_TX3S_MASK = (int)0xf00,
    FDCAN_TX3S_POS = 8,
    FDCAN_TX2S_MASK = (int)0xf0,
    FDCAN_TX2S_POS = 4,
    FDCAN_TX1S_MASK = (int)0xf,
    FDCAN_TX1S_POS = 0,
};

enum FDCAN_REG_TX_CMD_INFO_FIELD
{
    FDCAN_BUF_CNT_MASK = (int)0xf0000,
    FDCAN_BUF_CNT_POS = 16,
    FDCAN_TXB8_MASK = (int)0x8000,
    FDCAN_TXB8_POS = 15,
    FDCAN_TXB7_MASK = (int)0x4000,
    FDCAN_TXB7_POS = 14,
    FDCAN_TXB6_MASK = (int)0x2000,
    FDCAN_TXB6_POS = 13,
    FDCAN_TXB5_MASK = (int)0x1000,
    FDCAN_TXB5_POS = 12,
    FDCAN_TXB4_MASK = (int)0x800,
    FDCAN_TXB4_POS = 11,
    FDCAN_TXB3_MASK = (int)0x400,
    FDCAN_TXB3_POS = 10,
    FDCAN_TXB2_MASK = (int)0x200,
    FDCAN_TXB2_POS = 9,
    FDCAN_TXB1_MASK = (int)0x100,
    FDCAN_TXB1_POS = 8,
    FDCAN_TXCA_MASK = (int)0x4,
    FDCAN_TXCA_POS = 2,
    FDCAN_TXCR_MASK = (int)0x2,
    FDCAN_TXCR_POS = 1,
    FDCAN_TXCE_MASK = (int)0x1,
    FDCAN_TXCE_POS = 0,
};

enum FDCAN_REG_TX_PRI_FIELD
{
    FDCAN_TXT8P_MASK = (int)0x70000000,
    FDCAN_TXT8P_POS = 28,
    FDCAN_TXT7P_MASK = (int)0x7000000,
    FDCAN_TXT7P_POS = 24,
    FDCAN_TXT6P_MASK = (int)0x700000,
    FDCAN_TXT6P_POS = 20,
    FDCAN_TXT5P_MASK = (int)0x70000,
    FDCAN_TXT5P_POS = 16,
    FDCAN_TXT4P_MASK = (int)0x7000,
    FDCAN_TXT4P_POS = 12,
    FDCAN_TXT3P_MASK = (int)0x700,
    FDCAN_TXT3P_POS = 8,
    FDCAN_TXT2P_MASK = (int)0x70,
    FDCAN_TXT2P_POS = 4,
    FDCAN_TXT1P_MASK = (int)0x7,
    FDCAN_TXT1P_POS = 0,
};

enum FDCAN_REG_TXTB_DATA_1_FIELD
{
    FDCAN_TXTB_DATA_1_RWCNT_MASK = (int)0xf800,
    FDCAN_TXTB_DATA_1_RWCNT_POS = 11,
    FDCAN_TXTB_DATA_1_ESIRSV_MASK = (int)0x400,
    FDCAN_TXTB_DATA_1_ESIRSV_POS = 10,
    FDCAN_TXTB_DATA_1_BRS_MASK = (int)0x200,
    FDCAN_TXTB_DATA_1_BRS_POS = 9,
    FDCAN_TXTB_DATA_1_FDF_MASK = (int)0x80,
    FDCAN_TXTB_DATA_1_FDF_POS = 7,
    FDCAN_TXTB_DATA_1_IDE_MASK = (int)0x40,
    FDCAN_TXTB_DATA_1_IDE_POS = 6,
    FDCAN_TXTB_DATA_1_RTR_MASK = (int)0x20,
    FDCAN_TXTB_DATA_1_RTR_POS = 5,
    FDCAN_TXTB_DATA_1_DLC_MASK = (int)0xf,
    FDCAN_TXTB_DATA_1_DLC_POS = 0,
};

enum FDCAN_REG_TXTB_DATA_2_FIELD
{
    FDCAN_TXTB_DATA_2_IDENTIFIER_BASE_MASK = (int)0x1ffc0000,
    FDCAN_TXTB_DATA_2_IDENTIFIER_BASE_POS = 18,
    FDCAN_TXTB_DATA_2_IDENTIFIER_EXT_MASK = (int)0x3ffff,
    FDCAN_TXTB_DATA_2_IDENTIFIER_EXT_POS = 0,
};

enum FDCAN_REG_ERR_CTR_FIELD
{
    FDCAN_TS_BITS_MASK = (int)0x3f000000,
    FDCAN_TS_BITS_POS = 24,
    FDCAN_ALC_ID_MASK = (int)0xf00000,
    FDCAN_ALC_ID_POS = 20,
    FDCAN_ALC_BIT_MASK = (int)0xf0000,
    FDCAN_ALC_BIT_POS = 16,
    FDCAN_PETR_CTR_MASK = (int)0xf00,
    FDCAN_PETR_CTR_POS = 8,
    FDCAN_ERR_TYPE_MASK = (int)0xf0,
    FDCAN_ERR_TYPE_POS = 4,
    FDCAN_ERR_POS_MASK = (int)0xf,
    FDCAN_ERR_POS_POS = 0,
};

enum FDCAN_REG_TRV_SSP_FIELD
{
    FDCAN_SSP_SRC_MASK = (int)0x3000000,
    FDCAN_SSP_SRC_POS = 24,
    FDCAN_SSP_OFS_MASK = (int)0xff0000,
    FDCAN_SSP_OFS_POS = 16,
    FDCAN_TRV_DLY_MASK = (int)0x7f,
    FDCAN_TRV_DLY_POS = 0,
};

enum FDCAN_REG_DBG_REG_FIELD
{
    FDCAN_PC_SOF_MASK = (int)0x40000,
    FDCAN_PC_SOF_POS = 18,
    FDCAN_PC_OVR_MASK = (int)0x20000,
    FDCAN_PC_OVR_POS = 17,
    FDCAN_PC_SUSP_MASK = (int)0x10000,
    FDCAN_PC_SUSP_POS = 16,
    FDCAN_PC_INT_MASK = (int)0x8000,
    FDCAN_PC_INT_POS = 15,
    FDCAN_PC_EOF_MASK = (int)0x4000,
    FDCAN_PC_EOF_POS = 14,
    FDCAN_PC_ACKD_MASK = (int)0x2000,
    FDCAN_PC_ACKD_POS = 13,
    FDCAN_PC_ACK_MASK = (int)0x1000,
    FDCAN_PC_ACK_POS = 12,
    FDCAN_PC_CRCD_MASK = (int)0x800,
    FDCAN_PC_CRCD_POS = 11,
    FDCAN_PC_CRC_MASK = (int)0x400,
    FDCAN_PC_CRC_POS = 10,
    FDCAN_PC_STC_MASK = (int)0x200,
    FDCAN_PC_STC_POS = 9,
    FDCAN_PC_DAT_MASK = (int)0x100,
    FDCAN_PC_DAT_POS = 8,
    FDCAN_PC_CON_MASK = (int)0x80,
    FDCAN_PC_CON_POS = 7,
    FDCAN_PC_ARB_MASK = (int)0x40,
    FDCAN_PC_ARB_POS = 6,
    FDCAN_DESUFF_CNT_MASK = (int)0x38,
    FDCAN_DESUFF_CNT_POS = 3,
    FDCAN_STUFF_CNT_MASK = (int)0x7,
    FDCAN_STUFF_CNT_POS = 0,
};

enum FDCAN_REG_TST_CTRL_FIELD
{
    FDCAN_TWRSTB_MASK = (int)0x2,
    FDCAN_TWRSTB_POS = 1,
    FDCAN_TMAENA_MASK = (int)0x1,
    FDCAN_TMAENA_POS = 0,
};

enum FDCAN_REG_TST_DEST_FIELD
{
    FDCAN_TST_MTGT_MASK = (int)0xf0000,
    FDCAN_TST_MTGT_POS = 16,
    FDCAN_TST_ADDR_MASK = (int)0xffff,
    FDCAN_TST_ADDR_POS = 0,
};

#ifdef __cplusplus
}
#endif

#endif

