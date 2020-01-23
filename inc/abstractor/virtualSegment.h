#ifndef _VIRTUAL_SEGMENT_H_
#define _VIRTUAL_SEGMENT_H_

#include "eternity.h"

struct vseg
{
    virtaddr_t start;
    virtaddr_t end;
    uint64     flag;
} __packed;

void vseg_increase(pml4_t *root, struct vseg *seg, uint64 size);
struct vseg *vseg_init(pml4_t *root, virtaddr_t start, virtaddr_t end, uint64 flag);
void vseg_free(pml4_t *root, struct vseg *seg);

#endif