#ifndef _VIRTUAL_SEGMENT_H_
#define _VIRTUAL_SEGMENT_H_

#include "eternity.h"

#define VSEG_RDWR
#define VSEG_PRES
#define VSEG_

struct vseg
{
    virtaddr_t start;
    virtaddr_t end;
    uint64     flag;
};

void vseg_increase(struct vseg *seg, uint64 size);
void vseg_init(struct vseg *seg, virtaddr_t start, virtaddr_t end, uint64 flag);

#endif