import os
import subprocess
file_path = os.path.basename(__file__)
root_path = os.path.realpath(os.path.join(file_path,'../'))
os.chdir(root_path)

def proj_gen(path,ic,ide):
    os.chdir(path)
    process = subprocess.Popen(['scons','tool=progen','ide='+ide,'ic='+ic],shell=True)
    process.wait()
    os.chdir(root_path)

def keil_proj_gen(path,ic):
    proj_gen(path,ic,'uvision5')

def iar_proj_gen(path,ic):
    proj_gen(path,ic,'iar')

def le501x_proj_gen(path):
    keil_proj_gen(path,'le501x')
    iar_proj_gen(path,'le501x')

def lm3050_proj_gen(path):
    keil_proj_gen(path,'lm3050')
    iar_proj_gen(path,'lm3050')

# le501x
le501x_proj_gen('examples/ble/ble_advertiser')
le501x_proj_gen('examples/ble/ble_ancs')
le501x_proj_gen('examples/ble/ble_at_proj')
le501x_proj_gen('examples/ble/ble_dis')
le501x_proj_gen('examples/ble/ble_dis_freertos')
le501x_proj_gen('examples/ble/ble_fota_server')
le501x_proj_gen('examples/ble/ble_hid')
le501x_proj_gen('examples/ble/ble_hid_dmic')
le501x_proj_gen('examples/ble/ble_mult_roles')
le501x_proj_gen('examples/ble/ble_single_role')
le501x_proj_gen('examples/ble/ble_pairing_master_role')
le501x_proj_gen('examples/ble/ble_pairing_slave_role')
le501x_proj_gen('examples/ble/ble_tk')
le501x_proj_gen('examples/ble/ble_uart_server')
le501x_proj_gen('examples/ble/ble_uart_server_mult_link')
le501x_proj_gen('examples/ble/fota')
le501x_proj_gen('examples/ble/host_test')

le501x_proj_gen('examples/mesh/genie_mesh/tmall_mesh')
le501x_proj_gen('examples/mesh/genie_mesh/tmall_mesh_gatt')
le501x_proj_gen('examples/mesh/genie_mesh/tmall_mesh_gatt_ls_ota')
le501x_proj_gen('examples/mesh/genie_mesh/tmall_mesh_gatt_glp')
le501x_proj_gen('examples/mesh/ls_mesh')
le501x_proj_gen('examples/mesh/sig_mesh/sig_mesh_provee')
le501x_proj_gen('examples/mesh/sig_mesh/sig_mesh_provee_alexa')
le501x_proj_gen('examples/mesh/sig_mesh/sig_mesh_provee_auto_prov')
le501x_proj_gen('examples/mesh/sig_mesh/sig_mesh_provisioner')

le501x_proj_gen('examples/peripheral/adc/adc_amic_sampling')
le501x_proj_gen('examples/peripheral/adc/adc_blocking_sampling')
le501x_proj_gen('examples/peripheral/adc/adc_multi_channel')
le501x_proj_gen('examples/peripheral/adc/adc_multi_channel_dma')
le501x_proj_gen('examples/peripheral/adc/adc_single_channel')
le501x_proj_gen('examples/peripheral/adc/adc_analog_wdg')
le501x_proj_gen('examples/peripheral/crypt/ecb_cbc_it')
le501x_proj_gen('examples/peripheral/crypt/ecb_cbc_polling')
le501x_proj_gen('examples/peripheral/crypt/ecb_it_padding')
le501x_proj_gen('examples/peripheral/gpio')
le501x_proj_gen('examples/peripheral/i2c/i2c_dma')
le501x_proj_gen('examples/peripheral/i2c/i2c_it')
le501x_proj_gen('examples/peripheral/i2c/i2c_polling')
le501x_proj_gen('examples/peripheral/i2c/ll_i2c_it')
le501x_proj_gen('examples/peripheral/i2c/ll_i2c_polling')
le501x_proj_gen('examples/peripheral/pdm')
le501x_proj_gen('examples/peripheral/rtc')
le501x_proj_gen('examples/peripheral/software_calendar')
le501x_proj_gen('examples/peripheral/software_timers')
le501x_proj_gen('examples/peripheral/spi_i2s/i2s_dma_master')
le501x_proj_gen('examples/peripheral/spi_i2s/i2s_dma_slave')
le501x_proj_gen('examples/peripheral/spi_i2s/i2s_it_master')
le501x_proj_gen('examples/peripheral/spi_i2s/i2s_it_slave')
le501x_proj_gen('examples/peripheral/spi_i2s/i2s_polling_master')
le501x_proj_gen('examples/peripheral/spi_i2s/i2s_polling_slave')
le501x_proj_gen('examples/peripheral/spi_i2s/ll_spi_it')
le501x_proj_gen('examples/peripheral/spi_i2s/ll_spi_polling')
le501x_proj_gen('examples/peripheral/spi_i2s/spi_dma_master')
le501x_proj_gen('examples/peripheral/spi_i2s/spi_dma_slave')
le501x_proj_gen('examples/peripheral/spi_i2s/spi_it_master')
le501x_proj_gen('examples/peripheral/spi_i2s/spi_it_slave')
le501x_proj_gen('examples/peripheral/spi_i2s/spi_polling_master')
le501x_proj_gen('examples/peripheral/spi_i2s/spi_polling_slave')
le501x_proj_gen('examples/peripheral/ssi/ll_ssi_it')
le501x_proj_gen('examples/peripheral/ssi/ssi_dma')
le501x_proj_gen('examples/peripheral/ssi/ssi_it')
le501x_proj_gen('examples/peripheral/timer/Basic_PWM')
le501x_proj_gen('examples/peripheral/timer/Basic_TIM')
le501x_proj_gen('examples/peripheral/timer/DTC_PWM')
le501x_proj_gen('examples/peripheral/timer/Input_Capture')
le501x_proj_gen('examples/peripheral/tk/tk_it_dp')
le501x_proj_gen('examples/peripheral/tk/tk_it_lp')
le501x_proj_gen('examples/peripheral/tk/tk_polling')
le501x_proj_gen('examples/peripheral/uart/ll_uart_it')
le501x_proj_gen('examples/peripheral/uart/ll_uart_polling')
le501x_proj_gen('examples/peripheral/uart/uart_dma')
le501x_proj_gen('examples/peripheral/uart/uart_it')
le501x_proj_gen('examples/peripheral/uart/uart_polling')
le501x_proj_gen('examples/peripheral/wdg/iwdg')
le501x_proj_gen('examples/peripheral/wdg/wwdg')
le501x_proj_gen('examples/prop_24g/ls_prop_24g')
le501x_proj_gen('examples/prop_24g/ls_prop_24g_freertos')


