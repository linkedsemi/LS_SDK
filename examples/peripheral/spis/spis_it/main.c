#include "ls_hal_spis.h"
#include "ls_msp_spis.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#include <string.h>
#define LED_IO      PE05
#define spis_cs     PE00  //HA23_P
#define spis_clk    PE01  //HA23_N
#define spis_mosi   PE02  //HA22_P
#define spis_miso   PE03  //HA22_N

#define BUFFERSIZE                  COUNTOF(TxBuffer)
#define COUNTOF(__BUFFER__)         (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

enum
{
    spis_trans,
    spis_complete,
};

volatile uint8_t Spis_State = spis_trans;

SPIS_HandleTypeDef    SPIS_Hdl;

__attribute__((aligned(2))) uint8_t TxBuffer[] = {0x0c,0x45,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0xf};

__attribute__((aligned(2))) uint8_t RxBuffer[BUFFERSIZE] = {0};

void LED_init(void)
{
    io_cfg_output(LED_IO);
    io_write_pin(LED_IO,1);
}

void LED_flicker(void)
{
    io_toggle_pin(LED_IO);
	DELAY_US(500*1000);
}

void Error_Handler(void)
{
    while(1)
    {
        LED_flicker();
    }
}

void SPIS_Init_Func(void)
{
    SPIS_Hdl.Instance = LSSPIS;
    SPIS_Hdl.Init.CLKPolarity   = SPIS_POLARITY_LOW;        // 极性
    SPIS_Hdl.Init.CLKPhase      = SPIS_PHASE_1EDGE;         // 相位
    SPIS_Hdl.Init.FirstBit      = SPIS_FIRSTBIT_MSB;        // 先传输MSB
    SPIS_Hdl.Init.Frame_Size    = 7;                        // 帧的大小

    if(HAL_SPIS_Init(&SPIS_Hdl) != HAL_OK)
    {
        Error_Handler();
    }
}

static uint16_t BufferCmp(uint8_t *TxBuffer, uint8_t *RxBuffer, uint16_t Length)
{
    while(Length--)
    {
        if(*TxBuffer !=  *RxBuffer)
        {
            return Length;
        }
        TxBuffer++;
        RxBuffer++;
    }
    return 0;
}

void HAL_SPIS_RxCpltCallback()
{
    LOG_I("receive complete\r\n");
    LOG_I("The following data is received:");
    for (uint8_t i = 0; i < BUFFERSIZE; i++)
    {
        LOG_I("RxBuffer[%d] = %d", i,RxBuffer[i]);
    }
    Spis_State = spis_complete;
}

void HAL_SPIS_TxCpltCallback()
{
    LOG_I("transmit complete\r\n");
    Spis_State = spis_complete;
}

void HAL_SPIS_Tx_UDR_Callback()
{
    LOG_I("ISR_SPIS_TX_UDR\r\n");
}

void HAL_SPIS_Rx_OVR_Callback()
{
    LOG_I("ISR_SPIS_RX_OVR\r\n");
}

int main()
{    
    sys_init_none();
    LED_init();
    pinmux_spis_init();
    SPIS_Init_Func();
    io_cfg_output(PH07);
    io_clr_pin(PH07);
    io_cfg_output(PH06);
    io_clr_pin(PH06);
    uint8_t flag;
    
    LOG_I("BUFFERSIZE = %d",BUFFERSIZE);
    Spis_State = spis_trans;

    // flag = HAL_SPIS_Receive_IT(&SPIS_Hdl, (uint8_t*)RxBuffer, BUFFERSIZE*3);  //当cap_iygnfnt等于1时，Size必须和cap_idx相等
    // flag = HAL_SPIS_Transmit_IT(&SPIS_Hdl, (uint8_t*)TxBuffer, BUFFERSIZE);
    flag = HAL_SPIS_TransmitReceive_IT(&SPIS_Hdl, (uint8_t*)TxBuffer, (uint8_t*)RxBuffer, BUFFERSIZE);
    while (Spis_State == spis_trans);

    switch (flag)
    {
    case HAL_OK:
        if(BufferCmp((uint8_t*)TxBuffer, (uint8_t*)RxBuffer, BUFFERSIZE))
        {
            Error_Handler();
        }
        break;
    default:
        Error_Handler();
        break;
    }
    
    while (1)
    {

    }  
}