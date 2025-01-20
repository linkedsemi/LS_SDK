#ifndef REG_SYSC_SEC_CPU_TYPE_H_
#define REG_SYSC_SEC_CPU_TYPE_H_
#include <stdint.h>
#include "reg_base_addr.h"

#define SYSC_SEC_CPU ((reg_sysc_sec_cpu_t *)SEC_SYSC_CPU_SEC_ADDR)

typedef struct
{
    volatile uint32_t CPU_SYSC; //0x0
    volatile uint32_t SYS_CLK; //0x4
    volatile uint32_t APP_CPU_ADDR_CFG; //0x8
    volatile uint32_t APP_CPU_SRST; //0xc
#if 1
    volatile uint32_t PD_CPU_CLKG[2]; //0x10
    volatile uint32_t PD_CPU_SRST[2]; //0x18
#else
    volatile uint32_t PD_CPU_CLKG0; //0x10
    volatile uint32_t PD_CPU_CLKG1; //0x14
    volatile uint32_t PD_CPU_SRST; //0x18
    volatile uint32_t PD_CPU_SRST1; //0x1c
#endif
    volatile uint32_t RESERVED0[2];
    volatile uint32_t SEC_CPU_INTR; //0x28
    volatile uint32_t SEC_CPU_IMSK; //0x2c
    volatile uint32_t RESERVED1[3];
    volatile uint32_t NIST_TRNG_CTRL; //0x3c
    volatile uint32_t RESERVED2[8];
    volatile uint32_t INTR_CTRL_INTR_MSK; //0x60
    volatile uint32_t INTR_CLR_MSK; //0x64
    volatile uint32_t OTBN_INTR_STT; //0x68
    volatile uint32_t OTBN_INTR_RAW; //0x6c
    volatile uint32_t OTBN_STT; //0x70
    volatile uint32_t OTBN_CTRL2; //0x74
    volatile uint32_t EDN_RND_BUS; //0x78
    volatile uint32_t EDN_URND_BUS; //0x7c
    volatile uint32_t OTBN_OTP_NONCE_0; //0x80
    volatile uint32_t OTBN_OTP_NONCE_1; //0x84
    volatile uint32_t OTBN_OTP_KEY_0; //0x88
    volatile uint32_t OTBN_OTP_KEY_1; //0x8c
    volatile uint32_t OTBN_OTP_KEY_2; //0x90
    volatile uint32_t OTBN_OTP_KEY_3; //0x94
    volatile uint32_t KEYMGR_KEY0_00; //0x98
    volatile uint32_t KEYMGR_KEY0_01; //0x9c
    volatile uint32_t KEYMGR_KEY0_02; //0xa0
    volatile uint32_t KEYMGR_KEY0_03; //0xa4
    volatile uint32_t KEYMGR_KEY0_04; //0xa8
    volatile uint32_t KEYMGR_KEY0_05; //0xac
    volatile uint32_t KEYMGR_KEY0_06; //0xb0
    volatile uint32_t KEYMGR_KEY0_07; //0xb4
    volatile uint32_t KEYMGR_KEY0_08; //0xb8
    volatile uint32_t KEYMGR_KEY0_09; //0xbc
    volatile uint32_t KEYMGR_KEY0_10; //0xc0
    volatile uint32_t KEYMGR_KEY0_11; //0xc4
    volatile uint32_t KEYMGR_KEY1_00; //0xc8
    volatile uint32_t KEYMGR_KEY1_01; //0xcc
    volatile uint32_t KEYMGR_KEY1_02; //0xd0
    volatile uint32_t KEYMGR_KEY1_03; //0xd4
    volatile uint32_t KEYMGR_KEY1_04; //0xd8
    volatile uint32_t KEYMGR_KEY1_05; //0xdc
    volatile uint32_t KEYMGR_KEY1_06; //0xe0
    volatile uint32_t KEYMGR_KEY1_07; //0xe4
    volatile uint32_t KEYMGR_KEY1_08; //0xe8
    volatile uint32_t KEYMGR_KEY1_09; //0xec
    volatile uint32_t KEYMGR_KEY1_10; //0xf0
    volatile uint32_t KEYMGR_KEY1_11; //0xf4
} reg_sysc_sec_cpu_t;

