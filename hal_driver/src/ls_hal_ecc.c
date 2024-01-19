#include <stdbool.h>
#include <string.h>
#include "ls_hal_ecc.h"
#include "ls_msp_ecc.h"
#include "common.h"
#include "field_manipulate.h"
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
    Mode_MontMul,
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

enum ECC_Add_FSM
{
    ADD_XP_XQ_MOD_SUB, // xp-xq
    ADD_XP_XQ_MOD_INV, // 1/(xp-xq)
    ADD_YP_YQ_MOD_SUB, // yp-yq
    ADD_XP_XQ_INV_MONT_IN,
    ADD_YP_YQ_MONT_IN,
    ADD_M_MONT_MULT, // m = (yp-yq)/(xp-xq)
    ADD_M_M_MONT_MULT, // m*m
    ADD_M_M_MONT_OUT,
    ADD_XP_XQ_MOD_ADD, // xq+xq
    ADD_MM_XP_XP_MOD_SUB, // res.x = m*m - xp - xq
    ADD_XQ_X_MOD_SUB, // xq - res.x
    ADD_XQ_X_MONT_IN,
    ADD_M_XQ_X_MONT_MULT, // (xq - res.x)*m
    ADD_M_XQ_X_MONT_OUT,
    ADD_M_XQ_X_YQ_MOD_SUB, // res.y = (xq - res.x)*m - yq
    ADD_DONE,
};

enum ECC_Sign_FSM
{
    SIGN_POINT_MULT,
    SIGN_K_MOD_INV,
    SIGN_K_INV_MONT_IN,
    SIGN_DA_MONT_IN,
    SIGN_R_MONT_IN,
    SIGN_Z_MONT_IN,
    SIGN_R_DA_MONT_MULT,
    SIGN_Z_RDA_MOD_ADD,
    SIGN_FINAL_MONT_MULT,
    SIGN_S_MONT_OUT,
    SIGN_DONE,
};

enum ECC_Verify_FSM
{
    VERIFY_S_MOD_INV,
    VERIFY_S_INV_MONT_IN,
    VERIFY_Z_MONT_IN,
    VERIFY_MONT_MULT_U1,
    VERIFY_U1_MOUT_OUT,
    VERIFY_R_MONT_IN,
    VERIFY_MONT_MULT_U2,
    VERIFY_U2_MONT_OUT,
    VERIFY_POINT_MULT_U1G,
    VERIFY_POINT_MULT_U2H,
    VERIFY_POINT_ADD_U1G_U2H,
    VERIFY_SUM_MOD_N,
    VERIFY_DONE,
};

static void (*ecc_int_handler)();
static const struct ecc_curve_param *ecc_curve;
static const uint8_t *ecc_scalar;
static const uint8_t *ecc_point_a[2];
static const uint8_t *ecc_point_b[2];
static uint8_t *ecc_result[2];
static enum ECC_FSM ecc_fsm;
static uint8_t fsm_step;
static enum ECC_Add_FSM ecc_add_fsm;
static enum ECC_Sign_FSM ecc_sign_fsm;
static enum ECC_Verify_FSM ecc_verify_fsm;
static union 
{
    struct 
    {
        const uint8_t *pri_key;
        const uint8_t *hash;
        uint32_t hash_size;
        const uint8_t *k;
        uint8_t *signature;
        uint8_t P[2][32];
    }sign;
    struct
    {
        const uint8_t *pub_key[2];
        const uint8_t *hash;
        uint32_t hash_size;
        const uint8_t *signature;
        uint8_t u[2][32];
        uint8_t u1G[2][32];
        uint8_t u2H[2][32];
    }verify;
}ecc_u;

__attribute__((weak)) void HAL_LSECC_PointAdd_Complete_Callback(void){}
__attribute__((weak)) void HAL_LSECC_PointMult_Complete_Callback(void){}
__attribute__((weak)) void HAL_LSECC_Sign_Complete_Callback(void){}
__attribute__((weak)) void HAL_LSECC_Verify_Complete_Callback(bool succeed){}

