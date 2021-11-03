#ifndef LSPDM_H_
#define LSPDM_H_
#include <stdbool.h>
#include "reg_pdm_type.h"
#include "reg_base_addr.h"
#include "HAL_def.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSPDM
 *  @{
 */

/// LSPDM Macro for Register Access
#define LSPDM ((reg_pdm_t *)LSPDM_BASE_ADDR)

extern const uint32_t fir_coef_8khz[64];
///Select the PDM filter controller at a sampling rate of 8kHz
#define PDM_FIR_COEF_8KHZ ((const struct pdm_fir *)fir_coef_8khz)

extern const uint32_t fir_coef_16khz[64];
///Select the PDM filter controller at a sampling rate of 16kHz
#define PDM_FIR_COEF_16KHZ ((const struct pdm_fir *)fir_coef_16khz)

/**
  * \brief Calculate the PDM clock rate value
  * \param[in] kHz: Set the PDM clock rate value    Unit: khz
  * \note eg: if pdm clock is 1.024MHz, configure khz is 1024.
  */
#define PDM_CLK_RATIO(kHz) (128000/(kHz) - 1)

/**
  * \brief Calculate the PDM sample rate value
  * \param[in] Clk_kHz: Set the PDM clock rate value    Unit: khz
  * \param[in] Sample_Rate_Hz: Set the PDM sample rate value    Unit: hz
  * @note eg: if pdm sample rare is 16KHz and pdm clock is 1.024MHz, configure the Clk_kHz is 1024, configure the Sample_Rate_Hz is 16000.
  */
#define PDM_SAMPLE_RATE(Clk_kHz,Sample_Rate_Hz) ((Clk_kHz)*1000/(Sample_Rate_Hz) - 1)

/// PDM mode selection enumeration typedef
typedef enum __PDM_MODE_TypeDef
{
    PDM_MODE_Mono = 0,
    PDM_MODE_Stereo = 1
} PDM_MODE_TypeDef;

/// PDM Configuration Parameters Typedef
typedef struct __PDM_CFG_TypeDef
{
    uint8_t clk_ratio;      /**< ::PDM_CLK_RATIO */
    uint8_t cap_delay;      /**< Configure the value of the PDM capture delay.  data capture after this value cycles of 128Mhz */
    uint8_t sample_rate;    /**< ::PDM_SAMPLE_RATE */
    uint8_t data_gain:4;    /**< Configuration the value of the PDM gain adjustment */
} PDM_CFG_TypeDef;

/// PDM Initialization Parameters Typedef
typedef struct __PDM_Init_TypeDef
{
    const struct pdm_fir *fir;  /**< Select the PDM filter controller */
    PDM_CFG_TypeDef cfg;        /**< ::PDM_CFG_TypeDef */
    PDM_MODE_TypeDef mode;      /**< ::PDM_MODE_TypeDef */
} PDM_Init_TypeDef;

 /// PDM DMA Environment
struct PDM_DMA_Env
{
    uint32_t PingPong_Ctrl_Data;    /**< Configuration the data control register for DMA ping-pong mode */
    uint8_t Channel[2];             /**< Configure the number of DMA channels */
    bool Channel_Done[2];           /**< DMA channel completion flag */
};

/// PDM Interrupt Environment
struct PDM_Interrupt_Env
{
    uint16_t *pFrameBuffer[2];  /**< An pointer array to accept PDM data */
    uint16_t FrameNum;          /**< Configure the size to accept PDM data */
};

/// PDM PingPong Buffer Pointer Structure 
struct PDM_PingPong_Bufptr
{
    uint16_t *Bufptr[2];    /**< Configure the pointer array to accept PDM data */
};

 /// PDM Handle Typedef
typedef struct __PDM_HandleTypeDef
{
    reg_pdm_t *Instance;                        /**< PDM registers base address */
    void *DMAC_Instance;                        /**< Select the initialized DMA object */
    union{
        struct PDM_DMA_Env DMA;  /**< DMA Env */
        struct PDM_Interrupt_Env Interrupt; /**< Interrupt Env */
    }Env;/**< Select Environment: DMA or Interrupt Environment */
} PDM_HandleTypeDef;

/** \brief PDM Initialize 
 *  \param[in] hpdm Handle of PDM
 *  \param[in] Init Initialization Parameters
 *  \return Status
 */
HAL_StatusTypeDef HAL_PDM_Init(PDM_HandleTypeDef *hpdm,PDM_Init_TypeDef *Init);

 /** \brief PDM DeInitialize 
 *   \param[in] hpdm Handle of PDM
 *   \return Status
 */
HAL_StatusTypeDef HAL_PDM_DeInit(PDM_HandleTypeDef *hpdm);

 /** \brief PDM Transfer Data Configuration (Interrupt Mode)
 *   \param[in] hpdm Handle of PDM
 *   \param[in] pFrameBuffer0 The Buffer pointer to accept PDM data
 *   \param[in] pFrameBuffer1 The Buffer pointer to accept PDM data in stereo mode. Other mode is NULL.
 *   \param[in] FrameNum Accept the size of PDM data 
 *   \return Status
 */
HAL_StatusTypeDef HAL_PDM_Transfer_Config_IT(PDM_HandleTypeDef *hpdm,uint16_t *pFrameBuffer0,uint16_t *pFrameBuffer1,uint16_t FrameNum);

 /** Callback function that will be invoked in the interrupt context when PDM Transfer (Interrupt Mode) is complete
 *  \param hpdm Handle of PDM
 */
void HAL_PDM_CpltCallback(PDM_HandleTypeDef *hpdm);

 /** \brief PDM Transfer Data Configuration (DMA Mode)
 *   \param[in] hpdm Handle of PDM
 *   \param[in] pFrameBuffer0 The Buffer pointer to accept PDM data
 *   \param[in] pFrameBuffer1 The Buffer pointer to accept PDM data in stereo mode. Other mode is NULL.
 *   \param[in] FrameNum Accept the size of PDM data 
 *   \return Status
 */
HAL_StatusTypeDef HAL_PDM_Transfer_Config_DMA(PDM_HandleTypeDef *hpdm,uint16_t *pFrameBuffer0,uint16_t *pFrameBuffer1,uint16_t FrameNum);

/** \brief PDM Transfer Data Configuration (DMA PingPong Mode)
 *   \param[in] hpdm Handle of PDM
 *   \param[in] CH0_Buf The Buffer pointer to accept PDM data ::PDM_PingPong_Bufptr
 *   \param[in] CH1_Buf The Buffer pointer to accept PDM data in stereo mode. Other mode is NULL. ::PDM_PingPong_Bufptr
 *   \param[in] FrameNum Accept the size of PDM data 
 *   \return Status
 */
HAL_StatusTypeDef HAL_PDM_PingPong_Transfer_Config_DMA(PDM_HandleTypeDef *hpdm,struct PDM_PingPong_Bufptr *CH0_Buf,struct PDM_PingPong_Bufptr *CH1_Buf,uint16_t FrameNum);

/** Callback function that will be invoked in the interrupt context when PDM Transfer (DMA Mode) is complete
 *  \param hpdm Handle of PDM
 *  \param buf_idx Transfer data to complete IDX
 */
void HAL_PDM_DMA_CpltCallback(PDM_HandleTypeDef *hpdm,uint8_t buf_idx);

/** PDM peripheral start working
 *  \param[in] hpdm Handle of PDM
 */
HAL_StatusTypeDef HAL_PDM_Start(PDM_HandleTypeDef *hpdm);

/** PDM peripheral stop working
 *  \param[in] hpdm Handle of PDM
 */
HAL_StatusTypeDef HAL_PDM_Stop(PDM_HandleTypeDef *hpdm);

/** PDM interrupt handler function
 *  \param[in] hpdm Handle of PDM
 */
void HAL_PDM_IRQHandler(PDM_HandleTypeDef *hpdm);

/** @}*/


/** @}*/
#endif
