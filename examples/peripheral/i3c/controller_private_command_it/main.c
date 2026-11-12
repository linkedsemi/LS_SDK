#include <string.h>
#include "ls_soc_gpio.h"
#include "platform.h"


#include "ls_hal_i3c_target.h"
#include "ls_hal_i3c_controller.h"
#include "ls_msp_i3c.h"

#include "reg_sysc_app_per.h"
#include "log.h"

I3C_HandleTypeDef hi3c10;
I3C_HandleTypeDef hi3c9;

static I3C_XferTypeDef aContextBuffers[2];
static uint32_t aControlBuffer[0xF];
static uint8_t aTxBuffer[300];


void I3C10_CONTROLLER_INIT(void)
{
    hi3c10.Instance = I3C10;
    hi3c10.Mode = HAL_I3C_MODE_CONTROLLER;
    hi3c10.Init.CtrlBusCharacteristic.SDAHoldTime = HAL_I3C_SDA_HOLD_TIME_0_5;
    hi3c10.Init.CtrlBusCharacteristic.WaitTime = HAL_I3C_OWN_ACTIVITY_STATE_0;
    hi3c10.Init.CtrlBusCharacteristic.SCLPPLowDuration = 0x1f;//0xa0;//
    hi3c10.Init.CtrlBusCharacteristic.SCLI3CHighDuration = 0x0f;//0x5c;//
    hi3c10.Init.CtrlBusCharacteristic.SCLODLowDuration = 0x2f;//0x7c;//
    hi3c10.Init.CtrlBusCharacteristic.SCLI2CHighDuration = 0x1f;//0x00;//
    hi3c10.Init.CtrlBusCharacteristic.BusFreeDuration = 0xa;
    hi3c10.Init.CtrlBusCharacteristic.BusIdleDuration = SDK_I3C_PCLK_MHZ*2;
    
    hi3c10.Init.CtrlFifoConfig.RxFifoThreshold = HAL_I3C_RXFIFO_THRESHOLD_4_4;
    hi3c10.Init.CtrlFifoConfig.TxFifoThreshold = HAL_I3C_TXFIFO_THRESHOLD_4_4;
    hi3c10.Init.CtrlFifoConfig.StatusFifo = HAL_I3C_STATUSFIFO_DISABLE;

    hi3c10.Init.CtrlConfig.StallTime = 0xff;
    hi3c10.Init.CtrlConfig.HotJoinAllowed = ENABLE;
    hi3c10.Init.CtrlConfig.ACKStallState = DISABLE;
    hi3c10.Init.CtrlConfig.CCCStallState = DISABLE;
    hi3c10.Init.CtrlConfig.TxStallState = DISABLE;
    hi3c10.Init.CtrlConfig.RxStallState = DISABLE;
    REG_FIELD_WR(hi3c10.Instance->SCONFIG2,I3C_SCONFIG2_SDA_SCL_DELAY,0);
    hi3c10.EnableController = true;
    HAL_I3C_Controller_Init(&hi3c10);
}

typedef struct {
  char *        TARGET_NAME;          /*!< Marketing Target reference */
  uint32_t      TARGET_ID;            /*!< Target Identifier on the Bus */
  uint64_t      TARGET_BCR_DCR_PID;   /*!< Concatenation value of PID, BCR and DCR of the target */
  uint8_t       STATIC_ADDR;          /*!< Static Address of the target, value found in the datasheet of the device */
  uint8_t       DYNAMIC_ADDR;         /*!< Dynamic Address of the target preset by software/application */
} TargetDesc_TypeDef;
TargetDesc_TypeDef TargetDesc1 =
{
  "TARGET_ID1",
  0,
  0x0000000000000000,
  0x00,
  0x32,
};
TargetDesc_TypeDef TargetDesc2 =
{
  "TARGET_ID2",
  0,
  0x0000000000000000,
  0x00,
  0x33,
};

TargetDesc_TypeDef TargetDesc3 =
{
  "TARGET_ID3",
  0,
  0x0000000000000000,
  0x00,
  0x34,
};

