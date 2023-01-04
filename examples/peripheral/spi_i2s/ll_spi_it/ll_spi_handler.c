#include <stdio.h>
#include "ls_hal_spi_i2s.h"
#include "log.h"
#include "systick.h"

extern void LL_SPI_TxCpltCallback(void);
extern void LL_SPI_RxCpltCallback(void);

void LL_SPI2_IRQHandler(void)
{
    /* SPI in mode Receiver ----------------------------------------------------*/
    if ((LL_SPI_IsActiveFlagIT(SPI2, SPI_ITRI_RXNE) != RESET) && (LL_SPI_IsEnabledIT(SPI2, SPI_ITVS_RXNE) != RESET))
    {
        LL_SPI_ClearFlagIT(SPI2, SPI_ITIC_RXNE);
        /* Set the function for IT treatment */
        /* Call function Slave Reception Callback */
        LL_SPI_RxCpltCallback();

        // return;
    }

    /* SPI in mode Transmitter -------------------------------------------------*/
    if ((LL_SPI_IsActiveFlagIT(SPI2, SPI_ITRI_TXE) != RESET) && (LL_SPI_IsEnabledIT(SPI2, SPI_ITVS_TXE) != RESET))
    {

        LL_SPI_ClearFlagIT(SPI2, SPI_ITIC_TXE);
        /* Call function Slave Reception Callback */
        LL_SPI_TxCpltCallback();

        // return;
    }

    /* SPI in Error Treatment --------------------------------------------------*/
    if (((LL_SPI_IsActiveFlagIT(SPI2, SPI_ITRI_OVR) != RESET) || (LL_SPI_IsActiveFlagIT(SPI2, SPI_ITRI_MODF) != RESET)) && (LL_SPI_IsEnabledIT(SPI2, SPI_ITVS_OVR) != RESET))
    {
        LOG_I("ERROR\n");
        LL_SPI_ClearFlagIT(SPI2, SPI_ITIC_OVR);
        LL_SPI_DisableIT(SPI2, SPI_ITDEN_RXNE);
        LL_SPI_DisableIT(SPI2, SPI_ITDEN_TXE);
        LL_SPI_DisableIT(SPI2, SPI_ITDEN_OVR);

        /* SPI Frame error interrupt occurred ------------------------------------*/
    }
}