#ifndef SSI_MISC_H_
#define SSI_MISC_H_

typedef enum{
	Standard_SPI_Format = 0,
	Dual_SPI_Format = 1,
	Quad_SPI_Format = 2,
}CTRLR0_SPI_FRF_FIELD;

typedef enum{
	Normal_Mode_Operation = 0,
	Test_Mode_Operation
}CTRLR0_SRL_FIELD;

typedef enum{
	Slave_txd_Enabled = 0,
	Slave_txd_Disabled
}CTRLR0_SLV_OE_FIELD;

typedef enum{
	Transmit_and_Receive = 0,
	Transmit_Only,
	Receive_Only,
	EEPROM_Read
}CTRLR0_TMOD_FIELD;

typedef enum{
	Handshaking_Interface_Disabled = 0,
	Handshaking_Interface_Enabled
}MWCR_MHS_FIELD;

typedef enum{
	Microwire_Receive = 0,
	Microwire_Transmit
}MWCR_MDD_FIELD;

typedef enum{
	Non_Sequential_Transfer = 0,
	Sequential_Transfer
}MWCR_MWMOD_FIELD;

typedef enum
{
	SSI_Disabled = 0,
	SSI_Enabled
}SSIENR_SSI_EN_FIELD;

typedef enum
{
	No_Transmit_Data_Collision_Error = 0,
	Transmit_Data_Collision_Error
}SR_DCOL_FIELD;

typedef enum
{
	No_Transmission_Error = 0,
	Transmission_Error
}SR_TXE_FIELD;

typedef enum
{
	Receive_FIFO_Not_Full = 0,
	Receive_FIFO_Full
}SR_RFF_FIELD;

typedef enum
{
	Receive_FIFO_Empty = 0,
	Receive_FIFO_Not_Empty
}SR_RFNE_FIELD;

typedef enum
{
	Transmit_FIFO_Not_Empty = 0,
	Transmit_FIFO_Empty
}SR_TFE_FIELD;

typedef enum
{
	Transmit_FIFO_Full = 0,
	Transmit_FIFO_Not_Full
}SR_TFNF_FIELD;

typedef enum
{
	SSI_Idle_or_Disabled = 0,
	SSI_Busy
}SR_BUSY_FIELD;

typedef enum
{
	Multi_Master_Con_Interrupt_Disable = 0,
	Multi_Master_Con_Interrupt_Enable
}IMR_MSTIM_MASK;

typedef enum
{
	Receive_FIFO_Full_Disable = 0,
	Receive_FIFO_Full_Enable
}IMR_RXFIM_MASK;

typedef enum
{
	Receive_FIFO_OverFlow_Disable = 0,
	Receive_FIFO_OverFlow_Enable
}IMR_RXOIM_MASK;

typedef enum
{
	Receive_FIFO_UnderFlow_Disable = 0,
	Receive_FIFO_UnderFlow_Enable
}IMR_RXUIM_MASK;

typedef enum
{
	Transmit_FIFO_OverFlow_Disable = 0,
	Transmit_FIFO_OverFlow_Enable
}IMR_TXOIM_MASK;

typedef enum
{
	Transmit_FIFO_Empty_Disable = 0,
	Transmit_FIFO_Empty_Enable
}IMR_TXEIM_MASK;	

typedef enum
{
	Transmit_DMA_Disabled = 0,
	Transmit_DMA_Enabled
}DMACR_TDMAE_FIELD;

typedef enum
{
	Receive_DMA_Disabled = 0,
	Receive_DMA_Enabled
}DMACR_RDMAE_FIELD;

typedef enum
{
	Instruction_Length_0_bit = 0,
	Instruction_Length_4_bits,
	Instruction_Length_8_bits,
	Instruction_Length_16_bits,
}SPI_CTRLR0_INST_L_FIELD;

typedef enum
{
	Addr_Width_0_bit = 0,
	Addr_Width_4_bits,
	Addr_Width_8_bits,
	Addr_Width_12_bits,
	Addr_Width_16_bits,
	Addr_Width_20_bits,
	Addr_Width_24_bits,
	Addr_Width_28_bits,
	Addr_Width_32_bits,
	Addr_Width_36_bits,
	Addr_Width_40_bits,
	Addr_Width_44_bits,
	Addr_Width_48_bits,
	Addr_Width_52_bits,
	Addr_Width_56_bits,
	Addr_Width_60_bits
}SPI_CTRLR0_ADDR_L_FIELD;

typedef enum
{
	Both_Standard_SPI_Mode = 0,
	Instruction_Standard_Address_Specific,
	Both_Specific_Mode,
}SPI_CTRLR0_TRANS_TYPE_FIELD;

#endif
