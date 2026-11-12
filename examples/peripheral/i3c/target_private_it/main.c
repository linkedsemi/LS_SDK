#include <string.h>
#include "ls_soc_gpio.h"
#include "platform.h"


#include "ls_hal_i3c_target.h"
#include "ls_hal_i3c_controller.h"
#include "ls_msp_i3c.h"

#include "reg_sysc_app_per.h"
#include "log.h"

I3C_HandleTypeDef hi3c9;

static I3C_XferTypeDef aContextBuffers[2];
static uint8_t aTxBuffer[50];
static uint8_t aRxBuffer[50];


void I3C9_TARGET_INIT(void)
{
    hi3c9.Mode = HAL_I3C_MODE_TARGET;
    hi3c9.Instance = I3C9;
    hi3c9.EnableTarget = true;
    LL_I3C_TgtBusConfTypeDef *slaveConfig = &hi3c9.Init.TgtBusCharacteristic;
    slaveConfig->isHotJoin = false;
    slaveConfig->staticAddr = 0xcc;
    slaveConfig->vendorID = 0x11bU;
    slaveConfig->enableRandomPart = false;
    slaveConfig->partNumber = 0;
    slaveConfig->dcr = 0;/* Generic device. */
    slaveConfig->bcr = 
        0b1100110; /* BCR[7:6]: device role, I3C slave(2b'00), BCR[5]: SDR Only / SDR and HDR Capable,  SDR and HDR
              Capable(1b'1), BCR[4]: Bridge Identifier, Not a bridge device(1b'0), BCR[3]: Offline Capable, device is
              offline capable(1b'1), BCR[2]: IBI Payload(1b'1). No data byte following(1b'0), BCR[1]: IBI Request Capable,
              capable(1b'1), BCR[0]: Max Data Speed Limitation, has limitation(1b'1). */
    slaveConfig->nakAllRequest          = false;
    slaveConfig->ignoreS0S1Error        = true;
    slaveConfig->offline                = false;
    slaveConfig->matchTargetStartStop    = false;
    slaveConfig->maxWriteLength = 255;
    slaveConfig->maxReadLength = 255;
    slaveConfig->matchCount = (uint8_t)(SDK_HCLK_MHZ);

    HAL_I3C_Target_Init(&hi3c9);
}


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

  per_func_enable(I3C9_SCL,PINMUX_FUNC3);
  per_func_enable(I3C9_SDA,PINMUX_FUNC3);

  /*时钟使能*/
  SYSC_APP_PER->PD_PER_CLKG3 |=SYSC_APP_PER_CLKG_SET_I3C9_MASK;

  I3C9_TARGET_INIT();

  aContextBuffers[0].RxBuf.pBuffer   = aRxBuffer;
  aContextBuffers[0].RxBuf.Size      = 50;

  if(HAL_I3C_Tgt_Receive_IT(&hi3c9,&aContextBuffers[0]) != HAL_OK)
  {
    Error_Handler();
  }

  while (HAL_I3C_GetState(&hi3c9) != HAL_I3C_STATE_READY)
  {
  }

  aContextBuffers[0].TxBuf.pBuffer   = aTxBuffer;
  aContextBuffers[0].TxBuf.Size      = 50;

  if(HAL_I3C_Tgt_Transmit_IT(&hi3c9,&aContextBuffers[0]) != HAL_OK)
  {
    Error_Handler();
  }

  while (HAL_I3C_GetState(&hi3c9) != HAL_I3C_STATE_READY)
  {
  }

  while (1);
  return 0;
}