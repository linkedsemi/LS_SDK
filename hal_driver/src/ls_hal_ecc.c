#include <stdbool.h>
#include <string.h>
#include "ls_hal_ecc.h"
#include "ls_msp_ecc.h"
#include "common.h"
#include "field_manipulate.h"
static const struct ecc_curve_param *ecc_curve;
static uint32_t ecc_private_key[8];
static uint32_t ecc_public_key[2][8];
static uint8_t *ecc_result[2];

enum ECC_ComMod
{
    ECC_ZACAU,
    ECC_DBLU,
    ECC_ZADDC,
    ECC_ZADDU,
};

enum ECC_Mode
{
    Mode_H,
    Mode_ModMul,
    Mode_ModAddi,
    Mode_ModSub,
    Mode_ModInver,
    Mode_MontOut,
    Mode_MontIn,
};

enum ECC_FSM
{
    FSM_INPUT,
    FSM_DBLU,
    FSM_ZACAU,
    FSM_ZADDC,
    FSM_INVERSE,
    FSM_ZADDU,
    FSM_OUTPUT,
    FSM_DONE,
};

static enum ECC_FSM ecc_fsm;
static uint8_t fsm_step;

const struct ecc_curve_param secp256r1_param = {
    .p =        {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x00000000,0x00000000,0x00000000,0x00000001,0xFFFFFFFF},
    .neg_a =    {0x00000003,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
    .h =        {0X00000003,0X00000000,0Xffffffff,0Xfffffffb,0Xfffffffe,0Xffffffff,0Xfffffffd,0X00000004},
    .omega =    0x1,
};

const struct ecc_curve_param secp256k1_param = {
    .p =        {0xFFFFFC2F,0xFFFFFFFE,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
    .neg_a =    {0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
    .h =        {0X000E90A1,0X000007A2,0X00000001,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000},
    .omega =    0xd2253531,
};

const struct ecc_curve_param sm2_param = {
    .p =        {0xFFFFFFFF,0xFFFFFFFF,0x00000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFE},
    .neg_a =    {0x00000003,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
    .h =        {0X00000003,0X00000002,0Xffffffff,0X00000002,0X00000001,0X00000001,0X00000002,0X00000004},
    .omega =    0x1,
};

void HAL_LSECC_Init(void)
{
    HAL_LSECC_MSP_Init();
    HAL_LSECC_Busy_Set();
}

void HAL_LSECC_DeInit(void)
{
    HAL_LSECC_MSP_DeInit();
    HAL_LSECC_Idle_Set();
}

static void calc_done_wait()
{
    while((LSECC->STAT&ECC_DONE_MASK)==0);
}

/*
void h_calc(const uint32_t *p,uint32_t *result_h)
{
    memcpy32((uint32_t *)LSECC->NRAM,p,8);
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_MODE,Mode_H);
    calc_done_wait();
    memcpy32(result_h,(uint32_t *)&LSECC->ARAM[56],8);
}

uint32_t omega_calc(const uint32_t *p)
{
    uint32_t val = 1;
    uint8_t i;
    for(i=0;i<31;++i)
    {
        val = val * val * p[0];
    }
    return val;
}

*/


static void mont_in(uint8_t dst)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPR,dst)|FIELD_BUILD(ECC_RES,dst)|FIELD_BUILD(ECC_MODE,Mode_MontIn);
}

static void mont_in_data(const uint32_t *data,uint8_t dst)
{
    memcpy32((uint32_t *)&LSECC->ARAM[dst*8],data,8);
    mont_in(dst);
}

static void p_in()
{
    memcpy32((uint32_t *)LSECC->NRAM,ecc_curve->p,8);
}

static void h_in()
{
    memcpy32((uint32_t *)&LSECC->ARAM[56],ecc_curve->h,8);
}

static bool orig2mont()
{
    switch(fsm_step)
    {
    case 0:
        h_in();
        mont_in_data(ecc_public_key[0],0);
    break;
    case 1:
        mont_in_data(ecc_public_key[0],1);
    break;
    case 2:
        mont_in_data(ecc_public_key[1],2);
    break;
    case 3:
        mont_in_data(ecc_curve->neg_a,6);
    break;
    }
    fsm_step += 1;
    return fsm_step == 4;
}

static void dblu()
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_COMB,1)|FIELD_BUILD(ECC_COMMOD,ECC_DBLU);
}

static void zacau_calc(bool remap)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_COMB,1)|FIELD_BUILD(ECC_REMAP,remap?1:0)|FIELD_BUILD(ECC_COMMOD,ECC_ZACAU);
}

static bool zacau_loop()
{
    if(fsm_step == 0)
    {
        fsm_step = 255;
        while((ecc_private_key[fsm_step/32]&1<<fsm_step%32)==0)
        {
            fsm_step -= 1;
        }
        fsm_step -= 1;
    }
    zacau_calc(ecc_private_key[fsm_step/32]&1<<fsm_step%32);
    fsm_step -= 1;
    return fsm_step == 0;
}

