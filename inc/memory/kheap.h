#ifndef _KHEAP_H_
#define _KHEAP_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"
#include "paging.h"
#include "vmm.h"

struct kheap {
    struct kheap *next;
    uint size;
    bool used;
};

#define SIZEOF_KHEAPBLOCK sizeof(struct kheap)

void kfree(virtaddr ptr);
void init_kalloc(void);
virtaddr kalloc(uint size);
void dump_kheap(void);

#endif