enum SYSC_SEC_CPU_REG_CPU_SYSC_FIELD {
    SYSC_SEC_CPU_PMU_IWDT_DBG_MASK = (int)0x1,
    SYSC_SEC_CPU_PMU_IWDT_DBG_POS = 0,
    SYSC_SEC_CPU_CACHE1_MEMTST_MASK = (int)0x10,
    SYSC_SEC_CPU_CACHE1_MEMTST_POS = 4,
    SYSC_SEC_CPU_IWDT1_DBG_MASK = (int)0x100,
    SYSC_SEC_CPU_IWDT1_DBG_POS = 8,
    SYSC_SEC_CPU_WWDT1_DBG_MASK = (int)0x1000,
    SYSC_SEC_CPU_WWDT1_DBG_POS = 12,
};

enum SYSC_SEC_CPU_REG_SYS_CLK_FIELD {
    SYSC_SEC_CPU_GATE_SYS_EN_MASK = (int)0x1,
    SYSC_SEC_CPU_GATE_SYS_EN_POS = 0,
    SYSC_SEC_CPU_DBG_EN_MASK = (int)0x1,
    SYSC_SEC_CPU_DBG_EN_POS = 0,
};

enum SYSC_SEC_CPU_REG_APP_CPU_ADDR_CFG_FIELD {
    SYSC_SEC_CPU_APP_CPU_ADDR_CFG_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_APP_CPU_ADDR_CFG_POS = 0,
};

enum SYSC_SEC_CPU_REG_APP_CPU_SRST_FIELD {
    SYSC_SEC_CPU_APP_CPU_SRST_SET_MASK = (int)0x1,
    SYSC_SEC_CPU_APP_CPU_SRST_SET_POS = 0,
    SYSC_SEC_CPU_APP_CPU_SRST_CLR_MASK = (int)0x2,
    SYSC_SEC_CPU_APP_CPU_SRST_CLR_POS = 1,
};

enum SYSC_SEC_CPU_REG_PD_CPU_CLKG0_FIELD {
    SYSC_SEC_CPU_CLKG_SET_CPU_DBG_MASK = (int)0x1,
    SYSC_SEC_CPU_CLKG_SET_CPU_DBG_POS = 0,
    SYSC_SEC_CPU_CLKG_CLR_CPU_DBG_MASK = (int)0x2,
    SYSC_SEC_CPU_CLKG_CLR_CPU_DBG_POS = 1,
    SYSC_SEC_CPU_CLKG_SET_CACHE1_MASK = (int)0x4,
    SYSC_SEC_CPU_CLKG_SET_CACHE1_POS = 2,
    SYSC_SEC_CPU_CLKG_CLR_CACHE1_MASK = (int)0x8,
    SYSC_SEC_CPU_CLKG_CLR_CACHE1_POS = 3,
    SYSC_SEC_CPU_CLKG_SET_IOPMP_MASK = (int)0x10,
    SYSC_SEC_CPU_CLKG_SET_IOPMP_POS = 4,
    SYSC_SEC_CPU_CLKG_CLR_IOPMP_MASK = (int)0x20,
    SYSC_SEC_CPU_CLKG_CLR_IOPMP_POS = 5,
    SYSC_SEC_CPU_CLKG_SET_QSPI1_MASK = (int)0x40,
    SYSC_SEC_CPU_CLKG_SET_QSPI1_POS = 6,
    SYSC_SEC_CPU_CLKG_CLR_QSPI1_MASK = (int)0x80,
    SYSC_SEC_CPU_CLKG_CLR_QSPI1_POS = 7,
    SYSC_SEC_CPU_CLKG_SET_SHA512_MASK = (int)0x100,
    SYSC_SEC_CPU_CLKG_SET_SHA512_POS = 8,
    SYSC_SEC_CPU_CLKG_CLR_SHA512_MASK = (int)0x200,
    SYSC_SEC_CPU_CLKG_CLR_SHA512_POS = 9,
};

