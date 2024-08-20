#ifndef LS_SOC_GPIO_H_
#define LS_SOC_GPIO_H_
#include <stdint.h>
#include <stdbool.h>
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
//lsgpioe
#define PE00 ((uint8_t)0X40)   /*!< GPIOE00 selected */     
#define PE01 ((uint8_t)0X41)   /*!< GPIOE01 selected */      
#define PE02 ((uint8_t)0X42)   /*!< GPIOE02 selected */     
#define PE03 ((uint8_t)0X43)   /*!< GPIOE03 selected */     
#define PE04 ((uint8_t)0X44)   /*!< GPIOE04 selected */     
#define PE05 ((uint8_t)0X45)   /*!< GPIOE05 selected */     
#define PE06 ((uint8_t)0X46)   /*!< GPIOE06 selected */      
#define PE07 ((uint8_t)0X47)   /*!< GPIOE07 selected */      
#define PE08 ((uint8_t)0X48)   /*!< GPIOE08 selected */     
#define PE09 ((uint8_t)0X49)   /*!< GPIOE09 selected */    
#define PE10 ((uint8_t)0X4A)   /*!< GPIOE10 selected */    
#define PE11 ((uint8_t)0X4B)   /*!< GPIOE11 selected */    
#define PE12 ((uint8_t)0X4C)   /*!< GPIOE12 selected */     
#define PE13 ((uint8_t)0X4D)   /*!< GPIOE13 selected */    
#define PE14 ((uint8_t)0X4E)   /*!< GPIOE14 selected */    
#define PE15 ((uint8_t)0X4F)   /*!< GPIOE15 selected */   
//lsgpiof
#define PF00 ((uint8_t)0X50)   /*!< GPIOF00 selected */     
#define PF01 ((uint8_t)0X51)   /*!< GPIOF01 selected */      
#define PF02 ((uint8_t)0X52)   /*!< GPIOF02 selected */     
#define PF03 ((uint8_t)0X53)   /*!< GPIOF03 selected */     
#define PF04 ((uint8_t)0X54)   /*!< GPIOF04 selected */     
#define PF05 ((uint8_t)0X55)   /*!< GPIOF05 selected */     
#define PF06 ((uint8_t)0X56)   /*!< GPIOF06 selected */      
#define PF07 ((uint8_t)0X57)   /*!< GPIOF07 selected */      
#define PF08 ((uint8_t)0X58)   /*!< GPIOF08 selected */     
#define PF09 ((uint8_t)0X59)   /*!< GPIOF09 selected */    
#define PF10 ((uint8_t)0X5A)   /*!< GPIOF10 selected */    
#define PF11 ((uint8_t)0X5B)   /*!< GPIOF11 selected */    
#define PF12 ((uint8_t)0X5C)   /*!< GPIOF12 selected */     
#define PF13 ((uint8_t)0X5D)   /*!< GPIOF13 selected */    
#define PF14 ((uint8_t)0X5E)   /*!< GPIOF14 selected */    
#define PF15 ((uint8_t)0X5F)   /*!< GPIOF15 selected */   
//lsgpiog
#define PG00 ((uint8_t)0X60)   /*!< GPIOG00 selected */     
#define PG01 ((uint8_t)0X61)   /*!< GPIOG01 selected */      
#define PG02 ((uint8_t)0X62)   /*!< GPIOG02 selected */     
#define PG03 ((uint8_t)0X63)   /*!< GPIOG03 selected */     
#define PG04 ((uint8_t)0X64)   /*!< GPIOG04 selected */     
#define PG05 ((uint8_t)0X65)   /*!< GPIOG05 selected */     
#define PG06 ((uint8_t)0X66)   /*!< GPIOG06 selected */      
#define PG07 ((uint8_t)0X67)   /*!< GPIOG07 selected */      
#define PG08 ((uint8_t)0X68)   /*!< GPIOG08 selected */     
#define PG09 ((uint8_t)0X69)   /*!< GPIOG09 selected */    
#define PG10 ((uint8_t)0X6A)   /*!< GPIOG10 selected */    
#define PG11 ((uint8_t)0X6B)   /*!< GPIOG11 selected */    
#define PG12 ((uint8_t)0X6C)   /*!< GPIOG12 selected */     
#define PG13 ((uint8_t)0X6D)   /*!< GPIOG13 selected */    
#define PG14 ((uint8_t)0X6E)   /*!< GPIOG14 selected */    
#define PG15 ((uint8_t)0X6F)   /*!< GPIOG15 selected */   
//lsgpioh
#define PH00 ((uint8_t)0X70)   /*!< GPIOH00 selected */     
#define PH01 ((uint8_t)0X71)   /*!< GPIOH01 selected */      
#define PH02 ((uint8_t)0X72)   /*!< GPIOH02 selected */     
#define PH03 ((uint8_t)0X73)   /*!< GPIOH03 selected */     
#define PH04 ((uint8_t)0X74)   /*!< GPIOH04 selected */     
#define PH05 ((uint8_t)0X75)   /*!< GPIOH05 selected */     
#define PH06 ((uint8_t)0X76)   /*!< GPIOH06 selected */      
#define PH07 ((uint8_t)0X77)   /*!< GPIOH07 selected */      
#define PH08 ((uint8_t)0X78)   /*!< GPIOH08 selected */     
#define PH09 ((uint8_t)0X79)   /*!< GPIOH09 selected */    
#define PH10 ((uint8_t)0X7A)   /*!< GPIOH10 selected */    
#define PH11 ((uint8_t)0X7B)   /*!< GPIOH11 selected */    
#define PH12 ((uint8_t)0X7C)   /*!< GPIOH12 selected */     
#define PH13 ((uint8_t)0X7D)   /*!< GPIOH13 selected */    
#define PH14 ((uint8_t)0X7E)   /*!< GPIOH14 selected */    
#define PH15 ((uint8_t)0X7F)   /*!< GPIOH15 selected */  
//lsgpioL
#define PI00 ((uint8_t)0x80)   /*!< GPIOI00 selected */     
#define PI01 ((uint8_t)0x81)   /*!< GPIOI01 selected */      
#define PI02 ((uint8_t)0x82)   /*!< GPIOI02 selected */     
#define PI03 ((uint8_t)0x83)   /*!< GPIOI03 selected */     
#define PI04 ((uint8_t)0x84)   /*!< GPIOI04 selected */     
#define PI05 ((uint8_t)0x85)   /*!< GPIOI05 selected */     
#define PI06 ((uint8_t)0x86)   /*!< GPIOI06 selected */      
#define PI07 ((uint8_t)0x87)   /*!< GPIOI07 selected */      
#define PI08 ((uint8_t)0x88)   /*!< GPIOI08 selected */     
#define PI09 ((uint8_t)0x89)   /*!< GPIOI09 selected */    
#define PI10 ((uint8_t)0x8A)   /*!< GPIOI10 selected */    
#define PI11 ((uint8_t)0x8B)   /*!< GPIOI11 selected */    
#define PI12 ((uint8_t)0x8C)   /*!< GPIOI12 selected */     
#define PI13 ((uint8_t)0x8D)   /*!< GPIOI13 selected */    
#define PI14 ((uint8_t)0x8E)   /*!< GPIOI14 selected */    
#define PI15 ((uint8_t)0x8F)   /*!< GPIOI15 selected */  
//lsgpioJ
#define PJ00 ((uint8_t)0x90)   /*!< GPIOJ00 selected */     
#define PJ01 ((uint8_t)0x91)   /*!< GPIOJ01 selected */      
#define PJ02 ((uint8_t)0x92)   /*!< GPIOJ02 selected */     
#define PJ03 ((uint8_t)0x93)   /*!< GPIOJ03 selected */     
#define PJ04 ((uint8_t)0x94)   /*!< GPIOJ04 selected */     
#define PJ05 ((uint8_t)0x95)   /*!< GPIOJ05 selected */     
#define PJ06 ((uint8_t)0x96)   /*!< GPIOJ06 selected */      
#define PJ07 ((uint8_t)0x97)   /*!< GPIOJ07 selected */      
#define PJ08 ((uint8_t)0x98)   /*!< GPIOJ08 selected */     
#define PJ09 ((uint8_t)0x99)   /*!< GPIOJ09 selected */    
#define PJ10 ((uint8_t)0x9A)   /*!< GPIOJ10 selected */    
#define PJ11 ((uint8_t)0x9B)   /*!< GPIOJ11 selected */    
#define PJ12 ((uint8_t)0x9C)   /*!< GPIOJ12 selected */     
#define PJ13 ((uint8_t)0x9D)   /*!< GPIOJ13 selected */    
#define PJ14 ((uint8_t)0x9E)   /*!< GPIOJ14 selected */    
#define PJ15 ((uint8_t)0x9F)   /*!< GPIOJ15 selected */   
//lsgpiok
#define PK00 ((uint8_t)0xA0)   /*!< GPIOK00 selected */     
#define PK01 ((uint8_t)0xA1)   /*!< GPIOK01 selected */      
#define PK02 ((uint8_t)0xA2)   /*!< GPIOK02 selected */     
#define PK03 ((uint8_t)0xA3)   /*!< GPIOK03 selected */     
#define PK04 ((uint8_t)0xA4)   /*!< GPIOK04 selected */     
#define PK05 ((uint8_t)0xA5)   /*!< GPIOK05 selected */     
#define PK06 ((uint8_t)0xA6)   /*!< GPIOK06 selected */      
#define PK07 ((uint8_t)0xA7)   /*!< GPIOK07 selected */      
#define PK08 ((uint8_t)0xA8)   /*!< GPIOK08 selected */     
#define PK09 ((uint8_t)0xA9)   /*!< GPIOK09 selected */    
#define PK10 ((uint8_t)0xAA)   /*!< GPIOK10 selected */    
#define PK11 ((uint8_t)0xAB)   /*!< GPIOK11 selected */    
#define PK12 ((uint8_t)0xAC)   /*!< GPIOK12 selected */     
#define PK13 ((uint8_t)0xAD)   /*!< GPIOK13 selected */    
#define PK14 ((uint8_t)0xAE)   /*!< GPIOK14 selected */    
#define PK15 ((uint8_t)0xAF)   /*!< GPIOK15 selected */    
//lsgpioQ
#define PM00 ((uint8_t)0xB0)   /*!< GPIOQ00 selected */     
#define PM01 ((uint8_t)0xB1)   /*!< GPIOQ01 selected */      
#define PM02 ((uint8_t)0xB2)   /*!< GPIOQ02 selected */     
#define PM03 ((uint8_t)0xB3)   /*!< GPIOQ03 selected */     
#define PM04 ((uint8_t)0xB4)   /*!< GPIOQ04 selected */     
#define PM05 ((uint8_t)0xB5)   /*!< GPIOQ05 selected */     
#define PM06 ((uint8_t)0xB6)   /*!< GPIOQ06 selected */      
#define PM07 ((uint8_t)0xB7)   /*!< GPIOQ07 selected */      
#define PM08 ((uint8_t)0xB8)   /*!< GPIOQ08 selected */     
#define PM09 ((uint8_t)0xB9)   /*!< GPIOQ09 selected */    
#define PM10 ((uint8_t)0xBA)   /*!< GPIOQ10 selected */    
#define PM11 ((uint8_t)0xBB)   /*!< GPIOQ11 selected */    
#define PM12 ((uint8_t)0xBC)   /*!< GPIOQ12 selected */     
#define PM13 ((uint8_t)0xBD)   /*!< GPIOQ13 selected */    
#define PM14 ((uint8_t)0xBE)   /*!< GPIOQ14 selected */    
#define PM15 ((uint8_t)0xBF)   /*!< GPIOQ15 selected */   
//lsgpioQ
#define PN00 ((uint8_t)0xC0)   /*!< GPIOQ00 selected */     
#define PN01 ((uint8_t)0xC1)   /*!< GPIOQ01 selected */      
#define PN02 ((uint8_t)0xC2)   /*!< GPIOQ02 selected */     
#define PN03 ((uint8_t)0xC3)   /*!< GPIOQ03 selected */     
#define PN04 ((uint8_t)0xC4)   /*!< GPIOQ04 selected */     
#define PN05 ((uint8_t)0xC5)   /*!< GPIOQ05 selected */     
#define PN06 ((uint8_t)0xC6)   /*!< GPIOQ06 selected */      
#define PN07 ((uint8_t)0xC7)   /*!< GPIOQ07 selected */      
#define PN08 ((uint8_t)0xC8)   /*!< GPIOQ08 selected */     
#define PN09 ((uint8_t)0xC9)   /*!< GPIOQ09 selected */    
#define PN10 ((uint8_t)0xCA)   /*!< GPIOQ10 selected */    
#define PN11 ((uint8_t)0xCB)   /*!< GPIOQ11 selected */    
#define PN12 ((uint8_t)0xCC)   /*!< GPIOQ12 selected */     
#define PN13 ((uint8_t)0xCD)   /*!< GPIOQ13 selected */    
#define PN14 ((uint8_t)0xCE)   /*!< GPIOQ14 selected */    
#define PN15 ((uint8_t)0xCF)   /*!< GPIOQ15 selected */   
//lsgpioQ
#define PQ00 ((uint8_t)0xD0)   /*!< GPIOQ00 selected */     
#define PQ01 ((uint8_t)0xD1)   /*!< GPIOQ01 selected */      
#define PQ02 ((uint8_t)0xD2)   /*!< GPIOQ02 selected */     
#define PQ03 ((uint8_t)0xD3)   /*!< GPIOQ03 selected */     
#define PQ04 ((uint8_t)0xD4)   /*!< GPIOQ04 selected */     
#define PQ05 ((uint8_t)0xD5)   /*!< GPIOQ05 selected */     
#define PQ06 ((uint8_t)0xD6)   /*!< GPIOQ06 selected */      
#define PQ07 ((uint8_t)0xD7)   /*!< GPIOQ07 selected */      
#define PQ08 ((uint8_t)0xD8)   /*!< GPIOQ08 selected */     
#define PQ09 ((uint8_t)0xD9)   /*!< GPIOQ09 selected */    
#define PQ10 ((uint8_t)0xDA)   /*!< GPIOQ10 selected */    
#define PQ11 ((uint8_t)0xDB)   /*!< GPIOQ11 selected */    
#define PQ12 ((uint8_t)0xDC)   /*!< GPIOQ12 selected */     
#define PQ13 ((uint8_t)0xDD)   /*!< GPIOQ13 selected */    
#define PQ14 ((uint8_t)0xDE)   /*!< GPIOQ14 selected */    
#define PQ15 ((uint8_t)0xDF)   /*!< GPIOQ15 selected */   
//lsgpioQ
#define PT00 ((uint8_t)0xE0)   /*!< GPIOQ00 selected */     
#define PT01 ((uint8_t)0xE1)   /*!< GPIOQ01 selected */      
#define PT02 ((uint8_t)0xE2)   /*!< GPIOQ02 selected */     
#define PT03 ((uint8_t)0xE3)   /*!< GPIOQ03 selected */     
#define PT04 ((uint8_t)0xE4)   /*!< GPIOQ04 selected */     
#define PT05 ((uint8_t)0xE5)   /*!< GPIOQ05 selected */     
#define PT06 ((uint8_t)0xE6)   /*!< GPIOQ06 selected */      
#define PT07 ((uint8_t)0xE7)   /*!< GPIOQ07 selected */      
#define PT08 ((uint8_t)0xE8)   /*!< GPIOQ08 selected */     
#define PT09 ((uint8_t)0xE9)   /*!< GPIOQ09 selected */    
#define PT10 ((uint8_t)0xEA)   /*!< GPIOQ10 selected */    
#define PT11 ((uint8_t)0xEB)   /*!< GPIOQ11 selected */    
#define PT12 ((uint8_t)0xEC)   /*!< GPIOQ12 selected */     
#define PT13 ((uint8_t)0xED)   /*!< GPIOQ13 selected */    
#define PT14 ((uint8_t)0xEE)   /*!< GPIOQ14 selected */    
#define PT15 ((uint8_t)0xEF)   /*!< GPIOQ15 selected */   





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

