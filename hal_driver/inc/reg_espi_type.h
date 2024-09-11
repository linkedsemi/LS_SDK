#ifndef REG_ESPI_TYPE_H_
#define REG_ESPI_TYPE_H_


#include <stdint.h>


/**
 * @brief eSPI Control Registers
 */
typedef struct
{
    volatile uint32_t RESERVED0[1];      // 0x00
    volatile uint32_t DEV_ID;            // 0x04    Device Identification; Reset:0x1
    volatile uint32_t GEN_CFG;           // 0x08    General Capabilities and Configurations; Reset:0x3040F
    volatile uint32_t RESERVED1[1];      // 0x0C
    volatile uint32_t PER_CH0_CFG;       // 0x10    Peripheral Channel 0 Capabilities and Configurations; Reset:0x1111
    volatile uint32_t RESERVED2[3];      // 0x14
    volatile uint32_t VWIR_CH1_CFG;      // 0x20    Virtual Wire Channel 1 Capabilities and Configurations; Reset:0x1F00
    volatile uint32_t RESERVED3[3];      // 0x24
    volatile uint32_t OOB_CH2_CFG;       // 0x30    OOB Channel 2 Capabilities and Configurations; Reset:0x110
    volatile uint32_t RESERVED4[3];      // 0x34
    volatile uint32_t FLS_CH3_CFG;       // 0x40    Flash Channel 3 Capabilities and Configurations; Reset:0x31124
    volatile uint32_t FLS_CH3_CFG2;      // 0x44    Flash Channel 3 Capabilities and Configurations2; Reset:0x1
    volatile uint32_t RESERVED5[46];     // 0x48
    volatile uint32_t UP_NPST_LEN_M1;    // 0x100   up stream non-posted command length minus 1; Reset:0x0
    volatile uint32_t UP_NPST_DAT;       // 0x104   first 4 byte of up stream non-posted command; Reset:0x0
    volatile uint32_t UP_NPST_ADR;       // 0x108   up stream non-posted command buffer address; Reset:0x0
    volatile uint32_t DW_NPST_ADR;       // 0x10C   down stream non-posted command buffer address; Reset:0x0
    volatile uint32_t UP_PSTC_LEN_M1;    // 0x110   up stream posted command length minus 1; Reset:0x0
    volatile uint32_t UP_PSTC_DAT;       // 0x114   first 4 byte of up stream posted command; Reset:0x0
    volatile uint32_t UP_PSTC_ADR;       // 0x118   up stream posted command buffer address; Reset:0x0
    volatile uint32_t DW_PSTC_ADR;       // 0x11C   down stream posted command buffer address; Reset:0x0
    volatile uint32_t UP_VWIR_LEN_M1;    // 0x120   up stream virtual wire command length minus 1; Reset:0x0
    volatile uint32_t UP_VWIR_DAT;       // 0x124   first 4 byte of up stream virtual wire command; Reset:0x0
    volatile uint32_t UP_VWIR_ADR;       // 0x128   up stream virtual wire command buffer address; Reset:0x0
    volatile uint32_t RESERVED6[1];      // 0x12C
    volatile uint32_t UP_OOBP_LEN_M1;    // 0x130   up stream OOB posted command length minus 1; Reset:0x0
    volatile uint32_t UP_OOBP_DAT;       // 0x134   first 4 byte of up stream OOB posted command; Reset:0x0
    volatile uint32_t UP_OOBP_ADR;       // 0x138   up stream OOB posted command buffer address; Reset:0x0
    volatile uint32_t DN_OOBP_ADR;       // 0x13C   down stream OOB posted command buffer address; Reset:0x0
    volatile uint32_t UP_FLASH_LEN_M1;   // 0x140   up stream flash command length minus 1; Reset:0x0
    volatile uint32_t UP_FLASH_DAT;      // 0x144   first 4 byte of up stream flash command; Reset:0x0
    volatile uint32_t UP_FLASH_ADR;      // 0x148   up stream flash command buffer address; Reset:0x0
    volatile uint32_t DN_FLASH_ADR;      // 0x14C   down stream flash command buffer address; Reset:0x0
    volatile uint32_t ICAP_CTRL;         // 0x150   choose icap mode; Reset:0x0
    volatile uint32_t STATUS_SET;        // 0x154   status set; Reset:0x0
    volatile uint32_t RESERVED7[2];      // 0x158
    volatile uint32_t DN_VWIR_IDX_CTRL0; // 0x160   dn virtual wire index for user defined virtual wire group0~group3; Reset:0x43424140
    volatile uint32_t DN_VWIR_IDX_CTRL1; // 0x164   dn virtual wire index for user defined virtual wire group4~group7; Reset:0x47464544
    volatile uint32_t RESERVED8[6];      // 0x168
    volatile uint32_t DN_VWIR_VAL0;      // 0x180   dn virtual wire value for user defined virtual wire group0~group3; Reset:0x0
    volatile uint32_t DN_VWIR_VAL1;      // 0x184   dn virtual wire value for user defined virtual wire group4~group7; Reset:0x0
    volatile uint32_t RESERVED9[6];      // 0x188
    volatile uint32_t DN_VWIR_SYS0;      // 0x1A0   virtual wire value for system virtual wire group2~group3; Reset:0x0
    volatile uint32_t DN_VWIR_SYS1;      // 0x1A4   virtual wire value for system virtual wire group7; Reset:0x0
    volatile uint32_t RESERVED10[22];    // 0x1A8
    volatile uint32_t INTERRUPT_MASK;    // 0x200   interrupt mask, each bit for one interrupt; Reset:0x0
    volatile uint32_t INTERRUPT_CLEAR;   // 0x204   interrupt clear, each bit for one interrupt, write 1 will clear the interrupt; Reset:0x0
    volatile uint32_t INTERRUPT_STT;     // 0x208   interrupt stt; Reset:0x0
    volatile uint32_t INTERRUPT_RAW;     // 0x20C   interrupt raw status; Reset:0x0
    volatile uint32_t STATUS;            // 0x210   current eSPI status defined by the eSPI protocol; Reset:0x0
    volatile uint32_t STATUS_SEND;       // 0x214   the status send inthe last eSPI command; Reset:0x0
} reg_espi_t;

