#ifndef REG_APB_LCD_TYPE_H_
#define REG_APB_LCD_TYPE_H_
#include <stdint.h>

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t FCR;
    volatile uint32_t RESERVED0[2];
    volatile uint32_t INTR_MSK;
    volatile uint32_t INTR_CLR;
    volatile uint32_t INTR_STAT;
    volatile uint32_t INTR_RAW;
    volatile uint32_t SEGCR;
    volatile uint32_t RESERVED1[1];
    volatile uint32_t CTRL_CHP;
    volatile uint32_t RESERVED2[1];
    volatile uint32_t SR;
    volatile uint32_t RESERVED3[2];
    volatile uint32_t DAT_UPD;
    volatile uint32_t BUF0;
    volatile uint32_t BUF1;
    volatile uint32_t BUF2;
    volatile uint32_t BUF3;
    volatile uint32_t BUF4;
    volatile uint32_t BUF5;
    volatile uint32_t BUF6;
    volatile uint32_t BUF7;
}reg_apb_lcd_t;

enum APB_LCD_REG_CR_FIELD
{
    APB_LCD_LCD_DS_LP_MASK = (int)0xf00000,
    APB_LCD_LCD_DS_LP_POS = 20,
    APB_LCD_LCD_DS_MASK = (int)0xf0000,
    APB_LCD_LCD_DS_POS = 16,
    APB_LCD_LCD_BUF_LP_MASK = (int)0x8000,
    APB_LCD_LCD_BUF_LP_POS = 15,
    APB_LCD_LCD_BUF_MASK = (int)0x4000,
    APB_LCD_LCD_BUF_POS = 14,
    APB_LCD_LCD_RES_LP_MASK = (int)0x3000,
    APB_LCD_LCD_RES_LP_POS = 12,
    APB_LCD_LCD_RES_MASK = (int)0xc00,
    APB_LCD_LCD_RES_POS = 10,
    APB_LCD_LCD_BIAS_MASK = (int)0x300,
    APB_LCD_LCD_BIAS_POS = 8,
    APB_LCD_LCD_DUTY_MASK = (int)0x70,
    APB_LCD_LCD_DUTY_POS = 4,
    APB_LCD_LCD_OE_MASK = (int)0x8,
    APB_LCD_LCD_OE_POS = 3,
    APB_LCD_LCD_EN_MASK = (int)0x1,
    APB_LCD_LCD_EN_POS = 0,
};

enum APB_LCD_REG_FCR_FIELD
{
    APB_LCD_LCD_WFS_MASK = (int)0x80000000,
    APB_LCD_LCD_WFS_POS = 31,
    APB_LCD_LCD_PRS_MASK = (int)0xf000000,
    APB_LCD_LCD_PRS_POS = 24,
    APB_LCD_LCD_DIV_MASK = (int)0xf00000,
    APB_LCD_LCD_DIV_POS = 20,
    APB_LCD_LCD_DEAD_MASK = (int)0x700,
    APB_LCD_LCD_DEAD_POS = 8,
    APB_LCD_LCD_PON_MASK = (int)0xf0,
    APB_LCD_LCD_PON_POS = 4,
};

enum APB_LCD_REG_INTR_MSK_FIELD
{
    APB_LCD_IMSK_MASK = (int)0x1,
    APB_LCD_IMSK_POS = 0,
};

enum APB_LCD_REG_INTR_CLR_FIELD
{
    APB_LCD_ICLR_MASK = (int)0x1,
    APB_LCD_ICLR_POS = 0,
};

enum APB_LCD_REG_INTR_STAT_FIELD
{
    APB_LCD_ISTAT_MASK = (int)0x1,
    APB_LCD_ISTAT_POS = 0,
};

enum APB_LCD_REG_INTR_RAW_FIELD
{
    APB_LCD_IRAW_MASK = (int)0x1,
    APB_LCD_IRAW_POS = 0,
};

enum APB_LCD_REG_SEGCR_FIELD
{
    APB_LCD_LCD_SEG_OE_MASK = (int)0xffffff,
    APB_LCD_LCD_SEG_OE_POS = 0,
};

enum APB_LCD_REG_CTRL_CHP_FIELD
{
    APB_LCD_CHP_EN_MASK = (int)0x1,
    APB_LCD_CHP_EN_POS = 0,
    APB_LCD_CHP_TRIM_MASK = (int)0x3000,
    APB_LCD_CHP_TRIM_POS = 12,
    APB_LCD_CHP_CLK_DIV_M1_MASK = (int)0x3fff0000,
    APB_LCD_CHP_CLK_DIV_M1_POS = 16,
};

enum APB_LCD_REG_SR_FIELD
{
    APB_LCD_CTRL_REQ_MASK = (int)0x1,
    APB_LCD_CTRL_REQ_POS = 0,
    APB_LCD_DATA_REQ_MASK = (int)0x2,
    APB_LCD_DATA_REQ_POS = 1,
    APB_LCD_CTRL_ACK_MASK = (int)0x4,
    APB_LCD_CTRL_ACK_POS = 2,
    APB_LCD_DATA_ACK_MASK = (int)0x8,
    APB_LCD_DATA_ACK_POS = 3,
};

enum APB_LCD_REG_DAT_UPD_FIELD
{
    APB_LCD_LCD_DAT_UPD_MASK = (int)0x1,
    APB_LCD_LCD_DAT_UPD_POS = 0,
};

enum APB_LCD_REG_BUF0_FIELD
{
    APB_LCD_LCD_BUF0_MASK = (int)0xffffff,
    APB_LCD_LCD_BUF0_POS = 0,
};

enum APB_LCD_REG_BUF1_FIELD
{
    APB_LCD_LCD_BUF1_MASK = (int)0xffffff,
    APB_LCD_LCD_BUF1_POS = 0,
};

enum APB_LCD_REG_BUF2_FIELD
{
    APB_LCD_LCD_BUF2_MASK = (int)0xffffff,
    APB_LCD_LCD_BUF2_POS = 0,
};

enum APB_LCD_REG_BUF3_FIELD
{
    APB_LCD_LCD_BUF3_MASK = (int)0xffffff,
    APB_LCD_LCD_BUF3_POS = 0,
};

enum APB_LCD_REG_BUF4_FIELD
{
    APB_LCD_LCD_BUF4_MASK = (int)0xffffff,
    APB_LCD_LCD_BUF4_POS = 0,
};

enum APB_LCD_REG_BUF5_FIELD
{
    APB_LCD_LCD_BUF5_MASK = (int)0xffffff,
    APB_LCD_LCD_BUF5_POS = 0,
};

enum APB_LCD_REG_BUF6_FIELD
{
    APB_LCD_LCD_BUF6_MASK = (int)0xffffff,
    APB_LCD_LCD_BUF6_POS = 0,
};

enum APB_LCD_REG_BUF7_FIELD
{
    APB_LCD_LCD_BUF7_MASK = (int)0xffffff,
    APB_LCD_LCD_BUF7_POS = 0,
};

#endif


