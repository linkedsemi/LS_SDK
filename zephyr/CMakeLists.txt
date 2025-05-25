if(CONFIG_SOC_LE5010)

  zephyr_include_directories(
    .
    ../soc
    ../soc/arm_cm
    ../soc/arm_cm/le501x
    ../soc/arm_cm/le501x/integration
    ../hal_driver/api
    ../hal_driver/inc
  )

  zephyr_library_include_directories(
    .
    ../module/common
    ../module/debug
    ../module/tinyfs
    ../module/ble
    ../module/static_buffer
  )

  zephyr_library_sources(
    ../module/common/common.c
    ../module/debug/ls_dbg.c
    ../module/debug/log.c
    ../hal_driver/src/calc_div.c
    ../hal_driver/src/ls_hal_trng.c
    ../hal_driver/src/ls_hal_flash.c
    ../hal_driver/src/ls_hal_flash_qspi.c
    ../hal_driver/src/ls_hal_flash_swint.c
    ../hal_driver/src/ls_hal_qspi.c
    ../hal_driver/src/ls_hal_ecc.c
    ../hal_driver/src/ls_hal_pis.c
    ../soc/arm_cm/systick.c
    ../soc/arm_cm/le501x/cpu.c
    ../soc/arm_cm/le501x/platform.c
    ../soc/arm_cm/le501x/sleep.c
    ../soc/arm_cm/le501x/stack_var.c
    ../soc/arm_cm/le501x/sys_stat.c
    ../soc/arm_cm/le501x/compiler/gnu/swint_asm.S
    ../soc/arm_cm/le501x/compiler/gnu/sleep_asm.S
    ../soc/arm_cm/le501x/compiler/gnu/stack_asm.S
    ../soc/arm_cm/le501x/compiler/gnu/delay_asm.S
    ../soc/arm_cm/le501x/integration/calc_acc.c
    ../soc/arm_cm/le501x/integration/ls_soc_gpio.c
    ../soc/arm_cm/le501x/integration/ls_msp_trng.c
    ../soc/arm_cm/le501x/integration/ls_msp_ecc.c
    ../soc/arm_cm/le501x/integration/ls_msp_pis.c
    ../soc/arm_cm/le501x/integration/ls_msp_qspi.c
    ../soc/arm_cm/le501x/integration/modem_rf_le501x.c
  )

  zephyr_link_libraries(
    ll_fw
    -L${CMAKE_CURRENT_SOURCE_DIR}/../soc/arm_cm/le501x/bin
  )

  zephyr_linker_sources(
    RAMFUNC_SECTION
    xip_banned.ld
  )

  zephyr_linker_sources(
    NOINIT
    reset_retain.ld
  )

  set_property(GLOBAL APPEND PROPERTY extra_post_build_commands
    COMMAND ${PYTHON_EXECUTABLE} ${ZEPHYR_CURRENT_MODULE_DIR}/tools/le501x/info_sbl_merge.py 
    ${ZEPHYR_CURRENT_MODULE_DIR}/soc/arm_cm/le501x/bin/bram.bin 0x18026000 ${CMAKE_BINARY_DIR}/zephyr/info_sbl.hex)
  set_property(GLOBAL APPEND PROPERTY extra_post_build_commands
    COMMAND ${PYTHON_EXECUTABLE} ${ZEPHYR_CURRENT_MODULE_DIR}/tools/hexmerge.py 
    ${CMAKE_BINARY_DIR}/zephyr/info_sbl.hex ${ZEPHYR_CURRENT_MODULE_DIR}/soc/arm_cm/le501x/bin/ll_fw.hex 
    ${CMAKE_BINARY_DIR}/zephyr/${CONFIG_KERNEL_BIN_NAME}.hex > production.hex)
endif()

