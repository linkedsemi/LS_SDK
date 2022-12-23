
    MODULE sleep_asm
    PUBLIC cpu_sleep_asm
    PUBLIC cpu_recover_asm
    EXTERN before_wfi
    EXTERN store_msp_psp_control
    EXTERN after_wfi
    EXTERN restore_msp_psp_control
    SECTION `__iar_init$$done.xip_banned.sleep_recover_asm`:CODE:NOROOT
    THUMB
cpu_sleep_asm:
    mov r0, r8
    mov r1, r9
    mov r2, r10
    mov r3, r11
    PUSH {R0,R1,R2,R3,R4,R5,R6,R7,LR}
    BL store_msp_psp_control
    BL before_wfi
    WFI
cpu_recover_asm:
    BL restore_msp_psp_control
    BL after_wfi
    POP {R0,R1,R2,R3,R4,R5,R6,R7}
    mov r8, r0
    mov r9, r1
    mov r10, r2
    mov r11, r3
    POP {PC}

    END