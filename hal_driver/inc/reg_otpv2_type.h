#ifndef __REG_OTPV2_TYPE_H__
#define __REG_OTPV2_TYPE_H__
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    volatile uint32_t PIF_TEST_MODE_FLAGS; //0X0
    volatile uint32_t PIF_OP_SETTING; //0X4
    volatile uint32_t PIF_OP_HEALTHCFG; //0x8
    volatile uint32_t RESERVED0; //0xc
    volatile uint32_t PIF_CDE_LCKWD[4]; //0x10 - 0x1c
    volatile uint32_t PIF_SECRP_PROT_EN; //0x20
    volatile uint32_t PIF_CDE_SECRP; //0x24
    volatile uint32_t RESERVED1[13]; //0x28 - 0x58
    volatile uint16_t PIF_CDE_LV2LCK; //0x5c
    volatile uint16_t RESERVED2;
    volatile uint32_t RESERVED3[72]; //0x60 - 0x17c
    volatile uint32_t CFG_VERSION; //0x180
    volatile uint32_t RESERVED4[3]; //0x184 - 0x18c
    volatile uint32_t CFG_INTRPT_STT_EN; //0x190
    volatile uint32_t RESERVED5[3]; //0x194 - 0x19c
    volatile uint32_t CFG_0x20; //0x1a0
    volatile uint32_t CFG_PDSTB; //0x1a4
    volatile uint32_t CFG_0x28; //0x1a8
    volatile uint32_t CFG_CONFIG2; //0x1ac
    volatile uint32_t RESERVED6[12]; //0x1b0 - 0x1dc
    volatile uint32_t CFG_CDE_PSMSK_0; //0x1e0
    volatile uint32_t CFG_CDE_PSMSK_1; //0x1e4
    volatile uint32_t RESERVED7[4]; //0x1e8 - 0x1f4
    volatile uint32_t CFG_SEC_RANGE; //0x1F8
    volatile uint32_t CFG_LOCK_WRITE_ACCESS; //0x1FC
    volatile uint32_t PTR_PTR[16]; //0x200 - 0x23c
    volatile uint32_t PTC_PTC[16]; //0x240 - 0x27c
    volatile uint32_t PTM_STATUS_REG; //0x280
    volatile uint32_t PTM_RD_MODE; //0x284
    volatile uint32_t PTM_PTC_PAGE; //0x288
    volatile uint32_t PTM_REG_HEALTHCFG; //0x28C
    volatile uint32_t PTM_SET_PIN; //0x290
    volatile uint32_t PTM_SET_FLAG; //0x294
    volatile uint32_t RESERVED8[2]; //0x298
    volatile uint32_t PTM_PUF_CHK; //0x2A0
    volatile uint32_t PTM_PUF_ENROLL; //0x2A4
    volatile uint32_t RESERVED9; //0x2A8
    volatile uint32_t PTM_PUF_CRC; //0x2AC
    volatile uint32_t PTM_OFF_CHK; //0x2B0
    volatile uint32_t PTM_AUTO_REPAIR; //0x2B4
    volatile uint32_t RESERVED10[3]; //0x2B8
    volatile uint32_t PTM_REPAIR_REG; //0x2C4
}reg_axi_otp_t;

enum OTPV2_REG_CFG_0x20_FIELD
{
    OTPV2_CFG_PIN_PDSTB_MASK = (int)0x4,
    OTPV2_CFG_PIN_PDSTB_POS = 2,
    OTPV2_CFG_INIT_MASK = (int)0x2,
    OTPV2_CFG_INIT_POS = 1,
    OTPV2_CFG_BUSY_MASK = (int)0x1,
    OTPV2_CFG_BUSY_POS = 0,
};

#ifdef __cplusplus
}
#endif

#endif /* __REG_OTPV2_TYPE_H__ */