    PRESERVE8
    THUMB
    AREA    |.text.stack_assert_asm|, CODE, READONLY
    FRAME UNWIND ON
stack_assert_asm PROC
    EXPORT stack_assert_asm
    IMPORT stack_assert_c
    PUSH {LR}
    FRAME PUSH {LR}
    MOV R3,LR
    BL stack_assert_c
    POP {PC}
    ENDP

    END
    
