#include "virtualSegment.h"
#include "memory.h"

void vseg_init(struct vseg *seg, virtaddr_t start, virtaddr_t end, uint64 flag)
{
    seg->start = start;
    seg->end = end;
    seg->flag = flag;
}

/* increase virtual segment by the given size using MMAP */
void vseg_increase(struct vseg *seg, uint64 size)
{
    fatalAssert(IS_PAGE_ALIGNED(size));
}