enum ESPI_REG_DEV_ID_FIELD
{
    // Indicates compliance to specific eSPI specification revision; Type:RO; Reset:0x01
    ESPI_DEV_ID_MASK = (int)0x0F,
    ESPI_DEV_ID_POS = 0
};

enum ESPI_REG_GEN_CFG_FIELD
{
    // Each of the bits when set indicates that the corresponding channel is supported by the slave; Type:RW; Reset:0xf
    ESPI_GEN_CFG_CH_SUPP_MASK = (int)0x0F,
    ESPI_GEN_CFG_CH_SUPP_POS = 0,
    // eSPI master sets the maximum WAIT STATE allowed to be responded by slave; Type:RW; Reset:0x0
    ESPI_GEN_CFG_MAX_WAIT_MASK = (int)0xF000,
    ESPI_GEN_CFG_MAX_WAIT_POS = 12,
    // This field identifies the maximum frequency of operation supported by the slave; Type:RW; Reset:0x4
    ESPI_GEN_CFG_OP_FREQ_SUPP_MASK = (int)0x70000,
    ESPI_GEN_CFG_OP_FREQ_SUPP_POS = 16,
    // This bit indicates the support of the Alert# pin as an open-drain output by the slave; Type:RW; Reset:0x0
    ESPI_GEN_CFG_OD_ALERT_SUPP_MASK = (int)0x80000,
    ESPI_GEN_CFG_OD_ALERT_SUPP_POS = 19,
    // This field identifies the frequency of operation; Type:RW; Reset:0x0
    ESPI_GEN_CFG_OP_FREQ_MASK = (int)0x700000,
    ESPI_GEN_CFG_OP_FREQ_POS = 20,
    // This bit is set to ‘1’ by eSPI master to configure the Alert# pin as an open-drain output; Type:RW; Reset:0x0
    ESPI_GEN_CFG_OD_ALERT_MASK = (int)0x800000,
    ESPI_GEN_CFG_OD_ALERT_POS = 23,
    // This field indicates the I/O modes supported by the slave; Type:RW; Reset:0x3
    ESPI_GEN_CFG_IO_MODE_SUPP_MASK = (int)0x3000000,
    ESPI_GEN_CFG_IO_MODE_SUPP_POS = 24,
    // eSPI master programs this field to enable the appropriate mode of operation, which will take effect at the deassertion edge of the CS#; Type:RW; Reset:0x0
    ESPI_GEN_CFG_IO_MODE_MASK = (int)0xC000000,
    ESPI_GEN_CFG_IO_MODE_POS = 26,
    // This bit serves to configure the Alert mechanism used by the slave to initiate a transaction on the eSPI interface; Type:RW; Reset:0x0
    ESPI_GEN_CFG_ALERT_MODE_MASK = (int)0x10000000,
    ESPI_GEN_CFG_ALERT_MODE_POS = 28,
    // eSPI slave completion to the GET_STATUS response phase; Type:RW; Reset:0x0
    ESPI_GEN_CFG_RSP_MOD_EN_MASK = (int)0x40000000,
    ESPI_GEN_CFG_RSP_MOD_EN_POS = 30,
    // This bit is set to ‘1’ by eSPI master to enable the CRC checking on the eSPI bus. By default, CRC checking is disabled; Type:RW; Reset:0x0
    ESPI_GEN_CFG_CRC_EN_MASK = (int)0x80000000,
    ESPI_GEN_CFG_CRC_EN_POS = 31
};

