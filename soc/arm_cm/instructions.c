#include "instructions.h"

union branch_instruction_32_u
{
    uint32_t ins;
    struct
    {
        uint32_t imm10:      10,
                 s:          1,
                 reserved0: 5,
                 imm11:      11,
                 j2:         1,
                 reserved1: 1,
                 j1:         1,
                 reserved2: 2;
    }s;
};

union branch_diff_u
{
    uint32_t diff;
    struct
    {
        uint32_t reserved0: 1,
                 imm11:      11,
                 imm10:      10,
                 i2:         1,
                 i1:         1,
                 s:          1,
                 reserved1: 7;
    }s;
};

uint32_t b_bl_instruction_32_generate(uint32_t src_addr,uint32_t dst_addr,bool link)
{
    union branch_instruction_32_u instruction;
    union branch_diff_u diff;
    diff.diff = dst_addr - src_addr - 4;
    instruction.s.imm11 = diff.s.imm11;
    instruction.s.imm10 = diff.s.imm10;
    instruction.s.j2 = ~(diff.s.s ^ diff.s.i2);
    instruction.s.j1 = ~(diff.s.s ^ diff.s.i1);
    instruction.s.s = diff.s.s;
    instruction.s.reserved0 = 0x1e;
    instruction.s.reserved1 = 1;
    instruction.s.reserved2 = link? 3 : 2;
    return instruction.ins;
}