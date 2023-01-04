#ifndef LS_SOC_PINMUX_H_
#define LS_SOC_PINMUX_H_
#include <stdint.h>

/**
  * @brief Init IO for SPI Flash (CS CLK DQ0 DQ1)
  */
void pinmux_hal_flash_init(void);

/**
  * @brief DeInit SPI Flash IO
  */
void pinmux_hal_flash_deinit(void);

/**
  * @brief Init IO for QSPI Flash (CS CLK DQ0 DQ1 DQ2 DQ3)
  */
void pinmux_hal_flash_quad_init(void);

/**
  * @brief DeInit QSPI Flash IO
  */
void pinmux_hal_flash_quad_deinit(void);

/**
  * @brief  GPIO initilization
  * @param  clk  Specific GPIO pin
  */
void pinmux_ssi_clk_init(uint8_t clk);

/**
  * @brief     GPIO initilization as ssi nss0
  * @param  nss0  Specific GPIO pin
  */
void pinmux_ssi_nss0_init(uint8_t nss0);

/**
  * @brief    Set pin mux function to ssi nss1
  * @param  nss1   Specific GPIO pin
  */
void pinmux_ssi_nss1_init(uint8_t nss1);

/**
  * @brief  config GPIO  to ssi dq0
  * @param  dq0  Specific GPIO pin
  */
void pinmux_ssi_dq0_init(uint8_t dq0);

/**
  * @brief   Set pin mux function to ssi dq1
  * @param  dq1   Specific GPIO pin
  */
void pinmux_ssi_dq1_init(uint8_t dq1);

/**
  * @brief   Set pin mux function to ssi dq2
  * @param  dq2   Specific GPIO pin
  */
void pinmux_ssi_dq2_init(uint8_t dq2);

/**
  * @brief  Set pin mux function to ssi dq3
  * @param  dq3   Specific GPIO pin
  */
void pinmux_ssi_dq3_init(uint8_t dq3);

/**
  * @brief  Set pin mux function to spi2 master clk
  * @param  clk   Specific GPIO pin
  */
void pinmux_spi2_master_clk_init(uint8_t clk);

/**
  * @brief   Set pin mux function to spi2 master nss
  * @param  nss  Specific GPIO pin
  */
void pinmux_spi2_master_nss_init(uint8_t nss);

/**
  * @brief   Set pin mux function to spi2 master mosi
  * @param  mosi   Specific GPIO pin
  */
void pinmux_spi2_master_mosi_init(uint8_t mosi);

/**
  * @brief    Set pin mux function to spi2 master mosi
  * @param  miso   Specific GPIO pin
  */
void pinmux_spi2_master_miso_init(uint8_t miso);

/**
  * @brief  Set pin mux function to spi2 slave clk
  * @param  clk   Specific GPIO pin
  */
void pinmux_spi2_slave_clk_init(uint8_t clk);

/**
  * @brief   Set pin mux function to spi2 slave nss
  * @param  nss  Specific GPIO pin
  */
void pinmux_spi2_slave_nss_init(uint8_t nss);

/**
  * @brief   Set pin mux function to spi2 slave mosi
  * @param  mosi   Specific GPIO pin
  */
void pinmux_spi2_slave_mosi_init(uint8_t mosi);

/**
  * @brief    Set pin mux function to spi2 slave mosi
  * @param  miso   Specific GPIO pin
  */
void pinmux_spi2_slave_miso_init(uint8_t miso);

/**
  * @brief  clear pin mux function of spi2_clk
  */
void pinmux_spi2_clk_deinit(void);

/**
  * @brief  clear pin mux functions of spi2_nss
  */
void pinmux_spi2_nss_deinit(void);

/**
  * @brief   clear pin mux function of spi2_mosi
  */
void pinmux_spi2_mosi_deinit(void);

/**
  * @brief   clear pin mux function of spi2_miso
  */
void pinmux_spi2_miso_deinit(void);

/**
  * @brief  Set pin mux function to iis2 master ck
  * @param  ck   Specific GPIO pin
  */