const struct ecc_curve_param secp256r1_param = {
    .p = {
        .mod =  {0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0x00000000,0x00000000,0x00000000,0x00000001,0xFFFFFFFF},
        .h =    {0X00000003,0X00000000,0Xffffffff,0Xfffffffb,0Xfffffffe,0Xffffffff,0Xfffffffd,0X00000004},
        .omega = 0x1,
    },
    .n = {
        .mod =  {0xfc632551,0xf3b9cac2,0xa7179e84,0xbce6faad,0xffffffff,0xffffffff,0x00000000,0xffffffff},
        .h =    {0xbe79eea2,0x83244c95,0x49bd6fa6,0x4699799c,0x2b6bec59,0x2845b239,0xf3d95620,0x66e12d94},
        .omega = 0xee00bc4f,
    },
    .neg_a =    {0x00000003,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
    .G =        {0xd898c296,0xf4a13945,0x2deb33a0,0x77037d81,0x63a440f2,0xf8bce6e5,0xe12c4247,0x6b17d1f2,
                 0x37bf51f5,0xcbb64068,0x6b315ece,0x2bce3357,0x7c0f9e16,0x8ee7eb4a,0xfe1a7f9b,0x4fe342e2},
};

const struct ecc_curve_param secp256k1_param = {
    .p =  {
        .mod=   {0xFFFFFC2F,0xFFFFFFFE,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
        .h =    {0X000E90A1,0X000007A2,0X00000001,0X00000000,0X00000000,0X00000000,0X00000000,0X00000000},
        .omega = 0xd2253531,
    },
    .n = {
        .mod =  {0xd0364141,0xbfd25e8c,0xaf48a03b,0xbaaedce6,0xfffffffe,0xffffffff,0xffffffff,0xffffffff},
        .h =    {0x67d7d140,0x896cf214,0xe7cf878,0x741496c2,0x5bcd07c6,0xe697f5e4,0x81c69bc5,0x9d671cd5},
        .omega = 0x5588b13f,
    },
    .neg_a =    {0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
    .G =        {0x16F81798,0x59F2815B,0x2DCE28D9,0x029BFCDB,0xCE870B07,0x55A06295,0xF9DCBBAC,0x79BE667E,
                 0xFB10D4B8,0x9C47D08F,0xA6855419,0xFD17B448,0x0E1108A8,0x5DA4FBFC,0x26A3C465,0x483ADA77},
};

const struct ecc_curve_param sm2_param = {
    .p =  {
        .mod =  {0xFFFFFFFF,0xFFFFFFFF,0x00000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFE},
        .h =    {0X00000003,0X00000002,0Xffffffff,0X00000002,0X00000001,0X00000001,0X00000002,0X00000004},
        .omega = 0x1,
    },
    .n = {
        .mod =  {0x39d54123,0x53bbf409,0x21c6052b,0x7203df6b,0xffffffff,0xffffffff,0xffffffff,0xfffffffe},
        .h =    {0x7c114f20,0x901192af,0xde6fa2fa,0x3464504a,0x3affe0d4,0x620fc84c,0xa22b3d3b,0x1eb5e412},
        .omega = 0x72350975,
    },
    .neg_a =    {0x00000003,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000},
    .G =        {0x334C74C7,0x715A4589,0xF2660BE1,0x8FE30BBF,0x6A39C994,0x5F990446,0x1F198119,0x32C4AE2C,
                 0x2139F0A0,0x02DF32E5,0xC62A4740,0xD0A9877C,0x6B692153,0x59BDCEE3,0xF4F6779C,0xBC3736A2},
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

static void mod_set(const uint32_t *mod)
{
    memcpy32((uint32_t *)LSECC->NRAM,mod,8);
}

static void mont_mult_param_set(const struct ecc_mont_mod *ptr)
{
    mod_set(ptr->mod);
    memcpy32((uint32_t *)&LSECC->ARAM[56],ptr->h,8);
    LSECC->OMEGA = ptr->omega;
}

static void mont_in(uint8_t src,uint8_t dst)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPR,src)|FIELD_BUILD(ECC_RES,dst)|FIELD_BUILD(ECC_MODE,Mode_MontIn);
}

static void bytecopy2aram(uint8_t dst,const uint8_t *data,uint8_t word_num)
{
    volatile uint32_t *ptr = &LSECC->ARAM[dst*8];
    while(word_num--)
    {
        *ptr++ = data[3]<<24 | data[2]<<16 | data[1]<<8 | data[0]; 
        data += sizeof(uint32_t);
    }
}

static void mont_in_data(const uint8_t *data,uint8_t dst)
{
    bytecopy2aram(dst,data,8);
    mont_in(dst,dst);
}

static bool orig2mont()
{
    switch(fsm_step)
    {
    case 0:
        mont_mult_param_set(&ecc_curve->p);
        mont_in_data(ecc_point_a[0],0);
    break;
    case 1:
        mont_in_data(ecc_point_a[0],1);
    break;
    case 2:
        mont_in_data(ecc_point_a[1],2);
    break;
    case 3:
        mont_in_data((uint8_t *)ecc_curve->neg_a,6);
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
        while((ecc_scalar[fsm_step/8]&1<<fsm_step%8)==0)
        {
            fsm_step -= 1;
        }
        fsm_step -= 1;
    }
    zacau_calc(ecc_scalar[fsm_step/8]&1<<fsm_step%8);
    fsm_step -= 1;
    return fsm_step == 0;
}

static void zaddc_calc(bool remap)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_COMB,1)|FIELD_BUILD(ECC_REMAP,remap?1:0)|FIELD_BUILD(ECC_COMMOD,ECC_ZADDC);
}

