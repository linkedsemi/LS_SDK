#ifndef REG_MAC_TYPE_H_
#define REG_MAC_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t CLK_DIV; 		// 0x00
    volatile uint32_t POLY;			// 0x04
    volatile uint32_t TX_RAMP;		// 0x08
    volatile uint32_t SYNC_WORD;	// 0x0c
    volatile uint32_t PHY;			// 0x10
    volatile uint32_t TX_LEN;		// 0x14
    volatile uint32_t TX_CTE;		// 0x18
    volatile uint32_t CRC_WHITEN;	// 0x1c
    volatile uint32_t TX_CTRL;		// 0x20
    volatile uint32_t START_TIME;	// 0x24
    volatile uint32_t TARGET_TIME1;	// 0x28
    volatile uint32_t TIME_ADJUST;	// 0x2c
    volatile uint32_t RX_RAMP;		// 0x30
    volatile uint32_t RX_WIN;		// 0x34
    volatile uint32_t RX_CFG;		// 0x38
    volatile uint32_t RX_CTRL;		// 0x3c
    volatile uint32_t INT_MASK1;	// 0x40
    volatile uint32_t INT_CLR;		// 0x44
    volatile uint32_t INT_STAT1;	// 0x48
    volatile uint32_t INT_RAW;		// 0x4c
    volatile uint32_t FIFO_CFG;		// 0x50
    volatile uint32_t FIFO_TX_THRESHOLD;	// 0x54
    volatile uint32_t FIFO_RX_THRESHOLD;	// 0x58
    volatile uint32_t DMA_EN;		// 0x5c
    volatile uint32_t FIFO_TX;		// 0x60
    volatile uint32_t FIFO_RX;		// 0x64
    volatile uint32_t SLEEP_CTRL;	// 0x68
    volatile uint32_t DBG_SEL;		// 0x6c
    volatile uint32_t FSM_STAT;		// 0x70
    volatile uint32_t CURRENT_TIME;	// 0x74
    volatile uint32_t RX_TIME;		// 0x78
    volatile uint32_t DBG_STAT;		// 0x7c
    volatile uint32_t DUMMY0;		// 0x80
    volatile uint32_t RX_STATUS;	// 0x84
    volatile uint32_t SLEEP_ANCHOR;	// 0x88
    volatile uint32_t RX_RSSI;		// 0x8c
    volatile uint32_t DUMMY1[2];    // 0x90 0x94
    volatile uint32_t CTE_CTRL;		// 0x98
    volatile uint32_t DUMMY2;		// 0x9c
    union
    {
        struct {
            volatile uint32_t PKT_CNT[2];    // 0xa0 0xa4
            volatile uint32_t IV[2]; // 0xa8 0xac
        }a;
        struct {
            volatile uint32_t AES_DATA[4]; // 0xa0 0xa4 0xa8 0xac
        }b;
    }CRYPTO;
    volatile uint32_t AES_KEY[4];	// 0xb0 0xb4 0xb8 0xbc
    volatile uint32_t CRYPTO_CTRL;	// 0xc0
    volatile uint32_t DUMMY3[3];    // 0xc4 0xc8 0xcc
    volatile uint32_t PKT_CTRL0;    // 0xd0
    volatile uint32_t PKT_CTRL1;    // 0xd4
    volatile uint32_t ANT_CTRL0;    // 0xd8
    volatile uint32_t ANT_CTRL1;    // 0xdc
    volatile uint32_t TARGET_TIME2; // 0xe0
    volatile uint32_t INT_MASK2;    // 0xe4
    volatile uint32_t INT_STAT2;    // 0xe8
    volatile uint32_t DUMMY4;       // 0xec
    volatile uint32_t AES_RSLT[4];  // 0xf0 0xf4 0xf8 0xfc
}reg_mac_t;

enum MAC_POLY_FIELD
{
    MAC_CRC_POLY_MASK = 0xffffff,
    MAC_CRC_POLY_POS = 0,
    MAC_WHITEN_POLY_MASK = 0xff000000,
    MAC_WHITEN_POLY_POS = 24,
};

enum MAC_TX_RAMP_FIELD
{
    MAC_TX_RAMPUP_MASK = 0xff,
    MAC_TX_RAMPUP_POS = 0,
    MAC_TX_RAMPDOWN_MASK = 0xff00,
    MAC_TX_RAMPDOWN_POS = 8,
};