enum SYSC_SEC_CPU_REG_PD_CPU_CLKG1_FIELD {
    SYSC_SEC_CPU_CLKG_SET_CALC_CRC_MASK = (int)0x1,
    SYSC_SEC_CPU_CLKG_SET_CALC_CRC_POS = 0,
    SYSC_SEC_CPU_CLKG_CLR_CALC_CRC_MASK = (int)0x2,
    SYSC_SEC_CPU_CLKG_CLR_CALC_CRC_POS = 1,
    SYSC_SEC_CPU_CLKG_SET_CALC_MASK = (int)0x4,
    SYSC_SEC_CPU_CLKG_SET_CALC_POS = 2,
    SYSC_SEC_CPU_CLKG_CLR_CALC_MASK = (int)0x8,
    SYSC_SEC_CPU_CLKG_CLR_CALC_POS = 3,
    SYSC_SEC_CPU_CLKG_SET_CRYPT_MASK = (int)0x10,
    SYSC_SEC_CPU_CLKG_SET_CRYPT_POS = 4,
    SYSC_SEC_CPU_CLKG_CLR_CRYPT_MASK = (int)0x20,
    SYSC_SEC_CPU_CLKG_CLR_CRYPT_POS = 5,
    SYSC_SEC_CPU_CLKG_SET_OTP_CTRL_MASK = (int)0x40,
    SYSC_SEC_CPU_CLKG_SET_OTP_CTRL_POS = 6,
    SYSC_SEC_CPU_CLKG_CLR_OTP_CTRL_MASK = (int)0x80,
    SYSC_SEC_CPU_CLKG_CLR_OTP_CTRL_POS = 7,
    SYSC_SEC_CPU_CLKG_SET_CALC_SHA_MASK = (int)0x100,
    SYSC_SEC_CPU_CLKG_SET_CALC_SHA_POS = 8,
    SYSC_SEC_CPU_CLKG_CLR_CALC_SHA_MASK = (int)0x200,
    SYSC_SEC_CPU_CLKG_CLR_CALC_SHA_POS = 9,
    SYSC_SEC_CPU_CLKG_SET_CALC_SM4_MASK = (int)0x400,
    SYSC_SEC_CPU_CLKG_SET_CALC_SM4_POS = 10,
    SYSC_SEC_CPU_CLKG_CLR_CALC_SM4_MASK = (int)0x800,
    SYSC_SEC_CPU_CLKG_CLR_CALC_SM4_POS = 11,
    SYSC_SEC_CPU_CLKG_SET_OTBN_MASK = (int)0x1000,
    SYSC_SEC_CPU_CLKG_SET_OTBN_POS = 12,
    SYSC_SEC_CPU_CLKG_CLR_OTBN_MASK = (int)0x2000,
    SYSC_SEC_CPU_CLKG_CLR_OTBN_POS = 13,
    SYSC_SEC_CPU_CLKG_SET_NIST_TRNG_MASK = (int)0x40000000,
    SYSC_SEC_CPU_CLKG_SET_NIST_TRNG_POS = 30,
    SYSC_SEC_CPU_CLKG_CLR_NIST_TRNG_MASK = (int)0x80000000,
    SYSC_SEC_CPU_CLKG_CLR_NIST_TRNG_POS = 31,
};