static void mont_out(uint8_t src,uint8_t dst)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPR,src)|FIELD_BUILD(ECC_RES,dst)|FIELD_BUILD(ECC_MODE,Mode_MontOut);
}

static void inversion_calc()
{
    uint8_t i;
    memcpy32((uint32_t *)&LSECC->ARAM[0],(uint32_t *)&LSECC->NRAM[0],8);
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
        mont_out(3,3);
    break;
    case 1:
        inversion_calc();
    break;
    case 2:
        mont_mult_param_set(&ecc_curve->p);
        mont_in(3,3);
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
        mont_in_data(ecc_point_a[1],0);
    break;
    case 1:
        zaddu_calc(ecc_scalar[0]&0x1);
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
        mont_out(1,1);
    break;
    case 1:
        mont_out(2,2);
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
        zaddc_calc(ecc_scalar[0]&0x1);
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

static void calc_init(const uint8_t *scalar,const uint8_t *const point[2],uint8_t *const result[2])
{
    ecc_scalar = scalar;
    ecc_point_a[0] = point[0];
    ecc_point_a[1] = point[1];
    ecc_result[0] = result[0];
    ecc_result[1] = result[1];
    ecc_fsm = FSM_INPUT;
    fsm_step = 0;
}

static void copy_from_eccram(uint32_t *src,uint8_t *dst)
{
    uint32_t buf[8];
    memcpy32(buf,src,8);
    memcpy(dst,(uint8_t *)buf,32);
}

static void result2buffer(uint8_t *x,uint8_t *y)
{
    if(x)
    {
        copy_from_eccram((uint32_t *)&LSECC->ARAM[8],x);
    }
    if(y)
    {
        copy_from_eccram((uint32_t *)&LSECC->ARAM[16],y);
    }
}

static void point_mult_point_add_result2buf()
{
    result2buffer(ecc_result[0],ecc_result[1]);
}

static void pointmult(const uint8_t *scalar,const uint8_t *const point[2],uint8_t *const result[2])
{
    calc_init(scalar,point,result);
    while(ecc_fsm != FSM_DONE)
    {
        calc_fsm_run();
        calc_done_wait();
    }
    point_mult_point_add_result2buf();
}

void HAL_LSECC_PointMult(const struct ecc_curve_param *curve,const uint8_t *scalar,const uint8_t *const point[2],uint8_t *const result[2])
{
    ecc_curve = curve;
    pointmult(scalar,point,result);
}

static void pointmult_it(const uint8_t *scalar,const uint8_t *const point[2],uint8_t *const result[2])
{
    HAL_LSECC_MSP_INT_CLRPENDING();
    calc_init(scalar,point,result);
    calc_fsm_run();
    HAL_LSECC_MSP_INT_ENABLE();
}

static void _point_mult_handler(void (*cb)())
{
    if(ecc_fsm == FSM_DONE)
    {
        point_mult_point_add_result2buf();
        cb();
    }else
    {
        calc_fsm_run();
        HAL_LSECC_MSP_INT_ENABLE();
    }
}

static void point_mult_handler()
{
    _point_mult_handler(HAL_LSECC_PointMult_Complete_Callback);
}

void HAL_LSECC_PointMult_IT(const struct ecc_curve_param *curve,const uint8_t *scalar,const uint8_t *const point[2],uint8_t *const result[2])
{
    ecc_curve = curve;
    ecc_int_handler = point_mult_handler;
    pointmult_it(scalar,point,result);
}

static inline void mont_mult(uint8_t x,uint8_t y,uint8_t res)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPL,x)|FIELD_BUILD(ECC_OPR,y)|FIELD_BUILD(ECC_RES,res)|FIELD_BUILD(ECC_MODE,Mode_MontMul);
}