if(CONFIG_SOC_LS1010)
  zephyr_include_directories(
    . 
    ../soc
    ../soc/rv32
    ../soc/rv32/leo
    ../hal_driver/inc
    ../hal_driver/api
    ../module/common
    # ../module/crc
    ../module/debug
    ../module/debug/RTT
    # ../module/static_buffer
    # ../module/tinyfs
    # ../module/tinycrypt/lib/include
  )

  zephyr_library_include_directories(
        # .
        # ../soc
        # ../soc/rv32
        # ../soc/rv32/leo
        #'module/calendar
        ../module/common
        ../module/crc
        ../module/debug
        ../module/debug/RTT
        ../module/static_buffer
        # ../module/tinyfs
        # ../module/tinycrypt/lib/include
        #'module/micro-ecc
        #'module/adpcm
        #'module/ble
        #'module/ble/prf
  )

  zephyr_library_sources(
    ../soc/rv32/startup.c
    ../module/common/common.c
    ../module/common/circular_doubly_linked_list.c
    ../module/common/linked_async_framework.c
    ../module/common/async_call.c
    ../module/common/sw_timer.c
    ../module/crc/crc16.c
    # ../module/debug/log.c
    ../module/debug/ls_dbg.c
    ../module/debug/RTT/SEGGER_RTT.c
    ../module/static_buffer/linked_buffer.c
    ../module/static_buffer/fifo.c
    ../hal_driver/src/ls_hal_flash_swint.c
    ../hal_driver/src/ls_hal_sha.c
    ../hal_driver/src/ls_hal_sm4.c
    ../hal_driver/src/ls_hal_crc.c
    ../hal_driver/src/ls_hal_ecc.c
    ../hal_driver/src/ls_hal_can.c
    ../hal_driver/src/ls_hal_fdcan.c
    # ../hal_driver/src/ls_hal_trngv2.c
    # ../hal_driver/src/ls_hal_crypt.c
    ../hal_driver/src/ls_hal_qspiv2.c
    ../hal_driver/src/ls_hal_flash_qspiv2.c
    ../hal_driver/src/ls_hal_flash.c
    ../hal_driver/src/ls_hal_cache.c
    ../hal_driver/src/ls_hal_comp.c
    ../hal_driver/src/ls_hal_uart.c
    ../hal_driver/src/ls_hal_dwuart.c
    ../hal_driver/src/ls_hal_dwuart_dma.c
    ../hal_driver/src/ls_hal_adcv2.c
    ../hal_driver/src/ls_hal_adcv2_dma.c
    ../hal_driver/src/ls_hal_dac.c
    ../hal_driver/src/ls_hal_dac_dma.c
    ../hal_driver/src/ls_hal_uart_dma.c
    ../hal_driver/src/ls_hal_ssi.c
    ../hal_driver/src/ls_hal_spi_i2s.c
    ../hal_driver/src/ls_hal_spi_i2s_dma.c
    ../hal_driver/src/ls_hal_spis.c
    ../hal_driver/src/ls_hal_spis_dma.c
    ../hal_driver/src/ls_hal_timer.c
    ../hal_driver/src/ls_hal_touchkey.c
    ../hal_driver/src/ls_hal_i2c.c
    ../hal_driver/src/ls_hal_kscan.c
    ../hal_driver/src/ls_hal_rtcv2.c
    ../hal_driver/src/ls_hal_pwm.c
    ../hal_driver/src/ls_hal_pdm.c
    ../hal_driver/src/ls_hal_pdm_dma.c
    ../hal_driver/src/ls_hal_dmacv3.c
    ../hal_driver/src/ls_hal_cec.c
    ../hal_driver/src/ls_hal_owm.c
    ../hal_driver/src/ls_hal_cap.c
    # ../hal_driver/src/ls_hal_i2c_dma.c
    ../hal_driver/src/ls_hal_pis.c
    ../hal_driver/src/ls_hal_ssi_dma.c
    ../hal_driver/src/ls_hal_wwdg.c
    ../hal_driver/src/ls_hal_iwdgv2.c
    ../hal_driver/src/ls_hal_ps2h.c
    ../soc/rv32/systick.c
    # ../soc/rv32/int_call_asm.S
    ../soc/rv32/leo/cpu.c
    ../soc/rv32/leo/sleep_asm.S
    ../soc/rv32/leo/exception_entry.S
    ../soc/rv32/leo/delay_asm.S
    ../soc/rv32/leo/ls_msp_qspiv2.c
    ../soc/rv32/leo/ls_msp_uart.c
    ../soc/rv32/leo/ls_msp_comp.c
    ../soc/rv32/leo/ls_msp_crc.c
    ../soc/rv32/leo/ls_msp_sha.c
    ../soc/rv32/leo/ls_msp_sm4.c
    # ../soc/rv32/leo/ls_msp_trngv2.c
    ../soc/rv32/leo/ls_msp_touchkey.c
    ../soc/rv32/leo/ls_msp_crypt.c
    ../soc/rv32/leo/ls_msp_adc.c
    ../soc/rv32/leo/ls_msp_ecc.c
    ../soc/rv32/leo/ls_msp_dac.c
    ../soc/rv32/leo/ls_msp_can.c
    ../soc/rv32/leo/ls_msp_fdcan.c
    ../soc/rv32/leo/ls_msp_spi_i2s.c
    ../soc/rv32/leo/ls_msp_spis.c
    ../soc/rv32/leo/ls_msp_pis.c
    ../soc/rv32/leo/ls_soc_gpio.c
    # 'rv32/leo/exception_isr.c
    ../soc/rv32/leo/sys_stat.c
    ../soc/rv32/leo/platform.c
    ../soc/rv32/leo/efuse.c
    ../soc/rv32/leo/sleep.c
    ../soc/rv32/leo/ls_msp_ssi.c
    ../soc/rv32/leo/ls_msp_timer.c
    ../soc/rv32/leo/ls_msp_i2c.c
    ../soc/rv32/leo/ls_msp_kscan.c
    ../soc/rv32/leo/ls_msp_rtc.c
    ../soc/rv32/leo/ls_msp_pwm.c
    ../soc/rv32/leo/ls_msp_dmacv3.c
    ../soc/rv32/leo/ls_msp_pdm.c
    ../soc/rv32/leo/ls_msp_cec.c
    ../soc/rv32/leo/ls_msp_owm.c
    ../soc/rv32/leo/ls_msp_cap.c
    ../soc/rv32/leo/sw_timer_port.c
    ../soc/rv32/leo/ls_msp_iwdg.c
    ../soc/rv32/leo/ls_msp_wwdg.c
    ../soc/rv32/leo/ls_msp_ps2h.c
    ../soc/rv32/leo/ls_msp_cache.c
  )

  # zephyr_link_libraries(

  # )
  
  zephyr_linker_sources(
    RAMFUNC_SECTION
    xip_banned.ld
  )

  zephyr_linker_sources(
    NOINIT
    reset_retain.ld
  )

  zephyr_linker_sources(ROM_START SORT_KEY -1vectors leo_sbl.ld)

  zephyr_ld_options("-T ${ZEPHYR_CURRENT_MODULE_DIR}/soc/rv32/leo/rom_sym.txt")
  
  zephyr_compile_definitions(LEO)
  zephyr_compile_definitions(GLOBAL_OUTPUT_LVL=0)
  message("ZEPHYR_CURRENT_MODULE_DIR: ${ZEPHYR_CURRENT_MODULE_DIR}  ${ZEPHYR_CURRENT_MODULE_DIR}/tools/leo/info_sbl_merge.py")
  message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/info_sbl.bin
    COMMAND ${PYTHON_EXECUTABLE} ${ZEPHYR_CURRENT_MODULE_DIR}/tools/leo/info_sbl_merge.py 
    ${ZEPHYR_CURRENT_MODULE_DIR}/soc/rv32/leo/bin/bram.bin 
    ${CMAKE_CURRENT_BINARY_DIR}/info_sbl.bin
    DEPENDS ${ZEPHYR_CURRENT_MODULE_DIR}/tools/leo/info_sbl_merge.py ${ZEPHYR_CURRENT_MODULE_DIR}/soc/rv32/leo/bin/bram.bin
  )
  add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/__info_array.c
      COMMAND ${PYTHON_EXECUTABLE} ${ZEPHYR_CURRENT_MODULE_DIR}/tools/bin2c/bin2c.py
      ${CMAKE_CURRENT_BINARY_DIR}/info_sbl.bin __info_array 80 4 > ${CMAKE_CURRENT_BINARY_DIR}/__info_array.c
      DEPENDS ${ZEPHYR_CURRENT_MODULE_DIR}/tools/bin2c/bin2c.py  ${CMAKE_CURRENT_BINARY_DIR}/info_sbl.bin
  )
  add_custom_target(
      build_info_obj
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/info_sbl.bin ${CMAKE_CURRENT_BINARY_DIR}/__info_array.c
  )
  # add_library(info_obj OBJECT ${ZEPHYR_CURRENT_MODULE_DIR}/zephyr/leo_build_info/__info_array.c)
  # add_dependencies(info_obj build_info_obj)

  zephyr_library_sources(
    ${CMAKE_CURRENT_BINARY_DIR}/__info_array.c
  )

  # riscv64-unknown-elf-objdump.exe -d -r -x  zephyr.elf > production.asm
