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
    IO_OUTPUT_QUARTER_DRIVER = 0, //1/4 output drive capability, range is 0~1
    IO_OUTPUT_HALF_DRIVER = 1,    //1/2 output drive capability
    IO_OUTPUT_MAX_DRIVER = 3,     //MAX output drive capability
}io_drive_type_t;

/**@brief IO pull type */
typedef enum
{
    IO_PULL_DISABLE = 0,
    IO_PULL_UP = 0x1,
    IO_PULL_DOWN = 0x2,
    IO_PULL_UP_DOWN = (IO_PULL_UP|IO_PULL_DOWN),
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
    uint8_t num:4,   /*!<gpio pin */   
            port:4;  /*!<gpio port */   
}gpio_port_pin_t;

/**
  * @brief GPIO Init
  */
void io_init(void);

/**
  * @brief GPIO config output
  * @param pin Specific GPIO pin
  */
void io_cfg_output(uint8_t pin);

/**
  * @brief GPIO config open drain output mode
  * @param  pin  Specific GPIO pin
  */
void io_cfg_opendrain(uint8_t pin);

/**
  * @brief GPIO config pushpull output mode
  * @param  pin  Specific GPIO pin
  */
void io_cfg_pushpull(uint8_t pin);

/**
  * @brief GPIO config input
  * @param  pin  Specific GPIO pin
  */
void io_cfg_input(uint8_t pin);

/**
  * @brief GPIO input disable
  * @param  pin  Specific GPIO pin
  */
void io_cfg_disable(uint8_t pin);

/**
  * @brief GPIO config output
  * @param  pin  Specific GPIO pin
  * @param  val  GPIO level status
  *              0 means low level
  *              1 means high level
  */
void io_write_pin(uint8_t pin,uint8_t val);

/**
  * @brief set GPIO high level
  * @param  pin  Specific GPIO pin
  */
void io_set_pin(uint8_t pin);

/**
  * @brief set GPIO low level
  * @param  pin  Specific GPIO pin
  */
void io_clr_pin(uint8_t pin);

/**
  * @brief toggle GPIO 
  * @param  pin  Specific GPIO pin
  */
void io_toggle_pin(uint8_t pin);

/**
  * @brief get GPIO output level
  * @param  pin  Specific GPIO pin
  * @retval GPIO output level
  *              0 means low level
  *              1 means high level
  */
uint8_t io_get_output_val(uint8_t pin);

/**
  * @brief get GPIO input level
  * @param  pin  Specific GPIO pin
  * @retval GPIO input level
  *              0 means low level
  *              1 means high level
  */
uint8_t io_get_input_val(uint8_t pin);

/**
  * @brief get GPIO level
  * @param  pin  Specific GPIO pin
  * @retval GPIO level
  *              0 means low level
  *              1 means high level
  */
uint8_t io_read_pin(uint8_t pin);

/**
  * @brief set GPIO drive capability
  * @param  pin  Specific GPIO pin
  * @param drive Configure the GPIO drive capability, This parameter can be a value of @ref io_drive_type_t
  */
void io_drive_capacity_write(uint8_t pin, io_drive_type_t drive);

/**
  * @brief read GPIO drive capability
  * @param  pin  Specific GPIO pin
  * @retval GPIO drive capability, This parameter can be a value of @ref io_drive_type_t
  *              0/1 means 1/4 output drive capability
  *              2 means 1/2 output drive capability
  *              3 means MAX output drive capability
  */
io_drive_type_t io_drive_capacity_read(uint8_t pin);

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
void io_pull_write(uint8_t pin,io_pull_type_t pull);

/**
  * @brief read GPIO pull states
  * @param  pin  Specific GPIO pin 
  * @retval GPIO pullup and pulldown state This parameter can be a value of @ref io_pull_type_t    
  */
io_pull_type_t io_pull_read(uint8_t pin);

/**
  * @brief GPIO external interrupt callback
  * @param pin specific GPIO pin
  */
void io_exti_callback(uint8_t pin,exti_edge_t edge);

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
void io_v33_exti_config(uint8_t pin,exti_edge_t edge);

/**
  * @brief Sets the trigger edge for IO interrupt 
  * @param  pin  Specific GPIO pin 
  * @param  edge edges for IO interrupts 
  */
void io_exti_config(uint8_t pin,exti_edge_t edge);
/** @}*/


/** @}*/

#ifdef __cplusplus
}
#endif

#endif