static inline void mod_add(uint8_t x,uint8_t y,uint8_t res)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPL,x)|FIELD_BUILD(ECC_OPR,y)|FIELD_BUILD(ECC_RES,res)|FIELD_BUILD(ECC_MODE,Mode_ModAddi);
}

static inline void mod_sub(uint8_t x,uint8_t y,uint8_t res)
{
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPL,x)|FIELD_BUILD(ECC_OPR,y)|FIELD_BUILD(ECC_RES,res)|FIELD_BUILD(ECC_MODE,Mode_ModSub);
}


static void pointadd_init(const uint8_t *const point_a[2],const uint8_t *const point_b[2],uint8_t *const result[2])
{
    ecc_point_a[0] = point_a[0];
    ecc_point_a[1] = point_a[1];
    ecc_point_b[0] = point_b[0];
    ecc_point_b[1] = point_b[1];
    ecc_result[0] = result[0];
    ecc_result[1] = result[1];
    ecc_add_fsm = ADD_XP_XQ_MOD_SUB;
}

static void add_fsm_run()
{
    switch(ecc_add_fsm)
    {
    case ADD_XP_XQ_MOD_SUB:
        mod_set(ecc_curve->p.mod);
        bytecopy2aram(1,ecc_point_a[0],8);
        bytecopy2aram(2,ecc_point_b[0],8);
        mod_sub(1,2,3);
    break;
    case ADD_XP_XQ_MOD_INV:
        inversion_calc();
    break;
    case ADD_YP_YQ_MOD_SUB:
        bytecopy2aram(4,ecc_point_a[1],8);
        bytecopy2aram(5,ecc_point_b[1],8);
        mod_sub(4,5,6);
    break;
    case ADD_XP_XQ_INV_MONT_IN:
        mont_mult_param_set(&ecc_curve->p);
        mont_in(3,3);
    break;
    case ADD_YP_YQ_MONT_IN:
        mont_in(6,6);
    break;
    case ADD_M_MONT_MULT:
        mont_mult(3,6,6);
    break;
    case ADD_M_M_MONT_MULT:
        mont_mult(6,6,3);
    break;
    case ADD_M_M_MONT_OUT:
        mont_out(3,3);
    break;
    case ADD_XP_XQ_MOD_ADD:
        mod_add(1,2,0);
    break;
    case ADD_MM_XP_XP_MOD_SUB:
        mod_sub(3,0,1);
    break;
    case ADD_XQ_X_MOD_SUB:
        mod_sub(2,1,0);
    break;
    case ADD_XQ_X_MONT_IN:
        mont_in(0,0);
    break;
    case ADD_M_XQ_X_MONT_MULT:
        mont_mult(0,6,3);
    break;
    case ADD_M_XQ_X_MONT_OUT:
        mont_out(3,3);
    break;
    case ADD_M_XQ_X_YQ_MOD_SUB:
        mod_sub(3,5,2);
    break;
    case ADD_DONE:
        while(1);
    break;
    }
}

