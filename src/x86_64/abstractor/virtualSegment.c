#include "virtualSegment.h"
#include "memory.h"

struct vseg *vseg_init(pml4_t *root, virtaddr_t start, virtaddr_t end, uint64 flag)
{
    struct vseg *seg = kalloc(sizeof(struct vseg));

    seg->start = start;
    seg->end = end;
    seg->flag = flag;
    allocate_segment(root, start, end, flag);
    return (seg);
}

void vseg_free(pml4_t *root, struct vseg *seg)
{
    if (!seg || !root) return;
    free_segment(root, seg->start, seg->end);
    kfree(seg);
}

/* increase virtual segment by the given size using MMAP */
void vseg_increase(pml4_t *root, struct vseg *seg, uint64 size)
{
    fatalAssert(IS_PAGE_ALIGNED(size));
    fatalAssert(root);
    fatalAssert(seg);
    // virtaddr_t end = seg->end;
    // virtaddr_t new = ADD_TO_PTR(end, size);
}