if(CONFIG_SOC_LE5010)

  zephyr_include_directories(
    .
    ../soc
    ../soc/arm_cm
    ../soc/arm_cm/le501x
    ../soc/arm_cm/le501x/integration
    ../module/common
    ../module/debug
    ../module/debug/RTT
    ../module/tinyfs
    ../module/ble
    ../module/static_buffer
    ../hal_driver/api
    ../hal_driver/inc
  )

  zephyr_sources(
    ../module/common/common.c
    ../module/debug/ls_dbg.c
    ../module/debug/log.c
    ../module/debug/RTT/SEGGER_RTT.c
    ../hal_driver/src/calc_div.c
    ../hal_driver/src/ls_hal_trng.c
    ../hal_driver/src/ls_hal_flash.c
    ../hal_driver/src/ls_hal_flash_qspi.c
    ../hal_driver/src/ls_hal_flash_swint.c
    ../hal_driver/src/ls_hal_qspi.c
    ../hal_driver/src/ls_hal_ecc.c
    ../hal_driver/src/ls_hal_pis.c
    ../soc/arm_cm/swint_handler.c
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