#ifndef FIFO_H_
#define FIFO_H_
#include <stdint.h>
#include <stdbool.h>
#include "common.h"

struct fifo_env{
    void *buf;
    uint16_t rd_idx;
    uint16_t wr_idx;
    uint16_t length;
    uint16_t item_size;
};

#define DEF_FIFO(name,type,length) \
    type _##name##_fifo_array[(length)];\
    struct fifo_env name;

#define INIT_FIFO(name) sw_fifo_init(&name,_##name##_fifo_array,ARRAY_LEN(_##name##_fifo_array),sizeof(_##name##_fifo_array[0]))

void sw_fifo_init(struct fifo_env *ptr,void *buf,uint16_t length, uint16_t item_size);

bool sw_fifo_full(struct fifo_env *ptr);

bool sw_fifo_empty(struct fifo_env *ptr);

void sw_fifo_flush(struct fifo_env *ptr);

uint16_t sw_fifo_element_amount(struct fifo_env *ptr);

bool general_fifo_put(struct fifo_env *ptr,void *data);

bool dword_fifo_put(struct fifo_env *ptr,void *data);

bool general_fifo_get(struct fifo_env *ptr,void *data);

bool dword_fifo_get(struct fifo_env *ptr,void *data);

#endif