enum ESPI_REG_CH0_CFG_PER_FIELD
{
    // The channel is by default enabled after the eSPI Reset#; Type:RW; Reset:0x01
    ESPI_CH0_CFG_PER_CH_EN_MASK = (int)0x01,
    ESPI_CH0_CFG_PER_CH_EN_POS = 0,
    // When this bit is a ‘1’, it indicates that the slave is ready to accept transactions on the Peripheral channel; Type:RW; Reset:0x00
    ESPI_CH0_CFG_PER_CH_RDY_MASK = (int)0x02,
    ESPI_CH0_CFG_PER_CH_RDY_POS = 1,
    //; Type:RW; Reset:0x00
    ESPI_CH0_CFG_PER_BUS_MST_EN_MASK = (int)0x04,
    ESPI_CH0_CFG_PER_BUS_MST_EN_POS = 2,
    // This field advertises the Maximum Payload Size supported by the slave; Type:RW; Reset:0x01
    ESPI_CH0_CFG_PER_MAX_PLOAD_SUPP_MASK = (int)0x70,
    ESPI_CH0_CFG_PER_MAX_PLOAD_SUPP_POS = 4,
    // eSPI master sets the maximum payload size for the Peripheral channel; Type:RW; Reset:0x01
    ESPI_CH0_CFG_PER_MAX_PLOAD_MASK = (int)0x700,
    ESPI_CH0_CFG_PER_MAX_PLOAD_POS = 8,
    // eSPI master sets the maximum read request size for the Peripheral channel; Type:RW; Reset:0x01
    ESPI_CH0_CFG_PER_MAX_RD_REQ_MASK = (int)0x7000,
    ESPI_CH0_CFG_PER_MAX_RD_REQ_POS = 12
};

enum ESPI_REG_CH1_CFG_VWIR_FIELD
{
    // This bit is set to ‘1’ by eSPI master to enable the Virtual Wire channel; Type:RW; Reset:0x0
    ESPI_CH1_CFG_VWIR_CH_EN_MASK = (int)0x01,
    ESPI_CH1_CFG_VWIR_CH_EN_POS = 0,
    // When this bit is a ‘1’, it indicates that the slave is ready to accept transactions on the Virtual Wire channel; Type:RW; Reset:0x0
    ESPI_CH1_CFG_VWIR_CH_RDY_MASK = (int)0x02,
    ESPI_CH1_CFG_VWIR_CH_RDY_POS = 1,
    // This field advertises the Maximum Virtual Wire Count supported by the slave; Type:RW; Reset:0x1f
    ESPI_CH1_CFG_VWIR_MAX_CNT_SUPP_MASK = (int)0x3F00,
    ESPI_CH1_CFG_VWIR_MAX_CNT_SUPP_POS = 8,
    // The maximum number of Virtual Wire groups that can be sent in a single Virtual Wire packet; Type:RW; Reset:0x0
    ESPI_CH1_CFG_VWIR_MXA_CNT_MASK = (int)0x3F0000,
    ESPI_CH1_CFG_VWIR_MAX_CNT_POS = 16
};

enum ESPI_REG_CH2_CFG_OOB_FIELD
{
    // This bit is set to ‘1’ by eSPI master to enable the OOB Message channel; Type:RW; Reset:0x0
    ESPI_CH2_CFG_OOB_CH_EN_MASK = (int)0x01,
    ESPI_CH2_CFG_OOB_CH_EN_POS = 0,
    // When this bit is a ‘1’, it indicates that the slave is ready to accept transactions on the OOB Message channel; Type:RW; Reset:0x0
    ESPI_CH2_CFG_OOB_CH_RDY_MASK = (int)0x02,
    ESPI_CH2_CFG_OOB_CH_RDY_POS = 1,
    // This field advertises the Maximum Payload Size supported by the slave; Type:RW; Reset:0x1
    ESPI_CH2_CFG_OOB_MAX_PLOAD_SUPP_MASK = (int)0x70,
    ESPI_CH2_CFG_OOB_MAX_PLOAD_SUPP_POS = 4,
    // eSPI master sets the maximum payload size for the OOB Message channel; Type:RW; Reset:0x1
    ESPI_CH2_CFG_OOB_MAX_PLOAD_MASK = (int)0x700,
    ESPI_CH2_CFG_OOB_MAX_PLOAD_POS = 8
};

