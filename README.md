# Linkedsemi SDK

For production purpose, please download the release package. **Do not use the latest main branch.**

For detailed information, please visit [Linkedsemi Documentation Center](http://ls-doc.rtfd.io/).

量产项目，请下载使用Release版本发布包。**勿使用最新main分支。**

SDK详细介绍，请参考[凌思文档中心](http://ls-doc.rtfd.io/)


| Examples                                                                  | LE501X | LM3050 |
| ------------------------------------------------------------------------- | ------ | ------ |
| ble/ble_advertiser                                                        |  √     |        |
| ble/ble_ancs                                                              |  √     |        |
| ble/ble_at_proj                                                           |  √     |        |
| ble/ble_dis                                                               |  √     |        |
| ble/ble_dis_freertos                                                      |  √     |        |
| ble/ble_fota_server                                                       |  √     |        |
| ble/ble_hid                                                               |  √     |        |
| ble/ble_hid_dmic                                                          |  √     |        |
| ble/ble_mult_roles                                                        |  √     |        |
| ble/ble_pairing_master_role                                               |  √     |        |
| ble/ble_pairing_slave_role                                                |  √     |        |
| ble/ble_single_master                                                     |  √     |        |
| ble/ble_single_role                                                       |  √     |        |
| ble/ble_tk                                                                |  √     |        |
| ble/ble_uart_server                                                       |  √     |        |
| ble/ble_mult_services                                                     |  √     |        |
| ble/ble_uart_server_mult_link                                             |  √     |        |
| ble/fota                                                                  |  √     |        |
| ble/host_test                                                             |  √     |        |
| mesh/genie_mesh/tmall_mesh_gatt                                           |  √     |        |
| mesh/genie_mesh/tmall_mesh_gatt_glp                                       |  √     |        |
| mesh/genie_mesh/tmall_mesh_gatt_ls_ota                                    |  √     |        |
| mesh/ls_mesh                                                              |  √     |        |
| mesh/sig_mesh/sig_mesh_provee                                             |  √     |        |
| mesh/sig_mesh/sig_mesh_provee_alexa                                       |  √     |        |
| mesh/sig_mesh/sig_mesh_provee_auto_prov                                   |  √     |        |
| mesh/sig_mesh/sig_mesh_provisioner                                        |  √     |        |
| peripheral/adc/adc_amic_sampling                                          |  √     |        |
| peripheral/adc/adc_analog_wdg                                             |  √     |        |
| peripheral/adc/adc_blocking_sampling                                      |  √     |        |
| peripheral/adc/adc_multi_channel                                          |  √     |        |
| peripheral/adc/adc_multi_channel_dma                                      |  √     |        |
| peripheral/adc/adc_single_channel                                         |  √     |        |
| peripheral/adcv2/adc_amic_sampling                                        |        |  √     |
| peripheral/adcv2/adc_analog_wdg                                           |        |  √     |
| peripheral/adcv2/adc_blocking_sampling                                    |        |  √     |
| peripheral/adcv2/adc_multi_channel                                        |        |  √     |
| peripheral/adcv2/adc_multi_channel_dma                                    |        |  √     |
| peripheral/adcv2/adc_single_channel                                       |        |  √     |
| peripheral/can/CAN_LoopBack                                               |        |  √     |
| peripheral/can/CAN_Normal                                                 |        |  √     |
| peripheral/comp/comp_dac                                                  |        |  √     |
| peripheral/comp/comp_internal                                             |        |  √     |
| peripheral/crypt/des_ecb_cbc_it                                           |  √     |  √     |
| peripheral/crypt/des_ecb_cbc_polling                                      |  √     |  √     |
| peripheral/crypt/des_it_padding                                           |  √     |  √     |
| peripheral/crypt/ecb_cbc_it                                               |  √     |  √     |
| peripheral/crypt/ecb_cbc_polling                                          |  √     |  √     |
| peripheral/crypt/ecb_it_padding                                           |  √     |  √     |
| peripheral/dac/dual_dac_channel_dma_voltage                               |        |  √     |
| peripheral/dac/dual_dac_channel_voltage                                   |        |  √     |
| peripheral/dac/dual_dac_channel_wave                                      |        |  √     |
| peripheral/dac/single_dac_channel_dma_voltage                             |        |  √     |
| peripheral/dac/single_dac_channel_sine_wave                               |        |  √     |
| peripheral/dac/single_dac_channel_voltage                                 |        |  √     |
| peripheral/dac/single_dac_channel_wave                                    |        |  √     |
| peripheral/ecc/ecdh_it                                                    |  √     |  √     |
| peripheral/ecc/ecdh_polling                                               |  √     |  √     |
| peripheral/gpio                                                           |  √     |  √     |
| peripheral/i2c/i2c_dma                                                    |  √     |  √     |
| peripheral/i2c/i2c_it                                                     |  √     |  √     |
| peripheral/i2c/i2c_polling                                                |  √     |  √     |
| peripheral/i2c/ll_i2c_it                                                  |  √     |  √     |
| peripheral/i2c/ll_i2c_polling                                             |  √     |  √     |
| peripheral/iap/iap_application                                            |  √     |  √     |
| peripheral/iap/iap_bootloader                                             |  √     |  √     |
| peripheral/pdm_pingpong_dma                                               |  √     |        |
| peripheral/pdm_it                                                         |  √     |  √     |
| peripheral/rtc                                                            |  √     |        |
| peripheral/rtcv2                                                          |        |  √     |
| peripheral/sha/sha_it                                                     |        |  √     |
| peripheral/sha/sha_polling                                                |        |  √     |
| peripheral/sm4/sm4_it                                                     |        |  √     |
| peripheral/sm4/sm4_polling                                                |        |  √     |
| peripheral/software_calendar                                              |  √     |  √     |
| peripheral/software_timers                                                |  √     |  √     |
| peripheral/spi_i2s/i2s_dma_master                                         |  √     |  √     |
| peripheral/spi_i2s/i2s_dma_slave                                          |  √     |  √     |
| peripheral/spi_i2s/i2s_it_master                                          |  √     |  √     |
| peripheral/spi_i2s/i2s_it_slave                                           |  √     |  √     |
| peripheral/spi_i2s/i2s_polling_master                                     |  √     |  √     |
| peripheral/spi_i2s/i2s_polling_slave                                      |  √     |  √     |
| peripheral/spi_i2s/ll_spi_it                                              |  √     |  √     |
| peripheral/spi_i2s/ll_spi_polling                                         |  √     |  √     |
| peripheral/spi_i2s/spi_dma_master                                         |  √     |  √     |
| peripheral/spi_i2s/spi_dma_slave                                          |  √     |  √     |
| peripheral/spi_i2s/spi_it_master                                          |  √     |  √     |
| peripheral/spi_i2s/spi_it_slave                                           |  √     |  √     |
| peripheral/spi_i2s/spi_polling_master                                     |  √     |  √     |
| peripheral/spi_i2s/spi_polling_slave                                      |  √     |  √     |
| peripheral/ssi/ll_ssi_it                                                  |  √     |  √     |
| peripheral/ssi/ssi_dma                                                    |  √     |  √     |
| peripheral/ssi/ssi_it                                                     |  √     |  √     |
| peripheral/timer/Basic_PWM                                                |  √     |  √     |
| peripheral/timer/Basic_TIM                                                |  √     |  √     |
| peripheral/timer/DTC_PWM                                                  |  √     |  √     |
| peripheral/timer/Input_Capture                                            |  √     |  √     |
| peripheral/tk/tk_it_dp                                                    |  √     |        |
| peripheral/tk/tk_it_lp                                                    |  √     |        |
| peripheral/tk/tk_polling                                                  |  √     |        |
| peripheral/touchkey/touchkey_it                                           |        |  √     |
| peripheral/touchkey/touchkey_polling                                      |        |  √     |
| peripheral/trng/trng_it                                                   |  √     |  √     |
| peripheral/trng/trng_polling                                              |  √     |  √     |
| peripheral/uart/ll_uart_it                                                |  √     |  √     |
| peripheral/uart/ll_uart_polling                                           |  √     |  √     |
| peripheral/uart/uart_dma                                                  |  √     |  √     |
| peripheral/uart/uart_it                                                   |  √     |  √     |
| peripheral/uart/uart_polling                                              |  √     |  √     |
| peripheral/usb/usbd_cdc_msc                                               |        |  √     |
| peripheral/usb/usbd_cdc_msc_fatfs                                         |        |  √     |
| peripheral/usb/usbd_cdc_msc_fatfs_upgrade                                 |        |  √     |
| peripheral/usb/usbd_hid_composite                                         |        |  √     |
| peripheral/usb/usbd_hid_keyboard                                          |        |  √     |
| peripheral/usb/usbh_msc_file_explorer                                     |        |  √     |
| peripheral/wdg/iwdg                                                       |  √     |  √     |
| peripheral/wdg/wwdg                                                       |  √     |  √     |
| prop_24g/ls_prop_24g                                                      |  √     |        |
| prop_24g/ls_prop_24g_freertos                                             |  √     |        |
| utility/coremark                                                          |  √     |  √     |
| utility/flash_prog/arm_cm                                                 |  √     |  √     |
| utility/ram_test                                                          |  √     |  √     |
