#include "ls_hal_can.h"
#include "ls_soc_gpio.h"
#include <stdint.h>
#include "platform.h"
#include "log.h"

#define CAN_IDE CAN_ID_STD
#define CAN_ID  0x12
#define CAN_DLC 8

CAN_HandleTypeDef Can_Handle;
CanTxMsgTypeDef TxMessage;
CanRxMsgTypeDef RxMessage;
volatile uint8_t flag;

static void CAN_Mode_config(void)
{
    Can_Handle.Instance = BXCAN;
    Can_Handle.pTxMsg = &TxMessage;
    Can_Handle.pRxMsg = &RxMessage;

    Can_Handle.Init.TTCM = DISABLE;
    Can_Handle.Init.ABOM = ENABLE;
    Can_Handle.Init.AWUM = ENABLE;
    Can_Handle.Init.NART = ENABLE;
    Can_Handle.Init.RFLM = DISABLE;
    Can_Handle.Init.TXFP = DISABLE;
    Can_Handle.Init.Mode = CAN_MODE_NORMAL;
    Can_Handle.Init.SJW = CAN_SJW_1TQ;

    Can_Handle.Init.BS1 = CAN_BS1_4TQ;
    Can_Handle.Init.BS2 = CAN_BS2_3TQ;

    Can_Handle.Init.Prescaler = 7;
    if(HAL_CAN_Init(&Can_Handle) != HAL_OK)
    {
        LOG_I("CAN INIT ERROR");
        while(1);
    }
}

uint32_t CAN_Fill_32Bit_FilterId(uint32_t id,uint8_t ide,uint8_t rtr)
{
    uint32_t ID_Value = 0;

    if (ide == CAN_ID_STD)
    {
        ID_Value = (id << 21) | CAN_ID_STD | rtr;
    }
    else if (ide == CAN_ID_EXT)
    {
        ID_Value = (id << 3) | CAN_ID_EXT | rtr;
    }
    LOG_I("FilterId REG = 0x%x", ID_Value);
    return ID_Value;
}

static void CAN_Filter_Config(void)
{
    CAN_FilterConfTypeDef CAN_FilterInitStructure = {0};
    uint32_t flt_id = 0;

    CAN_FilterInitStructure.FilterNumber = 0;
    CAN_FilterInitStructure.FilterMode = CAN_FILTERMODE_IDMASK; 
    CAN_FilterInitStructure.FilterScale = CAN_FILTERSCALE_32BIT; 

    flt_id = CAN_Fill_32Bit_FilterId(CAN_ID,CAN_IDE,CAN_RTR_DATA);
    CAN_FilterInitStructure.FilterIdHigh = (flt_id & 0xFFFF0000) >> 16;
    CAN_FilterInitStructure.FilterIdLow = flt_id & 0xFFFF;
    CAN_FilterInitStructure.FilterMaskIdHigh = 0; 
    CAN_FilterInitStructure.FilterMaskIdLow = 0;
    CAN_FilterInitStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    CAN_FilterInitStructure.FilterActivation = ENABLE;
    HAL_CAN_ConfigFilter(&Can_Handle, &CAN_FilterInitStructure);
}

void Init_RxMes(void)
{
    uint8_t ubCounter = 0;

    Can_Handle.pRxMsg->StdId = 0x00;
    Can_Handle.pRxMsg->ExtId = 0x00;
    Can_Handle.pRxMsg->IDE = CAN_ID_STD;
    Can_Handle.pRxMsg->DLC = 0;
    Can_Handle.pRxMsg->FMI = 0;
    for (ubCounter = 0; ubCounter < CAN_DLC; ubCounter++)
    {
        Can_Handle.pRxMsg->Data[ubCounter] = 0x00;
    }
}

void CAN_SetMsg(void)
{
    uint8_t ubCounter = 0;
    Can_Handle.pTxMsg->StdId = CAN_ID;
    Can_Handle.pTxMsg->ExtId = CAN_ID;
    Can_Handle.pTxMsg->IDE = CAN_IDE;
    Can_Handle.pTxMsg->RTR = CAN_RTR_DATA;
    Can_Handle.pTxMsg->DLC = CAN_DLC; 

    for (ubCounter = 0; ubCounter < CAN_DLC; ubCounter++)
    {
        Can_Handle.pTxMsg->Data[ubCounter] = ubCounter;
    }
}

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
    uint32_t id_tmp = 0, ide_temp = 0, dlc_tmp = 0;
    ide_temp = hcan->pRxMsg->IDE;
    dlc_tmp = hcan->pRxMsg->DLC;
    if (ide_temp == CAN_ID_EXT)
    {
        id_tmp = hcan->pRxMsg->ExtId;
    }
    else
    {
        id_tmp = hcan->pRxMsg->StdId;
    }
    LOG_I("ID:0x%x,IDE:%d,DLC:%d", id_tmp, ide_temp, dlc_tmp);
    if ((id_tmp == CAN_ID) && (ide_temp == CAN_IDE) && (dlc_tmp == CAN_DLC))
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    HAL_CAN_Receive_IT(&Can_Handle, CAN_FIFO0);
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
    LOG_I("\r\n CAN ERR \r\n");
}

int main(void)
{
    sys_init_none();
    io_pull_write(PB00,IO_PULL_DOWN);
    io_cfg_input(PB00);
    LOG_I("can test start...");
    pinmux_bxcan_init(PA00,PA01);
    CAN_Mode_config();
    CAN_Filter_Config();

    Init_RxMes(); 
    HAL_CAN_Receive_IT(&Can_Handle, CAN_FIFO0);

    while(1)
    {
        if(io_read_pin(PB00)==1)
        {
            CAN_SetMsg();
            HAL_CAN_Transmit_IT(&Can_Handle);
        }
        
        if(flag==1)
        {
            flag = 0;
            LOG_I("\r\nCAN RECV DATA:");
            LOG_HEX(Can_Handle.pRxMsg->Data,8);
        }
        DELAY_US(500000);
    }
}