enum MAC_PHY_FIELD
{
    MAC_RATE_MASK = 0x3,
    MAC_RATE_POS = 0,
    MAC_RATE_OUT_MASK = 0xc,
    MAC_RATE_OUT_POS = 2,
    MAC_CODED_EN_MASK = 0x10,
    MAC_CODED_EN_POS = 4,
    MAC_CODED_CI_MASK = 0x100,
    MAC_CODED_CI_POS = 8,
    MAC_CHANNEL_MASK = 0x3f000,
    MAC_CHANNEL_POS = 12,
    MAC_TX_VTB_BYPASS_MASK = 0x100000,
    MAC_TX_VTB_BYPASS_POS = 20,
    MAC_FEC_EN_MASK = 0x200000,
    MAC_FEC_EN_POS = 21,
    MAC_AGC_EN_MASK = 0x1000000,
    MAC_AGC_EN_POS = 24,
    MAC_TX_POWER_MASK = 0xf0000000,
    MAC_TX_POWER_POS = 28,
};

enum MAC_TX_LEN_FIELD
{
	MAC_TX_PAYLOAD_LEN_MASK = 0xff,
	MAC_TX_PAYLOAD_LEN_POS = 0,
	MAC_TX_CTE_INFO_EN_MASK = 0x100,
	MAC_TX_CTE_INFO_EN_POS = 8,
	MAC_TX_INFINITE_EN_MASK = 0x1000,
	MAC_TX_INFINITE_EN_POS = 12,
};

enum MAC_TX_CTE_FIELD
{
    MAC_TX_CTE_EN_MASK = 0x1,
    MAC_TX_CTE_EN_POS = 0,
    MAC_TX_CTE_LEN_MASK = 0x1ff0,
    MAC_TX_CTE_LEN_POS = 4,
    MAC_TX_CTE_SLOT_MASK = 0x10000,
    MAC_TX_CTE_SLOT_POS = 16,
    MAC_TX_CTE_SWITCH_EN_MASK = 0x100000,
    MAC_TX_CTE_SWITCH_EN_POS = 20,
};

enum MAC_CRC_WHITEN_FIELD
{
    MAC_CRC_INIT_MASK = 0xffffff,
    MAC_CRC_INIT_POS = 0,
    MAC_WHITEN_INIT_MASK = 0x7f000000,
    MAC_WHITEN_INIT_POS = 24,
    MAC_WHITEN_BYPASS_MASK = 0x80000000,
    MAC_WHITEN_BYPASS_POS = 31,
};

enum MAC_TX_CTRL_FIELD
{
    MAC_TX_FSM_EN_MASK = 0x1,
    MAC_TX_FSM_EN_POS = 0,
    MAC_TX_FSM_STOP_MASK = 0x10,
    MAC_TX_FSM_STOP_POS = 4,
};

enum MAC_RX_RAMP_FIELD
{
    MAC_RX_RAMPDOWN_MASK = 0xff,
    MAC_RX_RAMPDOWN_POS = 0,
    MAC_RX_RAMPUP_MASK = 0x1ff00,
    MAC_RX_RAMPUP_POS = 8,

};

enum MAC_RX_WIN_FIELD
{
    MAC_RX_WINDOW_MASK = 0x3fff,
    MAC_RX_WINDOW_POS = 0,
    MAC_RX_WINDOW_UNLIMITED_MASK = 0x10000,
    MAC_RX_WINDOW_UNLIMITED_POS = 16,
};

enum MAC_RX_CFG_FIELD
{
	MAC_RX_ADV_TYPE_CTE_MASK = 0x01,
	MAC_RX_ADV_TYPE_CTE_POS = 0,
    MAC_RX_ADV_PKT_MASK = 0x10,
    MAC_RX_ADV_PKT_POS = 4,
    MAC_RX_CTE_EN_MASK = 0x100,
    MAC_RX_CTE_EN_POS = 8,
    MAC_RX_TIME_SEL_MASK = 0x3000,
    MAC_RX_TIME_SEL_POS = 12,
    MAC_RX_FLUSH_POINT_MASK = 0x1f0000,
    MAC_RX_FLUSH_POINT_POS = 16,
    MAC_RX_CTE_ADJ_MASK = 0x3f000000,
    MAC_RX_CTE_ADJ_POS = 24,
    MAC_RX_CTE_SLOT_MASK = 0x80000000,
    MAC_RX_CTE_SLOT_POS = 31,
};

