#include "async_call.h"
#include "ls_dbg.h"
#include "compile_flag.h"
#include "cpu.h"

ROM_SYMBOL LL_PKT_ISR void async_call(void (*func)(void *),void *param,struct fifo_env *fifo)
{
    struct async_call_param env;
    env.func = func;
    env.param = param;
    uint32_t cpu_stat = ENTER_CRITICAL();
    bool not_full = dword_fifo_put(fifo, &env);
    EXIT_CRITICAL(cpu_stat);
    LS_ASSERT(not_full);
    (void)(not_full);
}

ROM_SYMBOL bool async_process(struct fifo_env *fifo)
{
    struct async_call_param env;
    uint32_t cpu_stat = ENTER_CRITICAL();
    bool not_empty = dword_fifo_get(fifo,&env); 
    EXIT_CRITICAL(cpu_stat);
    if(not_empty)
    {
        env.func(env.param);
    }
    return not_empty;
}
