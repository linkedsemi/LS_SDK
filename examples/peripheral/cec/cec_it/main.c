#include "app_config.h"
#include <stdio.h>
#include "platform.h"
#include "log.h"
#include "ls_hal_cec.h"
#include "ls_msp_cec.h"

static CEC_HandleTypeDef hcec_config;
volatile uint8_t OEM_CEC_T_Flag = 0;
volatile uint8_t OEM_CEC_R_Flag = 0;
uint32_t TBuffer[100];
uint32_t RBuffer[16] = {0};
uint8_t Rcount = 0;

static void ls_cec_init(void)
{
    hcec_config.Instance = CEC;
    hcec_config.Init.MasterAddress = CEC_INITIATOR_ADDRESS_4;
    hcec_config.Init.SlaveAddress = CEC_DESTINATION_ADDRESS;
    hcec_config.Init.FrameType = NORMAL_DATA_3;
    HAL_CEC_Init(&hcec_config);
}

static void CEC_Button_Send(void)
{
    if (io_read_pin(PH07) == 0)
    {
        DELAY_MS(100);
        TBuffer[0] = 0x8F;
        HAL_CEC_Transmit_IT(&hcec_config, hcec_config.Init.SlaveAddress, TBuffer, 2);

    }
}

int main(void)
{
    sys_init_none();  
    io_cfg_input(PH07);
    pinmux_cec_init(PH00);
    LOG_I("FPGA");
    DELAY_MS(100);
    ls_cec_init();
    while(1)
    {
        OEM_CEC_T_Flag = 0;
        CEC_Button_Send();
        while(OEM_CEC_T_Flag == 0);
        OEM_CEC_R_Flag = 0;
        HAL_CEC_Receive_IT(&hcec_config, RBuffer);
        while(OEM_CEC_R_Flag == 0);
    }
}

void HAL_CEC_TX_DONE_Callback(void)
{
    LOG_I("TX_DONE_Callback\n");
    LOG_I("Packet send: %02X", CEC->TX_DATA[0]);
    for (int i = 1; i < (CEC->TX_BUF_CNT); i++)
    {
        LOG_I(":%02X", CEC->TX_DATA[i]);
    }
    LOG_I("FPGA transmit complete!\n");
    OEM_CEC_T_Flag = 1;
}

void HAL_CEC_RX_FINISH_Callback(uint8_t count)
{	
    LOG_I("Packet Receive:");
    for (int i = 0; i < count; i++)
    {
        LOG_I("%02X ", RBuffer[i]);
    }
    LOG_I("FPGA receive complete!\n");	
   
    switch (RBuffer[1])
    {
        case 0x83:                                                  // <Give Physical Address>	
            HAL_CEC_Transmit_IT(&hcec_config, 0xf, (uint32_t *)"\x84\x00\x10\x04", 5); 
            break;
        case 0x8c:                                                  // <Give Device Vendor ID>
            HAL_CEC_Transmit_IT(&hcec_config, 0xf, (uint32_t *)"\x87\x01\x23\x45", 5); 
            break;
        case 0x90:        
            LOG_I("FPGA responds to 5010: 0x40,0x90,0x00");        // <Give Device Power>
            HAL_CEC_Transmit_IT(&hcec_config, hcec_config.Init.SlaveAddress, (uint32_t *)"\x90\x00", 3); 
            break;
        case 0x46:
            HAL_CEC_Transmit_IT(&hcec_config, 0x0, (uint32_t *)"\x47\x00\x10\x40", 5); 
            break;
    }
    OEM_CEC_R_Flag = 1;
}


