/******************************************************************************
 * File: main.c
 * Author: 
 * Overview: dac audio main source file
 *
 * Date: Created on 2023-11-30, 10:15
 ******************************************************************************/

/******************************************************************************
 Include
 ******************************************************************************/
#include "log.h"
#include "adpcm.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include "ls_hal_dac.h"
#include "ls_hal_timer.h"
#include "ls_hal_flash.h"
#include "adpcm.h"
#if DMACV2
#include "ls_hal_dmacv2.h"
#elif DMACV3
#include "ls_hal_dmacv3.h"
#endif
/******************************************************************************
 Local Macro Definition
 ******************************************************************************/
/** Audio sampling rate 16 KHz **/

    #ifdef LM3050
    #define TIM_PRESCALER     (8-1)
    #elif defined LEO
    #define TIM_PRESCALER     (9-1)
    #endif
#define TIM_PERIOD        (1000-1)

/* Data size of a single play */
#define SOURCE_BUF_SIZE 256    //Audio source data size
#define OUTPUT_BUF_SIZE 505    //Data size after audio decompression

/******************************************************************************
 Local Variable Definition
 ******************************************************************************/
/* Define dac transmission variables */
struct dac
{
    uint32_t data_buf1[OUTPUT_BUF_SIZE]; //Dac transmission data buffer 1
    uint32_t data_buf2[OUTPUT_BUF_SIZE]; //Dac transmission data buffer 2
    bool buf1_full;                      //Data buffer 1 is full of flag bits
    bool buf2_full;                      //Data buffer 2 is full of flag bits
    bool buf1_sending;                   //Data buffer 1 sending
} DAC_Transfer_st = {{0},{0},0,0,0};


/* Define audio processing variables */
struct audio
{
    uint32_t sound_codeIndex;     // Access the current location of audio data
    uint32_t data_size;           // Audio data size
    uint32_t data_flash_addr;     // FLASH address for storing audio data
} Audio_Var_st = {0,0,0x10000};

DEF_DMA_CONTROLLER(dmac1_inst,DMAC1);

/* Defines the DAC initialization structure variable */ 
DAC_HandleTypeDef DACx_Hdl = {
    .Env.DMA.DMA_Channel = 1,
    .DMAC_Instance = &dmac1_inst,

    .Instance = LSDAC12,
    .DACx = DAC1,
    .DAC1_wave = No_Wave,
    .DAC1_Trigger = GENERAL_TimerA_TRGO,
    .DAC1_Mamp = triangle_amplitude_4095,
};

/* Defines the Timer A initialization structure variable */ 
TIM_HandleTypeDef TimHandle = {
    .Instance = LSGPTIMA,
    .Init.Prescaler = TIM_PRESCALER,
    .Init.Period = TIM_PERIOD,
    .Init.ClockDivision = 0,
    .Init.TrgoSource = TIM_TRGO_UPDATE,
    .Init.CounterMode = TIM_COUNTERMODE_DOWN,
};
/******************************************************************************
 Local Function Declaration
 ******************************************************************************/
static void General_Timer_A_Init(void);
static void DAC_Init_Func(void);
static void Get_Flash_Size(void);
static bool SoundDecode(uint32_t *data_arr);
static void HAL_DAC_ConvCpltCallback(DAC_HandleTypeDef *hdac);

/******************************************************************************
 Local Function Definition
 ******************************************************************************/
/******************************************************************************
 * Function:int main(void)
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:
 *      1.Initialize system
 *      2.Initialize Timer A, DAC, DAC-DMA, GPIO
 *      3.Store the raw audio into data buffers 1 and 2
 *      4.Call the DAC-DMA function to output buffer 1 data from GPIO via DAC-DMA
 *      5.Fill the data buffer in While(1)
 * Note:
 ******************************************************************************/