enum SYSC_SEC_CPU_REG_PD_CPU_SRST_FIELD {
    SYSC_SEC_CPU_SRST_SET_CACHE1_MASK = (int)0x4,
    SYSC_SEC_CPU_SRST_SET_CACHE1_POS = 2,
    SYSC_SEC_CPU_SRST_CLR_CACHE1_MASK = (int)0x8,
    SYSC_SEC_CPU_SRST_CLR_CACHE1_POS = 3,
    SYSC_SEC_CPU_SRST_SET_IOPMP_MASK = (int)0x10,
    SYSC_SEC_CPU_SRST_SET_IOPMP_POS = 4,
    SYSC_SEC_CPU_SRST_CLR_IOPMP_MASK = (int)0x20,
    SYSC_SEC_CPU_SRST_CLR_IOPMP_POS = 5,
    SYSC_SEC_CPU_SRST_SET_QSPI1_MASK = (int)0x40,
    SYSC_SEC_CPU_SRST_SET_QSPI1_POS = 6,
    SYSC_SEC_CPU_SRST_CLR_QSPI1_MASK = (int)0x80,
    SYSC_SEC_CPU_SRST_CLR_QSPI1_POS = 7,
    SYSC_SEC_CPU_SRST_SET_SHA512_MASK = (int)0x100,
    SYSC_SEC_CPU_SRST_SET_SHA512_POS = 8,
    SYSC_SEC_CPU_SRST_CLR_SHA512_MASK = (int)0x200,
    SYSC_SEC_CPU_SRST_CLR_SHA512_POS = 9,
};

enum SYSC_SEC_CPU_REG_PD_CPU_SRST1_FIELD {
    SYSC_SEC_CPU_SRST_SET_CALC_CRC_MASK = (int)0x1,
    SYSC_SEC_CPU_SRST_SET_CALC_CRC_POS = 0,
    SYSC_SEC_CPU_SRST_CLR_CALC_CRC_MASK = (int)0x2,
    SYSC_SEC_CPU_SRST_CLR_CALC_CRC_POS = 1,
    SYSC_SEC_CPU_SRST_SET_CALC_MASK = (int)0x4,
    SYSC_SEC_CPU_SRST_SET_CALC_POS = 2,
    SYSC_SEC_CPU_SRST_CLR_CALC_MASK = (int)0x8,
    SYSC_SEC_CPU_SRST_CLR_CALC_POS = 3,
    SYSC_SEC_CPU_SRST_SET_CRYPT_MASK = (int)0x10,
    SYSC_SEC_CPU_SRST_SET_CRYPT_POS = 4,
    SYSC_SEC_CPU_SRST_CLR_CRYPT_MASK = (int)0x20,
    SYSC_SEC_CPU_SRST_CLR_CRYPT_POS = 5,
    SYSC_SEC_CPU_SRST_SET_OTP_CTRL_MASK = (int)0x40,
    SYSC_SEC_CPU_SRST_SET_OTP_CTRL_POS = 6,
    SYSC_SEC_CPU_SRST_CLR_OTP_CTRL_MASK = (int)0x80,
    SYSC_SEC_CPU_SRST_CLR_OTP_CTRL_POS = 7,
    SYSC_SEC_CPU_SRST_SET_CALC_SHA_MASK = (int)0x100,
    SYSC_SEC_CPU_SRST_SET_CALC_SHA_POS = 8,
    SYSC_SEC_CPU_SRST_CLR_CALC_SHA_MASK = (int)0x200,
    SYSC_SEC_CPU_SRST_CLR_CALC_SHA_POS = 9,
    SYSC_SEC_CPU_SRST_SET_CALC_SM4_MASK = (int)0x400,
    SYSC_SEC_CPU_SRST_SET_CALC_SM4_POS = 10,
    SYSC_SEC_CPU_SRST_CLR_CALC_SM4_MASK = (int)0x800,
    SYSC_SEC_CPU_SRST_CLR_CALC_SM4_POS = 11,
    SYSC_SEC_CPU_SRST_SET_OTBN_MASK = (int)0x1000,
    SYSC_SEC_CPU_SRST_SET_OTBN_POS = 12,
    SYSC_SEC_CPU_SRST_CLR_OTBN_MASK = (int)0x2000,
    SYSC_SEC_CPU_SRST_CLR_OTBN_POS = 13,
    SYSC_SEC_CPU_SRST_SET_NIST_TRNG_MASK = (int)0x40000000,
    SYSC_SEC_CPU_SRST_SET_NIST_TRNG_POS = 30,
    SYSC_SEC_CPU_SRST_CLR_NIST_TRNG_MASK = (int)0x80000000,
    SYSC_SEC_CPU_SRST_CLR_NIST_TRNG_POS = 31,
};