enum MAC_RX_CTRL_FIELD
{
    MAC_RX_FSM_EN_MASK = 0x1,
    MAC_RX_FSM_EN_POS = 0,
    MAC_RX_FSM_STOP_MASK = 0x10,
    MAC_RX_FSM_STOP_POS = 4,
};

enum MAC_INT_FIELD
{
    MAC_TX_START_INT_MASK              = 0x1,
    MAC_TX_START_INT_POS               = 0,
    MAC_TX_PKT_INT_MASK                = 0x2,
    MAC_TX_PKT_INT_POS                 = 1,
    MAC_TX_END_INT_MASK                = 0x4,
    MAC_TX_END_INT_POS                 = 2,
    MAC_TX_UNDERRUN_INT_MASK           = 0x8,
    MAC_TX_UNDERRUN_INT_POS            = 3,
    MAC_RX_START_INT_MASK              = 0x10,
    MAC_RX_START_INT_POS               = 4,
    MAC_RX_SYNC_FOUND_INT_MASK         = 0x20,
    MAC_RX_SYNC_FOUND_INT_POS          = 5,
    MAC_RX_HEADER_INT_MASK             = 0x40,
    MAC_RX_HEADER_INT_POS              = 6,
    MAC_RX_PKT_INT_MASK                = 0x80,
    MAC_RX_PKT_INT_POS                 = 7,
    MAC_RX_END_INT_MASK                = 0x100,
    MAC_RX_END_INT_POS                 = 8,
    MAC_RX_OVERRUN_INT_MASK            = 0x200,
    MAC_RX_OVERRUN_INT_POS             = 9,
    MAC_TIMER1_INT_MASK                = 0x400,
    MAC_TIMER1_INT_POS                 = 10,
    MAC_SLEEP_INT_MASK                 = 0x800,
    MAC_SLEEP_INT_POS                  = 11,
    MAC_TX_FIFO_INT_MASK               = 0x1000,
    MAC_TX_FIFO_INT_POS                = 12,
    MAC_RX_FIFO_INT_MASK               = 0x2000,
    MAC_RX_FIFO_INT_POS                = 13,
    MAC_WAKEUP_INT_MASK                = 0x4000,
    MAC_WAKEUP_INT_POS                 = 14,
    MAC_TIMER2_INT_MASK                = 0x8000,
    MAC_TIMER2_INT_POS                 = 15,
    MAC_AES_DONE_INT_MASK              = 0x10000,
    MAC_AES_DONE_INT_POS               = 16,
};

enum MAC_FIFO_CFG_FIELD
{
    MAC_FIFO_DIR_MASK = 0x1,
    MAC_FIFO_DIR_POS = 0,
    MAC_FIFO_CLR_MASK = 0x10,
    MAC_FIFO_CLR_POS = 4,
};

enum MAC_DMA_EN_FIELD
{
    MAC_DMA_TX_EN_MASK = 0x1,
    MAC_DMA_TX_EN_POS = 0,
    MAC_DMA_RX_EN_MASK = 0x10,
    MAC_DMA_RX_EN_POS = 4,
};

enum MAC_SLEEP_CTRL_FIELD
{
    MAC_TIMER_EN_MASK = 0x1,
    MAC_TIMER_EN_POS = 0,
    MAC_SLEEP_REQ_MASK = 0x10,
    MAC_SLEEP_REQ_POS = 4,
    MAC_WAKEUP_REQ_MASK = 0x100,
    MAC_WAKEUP_REQ_POS = 8,
};

enum MAC_FSM_STAT_FIELD
{
    MAC_SLEEP_STAT_MASK = 0x1,
    MAC_SLEEP_STAT_POS = 0,
    MAC_TX_FSM_MASK = 0x70,
    MAC_TX_FSM_POS = 4,
    MAC_RX_FSM_MASK = 0xf00,
    MAC_RX_FSM_POS = 8,
    MAC_FIFO_LEVEL_MASK = 0x7f0000,
    MAC_FIFO_LEVEL_POS = 16,
};

enum MAC_RX_STATUS_FIELD
{
	MAC_RX_CRC_SHIFT_MASK = 0xffffff,
	MAC_RX_CRC_SHIFT_POS = 0,
	MAC_RX_MIC_ERROR_MASK = 0x1000000,
	MAC_RX_MIC_ERROR_POS = 24,
};

