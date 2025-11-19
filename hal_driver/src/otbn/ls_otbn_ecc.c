

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "ls_otbn_ecc.h"
#include "ls_hal_otbn.h"
#include "ls_msp_otbn.h"
#include "field_manipulate.h"
#include "reg_sysc_sec_cpu.h"
#include "qsh.h"

static ls_otbn_fireware_t cur_curve = OTBN_UNUSED;

int ls_otbn_load_curve_fireware(ls_otbn_fireware_t curve_id)
{
    int err = 0;
    
    uint32_t imem_size;
    uint32_t dmem_size;
    uint32_t *imem_image;
    uint32_t *dmem_image;
    uint32_t dmem_end;

    if(!HAL_OTBN_In_Idle_State())
    {
        printf("The otbn is not in idle state,can not program otbn\n");
        return -1;
    }

    if(cur_curve == curve_id)
    {
        return 0;
    }
    cur_curve = curve_id;
    switch (curve_id)
    {
    case OTBN_ECDSA_P256:
        imem_size = LS_OTBN_ECDSA_P256_IMEM_SIZE;
        dmem_size = LS_OTBN_ECDSA_P256_DMEM_SIZE;
        dmem_end = LS_OTBN_ECDSA_P256_DMEM_END;
        imem_image = (uint32_t *)p256_imem;
        dmem_image = (uint32_t *)p256_dmem;
        break;
    case OTBN_ECDSA_P384:
        imem_size = LS_OTBN_ECDSA_P384_IMEM_SIZE;
        dmem_size = LS_OTBN_ECDSA_P384_DMEM_SIZE;
        dmem_end = LS_OTBN_ECDSA_P384_DMEM_END;
        imem_image = (uint32_t *)p384_imem;
        dmem_image = (uint32_t *)p384_dmem;
        break;
    case OTBN_SM2:
        imem_size = LS_OTBN_SM2_IMEM_SIZE;
        dmem_size = LS_OTBN_SM2_DMEM_SIZE;
        dmem_end = LS_OTBN_SM2_DMEM_END;
        imem_image = (uint32_t *)sm2_imem;
        dmem_image = (uint32_t *)sm2_dmem;
        break;
    default:
        printf("ecc curve not suppoted!!\n");
        return -1;
    }
    // printf("otbn load imem, curve_id: %d\n",curve_id);
    err |= HAL_OTBN_DMEM_Set(0, 0, dmem_end);
    err |= HAL_OTBN_IMEM_Write(0, imem_image, imem_size);
    err |= HAL_OTBN_DMEM_Write(0, dmem_image, dmem_size);

    return err;
}

int get_curve_otbn_info(ls_otbn_fireware_t curve, ecc_remote_addr *info)
{
    switch (curve)
    {
    case OTBN_ECDSA_P256:
        info->remote_random_addr = LS_OTBN_ECDSA_P256_RANDOM_SEED_OFFSET;
        info->remote_mode_addr = LS_OTBN_ECDSA_P256_MODE_OFFSET;
        info->remote_addr_d0 = LS_OTBN_ECDSA_P256_D0_OFFSET;
        info->remote_addr_d1 = LS_OTBN_ECDSA_P256_D1_OFFSET;
        info->remote_addr_r = LS_OTBN_ECDSA_P256_R_OFFSET;
        info->remote_addr_s = LS_OTBN_ECDSA_P256_S_OFFSET;
        info->remote_addr_qx = LS_OTBN_ECDSA_P256_X_OFFSET;
        info->remote_addr_qy = LS_OTBN_ECDSA_P256_Y_OFFSET;
        info->remote_addr_msg = LS_OTBN_ECDSA_P256_MSG_OFFSET;
        info->remote_addr_r_x = LS_OTBN_ECDSA_P256_X_R_OFFSET;
        info->curve_size = 32;
        break;
    
    case OTBN_ECDSA_P384:
        info->remote_random_addr = LS_OTBN_ECDSA_P384_RANDOM_SEED_OFFSET;
        info->remote_mode_addr = LS_OTBN_ECDSA_P384_MODE_OFFSET;
        info->remote_addr_d0 = LS_OTBN_ECDSA_P384_D0_OFFSET;
        info->remote_addr_d1 = LS_OTBN_ECDSA_P384_D1_OFFSET;
        info->remote_addr_r = LS_OTBN_ECDSA_P384_R_OFFSET;
        info->remote_addr_s = LS_OTBN_ECDSA_P384_S_OFFSET;
        info->remote_addr_qx = LS_OTBN_ECDSA_P384_X_OFFSET;
        info->remote_addr_qy = LS_OTBN_ECDSA_P384_Y_OFFSET;
        info->remote_addr_msg = LS_OTBN_ECDSA_P384_MSG_OFFSET;
        info->remote_addr_r_x = LS_OTBN_ECDSA_P384_X_R_OFFSET;
        info->curve_size = 48;
        break;

    case OTBN_SM2:
        info->remote_random_addr = LS_OTBN_SM2_RANDOM_SEED_OFFSET;
        info->remote_mode_addr = LS_OTBN_SM2_MODE_OFFSET;
        info->remote_addr_d0 = LS_OTBN_SM2_D0_OFFSET;
        info->remote_addr_d1 = LS_OTBN_SM2_D1_OFFSET;
        info->remote_addr_r = LS_OTBN_SM2_R_OFFSET;
        info->remote_addr_s = LS_OTBN_SM2_S_OFFSET;
        info->remote_addr_qx = LS_OTBN_SM2_X_OFFSET;
        info->remote_addr_qy = LS_OTBN_SM2_Y_OFFSET;
        info->remote_addr_r_x = LS_OTBN_SM2_X_R_OFFSET;
        info->remote_addr_msg = LS_OTBN_SM2_MSG_OFFSET;
        info->curve_size = 32;
        break;

    default:
        while(1);
        break;
    }

    if(ls_otbn_load_curve_fireware(curve) != 0)
    {
        printf("otbn software config error\n"); 
        return -1;
    }
    
    return 0;
}
