/******************************************************************************
 * File: main.c
 * Author: ZhangWF
 * Overview: amic main source file
 *
 * Date: Created on 2022-03-10, 10:15
 ******************************************************************************/

/******************************************************************************
 Include
 ******************************************************************************/
#define LOG_TAG	"ADC_AMIC"
#include "app_config.h"
#include "ls_hal_adc.h"
#include "platform.h"
#include "ls_soc_gpio.h"
#include <string.h>
#include <stdlib.h>
#include "ls_hal_dmac.h"
#include "log.h"
#include "ls_hal_uart.h"
#include "ls_hal_timer.h"

#include "ls_hal_pis.h"
#if (AMIC_STREAM_FORMAT & AMIC_SAMPLE_ADPCM)
#include "adpcm.h"
#endif

/******************************************************************************
 External Const Definition
 ******************************************************************************/

/******************************************************************************
 External Variable Declaration
 ******************************************************************************/

/******************************************************************************
 External Function Declaration
 ******************************************************************************/

/******************************************************************************
 Local Macro Definition
 ******************************************************************************/
#define TIM_INTERFACE	LSGPTIMC
#define TIM_PRESCALER   ((SDK_HCLK_MHZ / 2) - 1)

#if (AMIC_SAMPLE_RATE & AMIC_SAMPLE_RATE_16K)
#define TIM_PERIOD      (125 - 1) /* unit of us, Period is 16K */
#elif (AMIC_SAMPLE_RATE & AMIC_SAMPLE_RATE_8K)
#define TIM_PERIOD      (250 - 1) /* unit of us, Period is 8K */
#endif

#define GPIO_LOW 	0
#define GPIO_HIGH	1

#define UART1_TX_IO	PB00
#define UART1_RX_IO	PB01

#define UART2_TX_IO	PA13
#define UART2_RX_IO	PA12

#define GPIO_OUT_INIT(IO, STATE)	{	\
	io_cfg_output(IO);			\
	io_write_pin(IO, STATE);		\
}

#define GPIO_IN_INIT(IO, PULL, EDGE, IRQ) {	\
	io_cfg_input(IO);				\
	io_pull_write(IO, PULL);			\
	if (IRQ) {						\
		io_exti_config(IO, EDGE);	\
	}								\
}

#define GPIO_READ(IO)								io_read_pin(IO)
#define GPIO_SET(IO, STATE)							io_write_pin(IO, STATE)
#define GPIO_TOGGLE(IO)								io_toggle_pin(IO)
#define GPIO_SET_DRIVE_CAPACITY(IO, CAPACITY_LEVEL)	io_drive_capacity_write(IO, CAPACITY_LEVEL)

#define AMIC_PWR_IO	PA15	// amic power supply from gpio
#define BTN_IO		PB15	// keep collecting adc when hold on pressed button

#define BTN_INIT(IO, PULL, EDGE, IRQ)	GPIO_IN_INIT(IO, PULL, EDGE, IRQ)
#define BTN_READ(IO)					GPIO_READ(IO)
#define BTN_IS_PRESS(IO)				(0 == BTN_READ(IO))

#if (SDK_HCLK_MHZ == 64)
#define ADC_SAMPLE_BUF_LENGTH  		256 	// 8 16 32 64 128 256
#define ADC_CLOCK_DIV ADC_CLOCK_DIV8
#else
#define ADC_SAMPLE_BUF_LENGTH  		40 		// 8 16 32	8~64 if SDK_HCLK_MHZ is not 64
#define ADC_CLOCK_DIV ADC_CLOCK_DIV2
#endif

#define ADC_OUTPUT_BUF_LENGTH  		(ADC_SAMPLE_BUF_LENGTH * 2) 		// 16 32 64 128 256 512
#define ADC_ADPCM_BUF_LENGTH  		(ADC_SAMPLE_BUF_LENGTH * 2 / 4) 	// 8 16 32	8~32 if SDK_HCLK_MHZ is not 64
#define ADC_SAMPLE_CENTRAL_VALUE	2048	// the peripheral circuits increase adc sampling baseline to 2048

#if (AMIC_SAMPLE_ALGORITHM_MODE & AMIC_SAMPLE_ALGORITHM_LSH)
#define ADC_SAMPLE_ALGORITHM_LSH_BIT 2 	// the adc value left shift 2 bit to turn up the volume
#endif

#define AMIC_TRIG_TYPE	ADC_PIS_TRIG
#define ADC_PIS_CHANNEL	6
/******************************************************************************
 Local Type Definition
 ******************************************************************************/
