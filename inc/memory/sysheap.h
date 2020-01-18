#ifndef _KHEAP_H_
#define _KHEAP_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"
#include "paging.h"
#include "vmm.h"

/*
** We can only alloc one by one by page with this allocator
*/

struct sysheap {
    virtaddr_t     *start;
    virtaddr_t     *end;   // null when block is free;
} __packed;

#define SIZEOF_SYSHEAPBLOCK sizeof(struct sysheap)

void dump_system_heap(void);
void init_system_alloc(void);
virtaddr_t sysheap_get_free(struct sysheap *start);
virtaddr_t sysheap_new_block(void);
virtaddr_t sysalloc(void);
void sysfree(virtaddr_t ptr);

#endif