void pinmux_iis2_master_ck_init(uint8_t ck);

/**
  * @brief   Set pin mux function to iis2 master ws
  * @param   ws  Specific GPIO pin
  */
void pinmux_iis2_master_ws_init(uint8_t ws);

/**
  * @brief   Set pin mux function to iis2 master sd
  * @param   sd   Specific GPIO pin
  * @param   mode GPIO input/output mode
  */
void pinmux_iis2_master_sd_init(uint8_t sd, uint8_t mode);

/**
  * @brief    Set pin mux function to iis2 master mck
  * @param    mck   Specific GPIO pin
  */
void pinmux_iis2_master_mck_init(uint8_t mck);

/**
  * @brief  Set pin mux function to iis2 slave ck
  * @param  ck   Specific GPIO pin
  */
void pinmux_iis2_slave_ck_init(uint8_t ck);

/**
  * @brief   Set pin mux function to iis2 slave ws
  * @param   ws  Specific GPIO pin
  */
void pinmux_iis2_slave_ws_init(uint8_t ws);

/**
  * @brief   Set pin mux function to iis2 slave sd
  * @param   sd   Specific GPIO pin
  * @param   mode GPIO input/output mode
  */
void pinmux_iis2_slave_sd_init(uint8_t sd, uint8_t mode);

/**
  * @brief    Set pin mux function to iis2 slave mck
  * @param    mck   Specific GPIO pin
  */
void pinmux_iis2_slave_mck_init(uint8_t mck);

/**
  * @brief  clear pin mux function of iis2_clk
  */
void pinmux_iis2_ck_deinit(void);

/**
  * @brief  clear pin mux functions of iis2_ws
  */
void pinmux_iis2_ws_deinit(void);

/**
  * @brief   clear pin mux function of iis2_sd
  */
void pinmux_iis2_sd_deinit(void);

/**
  * @brief   clear pin mux function of iis2_mck
  */
void pinmux_iis2_mck_deinit(void);

/**
  * @brief       Set pin mux function as iic1_io_init
  * @param  scl  Specific GPIO pin 
  * @param  sda  Specific GPIO pin 
  */
void pinmux_iic1_init(uint8_t scl,uint8_t sda);

/**
  * @brief clean pin mux function  of iic1
  */
void pinmux_iic1_deinit(void);


/**
  * @brief         Set pin mux function as iic2_io_init
  * @param  scl    Specific GPIO pin  
  * @param  sda    Specific GPIO pin 
  */
void pinmux_iic2_init(uint8_t scl,uint8_t sda);


/**
  * @brief clean pin mux function of iic2
  */
void pinmux_iic2_deinit(void);

/**
  * @brief         Set pin mux function to uart1 (config of gpio)
  * @param  txd    Specific GPIO pin  
  * @param   rxd   Specific GPIO pin   
  */
void pinmux_uart1_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart1
  */
void pinmux_uart1_deinit(void);

/**
  * @brief          Set pin mux function to uart1_7816
   * @param  txd    Specific GPIO pin  
  * @param   ck     Specific GPIO pin  
  */
void pinmux_uart1_7816_init(uint8_t txd,uint8_t ck);

/**
  * @brief clear pin mux function of uart1_7816
  */
void pinmux_uart1_7816_deinit(void);

/**
  * @brief          Set pin mux function to uart2
  * @param  txd     Specific GPIO pin  
  * @param rxd      Specific GPIO pin  
  */
void pinmux_uart2_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart2
  */
void pinmux_uart2_deinit(void);

/**
  * @brief       Set pin mux function to uart3
  * @param  txd   Specific GPIO pin  
  * @param rxd   Specific GPIO pin   
  */
void pinmux_uart3_init(uint8_t txd,uint8_t rxd);

/**
  * @brief clear  pin mux function of uart3
  */
void pinmux_uart3_deinit(void);

/**
  * @brief Set pin mux function to adtim1 
  * @param   pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_adtim1_ch1_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear  mux function of pin adtim1
  */