enum SYSC_SEC_CPU_REG_SEC_CPU_INTR_FIELD {
    SYSC_SEC_CPU_SEC_CPU_INTR_MASK = (int)0x1,
    SYSC_SEC_CPU_SEC_CPU_INTR_POS = 0,
};

enum SYSC_SEC_CPU_REG_SEC_CPU_IMSK_FIELD {
    SYSC_SEC_CPU_SEC_CPU_IMSK_MASK = (int)0x1,
    SYSC_SEC_CPU_SEC_CPU_IMSK_POS = 0,
};

enum SYSC_SEC_CPU_REG_NIST_TRNG_CTRL_FIELD {
    SYSC_SEC_CPU_NIST_TRNG_TEST_MODE_MASK = (int)0x3,
    SYSC_SEC_CPU_NIST_TRNG_TEST_MODE_POS = 0,
    SYSC_SEC_CPU_NIST_TRNG_TEST_TWEAK_MUX_MASK = (int)0xc,
    SYSC_SEC_CPU_NIST_TRNG_TEST_TWEAK_MUX_POS = 2,
    SYSC_SEC_CPU_NIST_TRNG_CTL_ZEROIZE_MASK = (int)0x10,
    SYSC_SEC_CPU_NIST_TRNG_CTL_ZEROIZE_POS = 4,
    SYSC_SEC_CPU_NIST_TRNG_CTL_ALARM_MASK = (int)0x20,
    SYSC_SEC_CPU_NIST_TRNG_CTL_ALARM_POS = 5,
    SYSC_SEC_CPU_NIST_TRNG_CTL_NONCE_MODE_MASK = (int)0x40,
    SYSC_SEC_CPU_NIST_TRNG_CTL_NONCE_MODE_POS = 6,
    SYSC_SEC_CPU_NIST_TRNG_CTLURE_MODE_MASK = (int)0x80,
    SYSC_SEC_CPU_NIST_TRNG_CTLURE_MODE_POS = 7,
    SYSC_SEC_CPU_NIST_TRNG_TEST_TP_MASK = (int)0x7ffff00,
    SYSC_SEC_CPU_NIST_TRNG_TEST_TP_POS = 8,
};

enum SYSC_SEC_CPU_REG_INTR_CTRL_INTR_MSK_FIELD {
    SYSC_SEC_CPU_OTBN_INTR_MSK_MASK = (int)0x7ff,
    SYSC_SEC_CPU_OTBN_INTR_MSK_POS = 0,
};

