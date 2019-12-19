#ifndef _KHEAP_H_
#define _KHEAP_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"

struct kheap {
    void *start;
    struct kheap *next;
    uint32 sz;
};

struct kheap *kheap;

#endif