# LM3050
lm3050_proj_gen('examples/peripheral/adcv2/adc_amic_sampling')
lm3050_proj_gen('examples/peripheral/adcv2/adc_blocking_sampling')
lm3050_proj_gen('examples/peripheral/adcv2/adc_multi_channel')
lm3050_proj_gen('examples/peripheral/adcv2/adc_multi_channel_dma')
lm3050_proj_gen('examples/peripheral/adcv2/adc_single_channel')
lm3050_proj_gen('examples/peripheral/adcv2/adc_analog_wdg')
lm3050_proj_gen('examples/peripheral/can/CAN_LoopBack')
lm3050_proj_gen('examples/peripheral/can/CAN_Normal')
lm3050_proj_gen('examples/peripheral/comp/comp_dac')
lm3050_proj_gen('examples/peripheral/comp/comp_internal')
lm3050_proj_gen('examples/peripheral/crypt/ecb_cbc_it')
lm3050_proj_gen('examples/peripheral/crypt/ecb_cbc_polling')
lm3050_proj_gen('examples/peripheral/crypt/ecb_it_padding')
lm3050_proj_gen('examples/peripheral/gpio')
lm3050_proj_gen('examples/peripheral/i2c/i2c_dma')
lm3050_proj_gen('examples/peripheral/i2c/i2c_it')
lm3050_proj_gen('examples/peripheral/i2c/i2c_polling')
lm3050_proj_gen('examples/peripheral/i2c/ll_i2c_it')
lm3050_proj_gen('examples/peripheral/i2c/ll_i2c_polling')
lm3050_proj_gen('examples/peripheral/rtcv2')
lm3050_proj_gen('examples/peripheral/sha/sha_it')
lm3050_proj_gen('examples/peripheral/sha/sha_polling')
lm3050_proj_gen('examples/peripheral/sm4/sm4_it')
lm3050_proj_gen('examples/peripheral/sm4/sm4_polling')
lm3050_proj_gen('examples/peripheral/software_calendar')
lm3050_proj_gen('examples/peripheral/software_timers')
lm3050_proj_gen('examples/peripheral/spi_i2s/i2s_dma_master')
lm3050_proj_gen('examples/peripheral/spi_i2s/i2s_dma_slave')
lm3050_proj_gen('examples/peripheral/spi_i2s/i2s_it_master')
lm3050_proj_gen('examples/peripheral/spi_i2s/i2s_it_slave')
lm3050_proj_gen('examples/peripheral/spi_i2s/i2s_polling_master')
lm3050_proj_gen('examples/peripheral/spi_i2s/i2s_polling_slave')
lm3050_proj_gen('examples/peripheral/spi_i2s/ll_spi_it')
lm3050_proj_gen('examples/peripheral/spi_i2s/ll_spi_polling')
lm3050_proj_gen('examples/peripheral/spi_i2s/spi_dma_master')
lm3050_proj_gen('examples/peripheral/spi_i2s/spi_dma_slave')
lm3050_proj_gen('examples/peripheral/spi_i2s/spi_it_master')
lm3050_proj_gen('examples/peripheral/spi_i2s/spi_it_slave')
lm3050_proj_gen('examples/peripheral/spi_i2s/spi_polling_master')
lm3050_proj_gen('examples/peripheral/spi_i2s/spi_polling_slave')
lm3050_proj_gen('examples/peripheral/ssi/ll_ssi_it')
lm3050_proj_gen('examples/peripheral/ssi/ssi_dma')
lm3050_proj_gen('examples/peripheral/ssi/ssi_it')
lm3050_proj_gen('examples/peripheral/timer/Basic_PWM')
lm3050_proj_gen('examples/peripheral/timer/Basic_TIM')
lm3050_proj_gen('examples/peripheral/timer/DTC_PWM')
lm3050_proj_gen('examples/peripheral/timer/Input_Capture')
lm3050_proj_gen('examples/peripheral/touchkey/touchkey_it')
lm3050_proj_gen('examples/peripheral/touchkey/touchkey_polling')
lm3050_proj_gen('examples/peripheral/uart/ll_uart_it')
lm3050_proj_gen('examples/peripheral/uart/ll_uart_polling')
lm3050_proj_gen('examples/peripheral/uart/uart_dma')
lm3050_proj_gen('examples/peripheral/uart/uart_it')
lm3050_proj_gen('examples/peripheral/uart/uart_polling')
lm3050_proj_gen('examples/peripheral/wdg/iwdg')
lm3050_proj_gen('examples/peripheral/wdg/wwdg')