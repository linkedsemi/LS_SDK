#ifndef LSSSI_H_
#define LSSSI_H_
#include "reg_ssi_type.h"
#include "reg_base_addr.h"
#include "HAL_def.h"
#include "ssi_misc.h"

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup LSSSI
 *  @{
 */

#ifdef LSSSI_BASE_ADDR
/// LSSSI Macro for Register Access
#define LSSSI ((reg_ssi_t *)LSSSI_BASE_ADDR)
#endif

/// Data Frame Size enumeration
enum Data_Frame_Size{
	DFS_32_4_bits = 3,
	DFS_32_5_bits ,
	DFS_32_6_bits ,
	DFS_32_7_bits ,
	DFS_32_8_bits ,
	DFS_32_9_bits ,
	DFS_32_10_bits ,
	DFS_32_11_bits ,
	DFS_32_12_bits ,
	DFS_32_13_bits ,
	DFS_32_14_bits ,
	DFS_32_15_bits ,
	DFS_32_16_bits ,
	DFS_32_17_bits ,
	DFS_32_18_bits ,
	DFS_32_19_bits ,
	DFS_32_20_bits ,
	DFS_32_21_bits ,
	DFS_32_22_bits ,
	DFS_32_23_bits ,
	DFS_32_24_bits ,
	DFS_32_25_bits ,
	DFS_32_26_bits ,
	DFS_32_27_bits ,
	DFS_32_28_bits ,
	DFS_32_29_bits ,
	DFS_32_30_bits ,
	DFS_32_31_bits ,
	DFS_32_32_bits 
};

/// Control Frame Size enumeration
enum Control_Frame_Size{
	Control_Word_1_bit = 0,
	Control_Word_2_bit ,
	Control_Word_3_bit ,
	Control_Word_4_bit ,
	Control_Word_5_bit ,
	Control_Word_6_bit ,
	Control_Word_7_bit ,
	Control_Word_8_bit ,
	Control_Word_9_bit ,
	Control_Word_10_bit ,
	Control_Word_11_bit ,
	Control_Word_12_bit ,
	Control_Word_13_bit ,
	Control_Word_14_bit ,
	Control_Word_15_bit ,
	Control_Word_16_bit ,
};

/// Clock Phase enumeration
enum Clock_Phase{
	Inactive_Low = 0,
	Inactive_High
};

/// Clock Polarity enumeration
enum Clock_Polarity{
	SCLK_Toggle_In_Middle = 0,
	SCLK_Toggle_At_Start
};

/// Frame Format enumeration
enum Frame_Format{
	Motorola_SPI = 0,
	Texas_Instruments_SSP,
	National_Semiconductors_Microwire,
};

/// SSI DMA TX RX Environment
struct SSI_DMA_Env
{
    uint8_t DMA_Channel;
};

/// SSI Interrupt TX RX Environment
struct SSI_Interrupt_Env
{
    uint8_t *Data;
    uint16_t Count;
};

/// SSI Control Structure 
struct ssi_ctrl{
    uint32_t reserved0:4, 
            frame_format:2,   /**< ::Frame_Format */
            cph:1,            /**< ::Clock_Phase */
            cpol:1,           /**< ::Clock_Polarity */
            reserved1:4,
            control_frame_size:4, /**< ::Control_Frame_Size */
            data_frame_size:5;    /**< ::Data_Frame_Size */
};

/// SSI Initialization Parameters Typedef
typedef struct __SSI_InitTypeDef
{
    struct ssi_ctrl ctrl;  /**< Control Parameters */
    uint16_t clk_div;      /**< Clock Dividing Coefficient */
    uint8_t rxsample_dly;  /**< RX Sampling Delay */
}SSI_InitTypeDef;

/// SSI Handle Typedef
typedef struct __SSI_HandleTypeDef
{
    reg_ssi_t *REG;              /**< Register Base Pointer */
    SSI_InitTypeDef Init;       /**< Initialization Parameters */
    void *DMAC_Instance;        /**< DMA Controller Handle Pointer */
    union{
        struct SSI_DMA_Env DMA;     /**< DMA Env */
        struct SSI_Interrupt_Env Interrupt; /**< Interrupt Env */
    }Tx_Env,Rx_Env;            /**< Tx Rx Environment */
    uint8_t Hardware_CS_Mask;  /**< Hardware CS Bit Mask, 0 for Software CS */
}SSI_HandleTypeDef;

/** \brief SSI Initialize 
 *  \return Status 
 */
HAL_StatusTypeDef HAL_SSI_Init(SSI_HandleTypeDef *hssi);

/** \brief SSI De-Initialize 
 *  \return Status 
 */
HAL_StatusTypeDef HAL_SSI_Deinit(SSI_HandleTypeDef *hssi);

/** \brief SSI Transmit (Interrupt Mode)
 *  \param[in] hssi Handle of SSI
 *  \param[in] Data Buffer pointer for TX
 *  \param[in] Count Number of data frame in units of ::Data_Frame_Size
 *  \return Status
 */
HAL_StatusTypeDef HAL_SSI_Transmit_IT(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count);

/** Callback function that will be invoked in the interrupt context when SSI TX (Interrupt Mode) is complete
 *  Overwrite this function to get notification of completion of SSI TX.
 *  \param hssi Handle of SSI
 */
void HAL_SSI_TxCpltCallback(SSI_HandleTypeDef *hssi);

/** \brief SSI Receive (Interrupt Mode)
 *  \param[in] hssi Handle of SSI
 *  \param[out] Data Buffer pointer for RX
 *  \param[in] Count Number of data frame in units of ::Data_Frame_Size
 *  \return Status
 */
HAL_StatusTypeDef HAL_SSI_Receive_IT(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count);

/** Callback function that will be invoked in the interrupt context when SSI RX (Interrupt Mode) is complete
 *  Overwrite this function to get notification of completion of SSI RX.
 *  \param hssi Handle of SSI
 */
void HAL_SSI_RxCpltCallback(SSI_HandleTypeDef *hssi);

/** \brief SSI TransmitReceive (Interrupt Mode)
 *  \param[in] hssi Handle of SSI
 *  \param[in] TX_Data Buffer pointer for TX
 *  \param[out] RX_Data Buffer pointer for RX
 *  \param[in] Count Number of data frame in units of ::Data_Frame_Size
 *  \return Status
 */
HAL_StatusTypeDef HAL_SSI_TransmitReceive_IT(SSI_HandleTypeDef *hssi,void *TX_Data,void *RX_Data,uint16_t Count);

/** Callback function that will be invoked in the interrupt context when SSI TXRX (Interrupt Mode) is complete
 *  Overwrite this function to get notification of completion of SSI TXRX.
 *  \param hssi Handle of SSI
 */
void HAL_SSI_TxRxCpltCallback(SSI_HandleTypeDef *hssi);

/** \brief SSI Transmit (DMA Mode)
 *  \param[in] hssi Handle of SSI
 *  \param[in] Data Buffer pointer for TX
 *  \param[in] Count Number of data frame in units of ::Data_Frame_Size
 *  \return Status
 */
HAL_StatusTypeDef HAL_SSI_Transmit_DMA(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count);

/** Callback function that will be invoked in the interrupt context when SSI TX (DMA Mode) is complete
 *  Overwrite this function to get notification of completion of SSI TX.
 *  \param hssi
 */
void HAL_SSI_TxDMACpltCallback(SSI_HandleTypeDef *hssi);

/** \brief SSI Receive (DMA Mode)
 *  \param[in] hssi Handle of SSI
 *  \param[out] Data Buffer pointer for RX
 *  \param[in] Count Number of data frame in units of ::Data_Frame_Size
 *  \return Status
 */
HAL_StatusTypeDef HAL_SSI_Receive_DMA(SSI_HandleTypeDef *hssi,void *Data,uint16_t Count);

/** Callback function that will be invoked in the interrupt context when SSI RX (DMA Mode) is complete
 *  Overwrite this function to get notification of completion of SSI RX.
 *  \param hssi Handle of SSI
 */
void HAL_SSI_RxDMACpltCallback(SSI_HandleTypeDef *hssi);

/** \brief SSI TransmitReceive (Interrupt Mode)
 *  \param[in] hssi Handle of SSI
 *  \param[in] TX_Data Buffer pointer for TX
 *  \param[out] RX_Data Buffer pointer for RX
 *  \param[in] Count Number of data frame in units of ::Data_Frame_Size
 *  \return Status
 */
HAL_StatusTypeDef HAL_SSI_TransmitReceive_DMA(SSI_HandleTypeDef *hssi,void *TX_Data,void *RX_Data,uint16_t Count);

/** Callback function that will be invoked in the interrupt context when SSI TXRX (DMA Mode) is complete
 *  Overwrite this function to get notification of completion of SSI TXRX.
 *  \param hssi Handle of SSI
 */
void HAL_SSI_TxRxDMACpltCallback(SSI_HandleTypeDef *hssi);

void HAL_SSI_IRQHandler(SSI_HandleTypeDef *hssi);

/** @}*/


/** @}*/

#endif