enum ESPI_REG_CH3_CFG_FLASH_FIELD
{
    // This bit is set to ‘1’ by eSPI master to enable the Flash Access channel; Type:RW; Reset:0x0
    ESPI_CH3_CFG_FLS_CH_EN_MASK = (int)0x01,
    ESPI_CH3_CFG_FLS_CH_EN_POS = 0,
    // When this bit is a ‘1’, it indicates that the slave is ready to accept transactions on the Flash Access channel; Type:RW; Reset:0x0
    ESPI_CH3_CFG_FLS_CH_RDY_MASK = (int)0x02,
    ESPI_CH3_CFG_FLS_CH_RDY_POS = 1,
    // eSPI master sets this field to communicate the block erase size to the slave; Type:RW; Reset:0x1
    ESPI_CH3_CFG_FLS_ERS_SIZE_MASK = (int)0x1C,
    ESPI_CH3_CFG_FLS_ERS_SIZE_POS = 2,
    // This field advertises the Maximum Payload Size supported by the slave; Type:RW; Reset:0x1
    ESPI_CH3_CFG_FLS_MAX_PLOAD_SUPP_MASK = (int)0xE0,
    ESPI_CH3_CFG_FLS_MAX_PLOAD_SUPP_POS = 5,
    // eSPI master sets the maximum payload size for the Flash Access channel; Type:RW; Reset:0x1
    ESPI_CH3_CFG_FLS_MAX_PLOAD_MASK = (int)0x700,
    ESPI_CH3_CFG_FLS_MAX_PLOAD_POS = 8,
    // When Flash Access channel is supported, this bit advertises the flash sharing scheme intended by the slave; Type:RW; Reset:0x0
    ESPI_CH3_CFG_FLS_SHARE_MODE_MASK = (int)0x800,
    ESPI_CH3_CFG_FLS_SHARE_MODE_POS = 11,
    // eSPI master sets the maximum read request size for the Flash Access channel; Type:RW; Reset:0x1
    ESPI_CH3_CFG_FLS_MAX_RD_REQ_MASK = (int)0x7000,
    ESPI_CH3_CFG_FLS_MAX_RD_REQ_POS = 12,
    // This field indicates the flash sharing capability supported by the slave; Type:RW; Reset:0x3
    ESPI_CH3_CFG_FLS_SHARE_SUPP_MASK = (int)0x30000,
    ESPI_CH3_CFG_FLS_SHARE_SUPP_POS = 16
};

enum ESPI_REG_CH3_CFG2_FLASH_FIELD
{
    // This field indicates the maximum read request size supported by the slave as the Target on the Flash Access channel; Type:RW; Reset:0x01
    ESPI_CH3_CFG2_FLS_MAX_RD_REQ_SUPP_MASK = (int)0x07,
    ESPI_CH3_CFG2_FLS_MAX_RD_REQ_SUPP_POS = 0,
    // This field indicates the sizes of the erase commands the master may issue. If multiple bits are set then the master may issue an erase using any of the indicated sizes; Type:RW; Reset:0x00
    ESPI_CH3_CFG2_FLS_ERS_SIZE_MST_MASK = (int)0xFF00,
    ESPI_CH3_CFG2_FLS_ERS_SIZE_MST_POS = 8,
    // This field indicates the total number of Replay Protected Monotonic Counters (RPMC) supported by the Slave. It is a 1-based field; Type:RW; Reset:0x00
    ESPI_CH3_CFG2_FLS_RPMC_SUPP_MASK = (int)0x3F0000,
    ESPI_CH3_CFG2_FLS_RPMC_SUPP_POS = 16
};

enum ESPI_REG_UP_NPST_LEN_M1_FIELD
{
    // up stream non-posted command length minus 1; Type:RW; Reset:0x00
    ESPI_UP_NPST_LEN_M1_MASK = (int)0x1F,
    ESPI_UP_NPST_LEN_M1_POS = 0
};

enum ESPI_REG_UP_NPST_DAT_FIELD
{
    // first 4 byte of up stream non-posted command; Type:RW; Reset:0x00
    ESPI_UP_NPST_DAT_MASK = (int)0xFFFF,
    ESPI_UP_NPST_DAT_POS = 0
};

enum ESPI_REG_UP_NPST_ADR_FIELD
{
    // up stream non-posted command buffer address; Type:RW; Reset:0x00
    ESPI_UP_NPST_ADR_MASK = (int)0xFFFFC,
    ESPI_UP_NPST_ADR_POS = 2
};

enum ESPI_REG_DW_NPST_ADR_FIELD
{
    // down stream non-posted command buffer address; Type:RW; Reset:0x00
    ESPI_DW_NPST_ADR_MASK = (int)0xFFFFC,
    ESPI_DW_NPST_ADR_POS = 2
};

enum ESPI_REG_UP_PSTC_LEN_M1_FIELD
{
    // up stream posted command length minus 1; Type:RW; Reset:0x00
    ESPI_UP_PSTC_LEN_M1_MASK = (int)0x1F,
    ESPI_UP_PSTC_LEN_M1_POS = 0
};

enum ESPI_REG_UP_PSTC_DAT_FIELD
{
    // first 4 byte of up stream posted command; Type:RW; Reset:0x00
    ESPI_UP_PSTC_DAT_MASK = (int)0xFFFF,
    ESPI_UP_PSTC_DAT_POS = 0
};

