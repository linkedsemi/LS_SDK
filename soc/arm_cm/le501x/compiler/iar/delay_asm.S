    MODULE delay_asm
    PUBLIC arm_cm_delay_asm
    SECTION `__iar_init$$done.xip_banned.arm_cm_delay_asm`:CODE
    THUMB
arm_cm_delay_asm
    SUBS r0,r0,#1
    CMP r0,#0
    BNE arm_cm_delay_asm
    BX LR
    
    END