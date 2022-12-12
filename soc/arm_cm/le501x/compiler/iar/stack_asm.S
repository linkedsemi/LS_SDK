    MODULE stack_asm
    PUBLIC stack_assert_asm
    EXTERN stack_assert_c
    SECTION `.text.stack_assert_asm`:CODE
    THUMB
stack_assert_asm
    PUSH {LR}
    MOV R3,LR
    BL stack_assert_c
    POP {PC}
    
    END