enum ESPI_REG_UP_PSTC_ADR_FIELD
{
    // up stream posted command buffer address; Type:RW; Reset:0x00
    ESPI_UP_PSTC_ADR_MASK = (int)0xFFFFC,
    ESPI_UP_PSTC_ADR_POS = 2
};

enum ESPI_REG_DW_PSTC_ADR_FIELD
{
    // down stream posted command buffer address; Type:RW; Reset:0x00
    ESPI_DW_PSTC_ADR_MASK = (int)0xFFFFC,
    ESPI_DW_PSTC_ADR_POS = 2
};

enum ESPI_REG_UP_VWIRE_LEN_M1_FIELD
{
    // up stream virtual wire command length minus 1; Type:RW; Reset:0x00
    ESPI_UP_VWIRE_LEN_M1_MASK = (int)0x1F,
    ESPI_UP_VWIRE_LEN_M1_POS = 0
};

enum ESPI_REG_UP_VWIRE_DAT_FIELD
{
    // first 4 byte of up stream virtual wire command; Type:RW; Reset:0x00
    ESPI_UP_VWIRE_DAT_MASK = (int)0xFFFF,
    ESPI_UP_VWIRE_DAT_POS = 0
};

enum ESPI_REG_UP_VWIRE_ADR_FIELD
{
    // up stream virtual wire command buffer address; Type:RW; Reset:0x00
    ESPI_UP_VWIRE_ADR_MASK = (int)0xFFFFC,
    ESPI_UP_VWIRE_ADR_POS = 2
};

enum ESPI_REG_UP_OOBP_LEN_M1_FIELD
{
    // up stream OOB posted command length minus 1; Type:RW; Reset:0x00
    ESPI_UP_OOBP_LEN_M1_MASK = (int)0x1F,
    ESPI_UP_OOBP_LEN_M1_POS = 0
};

enum ESPI_REG_UP_OOBP_DAT_FIELD
{
    // first 4 byte of up stream OOB posted command; Type:RW; Reset:0x00
    ESPI_UP_OOBP_DAT_MASK = (int)0xFFFF,
    ESPI_UP_OOBP_DAT_POS = 0
};

enum ESPI_REG_UP_OOBP_ADR_FIELD
{
    // up stream OOB posted command buffer address; Type:RW; Reset:0x00
    ESPI_UP_OOBP_ADR_MASK = (int)0xFFFFC,
    ESPI_UP_OOBP_ADR_POS = 2
};

enum ESPI_REG_DW_OOBP_ADR_FIELD
{
    // down stream OOB posted command buffer address; Type:RW; Reset:0x00
    ESPI_DW_OOBP_ADR_MASK = (int)0xFFFFC,
    ESPI_DW_OOBP_ADR_POS = 2
};

enum ESPI_REG_UP_FLASH_LEN_M1_FIELD
{
    // up stream flash command length minus 1; Type:RW; Reset:0x00
    ESPI_UP_FLASH_LEN_M1_MASK = (int)0x1F,
    ESPI_UP_FLASH_LEN_M1_POS = 0
};

enum ESPI_REG_UP_FLASH_DAT_FIELD
{
    // first 4 byte of up stream flash command; Type:RW; Reset:0x00
    ESPI_UP_FLASH_DAT_MASK = (int)0xFFFF,
    ESPI_UP_FLASH_DAT_POS = 0
};

enum ESPI_REG_UP_FLASH_ADR_FIELD
{
    // up stream flash command buffer address; Type:RW; Reset:0x00
    ESPI_UP_FLASH_ADR_MASK = (int)0xFFFFC,
    ESPI_UP_FLASH_ADR_POS = 2
};

enum ESPI_REG_DW_FLASH_ADR_FIELD
{
    // down stream flash command buffer address; Type:RW; Reset:0x00
    ESPI_DW_FLASH_ADR_MASK = (int)0xFFFFC,
    ESPI_DW_FLASH_ADR_POS = 2
};

enum ESPI_REG_ICAP_CTRL_FIELD
{
    // The input data is how input to the internal FSM; Type:RW; Reset:0x00
    ESPI_ICAP_MODE_MASK = (int)0x1,
    ESPI_ICAP_MODE_POS = 0
};

