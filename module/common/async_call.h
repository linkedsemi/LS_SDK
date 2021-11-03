#ifndef ASYNC_CALL_H_
#define ASYNC_CALL_H_
#include "fifo.h"

struct async_call_param
{
    void (*func)(void *);
    void *param;
};

void async_call(void (*func)(void *),void *param,struct fifo_env *fifo);

bool async_process(struct fifo_env *fifo);


#endif
