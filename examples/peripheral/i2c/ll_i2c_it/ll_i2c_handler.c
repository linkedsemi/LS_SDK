#include <stdio.h>
#include "ls_hal_i2c.h"
#include "log.h"
#include "systick.h"
#include "ls_hal_i2c.h"
#include "ls_msp_i2c.h"
#include "field_manipulate.h"

extern void LL_I2C_MasterNACKCpltCallback(reg_i2c_t *I2Cx);
extern void LL_I2C_MasterTXECpltCallback(reg_i2c_t *I2Cx);
extern void LL_I2C_MasterTCRCpltCallback(reg_i2c_t *I2Cx);
extern void LL_I2C_MasterRXNECpltCallback(reg_i2c_t *I2Cx);

void LL_I2C1_IRQHandler(void)
{

    /* Check NACK flag -----------------------------------------------*/
    if ((LL_I2C_IsActiveFlagIT(I2C1, I2C_ITRI_NACK) != RESET) && (LL_I2C_IsEnableIT(I2C1, I2C_ITVS_NACK) != RESET))
    {
        LL_I2C_ClearFlagIT(I2C1, I2C_ITIC_NACK);
        LL_I2C_Clearflag(I2C1, I2C_CFR_NACKCF);
        LL_I2C_MasterNACKCpltCallback(I2C1);
    }

    /* Check STOP flag -----------------------------------------------*/
    if (LL_I2C_IsActiveFlagIT(I2C1, I2C_ITRI_STOP) != RESET)
    {
        /* Clear interrupt Flag */
        LL_I2C_ClearFlagIT(I2C1, I2C_ITIC_STOP);
    }

    /*  Check TX flag -----------------------------------------------*/
    if ((LL_I2C_IsActiveFlag(I2C1, I2C_SR_TXE)!= RESET) && (LL_I2C_IsEnableIT(I2C1, I2C_ITVS_TXE) != RESET))
    {
        LL_I2C_ClearFlagIT(I2C1, I2C_ITIC_TXE);
        LL_I2C_MasterTXECpltCallback(I2C1);
    }

    /* Check RXNE flag -----------------------------------------------*/
    if ((LL_I2C_IsActiveFlagIT(I2C1, I2C_ITRI_RXNE) != RESET) && (LL_I2C_IsEnableIT(I2C1, I2C_ITVS_RXNE) != RESET))
    {
        LL_I2C_ClearFlagIT(I2C1, I2C_ITIC_RXNE);
        LL_I2C_MasterRXNECpltCallback(I2C1);
    }

    /* Check BERR flag -----------------------------------------------*/
    if (LL_I2C_IsActiveFlagIT(I2C1, I2C_ITRI_ERR) != RESET)
    {
        LOG_I("error !\n");
        LL_I2C_ClearFlagIT(I2C1, I2C_ITIC_ERR);
        LL_I2C_Clearflag(I2C1, I2C_SR_BERR);
        LL_I2C_DisableIT(I2C1, I2C_ITDEN_ERR | I2C_ITDEN_ADDR | I2C_ITDEN_NACK | I2C_ITDEN_STOP);
    }
}

void LL_I2C2_IRQHandler()
{
    ;
}