enum ESPI_REG_STATUS_SET_FIELD
{
    // write 1 will set the pc_free; Type:WO; Reset:0x00
    ESPI_STATUS_SET_PC_FREE_MASK = (int)0x1,
    ESPI_STATUS_SET_PC_FREE_POS = 0,
    // write 1 will set the np_free; Type:WO; Reset:0x00
    ESPI_STATUS_SET_NP_FREE_MASK = (int)0x2,
    ESPI_STATUS_SET_NP_FREE_POS = 1,
    // write 1 will set the vwire_free; Type:WO; Reset:0x00
    ESPI_STATUS_SET_VWIRE_FREE_MASK = (int)0x4,
    ESPI_STATUS_SET_VWIRE_FREE_POS = 2,
    // write 1 will set the oob_free; Type:WO; Reset:0x00
    ESPI_STATUS_SET_OOB_FREE_MASK = (int)0x8,
    ESPI_STATUS_SET_OOB_FREE_POS = 3,
    // write 1 will set the pc_avail; Type:WO; Reset:0x00
    ESPI_STATUS_SET_PC_AVAIL_MASK = (int)0x10,
    ESPI_STATUS_SET_PC_AVAIL_POS = 4,
    // write 1 will set the np_avail; Type:WO; Reset:0x00
    ESPI_STATUS_SET_NP_AVAIL_MASK = (int)0x20,
    ESPI_STATUS_SET_NP_AVAIL_POS = 5,
    // write 1 will set the vwire_avail; Type:WO; Reset:0x00
    ESPI_STATUS_SET_VWIRE_AVAIL_MASK = (int)0x40,
    ESPI_STATUS_SET_VWIRE_AVAIL_POS = 6,
    // wire 1 will set the oob_avail; Type:WO; Reset:0x00
    ESPI_STATUS_SET_OOB_AVAIL_MASK = (int)0x80,
    ESPI_STATUS_SET_OOB_AVAIL_POS = 7,
    // write 1 will set the flash_c_free; Type:WO; Reset:0x00
    ESPI_STATUS_SET_FLASH_C_FREE_MASK = (int)0x100,
    ESPI_STATUS_SET_FLASH_C_FREE_POS = 8,
    // write 1 will set the flash_np_free; Type:WO; Reset:0x00
    ESPI_STATUS_SET_FLASH_NP_FREE_MASK = (int)0x200,
    ESPI_STATUS_SET_FLASH_NP_FREE_POS = 9,
    // write 1 will set the flash_c_avail; Type:WO; Reset:0x00
    ESPI_STATUS_SET_FLASH_C_AVAIL_MASK = (int)0x1000,
    ESPI_STATUS_SET_FLASH_C_AVAIL_POS = 12,
    // write 1 will set the flash_np_free; Type:WO; Reset:0x00
    ESPI_STATUS_SET_FLASH_NP_AVAIL_MASK = (int)0xe000,
    ESPI_STATUS_SET_FLASH_NP_AVAIL_POS = 13,
    // write 1 will clear the alert; Type:WO; Reset:0x00
    ESPI_STATUS_ALERT_SET_MASK = (int)0x10000,
    ESPI_STATUS_ALERT_SET_POS = 16,
    // write 1 will set the  alert; Type:WO; Reset:0x00
    ESPI_STATUS_ALERT_CLEAR_MASK = (int)0x20000,
    ESPI_STATUS_ALERT_CLEAR_POS = 17
};

enum ESPI_REG_DN_VWIR_IDX_CTRL0_FIELD
{
    // virtual wire index for user defined virtual wire group0; Type:RW; Reset:0x40
    ESPI_DN_VWIR_IDX_P00_MASK = 0xFF,
    ESPI_DN_VWIR_IDX_P00_POS = 0,
    // virtual wire index for user defined virtual wire group1; Type:RW; Reset:0x41
    ESPI_DN_VWIR_IDX_P01_MASK = 0xFF00,
    ESPI_DN_VWIR_IDX_P01_POS = 8,
    // virtual wire index for user defined virtual wire group2; Type:RW; Reset:0x42
    ESPI_DN_VWIR_IDX_P02_MASK = 0xFF0000,
    ESPI_DN_VWIR_IDX_P02_POS = 16,
    // virtual wire index for user defined virtual wire group3; Type:RW; Reset:0x43
    ESPI_DN_VWIR_IDX_P03_MASK = 0xFF000000,
    ESPI_DN_VWIR_IDX_P03_POS = 24
};

enum ESPI_REG_DN_VWIR_IDX_CTRL1_FIELD
{
    // virtual wire index for user defined virtual wire group4; Type:RW; Reset:0x44
    ESPI_DN_VWIR_IDX_P04_MASK = (int)0xFF,
    ESPI_DN_VWIR_IDX_P04_POS = 0,
    // virtual wire index for user defined virtual wire group5; Type:RW; Reset:0x45
    ESPI_DN_VWIR_IDX_P05_MASK = (int)0xFF00,
    ESPI_DN_VWIR_IDX_P05_POS = 8,
    // virtual wire index for user defined virtual wire group6; Type:RW; Reset:0x46
    ESPI_DN_VWIR_IDX_P06_MASK = (int)0xFF0000,
    ESPI_DN_VWIR_IDX_P06_POS = 16,
    // virtual wire index for user defined virtual wire group7; Type:RW; Reset:0x47
    ESPI_DN_VWIR_IDX_P07_MASK = (int)0xFF000000,
    ESPI_DN_VWIR_IDX_P07_POS = 24
};

