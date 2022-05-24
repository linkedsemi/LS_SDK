#ifndef IO_CONFIG_H_
#define IO_CONFIG_H_
#include <stdint.h>
#include <stdbool.h>

/** \addtogroup PERIPHERAL
 *  @{
 */

/** \addtogroup GPIO
 *  @{
 */
 
/**@brief IO pull type */
typedef enum 
{
    IO_PULL_DISABLE,
    IO_PULL_UP,
    IO_PULL_DOWN,
}io_pull_type_t;

typedef enum
{
    INT_EDGE_FALLING,
    INT_EDGE_RISING,
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
  * @brief GPIO external interrupt enable 
  * @param  pin  Specific GPIO pin
  */
void io_ext_intrp_enable(uint8_t pin);

/**
  * @brief GPIO external interrupt disable
  * @param  pin  Specific GPIO pin
  */
void io_ext_intrp_disable(uint8_t pin);

/**
  * @brief Sets the trigger edge for IO interrupt 
  * @param  pin  Specific GPIO pin 
  * @param  edge edges for IO interrupts 
  */
void io_exti_config(uint8_t pin,exti_edge_t edge);

/**
  * @brief GPIO external interrupt enable or disable
  * @param  pin  Specific GPIO pin
  * @param  enable
  */
void io_exti_enable(uint8_t pin,bool enable);

/**
  * @brief GPIO external interrupt callback
  * @param pin specific GPIO pin
  */
void io_exti_callback(uint8_t pin);

/**
  * @brief Set GPIO mode
  * @param pin specific GPIO pin
  */
void set_gpio_mode(gpio_pin_t *pin);

/**
  * @brief Init IO for SPI Flash (CS CLK DQ0 DQ1)
  */
void spi_flash_io_init(void);

/**
  * @brief DeInit SPI Flash IO
  */
void spi_flash_io_deinit(void);

/**
  * @brief Init IO for QSPI Flash (CS CLK DQ0 DQ1 DQ2 DQ3)
  */
void qspi_flash_io_init(void);

/**
  * @brief DeInit QSPI Flash IO
  */
void qspi_flash_io_deinit(void);

/**
  * @brief  GPIO initilization
  * @param  clk  Specific GPIO pin
  */
void ssi_clk_io_init(uint8_t clk);

/**
  * @brief     GPIO initilization as ssi nss0
  * @param  nss0  Specific GPIO pin
  */
void ssi_nss0_io_init(uint8_t nss0);

/**
  * @brief    Set pin mux function to ssi nss1
  * @param  nss1   Specific GPIO pin
  */
void ssi_nss1_io_init(uint8_t nss1);

/**
  * @brief  config GPIO  to ssi dq0
  * @param  dq0  Specific GPIO pin
  */
void ssi_dq0_io_init(uint8_t dq0);

/**
  * @brief   Set pin mux function to ssi dq1
  * @param  dq1   Specific GPIO pin
  */
void ssi_dq1_io_init(uint8_t dq1);

/**
  * @brief   Set pin mux function to ssi dq2
  * @param  dq2   Specific GPIO pin
  */
void ssi_dq2_io_init(uint8_t dq2);

/**
  * @brief  Set pin mux function to ssi dq3
  * @param  dq3   Specific GPIO pin
  */
void ssi_dq3_io_init(uint8_t dq3);

/**
  * @brief  Set pin mux function to spi2 clk
  * @param  clk   Specific GPIO pin
  */
void spi2_clk_io_init(uint8_t clk);

/**
  * @brief   Set pin mux function to spi2 nss
  * @param  nss  Specific GPIO pin
  */
void spi2_nss_io_init(uint8_t nss);

/**
  * @brief   Set pin mux function to spi2 mosi
  * @param  mosi   Specific GPIO pin
  */
void spi2_mosi_io_init(uint8_t mosi);

/**
  * @brief    Set pin mux function to spi2 mosi
  * @param  miso   Specific GPIO pin
  */
void spi2_miso_io_init(uint8_t miso);

/**
  * @brief  clear pin mux function of spi2_clk
  */
void spi2_clk_io_deinit(void);

/**
  * @brief  clear pin mux functions of spi2_nss
  */
void spi2_nss_io_deinit(void);

/**
  * @brief   clear pin mux function of spi2_mosi
  */
void spi2_mosi_io_deinit(void);

/**
  * @brief   clear pin mux function of spi2_miso
  */
void spi2_miso_io_deinit(void);

/**
  * @brief       Set pin mux function as iic1_io_init
  * @param  scl  Specific GPIO pin 
  * @param  sda  Specific GPIO pin 
  */
void iic1_io_init(uint8_t scl,uint8_t sda);

/**
  * @brief clean pin mux function  of iic1
  */
void iic1_io_deinit(void);


/**
  * @brief         Set pin mux function as iic2_io_init
  * @param  scl    Specific GPIO pin  
  * @param  sda    Specific GPIO pin 
  */
void iic2_io_init(uint8_t scl,uint8_t sda);


/**
  * @brief clean pin mux function of iic2
  */
void iic2_io_deinit(void);

/**
  * @brief         Set pin mux function to uart1 (config of gpio)
  * @param  txd    Specific GPIO pin  
  * @param   rxd   Specific GPIO pin   
  */
void uart1_io_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart1
  */
void uart1_io_deinit(void);

/**
  * @brief          Set pin mux function to uart1_7816
   * @param  txd    Specific GPIO pin  
  * @param   ck     Specific GPIO pin  
  */
void uart1_7816_io_init(uint8_t txd,uint8_t ck);

/**
  * @brief clear pin mux function of uart1_7816
  */
void uart1_7816_io_deinit(void);

/**
  * @brief          Set pin mux function to uart2
  * @param  txd     Specific GPIO pin  
  * @param rxd      Specific GPIO pin  
  */
void uart2_io_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart2
  */
void uart2_io_deinit(void);

/**
  * @brief       Set pin mux function to uart3
  * @param  txd   Specific GPIO pin  
  * @param rxd   Specific GPIO pin   
  */
void uart3_io_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart3
  */
void uart3_io_deinit(void);

/**
  * @brief Set pin mux function to adtim1 
  * @param   pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void adtim1_ch1_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear  mux function of pin adtim1
  */
void adtim1_ch1_io_deinit(void);

/**
  * @brief Set  mux function of pin adtmi1 of channel 2
  * @param   pin Specific GPIO pin  
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void adtim1_ch2_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin adtim1
  */
void adtim1_ch2_io_deinit(void);

/**
  * @brief Set  mux function of pin adtmi1 of channel 3
  * @param   pin Specific GPIO pin  
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void adtim1_ch3_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief Set pin mux function
  */
void adtim1_ch3_io_deinit(void);

/**
  * @brief  Set  mux function of pin adtmi1 of channel 4
  * @param   pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void adtim1_ch4_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin adtim1 of channel 4
  */
void adtim1_ch4_io_deinit(void);

/**
  * @brief      Set mux function of pin adtim1  of ch1n as input and output
  * @param  pin  Specific GPIO pin 
  */
void adtim1_ch1n_io_init(uint8_t pin);

/**
  * @brief clear mux function of pin adtim1 of ch1n
  */
void adtim1_ch1n_io_deinit(void);

/**
  * @brief           Set mux function of pin adtim1 of ch2n
  * @param  pin      Specific GPIO pin 
  */

void adtim1_ch2n_io_init(uint8_t pin);

/**
  * @brief          clear  mux function of pin adtim1 of ch2n
  */
void adtim1_ch2n_io_deinit(void);

/**
    @brief          Set mux function of pin adtim1 of ch3n
  * @param  pin     Specific GPIO pin 
  */
void adtim1_ch3n_io_init(uint8_t pin);

/**
  @brief             clear mux function of pin adtim1 of ch3n
  */
void adtim1_ch3n_io_deinit(void);

/**
    @brief           Set mux function of pin adtim1 of etr
  * @param  pin      Specific GPIO pin 
  */
void adtim1_etr_io_init(uint8_t pin);

/**
  @brief      clear mux function of pin adtim1 of etr
  */
void adtim1_etr_io_deinit(void);

/**
    @brief           configure gpio pin as adtim1_bk
  * @param  pin      Specific GPIO pin 
  */
void adtim1_bk_io_init(uint8_t pin);

/**
 @brief clear  mux function of pin adtim1_bk 
  */
void adtim1_bk_io_deinit(void);

/**
  *  @brief Set mux function of pin gptima1 of channel 1
  *  @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void gptima1_ch1_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptima1 of channel 1
  */
void gptima1_ch1_io_deinit(void);

/**
  * @brief  Set mux function of pin gptima1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void gptima1_ch2_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief   clear  mux function of pin gptima1 of channel 2
  */
void gptima1_ch2_io_deinit(void);

/**
  * @brief                Set mux function of pin gptima1 of channel 3
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void gptima1_ch3_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief       clear mux function of pin gptima1 of channel 3
  */
void gptima1_ch3_io_deinit(void);

/**
  * @brief                Set mux function of pin gptima1 of channel 4
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void gptima1_ch4_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief     clear mux function of pin gptima1 of channel 4
  */
void gptima1_ch4_io_deinit(void);

/**
  * @brief       Set mux function of pin gptima1 of channel etr
  * @param  pin  Specific GPIO pin 
  */
void gptima1_etr_io_init(uint8_t pin);

/**
  * @brief      clear mux function of pin gptima1 of etr
  */
void gptima1_etr_io_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 1
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void gptimb1_ch1_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 1
  */
void gptimb1_ch1_io_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void gptimb1_ch2_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief        clear mux function of pin gptimb1 of channel 2
  */
void gptimb1_ch2_io_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 3
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void gptimb1_ch3_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 3
  */
void gptimb1_ch3_io_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 4
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void gptimb1_ch4_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 4
  */
void gptimb1_ch4_io_deinit(void);

/**
  * @brief Set mux function of pin gptimb1 of etr
  * @param  pin  Specific GPIO pin 
  */
void gptimb1_etr_io_init(uint8_t pin);

/**
  * @brief   clear mux function of pin gptimb1 of etr
  */
void gptimb1_etr_io_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 1
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void gptimc1_ch1_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimc1 of channel 1
  */
void gptimc1_ch1_io_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of channel 1
  * @param  pin  Specific GPIO pin 
  */
void gptimc1_ch1n_io_init(uint8_t pin);

/**
  * @brief clear mux function of pin gptimc1 of channel 1
  */
void gptimc1_ch1n_io_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void gptimc1_ch2_io_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimc1 of channel 2
  */
void gptimc1_ch2_io_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of bk
  * @param  pin   Specific GPIO pin 
  */
void gptimc1_bk_io_init(uint8_t pin);

/**
  * @brief clear mux function of pin gptimc1 of bk
  */
void gptimc1_bk_io_deinit(void);

/**
  * @brief Set mux function of pin gadc12b of in0
  */
void adc12b_in0_io_init(void);

/**
  * @brief clear mux function of pin gadc12b of in0
  */
void adc12b_in0_io_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in1
  */
void adc12b_in1_io_init(void);

/**
  * @brief clear mux function of pin adc12b of in1
  */
void adc12b_in1_io_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in2
  */
void adc12b_in2_io_init(void);

/**
  * @brief clear mux function of pin adc12b of in2
  */
void adc12b_in2_io_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in3
  */
void adc12b_in3_io_init(void);

/**
  * @brief clear mux function of pin adc12b of in3
  */
void adc12b_in3_io_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in4
  */
void adc12b_in4_io_init(void);

/**
  * @brief clear mux function of pin adc12b of in4
  */
void adc12b_in4_io_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in5
  */
void adc12b_in5_io_init(void);

/**
  * @brief clear  mux function of pin adc12b of in5
  */
void adc12b_in5_io_deinit(void);

/**
  * @brief Set mux function of pin  adc12b of in6
  */
void adc12b_in6_io_init(void);

/**
  * @brief clear  mux function of pin adc12b of in6
  */
void adc12b_in6_io_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in7
  */
void adc12b_in7_io_init(void);

/**
  * @brief clear mux function of pin adc12b of in7
  */
void adc12b_in7_io_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in8
  */
void adc12b_in8_io_init(void);

/**
  * @brief clear mux function of pin adc12b of in8
  */
void adc12b_in8_io_deinit(void);

/**
  * @brief        configure gpio pin as pdm_clk
  * @param  pin   Specific GPIO pin 
  */
void pdm_clk_io_init(uint8_t pin);

/**
  * @brief clear gpio of pdm_clk
  */
void pdm_clk_io_deinit(void);

/**
  * @brief       configure gpio of pdm_data0
  * @param  pin  Specific GPIO pin 
  */
void pdm_data0_io_init(uint8_t pin);

/**
  * @brief clear gpio pin of pdm_data0
  */
void pdm_data0_io_deinit(void);

/**
  * @brief       configure gpio pin as pdm_data1
  * @param  pin  Specific GPIO pin 
  */
void pdm_data1_io_init(uint8_t pin);

/**
  * @brief disable pin mux function from pdm_data1
  */
void pdm_data1_io_deinit(void);

/** @}*/


/** @}*/

#endif

