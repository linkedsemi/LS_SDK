#include "circular_doubly_linked_list.h"
#include "compile_flag.h"

ROM_SYMBOL void cdll_init(struct cdll *list)
{
    list->first = NULL;
}

ROM_SYMBOL void cdll_push_back(struct cdll *list, struct cdll_hdr *hdr)
{
    if (list->first)
    {
        struct cdll_hdr *last = list->first->prev;
        last->next = hdr;
        hdr->prev = last;
        hdr->next = list->first;
        list->first->prev = hdr;
    }
    else
    {
        list->first = hdr;
        hdr->next = hdr;
        hdr->prev = hdr;
    }
}

ROM_SYMBOL LL_PKT_ISR struct cdll_hdr *cdll_pop_front(struct cdll *list)
{
    if (list->first)
    {
        struct cdll_hdr *head = list->first;
        if (head->next == head)
        {
            list->first = NULL;
        }
        else
        {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            list->first = head->next;
        }
        head->next = NULL;
        head->prev = NULL;
        return head;
    }
    else
    {
        return NULL;
    }
}

ROM_SYMBOL void cdll_extract(struct cdll *list, struct cdll_hdr *hdr)
{
    if (hdr->prev == hdr)
    {
        list->first = NULL;
    }
    else
    {
        hdr->prev->next = hdr->next;
        hdr->next->prev = hdr->prev;
        if (list->first == hdr)
        {
            list->first = hdr->next;
        }
    }
    hdr->next = NULL;
    hdr->prev = NULL;
}

ROM_SYMBOL void cdll_insert_before(struct cdll *list, struct cdll_hdr *ref_hdr, struct cdll_hdr *hdr_to_insert)
{
    bool update_head = list->first == ref_hdr;
    ref_hdr->prev->next = hdr_to_insert;
    hdr_to_insert->prev = ref_hdr->prev;
    ref_hdr->prev = hdr_to_insert;
    hdr_to_insert->next = ref_hdr;
    if (update_head)
    {
        list->first = hdr_to_insert;
    }
}

ROM_SYMBOL void cdll_insert_after(struct cdll_hdr *ref_hdr, struct cdll_hdr *hdr_to_insert)
{
    ref_hdr->next->prev = hdr_to_insert;
    hdr_to_insert->next = ref_hdr->next;
    ref_hdr->next = hdr_to_insert;
    hdr_to_insert->prev = ref_hdr;
}

ROM_SYMBOL void cdll_insert(struct cdll *list, struct cdll_hdr *hdr, bool (*cmp)(struct cdll_hdr *, struct cdll_hdr *))
{
    if (list->first == NULL)
    {
        list->first = hdr;
        hdr->next = hdr;
        hdr->prev = hdr;
        return;
    }
    bool inserted = false;
    struct cdll_hdr *ptr = list->first->prev;
    do
    {
        if (cmp(hdr, ptr))
        {
            ptr->next->prev = hdr;
            hdr->next = ptr->next;
            hdr->prev = ptr;
            ptr->next = hdr;
            inserted = true;
            break;
        }
        else
        {
            ptr = ptr->prev;
        }
    } while (ptr != list->first->prev);
    if (inserted == false)
    {
        ptr->next = hdr;
        hdr->next = list->first;
        hdr->prev = ptr;
        list->first->prev = hdr;
        list->first = hdr;
    }
}

ROM_SYMBOL LL_PKT_ISR struct cdll_hdr *cdll_first(struct cdll *list)
{
    return list->first;
}

ROM_SYMBOL struct cdll_hdr *cdll_next(struct cdll_hdr *hdr)
{
    return hdr->next;
}

ROM_SYMBOL struct cdll_hdr *cdll_prev(struct cdll_hdr *hdr)
{
    return hdr->prev;
}

ROM_SYMBOL bool cdll_is_elem_linked(struct cdll_hdr *hdr)
{
    return hdr->next && hdr->prev ? true : false;
}