endif()

if(CONFIG_SOC_LSQSH)
  zephyr_include_directories(
    . 
    ../soc
    ../soc/rv32
    ../soc/rv32/qsh
    ../soc/rv32/qsh/include
    ../hal_driver/inc
    ../hal_driver/api
    ../hal_driver/api/otbn
    ../module/common
    ../module/debug
    ../module/debug/semihosting/riscv
    ../module/debug/RTT
    ../module/static_buffer
  )

  zephyr_library_include_directories(
        ../module/common
        ../module/crc
        ../module/debug
        ../module/debug/semihosting/riscv
        ../module/debug/RTT
        ../module/static_buffer
  )

  zephyr_library_sources(
    ../soc/rv32/startup.c
    ../module/common/common.c
    ../module/common/circular_doubly_linked_list.c
    ../module/common/linked_async_framework.c
    ../module/common/async_call.c
    ../module/crc/crc16.c
    ../module/debug/semihosting/riscv/semihosting.c
    ../module/debug/RTT/SEGGER_RTT.c
    ../module/static_buffer/linked_buffer.c
    ../module/static_buffer/fifo.c
    ../hal_driver/src/ls_hal_uart.c
    ../hal_driver/src/ls_hal_dwuart.c
    ../hal_driver/src/ls_hal_sha.c
    ../hal_driver/src/ls_hal_sm4.c
    ../hal_driver/src/ls_hal_crypt.c
    ../hal_driver/src/ls_hal_otbn.c
    ../hal_driver/src/otbn/ls_hal_otbn_sha256.c
    ../hal_driver/src/otbn/ls_hal_otbn_sha384.c
    ../hal_driver/src/otbn/ls_hal_otbn_sha512.c
    ../hal_driver/src/otbn/ls_hal_otbn_ecc256.c
    ../hal_driver/src/otbn/ls_hal_otbn_ecc384.c
    ../hal_driver/src/otbn/ls_hal_otbn_sm2.c
    ../hal_driver/src/otbn/text_array/ecc256_base_mult_text.c
    ../hal_driver/src/otbn/text_array/ecc256_ecdsa_verify_text.c
    ../hal_driver/src/otbn/text_array/ecc256_scalar_mult_text.c
    ../hal_driver/src/otbn/text_array/ecc384_ecdsa_verify_text.c
    ../hal_driver/src/otbn/text_array/sha256_text.c
    ../hal_driver/src/otbn/text_array/sha512_text.c
    ../hal_driver/src/otbn/text_array/sm2_text.c
    ../soc/rv32/qsh/ls_msp_otbn.c
    ../soc/rv32/systick.c
    # ../soc/rv32/int_call_asm.S
    ../soc/rv32/qsh/cpu.c
    ../soc/rv32/qsh/sleep_asm.S
    ../soc/rv32/qsh/exception_entry.S
    ../soc/rv32/qsh/delay_asm.S
    ../soc/rv32/qsh/ls_msp_uart.c
    ../soc/rv32/qsh/ls_msp_dmacv3.c
    ../soc/rv32/qsh/ls_soc_gpio.c
    ../soc/rv32/qsh/sys_stat.c
    ../soc/rv32/qsh/platform.c
    ../module/static_buffer/fifo.c
    ../hal_driver/src/ls_hal_qspiv2.c
    ../hal_driver/src/ls_hal_flash_qspiv2.c
    ../hal_driver/src/ls_hal_flash.c
    ../hal_driver/src/ls_hal_flash_swint.c
    ../hal_driver/src/ls_hal_cache.c
    ../hal_driver/src/ls_hal_ssi.c
    ../hal_driver/src/ls_hal_dmacv3.c
    ../soc/rv32/qsh/ls_msp_qspiv2.c
    ../soc/rv32/qsh/ls_msp_cache.c
    ../soc/rv32/qsh/ls_msp_ssi.c
    ../hal_driver/src/ls_hal_iwdgv2.c
    ../soc/rv32/qsh/ls_msp_iwdg.c
  )

  zephyr_linker_sources(
    RAMFUNC_SECTION
    xip_banned.ld
  )

  zephyr_linker_sources(
    NOINIT
    reset_retain.ld
  )

  zephyr_compile_definitions(QSH)
  zephyr_compile_definitions(CONFIG_FSTACK_PROTECTOR)
  # riscv64-unknown-elf-objdump.exe -d -r -x  zephyr.elf > production.asm

  set_property(GLOBAL APPEND PROPERTY extra_post_build_commands
    COMMAND ${PYTHON_EXECUTABLE} ${ZEPHYR_CURRENT_MODULE_DIR}/tools/qsh/header_merge_non_secure.py
    -i ${PROJECT_BINARY_DIR}/${CONFIG_KERNEL_BIN_NAME}.bin
    -o ${PROJECT_BINARY_DIR}/${CONFIG_KERNEL_BIN_NAME}_flash_${CONFIG_FLASH_BASE_ADDRESS}.bin
    -a ${CONFIG_SRAM_BASE_ADDRESS}
  )

endif()
