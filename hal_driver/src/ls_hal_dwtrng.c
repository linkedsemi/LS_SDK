#include "ls_hal_trng.h"
#include "ls_msp_dwtrng.h"
#include "field_manipulate.h"

#define CO_BIT(pos) (1UL<<(pos))

static void send_cmd(uint8_t cmd)
{
    DWTRNG->CTRL = cmd;
    while ((DWTRNG->ISTAT & CO_BIT(4)) == 0) ;
    DWTRNG->ISTAT = CO_BIT(4);
}

HAL_StatusTypeDef HAL_TRNG_Init(void)
{
    HAL_DWTRNG_MSP_Init();
    DWTRNG->SMODE = 0x0;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TRNG_DeInit(void)
{
    HAL_DWTRNG_MSP_DeInit();
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TRNG_GenerateRandomNumber(uint32_t *random32bit)
{
    DWTRNG->IE = 0x0;
    DWTRNG->ISTAT = 0xffffffff;
    send_cmd(1);
    send_cmd(3);
    send_cmd(6);
    *random32bit = DWTRNG->RAND[0];
    return HAL_OK;
}

HAL_StatusTypeDef HAL_TRNG_GenerateRandomNumber_IT(void)
{
    return HAL_OK;
}

__attribute__((weak)) void HAL_TRNG_ReadyDataCallback(uint32_t random32bit){}

void HAL_TRNG_IRQHandler(void)
{
}

