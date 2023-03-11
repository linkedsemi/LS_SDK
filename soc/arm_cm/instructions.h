#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t b_bl_instruction_32_generate(uint32_t src_addr,uint32_t dst_addr,bool link);

#ifdef __cplusplus
}
#endif
#endif
