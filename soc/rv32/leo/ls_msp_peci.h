#ifndef __LS_MSP_PECI_H
#define __LS_MSP_PECI_H

#define PECI_LS_MAX_TX_BUF_LEN 24
#define PECI_LS_MAX_RX_BUF_LEN 24

#define PECI_PRE_DIV_VAL      5

#define PECI_DAT_LEN_VAL      6

#define PECI_A_BIT_CYC_VAL    11
#define PECI_A_TGT_IDX0_VAL   3
#define PECI_M_TGT_IDX0_VAL   3
#define PECI_A_SMP_IDX_VAL    9
#define PECI_A_TGT_IDX1_VAL   8
#define PECI_M_TGT_IDX1_VAL   8

/* PECI Voltage */
enum peci_ldo_voltage
{
    PECI_LDO_VOLT_1100,
    PECI_LDO_VOLT_1150,
    PECI_LDO_VOLT_1200,
    PECI_LDO_VOLT_1250,
    PECI_LDO_VOLT_900,
    PECI_LDO_VOLT_950,
    PECI_LDO_VOLT_1000,
    PECI_LDO_VOLT_1050,
};

#endif