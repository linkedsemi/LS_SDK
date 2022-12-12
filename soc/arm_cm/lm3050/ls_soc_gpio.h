#ifndef LS_SOC_GPIO_H_
#define LS_SOC_GPIO_H_
#include <stdint.h>
#include <stdbool.h>
#include "ls_soc_pinmux.h"

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
    IO_OUTPUT_HALF_DRIVER = 2,    //1/2 output drive capability
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
    INT_EDGE_FALLING = 0x1,
    INT_EDGE_RISING = 0x2,
    INT_EDGE_BOTH = (INT_EDGE_FALLING|INT_EDGE_RISING),
    INT_EDGE_UNKNOWN = 0xff,
}exti_edge_t;

typedef struct
{
    uint8_t num:4,   /*!<gpio pin */   
            port:4;  /*!<gpio port */   
}gpio_pin_t;

//lsgpioa
#define PA00 ((uint8_t)0x00)   /*!< GPIOA00 selected */     
#define PA01 ((uint8_t)0x01)   /*!< GPIOA01 selected */   
#define PA02 ((uint8_t)0x02)   /*!< GPIOA02 selected */     
#define PA03 ((uint8_t)0x03)   /*!< GPIOA03 selected */    
#define PA04 ((uint8_t)0x04)   /*!< GPIOA04 selected */      
#define PA05 ((uint8_t)0x05)   /*!< GPIOA05 selected */      
#define PA06 ((uint8_t)0x06)   /*!< GPIOA06 selected */     
#define PA07 ((uint8_t)0x07)   /*!< GPIOA07 selected */      
#define PA08 ((uint8_t)0x08)   /*!< GPIOA08 selected */     
#define PA09 ((uint8_t)0x09)   /*!< GPIOA09 selected */    
#define PA10 ((uint8_t)0x0A)   /*!< GPIOA10 selected */     
#define PA11 ((uint8_t)0x0B)   /*!< GPIOA11 selected */    
#define PA12 ((uint8_t)0x0C)   /*!< GPIOA12 selected */   
#define PA13 ((uint8_t)0x0D)   /*!< GPIOA13 selected */    
#define PA14 ((uint8_t)0x0E)   /*!< GPIOA14 selected */     
#define PA15 ((uint8_t)0x0F)   /*!< GPIOA15 selected */     
//lsgpiob
#define PB00 ((uint8_t)0X10)   /*!< GPIOB00 selected */      
#define PB01 ((uint8_t)0X11)   /*!< GPIOB01 selected */   
#define PB02 ((uint8_t)0X12)   /*!< GPIOB02 selected */    
#define PB03 ((uint8_t)0X13)   /*!< GPIOB03 selected */     
#define PB04 ((uint8_t)0X14)   /*!< GPIOB04 selected */    
#define PB05 ((uint8_t)0X15)   /*!< GPIOB05 selected */    
#define PB06 ((uint8_t)0X16)   /*!< GPIOB06 selected */     
#define PB07 ((uint8_t)0X17)   /*!< GPIOB07 selected */    
#define PB08 ((uint8_t)0X18)   /*!< GPIOB08 selected */     
#define PB09 ((uint8_t)0X19)   /*!< GPIOB09 selected */     
#define PB10 ((uint8_t)0X1A)   /*!< GPIOB10 selected */    
#define PB11 ((uint8_t)0X1B)   /*!< GPIOB11 selected */    
#define PB12 ((uint8_t)0X1C)   /*!< GPIOB12 selected */     
#define PB13 ((uint8_t)0X1D)   /*!< GPIOB13 selected */    
#define PB14 ((uint8_t)0X1E)   /*!< GPIOB14 selected */    
#define PB15 ((uint8_t)0X1F)   /*!< GPIOB15 selected */   
//lsgpioc
#define PC00 ((uint8_t)0X20)   /*!< GPIOC00 selected */     
#define PC01 ((uint8_t)0X21)   /*!< GPIOC01 selected */      
#define PC02 ((uint8_t)0X22)   /*!< GPIOC02 selected */     
#define PC03 ((uint8_t)0X23)   /*!< GPIOC03 selected */     
#define PC04 ((uint8_t)0X24)   /*!< GPIOC04 selected */     
#define PC05 ((uint8_t)0X25)   /*!< GPIOC05 selected */     
#define PC06 ((uint8_t)0X26)   /*!< GPIOC06 selected */      
#define PC07 ((uint8_t)0X27)   /*!< GPIOC07 selected */      
#define PC08 ((uint8_t)0X28)   /*!< GPIOC08 selected */     
#define PC09 ((uint8_t)0X29)   /*!< GPIOC09 selected */    
#define PC10 ((uint8_t)0X2A)   /*!< GPIOC10 selected */    
#define PC11 ((uint8_t)0X2B)   /*!< GPIOC11 selected */    
#define PC12 ((uint8_t)0X2C)   /*!< GPIOC12 selected */     
#define PC13 ((uint8_t)0X2D)   /*!< GPIOC13 selected */    
#define PC14 ((uint8_t)0X2E)   /*!< GPIOC14 selected */    
#define PC15 ((uint8_t)0X2F)   /*!< GPIOC15 selected */   
//lsgpiod
#define PD00 ((uint8_t)0X30)   /*!< GPIOD00 selected */     
#define PD01 ((uint8_t)0X31)   /*!< GPIOD01 selected */      
#define PD02 ((uint8_t)0X32)   /*!< GPIOD02 selected */     
#define PD03 ((uint8_t)0X33)   /*!< GPIOD03 selected */     
#define PD04 ((uint8_t)0X34)   /*!< GPIOD04 selected */     
#define PD05 ((uint8_t)0X35)   /*!< GPIOD05 selected */     
#define PD06 ((uint8_t)0X36)   /*!< GPIOD06 selected */      
#define PD07 ((uint8_t)0X37)   /*!< GPIOD07 selected */      
#define PD08 ((uint8_t)0X38)   /*!< GPIOD08 selected */     
#define PD09 ((uint8_t)0X39)   /*!< GPIOD09 selected */    
#define PD10 ((uint8_t)0X3A)   /*!< GPIOD10 selected */    
#define PD11 ((uint8_t)0X3B)   /*!< GPIOD11 selected */    
#define PD12 ((uint8_t)0X3C)   /*!< GPIOD12 selected */     
#define PD13 ((uint8_t)0X3D)   /*!< GPIOD13 selected */    
#define PD14 ((uint8_t)0X3E)   /*!< GPIOD14 selected */    
#define PD15 ((uint8_t)0X3F)   /*!< GPIOD15 selected */   

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
  * @retval GPIO output level
  *              0 means low level
  *              1 means high level
  */
uint8_t io_read_pin(uint8_t pin);

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
void io_exti_config(uint8_t pin,exti_edge_t edge);

/**
  * @brief GPIO external interrupt callback
  * @param pin specific GPIO pin
  * @param edge edge captured when the interrupt handler is called
  */
void io_exti_callback(uint8_t pin,exti_edge_t edge);

/**
  * @brief Set GPIO mode
  * @param pin specific GPIO pin
  */
void set_gpio_mode(gpio_pin_t *pin);


/** @}*/


/** @}*/

#endif

