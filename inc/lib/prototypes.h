#ifndef _PROTOTYPES_H_
#define _PROTOTYPES_H_

#include "types_shortcut.h"
#include "linkedList.h"

void *memset(void *ptr, uint8 value, size_t size);
void *memsetw(void *ptr, uint16 value, size_t size);
void *memsetd(void *ptr, uint32 value, size_t size);
void *memsetq(void *ptr, uint64 value, size_t size);

void *memcpy(void *dest, void *src, size_t size);
void *memcpyw(void *dest, void *src, size_t size);
void *memcpyd(void *dest, void *src, size_t size);
void *memcpyq(void *dest, void *src, size_t size);

void kprint(char const *format, ...);
void kvprint(char const *format, va_list ap);

/* A PART OF CLASSICAL LIB STDLIB.H */
uint64 rand_uintptr(void);
uint32 rand_uint32(void);
uint16 rand_uint16(void);
uint8 rand_uint8(void);
int atoi(char const *s);
long atol(char const *s);

/* A PART OF CLASSICAL LIBC STRING.H */
char *strcpy(char *d, char const *s);
int strlen(char const *s);
int strncmp(char const *s1, char const *s2, size_t size);
int strcmp(char const *s1, char const *s2);
void itoa(char *buf, uint64 n, int base);
void strcat(char *s1, char const *s2);

/* Linked list stolen library management */
list_t *list_create(void);
uint32 list_size(list_t *list);
listnode_t *list_insert_front(list_t *list, void *item);
void list_insert_back(list_t *list, void *item);
void *list_remove_node(list_t *list, listnode_t *node);
void *list_remove_front(list_t *list);
void *list_remove_back(list_t *list);
void list_push(list_t *list, void *item);
listnode_t *list_pop(list_t *list);
void *list_peek_front(list_t *list);
void *list_peek_back(list_t *list);
void list_destroy(list_t *list);
void listnode_destroy(listnode_t *node);
int list_contain(list_t *list, void *item);
listnode_t *list_get_node_by_index(list_t *list, int index);
void *list_remove_by_index(list_t *list, int index);

#endif
