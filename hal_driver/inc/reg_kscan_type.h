#ifndef REG_KSCAN_TYPE_H_
#define REG_KSCAN_TYPE_H_
#include <stdint.h>


/**
 * @brief KSCAN Control Registers
 */
typedef struct
{
    volatile uint32_t INTR_MSK;				//0x00	interrupt mask, each bit for one interrupt
    volatile uint32_t INTR_CLR;				//0x04	interrupt clear, each bit for one interrupt, write 1 will clear the interrupt
    volatile uint32_t INTR_STT;				//0x08	
    volatile uint32_t INTR_RAW;				//0x0C	interrupt raw status
    volatile uint32_t KSCAN_EN;				//0x10	scan enable, high active.
    volatile uint32_t KSCAN_ITV;			//0x14	clk_period*(kscan_itv+1) indicates the timing interval between two continuous scanning
    volatile uint32_t CYC_CTRL;				//0x18
    volatile uint32_t KEY_CTRL;				//0x1C
    volatile uint32_t CAP_VAL0;				//0x20
    volatile uint32_t CAP_VAL1;				//0x24
    volatile uint32_t CAP_VAL2;				//0x28
    volatile uint32_t CAP_VAL3;				//0x2C
    volatile uint32_t CAP_VAL4;				//0x30
}reg_kscan_t;


enum KSCAN_REG_INTR_STT_FIELD
{
    KSCAN_INTR_STT_ALL_MASK = (int)0x7,
    KSCAN_INTR_STT_ALL_POS = 0,
    KSCAN_INTR_STT_END_MASK = (int)0x1,
    KSCAN_INTR_STT_END_POS = 0,
    KSCAN_INTR_STT_KEY_MASK = (int)0x2,
    KSCAN_INTR_STT_KEY_POS = 1,
    KSCAN_INTR_STT_WAIT_MASK = (int)0x4,
    KSCAN_INTR_STT_WAIT_POS = 2
};


enum KSCAN_REG_KSCAN_EN_FIELD
{
    KSCAN_SCAN_EN_MASK = (int)0x1,
    KSCAN_SCAN_EN_POS = 0,
	KSCAN_WAIT_EN_MASK = (int)0x2,
    KSCAN_WAIT_EN_POS = 1
};

enum KSCAN_REG_CYC_CTRL_FIELD
{
	//64*clk_period*(cyc_len+1) indicates the scan time for one row of the key matrix
	KSCAN_CYC_CTRL_CYC_LEN_MASK = (int)0xFF,
	KSCAN_CYC_CTRL_CYC_LEN_POS = 0,
	//64*clk_period*(udrv_idx+1) indicates timing period between the beginning of scanning of each row and the timing point at which the controller will stop driving the output of the key scan
	KSCAN_CYC_CTRL_UDRV_IDX_MASK = (int)0xFF00,
	KSCAN_CYC_CTRL_UDRV_IDX_POS = 8,
	//64*clk_period*(cap_idx+1) indicates timing period between the beginning of scanning of each row and the sample point for the scanning of the current row
	KSCAN_CYC_CTRL_CAP_IDX_MASK = (int)0xFF0000,
	KSCAN_CYC_CTRL_CAP_IDX_POS = 16
};


enum KSCAN_REG_KEY_CTRL_FIELD
{
	//row valid, each bit for one row
	KSCAN_KEY_CTRL_KEYO_VLD_MASK = (int)0x3FFFF,
	KSCAN_KEY_CTRL_KEYO_VLD_POS = 0,
	//column valid, each bit for one column
	KSCAN_KEY_CTRL_KEYI_VLD_MASK = (int)0xFF00000,
	KSCAN_KEY_CTRL_KEYI_VLD_POS = 20,
	//column valid, each bit for one column
	KSCAN_KEY_CTRL_KEYO_VAL_MASK = (int)0x10000000,
	KSCAN_KEY_CTRL_KEYO_VAL_POS = 28,
	//the output value which the controller will drive on the output row
	KSCAN_KEY_CTRL_KEYI_VAL_MASK = (int)0x20000000,
	KSCAN_KEY_CTRL_KEYI_VAL_POS = 29
};


