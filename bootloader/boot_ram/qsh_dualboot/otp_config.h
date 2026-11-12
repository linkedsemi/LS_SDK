#ifndef _OTP_CONFIG_H_
#define _OTP_CONFIG_H_
#include "boot_port.h"

enum OTP_KEYHeader_Type
{
    OTP_KEYHeader_Type_NONE             = 0x0,//0000
    OTP_KEYHeader_Type_AES256           = 0x1,//0001
    OTP_KEYHeader_Type_SM4              = 0x2,//0010
    OTP_KEYHeader_Type_ECC_ECSDA_PriKey = 0x4,//0100
    OTP_KEYHeader_Type_ECC_ECSDA_PubKey = 0x5,//0101
    OTP_KEYHeader_Type_ECC_SM2_PriKey   = 0x6,//0110
    OTP_KEYHeader_Type_ECC_SM2_PubKey   = 0x7,//0111
    OTP_KEYHeader_Type_HKDF_IKM         = 0x8,//1000
};

typedef struct
{
    uint16_t
        type : 4,
        length : 4,
        offset : 8;
} keyHeader_t;

struct lvds_cfg
{
    uint32_t 
        tx_pll_kvco : 2,
        tx_pll_ichp : 2,
        tx_pll_lpf_rs : 3,
        tx_ssc_gain : 3,
        tx_fb_N_int : 6,
        tx_ssc_freq : 16;
    uint32_t 
        tx_step_b : 24,
        tx_step_d0 : 8;
    uint32_t
        tx_step_d1 : 8,
        tx_step_f : 24;
    uint32_t
        tx_pll_pre_div : 8,
        rx_pll_kvco : 2,
        rx_pll_ichp : 2,
        rx_pll_lpf_rs : 3, : 1,
        rx_fb_N_int : 6, : 2,
        rx_pll_pre_div : 8;
};

struct lvds_common
{
    //---------------------------LVDS_TX---------------------------//
    uint32_t
        tx_pll_lock_ref_thd : 16,
        tx_pll_lock_ref_err_thd0 : 8,
        tx_pll_lock_ref_err_thd1 : 2,
        tx_pll_fb_delay : 2,
        tx_pll_ref_delay : 2,
        tx_pfd_dly : 2;
    uint32_t
        tx_pll_aofs_div : 6,
        tx_pll_aofs_mode : 2,
        tx_pll_cp_adj : 4,
        tx_ntrim : 3, : 1,
        //---------------------------LVDS_RX---------------------------//
        rx_pll_lock_ref_thd : 16;
    uint32_t
        rx_pll_lock_ref_err_thd : 10,
        rx_pfd_dly : 2,
        rx_pll_fb_delay : 2,
        rx_pll_ref_delay : 2,
        rx_pll_aofs_div : 6,
        rx_pll_aofs_mode : 2,
        rx_pll_cp_adj : 4,
        rx_v09_vsel : 2, : 2;
    uint32_t 
        ltpi_reg_rxrst_dly_val : 16,
        rx_cal_phy0 : 5,
        rx_itrim_phy0 : 2, : 1,
        rx_cal_phy1 : 5,
        rx_itrim_phy1 : 2, : 1;
};


struct _produce_info
{
    uint32_t LotID;
    uint32_t
        waferid_x_y : 20,
        : 6,
        cp_program_version : 4,
        cp_pass_flag : 1,
        otp_pass_flag : 1;
    uint32_t
        lpldo_trim : 4,         // 3:0
        hpldo_trim : 4,         // 7:4
        bg_vref_trim : 6,       // 13:8
        bg_vref_fine : 2,       // 15:14
        bg_ibg_trim : 4,        // 19:16
        adc12b_g_cal_adc0 : 12; // 31:20
    uint32_t
        spi_code : 12,             // 11:0
        lvds_tx_pll_vtrim0 : 2,    // 13:12
        lvds_tx_pll_vtrim1 : 1,    // 14:14
        : 1,
        ldo_peci_vsel : 4,         // 19:16
        adc12b_os_cal_adc0 : 8,    // 27:20
        msi_cal : 4;               // 31:28
    uint32_t
        oscrc_cal : 10,         // 9:0
        oscrc_cap : 2,          // 11:10
        adc12b_g_cal_adc1 : 12, // 23:12
        adc12b_os_cal_adc1 : 8; // 31:24
    uint32_t
        adc12b_vref_trim_adc0 : 5,       // 4:0
        clkldo1 : 3,                     // 7:5
        clkldo2 : 3,                     // 10:8
        lvds_tx_vtrim : 5,               // 15:11
        adc12b_vref_trim_adc1 : 5,       // 20:16
        lvds_rx_pll_vtrim : 3,           // 23:21
        lvds_rx_itrim : 2,               // 25:24
        : 6;
    struct lvds_cfg lvds_30M;
    struct lvds_cfg lvds_50M;
    struct lvds_cfg lvds_100M;
    struct lvds_common lvds_common;
    uint32_t ltpi_reg_phy_cfg;
    uint16_t dpll1_ctrl2;
    uint16_t dpll2_ctrl2;
};
_Static_assert(sizeof(struct _produce_info) == 0x60, "struct _produce_info size error.");