typedef enum
{
	AMIC_SBUF_LIST_0,
	AMIC_SBUF_LIST_1,
	AMIC_SBUF_LIST_2,
	AMIC_SBUF_LIST_3,

	AMIC_SBUF_LIST_4,
	AMIC_SBUF_LIST_5,
	AMIC_SBUF_LIST_6,
	AMIC_SBUF_LIST_7,

	AMIC_SBUF_LIST_END = AMIC_SBUF_LIST_7,
	AMIC_SBUF_LIST_MAX
} AMIC_STREAM_BUF_LIST_te;

typedef struct
{
	// output
	volatile uint8_t outputIdx;
	// sample
	volatile uint8_t sampleIdx;
	volatile uint16_t sampleCnt;
	// adc handle
	ADC_HandleTypeDef adcHandle;
	// timer handle
	TIM_HandleTypeDef timHandle;
} AMIC_CTRL_ts;
/******************************************************************************
 Local Const Definition
 ******************************************************************************/

/******************************************************************************
 Local Variable Definition
 ******************************************************************************/
DEF_DMA_CONTROLLER(dmac1_inst, DMAC1);

#if (AMIC_STREAM_FORMAT & AMIC_SAMPLE_ADPCM)
DMA_RAM_ATTR uint8_t _ADPCM_Stream_Buf[ADC_ADPCM_BUF_LENGTH] = {0};	// pcm encode to adpcm cache buffer
#endif
DMA_RAM_ATTR int16_t _Stream_Buf[AMIC_SBUF_LIST_MAX][ADC_SAMPLE_BUF_LENGTH] = {0};	// adc sampling cache buffer

static UART_HandleTypeDef UART_Config1 =
{
#if (UART_TRANSMIT_MODE & UART_TRANSMIT_DMA)
	.DMAC_Instance = &dmac1_inst,
	.Tx_Env.DMA.DMA_Channel = 3,
#endif
	.UARTX = UART1,
	.Init.BaudRate = UART_BAUDRATE_921600,
	.Init.MSBEN = 0,
	.Init.Parity = UART_NOPARITY,
	.Init.StopBits = UART_STOPBITS1,
	.Init.WordLength = UART_BYTESIZE8,
};

static UART_HandleTypeDef UART_Config2 =
{
#if (UART_TRANSMIT_MODE & UART_TRANSMIT_DMA)
	.DMAC_Instance = &dmac1_inst,
	.Tx_Env.DMA.DMA_Channel = 4,
#endif
	.UARTX = UART2,
	.Init.BaudRate = UART_BAUDRATE_921600,
	.Init.MSBEN = 0,
	.Init.Parity = UART_NOPARITY,
	.Init.StopBits = UART_STOPBITS1,
	.Init.WordLength = UART_BYTESIZE8,
};

static AMIC_CTRL_ts _AMIC_Controller =
{
	.adcHandle = {
		/* dma sampling config */
		.Env.DMA.DMA_Channel        = 0,
		.DMAC_Instance              = &dmac1_inst,
		/* Common config */
		.Instance 					= LSADC,
		.Init.DataAlign             = ADC_DATAALIGN_RIGHT,
		.Init.ScanConvMode          = ADC_SCAN_DISABLE,		/* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
		.Init.NbrOfConversion       = 1,					/* Parameter discarded because sequencer is disabled */
		.Init.DiscontinuousConvMode = DISABLE,				/* Parameter discarded because sequencer is disabled */
		.Init.NbrOfDiscConversion   = 1,					/* Parameter discarded because sequencer is disabled */
		.Init.ContinuousConvMode    = DISABLE,				/* Continuous mode to have maximum conversion speed (no delay between conversions) */
		.Init.TrigType      		= AMIC_TRIG_TYPE,		/* Trig of conversion start done by which event */
		.Init.Vref          		= ADC_VREF_VCC,
		.Init.AdcCkDiv      		= ADC_CLOCK_DIV,        /*!< ADC division coefficient ranges from 1 to 128 */
		.Init.AdcDriveType 			= BINBUF_DIRECT_DRIVE_ADC
	},
	.timHandle = {
		.Instance           = TIM_INTERFACE,
		.Init.Prescaler     = TIM_PRESCALER,
		.Init.Period        = TIM_PERIOD,
		.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1,
		.Init.CounterMode   = TIM_COUNTERMODE_UP,
		.Init.TrgoSource 	= TIM_TRGO_UPDATE
	}
};
/******************************************************************************
 Local Function Declaration
 ******************************************************************************/
static bool _AMIC_Uart_Init(UART_HandleTypeDef *huart, uint8_t txd, uint8_t rxd, bool isRxPullup);
static void _AMIC_Sample_Channel_Enable(uint32_t channel);
static void _AMIC_Sampling_UartOutput(void);
static void _AMIC_ConvCplt_Callback(ADC_HandleTypeDef *hadc);
static void _AMIC_ExtChannel_Init(ADC_HandleTypeDef *hadc, void (*Callback)(ADC_HandleTypeDef* hadc), bool isStart);
static void _AMIC_Timer_Init(TIM_HandleTypeDef *TimHandle, bool isStart);

