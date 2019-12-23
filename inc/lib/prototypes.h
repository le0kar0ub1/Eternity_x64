#ifndef _PROTOTYPES_H_
#define _PROTOTYPES_H_

#include "types_shortcut.h"

void *memset(void *ptr, uint8 value, size_t size);
void *memsetw(void *ptr, uint16 value, size_t size);
void *memsetd(void *ptr, uint32 value, size_t size);
void *memsetq(void *ptr, uint64 value, size_t size);

void *memcpy(void *dest, void *src, size_t size);
void *memcpyw(void *dest, void *src, size_t size);
void *memcpyd(void *dest, void *src, size_t size);
void *memcpyq(void *dest, void *src, size_t size);

void kprint(char const *format, ...);

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

#endif
