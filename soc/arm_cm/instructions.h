#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include <stdint.h>
#include <stdbool.h>
uint32_t b_bl_instruction_32_generate(uint32_t src_addr,uint32_t dst_addr,bool link);
#endif
