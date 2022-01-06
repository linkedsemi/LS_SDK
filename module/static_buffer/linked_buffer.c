#include <stdarg.h>
#include <string.h>
#include "linked_buffer.h"
#include "ls_dbg.h"
#include "compile_flag.h"
#define LINKED_BUF_ASSERT(...) LS_ASSERT(__VA_ARGS__)

__attribute__((weak)) void co_list_init(struct co_list *list){}
__attribute__((weak)) void co_list_push_back(struct co_list *list, struct co_list_hdr *list_hdr){}
__attribute__((weak)) struct co_list_hdr *co_list_pop_front(struct co_list *list){return NULL;}
__attribute__((weak)) uint16_t co_list_size(struct co_list *list){return 0;}

ROM_SYMBOL void linked_buf_init(linked_buffer_t *ptr,uint16_t element_size,uint16_t buf_length,uint8_t *buf,uint8_t *ref_cnt)
{
    co_list_init(&ptr->allocatable);
    ptr->buf = buf;
    ptr->ref_cnt = ref_cnt;
    if(ref_cnt)
    {
        memset(ref_cnt,0,buf_length);
    }
    ptr->element_size = element_size;
    ptr->buf_length = buf_length;
    uint16_t i;
    for(i=0;i<buf_length;++i)
    {
        co_list_push_back(&ptr->allocatable,(struct co_list_hdr *)&buf[i*element_size]);
    }
}

ROM_SYMBOL LL_PKT_ISR void *linked_buf_alloc(linked_buffer_t *ptr)
{
    struct co_list_hdr *hdr = co_list_pop_front(&ptr->allocatable);
    if(hdr)
    {
        uint16_t idx = linked_buf_get_elem_idx(ptr,hdr);
        if(ptr->ref_cnt){
            ptr->ref_cnt[idx] += 1;
        }
    }
    return hdr;
}

LL_PKT_ISR static bool linked_buf_hdl_sanity_check(linked_buffer_t *buf_hdl,uint8_t *ptr)
{
    if((ptr-buf_hdl->buf)%buf_hdl->element_size)
    {
        return false;
    }
    if(ptr<buf_hdl->buf || ptr>= &buf_hdl->buf[buf_hdl->buf_length*buf_hdl->element_size])
    {
        return false;
    }
    return true;

}

ROM_SYMBOL LL_PKT_ISR uint8_t linked_buf_release(linked_buffer_t *ptr,void *hdr)
{
    LINKED_BUF_ASSERT(linked_buf_hdl_sanity_check(ptr,hdr));
    uint16_t idx = linked_buf_get_elem_idx(ptr,hdr);
    if(ptr->ref_cnt)
    {
        LINKED_BUF_ASSERT(ptr->ref_cnt[idx]);
        ptr->ref_cnt[idx] -= 1;
        if(ptr->ref_cnt[idx]==0)
        {
            co_list_push_back(&ptr->allocatable, hdr);
        }
        return ptr->ref_cnt[idx];
    }else
    {
        co_list_push_back(&ptr->allocatable, hdr);
        return 0;
    }
}

ROM_SYMBOL LL_PKT_ISR uint16_t linked_buf_get_elem_idx(linked_buffer_t *ptr,void *hdr)
{
    uint8_t *elem = hdr;
    LINKED_BUF_ASSERT((elem-(uint8_t *)ptr->buf)%ptr->element_size==0);
    return (elem-(uint8_t *)ptr->buf)/ptr->element_size;
}

ROM_SYMBOL LL_PKT_ISR void *linked_buf_get_elem_by_idx(linked_buffer_t *ptr,uint16_t idx)
{
    return &ptr->buf[ptr->element_size*idx];
}

ROM_SYMBOL uint16_t linked_buf_available_size(linked_buffer_t *ptr)
{
    return co_list_size(&ptr->allocatable);
}

ROM_SYMBOL LL_PKT_ISR bool linked_buf_is_allocatable(linked_buffer_t *ptr)
{
    return co_list_pick(&ptr->allocatable)? true : false;
}

ROM_SYMBOL uint8_t linked_buf_get_ref_cnt_by_idx(linked_buffer_t *ptr,uint16_t idx)
{
    LINKED_BUF_ASSERT(ptr->ref_cnt);
    return ptr->ref_cnt[idx];
}

ROM_SYMBOL uint8_t linked_buf_retain(linked_buffer_t *ptr,void *hdr)
{
    LINKED_BUF_ASSERT(linked_buf_hdl_sanity_check(ptr,hdr));
    uint16_t idx = linked_buf_get_elem_idx(ptr,hdr);
    if(ptr->ref_cnt)
    {
        return ++ptr->ref_cnt[idx];
    }else
    {
        return 0;
    }
}

ROM_SYMBOL bool linked_buf_contain_element(linked_buffer_t *ptr,void *hdr)
{
    bool contain = false;
    if(linked_buf_hdl_sanity_check(ptr,hdr))
    {
        if(ptr->ref_cnt)
        {
            uint16_t idx = linked_buf_get_elem_idx(ptr,hdr);
            contain = linked_buf_get_ref_cnt_by_idx(ptr,idx) ? true : false;
        }else
        {
            contain = true;
            struct co_list_hdr *avail = co_list_pick(&ptr->allocatable);
            while(avail)
            {
                if(avail == hdr)
                {
                    contain = false;
                    break; 
                }else
                {
                    avail = co_list_next(avail);
                }
            }
        }
    }
    return contain;
}

ROM_SYMBOL uint16_t linked_buf_element_size(linked_buffer_t *ptr)
{
    return ptr->element_size;
}

ROM_SYMBOL uint16_t linked_buf_element_num(linked_buffer_t *ptr)
{
    return ptr->buf_length;
}