enum MAC_RX_RSSI_FIELD
{
	MAC_RX_RSSI_VALUE_MASK = 0xff,
	MAC_RX_RSSI_VALUE_POS = 0,
	MAC_RX_RSSI_VALID_MASK = 0x100,
	MAC_RX_RSSI_VALID_POS = 8,
};

enum MAC_CTE_CTRL_FIELD
{
	MAC_CTE_SAMPLE_POINT_MASK = 0x3f,
	MAC_CTE_SAMPLE_POINT_POS = 0,
	MAC_CTE_SWITCH_POINT_MASK = 0x3f00,
	MAC_CTE_SWITCH_POINT_POS = 8,
    MAC_RX_CTE_START_POINT_MASK = 0x1f0000,
    MAC_RX_CTE_START_POINT_POS = 16,
    MAC_RX_CTE_AT_CRC_MASK = 0x1000000,
    MAC_RX_CTE_AT_CRC_POS = 24,
};

enum MAC_CRYPTO_CTRL_FIELD
{
	MAC_AES_EN_MASK = 0x1,
	MAC_AES_EN_POS = 0,
    MAC_AES_START_MASK = 0x10,
    MAC_AES_START_POS = 4,
	MAC_AES_HEAD_MASK_MASK = 0xff0000,
	MAC_AES_HEAD_MASK_POS = 16,
};

enum MAC_PKT_CTRL0_FIELD
{
    MAC_SYNCWD_5TH_MASK = 0xff,
    MAC_SYNCWD_5TH_POS = 0,
    MAC_SYNCWD_5TH_EN_MASK = 0x100,
    MAC_SYNCWD_5TH_EN_POS = 8,
    MAC_HEAD_BIT_LEN_MASK = 0x1f000,
    MAC_HEAD_BIT_LEN_POS = 12,
    MAC_CRC_LEN_MASK = 0x300000,
    MAC_CRC_LEN_POS = 20,
};

enum MAC_PKT_CTRL1_FIELD
{
    MAC_FIX_PAYLOAD_LEN_MASK = 0xff0,
    MAC_FIX_PAYLOAD_LEN_POS = 4,
    MAC_RX_LEN_POS_MASK = 0xf000,
    MAC_RX_LEN_POS_POS = 12,
    MAC_RX_LEN_WIDTH_MASK = 0xf0000,
    MAC_RX_LEN_WIDTH_POS = 16,
    MAC_TX_PREAMBLE_LEN_MASK = 0xf00000,
    MAC_TX_PREAMBLE_LEN_POS = 20,
};

enum MAC_ANT_CTRL0_FIELD
{
    MAC_CTE_PAT_ANT0_MASK = 0x7,
    MAC_CTE_PAT_ANT0_POS = 0,
    MAC_CTE_PAT_ANT1_MASK = 0x70,
    MAC_CTE_PAT_ANT1_POS = 4,
    MAC_CTE_PAT_ANT2_MASK = 0x700,
    MAC_CTE_PAT_ANT2_POS = 8,
    MAC_CTE_PAT_ANT3_MASK = 0x7000,
    MAC_CTE_PAT_ANT3_POS = 12,
    MAC_CTE_PAT_ANT4_MASK = 0x70000,
    MAC_CTE_PAT_ANT4_POS = 16,
    MAC_CTE_PAT_ANT5_MASK = 0x700000,
    MAC_CTE_PAT_ANT5_POS = 20,
    MAC_CTE_PAT_ANT6_MASK = 0x7000000,
    MAC_CTE_PAT_ANT6_POS = 24,
    MAC_CTE_PAT_ANT7_MASK = 0x70000000,
    MAC_CTE_PAT_ANT7_POS = 28,
};

enum MAC_ANT_CTRL1_FIELD
{
    MAC_CTE_PAT_ANT8_MASK = 0x7,
    MAC_CTE_PAT_ANT8_POS = 0,
    MAC_CTE_PAT_ANT9_MASK = 0x70,
    MAC_CTE_PAT_ANT9_POS = 4,
    MAC_CTE_PAT_ANT10_MASK = 0x700,
    MAC_CTE_PAT_ANT10_POS = 8,
    MAC_CTE_PAT_ANT11_MASK = 0x7000,
    MAC_CTE_PAT_ANT11_POS = 12,
    MAC_CTE_PAT_INIT_MASK = 0x70000,
    MAC_CTE_PAT_INIT_POS = 16,
    MAC_CTE_PAT_NUM_MASK = 0x700000,
    MAC_CTE_PAT_NUM_POS = 20,
};

#endif