static void zaddc_calc(bool remap)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_COMB,1)|FIELD_BUILD(ECC_REMAP,remap?1:0)|FIELD_BUILD(ECC_COMMOD,ECC_ZADDC);
}

static void mont_out(uint8_t src)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPR,src)|FIELD_BUILD(ECC_RES,src)|FIELD_BUILD(ECC_MODE,Mode_MontOut);
}

static void inversion_calc()
{
    uint8_t i;
    memcpy32((uint32_t *)&LSECC->ARAM[0],ecc_curve->p,8);
    for(i=0;i<8;++i)
    {
        LSECC->ARAM[48+i] = 0;
        LSECC->ARAM[56+i] = 0;
    }
    LSECC->ARAM[48] = 1;
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_RES,3)|FIELD_BUILD(ECC_MODE,Mode_ModInver);
}

static bool inversion()
{
    switch(fsm_step)
    {
    case 0:
        mont_out(3);
    break;
    case 1:
        inversion_calc();
    break;
    case 2:
        h_in();
        mont_in(3);
    break;
    }
    fsm_step += 1;
    return fsm_step == 3;
}

static void zaddu_calc(bool remap)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_COMB,1)|FIELD_BUILD(ECC_REMAP,remap?1:0)|FIELD_BUILD(ECC_COMMOD,ECC_ZADDU);
}

static bool zaddu()
{
    switch(fsm_step)
    {
    case 0:
        mont_in_data(ecc_public_key[1],0);
    break;
    case 1:
        zaddu_calc(ecc_private_key[0]&0x1);
    break;
    }
    fsm_step += 1;
    return fsm_step == 2;
}

static bool mont2rslt()
{
    switch(fsm_step)
    {
    case 0:
        mont_out(1);
    break;
    case 1:
        mont_out(2);
    break;
    }
    fsm_step += 1;
    return fsm_step == 2;
}


static void calc_fsm_run()
{
    bool fsm_next = true;
    switch(ecc_fsm)
    {
    case FSM_INPUT:
        fsm_next = orig2mont();
    break;
    case FSM_DBLU:
        dblu();
    break;
    case FSM_ZACAU:
        fsm_next = zacau_loop();
    break;
    case FSM_ZADDC:
        zaddc_calc(ecc_private_key[0]&0x1);
    break;
    case FSM_INVERSE:
        fsm_next = inversion();
    break;
    case FSM_ZADDU:
        fsm_next = zaddu();
    break;
    case FSM_OUTPUT:
        fsm_next = mont2rslt();
    break;
    case FSM_DONE:
        while(1);
    }
    if(fsm_next)
    {
        ecc_fsm += 1;
        fsm_step = 0;
    }
}


static void calc_init(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *public_key[2],uint8_t *result[2])
{
    ecc_curve = curve;
    memcpy((uint8_t *)ecc_private_key,private_key,32);
    memcpy((uint8_t *)ecc_public_key[0],public_key[0],32);
    memcpy((uint8_t *)ecc_public_key[1],public_key[1],32);
    ecc_result[0] = result[0];
    ecc_result[1] = result[1];
    p_in();
    LSECC->OMEGA = ecc_curve->omega;
    ecc_fsm = FSM_INPUT;
    fsm_step = 0;
}

static void copy_from_eccram(uint32_t *src,uint8_t *dst)
{
    uint32_t buf[8];
    memcpy32(buf,src,8);
    memcpy(dst,(uint8_t *)buf,32);
}

static void result2buffer()
{
    copy_from_eccram((uint32_t *)&LSECC->ARAM[8],ecc_result[0]);
    copy_from_eccram((uint32_t *)&LSECC->ARAM[16],ecc_result[1]);
}

void HAL_LSECC_PointMult(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *public_key[2],uint8_t *result[2])
{
    calc_init(curve,private_key,public_key,result);
    while(ecc_fsm != FSM_DONE)
    {
        calc_fsm_run();
        calc_done_wait();
    }
    result2buffer();
}

void HAL_LSECC_PointMult_IT(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *public_key[2],uint8_t *result[2])
{
    HAL_LSECC_MSP_INT_CLRPENDING();
    calc_init(curve,private_key,public_key,result);
    calc_fsm_run();
    HAL_LSECC_MSP_INT_ENABLE();
}

__attribute__((weak)) void HAL_LSECC_PointMult_Complete_Callback(void){}

void LSECC_IRQHandler(void)
{
    HAL_LSECC_MSP_INT_DISABLE();
    LSECC->CON = FIELD_BUILD(ECC_RST,1);
    if(ecc_fsm == FSM_DONE)
    {
        result2buffer();
        HAL_LSECC_PointMult_Complete_Callback();
    }else
    {
        calc_fsm_run();
        HAL_LSECC_MSP_INT_ENABLE();
    }
}