enum KSCAN_REG_CAP_VAL0_FIELD
{
	//the sampled column value when scanning row0
	KSCAN_CAP_VAL0_COL0_MASK = (int)0xFF,
	KSCAN_CAP_VAL0_COL0_POS = 0,
	//the sampled column value when scanning row1
	KSCAN_CAP_VAL0_COL1_MASK = (int)0xFF00,
	KSCAN_CAP_VAL0_COL1_POS = 8,
	//the sampled column value when scanning row2
	KSCAN_CAP_VAL0_COL2_MASK = (int)0xFF0000,
	KSCAN_CAP_VAL0_COL2_POS = 16,
	//the sampled column value when scanning row3
	KSCAN_CAP_VAL0_COL3_MASK = (int)0xFF000000,
	KSCAN_CAP_VAL0_COL3_POS = 24
};


enum KSCAN_REG_CAP_VAL1_FIELD
{
	//the sampled column value when scanning row4
	KSCAN_CAP_VAL1_COL4_MASK = (int)0xFF,
	KSCAN_CAP_VAL1_COL4_POS = 0,
	//the sampled column value when scanning row5
	KSCAN_CAP_VAL1_COL5_MASK = (int)0xFF00,
	KSCAN_CAP_VAL1_COL5_POS = 8,
	//the sampled column value when scanning row6
	KSCAN_CAP_VAL1_COL6_MASK = (int)0xFF0000,
	KSCAN_CAP_VAL1_COL6_POS = 16,
	//the sampled column value when scanning row7
	KSCAN_CAP_VAL1_COL7_MASK = (int)0xFF000000,
	KSCAN_CAP_VAL1_COL7_POS = 24
};


enum KSCAN_REG_CAP_VAL2_FIELD
{
	//the sampled column value when scanning row8
	KSCAN_CAP_VAL2_COL8_MASK = (int)0xFF,
	KSCAN_CAP_VAL2_COL8_POS = 0,
	//the sampled column value when scanning row9
	KSCAN_CAP_VAL2_COL9_MASK = (int)0xFF00,
	KSCAN_CAP_VAL2_COL9_POS = 8,
	//the sampled column value when scanning row10
	KSCAN_CAP_VAL2_COL10_MASK = (int)0xFF0000,
	KSCAN_CAP_VAL2_COL10_POS = 16,
	//the sampled column value when scanning row11
	KSCAN_CAP_VAL2_COL11_MASK = (int)0xFF000000,
	KSCAN_CAP_VAL2_COL11_POS = 24
};


enum KSCAN_REG_CAP_VAL3_FIELD
{
	//the sampled column value when scanning row12
	KSCAN_CAP_VAL3_COL12_MASK = (int)0xFF,
	KSCAN_CAP_VAL3_COL12_POS = 0,
	//the sampled column value when scanning row13
	KSCAN_CAP_VAL3_COL13_MASK = (int)0xFF00,
	KSCAN_CAP_VAL3_COL13_POS = 8,
	//the sampled column value when scanning row14
	KSCAN_CAP_VAL3_COL14_MASK = (int)0xFF0000,
	KSCAN_CAP_VAL3_COL14_POS = 16,
	//the sampled column value when scanning row15
	KSCAN_CAP_VAL3_COL15_MASK = (int)0xFF000000,
	KSCAN_CAP_VAL3_COL15_POS = 24
};


enum KSCAN_REG_CAP_VAL4_FIELD
{
	//the sampled column value when scanning row16
	KSCAN_CAP_VAL4_COL16_MASK = (int)0xFF,
	KSCAN_CAP_VAL4_COL16_POS = 0,
	//the sampled column value when scanning row17
	KSCAN_CAP_VAL4_COL17_MASK = (int)0xFF00,
	KSCAN_CAP_VAL4_COL17_POS = 8
};



#endif /* REG_KSCAN_TYPE_H_ */
