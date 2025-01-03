#ifndef REG_SYSC_SEC_AWO_TYPE_H_
#define REG_SYSC_SEC_AWO_TYPE_H_
#include <stdint.h>
#include "reg_base_addr.h"

#define SYSC_SEC_AWO ((reg_sysc_sec_awo_t *)SEC_SYSC_AWO_SEC_ADDR)

typedef struct
{
    volatile uint32_t RESERVED0[1];
    volatile uint32_t SLP_HLD_CTRL; //0x4
    volatile uint32_t CRYPT_WORD; //0x8
    volatile uint32_t AWO_CTRL; //0xc
    volatile uint32_t DPLL1_CTRL1; //0x10
    volatile uint32_t DPLL1_CTRL2; //0x14
    volatile uint32_t DPLL2_CTRL1; //0x18
    volatile uint32_t DPLL2_CTRL2; //0x1c
    volatile uint32_t RESERVED1[1];
    volatile uint32_t DBG_RST_CTRL; //0x24
    volatile uint32_t PD_AWO_CLKG_SRST; //0x28
    volatile uint32_t PD_AWO_CLK_CTRL0; //0x2c
    volatile uint32_t PD_AWO_CLK_CTRL1; //0x30
    volatile uint32_t RESERVED2[1];
    volatile uint32_t PD_AWO_ANA1; //0x38
    volatile uint32_t CLK_OUT_SEL; //0x3c
    volatile uint32_t TEST_STATUS; //0x40
    volatile uint32_t CPU_CDBGPWRUPACK; //0x44
    volatile uint32_t DPLL_LOCK; //0x48
    volatile uint32_t RESERVED3[1];
#if 1
    volatile uint32_t FUNC_IO_LOCK[15]; //0x50
#else
    volatile uint32_t FUNC_IOA_LOCK; //0x50
    volatile uint32_t FUNC_IOB_LOCK; //0x54
    volatile uint32_t FUNC_IOC_LOCK; //0x58
    volatile uint32_t FUNC_IOD_LOCK; //0x5c
    volatile uint32_t FUNC_IOE_LOCK; //0x60
    volatile uint32_t FUNC_IOF_LOCK; //0x64
    volatile uint32_t FUNC_IOG_LOCK; //0x68
    volatile uint32_t FUNC_IOH_LOCK; //0x6c
    volatile uint32_t FUNC_IOI_LOCK; //0x70
    volatile uint32_t FUNC_IOJ_LOCK; //0x74
    volatile uint32_t FUNC_IOK_LOCK; //0x78
    volatile uint32_t FUNC_IOM_LOCK; //0x7c
    volatile uint32_t FUNC_ION_LOCK; //0x80
    volatile uint32_t FUNC_IOQ_LOCK; //0x84
    volatile uint32_t FUNC_IOT_LOCK; //0x88
#endif
} reg_sysc_sec_awo_t;

enum SYSC_SEC_AWO_REG_SLP_HLD_CTRL_FIELD {
    SYSC_SEC_AWO_SLP_HLD_DLY_MASK = (int)0x3f,
    SYSC_SEC_AWO_SLP_HLD_DLY_POS = 0,
};

enum SYSC_SEC_AWO_REG_CRYPT_WORD_FIELD {
    SYSC_SEC_AWO_CRYPT_WORD_MASK = (int)0xffffffff,
    SYSC_SEC_AWO_CRYPT_WORD_POS = 0,
};

enum SYSC_SEC_AWO_REG_AWO_CTRL_FIELD {
    SYSC_SEC_AWO_DBG_REQ_VLD_MASK = (int)0x1,
    SYSC_SEC_AWO_DBG_REQ_VLD_POS = 0,
    SYSC_SEC_AWO_CRYPT_EN_MASK = (int)0x80000000,
    SYSC_SEC_AWO_CRYPT_EN_POS = 31,
};

enum SYSC_SEC_AWO_REG_DPLL1_CTRL1_FIELD {
    SYSC_SEC_AWO_DPLL1_CTRL1_MASK = (int)0xffffffff,
    SYSC_SEC_AWO_DPLL1_CTRL1_POS = 0,
};

