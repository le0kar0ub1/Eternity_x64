#ifndef _PROTOTYPES_H_
#define _PROTOTYPES_H_

void *memsetb(void *ptr, int value, size_t size);
void *memsetw(void *ptr, int value, size_t size);
void *memsetd(void *ptr, int value, size_t size);
void *memsetq(void *ptr, int value, size_t size);

void *memcpyb(void *dest, void *src, size_t size);
void *memcpyw(void *dest, void *src, size_t size);
void *memcpyd(void *dest, void *src, size_t size);
void *memcpyq(void *dest, void *src, size_t size);

void kprint(char const *format, ...);

#endif
