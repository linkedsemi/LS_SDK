#include <stdbool.h>
#include "linked_async_framework.h"
#include "compile_flag.h"

ROM_SYMBOL struct co_list_hdr *linked_async_current_pick(linked_async_inst_t *inst)
{
	return co_list_pick(&inst->list);
}

ROM_SYMBOL void linked_async_init(linked_async_inst_t *inst,void (*pre_process)(linked_async_inst_t *,struct co_list_hdr *),linked_async_callback_t common_callback)
{
	co_list_init(&inst->list);
	inst->pre_process = pre_process;
	inst->common_callback = common_callback;
}

ROM_SYMBOL void linked_async_start(linked_async_inst_t *inst,struct co_list_hdr *hdr)
{
	struct co_list_hdr *head_hdr = co_list_pick(&inst->list);
	co_list_push_back(&inst->list, hdr);
	if(head_hdr==NULL)
	{
		inst->pre_process(inst, hdr);
	}
}

ROM_SYMBOL void linked_async_end(linked_async_inst_t *inst,void *cb_dummy,uint8_t cb_status)
{
	struct co_list_hdr *hdr = co_list_pop_front(&inst->list);	
	bool new_elem_added = inst->common_callback(inst,hdr,cb_dummy,cb_status);
	if(new_elem_added == false)
	{
		struct co_list_hdr *next_hdr = co_list_pick(&inst->list);
		if(next_hdr)
		{
			inst->pre_process(inst,next_hdr);
		}
	}
}

ROM_SYMBOL struct co_list_hdr *linked_async_list_pop(linked_async_inst_t *inst)
{
	return co_list_pop_front(&inst->list);
}

ROM_SYMBOL uint16_t linked_async_list_current_size(linked_async_inst_t *inst)
{
	return co_list_size(&inst->list);
}