enum SYSC_SEC_AWO_REG_DPLL1_CTRL2_FIELD {
    SYSC_SEC_AWO_DPLL1_CTRL2_MASK = (int)0xff,
    SYSC_SEC_AWO_DPLL1_CTRL2_POS = 0,
};

enum SYSC_SEC_AWO_REG_DPLL2_CTRL1_FIELD {
    SYSC_SEC_AWO_DPLL2_CTRL1_MASK = (int)0xffffffff,
    SYSC_SEC_AWO_DPLL2_CTRL1_POS = 0,
};

enum SYSC_SEC_AWO_REG_DPLL2_CTRL2_FIELD {
    SYSC_SEC_AWO_DPLL2_CTRL2_MASK = (int)0xff,
    SYSC_SEC_AWO_DPLL2_CTRL2_POS = 0,
};

enum SYSC_SEC_AWO_REG_DBG_RST_CTRL_FIELD {
    SYSC_SEC_AWO_DBG_RST_STP_DLY_MASK = (int)0xf0,
    SYSC_SEC_AWO_DBG_RST_STP_DLY_POS = 4,
};

enum SYSC_SEC_AWO_REG_PD_AWO_CLKG_SRST_FIELD {
    SYSC_SEC_AWO_CLKG_SET_DIV_HBUS_MASK = (int)0x1,
    SYSC_SEC_AWO_CLKG_SET_DIV_HBUS_POS = 0,
    SYSC_SEC_AWO_CLKG_CLR_DIV_HBUS_MASK = (int)0x2,
    SYSC_SEC_AWO_CLKG_CLR_DIV_HBUS_POS = 1,
};

enum SYSC_SEC_AWO_REG_PD_AWO_CLK_CTRL0_FIELD {
    SYSC_SEC_AWO_CLK_DIV_PARA_HBUS_M1_MASK = (int)0xf,
    SYSC_SEC_AWO_CLK_DIV_PARA_HBUS_M1_POS = 0,
    SYSC_SEC_AWO_CLK_SEL_HBUS_MASK = (int)0x1f0,
    SYSC_SEC_AWO_CLK_SEL_HBUS_POS = 4,
    SYSC_SEC_AWO_CLK_SEL_HBUS_M1_MASK = (int)0x200,
    SYSC_SEC_AWO_CLK_SEL_HBUS_M1_POS = 9,
    SYSC_SEC_AWO_HSE_DCT_EN_MASK = (int)0x400,
    SYSC_SEC_AWO_HSE_DCT_EN_POS = 10,
    SYSC_SEC_AWO_HBUS_FLT_CTRL_MASK = (int)0xf000,
    SYSC_SEC_AWO_HBUS_FLT_CTRL_POS = 12,
    SYSC_SEC_AWO_QSPI_FLT_CTRL_MASK = (int)0xf0000,
    SYSC_SEC_AWO_QSPI_FLT_CTRL_POS = 16,
    SYSC_SEC_AWO_CLK_SEL_QSPI_MASK = (int)0x1f00000,
    SYSC_SEC_AWO_CLK_SEL_QSPI_POS = 20,
    SYSC_SEC_AWO_CLK_SEL_HBUS_FLT_MASK = (int)0x30000000,
    SYSC_SEC_AWO_CLK_SEL_HBUS_FLT_POS = 28,
    SYSC_SEC_AWO_CLK_SEL_QSPI_FLT_MASK = (int)0xc0000000,
    SYSC_SEC_AWO_CLK_SEL_QSPI_FLT_POS = 30,
};

