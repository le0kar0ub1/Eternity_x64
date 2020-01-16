#ifndef _KHEAP_H_
#define _KHEAP_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"
#include "paging.h"
#include "vmm.h"

/*
** easy to understand the current allocator
** let's build a better one later
*/

struct kheap {
    struct kheap *next;
    uint size;
    bool used;
} __packed;

#define SIZEOF_KHEAPBLOCK sizeof(struct kheap)

void kfree(virtaddr_t ptr);
void init_kalloc(void);
virtaddr_t kalloc(uint size);
void dump_kheap(void);

#endif
