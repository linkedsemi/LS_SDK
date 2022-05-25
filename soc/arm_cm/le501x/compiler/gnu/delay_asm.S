    .syntax unified
    .arch armv6-m
#if (ROM_CODE==1 || BOOT_RAM==1 || defined(FLASH_PROG_ALGO))
    .section .text.arm_cm_delay_asm,"x"
#else
    .section .xip_banned,"ax"
#endif
    .thumb
    .thumb_func
    .align 1
    .globl arm_cm_delay_asm
    .type arm_cm_delay_asm,%function
arm_cm_delay_asm:
    SUBS r0,r0,0x1
    CMP r0,0x0
    BNE arm_cm_delay_asm
    BX LR
    
    .size	arm_cm_delay_asm, . - arm_cm_delay_asm