static void add_fsm_next()
{
    if(ecc_add_fsm == ADD_MM_XP_XP_MOD_SUB && ecc_result[1] == NULL)
    {
        ecc_add_fsm = ADD_DONE;
    }else
    {
        ecc_add_fsm += 1;
    }
}

static void _point_add_handler(void (*cb)())
{
    add_fsm_next();
    if(ecc_add_fsm == ADD_DONE)
    {
        point_mult_point_add_result2buf();
        cb();
    }else
    {
        add_fsm_run();
        HAL_LSECC_MSP_INT_ENABLE();
    }
}

static void point_add_handler()
{
    _point_add_handler(HAL_LSECC_PointAdd_Complete_Callback);
}

static void pointadd(const uint8_t *const point_a[2],const uint8_t *const point_b[2],uint8_t *const result[2])
{
    pointadd_init(point_a,point_b,result);
    while(ecc_add_fsm != ADD_DONE)
    {
        add_fsm_run();
        calc_done_wait();
        add_fsm_next();
    }
    point_mult_point_add_result2buf();
}

static void pointadd_it(const uint8_t *const point_a[2],const uint8_t *const point_b[2],uint8_t *const result[2])
{
    HAL_LSECC_MSP_INT_CLRPENDING();
    pointadd_init(point_a,point_b,result);
    add_fsm_run();
    HAL_LSECC_MSP_INT_ENABLE();
}

void HAL_LSECC_PointAdd(const struct ecc_curve_param *curve,const uint8_t *const point_a[2],const uint8_t *const point_b[2],uint8_t *const result[2])
{
    ecc_curve = curve;
    pointadd(point_a,point_b,result);
}

void HAL_LSECC_PointAdd_IT(const struct ecc_curve_param *curve,const uint8_t *const point_a[2],const uint8_t *const point_b[2],uint8_t *const result[2])
{
    ecc_curve = curve;
    ecc_int_handler = point_add_handler;
    pointadd_it(point_a,point_b,result);
}

static void sign_fsm_run(bool blocking)
{
    switch(ecc_sign_fsm)
    {
    case SIGN_POINT_MULT:
    {
        const uint8_t *G[2]={(uint8_t *)&ecc_curve->G[0],(uint8_t *)&ecc_curve->G[8]};
        uint8_t *P[2]={ecc_u.sign.P[0],ecc_u.sign.P[1]};
        if(blocking)
        {
            pointmult(ecc_u.sign.k,G,P);
        }else
        {
            pointmult_it(ecc_u.sign.k,G,P);
        }
    }break;
    case SIGN_K_MOD_INV:
        mod_set(ecc_curve->n.mod);
        bytecopy2aram(3,ecc_u.sign.k,8);
        inversion_calc();
    break;
    case SIGN_K_INV_MONT_IN:
        mont_mult_param_set(&ecc_curve->n);
        mont_in(3,3);
    break;
    case SIGN_DA_MONT_IN:
        bytecopy2aram(2,ecc_u.sign.pri_key,8);
        mont_in(2,2);
    break;
    case SIGN_R_MONT_IN:
        mont_in(1,6);
    break;
    case SIGN_Z_MONT_IN:
    {
        uint8_t z[32];
        if(ecc_u.sign.hash_size<=32)
        {
            memcpy(z,ecc_u.sign.hash,ecc_u.sign.hash_size);
            memset(&z[ecc_u.sign.hash_size],0,32-ecc_u.sign.hash_size);
        }
        bytecopy2aram(5,z,8);
        mont_in(5,5);
    }break;
    case SIGN_R_DA_MONT_MULT:
        mont_mult(6,2,0);
    break;
    case SIGN_Z_RDA_MOD_ADD:
        mod_add(0,5,4);
    break;
    case SIGN_FINAL_MONT_MULT:
        mont_mult(3,4,2);
    break;
    case SIGN_S_MONT_OUT:
        mont_out(2,2);
    break;
    case SIGN_DONE:
        while(1);
    break;
    }
}

