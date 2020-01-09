#ifndef _SYSCALL_PROTOTYPES_H
#define _SYSCALL_PROTOTYPES_H

#include "typedef.h"

/* managers */
void register_syscall_handler(uint64, void *);
void syscall_register_init(void);

/* syscalls */
int64 syscall_write(uint64 sz, void *s, uint64 fd);
void syscall_exit(int status);
int64 syscall_exec(void *, char *);

/* userspace access */
int64 write(uint64 sz, void *s, uint64 fd);
void exit(int status);
int64 exec(void *, char const *);

#endif