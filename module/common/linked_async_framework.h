#ifndef LINKED_ASYNC_FRAMEWORK_H_
#define LINKED_ASYNC_FRAMEWORK_H_
#include "co_list.h"

struct linked_async_inst_s;

typedef bool (*linked_async_callback_t)(struct linked_async_inst_s *,struct co_list_hdr *,void *,uint8_t);

typedef struct linked_async_inst_s
{
	struct co_list list;
	void (*pre_process)(struct linked_async_inst_s *,struct co_list_hdr *);
	linked_async_callback_t common_callback;
}linked_async_inst_t;

void linked_async_init(linked_async_inst_t *inst,void (*pre_process)(linked_async_inst_t *,struct co_list_hdr *),linked_async_callback_t common_callback);

void linked_async_start(linked_async_inst_t *inst,struct co_list_hdr *hdr);

void linked_async_end(linked_async_inst_t *inst,void *cb_dummy,uint8_t cb_status);

struct co_list_hdr *linked_async_current_pick(linked_async_inst_t *inst);

struct co_list_hdr *linked_async_list_pop(linked_async_inst_t *inst);

uint16_t linked_async_list_current_size(linked_async_inst_t *inst);

#endif