static void signature2buffer()
{
    result2buffer(&ecc_u.sign.signature[0],&ecc_u.sign.signature[32]);
}

static void sign_callback_for_point_mult()
{
    ecc_sign_fsm += 1;
    sign_fsm_run(false);
    HAL_LSECC_MSP_INT_ENABLE();
}

static void sign_handler()
{
    if(ecc_sign_fsm == SIGN_POINT_MULT)
    {
        _point_mult_handler(sign_callback_for_point_mult);
    }else
    {
        ecc_sign_fsm += 1;
        if(ecc_sign_fsm == SIGN_DONE)
        {
            signature2buffer();
            HAL_LSECC_Sign_Complete_Callback();
        }else
        {
            sign_fsm_run(false);
            HAL_LSECC_MSP_INT_ENABLE();
        }
    }
}

static void sign_init(const uint8_t *private_key,const uint8_t *message_hash,uint32_t hash_size,const uint8_t *k,uint8_t *signature)
{
    ecc_u.sign.pri_key = private_key;
    ecc_u.sign.hash = message_hash;
    ecc_u.sign.hash_size = hash_size;
    ecc_u.sign.k = k;
    ecc_u.sign.signature = signature;
    ecc_sign_fsm = SIGN_POINT_MULT;
}

static void sign_fsm_wait()
{
    if(ecc_sign_fsm != SIGN_POINT_MULT)
    {
        calc_done_wait();
    }
    ecc_sign_fsm += 1;
}

static void sign(const uint8_t *private_key,const uint8_t *message_hash,uint32_t hash_size,const uint8_t *k,uint8_t *signature)
{
    sign_init(private_key,message_hash,hash_size,k,signature);
    while(ecc_sign_fsm!=SIGN_DONE)
    {
        sign_fsm_run(true);
        sign_fsm_wait();
    }
    signature2buffer();
}

static void sign_it(const uint8_t *private_key,const uint8_t *message_hash,uint32_t hash_size,const uint8_t *k,uint8_t *signature)
{
    HAL_LSECC_MSP_INT_CLRPENDING();
    sign_init(private_key,message_hash,hash_size,k,signature);
    sign_fsm_run(false);
    HAL_LSECC_MSP_INT_ENABLE();
}

void HAL_LSECC_Sign(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *message_hash,uint32_t hash_size,const uint8_t *k,uint8_t *signature)
{
    ecc_curve = curve;
    sign(private_key,message_hash,hash_size,k,signature);
}

void HAL_LSECC_Sign_IT(const struct ecc_curve_param *curve,const uint8_t *private_key,const uint8_t *message_hash,uint32_t hash_size,const uint8_t *k,uint8_t *signature)
{
    ecc_curve = curve;
    ecc_int_handler = sign_handler;
    sign_it(private_key,message_hash,hash_size,k,signature);
}

static void verify_init(const uint8_t *const public_key[2],const uint8_t *message_hash,uint32_t hash_size,const uint8_t *signature)
{
    ecc_u.verify.pub_key[0] = public_key[0];
    ecc_u.verify.pub_key[1] = public_key[1];
    ecc_u.verify.hash = message_hash;
    ecc_u.verify.hash_size = hash_size;
    ecc_u.verify.signature = signature;
    ecc_verify_fsm = VERIFY_S_MOD_INV;
}

