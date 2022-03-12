    .option rvc
    .align 1
#if (ROM_CODE==1 || BOOT_RAM==1 || defined(FLASH_PROG_ALGO))
    .section .text.rv32_delay_asm,"x"
#else
    .section .xip_banned,"x"
#endif
    .globl rv32_delay_asm
    .type rv32_delay_asm,%function
rv32_delay_asm:
    sub a0,a0,a1
    bnez a0,rv32_delay_asm
    ret
    .size	rv32_delay_asm, . - rv32_delay_asm
    
    .end
    