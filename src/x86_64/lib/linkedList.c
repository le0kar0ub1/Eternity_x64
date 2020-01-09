#include "linkedList.h"
#include "memory.h"

list_t *list_create(void)
{
    list_t *list = kalloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0x0;
    return (list);
}

listnode_t *list_init(list_t *list, listnode_t *new, void *item)
{
    list->head = new;
    list->tail = new;
    list->size++;
    new->prev = NULL;
    new->item = item;
    new->next = NULL;
    return (new);
}

uint32 list_size(list_t *list)
{
    if (!list)
        return (0);
    return (list->size);
}

void *list_remove_node(list_t *list, listnode_t *node)
{
    void *item = node->item;
    if (list->head == node)
        return (list_remove_front(list));
    else if (list->tail == node)
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
    listnode_t *new = kalloc(sizeof(listnode_t));

    /* then init the list if */
    if (!list->head && !list->tail)
        return (list_init(list, new, item));
    
    new->next = list->head;
    new->item = item;
    new->prev = NULL;

    list->head = new;
    list->size++;
    return (new);
}

listnode_t *list_insert_back(list_t *list, void *item)
{
    listnode_t *new = kalloc(sizeof(listnode_t));

    /* then init the list if */
    if (!list->head && !list->tail)
        return (list_init(list, new, item));
    
    new->prev = list->tail;
    new->item = item;
    new->next = NULL;

    list->tail = new;
    list->size++;
    return (new);
}

void *list_remove_front(list_t *list)
{
    if (!list->head)
        return (NULL);
    listnode_t *t = list->head;
    void *item = t->item;
    list->head = t->next;
    if (list->head)
        list->head->prev = NULL;
    kfree(t);
    list->size--;
    return (item);
}

void *list_remove_back(list_t *list)
{
    if (!list->head)
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
    if (!list->head)
        return (NULL);
    listnode_t *t = list->tail;
    list->tail = t->prev;
    if (list->tail)
        list->tail->next = NULL;
    list->size--;
    return t;
}

void *list_peek_front(list_t *list)
{
    if (!list->head)
        return (NULL);
    return (list->head->item);
}

void *list_peek_back(list_t *list)
{
    if (!list->tail)
        return (NULL);
    return (list->tail->item);
}


int list_contain(list_t *list, void *item)
{
    int idx = 0;
    list_foreach(listnode, list) {
        if (listnode->item == item)
            return (idx);
        idx++;
    }
    return (-1);
}

listnode_t *list_get_node_by_index(list_t *list, int index)
{
    if (index < 0 || index >= (int)list_size(list))
        return (NULL);
    int curr = 0;
    list_foreach(listnode, list) {
        if (index == curr)
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
