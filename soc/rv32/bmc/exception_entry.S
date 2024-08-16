
    .option rvc
    .section .text.exception_entry
    .align 6
    .global exception_entry
    .type   exception_entry, %function
exception_entry:
    .cfi_sections .debug_frame
    .cfi_startproc
    addi    sp, sp, -0x4c
    .cfi_def_cfa_offset 0x4c
    sw      a0, 0x3c(sp)
    sw      a1, 0x38(sp)
    sw      a2, 0x34(sp)
    sw      a3, 0x30(sp)
    sw      a4, 0x2c(sp)
    sw      a5, 0x28(sp)
    sw      a6, 0x24(sp)
    sw      a7, 0x20(sp)
    sw      t0, 0x1c(sp)
    sw      t1, 0x18(sp)
    sw      t2, 0x14(sp)
    sw      t3, 0x10(sp)
    sw      t4, 0x0c(sp)
    sw      t5, 0x08(sp)
    sw      t6, 0x04(sp)
    sw      ra, 0x00(sp)
    csrr    t0, mepc
    sw      t0, 0x48(sp)
    csrr    t1, mcause
    sw      t1, 0x44(sp)
    csrr    t2, mstatus
    sw      t2, 0x40(sp)
    .cfi_offset ra,-0x4c
    bgtz    t1, trap_handler
int_call:
    csrrwi  t0, mnxti, 8
    beqz    t0, exception_exit
    lw      t0, 0(t0)
    jalr    t0   
    csrc    mstatus, 8  # disable global irq to fetch mnxti correctly
    j       int_call
exception_exit:
    lw      ra, 0x00(sp)
    .cfi_restore ra
    lw      t6, 0x04(sp)
    lw      t5, 0x08(sp)
    lw      t4, 0x0c(sp)
    lw      t3, 0x10(sp)
    lw      t2, 0x14(sp)
    lw      t1, 0x18(sp)
    lw      t0, 0x1c(sp)
    lw      a7, 0x20(sp)
    lw      a6, 0x24(sp)
    lw      a5, 0x28(sp)
    lw      a4, 0x2c(sp)
    lw      a3, 0x30(sp)
    lw      a2, 0x34(sp)
    lw      a1, 0x38(sp)
    lw      a0, 0x40(sp)
    csrw    mstatus, a0
    lw      a0, 0x44(sp)
    csrw    mcause, a0
    lw      a0, 0x48(sp)
    csrw    mepc, a0
    lw      a0, 0x3c(sp)
    addi    sp, sp, 0x4c
    .cfi_def_cfa_offset 0
    mret
    .cfi_endproc
    .size	exception_entry, . - exception_entry

    .global trap_handler
    .type   trap_handler, %function
trap_handler:
    j trap_handler
    