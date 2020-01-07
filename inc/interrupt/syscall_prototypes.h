#ifndef _SYSCALL_PROTOTYPES_H
#define _SYSCALL_PROTOTYPES_H

#include "typedef.h"

/* managers */
void register_syscall_handler(uint64, void *);
void syscall_register_init(void);

/* syscalls */
int64 syscall_write(char c);

#endif