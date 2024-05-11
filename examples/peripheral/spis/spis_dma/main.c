#include "ls_hal_spis.h"
#include "ls_msp_spis.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "ls_hal_dmacv3.h"
#include "log.h"
#include <string.h>



static DEF_DMA_CONTROLLER(dmac1_inst,DMAC2)
#define LED_IO      PE05
#define spis_cs     PE00
#define spis_clk    PE01  
#define spis_mosi   PE02  
#define spis_miso   PE03  

#define BUFFERSIZE                  COUNTOF(TxBuffer)
#define COUNTOF(__BUFFER__)         (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

enum
{
    spis_trans,
    spis_Txcomplete,
    spis_Rxcomplete,
    spis_TxRxcomplete
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
    HAL_DMA_Controller_Init(&dmac1_inst);
    SPIS_Hdl.DMAC_Instance = &dmac1_inst;
    SPIS_Hdl.Rx_Env.DMA.Channel = 0;
    SPIS_Hdl.Tx_Env.DMA.Channel = 1;

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

int main()
{    
    sys_init_none();
    LED_init();
    pinmux_spis_init();
    SPIS_Init_Func();
    uint8_t flag;

    Spis_State = spis_trans;

    // flag = HAL_SPIS_Receive_DMA(&SPIS_Hdl, (uint8_t*)RxBuffer, BUFFERSIZE);  //当cap_infnt等于1时，Size必须和cap_idx相等
    // flag = HAL_SPIS_Transmit_DMA(&SPIS_Hdl, (uint8_t*)TxBuffer, BUFFERSIZE);
    flag = HAL_SPIS_TransmitReceive_DMA(&SPIS_Hdl, (uint8_t*)TxBuffer, (uint8_t*)RxBuffer, BUFFERSIZE);

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

void HAL_SPIS_DMA_RxCpltCallback()
{
    LOG_I("The following data is received:");
    for (uint8_t i = 0; i < sizeof(TxBuffer); i++)
    {
            LOG_I("%d", RxBuffer[i]);
    }
    Spis_State = spis_Rxcomplete;
}

void HAL_SPIS_DMA_TxCpltCallback()
{
    LOG_I("transmit complete");
    Spis_State = spis_Txcomplete;
}

void HAL_SPIS_DMA_TxRxCpltCallback()
{
    LOG_I("SPIS transmit and received complete");
    for (uint8_t i = 0; i < sizeof(TxBuffer); i++)
    {
            LOG_I("%d", RxBuffer[i]);
    }
    Spis_State = spis_TxRxcomplete;
}