enum SYSC_SEC_AWO_REG_PD_AWO_CLK_CTRL1_FIELD {
    SYSC_SEC_AWO_CLK_SEL_PBUS0_MASK = (int)0x3,
    SYSC_SEC_AWO_CLK_SEL_PBUS0_POS = 0,
    SYSC_SEC_AWO_CLK_SEL_PBUS1_MASK = (int)0xc,
    SYSC_SEC_AWO_CLK_SEL_PBUS1_POS = 2,
    SYSC_SEC_AWO_CLK_SEL_PBUS2_MASK = (int)0x30,
    SYSC_SEC_AWO_CLK_SEL_PBUS2_POS = 4,
    SYSC_SEC_AWO_CLK_SEL_PBUS3_MASK = (int)0xc0,
    SYSC_SEC_AWO_CLK_SEL_PBUS3_POS = 6,
    SYSC_SEC_AWO_CLK_SEL_PBUS4_MASK = (int)0x300,
    SYSC_SEC_AWO_CLK_SEL_PBUS4_POS = 8,
    SYSC_SEC_AWO_CLK_DIV_HBUS_MASK = (int)0xf000,
    SYSC_SEC_AWO_CLK_DIV_HBUS_POS = 12,
    SYSC_SEC_AWO_CLK_SEL_OTP_MASK = (int)0x70000,
    SYSC_SEC_AWO_CLK_SEL_OTP_POS = 16,
};

enum SYSC_SEC_AWO_REG_PD_AWO_ANA1_FIELD {
    SYSC_SEC_AWO_HSI_CAL_CFG_MASK = (int)0x7fff,
    SYSC_SEC_AWO_HSI_CAL_CFG_POS = 0,
};

enum SYSC_SEC_AWO_REG_CLK_OUT_SEL_FIELD {
    SYSC_SEC_AWO_CLK_OUT_SEL_MASK = (int)0x30000000,
    SYSC_SEC_AWO_CLK_OUT_SEL_POS = 28,
};

enum SYSC_SEC_AWO_REG_TEST_STATUS_FIELD {
    SYSC_SEC_AWO_TEST_DATA_MASK = (int)0xffff,
    SYSC_SEC_AWO_TEST_DATA_POS = 0,
    SYSC_SEC_AWO_TEST_DOTE_MASK = (int)0xffff0000,
    SYSC_SEC_AWO_TEST_DOTE_POS = 16,
};

enum SYSC_SEC_AWO_REG_CPU_CDBGPWRUPACK_FIELD {
    SYSC_SEC_AWO_CPU_CDBGPWRUPACK_MASK = (int)0x1,
    SYSC_SEC_AWO_CPU_CDBGPWRUPACK_POS = 0,
};

enum SYSC_SEC_AWO_REG_DPLL_LOCK_FIELD {
    SYSC_SEC_AWO_DPLL1_LOCK_MASK = (int)0x1,
    SYSC_SEC_AWO_DPLL1_LOCK_POS = 0,
    SYSC_SEC_AWO_DPLL2_LOCK_MASK = (int)0x2,
    SYSC_SEC_AWO_DPLL2_LOCK_POS = 1,
    SYSC_SEC_AWO_DPLL1_APFS_DONE_MASK = (int)0x4,
    SYSC_SEC_AWO_DPLL1_APFS_DONE_POS = 2,
    SYSC_SEC_AWO_DPLL2_APFS_DONE_MASK = (int)0x8,
    SYSC_SEC_AWO_DPLL2_APFS_DONE_POS = 3,
};

enum SYSC_SEC_AWO_REG_FUNC_IOA_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOA_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOA_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOB_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOB_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOB_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOC_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOC_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOC_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOD_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOD_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOD_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOE_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOE_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOE_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOF_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOF_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOF_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOG_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOG_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOG_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOH_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOH_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOH_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOI_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOI_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOI_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOJ_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOJ_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOJ_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOK_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOK_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOK_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOM_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOM_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOM_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_ION_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_ION_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_ION_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOQ_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOQ_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOQ_LOCK_POS = 0,
};

enum SYSC_SEC_AWO_REG_FUNC_IOT_LOCK_FIELD {
    SYSC_SEC_AWO_FUNC_IOT_LOCK_MASK = (int)0xffff,
    SYSC_SEC_AWO_FUNC_IOT_LOCK_POS = 0,
};

#endif