int main(void)
{
    sys_init_none();
    io_cfg_output(PC03);
    io_set_pin(PC03);
    General_Timer_A_Init();
    #ifdef LM3050
    pinmux_dac1_init();         // PA07
    #elif defined LEO
    pinmux_dac1_out1_init();    // PA02
    #endif
	DAC_Init_Func();
    io_clr_pin(PC03);
    HAL_TIM_Base_Start(&TimHandle);

    Get_Flash_Size();

    DAC_Transfer_st.buf1_full = SoundDecode(DAC_Transfer_st.data_buf1);
    DAC_Transfer_st.buf1_sending = 1;
    HAL_DAC_Start_DMA(&DACx_Hdl, DAC1_ALIGN_12B_L, DAC_Transfer_st.data_buf1, sizeof(DAC_Transfer_st.data_buf1), HAL_DAC_ConvCpltCallback);
	while (1)
	{
		if (!DAC_Transfer_st.buf1_full)
			DAC_Transfer_st.buf1_full = SoundDecode(DAC_Transfer_st.data_buf1);

		if (!DAC_Transfer_st.buf2_full)
			DAC_Transfer_st.buf2_full = SoundDecode(DAC_Transfer_st.data_buf2);
	}
}
/******************************************************************************
 * Function:static void General_Timer_A_Init(void)
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview: The general timer A is initialized
 * Note:
 ******************************************************************************/
static void General_Timer_A_Init(void)
{ 
    HAL_TIM_Init(&TimHandle);
}
/******************************************************************************
 * Function:static void DAC_Init_Func(void)
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:The DAC initialization
 * Note:
 ******************************************************************************/
static void DAC_Init_Func(void)
{
	DMA_CONTROLLER_INIT(dmac1_inst);
    HAL_DAC_Init(&DACx_Hdl);
}
/******************************************************************************
 * Function:
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:
 * Note:
 ******************************************************************************/
static void Get_Flash_Size(void)
{
    uint8_t temp_arr[4] = {0};
    hal_flash_fast_read(Audio_Var_st.data_flash_addr, temp_arr, 4);
    for (uint8_t i = 0; i < 4; i++)
    {
        Audio_Var_st.data_size |= temp_arr[i] << (8 * i);
    }
    Audio_Var_st.data_flash_addr += 0x04;
}
/******************************************************************************
 * Function:static bool SoundDecode(uint32_t *data_arr)
 * PreCondition:
 * Input: data_arr: data buffer
 * Output:
 * Return:
 * Side Effects:
 * Overview: Fill the raw data into the data buffer
 * Note:
 ******************************************************************************/
static bool SoundDecode(uint32_t *data_arr)
{
    int16_t temp_data[OUTPUT_BUF_SIZE] = {0};
    uint8_t source_cbuf[SOURCE_BUF_SIZE] = {0};

    hal_flash_fast_read(Audio_Var_st.data_flash_addr+Audio_Var_st.sound_codeIndex, source_cbuf, SOURCE_BUF_SIZE);
	Adpcm_Decode_Block(temp_data, source_cbuf, SOURCE_BUF_SIZE,1);

    for (uint32_t num = 0; num < OUTPUT_BUF_SIZE;num++)
	{
		if (temp_data[num] & 0x8000)
			data_arr[num] = temp_data[num] & 0x7fff;
		else
			data_arr[num] = temp_data[num] | 0x8000;
	}

    Audio_Var_st.sound_codeIndex += SOURCE_BUF_SIZE;
	if (Audio_Var_st.sound_codeIndex > Audio_Var_st.data_size)
	{
		Audio_Var_st.sound_codeIndex = 0;
	}

	return true;
}
/******************************************************************************
 * Function:static void HAL_DAC_ConvCpltCallback2(DAC_HandleTypeDef *hdac) 
 * PreCondition:
 * Input:
 * Output:
 * Return:
 * Side Effects:
 * Overview:DAC-DMA completes the callback function
 * Note:
 ******************************************************************************/
static void HAL_DAC_ConvCpltCallback(DAC_HandleTypeDef *hdac) 
{
    if (DAC_Transfer_st.buf1_sending)
    {
        DAC_Transfer_st.buf1_full = 0;
        DAC_Transfer_st.buf1_sending = 0;
        HAL_DAC_Start_DMA(&DACx_Hdl, DAC1_ALIGN_12B_L, DAC_Transfer_st.data_buf2, sizeof(DAC_Transfer_st.data_buf2), HAL_DAC_ConvCpltCallback);
    }
    else
    {
        DAC_Transfer_st.buf2_full = 0;
        DAC_Transfer_st.buf1_sending = 1;
        HAL_DAC_Start_DMA(&DACx_Hdl, DAC1_ALIGN_12B_L, DAC_Transfer_st.data_buf1, sizeof(DAC_Transfer_st.data_buf1), HAL_DAC_ConvCpltCallback);
    }
}
/*******************************************************************************
 End of File
 ******************************************************************************/