void pinmux_adtim1_ch1_deinit(void);

/**
  * @brief Set  mux function of pin adtmi1 of channel 2
  * @param   pin Specific GPIO pin  
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void pinmux_adtim1_ch2_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin adtim1
  */
void pinmux_adtim1_ch2_deinit(void);

/**
  * @brief Set  mux function of pin adtmi1 of channel 3
  * @param   pin Specific GPIO pin  
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_adtim1_ch3_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief Set pin mux function
  */
void pinmux_adtim1_ch3_deinit(void);

/**
  * @brief  Set  mux function of pin adtmi1 of channel 4
  * @param   pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_adtim1_ch4_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin adtim1 of channel 4
  */
void pinmux_adtim1_ch4_deinit(void);

/**
  * @brief      Set mux function of pin adtim1  of ch1n as input and output
  * @param  pin  Specific GPIO pin 
  */
void pinmux_adtim1_ch1n_init(uint8_t pin);

/**
  * @brief clear mux function of pin adtim1 of ch1n
  */
void pinmux_adtim1_ch1n_deinit(void);

/**
  * @brief           Set mux function of pin adtim1 of ch2n
  * @param  pin      Specific GPIO pin 
  */

void pinmux_adtim1_ch2n_init(uint8_t pin);

/**
  * @brief          clear  mux function of pin adtim1 of ch2n
  */
void pinmux_adtim1_ch2n_deinit(void);

/**
    @brief          Set mux function of pin adtim1 of ch3n
  * @param  pin     Specific GPIO pin 
  */
void pinmux_adtim1_ch3n_init(uint8_t pin);

/**
  @brief             clear mux function of pin adtim1 of ch3n
  */
void pinmux_adtim1_ch3n_deinit(void);

/**
    @brief           Set mux function of pin adtim1 of etr
  * @param  pin      Specific GPIO pin 
  */
void pinmux_adtim1_etr_init(uint8_t pin);

/**
  @brief      clear mux function of pin adtim1 of etr
  */
void pinmux_adtim1_etr_deinit(void);

/**
    @brief           configure gpio pin as adtim1_bk
  * @param  pin      Specific GPIO pin 
  */
void pinmux_adtim1_bk_init(uint8_t pin);

/**
 @brief clear  mux function of pin adtim1_bk 
  */
void pinmux_adtim1_bk_deinit(void);

/**
  *  @brief Set mux function of pin gptima1 of channel 1
  *  @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptima1_ch1_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptima1 of channel 1
  */
void pinmux_gptima1_ch1_deinit(void);

/**
  * @brief  Set mux function of pin gptima1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptima1_ch2_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief   clear  mux function of pin gptima1 of channel 2
  */
void pinmux_gptima1_ch2_deinit(void);

/**
  * @brief                Set mux function of pin gptima1 of channel 3
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptima1_ch3_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief       clear mux function of pin gptima1 of channel 3
  */
void pinmux_gptima1_ch3_deinit(void);

/**
  * @brief                Set mux function of pin gptima1 of channel 4
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptima1_ch4_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief     clear mux function of pin gptima1 of channel 4
  */
void pinmux_gptima1_ch4_deinit(void);

/**
  * @brief       Set mux function of pin gptima1 of channel etr
  * @param  pin  Specific GPIO pin 
  */
void pinmux_gptima1_etr_init(uint8_t pin);

/**
  * @brief      clear mux function of pin gptima1 of etr
  */
void pinmux_gptima1_etr_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 1
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptimb1_ch1_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 1
  */
void pinmux_gptimb1_ch1_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptimb1_ch2_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief        clear mux function of pin gptimb1 of channel 2
  */
void pinmux_gptimb1_ch2_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 3
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptimb1_ch3_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 3
  */
void pinmux_gptimb1_ch3_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 4
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void pinmux_gptimb1_ch4_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimb1 of channel 4
  */
void pinmux_gptimb1_ch4_deinit(void);

/**
  * @brief Set mux function of pin gptimb1 of etr
  * @param  pin  Specific GPIO pin 
  */