static void verify_fsm_run(bool blocking)
{
    switch(ecc_verify_fsm)
    {
    case VERIFY_S_MOD_INV:
        mod_set(ecc_curve->n.mod);
        bytecopy2aram(3,&ecc_u.verify.signature[32],8);
        inversion_calc();
    break;
    case VERIFY_S_INV_MONT_IN:
        mont_mult_param_set(&ecc_curve->n);
        mont_in(3,4);
    break;
    case VERIFY_Z_MONT_IN:
    {
        uint8_t z[32];
        if(ecc_u.verify.hash_size<=32)
        {
            memcpy(z,ecc_u.verify.hash,ecc_u.verify.hash_size);
            memset(&z[ecc_u.verify.hash_size],0,32-ecc_u.verify.hash_size);
        }
        bytecopy2aram(6,z,8);
        mont_in(6,5);
    }break;
    case VERIFY_MONT_MULT_U1:
        mont_mult(4,5,3);
    break;
    case VERIFY_U1_MOUT_OUT:
        mont_out(3,1);
    break;
    case VERIFY_R_MONT_IN:
        bytecopy2aram(6,ecc_u.verify.signature,8);
        mont_in(6,5);
    break;
    case VERIFY_MONT_MULT_U2:
        mont_mult(4,5,3);
    break;
    case VERIFY_U2_MONT_OUT:
        mont_out(3,2);
    break;
    case VERIFY_POINT_MULT_U1G:
    {
        result2buffer(ecc_u.verify.u[0],ecc_u.verify.u[1]);
        const uint8_t *G[2]={(uint8_t *)&ecc_curve->G[0],(uint8_t *)&ecc_curve->G[8]};
        uint8_t *rslt[2] = {ecc_u.verify.u1G[0],ecc_u.verify.u1G[1]};
        if(blocking)
        {
            pointmult(ecc_u.verify.u[0],G,rslt);
        }else
        {
            pointmult_it(ecc_u.verify.u[0],G,rslt);
        }
    }break;
    case VERIFY_POINT_MULT_U2H:
    {
        const uint8_t *H[2]={ecc_u.verify.pub_key[0],ecc_u.verify.pub_key[1]};
        uint8_t *rslt[2] = {ecc_u.verify.u2H[0],ecc_u.verify.u2H[1]};
        if(blocking)
        {
            pointmult(ecc_u.verify.u[1],H,rslt);
        }else
        {
            pointmult_it(ecc_u.verify.u[1],H,rslt);
        }
    }break;
    case VERIFY_POINT_ADD_U1G_U2H:
    {
        const uint8_t *a[2] = {ecc_u.verify.u1G[0],ecc_u.verify.u1G[1]};
        const uint8_t *b[2] = {ecc_u.verify.u2H[0],ecc_u.verify.u2H[1]};
        uint8_t *rslt[2] = {ecc_u.verify.u[0],NULL};
        if(blocking)
        {
            pointadd(a,b,rslt);
        }else
        {
            pointadd_it(a,b,rslt);
        }
    }break;
    case VERIFY_SUM_MOD_N:
    {
        mod_set(ecc_curve->n.mod);
        uint8_t zero[32]={0};
        bytecopy2aram(0,zero,8);
        mod_add(0,1,1);
    }break;
    case VERIFY_DONE:
        while(1);
    break;
    }
}


static void verify_callback_for_point_mult()
{
    ecc_verify_fsm += 1;
    verify_fsm_run(false);
    HAL_LSECC_MSP_INT_ENABLE();
}

static void verify_callback_for_point_add()
{
    ecc_verify_fsm += 1;
    verify_fsm_run(false);
    HAL_LSECC_MSP_INT_ENABLE();
}

static bool verify_compare()
{
    uint8_t x[32];
    copy_from_eccram((uint32_t *)&LSECC->ARAM[8],x);
    return memcmp(x,ecc_u.verify.signature,sizeof(x)) == 0;
}

static void verify_handler()
{
    if(ecc_verify_fsm == VERIFY_POINT_MULT_U1G || ecc_verify_fsm == VERIFY_POINT_MULT_U2H)
    {
        _point_mult_handler(verify_callback_for_point_mult);
    }else if(ecc_verify_fsm == VERIFY_POINT_ADD_U1G_U2H)
    {
        _point_add_handler(verify_callback_for_point_add);
    }else
    {
        ecc_verify_fsm += 1;
        if(ecc_verify_fsm == VERIFY_DONE)
        {
            bool succeed = verify_compare();
            HAL_LSECC_Verify_Complete_Callback(succeed);
        }else
        {
            verify_fsm_run(false);
            HAL_LSECC_MSP_INT_ENABLE();
        }
    }
}

