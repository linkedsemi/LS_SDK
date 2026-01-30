#include "ls_hal_flash.h"
#include "hal_flash_int.h"
#include "compile_flag.h"

extern struct hal_flash_env flash1;

void XIP_BANNED_FUNC(hal_flash_init){hal_flashx_init(&flash1);}

void XIP_BANNED_FUNC(hal_flash_continuous_mode_start){hal_flashx_continuous_mode_start(&flash1);}

void XIP_BANNED_FUNC(hal_flash_continuous_mode_stop){hal_flashx_continuous_mode_stop(&flash1);}

void XIP_BANNED_FUNC(hal_flash_read_status_register_0_ram,uint8_t *status_reg_0){hal_flashx_read_status_register_0_ram(&flash1,status_reg_0);}

void XIP_BANNED_FUNC(hal_flash_read_status_register_0,uint8_t *status_reg_0){hal_flashx_read_status_register_0(&flash1,status_reg_0);}

void XIP_BANNED_FUNC(hal_flash_read_status_register_1_ram,uint8_t *status_reg_1){hal_flashx_read_status_register_1_ram(&flash1,status_reg_1);}

void XIP_BANNED_FUNC(hal_flash_read_status_register_1,uint8_t *status_reg_1){hal_flashx_read_status_register_1(&flash1,status_reg_1);}

bool XIP_BANNED_FUNC(hal_flash_write_in_process){return hal_flashx_write_in_process(&flash1);}

void FLASH_API_SECTION(hal_flash_write_status_register,uint16_t status){hal_flashx_write_status_register(&flash1,status);}

void FLASH_API_SECTION(hal_flash_multi_io_page_program,uint32_t offset,uint8_t *data,uint16_t length){hal_flashx_multi_io_page_program(&flash1,offset,data,length);}

void FLASH_API_SECTION(hal_flash_dual_page_program,uint32_t offset,uint8_t *data,uint16_t length){hal_flashx_dual_page_program(&flash1,offset,data,length);}

void FLASH_API_SECTION(hal_flash_quad_page_program,uint32_t offset,uint8_t *data,uint16_t length){hal_flashx_quad_page_program(&flash1,offset,data,length);}

void FLASH_API_SECTION(hal_flash_page_program,uint32_t offset,uint8_t *data,uint16_t length){hal_flashx_page_program(&flash1,offset,data,length);}

void FLASH_API_SECTION(hal_flash_page_erase,uint32_t offset){hal_flashx_page_erase(&flash1,offset);}

void FLASH_API_SECTION(hal_flash_sector_erase,uint32_t offset){hal_flashx_sector_erase(&flash1,offset);}

void FLASH_API_SECTION(hal_flash_block_32K_erase,uint32_t offset){hal_flashx_block_32K_erase(&flash1,offset);}

void FLASH_API_SECTION(hal_flash_block_64K_erase,uint32_t offset){hal_flashx_block_64K_erase(&flash1,offset);}

void FLASH_API_SECTION(hal_flash_chip_erase){hal_flashx_chip_erase(&flash1);}

void FLASH_API_SECTION(hal_flash_multi_io_read,uint32_t offset,uint8_t *data,uint32_t length){hal_flashx_multi_io_read(&flash1,offset,data,length);}

void FLASH_API_SECTION(hal_flash_dual_io_read,uint32_t offset,uint8_t *data,uint32_t length){hal_flashx_dual_io_read(&flash1,offset,data,length);}

void FLASH_API_SECTION(hal_flash_quad_io_read,uint32_t offset,uint8_t *data,uint32_t length){hal_flashx_quad_io_read(&flash1,offset,data,length);}

void FLASH_API_SECTION(hal_flash_fast_read,uint32_t offset,uint8_t *data,uint32_t length){hal_flashx_fast_read(&flash1,offset,data,length);}

void FLASH_API_SECTION(hal_flash_read_sfdp,uint32_t offset,uint8_t *data,uint32_t length){hal_flashx_read_sfdp(&flash1,offset,data,length);}

void XIP_BANNED_FUNC(hal_flash_deep_power_down){hal_flashx_deep_power_down(&flash1);}

void XIP_BANNED_FUNC(hal_flash_release_from_deep_power_down){hal_flashx_release_from_deep_power_down(&flash1);}

void FLASH_API_SECTION(hal_flash_read_id,uint8_t jedec_id[3]){hal_flashx_read_id(&flash1,jedec_id);}

void FLASH_API_SECTION(hal_flash_read_unique_id,uint8_t unique_serial_id[16]){hal_flashx_read_unique_id(&flash1,unique_serial_id);}

void FLASH_API_SECTION(hal_flash_erase_security_area,uint8_t idx){hal_flashx_erase_security_area(&flash1,idx);}

void FLASH_API_SECTION(hal_flash_program_security_area,uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length){hal_flashx_program_security_area(&flash1,idx,addr,data,length);}

void FLASH_API_SECTION(hal_flash_read_security_area,uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length){hal_flashx_read_security_area(&flash1,idx,addr,data,length);}

void XIP_BANNED_FUNC(hal_flash_software_reset){hal_flashx_software_reset(&flash1);}

void FLASH_API_SECTION(hal_flash_qe_status_read_and_set,){hal_flashx_qe_status_read_and_set(&flash1);}

void XIP_BANNED_FUNC(hal_flash_prog_erase_suspend){hal_flashx_prog_erase_suspend(&flash1);}

void XIP_BANNED_FUNC(hal_flash_prog_erase_resume){hal_flashx_prog_erase_resume(&flash1);}

uint32_t FLASH_API_SECTION(hal_flash_total_size_get){return hal_flashx_total_size_get(&flash1);}

void XIP_BANNED_FUNC(hal_flash_continuous_mode_reset){hal_flashx_continuous_mode_reset(&flash1);}

void XIP_BANNED_FUNC(hal_flash_prog_erase_suspend_isr){hal_flashx_prog_erase_suspend_isr(&flash1);}

void XIP_BANNED_FUNC(hal_flash_prog_erase_resume_isr){hal_flashx_prog_erase_resume_isr(&flash1);}