void pinmux_gptimb1_etr_init(uint8_t pin);

/**
  * @brief   clear mux function of pin gptimb1 of etr
  */
void pinmux_gptimb1_etr_deinit(void);

/**
  * @brief Set mux function of pin gptima1 of channel 1
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level 
  */
void pinmux_gptimc1_ch1_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimc1 of channel 1
  */
void pinmux_gptimc1_ch1_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of channel 1
  * @param  pin  Specific GPIO pin 
  */
void pinmux_gptimc1_ch1n_init(uint8_t pin);

/**
  * @brief clear mux function of pin gptimc1 of channel 1
  */
void pinmux_gptimc1_ch1n_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of channel 2
  * @param  pin Specific GPIO pin 
  * @param  output config pin output status
  * @param  default_val  config pin output high level or low level
  */
void pinmux_gptimc1_ch2_init(uint8_t pin,bool output,uint8_t default_val);

/**
  * @brief clear mux function of pin gptimc1 of channel 2
  */
void pinmux_gptimc1_ch2_deinit(void);

/**
  * @brief Set mux function of pin gptimc1 of bk
  * @param  pin   Specific GPIO pin 
  */
void pinmux_gptimc1_bk_init(uint8_t pin);

/**
  * @brief clear mux function of pin gptimc1 of bk
  */
void pinmux_gptimc1_bk_deinit(void);

/**
  * @brief Set mux function of pin gadc12b of in0
  */
void pinmux_adc12b_in0_init(void);

/**
  * @brief clear mux function of pin gadc12b of in0
  */
void pinmux_adc12b_in0_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in1
  */
void pinmux_adc12b_in1_init(void);

/**
  * @brief clear mux function of pin adc12b of in1
  */
void pinmux_adc12b_in1_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in2
  */
void pinmux_adc12b_in2_init(void);

/**
  * @brief clear mux function of pin adc12b of in2
  */
void pinmux_adc12b_in2_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in3
  */
void pinmux_adc12b_in3_init(void);

/**
  * @brief clear mux function of pin adc12b of in3
  */
void pinmux_adc12b_in3_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in4
  */
void pinmux_adc12b_in4_init(void);

/**
  * @brief clear mux function of pin adc12b of in4
  */
void pinmux_adc12b_in4_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in5
  */
void pinmux_adc12b_in5_init(void);

/**
  * @brief clear  mux function of pin adc12b of in5
  */
void pinmux_adc12b_in5_deinit(void);

/**
  * @brief Set mux function of pin  adc12b of in6
  */
void pinmux_adc12b_in6_init(void);

/**
  * @brief clear  mux function of pin adc12b of in6
  */
void pinmux_adc12b_in6_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in7
  */
void pinmux_adc12b_in7_init(void);

/**
  * @brief clear mux function of pin adc12b of in7
  */
void pinmux_adc12b_in7_deinit(void);

/**
  * @brief Set mux function of pin adc12b of in8
  */
void pinmux_adc12b_in8_init(void);

/**
  * @brief clear mux function of pin adc12b of in8
  */
void pinmux_adc12b_in8_deinit(void);

/**
  * @brief        configure gpio pin as pdm_clk
  * @param  pin   Specific GPIO pin 
  */
void pinmux_pdm_clk_init(uint8_t pin);

/**
  * @brief clear gpio of pdm_clk
  */
void pinmux_pdm_clk_deinit(void);

/**
  * @brief       configure gpio of pdm_data0
  * @param  pin  Specific GPIO pin 
  */
void pinmux_pdm_data0_init(uint8_t pin);

/**
  * @brief clear gpio pin of pdm_data0
  */
void pinmux_pdm_data0_deinit(void);

/**
  * @brief       configure gpio pin as pdm_data1
  * @param  pin  Specific GPIO pin 
  */
void pinmux_pdm_data1_init(uint8_t pin);

/**
  * @brief disable pin mux function from pdm_data1
  */
void pinmux_pdm_data1_deinit(void);



#endif
