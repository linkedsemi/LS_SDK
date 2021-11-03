#ifndef WHITE_LIST_H_
#define WHITE_LIST_H_
#include <stdbool.h>
#include "hci_format.h"
#include "co_error.h"
#include "dev_addr_cache.h"
extern uint8_t white_list_size;

bool white_list_search(uint8_t addr_type,uint8_t *addr);

enum co_error le_clear_white_list(void);

enum co_error le_add_dev_to_white_list(struct ble_dev_addr *param);

enum co_error le_remove_dev_from_white_list(struct ble_dev_addr *param);

#endif
