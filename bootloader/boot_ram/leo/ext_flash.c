#include <string.h>
#include "ext_flash.h"
#include "ls_hal_ssi.h"
#define READ_ID_OPCODE 0x9f
#define STD_READ_OPCODE 0x03
#define EX4B_OPCODE 0xe9
#define WRITE_EXT_ADDR_REG_OPCODE 0xc5
SSI_HandleTypeDef ssi_inst;
bool ext_address_reg_exist;

void ext_flash_driver_init(void)
{
    ssi_inst.REG = LSSSI;
    ssi_inst.Init.ctrl.reserved0 = 0;
    ssi_inst.Init.ctrl.frame_format = Motorola_SPI;
    ssi_inst.Init.ctrl.cph = SCLK_Toggle_In_Middle;
    ssi_inst.Init.ctrl.cpol = Inactive_Low;
    ssi_inst.Init.ctrl.reserved1 = 0;
    ssi_inst.Init.ctrl.control_frame_size = 0;
    ssi_inst.Init.ctrl.data_frame_size = DFS_32_32_bits;
    ssi_inst.Init.clk_div = 2;
    ssi_inst.Init.rxsample_dly = 0;
    HAL_SSI_Init(&ssi_inst);
}

void ext_flash_read_id(uint8_t jedec_id[3])
{
    ssi_inst.Init.ctrl.data_frame_size = DFS_32_32_bits;
    HAL_SSI_Use_Reversed_Data_Reg(&ssi_inst,false);
    uint32_t wdata = READ_ID_OPCODE<<24;
    uint32_t rdata;
    HAL_SSI_TransmitReceive(&ssi_inst,&wdata,&rdata,1);
    jedec_id[0] = rdata >> 16 &0xff;
    jedec_id[1] = rdata >>8 & 0xff;
    jedec_id[2] = rdata & 0xff;
}

static void ext_flash_write_ext_addr_reg(uint8_t ext_addr)
{
    ssi_inst.Init.ctrl.data_frame_size = DFS_32_8_bits;
    HAL_SSI_Use_Reversed_Data_Reg(&ssi_inst,false);
    uint8_t data[2] = {WRITE_EXT_ADDR_REG_OPCODE,ext_addr};
    HAL_SSI_Transmit(&ssi_inst,data,sizeof(data));
}

static void ext_flash_read_24bit_addr(uint32_t offset,uint32_t *data,uint16_t length_by_word)
{
    ssi_inst.Init.ctrl.data_frame_size = DFS_32_32_bits;
    HAL_SSI_Use_Reversed_Data_Reg(&ssi_inst,true);
    uint32_t tx_data = STD_READ_OPCODE | (offset>>8&0xff00) | (offset<<8&0xff0000) | (offset<<24&0xff000000) ;
    HAL_SSI_TransmitReceive_HalfDuplex(&ssi_inst,&tx_data,1,data,length_by_word);
}

void ext_flash_read(uint32_t offset,uint32_t *data,uint16_t length_by_word)
{
    if(ext_address_reg_exist)
    {
        ext_flash_write_ext_addr_reg(offset>>24);
    }
    ext_flash_read_24bit_addr(offset,data,length_by_word);
}

static void ext_flash_exit_4_byte_address_mode()
{
    ssi_inst.Init.ctrl.data_frame_size = DFS_32_8_bits;
    HAL_SSI_Use_Reversed_Data_Reg(&ssi_inst,false);
    uint8_t opcode = EX4B_OPCODE;
    HAL_SSI_Transmit(&ssi_inst,&opcode,sizeof(opcode));
}

void ext_flash_addressing_mode_set(uint32_t flash_size)
{
    if(flash_size>1<<24)
    {
        ext_address_reg_exist = true;
        ext_flash_exit_4_byte_address_mode();
    }else
    {
        ext_address_reg_exist = false;
    }
}