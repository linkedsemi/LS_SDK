#ifndef SW_CACHE_H_
#define SW_CACHE_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "co_list.h"
#include "linked_buffer.h"

struct sw_cache
{
    linked_buffer_t *cache_buf;
    struct co_list list;
};

#define DEF_SW_CACHE(cache_hdl,type,size) \
    DEF_LINKED_BUF(_##cache_hdl##_cache_buf,type,size); \
    struct sw_cache cache_hdl

#define INIT_SW_CACHE(cache_hdl) \
    INIT_LINKED_BUF(_##cache_hdl##_cache_buf);\
    sw_cache_init(&cache_hdl,&_##cache_hdl##_cache_buf);

void sw_cache_init(struct sw_cache *ptr,linked_buffer_t *buf);

bool sw_cache_full(struct sw_cache *ptr);

void *sw_cache_add(struct sw_cache *ptr,void (*copy)(struct co_list_hdr const *,va_list *),...);

void *sw_cache_del(struct sw_cache *ptr,bool (*compare)(struct co_list_hdr const *,va_list *),...);

void *sw_cache_remove_oldest(struct sw_cache *ptr);

void *sw_cache_search(struct sw_cache *ptr,bool (*compare)(struct co_list_hdr const *,va_list *),...);

void sw_cache_clean_up(struct sw_cache *ptr,void (*free)(void *));
#endif
