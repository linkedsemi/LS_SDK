#ifndef BUILTIN_TIMER_H_
#define BUILTIN_TIMER_H_
#include <stdint.h>
#include <stdbool.h>
#include "linked_buffer.h"
#include "co_list.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef  CUSTOMIZED_MI_CONFIG_FILE
struct builtin_timer
{
    void (*timer_cb)(void *);
    void *param;
};
#else
struct builtin_timer
{
    void (*timer_cb)(void *);
    void *param;
    uint32_t timeout_value;       
    uint8_t mode;   //enum-type : mible_timer_mode
};
#endif

#define DEF_BUILTIN_TIMER_ENV(num) \
    DEF_LINKED_BUF(builtin_timer_env,struct builtin_timer,(num))

#define INIT_BUILTIN_TIMER_ENV() \
    do{ \
        INIT_LINKED_BUF(builtin_timer_env);\
        builtin_timer_env_register(&builtin_timer_env);\
    }while(0)

void builtin_timer_env_register(linked_buffer_t *env);

void *builtin_timer_create(void (*cb)(void *));

void builtin_timer_delete(void *timer);

void builtin_timer_stop(void *timer);

void builtin_timer_start(void *timer,uint32_t timeout,void *param);

bool builtin_timer_active(void *timer);

#ifdef __cplusplus
}
#endif

#endif

