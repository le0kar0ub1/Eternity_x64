#ifndef _PROTOTYPES_H_
#define _PROTOTYPES_H_

#include "types_shortcut.h"

void *memsetb(void *ptr, uint8 value, size_t size);
void *memsetw(void *ptr, uint16 value, size_t size);
void *memsetd(void *ptr, uint32 value, size_t size);
void *memsetq(void *ptr, uint64 value, size_t size);

void *memcpyb(void *dest, void *src, size_t size);
void *memcpyw(void *dest, void *src, size_t size);
void *memcpyd(void *dest, void *src, size_t size);
void *memcpyq(void *dest, void *src, size_t size);

void kprint(char const *format, ...);

#endif
