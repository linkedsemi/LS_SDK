#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H_
#define CIRCULAR_DOUBLY_LINKED_LIST_H_
#include <stddef.h>
#include <stdbool.h>
struct cdll_hdr
{
	struct cdll_hdr *next;
	struct cdll_hdr *prev;
};

struct cdll
{
	struct cdll_hdr *first;
};

void cdll_init(struct cdll *list);

void cdll_push_back(struct cdll *list,struct cdll_hdr *hdr);

void cdll_push_front(struct cdll *list,struct cdll_hdr *hdr);

struct cdll_hdr *cdll_pop_front(struct cdll *list);

void cdll_extract(struct cdll *list,struct cdll_hdr *hdr);

void cdll_insert_before(struct cdll *list,struct cdll_hdr *ref_hdr,struct cdll_hdr *hdr_to_insert);

void cdll_insert_after(struct cdll_hdr *ref_hdr,struct cdll_hdr *hdr_to_insert);

void cdll_insert(struct cdll *list,struct cdll_hdr *hdr,bool (*cmp)(struct cdll_hdr *,struct cdll_hdr *));

struct cdll_hdr *cdll_first(struct cdll *list);

struct cdll_hdr *cdll_next(struct cdll_hdr *hdr);

struct cdll_hdr *cdll_prev(struct cdll_hdr *hdr);

bool cdll_is_elem_linked(struct cdll_hdr *hdr);
#endif