enum ESPI_REG_DN_VWIR_VAL0_FIELD
{
    // virtual wire value for user defined virtual wire group0; Type:RO; Reset:0x00
    ESPI_DN_VWIR_VAL0_P00_MASK = (int)0xF,
    ESPI_DN_VWIR_VAL0_P00_POS = 0,
    // virtual wire value for user defined virtual wire group1; Type:RO; Reset:0x00
    ESPI_DN_VWIR_VAL0_P01_MASK = (int)0xF00,
    ESPI_DN_VWIR_VAL0_P01_POS = 8,
    // virtual wire value for user defined virtual wire group2; Type:RO; Reset:0x00
    ESPI_DN_VWIR_VAL0_P02_MASK = (int)0xF0000,
    ESPI_DN_VWIR_VAL0_P02_POS = 16,
    // virtual wire value for user defined virtual wire group3; Type:RO; Reset:0x00
    ESPI_DN_VWIR_VAL0_P03_MASK = (int)0xF000000,
    ESPI_DN_VWIR_VAL0_P03_POS = 24
};

enum ESPI_REG_DN_VWIR_VAL1_FIELD
{
    // virtual wire value for user defined virtual wire group4; Type:RO; Reset:0x00
    ESPI_DN_VWIR_VAL0_P04_MASK = (int)0xF,
    ESPI_DN_VWIR_VAL0_P04_POS = 0,
    // virtual wire value for user defined virtual wire group5; Type:RO; Reset:0x00
    ESPI_DN_VWIR_VAL0_P05_MASK = (int)0xF00,
    ESPI_DN_VWIR_VAL0_P05_POS = 8,
    // virtual wire value for user defined virtual wire group6; Type:RO; Reset:0x00
    ESPI_DN_VWIR_VAL0_P06_MASK = (int)0xF0000,
    ESPI_DN_VWIR_VAL0_P06_POS = 16,
    // virtual wire value for user defined virtual wire group7; Type:RO; Reset:0x00
    ESPI_DN_VWIR_VAL0_P07_MASK = (int)0xF000000,
    ESPI_DN_VWIR_VAL0_P07_POS = 24
};

enum ESPI_REG_DN_VWIR_SYS0_FIELD
{
    // virtual wire value  for system virtual wire group2; Type:RO; Reset:0x00
    ESPI_DN_VWIR_S02_MASK = (int)0xF0000,
    ESPI_DN_VWIR_S02_POS = 16,
    // virtual wire value  for system virtual wire group3; Type:RO; Reset:0x00
    ESPI_DN_VWIR_S03_MASK = (int)0xF000000,
    ESPI_DN_VWIR_S03_POS = 24,
};

enum ESPI_REG_DN_VWIR_SYS1_FIELD
{
    // virtual wire value for system virtual wire group7; Type:RO; Reset:0x00
    ESPI_DN_VWIR_S07_MASK = (int)0xF000000,
    ESPI_DN_VWIR_S07_POS = 24
};

