#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "compile_flag.h"
#include "co_math.h"

ROM_SYMBOL void rand_gen_by_word(uint8_t *ptr,uint8_t word_num)
{
    while(word_num--)
    {
        uint32_t x = rand_fn();
        memcpy(ptr,&x,sizeof(uint32_t));    
        ptr += sizeof(uint32_t);
    }
}

ROM_SYMBOL void memcpy32(uint32_t *dest, const uint32_t *src, uint32_t size_word)
{
    while(size_word--)
    {
        *dest++ = *src++;
    }
}

ROM_SYMBOL void memset32(uint32_t *start,uint32_t data,uint32_t size_word)
{
    while(size_word--)
    {
        *start++ = data;
    }
}

ROM_SYMBOL LL_PKT_ISR uint8_t count_trailing_zeros(uint32_t x)
{
    uint32_t i;
    for (i = 0; i < 32; i++)
    {
        if (x & 1<<i )
            break;
    }
    return i;
}
