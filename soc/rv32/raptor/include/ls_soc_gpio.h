#ifndef LS_SOC_GPIO_H_
#define LS_SOC_GPIO_H_
#include <stdint.h>
#include <stdbool.h>
#include "ls_soc_gpio_def.h"
#include "ls_soc_pinmux.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup GPIO
 *  @{
 */

/**@brief IO output drive capability type */
typedef enum
{
    ds0 = 0,
    ds1 = 1,
    ds2 = 2,
    ds3 = 3,
}io_drive_type_t;

/**@brief IO pull type */
typedef enum
{
    IO_PULL_DISABLE,
    IO_PULL_DOWN,
    IO_PULL_UP,
}io_pull_type_t;

typedef enum
{
    INT_EDGE_DISABLE = 0,
    INT_EDGE_NONE = 0,
    INT_EDGE_FALLING = 0x1,
    INT_EDGE_RISING = 0x2,
    INT_EDGE_BOTH = (INT_EDGE_FALLING|INT_EDGE_RISING),
}exti_edge_t;

typedef struct
{
    uint16_t num:4,   /*!<gpio pin */   
            port:12;  /*!<gpio port */   
}gpio_port_pin_t;

/**
  * @brief GPIO Init
  */
void io_init(void);

/**
  * @brief GPIO config output
  * @param pin Specific GPIO pin
  */
void io_cfg_output(uint16_t pin);

/**
  * @brief GPIO config open drain output mode
  * @param  pin  Specific GPIO pin
  */
void io_cfg_opendrain(uint16_t pin);

/**
  * @brief GPIO config pushpull output mode
  * @param  pin  Specific GPIO pin
  */
void io_cfg_pushpull(uint16_t pin);

/**
  * @brief GPIO config input and disable output
  * @param  pin  Specific GPIO pin
  */
void io_cfg_input(uint16_t pin);

/**
  * @brief GPIO just config input, not disable output
  * @param  pin  Specific GPIO pin
  */
void io_cfg_input_pure(uint16_t pin);

/**
  * @brief GPIO output disable
  * @param  pin  Specific GPIO pin
  */
void io_cfg_disable_output(uint16_t pin);

/**
  * @brief GPIO input disable
  * @param  pin  Specific GPIO pin
  */
void io_cfg_disable_input(uint16_t pin);

/**
  * @brief GPIO direction disable
  * @param  pin  Specific GPIO pin
  */
void io_cfg_disable(uint16_t pin);

/**
  * @brief GPIO config output
  * @param  pin  Specific GPIO pin
  * @param  val  GPIO level status
  *              0 means low level
  *              1 means high level
  */
void io_write_pin(uint16_t pin,uint16_t val);

/**
  * @brief set GPIO high level
  * @param  pin  Specific GPIO pin
  */
void io_set_pin(uint16_t pin);

/**
  * @brief set GPIO low level
  * @param  pin  Specific GPIO pin
  */
void io_clr_pin(uint16_t pin);

/**
  * @brief toggle GPIO 
  * @param  pin  Specific GPIO pin
  */
void io_toggle_pin(uint16_t pin);

/**
  * @brief get GPIO output level
  * @param  pin  Specific GPIO pin
  * @retval GPIO output level
  *              0 means low level
  *              1 means high level
  */
uint8_t io_get_output_val(uint16_t pin);

/**
  * @brief get GPIO level
  * @param  pin  Specific GPIO pin
  * @retval GPIO level
  *              0 means low level
  *              1 means high level
  */
uint16_t io_read_pin(uint16_t pin);

/**
  * @brief get GPIO input level
  * @param  pin  Specific GPIO pin
  * @retval GPIO input level
  *              0 means low level
  *              1 means high level
  */
uint8_t io_get_input_val(uint16_t pin);

/**
  * @brief app cpu get GPIO input level
  * @param  pin  Specific GPIO pin
  * @retval GPIO input level
  *              0 means low level
  *              1 means high level
  */
uint16_t io_app_get_input_val(uint16_t pin);

/**
  * @brief app cpu get GPIO level
  * @param  pin  Specific GPIO pin
  * @retval GPIO level
  *              0 means low level
  *              1 means high level
  */
uint16_t io_app_read_pin(uint16_t pin);

/**
  * @brief set GPIO drive capability
  * @param  pin  Specific GPIO pin
  * @param drive Configure the GPIO drive capability, This parameter can be a value of @ref io_drive_type_t
  */
void io_drive_capacity_write(uint16_t pin, io_drive_type_t drive);

/**
  * @brief read GPIO drive capability
  * @param  pin  Specific GPIO pin
  * @retval GPIO drive capability, This parameter can be a value of @ref io_drive_type_t
  *              0/1 means 1/4 output drive capability
  *              2 means 1/2 output drive capability
  *              3 means MAX output drive capability
  */
io_drive_type_t io_drive_capacity_read(uint16_t pin);

/**
  * @brief Sets the trigger edge for IO interrupt 
  * @param  pin  Specific GPIO pin 
  * @param  edge edges for IO interrupts 
  */

/**
  * @brief set GPIO pullup or pulldwon or nullpull
  * @param  pin  Specific GPIO pin
  * @param pull Configure the GPIO pull up and down ,This parameter can be a value of @ref io_pull_type_t    
  */
void io_pull_write(uint16_t pin,io_pull_type_t pull);

/**
  * @brief read GPIO pull states
  * @param  pin  Specific GPIO pin 
  * @retval GPIO pullup and pulldown state This parameter can be a value of @ref io_pull_type_t    
  */
io_pull_type_t io_pull_read(uint16_t pin);

/**
  * @brief GPIO external interrupt callback
  * @param pin specific GPIO pin
  */
void io_exti_callback(uint16_t pin,exti_edge_t edge);

/**
  * @brief Set GPIO mode
  * @param pin specific GPIO pin
  */
void set_gpio_mode(gpio_port_pin_t *pin);

/**
  * @brief Sets the trigger edge for IO interrupt 
  * @param  pin  Specific GPIO pin 
  * @param  edge edges for IO interrupts 
  */
void io_v33_exti_config(uint16_t pin,exti_edge_t edge);

/**
  * @brief Sets the trigger edge for IO interrupt 
  * @param  pin  Specific GPIO pin 
  * @param  edge edges for IO interrupts 
  */

void io_sec_exti_config(uint16_t pin, exti_edge_t edge);
void io_app_exti_config(uint16_t pin, exti_edge_t edge);
bool io_sec_get_exti_status(uint16_t pin, exti_edge_t edge);
bool io_app_get_exti_status(uint16_t pin, exti_edge_t edge);
void io_clr_exti(uint16_t pin, exti_edge_t edge);
void per_func_disable_all(uint16_t pin);
int per_func_get(uint16_t pin);
int per_func0_alt_get(uint16_t pin);
bool per_func_check(uint16_t pin, uint16_t func);
bool per_func0_alt_check(uint16_t pin, uint16_t alt);
void pinmux_cfg_pin_func_alt(uint16_t pin, uint16_t func, uint16_t func0_alt);
void io_func_cfg_lock(uint16_t pin, bool lock);
void io_exti_clr_cfg_lock(uint16_t pin, exti_edge_t edge, bool lock);
void io_cfg_lock(uint16_t pin, bool lock);
void io_cfg_app_input_lock(uint16_t pin, bool lock);
bool io_is_output_enabled(uint16_t pin);
bool io_is_input_enabled(uint16_t pin);
bool io_is_output(uint16_t pin);
bool io_is_input(uint16_t pin);
bool io_is_opendrain(uint16_t pin);
bool is_per_func_valid(uint16_t func);
void ext_intr_mask(volatile uint32_t *mask,volatile uint32_t *clr,uint16_t num,exti_edge_t edge);
void gpio_ana_init(uint16_t pin);
void gpio_ana_deinit(uint16_t pin);
void io_sl_st_init(uint16_t pin);
void io_filter_enable(uint16_t pin);
void io_filter_disable(uint16_t pin);

void pinmux_ssiv2_init();
void pinmux_emmc_init();
#ifdef __cplusplus
}
#endif

#endif

