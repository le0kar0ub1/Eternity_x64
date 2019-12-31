#include "linkedList.h"
#include "memory.h"

list_t *list_create(void)
{
    list_t * list = kalloc(sizeof(list_t));
    return (list);
}

uint32 list_size(list_t *list)
{
    if(!list)
        return (0);
    return (list->size);
}

void *list_remove_node(list_t *list, listnode_t *node)
{
    void *item = node->item;
    if(list->head == node)
        return (list_remove_front(list));
    else if(list->tail == node)
        return (list_remove_back(list));
    else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        list->size--;
        kfree(node);
    }
    return (item);
}

listnode_t *list_insert_front(list_t *list, void *item)
{
    listnode_t *t = kalloc(sizeof(listnode_t));
    list->head->prev = t;
    t->next = list->head;
    t->item = item;

    if(!list->head)
        list->tail = t;

    list->head = t;
    list->size++;
    return (t);
}

void list_insert_back(list_t *list, void *item)
{
    listnode_t *t = kalloc(sizeof(listnode_t));
    t->prev = list->tail;
    if(list->tail)
        list->tail->next = t;
    t->item = item;

    if(!list->head)
        list->head = t;

    list->tail = t;
    list->size++;
}

void *list_remove_front(list_t *list)
{
    if(!list->head)
        return (NULL);
    listnode_t *t = list->head;
    void *item = t->item;
    list->head = t->next;
    if(list->head)
        list->head->prev = NULL;
    kfree(t);
    list->size--;
    return (item);
}

void *list_remove_back(list_t *list)
{
    if(!list->head)
        return (NULL);
    listnode_t *t = list->tail;
    void *item = t ->item;
    list->tail = t->prev;
    if (list->tail)
        list->tail->next = NULL;
    kfree(t);
    list->size--;
    return (item);
}

void list_push(list_t *list, void *item)
{
    list_insert_back(list, item);
}

listnode_t *list_pop(list_t *list)
{
    if(!list->head)
        return (NULL);
    listnode_t *t = list->tail;
    list->tail = t->prev;
    if(list->tail)
        list->tail->next = NULL;
    list->size--;
    return t;
}

void *list_peek_front(list_t *list)
{
    if(!list->head)
        return (NULL);
    return (list->head->item);
}

void *list_peek_back(list_t *list)
{
    if(!list->tail)
        return (NULL);
    return (list->tail->item);
}


int list_contain(list_t *list, void *item)
{
    int idx = 0;
    list_foreach(listnode, list) {
        if(listnode->item == item)
            return (idx);
        idx++;
    }
    return (-1);
}

listnode_t *list_get_node_by_index(list_t *list, int index)
{
    if(index < 0 || index >= (int)list_size(list))
        return (NULL);
    int curr = 0;
    list_foreach(listnode, list) {
        if(index == curr)
            return (listnode);
        curr++;
    }
    return (NULL);
}

void *list_remove_by_index(list_t *list, int index)
{
    listnode_t *node = list_get_node_by_index(list, index);
    return (list_remove_node(list, node));
}

void list_destroy(list_t *list)
{
    listnode_t * node = list->head;
    while(node != NULL) {
        listnode_t * save = node;
        node = node->next;
        kfree(save);
    }
    kfree(list);
}

void listnode_destroy(listnode_t *node)
{
    kfree(node);
}
