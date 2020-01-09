#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "stdint.h"

typedef struct listnode {
    struct listnode *prev;
    struct listnode *next;
    void            *item;
} listnode_t;

typedef struct list {
    listnode_t *head;
    listnode_t *tail;
    uint64_t   size;
} list_t;

#define list_foreach(t, list) for(listnode_t *t = list->head; t != NULL; t = t->next)

#endif