/* Array contain targets descriptor */
TargetDesc_TypeDef *aTargetDesc[3] = \
                          {
                            &TargetDesc1,       /* DEVICE_ID1 */
                            &TargetDesc2,      /* DEVICE_ID1 */
                            &TargetDesc3,
                          };

/* Descriptor for private data transmit */
static I3C_PrivateTypeDef aPrivateDescriptor[] = \
                                          {
                                            {0x34, {aTxBuffer, 1}, {NULL, 0}, HAL_I3C_DIRECTION_WRITE},
                                          };
                                          
                                          
#define I3C10_SCL PJ00
#define I3C10_SDA PJ01

#define I3C9_SCL PJ02
#define I3C9_SDA PJ03

#ifndef PINMUX_FUNC3
#define PINMUX_FUNC3 2
#endif

static void Error_Handler(void)
{
    LOG_RAW("Error_Handler\r\n");
    while (1) {};
}


int main()
{
    sys_init_none();

    per_func_enable(I3C10_SCL,PINMUX_FUNC3);
    per_func_enable(I3C10_SDA,PINMUX_FUNC3);
    per_func_enable(I3C9_SCL,PINMUX_FUNC3);
    per_func_enable(I3C9_SDA,PINMUX_FUNC3);

    /*时钟使能*/
    SYSC_APP_PER->PD_PER_CLKG3 |=SYSC_APP_PER_CLKG_SET_I3C10_MASK;
    // SYSC_APP_PER->PD_PER_CLKG3 |=SYSC_APP_PER_CLKG_SET_I3C9_MASK;

    I3C10_CONTROLLER_INIT();

    if (HAL_I3C_Ctrl_DynAddrAssign_IT(&hi3c10, I3C_ONLY_ENTDAA) != HAL_OK)
    {
      LOG_I("entdaa error code = 0x%x",hi3c10.ErrorCode);
        /* Error_Handler() function is called when error occurs. */
        // Error_Handler();
    }

    while (HAL_I3C_GetState(&hi3c10) != HAL_I3C_STATE_READY)
    {
    }

  aContextBuffers[0].CtrlBuf.pBuffer = aControlBuffer;
  aContextBuffers[0].CtrlBuf.Size    = 1;
  aContextBuffers[0].TxBuf.pBuffer   = aTxBuffer;
  aContextBuffers[0].TxBuf.Size      = 1;
  if (HAL_I3C_AddDescToFrame(&hi3c10,
                             NULL,
                             &aPrivateDescriptor[0],
                             &aContextBuffers[0],
                             1,
                             I3C_PRIVATE_WITH_ARB_RESTART) != HAL_OK)
  {
    Error_Handler();
  }

  /*##- Start the transmission process ###################################*/
  /* Transmit private data processus */
  if (HAL_I3C_Ctrl_Transmit_IT(&hi3c10, &aContextBuffers[0]) != HAL_OK)
  {
    Error_Handler();
  }

  //target_recived_data_check(&hi3c9,1);

  while (HAL_I3C_GetState(&hi3c10) != HAL_I3C_STATE_READY)
  {
  }


    while (1);
    return 0;
}

volatile uint8_t target_dix = 0;
void HAL_I3C_TgtReqDynamicAddrCallback(I3C_HandleTypeDef *hi3c10, uint64_t targetPayload)
{
  /* Update Payload on aTargetDesc */
  if(__HAL_I3C_GET_BCR(targetPayload) == hi3c9.Init.TgtBusCharacteristic.bcr)
  {
    aTargetDesc[2]->TARGET_BCR_DCR_PID = targetPayload;
    HAL_I3C_Ctrl_SetDynAddr(hi3c10, aTargetDesc[2]->DYNAMIC_ADDR<<1);
  }else
  {
    aTargetDesc[target_dix]->TARGET_BCR_DCR_PID = targetPayload;
    HAL_I3C_Ctrl_SetDynAddr(hi3c10, aTargetDesc[target_dix]->DYNAMIC_ADDR<<1);
    // LOG_I("aTargetDesc[target_dix]->DYNAMIC_ADD = 0x%x",aTargetDesc[target_dix]->DYNAMIC_ADDR);
    target_dix++;
  }
  if(target_dix == 2)
  {
    target_dix = 0;
  }
}