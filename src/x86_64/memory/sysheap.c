#include "sysheap.h"

virtaddr_t sysheap_start;
struct sysheap *sysheap;
struct sysheap *sysheap_curblock;
virtaddr_t kheap_end;
virtaddr_t alloc_iterator;

void dump_system_heap(void)
{
    sysheap = (struct sysheap *)sysheap_start;
    while (sysheap < sysheap_curblock) {
        kprint("BLOCK from %x to %x | Used: %d\n", (uint64)sysheap->start,
        ((uint64)sysheap->end), sysheap->end != NULL);
        sysheap = (struct sysheap *)(((uint64)sysheap) + SIZEOF_SYSHEAPBLOCK);
    }
    kprint("\n");
}

extern virtaddr_t boostrap;
void init_system_alloc(void)
{
    /* panic if segment intersect */
    assert_gt((uint64)boostrap, SYSTEM_HEAP_BASE_START);
    sysheap_start = (virtaddr_t)SYSTEM_HEAP_BASE_START;
    sysheap = (virtaddr_t)SYSTEM_HEAP_BASE_START;
    kheap_end = (virtaddr_t)KHEAP_BASE_END;
    /* init a block to get a fast mallo */
    alloc_iterator = (virtaddr_t)SYSTEM_HEAP_START_ALLOC;
    sysheap->start = alloc_iterator;
    sysheap->end = NULL;
    alloc_iterator = (virtaddr_t)(((uint64)alloc_iterator) + PAGE_SIZE);
    sysheap_curblock = sysheap;
}

bool sysheap_isfree(struct sysheap *cur, uint nbr)
{
    uint64 start = (uint64)(cur->start);
    struct sysheap *next = (struct sysheap *)(((uint64)cur) + SIZEOF_SYSHEAPBLOCK);
    if (next == sysheap_curblock && nbr > 0x1)
        return (false);
    uint64 end = (uint64)(next->start);
    if (start + (PAGE_SIZE * nbr) <= end)
        return (true);
    return (false);
}

virtaddr_t sysheap_get_free(struct sysheap *start, uint nbr)
{
    while (start < sysheap_curblock) {
        if (start->end == NULL && sysheap_isfree(start, nbr)) {
            start->end = (virtaddr_t)(((uint64)start->start) + PAGE_SIZE);
            return (start->start);
        }
        start = (struct sysheap *)(((uint64)start) + SIZEOF_SYSHEAPBLOCK);
    }
    return (NULL);
}

virtaddr_t sysheap_new_block(uint nbr)
{
    virtaddr_t alloc = alloc_iterator;
    sysheap_curblock->start = alloc;
    sysheap_curblock->end = (virtaddr_t)(((uint64)alloc) + (PAGE_SIZE * nbr));
    alloc_iterator = (virtaddr_t)(((uint64)alloc) + (PAGE_SIZE * nbr));
    sysheap_curblock = (struct sysheap *)(((uint64)sysheap_curblock) + SIZEOF_SYSHEAPBLOCK);
    return (alloc);
}

virtaddr_t sysalloc(uint size)
{
    if (size == 0x0 || !IS_PAGE_ALIGNED(size))
        PANIC("System allocator allow only 0x1000 aligned size");
    size = size / PAGE_SIZE;
    virtaddr_t allocated = NULL;
    sysheap = (struct sysheap *)sysheap_start;

    allocated = sysheap_get_free(sysheap, size);   
    if (allocated)
        return (allocated);
    else
        allocated = sysheap_new_block(size);
    if (!allocated)
        PANIC("Kernel is running out of sysheap\n");
    return (allocated);
}

void sysfree(virtaddr_t ptr)
{
    sysheap = (struct sysheap *)sysheap_start;

    while (sysheap < sysheap_curblock) {
        if (sysheap->start == ptr) {
            sysheap->end = NULL;
            return;
        }
        sysheap = (struct sysheap *)(((uint64)sysheap) + SIZEOF_SYSHEAPBLOCK);
    }
    PANIC("Invalid pointer in sysheap free\n");
}