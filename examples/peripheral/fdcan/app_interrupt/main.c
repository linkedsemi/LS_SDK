#include "ls_hal_fdcan.h"
#include "ls_soc_gpio.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "platform.h"
#include "log.h"
#include "systick.h"

#define FDCAN_DEBUG_ARRAY_ON   1
#define FDCAN_DEBUG_ARRAY(array, num) do{    \
    int32_t i;                               \
    uint8_t* a = array;                      \
    if(FDCAN_DEBUG_ARRAY_ON)                 \
    {                                        \
        LOG_RAW("<<-FDCAN-DEBUG-ARRAY->>\n");\
        for (i = 0; i < (num); i++)          \
        {                                    \
            LOG_RAW("%02x ", (a)[i]);        \
            if ((i + 1 ) % 8 == 0)           \
            {                                \
                LOG_RAW("\n");               \
            }                                \
        }                                    \
        LOG_RAW("\n");                       \
    }                                        \
}while(0)

#define CANFD_TXD PA10
#define CANFD_RXD PA09

#define FDCAN_TRX_DATA_LEN   64
#define FDCAN_CONFIG_DLC     FDCAN_DLC_BYTES_64

FDCAN_HandleTypeDef FDCan_Handle;

FDCAN_TxMSGTypeDef pTxMsg;
FDCAN_RxMsgTypeDef RxMsg;

uint8_t RxData[FDCAN_TRX_DATA_LEN];
uint8_t TxData[FDCAN_TRX_DATA_LEN] = {0};

bool tx_cmpflag = true;

static void FDCAN_Mode_Config(void)
{
    pTxMsg.TxData = TxData;
    FDCan_Handle.pTxMsg = &pTxMsg;
    RxMsg.RxData = RxData;
    FDCan_Handle.pRxMsg = &RxMsg;

    FDCan_Handle.Instance = FDCAN;
    FDCan_Handle.Init.FrameFormat = FDCAN_FRAME_FD_BRS_PEX;
    FDCan_Handle.Init.Mode = FDCAN_MODE_NORMAL;

    // 24 MHz System clock: 500 KBit/s,75% sample point
    FDCan_Handle.Init.NominalBittiming.Prescaler = 2;
    FDCan_Handle.Init.NominalBittiming.PROP = 11;
    FDCan_Handle.Init.NominalBittiming.SJW = 3;
    FDCan_Handle.Init.NominalBittiming.PH1 = 6;
    FDCan_Handle.Init.NominalBittiming.PH2 = 6;

    // 24 MHz System clock: 2 MBit/s,75% sample point
    // FDCan_Handle.Init.DataBitting.Prescaler = 1;
    // FDCan_Handle.Init.DataBitting.PROP = 5;
    // FDCan_Handle.Init.DataBitting.SJW = 1;
    // FDCan_Handle.Init.DataBitting.PH1 = 3;
    // FDCan_Handle.Init.DataBitting.PH2 = 3;

    // 24 MHz System clock: 1 Mbit/s,75% sample point
    FDCan_Handle.Init.DataBitting.Prescaler = 1;
    FDCan_Handle.Init.DataBitting.PROP = 11;
    FDCan_Handle.Init.DataBitting.SJW = 3;
    FDCan_Handle.Init.DataBitting.PH1 = 6;
    FDCan_Handle.Init.DataBitting.PH2 = 6;

    FDCan_Handle.Init.FilterEnble = ENABLE;
    FDCan_Handle.Init.FDRF = ENABLE;
    FDCan_Handle.Init.ISOFD = ENABLE;
    FDCan_Handle.Init.TTCM = DISABLE;
    FDCan_Handle.Init.AutoRetransmission = ENABLE;
    FDCan_Handle.Init.reTransNbr = 2;

    HAL_FDCAN_Init(&FDCan_Handle);
    LOG_I("HAL_FDCAN_Init End");

    if(HAL_FDCAN_Start(&FDCan_Handle) != HAL_OK)
    {
        LOG_I("FDCAN Start ERROR.");
    }
}

static void FDCAN_Filter_Config(void)
{
    FDCAN_FilterTypeDef  sFilterConfig;

    sFilterConfig.FilterIndex = FDCAN_FILTER_BIT_A;
    sFilterConfig.FilterType = FDCAN_FILTER_FD_EXTEND;
    sFilterConfig.FilterValue1 = 0x2568;
    sFilterConfig.FilterValue2 = 0x2568;
    HAL_FDCAN_ConfigFilter(&FDCan_Handle,&sFilterConfig);
}

void FDCAN_Config(void)
{
    pinmux_fdcan_init(CANFD_TXD, CANFD_RXD);
    FDCAN_Mode_Config();
    FDCAN_Filter_Config();
}

void update_txdata(void)
{
    static int index = 0;
    static uint8_t value = 1;  

    TxData[index] = value;

    if (TxData[index] == 255) {
        index = (index + 1) % FDCAN_TRX_DATA_LEN;
        value = 1; 
    } else {
        value++;
    }
}

void FDCAN_SetMsg(bool it_mode)
{
    FDCan_Handle.pTxMsg->Identifier = 0x2568;
    FDCan_Handle.pTxMsg->IdType = FDCAN_EXTENDED_ID;
    FDCan_Handle.pTxMsg->TxFrameType = FDCAN_DATA_FRAME;
    FDCan_Handle.pTxMsg->DataLength = FDCAN_CONFIG_DLC;
    FDCan_Handle.pTxMsg->ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    FDCan_Handle.pTxMsg->BitRateSwitch = FDCAN_BRS_ON;
    FDCan_Handle.pTxMsg->FDFormat = FDCAN_FD_CAN;
    FDCan_Handle.pTxMsg->BufferIndex = FDCAN_TX_BUFFER1;

    if(it_mode)
    {   
        HAL_FDCAN_Transmit_IT(&FDCan_Handle);
    }
    else
    {
        HAL_FDCAN_Transmit(&FDCan_Handle, 100);
    }

    update_txdata();
}

void HAL_FDCAN_TxCpltCallback(FDCAN_HandleTypeDef* hcan)
{
    LOG_I("TX CMP");
    tx_cmpflag = true;
}
void HAL_FDCAN_RxCpltCallback(FDCAN_HandleTypeDef* hcan)
{
    LOG_I("ID:0x%x,DLC:0x%x",RxMsg.Identifier,RxMsg.DataLength);
    FDCAN_DEBUG_ARRAY(RxData,FDCAN_TRX_DATA_LEN);

    HAL_FDCAN_Receive_IT(&FDCan_Handle);
}

int main(void)
{
    sys_init_none();
    LOG_I("FDCAN TEST Examples...\r\n");
    FDCAN_Config();

    HAL_FDCAN_Receive_IT(&FDCan_Handle);
    memset(TxData,0x3C,sizeof(TxData));

    while(1)
    {
        if(tx_cmpflag){
            tx_cmpflag =false;
            FDCAN_SetMsg(true);
        }
        DELAY_MS(100);
    }

    return 0;
}

