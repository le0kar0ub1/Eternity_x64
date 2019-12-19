#include "eternity.h"
#include "kheap.h"

struct kheap *kheap;
uint64 kheapPageCycle = 0x0;

void *kalloc(uint size)
{
    if (!size)
        return (NULL);
    return (NULL);
}

/* for the moment just let the segment & set size to 0 == free */
void kfree(void *ptr)
{
    struct kheap *heap = kheap;

    for (; heap; heap = heap->next)
        if (heap->start == ptr)
            heap->sz = 0x0;
    PANIC("Invalid pointer in kfree\n");
}