struct _startup_param
{
    uint32_t dpll1_ctrl1;
    uint32_t dpll2_ctrl1;
    uint32_t feature_mask;
    uint32_t qspi_dac_ctrl;
    uint32_t qspi_ctrl_0;
    uint32_t qspi_ctrl_1;
    uint32_t clk_ctrl_0[2];
    uint32_t clk_ctrl_1;
    uint32_t 
        uart_baud_reg : 16,
        wdg_timeout_s : 5, /* unit : s */
        xtal_stable_time : 11;/* unit : 10us */
    uint32_t
        bkp_disable : 1,
        boot_fail_uart_en : 1,
        boot_fail_retry_disable: 1,
        secure_disable : 1,
        ali_mode_disable : 1,
        flash_reset_disable : 1,
        log_uart_en : 1,
        boot_uart_en : 1,
        xtal_25m_disable : 1,
        xip_dual : 1,
        xip_continu_mode_disable : 1,
        gm_en : 1,
        runtime_cfg_invaild : 1,
        selftest_disable : 1,
        ali_hash_algo_select : 8,
        bkp_flash_offset : 10; /* unit : 16k */
};
_Static_assert(sizeof(struct _startup_param) == 0x2C, "struct _startup_param size error.");

struct boot_otp
{
    // read only
    struct _produce_info produce_info;
    
    // read only
    struct _startup_param startup_param; //0x60
    uint8_t life_cycle_status;
    uint8_t otp_code_seg_idx;
    uint16_t otp_code_length;
    uint8_t reversed[0x10];
    uint32_t otp_read_en[0x4]; //0xA0
    uint32_t otp_write_en[0x4];

    // no write, no read
    uint32_t rma_token[0x4]; //0xC0
    uint32_t debug_lock_token[0x2];
    uint32_t otp_code_crc;
    uint32_t uds_seed_crc;
    uint8_t uds_seed[0x20];//0xe0
    
    // write, read
    uint32_t secure_version;//0x100
    uint32_t ali_sub_key_version;
    uint8_t reversed_1[0x18];

    // read only
    uint8_t ali_pubkey_sm3[0x20]; //0x120
    uint8_t ali_pubkey_sha384[0x30]; //0x140
    uint8_t uuid[0x10]; //0x170

    // readonly
    keyHeader_t key_header[0x10]; //0x180
};
_Static_assert(offsetof(struct boot_otp, otp_read_en)%0x20 == 0, "otp_read_en unaligned.");
_Static_assert(offsetof(struct boot_otp, uds_seed)%0x20 == 0, "uds_seed unaligned.");

#define OTP_OFFSET_LIFE_CYCLE_STATUS        (offsetof(struct boot_otp, life_cycle_status))
#define OTP_OFFSET_SECURE_VERSION           (offsetof(struct boot_otp, secure_version))
#define ALIOTP_OFFSET_SUB_KEY_VERSION       (offsetof(struct boot_otp, ali_sub_key_version))
#define OTP_FRA_ERASE_OFFSET_BIT            (offsetof(struct boot_otp, otp_read_en) / 4)
#define OTP_FRA_ERASE_BITMAX                (0x400)
#define OTP_OFFSET_KEY_START                (sizeof(struct boot_otp))
#define OTP_STARTUP_PARAM_SIZE              (sizeof(struct _startup_param))
#define PRODUCE_TRIM_INFO_BYTE_SIZE         (sizeof(struct _produce_info))

#endif