//System weak define callback
void io_exti_callback(uint8_t pin,exti_edge_t edge);
/******************************************************************************
 Local Function Definition
 ******************************************************************************/
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
int main(void)
{
	sys_init_none();

	DMA_CONTROLLER_INIT(dmac1_inst);

	BTN_INIT(BTN_IO, IO_PULL_UP, INT_EDGE_FALLING, true);

	/* need to set the io drive capacity in order to amic stable power supply if use io supply power to mic */
	GPIO_OUT_INIT(AMIC_PWR_IO, true);
	GPIO_SET_DRIVE_CAPACITY(AMIC_PWR_IO, IO_OUTPUT_MAX_DRIVER);
	DELAY_US(2 * 1000); // wait for the amic stable power supply according to the specifications of the mic

	_AMIC_Uart_Init(&UART_Config1, UART1_TX_IO, UART1_RX_IO, true);
	_AMIC_Uart_Init(&UART_Config2, UART2_TX_IO, UART2_RX_IO, true);

	LOG_I("System Start, Build Date Time: %s %s", __DATE__, __TIME__);
	LOG_I("Version: %02X%02X%02X", BUILD_SW_VER_H, BUILD_SW_VER_M, BUILD_SW_VER_L);

	_AMIC_ExtChannel_Init(&_AMIC_Controller.adcHandle, _AMIC_ConvCplt_Callback, true);

	_AMIC_Timer_Init(&_AMIC_Controller.timHandle, false);

	while (1) {
		// output adc data via uart, to test voice adc sample quality
		_AMIC_Sampling_UartOutput();
	}
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
static void _AMIC_Sampling_UartOutput(void)
{

	if (0 < _AMIC_Controller.sampleCnt) {

		_AMIC_Controller.sampleCnt--;
		// calculate the adc
		for (uint16_t i = 0; i < ADC_SAMPLE_BUF_LENGTH; i++) {
			#if (AMIC_SAMPLE_ALGORITHM_MODE & AMIC_SAMPLE_ALGORITHM_LSH)
			_Stream_Buf[_AMIC_Controller.outputIdx][i] = (int16_t)((_Stream_Buf[_AMIC_Controller.outputIdx][i] << ADC_SAMPLE_ALGORITHM_LSH_BIT) - (ADC_SAMPLE_CENTRAL_VALUE << ADC_SAMPLE_ALGORITHM_LSH_BIT));
			#else
			_Stream_Buf[_AMIC_Controller.outputIdx][i] = (int16_t)(_Stream_Buf[_AMIC_Controller.outputIdx][i] - ADC_SAMPLE_CENTRAL_VALUE);
			#endif
		}

		#if (AMIC_STREAM_FORMAT & AMIC_SAMPLE_PCM)
		#if  (UART_TRANSMIT_MODE & UART_TRANSMIT_DMA)
		HAL_UART_Transmit_DMA(&UART_Config1, (uint8_t *)&_Stream_Buf[_AMIC_Controller.outputIdx][0], ADC_OUTPUT_BUF_LENGTH);
		#else
		HAL_UART_Transmit(&UART_Config1, (uint8_t *)&_Stream_Buf[_AMIC_Controller.outputIdx][0], ADC_OUTPUT_BUF_LENGTH, 1000);
		#endif
		#endif

		#if (AMIC_STREAM_FORMAT & AMIC_SAMPLE_ADPCM)
		Adpcm_FrameEncode((const int16_t *)&_Stream_Buf[_AMIC_Controller.outputIdx][0], (void *)_ADPCM_Stream_Buf, ADC_SAMPLE_BUF_LENGTH);
		#if  (UART_TRANSMIT_MODE & UART_TRANSMIT_DMA)
		HAL_UART_Transmit_DMA(&UART_Config2, (uint8_t *)&_ADPCM_Stream_Buf[0], ADC_ADPCM_BUF_LENGTH);
		#else
		HAL_UART_Transmit(&UART_Config2, (uint8_t *)&_ADPCM_Stream_Buf[0], ADC_ADPCM_BUF_LENGTH, 1000);
		#endif
		#endif

		//next output or transfer data
		_AMIC_Controller.outputIdx = (AMIC_SBUF_LIST_END == _AMIC_Controller.outputIdx) ? AMIC_SBUF_LIST_0 : (_AMIC_Controller.outputIdx + 1);

		if (false == BTN_IS_PRESS(BTN_IO)) {
			// HAL_ADC_Stop(&_AMIC_Controller.adcHandle);
			HAL_TIM_Base_Stop(&_AMIC_Controller.timHandle);
		}
	}
}
/******************************************************************************
 * Function:
 * PreCondition:
 * Input: @param  hadc: ADC handle
 * Output:
 * Return: @retval None
 * Side Effects:
 * Overview: @brief  DMA Conversion complete callback in non blocking mode
 * Note:
 ******************************************************************************/
static void _AMIC_ConvCplt_Callback(ADC_HandleTypeDef *hadc)
{
	_AMIC_Controller.sampleCnt++;
	// next register next adc sample
	_AMIC_Controller.sampleIdx = (AMIC_SBUF_LIST_END == _AMIC_Controller.sampleIdx) ? AMIC_SBUF_LIST_0 : (_AMIC_Controller.sampleIdx + 1);

	HAL_ADC_Start_DMA(hadc, (uint16_t *)&_Stream_Buf[_AMIC_Controller.sampleIdx][0], ADC_SAMPLE_BUF_LENGTH, _AMIC_ConvCplt_Callback);
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
static void _AMIC_ExtChannel_Init(ADC_HandleTypeDef *hadc, void (*Callback)(ADC_HandleTypeDef* hadc), bool isStart)
{
	if (HAL_OK == HAL_ADC_Init(hadc)) {

		/* Configure Regular Channel */
		ADC_ChannelConfTypeDef sConfig = {
			.Channel  = ADC_CHANNEL_1,
			.Rank         = ADC_REGULAR_RANK_1,
			.SamplingTime = ADC_SAMPLETIME_15CYCLES
		};

		if (HAL_OK == HAL_ADC_ConfigChannel(hadc, &sConfig)) {
			_AMIC_Sample_Channel_Enable(sConfig.Channel);

			if (ADC_PIS_TRIG == hadc->Init.TrigType) {
				HAL_PIS_Config(ADC_PIS_CHANNEL, GPTIMC1_ADCTRIG, ADC_REG_TRIG, PIS_SYNC_DIRECT, PIS_EDGE_NONE);
			}

			HAL_ADC_Start_DMA(hadc, (uint16_t *)&_Stream_Buf[AMIC_SBUF_LIST_0][0], ADC_SAMPLE_BUF_LENGTH, Callback);

			if (isStart) {
				HAL_ADC_Start(hadc);
			}
			else {
				HAL_ADC_Stop(hadc);
			}
		}
	}
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
static void _AMIC_Timer_Init(TIM_HandleTypeDef *TimHandle, bool isStart)
{
	HAL_TIM_Init(TimHandle);

	if (isStart) {
		HAL_TIM_Base_Start(TimHandle);
	}
	else {
		HAL_TIM_Base_Stop(TimHandle);
	}
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
static bool _AMIC_Uart_Init(UART_HandleTypeDef *huart, uint8_t txd, uint8_t rxd, bool isRxPullup)
{
	switch ((uint32_t)huart->UARTX) {
		case (uint32_t)UART1: pinmux_uart1_init(txd, rxd); break;
		case (uint32_t)UART2: pinmux_uart2_init(txd, rxd); break;
		case (uint32_t)UART3: pinmux_uart3_init(txd, rxd); break;
	}

	if (isRxPullup) {
		io_pull_write(rxd, IO_PULL_UP);
	}
	return (HAL_OK == HAL_UART_Init(huart));
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
static void _AMIC_Sample_Channel_Enable(uint32_t channel)
{
	switch (channel) {
		case ADC_CHANNEL_0: pinmux_adc12b_in0_init(); break;
		case ADC_CHANNEL_1: pinmux_adc12b_in1_init(); break;
		case ADC_CHANNEL_2: pinmux_adc12b_in2_init(); break;
		case ADC_CHANNEL_3: pinmux_adc12b_in3_init(); break;
		case ADC_CHANNEL_4: pinmux_adc12b_in4_init(); break;
		case ADC_CHANNEL_5: pinmux_adc12b_in5_init(); break;
		case ADC_CHANNEL_6: pinmux_adc12b_in6_init(); break;
		case ADC_CHANNEL_7: pinmux_adc12b_in7_init(); break;
		case ADC_CHANNEL_8: pinmux_adc12b_in8_init(); break;
		default:
			break;
	}
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
void io_exti_callback(uint8_t pin,exti_edge_t edge)
{
	switch (pin) {
		case BTN_IO:
			// HAL_ADC_Start(&_AMIC_Controller.adcHandle);
			HAL_TIM_Base_Start(&_AMIC_Controller.timHandle);
			break;
		default:
			break;
	}
}
/*******************************************************************************
 End of File
 ******************************************************************************/