static void verify_fsm_wait()
{
    if(ecc_verify_fsm != VERIFY_POINT_MULT_U1G 
        && ecc_verify_fsm != VERIFY_POINT_MULT_U2H
        && ecc_verify_fsm != VERIFY_POINT_ADD_U1G_U2H)
    {
        calc_done_wait();
    }
    ecc_verify_fsm += 1;
}

static bool verify(const uint8_t *const public_key[2],const uint8_t *message_hash,uint32_t hash_size,const uint8_t *signature)
{
    verify_init(public_key,message_hash,hash_size,signature);
    while(ecc_verify_fsm!=VERIFY_DONE)
    {
        verify_fsm_run(true);
        verify_fsm_wait();
    }
    return verify_compare();
}

static void verify_it(const uint8_t *const public_key[2],const uint8_t *message_hash,uint32_t hash_size,const uint8_t *signature)
{
    HAL_LSECC_MSP_INT_CLRPENDING();
    verify_init(public_key,message_hash,hash_size,signature);
    verify_fsm_run(false);
    HAL_LSECC_MSP_INT_ENABLE();
}

bool HAL_LSECC_Verify(const struct ecc_curve_param *curve,const uint8_t *const public_key[2],const uint8_t *message_hash,uint32_t hash_size,const uint8_t *signature)
{
    ecc_curve = curve;
    return verify(public_key,message_hash,hash_size,signature);
}

void HAL_LSECC_Verify_IT(const struct ecc_curve_param *curve,const uint8_t *const public_key[2],const uint8_t *message_hash,uint32_t hash_size,const uint8_t *signature)
{
    ecc_curve = curve;
    ecc_int_handler = verify_handler;
    verify_it(public_key,message_hash,hash_size,signature);
}

void LSECC_IRQHandler(void)
{
    HAL_LSECC_MSP_INT_DISABLE();
    LSECC->CON = FIELD_BUILD(ECC_RST,1);
    ecc_int_handler();
}

void h_calc(const uint32_t *mod,uint32_t *result_h)
{
    memcpy32((uint32_t *)LSECC->NRAM,mod,8);
    LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_MODE,Mode_H);
    calc_done_wait();
    memcpy32(result_h,(uint32_t *)&LSECC->ARAM[56],8);
}

uint32_t omega_calc(const uint32_t *mod)
{
    uint32_t val = 1;
    uint8_t i;
    for(i=0;i<31;++i)
    {
        val = val * val * mod[0];
    }
    return -val;
}


// uint8_t x[32] = {5};
// uint8_t y[32] = {9};
// uint32_t mod[8] ={7};
// void mod_mult_test()
// {
//     mont_mult_param_set(&secp256r1_param.n);
//     bytecopy2aram(0,x,8);
//     LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPR,0)|FIELD_BUILD(ECC_RES,1)|FIELD_BUILD(ECC_MODE,Mode_MontIn);
//     calc_done_wait();
//     bytecopy2aram(2,y,8);
//     LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPR,2)|FIELD_BUILD(ECC_RES,3)|FIELD_BUILD(ECC_MODE,Mode_MontIn);
//     calc_done_wait();
//     mont_mult(1,3,6);
//     calc_done_wait();
//     LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPR,6)|FIELD_BUILD(ECC_RES,5)|FIELD_BUILD(ECC_MODE,Mode_MontOut);
//     calc_done_wait();
//     LSECC->CON = FIELD_BUILD(ECC_RUN,1)|FIELD_BUILD(ECC_OPR,1)|FIELD_BUILD(ECC_RES,4)|FIELD_BUILD(ECC_MODE,Mode_MontOut);
//     calc_done_wait();
// }

// uint32_t n_h[8];
// uint32_t n_omega;
// uint32_t test_mod[8] = {5};
// void mod_mult_test()
// {
//     h_calc(secp256r1_param.n.mod,n_h);
//     n_omega = omega_calc(secp256r1_param.n.mod);
//     while(1);
// }