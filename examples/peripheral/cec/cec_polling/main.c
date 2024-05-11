#include "app_config.h"
#include <stdio.h>
#include "platform.h"
#include "log.h"
#include "ls_hal_cec.h"
#include "ls_msp_cec.h"

static CEC_HandleTypeDef hcec_config;
uint8_t OEM_CEC_T_Flag = 0;
uint32_t TBuffer[100];
uint32_t RBuffer[16] = {0};
uint8_t Rcount = 0;

static void CEC_Button_Send(void)
{
    if (io_read_pin(PH07) == 0) // 按键按下后触发
    {
        DELAY_MS(100);
        if (io_read_pin(PH07) == 0)
        {
            if (OEM_CEC_T_Flag == 0) // 发送数据的标志位
            {
                TBuffer[0] = 0x8F;
                HAL_CEC_Transmit(&hcec_config, hcec_config.Init.SlaveAddress, TBuffer, 2);		
                OEM_CEC_T_Flag = 1;
                LOG_I("Packet send: %02X", CEC->TX_DATA[0]);
                for (int i = 1; i < (CEC->TX_BUF_CNT); i++)
                    LOG_I(":%02X\n", CEC->TX_DATA[i]);
                LOG_I("FPGA transmit complete!\n");
            }
        }
    }
    else
    {
        OEM_CEC_T_Flag = 0;
    }
}

static void CEC_Data_Processing(void)
{
    uint32_t tx_buf[16];
	
    if(HAL_CEC_Receive(&hcec_config, RBuffer, &Rcount) == HAL_OK)
    {
        if((RBuffer[0] == 0x04)&&(Rcount == 1))                         // <Report Physical Address>
        {
            HAL_CEC_Transmit(&hcec_config, hcec_config.Init.SlaveAddress, tx_buf, 1); 
        }
        LOG_I("HAL_CEC_Receive:Rcount=%02x\n", Rcount);
        LOG_I("Receive:");
        for (int i = 0; i <Rcount; i++)
        {
            LOG_I("%02X\n", RBuffer[i]);
        }
        LOG_I("FPGA receive complete!\n");
        switch (RBuffer[1])
        {
            case 0x83:                                                  // <Give Physical Address>	
                HAL_CEC_Transmit(&hcec_config, 0xf, (uint32_t *)"\x84\x00\x10\x04", 5); 
                break;
            case 0x8c:                                                  // <Give Device Vendor ID>
                HAL_CEC_Transmit(&hcec_config, 0xf, (uint32_t *)"\x87\x01\x23\x45", 5); 
                break;
            case 0x90:        
                LOG_I("FPGA responds to 5010: 0x40,0x90,0x00");                                           // <Give Device Power>
                HAL_CEC_Transmit(&hcec_config, hcec_config.Init.SlaveAddress, (uint32_t *)"\x90\x00", 3); 
                break;
            case 0x46:
                HAL_CEC_Transmit(&hcec_config, 0x0, (uint32_t *)"\x47\x00\x10\x40", 5); 
                break;
        }
    }
}

static void ls_cec_init(void)
{
    hcec_config.Instance = CEC;
    hcec_config.Init.MasterAddress = CEC_INITIATOR_ADDRESS_4;
    hcec_config.Init.SlaveAddress = CEC_DESTINATION_ADDRESS;
    hcec_config.Init.FrameType = NORMAL_DATA_3;
    HAL_CEC_Init(&hcec_config);
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
        CEC_Button_Send();
        CEC_Data_Processing();
    }
}

