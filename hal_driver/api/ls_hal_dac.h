#ifndef LS_HAL_DAC_H_
#define LS_HAL_DAC_H_
#include <stdbool.h>
#include "HAL_def.h"
#include "ls_msp_dac.h"

/**
 * @brief Select the DAC peripherals
 * 
 */
#define   DAC1                  0x00000001U
#define   DAC2                  0x00000002U
#define   DAC1AndDAC2           (DAC1|DAC2)

/**
 * @brief DAC_Channel_selection DAC Channel selection
 * 
 */
#define DAC_CHANNEL_1                      0x00000000U
#define DAC_CHANNEL_2                      0x00000010U
 
/**
 * @brief DAC noise/triangle wave generation 
 * 
 */
#define     No_Wave                 0x00000000U             /* wave generation disabled */
#define     Noise_Wave              0x00000001U             /* Noise wave generation enabled */
#define     Triangle_Wave           0x00000002U             /* Triangle wave generation enabled */

/**
 * @brief DAC channel trigger selection,These bits select the external event used to trigger.
 * 
 */
#define   BASE_TIMER_TRGO       0x00000000U
#define   GENERAL_TimerA_TRGO   0x00000001U
#define   GENERAL_TimerB_TRGO   0x00000002U
#define   GENERAL_TimerC_TRGO   0x00000003U
#define   ADVANCE_Timer1_TRGO   0x00000004U
#define   ADVANCE_Timer2_TRGO   0x00000005U
#define   PIP_OUTPUT_CHANNEL    0x00000006U
#define   SOFTWARE_TRIG         0x00000007U

/**
 * @brief Set the amplitude of the triangular wave
 * 
 */
#define   triangle_amplitude_1                  0x00000000U
#define   triangle_amplitude_3                  0x00000001U
#define   triangle_amplitude_7                  0x00000002U
#define   triangle_amplitude_15                 0x00000003U
#define   triangle_amplitude_31                 0x00000004U
#define   triangle_amplitude_63                 0x00000005U
#define   triangle_amplitude_127                0x00000006U
#define   triangle_amplitude_255                0x00000007U
#define   triangle_amplitude_511                0x00000008U
#define   triangle_amplitude_1023               0x00000009U
#define   triangle_amplitude_2047               0x0000000aU
#define   triangle_amplitude_4095               0x0000000bU

/** @defgroup DAC_data_alignment DAC data alignment
  * @{
  */
#define DAC1_ALIGN_12B_R                    0x00000000U
#define DAC1_ALIGN_12B_L                    0x00000004U
#define DAC1_ALIGN_8B_R                     0x00000008U

#define DAC2_ALIGN_12B_R                    0x00000000U
#define DAC2_ALIGN_12B_L                    0x00000004U
#define DAC2_ALIGN_8B_R                     0x00000008U

#define DAC12_ALIGN_12B_RD                  0x00000000U
#define DAC12_ALIGN_12B_LD                  0x00000004U
#define DAC12_ALIGN_8B_RD                   0x00000008U

#define IS_DAC12_ALIGN(ALIGN) (((ALIGN) == DAC1_ALIGN_12B_R) || \
                             ((ALIGN) == DAC1_ALIGN_12B_L) || \
                             ((ALIGN) == DAC1_ALIGN_8B_R)  || \
                             ((ALIGN) == DAC2_ALIGN_12B_R) || \
                             ((ALIGN) == DAC2_ALIGN_12B_L) || \
                             ((ALIGN) == DAC2_ALIGN_8B_R)  || \
                             ((ALIGN) == DAC12_ALIGN_12B_RD) || \
                             ((ALIGN) == DAC12_ALIGN_12B_LD) || \
                             ((ALIGN) == DAC12_ALIGN_8B_RD) )

#define IS_DAC12_DATA(DATA) ((DATA) <= 0xFFF0FFFUL)

/**
  * @brief  DAC DMA Environment 
  */
 struct __DAC_HandleTypeDef;
 struct DacDMAEnv
{
    void                          (*Callback)(struct __DAC_HandleTypeDef *);
    uint8_t                       DMA_Channel;
};

/**
  * @brief  DAC Interrupt Environment   
  */
struct DacInterruptEnv
{
    uint8_t                       *pBuffPtr;      /*!< Pointer to DAC data Buffer   */
    uint16_t                      XferCount;      /*!< UART DAC data Counter        */
};

 typedef struct __DAC_HandleTypeDef
 {
    reg_dac_t   *Instance;        /*!< Register base address */
    uint8_t     DACx;
    uint8_t     DAC1_Trigger;         /*!< trigger selection */
    uint8_t     DAC1_wave;            /*!< DAC noise/triangle wave generation */ 
    uint32_t    DAC1_Mamp;            /*!< Set the amplitude of the triangular wave */
    uint8_t     DAC2_Trigger;         
    uint8_t     DAC2_wave;            
    uint32_t    DAC2_Mamp;           
    void        *DMAC_Instance; 
    union{
        struct DacDMAEnv DMA;
        struct DacInterruptEnv Interrupt;
    }Env;
}DAC_HandleTypeDef;

/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_DAC_Init(DAC_HandleTypeDef *hdac);
HAL_StatusTypeDef HAL_DAC_DeInit(void);

/**
  * @brief  Stop DAC conversion, disable ADC peripheral.
  * @param  hadc: DAC handle.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_DAC_Stop(DAC_HandleTypeDef *hdac);

/**
 * @brief Set the specified data dac_dhrxx register value for DAC channel.
 * 
 * @param hdac DAC handle.
 * @param Alignment Specifies the data alignment.
 * @param Data Data to be loaded in the selected data dac_dhrxx register.
 * @return HAL status.
 */
HAL_StatusTypeDef HAL_DAC_SetValue(DAC_HandleTypeDef *hdac,uint32_t Alignment, uint32_t Data);

/**
 * @brief Returns the last data output value of the selected DAC channel.
 * @param hdac DAC handle.
 * @return uint32_t 
 */
uint32_t HAL_DAC_GetValue(DAC_HandleTypeDef *hdac);

/**
 * @brief Enables DAC and starts conversion of channel.
 * @param hdac DAC handle.
 * @param Alignment Specifies the data alignment.
 * @param pData The source Buffer address.
 * @param Length The length of data to be transferred from memory to DAC peripheral.
 * @param Callback function pointer.
 * @return HAL status
 */
HAL_StatusTypeDef HAL_DAC_Start_DMA(DAC_HandleTypeDef* hdac, uint32_t Alignment, const uint32_t* pData, uint32_t Length,void (*Callback)(DAC_HandleTypeDef* hdac));

/**
 * @brief 
 * @param hdac DAC handle.
 * @return HAL status.
 */

/**
 * @brief Stop ADC conversion,disable ADC DMA transfer, disable ADC peripheral.
 *
 * @param hdac DAC handle.
 * @param Channel The selected DAC channel.
 *          This parameter can be one of the following values:
 *            @arg DAC_CHANNEL_1: DAC1 selected
 *            @arg DAC_CHANNEL_2: DAC2 selected
 * @return HAL status
 */
HAL_StatusTypeDef HAL_DAC_Stop_DMA(DAC_HandleTypeDef* hdac,uint32_t Channel);
#endif