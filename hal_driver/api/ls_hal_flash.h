#ifndef LS_HAL_FLASH_H_
#define LS_HAL_FLASH_H_
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup SPI_FLASH
 *  @{
 */

struct hal_flash_env
{
    void *reg;
    bool dual_mode_only;
    bool continuous_mode_enable;
    bool writing;
    uint8_t suspend_count;
    bool continuous_mode_on;
    bool addr4b;
};

extern struct hal_flash_env flash1;

/// Flash Page Size
#define FLASH_PAGE_SIZE (256) 
/// Flash Sector Size
#define FLASH_SECTOR_SIZE (0x1000) 
/// Status Register 1 SUS1 Mask
#define STATUS_REG1_SUS1_MASK (0x80)
/// Status Register 1 SUS2 Mask
#define STATUS_REG1_SUS2_MASK (0x04)

/** \brief Initialize SPI Flash driver */
void hal_flashx_init(struct hal_flash_env *env);

/** \brief Enter SPI Flash continuous mode */
void hal_flashx_continuous_mode_start(struct hal_flash_env *env);

/** \brief Exit SPI Flash continuous mode */
void hal_flashx_continuous_mode_stop(struct hal_flash_env *env);

/** \brief Read Status Register 0 (can't be called during XIP)
 *  \param[in] env
 *  \param[out] status_reg_0
 */
void hal_flashx_read_status_register_0_ram(struct hal_flash_env *env,uint8_t *status_reg_0);

/** \brief Read Status Register 0
 *  \param[in] env
 *  \param[out] status_reg_0
 */
void hal_flashx_read_status_register_0(struct hal_flash_env *env,uint8_t *status_reg_0);

/** \brief Read Status Register 1 (can't be called during XIP) 
 *  \param[in] env
 *  \param[out] status_reg_1
 */
void hal_flashx_read_status_register_1_ram(struct hal_flash_env *env,uint8_t *status_reg_1);

/** \brief Read Status Register 1
 *  \param[in] env
 *  \param[out] status_reg_1
 */
void hal_flashx_read_status_register_1(struct hal_flash_env *env,uint8_t *status_reg_1);

/** \brief Check WIP Status
 *  \param[in] env
 *  \return WIP status
 */
bool hal_flashx_write_in_process(struct hal_flash_env *env);

/** \brief Write Status Register 
 *  \param[in] env
 *  \param[in] status The value to write to Status Register
 */
void hal_flashx_write_status_register(struct hal_flash_env *env,uint16_t status);

void hal_flashx_multi_io_page_program(struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint16_t length);

void hal_flashx_dual_page_program(struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint16_t length);

/** \brief Quad Page Program 
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset to FLASH_BASE_ADDR
 *  \param[in] data The pointer of the data to program into Flash
 *  \param[in] length Data length in bytes, must be less than or equal to FLASH_PAGE_SIZE
 */
void hal_flashx_quad_page_program(struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint16_t length);

/** \brief Page Program 
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset to FLASH_BASE_ADDR
 *  \param[in] data The pointer of the data to program into Flash
 *  \param[in] length Data length in bytes, must be less than or equal to FLASH_PAGE_SIZE
 */
void hal_flashx_page_program(struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint16_t length);

/** \brief Page Erase 
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset to FLASH_BASE_ADDR
 */
void hal_flashx_page_erase(struct hal_flash_env *env,uint32_t offset);

/** \brief Sector Erase
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset to FLASH_BASE_ADDR
 */
void hal_flashx_sector_erase(struct hal_flash_env *env,uint32_t offset);


/** \brief 32K block Erase 
 *  \note 擦除需要按照32k的块对齐。
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset to FLASH_BASE_ADDR
 */
void hal_flashx_block_32K_erase(struct hal_flash_env *env,uint32_t offset);

/** \brief 64K block Erase
 *  \note 擦除需要按照64k的块对齐。
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset to FLASH_BASE_ADDR
 */
void hal_flashx_block_64K_erase(struct hal_flash_env *env,uint32_t offset);

/** \brief Chip Erase */
void hal_flashx_chip_erase(struct hal_flash_env *env);

void hal_flashx_multi_io_read(struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint32_t length);

void hal_flashx_dual_io_read(struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint32_t length);

/** \brief Quad IO Read
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset to FLASH_BASE_ADDR
 *  \param[out] data The pointer of the data buffer
 *  \param[in] length Data length in bytes
 */
void hal_flashx_quad_io_read(struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint32_t length);

/** \brief Fast Read
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset to FLASH_BASE_ADDR
 *  \param[out] data The pointer of the data buffer
 *  \param[in] length Data length in bytes
 */
void hal_flashx_fast_read(struct hal_flash_env *env,uint32_t offset,uint8_t *data,uint32_t length);

/** \brief Read SFDP
 *  \param[in] env The handle of flash env
 *  \param[in] offset Offset
 *  \param[out] data The pointer of the data buffer
 *  \param[in] length Data length in bytes
 */
void hal_flashx_read_sfdp(struct hal_flash_env *env,uint32_t offset,uint8_t *data, uint32_t length);

/** \brief Deep Power Down */
void hal_flashx_deep_power_down(struct hal_flash_env *env);

/** \brief Release From Deep Power Down */
void hal_flashx_release_from_deep_power_down(struct hal_flash_env *env);

/** \brief Read ID  
 *  \param[in] env The handle of flash env
 *  \param[out] jedec_id The buffer for JEDEC ID
 */
void hal_flashx_read_id(struct hal_flash_env *env,uint8_t jedec_id[3]);

/** \brief Read Unique ID
 *  \param[in] env The handle of flash env
 *  \param[out] unique_serial_id The buffer for unique serial ID
 */
void hal_flashx_read_unique_id(struct hal_flash_env *env,uint8_t unique_serial_id[16]);

/** \brief Erase Security Area
 *  \param[in] env The handle of flash env
 *  \param[in] idx The index of security area
 */
void hal_flashx_erase_security_area(struct hal_flash_env *env,uint8_t idx);

/** \brief Program Security Area 
 *  \param[in] env The handle of flash env
 *  \param[in] idx The index of security area
 *  \param[in] addr The address of security area
 *  \param[in] data The pointer of the data to program into security area
 *  \param[in] length Data length in bytes, must be less than or equal to the size of one security area
 */
void hal_flashx_program_security_area(struct hal_flash_env *env,uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length);

/** \brief Read Security Area 
 *  \param[in] env The handle of flash env
 *  \param[in] idx The index of security area
 *  \param[in] addr The address of security area
 *  \param[out] data The pointer of the data buffer
 *  \param[in] length Data length in bytes
 */
void hal_flashx_read_security_area(struct hal_flash_env *env,uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length);

/** \brief Software Reset */
void hal_flashx_software_reset(struct hal_flash_env *env);

/** \brief Check and Set Quad Enable Status */
void hal_flashx_qe_status_read_and_set(struct hal_flash_env *env);

/** \brief Suspend Program or Erase Operation */
void hal_flashx_prog_erase_suspend(struct hal_flash_env *env);

/** \brief Resume Program or Erase Operation */
void hal_flashx_prog_erase_resume(struct hal_flash_env *env);

/** \brief Get Flash Total Size
 *  \param[in] env The handle of flash env
 *  \return Flash Size In Bytes
 */
uint32_t hal_flashx_total_size_get(struct hal_flash_env *env);

/** \brief Release the Continuous Read Mode and return to normal SPI operation */
void hal_flashx_continuous_mode_reset(struct hal_flash_env *env);

void hal_flashx_prog_erase_suspend_isr(struct hal_flash_env *env);

void hal_flashx_prog_erase_resume_isr(struct hal_flash_env *env);

uint8_t hal_flashx_read_ear(struct hal_flash_env *env);

void hal_flashx_write_ear(struct hal_flash_env *env, uint8_t ear);

void hal_flash_init();

void hal_flash_continuous_mode_start();

void hal_flash_continuous_mode_stop();

void hal_flash_read_status_register_0_ram(uint8_t *status_reg_0);

void hal_flash_read_status_register_0(uint8_t *status_reg_0);

void hal_flash_read_status_register_1_ram(uint8_t *status_reg_1);

void hal_flash_read_status_register_1(uint8_t *status_reg_1);

bool hal_flash_write_in_process();

void hal_flash_write_status_register(uint16_t status);

void hal_flash_multi_io_page_program(uint32_t offset,uint8_t *data,uint16_t length);

void hal_flash_dual_page_program(uint32_t offset,uint8_t *data,uint16_t length);

void hal_flash_quad_page_program(uint32_t offset,uint8_t *data,uint16_t length);

void hal_flash_page_program(uint32_t offset,uint8_t *data,uint16_t length);

void hal_flash_page_erase(uint32_t offset);

void hal_flash_sector_erase(uint32_t offset);

void hal_flash_block_32K_erase(uint32_t offset);

void hal_flash_block_64K_erase(uint32_t offset);

void hal_flash_chip_erase();

void hal_flash_multi_io_read(uint32_t offset,uint8_t *data,uint32_t length);

void hal_flash_dual_io_read(uint32_t offset,uint8_t *data,uint32_t length);

void hal_flash_quad_io_read(uint32_t offset,uint8_t *data,uint32_t length);

void hal_flash_fast_read(uint32_t offset,uint8_t *data,uint32_t length);

void hal_flash_read_sfdp(uint32_t offset,uint8_t *data, uint32_t length);

void hal_flash_deep_power_down();

void hal_flash_release_from_deep_power_down();

void hal_flash_read_id(uint8_t jedec_id[3]);

void hal_flash_read_unique_id(uint8_t unique_serial_id[16]);

void hal_flash_erase_security_area(uint8_t idx);

void hal_flash_program_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length);

void hal_flash_read_security_area(uint8_t idx,uint16_t addr,uint8_t *data,uint16_t length);

void hal_flash_software_reset();

void hal_flash_qe_status_read_and_set();

void hal_flash_prog_erase_suspend();

void hal_flash_prog_erase_resume();

uint32_t hal_flash_total_size_get();

void hal_flash_continuous_mode_reset();

void hal_flash_prog_erase_suspend_isr();

void hal_flash_prog_erase_resume_isr();
/** @}*/


/** @}*/

#ifdef __cplusplus
}
#endif

#endif