enum SYSC_SEC_CPU_REG_INTR_CLR_MSK_FIELD {
    SYSC_SEC_CPU_OTBN_INTR_CLR_MASK = (int)0x7ff,
    SYSC_SEC_CPU_OTBN_INTR_CLR_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_INTR_STT_FIELD {
    SYSC_SEC_CPU_OTBN_INTR_STT_MASK = (int)0x7ff,
    SYSC_SEC_CPU_OTBN_INTR_STT_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_INTR_RAW_FIELD {
    SYSC_SEC_CPU_OTBN_INTR_RAW_MASK = (int)0x7ff,
    SYSC_SEC_CPU_OTBN_INTR_RAW_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_STT_FIELD {
    SYSC_SEC_CPU_I_ALERT_TX0_ALERT_P_MASK = (int)0x1,
    SYSC_SEC_CPU_I_ALERT_TX0_ALERT_P_POS = 0,
    SYSC_SEC_CPU_I_ALERT_TX0_ALERT_N_MASK = (int)0x2,
    SYSC_SEC_CPU_I_ALERT_TX0_ALERT_N_POS = 1,
    SYSC_SEC_CPU_I_ALERT_TX1_ALERT_P_MASK = (int)0x4,
    SYSC_SEC_CPU_I_ALERT_TX1_ALERT_P_POS = 2,
    SYSC_SEC_CPU_I_ALERT_TX1_ALERT_N_MASK = (int)0x8,
    SYSC_SEC_CPU_I_ALERT_TX1_ALERT_N_POS = 3,
    SYSC_SEC_CPU_I_LC_RMA_ACK_MASK = (int)0xf0,
    SYSC_SEC_CPU_I_LC_RMA_ACK_POS = 4,
    SYSC_SEC_CPU_I_EDN_RND_REQ_MASK = (int)0x100,
    SYSC_SEC_CPU_I_EDN_RND_REQ_POS = 8,
    SYSC_SEC_CPU_I_EDN_URND_REQ_MASK = (int)0x200,
    SYSC_SEC_CPU_I_EDN_URND_REQ_POS = 9,
    SYSC_SEC_CPU_I_OTBN_OTP_REQ_MASK = (int)0x400,
    SYSC_SEC_CPU_I_OTBN_OTP_REQ_POS = 10,
    SYSC_SEC_CPU_I_OTBN_IDLE_MASK = (int)0x7800,
    SYSC_SEC_CPU_I_OTBN_IDLE_POS = 11,
};

enum SYSC_SEC_CPU_REG_OTBN_CTRL2_FIELD {
    SYSC_SEC_CPU_OTBN_ALERT_RX0_PING_P_MASK = (int)0x1,
    SYSC_SEC_CPU_OTBN_ALERT_RX0_PING_P_POS = 0,
    SYSC_SEC_CPU_OTBN_ALERT_RX0_PING_N_MASK = (int)0x2,
    SYSC_SEC_CPU_OTBN_ALERT_RX0_PING_N_POS = 1,
    SYSC_SEC_CPU_OTBN_ALERT_RX0_ACK_P_MASK = (int)0x4,
    SYSC_SEC_CPU_OTBN_ALERT_RX0_ACK_P_POS = 2,
    SYSC_SEC_CPU_OTBN_ALERT_RX0_ACK_N_MASK = (int)0x8,
    SYSC_SEC_CPU_OTBN_ALERT_RX0_ACK_N_POS = 3,
    SYSC_SEC_CPU_OTBN_ALERT_RX1_PING_P_MASK = (int)0x10,
    SYSC_SEC_CPU_OTBN_ALERT_RX1_PING_P_POS = 4,
    SYSC_SEC_CPU_OTBN_ALERT_RX1_PING_N_MASK = (int)0x20,
    SYSC_SEC_CPU_OTBN_ALERT_RX1_PING_N_POS = 5,
    SYSC_SEC_CPU_OTBN_ALERT_RX1_ACK_P_MASK = (int)0x40,
    SYSC_SEC_CPU_OTBN_ALERT_RX1_ACK_P_POS = 6,
    SYSC_SEC_CPU_OTBN_ALERT_RX1_ACK_N_MASK = (int)0x80,
    SYSC_SEC_CPU_OTBN_ALERT_RX1_ACK_N_POS = 7,
    SYSC_SEC_CPU_EDN_RND_ACK_MASK = (int)0x100,
    SYSC_SEC_CPU_EDN_RND_ACK_POS = 8,
    SYSC_SEC_CPU_EDN_RND_FIPS_MASK = (int)0x200,
    SYSC_SEC_CPU_EDN_RND_FIPS_POS = 9,
    SYSC_SEC_CPU_EDN_URND_ACK_MASK = (int)0x400,
    SYSC_SEC_CPU_EDN_URND_ACK_POS = 10,
    SYSC_SEC_CPU_EDN_URND_FIPS_MASK = (int)0x800,
    SYSC_SEC_CPU_EDN_URND_FIPS_POS = 11,
    SYSC_SEC_CPU_OTBN_TOP_ACK_MASK = (int)0x1000,
    SYSC_SEC_CPU_OTBN_TOP_ACK_POS = 12,
    SYSC_SEC_CPU_OTBN_TOP_SEED_VAILD_MASK = (int)0x2000,
    SYSC_SEC_CPU_OTBN_TOP_SEED_VAILD_POS = 13,
    SYSC_SEC_CPU_KEYMGR_VALID_MASK = (int)0x4000,
    SYSC_SEC_CPU_KEYMGR_VALID_POS = 14,
    SYSC_SEC_CPU_LC_ESCALATE_EN_MASK = (int)0xf0000,
    SYSC_SEC_CPU_LC_ESCALATE_EN_POS = 16,
    SYSC_SEC_CPU_LC_RMA_REQ_MASK = (int)0xf00000,
    SYSC_SEC_CPU_LC_RMA_REQ_POS = 20,
};

enum SYSC_SEC_CPU_REG_EDN_RND_BUS_FIELD {
    SYSC_SEC_CPU_EDN_RND_BUS_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_EDN_RND_BUS_POS = 0,
};

enum SYSC_SEC_CPU_REG_EDN_URND_BUS_FIELD {
    SYSC_SEC_CPU_EDN_URND_BUS_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_EDN_URND_BUS_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_OTP_NONCE_0_FIELD {
    SYSC_SEC_CPU_OTBN_OTP_NONCE_0_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_OTBN_OTP_NONCE_0_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_OTP_NONCE_1_FIELD {
    SYSC_SEC_CPU_OTBN_OTP_NONCE_1_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_OTBN_OTP_NONCE_1_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_OTP_KEY_0_FIELD {
    SYSC_SEC_CPU_OTBN_OTP_KEY_0_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_OTBN_OTP_KEY_0_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_OTP_KEY_1_FIELD {
    SYSC_SEC_CPU_OTBN_OTP_KEY_1_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_OTBN_OTP_KEY_1_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_OTP_KEY_2_FIELD {
    SYSC_SEC_CPU_OTBN_OTP_KEY_2_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_OTBN_OTP_KEY_2_POS = 0,
};

enum SYSC_SEC_CPU_REG_OTBN_OTP_KEY_3_FIELD {
    SYSC_SEC_CPU_OTBN_OTP_KEY_3_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_OTBN_OTP_KEY_3_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_00_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_00_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_00_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_01_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_01_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_01_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_02_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_02_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_02_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_03_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_03_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_03_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_04_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_04_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_04_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_05_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_05_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_05_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_06_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_06_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_06_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_07_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_07_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_07_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_08_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_08_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_08_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_09_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_09_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_09_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_10_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_10_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_10_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY0_11_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY0_11_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY0_11_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_00_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_00_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_00_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_01_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_01_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_01_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_02_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_02_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_02_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_03_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_03_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_03_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_04_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_04_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_04_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_05_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_05_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_05_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_06_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_06_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_06_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_07_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_07_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_07_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_08_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_08_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_08_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_09_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_09_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_09_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_10_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_10_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_10_POS = 0,
};

enum SYSC_SEC_CPU_REG_KEYMGR_KEY1_11_FIELD {
    SYSC_SEC_CPU_KEYMGR_KEY1_11_MASK = (int)0xffffffff,
    SYSC_SEC_CPU_KEYMGR_KEY1_11_POS = 0,
};

#endif