enum ESPI_REG_INTERRUPT_FIELD
{
    // peripheral channel down stream posted command interrupt which is issued after PUT_PC or PUT_MEMWR32_SHORT; Type:RO; Reset:0x00
    ESPI_INTR_STT_PSTC_FREE_MASK = (int)0x1,
    ESPI_INTR_STT_PSTC_FREE_POS = 0,
    // peripheral channel down stream non-posted command interrupt which is issued after PUT_NP, PUT_IORD32_SHORT, PUT_IOWR32_SHORT, PUT_MEMRD32_SHORT; Type:RO; Reset:0x00
    ESPI_INTR_STT_NPST_FREE_MASK = (int)0x2,
    ESPI_INTR_STT_NPST_FREE_POS = 1,
    // virtual wire channel down stream command interrupt which is issued after PUT_VWIRE; Type:RO; Reset:0x00
    ESPI_INTR_STT_VWIR_FREE_MASK = (int)0x4,
    ESPI_INTR_STT_VWIR_FREE_POS = 2,
    // OOB channel down stream command interrupt which is issued after PUT_OOB; Type:RO; Reset:0x00
    ESPI_INTR_STT_OOBP_FREE_MASK = (int)0x8,
    ESPI_INTR_STT_OOBP_FREE_POS = 3,
    // peripheral channel up stream posted command interrupt which is issued after GET_PC; Type:RO; Reset:0x00
    ESPI_INTR_STT_PSTC_AVAL_MASK = (int)0x10,
    ESPI_INTR_STT_PSTC_AVAL_POS = 4,
    // peripheral channel up stream non-posted command interrupt which is issued after GET_NP; Type:RO; Reset:0x00
    ESPI_INTR_STT_NPSTC_AVAL_MASK = (int)0x20,
    ESPI_INTR_STT_NPSTC_AVAL_POS = 5,
    // virtual wire channel up stream command interrupt which is issued after GET_VWIRE; Type:RO; Reset:0x00
    ESPI_INTR_STT_VWIR_AVAL_MASK = (int)0x40,
    ESPI_INTR_STT_VWIR_AVAL_POS = 6,
    // OOB channel up stream command interrupt which is issued after GET_OOB; Type:RO; Reset:0x00
    ESPI_INTR_STT_OOBP_AVAL_MASK = (int)0x80,
    ESPI_INTR_STT_OOBP_AVAL_POS = 7,
    // flash channel down stream posted command interrupt which is issued after PUT_FLASH_C; Type:RO; Reset:0x00
    ESPI_INTR_STT_FLSC_FREE_MASK = (int)0x100,
    ESPI_INTR_STT_FLSC_FREE_POS = 8,
    // flash channel down stream non-posted command interrupt which is issued after PUT_FLASH_NP; Type:RO; Reset:0x00
    ESPI_INTR_STT_FLSN_FREE_MASK = (int)0x200,
    ESPI_INTR_STT_FLSN_FREE_POS = 9,
    // flash channel up stream posted command interrupt which is issued after GET_FLASH_C; Type:RO; Reset:0x00
    ESPI_INTR_STT_FLSC_AVAL_MASK = (int)0x400,
    ESPI_INTR_STT_FLSC_AVAL_POS = 10,
    // flash channel up stream non-posted command interrupt which is issued after GET_FLASH_NP; Type:RO; Reset:0x00
    ESPI_INTR_STT_FLSN_AVAL_MASK = (int)0x800,
    ESPI_INTR_STT_FLSN_AVAL_POS = 11,
    // down stream FIFO over run interrupt; Type:RW; Reset:0x00
    ESPI_INTR_STT_DN_FIFO_OVR_MASK = (int)0x1000,
    ESPI_INTR_STT_DN_FIFO_OVR_POS = 12,
    // up stream FIFO under run interrupt; Type:RO; Reset:0x00
    ESPI_INTR_STT_UP_FIFO_UDR_MASK = (int)0x2000,
    ESPI_INTR_STT_UP_FIFO_UDR_POS = 13,
    // down stream configuration interrupt which is issued after SET_CONFIGURATION; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_CNFG_MASK = (int)0x4000,
    ESPI_INTR_STT_DN_CNFG_POS = 14,
    // down stream system virtual wire group 2 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_02_MASK = (int)0x8000,
    ESPI_INTR_STT_DN_VWIR_02_POS = 15,
    // down stream system virtual wire group 3 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_03_MASK = (int)0x10000,
    ESPI_INTR_STT_DN_VWIR_03_POS = 16,
    // down stream system virtual wire group 7 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_07_MASK = (int)0x20000,
    ESPI_INTR_STT_DN_VWIR_07_POS = 17,
    // down stream user defined virtual wire group 0 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_P00_MASK = (int)0x40000,
    ESPI_INTR_STT_DN_VWIR_P00_POS = 18,
    // down stream user defined virtual wire group 1 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_P01_MASK = (int)0x80000,
    ESPI_INTR_STT_DN_VWIR_P01_POS = 19,
    // down stream user defined virtual wire group 2 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_P02_MASK = (int)0x100000,
    ESPI_INTR_STT_DN_VWIR_P02_POS = 20,
    // down stream user defined virtual wire group 3 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_P03_MASK = (int)0x200000,
    ESPI_INTR_STT_DN_VWIR_P03_POS = 21,
    // down stream user defined virtual wire group 4 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_P04_MASK = (int)0x400000,
    ESPI_INTR_STT_DN_VWIR_P04_POS = 22,
    // down stream user defined virtual wire group 5 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_P05_MASK = (int)0x800000,
    ESPI_INTR_STT_DN_VWIR_P05_POS = 23,
    // down stream user defined virtual wire group 6 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_P06_MASK = (int)0x1000000,
    ESPI_INTR_STT_DN_VWIR_P06_POS = 24,
    // down stream user defined virtual wire group 7 interrupt which is issued when the virtual wire value changes; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_VWIR_P07_MASK = (int)0x2000000,
    ESPI_INTR_STT_DN_VWIR_P07_POS = 25,
    // down stream reset interrupt which is issued after RESET; Type:RO; Reset:0x00
    ESPI_INTR_STT_DN_REST_MASK = (int)0x4000000,
    ESPI_INTR_STT_DN_REST_POS = 26
};

enum ESPI_REG_STATUS_FIELD
{
    // current eSPI status defined by the eSPI protocol; Type:RO; Reset:0x00
    ESPI_STATUS_MASK = (int)0xFFFF,
    ESPI_STATUS_POS = 0
};

enum ESPI_REG_STATUS_SEND_FIELD
{
    // the status send inthe last eSPI command; Type:RO; Reset:0x00
    ESPI_STATUS_SEND_MASK = (int)0xFFFF,
    ESPI_STATUS_SEND_POS = 0
};

#endif /* REG_ESPI_TYPE_H_ */
